#ifndef A64SIM_DEBUG

#include <vector>
#include <map>
#include <string>

#include "scaffold.pb.h"

using namespace std;

//****************************************************************************************************
// A64BreakPoint
//****************************************************************************************************

class A64BreakPoint {
 public:
  A64BreakPoint(const scaffold_SAPI::Breakpoint &_bkpt) { bkpt = _bkpt; }; 

  bool Match(State *st, Packet *pkt, unsigned long long clock, const int cpuid);

 private:
  bool MatchOnASID(Packet *pkt);
  bool MatchOnPC(Packet *pkt);
  bool MatchOnDataAddress(Packet *pkt);
  bool MatchOnPhysicalAddress(Packet *pkt);
  bool MatchOnOpcode(Packet *pkt);
  bool MatchOnRegister(Packet *pkt);
  bool MatchOnException(Packet *pkt);

  scaffold_SAPI::Breakpoint bkpt; // using protocol buffer for convenience (gasp!)
};

//****************************************************************************************************
// DebugSet
//****************************************************************************************************

class DebugSet {
 public: 
 DebugSet() : cpuid(-1),instr_count(-1),step_count(0),instr_phase(-1),report_step_updates(false),report_memory_updates(false) {};
  ~DebugSet() {};

  void Update(scaffold_SAPI::Acknowledge &ack);
  bool Match(State *st, Packet *pkt, unsigned long long clock, const int cpuid);

 private:
  int  cpuid;                 // this cpu
  int  instr_count;           // total number of instructions simulated
  int  step_count;            // running count (down) until next break
  int  instr_phase;           // instruction phase to break on
  bool report_step_updates;   // if false, report step results only when break conditions met
  bool report_memory_updates; //     ",       "   memory             "
  
  vector<A64BreakPoint> bkpts; // active breakpoints
};

//****************************************************************************************************
// DebugManager
//****************************************************************************************************

class DebugManager {
 public:
  DebugManager() {};
  ~DebugManager() {};

  // client specifies debug conditions...
  void UpdateConditions(scaffold_SAPI::Acknowledge &ack);

  // return true if there are breakpoints in place for a given cpu...
  bool HaveCpuBreakConditions(const int cpuid);

  // return true if there are any breakpoints in place for any cpu...
  bool HaveAnyBreakConditions();

  // if match conditions hold then send step info on to client...
  bool Report(State *st, Packet *pkt, unsigned long long clock, const int cpuid);

  // if current debug state allows it send memory access info on to client...
  bool Report(scaffold_SAPI::MemoryAccessDebug &ma);

 private:
  map<int, DebugSet> debug_sets; // debug state indexed by cpu id. always active...
};

#endif

#define A64SIM_DEBUG 1






