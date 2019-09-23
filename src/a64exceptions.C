#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "a64sim.h"
#include "a64_instr_enums.h"
#include "a64_exceptions.h"

//#define DEBUG_EXCEPTIONS 1

//==========================================================================================
// ExceptionEnables - user control over which exceptions are enabled/disabled...
//==========================================================================================

ExceptionEnables::ExceptionEnables(ExceptionEnables &_src) {
  for (unordered_map<int,bool>::iterator i = _src.enables.begin(); i != _src.enables.end(); i++) {
    enables[i->first] = i->second;
  }
}

int ExceptionEnables::Index(int _sim_excep_type, int _main_excep, int _excep_subtype) {
  int index = (_sim_excep_type<<16) | (_main_excep<<8) | _excep_subtype;
#ifdef DEBUG_EXCEPTIONS
  printf("[ExceptionEnables::Index] _sim_excep_type = %d _main_excep = %d _excep_subtype = %d ===>index: %d\n",
         _sim_excep_type, _main_excep, _excep_subtype, index);
#endif
  return index;
}

void ExceptionEnables::Add(bool _is_enabled, int _sim_excep_type, int _main_excep, int _excep_subtype) {
  //printf("[Add] enabled? %d\n",_is_enabled);
  enables[Index(_sim_excep_type,_main_excep,_excep_subtype)] = _is_enabled;
}

bool ExceptionEnables::Enabled(int _sim_excep_type, int _main_excep, int _excep_subtype) {
  int excep_index = Index(_sim_excep_type,_main_excep,_excep_subtype);
 
  if (enables.find(excep_index) == enables.end()) {
#ifdef DEBUG_EXCEPTIONS
    printf("[ExceptionEnables::Enabled] enabled? Index %d NOT found?\n",excep_index);
#endif
    throw INTERNAL_ERROR;
  }
  
  bool enabled = enables[excep_index];
  //printf("[ExceptionEnables::Enabled] enabled? %d\n",enabled);
  return enabled;
}


//==========================================================================================
// simulator control over exceptions...
//==========================================================================================

bool Control::allowException() {
  bool rcode = exception_enables->Enabled(ARCH_EXCEPTION,packet->exception_type); // no exception sub-type yet...
#ifdef DEBUG_EXCEPTIONS
  printf("[Control::allowException] exception %d allowed? %s\n",packet->exception_type,(rcode ? "yes" : "no"));
#endif
  return rcode;
}

void Control::handleException(SIM_EXCEPTION_CLASS eclass) {
#ifdef DEBUG_EXCEPTIONS
  printf("[Control::handleException] eclass: %d\n",eclass);
#endif
  // handle exception if same is enabled (allowed), else defer to caller...

  packet->exception_class = eclass;
#ifdef DEBUG_EXCEPTIONS
  std::cout << "  class/type/sub-type/imm: " << packet->exceptionClass() << "/"
  	    << packet->exceptionType() << "/" << packet->exceptionSubtype() << "/"
  	    << packet->exceptionImmediate() << std::endl;
#endif  
  if (eclass == INTERNAL_ERROR) throw INTERNAL_ERROR; // simulator internal error...

  if (allowException()) {
#ifdef DEBUG_EXCEPTIONS
     printf("[Control::handleException] process the architectual exception...\n");
#endif
     processException(); 
#ifdef DEBUG_EXCEPTIONS
     printf("[Control::handleException] exception processed...\n");         
#endif
  } else if (packet->Goal == FOR_TEST) {
     // some sort of test creation going on, defer to test harness... 
    if (sim_monitor) sim_monitor->Abort(cpu->GetID());
     throw GENERATION_ERROR;
  } else {
     // how did we get here?...
     throw INTERNAL_ERROR;
  }

#ifdef DEBUG_EXCEPTIONS
  printf("[Control::handleException] exited.\n");
#endif
}

void Control::RaiseIRQ() {
  if (packet->Pstate.I() == 1) {
    // IRQ masked off at current privilege level...
  } else {
    packet->recordExceptionCondition(IRQ);
    throw ARCH_EXCEPTION;
  }
}

void Control::RaiseFIQ() {
  if (packet->Pstate.F() == 1) {
    // FIQ masked off at current privilege level...
  } else {
    packet->recordExceptionCondition(FIQ);
    throw ARCH_EXCEPTION;
  }
}

void Control::processException() {
#ifdef DEBUG_EXCEPTIONS
  printf("[Control::processException] entered, type: %d\n",packet->exception_type);
#endif
  
  // set error condition codes, save process state, goto new exception level...

  int exception_type=EXCEPTION_Uncategorized; // exception type as recorded in syndrome

  switch(packet->exception_type) {
    case SOFTWARE_STEP:                    exception_type = EXCEPTION_SoftwareStep;       break;
    case MISALIGNED_PC:                    exception_type = EXCEPTION_PCAlignment;        break;
    case INSTRUCTION_ABORT:                exception_type = EXCEPTION_InstructionAbort;   break;
    case BREAKPOINT:                       exception_type = EXCEPTION_SoftwareBreakpoint; break;
    case DEBUG_BREAKPOINT:                 exception_type = EXCEPTION_Breakpoint;         break;
    case ILLEGAL_EXECUTION_STATE:          exception_type = EXCEPTION_IllegalState;       break;
    case UNDEFINED_INSTRUCTION:            exception_type = EXCEPTION_Uncategorized;      break;
    case SMC_UNDEFINED:                    exception_type = EXCEPTION_Uncategorized;      break;
    case EXCEPTIONS_TO_EL3:                exception_type = EXCEPTION_Uncategorized;      break;
    case STACK_POINTER_ALIGNMENT:          exception_type = EXCEPTION_SPAlignment;        break;
    case DATA_ABORT:                       exception_type = EXCEPTION_DataAbort;          break;
    case DEBUG_WATCHPOINT:                 exception_type = EXCEPTION_Watchpoint;         break;
    case ADDRESS_SPACE_ERROR:              exception_type = EXCEPTION_Uncategorized;      break;

    case IRQ:                              exception_type = EXCEPTION_IRQ;                break;
    case FIQ:                              exception_type = EXCEPTION_FIQ;                break;

    case FLOATING_POINT_EXCEPTIONS:
    case EXCEPTION_GENERATING_INSTRUCTION: // float, SVC or SMC type specified from subtype...
                                           exception_type = packet->exception_subtype;    break;

    case TRAP:                             exception_type = EXCEPTION_SystemRegisterTrap; break;
    default: break;
  }

  switch(packet->exception_type) {
    case SOFTWARE_STEP: // 4961
    case MISALIGNED_PC: // 4957
    case INSTRUCTION_ABORT: // 4956
    case BREAKPOINT: // 4960 - BRK softwarebreakpoint
    case DEBUG_BREAKPOINT: // 4960 - debug breakpoint
    case ILLEGAL_EXECUTION_STATE: // 4966
    case UNDEFINED_INSTRUCTION: // 4966
    case SMC_UNDEFINED: // 4966
    case EXCEPTIONS_TO_EL3:
    case FLOATING_POINT_EXCEPTIONS: // including FP/ASID enable? access? in CPACR_EL1??? - 4964 4968
    case STACK_POINTER_ALIGNMENT: // 4957
    case DATA_ABORT: // 4957
    case DEBUG_WATCHPOINT: // 4961
    case ADDRESS_SPACE_ERROR: // MADE THIS ONE UP
    case EXCEPTION_GENERATING_INSTRUCTION:
    case TRAP:

    case IRQ:
    case FIQ:
              {
		//std::cout << "Packet:\n" << (*packet) << std::endl;
#ifdef DEBUG_EXCEPTIONS
		if (packet->exception_type==EXCEPTION_GENERATING_INSTRUCTION)
		  printf("[Control::processException] EXCEPTION_GENERATING_INSTRUCTION...\n");
		else 
		  printf("[Control::processException] ASYNCHRONOUS EXCEPTION, IE, INTERRUPT...\n");
#endif
	       
               SSAdvance();
	       DirectRecordSPRaccess(SPR_ID_AA64PFR0_EL1,cpu->ID_AA64PFR0_EL1.Value());
	       DirectRecordSPRaccess(SPR_ID_HCR_EL2,cpu->HCR_EL2.Value());

               bool route_to_el2 = cpu->HaveEL(EL2) && !cpu->IsSecure() && (packet->Pstate.EL()==0 || packet->Pstate.EL()==1) && (cpu->HCR_EL2.TGE() == 1);

#ifdef DEBUG_EXCEPTIONS
               printf("[Control::processException] route to EL2? %d\n",route_to_el2);
#endif
	       
               unsigned long long preferred_exception_return = (packet->exception_type==EXCEPTION_GENERATING_INSTRUCTION) ? NextInstrAddr() : packet->PC.Value(); 
               unsigned long long vector_offset = 0;

#ifdef DEBUG_EXCEPTIONS
               printf("[Control::processException] exception record...\n");
#endif
               ExceptionRecord exception(exception_type); // p 4965

	       exception.SetSyndrome(packet->exception_imm); //<---no syndrone for interrupt!

#ifdef DEBUG_EXCEPTIONS
               printf("[Control::processException] taking interrupt from EL%d...\n",packet->Pstate.EL());
	       fflush(stdout);
#endif

               if (packet->Pstate.EL() > EL1)
		 TakeException(packet->Pstate.EL(),exception,preferred_exception_return,vector_offset);
	       else if (route_to_el2)
		 TakeException(EL2,exception,preferred_exception_return,vector_offset);
               else
		 TakeException(EL1,exception,preferred_exception_return,vector_offset);
              }
              break;

    default: throw INTERNAL_ERROR; 
             break;
  }
#ifdef DEBUG_EXCEPTIONS
  printf("[Control::processException] exited.\n");
#endif
}

unsigned long long Control::VBAR(int EL) {
  unsigned long long r;
  bool vbar_not_set = false;

  switch(EL) {
    case EL1: vbar_not_set = cpu->VBAR_EL1.IsSet();
              r = cpu->VBAR_EL1.Value();
	      DirectRecordSPRaccess(SPR_VBAR_EL1,cpu->VBAR_EL1.Value());
	      break;
    case EL2: vbar_not_set = cpu->VBAR_EL2.IsSet();
              r = cpu->VBAR_EL2.Value();
	      DirectRecordSPRaccess(SPR_VBAR_EL2,cpu->VBAR_EL2.Value());
	      break;
    case EL3: vbar_not_set = cpu->VBAR_EL3.IsSet();
              r = cpu->VBAR_EL3.Value();
	      DirectRecordSPRaccess(SPR_VBAR_EL3,cpu->VBAR_EL3.Value());
	      break;
    default: throw INTERNAL_ERROR; break;
  }

  if (!vbar_not_set) {
    throw GENERATION_ERROR;
  }

  return r;
}

void Control::SetELR(int target_el,unsigned long long return_addr) {
  switch(target_el) {
    case EL1: cpu->ELR_EL1.Value(return_addr);
              DirectRecordSPRaccess(SPR_ELR_EL1,return_addr,true);
              break;
    case EL2: cpu->ELR_EL2.Value(return_addr);
              DirectRecordSPRaccess(SPR_ELR_EL2,return_addr,true);
              break;
    case EL3: cpu->ELR_EL3.Value(return_addr);
              DirectRecordSPRaccess(SPR_ELR_EL3,return_addr,true);
              break;
    default: throw INTERNAL_ERROR; break;
  }
}
 
unsigned long long Control::ELR(int EL) {
  unsigned long long return_addr;

  switch(EL) {
    case EL1: return_addr = cpu->ELR_EL1.Value();
              DirectRecordSPRaccess(SPR_ELR_EL1,return_addr);
              break;
    case EL2: return_addr = cpu->ELR_EL2.Value();
              DirectRecordSPRaccess(SPR_ELR_EL2,return_addr);
              break;
    case EL3: return_addr = cpu->ELR_EL3.Value();
              DirectRecordSPRaccess(SPR_ELR_EL3,return_addr);
              break;
    default: throw INTERNAL_ERROR; break;
  }

  return return_addr;
}
 
void Control::SetESR(unsigned int ec,unsigned int il,unsigned int iss) { //p1834
  unsigned long long syndrome = (ec << 26) | (il << 25) | iss;
 
  switch(packet->Pstate.EL()) {
    case EL0:
    case EL1: cpu->ESR_EL1.Value(syndrome);
              DirectRecordSPRaccess(SPR_ESR_EL1,syndrome,true);
              break;
    case EL2: cpu->ESR_EL2.Value(syndrome);
              DirectRecordSPRaccess(SPR_ESR_EL2,syndrome,true);
              break;
    case EL3: cpu->ESR_EL3.Value(syndrome);
              DirectRecordSPRaccess(SPR_ESR_EL3,syndrome,true);
              break;
    default: throw INTERNAL_ERROR; break;
  }
}

void Control::SetFAR(int target_el,unsigned long long address) {
  switch(target_el) {
    case EL1: cpu->FAR_EL1.Value(address);
              DirectRecordSPRaccess(SPR_FAR_EL1,address,true);
              break;
    case EL2: cpu->FAR_EL2.Value(address);
              DirectRecordSPRaccess(SPR_FAR_EL2,address,true);
              break;
    case EL3: cpu->FAR_EL3.Value(address);
              DirectRecordSPRaccess(SPR_FAR_EL3,address,true);
              break;
    default: throw INTERNAL_ERROR; break;
  }
}

void Control::SetSPSR(int target_el,unsigned int rval) {
  switch(target_el) {
    case EL1: cpu->SPSR_EL1.Value(rval);
              DirectRecordSPRaccess(SPR_SPSR_EL1,rval,true);
              break;
    case EL2: cpu->SPSR_EL2.Value(rval);
              DirectRecordSPRaccess(SPR_SPSR_EL2,rval,true);
              break;
    case EL3: cpu->SPSR_EL3.Value(rval);
              DirectRecordSPRaccess(SPR_SPSR_EL3,rval,true);
              break;
    default: throw INTERNAL_ERROR; break;
  }
}

unsigned int Control::SPSRval(int target_el) {
  unsigned int spsr_val;

  switch(target_el) {
    case EL1: spsr_val = cpu->SPSR_EL1.Value();
              DirectRecordSPRaccess(SPR_SPSR_EL1,spsr_val);
              break;
    case EL2: spsr_val = cpu->SPSR_EL2.Value();
              DirectRecordSPRaccess(SPR_SPSR_EL2,spsr_val);
              break;
    case EL3: spsr_val = cpu->SPSR_EL3.Value();
              DirectRecordSPRaccess(SPR_SPSR_EL3,spsr_val);
              break;
    default: throw INTERNAL_ERROR; break;
  }

  return spsr_val;
}

void Control::TakeException(unsigned int EL,ExceptionRecord exception,unsigned long long preferred_exception_return,
                            unsigned long long vector_offset) {

#ifdef DEBUG_EXCEPTIONS
  printf("[Control::TakeException] entered, exception EL: %d current EL: %d...\n",EL,packet->Pstate.EL());
#endif
  
  if (!cpu->HaveEL(EL) || EL < packet->Pstate.EL()) 
     throw INTERNAL_ERROR;

  // page 4965:

  // from_32 = UsingAArch32();
  // if from_32 then MaybeZeroRegisterUppers(EL);

  bool lower_32 = false;
  bool from_32  = false;

#ifdef DEBUG_EXCEPTIONS
  printf("[Control::TakeException] exception level checks out...\n");
#endif
  
  if (EL > packet->Pstate.EL()) {
/*
    if (EL == EL3) {

      if (!IsSecure(0) && HaveEL(EL2))
	lower_32 = ELUsingAARCH32(EL2);
      else
	lower_32 = ELUsingAARCH32(EL1);
    } else {
	lower_32 = ELUsingAARCH32(EL1 - 1);
    }
*/
    vector_offset += lower_32 ? 0x600 : 0x400;
  } else if (packet->Pstate.SP() == 1) {
    vector_offset += 0x200;
  }

  if (exception.Type()==EXCEPTION_IRQ)
    vector_offset += 0x80;
  else if (exception.Type()==EXCEPTION_FIQ)
    vector_offset += 0x100;
  
#ifdef DEBUG_EXCEPTIONS
  printf("[Control::TakeException] have vector offset 0x%llx...\n",vector_offset);
#endif
  
  SetSPSR(EL,packet->Pstate.ValueAsSPSR());

  //printf("[Control::TakeException] return state recorded...\n");
  
  SetELR(EL,preferred_exception_return);

  //printf("[Control::TakeException] return address recorded...\n");
  
  packet->Pstate.EL(EL);
  packet->Pstate.nRW(0);
  packet->Pstate.SP(1);
  packet->Pstate.D(1);  

  if (exception.Type()==EXCEPTION_IRQ) {
#ifdef DEBUG_EXCEPTIONS
    packet->Pstate.A(1); //
    packet->Pstate.I(1); // mask off all interrupts...
    packet->Pstate.F(1); //
    printf("[Control::TakeException] IRQ...\n");
#endif    
  } else if (exception.Type()==EXCEPTION_FIQ) {
#ifdef DEBUG_EXCEPTIONS
    packet->Pstate.A(1); //
    packet->Pstate.I(1); // mask off all interrupts...
    packet->Pstate.F(1); //
    printf("[Control::TakeException] FIQ...\n");
#endif    
  } else {
    ReportException(exception,EL); //<---we think this needs to be here to allow ESR for exception EL to be set
  }

#ifdef DEBUG_EXCEPTIONS
  printf("[Control::TakeException] exception reported...\n");
#endif
  
  packet->Pstate.SS(0);
  packet->Pstate.NZCV(0xf0000000);
  packet->Pstate.IL(0);

  if (from_32) {
    //packet->Pstate.IT(0); <<<always zero
    packet->Pstate.J(0);
    packet->Pstate.T(0);
  }

  // did all this work to update Pstate for exception, but the 'next' pstate is what the cpu state is updated from...

  packet->NextPstate = packet->Pstate;

#ifdef DEBUG_EXCEPTIONS
  printf("[Control::TakeException] branching to handler (packet pstate: 0x%x next pstate: 0x%x)...\n",packet->Pstate.Value(),packet->NextPstate.Value());
#endif
  
  BranchTo(VBAR(packet->Pstate.EL()) + vector_offset,BranchType_EXCEPTION,(lower_32==true ? 32 : 64));

#ifdef DEBUG_EXCEPTIONS
  printf("[Control::TakeException] exited.\n");
#endif
}

// p 5118
void Control::BranchTo(unsigned long long target,BranchType branch_type,int N) {
#ifdef DEBUG_EXCEPTIONS
   printf("[Control::BranchTo] target: 0x%llx...\n",target);
#endif
   
   //HintBranch(branch_type);

   if (N==32) {
     if (!cpu->UsingAArch32())
       throw INTERNAL_ERROR;
     packet->NextPC.Value( target );
     return;
   }

   if (cpu->UsingAArch32()) throw INTERNAL_ERROR;

   unsigned long long upper_bits_mask = ~(0xffull<<56);

   // remove the tag bits from a tagged target...

   switch(packet->Pstate.EL()) { //<---after updating pstate.EL, ie, pstate.el is target el
     case 0:
     case 1: {
              // see p1954
              unsigned int bit55 = (target>>55) & 1;
              if (bit55 && (cpu->TCR_EL1.TBI1() == 1) )
                target = (target & upper_bits_mask) | 0xffull<<56;
              if (!bit55 && (cpu->TCR_EL1.TBI0() == 1) )
                target = target & upper_bits_mask;
	      DirectRecordSPRaccess(SPR_TCR_EL1,cpu->TCR_EL1.Value());
             }
             break;
     case 2: if (cpu->TCR_EL2.TBI() == 1)
               target = target & upper_bits_mask;
	      DirectRecordSPRaccess(SPR_TCR_EL2,cpu->TCR_EL2.Value());
              break;
     case 3: if (cpu->TCR_EL3.TBI() == 1)
               target = target & upper_bits_mask;
	      DirectRecordSPRaccess(SPR_TCR_EL3,cpu->TCR_EL3.Value());
              break;
     default: throw INTERNAL_ERROR; break;
   } 

#ifdef DEBUG_EXCEPTIONS
   printf("[Control::BranchTo] next PC: 0x%llx...\n",target);
#endif
   
   packet->NextPC.Value( target );

#ifdef DEBUG_EXCEPTIONS
   printf("[Control::BranchTo] exited.\n");
#endif
}

int Control::InstrLength() {
   return cpu->Pstate.ThumbMode() ? 16 : 32;
}

// p4962...
void Control::ExceptionClass(unsigned int &ec,unsigned int &il,unsigned int type,unsigned int target_el) {
  //printf("[Control::ExceptionClass] entered...\n");

  il = (InstrLength()==32) ? 1 : 0;
  bool from_32 = cpu->UsingAArch32();

  if (!(from_32 || il == 1)) {
     throw INTERNAL_ERROR; // AArch64 instructions are always 32 bits...
  }

  //printf("[Control::ExceptionClass] instruction length okay...\n");

  ec = type;

  switch((int) type) {
    case EXCEPTION_Uncategorized:      il = 1;                                     break;
    case EXCEPTION_CP15RTTrap:                 if (!from_32) throw INTERNAL_ERROR; break;
    case EXCEPTION_CP15RRTrap:                 if (!from_32) throw INTERNAL_ERROR; break;
    case EXCEPTION_CP14RTTrap:                 if (!from_32) throw INTERNAL_ERROR; break;
    case EXCEPTION_CP14DTTrap:                 if (!from_32) throw INTERNAL_ERROR; break;
    case EXCEPTION_CP14RRTTrap:                if (!from_32) throw INTERNAL_ERROR; break;
    case EXCEPTION_IllegalState:       il = 1;                                     break;
    case EXCEPTION_SystemRegisterTrap:         if (!from_32) throw INTERNAL_ERROR; break;
    case EXCEPTION_InstructionAbort:   il = 1;                                     break;
    case EXCEPTION_PCAlignment:        il = 1;                                     break;
    case EXCEPTION_SPAlignment:        il = 1; if (!from_32) throw INTERNAL_ERROR; break;
    case EXCEPTION_SError:             il = 1;                                     break;
    case EXCEPTION_Breakpoint:         il = 1;                                     break;
    case EXCEPTION_SoftwareStep:       il = 1;                                     break;
    case EXCEPTION_Watchpoint:         il = 1;                                     break;
    case EXCEPTION_SoftwareBreakpoint: il = 1;                                     break;
    case EXCEPTION_VectorCatch:                if (!from_32) throw INTERNAL_ERROR; break;

    default: break;
  }

  //printf("[Control::ExceptionClass] type okay, able to set il...\n");

  switch((int) type) {
    case EXCEPTION_InstructionAbort:
    case EXCEPTION_DataAbort:
    case EXCEPTION_Breakpoint:
    case EXCEPTION_SoftwareStep:
    case EXCEPTION_Watchpoint:   if (target_el == packet->Pstate.EL()) ec += 1; break;
    default: break;
  }

  switch((int) type) {
    case EXCEPTION_SupervisorCall:
    case EXCEPTION_HypervisorCall:
    case EXCEPTION_MonitorCall:
    case EXCEPTION_FPTrappedException: 
    case EXCEPTION_SoftwareBreakpoint: if (!from_32) ec += 4; break;
    default: break;
  }

  //printf("[Control::ExceptionClass] exited.\n");
}

// p5242...

void Control::ReportException(ExceptionRecord exception, int target_el) {
  unsigned int ec,il;
  ExceptionClass(ec,il,exception.Type(),target_el);

  SetESR(ec,il,exception.Syndrome());

  switch(exception.Type()) {
    case EXCEPTION_InstructionAbort:
    case EXCEPTION_PCAlignment:
    case EXCEPTION_DataAbort:
    case EXCEPTION_Watchpoint: SetFAR(target_el,exception.Vaddress()); break;
    default: break; // FAR is unknown...
  }

//  if (target_el == EL2 && exception.ipavalid) {
//    HPFAR_EL2<39:2> = exception.ipaddress<47:12>;
//  }
}

//==========================================================================================
// methods related to A64 exceptions, return from exceptions...
//==========================================================================================

// see page 4967
// page 5083 - handling exceptions

void Control::SystemRegisterTrap(unsigned target_el,unsigned op0, unsigned op2, unsigned op1, 
                                 unsigned crn, unsigned rt, unsigned crm, unsigned dir) {
  // ASSERT target EL >= current EL...
  if (target_el < packet->Pstate.EL()) {
    throw INTERNAL_ERROR;
  }

  unsigned long long preferred_return_address = packet->PC.Value();
  unsigned long long vector_offset = 0;

  ExceptionRecord exception(EXCEPTION_SystemRegisterTrap); // p 4965

  exception.SetSyndrome( (op0<<20) | (op2<<17) | (op1<<14) | (crn<<10) | (rt<<5) | (crm<<1) | dir );

  if (target_el == EL1 && cpu->HaveEL(EL2) && !cpu->IsSecure() && cpu->HCR_EL2.TGE() == 1)
     TakeException(EL2,exception,preferred_return_address,vector_offset);
  else
     TakeException(target_el,exception,preferred_return_address,vector_offset);
}

unsigned long long Control::NextInstrAddr() {
  return packet->PC.Value() + 4;
}

void Control::SSAdvance() {
  bool step_enabled = cpu->MDSCR_EL1.SS()==1;
  bool active_not_pending = step_enabled && packet->Pstate.SS()==1;

  //DirectRecordSPRaccess(SPR_MDSCR_EL1,cpu->MDSCR_EL1.Value());

  if (active_not_pending) packet->Pstate.SS(0);
}

//#define FOR_UBOOT 1

// page 4965
void Control::CallSupervisor(unsigned int imm) {
  //printf("[Control::CallSupervisor] imm: %d\n",imm);

#ifdef FOR_UBOOT
  switch((int) imm) {
    case 0:  // puts. get pointer from X0, read memory (make sure its defined), make sure string is null terminated, print it...
             {
             unsigned long long string_addr = cpu->GP[0].Value();  
             unsigned char tbuf[1024];
             for (int i = 0; i < 1024; i++) {
                memory->ReadMemory(cpu,packet,sim_monitor,string_addr + i,DATA,cpu->Privileged(),1,&tbuf[i],false);
                if (tbuf[i] == 0)
                  break;
	     }
             printf("[CONSOLE] %s\n",tbuf);
             }
             return;
	     break;
    default: // fall thru on any other immediate value...
             break;
  }
#endif

  packet->recordExceptionCondition(EXCEPTION_GENERATING_INSTRUCTION,EXCEPTION_SupervisorCall,imm);
  handleException(ARCH_EXCEPTION);

  //printf("[Control::CallSupervisor] exited.\n");
}

void Control::CallSecureMonitor(unsigned int imm) {
  packet->recordExceptionCondition(EXCEPTION_GENERATING_INSTRUCTION,EXCEPTION_MonitorCall,imm);
  handleException(ARCH_EXCEPTION);
}

void Control::SetPSTATEFromSPSR(unsigned int spsr_val) {
  SPSR spsr;

  spsr.Value(spsr_val);

  packet->NextPstate.Value(spsr.Value());

  //printf("[Control::SetPSTATEFromSPSR] spsr_val: 0x%x spsr: 0x%x new pstate: 0x%x\n",spsr_val,spsr.Value(),packet->NextPstate.Value());
}

unsigned int Control::GetPSRFromPSTATE() {
  return packet->Pstate.ValueAsSPSR();
}

unsigned int Control::ProcessorID() {
  return cpu->MPIDR_EL1.Aff0();
}

void Control::EventRegisterSet() {
  // p 5127 - set processors local event register...
}

// ERET - p474
// ExceptionReturn - p4981
void Control::ExceptionReturn() {
  
  unsigned long long new_pc = ELR(packet->Pstate.EL()); // p4978
  unsigned int spsr_val = SPSRval(packet->Pstate.EL()); // p5119

#ifdef DEBUG_EXCEPTIONS
  printf("[Control::ExceptionReturn] EL: %d --> new PC: 0x%llx SPSR: 0x%x\n",packet->Pstate.EL(),new_pc,spsr_val);
#endif
  
  SetPSTATEFromSPSR(spsr_val);
  ClearExclusiveMonitor();
  EventRegisterSet();

  if ( (spsr_val >>4) & 1 ) {
    // attempt to change to AArch32...hmmm...
  }

  if (packet->Pstate.nRW() == 1)
    BranchTo(new_pc & 0xffffffff,BranchType_UNKNOWN,32);
  else
    BranchTo(new_pc,BranchType_ERET,64);
}




