#ifndef __USER_SPACE__

namespace a64simUserSpace {
  
class FreeRun {
 public:
  FreeRun() {};
  virtual ~FreeRun() {};

  // 'Init' is called after internal cpu/memory setup, but before simulation begins.
  // Provided to allow some minor tweaks of cpu configuration such as input address size.
  // Init has true/false return code, to allow some validation at init time, if desired.
  
  virtual bool Init(State *cpus, int num_cores, std::string cmdline_options) {
    return true;
  };

  enum outcome {
    ABORT_TEST,   // user-space code indicates test can't succeed.
    END_TEST,     // issue end-test sequence, end test
    SUCCESS,      // user-space 'freerun' step succeeded, continue simulation
    FAIL,         //      "         "       "  failed. retry if possible
    STEP,         // user-space 'freerun' made some 'adjustments'; try normal step
    FREERUNSTEP   // user-space 'freerun' made some 'adjustments'; try built-in freerun step
  };

  // 'PreStep' is called when 'freerun' mode has been enabled, and a fetch from an uninitialized
  // memory location occurs. The PreStep method then has the option of ending or aborting the
  // test, or inserting some valid opcode(s) at the address in question...
  
  virtual outcome PreStep(State *cpu,Memory *memory,Packet *ipacket,bool first_time, bool last_time) {
    return FREERUNSTEP;
  };
  
  enum STEP_RESULT {
    NO_SIM_ERROR=0,                      // instruction stepped okay
    TEST_ENDS=1,                         // end-test condition raised
    RANDOM_INSTR_ERR=-1,                 // 'freerun' step failed
    FETCH_FROM_UNINITIALIZED_MEMORY=-2,  // attempt to fetch instruction from uninitialised memory
    SIMULATION_ERROR=-3,                 // unspecified simulation error
    INTERNAL_ERROR=-4                    // probably shouldn't see this one (sigh)
  };

  // 'PostStep' is called after each simulated instruction.
  // NOTE: Since PostStep is called after an instruction has been simulated, the STEP and FREERUNSTEP
  //       outcome return codes do not apply, and are interpreted the same as ABORT_TEST!
  
  virtual outcome PostStep(State *cpu, Memory *memory, Packet *ipacket, STEP_RESULT step_result) {
    return SUCCESS;
  };

  // 'MapAddress' is called when the mmu is enabled, for each logical address to be translated.
  // Returns true if address is valid, can be mapped, and was mapped...
  
  virtual bool MapAddress(State *cpu, Packet *packet, Memory *memory, unsigned long long LA,
		          bool is_data, bool is_privileged, bool is_write, int number_of_bytes) {
    return true;
  };
};


extern "C" void *get_freerun_handle();
extern "C" void discard_freerun_handle(void *the_handle);

};

#endif
#define __USER_SPACE__ 1

