#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <unordered_map>
#include <memory>

using namespace std;

#include "a64sim.h"
#include "a64_exceptions.h"

#include "ELFIO.h"

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

int ELFIO::Save(Memory &mem, string &elf_file, unsigned long long entry_point, bool compress, bool verbose) {
  //verbose = true;
  
  if (verbose)
    printf("\n[ELFIO::Save] entered. file: '%s', entry-point: 0x%llx, compress? %d...\n",
	   elf_file.c_str(),entry_point,compress);

  vector<unsigned long long> test_block_addresses;  // list of memory blocks used, each of size PM_BLOCK_SIZE   
  mem.TestBlockAddresses(test_block_addresses,verbose);

  if (compress) {
    /* Produce smallest ELF file image possible. If necessary, use ELF extended section numbering. */
    /* Some elf readers (in particular, if they use BSF libelf or C++ elfio) may not support       */
    /* extended section numbering...                                                               */
    if (verbose)
      printf("  Produce smallest ELF file image, block size: %d...\n",PM_BLOCK_SIZE);
    int rcode = SaveToELF(mem,elf_file,test_block_addresses,PM_BLOCK_SIZE,entry_point,verbose);
    if (verbose) printf("  done.\n");
    return rcode;    
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

  if (verbose)
      printf("  Produce smallest number of ELF sections, file block size: %d...\n",file_block_size);
    

  vector<unsigned long long> file_block_addresses;
  unsigned long long addr_mask = ~((1ull<<file_block_size_in_bits) - 1ull);

  mem.SetFileBlockAddresses(file_block_addresses,test_block_addresses,addr_mask,verbose);

  if (verbose) printf("  writing elf file...\n");

  int rcode = SaveToELF(mem,elf_file,file_block_addresses,file_block_size,entry_point,verbose);
  
  if (verbose) printf("  done.\n");

  return rcode;
}


//=================================================================================================================================
// SaveToELF - write out list of simulator memory blocks (of fixed size) to ELF file...
//=================================================================================================================================

int ELFIO::SaveToELF(Memory &mem, string &elf_file, vector<unsigned long long> &file_block_addresses, int file_block_size,
		     unsigned long long entry_point, bool verbose) {
  //verbose = true;

  if (verbose) printf("\n[SaveToELF] entered...\n");

  void *edata = NULL;
  char err_msg[1024];

  int rcode = 0;

  if ((rcode = elfio_init(&edata,(char *) elf_file.c_str(),1,entry_point,err_msg))) {
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

int ELFIO::Load(Memory &mem, string &elf_file, bool verbose) {
  return Load(mem,elf_file,-1,verbose);
}

int ELFIO::Load(Memory &mem, string &elf_file, unsigned long long load_address, bool verbose) {
  bool use_load_address = (load_address != (unsigned long long) -1);

  int section_load_count = 0;

  printf("Loading test from ELF file '%s'...\n",elf_file.c_str());

  //verbose = true;
  
  void *edata = NULL;
  char err_msg[1024];

  int rcode = 0;

  if ((rcode = elfio_init(&edata,(char *) elf_file.c_str(),0,0,err_msg))) {
    fprintf(stderr,"Load (from ELF) failed: %s\n",err_msg);
    return rcode;
  }

  if (verbose) printf("reader initialized...\n");

  int section_count = elf_io_section_count(&edata);

  int section_index = 0;

  for (section_index = 0; (section_index < section_count) && !rcode; section_index++) {
    
    if (verbose) printf("reading section %d...\n",section_index);

    unsigned long long address;
    char section_name[1024];
    unsigned char *section_data;
    int is_data = 0;   // set to 1 for valid section data
    section_name[0] = '\0';
    int size_in_bytes = 0;
    int done = 0;
    
    if ((rcode = elfio_read_next_section(&edata,section_name,&address,&is_data,&section_data,&size_in_bytes,err_msg,&done))) {
      fprintf(stderr,"%s\n",err_msg);
      break;
    }

    if (rcode) {
      if (verbose) printf("Non-zero return code from elf 'section read'...\n:");
      break;
    }
    
    if (verbose) printf("section[%d]: '%s'\n",section_index,section_name);

    // ignore symbol table or string table...

    if (!strncmp(section_name,".symtab",7) || !strncmp(section_name,".strtab",7) || !strncmp(section_name,".shstrtab",9) || !strncmp(section_name,".stab",5) ) {
      if (verbose) printf("Skipping '%s' section...\n",section_name);
      continue;
    }

    // ignore debug stuff (sigh)...

    if (!strncmp(section_name,".debug_",7) ) {
      if (verbose) printf("Skipping '%s' section...\n",section_name);
      continue;
    }
    
    // skip 'comment' section...

    if (!strncmp(section_name,".comment",9) ) {
      if (verbose) printf("skipping 'comments' section...\n:");
      continue;
    }

    if ( !is_data ) { // skip "non-data" section....
      if (verbose) printf("section does not appear to contain instructions or data...\n");
      continue;
    }

    if ( size_in_bytes <= 0 ) { // skip empty section....
      if (verbose) printf("empty section...\n");
      continue;
    }

    if (done) {
      if (verbose) printf("ELF section read indicates we are done...\n:");
      break;
    }

    // If a load address has been specified, then:
    //   * elf file itself must NOT specify a load address.
    //   * elf file must contain only a single 'data' section (which we assume contains one or more assembled instructions)
    //
    //   * The INTENT is to allow some assembly language 'macro' to be inserted, most likely at the current PC.
    
    if (use_load_address) {
      if (address == 0) {
	address = load_address;
      } else {
        printf("[ELFIO::Load] Error: attempt to load code from ELF file at a specified load address (0x%llx), but the ELF file itself has a specified entry point (0x%llx)\n", load_address, address);
	rcode = -1;
	break;
      }
    }

    section_load_count += 1;
    
    if (use_load_address && (section_load_count > 1)) {
        printf("[ELFIO::Load] ERROR (FOR NOW ANYWAY): When loading from ELF file to specific load address, the ELF file to be loaded can contain only a single section\n");
	rcode = -1;
	break;
    }
  

    // make sure this block does not load above the top of physical memory...

    unsigned long long pegged_address = mem.ValidatePhysicalMemoryAddress(address,false);

    if (address != pegged_address) {
      //if (verbose) {
        printf("WARNING: ELF section load address (0x%llx) exceeds physical memory. New load address will be 0x%llx\n",address,pegged_address);
      //}
      address = pegged_address; // for now just ASSSUME all data addresses within this section will be okay if the start address is adjusted (gasp!)
    }
      
    int num_blocks = size_in_bytes / PM_BLOCK_SIZE;
    int extra_bytes = size_in_bytes % PM_BLOCK_SIZE;

    if (verbose) 
      printf("section %s, total size in bytes: %d, # blocks: %d, remainder: %d\n",section_name,size_in_bytes,num_blocks,extra_bytes);

    int block_offset = 0;

    for (int i = 1; i <= num_blocks; i++) {
       try {
	 mem.WritePhysicalMemory(address + block_offset,PM_BLOCK_SIZE,&section_data[block_offset],false,true);
       } catch(SIM_EXCEPTION_CLASS eclass) {
	 fprintf(stderr,"Load failed (on memory block write): section: '%s', address: 0x%llx size: %d\n",
                 section_name,address + block_offset,PM_BLOCK_SIZE);
         rcode = -1;
	 break;
       }

       if (verbose) {
         unsigned char mbuf[PM_BLOCK_SIZE];
         for(int k = 0; k < PM_BLOCK_SIZE; k++) mbuf[k] = 0;
         int rcode = mem.ReadPhysicalMemory(address + block_offset,PM_BLOCK_SIZE,mbuf,false);
         if (rcode) { 
           printf("PROBLEMS READING BACK ELF-INITIALIZED MEMORY???\n");
	   break;
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
	mem.WritePhysicalMemory(address + block_offset,extra_bytes,&section_data[block_offset],false);
       } catch(SIM_EXCEPTION_CLASS eclass) {
	 fprintf(stderr,"Load failed (on memory block write): section: '%s', address: 0x%llx size: %d\n",
                 section_name,address + block_offset,PM_BLOCK_SIZE);
         rcode = -1;
	 break;
       }
       if (verbose) {
         unsigned char mbuf[extra_bytes];
         int rcode = mem.ReadPhysicalMemory(address + block_offset,extra_bytes,mbuf,false);
         if (rcode) { 
           printf("PROBLEMS READING BACK ELF-INITIALIZED MEMORY???\n");
	   break;
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

  if (section_index == section_count) {
    if (verbose) printf("Processed %d sections...\n",section_count);
  } else {
    if (use_load_address) {
      // section count WILL mismatch...
    } else
      printf("WARNING: # of sections read (%d) does not match # of sections in file (%d)\n", section_index, section_count);
  }

  return rcode;
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

unsigned long long ELFIO::estimateELFFileSize(unsigned int &resulting_block_count,vector<unsigned long long> &program_block_addresses, 
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

bool ELFIO::ChooseFileBlockSize(int &block_size_in_bits, unsigned int &resulting_block_count, 
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

