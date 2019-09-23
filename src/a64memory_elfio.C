#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <unordered_map>
#include <memory>

//#define FOR_MAC_IOS 1


#ifdef FOR_MAC_IOS
#import "a64Scaffold.h"
#endif

using namespace std;

#include "a64sim.h"
#include "a64_exceptions.h"
#include "SimTrace.h"
#include "a64Scaffold.h"

extern "C" {
  #include "elfio.h"
};

//=================================================================================================================================
// Save - write out simulator memory to ELF file...
//
// NOTES:
// -------
//    1. Elf file format does not support block counts (ELF sections count) exceeding 16 bits. Thus larger block sizes must
//       be employed when writing large tests in ELF format. 
//
//    2. For typical large random test, minimal block size will likely be 2**16 
//       (to cover 32 bit address space without exceeding ELF file max sections count)
//
//    3. Block sizes above 16 will only result when the physical memory emulated exceeds 32 bits 
//       - WE THEN COULD QUERY THE PROCESSOR SETUP THEN TO DETERMINE WHAT MAXIMUM BLOCK SIZE TO USE
//=================================================================================================================================

int Scaffold::Save(Memory &mem, string &elf_file, bool compress, bool verbose) {
  if (verbose) printf("\n[Save] entered. Write physical memory to ELF file...\n");

  vector<unsigned long long> test_block_addresses;  // list of memory blocks used, each of size PM_BLOCK_SIZE   
  mem.TestBlockAddresses(test_block_addresses,verbose);

  if (compress) {
    /* Produce smallest ELF file image possible. If necessary, use ELF extended section numbering. */
    /* Some elf readers (in particular, if they use BSF libelf or C++ elfio) may not support       */
    /* extended section numbering...                                                               */
    return SaveToELF(mem,elf_file,test_block_addresses,PM_BLOCK_SIZE,verbose);
  }

  /* write larger blocks of memory, ie, smaller number of ELF sections will result, AND the */
  /* resulting ELF file will be much larger...                                              */

  int file_block_size_in_bits;
  unsigned int file_block_count;

  if (!ChooseFileBlockSize(file_block_size_in_bits,file_block_count,test_block_addresses,verbose)) {
    printf("Save aborted.\n");
    return -1;
  }

  int file_block_size = 1<<file_block_size_in_bits;

  vector<unsigned long long> file_block_addresses;
  unsigned long long addr_mask = ~((1ull<<file_block_size_in_bits) - 1ull);

  mem.SetFileBlockAddresses(file_block_addresses,test_block_addresses,addr_mask,verbose);

  if (verbose) printf("  starting elf file...\n");

  return SaveToELF(mem,elf_file,file_block_addresses,file_block_size,verbose);
}


//=================================================================================================================================
// SaveToELF - write out list of simulator memory blocks (of fixed size) to ELF file...
//=================================================================================================================================

int Scaffold::SaveToELF(Memory &mem, string &elf_file, vector<unsigned long long> &file_block_addresses, int file_block_size, bool verbose) {
  //verbose = true;

  if (verbose) printf("\n[SaveToELF] entered. Write physical memory to ELF file %s...\n",elf_file.c_str());

  void *edata = NULL;
  char err_msg[1024];

  int rcode = 0;

  if ((rcode = elfio_init(&edata,(char *) elf_file.c_str(),1,err_msg))) {
    fprintf(stderr,"Save to ELF failed: %s\n",err_msg);
    return rcode;
  }

  vector<unsigned char *> block_data;

  for (unsigned int i = 0; i < file_block_addresses.size(); i++) {
     unsigned long long section_address = file_block_addresses[i];

     // sanity check on section address: is it aligned to the block size???

     if ((section_address & (file_block_size - 1)) != 0) {
       fprintf(stderr,"INTERNAL ERROR: section address (0x%llx) is not aligned to the section size (%d).\n",
               section_address,file_block_size);
       return -1;
     }
 
     int section_size = file_block_size;

     if (verbose) printf("Writing next ELF section %u, address: 0x%llx, size: %d...\n",i,section_address,section_size);

     // initialize section from physical memory...

     unsigned char *section_data = new unsigned char[section_size];

     block_data.push_back(section_data); //<---used to keep track of local memory allocations, to be deleted at the end of this method

     bool is_data = mem.InvalidRegionAccess(section_address,INSTRUCTION,0,1,false);

     if (section_size <= PM_BLOCK_SIZE) {
         for (int j = 0; j < section_size; j++) {
	   section_data[j] = 0;
	 }

         mem.ReadInitialState(section_address,section_data,is_data);

         if (verbose) {
           printf("0x%llx/%s (%d) : ",section_address,(is_data ? "DATA" : "INSTR"),section_size);
           for (int j = 0; j < section_size; j++) {
              printf(" %2.2x",(unsigned char) section_data[j]);
           }
           printf("\n");
	 }
     } else {
       for (int j = 0; j < section_size; j++) {
          unsigned char tbuf[128];
          section_data[j] = (mem.ReadPhysicalMemory(section_address + j,1,tbuf,true) == ALL_BYTES_DEFINED) ? tbuf[0] : 0;
       }
     }

     // create a new section for this block of data...

     if ((rcode = elfio_add_section(&edata,section_address,is_data,section_data,file_block_size,err_msg))) {
       fprintf(stderr,"Save to ELF failed: %s\n",err_msg);
       break;
     }
  }

  if (verbose) printf("  done.\n");

  if (verbose) printf("# of sections written: %lu\n",file_block_addresses.size());

  //if (verbose) printf("Program entry point: 0x%llx\n",start_address); //<---not setting entry point. not sure if this matters

  if (!rcode)
    rcode = elfio_fini(&edata,err_msg);

  for (unsigned int i = 0; i < block_data.size(); i++) {
     delete [] block_data[i];
  }

  if (verbose) printf("\n[SaveToELF] exited, rcode: %d\n",rcode);

  return rcode;
}


//=================================================================================================================================
// Load - initialize simulator memory from ELF file...
//=================================================================================================================================

int Scaffold::Load(Memory &mem, string &elf_file, bool verbose) {
  printf("Loading test from ELF file '%s'...\n",elf_file.c_str());

  //verbose = true;
  
  void *edata = NULL;
  char err_msg[1024];

  int rcode = 0;

  if ((rcode = elfio_init(&edata,(char *) elf_file.c_str(),0,err_msg))) {
    fprintf(stderr,"Load (from ELF) failed: %s\n",err_msg);
    return rcode;
  }

  if (verbose) printf("reader initialized...\n");

  bool more_to_read = true;

  while(more_to_read) {
    if (verbose) printf("reading next section...\n");

    unsigned long long address;
    char section_name[1024];
    unsigned char *section_data;
    int is_data;
    section_name[0] = '\0';
    int size_in_bytes = 0;

    if ((rcode = elfio_read_next_section(&edata,section_name,&address,&is_data,&section_data,&size_in_bytes,err_msg))) {
      fprintf(stderr,"%s\n",err_msg);
      break;
    }

    if (verbose) printf("section: '%s'\n",section_name);

    if (size_in_bytes <= 0) { // break when section read count is zero...
      if (verbose) printf("empty section!\n");
      continue;
    }

    // if we hit the symbol table or string table we will ASSUME we are done...
    
    if (!strncmp(section_name,".symtab",7) || !strncmp(section_name,".strtab",7)) {
      if (verbose) printf("symtable reached. Will ASSUME no more sections to process...\n:");
      break;
    }
    
    if (strncmp(section_name,".text",5) && strncmp(section_name,".data",5) && strncmp(section_name,".rodata",7)) {
      // for now we only recognize .text or .data or .rodata
      continue;
    }

    int num_blocks = size_in_bytes / PM_BLOCK_SIZE;
    int extra_bytes = size_in_bytes % PM_BLOCK_SIZE;

    if (verbose) 
      printf("section %s, total size in bytes: %d, # blocks: %d, remainder: %d\n",section_name,size_in_bytes,num_blocks,extra_bytes);

    int block_offset = 0;

    for (int i = 1; i <= num_blocks; i++) {
       try {
          mem.WritePhysicalMemory(address + block_offset,PM_BLOCK_SIZE,&section_data[block_offset]);
       } catch(SIM_EXCEPTION_CLASS eclass) {
	 fprintf(stderr,"Load failed (on memory block write): section: '%s', address: 0x%llx size: %d\n",
                 section_name,address + block_offset,PM_BLOCK_SIZE);
         return -1;
       }

       if (verbose) {
         unsigned char mbuf[PM_BLOCK_SIZE];
         for(int k = 0; k < PM_BLOCK_SIZE; k++) mbuf[k] = 0;
         int rcode = mem.ReadPhysicalMemory(address + block_offset,PM_BLOCK_SIZE,mbuf,false);
         if (rcode) { 
           printf("PROBLEMS READING BACK ELF-INITIALIZED MEMORY???\n");
	   return rcode;
         }
         printf("<%s> 0x%llx (%d) : ",section_name,address + block_offset,PM_BLOCK_SIZE);
         for (int j = 0; j < PM_BLOCK_SIZE; j++) {
            printf(" %2.2x",(unsigned char) mbuf[j]);
         }
         printf("\n");
       }
       block_offset += PM_BLOCK_SIZE;
    }

    if (extra_bytes > 0) {
      try {
         mem.WritePhysicalMemory(address + block_offset,extra_bytes,&section_data[block_offset]);
       } catch(SIM_EXCEPTION_CLASS eclass) {
	 fprintf(stderr,"Load failed (on memory block write): section: '%s', address: 0x%llx size: %d\n",
                 section_name,address + block_offset,PM_BLOCK_SIZE);
         return -1;
       }
       if (verbose) {
         unsigned char mbuf[extra_bytes];
         int rcode = mem.ReadPhysicalMemory(address + block_offset,extra_bytes,mbuf,false);
         if (rcode) { 
           printf("PROBLEMS READING BACK ELF-INITIALIZED MEMORY???\n");
	   return rcode;
         }
         printf("<%s> 0x%llx (%d) : ",section_name,address + block_offset,extra_bytes);
         for (int j = 0; j < extra_bytes; j++) {
            printf(" %2.2x",(unsigned char) mbuf[j]);
         }
         printf("\n");
       }
    }
  }

  printf("Done.\n");

  return 0;
}

//=================================================================================================================================
// Save - write out simulator memory to ELF file...
//
// NOTES:
// -------
//    1. Elf writer in use is slow, so merging blocks (into elf sections) when possible to reduce the number of sections to write.
//    2. Blocks of memory containing data only are NOT written. Thus initial values for memory associated with load/stores is 
//       NOT supported.
//=================================================================================================================================

unsigned long long Scaffold::estimateELFFileSize(unsigned int &resulting_block_count,vector<unsigned long long> &program_block_addresses, 
                                               int desired_block_size, bool verbose) {
  if (verbose) printf("[estimateELFFileSize] entered...\n");
  if (verbose) printf("    # of blocks: %lu, desired block size (# of bits): %d\n",program_block_addresses.size(),desired_block_size);

  unsigned long long block_offset_bits  = (1ull<<desired_block_size) - 1;
  unsigned long long block_address_mask = ~block_offset_bits;

  if (verbose) printf("    block address/offset masks: 0x%llx/0x%llx\n",block_address_mask,block_offset_bits); 
  
  vector<unsigned long long> elf_block_addresses;

  unsigned long long current_block_address = 0;

  for (unsigned int i = 0; i < program_block_addresses.size(); i++) {
     unsigned long long next_block_addr = program_block_addresses[i] & block_address_mask;
     if (next_block_addr != current_block_address) {
       elf_block_addresses.push_back(next_block_addr);
       current_block_address = next_block_addr; //<---data in this block could be merged in here
     }
  }

  resulting_block_count = elf_block_addresses.size();
  unsigned long long estimated_size = (1ull<<desired_block_size) * elf_block_addresses.size();
 
  if (verbose) 
     printf("[estimateELFFileSize] exited, # of merged blocks: %u, estimated ELF file size: 0x%llx\n",
            resulting_block_count,estimated_size);

  return estimated_size;
}

//=================================================================================================================================
// ChooseFileBlockSize - based on the number of memory blocks in use, choose a memory block size to use when writing an ELF
//                       file...
//=================================================================================================================================

#define ELF_MAX_SECTIONS 0xff00 

bool Scaffold::ChooseFileBlockSize(int &block_size_in_bits, unsigned int &resulting_block_count, 
                                vector<unsigned long long> &test_block_addresses,bool verbose) {

  block_size_in_bits    = PM_BLOCK_SIZE_LOG2; //default physical memory block size in bits
  resulting_block_count = test_block_addresses.size();

  if (test_block_addresses.size() >= ELF_MAX_SECTIONS) {
    if (verbose) { 
      printf("  # of memory blocks to write to ELF file will cause the maximum # of sections in an ELF file (%u) to be exceeded...\n",
             ELF_MAX_SECTIONS);
      printf("  Choosing larger block size...\n");
    }

    // powers of two, starting with 4k page...

    int trial_block_sizes[] = { 12,13,14,15,16,20,24,32,0 };

    for (int i = 0; trial_block_sizes[i] != 0; i++) {
       block_size_in_bits = trial_block_sizes[i];
       estimateELFFileSize(resulting_block_count,test_block_addresses,block_size_in_bits,verbose);
       if (resulting_block_count < ELF_MAX_SECTIONS)
         break;
    }

    if (resulting_block_count > ELF_MAX_SECTIONS) {
      printf("[SAVE] ELF max file sections count (%d) exceeded. Test memory footprint too large.\n",ELF_MAX_SECTIONS);
      return false;
    }
  }

  if (verbose) printf("  Block size chosen: %d bits (0x%llx bytes)\n",block_size_in_bits,1ull<<block_size_in_bits);

  return true;
}

