#ifndef X64SIMULATOR

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

#include "a64sim.h"
#include "a64sim_monitor.h"
#include "SimTrace.h"
#include "a64Scaffold.h"
#include "a64SemiHosting.h"
#include "a64DebugServer.h"

#define CMDLINE_MAX_LEN 4096

struct dll {
  dll(string &_path,string &_options) { path = _path; options = _options; };
  string path;     // path to user-space dynamic library
  string options;  // cmdline options for user-space dynamic library
};
    
class X64Simulator : public Scaffold {
 public:
  X64Simulator() : Scaffold(), num_cores(1),max_instrs_per_core(1000),enable_freerun(false),
    use_threads(false), number_simulated(0), for_end_test(false), semihosting_exit_code(0),
    configure_system_calls(false), semihost_helper(NULL), show_progress(false), debug_port(-1), debug_core_id(0),dbg_server(NULL)
  { 
    //seed = time(NULL); //<---not fine grained enough

    seed = mix(clock(),time(NULL),getpid());
  };

  //~X64Simulator() {};

  void RecordCommandLine(char *_cmdline)       { strcpy(cmdline,_cmdline);              }; 
  void AddSrcFile(const string &elf_obj_file)  { elf_src_files.push_back(elf_obj_file); };
  void SetDestFile(const string &elf_out_file) { elf_dest_file = elf_out_file;          };
  //void SetSimTraceFile(const string &trfile)   { simtrace_file = trfile;                };
  void SetCoreCount(int _num_cores)            { num_cores = _num_cores;                };
  void SetMaxInstrs(unsigned int _max_count)   { max_instrs_per_core = _max_count;      };
  void EnableFreerun()                         { enable_freerun = true;                 };
  void SetSeed(unsigned int _seed)             { seed = _seed;                          };
  int  SetThreadedCoreCount(int _nthreads); 

  void AddUserSpaceDLL(string &dll_file,string &options) {
    struct dll my_dll(dll_file,options);
    userspace_dlls.push_back(my_dll);
  };

  void AddRegisterReservation(string &rname) {
    reserved_registers.push_back(rname);
  };

  void SetEndTestFile(const string &end_test_file) { freerun_end_test_file = end_test_file; };
  bool HaveEndTestFile(string &end_test_file) { if (freerun_end_test_file.size() > 0) { end_test_file = freerun_end_test_file; return true;} else return false; };
  
  void AllowSystemCalls(bool _on_or_off)       { allow_system_calls = _on_or_off; configure_system_calls = true; };
  bool ConfigureSystemCalls(bool &_on_or_off)  { _on_or_off = allow_system_calls; return configure_system_calls; }; 

  unsigned long mix(unsigned long a, unsigned long b, unsigned long c)
  {
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
  }

  int  MaxCores()                              { return MAX_CPUS;                       };
  int  CoreCount()                             { return num_cores;                      };
  int  InstrsPerCore()                         { return max_instrs_per_core;            };
  int  SimulatedCount()                        { return number_simulated;               };
  bool FreerunEnabled()                        { return enable_freerun;                 };

  void SetDebugServerParms(int _debug_port,unsigned int _debug_core_id);
  bool DebugServerEnabled();
  bool DebugPreStepChecks(State *my_cpu, Memory *my_memory, unsigned long long PC, Packet *ipkt);
  bool DebugPostStepChecks(State *my_cpu, Memory *my_memory, unsigned long long PC, Packet *ipkt);
  void ShutdownDebugServer();
  
  void ProcessConfigOverrides();

  int Go(unsigned long long reset_address = 0ull); // go forth and simulate...
  
  int SaveTestImage();

  void TrackInstrGroup(string &group);
  void FreeRunTalleys();

  void ShowOptions();
  int  ValidateOptions();

  int  HaltCore(unsigned int cpuid);
  bool TestEndReached(unsigned char *ibuf);
  bool IllegalOpcode(unsigned int opcode);
  bool SemihostRequest(unsigned char *ibuf);

  void ClearEndTest() { for_end_test = false; };
  void SetEndTest()   { for_end_test = true;  };
  bool ForTestEnd()   { return for_end_test;  };

  void InitSemihostingParms(class semihostParams &_app_sh_parms) { app_sh_parms = _app_sh_parms; app_sh_parms.MarkAsSet(); };

  bool ShowProgress() { return show_progress; };
  void setShowProgress(bool _do_set) { show_progress = _do_set; };

 protected:
  int  LoadSupportCode();
  void RecordInitialState();
  void WriteSimTrace();

  bool Simulate();

  int ReadSimulatorMemory(int cpuid,  Packet *ipacket, unsigned long long simulator_LA, int instr_vs_data, 
                          int num_bytes, unsigned char *dest_buffer, bool init_if_free);

  int WriteSimulatorMemory(int cpuid, Packet *ipacket, unsigned long long simulator_LA, int instr_vs_data, 
			   int num_bytes, unsigned char *src_buffer);

  int HandleSemihostingOperation(int cpuid,Packet *ipacket);

  bool GetReadyCpus(vector<int> &step_cpus,unsigned long long &clock_advance);
  bool GetReadyCpus(vector<int> &step_cpus);
  
  int  SimulateNextInstruction(unsigned int cpuid,int phase,Packet *ipacket,string &rcode_decoded);
  void DisassembleInstruction(unsigned int cpuid,Packet *ipacket,unsigned long long PC);

  int  ReportStepFailed(unsigned int cpuid,Packet *ipacket);
  void StepResultsToLog(unsigned int cpuid,Packet *ipacket);

  bool InstructionMemoryIsFree(int cpuid,unsigned long long PC,Packet *ipacket,int byte_count, unsigned char *tbuf = NULL);

  int  FreerunStep(int cpuid,unsigned long long PC,Packet *ipacket,string &rcode_decoded,bool first_time, bool last_time=false);

  void SelectInstruction(string &group,unsigned int &encoding,bool need_branch, bool last_shot=false);
  int  WriteOpcodeToMemory(int cpuid,unsigned long long PC,Packet *ipacket,unsigned int encoding);

  void SetSimulatedCount(int cnt) { number_simulated = cnt; };

  char *CommandLine() { return cmdline; };
  
  int SemihostExitCode() { return semihosting_exit_code; };
  
 private:
  bool SimulateViaThreads(int &total_num_instrs, int &total_num_iterations);
  bool SimulateViaReadyQueue(int &total_num_instrs, int &total_num_iterations);

  vector<string> elf_src_files;            // list of object files (assembly code, assembled to elf object file) to load
  string         elf_dest_file;            // elf file to create from simulator, and end of simulation
  int            num_cores;                // # of cores to simulate (up to max # of cores scaffold compiled to)
  int            max_instrs_per_core;      // max # of instructions to simulate per core
  bool           enable_freerun;           // allow simulator to 'freerun' when uninitialized instruction memory encountered
  bool           use_threads;              // if true then running on threaded processor. use threaded MP simulate algorithm
  int            number_simulated;         // total # of instructions simulated
  bool           for_end_test;             // set at test end; affects end-test instruction selection

  vector<struct dll> userspace_dlls;       // user-specified shared objects to load

  vector<string> reserved_registers;       // list of application registers to reserve at run-time
  
  string         freerun_end_test_file;    // object file to load at freerun end-of-test address
  
  int            semihosting_exit_code;    // set by semihost SYS_EXIT op 

  bool           configure_system_calls;   // if set, then:
  bool           allow_system_calls;       //   allow or disallow SVC calls.

  char           cmdline[CMDLINE_MAX_LEN]; // command line passed in

  semihostParams app_sh_parms;
  a64SemiHosting *semihost_helper;

  bool           show_progress;            // display disassembly for each instruction as test progresses

  int            debug_port;               // debug server
  unsigned int   debug_core_id;            //   parms

  a64DebugServer *dbg_server;              // debug server instance
};

#define X64SIMULATOR 1
#endif

