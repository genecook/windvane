#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>

#include "scaffold.pb.h"

class TraceHistory;

class SimTrace {
 public:
  SimTrace();
  ~SimTrace();

  void ToFile(string filePath);
  int  FromFile(string filePath);

  void ToFile();
  void WriteSimTraceSummary();

  void Dump();
  void DumpSummary();

  void RecordCoreCount(int num_cores);

  void RecordCpuInitialState(State *cpu, int cpuid);
  void RecordCpuSlice(State *cpu, Memory *mem, Packet *packet, unsigned long long clock, int _cpuid);

  void RecordUartInitialState(unsigned long long uart_base_pa, int uart_reg_id, unsigned int rval);
  void UpdateUartState(unsigned long long clock, int cpuid, unsigned long long uart_base_pa, int uart_reg_id, unsigned int rval, bool initial_value=false);

  void RecordFinalCounts(int num_instrs);

  void EnableTrace(bool _enable_trace) { trace_enabled = _enable_trace; };
  void SetFilePath(const string &filePath);

  void nextBlockFilePath(string &fp);

  int NeedInitialState();

  int BlockSize() { return 10000; };

  void RecordCpuState(scaffold_SAPI::CpuSlice *my_slice, State *cpu);
  void RecordPacket(scaffold_SAPI::Packet *pkt, State *cpu, Memory *mem, Packet *packet, unsigned long long clock);

  bool MatchingTranslation(scaffold_SAPI::Translation *my_trans,Translation *trans);
  int RecordTranslation(scaffold_SAPI::Cpu *my_core, Translation *trans);

 private:
  unsigned long long TranslationMask(Translation *trans);

  void RecordCpuState(State *cpu);

  void RecordCpuUpdates(State *cpu,int _cpuid);

  void RecordPacket(State *cpu, Memory *mem, Packet *packet, unsigned long long clock);

  void RecordCpuBase(scaffold_SAPI::BaseLevel *base, State *cpu);
  void RecordCpuConfig(scaffold_SAPI::Configuration *my_cfg, State *cpu);
  void RecordCpuProcID(scaffold_SAPI::ProcID *my_ids, State *cpu);
  void RecordCpuFPU(scaffold_SAPI::FPU *my_fpu, State *cpu);
  void RecordCpuDebug(scaffold_SAPI::Debug *my_dbg, State *cpu);
  void RecordCpuExceptionState(scaffold_SAPI::ExceptionState *my_excep, State *cpu);
  void RecordCpuVMSA(scaffold_SAPI::VMSA *my_mmu, State *cpu);
  void RecordCpuResetMgmt(scaffold_SAPI::ResetMgmt *my_reset, State *cpu);
  void RecordCpuThreadState(scaffold_SAPI::ThreadRegs *my_thread, State *cpu);
  void RecordCpuTimerState(scaffold_SAPI::GenericTimer *my_timer, State *cpu);
  void RecordCpuGICState(scaffold_SAPI::GICSystemRegs *my_gic_sregs, State *cpu);

  void RecordCpuBase(scaffold_SAPI::CpuSlice *slice, State *cpu);
  void RecordCpuConfig(scaffold_SAPI::CpuSlice *slice, State *cpu);
  void RecordCpuProcID(scaffold_SAPI::CpuSlice *slice, State *cpu);
  void RecordCpuFPU(scaffold_SAPI::CpuSlice *slice, State *cpu);
  void RecordCpuDebug(scaffold_SAPI::CpuSlice *slice, State *cpu);
  void RecordCpuExceptionState(scaffold_SAPI::CpuSlice *slice, State *cpu);
  void RecordCpuVMSA(scaffold_SAPI::CpuSlice *slice, State *cpu);
  void RecordCpuResetMgmt(scaffold_SAPI::CpuSlice *slice, State *cpu);
  void RecordCpuThreadState(scaffold_SAPI::CpuSlice *slice, State *cpu);
  void RecordCpuTimerState(scaffold_SAPI::CpuSlice *slice, State *cpu);
  void RecordCpuGICState(scaffold_SAPI::CpuSlice *slice, State *cpu);

  void diffCpuBase(State &diffs, State *);
  void diffCpuConfig(State &diffs, State *);
  void diffCpuProcID(State &diffs, State *);
  void diffCpuFPU(State &diffs, State *);
  void diffCpuDebug(State &diffs, State *);
  void diffCpuExceptionState(State &diffs, State *);
  void diffCpuVMSA(State &diffs, State *);
  void diffCpuResetMgmt(State &diffs, State *);
  void diffCpuThreadState(State &diffs, State *);
  void diffCpuTimerState(State &diffs, State *);
  void diffCpuGICState(State &diffs, State *);

  void RecordPacketFetch(scaffold_SAPI::Packet *pkt, Packet *);
  void RecordPacketDecode(scaffold_SAPI::Packet *pkt, Packet *);
  void RecordPacketFetchOperands(scaffold_SAPI::Packet *pkt, State *cpu, Packet *);
  void RecordPacketExecute(scaffold_SAPI::Packet *pkt, Packet *);
  void RecordPacketMemoryAccesses(scaffold_SAPI::Packet *pkt, State *cpu, Memory *mem, Packet *);
  void RecordPacketWriteBack(scaffold_SAPI::Packet *pkt, State *cpu, Packet *);
  void RecordPacketRetire(scaffold_SAPI::Packet *pkt, Packet *);
  void RecordPacketException(scaffold_SAPI::Packet *pkt, Packet *);

  scaffold_SAPI::Scaffold *my_scaffold;

  scaffold_SAPI::Cpu      *my_core;
  scaffold_SAPI::CpuSlice *my_slice;
  scaffold_SAPI::Packet   *pkt;

  void DiffState(State *);

  bool CrackFloat(std::string &decode_str,FloatRegister &src_reg);
  
  int cpuid;

  vector<State> prevCpu;

  bool trace_enabled;

  int slice_count;
  int block_count;
  string block_file_prefix;
  bool enable_block_output;

  bool TraceSummaryEnabled() { return my_trace_history != NULL; };
 
  TraceHistory *my_trace_history;

  unsigned long long current_time;
};


class TrInstr {
 public:
  TrInstr() {};
  TrInstr(int _core, unsigned long long _addr, const string _disasm, int _block) : core(_core),addr(_addr),disasm(_disasm),block(_block) {};

  void Dump();
 
  int                core;    // core this instruction executed on
  unsigned long long addr;    // address of the instruction
  string             disasm;  // the disassembly
  int                block;   // which block this instruction belongs to
};

class TrIter {
 public:
  TrIter() {};
  TrIter(unsigned long long _clock) : clock(_clock) {};

  void Dump();

  void AddInstr(int _core, unsigned long long _addr, const string _disasm, int _block) { instrs.push_back(TrInstr(_core,_addr,_disasm,_block)); };

  unsigned long long clock;

  vector<TrInstr> instrs;  // each entry represents a single core instruction execution (address, disasm) in a simulation block 
};

class SimTraceSummary {
 public:
  SimTraceSummary() {};

  void SetCoreCount(int _num_cores) { num_cores = _num_cores; };
  void AddBlock(const string &_block_filepath) { blocks.push_back(_block_filepath); };
  void AddIter(unsigned long long _clock) { trace.push_back(TrIter(_clock)); };
  void AddInstr(int _core, unsigned long long _addr, const string _disasm,int _block) { trace.back().AddInstr(_core,_addr,_disasm,_block); };
  void RecordFinalCounts(int _num_blocks,int _num_instrs) { num_blocks = _num_blocks; num_instrs = _num_instrs; }; 

  void Dump();

  int ToFile(const string & _summary_file);
  int FromFile(const string & _summary_file);

 private:
  int num_cores;
  int num_blocks;
  int num_instrs;

  vector<string> blocks; // index is block#, value is block filepath
  vector<TrIter> trace;  // each entry represents one (clocked) iteration
};


// to create:
//
//   SimTraceSummary my_trsum(num_cores);
//
//   foreach iter:
//      my_trsum.AddIter(clock); //<---we know what the clock is on each iteration, but ready instructions may span multiple blocks...
//      foreach ready-cpu:
//         step;
//         my_trsum.AddInstr(addr,disasm,block);
//         if (start or block changed):
//            my_trsum.AddBlock(block_filepath) //<---thus each new instr will be added to an existing (recorded) block...
//
//   my_trsum.SetCounts(num_blocks,num_instrs);
//   my_trsum.ToFile(simtrace_summary_file);
//
// to reconstitute:
//
//   SimTraceSummary my_trsum;
//   my_trsum.FromFile(simtrace_summary_file);


class TracePeriod {
 public:
  TracePeriod() {};
  TracePeriod(const string _block_file) : block_file(_block_file) {};
  unsigned long long StartTime() { return start_time; };
  unsigned long long EndTime() { return end_time; };
  string BlockFile() { return block_file; };
  unsigned long long StartTime(unsigned long long _start_time) { start_time = _start_time; return start_time; };
  unsigned long long EndTime(unsigned long long _end_time) { end_time = _end_time; return end_time; };
  string BlockFile(string _block_file) { block_file = _block_file; return block_file; };
 private:
  unsigned long long start_time;
  unsigned long long end_time;
  string block_file;
};

class TraceHistory {
 public:
  TraceHistory() {};
  TraceHistory(int _num_cores) : num_cores(_num_cores) {};

  void SetNumInstrs(int _num_instrs) { num_instrs = _num_instrs; };

  void AddPeriod(const string _block_file) { epochs.push_back(TracePeriod(_block_file)); };

  void SetPeriodStart(unsigned long long _start_time) { epochs.back().StartTime(_start_time); };
  void SetPeriodEnd(unsigned long long _end_time)     { epochs.back().EndTime(_end_time);     };

  void Dump();

  int ToFile(const string & _history_file);
  int FromFile(const string & _history_file);

  void SetCoreCount(int _num_cores)    { num_cores  = _num_cores;  };
  void SetInstrCounts(int _num_instrs) { num_instrs = _num_instrs; };

  int NumCores()   { return num_cores;           };
  int NumPeriods() { return (int) epochs.size(); };
  int NumInstrs()  { return num_instrs;          };

 private:
  int num_cores;
  int num_instrs;

  vector<TracePeriod> epochs;
};

