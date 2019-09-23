#ifdef FOR_MAC_IOS

#import <Foundation/Foundation.h>

extern NSMutableString *RunLogBuffer;
extern NSMutableString *ErrorLogBuffer;
extern NSMutableString *TraceLogBuffer;
extern NSMutableString *DebugLogBuffer;
 
#endif


// Scaffold - same as platform, but more rickety...

#define MAX_CPUS 256
#define PIPELINE_WIDTH 1
#define DEFAULT_CLOCK_ADVANCE 1

class Scaffold {
 public:
 Scaffold();

  Scaffold(const char *sim_init_file,const char *sim_exception_enables_file,
           FILE *runlog=NULL,FILE *errlog=NULL,FILE *tracelog=NULL,FILE *debuglog=NULL,
           unsigned long long sclock=0,unsigned long long clock_advance_interval=DEFAULT_CLOCK_ADVANCE);

  virtual ~Scaffold();

  void SetLogFiles(stringstream *runlog,stringstream *errlog,stringstream *tracelog,stringstream *debuglog);
  void SetLogFiles(FILE *runlog,FILE *errlog,FILE *tracelog,FILE *debuglog);
  void SetSimConfig();
  void SetSimExceptionEnables();
  void InitSimulator();
  void ReserveRegisters(vector<string> &reserved_registers);

  void SetStartPrivilegeLevel(int pl);
  int  StartPrivilegeLevel() { return start_privilege_level; };
  void SetResetAddress(unsigned long long _reset_address);
  unsigned long long ResetAddress() { return reset_address; };
  void SetAddressRange(unsigned long long _address_lo, unsigned long long _address_hi);
  
  void SetSimTraceFile(const string &_simtrace_file);
  string SimTraceFile() { return simtrace_file; };

  void SpecifyMonitorServer(const int port);

  int ReadMemory(int cpu,Packet *packet,unsigned long long address,bool is_data,int number_of_bytes,unsigned char *buffer,bool init_if_free);
  int WriteMemory(int cpu,Packet *packet,unsigned long long address,bool is_data,int number_of_bytes,unsigned char *buffer);
  
  int StepNextInstruction(int cpu,int phase,Packet *packet,string &rcode_decoded);
  int DisassemblyInstruction(int cpu,char *tbuf,Packet *packet);
  int ReadRegister(int cpu,const char *rname,unsigned long long *rval);

  void RunLogEntry(const char *format, ...);
  void ErrorLogEntry(const char *format, ...);
  void TraceLogEntry(const char *format, ...);
  void DebugLogEntry(const char *format, ...);

  virtual void PrintToRunLog(const char *tbuf);
  virtual void PrintToErrorLog(const char *tbuf);
  virtual void PrintToTraceLog(const char *tbuf);
  virtual void PrintToDebugLog(const char *tbuf);

  void FreeRunReset();
  int  FreeRun(int cpu,int number_of_instructions,unsigned int seed,unsigned int do_break,int verbose=0);
  int  FreeRunStep(int i);
  int  FreeRunInit(int _CPUID,int _number_of_instrs,unsigned int _seed,unsigned int _do_break, int _verbose=0);
  void FreeRunEnd(int _CPUID);
  unsigned int Seed() { return seed; };
  
  int Load(string &input_file, unsigned long long load_address = -1);
  int Save(string &output_file, unsigned long long entry_point);

  int Simulate(string &sim_src_file,int cpu,int number_of_instructions,unsigned int do_break,int verbose=0);

  unsigned long long sclock;                   // counter that more or less represents a cpu clock
  unsigned long long clock_advance_interval;   // minimal cpu phase advance interval
                                               // each instruction phase will advance the clock by a multiple of the clock interval

  unsigned long long Clock() { return sclock; };
  unsigned long long ClockAdvanceInterval() { return clock_advance_interval; };
  void advanceClock(unsigned int multiplier) { sclock += clock_advance_interval * multiplier; };
  void syncClock(unsigned long long _sync_clock) { sclock = _sync_clock; };

  unsigned long long reset_address;
  
  int MaxCores() { return MAX_CPUS; };

  bool MapDevice(string device_name, unsigned long long base_address, unsigned long long extent=0xffff);
  
  State cpus[MAX_CPUS];                //<---cores
  Memory memory;                       //<---physical memory + translators + interface
  ExceptionEnables exception_enables;  //<---for the testbed as well as the simulator
  UART_pl011 uart;                     //<---one uart in system. not enabled 'til mapped to physical memory
  SystemCounterModule system_counter;  //<---one system counter. clock value to feed into each core
  
  FILE *RUNLOG;
  FILE *ERRLOG;
  FILE *TRACELOG;
  FILE *DEBUGLOG;

  stringstream *RUNSTREAM;
  stringstream *ERRSTREAM;
  stringstream *TRACESTREAM;
  stringstream *DEBUGSTREAM;

  string simtrace_file;
  SimTrace my_trace;

  int start_privilege_level;   // user may specify (override) starting privilege level

  string sim_monitor_host;
  int    sim_monitor_port;

  A64SimMonitor *sim_monitor;

  // step related parameters:

  int           CPUID;
  unsigned int  seed;
  unsigned int  do_break;
  int           verbose_level;

  int           current_count;
  int           desired_count;
  int           max_retries_count;

  int           rand_instr_group;
  unsigned int  set_mask;

  unsigned char mbuf[1024];

  int           branch_away_count;
  int           good_instr_count;
  int           retries_count;
  int           forward_branch_count;
  int           backwards_branch_count;

  unordered_map<string,int> group_counts;
  unordered_map<string,int> group_retry_counts;
  unordered_map<string,int> undef_opcode_counts;
};

