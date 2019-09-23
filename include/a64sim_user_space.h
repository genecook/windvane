namespace UserSpace {

    enum outcome {
    ABORT_TEST,    // user-space code indicates test can't succeed.
    END_TEST,      // issue end-test sequence, end test
    SUCCESS,       // user-space 'freerun' step succeeded, continue simulation
    FAIL,          //      "         "       "  failed. retry if possible
    STEP,          // user-space 'freerun' made some 'adjustments'; try normal step
    FREERUNSTEP,   // user-space 'freerun' made some 'adjustments'; try built-in freerun step
    CONTINUE       // continue on, either to next plugin, or onward to whatever in simulator
  };

  void Load(std::string dll_file);
  void Unload();

  int  Init(State *cpus, int num_cores, std::string cmdline_options);
  int  FreerunStep(State *cpu,Memory *memory,Packet *ipacket,bool first_time, bool last_time);
  int  PostStep(State *cpu, Memory *memory, Packet *ipacket, int step_result);
  int  MapAddress(State *cpu,Packet *packet,Memory *memory,unsigned long long LA,bool is_data,
		  bool is_privileged,bool is_write,int number_of_bytes);
};
