#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

#define VFP_TEST_HARNESS "/home/gene/Desktop/windvane/unit_test/obj/vfp_test_harness.elf"

#include "a64_instr_enums.h"

#include "X64Simulator.h"

bool is_vfp_instr(int instr_index) {
  switch(instr_index) {
    #include "VFP_CASES.C"
    return true;
    break;
  default: return false; break;
  }
  return false;
}

void get_vfp_instr_indices(std::vector<int> &vfp_instr_indices) {
  for (int i = 0; i < A64_UNALLOCATED; i++) {
     if (is_vfp_instr(i))
       vfp_instr_indices.push_back(i);
  }

  printf("Out of %d instruction indexes, %d represent implemented VFP instructions...\n",
         (int) A64_UNALLOCATED, (int) vfp_instr_indices.size());
}

namespace X64SIM_UTILS {
  #include "test_a64sim_all_instr_encodings.C"
}

int run_test(int instr_index, int retries_count);
int gen_instr(X64Simulator &my_simulator, Packet &my_packet, int instr_index);
int setup_unit_test(X64Simulator &my_simulator,Packet &my_packet);

#define RETRIES_COUNT 5

//------------------------------------------------------------------------------------
// create unit-test for each implemented A64 VFP instruction...
//------------------------------------------------------------------------------------

int main(int argc,char **argv) {
  printf("dude!\n");

  vector<int> vfp_instr_indices;

  get_vfp_instr_indices(vfp_instr_indices);

  int rcode = 0;

  for (vector<int>::iterator i = vfp_instr_indices.begin(); i != vfp_instr_indices.end(); i++) { 
     rcode = run_test(*i,RETRIES_COUNT);  
/*
     if (rcode) {
       printf("VFP UNIT-TESTS BUILD ABORTED!\n");
       break;
     }
*/
  }

  return rcode;
}


// -------------------------------------------------------------------------------------------------------
// create simulator instance, load unit-test preamble...
//   --test preamble should initialize all vector and GP registers 
// create packet...
// for N times or until instruction successfully stepped:
//    generate opcode for this instruction, write to memory...
//    simulate, update sim-trace.
// write out sim-trace to unit-test/test/instr directory
// if successful step:
//    write out assembly source to unit-test src dir
// discard simulator instance
// -------------------------------------------------------------------------------------------------------

enum { NO_FAIL, DECODE_FAIL, DISASM_FAIL, FETCHOPS_FAIL, EXECUTE_FAIL, MEMACCESS_FAIL, WRITEBACK_FAIL };

#define STARTING_PC 4096

int gen_instr(X64Simulator &my_simulator, Packet &my_packet, int instr_index) {
   //printf("[gen_instr] entered...\n");
  
   unsigned int set_mask = (unsigned int) rand();
   string       group    = "";
   unsigned int encoding = 0;
   unsigned int mask     = 0;

   X64SIM_UTILS::get_next_instr_encoding(instr_index,set_mask,group,encoding,mask);

   my_packet.recordInstrEncoding(encoding);
   my_packet.setOpcode(encoding);
   my_packet.Pstate.Value(my_simulator.cpus[0].Pstate.Value());

   my_simulator.cpus[0].PC = STARTING_PC;

   my_simulator.cpus[0].CPACR_EL1.FPEN(3);

   my_packet.PC = STARTING_PC;

   // write instruction bytes to memory in order by physical address

   union {
     unsigned opcode;
     unsigned char ibuf[4];
   } uval;

   uval.opcode = encoding;

   int rcode = my_simulator.WriteMemory(0,&my_packet,(unsigned long long) STARTING_PC,INSTRUCTION,4,uval.ibuf); 

   if (rcode) {
     printf("ERROR: problems writing opcode to address 0x%llx ???\n",(unsigned long long) STARTING_PC);
   }

   for (int i = 0; i < 30; i++) {
     my_simulator.cpus[0].GP[i].Value(i * 1024);
   }

   for (int i = 0; i < 31; i++) {
     float fv = 1.0 * i;
     my_simulator.cpus[0].V[i].Single(fv);
   }

   string rcode_decoded = "?";

   //printf("[gen_instr] step...");
   
   rcode = my_simulator.StepNextInstruction(0,DECODE_STATE,&my_packet,rcode_decoded);

   //printf("step complete.\n");
   
   if (rcode) {
     printf("    ERROR: Instruction failed to decode.\n");
     return DECODE_FAIL;
   }

   char disasm[1024];
   strcpy(disasm,"?");
   if (!rcode) {
     try {
        my_simulator.DisassemblyInstruction(0,disasm,&my_packet);
     } catch(...) {
        printf("    ERROR: Instruction failed to disassemble.\n");
        return DISASM_FAIL;
     }
   }

   printf("    instr %d, encoding 0x%8x, name '%s', enum '%s', disassembly: %s",
          instr_index,encoding,my_packet.InstrName().c_str(),my_packet.InstrEnumName().c_str(),disasm);

   rcode = my_simulator.StepNextInstruction(0,FETCH_OPERANDS_STATE,&my_packet,rcode_decoded);

   if (rcode) {
     printf("    ERROR: problems fetching operands for instruction %s, rcode: %d???\n",
            my_packet.InstrEnumName().c_str(),rcode);
     printf("       exception class/type/subtype: %s/%s/%s\n",my_packet.exceptionClass().c_str(),
            my_packet.archExceptionType().c_str(),my_packet.archExceptionSubtype().c_str());
     return FETCHOPS_FAIL;
   }

   rcode = my_simulator.StepNextInstruction(0,EXECUTE_STATE,&my_packet,rcode_decoded);

   if (rcode) {
     printf("    ERROR: problems executing instruction %s, rcode: %d???\n",my_packet.InstrEnumName().c_str(),rcode);
     return EXECUTE_FAIL;
   }

   rcode = my_simulator.StepNextInstruction(0,MEMORY_ACCESS_STATE,&my_packet,rcode_decoded);

   if (rcode) {
     printf("    ERROR: problems accessing memory for instruction %s, rcode: %d???\n",my_packet.InstrEnumName().c_str(),rcode);
     my_packet.DumpMemoryAccesses();
     return MEMACCESS_FAIL;
   }

   rcode = my_simulator.StepNextInstruction(0,WRITEBACK_STATE,&my_packet,rcode_decoded);

   if (rcode) {
     printf("    ERROR: problems with writeback for instruction %s, rcode: %d???\n",my_packet.InstrEnumName().c_str(),rcode);
     return WRITEBACK_FAIL;
   }

   return 0;
}

int run_test(int instr_index, int retries_count) {
  printf("[run_test] entered, instr index: %d...\n",instr_index);

  int rcode = 0;
   
  string instr_enum;

  for (int i = 0; i < retries_count; i++) {
     printf("  pass %d...\n",i + 1);

     X64Simulator my_simulator;

     my_simulator.memory.SetPhysicalSize(32);

     std::string test_harness_image = VFP_TEST_HARNESS;
 
     my_simulator.Load(test_harness_image);

     Packet my_packet(FOR_SIMULATION);

     rcode = gen_instr(my_simulator,my_packet,instr_index);

     if (i == 0) {
       instr_enum = my_packet.InstrEnumName();
     }

     if (!rcode) {
       rcode = setup_unit_test(my_simulator,my_packet);
       break;
     }
  }

  if (rcode) {
    printf("  ERROR: problems generating or executing vfp instruction %s, rcode: %d???\n",instr_enum.c_str(),rcode);
  } else {
    printf("  vfp instruction '%s' executed!\n",instr_enum.c_str());
  }

  printf("[run_test] exited\n\n");

  return rcode;
}

int setup_unit_test(X64Simulator &my_simulator,Packet &my_packet) {
   char current_dir[1024];

   if (getcwd(current_dir,1024) == NULL) {
       fprintf(stderr,"ERROR: getcwd returned NULL???\n");
       return -1;
   }

   char test_dir[1024];
   sprintf(test_dir,"unit_test/test/%s",my_packet.InstrEnumName().c_str());

   int rcode = mkdir(test_dir, 0755);

   if ( (rcode != 0) && (errno != EEXIST) ) {
       fprintf(stderr,"ERROR: Unable to create test dir '%s'\n",test_dir);
       return -1;
   }
  
   if (chdir(test_dir)) {
       fprintf(stderr,"ERROR: Unable to 'chdir' into test dir '%s'\n",test_dir);
       return -1;
   }

   printf("TEST DIR '%s' CREATED!\n",test_dir);

   // write out ELF file...

   char elf_file[1024];
   sprintf(elf_file,"%s.elf",my_packet.InstrEnumName().c_str());

   std::string ef = elf_file;

   rcode = my_simulator.Save(ef);

   if (rcode)
     printf("ERROR: problems saving test case ELF...\n");\

   if (chdir(current_dir)) {
     fprintf(stderr,"ERROR: Unable to 'chdir' back to starting dir '%s' ?\n",current_dir);
     return -1;
   }

   return 0;
}
