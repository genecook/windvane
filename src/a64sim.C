#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "a64sim.h"
#include "a64_instr_enums.h"

//==========================================================================================
// operator overloaded from a64sim.h... 
//==========================================================================================

unsigned int operator<<( InstructionField &instr_field, unsigned int sv) { return instr_field.Value() << sv; }
unsigned int operator<<( InstructionField &instr_field, int sv) { return instr_field.Value() << sv; }
unsigned int operator|( unsigned int lhs,InstructionField &instr_field) { return lhs | instr_field.Value(); }

//==========================================================================================
// stream methods... 
//==========================================================================================

ostream& operator<< (ostream &os, InstructionField &fld) {
  if (fld.is_set) {
    os << "0x" << std::hex << fld.fval << std::dec;
  } else {
    os << "?";
  }

  return os;
}

ostream& operator<< (std::ostream &os, MemoryAccess &ma) {
  os << "  MemoryAccess\n";
  os << "      address = 0x" << std::hex << ma.address << std::dec << "\n";
  os << "      # of bytes accessed: " << ma.size << "\n";
  string _type;
  switch(ma.type) {
  case INSTRUCTION: _type = "INSTRUCTION"; break;
  case DATA: _type = "DATA"; break;
  case NORMAL: _type = "NORMAL"; break;
  case ATOMIC: _type = "ATOMIC"; break;
  case ORDERED: _type = "ORDERED"; break;
  case UNPRIVILEGED: _type = "UNPRIVILEGED"; break;
  case STREAM: _type = "STREAM"; break;
  case VECTOR: _type = "VECTOR"; break;

  default: throw INTERNAL_ERROR; break;
  }
  os << "      type: " << _type << "\n";
  os << "      exclusive?: " << (ma.exclusive ? "yes" : "no") << "\n";
  os << "      direction: " << (ma.direction==FOR_READ ? "READ" : "WRITE") << "\n";
  os << "      endianness: " << (ma.big_endian ? "big-endian" : "little-endian") << "\n";
  os << "      element size in bytes: " << ma.size << "\n";
  os << "      element word size (endianness): " << ma.word_size << "\n";
  os << "      aligned? " << ma.Aligned() << "\n";
  if (ma.sign_extend) {
    os << "      sign-extend?: yes (sign-bit: " << ma.SignBit() << ", extend-to: " << ma.SignExtendTo() << ")" << "\n";  
  } else {
    os << "      sign-extend?: none\n";  
  }
  os << "      paired?: " << (ma.paired ? "yes" : "no") << "\n";  
  os << "      privileged?: " << (ma.privileged ? "yes" : "no") << "\n";

  if (ma.exclusive)
    os << "      exclusive write successful?: " << (ma.exclusive_passed ? "yes" : "no") << "\n";
    
  char hbuf[2048];
  hbuf[0] = '\0';
  for (int j = 0; j < ma.size; j++) {
     char hc[128];
     sprintf(hc," %2.2x",ma.membuffer[j]);
     strcat(hbuf,hc);
  }
  os << "      membuffer: " << hbuf << "\n";

  return os;
}

ostream& operator<< (ostream &os, Packet &pkt) { 
  if (pkt.State == FREERUN_INIT) {
     os << "   Freerun: Initialize instruction:\n";
     os << "      Pstate: 0x" << std::hex << pkt.Pstate.Value() << std::dec << "\n";
     os << "      PC: 0x" << std::hex << pkt.PC.Value() << std::dec << "\n";
  }

  if (pkt.State == FREERUN_RESERVE_MEMORY) {
     os << "   Freerun: Reserve memory:\n";
     os << "      <no info available>\n";
  }

  if (pkt.State == FREERUN_SELECT_INSTRUCTION) {
     os << "   Freerun: Select instruction:\n";
     os << "      <no info available>\n";
  }

  if (pkt.State == FREERUN_ENCODE_INSTRUCTION) {
     os << "   Freerun: Encode instruction:\n";
     os << "      Instruction group: " << pkt.instrGroup() << "\n";
     os << "      Encoding: 0x" << std::hex << pkt.instrEncoding() << std::dec << "\n";
  }

  if (pkt.State == FREERUN_WRITE_INSTRUCTION) {
     os << "   Freerun: Write instruction:\n";
     os << "      <no info available>\n";
  }

  if (pkt.State == FREERUN_END_INSTRUCTION) {
     os << "   Freerun: End instruction:\n";
     os << "      <no info available>\n";
  }

  bool exception_occurred = (pkt.exception_class != NO_SIM_EXCEPTION); 

  if ((pkt.State == FETCH_STATE) || (exception_occurred && (pkt.State >= FETCH_STATE)) ) {
     os << "   Fetch:\n";
     os << "      Pstate: 0x" << std::hex << pkt.Pstate.Value() << std::dec << "\n";
     os << "      PC: 0x" << std::hex << pkt.PC.Value() << std::dec << "\n";

     os << "      Instruction size: " << pkt.instr_size_in_bytes << "\n";
     os << "      Access size: " << pkt.access_size_in_bytes << "\n";

     os << "      Memory:" << std::hex;
     for (int i = 0; i < pkt.instr_size_in_bytes; i++) {
       os << " 0x" << (unsigned int) pkt.mbuf[i];
     }
     os << std::dec << "\n";

     os << "      Instruction endianness: " << (pkt.big_endian ? "Big Endian" : "Little Endian") << "\n";

     os << "      Resulting opcode: 0x" << std::hex << pkt.Opcode << std::dec << "\n";

     if (pkt.State == FETCH_STATE && pkt.exception_class != NO_SIM_EXCEPTION) 
        os << "      !!!" << pkt.exceptionClass() << " exception taken during fetch!!!" << "\n";
  }

  if ((pkt.State == DECODE_STATE) || (exception_occurred && (pkt.State >= DECODE_STATE)) ) {
     os << "   Decode:\n";
     os << "      Instruction: " << pkt.InstrName() << "\n";
     os << "      Enum: " << pkt.InstrEnumName() << "\n";

     bool exception_noted = false;

     if (pkt.State == DECODE_STATE && pkt.exception_class != NO_SIM_EXCEPTION && pkt.exception_type == UNDEFINED_INSTRUCTION) { 
        os << "      !!!" << pkt.exceptionClass() << " exception taken during decode!!!" << "\n";
        exception_noted = true;
     } else {
     os << "      Fields:\n";

     if (pkt.sf.IsDefined())      os << "           sf      = " << pkt.sf << "\n";
     if (pkt.op.IsDefined())      os << "           op      = " << pkt.op << "\n";
     if (pkt.op0.IsDefined())     os << "           op0     = " << pkt.op0 << "\n";
     if (pkt.op1.IsDefined())     os << "           op1     = " << pkt.op1 << "\n";
     if (pkt.op2.IsDefined())     os << "           op2     = " << pkt.op2 << "\n";
     if (pkt.op3.IsDefined())     os << "           op3     = " << pkt.op3 << "\n";
     if (pkt.op4.IsDefined())     os << "           op4     = " << pkt.op4 << "\n";
     if (pkt.op21.IsDefined())    os << "           op21    = " << pkt.op21 << "\n";
     if (pkt.op31.IsDefined())    os << "           op31    = " << pkt.op31 << "\n";
     if (pkt.op54.IsDefined())    os << "           op54    = " << pkt.op54 << "\n";
     if (pkt.opc.IsDefined())     os << "           opc     = " << pkt.opc << "\n";
     if (pkt.o0.IsDefined())      os << "           o0      = " << pkt.o0 << "\n";
     if (pkt.o1.IsDefined())      os << "           o1      = " << pkt.o1 << "\n";
     if (pkt.o2.IsDefined())      os << "           o2      = " << pkt.o2 << "\n";
     if (pkt.o3.IsDefined())      os << "           o3      = " << pkt.o3 << "\n";
     if (pkt.o4.IsDefined())      os << "           o4      = " << pkt.o4 << "\n";
     if (pkt.a.IsDefined())       os << "           a       = " << pkt.a << "\n";
     if (pkt.b.IsDefined())       os << "           b       = " << pkt.b << "\n";
     if (pkt.b40.IsDefined())     os << "           b40     = " << pkt.b40 << "\n";
     if (pkt.b5.IsDefined())      os << "           b5      = " << pkt.b5 << "\n";
     if (pkt.c.IsDefined())       os << "           c       = " << pkt.c << "\n";
     if (pkt.d.IsDefined())       os << "           d       = " << pkt.d << "\n";
     if (pkt.e.IsDefined())       os << "           e       = " << pkt.e << "\n";
     if (pkt.f.IsDefined())       os << "           f       = " << pkt.f << "\n";
     if (pkt.g.IsDefined())       os << "           g       = " << pkt.g << "\n";
     if (pkt.h.IsDefined())       os << "           h       = " << pkt.h << "\n";
     if (pkt.H.IsDefined())       os << "           H       = " << pkt.H << "\n";
     if (pkt.L.IsDefined())       os << "           L       = " << pkt.L << "\n";
     if (pkt.LL.IsDefined())      os << "           LL      = " << pkt.LL << "\n";
     if (pkt.S.IsDefined())       os << "           S       = " << pkt.S << "\n";
     if (pkt.M.IsDefined())       os << "           M       = " << pkt.M << "\n";
     if (pkt.N.IsDefined())       os << "           N       = " << pkt.N << "\n";
     if (pkt.hw.IsDefined())      os << "           hw      = " << pkt.hw << "\n";
     if (pkt.Q.IsDefined())       os << "           Q       = " << pkt.Q << "\n";
     if (pkt.R.IsDefined())       os << "           R       = " << pkt.R << "\n";
     if (pkt.U.IsDefined())       os << "           U       = " << pkt.U << "\n";
     if (pkt.V.IsDefined())       os << "           V       = " << pkt.V << "\n";
     if (pkt.Rd.IsDefined())      os << "           Rd      = R" << std::dec << pkt.Rd.Value() << std::hex << "\n";
     if (pkt.Rn.IsDefined())      os << "           Rn      = R" << std::dec << pkt.Rn.Value() << std::hex << "\n";
     if (pkt.Rs.IsDefined())      os << "           Rs      = R" << std::dec << pkt.Rs.Value() << std::hex << "\n";
     if (pkt.Rt.IsDefined())      os << "           Rt      = R" << std::dec << pkt.Rt.Value() << std::hex << "\n";
     if (pkt.Rt2.IsDefined())     os << "           Rt2     = R" << std::dec << pkt.Rt2.Value() << std::hex << "\n";
     if (pkt.Ra.IsDefined())      os << "           Ra      = R" << std::dec << pkt.Ra.Value() << std::hex << "\n";
     if (pkt.CRn.IsDefined())     os << "           CRn     = " << pkt.CRn << "\n";
     if (pkt.Rm.IsDefined())      os << "           Rm      = R" << std::dec << pkt.Rm.Value() << std::hex << "\n";
     if (pkt.CRm.IsDefined())     os << "           CRm     = " << pkt.CRm << "\n";
     if (pkt.shift.IsDefined())   os << "           shift   = " << pkt.shift << "\n";
     if (pkt.size.IsDefined())    os << "           size    = " << pkt.size << "\n";
     if (pkt.cmode.IsDefined())   os << "           cmode   = " << pkt.cmode << "\n";
     if (pkt.rmode.IsDefined())   os << "           rmode   = " << pkt.rmode << "\n";
     if (pkt.cond.IsDefined())    os << "           cond    = " << pkt.cond << "\n";
     if (pkt.nzcv.IsDefined())    os << "           nzcv    = " << pkt.nzcv << "\n";
     if (pkt.opcode.IsDefined())  os << "           opcode  = " << pkt.opcode << "\n";
     if (pkt.opcode2.IsDefined()) os << "           opcode2 = " << pkt.opcode2 << "\n";
     if (pkt.opt.IsDefined())     os << "           opt     = " << pkt.opt << "\n";
     if (pkt.option.IsDefined())  os << "           option  = " << pkt.option << "\n";
     if (pkt.type.IsDefined())    os << "           type    = " << pkt.type << "\n";
     if (pkt.scale.IsDefined())   os << "           scale   = " << pkt.scale << "\n";
     if (pkt.len.IsDefined())     os << "           len     = " << pkt.len << "\n";
     if (pkt.imm3.IsDefined())    os << "           imm3    = " << pkt.imm3 << "\n";
     if (pkt.imm4.IsDefined())    os << "           imm4    = " << pkt.imm4 << "\n";
     if (pkt.imm5.IsDefined())    os << "           imm5    = " << pkt.imm5 << "\n";
     if (pkt.imm6.IsDefined())    os << "           imm6    = " << pkt.imm6 << "\n";
     if (pkt.imm7.IsDefined())    os << "           imm7    = " << pkt.imm7 << "\n";
     if (pkt.imm8.IsDefined())    os << "           imm8    = " << pkt.imm8 << "\n";
     if (pkt.imm9.IsDefined())    os << "           imm9    = " << pkt.imm9 << "\n";
     if (pkt.imm12.IsDefined())   os << "           imm12   = " << pkt.imm12 << "\n";
     if (pkt.imm14.IsDefined())   os << "           imm14   = " << pkt.imm14 << "\n";
     if (pkt.imm16.IsDefined())   os << "           imm16   = " << pkt.imm16 << "\n";
     if (pkt.imm19.IsDefined())   os << "           imm19   = " << pkt.imm19 << "\n";
     if (pkt.imm26.IsDefined())   os << "           imm26   = " << pkt.imm26 << "\n";
     if (pkt.immlo.IsDefined())   os << "           immlo   = " << pkt.immlo << "\n";
     if (pkt.immhi.IsDefined())   os << "           immhi   = " << pkt.immhi << "\n";
     if (pkt.immr.IsDefined())    os << "           immr    = " << pkt.immr << "\n";
     if (pkt.imms.IsDefined())    os << "           imms    = " << pkt.imms << "\n";
     if (pkt.immb.IsDefined())    os << "           immb    = " << pkt.immb << "\n";
     if (pkt.immh.IsDefined())    os << "           immh    = " << pkt.immh << "\n";
     }

     if (!exception_noted && pkt.State == DECODE_STATE && pkt.exception_class != NO_SIM_EXCEPTION) 
        os << "      !!!" << pkt.exceptionClass() << " exception taken during decode!!!" << "\n";
  } 

  if ((pkt.State == FETCH_OPERANDS_STATE) || (exception_occurred && (pkt.State >= FETCH_OPERANDS_STATE)) ) {
     os << "   Fetch Operands:\n" << std::hex;
     if (pkt.Nreg.IsSet())  os << "         Nreg  = 0x" << pkt.Nreg.Value() << "\n";
     if (pkt.Mreg.IsSet())  os << "         Mreg  = 0x" << pkt.Mreg.Value() << "\n";
     if (pkt.Treg.IsSet())  os << "         Treg  = 0x" << pkt.Treg.Value() << "\n";
     if (pkt.T2reg.IsSet()) os << "         T2reg = 0x" << pkt.T2reg.Value() << "\n";
     if (pkt.RSreg.IsSet()) os << "         RSreg = 0x" << pkt.RSreg.Value() << "\n";
     if (pkt.RAreg.IsSet()) os << "         RAreg = 0x" << pkt.RAreg.Value() << "\n";
     os << std::dec;

     if (pkt.State == FETCH_OPERANDS_STATE && pkt.exception_class != NO_SIM_EXCEPTION) 
        os << "      !!!" << pkt.exceptionClass() << " exception taken during fetch operands!!!" << "\n";
  }

  if ((pkt.State == EXECUTE_STATE) || (exception_occurred && (pkt.State >= EXECUTE_STATE)) ) {
     os << "   Execute:\n";
     if (pkt.Dreg.IsSet())  os << "         Dreg  = 0x" << std::hex << pkt.Dreg.Value() << std::dec << "\n";
     if (pkt.Dreg2.IsSet()) os << "         Dreg2 = 0x" << std::hex << pkt.Dreg2.Value() << std::dec << "\n";
     // addressing mode could cause base register update...
     if (pkt.Nreg.IsSet())  os << "         Nreg  = 0x" << std::hex << pkt.Nreg.Value() << std::dec << "\n";

     if (pkt.State == EXECUTE_STATE && pkt.exception_class != NO_SIM_EXCEPTION) 
         os << "      !!!" << pkt.exceptionClass() << " exception taken during execute!!!" << "\n";
  } 

  if ((pkt.State == MEMORY_ACCESS_STATE) || (exception_occurred && (pkt.State >= MEMORY_ACCESS_STATE)) ) {
     os << "   Memory Access:\n";
     for (vector<MemoryAccess>::iterator i = pkt.mOpsMemory.begin(); i != pkt.mOpsMemory.end(); i++) {
        os << "      " << (*i);
     }

     if (pkt.State == MEMORY_ACCESS_STATE && pkt.exception_class != NO_SIM_EXCEPTION) 
         os << "      !!!" << pkt.exceptionClass() << " exception taken during memory accesses!!!" << "\n";
  } 

  if ((pkt.State == WRITEBACK_STATE) || (exception_occurred && (pkt.State >= WRITEBACK_STATE)) ) {
     os << "   Writeback:\n";
     if (pkt.State == WRITEBACK_STATE && pkt.exception_class != NO_SIM_EXCEPTION) 
         os << "      !!!" << pkt.exceptionClass() << " exception taken during writeback!!!" << "\n";
  } 

  if ((pkt.State == RETIRE_STATE) || (exception_occurred && (pkt.State >= RETIRE_STATE)) ) {
     os << "   Retire:\n";
     os << "      Pstate: 0x" << std::hex << pkt.NextPstate.Value() << std::dec << "\n";
     os << "      PC: 0x" << std::hex << pkt.NextPC.Value() << std::dec << "\n";
  } 

  return os;
}


//==========================================================================================
// misc register methods...
//==========================================================================================

bool MAIR::Attributes(int &mem_type,int &device_type,struct AttrXcacheHints &cache_hints, int attr_index) {
  bool attribute_decode_okay = true;

  int attrX;

  //printf("[MAIR::Attributes] attr_index: %d\n",attr_index);

  switch(attr_index) {
    case 0: attrX = Attr0(); break;
    case 1: attrX = Attr1(); break;
    case 2: attrX = Attr2(); break;
    case 3: attrX = Attr3(); break;
    case 4: attrX = Attr4(); break;
    case 5: attrX = Attr5(); break;
    case 6: attrX = Attr6(); break;
    case 7: attrX = Attr7(); break;
    default: throw INTERNAL_ERROR;
  }

  //printf("[MAIR::Attributes] attrX: 0x%x\n",attrX);

  if ((attrX & 0xf0) == 0) {
    // device memory - cases where Attr<n>[7:4] is 0000:

    mem_type = DEVICE_MEMORY;
    switch(attrX) {
      case 0: case 4: case 8: case 12: device_type = attrX; break;
      default: // unpredictable device attributes...
	       attribute_decode_okay = false;
      break;
    }    
  } else {
    // normal memory...

    mem_type = NORMAL_MEMORY;

    int outer_attr = (int)(attrX>>4);

    bool outer_is_cacheable = false;

    switch(outer_attr) {
      case 1: case 2: case 3: 
               cache_hints.outer_cache_type = MEMATTR_WT; 
               cache_hints.outer_transient  = true; 
               outer_is_cacheable = true;
               break;
      case 5: case 6: case 7: 
               cache_hints.outer_cache_type = MEMATTR_WB; 
               cache_hints.outer_transient  = true; 
               outer_is_cacheable= true;
               break;
      case 8: case 9: case 10: case 11: 
               cache_hints.outer_cache_type = MEMATTR_WT; 
               outer_is_cacheable = true;
               break;
      case 12: case 13: case 14: case 15: 
               cache_hints.outer_cache_type = MEMATTR_WB;  
               outer_is_cacheable = true;
	       break;
      case 4:
               cache_hints.outer_cache_type = MEMATTR_NONCACHEABLE;
               outer_is_cacheable = true;
               break;
      default: throw INTERNAL_ERROR; 
               break;
    }

    int inner_attr = (int)(attrX & 0xf);

    if (outer_is_cacheable) {
      cache_hints.outer_read_allocate  = (outer_attr & 2) == 2;
      cache_hints.outer_write_allocate = (outer_attr & 1) == 1;
    }

    bool inner_is_cacheable = false;

    switch(inner_attr) {
      case 1: case 2: case 3: 
               cache_hints.inner_cache_type = MEMATTR_WT; 
               cache_hints.inner_transient  = true; 
               inner_is_cacheable = true;
               break;
      case 5: case 6: case 7: 
               cache_hints.inner_cache_type = MEMATTR_WB; 
               cache_hints.inner_transient  = true; 
               inner_is_cacheable = true;
               break;
      case 8: case 9: case 10: case 11: 
               cache_hints.inner_cache_type = MEMATTR_WT; 
               inner_is_cacheable = true;
               break;
      case 12: case 13: case 14: case 15: 
               cache_hints.inner_cache_type = MEMATTR_WB;  
               inner_is_cacheable = true;
	       break;
     case 4:
               cache_hints.inner_cache_type = MEMATTR_NONCACHEABLE;
               inner_is_cacheable = true;
               break;
      default: throw INTERNAL_ERROR; 
               break;
    }

    if (inner_is_cacheable) {
      cache_hints.inner_read_allocate  = (inner_attr & 2) == 2;
      cache_hints.inner_write_allocate = (inner_attr & 1) == 1;
    }
  }

  return attribute_decode_okay;
}

//==========================================================================================
// Control class
//==========================================================================================

Control::Control(State *_cpu,Memory *_memory,Packet *_packet,ExceptionEnables *_exception_enables, A64SimMonitor *_sim_monitor) 
  : cpu(_cpu),memory(_memory),packet(_packet),exception_enables(_exception_enables),sim_monitor(_sim_monitor) {

  if (sim_monitor) _memory->SetMonitor(sim_monitor);

  allow_uninitialized_reg_access = true; // by default do NOT enforce uninitialized register checks
}

int Control::InstrState(void) {
  return packet->State;
}
int Control::InstrState(int _state) {
  packet->State = _state;
  return packet->State;
}

string Control::StateName() {
  string _state;
  switch(packet->State) {
    case FETCH_STATE:          _state = "Fetch";               break;
    case DECODE_STATE:         _state = "Decode";              break;
    case FETCH_OPERANDS_STATE: _state = "Fetch Operands";      break;
    case EXECUTE_STATE:        _state = "Execute";             break;       
    case MEMORY_ACCESS_STATE:  _state = "Access Memory";       break;
    case WRITEBACK_STATE:      _state = "Writeback Operands";  break;
    case RETIRE_STATE:         _state = "Instruction Retired"; break;

    case FREERUN_INIT:               _state = "Freerun Init";    break;
    case FREERUN_RESERVE_MEMORY:     _state = "Freerun Reserve"; break;
    case FREERUN_SELECT_INSTRUCTION: _state = "Freerun Select";  break;
    case FREERUN_ENCODE_INSTRUCTION: _state = "Freerun Encode";  break;
    case FREERUN_WRITE_INSTRUCTION:  _state = "Freerun Write";   break;
    case FREERUN_END_INSTRUCTION:    _state = "Freerun End";     break;

    default: _state = "?"; break;
  }
  return _state;
}

int Control::NextState(unsigned int &multiplier) {
    switch(packet->State) {
      case FETCH_STATE:
	   //printf("Fetch...\n");          
           Fetch(multiplier);         
           break;
      case DECODE_STATE:         
	   //printf("Decode...\n");          
           Decode(multiplier);        
           break;
      case FETCH_OPERANDS_STATE: 
	   //printf("Fetch operands...\n");          
           FetchOperands(multiplier); 
           break;
      case EXECUTE_STATE:        
	   //printf("Execute...\n");          
           Execute(multiplier);    
           //printf("Fake writeback, next PC: 0x%llx...\n", packet->NextPC.Value());
           // after execute, use 'fake' writeback to check destination registers...
           Writeback(multiplier,false /* no commit */);
           break;
      case MEMORY_ACCESS_STATE:
	   //printf("Access memory...\n");    
           AccessMemory(multiplier);  
           break;
      case WRITEBACK_STATE:      
	   //printf("Writeback...\n");
	   Writeback(multiplier,true);     
           break;
      case RETIRE_STATE: 
	   //printf("Retire...\n");     
	   Retire(multiplier);     
           break;

      case FREERUN_INIT:
	   // freerun setup for next instruction... 
	   FreerunInit();
           break;
      case FREERUN_RESERVE_MEMORY:
	   // reserve memory for next instruction...
	   FreerunReserveMemory();
           break;
      case FREERUN_SELECT_INSTRUCTION:
	   // select instruction group, instruction opcode...
	   FreerunSelectInstruction();
           break;
      case FREERUN_ENCODE_INSTRUCTION:
	   // complete instruction encoding...
	   FreerunEncodeInstruction();
           break;
      case FREERUN_WRITE_INSTRUCTION:
	   // write instruction to memory...
	   FreerunWriteInstruction();
           break;
      case FREERUN_END_INSTRUCTION:
	   // freerun instruction complete...
	   FreerunEndInstruction();
	   break;

      default: break;
    }

    return packet->State;
}

void Control::FreerunInit() {
  if (sim_monitor) sim_monitor->Step(cpu,memory,packet,cpu->Clock(),cpu->GetID());
  InstrState(FREERUN_RESERVE_MEMORY);
}
void Control::FreerunReserveMemory() {
  if (sim_monitor) sim_monitor->Step(cpu,memory,packet,cpu->Clock(),cpu->GetID());
  InstrState(FREERUN_SELECT_INSTRUCTION);
}
void Control::FreerunSelectInstruction() {
  if (sim_monitor) sim_monitor->Step(cpu,memory,packet,cpu->Clock(),cpu->GetID());
  InstrState(FREERUN_ENCODE_INSTRUCTION);
}
void Control::FreerunEncodeInstruction() {
  if (sim_monitor) sim_monitor->Step(cpu,memory,packet,cpu->Clock(),cpu->GetID());
  InstrState(FREERUN_WRITE_INSTRUCTION);
}
void Control::FreerunWriteInstruction() {
  if (sim_monitor) sim_monitor->Step(cpu,memory,packet,cpu->Clock(),cpu->GetID());
  InstrState(FREERUN_END_INSTRUCTION);
}
void Control::FreerunEndInstruction() {
  if (sim_monitor) sim_monitor->Step(cpu,memory,packet,cpu->Clock(),cpu->GetID());
  InstrState(FETCH_STATE);
}

//#define DEBUG_STEP 1

void Control::Step(int state, bool start_recording) {
#ifdef DEBUG_STEP
  printf("[Control::Step] entered, state: %d\n", state);
#endif
  packet->State = state;

  if (start_recording && sim_monitor)
    sim_monitor->Record(cpu->GetID());

  unsigned int instruction_multiplier = 0; //<--each instruction will report its duration as a multiplier...

  // any packet transactions recorded thusfar were created during loading of the test or test generation,
  // NOT execution...

  packet->discardTransactions();

  try {
#ifndef NO_TIMER
     if (TimerTick()) {
       // need a bit of current 'context' to process the interrupt...
       packet->Pstate = cpu->Pstate;
       packet->PC = cpu->PC;
#ifdef DEBUG_STEP
       printf("[Control::Step] Raising IRQ...\n");
#endif
       RaiseIRQ();
     }
#endif
     unsigned int phase_multiplier = 1;
     while(NextState(phase_multiplier) != RETIRE_STATE) {
       // execute instruction to completion, unless internal error...
       instruction_multiplier += phase_multiplier;
     }
     if (sim_monitor) sim_monitor->Save(cpu->GetID());

     // exception generating instructions (oddly enough) don't throw exceptions, but exception state is updated.
     // this annotation is solely for the simulation trace, ie, is not critical to simulation operation...
     
     if ( (packet->A64InstrIndex == SVC) || (packet->A64InstrIndex == SVC) || (packet->A64InstrIndex == SVC) )
       packet->last_state = EXECUTE_STATE;
  }
  catch(SIM_EXCEPTION_CLASS eclass) {
    if (sim_monitor) sim_monitor->Step(cpu,memory,packet,cpu->Clock(),cpu->GetID()); //<---allow exception to be traced

    if (eclass == ARCH_EXCEPTION) {
      handleException(ARCH_EXCEPTION);

      // packet pstate, next-pc updated...
      cpu->PC     = packet->NextPC;
      cpu->Pstate = packet->NextPstate;

#ifdef DEBUG_STEP
      printf("[Control::Step] exception handled, new PC/Pstate: 0x%llx/0x%x...\n",cpu->PC.Value(),cpu->Pstate.Value());
#endif      
      //cpu->FPSR   = packet->Next_FPSR; ?? in this implementation, no FP exceptions so no need to update FPSR here

      // use exception type to determine which instruction phase to put exception on.
      // this annotation is solely for the simulation trace, ie, is not critical to simulation operation...

      switch(packet->exception_type) {
        case SOFTWARE_STEP:                    packet->last_state = FETCH_STATE; break;
        case MISALIGNED_PC:                    packet->last_state = FETCH_STATE; break;
        case INSTRUCTION_ABORT:                packet->last_state = FETCH_STATE; break;
        case BREAKPOINT:                       packet->last_state = FETCH_STATE; break;
	
        case DEBUG_BREAKPOINT:                 packet->last_state = EXECUTE_STATE; break;
        case ILLEGAL_EXECUTION_STATE:          packet->last_state = EXECUTE_STATE; break;
	
        case UNDEFINED_INSTRUCTION:            packet->last_state = DECODE_STATE; break;
        case SMC_UNDEFINED:                    packet->last_state = DECODE_STATE; break;
	
        case EXCEPTION_GENERATING_INSTRUCTION: packet->last_state = EXECUTE_STATE; break;
        case EXCEPTIONS_TO_EL3:                packet->last_state = EXECUTE_STATE; break;
        case FLOATING_POINT_EXCEPTIONS:        packet->last_state = EXECUTE_STATE; break;
	
        case STACK_POINTER_ALIGNMENT:          packet->last_state = EXECUTE_STATE; break;
	
        case DATA_ABORT:                       packet->last_state = MEMORY_ACCESS_STATE; break;
        case DEBUG_WATCHPOINT:                 packet->last_state = MEMORY_ACCESS_STATE; break;
	
        case ADDRESS_SPACE_ERROR:              packet->last_state = (InstrState() >= EXECUTE_STATE) ? MEMORY_ACCESS_STATE : FETCH_STATE; break;
	
        case TRAP:                             packet->last_state = EXECUTE_STATE; break;

        default:  packet->last_state = DECODE_STATE; break;
      }
    
      // exception has been 'handled', so offending instruction can be retired...
      InstrState(RETIRE_STATE);
    } else {
#ifdef DEBUG_STEP
      printf("[Control::Step] passing exception on...\n");
#endif
      throw eclass; // pass it on...
    }
  }

  // each instruction has a multiplier according to how many cycles the instruction needs to complete.
  // adjust the cpu clock accordingly...

  // cpu->advanceClock(instruction_multiplier); <--- cpu clock advanced as same time as system clock. now assume 1 clock cycle per instruction
  
#ifdef DEBUG_STEP
  printf("[Control::Step] exited...\n");
#endif
}

void Control::Fetch(unsigned int &multiplier) {
   packet->Pstate = cpu->Pstate;
   packet->NextPstate = packet->Pstate;

   packet->FPSR = cpu->FPSR;
   packet->Next_FPSR = packet->FPSR;

   packet->PC = cpu->PC;

   packet->instr_size_in_bytes  = packet->Pstate.ThumbMode() ? 2 : 4;
   packet->access_size_in_bytes = packet->instr_size_in_bytes;

   packet->NextPC = packet->PC.Value() + packet->instr_size_in_bytes; // assume no wraparound

   //printf("[FETCH] reading next instruction from PC: 0x%llx (next PC: 0x%llx)\n",cpu->PC.Value(),packet->NextPC.Value());
   
   memory->ReadMemory(cpu,packet,cpu->PC.Value(),false,cpu->Privileged(),packet->instr_size_in_bytes,true,packet->mbuf,false);
   
   packet->big_endian = false; // instruction endianness is always little on arm processor...

   memory->ApplyEndianness((unsigned char *) &packet->Opcode,packet->mbuf,packet->big_endian,packet->access_size_in_bytes,packet->instr_size_in_bytes);

   multiplier = 8; // memory access for instruction - clock phase multiplier of 8

   if (sim_monitor) sim_monitor->Step(cpu,memory,packet,cpu->Clock(),cpu->GetID());

   InstrState(DECODE_STATE);
}

void Control::FetchOperands(unsigned int &multiplier) { 
  for (vector<int>::iterator i = packet->mOpsFetch.begin(); i != packet->mOpsFetch.end(); i++) {
    switch(*i) {
    case RN:   { // fetch src operand Rn...
               bool or_zero = packet->Rn.Value()==31;
               int rindex   = packet->Rn.Value();
               if ((rindex < 0) || (rindex > 31)) {
                  packet->recordExceptionCondition(INVALID_REGISTER_INDEX); 
                  throw INTERNAL_ERROR;
	       }
               if (!or_zero && !allow_uninitialized_reg_access && !cpu->GP[rindex].IsSet()) {
                  packet->recordExceptionCondition(UNINITIALIZED_REGISTER); 
                  throw GENERATION_ERROR;
	       }
               if (!or_zero && cpu->GP[rindex].IsReserved()) {
                  packet->recordExceptionCondition(RESERVED_REGISTER); 
                  throw GENERATION_ERROR;
	       }
		 
               packet->Nreg.Value( or_zero ? 0 : cpu->GP[rindex].Value() );

               if (!or_zero) packet->srcRegDep.push_back(RegDep(DEP_GP | rindex,cpu->GP[rindex].Value()) );
               }
               break;

    case XD:   { // fetch src operand Xd (see BFM instruction)...
               bool or_zero = packet->Rd.Value()==31;
               int rindex   = packet->Rd.Value();
               if ((rindex < 0) || (rindex > 31)) {
                  packet->recordExceptionCondition(INVALID_REGISTER_INDEX); 
                  throw INTERNAL_ERROR;
	       }
               if (!allow_uninitialized_reg_access && !cpu->GP[rindex].IsSet()) {
                  packet->recordExceptionCondition(UNINITIALIZED_REGISTER); 
                  throw GENERATION_ERROR;
	       }
               if (!or_zero && cpu->GP[rindex].IsReserved()) {
                  packet->recordExceptionCondition(RESERVED_REGISTER); 
                  throw GENERATION_ERROR;
	       }

               packet->Dreg.Value( or_zero ? 0 : cpu->GP[rindex].Value() );

               if (!or_zero) packet->srcRegDep.push_back(RegDep(DEP_GP | rindex,cpu->GP[rindex].Value()) );
               }
               break;

    case RNSP: { // fetch src operand Rn or SP...
               int rindex = packet->Rn.Value();
               if ((rindex < 0) || (rindex > 31)) {
                  packet->recordExceptionCondition(INVALID_REGISTER_INDEX); 
                  throw INTERNAL_ERROR;
	       }
               if (rindex == 31) {
                 if (!allow_uninitialized_reg_access && !cpu->GetSP().IsSet()) {
                    packet->recordExceptionCondition(UNINITIALIZED_REGISTER); 
                    throw GENERATION_ERROR;
		 }
                 if (cpu->GetSP().IsReserved()) {
                   packet->recordExceptionCondition(RESERVED_REGISTER); 
                   throw GENERATION_ERROR;
	         }
                 packet->Nreg.Value( cpu->GetSP().Value() );

                 packet->srcRegDep.push_back(RegDep(DEP_SP | cpu->GetSPindex(),cpu->GetSP().Value()) );
	       } else {
		   if (!allow_uninitialized_reg_access && !cpu->GP[rindex].IsSet()) {
                     packet->recordExceptionCondition(UNINITIALIZED_REGISTER); 
                     throw GENERATION_ERROR;
		 }
                 if (cpu->GP[rindex].IsReserved()) {
                   packet->recordExceptionCondition(RESERVED_REGISTER); 
                   throw GENERATION_ERROR;
	         }
                 packet->Nreg.Value( cpu->GP[rindex].Value() );

                 packet->srcRegDep.push_back(RegDep(DEP_GP | rindex,cpu->GP[rindex].Value()) );
	       }
               }
               break;
    case RM:   { // fetch src operand Rm...
               bool or_zero = packet->Rm.Value()==31;
               int rindex   = packet->Rm.Value();
               if ((rindex < 0) || (rindex > 31)) {
                  packet->recordExceptionCondition(INVALID_REGISTER_INDEX); 
                  throw INTERNAL_ERROR;
	       }
               if (!or_zero && !allow_uninitialized_reg_access && !cpu->GP[rindex].IsSet()) {
                  packet->recordExceptionCondition(UNINITIALIZED_REGISTER); 
                  throw GENERATION_ERROR;
	       }
               if (!or_zero && cpu->GP[rindex].IsReserved()) {
                  packet->recordExceptionCondition(RESERVED_REGISTER); 
                  throw GENERATION_ERROR;
	       }
               packet->Mreg.Value( or_zero ? 0 : cpu->GP[rindex].Value() );
               if (!or_zero) packet->srcRegDep.push_back(RegDep(DEP_GP | rindex,cpu->GP[rindex].Value()) );
	       } 
               break;
    case RT:   { // fetch src operand Rt...
               bool or_zero = packet->Rt.Value()==31;
               int rindex   = packet->Rt.Value();
               if ((rindex < 0) || (rindex > 31)) {
                  packet->recordExceptionCondition(INVALID_REGISTER_INDEX); 
                  throw INTERNAL_ERROR;
	       }
               if (!or_zero && !allow_uninitialized_reg_access && !cpu->GP[rindex].IsSet()) {
                   packet->recordExceptionCondition(UNINITIALIZED_REGISTER); 
                   throw GENERATION_ERROR;
	       }
               if (!or_zero && cpu->GP[rindex].IsReserved()) {
                  packet->recordExceptionCondition(RESERVED_REGISTER); 
                  throw GENERATION_ERROR;
	       }

               packet->Treg.Value( or_zero ? 0 : cpu->GP[rindex].Value() );

               if (!or_zero) packet->srcRegDep.push_back(RegDep(DEP_GP | rindex,cpu->GP[rindex].Value()) );
               } 
               break;
    case RT1:  { // fetch src operand Rt1...
               bool or_zero = packet->Rt.Value()==31;
               int rindex   = packet->Rt.Value();
               if ((rindex < 0) || (rindex > 31)) {
                  packet->recordExceptionCondition(INVALID_REGISTER_INDEX); 
                  throw INTERNAL_ERROR;
	       }
               if (!or_zero && !allow_uninitialized_reg_access && !cpu->GP[rindex].IsSet()) {
                  packet->recordExceptionCondition(UNINITIALIZED_REGISTER); 
                  throw GENERATION_ERROR;
	       }
               if (!or_zero && cpu->GP[rindex].IsReserved()) {
                  packet->recordExceptionCondition(RESERVED_REGISTER); 
                  throw GENERATION_ERROR;
	       }
               packet->Treg.Value( or_zero ? 0 : cpu->GP[rindex].Value() );

               if (!or_zero) packet->srcRegDep.push_back(RegDep(DEP_GP | rindex,cpu->GP[rindex].Value()) );
               }
               break;
    case RT2:  { // fetch src operand Rt2...
               bool or_zero = packet->Rt2.Value()==31;
               int rindex   = packet->Rt2.Value();
               if ((rindex < 0) || (rindex > 31)) {
                  packet->recordExceptionCondition(INVALID_REGISTER_INDEX); 
                  throw INTERNAL_ERROR;
               }
               if (!or_zero && !allow_uninitialized_reg_access && !cpu->GP[rindex].IsSet()) {
                  packet->recordExceptionCondition(UNINITIALIZED_REGISTER); 
                  throw GENERATION_ERROR;
	       }
               if (!or_zero && cpu->GP[rindex].IsReserved()) {
                  packet->recordExceptionCondition(RESERVED_REGISTER); 
                  throw GENERATION_ERROR;
	       }
               packet->T2reg.Value( or_zero ? 0 : cpu->GP[rindex].Value() );

               if (!or_zero) packet->srcRegDep.push_back(RegDep(DEP_GP | rindex,cpu->GP[rindex].Value()) );
               }
               break;
    case RS:   { // fetch src operand Rs...
               bool or_zero = packet->Rs.Value()==31;
               int rindex   = packet->Rs.Value();
               if ((rindex < 0) || (rindex > 31)) {
                  packet->recordExceptionCondition(INVALID_REGISTER_INDEX); 
                  throw INTERNAL_ERROR;
	       }
               if (!or_zero && !allow_uninitialized_reg_access && !cpu->GP[rindex].IsSet()) {
                  packet->recordExceptionCondition(UNINITIALIZED_REGISTER); 
                  throw GENERATION_ERROR;
	       }
               if (!or_zero && cpu->GP[rindex].IsReserved()) {
                  packet->recordExceptionCondition(RESERVED_REGISTER); 
                  throw GENERATION_ERROR;
	       }
               packet->RSreg.Value( or_zero ? 0 : cpu->GP[rindex].Value() );

               if (!or_zero) packet->srcRegDep.push_back(RegDep(DEP_GP | rindex,cpu->GP[rindex].Value()) );
               } 
               break;
    case RA:   { // fetch src operand Ra...
               bool or_zero = packet->Ra.Value()==31;
               int rindex   = packet->Ra.Value();
               if ((rindex < 0) || (rindex > 31)) {
                  packet->recordExceptionCondition(INVALID_REGISTER_INDEX); 
                  throw INTERNAL_ERROR;
	       }
               if (!or_zero && !allow_uninitialized_reg_access && !cpu->GP[rindex].IsSet()) {
                  packet->recordExceptionCondition(UNINITIALIZED_REGISTER); 
                  throw GENERATION_ERROR;
	       }
               if (!or_zero && cpu->GP[rindex].IsReserved()) {
                  packet->recordExceptionCondition(RESERVED_REGISTER); 
                  throw GENERATION_ERROR;
	       }
               packet->RAreg.Value( or_zero ? 0 : cpu->GP[rindex].Value() );

               if (!or_zero) packet->srcRegDep.push_back(RegDep(DEP_GP | rindex,cpu->GP[rindex].Value()) );
               } 
               break;

    case NZCV: // fetch flags...
               // flags already recorded as part of packet pstate...
               break;
    case PC_OP: // fetch PC value...
                // current PC value already recored in packet...
                break;

    case SA:
    case SM:
    case SN:
    case DA:   
    case DM:
    case DN:   // single/double precision floating pt source register operands...
               {
	       int rindex = 0;
               int deptype = 0;
               switch(*i) {
		 case SA: rindex = packet->Ra.Value(); deptype = DEP_FP_SP; break;
                 case SM: rindex = packet->Rm.Value(); deptype = DEP_FP_SP; break;
                 case SN: rindex = packet->Rn.Value(); deptype = DEP_FP_SP; break;
		 case DA: rindex = packet->Ra.Value(); deptype = DEP_FP_DP; break;
                 case DM: rindex = packet->Rm.Value(); deptype = DEP_FP_DP; break;
                 case DN: rindex = packet->Rn.Value(); deptype = DEP_FP_DP; break;
	         default: break;
	       }
               if ((rindex < 0) || (rindex > 31)) {
                  packet->recordExceptionCondition(INVALID_REGISTER_INDEX);
                  throw INTERNAL_ERROR;
	       }
               if (!allow_uninitialized_reg_access && !cpu->V[rindex].IsSet()) {
                  packet->recordExceptionCondition(UNINITIALIZED_REGISTER); 
                  throw GENERATION_ERROR;
	       }
               if (cpu->V[rindex].IsReserved()) {
                  packet->recordExceptionCondition(RESERVED_REGISTER); 
                  throw GENERATION_ERROR;
	       }

               switch(*i) {
                 case SA: packet->VAreg.Value( cpu->V[rindex].Value() ); break;
                 case SM: packet->VMreg.Value( cpu->V[rindex].Value() ); break;
                 case SN: packet->VNreg.Value( cpu->V[rindex].Value() ); break;
                 case DA: packet->VAreg.Value( cpu->V[rindex].Value() ); break;
                 case DM: packet->VMreg.Value( cpu->V[rindex].Value() ); break;
                 case DN: packet->VNreg.Value( cpu->V[rindex].Value() ); break;
	         default: break;
	       }

               packet->srcRegDep.push_back( RegDep(deptype | rindex,cpu->V[rindex].Value(),cpu->V[rindex].ValueHi()) );
               }
	       break;

    case DT:
    case DT2:

    case BT:
      
    case HN:
    case HT:

    case ST:
    case ST2:

    case VN:
    case VM:
    case VD:
    case VT2:
    case VT3:
    case VT4:
    case VT:   // float/simd load/store or simd related source operands...
               {
	       int rindex = 0;
               int deptype = 0;
               switch(*i) {
		 case DT:  rindex = packet->Rt.Value();     deptype = DEP_ASIMD; break;
                 case DT2: rindex = packet->Rt2.Value();    deptype = DEP_ASIMD; break;
		 case BT:  rindex = packet->Rt.Value();     deptype = DEP_ASIMD; break;
                 case HN:  rindex = packet->Rn.Value();     deptype = DEP_ASIMD; break;
		 case HT:  rindex = packet->Rt.Value();     deptype = DEP_ASIMD; break;
                 case ST:  rindex = packet->Rt.Value();     deptype = DEP_ASIMD; break;
                 case ST2: rindex = packet->Rt2.Value();    deptype = DEP_ASIMD; break;
                 case VN:  rindex = packet->Rn.Value();     deptype = DEP_ASIMD; break;
                 case VM:  rindex = packet->Rm.Value();     deptype = DEP_ASIMD; break;
                 case VD:  rindex = packet->Rd.Value();     deptype = DEP_ASIMD; break;
                 case VT:  rindex = packet->Rt.Value();     deptype = DEP_ASIMD; break;
                 case VT2: rindex = packet->Rt.Value() + 1; deptype = DEP_ASIMD; break;
                 case VT3: rindex = packet->Rt.Value() + 2; deptype = DEP_ASIMD; break;
                 case VT4: rindex = packet->Rt.Value() + 3; deptype = DEP_ASIMD; break;
	         default: break;
	       }
               if ((rindex < 0) || (rindex > 31)) {
                  packet->recordExceptionCondition(INVALID_REGISTER_INDEX);
                  throw INTERNAL_ERROR;
	       }
               if (!allow_uninitialized_reg_access && !cpu->V[rindex].IsSet()) {
                  packet->recordExceptionCondition(UNINITIALIZED_REGISTER); 
                  throw GENERATION_ERROR;
	       }
               if (cpu->V[rindex].IsReserved()) {
                  packet->recordExceptionCondition(RESERVED_REGISTER); 
                  throw GENERATION_ERROR;
	       }

               switch(*i) {
                 case DT:  packet->VTreg.Value( cpu->V[rindex].Value() ); 
                           packet->VTreg.ValueHi( cpu->V[rindex].ValueHi() ); 
			   break;
	         case DT2: packet->VT2reg.Value( cpu->V[rindex].Value() ); 
                           packet->VT2reg.ValueHi( cpu->V[rindex].ValueHi() ); 
			   break;
                 case BT:  packet->VTreg.Value( cpu->V[rindex].Value() ); 
                           packet->VTreg.ValueHi( cpu->V[rindex].ValueHi() ); 
			   break;
                 case HN:  packet->VNreg.Value( cpu->V[rindex].Value() ); 
                           packet->VNreg.ValueHi( cpu->V[rindex].ValueHi() ); 
			   break;
                 case HT:  packet->VTreg.Value( cpu->V[rindex].Value() ); 
                           packet->VTreg.ValueHi( cpu->V[rindex].ValueHi() ); 
			   break;
                 case ST:  packet->VTreg.Value( cpu->V[rindex].Value() ); 
                           packet->VTreg.ValueHi( cpu->V[rindex].ValueHi() ); 
			   break;
                 case ST2: packet->VT2reg.Value( cpu->V[rindex].Value() ); 
                           packet->VT2reg.ValueHi( cpu->V[rindex].ValueHi() ); 
			   break;
                 case VN:  packet->VNreg.Value( cpu->V[rindex].Value() ); 
                           packet->VNreg.ValueHi( cpu->V[rindex].ValueHi() ); 
			   break;
                 case VM:  packet->VMreg.Value( cpu->V[rindex].Value() ); 
                           packet->VMreg.ValueHi( cpu->V[rindex].ValueHi() ); 
			   break;
                 case VD:  packet->VDreg.Value( cpu->V[rindex].Value() ); 
                           packet->VDreg.ValueHi( cpu->V[rindex].ValueHi() ); 
			   break;
	         case VT:  packet->VTreg.Value( cpu->V[rindex].Value() ); 
                           packet->VTreg.ValueHi( cpu->V[rindex].ValueHi() ); 
			   break;
                 case VT2: packet->VT2reg.Value( cpu->V[rindex].Value() ); 
                           packet->VT2reg.ValueHi( cpu->V[rindex].ValueHi() ); 
			   break;
                 case VT3: packet->VT3reg.Value( cpu->V[rindex].Value() ); 
                           packet->VT3reg.ValueHi( cpu->V[rindex].ValueHi() ); 
			   break;
                 case VT4: packet->VT4reg.Value( cpu->V[rindex].Value() ); 
                           packet->VT4reg.ValueHi( cpu->V[rindex].ValueHi() ); 
			   break;
	       }

               packet->srcRegDep.push_back(RegDep(deptype | rindex,cpu->V[rindex].Value(),cpu->V[rindex].ValueHi()) );
	       }
               break;

    default:   // internal error - unknown operand index...
               packet->recordExceptionCondition(INVALID_REGISTER); 
               throw INTERNAL_ERROR;
               break;
    }
  }

  multiplier = 1; // ASSUME clock phase multiplier of 1 

  if (sim_monitor) sim_monitor->Step(cpu,memory,packet,cpu->Clock(),cpu->GetID());

  InstrState(EXECUTE_STATE);
}


// apply endianness when loading/saving registers from/to memory...

// save/load a single register value(s) to read/write buffer...

void Control::SaveRegister(unsigned long long t, unsigned char *mbuf, int size, bool endianness) {
  //printf("[Control::SaveRegister] t hi/lo: 0x%8.8x/0x%8.8x size: %d endianness: %d host-endianness: %d\n",
  //       (unsigned int)(t >> 32),(unsigned int)(t & 0xffffffffull),
  //       size,(int) endianness, (int) memory->HostEndianness());

  if (memory->HostEndianness() == endianness) {
    // straight copy from register to memory...
    for (int i = 0; i < size; i++) {
      mbuf[i] = (t>>(i*8)) & 0xff;
    }
  } else {
    // swap register bytes during copy...
    int j = size - 1;
    for (int i = 0; i < size; i++) {
       mbuf[j] = (t>>(i*8)) & 0xff;
       j = j - 1;
    }
  }
}

void Control::LoadRegister(unsigned long long &t, unsigned char *mbuf, int size, bool endianness) {
  t = 0; //<---by default assume zero extended load...
  if (memory->HostEndianness() == endianness) {
    // straight copy from memory to register...
    for (int i = 0; i < size; i++) {
      t = t | ((unsigned long long)mbuf[i])<<(i*8);
    }
  } else {
    // swap memory bytes during copy...
    int j = size - 1;
    for (int i = 0; i < size; i++) {
      t = t | ((unsigned long long)mbuf[j])<<(i*8);
       j = j - 1;
    }
  }
}

//  if (exclusive && big_endian) {

void Control::SaveRegisterPair(unsigned long long t,unsigned long long t2, unsigned char *mbuf, int size, bool endianness, bool swap_regs) {
  if (swap_regs) {
    SaveRegister(t, &mbuf[size],size,endianness);
    SaveRegister(t2, mbuf,size,endianness);
  } else {
    SaveRegister(t, mbuf,size,endianness);
    SaveRegister(t2, &mbuf[size],size,endianness);
  }
} 

void Control::LoadRegisterPair(unsigned long long &t,unsigned long long &t2, unsigned char *mbuf, int size, bool endianness, bool swap_regs) {
  if (swap_regs) {
    LoadRegister(t, &mbuf[size],size,endianness);
    LoadRegister(t2, mbuf,size,endianness);
  } else {
    LoadRegister(t, mbuf,size,endianness);
    LoadRegister(t2, &mbuf[size],size,endianness);
  }
}
            

void Control::AccessMemory(unsigned int &multiplier) {
  //std::cout << "[Control::AccessMemory] entered..." << std::endl;
  
  packet->clear_exclusive_monitor = false;
  packet->set_exclusive_monitor   = false;

  for (vector<MemoryAccess>::iterator i = packet->mOpsMemory.begin(); i != packet->mOpsMemory.end(); i++) {
    //printf("MEM ACCESS: PC: 0x%llx, 0x%llx/%d\n",packet->PC.Value(),(*i).address,(*i).size);
    
     bool is_clear_exclusive_monitor = ((*i).size==0) && (*i).exclusive;
  
     if ( !((*i).size==1 || (*i).size==2 || (*i).size==4 || (*i).size==8 || (*i).size==16 || (*i).size==32 || is_clear_exclusive_monitor) ) {
       //std::cout << "[Control::AccessMemory] unexpected data size: " << (*i).size << std::endl;
       fflush(stdout);
       throw INTERNAL_ERROR;  
     }

     if ((*i).direction == FOR_WRITE) {
       // write to memory...
       //std::cout << "[Control::AccessMemory] WRITE: " << (*i) << std::endl;
       bool do_write = true;
       if ((*i).exclusive) {
	 //std::cout << "exclusive monitor access on write - see page 484" << std::endl;
         do_write = memory->ExclusiveMonitorsPass(cpu,packet,(*i).address,(*i).size,(*i).Aligned(),(*i).privileged,packet->ForTest());
	 //std::cout << "exclusive monitor access/write success? " << do_write << std::endl;
       }
       if (do_write) {
         // NOTE: the byte order of the data in membuffer must match memory, ie, endiannesas
         // must already have been accounted for...
	 //std::cout << "  WRITE: 0x" << std::hex << (*i).address << std::dec << " size: " << (*i).size << std::endl;
         memory->WriteMemory(cpu,packet,(*i).address,true,(*i).privileged,(*i).size,(*i).Aligned(),(*i).membuffer);
       }
       (*i).exclusive_passed = do_write; // record whether or not exclusive write made it
     } else {
       // read from memory...
       bool do_read = true;
       bool set_monitor = false;
       if ((*i).exclusive) {
	 // exclusive monitor access - see page 484
         if (is_clear_exclusive_monitor) {
	    packet->clear_exclusive_monitor = true;
            do_read = false;
         } else {
	   // lets set the exclusive monitor, even if afterwards the memory access causes an abort...
           set_monitor = true;
         }
       }
       if (do_read) {
         // memory read/copied into membuffer...
	 //std::cout << "  READ: 0x" << std::hex << (*i).address << std::dec << " size: " << (*i).size << std::endl;
         memory->ReadMemory(cpu,packet,(*i).address,true,(*i).privileged,(*i).size,(*i).Aligned(),(*i).membuffer,true);	 
         if ((*i).paired) {
	   // two registers...
           bool swap_regs = ((*i).exclusive==true) ? (*i).big_endian : false;
	   if ((*i).word_size == 16) {
	      // load 1st of two quad registers...
              unsigned long long rval1_lo;
              unsigned long long rval1_hi;
              LoadRegisterPair(rval1_lo,rval1_hi,(*i).membuffer,(*i).word_size,(*i).big_endian,swap_regs);
              packet->Dreg.Value(rval1_lo);
              packet->Dreg2.Value(rval1_hi);
	      // load 2nd quad register...
              unsigned long long rval2_lo;
              unsigned long long rval2_hi;
              LoadRegisterPair(rval2_lo,rval2_hi,(*i).membuffer,(*i).word_size,(*i).big_endian,swap_regs);
              packet->Dreg3.Value(rval2_lo);
              packet->Dreg4.Value(rval2_hi);
	   } else {
	      // load two registers, each no more than 64 bits...
              unsigned long long rval1;
              unsigned long long rval2;
              LoadRegisterPair(rval1,rval2,(*i).membuffer,(*i).word_size,(*i).big_endian,swap_regs);
              if ((*i).sign_extend) 
                rval1 = (unsigned long long) SignExtend(rval1,(*i).SignBit(),(*i).SignExtendTo());
              if ((*i).sign_extend) 
                rval2 = (unsigned long long) SignExtend(rval2,(*i).SignBit(),(*i).SignExtendTo());
              packet->Dreg.Value(rval1);
              packet->Dreg2.Value(rval2);
	   }
         } else if ((*i).size == 16) {
	   // quad (float) register is dest. load two register values...
           unsigned long long rval1;
           unsigned long long rval2;
           LoadRegisterPair(rval1,rval2,(*i).membuffer,8,(*i).big_endian,false);
           packet->Dreg2.Value(rval2); // hi 64 bits
           packet->Dreg.Value(rval1);  // lo 64 bits
         } else {
	   // a single register...
           unsigned long long rval;
           LoadRegister(rval,(*i).membuffer,(*i).word_size,(*i).big_endian);
           if ((*i).sign_extend) 
             rval = (unsigned long long) SignExtend(rval,(*i).SignBit(),(*i).SignExtendTo());
           packet->Dreg.Value(rval);
         }
         // if we got here then memory access(es) succeeded, so if needed, set monitor(s)...
         if (set_monitor) {
           packet->set_exclusive_monitor = true;
           packet->excl_la   = (*i).address;
           packet->excl_size = (*i).size;
           packet->excl_priv = (*i).privileged;
	 }
       }
     }

     multiplier = 12; // data memory accesses are painful - use clock phase multiplier of 12
  }

  if (packet->clear_exclusive_monitor && packet->set_exclusive_monitor) {
    throw INTERNAL_ERROR;  
  }

  InstrState(WRITEBACK_STATE);
}

void Control::Retire(unsigned int & /*multiplier*/) {
   // retire instruction - a token op. consumes no clock cycles...
   if (sim_monitor) sim_monitor->Step(cpu,memory,packet,cpu->Clock(),cpu->GetID());
}

// DirectRecordSPRaccess - record SPR access directly (like when an exception occurs), for trace purposes...
//   rindex - internal system register index
//   rval - access or update value
//   updated - if spr is written to

void Control::DirectRecordSPRaccess(int system_reg_index,unsigned long long system_reg_val,bool updated) {
  if (updated) {
     packet->destRegDep.push_back( RegDep(DEP_SPR | system_reg_index, system_reg_val) );
  } else {
     packet->srcRegDep.push_back(RegDep(DEP_SPR | system_reg_index, system_reg_val) );
  }
}

void Control::Writeback(unsigned int &multiplier, bool commit) {
  //printf("[Writeback] entered, commit: %d, this PC: 0x%llx, next PC: 0x%llx...\n",commit,packet->PC.Value(),packet->NextPC.Value());
  // Before we update cpu state check to see if we are running into an existing instruction.
  // for now at least we'll assume thats bad. Later on we may add parameters to specify
  // that this 'apparent' looping is okay...

  int instr_size_in_bytes = cpu->Pstate.ThumbMode() ? 2 : 4;

  unsigned char tbuf[4];

  // packet->Goal == FOR_TEST - then creating a new test and for now do NOT allow loops...
  // packet->Goal == FOR_SIMULATION - simulating an existing test. if there are loops we hope they exit cleanly...

  bool check_for_loops = (packet->Goal == FOR_TEST); 

  if (check_for_loops && (memory->ReadMemory(cpu,packet,packet->NextPC.Value(),false,cpu->Privileged(),instr_size_in_bytes,true,tbuf,false) != ALL_BYTES_FREE)) {
      //printf("[Writeback] next PC value (0x%llx) is to existing code or data. This apparent 'looping' is not supported.\n", packet->NextPC.Value());
      packet->testbench_error = UNEXPECTED_REEXECUTION;
      throw GENERATION_ERROR;
  } else {
    for (vector<int>::iterator i = packet->mOpsWriteback.begin(); i != packet->mOpsWriteback.end(); i++) {
       switch(*i) {
         case XD:   { // update dest operand Rd...
                      int rindex = packet->Rd.Value();
                      if (rindex == 31) {
                        // 'dest' reg is zeros...
                      } else if ((rindex < 0) || (rindex > 31)) {
                        // invalid GP register index...
                        throw INTERNAL_ERROR;
		      } else {
                        if (commit) {
                          if (cpu->GP[rindex].IsReserved()) {
                            packet->recordExceptionCondition(RESERVED_REGISTER); 
                            throw GENERATION_ERROR;
	                  }
               	          cpu->GP[rindex].Value( packet->Dreg.Value() );
                          packet->destRegDep.push_back(RegDep(DEP_GP | rindex,packet->Dreg.Value()));
			}
		      }
                    }
                    break;

         case XDSP: { // update dest operand Rd which can include the stack (GP[31])...
	              int rindex = packet->Rd.Value();
                      if (rindex == 31) {
                        if (commit) {
                          if (cpu->GetSP().IsReserved()) {
                            packet->recordExceptionCondition(RESERVED_REGISTER); 
                            throw GENERATION_ERROR;
	                  }
                          cpu->UpdateSP( Register(packet->Dreg.Value()) );
                          packet->destRegDep.push_back(RegDep(DEP_SP | cpu->GetSPindex(),packet->Dreg.Value()) );
			}
                      } else if ((rindex < 0) || (rindex > 31)) {
                        // invalid GP register index...
                        throw INTERNAL_ERROR;
                      } else {
                        if (commit) {
                          if (cpu->GP[rindex].IsReserved()) {
                            packet->recordExceptionCondition(RESERVED_REGISTER); 
                            throw GENERATION_ERROR;
	                  }
               	          cpu->GP[rindex].Value( packet->Dreg.Value() );
                          packet->destRegDep.push_back(RegDep(DEP_GP | rindex,packet->Dreg.Value()) );
			}
                      }
                    } 
                    break;

         case XNSP: { // update source operand Rn which can include the stack (GP[31])...
	              // (update from load instr post-index addressing mode)
	              int rindex = packet->Rn.Value();
                      if (rindex == 31) {
                        if (commit) {
                          if (cpu->GetSP().IsReserved()) {
                            packet->recordExceptionCondition(RESERVED_REGISTER); 
                            throw GENERATION_ERROR;
	                  }
                          cpu->UpdateSP( Register(packet->Nreg.Value()) );
                          packet->destRegDep.push_back(RegDep(DEP_SP | cpu->GetSPindex(),packet->Nreg.Value()) );
			}
                      } else if ((rindex < 0) || (rindex > 31)) {
                        // invalid GP register index...
                        throw INTERNAL_ERROR;
                      } else {
                        if (commit) {
                          if (cpu->GP[rindex].IsReserved()) {
                            packet->recordExceptionCondition(RESERVED_REGISTER); 
                            throw GENERATION_ERROR;
	                  }
               	          cpu->GP[rindex].Value( packet->Nreg.Value() );
		          packet->destRegDep.push_back(RegDep(DEP_GP | rindex,packet->Nreg.Value()) );
                        }
                      }
                    } 
                    break;

         case XT:   { //printf(">>>update dest operand Rt...\n");
                      int rindex = packet->Rt.Value();
                      if (rindex == 31) {
                        // 'dest' reg is zeros...
                      } else if ((rindex < 0) || (rindex > 31)) {
                        // invalid GP register index...
                        throw INTERNAL_ERROR;
		      } else {
                        if (commit) {
                          if (cpu->GP[rindex].IsReserved()) {
                            packet->recordExceptionCondition(RESERVED_REGISTER); 
                            throw GENERATION_ERROR;
	                  }
                          cpu->GP[rindex].Value( packet->Dreg.Value() );
                          packet->destRegDep.push_back(RegDep(DEP_GP | rindex, packet->Dreg.Value()) );
			}
		      }
                    }
                    break;

         case XT2:  { // update 2nd dest operand Rt2...
                      int rindex = packet->Rt2.Value();
                      if (rindex == 31) {
                        // 'dest' reg is zeros...
                      } else if ((rindex < 0) || (rindex > 31)) {
                        // invalid GP register index...
                        throw INTERNAL_ERROR;
		      } else {
                        if (commit) {
                          if (cpu->GP[rindex].IsReserved()) {
                            packet->recordExceptionCondition(RESERVED_REGISTER); 
                            throw GENERATION_ERROR;
	                  }
                          cpu->GP[rindex].Value( packet->Dreg2.Value() );
                          packet->destRegDep.push_back(RegDep(DEP_GP | rindex, packet->Dreg2.Value()) );
			}
		      }
                    }
                    break;

         case XS:   { // update dest operand Rs...
                      int rindex = packet->Rs.Value();
                      if (commit) {
                        if (cpu->GP[rindex].IsReserved()) {
                          packet->recordExceptionCondition(RESERVED_REGISTER); 
                          throw GENERATION_ERROR;
	                }
                        cpu->GP[rindex].Value( packet->Dreg.Value() );
                        packet->destRegDep.push_back(RegDep(DEP_GP | rindex, packet->Dreg.Value()) );
		      }
                    }
                    break;

         case X30:  if (commit) {
                      if (cpu->GP[30].IsReserved()) {
                        packet->recordExceptionCondition(RESERVED_REGISTER); 
                        throw GENERATION_ERROR;
	              }
                      cpu->GP[30].Value( packet->Dreg.Value() );
	              packet->destRegDep.push_back(RegDep(DEP_GP | 30, packet->Dreg.Value()) );
		    }
		    break;

         case SREG: // system register update...
                    if (commit) {
		      // possible exception conditions already accounted for...
                      int system_reg_index = packet->Sreg.Value();
                      unsigned long long system_reg_update_val = packet->Treg.Value();
                      if (cpu->PstateUpdate(packet->NextPstate,system_reg_index,system_reg_update_val)) {
			// 'next' pstate updated - value recorded is from updated pstate
  	                packet->destRegDep.push_back( RegDep(DEP_SPR | system_reg_index, system_reg_update_val) );
                      } else {
			// update some other system register...
                        cpu->SystemRegisterPut( system_reg_index, system_reg_update_val );
  	                packet->destRegDep.push_back( RegDep(DEP_SPR | system_reg_index, system_reg_update_val) );
		      }
		    }
		    break;

		    
         case DD:   // writeback
         case SD:   //    single/double-precision register value...
                    {
                    int rindex = packet->Rd.Value();
                    if ((rindex < 0) || (rindex > 31)) {
                      // invalid GP register index...
                      throw INTERNAL_ERROR;
		    }
                    if (commit) {
                      if (cpu->V[rindex].IsReserved()) {
                        packet->recordExceptionCondition(RESERVED_REGISTER); 
                        throw GENERATION_ERROR;
	              }
		      cpu->V[rindex].Value( packet->VDreg.Value() );
                      cpu->V[rindex].ValueHi( 0 ); //<---zero upper bits
		      cpu->V[rindex].SetType((*i == DD) ? FL_DOUBLE : FL_SINGLE);
		      packet->destRegDep.push_back(RegDep(((*i == DD) ? DEP_FP_DP : DEP_FP_SP) | rindex,packet->VDreg.Value(),packet->VDreg.ValueHi()) );
                      //printf("[Control::Writeback] SD/DD: V[%d] = 0x%llx (as double: %g)\n",rindex,cpu->V[rindex].Value(),
                      //       cpu->V[rindex].Double());
		    }
                    }
	            break;

         case VD:   // writeback vector register...
         case HD:   // writeback vector register...
                    {
                    int rindex = packet->Rd.Value();
                    if ((rindex < 0) || (rindex > 31)) {
                      // invalid GP register index...
                      throw INTERNAL_ERROR;
		    }
                    if (commit) {
                      if (cpu->V[rindex].IsReserved()) {
                        packet->recordExceptionCondition(RESERVED_REGISTER); 
                        throw GENERATION_ERROR;
	              }
		      cpu->V[rindex].Value( packet->VDreg.Value() );
                      cpu->V[rindex].ValueHi( packet->VDreg.ValueHi() );
		      packet->destRegDep.push_back(RegDep(((*i == DD) ? DEP_FP_DP : DEP_FP_SP) | rindex,packet->VDreg.Value(),packet->VDreg.ValueHi()) );
                      //printf("[Control::Writeback] VD/HDD: V[%d].0 = 0x%llx (as double: %g) V[%d].1 = 0x%llx (as double: %g)\n",
                      //       rindex,cpu->V[rindex].Value(),cpu->V[rindex].Double(), rindex,cpu->V[rindex].ValueHi(),cpu->V[rindex].DoubleHi() );
		    }
                    }
	            break;

		    
         case DT:
         case ST:   { //printf(">>>update dest operand St/Dt...\n");
                      int rindex = packet->Rt.Value();
                      if ((rindex < 0) || (rindex > 31)) {
                        // invalid register index...
                        throw INTERNAL_ERROR;
		      }
                      if (commit) {
                          if (cpu->V[rindex].IsReserved()) {
                            packet->recordExceptionCondition(RESERVED_REGISTER); 
                            throw GENERATION_ERROR;
	                  }
			  cpu->V[rindex].Value( packet->Dreg.Value() );
                          cpu->V[rindex].ValueHi( 0 ); //<---zero upper bits
		          cpu->V[rindex].SetType((*i == DT) ? FL_DOUBLE : FL_SINGLE);
                          packet->destRegDep.push_back( RegDep( ((*i == ST) ? DEP_FP_SP : DEP_FP_DP) | rindex, packet->Dreg.Value(),0) );
		      }
	            }
		    break;
         case DT2:
         case ST2:  {
                      int rindex = packet->Rt2.Value();
                      if ((rindex < 0) || (rindex > 31)) {
                        // invalid register index...
                        throw INTERNAL_ERROR;
		      }
                      if (commit) {
                          if (cpu->V[rindex].IsReserved()) {
                            packet->recordExceptionCondition(RESERVED_REGISTER); 
                            throw GENERATION_ERROR;
	                  }
                          cpu->V[rindex].Value( packet->Dreg2.Value() );
                          cpu->V[rindex].ValueHi( 0 ); //<---zero upper bits
		          cpu->V[rindex].SetType((*i == DT2) ? FL_DOUBLE : FL_SINGLE);
                          packet->destRegDep.push_back(RegDep( ((*i == ST) ? DEP_FP_SP : DEP_FP_DP) | rindex, packet->Dreg2.Value(),0) );
		      }
	            }
		    break;

         case BT:
         case HT:   // writeback vector register...
                    {
                      int rindex = packet->Rt.Value();
                      if ((rindex < 0) || (rindex > 31)) {
                        // invalid register index...
                        throw INTERNAL_ERROR;
		      }
                      if (commit) {
                        if (cpu->V[rindex].IsReserved()) {
                          packet->recordExceptionCondition(RESERVED_REGISTER); 
                          throw GENERATION_ERROR;
	                }
			cpu->V[rindex].Value( packet->Dreg.Value() );
			cpu->V[rindex].ValueHi( 0 ); //<---zero upper bits
                        packet->destRegDep.push_back( RegDep(DEP_ASIMD | rindex, packet->Dreg.Value(),0) );
		      }
	            }
		    break;

         case QT:   // writeback vector register...
                    {
                      int rindex = packet->Rt.Value();
                      if ((rindex < 0) || (rindex > 31)) {
                        // invalid register index...
                        throw INTERNAL_ERROR;
		      }
                      if (commit) {
			// each quad register was read from memory and stored in  a pair of 64 bit reg values: Dreg, Dreg2 
                        if (cpu->V[rindex].IsReserved()) {
                          packet->recordExceptionCondition(RESERVED_REGISTER); 
                          throw GENERATION_ERROR;
	                }
			cpu->V[rindex].Value( packet->Dreg.Value() );
                        cpu->V[rindex].ValueHi( packet->Dreg2.Value() );
                        packet->destRegDep.push_back( RegDep(DEP_ASIMD | rindex, packet->Dreg.Value(),packet->Dreg2.Value()) );
		      }
	            }
		    break;

         case QT2:  // writeback 2nd vector register...
                    {
                      int rindex = packet->Rt2.Value();
                      if ((rindex < 0) || (rindex > 31)) {
                        // invalid register index...
                        throw INTERNAL_ERROR;
		      }
                      if (commit) {
			// each quad register was read from memory and stored in a pair of 64 bit reg values: Dreg3, Dreg4
                        if (cpu->V[rindex].IsReserved()) {
                          packet->recordExceptionCondition(RESERVED_REGISTER); 
                          throw GENERATION_ERROR;
	                }
			cpu->V[rindex].Value( packet->Dreg3.Value() );
			cpu->V[rindex].ValueHi( packet->Dreg4.Value() );
                        packet->destRegDep.push_back( RegDep(DEP_ASIMD | rindex, packet->Dreg3.Value(),packet->Dreg4.Value()) );
		      }
	            }
		    break;

         default:   // internal error - unknown operand index...
	            printf("Writeback: unknown or unimplemented operand %s (index: %d)\n", packet->WritebackOpName(*i).c_str(),*i);
                    throw INTERNAL_ERROR;
                    break;
        }
    }
  }

  if (commit) {
    // exclusive monitor state only updated if no other errors have occurred...
    //printf("[Writeback] commit...\n");
    if (packet->clear_exclusive_monitor) {
      //printf("[Writeback] clear exclusive monitor - core %d...\n", cpu->GetID());
      memory->ClearExclusiveMonitor(cpu);
    } else if (packet->set_exclusive_monitor) {
      //printf("[Writeback] set exclusive monitor - core %d...\n",cpu->GetID());
      memory->SetExclusiveMonitor(cpu,packet,packet->excl_la,packet->excl_size,packet->excl_priv);
    }
    
    cpu->PC     = packet->NextPC;
    cpu->Pstate = packet->NextPstate;
    cpu->FPSR   = packet->Next_FPSR;

    multiplier = 1; // ASSUME clock phase multiplier of 1 

    //printf("[Writeback] next PC: 0x%8.8llx\n",packet->NextPC.Value());

    if (sim_monitor) sim_monitor->Step(cpu,memory,packet,cpu->Clock(),cpu->GetID());

    InstrState(RETIRE_STATE);
  }

  //printf("[Writeback] exited.\n");
}
