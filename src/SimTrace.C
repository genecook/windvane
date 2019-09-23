#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <math.h>

#include "scaffold.pb.h"

using namespace std;

#include "a64sim.h"
#include "SimTrace.h"

//#define DEBUG_TRANSLATIONS 1

//=============================================================================================================
// public interface...
//=============================================================================================================

SimTrace::SimTrace() : my_scaffold(NULL), my_core(NULL), my_slice(NULL), pkt(NULL), cpuid(0), trace_enabled(false), 
                       slice_count(0), block_count(0), enable_block_output(false), my_trace_history(NULL) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
}

SimTrace::~SimTrace() {
  //google::protobuf::ShutdownProtobufLibrary();

  if (my_trace_history) 
    delete my_trace_history;
}

void SimTrace::SetFilePath(const string &filePath) {
   block_file_prefix   = filePath;
   enable_block_output = true;
   trace_enabled       = true;

   my_trace_history = new TraceHistory;
   string fp;
   nextBlockFilePath(fp);
   my_trace_history->AddPeriod(fp);

   current_time = 0;
   my_trace_history->SetPeriodStart(current_time);
}

void SimTrace::ToFile(string filePath) {
  if (!trace_enabled)
    return;

  fstream output(filePath, ios::out | ios::trunc | ios::binary);

  if (!output) {
      cerr << "Error: failed to open sim-trace file '" << filePath << "'" << endl;
  } else if (!my_scaffold->SerializeToOstream(&output)) {
      cerr << "Error: failed to write cpu contents to sim-trace file." << endl;
  } else {
      cout << "  Sim-trace file " << filePath << " created." << endl;
  }
}

void SimTrace::nextBlockFilePath(string &fp) {
    char tbuf[1024];
    sprintf(tbuf,"%s.%d",block_file_prefix.c_str(),block_count);
    fp = tbuf;
}

void SimTrace::ToFile() {
  if (!trace_enabled)
    return;

  string block_filePath;
  nextBlockFilePath(block_filePath);

  fstream output(block_filePath, ios::out | ios::trunc | ios::binary);

  if (!output) {
      cerr << "Error: failed to open sim-trace file '" << block_filePath << "'" << endl;
  } else if (!my_scaffold->SerializeToOstream(&output)) {
      cerr << "Error: failed to write cpu contents to sim-trace file." << endl;
  } else {
      cout << "."; 
      fflush(stdout);
  }
}

int SimTrace::NeedInitialState() { 
   return slice_count==0; 
}

int SimTrace::FromFile(string filePath) {
  if (!trace_enabled)
    return -1;

  int rcode = -1;

   fstream input(filePath,ios::in | ios::binary);

   if (!input) {
       cerr << "[SimTrace::FromFile] failed to open sim-trace file '" << filePath << "'" << endl;
   } else if (!my_scaffold->ParseFromIstream(&input)) {
       cerr << "[SimTrace::FromFile] failed to parse sim-trace!" << endl;
   } else {
     cout << "  Sim-trace file " << filePath << " parsed successfully" << endl;
     rcode = 0;
   }

  return rcode;
}

void SimTrace::Dump() {
   if (trace_enabled) {
     cout << "SimTrace: " << my_scaffold->DebugString() << endl;
   }
}

void SimTrace::RecordCpuInitialState(State *cpu, int _cpuid) {
   if (trace_enabled) {
     //printf("[SimTrace::RecordCpuInitialState] block: %d cpu: %d\n",block_count,_cpuid);
     if (my_scaffold == NULL) {
       my_scaffold = new scaffold_SAPI::Scaffold;
     }
     my_core  = my_scaffold->add_core();
     my_slice = my_core->mutable_initial_state();
     
     RecordCpuUpdates(cpu, _cpuid);
   }
}

void SimTrace::RecordUartInitialState(unsigned long long uart_base_pa, int uart_reg_id, unsigned int rval) {
  UpdateUartState(0,-1,uart_base_pa,uart_reg_id,rval,true);
}

void SimTrace::UpdateUartState(unsigned long long clock, int cpuid, unsigned long long uart_base_pa, int uart_reg_id, unsigned int rval, bool initial_value) {
   if (trace_enabled) {
     // look up uart by physical address; add if not found...
     
     scaffold_SAPI::UART *my_uart = NULL;
         
     for (int i = 0; i < my_scaffold->uart_size() && (my_uart == NULL); i++) {
        scaffold_SAPI::UART *next_uart = my_scaffold->mutable_uart(i);
        if (next_uart->pa_base() == uart_base_pa) 
	  my_uart = next_uart;
     }
     
     if (my_uart == NULL) {
       my_uart = my_scaffold->add_uart();
       my_uart->set_pa_base(uart_base_pa);
     }

     // this update is either for establishing initial state, or as a result of a cpu (memory mapped) write to a uart register...

     scaffold_SAPI::UartSlice *my_slice = NULL;

     if (my_uart->updates_size() == 0) {
       my_slice = my_uart->add_updates();      // no previous state, so add one...
     } else if (initial_value) {
       my_slice = my_uart->mutable_updates(0); // have previous state, state[0] hold initial state...
     } else {
       my_slice = my_uart->add_updates();      // add a new state (update)...
     }

     my_slice->set_clock(clock);         // set clock, cpu id always,
     my_slice->set_core_id(cpuid);       //  even though on initial state is meaningless

     // each uart access (other than for the initial state) consists of a single uart register update...

     // will ASSUME: uart register updates are infrequent enough that we need not worry about "diff'ing" the
     // new value against the existing value...

     scaffold_SAPI::UART_PL011 *my_state = my_slice->mutable_state();

     switch(uart_reg_id) {
       case UART_pl011::DR:     my_state->set_uartdr(rval);        break;
       case UART_pl011::RSR:    my_state->set_uartrsr(rval);       break;
       case UART_pl011::FR:     my_state->set_uartfr(rval);        break;
       case UART_pl011::ILPR:   my_state->set_uartilpr(rval);      break;
       case UART_pl011::IBRD:   my_state->set_uartibrd(rval);      break;
       case UART_pl011::FBRD:   my_state->set_uartfbrd(rval);      break;
       case UART_pl011::LCR_H:  my_state->set_uartlcr_h(rval);     break;
       case UART_pl011::TCR:    my_state->set_uarttcr(rval);       break;
       case UART_pl011::IFLS:   my_state->set_uartifls(rval);      break;
       case UART_pl011::IMSC:   my_state->set_uartimsc(rval);      break;
       case UART_pl011::TRIS:   my_state->set_uartris(rval);       break;
       case UART_pl011::TMIS:   my_state->set_uartmis(rval);       break;
       case UART_pl011::TDMACR: my_state->set_uartdmacr(rval);     break;
       case UART_pl011::PID0:   my_state->set_uartperiphid0(rval); break;
       case UART_pl011::PID1:   my_state->set_uartperiphid1(rval); break;
       case UART_pl011::PID2:   my_state->set_uartperiphid2(rval); break;
       case UART_pl011::PID3:   my_state->set_uartperiphid3(rval); break;
       case UART_pl011::CID0:   my_state->set_uartcellid0(rval);   break;
       case UART_pl011::CID1:   my_state->set_uartcellid1(rval);   break;
       case UART_pl011::CID2:   my_state->set_uartcellid2(rval);   break;
       case UART_pl011::CID3:   my_state->set_uartcellid3(rval);   break;

       default: break;
     }
   }
}

void SimTrace::RecordCpuSlice(State *cpu, Memory *mem, Packet *packet, unsigned long long clock, int _cpuid) {
   if (trace_enabled) {
    //printf("[SimTrace::RecordCpuSlice] cpu: %d\n",_cpuid);

    cpuid = _cpuid;

    my_core  = my_scaffold->mutable_core(cpuid);

    my_slice = my_core->add_slice();
    pkt      = my_slice->mutable_trace();

    RecordCpuUpdates(cpu,_cpuid);
    RecordPacket(cpu,mem,packet,clock);

    slice_count++;

    current_time = clock;

    if (TraceSummaryEnabled()) {
       my_trace_history->SetPeriodEnd(current_time);
    }

    if (slice_count > BlockSize()) {
      //printf("Dumping next block...\n");
      ToFile();

      block_count++;
      delete my_scaffold;
      my_scaffold = NULL;
      slice_count = 0;
      prevCpu.erase(prevCpu.begin(),prevCpu.end());

      if (TraceSummaryEnabled()) {
        string fp;
        nextBlockFilePath(fp);
        my_trace_history->AddPeriod(fp);
        my_trace_history->SetPeriodStart(current_time);
      }
    }
   }
}

// methods for creating simulation trace summary...
// ----------------------------------------------------------------------

void SimTrace::RecordCoreCount(int num_cores) {
   if (TraceSummaryEnabled()) { 
       my_trace_history->SetCoreCount(num_cores);
   }
}

void SimTrace::RecordFinalCounts(int num_instrs) {
   if (TraceSummaryEnabled()) { 
      my_trace_history->SetInstrCounts(num_instrs);
   }
}

void SimTrace::WriteSimTraceSummary() {
   if (TraceSummaryEnabled()) { 
      string trace_top_file = block_file_prefix + ".top";
      my_trace_history->ToFile(trace_top_file);
   }
}

void SimTrace::DumpSummary() {
   if (TraceSummaryEnabled()) { 
      my_trace_history->Dump();
   }
}

void SimTraceSummary::Dump() {
   printf("Simulation Trace summary:\n");
   printf("    #cores:      %d\n",num_cores);
   printf("    #blocks:     %d\n",num_blocks);
   printf("    #instrs:     %d\n",num_instrs);
   printf("    #iterations: %d\n",(int) trace.size());
   printf("    block files:\n");

   for (int i = 0; i < (int) blocks.size(); i++) {
     printf("      %d --> '%s'\n",i,(blocks[i]).c_str());
   }
   printf("    instr trace:\n");
   for (int i = 0; i < (int) trace.size(); i++) {
     trace[i].Dump();
   }
}

int SimTraceSummary::ToFile(const string &summary_file) { 
  int rcode = -1;

   //printf("[SimTraceSummary::ToFile] --> %s\n",summary_file.c_str());

   scaffold_SAPI::TraceSummary trsum;

   trsum.set_num_cores(num_cores);
   trsum.set_num_blocks(num_blocks);
   trsum.set_num_instrs(num_instrs);

   for (int i = 0; i < (int) blocks.size(); i++) {
     trsum.add_block_files(blocks[i]);
   }

   for (int i = 0; i < (int) trace.size(); i++) {
     scaffold_SAPI::TraceIter *ti = trsum.add_trace();
     ti->set_clock(trace[i].clock);
     for (int j = 0; j < (int) trace[i].instrs.size(); j++) {
       scaffold_SAPI::TraceInstr *tinstr = ti->add_instrs();
       tinstr->set_core(trace[i].instrs[j].core);
       tinstr->set_addr(trace[i].instrs[j].addr);
       tinstr->set_block(trace[i].instrs[j].block);
       tinstr->set_disasm(trace[i].instrs[j].disasm);
     }    
   }

   fstream output(summary_file, ios::out | ios::trunc | ios::binary);

   if (!output) {
     cerr << "Error: failed to open sim-trace summary file '" << summary_file << "'" << endl;
   } else if (!trsum.SerializeToOstream(&output)) {
     cerr << "Error: failed to write cpu contents to sim-trace summary file." << endl; 
   } else {
     cout << "  Sim-trace summary file " << summary_file << " created." << endl;
     rcode = 0;
   }

  return rcode; 
}

int SimTraceSummary::FromFile(const string &summary_file) { 
  printf("[SimTraceSummary::FromFile] <-- %s\n",summary_file.c_str());
  return -1; 
}

void TrInstr::Dump() {
   printf("      %d/%d 0x%8.8llx %s",block,core,addr,disasm.c_str());  
}

void TrIter::Dump() {
   printf("       0x%llx\n",clock);
   for (int i = 0; i < (int) instrs.size(); i++) {
     instrs[i].Dump();
   }
}


// methods for creating simulation timeline...
// ----------------------------------------------------------------------

void TraceHistory::Dump() {
   printf("Simulation History:\n");
   printf("    #cores:      %d\n",NumCores());
   printf("    #perionds:   %d\n",NumPeriods());
   printf("    #instrs:     %d\n",NumInstrs());
   printf("    Epochs:\n");
   for (int i = 0; i < (int) epochs.size(); i++) {
     printf("       0x%llx --> 0x%llx : %s\n",epochs[i].StartTime(),epochs[i].EndTime(),epochs[i].BlockFile().c_str());
   }
}

int TraceHistory::ToFile(const string & history_file) {
  int rcode = -1;

   //printf("[TraceHistory::ToFile] --> %s\n",history_file.c_str());

   scaffold_SAPI::TraceHistory history;

   history.set_num_cores(NumCores());
   history.set_num_blocks(NumPeriods());
   history.set_num_instrs(NumInstrs());

   for (int i = 0; i < (int) epochs.size(); i++) {
     scaffold_SAPI::Period *epoch = history.add_epochs();
     epoch->set_start_time(epochs[i].StartTime());
     epoch->set_end_time(epochs[i].EndTime());
     epoch->set_block_file(epochs[i].BlockFile());
   }
  
   fstream output(history_file, ios::out | ios::trunc | ios::binary);

   if (!output) {
     cerr << "Error: failed to open sim-trace history file '" << history_file << "'" << endl;
   } else if (!history.SerializeToOstream(&output)) {
     cerr << "Error: failed to write cpu contents to sim-trace history file." << endl;
   } else {
     cout << "  Sim-trace history file " << history_file << " created." << endl;
     rcode = 0;
   }

  return rcode;
}

int TraceHistory::FromFile(const string & _history_file) {
   printf("[TraceHistory::FromFile] <-- %s\n",_history_file.c_str());
  return -1; 
}

//=============================================================================================================
// private methods...
//=============================================================================================================

void SimTrace::RecordCpuBase(scaffold_SAPI::BaseLevel *my_base, State *cpu) {
  if (cpu->SCR_EL3.IsSet()) my_base->set_scr_el3(cpu->SCR_EL3.Value());
  if (cpu->SP_EL0.IsSet())  my_base->set_sp_el0(cpu->SP_EL0.Value());
  if (cpu->SP_EL1.IsSet())  my_base->set_sp_el1(cpu->SP_EL1.Value());
  if (cpu->SP_EL2.IsSet())  my_base->set_sp_el2(cpu->SP_EL2.Value());
  if (cpu->SP_EL3.IsSet())  my_base->set_sp_el3(cpu->SP_EL3.Value());

  for (int i = 0; i < 31; i++) {
    if (cpu->GP[i].IsSet()) {
      scaffold_SAPI::GPRegister* reg = my_base->add_gp();
      reg->set_key(i);
      reg->set_val(cpu->GP[i].Value());
    }
  }
}

void SimTrace::RecordCpuBase(scaffold_SAPI::CpuSlice *slice, State *cpu) {
  scaffold_SAPI::BaseLevel *my_base = slice->mutable_base();
  RecordCpuBase(my_base,cpu);
}

#define SDIFF(X) if (cpu->X.IsSet() && ( !prevCpu[cpuid].X.IsSet() || (cpu->X.Value() != prevCpu[cpuid].X.Value()) ) ) diffs.X = cpu->X

void SimTrace::diffCpuBase(State &diffs, State *cpu) {
  SDIFF(PC);
  SDIFF(Pstate);
  SDIFF(SCR_EL3);
  SDIFF(SP_EL0);
  SDIFF(SP_EL1);
  SDIFF(SP_EL2);
  SDIFF(SP_EL3);

  for (int i = 0; i < 31; i++) {
     SDIFF(GP[i]);
  }
}

void SimTrace::RecordCpuConfig(scaffold_SAPI::Configuration *my_cfg,State *cpu) {
  if (cpu->ID_AA64DFR0_EL1.IsSet()) my_cfg->set_id_aa64dfr0_el1(cpu->ID_AA64DFR0_EL1.Value());
  if (cpu->ID_AA64MMFR0_EL1.IsSet()) my_cfg->set_id_aa64mmfr0_el1(cpu->ID_AA64MMFR0_EL1.Value());
  if (cpu->ID_AA64PFR0_EL1.IsSet()) my_cfg->set_id_aa64pfr0_el1(cpu->ID_AA64PFR0_EL1.Value());
  if (cpu->ID_AA64ISAR0_EL1.IsSet()) my_cfg->set_id_aa64isar0_el1(cpu->ID_AA64ISAR0_EL1.Value());

  if (cpu->MIDR_EL1.IsSet()) my_cfg->set_midr_el1(cpu->MIDR_EL1.Value());
  if (cpu->VPIDR_EL2.IsSet()) my_cfg->set_vpidr_el2(cpu->VPIDR_EL2.Value());
  if (cpu->CTR_EL0.IsSet()) my_cfg->set_ctr_el0(cpu->CTR_EL0.Value());
  if (cpu->DCZID_EL0.IsSet()) my_cfg->set_dczid_el0(cpu->DCZID_EL0.Value());

  if (cpu->RVBAR_EL1.IsSet()) my_cfg->set_rvbar_el1(cpu->RVBAR_EL1.Value());
  if (cpu->RVBAR_EL2.IsSet()) my_cfg->set_rvbar_el2(cpu->RVBAR_EL2.Value());
  if (cpu->RVBAR_EL3.IsSet()) my_cfg->set_rvbar_el3(cpu->RVBAR_EL3.Value());

  if (cpu->AFSR0_EL1.IsSet()) my_cfg->set_afsr0_el1(cpu->AFSR0_EL1.Value());
  if (cpu->AFSR0_EL2.IsSet()) my_cfg->set_afsr0_el2(cpu->AFSR0_EL2.Value());
  if (cpu->AFSR0_EL3.IsSet()) my_cfg->set_afsr0_el3(cpu->AFSR0_EL3.Value());

  if (cpu->AFSR1_EL1.IsSet()) my_cfg->set_afsr1_el1(cpu->AFSR1_EL1.Value());
  if (cpu->AFSR1_EL2.IsSet()) my_cfg->set_afsr1_el2(cpu->AFSR1_EL2.Value());
  if (cpu->AFSR1_EL3.IsSet()) my_cfg->set_afsr1_el3(cpu->AFSR1_EL3.Value());
}

void SimTrace::RecordCpuConfig(scaffold_SAPI::CpuSlice *slice, State *cpu) {
  scaffold_SAPI::Configuration *my_cfg = slice->mutable_cfg();
  RecordCpuConfig(my_cfg,cpu);
}

void SimTrace::diffCpuConfig(State &diffs, State *cpu) {
  SDIFF(ID_AA64DFR0_EL1);
  SDIFF(ID_AA64MMFR0_EL1);
  SDIFF(ID_AA64PFR0_EL1);
  SDIFF(ID_AA64ISAR0_EL1);

  SDIFF(MIDR_EL1);
  SDIFF(VPIDR_EL2);
  SDIFF(CTR_EL0);
  SDIFF(DCZID_EL0);

  SDIFF(RVBAR_EL1);
  SDIFF(RVBAR_EL2);
  SDIFF(RVBAR_EL3);

  SDIFF(AFSR0_EL1);
  SDIFF(AFSR0_EL2);
  SDIFF(AFSR0_EL3);

  SDIFF(AFSR1_EL1);
  SDIFF(AFSR1_EL2);
  SDIFF(AFSR1_EL3);
} 

void SimTrace::RecordCpuProcID(scaffold_SAPI::ProcID *my_ids,State *cpu) {
  if (cpu->MPIDR_EL1.IsSet()) my_ids->set_mpidr_el1(cpu->MPIDR_EL1.Value());
  if (cpu->VMPIDR_EL2.IsSet()) my_ids->set_vmpidr_el2(cpu->VMPIDR_EL2.Value());
  if (cpu->REVIDR_EL1.IsSet()) my_ids->set_revidr_el1(cpu->REVIDR_EL1.Value());
}

void SimTrace::RecordCpuProcID(scaffold_SAPI::CpuSlice *slice, State *cpu) {
  scaffold_SAPI::ProcID *my_ids = slice->mutable_ids();
  RecordCpuProcID(my_ids,cpu);
}

void SimTrace::diffCpuProcID(State &diffs, State *cpu) {
  SDIFF(MPIDR_EL1);
  SDIFF(VMPIDR_EL2);
  SDIFF(REVIDR_EL1);
}

bool SimTrace::CrackFloat(std::string &decode_str,FloatRegister &src_reg) {
  bool format_supported = false;

  char tbuf[1024];
  
  switch(src_reg.Type()) {
    case FL_SINGLE:
    case FL_DOUBLE:
      {
	bool IS_DOUBLE = src_reg.Type() == FL_DOUBLE;
	
       unsigned long long uval = src_reg.Value();
       
       unsigned long long sign     = IS_DOUBLE ? (uval >> 63) : (uval >> 31);
       unsigned long long exponent = IS_DOUBLE ? ((uval >> 52) & 0x7ff) : ((uval >> 23) & 0xff);
       unsigned long long fraction = IS_DOUBLE ? (uval & 0xfffffffffffffull) : (uval & 0x7fffff);

       bool is_positive        = sign == 1;
       bool is_signaling       = IS_DOUBLE ? (((uval >> 51) & 1) == 1) : ( ((uval >> 22) & 1) == 1);
       
       bool is_normalized      = (exponent > 0) && (IS_DOUBLE ? (exponent < 0x7ff) : (exponent < 0xff));
       bool is_zero            = (exponent == 0) && (fraction == 0);
       bool is_denormalized    = (exponent == 0) && (fraction != 0);
       bool is_infinity        = (IS_DOUBLE ? (exponent == 0x7ff) : (exponent == 0xff)) && (fraction == 0);
       bool is_nan             = (IS_DOUBLE ? (exponent == 0x7ff) : (exponent == 0xff)) && (fraction != 0);

       if (is_normalized) {
	 if (src_reg.Type() == FL_DOUBLE)
	   sprintf(tbuf,"%g",src_reg.Double());
	 else
	   sprintf(tbuf,"%g",src_reg.Single());
       } else if (is_zero)
	 strcpy(tbuf, is_positive ? "+Zero" : "-Zero");
       else if (is_denormalized)
         strcpy(tbuf, "Subnormal");
       else if (is_infinity)
         strcpy(tbuf, is_positive ? "+Infinity" : "-Infinity");
       else if (is_nan)
	 strcpy(tbuf, is_signaling ? "SNaN" : "QNaN");
       else {
	 // what???...
         throw INTERNAL_ERROR; 
       }
       
       decode_str = tbuf;
       format_supported = true;
      }
      break;
      
    default: break;
  }
  
  return format_supported;
}

void SimTrace::RecordCpuFPU(scaffold_SAPI::FPU *my_fpu,State *cpu) {
  if (cpu->CPACR_EL1.IsSet()) my_fpu->set_cpacr_el1(cpu->CPACR_EL1.Value());
  if (cpu->CPTR_EL2.IsSet()) my_fpu->set_cptr_el2(cpu->CPTR_EL2.Value());
  if (cpu->CPTR_EL3.IsSet()) my_fpu->set_cptr_el3(cpu->CPTR_EL3.Value());

  if (cpu->FPCR.IsSet()) my_fpu->set_fpcr(cpu->FPCR.Value());
  if (cpu->FPSR.IsSet()) my_fpu->set_fpsr(cpu->FPSR.Value());

  for (int i = 0; i < 32; i++) {
     if (cpu->V[i].IsSet()) {
       scaffold_SAPI::SimdReg* v = my_fpu->add_v();
       v->set_key( i );
       v->set_rval_hi( cpu->V[i].ValueHi() );
       v->set_rval_lo( cpu->V[i].Value()   );
       std::string decode_str;
       if (CrackFloat(decode_str,cpu->V[i])) {
	 v->set_rval_lo_decoded( decode_str );
       }
     }
  }
}

void SimTrace::RecordCpuFPU(scaffold_SAPI::CpuSlice *slice, State *cpu) {
  scaffold_SAPI::FPU *my_fpu = slice->mutable_fpu();
  RecordCpuFPU(my_fpu,cpu);
}

void SimTrace::diffCpuFPU(State &diffs, State *cpu) {
  SDIFF(CPACR_EL1);
  SDIFF(CPTR_EL2);
  SDIFF(CPTR_EL3);
  SDIFF(FPCR);
  SDIFF(FPSR);

  for (int i = 0; i < 32; i++) {
     if (cpu->V[i].IsSet()) {
       if (!prevCpu[cpuid].V[i].IsSet() ||
	   (prevCpu[cpuid].V[i].Value() != cpu->V[i].Value()) ||
	   (prevCpu[cpuid].V[i].ValueHi() != cpu->V[i].ValueHi())) {
	 diffs.V[i].Value(cpu->V[i].Value());                //
         diffs.V[i].ValueHi(cpu->V[i].ValueHi());            // should use copy constructor
	 diffs.V[i].SetType((float_type) cpu->V[i].Type());  //
       } 
     }
  }
}

void SimTrace::RecordCpuDebug(scaffold_SAPI::Debug *my_dbg, State *cpu) {
  if (cpu->MDSCR_EL1.IsSet()) my_dbg->set_mdscr_el1(cpu->MDSCR_EL1.Value());

  if (cpu->MDCCSR_EL0.IsSet())   my_dbg->set_mdccsr_el0(cpu->MDCCSR_EL0.Value());
  if (cpu->DBGDTR_EL0.IsSet())   my_dbg->set_dbgdtr_el0(cpu->DBGDTR_EL0.Value());
  if (cpu->DBGDTRRX_EL0.IsSet()) my_dbg->set_dbgdtrrx_el0(cpu->DBGDTRRX_EL0.Value());
  if (cpu->DBGDTRTX_EL0.IsSet()) my_dbg->set_dbgdtrtx_el0(cpu->DBGDTRTX_EL0.Value());

  if (cpu->DLR_EL0.IsSet())        my_dbg->set_dlr_el0(cpu->DLR_EL0.Value());
  if (cpu->DSPSR_EL0.IsSet())      my_dbg->set_dspsr_el0(cpu->DSPSR_EL0.Value());
  if (cpu->CONTEXTIDR_EL1.IsSet()) my_dbg->set_contextidr_el1(cpu->CONTEXTIDR_EL1.Value());
}

void SimTrace::RecordCpuDebug(scaffold_SAPI::CpuSlice *slice, State *cpu) {
  scaffold_SAPI::Debug *my_dbg = slice->mutable_dbg();
  RecordCpuDebug(my_dbg,cpu);
}

void SimTrace::diffCpuDebug(State &diffs, State *cpu) {
  SDIFF(MDSCR_EL1);

  SDIFF(MDCCSR_EL0);
  SDIFF(DBGDTR_EL0);
  SDIFF(DBGDTRRX_EL0);
  SDIFF(DBGDTRTX_EL0);

  SDIFF(DLR_EL0);
  SDIFF(DSPSR_EL0);
  SDIFF(CONTEXTIDR_EL1);
}

void SimTrace::RecordCpuExceptionState(scaffold_SAPI::ExceptionState *my_excep, State *cpu) {
  if (cpu->SPSR_EL1.IsSet()) my_excep->set_spsr_el1(cpu->SPSR_EL1.Value());
  if (cpu->SPSR_EL2.IsSet()) my_excep->set_spsr_el2(cpu->SPSR_EL2.Value());
  if (cpu->SPSR_EL3.IsSet()) my_excep->set_spsr_el3(cpu->SPSR_EL3.Value());

  if (cpu->ELR_EL1.IsSet()) my_excep->set_elr_el1(cpu->ELR_EL1.Value());
  if (cpu->ELR_EL2.IsSet()) my_excep->set_elr_el2(cpu->ELR_EL2.Value());
  if (cpu->ELR_EL3.IsSet()) my_excep->set_elr_el3(cpu->ELR_EL3.Value());

  if (cpu->ESR_EL1.IsSet()) my_excep->set_esr_el1(cpu->ESR_EL1.Value());
  if (cpu->ESR_EL2.IsSet()) my_excep->set_esr_el2(cpu->ESR_EL2.Value());
  if (cpu->ESR_EL3.IsSet()) my_excep->set_esr_el3(cpu->ESR_EL3.Value());

  if (cpu->FAR_EL1.IsSet()) my_excep->set_far_el1(cpu->FAR_EL1.Value());
  if (cpu->FAR_EL2.IsSet()) my_excep->set_far_el2(cpu->FAR_EL2.Value());
  if (cpu->FAR_EL3.IsSet()) my_excep->set_far_el3(cpu->FAR_EL3.Value());
}

void SimTrace::RecordCpuExceptionState(scaffold_SAPI::CpuSlice *slice, State *cpu) {
  scaffold_SAPI::ExceptionState *my_excep = slice->mutable_excep();
  RecordCpuExceptionState(my_excep,cpu);
}

void SimTrace::diffCpuExceptionState(State &diffs, State *cpu) {
  SDIFF(SPSR_EL1);
  SDIFF(SPSR_EL2);
  SDIFF(SPSR_EL3);

  SDIFF(ELR_EL1);
  SDIFF(ELR_EL2);
  SDIFF(ELR_EL3);

  SDIFF(ESR_EL1);
  SDIFF(ESR_EL2);
  SDIFF(ESR_EL3);

  SDIFF(FAR_EL1);
  SDIFF(FAR_EL2);
  SDIFF(FAR_EL3);
}

void SimTrace::RecordCpuVMSA(scaffold_SAPI::VMSA *my_mmu, State *cpu) {
  if (cpu->VBAR_EL1.IsSet()) my_mmu->set_vbar_el1(cpu->VBAR_EL1.Value());
  if (cpu->VBAR_EL2.IsSet()) my_mmu->set_vbar_el2(cpu->VBAR_EL2.Value());
  if (cpu->VBAR_EL3.IsSet()) my_mmu->set_vbar_el3(cpu->VBAR_EL3.Value());

  if (cpu->TCR_EL1.IsSet()) my_mmu->set_tcr_el1(cpu->TCR_EL1.Value());
  if (cpu->TCR_EL2.IsSet()) my_mmu->set_tcr_el2(cpu->TCR_EL2.Value());
  if (cpu->TCR_EL3.IsSet()) my_mmu->set_tcr_el3(cpu->TCR_EL3.Value());

  if (cpu->MAIR_EL1.IsSet()) my_mmu->set_mair_el1(cpu->MAIR_EL1.Value());
  if (cpu->MAIR_EL2.IsSet()) my_mmu->set_mair_el2(cpu->MAIR_EL2.Value());
  if (cpu->MAIR_EL3.IsSet()) my_mmu->set_mair_el3(cpu->MAIR_EL3.Value());

  if (cpu->SCTLR_EL1.IsSet()) my_mmu->set_sctlr_el1(cpu->SCTLR_EL1.Value());
  if (cpu->SCTLR_EL2.IsSet()) my_mmu->set_sctlr_el2(cpu->SCTLR_EL2.Value());
  if (cpu->SCTLR_EL3.IsSet()) my_mmu->set_sctlr_el3(cpu->SCTLR_EL3.Value());

  if (cpu->TTBR0_EL1.IsSet()) my_mmu->set_ttbr0_el1(cpu->TTBR0_EL1.Value());
  if (cpu->TTBR1_EL1.IsSet()) my_mmu->set_ttbr1_el1(cpu->TTBR1_EL1.Value());
  if (cpu->TTBR0_EL2.IsSet()) my_mmu->set_ttbr0_el2(cpu->TTBR0_EL2.Value());
  if (cpu->TTBR0_EL3.IsSet()) my_mmu->set_ttbr0_el3(cpu->TTBR0_EL3.Value());

  if (cpu->HCR_EL2.IsSet()) my_mmu->set_hcr_el2(cpu->HCR_EL2.Value());

  if (cpu->PAR_EL1.IsSet()) my_mmu->set_par_el1(cpu->PAR_EL1.Value());
}

void SimTrace::RecordCpuVMSA(scaffold_SAPI::CpuSlice *slice, State *cpu) {
  scaffold_SAPI::VMSA *my_mmu = slice->mutable_mmu();
  RecordCpuVMSA(my_mmu,cpu);
}

void SimTrace::diffCpuVMSA(State &diffs, State *cpu) {
  SDIFF(VBAR_EL1);
  SDIFF(VBAR_EL2);
  SDIFF(VBAR_EL3);

  SDIFF(TCR_EL1);
  SDIFF(TCR_EL2);
  SDIFF(TCR_EL3);

  SDIFF(MAIR_EL1);
  SDIFF(MAIR_EL2);
  SDIFF(MAIR_EL3);

  SDIFF(SCTLR_EL1);
  SDIFF(SCTLR_EL2);
  SDIFF(SCTLR_EL3);

  SDIFF(TTBR0_EL1);
  SDIFF(TTBR1_EL1);
  SDIFF(TTBR0_EL2);
  SDIFF(TTBR0_EL3);

  SDIFF(HCR_EL2);
  SDIFF(PAR_EL1);
}

void SimTrace::RecordCpuResetMgmt(scaffold_SAPI::ResetMgmt *my_reset, State *cpu) {
  if (cpu->RMR_EL1.IsSet()) my_reset->set_rmr_el1(cpu->RMR_EL1.Value());
  if (cpu->RMR_EL2.IsSet()) my_reset->set_rmr_el2(cpu->RMR_EL2.Value());
  if (cpu->RMR_EL3.IsSet()) my_reset->set_rmr_el3(cpu->RMR_EL3.Value());
}

void SimTrace::RecordCpuResetMgmt(scaffold_SAPI::CpuSlice *slice, State *cpu) {
  scaffold_SAPI::ResetMgmt *my_reset = slice->mutable_reset();
  RecordCpuResetMgmt(my_reset,cpu);
}

void SimTrace::diffCpuResetMgmt(State &diffs, State *cpu) {
  SDIFF(RMR_EL1);
  SDIFF(RMR_EL2);
  SDIFF(RMR_EL3);
}

void SimTrace::RecordCpuThreadState(scaffold_SAPI::ThreadRegs *my_thread, State *cpu) {
  if (cpu->TPIDR_EL0.IsSet()) my_thread->set_tpidr_el0(cpu->TPIDR_EL0.Value());
  if (cpu->TPIDR_EL1.IsSet()) my_thread->set_tpidr_el1(cpu->TPIDR_EL1.Value());
  if (cpu->TPIDR_EL2.IsSet()) my_thread->set_tpidr_el2(cpu->TPIDR_EL2.Value());
  if (cpu->TPIDR_EL3.IsSet()) my_thread->set_tpidr_el3(cpu->TPIDR_EL3.Value());
}

void SimTrace::RecordCpuThreadState(scaffold_SAPI::CpuSlice *slice, State *cpu) {
  scaffold_SAPI::ThreadRegs *my_thread = slice->mutable_thread();
  RecordCpuThreadState(my_thread,cpu);
}

void SimTrace::diffCpuThreadState(State &diffs, State *cpu) {
  SDIFF(TPIDR_EL0);
  SDIFF(TPIDR_EL1);
  SDIFF(TPIDR_EL2);
  SDIFF(TPIDR_EL3);
}

void SimTrace::RecordCpuTimerState(scaffold_SAPI::GenericTimer *my_timer, State *cpu) {
  if (cpu->CNTFRQ_EL0.IsSet())     my_timer->set_cntfrq_el0(cpu->CNTFRQ_EL0.Value());
  if (cpu->CNTHCTL_EL2.IsSet())    my_timer->set_cnthctl_el2(cpu->CNTHCTL_EL2.Value());
  if (cpu->CNTHP_CTL_EL2.IsSet())  my_timer->set_cnthp_ctl_el2(cpu->CNTHP_CTL_EL2.Value());
  if (cpu->CNTHP_CVAL_EL2.IsSet()) my_timer->set_cnthp_cval_el2(cpu->CNTHP_CVAL_EL2.Value());
  if (cpu->CNTHP_TVAL_EL2.IsSet()) my_timer->set_cnthp_tval_el2(cpu->CNTHP_TVAL_EL2.Value());
  if (cpu->CNTKCTL_EL1.IsSet())    my_timer->set_cntkctl_el1(cpu->CNTKCTL_EL1.Value());
  if (cpu->CNTP_CTL_EL0.IsSet())   my_timer->set_cntp_ctl_el0(cpu->CNTP_CTL_EL0.Value());
  if (cpu->CNTP_CVAL_EL0.IsSet())  my_timer->set_cntp_cval_el0(cpu->CNTP_CVAL_EL0.Value());
  if (cpu->CNTP_TVAL_EL0.IsSet())  my_timer->set_cntp_tval_el0(cpu->CNTP_TVAL_EL0.Value());
  if (cpu->CNTPCT_EL0.IsSet())     my_timer->set_cntpct_el0(cpu->CNTPCT_EL0.Value());
  if (cpu->CNTPS_CTL_EL1.IsSet())  my_timer->set_cntps_ctl_el1(cpu->CNTPS_CTL_EL1.Value());
  if (cpu->CNTPS_CVAL_EL1.IsSet()) my_timer->set_cntps_cval_el1(cpu->CNTPS_CVAL_EL1.Value());
  if (cpu->CNTPS_TVAL_EL1.IsSet()) my_timer->set_cntps_tval_el1(cpu->CNTPS_TVAL_EL1.Value());
  if (cpu->CNTV_CTL_EL0.IsSet())   my_timer->set_cntv_ctl_el0(cpu->CNTV_CTL_EL0.Value());
  if (cpu->CNTV_CVAL_EL0.IsSet())  my_timer->set_cntv_cval_el0(cpu->CNTV_CVAL_EL0.Value());
  if (cpu->CNTV_TVAL_EL0.IsSet())  my_timer->set_cntv_tval_el0(cpu->CNTV_TVAL_EL0.Value());
  if (cpu->CNTVCT_EL0.IsSet())     my_timer->set_cntvct_el0(cpu->CNTVCT_EL0.Value());
  if (cpu->CNTVOFF_EL2.IsSet())    my_timer->set_cntvoff_el2(cpu->CNTVOFF_EL2.Value());
}
void SimTrace::RecordCpuTimerState(scaffold_SAPI::CpuSlice *slice, State *cpu) {
  scaffold_SAPI::GenericTimer *my_timer = slice->mutable_timer();
  RecordCpuTimerState(my_timer,cpu);
}
void SimTrace::diffCpuTimerState(State &diffs, State *cpu) {
  SDIFF(CNTFRQ_EL0);
  SDIFF(CNTHCTL_EL2);
  SDIFF(CNTHP_CTL_EL2);
  SDIFF(CNTHP_CVAL_EL2);
  SDIFF(CNTHP_TVAL_EL2);
  SDIFF(CNTKCTL_EL1);
  SDIFF(CNTP_CTL_EL0);
  SDIFF(CNTP_CVAL_EL0);
  SDIFF(CNTP_TVAL_EL0);
  SDIFF(CNTPCT_EL0);
  SDIFF(CNTPS_CTL_EL1);
  SDIFF(CNTPS_CVAL_EL1);
  SDIFF(CNTPS_TVAL_EL1);
  SDIFF(CNTV_CTL_EL0);
  SDIFF(CNTV_CVAL_EL0);
  SDIFF(CNTV_TVAL_EL0);
  SDIFF(CNTVCT_EL0);
  SDIFF(CNTVOFF_EL2);
}

void SimTrace::RecordCpuGICState(scaffold_SAPI::GICSystemRegs *my_gic_sregs, State *cpu) {
  if (cpu->ICC_PMR_EL1.IsSet())     my_gic_sregs->set_icc_pmr_el1(cpu->ICC_PMR_EL1.Value());
  if (cpu->ICC_IAR0_EL1.IsSet())    my_gic_sregs->set_icc_iar0_el1(cpu->ICC_IAR0_EL1.Value());
  if (cpu->ICC_EORI0_EL1.IsSet())   my_gic_sregs->set_icc_eori0_el1(cpu->ICC_EORI0_EL1.Value());
  if (cpu->ICC_HPPIR0_EL1.IsSet())  my_gic_sregs->set_icc_hppir0_el1(cpu->ICC_HPPIR0_EL1.Value());
  if (cpu->ICC_BPR0_EL1.IsSet())    my_gic_sregs->set_icc_bpr0_el1(cpu->ICC_BPR0_EL1.Value()); 
  if (cpu->ICC_AP0R0_EL1.IsSet())   my_gic_sregs->set_icc_ap0r0_el1(cpu->ICC_AP0R0_EL1.Value());
  if (cpu->ICC_AP0R1_EL1.IsSet())   my_gic_sregs->set_icc_ap0r1_el1(cpu->ICC_AP0R1_EL1.Value());
  if (cpu->ICC_AP0R2_EL1.IsSet())   my_gic_sregs->set_icc_ap0r2_el1(cpu->ICC_AP0R2_EL1.Value());
  if (cpu->ICC_AP0R3_EL1.IsSet())   my_gic_sregs->set_icc_ap0r3_el1(cpu->ICC_AP0R3_EL1.Value());
  if (cpu->ICC_AP1R0_EL1.IsSet())   my_gic_sregs->set_icc_ap1r0_el1(cpu->ICC_AP1R0_EL1.Value());
  if (cpu->ICC_AP1R1_EL1.IsSet())   my_gic_sregs->set_icc_ap1r1_el1(cpu->ICC_AP1R1_EL1.Value());
  if (cpu->ICC_AP1R2_EL1.IsSet())   my_gic_sregs->set_icc_ap1r2_el1(cpu->ICC_AP1R2_EL1.Value());
  if (cpu->ICC_AP1R3_EL1.IsSet())   my_gic_sregs->set_icc_ap1r3_el1(cpu->ICC_AP1R3_EL1.Value());
  if (cpu->ICC_DIR_EL1.IsSet())     my_gic_sregs->set_icc_dir_el1(cpu->ICC_DIR_EL1.Value());
  if (cpu->ICC_RPR_EL1.IsSet())     my_gic_sregs->set_icc_rpr_el1(cpu->ICC_RPR_EL1.Value());
  if (cpu->ICC_SGI1R_EL1.IsSet())   my_gic_sregs->set_icc_sgi1r_el1(cpu->ICC_SGI1R_EL1.Value());
  if (cpu->ICC_ASGI1R_EL1.IsSet())  my_gic_sregs->set_icc_asgi1r_el1(cpu->ICC_ASGI1R_EL1.Value());
  if (cpu->ICC_SGI0R_EL1.IsSet())   my_gic_sregs->set_icc_sgi0r_el1(cpu->ICC_SGI0R_EL1.Value());
  if (cpu->ICC_IAR1_EL1.IsSet())    my_gic_sregs->set_icc_iar1_el1(cpu->ICC_IAR1_EL1.Value());
  if (cpu->ICC_EOIR1_EL1.IsSet())   my_gic_sregs->set_icc_eoir1_el1(cpu->ICC_EOIR1_EL1.Value());
  if (cpu->ICC_HPPIR1_EL1.IsSet())  my_gic_sregs->set_icc_hppir1_el1(cpu->ICC_HPPIR1_EL1.Value());
  if (cpu->ICC_BPR1_EL1.IsSet())    my_gic_sregs->set_icc_bpr1_el1(cpu->ICC_BPR1_EL1.Value());
  if (cpu->ICC_CTLR_EL1.IsSet())    my_gic_sregs->set_icc_ctlr_el1(cpu->ICC_CTLR_EL1.Value());
  if (cpu->ICC_SRE_EL1.IsSet())     my_gic_sregs->set_icc_sre_el1(cpu->ICC_SRE_EL1.Value());
  if (cpu->ICC_IGRPEN0_EL1.IsSet()) my_gic_sregs->set_icc_igrpen0_el1(cpu->ICC_IGRPEN0_EL1.Value());
  if (cpu->ICC_IGRPEN1_EL1.IsSet()) my_gic_sregs->set_icc_igrpen1_el1(cpu->ICC_IGRPEN1_EL1.Value());
  if (cpu->ICC_SRE_EL2.IsSet())     my_gic_sregs->set_icc_sre_el2(cpu->ICC_SRE_EL2.Value());
  if (cpu->ICC_CTLR_EL3.IsSet())    my_gic_sregs->set_icc_ctlr_el3(cpu->ICC_CTLR_EL3.Value());
  if (cpu->ICC_SRE_EL3.IsSet())     my_gic_sregs->set_icc_sre_el3(cpu->ICC_SRE_EL3.Value());
  if (cpu->ICC_IGRPEN1_EL3.IsSet()) my_gic_sregs->set_icc_igrpen1_el3(cpu->ICC_IGRPEN1_EL3.Value());
}

void SimTrace::RecordCpuGICState(scaffold_SAPI::CpuSlice *slice, State *cpu) {
  scaffold_SAPI::GICSystemRegs *my_gic_sregs = slice->mutable_gic_sregs();
  RecordCpuGICState(my_gic_sregs,cpu);
}

void SimTrace::diffCpuGICState(State &diffs, State *cpu) {
  SDIFF(ICC_PMR_EL1);
  SDIFF(ICC_IAR0_EL1);
  SDIFF(ICC_EORI0_EL1);
  SDIFF(ICC_HPPIR0_EL1);
  SDIFF(ICC_BPR0_EL1); 
  SDIFF(ICC_AP0R0_EL1);
  SDIFF(ICC_AP0R1_EL1);
  SDIFF(ICC_AP0R2_EL1);
  SDIFF(ICC_AP0R3_EL1);
  SDIFF(ICC_AP1R0_EL1);
  SDIFF(ICC_AP1R1_EL1);
  SDIFF(ICC_AP1R2_EL1);
  SDIFF(ICC_AP1R3_EL1);
  SDIFF(ICC_DIR_EL1);
  SDIFF(ICC_RPR_EL1);
  SDIFF(ICC_SGI1R_EL1);
  SDIFF(ICC_ASGI1R_EL1);
  SDIFF(ICC_SGI0R_EL1);
  SDIFF(ICC_IAR1_EL1);
  SDIFF(ICC_EOIR1_EL1);
  SDIFF(ICC_HPPIR1_EL1);
  SDIFF(ICC_BPR1_EL1);
  SDIFF(ICC_CTLR_EL1);
  SDIFF(ICC_SRE_EL1);
  SDIFF(ICC_IGRPEN0_EL1);
  SDIFF(ICC_IGRPEN1_EL1);
  SDIFF(ICC_SRE_EL2);
  SDIFF(ICC_CTLR_EL3);
  SDIFF(ICC_SRE_EL3);
  SDIFF(ICC_IGRPEN1_EL3);
}

void SimTrace::RecordCpuState(scaffold_SAPI::CpuSlice *my_slice, State *cpu) {
  RecordCpuBase(my_slice,cpu);
  RecordCpuConfig(my_slice,cpu);
  RecordCpuProcID(my_slice,cpu);
  RecordCpuFPU(my_slice,cpu);
  RecordCpuDebug(my_slice,cpu);
  RecordCpuExceptionState(my_slice,cpu);
  RecordCpuVMSA(my_slice,cpu);
  RecordCpuResetMgmt(my_slice,cpu);
  RecordCpuThreadState(my_slice,cpu);
  RecordCpuGICState(my_slice,cpu);
  RecordCpuTimerState(my_slice,cpu);
}

void SimTrace::RecordCpuState(State *cpu) {
  RecordCpuState(my_slice,cpu);
}

void SimTrace::RecordPacketFetch(scaffold_SAPI::Packet *pkt, Packet *packet) {
  scaffold_SAPI::Fetch *ftch = pkt->mutable_fetch();

  ftch->set_instr_size_in_bytes(packet->instr_size_in_bytes);
  ftch->set_access_size_in_bytes(packet->access_size_in_bytes);
  ftch->set_big_endian(packet->big_endian);

  if (packet->instr_size_in_bytes > 0)
    ftch->set_mbuf((void *) packet->mbuf,packet->instr_size_in_bytes);
}

void SimTrace::RecordPacketDecode(scaffold_SAPI::Packet *pkt, Packet *packet) {
  scaffold_SAPI::Decode *dcd = pkt->mutable_decode();

  dcd->set_opcode(packet->Opcode);
  dcd->set_primary_opcode(packet->primary_opcode);
  //dcd->set_a64instrname(packet->InstrName());
  dcd->set_a64instrenum(packet->InstrEnumName());

  if (packet->sf.IsDefined())      { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("sf");      fld->set_val(packet->sf.Value());      };
  if (packet->op.IsDefined())      { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("op");      fld->set_val(packet->op.Value());      };
  if (packet->op0.IsDefined())     { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("op0");     fld->set_val(packet->op0.Value());     };
  if (packet->op1.IsDefined())     { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("op1");     fld->set_val(packet->op1.Value());     };
  if (packet->op2.IsDefined())     { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("op2");     fld->set_val(packet->op2.Value());     };
  if (packet->op3.IsDefined())     { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("op3");     fld->set_val(packet->op3.Value());     };
  if (packet->op4.IsDefined())     { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("op4");     fld->set_val(packet->op4.Value());     };
  if (packet->op21.IsDefined())    { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("op21");    fld->set_val(packet->op21.Value());    };
  if (packet->op31.IsDefined())    { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("op31");    fld->set_val(packet->op31.Value());    };
  if (packet->op54.IsDefined())    { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("op54");    fld->set_val(packet->op54.Value());    };
  if (packet->opc.IsDefined())     { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("opc");     fld->set_val(packet->opc.Value());     };
  if (packet->o0.IsDefined())      { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("o0");      fld->set_val(packet->o0.Value());      };
  if (packet->o1.IsDefined())      { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("o1");      fld->set_val(packet->o1.Value());      };
  if (packet->o2.IsDefined())      { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("o2");      fld->set_val(packet->o2.Value());      };
  if (packet->o3.IsDefined())      { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("o3");      fld->set_val(packet->o3.Value());      };
  if (packet->o4.IsDefined())      { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("o4");      fld->set_val(packet->o4.Value());      };
  if (packet->a.IsDefined())       { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("a");       fld->set_val(packet->a.Value());       };
  if (packet->b.IsDefined())       { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("b");       fld->set_val(packet->b.Value());       };
  if (packet->b40.IsDefined())     { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("b40");     fld->set_val(packet->b40.Value());     };
  if (packet->b5.IsDefined())      { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("b5");      fld->set_val(packet->b5.Value());      };
  if (packet->c.IsDefined())       { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("c");       fld->set_val(packet->c.Value());       };
  if (packet->d.IsDefined())       { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("d");       fld->set_val(packet->d.Value());       };
  if (packet->e.IsDefined())       { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("e");       fld->set_val(packet->e.Value());       };
  if (packet->f.IsDefined())       { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("f");       fld->set_val(packet->f.Value());       };
  if (packet->g.IsDefined())       { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("g");       fld->set_val(packet->g.Value());       };
  if (packet->h.IsDefined())       { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("h");       fld->set_val(packet->h.Value());       };
  if (packet->H.IsDefined())       { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("H");       fld->set_val(packet->H.Value());       };
  if (packet->L.IsDefined())       { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("L");       fld->set_val(packet->L.Value());       };
  if (packet->LL.IsDefined())      { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("LL");      fld->set_val(packet->LL.Value());      };
  if (packet->S.IsDefined())       { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("S");       fld->set_val(packet->S.Value());       };
  if (packet->M.IsDefined())       { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("M");       fld->set_val(packet->M.Value());       };
  if (packet->N.IsDefined())       { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("N");       fld->set_val(packet->N.Value());       };
  if (packet->hw.IsDefined())      { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("hw");      fld->set_val(packet->hw.Value());      };
  if (packet->Q.IsDefined())       { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("Q");       fld->set_val(packet->Q.Value());       };
  if (packet->R.IsDefined())       { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("R");       fld->set_val(packet->R.Value());       };
  if (packet->U.IsDefined())       { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("U");       fld->set_val(packet->U.Value());       };
  if (packet->V.IsDefined())       { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("V");       fld->set_val(packet->V.Value());       };
  if (packet->Rd.IsDefined())      { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("Rd");      fld->set_val(packet->Rd.Value());      };
  if (packet->Rn.IsDefined())      { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("Rn");      fld->set_val(packet->Rn.Value());      };
  if (packet->Rs.IsDefined())      { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("Rs");      fld->set_val(packet->Rs.Value());      };
  if (packet->Rt.IsDefined())      { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("Rt");      fld->set_val(packet->Rt.Value());      };
  if (packet->Rt2.IsDefined())     { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("Rt2");     fld->set_val(packet->Rt2.Value());     };
  if (packet->Ra.IsDefined())      { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("Ra");      fld->set_val(packet->Ra.Value());      };
  if (packet->CRn.IsDefined())     { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("CRn");     fld->set_val(packet->CRn.Value());     };
  if (packet->Rm.IsDefined())      { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("Rm");      fld->set_val(packet->Rm.Value());      };
  if (packet->CRm.IsDefined())     { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("CRm");     fld->set_val(packet->CRm.Value());     };
  if (packet->shift.IsDefined())   { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("shift");   fld->set_val(packet->shift.Value());   };
  if (packet->size.IsDefined())    { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("size");    fld->set_val(packet->size.Value());    };
  if (packet->cmode.IsDefined())   { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("cmode");   fld->set_val(packet->cmode.Value());   };
  if (packet->rmode.IsDefined())   { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("rmode");   fld->set_val(packet->rmode.Value());   };
  if (packet->cond.IsDefined())    { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("cond");    fld->set_val(packet->cond.Value());    };
  if (packet->nzcv.IsDefined())    { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("nzcv");    fld->set_val(packet->nzcv.Value());    };
  if (packet->opcode.IsDefined())  { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("opcode");  fld->set_val(packet->opcode.Value());  };
  if (packet->opcode2.IsDefined()) { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("opcode2"); fld->set_val(packet->opcode2.Value()); };
  if (packet->opt.IsDefined())     { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("opt");     fld->set_val(packet->opt.Value());     };
  if (packet->option.IsDefined())  { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("option");  fld->set_val(packet->option.Value());  };
  if (packet->type.IsDefined())    { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("type");    fld->set_val(packet->type.Value());    };
  if (packet->scale.IsDefined())   { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("scale");   fld->set_val(packet->scale.Value());   };
  if (packet->len.IsDefined())     { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("len");     fld->set_val(packet->len.Value());     };
  if (packet->imm3.IsDefined())    { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("imm3");    fld->set_val(packet->imm3.Value());    };
  if (packet->imm4.IsDefined())    { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("imm4");    fld->set_val(packet->imm4.Value());    };
  if (packet->imm5.IsDefined())    { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("imm5");    fld->set_val(packet->imm5.Value());    };
  if (packet->imm6.IsDefined())    { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("imm6");    fld->set_val(packet->imm6.Value());    };
  if (packet->imm7.IsDefined())    { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("imm7");    fld->set_val(packet->imm7.Value());    };
  if (packet->imm8.IsDefined())    { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("imm8");    fld->set_val(packet->imm8.Value());    };
  if (packet->imm9.IsDefined())    { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("imm9");    fld->set_val(packet->imm9.Value());    };
  if (packet->imm12.IsDefined())   { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("imm12");   fld->set_val(packet->imm12.Value());   };
  if (packet->imm14.IsDefined())   { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("imm14");   fld->set_val(packet->imm14.Value());   };
  if (packet->imm16.IsDefined())   { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("imm16");   fld->set_val(packet->imm16.Value());   };
  if (packet->imm19.IsDefined())   { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("imm19");   fld->set_val(packet->imm19.Value());   };
  if (packet->imm26.IsDefined())   { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("imm26");   fld->set_val(packet->imm26.Value());   };
  if (packet->immlo.IsDefined())   { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("immlo");   fld->set_val(packet->immlo.Value());   };
  if (packet->immhi.IsDefined())   { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("immhi");   fld->set_val(packet->immhi.Value());   };
  if (packet->immr.IsDefined())    { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("immr");    fld->set_val(packet->immr.Value());    };
  if (packet->imms.IsDefined())    { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("imms");    fld->set_val(packet->imms.Value());    };
  if (packet->immb.IsDefined())    { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("immb");    fld->set_val(packet->immb.Value());    };
  if (packet->immh.IsDefined())    { scaffold_SAPI::InstrField* fld = dcd->add_field_ops(); fld->set_key("immh");    fld->set_val(packet->immh.Value());    };
}

void SimTrace::RecordPacketFetchOperands(scaffold_SAPI::Packet *pkt, State *cpu, Packet *packet) {
  scaffold_SAPI::FetchOperands *fops = pkt->mutable_read_ops();

  for (vector<struct RegDep>::iterator i = packet->srcRegDep.begin(); i != packet->srcRegDep.end(); i++) {
     int reg_type = (*i).TYPE();
     int reg_id = (*i).ID();
     unsigned long long rval = (*i).RVAL();
     unsigned long long rval_hi = (*i).RVAL_HI();

     char tbuf[128];
     string rname;

     switch(reg_type) {
       case DEP_GP:     {
                        sprintf(tbuf,"GP[%d]",reg_id); 
                        rname = tbuf; 
                        scaffold_SAPI::RegisterUpdate* reg = fops->add_srcregsgp();
                        reg->set_key(rname);
                        reg->set_val(rval);
                        }
                        break;

       case DEP_SP:     // stack pointer...
                        {
                        sprintf(tbuf,"SP_EL%d",reg_id); 
                        rname = tbuf; 
                        scaffold_SAPI::RegisterUpdate* reg = fops->add_srcregsgp();
                        reg->set_key(rname);
                        reg->set_val(rval);
                        }
                        break;

       case DEP_FP_SP:  // record all float reg accesses as simd reg accessess... 
       case DEP_FP_DP:     
       case DEP_ASIMD:  {
                        scaffold_SAPI::SimdReg* reg = fops->add_srcregsasimd();
                        reg->set_key(reg_id);
                        reg->set_rval_lo(rval);
                        reg->set_rval_hi(rval_hi);
                        }
                        break;
			
       case DEP_SPR:    {
                        rname = cpu->SystemRegisterName(reg_id);     
                        scaffold_SAPI::RegisterUpdate* reg = fops->add_srcregssys();
                        reg->set_key(rname);
                        reg->set_val(rval);
                        }
                        break;
			
       case DEP_PSTATE: {
                        rname = "PSTATE";                            
                        scaffold_SAPI::RegisterUpdate* reg = fops->add_srcregssys();
                        reg->set_key(rname);
                        reg->set_val(rval);
                        }
                        break;
		       
       default: break;
     }
  }

  for (vector<XRegister>::iterator i = packet->srcXreg.begin(); i != packet->srcXreg.end(); i++) {
     unsigned long long rval = (*i).Value();
     unsigned long long rval_hi = (*i).ValueHi();
     int rid = (*i).ID();
     int type = (*i).Type();
     char tbuf[128];
     std::string rname;
     switch(type) {
       case XRegister::IS_GPR:    {
                                   sprintf(tbuf,"GP[%d]",rid); 
			           rname = tbuf; 
                                   scaffold_SAPI::RegisterUpdate* reg = fops->add_srcregsgp();
                                   reg->set_key(rname);
                                   reg->set_val(rval);
                                  }
	                          break;
       case XRegister::IS_SP:     {
                                   sprintf(tbuf,"SP_EL%d",rid); 
                                   rname = tbuf; 
                                   scaffold_SAPI::RegisterUpdate* reg = fops->add_srcregsgp();
                                   reg->set_key(rname);
                                   reg->set_val(rval);
                                  }
                                  break;    
       case XRegister::IS_FLOAT:  {
                                   // record all float reg accesses as simd reg accessess...
	                           scaffold_SAPI::SimdReg* reg = fops->add_srcregsasimd();
                                   reg->set_key((*i).ID());
                                   reg->set_rval_lo(rval);
                                   reg->set_rval_hi(rval_hi);
                                  }
                                  break;		
       case XRegister::IS_SPR:    {
                                   rname = (*i).Name();    
                                   scaffold_SAPI::RegisterUpdate* reg = fops->add_srcregssys();
                                   reg->set_key(rname);
                                   reg->set_val(rval);
                                  }
                                  break;	
       case XRegister::IS_PSTATE: {
                                   rname = (*i).Name();                            
                                   scaffold_SAPI::RegisterUpdate* reg = fops->add_srcregssys();
                                   reg->set_key(rname);
                                   reg->set_val(rval);
                                  }
                                  break;
       default: break;
     }
  }
}

void SimTrace::RecordPacketExecute(scaffold_SAPI::Packet *pkt, Packet *packet) {
  //scaffold_SAPI::Execute *exec = pkt->mutable_exec(); //<---nothing to add just yet...
}

void SimTrace::RecordPacketMemoryAccesses(scaffold_SAPI::Packet *pkt, State *cpu, Memory *mem, Packet *packet) {
  scaffold_SAPI::AccessMemory *mops = pkt->mutable_mem_ops();

  for (vector<MemoryAccess>::iterator i = packet->mOpsMemory.begin(); i != packet->mOpsMemory.end(); i++) {
     scaffold_SAPI::MemoryAccess* macc = mops->add_mopsmemory();
     macc->set_address((*i).address);
     macc->set_size((*i).size);
     switch((*i).type) {
     case INSTRUCTION:  macc->set_type("INSTRUCTION");  break;
     case DATA:         macc->set_type("DATA");         break;
     case NORMAL:       macc->set_type("NORMAL");       break;
     case ATOMIC:       macc->set_type("ATOMIC");       break;
     case ORDERED:      macc->set_type("ORDERED");      break;
     case UNPRIVILEGED: macc->set_type("UNPRIVILEGED"); break;
     case STREAM:       macc->set_type("STREAM");       break;
     case VECTOR:       macc->set_type("VFP/ASIMD");    break;       
     default: macc->set_type("?"); break;
     }
     macc->set_exclusive((*i).exclusive);

     if ((*i).direction==FOR_READ)
       macc->set_direction("READ");
     else if ((*i).direction==FOR_WRITE)
       macc->set_direction("WRITE");
     else if ((*i).direction==FOR_PREFETCH)
       macc->set_direction("PREFETCH");
     else
       macc->set_direction("?");
       
     macc->set_endianness((*i).big_endian ? "big-endian" : "little-endian");
     macc->set_word_size((*i).word_size);
     macc->set_sign_extend((*i).sign_extend);
     macc->set_paired((*i).paired);
     macc->set_privileged((*i).privileged);

     macc->set_membuffer((void *) (*i).membuffer,(*i).size);

     macc->set_exclusive_passed((*i).exclusive_passed);
     
     if ((*i).exclusive) {
       scaffold_SAPI::ExclusiveMonitor* excl_global = macc->mutable_global_monitor();
       excl_global->set_la(mem->global_monitor.LA());
       excl_global->set_pa(mem->global_monitor.PA());
       excl_global->set_elem_size(mem->global_monitor.ElementSize());
       excl_global->set_cpu_id(mem->global_monitor.CPUID());
       excl_global->set_exclusive(mem->global_monitor.IsExclusive());

       scaffold_SAPI::ExclusiveMonitor* excl_local = macc->mutable_local_monitor();
       excl_local->set_la(cpu->local_monitor.LA());
       excl_local->set_pa(cpu->local_monitor.PA());
       excl_local->set_elem_size(cpu->local_monitor.ElementSize());
       excl_local->set_cpu_id(cpu->local_monitor.CPUID());
       excl_local->set_exclusive(cpu->local_monitor.IsExclusive());
     }
  }

  for (vector<Translation *>::iterator i = packet->translations.begin(); i != packet->translations.end(); i++) {
     int trans_id = RecordTranslation(my_core,*i);
     mops->add_translations(trans_id);
  }
}

// for address comparison between translations, either mask to the translation base address
// (if non-zero) or a 4k page (smallest sim-trace archived translation)... 

unsigned long long SimTrace::TranslationMask(Translation *trans) {
  return (trans->mmu_enabled && (trans->base_address != 0)) ? trans->base_address : 0xffffffffffff0000ull;
}

bool SimTrace::MatchingTranslation(scaffold_SAPI::Translation *nt,Translation *trans) {
  if ((trans->LA & TranslationMask(trans)) != nt->la()) 
    return false;
  if (trans->ASID != nt->asid()) 
    return false;
  if (trans->privileged != nt->privileged())
    return false;
  if (trans->NS != nt->ns())
    return false;
  if (trans->is_data != nt->is_data()) 
    return false;
  if (trans->is_write != nt->is_write()) 
    return false;

  if ((trans->PA & TranslationMask(trans)) != nt->pa()) 
    return false;

  if (trans->mmu_enabled != nt->mmu_enabled())
    return false;

  if (trans->mmu_enabled) {
    if (trans->levels != nt->descriptors_size())
      return false;
    // check the actual descriptor values used in the translation...
    for (int i = 0; i < trans->levels; i++) {
      if (nt->descriptors(i).dval() != trans->descriptors[i].Value()) 
         return false;
    }
  } else {
    // mmu is off. we'll ASSUME other translation parameters are the same...
  }

  return true;
}

int SimTrace::RecordTranslation(scaffold_SAPI::Cpu *my_core, Translation *trans) {
  // look for matching translation from the last (latest) recorded translation to the earliest.
  // we do this simply to cut down on the # of redundant translations...

  int trans_index = -1;

  for (trans_index = my_core->translations_size() - 1; trans_index >=0; trans_index--) {
     scaffold_SAPI::Translation *nt = my_core->mutable_translations(trans_index);
     if (MatchingTranslation(nt,trans))
       break;
  }

  if (trans_index >= 0) {
#ifdef DEBUG_TRANSLATIONS
    printf("[SimTrace::RecordTranslation] translation for this address (LA/PA: 0x%llx/0x%llx) has already been recorded (id: %d, cnt: %d)...\n",
           trans->LA,trans->PA,trans_index, my_core->translations_size());
#endif
    return trans_index;
  }

  // new translation to record!...
    
  scaffold_SAPI::Translation *nt = my_core->add_translations();

  trans_index = my_core->translations_size() - 1;

  nt->set_la(   trans->LA    & TranslationMask(trans) ); //
  nt->set_extla(trans->extLA & TranslationMask(trans) ); // an archived translation is to a page,
  nt->set_ipa(  trans->IPA   & TranslationMask(trans) ); //  not a specific address...
  nt->set_pa(   trans->PA    & TranslationMask(trans) ); //

  nt->set_asid(trans->ASID);
  nt->set_global(trans->Global); 
  nt->set_ns(trans->NS);
  nt->set_is_data(trans->is_data);
  nt->set_is_write(trans->is_write);
  nt->set_mmu_enabled(trans->mmu_enabled);
  nt->set_secondstage(trans->secondstage);
  nt->set_permissioncheck(trans->permissioncheck);
  nt->set_addressextended(trans->addressExtended);
  nt->set_wasaligned(trans->wasaligned);
  nt->set_size(trans->size);
  nt->set_privileged(trans->privileged);
  nt->set_bigendian(trans->BigEndian);
  nt->set_topbit(trans->topBit);
  nt->set_s1_enabled(trans->s1_enabled);
  nt->set_s2_enabled(trans->s2_enabled);
  nt->set_ttb_base_address(trans->ttb_base_address);
  nt->set_tbi(trans->tbi);
  nt->set_readunprivileged(trans->readUnprivileged);
  nt->set_writeunprivileged(trans->writeUnprivileged);
  nt->set_readprivileged(trans->readPrivileged);
  nt->set_writeprivileged(trans->writePrivileged);
  nt->set_xn(trans->XN);
  nt->set_pxn(trans->PXN);
  nt->set_contiguous(trans->Contiguous);
  nt->set_ng(trans->nG);
  nt->set_af(trans->AF);
  nt->set_memory_type(trans->memory_type);
  nt->set_device_type(trans->device_type);
  nt->set_outer_cache_type(trans->outer_cache_type);
  nt->set_outer_transient(trans->outer_transient);
  nt->set_outer_read_allocate(trans->outer_read_allocate);
  nt->set_outer_write_allocate(trans->outer_write_allocate);
  nt->set_inner_cache_type(trans->inner_cache_type);
  nt->set_inner_transient(trans->inner_transient);
  nt->set_inner_read_allocate(trans->inner_read_allocate);
  nt->set_inner_write_allocate(trans->inner_write_allocate);
  nt->set_innershareable(trans->innershareable);
  nt->set_outershareable(trans->outershareable);
  nt->set_domain(trans->domain);
  nt->set_level(trans->level);
  nt->set_blocksize(trans->blocksize);
  nt->set_unpredictable(trans->unpredictable);
  nt->set_levels(trans->levels);

  nt->set_base_address(trans->base_address);
  nt->set_page_offset_mask(trans->page_offset_mask);

  for (int i = 0; i < trans->levels; i++) {
     scaffold_SAPI::A64Descriptor *desc = nt->add_descriptors();

     desc->set_address(trans->descriptors[i].address);
     desc->set_big_endian(trans->descriptors[i].big_endian);
     desc->set_level(trans->descriptors[i].level);
     desc->set_format(trans->descriptors[i].format);
     desc->set_nstable(trans->descriptors[i].NSTable);
     desc->set_aptable(trans->descriptors[i].APTable);
     desc->set_uxntable(trans->descriptors[i].UXNTable);
     desc->set_pxntable(trans->descriptors[i].PXNTable);
     desc->set_contiguous(trans->descriptors[i].Contiguous);
     desc->set_ng(trans->descriptors[i].nG);
     desc->set_af(trans->descriptors[i].AF);
     desc->set_sh(trans->descriptors[i].SH);
     desc->set_ap(trans->descriptors[i].AP);
     desc->set_ns(trans->descriptors[i].NS);
     desc->set_attrindx(trans->descriptors[i].AttrIndx);
     desc->set_page_offset_mask(trans->descriptors[i].PageOffsetMask());
     desc->set_output_address(trans->descriptors[i].OutputAddress());
     desc->set_table_address(trans->descriptors[i].TableAddress());
     desc->set_dval(trans->descriptors[i].Value());

     unsigned char tbuf[8];
     trans->descriptors[i].MemValue(tbuf);
     desc->set_dbuf((void *) tbuf, 8);
  }
  
#ifdef DEBUG_TRANSLATIONS
  printf("[SimTrace::RecordTranslation] recording new translation (id: %d), mapped la/pa: 0x%llx/0x%llx...\n",
         trans_index,trans->LA,trans->PA);
#endif

  return trans_index;
}

void SimTrace::RecordPacketWriteBack(scaffold_SAPI::Packet *pkt, State *cpu, Packet *packet) {
  scaffold_SAPI::WriteBack *wops = pkt->mutable_write_ops();

  unsigned long long next_pc = 0;
  unsigned int next_pstate = 0;
  unsigned int next_fpsr = 0;
  
  try {
    next_pc = packet->NextPC.Value();
    next_pstate = packet->NextPstate.Value();
    next_fpsr = packet->Next_FPSR.Value();
  } catch(...) {
    printf("OOPS! 'next' PC,pstate not set???\n");
    next_pc = 0;
    next_pstate = 0;
    wops->set_nextpc(next_pc);
    wops->set_nextpstate(next_pstate);
    //return;
  }

  wops->set_nextpc(next_pc);
  wops->set_nextpstate(next_pstate);
  wops->set_nextfpsr(next_fpsr);
  
  for (vector<struct RegDep>::iterator i = packet->destRegDep.begin(); i != packet->destRegDep.end(); i++) {
     int reg_type = (*i).TYPE();
     int reg_id = (*i).ID();
     unsigned long long rval = (*i).RVAL();
     unsigned long long rval_hi = (*i).RVAL_HI();

     char tbuf[128];
     string rname;

     switch(reg_type) {
       case DEP_GP:     {
                        sprintf(tbuf,"GP[%d]",reg_id); 
                        rname = tbuf; 
                        scaffold_SAPI::RegisterUpdate* reg = wops->add_destregsgp();
                        reg->set_key(rname);
                        reg->set_val(rval);
                        }
                        break;
			
       case DEP_SP:     // stack pointer...
                        {
                        sprintf(tbuf,"SP_EL%d",reg_id); 
                        rname = tbuf; 
                        scaffold_SAPI::RegisterUpdate* reg = wops->add_destregsgp();
                        reg->set_key(rname);
                        reg->set_val(rval);
                        }
                        break;
			
       case DEP_FP_SP:  // all float reg updates recorded as simd reg updates...
       case DEP_FP_DP:  
       case DEP_ASIMD:  {
                        scaffold_SAPI::SimdReg* reg = wops->add_destregsasimd();
                        reg->set_key(reg_id);
                        reg->set_rval_lo(rval);
                        reg->set_rval_hi(rval_hi);
                        }
                        break;
			
       case DEP_SPR:    {
                        rname = cpu->SystemRegisterName(reg_id); 
                        scaffold_SAPI::RegisterUpdate* reg = wops->add_destregssys();
                        reg->set_key(rname);
                        reg->set_val(rval);
                        }
                        break;
			
       case DEP_PSTATE: {
                        rname = "PSTATE";                            
                        scaffold_SAPI::RegisterUpdate* reg = wops->add_destregssys();
                        reg->set_key(rname);
                        reg->set_val(rval);
                        }
                        break;
		      
       default: break;
     }
  }

  for (vector<XRegister>::iterator i = packet->destXreg.begin(); i != packet->destXreg.end(); i++) {
     unsigned long long rval = (*i).Value();
     unsigned long long rval_hi = (*i).ValueHi();
     int rid = (*i).ID();
     int type = (*i).Type();
     char tbuf[128];
     std::string rname;
     switch(type) {
       case XRegister::IS_GPR:    {
                                   sprintf(tbuf,"GP[%d]",rid); 
			           rname = tbuf; 
                                   scaffold_SAPI::RegisterUpdate* reg = wops->add_destregsgp();
                                   reg->set_key(rname);
                                   reg->set_val(rval);
                                  }
                                  break;
       case XRegister::IS_SP:     {
                                   sprintf(tbuf,"SP_EL%d",rid); 
                                   rname = tbuf; 
                                   scaffold_SAPI::RegisterUpdate* reg = wops->add_destregsgp();
                                   reg->set_key(rname);
                                   reg->set_val(rval);
                                  }
                                  break;    
       case XRegister::IS_FLOAT:  {
                                   // record all float reg accesses as simd reg accessess...
	                           scaffold_SAPI::SimdReg* reg = wops->add_destregsasimd();
                                   reg->set_key((*i).ID());
                                   reg->set_rval_lo(rval);
                                   reg->set_rval_hi(rval_hi);
                                  }
                                  break;		
       case XRegister::IS_SPR:    {
                                   rname = (*i).Name();    
                                   scaffold_SAPI::RegisterUpdate* reg = wops->add_destregssys();
                                   reg->set_key(rname);
                                   reg->set_val(rval);
                                  }
                                  break;	
       case XRegister::IS_PSTATE: {
                                   rname = (*i).Name();                            
                                   scaffold_SAPI::RegisterUpdate* reg = wops->add_destregssys();
                                   reg->set_key(rname);
                                   reg->set_val(rval);
                                  }
                                  break;
       default: break;
     }
  }
}

void SimTrace::RecordPacketRetire(scaffold_SAPI::Packet *pkt, Packet *packet) {
  //scaffold_SAPI::Retire *rte = pkt->mutable_retire(); //<---nothing here yet...
}

void SimTrace::RecordPacketException(scaffold_SAPI::Packet *pkt, Packet *packet) {
  scaffold_SAPI::Exception *exc = pkt->mutable_excep();

  exc->set_exception_class(packet->exceptionClass());
  exc->set_exception_type(packet->exceptionType());
  exc->set_exception_subtype(packet->exceptionSubtype());
  exc->set_exception_imm(packet->exceptionImmediate());
}

void SimTrace::RecordPacket(scaffold_SAPI::Packet *pkt, State *cpu, Memory *mem, Packet *packet, unsigned long long clock) {
  pkt->set_clock(clock);
  pkt->set_pc(packet->PC.Value());
  pkt->set_pstate(packet->Pstate.Value());
  pkt->set_goal(packet->Goal);
  pkt->set_state(packet->State);
  pkt->set_disassembly(packet->Disassembly());
  pkt->set_instr_group(packet->instrGroup());

  if (packet->State >= FETCH_STATE)          RecordPacketFetch(pkt,packet);
  if (packet->State >= DECODE_STATE)         RecordPacketDecode(pkt,packet);
  if (packet->State >= FETCH_OPERANDS_STATE) RecordPacketFetchOperands(pkt,cpu,packet);
  if (packet->State >= EXECUTE_STATE)        RecordPacketExecute(pkt,packet);
  if (packet->State >= MEMORY_ACCESS_STATE)  RecordPacketMemoryAccesses(pkt,cpu,mem,packet);
  if (packet->State >= WRITEBACK_STATE)      RecordPacketWriteBack(pkt,cpu,packet);
  if (packet->State >= RETIRE_STATE)         RecordPacketRetire(pkt,packet);

  if (packet->exception_class != NO_SIM_EXCEPTION) RecordPacketException(pkt,packet);

  if (cpu->IsWaiting()) pkt->set_waiting(true);
}

void SimTrace::RecordPacket(State *cpu, Memory *mem, Packet *packet, unsigned long long clock) {
  RecordPacket(pkt,cpu,mem,packet,clock);
}

void SimTrace::RecordCpuUpdates(State *cpu, int _cpuid) {
  State diffs;

  bool have_prev_cpu = ((int) prevCpu.size()) > _cpuid;

  //printf("[SimTrace::RecordCpuUpdates] (input) cpu: %d (internal) cpu: %d have-prev-cpu? %d\n",_cpuid,cpuid,have_prev_cpu);

  if (have_prev_cpu) {
    diffCpuBase(diffs,cpu);
    diffCpuConfig(diffs,cpu);
    diffCpuProcID(diffs,cpu);
    diffCpuFPU(diffs,cpu);
    diffCpuDebug(diffs,cpu);
    diffCpuExceptionState(diffs,cpu);
    diffCpuVMSA(diffs,cpu);
    diffCpuResetMgmt(diffs,cpu);
    diffCpuThreadState(diffs,cpu);
    diffCpuGICState(diffs,cpu);
    diffCpuTimerState(diffs,cpu);
    RecordCpuState(&diffs);
  } else {
    RecordCpuState(cpu);
    prevCpu.push_back(*cpu);
  }
}


