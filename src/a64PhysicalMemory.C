#include <string.h>

using namespace std;

#include "a64PhysicalMemory.h"

//===================================================================================================
// MemBlock - simulator memory is managed as a set of dynamically allocated blocks of a fixed size...
//===================================================================================================

MemBlock::MemBlock() : mptr(NULL), mptr_init(NULL), free_bytes(0), initial_byte_value(RANDOM_INITIAL_VALUE), verbose(false) {};

MemBlock::~MemBlock() { 
  if (mptr) delete [] mptr; // mptr points to a memory blocks current value
   mptr = NULL;

   if (mptr_init) delete [] mptr_init; // mptr_init points to the initial value for a memory block
   mptr_init = NULL;

   free_bytes = 0; // until we allocate the block there are no free bytes
}

// the address of a memory block is aligned to the size of the block...
unsigned long long MemBlock::BlockAddress(unsigned long long address) {
  return address & ~((unsigned long long) PM_BLOCK_SIZE - 1ull); 
}

// for a given address return the offset into its memory block...
int MemBlock::Offset(unsigned long long address) {
  return (int)(address & (PM_BLOCK_SIZE - 1));
}

// some simple checks on memory block access parameters...
void MemBlock::ValidateAccess(int offset,unsigned char *buffer,int number_of_bytes) {
  if (!buffer) throw MEM_ERROR;
  if ((offset < 0) || (offset >= PM_BLOCK_SIZE)) throw MEM_ERROR;
  if ((number_of_bytes <= 0) || (number_of_bytes > PM_BLOCK_SIZE)) throw MEM_ERROR;

  if ((offset + number_of_bytes) > PM_BLOCK_SIZE) throw SPLIT_ACCESS; // access spans two blocks...
}

// allocate a memory block. mark all bytes as free...
void MemBlock::AllocateBlock() { 
  if (mptr) return; // already have this block allocated... 
  mptr = new unsigned char[PM_BLOCK_SIZE]; //<---block allocated
  free_bytes = 0xffffffffffffffffull;    //<---all bytes in block free; thus max buffer size is 64 bytes
  //printf("[MemBlock::AllocateBlock] new block allocated...\n");
}

// initial memory value can be a random number, or a specific value...
unsigned char MemBlock::InitialByteValue() {
  return (unsigned char) ( (initial_byte_value == RANDOM_INITIAL_VALUE) ? (rand() & 0xff) : initial_byte_value );
}

// allocate the initial memory storage for a memory block...
void MemBlock::AllocateInitBlock() { 
  if (mptr_init) return; // already have this block allocated... 
  mptr_init = new unsigned char[PM_BLOCK_SIZE];

  // initialize all bytes of initial memory...
  // since we are initializing all bytes, there is no concept of free bytes
  for (int i = 0; i < PM_BLOCK_SIZE; i++) {
     mptr_init[i] = InitialByteValue();
  }
  //printf("[MemBlock::AllocateInitBlock] new init block allocated...\n");
}

// return memory block byte value...
unsigned char MemBlock::ReadByte(int buffer_index) {
  return mptr[buffer_index];
}

// return initial value for an indexed memory block byte...
unsigned char MemBlock::ReadFreeByte(int index) {
  return mptr_init[index];
}

// write to memory block byte. clear corresponding free byte marker (bit) for
// this byte. The free bytes markers are used when laying down new instructions
// to be executed and one needs to know if existing instructions (or data) are
// near...
void MemBlock::WriteByte(int buffer_index,unsigned char byte_val, bool is_initial_value) {
  mptr[buffer_index] = byte_val;
  // lsb of free_bytes equates to msb of memory block: if mptr[0] is free, free_bytes[0] == 1 
  free_bytes &= ~(1ull<<buffer_index); //<---clear bit corresponding to buffer index

  if (is_initial_value)
    mptr_init[buffer_index] = byte_val;
}

// check the free-bytes marker for some specified byte of a memory block...
bool MemBlock::ByteIsFree(int buffer_index) {
  return (free_bytes & (1ull<<buffer_index)) != 0ull;
}

// return count of used bytes in a memory block...
int MemBlock::ByteCount() {
  int bcnt = 0;
  for (int i = 0; i < PM_BLOCK_SIZE; i++) {
    if (!ByteIsFree(i)) bcnt += 1;
  }
  return bcnt;
}

// return the initial values for a memory block - used in particular when writing out an
// ELF file containing instructions (in .text section) and data (in .data section). The data
// values that should be written should be the initial values, not the current values...
void MemBlock::ReadInitialState(unsigned long long address,unsigned char *buffer,bool is_data) {
  if (Offset(address) != 0) throw MEM_ERROR; //<---must be block aligned address
  if (buffer == NULL) throw MEM_ERROR;       //<---crude check on buffer ptr

  unsigned char *src_mem = is_data ? mptr_init : mptr;

  if (src_mem == NULL) throw MEM_ERROR;      //<---how could the resulting memory block pointer be null???

  memcpy(buffer,src_mem,PM_BLOCK_SIZE);
}

// 'initial' memory is allocated/initialized on reads only
//    we assume when memory is written to, its initial value is not important.
//    (on the other hand we allocate initial memory on reads or writes for uniformity's sake)
//  Intended policy:
//    1. instructions and data do not share memory blocks.
//    2. for instructions:
//       a. keep track of free bytes, only initializing bytes as they are used
//       b. instruction memory is treated as read-only
//       c. current state of instruction memory may be used when writing elf file
//    3. for data:
//       a. allocate and initialize an entire memory block on any read - call this initial (data) memory
//       b. for reads from unitialized memory, initial values are from initial memory
//       c. writes affect current memory state only
//       c. initial memory may be used when writing data to elf file

int MemBlock::Write(unsigned long long address,unsigned char *buffer,int number_of_bytes, bool initial_values) {

  if (verbose) printf("[MemBlock::Write] address: 0x%llx #bytes: %d\n",address,number_of_bytes);

  int offset = Offset(address);

  ValidateAccess(offset,buffer,number_of_bytes);
  AllocateBlock();
  AllocateInitBlock();

  for (int i = 0; i < number_of_bytes; i++) { 
    WriteByte(offset + i,buffer[i],initial_values);
  }
 
  if (ByteCount() == 0) throw MEM_ERROR;  // we just added some bytes. how could this block be empty???

  return 0;  
}

int MemBlock::Read(unsigned long long address,unsigned char *buffer,int number_of_bytes, bool init_if_free) {

  if (verbose) printf("[MemBlock::Read] address: 0x%llx #bytes: %d, init-if-free? %d\n",address,number_of_bytes,init_if_free);

  int offset = Offset(address);

  ValidateAccess(offset,buffer,number_of_bytes);
  AllocateBlock();
  AllocateInitBlock();

  int undef_count = 0;

  for (int i = 0; i < number_of_bytes; i++) {
     int buffer_index = offset + i; 

     unsigned char next_byte_value = ReadFreeByte(buffer_index); // assume byte is not in current memory

     if (ByteIsFree(buffer_index)) {
       if (init_if_free)
         WriteByte(buffer_index,next_byte_value,false); // update current memory
       undef_count += 1;
     } else {
       next_byte_value = ReadByte(buffer_index); // read from current memory 
     }

     buffer[i] = next_byte_value;
  }

  if ((ByteCount() == 0) && init_if_free) {
    throw MEM_ERROR;  // some bytes should be initialized, how could this block be empty???
  }

  int rcode = ALL_BYTES_DEFINED; // return code of zero means all memory at the requested locations has value

  if (undef_count == number_of_bytes)
    rcode = ALL_BYTES_FREE; // all memory at the requested locations is free
  else if (undef_count > 0)
    rcode = SOME_BYTES_UNDEFINED; // one or more bytes at the requested locations is undefined

  if (verbose) printf("[MemBlock::Read] rcode: %d\n",rcode);

  return rcode;
}


//============================================================================================
//============================================================================================

PhysicalMemory::PhysicalMemory() : block_size(PM_BLOCK_SIZE), verbose(false) {
#ifdef DO_TRACE
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  mt = new scaffold_SAPI::Memory;
#endif
}

PhysicalMemory::~PhysicalMemory() {
#ifdef DO_BLOCKMEM_SUMMARY 
  //int bytesize = (8 + 1) * physical_memory.size();
  int sim_blocksize = PM_BLOCK_SIZE;
  int bytes_allocated_sim = 0;  //sim_blocksize * physical_memory_by_block.size();

  // add up actual bytes in use by simulator...

  int block_cnt        = 0;  // actual # of blocks allocated, not size of map
  int full_block_cnt   = 0;  // all bytes in block allocated
  int empty_block_cnt  = 0;  // block completely empty (how did this happen?)
  int sparce_block_cnt = 0;  // 4 or less bytes used in block

  for (unordered_map<unsigned long long,MemBlock>::iterator i = physical_memory_by_block.begin(); i != physical_memory_by_block.end(); i++) {
     //printf("Next block addr: 0x%llx\n",(*i).first);
     block_cnt += 1;
     int bcnt = (*i).second.ByteCount();
     bytes_allocated_sim += bcnt;
     if (bcnt == PM_BLOCK_SIZE) full_block_cnt += 1;
     else if (bcnt == 0) empty_block_cnt += 1;
     else if (bcnt <= 4) sparce_block_cnt += 1;
     //if (bcnt == 0) {
     //  printf("EMPTY BLOCK: block-addr: 0x%llx used-count: %d, free-bytes: 0x%llx\n",(*i).first,(*i).second.ByteCount(),(*i).second.FreeBytes());
     //}
  }

  int blocksize       = sizeof(MemBlock) + sizeof(unsigned long long) + PM_BLOCK_SIZE;
  int bytes_allocated = blocksize * block_cnt; 
  int bytes_recorded  = (block_cnt - empty_block_cnt) * PM_BLOCK_SIZE;
  printf("block size: %d, approx memory allocated: %d blocks (%d bytes)\n",blocksize,block_cnt,bytes_allocated);
  printf("simulator bytes per block: %d, actual #bytes simulator memory marked as used: %d)\n",sim_blocksize,bytes_allocated_sim);
  printf("# of full blocks: %d, # of empty blocks: %d, # of sparcely-filled blocks: %d\n",
         full_block_cnt,empty_block_cnt,sparce_block_cnt);
  printf("# of bytes to record in elf file: %d (raw size, prior to packing)\n",bytes_recorded);
#endif

#ifdef DO_TRACE
  {
   fstream output(TRACE_FILE, ios::out | ios::trunc | ios::binary);

    if (!output) {
      cerr << "Error: failed to open memory trace file '" << TRACE_FILE << "'" << endl;
      return;
    }

    if (!mt->SerializeToOstream(&output)) {
      cerr << "Error: failed to write memory trace file." << endl;
    }

    cout << "  Memory trace file " << TRACE_FILE << " created." << endl;
  }

  google::protobuf::ShutdownProtobufLibrary();
#endif
}

int PhysicalMemory::BlockWrite(unsigned long long address,unsigned char *buffer,int number_of_bytes,bool initial_values) {
  if (verbose) printf("[PhysicalMemory::BlockWrite] address: 0x%llx #bytes: %d, initial values? %d\n",address,number_of_bytes,initial_values);

  try {
    physical_memory_by_block[MemBlock::BlockAddress(address)].Write(address,buffer,number_of_bytes,initial_values);
  }
  catch(MBLOCK_ERROR merr) {
    int rcode = merr;
    if (rcode != SPLIT_ACCESS) throw MEM_ERROR;

    // access crossed blocks...

    unsigned long long address_1st_line = MemBlock::BlockAddress(address);
    unsigned long long address_2nd_line = address_1st_line + PM_BLOCK_SIZE;

    int numbytes_1st_line = PM_BLOCK_SIZE - MemBlock::Offset(address);
    int numbytes_2nd_line = number_of_bytes - numbytes_1st_line;

    physical_memory_by_block[address_1st_line].Write(address,buffer,numbytes_1st_line,initial_values);
    physical_memory_by_block[address_2nd_line].Write(address + numbytes_1st_line,&buffer[numbytes_1st_line],numbytes_2nd_line,initial_values);
  }

  return 0;
}

// a read from initial memory state always returns a block of data...

void PhysicalMemory::ReadInitialState(unsigned long long address,unsigned char *buffer,bool is_data) {
  if (MemBlock::Offset(address) != 0) throw MEM_ERROR; //<---must be block aligned address
  physical_memory_by_block[address].ReadInitialState(address,buffer,is_data);
}


int PhysicalMemory::BlockRead(unsigned long long address,unsigned char *buffer,bool init_if_free,int number_of_bytes) {
  if (verbose) printf("[PhysicalMemory::BlockRead] address: 0x%llx #bytes: %d\n",address,number_of_bytes);

  int rcode = 0;

  unsigned long long address_1st_line = MemBlock::BlockAddress(address);

  if (verbose) printf("[PhysicalMemory::BlockRead] address (1st line): 0x%llx\n",address_1st_line);

  try {
     rcode = physical_memory_by_block[address_1st_line].Read(address,buffer,number_of_bytes,init_if_free);
  }
  catch(MBLOCK_ERROR merr) {
    if (merr != SPLIT_ACCESS) throw MEM_ERROR;

    // access crossed blocks...

    unsigned long long address_1st_line = MemBlock::BlockAddress(address);
    unsigned long long address_2nd_line = address_1st_line + PM_BLOCK_SIZE;

    int numbytes_1st_line = PM_BLOCK_SIZE - MemBlock::Offset(address);
    int numbytes_2nd_line = number_of_bytes - numbytes_1st_line;

    int rcode1 = physical_memory_by_block[address_1st_line].Read(address,buffer,numbytes_1st_line,init_if_free);
    int rcode2 = physical_memory_by_block[address_2nd_line].Read(address + numbytes_1st_line,&buffer[numbytes_1st_line],numbytes_2nd_line,init_if_free);

    if (verbose) printf("[PhysicalMemory::BlockRead] rcode1: %d rcode2: %d\n",rcode1,rcode2);
    if (rcode1 == rcode2) {
      rcode = rcode1; // both sides of the access yield same result...
    } else {
      rcode = SOME_BYTES_UNDEFINED; // on one side of the other, one or more bytes were undefined...
    }
  }

  if (verbose) printf("[PhysicalMemory::BlockRead] rcode: %d\n",rcode);
  return rcode;
}

#define USE_BLOCK_STORE 1

int PhysicalMemory::Write(unsigned long long address,unsigned char *buffer,int number_of_bytes,bool initial_values) {
  if (verbose) printf("[PhysicalMemory::Write] address: 0x%llx #bytes: %d, initial-values? %d\n",address,number_of_bytes,initial_values);

#ifdef USE_BLOCK_STORE
  BlockWrite(address,buffer,number_of_bytes,initial_values);
#else
  for (int i = 0; i < number_of_bytes; i++) {
     physical_memory[address + i] = buffer[i];
     if (verbose) printf("   0x%llx: 0x%x\n",(address + i),buffer[i]);
  }
#endif

  //for (int i = 0; i < number_of_bytes; i++) {
  //   if (tbuf[i] != buffer[i])
  //     throw MEM_ERROR;
  //}

#ifdef DO_TRACE
  {
  scaffold_SAPI::PhysMemBlock *mb = mt->add_phys_mem();
  mb->set_address(address);
  mb->set_size(number_of_bytes);
  mb->set_read(false);
  mb->set_do_init(false);
  mb->set_memblock((void *) buffer,number_of_bytes);
  mb->set_block_address(  MemBlock::BlockAddress(address));

  //mb->set_blockmem((void *) tbuf,number_of_bytes);

  mb->set_free_bytes(physical_memory_by_block[MemBlock::BlockAddress(address)].FreeBytes());
  }
#endif

  return 0;
}

int PhysicalMemory::Read(unsigned long long address,unsigned char *buffer,bool init_if_free,int number_of_bytes) {
  int rcode;

  if (verbose) printf("[PhysicalMemory::Read] address: 0x%llx #bytes: %d init? %d\n",address,number_of_bytes,init_if_free);

#ifdef USE_BLOCK_STORE
  rcode = BlockRead(address,buffer,init_if_free,number_of_bytes);
#else
  int undef_count = 0;

  for (int i = 0; i < number_of_bytes; i++) {
    unsigned long long next_byte_address = address + i;
    unsigned char next_byte_value = MEM_UNDEF_VAL;

    if (physical_memory.find(next_byte_address) == physical_memory.end()) {
      if (init_if_free)
         physical_memory[address + i] = MEM_UNDEF_VAL;
      undef_count += 1;
      if (verbose) printf("   byte at address 0x%llx undefined: 0x%x\n",next_byte_address,next_byte_value);
    } else {
      next_byte_value = physical_memory[address + i];
      if (verbose) printf("   byte at address 0x%llx IS DEFINED: 0x%x\n",next_byte_address,next_byte_value);
    }

    buffer[i] = next_byte_value;
  }

  rcode = ALL_BYTES_DEFINED; // return code of zero means all memory at the requested locations has value

  if (undef_count == number_of_bytes)
    rcode = ALL_BYTES_FREE; // all memory at the requested locations is free
  else if (undef_count > 0)
    rcode = SOME_BYTES_UNDEFINED; // one or more bytes at the requested locations is undefined

  if (verbose) printf("[PhysicalMemory::Read] undef-count: %d rcode: %d\n",undef_count,rcode);
#endif

  //for (int i = 0; i < number_of_bytes; i++) {
  //   if (tbuf[i] != buffer[i])
  //     throw MEM_ERROR;
  //}

#ifdef DO_TRACE
  {
  scaffold_SAPI::PhysMemBlock *mb = mt->add_phys_mem();
  mb->set_address(address);
  mb->set_size(number_of_bytes);
  mb->set_read(true);
  mb->set_do_init(init_if_free);
  mb->set_outcome(rcode);
  mb->set_memblock((void *) buffer,number_of_bytes);  
  mb->set_block_address(  MemBlock::BlockAddress(address));

  //mb->set_blockmem((void *) tbuf,number_of_bytes);

  mb->set_free_bytes(physical_memory_by_block[MemBlock::BlockAddress(address)].FreeBytes());
  }

#endif

  if (verbose) printf("[PhysicalMemory::Read] rcode: %d\n",rcode);

  return rcode;
}

void PhysicalMemory::AddressList(vector<unsigned long long> &all_mem_addresses, bool skip_empty_blocks) {
  //for (unordered_map<unsigned long long,unsigned char>::iterator i = physical_memory.begin(); i != physical_memory.end(); i++) {
  //  all_mem_addresses.push_back(i->first);
  //}
  
  for (unordered_map<unsigned long long,MemBlock>::iterator i = physical_memory_by_block.begin(); i != physical_memory_by_block.end(); i++) {
    if (!skip_empty_blocks || (i->second.ByteCount() > 0))
      all_mem_addresses.push_back(i->first); // <---block addresses that is...
  }
}


