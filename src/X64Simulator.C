
//#define FOR_MAC_IOS 1

#ifdef FOR_MAC_IOS
#import "X64Simulator.h"
#else
#include "X64Simulator.h"
#endif

#include <memory>

//#define FOR_KERNEL_DEBUG 1
//#define HALT_DEBUG 1
//#define ARMV8_FOUNDATION_MODEL 1

// certain instructions (example: SYS) may or may not be implemented on some cores and thus need to
// be avoided when generating random sequences...
#define AVOID_QUASI_PRIVILEGED_OPS 1

//#define SHOW_INSTR_COUNTS 1

namespace X64SIM_UTILS {
  #include "test_a64sim_utils.C"
  #include "a64sim_easy_picks.C"
}

//***********************************************************************************************************
// X64Simulator::Go()
//***********************************************************************************************************

int X64Simulator::Go(unsigned long long reset_address) {
  bool trace_is_enabled = !SimTraceFile().empty();

  if (trace_is_enabled) {
    my_trace.SetFilePath(simtrace_file);
    my_trace.RecordCoreCount(num_cores);
  }

  InitSimulator();
  SetResetAddress(reset_address);
  ProcessConfigOverrides();
  ReserveRegisters(reserved_registers);
  
  if (LoadSupportCode()) {
    // problems loading boot code, etc. abort...
    return -1;
  }

  for (vector<struct dll>::iterator i = userspace_dlls.begin(); i != userspace_dlls.end(); i++) { 
     try {
        UserSpace::Load((*i).path);
        UserSpace::Init(cpus,num_cores,(*i).options);
     }
     catch(const std::runtime_error& ex) {
        // problems loading user-space dll. abort...
        std::cerr << ex.what() << std::endl;
        return -1;
     }
  }
  
  int rcode = 0;
  
  if (Simulate()) {
    // simulation errors occurred...
    rcode = -1;
  }

  if (SemihostExitCode()) {
    // program under test has flagged some error...
    rcode = -1;
  }

  UserSpace::Unload();
  
  return rcode;
}

//***********************************************************************************************************
// X64Simulator::ProcessConfigOverrides() - a few command line options have been provided (in this ap) to 
//                                          override the base level configuration. Apply them here...
//***********************************************************************************************************

void X64Simulator::ProcessConfigOverrides() {
  bool on_or_off = false;

  if (ConfigureSystemCalls(on_or_off)) {
    if (exception_enables.Enabled(ARCH_EXCEPTION,EXCEPTION_GENERATING_INSTRUCTION) == on_or_off) {
     // specified enable matches currently configured value...
    } else if (on_or_off) {
      // DO allow system call...
      exception_enables.Add(1,ARCH_EXCEPTION,EXCEPTION_GENERATING_INSTRUCTION);
      TraceLogEntry("  # Exception Enables.EXCEPTION_GENERATING_INSTRUCTION: Enabled (via override).\n");
    } else {
      // DO NOT allow system call...
      exception_enables.Add(0,ARCH_EXCEPTION,EXCEPTION_GENERATING_INSTRUCTION);
      TraceLogEntry("  # Exception Enables.EXCEPTION_GENERATING_INSTRUCTION: Disabled (via override).\n");
    }
  }
}

//***********************************************************************************************************
// X64Simulator::Simulate()
//***********************************************************************************************************

bool X64Simulator::Simulate() {
  FreeRunReset();

  int total_num_instrs = 0;
  int total_num_iterations = 0;

  bool sim_err = false;

  if (use_threads) {
    // WORKING AT ONE POINT, BUT NOT CURRENTLY SUPPORTED...
    //sim_err = !SimulateViaThreads(total_num_instrs,total_num_iterations);
  } else {
    sim_err = !SimulateViaReadyQueue(total_num_instrs,total_num_iterations);
  }

  SetSimulatedCount(total_num_instrs);

  my_trace.RecordFinalCounts(total_num_instrs);

  WriteSimTrace();

  my_trace.WriteSimTraceSummary();

  if (sim_err && ((total_num_iterations <= 1) || (total_num_instrs <= 1)) ) {
     // errors and (almost) no output. don't bother to summarize...
  } else if (max_instrs_per_core < 0) {
    // no max instr count specified. for now, don't risk overflow reporting talleys...
  } else {
     printf("For %d cores:\n",num_cores);
     printf("   Total # of iterations %d\n",total_num_iterations);
     printf("   Total # of instructions simulated: %d\n",total_num_instrs);
  }

  if (FreerunEnabled())
     FreeRunTalleys();

  ShutdownDebugServer();

  return sim_err;
}


enum X64SIM_ERR_CODES { X64SIM_NO_SIM_ERROR=0, X64SIM_TEST_ENDS=1, X64SIM_RANDOM_INSTR_ERR=-1, 
                        X64SIM_FETCH_FROM_UNINITIALIZED_MEMORY=-2, X64SIM_SIMULATION_ERROR=-3, X64SIM_INTERNAL_ERROR=-4 
};


// simulate main loop, implemented using omp - THIS METHOD HAS FALLEN ON HARD TIMES, IE, IS NO LONGER BEING MAINTAINED.

bool X64Simulator::SimulateViaThreads(int &total_num_instrs, int &total_num_iterations) {
    int icnt,rcode;
    string rcode_decoded;

    bool sim_err = false;
    
    #pragma omp parallel private(icnt,rcode,rcode_decoded)
    {
      #pragma omp for
      for (int n = 0; n < num_cores; n++) { 
	 // ultimately should have way of knowing that all cores have reached end-of-test...
      
 	 bool test_end = false;

         for (icnt = 0; (icnt < max_instrs_per_core) && !sim_err && !test_end; icnt++) {
            #pragma omp critical
            { 
             // let only one thread at a time have access to the trace handle...
             if (my_trace.NeedInitialState()) RecordInitialState();  
	    }

            rcode = X64SIM_NO_SIM_ERROR;
            try {
               rcode = SimulateNextInstruction(n,-1,NULL,rcode_decoded);
	    } catch (SIM_EXCEPTION_CLASS eclass) {
              printf("ABORT: '%s'\n",rcode_decoded.c_str());
	      sim_err = true; ///o fudge...      
	    }

            if (rcode != X64SIM_NO_SIM_ERROR) {
              #pragma omp critical
              {
		if (rcode == X64SIM_TEST_ENDS) {
                  // core is (or should be) halted...
                  cpus[n].Halt();
                  test_end = true;
                } else {               
                  printf("Step failed. Aborting simulation...\n");
                  rcode = ReportStepFailed(n,NULL);
                  sim_err = true;
		}
	     }
	    } else {
             #pragma omp critical
             { 
	       total_num_instrs += 1;
	     }
	   }
	 }

         if (!sim_err && !test_end) {
	   // simulated desired # of instructions but test is not ended...
           HaltCore(n);
	   sim_err = true;
	 }
      }
    }

    total_num_iterations = max_instrs_per_core;

    return sim_err;
}

bool X64Simulator::SimulateViaReadyQueue(int &total_num_instrs, int &total_num_iterations) {
   //printf("[SimulateViaReadyQueue] entered...\n");

   bool sim_err = false;
  
   bool cores_are_running = true; //<--- ASSUME one or more cores are running...

   if (FreerunEnabled()) {
     // if 'free-running' test will end at max-instrs plus a few extra instructions needed to 'halt' each core...
   } else {
     // gasp! extra instrs added to halt a core better not exceed 10 instrs per core!!!
     max_instrs_per_core += 10; // add a few extra instrs to max-count to allow test to end close to max instrs...
   }
   
   bool do_instr_counts = max_instrs_per_core >= 0; // negative max instrs per core means run forever...
   
   while( (!do_instr_counts || (total_num_instrs < (max_instrs_per_core * num_cores))) && !sim_err && cores_are_running) {
     //printf("[SimulateViaReadyQueue] iteration: %d\n",total_num_iterations);
     
     if (do_instr_counts)
       total_num_iterations += 1; //<--- iterations over one or more cores...

     vector<int> step_cpus;

     cores_are_running = GetReadyCpus(step_cpus); 

     // update system counter, core timers, device clocks...
     
     system_counter.advanceClock();
     for (int i = 0; i < num_cores; i++) {
       if (!cpus[i].IsHalted()) {
	 cpus[i].advanceClock();
	 cpus[i].AdvanceTimers(); //<---timers advance as long as core is not halted
       }
     }
     uart.advanceClock();

     for (int i = 0; (i < (int) step_cpus.size()) && cores_are_running; i++) {
        // see if any devices need servicing...

        // uart is only device implemented thusfar...
        if (uart.IsImplemented()) { 
	  uart.ServiceIOs();
	  /* uart interrupt not supported yet...
	  int int_info;
	  if (uart.InterruptPending(int_info)) {
	    // until GIC is implemented, uart interrupt is tied to cpu0 IRQ...
            cpus[0].SignalIRQ();
	  }
	  */
        }
       
        if (my_trace.NeedInitialState())
          RecordInitialState();

        int cpuid = step_cpus[i];

        //printf("[SimulateViaReadyQueue] next instruction started (#iterations: %d)...\n",total_num_iterations);

        string rcode_decoded;
        int rcode = SimulateNextInstruction(cpuid,-1,NULL,rcode_decoded);

        //printf("[SimulateViaReadyQueue] next instruction ended, rcode:%d...\n",rcode);
 
        if (rcode == X64SIM_NO_SIM_ERROR) {
           // no errors so far...
        } else if (rcode == X64SIM_TEST_ENDS) {
           // core is (or should be) halted...
	   cpus[cpuid].Halt();
	   //printf("Core %d is halted!\n",cpuid);
	} else {
	   // break on any simulate error...
           printf("Step failed. Aborting simulation...\n");
           rcode = ReportStepFailed(cpuid,NULL);
           sim_err = true;
           break;
	}
     }

     if (do_instr_counts) {
       if (step_cpus.size() > 0)
         total_num_instrs += step_cpus.size();
       else if (cores_are_running) {
	 total_num_instrs += 1;
         std::cerr << "NOTE: All cores waiting?..." << std::endl;
       }
     }
   }


    // watch out for case wherein all cores are waiting...
   
    int num_cores_waiting = 0;

    for (int n = 0; n < num_cores; n++) { 
      if (cpus[n].IsWaiting()) {
        num_cores_waiting += 1;
      }
    }

    if (num_cores_waiting == num_cores) {
      std::cerr << "WARNING: All cores are waiting? Was this expected?" << std::endl;
    } else if (num_cores_waiting > 0) {
      std::cerr << "WARNING: " << num_cores_waiting << " cores are waiting. Was this expected?" << std::endl;
    }
    
    // have simulated the desired # of instructions. make sure all cores are halted...

    int halt_count = 0;
    
    for (int n = 0; n < num_cores; n++) { 
      if (cpus[n].IsWaiting()) {
	 // a core waiting at the alter, so sad...
	 sim_err = true;
      } else if (cpus[n].IsHalted()) {
	 // this core is already halted. lets assume thats okay...
	 halt_count += 1;
      } else if (FreerunEnabled()) {
	 // if 'free run' enabled, then lets assume we got here by design (we intended to generate this many instructions)
	 //   and cause cores to be halted...
	 halt_count += 1;
 	 HaltCore(n);	
      } else {
	 // halt it anyway - by 'halting' test, maybe test is salvageable?...
	 HaltCore(n);	
       }
    }

    // we expect all cores to be halted.
    // if one or more cores is not halted we ASSUME an error...

    //printf("[SimulateViaReadyQueue] exited, sim-err: %d\n",sim_err);

    bool ended_early = !sim_err && (halt_count != num_cores);

    if (ended_early) {
      if (halt_count == 0)
        fprintf(stderr,"WARNING: test ended after specified or maximum # of instructions reached (%d per core), but the processor does not appear to be halted as expected.\n",
		max_instrs_per_core);
      else
        fprintf(stderr,"WARNING: test ended after specified or maximum # of instructions reached (%d per core), but only %d cores appear to be halted as expected.\n",
	        max_instrs_per_core,halt_count);
      sim_err = true;
    }
    
    return !sim_err;
}


//***********************************************************************************************************
//***********************************************************************************************************

bool X64Simulator::GetReadyCpus(vector<int> &step_cpus) {
  bool have_running_cpus = false;
  
  for (int i = 0; i < num_cores; i++) {
     if (cpus[i].IsHalted()) {
       // a halted cpu is not ready...
     } else if (cpus[i].IsWaiting()) {
       // a waiting cpu is not ready...
       step_cpus.push_back(cpus[i].GetID()); // but could go ready depending
       have_running_cpus = true;             //  on cpu events...
     } else {
       step_cpus.push_back(cpus[i].GetID());
       have_running_cpus = true;
     }
  }
     
  // random execution order for those cpus ready to execute...

  if (step_cpus.size() > 1)
    random_shuffle(step_cpus.begin(), step_cpus.end());

  return have_running_cpus;
}

//***********************************************************************************************************
//***********************************************************************************************************

bool X64Simulator::GetReadyCpus(vector<int> &step_cpus,unsigned long long &clock_advance) {
     // each cpu has its own clock. cpu clock is advanced each time an instruction executes.

     // look for shortest execution time from previous instructions executed...

     unsigned long long _clock_advance = cpus[0].Clock();

     for (int i = 0; i < num_cores; i++) {
        if (cpus[i].IsHalted()) {
          // a halted cpu is not ready...
	} else if (cpus[i].IsWaiting()) {
          // a waiting cpu's clock is still running...
	  printf("[X64Simulator::GetReadyCpus] CPU IS WAITING...\n");
	  cpus[i].advanceClock();
        }
        if (cpus[i].Clock() < _clock_advance)
          _clock_advance = cpus[i].Clock();
     }

     // come up with list of cpus ready to step based on shortest execution time...

     for (int i = 0; i < num_cores; i++) {
        if (cpus[i].IsHalted()) {
          // halted cpu is not ready...
        } else if (cpus[i].IsWaiting()) {
          // waiting cpus are not ready, but might wake up, so assume they are ready...
	  printf("[X64Simulator::GetReadyCpus] CPU IS WAITING, ASSUME ITS 'READY'...\n");
          step_cpus.push_back(cpus[i].GetID());
        } else if (cpus[i].Clock() <= _clock_advance) {
          step_cpus.push_back(cpus[i].GetID());
	}
     }

     // if no cpus are ready, bail...

     if (step_cpus.size() == 0)
       return false;
     
     // random execution order for those cpus ready to execute...

     random_shuffle(step_cpus.begin(), step_cpus.end());

     // advance system clock from lowest cpu clock...

     syncClock(_clock_advance);

     clock_advance = _clock_advance;

     // if we got here there is at least one cpu ready...

     return true;
}

//***********************************************************************************************************
// HaltCore - at the end of a simulation, generate end-test sequence for each core. ask me how!
//***********************************************************************************************************

int X64Simulator::HaltCore(unsigned int cpuid) {
#ifdef HALT_DEBUG
     printf("[X64Simulator::HaltCore] entered...\n");
#endif
     
     if (cpus[cpuid].IsHalted()) {
#ifdef HALT_DEBUG
       printf("[X64Simulator::HaltCore] core %d IS halted.\n",cpuid);
#endif
       return 0;
     }
     
     unsigned long long PC = cpus[cpuid].PC.Value();

     unique_ptr<Packet> ipacket_holder((Packet *) NULL);
     #pragma omp critical
     {
     ipacket_holder.reset(new Packet(FOR_SIMULATION));
     }
     
     Packet *ipacket = ipacket_holder.get();

     unsigned char tbuf[128]; //<---opcode for instruction at PC, if there is one...

     if (!InstructionMemoryIsFree(cpuid,PC,ipacket,4,tbuf)) {
       // hmmm. maybe we are at the test end?...
       if (TestEndReached(tbuf))
         return 0;
       // OOPS! we need to halt this core, but can't issue the instruction (sequence) to do so...
       // (this could have occurred if the core in question did't complete its simulation or is stuck)
#ifdef HALT_DEBUG
       printf("[X64Simulator::HaltCore] OOPS! we need to halt this core (core %d), but can't issue the instruction (sequence) to do so...\n",cpuid);
#endif 
       return -1;
     }

     int halt_wfi_offset = 0;

#ifdef ARMV8_FOUNDATION_MODEL     
     printf("[X64Simulator::HaltCore] stuff semihosting sequence to end simulation...\n");

     Packet ipacketX(FOR_SIMULATION);
     unsigned int encodingX = 0x52800300; // movz w0,#0x18
     ipacketX.recordInstrEncoding(encodingX); 
     WriteOpcodeToMemory(cpuid,PC,&ipacketX,encodingX);
     encodingX = 0xd45e0000; // hlt #0xf000
     ipacketX.recordInstrEncoding(encodingX); 
     WriteOpcodeToMemory(cpuid,PC + 4,&ipacketX,encodingX);
     halt_wfi_offset = 8;
#endif

     int rcode = 0;
     
     string end_test_file;
     
     if (HaveEndTestFile(end_test_file)) {
       // load end-test code at the current PC. will assume there is room...
#ifdef HALT_DEBUG
       printf("[X64Simulator::HaltCore] load end-test code (from '%s') at the current PC (0x%llx). Will assume there is room...\n",
              end_test_file.c_str(),PC);
#endif
       rcode = Load(end_test_file,PC);
     } else {
       // always stuff "halt" WFI instruction...
     
#ifdef HALT_DEBUG
       printf("[X64Simulator::HaltCore] stuff WFI into memory at PC, halt cpu...\n");
#endif
       
       SetEndTest(); //<---must be set for each core; affects instruction selection...
     
       string group = "?";
       unsigned int encoding = 0;

       SelectInstruction(group,encoding,false);
       ipacket->recordInstrEncoding(encoding);
       rcode = WriteOpcodeToMemory(cpuid,PC + halt_wfi_offset,ipacket,encoding);
     }
     
#ifdef HALT_DEBUG
     printf("[X64Simulator::HaltCore] PC AT END: 0x%llx, opcode: 0x%08x\n",PC + 8,encoding);
#endif
     
     cpus[cpuid].Halt();
 
     return rcode;
}


#define WFI_OPCODE 0xd503207f
#define HLT_OPCODE 0xd45e0000

bool X64Simulator::TestEndReached(unsigned char *ibuf) {
  // ibuf - pointer to opcode in memory (for arm, instructions are always
  //        little endian). Return true if this is WFI instruction...
  bool end_test_code = ( (ibuf[0]==0x7f) && (ibuf[1]==0x20) && (ibuf[2]==0x03) && (ibuf[3]==0xd5) );
  //if (end_test_code) {
  //  printf("END TEST REACHED!!!\n");
  //}
  
#ifdef FOR_KERNEL_DEBUG
  if (end_test_code) {
    end_test_code = false;
    printf("[X64Simulator::TestEndReached] IGNORING WFI!!!\n");
  }
#endif
  
  return end_test_code;
}

bool X64Simulator::SemihostRequest(unsigned char *ibuf) {
  bool semihost_request = ( (ibuf[0]==0x00) && (ibuf[1]==0x00) && (ibuf[2]==0x5e) && (ibuf[3]==0xd4) );
  return semihost_request;
}

bool X64Simulator::IllegalOpcode(unsigned int opcode) {
  // for now, the only 'illegal' opcode is WFI, which is intended to signal a test-end...
  // added support for semihosting, HLT instruction (hlt #0xf000) trigger it...
  if ( (opcode == WFI_OPCODE) || (opcode == HLT_OPCODE) )
    return true;

#ifdef AVOID_QUASI_PRIVILEGED_OPS
  // SYS or SYSL...
  if ( ((opcode & 0xfff80000) == 0xd5080000) || ((opcode & 0xfff80000) == 0xd5280000) )
    return true;

  // YIELD (but NOT NOP dummy!)...
  if ( ((opcode & 0xfffff01f) == 0xd503201f) && (opcode != 0xd503201f) )
    return true;

  // MSR SPSel,x...
  if ((opcode & 0xfffff0ff) == 0xd50040bf)
    return true;
#endif
  return false;
}

//***********************************************************************************************************
// ReadSimulatorMemory, WriteSimulatorMemory - the simulator 'supplied' read/write memory methods (for
//    historical reasons) only read/write fixed block sizes of memory. These local methods then allow for
//    an arbitrary # of bytes to be read or written.
//***********************************************************************************************************

int X64Simulator::ReadSimulatorMemory(int cpuid, Packet *ipacket, unsigned long long simulator_LA, int instr_vs_data, 
                                      int num_bytes, unsigned char *dest_buffer, bool init_if_free) {

  return ReadMemory(cpuid,ipacket,simulator_LA,instr_vs_data,num_bytes,dest_buffer,init_if_free);
}

int X64Simulator::WriteSimulatorMemory(int cpuid, Packet *ipacket, unsigned long long simulator_LA, int instr_vs_data, 
                                       int num_bytes, unsigned char *src_buffer) {
   return WriteMemory(cpuid,ipacket,simulator_LA,instr_vs_data,num_bytes,src_buffer);
}

//***********************************************************************************************************
//***********************************************************************************************************

int X64Simulator::HandleSemihostingOperation(int cpuid, Packet *ipacket) {
  if (semihost_helper == NULL) 
    semihost_helper = new a64SemiHosting(&cpus[cpuid],&memory,app_sh_parms);

  return semihost_helper->Dispatch(ipacket,false /* verbose */);
}

//***********************************************************************************************************
//***********************************************************************************************************

void X64Simulator::SetDebugServerParms(int _debug_port,unsigned int _debug_core_id) {
  debug_port = _debug_port;
  debug_core_id = debug_core_id;

  if (debug_port > 0) {
    printf("configuring debug server on port %d, attached to core %u...\n",_debug_port,_debug_core_id);
    dbg_server = new a64DebugServer(debug_port,debug_core_id);
  }
  
  //printf("[X64Simulator::SetDebugServerParms] port: %d, core: %u\n",debug_port,debug_core_id);
}

bool X64Simulator::DebugServerEnabled() {
  bool is_enabled = dbg_server != NULL; //<---do we have a debug server?...
  //printf("[X64Simulator::DebugServerEnabled] enabled? %d\n",is_enabled);
  return is_enabled;
}

void X64Simulator::ShutdownDebugServer() {
  if (DebugServerEnabled())
    delete dbg_server;
}

bool X64Simulator::DebugPreStepChecks(State *my_cpu, Memory *my_memory, unsigned long long PC, Packet *ipkt) {
  if (!DebugServerEnabled())
    return true; //<---only return false if debug server aborts or exits...
  
  //printf("[X64Simulator::DebugPreStepChecks] PC: 0x%llx\n",PC);
  
  return dbg_server->RunPreStepChecks(my_cpu,my_memory,PC,ipkt);
}

bool X64Simulator::DebugPostStepChecks(State *my_cpu, Memory *my_memory, unsigned long long PC, Packet *ipkt) {
  if (!DebugServerEnabled())
    return true; //<---only return false if debug server aborts or exits...
  
  //printf("[X64Simulator::DebugPostStepChecks] PC: 0x%llx\n",PC);
    
  return dbg_server->RunPostStepChecks(my_cpu,my_memory,PC,ipkt);
}


//***********************************************************************************************************
// SimulateNextInstruction
//
// return codes:
//     0   - no error, no change in simulation state
//     1   - no error, but test end-sequence encountered
//    -1   - error on attempt to insert/simulate random opcode
//    -2   - instruction fetch from uninitialized memory
//    -3   - simulation error
//***********************************************************************************************************

int X64Simulator::SimulateNextInstruction(unsigned int cpuid,int phase,Packet * /*ipacket*/, string &rcode_decoded) {
     unsigned long long PC = cpus[cpuid].PC.Value();              // record cpu PC, clock
     unsigned long long starting_clock = cpus[cpuid].Clock();     //    prior to instruction execution

     unique_ptr<Packet> ipacket_holder((Packet *) NULL);
     #pragma omp critical
     {
     ipacket_holder.reset(new Packet(FOR_SIMULATION));
     }
     Packet *ipacket = ipacket_holder.get();

     int rcode = X64SIM_NO_SIM_ERROR;
     bool mfree = false;
     int retries_count = 0;

     unsigned char tbuf[128];

     if (InstructionMemoryIsFree(cpuid,PC,ipacket,4,tbuf)) {
        if (FreerunEnabled()) {
          // generate instruction... 
          #pragma omp critical
          {
           ipacket_holder.reset(new Packet(FOR_TEST));
          }
          ipacket = ipacket_holder.get();
          mfree = true;
	  
          //printf("[SimulateNextInstruction] make N attempts to pick/encode/step a single instruction...\n");
	  
          for (int j = 0; j <= max_retries_count; j++) {
             bool first_try = (j == 0);
	     bool last_try = (j == max_retries_count); // will result in one last desparate attempt to generate something...
	     
             retries_count += 1;

             try {
	       int freerun_rcode = FreerunStep(cpuid,PC,ipacket,rcode_decoded,first_try,last_try);
	       if (freerun_rcode == X64SIM_TEST_ENDS) {
                 return X64SIM_TEST_ENDS;
	       }
	       if (freerun_rcode != 0)
	         rcode = X64SIM_RANDOM_INSTR_ERR;
	       else
		 rcode = X64SIM_NO_SIM_ERROR;
	       //printf("\tfreerun_rcode: %d, rcode: %d, retry-count: %d\n",freerun_rcode,rcode,j);
	     } catch (SIM_EXCEPTION_CLASS eclass) {
	        //printf("ABORT RANDOM: '%s'\n",rcode_decoded.c_str());
	        rcode = X64SIM_RANDOM_INSTR_ERR; ///o fudge...      
	     }

             if (!rcode)
               break;

             #pragma omp critical
             {
              ipacket_holder.reset(new Packet(FOR_TEST));
	     }
             ipacket = ipacket_holder.get();
	  }

	  //printf("[SimulateNextInstruction] rcode: %d, retries count: %d\n",rcode,retries_count);
		    
        } else {
          // OOPS! ran into uninitialized memory but not authorized to insert random code, ie, help: I've fallen and can't get up...
          rcode = X64SIM_FETCH_FROM_UNINITIALIZED_MEMORY;
          #pragma omp critical
          {
           fprintf(stderr,"ERROR: instruction fetch from uninitialized memory, PC: 0x%llx\n",PC);
	  }
        }
     } else {
        // simulate existing instruction...
        //printf("\tsimulate existing instruction...\n"); 

        // see if end-test instruction reached...

        if (TestEndReached(tbuf)) {
          return X64SIM_TEST_ENDS;
        }
	// see if instruction to be executed is of debug interest...
        if (!DebugPreStepChecks(&cpus[cpuid],&memory,PC,ipacket)) {
          return X64SIM_TEST_ENDS;
        }	  
        if (SemihostRequest(tbuf)) {
          // handle semihosting operation...
          //printf("handle semihosting operation...\n");
          if (HandleSemihostingOperation(cpuid,ipacket) == 0x100) {
	    // application has exited...
            printf("application has exited...\n");
            return X64SIM_TEST_ENDS;
          }	  	    
          // let instruction that triggered semihosting execute...
	}
        try {
	   rcode = StepNextInstruction(cpuid,-1,ipacket,rcode_decoded) ? X64SIM_SIMULATION_ERROR : X64SIM_NO_SIM_ERROR;
	} catch (SIM_EXCEPTION_CLASS eclass) {
	  switch((int) eclass) {
	    case WAIT_FOR_EVENT:    // interpret WFE instruction to mean this core 'goes to sleep'...
	                            if (cpus[cpuid].WakeupPending()) {
				      std::cout << "# Core " << cpuid << " wakes up..." << std::endl;
	                              cpus[cpuid].ClearWaitState();
				      cpus[cpuid].ClearWakeup();
				      cpus[cpuid].AdvancePC();  // manually 'step' past the WFE...
				    } else {
	                              cpus[cpuid].EnterWaitState();
				      std::cout << "Core " << cpuid << " is waiting..." << std::endl;
				    }
				    break;
	    case EVENT_NOTICE:      // SEV instruction used to wake up any 'sleeping' cores...
	                            for (int sc = 0; sc < num_cores; sc++) {
				       if (cpus[sc].IsWaiting()) {
				         std::cout << "# Core " << sc << " wakes up..." << std::endl;
	                                 cpus[sc].ClearWaitState();
				         cpus[sc].AdvancePC();  // manually 'step' the waiting core...
				       }
	                            }
				    cpus[cpuid].AdvancePC();  // manually 'step' past the SEV...
				    break;
	   case EVENT_NOTICE_LOCAL: // not sure what to do with SEVL instruction. lets ignore it...
				    std::cout << "Ignoring SEVL..." << std::endl;
				    cpus[cpuid].AdvancePC();  // manually 'step' past the SEVL...
				    break;
	   default:                 // not prepared to handle any other exceptions...
	                            fprintf(stderr,"ABORT: '%s'\n",rcode_decoded.c_str());
				    rcode = X64SIM_SIMULATION_ERROR; ///o fudge...
				    break;
	  }
	}   
        #pragma omp critical
        {
         string igrp = ipacket->InstrName();
         ipacket->recordInstrGroup(igrp); //<---ideally Decode should also ID instruction group but dont want the overhead
        }
     }

     if (!cpus[cpuid].IsWaiting())
       ipacket->PC.Value(PC); //<---a bit of a hack: set PC 'back' to value before step, to
                              //    insure disassembly (in case of a relative branch) is correct...

     #pragma omp critical
     {
       if ( (ipacket->exception_type == IRQ) || (ipacket->exception_type == FIQ) ) {
         printf("### IRQ at or around 0x%08llx\n",ipacket->PC.Value());
       } else {
         if (sim_monitor) sim_monitor->Step(&cpus[cpuid],&memory,ipacket,cpus[cpuid].Clock(),cpuid);
         DisassembleInstruction(cpuid,ipacket,PC); //<---now packet has the disassembly dude!!!
         if (ShowProgress()) {
	   if (num_cores > 1) {
             printf("%03d  0x%08llx  0x%08x  %s",cpuid,ipacket->PC.Value(),ipacket->Opcode,ipacket->Disassembly().c_str());
	   } else {
	     if (cpus[cpuid].IsWaiting())
               printf("### (waiting) 0x%08llx  0x%08x  %s",ipacket->PC.Value(),ipacket->Opcode,ipacket->Disassembly().c_str());
	     else
               printf("0x%08llx  0x%08x  %s",ipacket->PC.Value(),ipacket->Opcode,ipacket->Disassembly().c_str());
	   }
       }
       }
     }

     // an error occurred?...

     switch(rcode) {
       case X64SIM_NO_SIM_ERROR:   // no errors. record simulation outcome...
                                   StepResultsToLog(cpuid,ipacket);
                                   break;
       case X64SIM_TEST_ENDS:      // test ended. assume results still useful, record simulation outcome...
                                   StepResultsToLog(cpuid,ipacket);
                                   break;
       case X64SIM_FETCH_FROM_UNINITIALIZED_MEMORY:
	                           // we ran into uninitialized memory. simulation fails. break it up, nothing to see here...
                                   break;
       case X64SIM_RANDOM_INSTR_ERR:
       case X64SIM_SIMULATION_ERROR: // simulation error. record outcome...
                                   #pragma omp critical
                                   { 
                                    fprintf(stderr,"ERROR: problems stepping? rcode: %d (%s) retries count: %d memory-free? %d\n",
                                            rcode,rcode_decoded.c_str(),retries_count,mfree);
                                    ErrorLogEntry(">>>>>0x%8.8llx 0x%8.8x  %s\n",PC,ipacket->Opcode,ipacket->Disassembly().c_str());
                                    fprintf(stderr,">>>>>0x%8.8llx 0x%8.8x  %s\n",PC,ipacket->Opcode,ipacket->Disassembly().c_str());
                                    for (vector<MemoryAccess>::iterator i = ipacket->mOpsMemory.begin(); i != ipacket->mOpsMemory.end(); i++) {
	                               fprintf(stderr,">>>>>0x%8.8llx   data access caused issue???",i->address);
                                       cerr << (*ipacket) << "\n" << (*i) << endl;
	                            }
	                           }
	                           break;
       default:                    rcode = X64SIM_INTERNAL_ERROR;
                                   break;
     }

     if (UserSpace::PostStep(&cpus[cpuid],&memory,ipacket,rcode) != UserSpace::SUCCESS) {
       rcode = X64SIM_SIMULATION_ERROR;
     }

     // try to get instruction into trace irregardless of outcome, for debug purposes...

     #pragma omp critical
     { 
      my_trace.RecordCpuSlice(&cpus[cpuid],&memory,ipacket,starting_clock,cpuid);
     }

     // see if executed instruction is of debug interest...
     if (!DebugPostStepChecks(&cpus[cpuid],&memory,PC,ipacket)) {
       rcode = X64SIM_TEST_ENDS;
     }	  

     return rcode;
}

//***********************************************************************************************************
//***********************************************************************************************************

// Init      - no meaning just yet 
// Reserve   - reserve memory for instruction (in mp/threading scenario prevent some other core from grabbing memory required for instruction)
// Select    - select random instruction group/master opcode
// Encode    - encode instruction opcode, operands
// Write     - write instruction encoding to memory
// Finalize  - no meaning just yet

int X64Simulator::FreerunStep(int cpuid,unsigned long long PC,Packet *ipacket,string &rcode_decoded,bool first_try,bool last_try) {
   bool verbose = false;
	    
   if (verbose) printf("[FreerunStep] entered, PC: 0x%llx, first-try? %d, last-try? %d...\n",PC,first_try,last_try);

   
   int user_freerun_directive = UserSpace::FreerunStep(&cpus[cpuid],&memory,ipacket,first_try,last_try);

   bool do_default_freerun = true;
   
   switch(user_freerun_directive) {
     case UserSpace::ABORT_TEST: return X64SIM_SIMULATION_ERROR; break;
     case UserSpace::END_TEST:   return X64SIM_TEST_ENDS; break;
     case UserSpace::SUCCESS:    return X64SIM_NO_SIM_ERROR; break;
     case UserSpace::FAIL:       return X64SIM_RANDOM_INSTR_ERR; break;
     case UserSpace::STEP:       do_default_freerun = false; break;
     case UserSpace::FREERUNSTEP: break;
     default: break;
   }

   
   string group = "?";
   unsigned int encoding = 0;

   int rcode = 0;
   
   if (do_default_freerun) {
     ipacket->State = FREERUN_INIT;
     ipacket->PC.Value(PC);
     ipacket->Pstate.Value(cpus[cpuid].Pstate.Value());

     if (verbose) printf("[FreerunStep] checkpt 1...\n");
   
     if (sim_monitor) sim_monitor->Step(&cpus[cpuid],&memory,ipacket,cpus[cpuid].Clock(),cpuid);

     ipacket->State = FREERUN_RESERVE_MEMORY;
     if (sim_monitor) sim_monitor->Step(&cpus[cpuid],&memory,ipacket,cpus[cpuid].Clock(),cpuid);

     if (verbose) printf("[FreerunStep] checkpt 2...\n");
   
     bool room_for_more = true; // prove me wrong...

     if (first_try) {
       // if this is the 1st try, then check ahead starting at the current PC
       // we ASSUME this address is free???
       room_for_more = InstructionMemoryIsFree(cpuid,PC,ipacket,8);
     } else {
       // if this is NOT the first try then we assume we have already generated a bogus
       // instruction at the current PC (and thus this address is NOT free). instead lets
       // look ahead 2 instructions past this (to be replaced) instruction...
       room_for_more = InstructionMemoryIsFree(cpuid,PC + 4,ipacket,8);
     }
   
     if (verbose && !room_for_more)
       printf(">>> WARNING: TOO CLOSE TO NEXT INSTR!\n");
   
     //bool need_branch = first_try && !room_for_more; // always allow room for at least two instructions

     bool need_branch = !room_for_more; // always allow room for at least two instructions. check on every call

     //if (need_branch) {
       // 1st time for this address AND the memory at/near this address is NOT free, ie, have run into an existing instruction...
       // too close to existing code or data (but not this instruction). request branch encoding... 
       //printf(">>> branch away from existing code at 0x%8.8llx...\n",PC);
     //}

     if (verbose) printf("[FreerunStep] checkpt 3...\n");

     SelectInstruction(group,encoding,need_branch,last_try); //<---OR MAYBE ADD STATE TO CONTROL THIS METHOD!!!

     if (IllegalOpcode(encoding)) { // illegal insofar as this particular test generator is concerned...
       if (verbose) printf("Illegal opcode?: 0x%x...\n",encoding);
       return -1;
     }

     // derive new method here...

     ipacket->recordInstrGroup(group); //<--record intended instruction group
     ipacket->recordInstrEncoding(encoding);

     ipacket->State = FREERUN_ENCODE_INSTRUCTION;
     if (sim_monitor) sim_monitor->Step(&cpus[cpuid],&memory,ipacket,cpus[cpuid].Clock(),cpuid);

     if (verbose) printf("Opcode to write: 0x%x (%s)...\n",encoding,group.c_str());

     ipacket->State = FREERUN_WRITE_INSTRUCTION;
     if (sim_monitor) sim_monitor->Step(&cpus[cpuid],&memory,ipacket,cpus[cpuid].Clock(),cpuid);

     rcode = WriteOpcodeToMemory(cpuid,PC,ipacket,encoding);

     ipacket->State = FREERUN_END_INSTRUCTION;
     if (sim_monitor) sim_monitor->Step(&cpus[cpuid],&memory,ipacket,cpus[cpuid].Clock(),cpuid);
   }

   
   if (verbose) printf("Stepping random instr...\n");

   try {
      rcode = StepNextInstruction(cpuid,-1,ipacket,rcode_decoded);
   } catch (SIM_EXCEPTION_CLASS eclass) {
      ipacket->exception_class = eclass;
      rcode = 1; ///o fudge...      
      if (verbose) {
      printf("[StepNextInstruction] ABORT:\n");
      printf("   eclass: %d\n",(int) eclass);
      printf("   rcode: %d (%s)\n",rcode,rcode_decoded.c_str());
      printf("   class: %d (%s)\n",ipacket->exception_class, ipacket->exceptionClass().c_str());
      printf("   type:  %d (%s)\n",ipacket->exception_type, ipacket->exceptionType().c_str());
      printf("   sub-type:  %d (%s)\n",ipacket->exception_subtype, ipacket->exceptionSubtype().c_str());
      DisassembleInstruction(cpuid,ipacket,PC);
      printf("   opcode: 0x%08x -- %s",encoding,ipacket->disassembly);
      }
   }

   if (verbose) printf("\tOutcome of random instr step: %d...\n",rcode);

   if (rcode) {
      ipacket->exception_class = rcode;
      if (verbose) {
      printf("   rcode: %d (%s)\n",rcode,rcode_decoded.c_str());
      printf("   state: %d\n",ipacket->State);
      printf("   class: %d (%s)\n",ipacket->exception_class, ipacket->exceptionClass().c_str());
      printf("   type:  %d (%s)\n",ipacket->exception_type, ipacket->exceptionType().c_str());
      printf("   sub-type:  %d (%s)\n",ipacket->exception_subtype, ipacket->exceptionSubtype().c_str());
      DisassembleInstruction(cpuid,ipacket,PC);
      printf("   opcode: 0x%08x -- %s",encoding,ipacket->disassembly);
      }
   }
   
   if (!rcode) {
     // make sure next instruction address does NOT itself cause exception. If it does, then back up cpu PC and try again...
     try {
        unsigned char xbuf[1024];
	ReadMemory(cpuid,ipacket,ipacket->NextPC.Value(),INSTRUCTION,4,xbuf,0);
     } catch (...) {
	if (verbose) printf("OOPS! INSTRUCTION EXECUTION RESULTED IN BAD PC 0x%llx!!! PREVIOUS PC: 0x%llx\n",cpus[CPUID].PC.Value(),PC);
	cpus[cpuid].PC.Value(PC);  
        rcode = -1;
	ipacket->exception_class = GENERATION_ERROR;
     } 

     TrackInstrGroup(group);
   }

   if (verbose) printf("[FreerunStep] exited, rcode = %d\n",rcode);

   return rcode;
}


void X64Simulator::ShowOptions() {
  printf("     Source (elf) object files to load:  ");
  if (elf_src_files.size() == 0) {
    printf(" <none>\n");
  } else {
    for (vector<string>::iterator i = elf_src_files.begin(); i != elf_src_files.end(); i++) {
       printf(" %s",(*i).c_str());
    }
    printf("\n");    
  }
  printf("     Output (elf) object file:            %s\n",(elf_dest_file=="") ? "<none>" : elf_dest_file.c_str());
  printf("     Simulation trace file:               %s\n",simtrace_file.c_str());
  printf("     # of cores to enable:                %d\n",num_cores);
  printf("     maximum instrs per core to simulate: %d\n",max_instrs_per_core);
  printf("     freerun enabled?:                    %d\n",enable_freerun);
  printf("     seed (for use by freerun):           %d\n",seed);
}

int X64Simulator::ValidateOptions() {
  if (num_cores <= 0) {
    printf("ERROR: Invalid core count (%d).\n",num_cores);
    return -1;
  }

  if (num_cores > MaxCores()) {
    printf("ERROR: number of cores specified (%d) exceeds the current implementation maximum of %d.\n",
           num_cores,MaxCores());
    return -1;
  }

  bool have_boot_code = elf_src_files.size() > 0; // we ASSUME that if elf src files are present, then MP boot code is too...

  if ( (CoreCount() > 1) && !have_boot_code) {
     printf("ERROR: Core count specified is greater than one, but no (MP) boot code has been specified. Program aborted.\n");
     return -1;
  }

  printf("  Setup appears valid.\n");

  return 0;
}

int X64Simulator::SetThreadedCoreCount(int _nthreads) {
  use_threads = true;
  return 0;
} 

int X64Simulator::LoadSupportCode() {
  for (vector<string>::iterator i = elf_src_files.begin(); i != elf_src_files.end(); i++) {
    if (Load(*i))
      return -1;
  }
  return 0;
}

void X64Simulator::RecordInitialState() {
  unsigned long long PC = 0;
  char rname[] = "PC";

  for (int i = 0; i < num_cores; i++) {
     ReadRegister(i,rname,&PC);
     TraceLogEntry("# Starting PC: 0x%llx\n",PC);
     my_trace.RecordCpuInitialState(&cpus[i],i);    //<---implies core[i] added to sim-trace, initial state too...
     if (sim_monitor) sim_monitor->Initialize(&cpus[i],i);
  }
}

void X64Simulator::WriteSimTrace() {
  my_trace.ToFile();
}

void X64Simulator::DisassembleInstruction(unsigned int cpuid,Packet *ipacket,unsigned long long PC) {
   char tbuf[1024];

   try {
        DisassemblyInstruction(cpuid,tbuf,ipacket);
        string disasm = string(tbuf);
        ipacket->recordDisassembly(disasm);
   }
   catch(...) {
	ErrorLogEntry(">>>>>0x%8.8llx   Disassembly not available on apparently correctly formed instruction?\n",PC);
        TraceLogEntry("0x%8.8llx   ???\n",PC);
   }
}

int X64Simulator::ReportStepFailed(unsigned int cpuid,Packet *ipacket) {
  return -1;
}

void X64Simulator::StepResultsToLog(unsigned int cpuid,Packet *ipacket) {
}

int X64Simulator::SaveTestImage() {
  int rcode = 0;

  if (elf_dest_file.empty()) {
    fprintf(stderr,"Unable to save. No (ELF) output file specified?\n");
    rcode = -1;
  } else {
    printf("\nSaving test (elf64 format) image to file '%s'...",elf_dest_file.c_str());
    fflush(stdout);
    rcode = Save(elf_dest_file, ResetAddress());
    if (rcode) {
      fprintf(stderr,"Save failed!\n");
    } else {
      printf("done.\n");
    }    
  }

  return rcode;
}

bool X64Simulator::InstructionMemoryIsFree(int cpuid,unsigned long long PC,Packet *ipacket, int byte_count, unsigned char *tbuf) {
  unsigned char mbuf[128];

  unsigned char *mptr = (tbuf != NULL) ? tbuf : mbuf;

  bool is_free = true;
  
  try {
    is_free = (ReadMemory(cpuid,ipacket,PC,INSTRUCTION,byte_count,mptr,0) == ALL_BYTES_FREE);
  } catch (...) {
    //printf("[X64Simulator::InstructionMemoryIsFree] if there was a problem reading memory, then will ASSUME memory is NOT free...\n");
    is_free = false;
  }

  //printf("[X64Simulator::InstructionMemoryIsFree] free? %d\n",is_free);
  
  return is_free;
}

int X64Simulator::WriteOpcodeToMemory(int cpuid,unsigned long long PC,Packet *ipacket,unsigned int encoding) {
   union {
     unsigned opcode;
     unsigned char ibuf[4];
   } uval;

   uval.opcode = encoding;

   return WriteMemory(cpuid,ipacket,PC,INSTRUCTION,4,uval.ibuf); //<--- writes bytes to memory in order by physical address
}


void X64Simulator::SelectInstruction(string &group,unsigned int &encoding,bool need_branch, bool last_shot) {
   int rand_instr_group = rand() % INSTRUCTION_GROUPS_COUNT;
   unsigned int set_mask = (unsigned int) rand();
   unsigned int mask = 0;

   #pragma omp critical
   {
      if (ForTestEnd()) {
        group    = "System";    // a64
        encoding = WFI_OPCODE;  //  wfi instruction    
        ClearEndTest();         // need to set 'end test' condition for each core 
      } else if (need_branch) {
	// need to pick branch to 'escape' from some bad place...
	X64SIM_UTILS::get_branch_encoding(set_mask,group,encoding,mask);
        branch_away_count++;
      } else if (last_shot) {
	// as a last result pick random 'safe' instruction...
        rand_instr_group = rand() % SAFE_INSTRUCTION_GROUPS_COUNT;
	X64SIM_UTILS::get_next_safe_encoding(rand_instr_group,set_mask,group,encoding,mask);
      } else {
	// usual random pick...
	X64SIM_UTILS::get_next_encoding(rand_instr_group,set_mask,group,encoding,mask);
      }
   }

}

void X64Simulator::TrackInstrGroup(string &group) {
  // keep track of good instr counts for each instruction class...
  // keep track of retries for each instruction class...

  #pragma omp critical
  {
   good_instr_count++;

   if (group_counts.find(group) == group_counts.end()) 
     group_counts[group] = 1;
   else
     group_counts[group] += 1;
	  
   if (group_retry_counts.find(group) == group_retry_counts.end()) 
     group_retry_counts[group] = 1;
   else
     group_retry_counts[group] += 1;

   retries_count++;
  }
}

void X64Simulator::FreeRunTalleys() {
#ifdef SHOW_INSTR_COUNTS
  printf("\n# of instructions stepped: %d, # of retries: %d, # of 'branch aways': %d\n",good_instr_count,retries_count,branch_away_count);

  printf("# of forward branches: %d, # of backwards branches: %d\n",forward_branch_count,backwards_branch_count);

  printf("Step counts for each instruction group:\n");

  for (unordered_map<string,int>::iterator i = group_counts.begin(); i != group_counts.end(); i++) {
     printf("  %s : %d\n",(i->first).c_str(), i->second);
  }

  printf("Retry counts for each instruction group:\n");

  for (unordered_map<string,int>::iterator i = group_retry_counts.begin(); i != group_retry_counts.end(); i++) {
     printf("  %s : %d\n",(i->first).c_str(), i->second);
  }

  printf("Undef opcode counts for each instruction group:\n");

  for (unordered_map<string,int>::iterator i = undef_opcode_counts.begin(); i != undef_opcode_counts.end(); i++) {
     printf("  %s : %d\n",(i->first).c_str(), i->second);
  }
#endif
}
