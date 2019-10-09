#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <omp.h>
#include <unordered_set>
#include <iostream>

#include <assert.h>

#include "a64sim.h"
#include "a64_exceptions.h"
#include "a64_vmsa.h"

using namespace std;

//#define MEM_DEBUG 1
//#define DEVICE_MEM_DEBUG 1
//#define TEST_TLBS 1
//#define ARMV8_FOUNDATION_MODEL 1

#define NO_MIXED_ACCESSES 1
#define IGNORE_UPPER_PA_BITS 1

//==========================================================================================
// Memory class
//==========================================================================================

Memory::Memory() : monitor(NULL), block_size(PM_BLOCK_SIZE), physical_address_lo(0), physical_address_hi(0) {
};

Memory::~Memory() {
  ClearBlockStorage();
}

//***********************************************************************************************************
// ReadMemory, WriteMemory - the simulator 'supplied' read/write memory methods (for historical and in
// restrospect tragic reasons) only read/write fixed block sizes of memory. These 'wrapper' methods then
// allow for an arbitrary # of bytes to be read or written.
//***********************************************************************************************************

int Memory::ReadMemory(State *cpu,Packet *packet,unsigned long long LA,bool is_data,bool privileged,
		       int number_of_bytes,bool is_aligned,unsigned char *buffer,bool init_if_free) {

#ifdef MEM_DEBUG
  printf("[Memory::ReadMemory] LA: 0x%llx, data? %d, privileged? %d, size: %d, aligned? %d,init if free? %d\n",
  	 LA,is_data,privileged,number_of_bytes,is_aligned,init_if_free);
#endif

  // sanity-check: instructions are never mis-aligned...
  
  if ( !is_data && !is_aligned ) {
    std::cout << "[Memory::ReadMemory] Internal Error: Instruction access is mis-aligned?" << std::endl;
    fflush(stdout);
    throw INTERNAL_ERROR;  
  }

  // short circuit as most of the internal simulator memory accesses are less than a memory block size...
  
  if (number_of_bytes <= PM_BLOCK_SIZE)
    return ReadMemoryBlock(cpu,packet,LA,is_data,privileged,number_of_bytes,is_aligned,buffer,init_if_free);

  int rcode = 0;

  int num_blocks  = number_of_bytes / PM_BLOCK_SIZE;
  int extra_bytes = number_of_bytes % PM_BLOCK_SIZE;

  int block_offset = 0;

  // NOTE: will ASSUME if 1st block access is mis-aligned, then ALL blocks accessed are mis-aligned...
  
  for (int i = 1; (i <= num_blocks) && !rcode; i++) {
     rcode = ReadMemoryBlock(cpu,packet,LA + block_offset,is_data,privileged,PM_BLOCK_SIZE,is_aligned,&buffer[block_offset],init_if_free);
     block_offset += PM_BLOCK_SIZE;
  }

  if ( (extra_bytes > 0) && !rcode)
    rcode = ReadMemoryBlock(cpu,packet,LA + block_offset,is_data,privileged,extra_bytes,is_aligned,&buffer[block_offset],init_if_free);

  return rcode;
}

int Memory::WriteMemory(State *cpu,Packet *packet,unsigned long long LA,bool is_data,bool privileged,
			int number_of_bytes,bool is_aligned,unsigned char *buffer) {

#ifdef MEM_DEBUG
  printf("[Memory::WriteMemory] LA: 0x%llx, data? %d, privileged? %d, aligned? %d, size: %d\n",LA,is_data,privileged,is_aligned,number_of_bytes);
#endif
  
  // sanity-check: instructions are never mis-aligned...
  
  if ( !is_data && !is_aligned ) {
    std::cout << "[Memory::ReadMemory] Internal Error: Instruction access is mis-aligned?" << std::endl;
    fflush(stdout);
    throw INTERNAL_ERROR;  
  }

  // short circuit as most of the internal simulator memory accesses are less than a memory block size...
  
  if (number_of_bytes <= PM_BLOCK_SIZE)
    return WriteMemoryBlock(cpu,packet,LA,is_data,privileged,number_of_bytes,is_aligned,buffer);

  int rcode = 0;

  int num_blocks  = number_of_bytes / PM_BLOCK_SIZE;
  int extra_bytes = number_of_bytes % PM_BLOCK_SIZE;

  int block_offset = 0;

  for (int i = 1; (i <= num_blocks) && !rcode; i++) {
    rcode = WriteMemoryBlock(cpu,packet,LA + block_offset,is_data,privileged,PM_BLOCK_SIZE,is_aligned,&buffer[block_offset]);
     block_offset += PM_BLOCK_SIZE;
  }

  if ( (extra_bytes > 0) && !rcode)
    rcode = WriteMemoryBlock(cpu,packet,LA + block_offset,is_data,privileged,extra_bytes,is_aligned,&buffer[block_offset]);

   return rcode;
}

//******************************************************************************************
// ReadMemoryBlock, WriteMemoryBlock - logical accesses to memory...
// data read/written to memory is always byte ordered, ie, independent of endianness...
//
// NOTE: translation(s) retained even if a region access is invalid...
//******************************************************************************************

int Memory::ReadMemoryBlock(State *cpu,Packet *packet,unsigned long long LA,bool is_data,
                       bool privileged,int number_of_bytes,bool is_aligned,unsigned char *buffer,bool init_if_free) {
#ifdef MEM_DEBUG
  printf("[Memory::ReadMemoryBlock] LA: 0x%llx #bytes: %d, init? %d\n",LA,number_of_bytes,init_if_free);
#endif
  
  A64_VMSA mmu(cpu,this,packet,&cpu->itlb,&cpu->dtlb,monitor);

  bool NS = !cpu->IsSecure();

#ifdef MEM_DEBUG
  printf("[Memory::ReadMemoryBlock] translating LA: 0x%llx...\n",LA);
#endif

  Translation *trans = mmu.LA2PA(LA,NS,privileged,is_data,is_aligned,number_of_bytes,false);

#ifdef MEM_DEBUG
  printf("[Memory::ReadMemoryBlock] LA: 0x%llx PA: 0x%llx\n",LA,trans->PA);
#endif

  // use initial translation to check for page crossing...

  int spill_byte_count = trans->PageCrossed(number_of_bytes);  // count for 2nd page access (if any)
  int byte_count       = number_of_bytes - spill_byte_count;   // count for 1st page access

  int rcode = 0;
  SIM_EXCEPTION_CLASS region_access_exc = NO_SIM_EXCEPTION;

  #pragma omp critical
  {
    try {
      rcode = RegionAccess(buffer,cpu->GetID(),trans->LA,trans->PA,is_data,FOR_READ,byte_count,packet->ForTest(),init_if_free);
#ifdef MEM_DEBUG
      printf("[ReadMemoryBlock] rcode = %d, spill count = %d\n",rcode,spill_byte_count);
#endif
    } catch(SIM_EXCEPTION_CLASS eclass) {
      region_access_exc = eclass;
    }

    if (spill_byte_count > 0) {
#ifdef MEM_DEBUG
      printf("[ReadMemoryBlock] page crossing...\n");
#endif
      int rcode2 = 0;
      // NOTE: access to 2nd page will be aligned
      Translation *trans2 = mmu.LA2PA(LA + byte_count,NS,privileged,is_data,false,spill_byte_count,false);
      try {
        rcode2 = RegionAccess(&buffer[byte_count],cpu->GetID(),trans2->LA,trans2->PA,is_data,FOR_READ,spill_byte_count,packet->ForTest(),init_if_free);
      } catch(SIM_EXCEPTION_CLASS eclass) {
        region_access_exc = eclass;
      }
      if (rcode2 == rcode) {
	// region access return code for both regions matches...
      } else {
        rcode = SOME_BYTES_UNDEFINED;  // mismatch on region accesses means one or more bytes may be undefined...
      }
    }
  }

  // throw any exception caught in critical block...

  if (region_access_exc != NO_SIM_EXCEPTION) {
#ifdef MEM_DEBUG
    printf("[Memory::ReadMemoryBlock WARNING: possible region violation: LA: 0x%llx PA: 0x%llx rcode: %d\n",LA,trans->PA,rcode);
#endif
    throw region_access_exc;
  }
  
#ifdef MEM_DEBUG
  printf("[Memory::ReadMemoryBlock] exited, LA: 0x%llx PA: 0x%llx rcode: %d\n",LA,trans->PA,rcode);
#endif
  
  return rcode;
}

int Memory::WriteMemoryBlock(State *cpu,Packet *packet,unsigned long long LA,bool is_data,bool privileged,int number_of_bytes,bool is_aligned,unsigned char *buffer) {
#ifdef MEM_DEBUG
  printf("[Memory::WriteMemory] LA: 0x%llx #bytes: %d\n",LA,number_of_bytes);
#endif
  
  A64_VMSA mmu(cpu,this,packet,&cpu->itlb,&cpu->dtlb,monitor);

  bool NS = !cpu->IsSecure();

  Translation *trans = mmu.LA2PA(LA,NS,privileged,is_data,is_aligned,number_of_bytes,true);

  // use initial translation to check for page crossing...

  int spill_byte_count = trans->PageCrossed(number_of_bytes);  // count for 2nd page access (if any)
  int byte_count       = number_of_bytes - spill_byte_count;   // count for 1st page access
 
#ifdef MEM_DEBUG
  printf("[Memory::WriteMemory] la: 0x%llx data? %d privileged? %d #bytes: %d aligned? %d byte-counts: %d/%d bytes:\n",
         LA,is_data,privileged,number_of_bytes,is_aligned,spill_byte_count,byte_count);
  for (int i = 0; i < number_of_bytes; i++) {
    printf(" 0x%x",buffer[i]);
  }
  printf("\n");
#endif
  
  int rcode = 0;
  SIM_EXCEPTION_CLASS region_access_exc = NO_SIM_EXCEPTION;

  #pragma omp critical
  {
    try {
      rcode = RegionAccess(buffer,cpu->GetID(),trans->LA,trans->PA,is_data,FOR_WRITE,byte_count,packet->ForTest());
#ifdef MEM_DEBUG
      printf("[WriteMemoryBlock] rcode = %d, spill count: %d\n",rcode,spill_byte_count);
#endif
    } catch(SIM_EXCEPTION_CLASS eclass) {
      region_access_exc = eclass;
    }

    if (spill_byte_count > 0) {
      // handle page crossing...
      // NOTE: access to 2nd page will be aligned
      Translation *trans2 = mmu.LA2PA(LA + byte_count,NS,privileged,is_data,false,spill_byte_count,true);
      int rcode2 = 0;
      try {
	rcode2 = RegionAccess(&buffer[byte_count],cpu->GetID(),trans2->LA,trans2->PA,is_data,FOR_WRITE,spill_byte_count,packet->ForTest());
      } catch(SIM_EXCEPTION_CLASS eclass) {
        region_access_exc = eclass;
      }
      if (rcode2 == rcode) {
	// region access return code for both regions matches...
      } else {
        rcode = SOME_BYTES_UNDEFINED;  // mismatch on region accesses means one or more bytes may be undefined...
      }
    }
  }

  // throw any exception caught in critical block...

  if (region_access_exc != NO_SIM_EXCEPTION) {
#ifdef MEM_DEBUG
    printf("[Memory::WriteMemoryBlock] region access???\n");
#endif
    throw region_access_exc;
  }

#ifdef MEM_DEBUG
  printf("[Memory::WriteMemory] LA: 0x%llx PA: 0x%llx rcode: %d\n",LA,trans->PA,rcode);
#endif
  return rcode;
}


//******************************************************************************************
// memory is just bytes, but instructions and data can be segregrated to separate memory 
//   regions...
//******************************************************************************************

int Memory::RegionAccess(unsigned char *buffer,unsigned int cpu_id,unsigned long long LA,unsigned long long PA,
                         bool instr_vs_data,int read_vs_write,int byte_count,bool for_test,bool init_if_free) {

  unsigned long long startPA = PA;
  unsigned long long endPA   = PA + byte_count - 1;  // in case access spans regions

  if (for_test && InvalidRegionAccess(startPA,instr_vs_data,read_vs_write,byte_count,init_if_free)) {
#ifdef MEM_DEBUG
    printf("[RegionAccess] startPA invalid?\n");
#endif
    throw GENERATION_ERROR; //<---we'll just ASSUME this has occurred during test creation(?)
  }
  
  if (for_test && InvalidRegionAccess(endPA,instr_vs_data,read_vs_write,1,init_if_free)) {
#ifdef MEM_DEBUG
    printf("[RegionAccess] endPA invalid?\n");
#endif
    throw GENERATION_ERROR; //<---check both ends of the access (access crosses cache line?)
  }
  
  LogRegionAccess(startPA,instr_vs_data,byte_count);
  LogRegionAccess(endPA,instr_vs_data,byte_count);

  if (monitor)
    monitor->RegionAccess(buffer,cpu_id,LA,PA,instr_vs_data,read_vs_write,byte_count,init_if_free);

#ifdef MEM_DEBUG
  printf("[Memory::RegionAccess] PA: 0x%llx, byte-count: %d, for-test? %d, init-if-free? %d\n",PA,byte_count,for_test,init_if_free);
#endif
  
  int rcode = (read_vs_write==FOR_READ) ? ReadPhysicalMemory(PA,byte_count,buffer,for_test,init_if_free) : WritePhysicalMemory(PA,byte_count,buffer,for_test);

  return rcode;
}


//******************************************************************************************
// methods for accessing physical memory...
//******************************************************************************************

void Memory::SetPhysicalAddressRange(unsigned long long address_lo, unsigned long long address_hi) {
  physical_address_lo = address_lo; physical_address_hi = address_hi;
}

bool Memory::PhysicalAddressRange(unsigned long long &address_lo, unsigned long long &address_hi) {
  bool pa_range_set = (physical_address_hi != physical_address_lo);

  if (pa_range_set) {
    address_lo = physical_address_lo;
    address_hi = physical_address_hi;
  }

  return pa_range_set;
}

#ifdef ARMV8_FOUNDATION_MODEL
static bool in_dram = false; // ugly...
#endif

unsigned long long Memory::ValidatePhysicalMemoryAddress(unsigned long long address, bool for_test) {
  
  // exceeded range of physical memory?

  if ((address & pa_mask()) != address) {
    if (for_test) {
      // its just easier to build tests that run on other simulators (such as QEMU) if we just limit
      // physical memory...
#ifdef MEM_DEBUG
      printf("[ValidatePhysicalMemoryAddress] address 0x%llx exceeds physical memory range (pa mask: 0x%llx)\n",address,pa_mask());
#endif
      throw GENERATION_ERROR;
    } else {
#ifdef IGNORE_UPPER_PA_BITS
      address = address & pa_mask();  // strip upper physical address bits - does TCR control this???
#endif
    }
  }

#ifdef ARMV8_FOUNDATION_MODEL
  // constrain physical addresses to armv8 foundation model DRAM...

  if ( (address >= 0x80000000) && for_test)
    in_dram = true;

  if (in_dram) {
    if ( (address < 0x80000000) || (address > 0xffffffff) ) {
      printf("[ValidatePhysicalMemoryAddress] address 0x%llx NOT in armv8 foundation model DRAM bank 1 range (0x80000000...0xffffffff)\n",address);
      throw GENERATION_ERROR;
    }      
  }
#endif

  unsigned long long pa_lo = 0,pa_hi = 0;
  
  if (PhysicalAddressRange(pa_lo, pa_hi)) {
    if ( (address >= pa_lo) && (address <= pa_hi) ) {
      // address is okay...
#ifdef MEM_DEBUG
      printf("[ValidatePhysicalMemoryAddress] physical address 0x%llx IS OKAY, ie, in (user-specified) physical address range (0x%llx...0x%llx)\n",address,pa_lo,pa_hi);
#endif
    } else {
#ifdef MEM_DEBUG
      printf("[ValidatePhysicalMemoryAddress] physical address 0x%llx NOT in (user-specified) physical address range (0x%llx...0x%llx)\n",address,pa_lo,pa_hi);
#endif
      throw GENERATION_ERROR;
    }      
  }
  
  return address;
}

int Memory::WritePhysicalMemory(unsigned long long address_in,int number_of_bytes,unsigned char *buffer, bool for_test, bool initial_values) {
#ifdef MEM_DEBUG
  printf("[WritePhysicalMemory] address: 0x%llx #bytes: %d\n",address_in,number_of_bytes);
#endif

  // check (and possibly 'adjust' starting address...
  
  unsigned long long address = ValidatePhysicalMemoryAddress(address_in, for_test);

#ifdef MEM_DEBUG
  printf("[WritePhysicalMemory] 'adjusted' address: 0x%llx\n",address);
#endif
  // check end-address too...
  
  ValidatePhysicalMemoryAddress(address + number_of_bytes - 1, for_test);

  
  // pick off write to device memory...

  int rcode = 0;

  if (WriteDeviceMemory(rcode,address,number_of_bytes,buffer,for_test)) {
#ifdef DEVICE_MEM_DEBUG
    printf("[Memory::WritePhysicalMemory] write to device memory, rcode: %d\n",rcode);
#endif
  } else {
    rcode = phys_mem.Write(address,buffer,number_of_bytes,initial_values);
  }
  
  if (monitor)
    monitor->WritePhysicalMemory(address,number_of_bytes,buffer);

  return rcode;
}

int Memory::ReadPhysicalMemory(unsigned long long address_in,int number_of_bytes,unsigned char *buffer,bool for_test, bool init_if_free) {
#ifdef MEM_DEBUG
    printf("[Memory::ReadPhysicalMemory] address: 0x%llx #bytes: %d, for-test? %d, init-if-free? %d\n",address_in,number_of_bytes,for_test,init_if_free);
#endif
  
  // check (and possibly 'adjust') starting address...
  
  unsigned long long address = ValidatePhysicalMemoryAddress(address_in, for_test);
  
#ifdef MEM_DEBUG
  printf("[Memory::ReadPhysicalMemory] 'adjusted' address: 0x%llx\n",address);
#endif
  
  // check end-address too...
  
  ValidatePhysicalMemoryAddress(address + number_of_bytes - 1, for_test);

  
  // pick off read from device memory...

  int rcode = 0;

  if (ReadDeviceMemory(rcode,address,number_of_bytes,buffer,for_test)) {
#ifdef DEVICE_MEM_DEBUG
    printf("[Memory::ReadPhysicalMemory] read from device memory, rcode: %d\n",rcode);
#endif
  } else {  
    rcode = phys_mem.Read(address,buffer,init_if_free,number_of_bytes);
  }
  
  if (monitor)
    monitor->ReadPhysicalMemory(address,number_of_bytes,buffer,init_if_free);

#ifdef MEM_DEBUG
  printf("[Memory::ReadPhysicalMemory] exited, rcode: %d\n",rcode);
#endif

  return rcode;
}


// apply endianness when copying memory...

void Memory::ApplyEndianness(unsigned char *dest,unsigned char *src,bool src_dest_endianness,int access_size_in_bytes,int total_number_of_bytes) {
#ifdef MEM_DEBUG
  printf("[Memory::ApplyEndianness] requested endianness: %s access size: %d total # of bytes: %d host-endianness: %s\n",
         (src_dest_endianness ? "Big" : "Little"),access_size_in_bytes,total_number_of_bytes,(HostEndianness() ? "Big" : "Little"));
#endif
  
  int num_words = total_number_of_bytes / access_size_in_bytes;

  for (int i = 0; i < num_words; i++) {
     int word_index = i * access_size_in_bytes; //<---index into dest char buffer  

     if (HostEndianness() == src_dest_endianness) {
       // host endianness matches either desired or expected endianness, thus straight copy of bytes...
       for (int j = 0; j < access_size_in_bytes; j++) {
	  dest[word_index + j] = src[word_index + j];  // copy bytes in order...
       }
     } else {
       // endianness mismatch, swap/copy bytes... 
       for (int j = 0; j < access_size_in_bytes; j++) {
	 dest[word_index + j] = src[word_index + (access_size_in_bytes - 1) - j]; // copy/swap bytes...
       }
     }
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------
// device-memory methods return true if access was indeed to device memory, return code (rcode) indicates outcome of the device-memory access...
//
// NOTE: if for_test==true (random test generation), access fails, ie, we assume its an error to access devices during random test
//
// NOTE2: device memory is ASSUMED to have same endianness as normal memory. Thus devices must encode/decode memory values in same manner as
//        system.
//
// HOW TO ACCESS CONTROL ENDIANNESS METHODS???
//-----------------------------------------------------------------------------------------------------------------------------------------------

bool Memory::WriteDeviceMemory(int &rcode,unsigned long long address_in,int number_of_bytes,unsigned char *buffer, bool for_test) {
//#ifdef DEVICE_MEM_DEBUG
//  printf("[Memory::WriteDeviceMemory] entered, address: 0x%llx\n",address_in);
//#endif
  
  bool maps_to_device = false;
  
  for (vector<memmap_device *>::iterator i = devices.begin(); i != devices.end() && !maps_to_device; i++) {
    if ( (*i)->IsImplemented() && (*i)->InRange(address_in) ) {
#ifdef DEVICE_MEM_DEBUG
      printf("[Memory::WriteDeviceMemory] address maps to device '%s'...\n",(*i)->Name().c_str());
#endif
      maps_to_device = true;
      if (for_test) {
	rcode = -1; // disallow access to device during random test generation...
      } else if ((*i)->IsMapped(address_in)) {
#ifdef DEVICE_MEM_DEBUG
        printf("[Memory::WriteDeviceMemory] address maps to device register '%s'...\n",(*i)->RegisterName(address_in).c_str());
#endif
	if (HostEndianness() != (*i)->Endianness()) {
	  // host-memory/device-memory endianness mismatch...
	  unsigned char tbuf[number_of_bytes];
          ApplyEndianness(tbuf,buffer,(*i)->Endianness(),number_of_bytes,(*i)->RegisterSize());
	  rcode = (*i)->Write(address_in,tbuf,number_of_bytes);	  
	} else {
	  // device endianness matches host...
	  rcode = (*i)->Write(address_in,buffer,number_of_bytes);
	}
      } else {
	rcode = -1; // address falls in device memory range, but does not map to any implemented device register...
      }
    }
  }

//#ifdef DEVICE_MEM_DEBUG
//  printf("[Memory::WriteDeviceMemory] exited. maps-to-device? %d\n",maps_to_device);
//#endif
  
  return maps_to_device;
}

bool Memory::ReadDeviceMemory(int &rcode,unsigned long long address_in,int number_of_bytes,unsigned char *buffer, bool for_test) {
//#ifdef DEVICE_MEM_DEBUG
//  printf("[Memory::ReadDeviceMemory] entered, address: 0x%llx\n",address_in);
//#endif
  
  bool maps_to_device = false;
  
  for (vector<memmap_device *>::iterator i = devices.begin(); i != devices.end() && !maps_to_device; i++) {
    if ( (*i)->IsImplemented() && (*i)->InRange(address_in) ) {
#ifdef DEVICE_MEM_DEBUG
      printf("[Memory::ReadDeviceMemory] address maps to device '%s'...\n",(*i)->Name().c_str());
#endif
      maps_to_device = true;
      if (for_test) {
	rcode = -1; // disallow access to device during random test generation...
      } else if ((*i)->IsMapped(address_in)) {
#ifdef DEVICE_MEM_DEBUG
        printf("[Memory::ReadDeviceMemory] address maps to device register '%s'...\n",(*i)->RegisterName(address_in).c_str());
#endif
	if (HostEndianness() != (*i)->Endianness()) {
	  // host-memory/device-memory endianness mismatch...
	  unsigned char tbuf[number_of_bytes];
          rcode = (*i)->Read(address_in,tbuf,number_of_bytes);
          ApplyEndianness(buffer,tbuf,(*i)->Endianness(),number_of_bytes,(*i)->RegisterSize());
	} else {
	  // device endianness matches host...
          rcode = (*i)->Read(address_in,buffer,number_of_bytes);
	}
      } else {
	rcode = -1; // address falls in device memory range, but does not map to any implemented device register...
      }
    }
  }

//#ifdef DEVICE_MEM_DEBUG
//  printf("[Memory::WriteDeviceMemory] exited. maps-to-device? %d\n",maps_to_device);
//#endif
  
  return maps_to_device;
}



void Memory::LogRegionAccess(unsigned long long address,int instr_vs_data,int /*number_of_bytes*/) {
  unsigned long long block_mask = ~( (unsigned long long)(block_size-1) );
  unsigned long long block_address = address & block_mask;

   if (instr_vs_data == DATA) {
     if ( data_blocks.find(block_address) == data_blocks.end() ) 
       data_blocks.insert(block_address);
   } else {
     if ( instr_blocks.find(block_address) == instr_blocks.end() ) 
       instr_blocks.insert(block_address);
   }
}

int Memory::AccessType(unsigned long long address) {
#ifdef NO_MIXED_ACCESSES
  unsigned long long block_mask = ~( (unsigned long long)(block_size-1) );
  unsigned long long block_address = address & block_mask;
  
  if (data_blocks.find(block_address) != data_blocks.end())
    return DATA;
  else
    return INSTRUCTION;
#else
  // ASSUME all accesses to be data since not tracking data vs instr...
  return DATA;
#endif  
}

int Memory::InvalidRegionAccess(unsigned long long address,int instr_vs_data,int /*read_vs_write*/,int number_of_bytes,bool /*init_if_free*/) {
  int rcode = 0;

#ifdef NO_MIXED_ACCESSES
  unsigned long long block_mask = ~( (unsigned long long)(block_size-1) );

  unsigned long long block_address = address & block_mask;

#ifdef MEM_DEBUG
  printf("[Memory::InvalidRegionAccess] block-address: 0x%llx ivsd: %d instr_blocks.size: %d data_blocks.size: %d\n",
         block_address,instr_vs_data,(int) instr_blocks.size(),(int) data_blocks.size());
#endif
  
  // right now we are just not going to mix instructions and data in the same memory block...

   if (instr_vs_data == DATA) {
     if ( (instr_blocks.size() > 0) && (instr_blocks.find(block_address) != instr_blocks.end()) )
       rcode = -1;
   }

   if (instr_vs_data == INSTRUCTION) {
     if ( (data_blocks.size() > 0) && (data_blocks.find(block_address) != data_blocks.end()) )
       rcode = -1;
   }
#endif
   
  return rcode;
}


//=================================================================================================================================
// exclusive monitor methods...
//=================================================================================================================================

/*
  // local monitor - always in use.
  // global monitor - used when:
  //                    1. MMU enabled
  //                    2. mapped page is sharable and cacheable 

  exclMonitor global_monitor;          // in this implementation there is only one global monitor 
                                       //   (we assume a single cpu cluster with a single corresponding global monitor)
*/

// clear local monitor, but NOT global...

void Memory::ClearExclusiveMonitor(State *cpu) {
  cpu->local_monitor.Clear();
}

// access the glopal monitor if:
//   mmu enabled, cache(s) on, transaction itself is shareable and cacheable...
// or:
//   transaction is shareable (will ASSUME that (global) monitor state can be maintained even
//   when vmsa is disabled(?)

bool Memory::AccessGlobalMonitor(A64_VMSA *mmu,Translation *trans) {
  bool use_global_monitor = trans->Shareable(); // assume global monitor if transaction is shareable...

  // if the mmu is on however, then check shareability and cacheability...

  if (mmu->Enabled()) {
    use_global_monitor = mmu->Enabled() && mmu->Cacheable(true) && trans->Shareable() && trans->Cacheable();
  }

#ifdef MEM_DEBUG
  printf("[Memory::SetExclusive] access-global? %d (mmu on? %d mmu-cacheable? %d trans-shareable? %d trans-cacheable? %d)\n",
         use_global_monitor, mmu->Enabled(),mmu->Cacheable(true),trans->Shareable(),trans->Cacheable());
#endif
  
  return use_global_monitor;
}

// set local/global monitor...

void Memory::SetExclusiveMonitor(State *cpu,Packet *packet,unsigned long long logical_address,int num_bytes,bool privileged) {
  A64_VMSA mmu(cpu,this,packet,&cpu->itlb,&cpu->dtlb,monitor);
  Translation *trans = mmu.LA2PA(logical_address,!cpu->IsSecure(),privileged,true,true /*wasaligned*/,num_bytes,false);

  bool set_global_monitor = AccessGlobalMonitor(&mmu,trans);

  if (set_global_monitor) {
    global_monitor.Set(logical_address,trans->PA,num_bytes,cpu->GetID());
#ifdef MEM_DEBUG
    printf("[Memory::SetExclusive] core %d owns the monitor!\n",global_monitor.CPUID());
#endif
  }
  
  cpu->local_monitor.Set(logical_address,trans->PA,num_bytes,cpu->GetID());
}
  
// IsExclusive - use to see if an access is exclusive. does NOT change state...
bool Memory::IsExclusive(State *cpu,Packet *packet,unsigned long long logical_address,int num_bytes,bool privileged) {
  A64_VMSA mmu(cpu,this,packet,&cpu->itlb,&cpu->dtlb,monitor);
  Translation *trans = mmu.LA2PA(logical_address,!cpu->IsSecure(),privileged,true,true /*wasaligned*/,num_bytes,false);

  bool check_global_monitor = AccessGlobalMonitor(&mmu,trans);
  
  bool is_exclusive = false;

  if (check_global_monitor) {
    // check global monitor...
#ifdef MEM_DEBUG
    printf("[Memory::SetExclusive] core %d owns the monitor!\n",global_monitor.CPUID());
#endif
    is_exclusive = global_monitor.IsExclusive(logical_address,trans->PA,num_bytes,cpu->GetID());
  } else {
    // check local monitor...
    is_exclusive = cpu->local_monitor.IsExclusive(logical_address,trans->PA,num_bytes,cpu->GetID());
  }

  return is_exclusive;
}

// ExclusiveMonitorsPass - use to see if an access is exclusive. If global exclusive op, then local exclusive op is cleared...
bool Memory::ExclusiveMonitorsPass(State *cpu,Packet *packet,unsigned long long logical_address,int num_bytes,bool is_aligned, bool privileged, bool for_test) {
#ifdef MEM_DEBUG
  printf("[Memory::ExclusiveMonitorsPass] entered...\n");
#endif
  
  A64_VMSA mmu(cpu,this,packet,&cpu->itlb,&cpu->dtlb,monitor);
  Translation *trans = mmu.LA2PA(logical_address,!cpu->IsSecure(),privileged,true,is_aligned,num_bytes,false);

  ValidatePhysicalMemoryAddress(trans->PA, for_test); // will use as 'quick' check on exclusive monitor address...

  bool check_global_monitor = AccessGlobalMonitor(&mmu,trans);

  bool is_exclusive = false;

  if (check_global_monitor) {
#ifdef MEM_DEBUG
    printf("   check global monitor. if exclusive clear local monitor...\n");
#endif
    is_exclusive = global_monitor.IsExclusive(logical_address,trans->PA,num_bytes,cpu->GetID());
    if (is_exclusive)
      cpu->local_monitor.Clear();
  } else {
#ifdef MEM_DEBUG
    printf("  check local monitor...\n");
#endif
    is_exclusive = cpu->local_monitor.IsExclusive(logical_address,trans->PA,num_bytes,cpu->GetID());
  }

#ifdef MEM_DEBUG
  printf("[Memory::ExclusiveMonitorsPass] exited, is-exclusive? %d.\n",is_exclusive);
#endif
  
  return is_exclusive;
}

//=================================================================================================================================
// TestBlockAddresses - make sorted list of all physical memory blocks used by test...
//
//  NOTE: Currently NOT tracking initial memory (other than treating instruction memory as read-only). Thus could see errors
//        during resimulation due to some initial data memory value being overwritten during simulation. 
//=================================================================================================================================

void Memory::TestBlockAddresses(vector<unsigned long long> &test_block_addresses,bool verbose) {
  if (verbose) printf("  making up sorted list of all physical memory block addresses...");

  phys_mem.AddressList(test_block_addresses,true);
  std::sort(test_block_addresses.begin(),test_block_addresses.end());

  if (verbose) printf("done.\n");
}

//=================================================================================================================================
//=================================================================================================================================

void Memory::SetFileBlockAddresses(vector<unsigned long long> &file_block_addresses,vector<unsigned long long> &test_block_addresses,
                                   unsigned long long address_mask,bool verbose) {

  if (verbose) printf("ADDR MASK: 0x%llx\n",address_mask);

  unordered_set<unsigned long long> all_block_addresses;

  for (unsigned int i = 0; i < test_block_addresses.size(); i++) {
    unsigned long long block_address = test_block_addresses[i] & address_mask;
    if (all_block_addresses.find(block_address) == all_block_addresses.end()) {
      all_block_addresses.insert(block_address);
      file_block_addresses.push_back(block_address);
      //if (verbose) printf(">>>0x%llx<<<\n",block_address);
    }
  }

  if (verbose) printf("FINAL BLOCK COUNT: %lu\n",file_block_addresses.size());
}

void Memory::ClearBlockStorage() {}
void Memory::BlockSort(int /* block_size*/) {}

//=================================================================================================================================
//=================================================================================================================================

void Memory::ReadInitialState(unsigned long long section_address,unsigned char *buffer, bool is_data) {
  phys_mem.ReadInitialState(section_address,buffer,is_data);
}

