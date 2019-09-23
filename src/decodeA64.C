#include <stdio.h>
#include <stdlib.h>

#include "a64sim.h"
#include "a64_instr_enums.h"

//==========================================================================================
// shared library interface...
//==========================================================================================

void Control::Decode(unsigned int &multiplier) { 
  //packet->Pstate = cpu->Pstate; // if decoding new instruction then record current cpu pstate
  //packet->PC = cpu->PC;

   if (packet->Pstate.A64Mode()) {
     DecodeA64(); 
   } else {
     // no a32 instr decoder in place...
     packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
     throw ARCH_EXCEPTION;
     DecodeA32();
   }

   multiplier = 1; // ASSUME decode clock phase multiplier of 1 

   if (sim_monitor) sim_monitor->Step(cpu,memory,packet,cpu->Clock(),cpu->GetID());

   InstrState(FETCH_OPERANDS_STATE); 
}

void Control::DecodeA64() { 
   packet->primary_opcode = (packet->Opcode >> 25) & 0xf;

   //printf("[DecodeA64] A64 primary opcode: 0x%x\n",packet->primary_opcode);

#include "a64_instr_decode.C"

   if (packet->A64InstrIndex==A64_UNALLOCATED) {
     //printf("  A64 opcode not recognized???\n");
     packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
     throw ARCH_EXCEPTION;
   }

   IdentifyMachineOP(); // see if the instruction is implemented...

   //printf("  A64 instruction index (after decode): 0x%x\n",packet->A64InstrIndex);
   ScheduleFetchOpsA64();
   ScheduleWriteBackOpsA64();
}

void Control::ScheduleFetchOpsA64() {
  switch(packet->A64InstrIndex)  {
#include "fetch_ops_code.C"
  default: break;
  }

  // instruction decode may not have picked up all source operands...
  switch(packet->A64InstrIndex)  {
  //case MRS: packet->mOpsFetch.push_back(SYS_REG_OP); MRS/MSR access system regs directly via instruction fields
  //        break;
  case TBNZ:
  case TBZ: packet->mOpsFetch.push_back(RT);
            break;
  case BFM_32:
  case BFM_64: // bitfield move src (and dest) is XD...
            packet->mOpsFetch.push_back(XD);
            break;
  case MOVK_IMM_32:
  case MOVK_IMM_64: // mov 16-bit into reg, keeping other bits intact. thus XD is src...
            packet->mOpsFetch.push_back(XD);
            break;
  case FMOV_FP_8_64_128_TO_TOP: // update top half of 128 bit reg, so need to fetch it...
            packet->mOpsFetch.push_back(VD);
            break;

  case SIMD_STP_REG_POST_8_128:
  case SIMD_STP_REG_PRE_8_128:
  case SIMD_STNP_OFF_8_128:
            packet->mOpsFetch.push_back(VT);
            packet->mOpsFetch.push_back(VT2);
            break;
    
  case SIMD_STP_REG_OFF_8_128:
  case SIMD_STR_IMM_REG_PRE_8_128:
  case SIMD_STR_IMM_REG_8_128:
  case SIMD_STR_IMM_REG_POST_8_128:
  case SIMD_STR_REG_OFF_8_128:
  case SIMD_STUR_IMM_REG_8_128:
            packet->mOpsFetch.push_back(VT);
            packet->mOpsFetch.push_back(VT2);
            break;

  case SIMD_STR_IMM_REG_PRE_8:
  case SIMD_STR_IMM_REG_POST_8:
  case SIMD_STR_IMM_REG_8:
  case SIMD_STR_REG_OFF_8:
            packet->mOpsFetch.push_back(BT);
            break;

  case FCMP_SINGLE_FROM_SP_ZERO:
  case FCMPE_SINGLE_FROM_SP_ZERO:
            packet->mOpsFetch.push_back(SN);
            break;
	    
  case FCMP_FROM_DP_ZERO:
  case FCMPE_FROM_DP_ZERO:
            packet->mOpsFetch.push_back(DN);
            break;

  case PRFM_REG_OFF:
            packet->mOpsFetch.push_back(RM);
	    break;

  default: break;
  }

}

void Control::ScheduleWriteBackOpsA64() {
  switch(packet->A64InstrIndex)  {
#include "writeback_ops_code.C"
  default: break;
  }

  // instruction decode may not have picked up all write-back operands...

  switch(packet->A64InstrIndex)  {
   case MSR_IMM:
   case MSR_REG:
             packet->mOpsWriteback.push_back(SREG);
             break;
   case BL:  packet->mOpsWriteback.push_back(X30);
             break;
   case BLR: packet->mOpsWriteback.push_back(X30);
             break;
  default: break;
  }
}

void Control::DecodeA32() { 
  //if (packet->Status != NO_ERROR) return packet->Status;
}

