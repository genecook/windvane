#include "X64Simulator.h"
#include "a64simUserSpace.h"

namespace a64simUserSpace {

class gabbyRunner : public FreeRun {
public:
  gabbyRunner() {};
  ~gabbyRunner() {};
  
  outcome PreStep(State *cpu, Memory *memory, Packet *ipacket, bool first_time, bool last_time) {
    printf("[FreerunStep] first-time? %d last-time? %d\n",first_time,last_time);
    //return FREERUNSTEP;
    return END_TEST;
  }

  void PostStep(const State *cpu, const Memory *memory, const Packet *ipacket, STEP_RESULT step_result) {
    printf("[PostStep] result: %d\n",step_result);
  }

  void MapAddress(const State *cpu, const Packet *packet, Memory *memory, unsigned long long LA, bool is_data,
  			   bool is_privileged, bool is_write, int number_of_bytes) {
    printf("[MapAddress] LA: 0x%llx, type: %s, access: %s, privileged? %d, # of bytes: %d\n",
	   LA, (is_data ? "data" : "instr"), (is_write ? "write" : "read"), is_privileged, number_of_bytes);
  }

};
  
extern "C" void *get_freerun_handle() {
  return (void *) new gabbyRunner;
};

extern "C" void discard_freerun_handle(void *the_handle) {
  delete (gabbyRunner *) the_handle;
};


}
