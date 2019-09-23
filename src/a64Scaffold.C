#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sstream>
#include <unordered_map>
#include <memory>


//#define FOR_MAC_IOS 1


#ifdef FOR_MAC_IOS
#import "a64Scaffold.h"
#endif

using namespace std;

#include "a64sim.h"
#include "test_a64sim_utils.C"
#include "a64_exceptions.h"

#include "SimTrace.h"
#include "a64Scaffold.h"

#include "a64sim_monitor.h"
#include "ELFIO.h"
//==========================================================================================
// Scaffold class
//==========================================================================================
/*
unsigned int ptree_uint(ptree &pt,const char *ptvar) {
  string my_str = pt.get(ptvar,"");
  char *ptr;
  return strtol(my_str.c_str(),&ptr,0);
}

unsigned long long ptree_ulong(ptree &pt,const char *ptvar) {
  string my_str = pt.get(ptvar,"");
  char *ptr;
  return strtoll(my_str.c_str(),&ptr,0);
}
*/
// override following three methods to direct log entries elsewhere:
void Scaffold::PrintToRunLog(const char *tbuf) {
  if (RUNSTREAM) {
    (*RUNSTREAM) << tbuf;
  } else if (RUNLOG) {
     fprintf(RUNLOG,"%s",tbuf);
  } else {
     // for mac os only: write to external objective C buffer...
#ifdef FOR_MAC_IOS
     [RunLogBuffer appendFormat:@"%s",tbuf];
#endif 
  }
}
void Scaffold::PrintToTraceLog(const char *tbuf) {
  if (TRACESTREAM) {
    (*TRACESTREAM) << tbuf;
  } else if (TRACELOG) {
     fprintf(TRACELOG,"%s",tbuf);
  } else {
#ifdef FOR_MAC_IOS
     // for mac os only: write to external objective C buffer...
    [TraceLogBuffer appendFormat:@"%s",tbuf];
#endif 
  }
}
void Scaffold::PrintToErrorLog(const char *tbuf) {
  if (ERRSTREAM) {
    (*ERRSTREAM) << tbuf;
  } else if (ERRLOG) {
     fprintf(ERRLOG,"%s",tbuf);
  } else {
#ifdef FOR_MAC_IOS
     // for mac os only: write to external objective C buffer...
     [ErrorLogBuffer appendFormat:@"%s",tbuf];
#endif 
  }
}
void Scaffold::PrintToDebugLog(const char *tbuf) {
  if (DEBUGSTREAM) {
    (*DEBUGSTREAM) << tbuf;
  } else if (DEBUGLOG) {
     fprintf(DEBUGLOG,"%s",tbuf);
  } else {
#ifdef FOR_MAC_IOS
     // for mac os only: write to external objective C buffer...
     [DebugLogBuffer appendFormat:@"%s",tbuf];
#endif 
  }
}

// these three methods will use above virtual methods to create log entries...
void Scaffold::RunLogEntry(const char *format, ...) {
  char tbuf[4096];

  va_list args;
  va_start(args,format);
  vsprintf(tbuf,format,args);
  va_end(args);

  PrintToRunLog(tbuf);
}
void Scaffold::TraceLogEntry(const char *format, ...) {
  char tbuf[4096];

  va_list args;
  va_start(args,format);
  vsprintf(tbuf,format,args);
  va_end(args);

  PrintToTraceLog(tbuf);
}
void Scaffold::ErrorLogEntry(const char *format, ...) {
  char tbuf[4096];

  va_list args;
  va_start(args,format);
  vsprintf(tbuf,format,args);
  va_end(args);

  PrintToErrorLog(tbuf);
}
void Scaffold::DebugLogEntry(const char *format, ...) {
  char tbuf[4096];

  va_list args;
  va_start(args,format);
  vsprintf(tbuf,format,args);
  va_end(args);

  PrintToDebugLog(tbuf);
}

void Scaffold::SetLogFiles(stringstream *runlog,stringstream *errlog,stringstream *tracelog,stringstream *debuglog) {
  RUNSTREAM   = runlog;
  ERRSTREAM   = errlog;
  TRACESTREAM = tracelog;
  DEBUGSTREAM = debuglog;

  RUNLOG   = NULL;
  ERRLOG   = NULL;
  TRACELOG = NULL;
  DEBUGLOG = NULL;
}

void Scaffold::SetLogFiles(FILE *runlog,FILE *errlog,FILE *tracelog,FILE *debuglog) {
  RUNLOG   = runlog;
  ERRLOG   = errlog;
  TRACELOG = tracelog;
  DEBUGLOG = debuglog;

  RUNSTREAM   = NULL;
  ERRSTREAM   = NULL;
  TRACESTREAM = NULL;
  DEBUGSTREAM = NULL;
}

void Scaffold::SetSimTraceFile(const string &_simtrace_file) {
  simtrace_file = _simtrace_file;

  my_trace.EnableTrace(!simtrace_file.empty());
}

void Scaffold::SpecifyMonitorServer(const int _port) {
  sim_monitor_port = _port;
  sim_monitor->Connect(sim_monitor_port);
}

void Scaffold::SetSimConfig() {
  //if (StartPrivilegeLevel() >= 0)
  //  printf("[Scaffold::SetSimConfig] starting at EL%d...\n",StartPrivilegeLevel());
  //else
  //  printf("[Scaffold::SetSimConfig] using default privilege level...\n");
  
  for (int i = 0; i < MAX_CPUS; i++) {
     TraceLogEntry("#  CPU: %d\n",i);
     State *my_cpu = &cpus[i];
     
#include "a64sim.ini.C"

     if (StartPrivilegeLevel() == 1) {
       // start at EL1 (QEMU compatibility)...
       my_cpu->Pstate.EL(1);           // current state - EL1,
       my_cpu->SCR_EL3.NS(1);          // non-secure mode,
       my_cpu->ID_AA64PFR0_EL1.EL3(0); // no EL3...
     }
  }
}

void Scaffold::SetSimExceptionEnables() {
  // for now will assume same set of exception enables are applied across all cpus...
#include "a64sim_exceptions.ini.C"
}

void Scaffold::InitSimulator() {
  RunLogEntry("Initializing simulator...\n");

  RunLogEntry("Initializing simulator 'personality'...\n");
  SetSimConfig();
  RunLogEntry("done.\n");

  RunLogEntry("Enabling/disabling testbed/simulator exception...\n");
  SetSimExceptionEnables();
  RunLogEntry("done.\n");

  for (int i = 0; i < MAX_CPUS; i++) {
    // each cpu will maintain its own clock. The scaffold clock is the master clock...
    cpus[i].setClock(Clock(),ClockAdvanceInterval());
    // for now will infer from initial pstate
    switch((int) cpus[i].Pstate.EL()) {
    case 0:  // ERROR: all v8 implementations must implement EL levels 0 and 1
             //   and thus lowest EL boot level should be 1 or greater...
             ErrorLogEntry("ERROR: Initial CPU Pstate.EL level of zero is incorrect.\n");
             exit(-1);
             break;
    case 1:  cpus[i].PC = cpus[i].RVBAR_EL1;
             break;
    case 2:  cpus[i].PC = cpus[i].RVBAR_EL2;
             break;
    case 3:  cpus[i].PC = cpus[i].RVBAR_EL3;
             break;
    default: // ERROR: unknown Pstate EL level...
             ErrorLogEntry("INTERNAL ERROR: Initial CPU Pstate.EL level (0x%x) is incorrect.\n",cpus[i].Pstate.EL());
             exit(-1);
             break;
    }
    TraceLogEntry("#   For cpu %d, starting EL/PC: EL%d/0x%llx\n",i,cpus[i].Pstate.EL(),cpus[i].PC.Value()); 
  } 

  int pa_size = cpus[0].ID_AA64MMFR0_EL1.physical_memory_size_in_bits();

  TraceLogEntry("#   Physical memory size in bits: %d (taken from CPU[0] configuration.\n",pa_size); 

  memory.SetPhysicalSize(pa_size);
  memory.SetMonitor(sim_monitor);
  
  RunLogEntry("done.\n");
}

void Scaffold::ReserveRegisters(vector<string> &reserved_registers) {
  for (int i = 0; i < MAX_CPUS; i++) {  
     for (vector<string>::iterator rname = reserved_registers.begin(); rname != reserved_registers.end(); rname++) {
        try {
            cpus[i].ReserveAppRegister(*rname);
        } catch(const std::runtime_error& ex) {
            // problems reserving register?
            std::cerr << ex.what() << std::endl;
            exit(-1);
	}
     }
  }
}

void Scaffold::SetStartPrivilegeLevel(int pl) {
  start_privilege_level = pl;
  //printf("[Scaffold::SetStartPrivilegeLevel] start_privilege_level set to: %d\n",start_privilege_level);
}

void Scaffold::SetResetAddress(unsigned long long _reset_address) {
  reset_address = _reset_address;
  
  for (int i = 0; i < MAX_CPUS; i++) {
    switch((int) cpus[i].Pstate.EL()) {
    case 0:  // ERROR: all v8 implementations must implement EL levels 0 and 1
             //   and thus lowest EL boot level should be 1 or greater...
             ErrorLogEntry("ERROR: Initial CPU Pstate.EL level of zero is incorrect.\n");
	     fflush(stderr);
             exit(-1);
             break;
    case 1:  cpus[i].RVBAR_EL1.ResetAddress(_reset_address);
             cpus[i].PC = cpus[i].RVBAR_EL1;
             break;
    case 2:  cpus[i].RVBAR_EL2.ResetAddress(_reset_address);
             cpus[i].PC = cpus[i].RVBAR_EL2;
             break;
    case 3:  cpus[i].RVBAR_EL3.ResetAddress(_reset_address);
             cpus[i].PC = cpus[i].RVBAR_EL3;
             break;
    default: // ERROR: unknown Pstate EL level...
             ErrorLogEntry("INTERNAL ERROR: Initial CPU Pstate.EL level (0x%x) is incorrect.\n",cpus[i].Pstate.EL());
	     fflush(stderr);
             exit(-1);
             break;
    }
  }
}

bool Scaffold::MapDevice(string device_name, unsigned long long base_address, unsigned long long extent) {
  if ( (device_name == "UART_PL011") or (device_name == "UART") ) {
    //printf("[Scaffold::MapDevice] UART base-address: 0x%llx, extent: 0x%llx\n",base_address,extent);
    uart.MapDevice(base_address); // instance device, map to requested physical address range
    memory.AddDevice(&uart);      // make memory aware of device
    return true;
  } 

  if ( (device_name == "SYSTEM_COUNTER") or (device_name == "SYS_CNTR") ) {
    //printf("[Scaffold::MapDevice] System Counter Module base-address: 0x%llx, extent: 0x%llx\n",base_address,extent);
    system_counter.MapDevice(base_address); // instance device, map to requested physical address range
    memory.AddDevice(&system_counter);      // make memory aware of device
    return true;
  } 

  return false; 
}

void Scaffold::SetAddressRange(unsigned long long _address_lo, unsigned long long _address_hi) {
  memory.SetPhysicalAddressRange(_address_lo, _address_hi);
}

Scaffold::Scaffold() : sclock(0),clock_advance_interval(DEFAULT_CLOCK_ADVANCE),RUNLOG(NULL),ERRLOG(NULL),TRACELOG(NULL),DEBUGLOG(NULL),
	      RUNSTREAM(NULL),ERRSTREAM(NULL),TRACESTREAM(NULL),DEBUGSTREAM(NULL),verbose_level(0) {
  sim_monitor = (A64SimMonitor *) new a64sim_monitor;
  start_privilege_level = -1;

  //printf("[Scaffold::Scaffold] start_privilege_level: %d\n",start_privilege_level);
 }

Scaffold::Scaffold(const char * /*sim_init_file*/,const char * /*sim_exception_enables_file*/, FILE *runlog,FILE *errlog,
		   FILE *tracelog,FILE *debuglog,unsigned long long _clock,unsigned long long _clock_advance_interval) {
  sim_monitor = (A64SimMonitor *) new a64sim_monitor;
   
  SetLogFiles(runlog,errlog,tracelog,debuglog);

  sclock = _clock;
  clock_advance_interval = _clock_advance_interval;

  start_privilege_level = -1;

  //printf("[Scaffold::Scaffold] start_privilege_level: %d\n",start_privilege_level);
  
  RunLogEntry("Booting simulator...\n");

  InitSimulator();

  RunLogEntry("Simulator boot complete.\n");
}

Scaffold::~Scaffold() {
  RunLogEntry("Powering down simulator...\n");

  sim_monitor->Disconnect();

  delete sim_monitor;
  
  // nothing to do here yet...

  RunLogEntry("done.\n");
}

int Scaffold::Load(string &input_file, unsigned long long load_address) {
  ELFIO elf_helper;
  return elf_helper.Load(memory,input_file,load_address,false);  
}

int Scaffold::Save(string &output_file, unsigned long long entry_point) {
  ELFIO elf_helper;
  return elf_helper.Save(memory, output_file, entry_point, true /* by default, produce 'compressed' ELF output */,false);
}

int Scaffold::ReadMemory(int cpu,Packet *packet,unsigned long long address,bool is_data,int number_of_bytes,unsigned char *buffer,bool init_if_free) {
  Control ctrl(&cpus[cpu],&memory,packet,&exception_enables,sim_monitor);
  bool is_aligned = true; // these methods allow 'platform' access to memory; thus no (architectual) alignment check enforced...
  return memory.ReadMemory(&cpus[cpu],packet,address,is_data,ctrl.Privileged(),number_of_bytes,is_aligned,buffer,init_if_free);
}

int Scaffold::WriteMemory(int cpu,Packet *packet,unsigned long long address,bool is_data,int number_of_bytes,unsigned char *buffer) {
  Control ctrl(&cpus[cpu],&memory,packet,&exception_enables,sim_monitor);
  bool is_aligned = true; // these methods allow 'platform' access to memory; thus no (architectual) alignment check enforced...
  return memory.WriteMemory(&cpus[cpu],packet,address,is_data,ctrl.Privileged(),number_of_bytes,is_aligned,buffer);
}

int Scaffold::StepNextInstruction(int cpu,int phase,Packet *packet,string &rcode_decoded) {
  Control ctrl(&cpus[cpu],&memory,packet,&exception_enables,sim_monitor);
  ctrl.allow_uninitialized_reg_access = true;
  if (packet->ForTest())   // if a 'test' packet then enforce uninitialized operands checks
    ctrl.allow_uninitialized_reg_access = false;

  int rcode = 0;
  
  try {
     if (phase > 0) {
       ctrl.InstrState(phase);
       unsigned int multiplier = 1;
       ctrl.NextState(multiplier);
       cpus[cpu].advanceClock(multiplier); //<---normally Step method advances the cpu clock...
     } else {
       ctrl.Step();
     }
  }
  catch(SIM_EXCEPTION_CLASS etype) {
    if (etype == WAIT_FOR_EVENT)
      throw WAIT_FOR_EVENT;
    if (etype == EVENT_NOTICE)
      throw EVENT_NOTICE;
    if (etype == EVENT_NOTICE_LOCAL)
      throw EVENT_NOTICE_LOCAL;
    rcode = etype;
    rcode_decoded = packet->exceptionClass();
    if (rcode == 0) throw INTERNAL_ERROR; 
  }

  return rcode;
}

int Scaffold::DisassemblyInstruction(int cpu,char *tbuf,Packet *packet) {
  Control ctrl(&cpus[cpu],&memory,packet,&exception_enables,sim_monitor);
  ctrl.Disassemble(tbuf);
  return 0;
}

int Scaffold::ReadRegister(int cpu,const char *rname,unsigned long long *rval) {
  if (!strcmp(rname,"PC")) {
    *rval = cpus[cpu].PC.Value();
    return 0;
  }

  return -1;
}


/*
  freerun at start:
    int CPUID;             //<---which cpu to advance
    int number_of_instrs;  //<---total desired # of instructions
    unsigned int seed;     //<---starting seed
    unsigned int do_break; //<---old way of specifying break
    int verbose_level;     //<---how much verbage to produce

    int step_count;        //<---how many instructions to advance
    int instr_phase;       //<---can set to indicate to stip on particular phase

    int number_retries;    //<---maximum # of retries per instruction

  during generation:
    unsigned long long PC; //<---current PC

    Packet *ipacket;       //<---current packet

  relate during summary:
    int good_instr_count;                          //
    int retries_count;                             //
    int branch_away_count;                         // some stats gathering
    unordered_map<string,int> group_counts;        //
    unordered_map<string,int> group_retry_counts;  //

    int instr_count;       //<---current instr count
    int retry_count;       //<---current retries count
*/

void Scaffold::FreeRunReset() {
  CPUID = 0;
  //seed  = 0;

  srand(seed);

  //printf("[Scaffold::FreeRunReset] seed: %u\n",seed);

  do_break = false;
  verbose_level  = 0;

  current_count = 0;
  desired_count = 1;
  max_retries_count = 200;

  //group    = "";
  //encoding = 0;
  //mask     = 0;

  rand_instr_group = -1;
  set_mask = 0;

  mbuf[0] = '\0';

  branch_away_count      = 0;
  good_instr_count       = 0;
  retries_count          = 0;
  branch_away_count      = 0;
  forward_branch_count   = 0;
  backwards_branch_count = 0;

  group_counts.erase(group_counts.begin(),group_counts.end());
  group_retry_counts.erase(group_retry_counts.begin(),group_retry_counts.end());
}

/*
int Scaffold::FreeRun(ptree &setup) {
  FreeRunReset();

  CPUID         = setup.get("CPUID",0);
  desired_count = setup.get("NUMBER_OF_INSTRUCTIONS",1);
  seed          = setup.get("SEED",0);
  do_break      = false;
  verbose_level = setup.get("VERBOSE",0);

  srand(seed);

  RunLogEntry("\nSimulator 'free run' setup complete.\n");
  return 0;
}
*/

int Scaffold::FreeRunInit(int _CPUID,int _number_of_instrs,unsigned int _seed,unsigned int _do_break, int _verbose_level) {
  FreeRunReset();

  CPUID         = _CPUID;
  desired_count = _number_of_instrs;
  seed          = _seed;
  do_break      = _do_break;
  verbose_level = _verbose_level;

  srand(seed);

  unsigned long long PC = 0;

  char rname[] = "PC";

  if (ReadRegister(CPUID,rname,&PC)) {
    ErrorLogEntry("Oops! Unable to get PC value?...\n");
    return -1;
  }

  TraceLogEntry("# Starting PC: 0x%llx\n",PC);

  RunLogEntry("  seed: %d\n",seed);

  my_trace.RecordCpuInitialState(&cpus[CPUID],CPUID);

  RunLogEntry("\nSimulator 'free run' setup complete.\n");
 
  return 0;
}


int Scaffold::Simulate(string &sim_src_file,int _CPUID,int _number_of_instrs,unsigned int /*do_break*/,int /*verbose*/) {
  RunLogEntry("\nSimulating from an existing test...\n");

  FreeRunReset(); // not doing a freerun, but initialize freerun parms anyway...

  CPUID         = _CPUID;
  desired_count = _number_of_instrs;

  ELFIO elf_helper;

  int rcode = elf_helper.Load(memory,sim_src_file,false);

  if (rcode) {
    RunLogEntry("Simulation aborted due to errors when loading test.\n");
    return rcode;
  }

  unsigned long long PC = 0;

  char rname[] = "PC";

  if (ReadRegister(CPUID,rname,&PC)) {
    ErrorLogEntry("Oops! Unable to get PC value?...\n");
    return -1;
  }

  TraceLogEntry("# Starting PC: 0x%llx\n",PC);

  my_trace.RecordCpuInitialState(&cpus[CPUID],CPUID);

  for (int i = 0; i < _number_of_instrs && rcode==0; i++) {
     if (ReadRegister(CPUID,rname,&PC)) {
       ErrorLogEntry("Oops! Unable to get PC value?...\n");
       return -1;
     }

     unsigned long long current_clock = Clock(); //<---record this value on packet, perhaps packet 'elapsed time' too?

     unique_ptr<Packet> ipacket_holder(new Packet(FOR_SIMULATION));
     Packet *ipacket = ipacket_holder.get();

     string rcode_decoded;

     string instr_group = string("?");
     ipacket->recordInstrGroup(instr_group);

     rcode = StepNextInstruction(CPUID,-1,ipacket,rcode_decoded);

     if (rcode) {
 	ErrorLogEntry("STEP ABORTED - PC: 0x%x, CPU-PC: 0x%x, rcode: %d (%s - %s/%s), instruction count: %d\n",
		      ipacket->PC.Value(),cpus[0].PC.Value(),rcode,rcode_decoded.c_str(),ipacket->exceptionType().c_str(),ipacket->exceptionSubtype().c_str(),i);
        char tbuf[4096];
        try {
              DisassemblyInstruction(CPUID,tbuf,ipacket);
              //ErrorLogEntry(">>>>>0x%8.8llx 0x%8.8x  %s\n",PC,encoding,tbuf);
              string disasm = string(tbuf);
              ipacket->recordDisassembly(disasm);
        }
        catch(...) {
              ErrorLogEntry(">>>>>0x%8.8llx   Disassembly not available\n",PC);
        }
        for (vector<MemoryAccess>::iterator iop = ipacket->mOpsMemory.begin(); iop != ipacket->mOpsMemory.end(); iop++) {
	       ErrorLogEntry(">>>>>0x%8.8llx   data access caused issue???\n",iop->address);
	}

        if (verbose_level >= 1) {
          ostringstream obuf;
          obuf << (*ipacket) << endl;
          string pkt_str = obuf.str();
          PrintToTraceLog(pkt_str.c_str());
	}

        my_trace.RecordCpuSlice(&cpus[CPUID],&memory,ipacket,current_clock,CPUID);
        my_trace.ToFile("cpu.simtrace");

        return -1;
     }

      good_instr_count++;
      ipacket->PC.Value(PC); //<---a bit of a hack: set PC 'back' to value before step, to 
	                     // insure disassembly (in case of a relative branch) is correct...
      char tbuf[1024];
      try {
         DisassemblyInstruction(CPUID,tbuf,ipacket);
         TraceLogEntry("0x%8.8llx  0x%8.8x  %s",PC,ipacket->Opcode,tbuf);
         string disasm = string(tbuf);
         ipacket->recordDisassembly(disasm);
      } 
      catch(...) {
         ErrorLogEntry(">>>>>0x%8.8llx   Disassembly not available on apparently correctly formed instruction?\n",PC);
         TraceLogEntry("0x%8.8llx   ???\n",PC);
      }
      for (vector<MemoryAccess>::iterator iop = ipacket->mOpsMemory.begin(); iop != ipacket->mOpsMemory.end(); iop++) {
         TraceLogEntry("#  0x%8.8llx   data\n",iop->address);
      }

      my_trace.RecordCpuSlice(&cpus[CPUID],&memory,ipacket,current_clock,CPUID);

      syncClock(cpus[CPUID].Clock());
  }

  my_trace.ToFile("cpu.simtrace");

  RunLogEntry("\nDone.\n");

  return rcode;
}


int Scaffold::FreeRun(int CPUID,int number_of_instrs,unsigned int seed,unsigned int do_break, int _verbose_level) {
  RunLogEntry("\nSimulator 'free run' started...\n");

  // if error messages goto stdout then allow user to specify verbage level...

  verbose_level = _verbose_level;

  RunLogEntry("\nSimulator 'free run' started...\n");

  int rcode = FreeRunInit(CPUID,number_of_instrs,seed,do_break,_verbose_level);

  if (rcode)
    return rcode;

  for (int i = 0; i < number_of_instrs && rcode==0; i++) {
     rcode = FreeRunStep(i);
  }

  FreeRunEnd(CPUID);

  return 0;
}

void Scaffold::FreeRunEnd(int _CPUID) {
  my_trace.ToFile("cpu.simtrace");
/*
  if (ipacket) {
     delete cpus[CPUID].packet;
     cpus[CPUID].packet = NULL;
     ipacket = NULL;
  }
*/
  RunLogEntry("\n# of instructions stepped: %d, # of retries: %d, # of 'branch aways': %d\n",good_instr_count,retries_count,branch_away_count);

  RunLogEntry("# of forward branches: %d, # of backwards branches: %d\n",forward_branch_count,backwards_branch_count);

  RunLogEntry("Step counts for each instruction group:\n");
  
  for (unordered_map<string,int>::iterator i = group_counts.begin(); i != group_counts.end(); i++) {
    RunLogEntry("  %s : %d\n",(i->first).c_str(), i->second);
  } 

  RunLogEntry("Retry counts for each instruction group:\n");
  
  for (unordered_map<string,int>::iterator i = group_retry_counts.begin(); i != group_retry_counts.end(); i++) {
    RunLogEntry("  %s : %d\n",(i->first).c_str(), i->second);
  } 

  RunLogEntry("Undef opcode counts for each instruction group:\n");
  
  for (unordered_map<string,int>::iterator i = undef_opcode_counts.begin(); i != undef_opcode_counts.end(); i++) {
    RunLogEntry("  %s : %d\n",(i->first).c_str(), i->second);
  } 
}

int Scaffold::FreeRunStep(int i) {
    int rcode = 0;

    unsigned long long PC = 0;

    char rname[] = "PC";

    if (ReadRegister(CPUID,rname,&PC)) {
      ErrorLogEntry("Oops! Unable to get PC value?...\n");
      return -1;
    }

    // record clock value before instruction executes...

    unsigned long long current_clock = Clock(); //<---record this value on packet, perhaps packet 'elapsed time' too?

    // make N attempts to pick/encode/step a single instruction...

    unique_ptr<Packet> ipacket_holder;
    Packet *ipacket = NULL;

    for (int j = 0; j < max_retries_count; j++) {
         string group = "?";
         unsigned int encoding = 0;
         unsigned int mask = 0;

         union {
            unsigned opcode;
            unsigned char ibuf[4];
         } uval;

	 // discard previous packet here so if error or retries count exceeded,
	 //   the offending packet will still be around...

         ipacket_holder.reset(new Packet(FOR_TEST));
         ipacket = ipacket_holder.get();

	 rand_instr_group = rand() % INSTRUCTION_GROUPS_COUNT;
         set_mask = (unsigned int) rand(); // 0
         unsigned char mbuf[1024];

         if ( (j > 0) || (ReadMemory(CPUID,ipacket,PC,INSTRUCTION,8 /* allow a couple of instructions */,mbuf,0 /* don't init free memory */) == ALL_BYTES_FREE) ) {
	     // get next instruction encoding...
             get_next_encoding(rand_instr_group,set_mask,group,encoding,mask);

             //printf("NEXT ENCODING: group-id: %d, set-mask: 0x%4.4x, group: '%s', encoding: 0x%4.4x, mask: 0x%4.4x\n",
             //       rand_instr_group,set_mask,group.c_str(),encoding,mask);
             // tweak the encoding some to avoid some reserved cases if the 'malformed instruction' exception is disabled...

             if (!exception_enables.Enabled(GENERATION_ERROR,MALFORMED_INSTRUCTION))
                 tweak_encoding(rand_instr_group,encoding);
	 } else {
	     // too close to existing code or data (but not this instruction). request branch encoding... 
	     RunLogEntry("# branch away from existing code at 0x%8.8llx...\n",PC);
	     TraceLogEntry("# branch away from existing code at 0x%8.8llx...\n",PC);
             get_branch_encoding(set_mask,group,encoding,mask);
             branch_away_count++;
	 }

         //printf("seed: %d, PC: 0x%8.8llx, next encoding: 0x%4.4x\n",seed,PC,encoding);

         //printf("NEXT ENCODING: group-id: %d, set-mask: 0x%4.4x, group: '%s', encoding: 0x%4.4x, mask: 0x%4.4x\n",
	 //     rand_instr_group,set_mask,group.c_str(),encoding,mask);
         
         ipacket->recordInstrGroup(group); //<--record intended instruction group

         uval.opcode = encoding;

         rcode = WriteMemory(CPUID,ipacket,PC,INSTRUCTION,4,uval.ibuf); //<--- writes bytes to memory in order by physical address

         if (verbose_level >= 3)
           ErrorLogEntry("Step:\n");
         
         string rcode_decoded;
         rcode = StepNextInstruction(CPUID,-1,ipacket,rcode_decoded);

         if (verbose_level >= 3) {
            ostringstream obuf;
            obuf << (*ipacket) << endl;
            string pkt_str = obuf.str();
            PrintToErrorLog(pkt_str.c_str());
	 }

         if (!rcode) {
	   // make sure next instruction address does NOT itself cause exception. If it does, then back up PC and try again...
           try {
              unsigned char xbuf[1024];
	      ReadMemory(CPUID,ipacket,ipacket->NextPC.Value(),INSTRUCTION,4,xbuf,0);
	   } catch (...) {
	      printf("OOPS! INSTRUCTION EXECUTION RESULTED IN BAD PC 0x%llx!!! FIXED UP PC: 0x%llx\n",cpus[CPUID].PC.Value(),cpus[CPUID].PC.Value(PC));    
              rcode = -1;
	   } 
	 }

         if (!rcode) {
           // instruction successfully stepped...
           if (ipacket->NextPC.Value() != (ipacket->PC.Value() + 4)) {
             // we think we have a branch. see if its forward or backward...
             if (ipacket->NextPC.Value() > ipacket->PC.Value())
	       forward_branch_count++;
             else
	       backwards_branch_count++;
           }
           // keep track of good instr counts for each instruction class...
           if (group_counts.find(group) == group_counts.end()) 
             group_counts[group] = 1;
           else
             group_counts[group] += 1;

	   break;
	 }

         if (verbose_level > 1) {
 	    ErrorLogEntry("STEP ABORTED - PC: 0x%x, CPU-PC: 0x%x, group: %s, encoding: 0x%x, rcode: %d (%s - %s/%s), instruction count: %d, retry count: %d\n",
                          PC,cpus[CPUID].PC.Value(),group.c_str(),encoding,rcode,rcode_decoded.c_str(),ipacket->exceptionType().c_str(),ipacket->exceptionSubtype().c_str(),i,j);
            char tbuf[4096];
            try {
              DisassemblyInstruction(CPUID,tbuf,ipacket);
              ErrorLogEntry(">>>>>0x%8.8llx 0x%8.8x  %s\n",PC,encoding,tbuf);
              string disasm = string(tbuf);
              ipacket->recordDisassembly(disasm);
            }
            catch(...) {
              ErrorLogEntry(">>>>>0x%8.8llx   Disassembly not available\n",PC);
            }
            for (vector<MemoryAccess>::iterator iop = ipacket->mOpsMemory.begin(); iop != ipacket->mOpsMemory.end(); iop++) {
	       ErrorLogEntry(">>>>>0x%8.8llx   data access caused issue???\n",iop->address);
	    }
	 }

         // keep track of retries for each instruction class...

         if (group_retry_counts.find(group) == group_retry_counts.end()) 
           group_retry_counts[group] = 1;
         else
           group_retry_counts[group] += 1;

	 // lastly, lets keep track of undefs that perhaps could be avoided...

         if ( (ipacket->exception_class == ARCH_EXCEPTION) && (ipacket->exception_type == UNDEFINED_INSTRUCTION) && (ipacket->exception_subtype == UNALLOCATED_ENCODING) && (ipacket->State == DECODE_STATE)) {
	   //printf("UNDEF COULD BE AVOIDED!\n");
           if (undef_opcode_counts.find(group) == undef_opcode_counts.end()) 
	     undef_opcode_counts[group] = 1;
           else
	     undef_opcode_counts[group] += 1;
	 }

	 retries_count++;
    }

      if (ipacket == NULL) {
	// OOPS! HOW DID WE END UP WITH NO IPACKET???...
	  ErrorLogEntry("INTERNAL ERROR: NO INSTRUCTION OBJECT AFTER STEPPING?\n");
          return -1;
      }

      // an error occurred...

      if (rcode) {
	  ErrorLogEntry("ERROR: problems stepping? rcode: %d\n",rcode);
          char tbuf[1024];
          try {
            DisassemblyInstruction(CPUID,tbuf,ipacket);
            ErrorLogEntry(">>>>>0x%8.8llx 0x%8.8x  %s\n",PC,ipacket->Opcode,tbuf);
            string disasm = string(tbuf);
            ipacket->recordDisassembly(disasm);
          }
          catch(...) {
            ErrorLogEntry(">>>>>0x%8.8llx   Disassembly not available\n",PC);
          }
          for (vector<MemoryAccess>::iterator i= ipacket->mOpsMemory.begin(); i != ipacket->mOpsMemory.end(); i++) {
	     ErrorLogEntry(">>>>>0x%8.8llx   data access caused issue???",i->address);
	  }
          return rcode;
      }

      // instruction successfully stepped...

      good_instr_count++;
      ipacket->PC.Value(PC); //<---a bit of a hack: set PC 'back' to value before step, to 
	                     // insure disassembly (in case of a relative branch) is correct...

      syncClock(cpus[CPUID].Clock());

      char tbuf[1024];
      try {
         DisassemblyInstruction(CPUID,tbuf,ipacket);
         TraceLogEntry("%12.12llu  0x%8.8llx  0x%8.8x  %s",current_clock,PC,ipacket->Opcode,tbuf);
         string disasm = string(tbuf);
         ipacket->recordDisassembly(disasm);
      } 
      catch(...) {
         ErrorLogEntry(">>>>>0x%8.8llx   Disassembly not available on apparently correctly formed instruction?\n",PC);
         TraceLogEntry("0x%8.8llx   ???\n",PC);
      }
      for (vector<MemoryAccess>::iterator iop = ipacket->mOpsMemory.begin(); iop != ipacket->mOpsMemory.end(); iop++) {
         TraceLogEntry("#  0x%8.8llx   data\n",iop->address);
      }

      if (verbose_level >= 1) {
        ostringstream obuf;
        obuf << (*ipacket) << endl;
        string pkt_str = obuf.str();
        PrintToTraceLog(pkt_str.c_str());
      }

      my_trace.RecordCpuSlice(&cpus[CPUID],&memory,ipacket,current_clock,CPUID);

      return rcode;
}

/*
int Scaffold::CheckPointPacket(int cpu) {
  RunLogEntry("Writing packet checkpoint...");

  ptree pt;

  //State &my_cpu = cpus[cpu];

  ostringstream obuf;
  //obuf << (*my_cpu.packet) << endl;
  string pkt_str = obuf.str();
  PrintToDebugLog(pkt_str.c_str());

  RunLogEntry("done.\n");

  return 0;
}


int Scaffold::CheckPointCPU(int cpu) {
  RunLogEntry("Writing cpu checkpoint...");

  ptree pt;

  // start with State cpus[cpu]...

  //for (int cpu = 0; cpu < cpu_count; cpu++) {
     State &my_cpu = cpus[cpu];

     char cpu_prfx[128];
     sprintf(cpu_prfx,"cpu%d.state.",cpu);

     pt.put((string(cpu_prfx) + string("PSTATE")).c_str(),my_cpu.Pstate.Value());
     pt.put((string(cpu_prfx) + string("PC")).c_str(),my_cpu.PC.Value());

     string regs_prfx = string(cpu_prfx) + string("registers.");

     for (int i = 0; i < 31; i++) {
        char tbuf[128];
        sprintf(tbuf,"General.GP%d",i);
        pt.put((regs_prfx + string(tbuf)).c_str(),my_cpu.GP[i].Value());
     }

     for (int i = 0; i < 32; i++) {
        char tbuf[128];
        sprintf(tbuf,"Float.V%d",i);
        pt.put((regs_prfx + string(tbuf)).c_str(),my_cpu.V[i].Value());
     }
     pt.put((regs_prfx + string("Float.FPCR")).c_str(),my_cpu.FPCR.Value());
     pt.put((regs_prfx + string("Float.FPSR")).c_str(),my_cpu.FPSR.Value());

     pt.put((regs_prfx + string("System.SCR_EL3")).c_str(),my_cpu.SCR_EL3.Value());

     pt.put((regs_prfx + string("System.SPSR_EL1")).c_str(),my_cpu.SPSR_EL1.Value());
     pt.put((regs_prfx + string("System.SPSR_EL2")).c_str(),my_cpu.SPSR_EL2.Value());
     pt.put((regs_prfx + string("System.SPSR_EL3")).c_str(),my_cpu.SPSR_EL3.Value());

     pt.put((regs_prfx + string("System.ID_AA64DFR0_EL1")).c_str(),my_cpu.ID_AA64DFR0_EL1.Value());
     pt.put((regs_prfx + string("System.ID_AA64MMFR0_EL1")).c_str(),my_cpu.ID_AA64MMFR0_EL1.Value());
     pt.put((regs_prfx + string("System.ID_AA64PFR0_EL1")).c_str(),my_cpu.ID_AA64PFR0_EL1.Value());
     pt.put((regs_prfx + string("System.ID_AA64ISAR0_EL1")).c_str(),my_cpu.ID_AA64ISAR0_EL1.Value());

     pt.put((regs_prfx + string("System.CPACR_EL1")).c_str(),my_cpu.CPACR_EL1.Value());
     pt.put((regs_prfx + string("System.CPTR_EL2")).c_str(),my_cpu.CPTR_EL2.Value());
     pt.put((regs_prfx + string("System.CPTR_EL3")).c_str(),my_cpu.CPTR_EL3.Value());

     pt.put((regs_prfx + string("System.MIDR_EL1")).c_str(),my_cpu.MIDR_EL1.Value());
     pt.put((regs_prfx + string("System.VPIDR_EL2")).c_str(),my_cpu.VPIDR_EL2.Value());
     pt.put((regs_prfx + string("System.REVIDR_EL1")).c_str(),my_cpu.REVIDR_EL1.Value());

     pt.put((regs_prfx + string("System.MPIDR_EL1")).c_str(),my_cpu.MPIDR_EL1.Value());
     pt.put((regs_prfx + string("System.VMPIDR_EL2")).c_str(),my_cpu.VMPIDR_EL2.Value());

     pt.put((regs_prfx + string("System.CTR_EL0")).c_str(),my_cpu.CTR_EL0.Value());
     pt.put((regs_prfx + string("System.DCZID_EL0")).c_str(),my_cpu.DCZID_EL0.Value());

     pt.put((regs_prfx + string("System.RVBAR_EL1")).c_str(),my_cpu.RVBAR_EL1.Value());
     pt.put((regs_prfx + string("System.RVBAR_EL2")).c_str(),my_cpu.RVBAR_EL2.Value());
     pt.put((regs_prfx + string("System.RVBAR_EL3")).c_str(),my_cpu.RVBAR_EL3.Value());

     pt.put((regs_prfx + string("System.MDCCSR_EL0")).c_str(),my_cpu.MDCCSR_EL0.Value());
     pt.put((regs_prfx + string("System.DBGDTR_EL0")).c_str(),my_cpu.DBGDTR_EL0.Value());
     pt.put((regs_prfx + string("System.DBGDTRRX_EL0")).c_str(),my_cpu.DBGDTRRX_EL0.Value());
     pt.put((regs_prfx + string("System.DBGDTRTX_EL0")).c_str(),my_cpu.DBGDTRTX_EL0.Value());

     pt.put((regs_prfx + string("System.DLR_EL0")).c_str(),my_cpu.DLR_EL0.Value());
     pt.put((regs_prfx + string("System.DSPSR_EL0")).c_str(),my_cpu.DSPSR_EL0.Value());
     pt.put((regs_prfx + string("System.CONTEXTIDR_EL1")).c_str(),my_cpu.CONTEXTIDR_EL1.Value());

     pt.put((regs_prfx + string("System.PAR_EL1")).c_str(),my_cpu.PAR_EL1.Value());

     pt.put((regs_prfx + string("System.TPIDR_EL0")).c_str(),my_cpu.TPIDR_EL0.Value());
     pt.put((regs_prfx + string("System.TPIDR_EL1")).c_str(),my_cpu.TPIDR_EL1.Value());
     pt.put((regs_prfx + string("System.TPIDR_EL2")).c_str(),my_cpu.TPIDR_EL2.Value());
     pt.put((regs_prfx + string("System.TPIDR_EL3")).c_str(),my_cpu.TPIDR_EL0.Value());

     pt.put((regs_prfx + string("System.ELR_EL1")).c_str(),my_cpu.ELR_EL1.Value());
     pt.put((regs_prfx + string("System.ELR_EL2")).c_str(),my_cpu.ELR_EL2.Value());
     pt.put((regs_prfx + string("System.ELR_EL3")).c_str(),my_cpu.ELR_EL3.Value());

     pt.put((regs_prfx + string("System.ESR_EL1")).c_str(),my_cpu.ESR_EL1.Value());
     pt.put((regs_prfx + string("System.ESR_EL2")).c_str(),my_cpu.ESR_EL2.Value());
     pt.put((regs_prfx + string("System.ESR_EL3")).c_str(),my_cpu.ESR_EL3.Value());

     pt.put((regs_prfx + string("System.FAR_EL1")).c_str(),my_cpu.FAR_EL1.Value());
     pt.put((regs_prfx + string("System.FAR_EL2")).c_str(),my_cpu.FAR_EL2.Value());
     pt.put((regs_prfx + string("System.FAR_EL3")).c_str(),my_cpu.FAR_EL3.Value());

     pt.put((regs_prfx + string("System.VBAR_EL1")).c_str(),my_cpu.VBAR_EL1.Value());
     pt.put((regs_prfx + string("System.VBAR_EL2")).c_str(),my_cpu.VBAR_EL2.Value());
     pt.put((regs_prfx + string("System.VBAR_EL3")).c_str(),my_cpu.VBAR_EL3.Value());

     pt.put((regs_prfx + string("System.TCR_EL1")).c_str(),my_cpu.TCR_EL1.Value());
     pt.put((regs_prfx + string("System.TCR_EL2")).c_str(),my_cpu.TCR_EL2.Value());
     pt.put((regs_prfx + string("System.TCR_EL3")).c_str(),my_cpu.TCR_EL3.Value());

     pt.put((regs_prfx + string("System.MAIR_EL1")).c_str(),my_cpu.MAIR_EL1.Value());
     pt.put((regs_prfx + string("System.MAIR_EL2")).c_str(),my_cpu.MAIR_EL2.Value());
     pt.put((regs_prfx + string("System.MAIR_EL3")).c_str(),my_cpu.MAIR_EL3.Value());

     pt.put((regs_prfx + string("System.RMR_EL1")).c_str(),my_cpu.RMR_EL1.Value());
     pt.put((regs_prfx + string("System.RMR_EL2")).c_str(),my_cpu.RMR_EL2.Value());
     pt.put((regs_prfx + string("System.RMR_EL3")).c_str(),my_cpu.RMR_EL3.Value());

     pt.put((regs_prfx + string("System.AFSR0_EL1")).c_str(),my_cpu.AFSR0_EL1.Value());
     pt.put((regs_prfx + string("System.AFSR0_EL2")).c_str(),my_cpu.AFSR0_EL2.Value());
     pt.put((regs_prfx + string("System.AFSR0_EL3")).c_str(),my_cpu.AFSR0_EL3.Value());

     pt.put((regs_prfx + string("System.AFSR1_EL1")).c_str(),my_cpu.AFSR1_EL1.Value());
     pt.put((regs_prfx + string("System.AFSR1_EL2")).c_str(),my_cpu.AFSR1_EL2.Value());
     pt.put((regs_prfx + string("System.AFSR1_EL3")).c_str(),my_cpu.AFSR1_EL3.Value());

     pt.put((regs_prfx + string("System.SP_EL0")).c_str(),my_cpu.SP_EL0.Value());
     pt.put((regs_prfx + string("System.SP_EL1")).c_str(),my_cpu.SP_EL1.Value());
     pt.put((regs_prfx + string("System.SP_EL2")).c_str(),my_cpu.SP_EL2.Value());
     pt.put((regs_prfx + string("System.SP_EL3")).c_str(),my_cpu.SP_EL3.Value());

     pt.put((regs_prfx + string("System.SCTLR_EL1")).c_str(),my_cpu.SCTLR_EL1.Value());
     pt.put((regs_prfx + string("System.SCTLR_EL2")).c_str(),my_cpu.SCTLR_EL2.Value());
     pt.put((regs_prfx + string("System.SCTLR_EL3")).c_str(),my_cpu.SCTLR_EL3.Value());

     pt.put((regs_prfx + string("System.TTBR0_EL1")).c_str(),my_cpu.TTBR0_EL1.Value());
     pt.put((regs_prfx + string("System.TTBR0_EL2")).c_str(),my_cpu.TTBR0_EL2.Value());
     pt.put((regs_prfx + string("System.TTBR0_EL3")).c_str(),my_cpu.TTBR0_EL3.Value());

     // then packet...

     //char packet_prfx[128];
     //sprintf(packet_prfx,"cpu%d.packet.",cpu);

     //my_cpu.packet->DebugCheckPoint(pt, string(packet_prfx));
     //}

  // finally affected memory blocks...

  // now format xml, then stream to debug file...

  ostringstream obuf;
  write_xml(obuf,pt);

  string xml_str = obuf.str();

  PrintToDebugLog(xml_str.c_str());

  //DebugLogEntry("%s",xml_str.c_str());

  RunLogEntry("done.\n");

  return 0;
}
*/

