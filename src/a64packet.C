#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "a64sim.h"
#include "a64_instr_enums.h"

//==========================================================================================
// packet methods...
//==========================================================================================

Packet::~Packet() {
  discardTransactions();
}

void Packet::discardTransactions() {
  for (vector<Translation *>::iterator i = translations.begin(); i != translations.end(); i++) {
     delete *i;
  }
  translations.erase(translations.begin(),translations.end());
}

string Packet::InstrName() {
  string iname = "?";
  switch((int) A64InstrIndex) {
#include "a64_instr_names.C"
  default: break;
  }
  return iname;
}

string Packet::InstrEnumName() {
  string iname = "?";
  switch((int) A64InstrIndex) {
#include "a64_instr_enum_names.C"
  default: break;
  }
  return iname;
}

void Packet::recordExceptionCondition(int _type, int _subtype,unsigned int _imm) {
  //printf("[Packet::recordExceptionCondition] entered, type: %d sub-type: %d imm: %d\n",_type,_subtype,_imm);
  
  // exception class recorded when exception thrown...

  // record the specifics of the error condition on the packet...

  exception_type     = _type;    // exception type
  exception_subtype  = _subtype; //   exception subtype when appropriate (undef vs svc vs smc...)
  exception_imm      = _imm;     // immediate field for exceptions like SVC

  //std::cout << "[Packet::recordExceptionCondition] exited. class: " << exceptionClass() << " type: " << exceptionType()
  //	    << " sub-type: " << exceptionSubtype() << " arch-exc-type: " << archExceptionType()
  //	    << " arch-exc-subtype: " << archExceptionSubtype() << std::endl;
}

string Packet::exceptionClass() {
  char tbuf[1024];
  switch((int) exception_class) {
    case NO_SIM_EXCEPTION:   strcpy(tbuf,"None");                break;
    case ARCH_EXCEPTION:     strcpy(tbuf,"Architectual");        break;
    case INTERNAL_ERROR:     strcpy(tbuf,"Internal Error");      break;
    case GENERATION_ERROR:   strcpy(tbuf,"Test Creation Error"); break;
    case WAIT_FOR_EVENT:     strcpy(tbuf,"Wait For Event");      break;
    case WAIT_FOR_INTERRUPT: strcpy(tbuf,"Wait For Interrupt");  break;
    case EVENT_NOTICE:       strcpy(tbuf,"Event Notice");        break;
    case EVENT_NOTICE_LOCAL: strcpy(tbuf,"Event Notice Local");  break;
  
    default: strcpy(tbuf,"?"); break;
  }

  return string(tbuf);
}

string Packet::exceptionType() {
  if (exception_class == ARCH_EXCEPTION)
    return archExceptionType();
  if (exception_class == INTERNAL_ERROR)
    return internalExceptionType();

  return string("?");
}

string Packet::exceptionSubtype() {
  if (exception_class == ARCH_EXCEPTION)
    return archExceptionSubtype();
  if (exception_class == INTERNAL_ERROR)
    return internalExceptionSubtype();

  return string("?");
}

string Packet::internalExceptionType() {
  char tbuf[1024];
  switch((int) exception_type) {
    case INVALID_CONDITION:         strcpy(tbuf,"Invalid Condition field"); break;
    case INVALID_EXCEPTION_LEVEL:   strcpy(tbuf,"Invalid Exception Level"); break;
    case INVALID_REG_EXTEND_FIELD:  strcpy(tbuf,"Invalid Register Extend field"); break;
    case PAIRED_REGISTERS_INVALID:  strcpy(tbuf,"Paired register invalid when NOT exclusive op"); break;
    case INVALID_OPC_FIELD:         strcpy(tbuf,"Invalid OPC (size) field"); break;
    case INVALID_REGISTER:          strcpy(tbuf,"Invalid (not yet supported) Register"); break;
    case UNINITIALIZED_REGISTER:    strcpy(tbuf,"Register has not been initialized"); break;
    case INVALID_REGISTER_INDEX:    strcpy(tbuf,"Invalid Field - Register Index"); break;
    case UNIMPLEMENTED_INSTRUCTION: strcpy(tbuf,"Recognized instruction not yet implemented"); break;
    case RESERVED_REGISTER:         strcpy(tbuf,"Register is reserved"); break;
    default: strcpy(tbuf,"?"); break;
  }

  return string(tbuf);
}

string Packet::internalExceptionSubtype() {
  char tbuf[1024];
  switch((int) exception_subtype) {

    default: strcpy(tbuf,"");
  }

  return string(tbuf);
}

string Packet::archExceptionType() {
  char tbuf[1024];
  switch((int) exception_type) {
    case NO_EXCEPTION:                     strcpy(tbuf,"None");                             break;
    case SOFTWARE_STEP:                    strcpy(tbuf,"Software Step");                    break;
    case MISALIGNED_PC:                    strcpy(tbuf,"Misaligned PC");                    break;
    case INSTRUCTION_ABORT:                strcpy(tbuf,"Instruction Abort");                break;
    case BREAKPOINT:                       strcpy(tbuf,"Breakpoint Instruction");           break;
    case DEBUG_BREAKPOINT:                 strcpy(tbuf,"Debug Breakpoint");                 break;
    case ILLEGAL_EXECUTION_STATE:          strcpy(tbuf,"Illegal Execution State");          break;
    case UNDEFINED_INSTRUCTION:            strcpy(tbuf,"Undefined Instruction");            break;
    case SMC_UNDEFINED:                    strcpy(tbuf,"SMC Undefined");                    break;
    case EXCEPTION_GENERATING_INSTRUCTION: strcpy(tbuf,"Exception Generating Instruction"); break;
    case EXCEPTIONS_TO_EL3:                strcpy(tbuf,"Exception to EL3");                 break;
    case FLOATING_POINT_EXCEPTIONS:        strcpy(tbuf,"Floating Point Exception");         break;
    case STACK_POINTER_ALIGNMENT:          strcpy(tbuf,"Stack Pointer Alignment");          break;
    case DATA_ABORT:                       strcpy(tbuf,"Data Abort");                       break;
    case DEBUG_WATCHPOINT:                 strcpy(tbuf,"Debug Watchpoint");                 break;
    case ADDRESS_SPACE_ERROR:              strcpy(tbuf,"Address Space Error");              break;
    case TRAP:                             strcpy(tbuf,"Trap");                             break;
    case IRQ:                              strcpy(tbuf,"IRQ");                              break;
    case FIQ:                              strcpy(tbuf,"FIQ");                              break;
    default: strcpy(tbuf,"?"); break;
  }

  return string(tbuf);
}

string Packet::archExceptionSubtype() {
  char tbuf[1024];

  switch((int) exception_type) {
    case UNDEFINED_INSTRUCTION:
      switch((int) exception_subtype) {
        case NO_UNDEF:                               strcpy(tbuf,"None");                                   break;
        case UNALLOCATED_ENCODING:                   strcpy(tbuf,"Unallocated Encoding");                   break;
        case INACCESSIBLE_INSTRUCTION_AT_CURRENT_EL: strcpy(tbuf,"Instruction Inaccessible at Current EL"); break;
        case UNALLOCATED_ENCODING_DBG_STATE:         strcpy(tbuf,"Unallocated Encoding - Debug State");     break;
        case NON_DEBUG_STATE_EXECUTION:              strcpy(tbuf,"Non Debug State Execution");              break;
        case HVC_EXECUTION_DISABLED:                 strcpy(tbuf,"HVC Instruction Disabled");               break;
        case MSR_MRS_SP_EL0:                         strcpy(tbuf,"MSR MRS SP EL0");                         break;
        case HLT_EXECUTION_DISABLED:                 strcpy(tbuf,"HLT Instruction Disabled");               break;
        case DCPS1_NON_SECURE_EL0:                   strcpy(tbuf,"DCPS1 Non Secure EL0");                   break;
        case DCPS2_NO_EL2:                           strcpy(tbuf,"DCPS2 - No EL2");                         break;
        case DCPS3_NO_EL3:                           strcpy(tbuf,"DCPS3 - No EL3");                         break;
        default: strcpy(tbuf,"?"); break;
      }
      break;

    case DATA_ABORT:
      switch((int) exception_subtype) {
        case ALIGNMENT:         strcpy(tbuf,"Alignment");         break;
        case READ_PERMISSIONS:  strcpy(tbuf,"Read Permissions");  break;
        case WRITE_PERMISSIONS: strcpy(tbuf,"Write Permissions"); break;
        default: strcpy(tbuf,"?"); break;
      }
      break;

    case INSTRUCTION_ABORT:
      switch((int) exception_subtype) {
        case PERMISSIONS:              strcpy(tbuf,"Read Permissions");         break;
        case EXECUTE_NEVER:            strcpy(tbuf,"Execute Never");            break;
        case SECURE_INSTRUCTION_FETCH: strcpy(tbuf,"Secure Instruction Fetch"); break;
        default: strcpy(tbuf,"?"); break;
      }
      break;

    default: strcpy(tbuf,"?"); break;
  }

  return string(tbuf);
}

string Packet::exceptionImmediate() {
  char tbuf[1024];
  sprintf(tbuf,"%d",exception_imm);
  return string(tbuf);
}

string Packet::testBenchError() {
  string tberr_str;
  switch(testbench_error) {
    case UNEXPECTED_REEXECUTION: tberr_str = "Unexpected reexecution - unintended loop?"; break; 
    case MALFORMED_INSTRUCTION:  tberr_str = "Malformed instruction";                     break;
    case UNEXPECTED_EXCEPTION:   tberr_str = "Unexpected exception";                      break;
    default: tberr_str = "?"; break;
  }
  return tberr_str;
}

void Packet::DumpMemoryAccesses() {
  for (vector<MemoryAccess>::iterator i = mOpsMemory.begin(); i != mOpsMemory.end(); i++) {
    std::cout << (*i) << std::endl;
  }
}

string Packet::FetchOpName(int fop_id) {
  string fname;
  switch(fop_id) {
  case DA:   fname = "DA";   break;
  case DM:   fname = "DM";   break;
  case DN:   fname = "DN";   break;
  case DT:   fname = "DT";   break;
  case DT2:  fname = "DT2";  break;
  case HN:   fname = "HN";   break;
  case HT:   fname = "HT";   break;
  case SA:   fname = "SA";   break;
  case SM:   fname = "SM";   break;
  case SN:   fname = "SN";   break;
  case ST:   fname = "ST";   break;
  case ST2:  fname = "ST2";  break;
  case VN:   fname = "VN";   break;
  case VM:   fname = "VM";   break;
  case VT2:  fname = "VT2";  break;
  case VT3:  fname = "VT3";  break;
  case VT4:  fname = "VT4";  break;
  case VT:   fname = "VT";   break;
  case RA:   fname = "RA";   break;
  case RM:   fname = "RM";   break;
  case RN:   fname = "RN";   break;
  case RS:   fname = "RS";   break;
  case RT2:  fname = "RT2";  break;
  case RNSP: fname = "RNSP"; break;
  case RT1:  fname = "RT1";  break;
  case RT:   fname = "RT";   break;
  case BT:   fname = "BT";   break;
  case QT:   fname = "QT";   break;
  case QT2:  fname = "QT2";  break;

  case NZCV:       fname = "NZCV";    break;
  case PC_OP:      fname = "PC";      break;
  case SYS_REG_OP: fname = "SYS_REG"; break;

  default:   fname = "???";  break;
  }
  return fname;
}

string Packet::WritebackOpName(int fop_id) {
  string fname;
  switch(fop_id) {
  case DD:     fname = "DD";     break;
  case HD:     fname = "HD";     break;
  case SD:     fname = "SD";     break;
  case VD:     fname = "VD";     break;
  case XD:     fname = "XD";     break;
  case XT:     fname = "XT";     break;
  case XDSP:   fname = "XDSP";   break;
  case XNSP:   fname = "XNSP";   break;
  case X30:    fname = "X30";    break;
  case XT2:    fname = "XT2";    break;
  case XS:     fname = "XS";     break;
  case HT:     fname = "HT";     break;
  case BT:     fname = "BT";     break;
  case QT:     fname = "QT";     break;
  case QT2:    fname = "QT2";    break;

  default:     fname = "???";    break;
  }
  return fname;
}

// XRegister - uncategorized register reference (used during translations from 'foreign' sim trace format such as tarmac...

void Packet::AddRegisterAccess(std::string &rname,int type,int id,unsigned long long rval_lo,unsigned long long rval_hi,bool for_write) {
  if (for_write) {
    destXreg.push_back(XRegister(rname,type,id,rval_lo,rval_hi));
  } else {
    srcXreg.push_back(XRegister(rname,type,id,rval_lo,rval_hi));
  }
}

// AddMemoryAccess - used during translations from 'foreign' sim trace format such as tarmac...

void Packet::AddMemoryAccess(MemoryAccess &my_access) {
  mOpsMemory.push_back(my_access);
}

// SetState - used during translations from 'foreign' sim trace format such as tarmac...

void Packet::SetState(int _new_state) {
  switch(_new_state) {
    case FETCH_STATE:
    case DECODE_STATE:
    case FETCH_OPERANDS_STATE:
    case EXECUTE_STATE:
    case MEMORY_ACCESS_STATE:
    case WRITEBACK_STATE:
    case RETIRE_STATE: State = _new_state; break;
    default: break;
  }
}
