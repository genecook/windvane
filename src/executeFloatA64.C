#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <cfenv>
#include <math.h>

//#pragma STDC FENV_ACCESS ON

#include "a64sim.h"
#include "a64_instr_enums.h"
#include "disasm_utils.h"
#include "a64_vfpMath.h"

//#define DEBUG_VFP 1

vfpMath vfp_helper;

//---------------------------------------------------------------------------------------------------------------------------
// TrapFPaccess() - are accesses to vfp/simd registers trapped???
//---------------------------------------------------------------------------------------------------------------------------

void Control::TrapFPaccess() {
#ifdef DEBUG_VFP
  printf("[Control::TrapFPaccess] Pstate.EL: %u, Secure: %d, CPACR_EL1: 0x%x (FPEN = %u), cpu->CPTR_EL2.TFP = %u, cpu->CPTR_EL3.TFP = %u\n",
         packet->Pstate.EL(),cpu->IsSecure(),cpu->CPACR_EL1.Value(),cpu->CPACR_EL1.FPEN(),cpu->CPTR_EL2.TFP(),cpu->CPTR_EL3.TFP());
#endif
  
  bool vfp_op_trapped = false;
  int exc_subtype = UNDEFINED_INSTRUCTION;


  switch(cpu->CPACR_EL1.FPEN()) {
    case 0:  // trap EL0 or EL1 float accesses...
             if (packet->Pstate.EL() < 2)
               vfp_op_trapped = true;
	     break;

    case 1:  // trap EL0 float accesses...
             if (packet->Pstate.EL() == 0)
               vfp_op_trapped = true;
             break;

    case 2:  // trap EL0 or EL1 float accesses...
             if (packet->Pstate.EL() < 2)
               vfp_op_trapped = true;
	     break;

    default: // no trap on float accesses via CPACR_EL1 but now check CPTR_EL2 and CPTR_EL3...

             if ( (cpu->CPTR_EL2.TFP()==1) && !cpu->IsSecure() ) {
	       // trap to EL2 on non-secure access to vfp/simd registers...
               vfp_op_trapped = true;
             }
             else if (cpu->CPTR_EL3.TFP()==1) {
	       // trap to EL3 on any access to vfp/simd registers...
               vfp_op_trapped = true;
               exc_subtype = EXCEPTIONS_TO_EL3;
             }
             break;
  }

  if (vfp_op_trapped) {
#ifdef DEBUG_VFP
    printf("[Control::TrapFPaccess] OOPS! vfp access denied?\n");
#endif
    packet->recordExceptionCondition(FLOATING_POINT_EXCEPTIONS,exc_subtype);
    throw ARCH_EXCEPTION;
  }

#ifdef DEBUG_VFP
  printf("[Control::TrapFPaccess] exited, no vfp trap.\n");
#endif
}

//---------------------------------------------------------------------------------------------------------------------------
// SetupFloatExecEnv() - setup floating point "execution env" (exc flags + rounding mode)
//---------------------------------------------------------------------------------------------------------------------------

//enum FPRounding { TIEVEN, POSINF, NEGINF, ZERO, TIEAWAY };
// use instead C fprounding enums:
//   TIEVEN  --> FE_TONEAREST  - tie to even
//   POSINF  --> FE_UPWARD     - towards positive infinity
//   NEGINF  --> FE_DOWNWARD   - towards negative infinity
//   ZERO    --> FE_TOWARDZERO - towards zero
//   TIEAWAY --> FE_TIEAWAY    - away from zero

// FE_TIEAWAY - not supported by C++ (yet?)

#define FE_TIEAWAY FE_TONEAREST

int Control::FPDecodeRM(unsigned int rm) {
  int rmode = 0;
  switch((int) rm) {
    case 0: rmode = FE_TONEAREST;  break;
    case 1: rmode = FE_UPWARD;     break;
    case 2: rmode = FE_DOWNWARD;   break;
    case 3: rmode = FE_TOWARDZERO; break;
    case 4: rmode = FE_TIEAWAY;    break;
    default: //printf("[Control::FPDecodeRM] invalid rounding mode (%u)...\n",rm);
             throw INTERNAL_ERROR; 
             break;
  }
  return rmode;
}
int Control::FPRoundingMode() {
  return (int) cpu->FPCR.RMode();
}

void Control::SetupFloatExecEnv() {
#ifdef DEBUG_VFP
  printf("[SetupFloatExecEnv] setup flags, rounding mode...\n");
#endif
  
  if (packet->saveFloatFlags()) {
      printf("problem saving floating point execution environment?\n");
      throw INTERNAL_ERROR;
    }

  // reset/set floating pt flags, rounding mode...
  
  std::feclearexcept(FE_ALL_EXCEPT);

#ifdef DEBUG_VFP
  _FPSR fp_flags = packet->FPSR;
  
  printf("[SetupFloatExecEnv] FPSR: 0x%x QC: %u IDC: %u IXC: %u UFC: %u OFC: %u DZC: %u IOC: %u\n",
	 fp_flags.Value(),fp_flags.QC(),fp_flags.IDC(),fp_flags.IXC(),fp_flags.UFC(),fp_flags.OFC(),fp_flags.DZC(),fp_flags.IOC());
#endif

  _FPCR fp_ctrl = cpu->FPCR;  
  vfp_helper.setFPRoundingMode(fp_ctrl.RMode());
}

//---------------------------------------------------------------------------------------------------------------------------
// RestoreFloatExecEnv() - restore floating point "execution env"
//---------------------------------------------------------------------------------------------------------------------------

void Control::RestoreFloatExecEnv() {
#ifdef DEBUG_VFP
  printf("[restoreFloatExecEnv] flags restored...\n");
#endif
  
  if (packet->restoreFloatFlags()) {
      printf("problem restoring flags?\n");
      throw INTERNAL_ERROR;
    }
}

//---------------------------------------------------------------------------------------------------------------------------
// UpdateSimulatorFloatFlags() - after floating pt operation, update simulator floating pt flags...
//---------------------------------------------------------------------------------------------------------------------------

void Control::GetEnvFloatFlags(_FPSR &fp_flags) {
    if (std::fetestexcept(FE_DIVBYZERO) != 0) fp_flags.DZC(1);
    if (std::fetestexcept(FE_INEXACT)   != 0) fp_flags.IXC(1);
    if (std::fetestexcept(FE_INVALID)   != 0) fp_flags.IOC(1);
    if (std::fetestexcept(FE_OVERFLOW)  != 0) fp_flags.OFC(1);
    if (std::fetestexcept(FE_UNDERFLOW) != 0) fp_flags.UFC(1);
}

void Control::UpdateSimulatorFloatFlags(bool do_update) {
  // read float flags from execution env, update simulator 'next' state...

  _FPSR fp_flags = packet->FPSR;

#ifdef DEBUG_VFP
  printf("[UpdateSimulatorFloatFlags] FPSR (at entry): 0x%x QC: %u IDC: %u IXC: %u UFC: %u OFC: %u DZC: %u IOC: %u\n",
	 fp_flags.Value(),fp_flags.QC(),fp_flags.IDC(),fp_flags.IXC(),fp_flags.UFC(),fp_flags.OFC(),fp_flags.DZC(),fp_flags.IOC());
#endif

#ifdef DEBUG_VFP
    printf("[UpdateSimulatorFloatFlags] update flags from env? %d\n",do_update);
#endif

  if (do_update) {
    // what about fp_flags.IDC <---Input Denormal cumulative bit dude...
    // the flags are cumulative...
    GetEnvFloatFlags(fp_flags);
  }
  
  packet->Next_FPSR = fp_flags;

#ifdef DEBUG_VFP
  printf("[UpdateSimulatorFloatFlags] FPSR (at exit): 0x%x QC: %u IDC: %u IXC: %u UFC: %u OFC: %u DZC: %u IOC: %u\n",
	 fp_flags.Value(),fp_flags.QC(),fp_flags.IDC(),fp_flags.IXC(),fp_flags.UFC(),fp_flags.OFC(),fp_flags.DZC(),fp_flags.IOC());
#endif
}


//---------------------------------------------------------------------------------------------------------------------------
// expand encoded float immediate into float or double...
//---------------------------------------------------------------------------------------------------------------------------

unsigned long long Control::VFPExpandImm(int my_dsize, unsigned int imm8) {
  int E = (my_dsize==64) ? 11 : 8;
  int F = my_dsize - E - 1;

  unsigned long long sign = (imm8>>7) & 1;

  unsigned long long bit6 = (imm8>>6) & 1;

  unsigned long long replicate_bit6 = (bit6==1) ? (1<<(E-3)) - 1 : 0; // Replicate((imm8>>6) & 1,E - 3)

  unsigned long long exp = (~bit6 & 1)<<(E - 1) | replicate_bit6<<2 | ((imm8>>4) & 3);

  unsigned long long frac = ((unsigned long long) imm8 & 0xfull)<<(F - 4);

  unsigned long long result = (sign<<(my_dsize-1)) | (exp<<F) | frac;

#ifdef DEBUG_VFP
  printf("[vfpMath::VFPExpandImm] dsize: %d imm8: 0x%x E: %d F: %d sign: %llu $exp: 0x%llx frac: 0x%llx result: 0x%llx\n",
         my_dsize,imm8,E,F,sign,exp,frac,result);
 #endif
  
  return result;
}


//---------------------------------------------------------------------------------------------------------------------------
// execute floating pt or simd op...
//---------------------------------------------------------------------------------------------------------------------------

void Control::executeFloatSIMD(unsigned int &multiplier) {
#ifdef DEBUG_VFP
  printf("\n[executeFloatSIMD] entered...\n");
#endif
  
  TrapFPaccess();
  SetupFloatExecEnv();

  try {
     bool do_update_flags = executeFloatSIMD_inner(multiplier);
     UpdateSimulatorFloatFlags(do_update_flags);
     RestoreFloatExecEnv();
  } catch(SIM_EXCEPTION_CLASS etype) {
     RestoreFloatExecEnv(); // exception caught just to make sure fp exec env restored
                            // simulator flags unknown
     
#ifdef DEBUG_VFP
     printf("\n[executeFloatSIMD] FLOAT EXCEPTION CLASS: %d\n",(int) etype);
#endif
     throw etype;
  }

#ifdef DEBUG_VFP
  printf("[executeFloatSIMD] exited.\n");
#endif
}

bool Control::executeFloatSIMD_inner(unsigned int &multiplier) {
#ifdef DEBUG_VFP
  printf("\n[executeFloatSIMD_inner] entered...\n");
#endif
  bool update_flags = false;
  
  switch(instrID) {
    case FABS_FROM_DP: case FABS_SINGLE_FROM_SP: case FADD_FROM_DP: case FADD_SINGLE_FROM_SP:
    case FDIV_FROM_DP: case FDIV_SINGLE_FROM_SP: case FMADD_FROM_DP: case FMADD_SINGLE_FROM_SP:
    case FMAX_FROM_DP: case FMAXNM_FROM_DP: case FMAXNM_SINGLE_FROM_SP: case FMAX_SINGLE_FROM_SP:
    case FMIN_FROM_DP: case FMINNM_FROM_DP: case FMINNM_SINGLE_FROM_SP: case FMIN_SINGLE_FROM_SP:
    case FMOV_REG_FROM_DP: case FMOV_SINGLE_REG_FROM_SP: 
    case FMSUB_FROM_DP: case FMSUB_SINGLE_FROM_SP: case FMUL_FROM_DP: case FMUL_SINGLE_FROM_SP:
    case FNEG_FROM_DP: case FNEG_SINGLE_FROM_SP: case FNMADD_FROM_DP: case FNMADD_SINGLE_FROM_SP:
    case FNMSUB_FROM_DP: case FNMSUB_SINGLE_FROM_SP: case FNMUL_FROM_DP: case FNMUL_SINGLE_FROM_SP:
    case FSQRT_FROM_DP: case FSQRT_SINGLE_FROM_SP: case FSUB_FROM_DP: case FSUB_SINGLE_FROM_SP:

      vfpMath();
      update_flags = true;
      break;

    case FRINTA_FROM_DP: case FRINTA_SINGLE_FROM_SP: case FRINTI_FROM_DP: case FRINTI_SINGLE_FROM_SP:
    case FRINTM_FROM_DP: case FRINTM_SINGLE_FROM_SP: case FRINTN_FROM_DP: case FRINTN_SINGLE_FROM_SP:
    case FRINTP_FROM_DP: case FRINTP_SINGLE_FROM_SP: case FRINTX_FROM_DP: case FRINTX_SINGLE_FROM_SP:
    case FRINTZ_FROM_DP: case FRINTZ_SINGLE_FROM_SP:

      vfpRounding();
      update_flags = true;
      break;

    case FCMP_FROM_DP: case FCMP_SINGLE_FROM_SP: case FCMP_FROM_DP_ZERO: case FCMP_SINGLE_FROM_SP_ZERO:
    case FCMPE_FROM_DP: case FCMPE_SINGLE_FROM_SP: case FCMPE_FROM_DP_ZERO: case FCMPE_SINGLE_FROM_SP_ZERO:

      vfpCompare();
      update_flags = true;
      break;

    case FCCMP_FROM_DP: case FCCMP_SINGLE_FROM_SP: case FCCMPE_FROM_DP: case FCCMPE_SINGLE_FROM_SP: 

      vfpConditionalCompare();
      update_flags = true;
      break;

    case FCSEL_FROM_DP: case FCSEL_SINGLE_FROM_SP:

      vfpConditionalSelect();
      update_flags = true;
      break;

    case FMOV_IMM_FROM_DP: case FMOV_IMM_SINGLE_FROM_SP: 
      vfpMoveImm();
      break;

    case FCVT_FROM_DP_TO_HP: 
    case FCVT_FROM_HP_TO_DP: 
    case FCVT_SINGLE_FROM_SP_TO_DP: 
    case FCVT_SINGLE_FROM_SP_TO_HP: 
    case FCVT_SINGLE_FROM_HP_TO_SP: 
    case FCVT_SINGLE_FROM_DP_TO_SP:

      vfpFPConvert();
      update_flags = true;
      break;

    case FCVTMS_FROM_DP_FP_32: case FCVTMS_FROM_DP_FP_64:
    case FCVTAS_FROM_DP_FP_32: case FCVTAS_FROM_DP_FP_64: case FCVTAS_SINGLE_FROM_SP_FP_32: case FCVTAS_SINGLE_FROM_SP_FP_64:
    case FCVTAU_FROM_DP_FP_32: case FCVTAU_FROM_DP_FP_64: case FCVTAU_SINGLE_FROM_SP_FP_32: case FCVTAU_SINGLE_FROM_SP_FP_64:
    case FCVTNS_SINGLE_FROM_SP_FP_32: case FCVTNS_SINGLE_FROM_SP_FP_64: 
    case FCVTNU_FROM_DP_FP_32: case FCVTNU_FROM_DP_FP_64: case FCVTNU_SINGLE_FROM_SP_FP_32: case FCVTNU_SINGLE_FROM_SP_FP_64:
    case FCVTPS_FROM_DP_FP_32: case FCVTPS_FROM_DP_FP_64:
    case FCVTPS_SINGLE_FROM_SP_FP_32: case FCVTPS_SINGLE_FROM_SP_FP_64: 
    case FCVTPU_FROM_DP_FP_32: case FCVTPU_FROM_DP_FP_64: case FCVTPU_SINGLE_FROM_SP_FP_32: case FCVTPU_SINGLE_FROM_SP_FP_64:  
    case FCVTMS_SINGLE_FROM_SP_FP_32: case FCVTMS_SINGLE_FROM_SP_FP_64: 
    case FCVTMU_FROM_DP_FP_32: case FCVTMU_FROM_DP_FP_64: case FCVTMU_SINGLE_FROM_SP_FP_32: case FCVTMU_SINGLE_FROM_SP_FP_64: 
    case FCVTNS_FROM_DP_FP_32: case FCVTNS_FROM_DP_FP_64: 
    case FCVTZS_FROM_DP_FP_32: case FCVTZS_FROM_DP_FP_64: case FCVTZS_SINGLE_FROM_SP_FP_32: case FCVTZS_SINGLE_FROM_SP_FP_64: 
    case FCVTZU_FROM_DP_FP_32: case FCVTZU_FROM_DP_FP_64: case FCVTZU_SINGLE_FROM_SP_FP_32: case FCVTZU_SINGLE_FROM_SP_FP_64: 
    case FCVTZS_FROM_DP_FP_FIXED_32: case FCVTZS_FROM_DP_FP_FIXED_64: case FCVTZS_SINGLE_FROM_SP_FP_FIXED_32: case FCVTZS_SINGLE_FROM_SP_FP_FIXED_64: 
    case FCVTZU_FROM_DP_FP_FIXED_32: case FCVTZU_FROM_DP_FP_FIXED_64: case FCVTZU_SINGLE_FROM_SP_FP_FIXED_32: case FCVTZU_SINGLE_FROM_SP_FP_FIXED_64: 
    case SCVTF_SINGLE_TO_SP_FP_32: case SCVTF_SINGLE_TO_SP_FP_64: case SCVTF_SINGLE_TO_SP_FP_FIXED_32: case SCVTF_SINGLE_TO_SP_FP_FIXED_64:
    case SCVTF_TO_DP_FP_32: case SCVTF_TO_DP_FP_64: case SCVTF_TO_DP_FP_FIXED_32: case SCVTF_TO_DP_FP_FIXED_64:
    case UCVTF_SINGLE_TO_SP_FP_32: case UCVTF_SINGLE_TO_SP_FP_64: case UCVTF_SINGLE_TO_SP_FP_FIXED_32: case UCVTF_SINGLE_TO_SP_FP_FIXED_64:
    case UCVTF_TO_DP_FP_32: case UCVTF_TO_DP_FP_64: case UCVTF_TO_DP_FP_FIXED_32: case UCVTF_TO_DP_FP_FIXED_64:
            update_flags = true;

    // simple fp move ops don't update the flags...
	    
    case FMOV_FP_8_64_128: case FMOV_FP_8_64_128_TO_TOP: 
    case FMOV_SINGLE_FROM_SP_FP_32: case FMOV_FROM_DP_FP_64: case FMOV_SINGLE_TO_SP_FP_32: case FMOV_TO_DP_FP_64:

      vfpMove();
      break;

    // fp load/store ops don't update the flags...
      
    case SIMD_LDP_REG_OFF_8_128: case SIMD_LDP_REG_OFF_32: case SIMD_LDP_REG_OFF_64: case SIMD_LDP_REG_POST_8_128:
    case SIMD_LDP_REG_POST_32: case SIMD_LDP_REG_POST_64: case SIMD_LDP_REG_PRE_8_128: case SIMD_LDP_REG_PRE_32:
    case SIMD_LDP_REG_PRE_64: case SIMD_LDNP_OFF_8_128: case SIMD_LDNP_OFF_32: case SIMD_LDNP_OFF_64:
    case SIMD_STP_REG_OFF_8_128: case SIMD_STP_REG_OFF_32: case SIMD_STP_REG_OFF_64: case SIMD_STP_REG_POST_8_128:
    case SIMD_STP_REG_POST_32: case SIMD_STP_REG_POST_64: case SIMD_STP_REG_PRE_8_128: case SIMD_STP_REG_PRE_32:
    case SIMD_STP_REG_PRE_64: case SIMD_STNP_OFF_8_128: case SIMD_STNP_OFF_32: case SIMD_STNP_OFF_64:

      vfpLoadStorePair();
      break;

    case SIMD_LDR_IMM_REG_POST_8_128: case SIMD_LDR_IMM_REG_POST_16: case SIMD_LDR_IMM_REG_POST_32: case SIMD_LDR_IMM_REG_POST_64: 
    case SIMD_LDR_IMM_REG_POST_8: case SIMD_LDR_IMM_REG_PRE_8_128: case SIMD_LDR_IMM_REG_PRE_16: case SIMD_LDR_IMM_REG_PRE_32: 
    case SIMD_LDR_IMM_REG_PRE_64: case SIMD_LDR_IMM_REG_PRE_8: case SIMD_LDR_IMM_REG_8_128: case SIMD_LDR_IMM_REG_16: 
    case SIMD_LDR_IMM_REG_32: case SIMD_LDR_IMM_REG_64: case SIMD_LDR_IMM_REG_8: case SIMD_STR_IMM_REG_POST_8_128: 
    case SIMD_STR_IMM_REG_POST_16: case SIMD_STR_IMM_REG_POST_32: case SIMD_STR_IMM_REG_POST_64: case SIMD_STR_IMM_REG_POST_8: 
    case SIMD_STR_IMM_REG_PRE_8_128: case SIMD_STR_IMM_REG_PRE_16: case SIMD_STR_IMM_REG_PRE_32: case SIMD_STR_IMM_REG_PRE_64: 
    case SIMD_STR_IMM_REG_PRE_8: case SIMD_STR_IMM_REG_8_128: case SIMD_STR_IMM_REG_16: case SIMD_STR_IMM_REG_32: 
    case SIMD_STR_IMM_REG_64: case SIMD_STR_IMM_REG_8:

      vfpLoadStore();
      break;

    case SIMD_LDR_REG_OFF_8: case SIMD_LDR_REG_OFF_16: case SIMD_LDR_REG_OFF_32: case SIMD_LDR_REG_OFF_64: case SIMD_LDR_REG_OFF_8_128: 
    case SIMD_STR_REG_OFF_8: case SIMD_STR_REG_OFF_16: case SIMD_STR_REG_OFF_32: case SIMD_STR_REG_OFF_64: case SIMD_STR_REG_OFF_8_128: 

      vfpLoadStoreRegisterOffset();
      break;

    case SIMD_LDR_REG_8_128: case SIMD_LDR_REG_32: case SIMD_LDR_REG_64:

      vfpLoadLiteral();
      break;

    // remaining (simd) instructions not implemented yet...

    default: 
#ifdef DEBUG_VFP
             printf("\n[executeFloatSIMD_inner] Unimplemented instruction...\n");
#endif
             packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNIMPLEMENTED_INSTRUCTION);
             throw ARCH_EXCEPTION;
             break;
  }

  // update fake clock multiplier...

  switch(instrID) {
    case FDIV_FROM_DP: case FDIV_SINGLE_FROM_SP:     multiplier = 8; 
                                                     break;
    case FMADD_FROM_DP: case FMADD_SINGLE_FROM_SP:
    case FMUL_FROM_DP: case FMUL_SINGLE_FROM_SP:
    case FNMADD_FROM_DP: case FNMADD_SINGLE_FROM_SP:
    case FMSUB_FROM_DP: case FMSUB_SINGLE_FROM_SP: 
    case FNMSUB_FROM_DP: case FNMSUB_SINGLE_FROM_SP: 
    case FNMUL_FROM_DP: case FNMUL_SINGLE_FROM_SP:   multiplier = 4; 
                                                     break;
    default: break;
  }

#ifdef DEBUG_VFP
  printf("\n[executeFloatSIMD_inner] exited.\n");
#endif
  
  return update_flags;
}


//---------------------------------------------------------------------------------------------------------------------------
// vfp math...
//---------------------------------------------------------------------------------------------------------------------------

void Control::vfpMath() {
#ifdef DEBUG_VFP
  printf("[Control::vfpMath] entered...\n");
#endif
  
  switch(instrID) {
    case FABS_SINGLE_FROM_SP:
    case FNEG_SINGLE_FROM_SP: 
    case FSQRT_SINGLE_FROM_SP: 
    case FMOV_SINGLE_REG_FROM_SP:  {
                                     float operand = packet->VNreg.Single();
                                     float result;

#ifdef DEBUG_VFP
				     printf("Operand (single precision): %f\n",operand);
#endif
				     
                                     switch(instrID) {
                                        case FABS_SINGLE_FROM_SP:     result = vfp_helper.FPAbs(operand);  break;
				        case FNEG_SINGLE_FROM_SP:     result = vfp_helper.FPNeg(operand);  break;
				        case FSQRT_SINGLE_FROM_SP:    result = vfp_helper.FPSqrt(operand); break;
                                        case FMOV_SINGLE_REG_FROM_SP: result = operand;                    break;
				        default: throw INTERNAL_ERROR; break;
                                     }

                                     packet->VDreg.Single(result);
                                   }
                                   break;

    case FABS_FROM_DP:
    case FNEG_FROM_DP: 
    case FSQRT_FROM_DP: 
    case FMOV_REG_FROM_DP:         {
                                     double operand = packet->VNreg.Double();
                                     double result;

#ifdef DEBUG_VFP
				     printf("Operand (double precision): %g (0x%llx)\n",operand,packet->VNreg.Value());
#endif
				     
                                     switch(instrID) {
                                        case FABS_FROM_DP:     result = vfp_helper.FPAbs(operand);   break;
				        case FNEG_FROM_DP:     result = vfp_helper.FPNeg(operand);   break;
                                        case FSQRT_FROM_DP:    result = vfp_helper.FPSqrt(operand);  break;
                                        case FMOV_REG_FROM_DP: result = operand;                     break;
                                        default: throw INTERNAL_ERROR; break;
                                     }

                                     packet->VDreg.Double(result);
                                   }
                                   break;

    case FADD_SINGLE_FROM_SP:
    case FSUB_SINGLE_FROM_SP:      {
                                     float operand1 = packet->VNreg.Single(); // SN
                                     float operand2 = packet->VMreg.Single(); // SM

                                     float result;

                                     switch(instrID) {
				        case FADD_SINGLE_FROM_SP: result = vfp_helper.FPAdd(operand1,operand2); break;
                                        case FSUB_SINGLE_FROM_SP: result = vfp_helper.FPNeg(operand1,operand2); break;
				        default: throw INTERNAL_ERROR; break;
                                     }

                                     packet->VDreg.Single(result);
                                   }
                                   break;

    case FADD_FROM_DP: 
    case FSUB_FROM_DP:             {
                                     double operand1 = packet->VNreg.Double();
                                     double operand2 = packet->VMreg.Double();
                                     double result;

                                     switch(instrID) {
				        case FADD_FROM_DP: result = vfp_helper.FPAdd(operand1,operand2); break;
                                        case FSUB_FROM_DP: result = vfp_helper.FPNeg(operand1,operand2); break;
				        default: throw INTERNAL_ERROR; break;
                                     }
                       
                                     packet->VDreg.Double(result);
                                   }
                                   break;

    case FDIV_SINGLE_FROM_SP:      {
                                     float operand1 = packet->VNreg.Single();
                                     float operand2 = packet->VMreg.Single();

                                     float result = vfp_helper.FPDiv(operand1,operand2);

                                     packet->VDreg.Single(result);
                                   }
                                   break;

    case FDIV_FROM_DP:             {
                                     double operand1 = packet->VNreg.Double();
                                     double operand2 = packet->VMreg.Double();

                                     double result = vfp_helper.FPDiv(operand1,operand2);

                                     packet->VDreg.Double(result);
                                   }
                                   break;

    case FMADD_SINGLE_FROM_SP:     
    case FMSUB_SINGLE_FROM_SP:     
    case FNMADD_SINGLE_FROM_SP:
    case FNMSUB_SINGLE_FROM_SP:    {
                                     float operanda = packet->VAreg.Single();
                                     float operand1 = packet->VNreg.Single();
                                     float operand2 = packet->VMreg.Single();

                                     bool opa_neg = packet->o1 == 1;
                                     bool op1_neg = packet->o0 != packet->o1;

                                     if (opa_neg) operanda = vfp_helper.FPNeg(operanda);
                                     if (op1_neg) operand1 = vfp_helper.FPNeg(operand1);

                                     float result = vfp_helper.FPMulAdd(operanda,operand1,operand2);

                                     packet->VDreg.Single(result);
                                   }
                                   break;

    case FMADD_FROM_DP:            
    case FMSUB_FROM_DP:             
    case FNMADD_FROM_DP: 
    case FNMSUB_FROM_DP:           {
                                     double operanda = packet->VAreg.Double();
                                     double operand1 = packet->VNreg.Double();
                                     double operand2 = packet->VMreg.Double();

                                     bool opa_neg = packet->o1 == 1;
                                     bool op1_neg = packet->o0 != packet->o1;

                                     if (opa_neg) operanda = vfp_helper.FPNeg(operanda);
                                     if (op1_neg) operand1 = vfp_helper.FPNeg(operand1);

                                     double result = vfp_helper.FPMulAdd(operanda,operand1,operand2);

                                     packet->VDreg.Double(result);
                                   }
                                   break;

    case FMAX_SINGLE_FROM_SP:      
    case FMAXNM_SINGLE_FROM_SP:    {
                                     float operand1 = packet->VNreg.Single();
                                     float operand2 = packet->VMreg.Single();

                                     float result;

                                     switch(instrID) {
				        case FMAX_SINGLE_FROM_SP:   result = vfp_helper.FPMax(operand1,operand2);    break;
                                        case FMAXNM_SINGLE_FROM_SP: result = vfp_helper.FPMaxNum(operand1,operand2); break;
				        default: throw INTERNAL_ERROR; break;
				     }

                                     packet->VDreg.Single(result);
                                   }
                                   break;

    case FMAX_FROM_DP:             
    case FMAXNM_FROM_DP:           {
                                     double operand1 = packet->VNreg.Double();
                                     double operand2 = packet->VMreg.Double();

                                     double result;

                                     switch(instrID) {
				        case FMAX_FROM_DP:   result = vfp_helper.FPMax(operand1,operand2);    break;
                                        case FMAXNM_FROM_DP: result = vfp_helper.FPMaxNum(operand1,operand2); break;
				        default: throw INTERNAL_ERROR; break;
				     }

                                     packet->VDreg.Double(result);
                                   }
                                   break;

    case FMIN_FROM_DP:             
    case FMINNM_FROM_DP:           {
                                     double operand1 = packet->VNreg.Double();
                                     double operand2 = packet->VMreg.Double();

                                     double result;

                                     switch(instrID) {
				        case FMIN_FROM_DP:   result = vfp_helper.FPMin(operand1,operand2);    break;
                                        case FMINNM_FROM_DP: result = vfp_helper.FPMinNum(operand1,operand2); break;
				        default: throw INTERNAL_ERROR; break;
				     }

#ifdef DEBUG_VFP
				     printf("[Control::vfpMath] operand1: %g, operand2: %g, FMIN/DP result: %g\n",
					    operand1,operand2,result);
#endif				     
                                     packet->VDreg.Double(result);
                                   }
                                   break;

    case FMIN_SINGLE_FROM_SP:      
    case FMINNM_SINGLE_FROM_SP:    {
                                     float operand1 = packet->VNreg.Single();
                                     float operand2 = packet->VMreg.Single();

                                     float result;

                                     switch(instrID) {
				        case FMIN_SINGLE_FROM_SP:   result = vfp_helper.FPMin(operand1,operand2);    break;
                                        case FMINNM_SINGLE_FROM_SP: result = vfp_helper.FPMinNum(operand1,operand2); break;
				        default: throw INTERNAL_ERROR; break;
				     }

#ifdef DEBUG_VFP
				     printf("[Control::vfpMath] operand1: %g, operand2: %g, FMIN/SP result: %g\n",
					    operand1,operand2,result);
#endif
				     
                                     packet->VDreg.Single(result);
                                   }
                                   break;

    case FMUL_SINGLE_FROM_SP:      
    case FNMUL_SINGLE_FROM_SP:     {
                                     float operand1 = packet->VNreg.Single();
                                     float operand2 = packet->VMreg.Single();

                                     bool negated = instrID == FNMUL_SINGLE_FROM_SP;

                                     float result = vfp_helper.FPMul(operand1,operand2);

                                     if (negated) result = vfp_helper.FPNeg(result);

                                     packet->VDreg.Single(result);
                                   }
                                   break;

    case FMUL_FROM_DP: 
    case FNMUL_FROM_DP:            {
                                     double operand1 = packet->VNreg.Double();
                                     double operand2 = packet->VMreg.Double();

                                     bool negated = instrID == FNMUL_FROM_DP;

                                     double result = vfp_helper.FPMul(operand1,operand2);

                                     if (negated) result = vfp_helper.FPNeg(result);

                                     packet->VDreg.Double(result);
                                   }
                                   break;

    default: throw INTERNAL_ERROR; break;
  }
  
#ifdef DEBUG_VFP
  printf("[Control::vfpMath] exited.\n");
#endif
}

//---------------------------------------------------------------------------------------------------------------------------
// vfp rounding...
//---------------------------------------------------------------------------------------------------------------------------

void Control::vfpRounding() {
#ifdef DEBUG_VFP
  printf("[Control::vfpRounding] entered...\n");
#endif
  
  int datasize = 32;
  switch((int) packet->type.Value()) {
    case 0:  datasize = 32; break;
    case 1:  datasize = 64; break;
    default: // invalid datasize...
             printf("[Control::vfpRounding] invalid datasize???\n");
             packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
             throw ARCH_EXCEPTION;
             break;
  }

  bool exact = false;
  int rounding = 0;

  switch(packet->RMode()) {
    case 4:  rounding = 4; 
             break;
    case 5:  // invalid rounding specifier...
             printf("[Control::vfpRounding] invalid rounding specifier???\n");
             packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
             throw ARCH_EXCEPTION;
             break;
    case 6:  rounding = FPRoundingMode(); 
             exact = true; 
             break;
    case 7:  rounding = FPRoundingMode(); 
             break;
    default: rounding = packet->RMode() & 3; 
             break;
  }

  switch(datasize) {
    case 32: {
#ifdef DEBUG_VFP
              printf("[Control::vfpRounding] datasize: 32, exact: %d, RMode: 0x%x\n",exact, packet->RMode());
#endif
              float operand1 = packet->VNreg.Single();
              float result   = vfp_helper.FPRoundInt(operand1,rounding,exact);
 
#ifdef DEBUG_VFP
              printf("[Control::vfpRounding] operand1: %f (0x%x), result: %f (0x%x)\n",
                     operand1,(unsigned int) operand1,result,(unsigned int) result);
#endif
	      packet->VDreg.Single(result);

#ifdef DEBUG_VFP
              printf("[Control::vfpRounding] VD[%d]: 0x%llx\n",packet->Rd.Value(), packet->VDreg.Value());
#endif
             }
             break;
    case 64: {
#ifdef DEBUG_VFP
              printf("[Control::vfpRounding] datasize: 64, exact: %d, RMode: 0x%x\n",exact, packet->RMode());
#endif
              double operand1 = packet->VNreg.Double();
              double result = vfp_helper.FPRoundInt(operand1,rounding,exact);

              packet->VDreg.Double(result);
             }
             break;

    default: // how did we get here???
             packet->recordExceptionCondition(INTERNAL_ERROR);
             throw ARCH_EXCEPTION;
             break;
  }

#ifdef DEBUG_VFP
  printf("[Control::vfpRounding] exited.\n");
#endif
}

//---------------------------------------------------------------------------------------------------------------------------
// vfp comparison...
//---------------------------------------------------------------------------------------------------------------------------

void Control::vfpCompare() {
  bool signal_all_nans = (packet->opcode2.Value() & 0x10) == 0x10;
  bool cmp_with_zero   = (packet->opcode2.Value() & 8) == 8;

  switch((int) packet->type.Value()) {
    case 0:  // datasize = 32...
             { 
              float operand1 = packet->VNreg.Single();
              float operand2 = cmp_with_zero ? 0.0 : packet->VMreg.Single();
              packet->NextPstate.NZCV(vfp_helper.FPCompare(operand1,operand2,signal_all_nans));
             }
             break;

    case 1:  // datasize = 64...
             {
              double operand1 = packet->VNreg.Double();
              double operand2 = cmp_with_zero ? 0.0 : packet->VMreg.Double();
              packet->NextPstate.NZCV(vfp_helper.FPCompare(operand1,operand2,signal_all_nans));
	     }
             break;

    default: // invalid datasize...
             packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
             throw ARCH_EXCEPTION;
             break;
  }
}

//---------------------------------------------------------------------------------------------------------------------------
// vfp conditional comparison...
//---------------------------------------------------------------------------------------------------------------------------

void Control::vfpConditionalCompare() {
  bool signal_all_nans = packet->op.Value() == 1;
  unsigned int condition = packet->cond.Value();
  unsigned int flags = packet->nzcv.Value();

  switch((int) packet->type.Value()) {
    case 0:  // datasize = 32...
             {
              float operand1 = packet->VNreg.Single();
              float operand2 = packet->VMreg.Single();
              flags = ConditionHolds(condition) ? vfp_helper.FPCompare(operand1,operand2,signal_all_nans) : flags;
              packet->NextPstate.NZCV(flags);
	     }
             break;

    case 1:  // datasize = 64...
             {
              double operand1 = packet->VNreg.Double();
              double operand2 = packet->VMreg.Double();
              flags = ConditionHolds(condition) ? vfp_helper.FPCompare(operand1,operand2,signal_all_nans) : flags;
              packet->NextPstate.NZCV(flags);
	     }
             break;

    default: // invalid datasize...
             packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
             throw ARCH_EXCEPTION;
             break;
  }
}

//---------------------------------------------------------------------------------------------------------------------------
// vfp conditional select...
//---------------------------------------------------------------------------------------------------------------------------

void Control::vfpConditionalSelect() {
  switch(instrID) {
    case FCSEL_FROM_DP:        {
                                double selection = ConditionHolds(packet->cond.Value()) ? packet->VNreg.Double() : packet->VMreg.Double();
                                packet->VDreg.Double(selection);
                               }
			       break;
    case FCSEL_SINGLE_FROM_SP: {
                                float selection = ConditionHolds(packet->cond.Value()) ? packet->VNreg.Single() : packet->VMreg.Single();
                                packet->VDreg.Single(selection);
                               }
			       break;
    default: break;
  }
}

//---------------------------------------------------------------------------------------------------------------------------
// vfp move immediate...
//---------------------------------------------------------------------------------------------------------------------------

void Control::vfpMoveImm() {
  switch(instrID) {
    case FMOV_IMM_FROM_DP:        {
                                   unsigned long long imm = VFPExpandImm(64, packet->imm8.Value());
                                   packet->VDreg.UnsignedLong(imm);
                                  }
                                  break;
    case FMOV_IMM_SINGLE_FROM_SP: {
                                   unsigned int imm = (unsigned int) VFPExpandImm(32, packet->imm8.Value());
                                   packet->VDreg.Unsigned(imm);
                                  }
                                  break;
    default: break;
  }
}

//---------------------------------------------------------------------------------------------------------------------------
// vfp convert precision...
//---------------------------------------------------------------------------------------------------------------------------

void Control::vfpFPConvert() {
  packet->opc.Value(packet->opcode.Value() & 3); // OOPS! instruction decode missed this field, gasp!

  if (packet->type.Value() == packet->opc.Value()) {
     packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
     throw ARCH_EXCEPTION;
  }
 
  int srcsize = 0;

  switch((int) packet->type.Value()) {
    case 0:  srcsize = 32; 
             break;
    case 1:  srcsize = 64; 
             break;
    case 2:  packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
             throw ARCH_EXCEPTION;
             break;
    case 3:  srcsize = 16;
             break;
    default: packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
             throw ARCH_EXCEPTION;
             break;
  }

  int dstsize = 0;

  switch((int) packet->opc.Value()) {
    case 0:  dstsize = 32; 
             break;
    case 1:  dstsize = 64; 
             break;
    case 2:  packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
             throw ARCH_EXCEPTION;
             break;
    case 3:  dstsize = 16;
             break;
    default: packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
             throw ARCH_EXCEPTION;
             break;
  }

  switch(srcsize) {
  case 32: if (dstsize == 32) {
             packet->VDreg.Single(packet->VNreg.Single());
           } else if (dstsize == 64) {
             packet->VDreg.Double((double) packet->VNreg.Single());
           } else {
             // float to half-precision...
#ifdef NO_HALF_FLOAT
             packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
#else
             packet->VDreg.Half((unsigned long long) FPFloatToHalfPrecision(packet->VNreg.Single()));
#endif
           } 
           break;
  case 64: if (dstsize == 32) {
             packet->VDreg.Single((float) packet->VNreg.Double());
           } else if (dstsize == 64) {
             packet->VDreg.Double(packet->VNreg.Double());
           } else {
             // double to half-precision...
#ifdef NO_HALF_FLOAT
             packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
#else
             packet->VDreg.Half((unsigned long long) FPDoubleToHalfPrecision(packet->VNreg.Double()));
#endif
           } 
           break;

  case 16: if (dstsize == 32) {
	     // half-precision to float...
#ifdef NO_HALF_FLOAT
             packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
#else
             packet->VDreg.Single(FPHalfPrecisionToFloat((unsigned int) packet->VNreg.Value()));
#endif
	   } else if (dstsize == 64) {
	     // half-precision to double...
#ifdef NO_HALF_FLOAT
             packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
#else
             packet->VDreg.Double(FPHalfPrecisionToDouble((unsigned int) packet->VNreg.Value()));
#endif
	   } else {
             // half-precision to half-precision, ie, straight copy...
             packet->VDreg.Value(packet->VNreg.Value());
             packet->VDreg.ValueHi(0);
	   }
           break;            

  default: break;
  }
}

//---------------------------------------------------------------------------------------------------------------------------
// vfp move...
//---------------------------------------------------------------------------------------------------------------------------

void Control::vfpMove() {
#ifdef DEBUG_VFP
  printf("[Control::vfpMove] entered...\n");
#endif
  
  int intsize = (packet->sf.Value() == 1) ? 64 : 32;
  int fltsize = 0;
  int op = 0;
  int rounding = 0;
  bool is_unsigned = false;
  int part = 0;
  int scale = 0;

  int t_op = ( (packet->opcode.Value()>>1 & 3)<<2 ) | packet->rmode.Value();

  switch((int) packet->type.Value()) {
    case 0:  fltsize = 32; 
             break;
    case 1:  fltsize = 64; 
             break;
    case 2:  if ( t_op != 0xd) {
               packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
               throw ARCH_EXCEPTION;
             }
             fltsize = 128; 
             break;
    default: packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
             throw ARCH_EXCEPTION;
             break;
  }

#ifdef DEBUG_VFP
  printf("  int-size: %d, flt-size: %d, t_op: %d\n",intsize,fltsize,t_op);
#endif
  
  enum { FPConvOp_CVT_FtoI, FPConvOp_CVT_ItoF, FPConvOp_MOV_ItoF, FPConvOp_MOV_FtoI };

  switch(t_op) {
    case 0:
    case 1:
    case 2:
    case 3:   // FCVT[NPMZ][US]
              rounding = packet->rmode.Value();
              is_unsigned = (packet->opcode.Value() & 1) == 1;
              op = FPConvOp_CVT_FtoI;
              break;
   case 4:    // [US]CVTF
              rounding = FPRoundingMode();
              is_unsigned = (packet->opcode.Value() & 1) == 1;
              op = FPConvOp_CVT_ItoF;
              break;
    case 8:   // FCVTA[US]
              rounding = 4;
              is_unsigned = (packet->opcode.Value() & 1) == 1;
              op = FPConvOp_CVT_FtoI;
              break;
    case 0xc: // FMOV
              if (fltsize != intsize) {
                packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
                throw ARCH_EXCEPTION;
              }
              op = ( (packet->opcode.Value() & 1) == 1 ) ? FPConvOp_MOV_ItoF : FPConvOp_MOV_FtoI; 
              part = 0;
              break;
    case 0xd: // FMOV D[1]
              if ( (intsize != 64) || (fltsize != 128) ) {
                packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
                throw ARCH_EXCEPTION;
              }
              op = ( (packet->opcode.Value() & 1) == 1 ) ? FPConvOp_MOV_ItoF : FPConvOp_MOV_FtoI; 
              part = 1;
              break;

    default:  packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
              throw ARCH_EXCEPTION;
              break;
  }

#ifdef DEBUG_VFP
  printf("  op: %d\n",op);
#endif
  
  switch(instrID) {
    case FCVTZS_FROM_DP_FP_FIXED_32: 
    case FCVTZS_FROM_DP_FP_FIXED_64: 
    case FCVTZS_SINGLE_FROM_SP_FP_FIXED_32: 
    case FCVTZS_SINGLE_FROM_SP_FP_FIXED_64: 
    case FCVTZU_FROM_DP_FP_FIXED_32: 
    case FCVTZU_FROM_DP_FP_FIXED_64: 
    case FCVTZU_SINGLE_FROM_SP_FP_FIXED_32: 
    case FCVTZU_SINGLE_FROM_SP_FP_FIXED_64:
    case SCVTF_SINGLE_TO_SP_FP_FIXED_32:
    case SCVTF_SINGLE_TO_SP_FP_FIXED_64:
    case SCVTF_TO_DP_FP_FIXED_32:
    case SCVTF_TO_DP_FP_FIXED_64:
    case UCVTF_SINGLE_TO_SP_FP_FIXED_32:
    case UCVTF_SINGLE_TO_SP_FP_FIXED_64:
    case UCVTF_TO_DP_FP_FIXED_32:
    case UCVTF_TO_DP_FP_FIXED_64:       
             scale = 64 - packet->scale.Value();
             if ( (intsize == 32) && (packet->scale.Value() < 32) ) { 
               packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
               throw ARCH_EXCEPTION;
	     }
             break;
    default: break;
  }

  switch(op) {
    case FPConvOp_CVT_FtoI: switch(fltsize) {
                              case 32: {
				        
				        float fltval = packet->VNreg.Single();
#ifdef DEBUG_VFP
					printf("[Control::vfpMove] FPConvOp_CVT_FtoI(32) / V[n]: 0x%llx, as float: %f\n",packet->VNreg.Value(),fltval);
#endif					
                                        unsigned long long intval = vfp_helper.FPToFixed32(fltval,scale,is_unsigned,rounding,intsize);
#ifdef DEBUG_VFP
					printf("[Control::vfpMove] fltval: %f (0x%llx), intval: %d (0x%llx)\n",fltval,packet->VNreg.Value(),(int) intval, intval);
#endif
                                        packet->Dreg.Value(intval);
                                       }
	                               break;
                              case 64: {
                                        double fltval = packet->VNreg.Double();
#ifdef DEBUG_VFP
					printf("[Control::vfpMove] FPConvOp_CVT_FtoI(64) / V[n]: 0x%llx, as double: %g\n",packet->VNreg.Value(),fltval);
#endif					
                                        unsigned long long intval = vfp_helper.FPToFixed64(fltval,scale,is_unsigned,rounding,intsize);
#ifdef DEBUG_VFP
					printf("[Control::vfpMove] fltval: %f (0x%llx), intval: 0x%llx\n",fltval,packet->VNreg.Value(),intval);
#endif
                                        packet->Dreg.Value(intval);
                                       }
	                               break;
                              default: break;
                            }
                            break;

    case FPConvOp_CVT_ItoF:
                            switch(fltsize) {
                              case 32: {
	                                unsigned long long intval = packet->Nreg.Value();
	                                float fltval = vfp_helper.FixedToFP32(intval,scale,is_unsigned,rounding,intsize);
                                        packet->VDreg.Single(fltval);
#ifdef DEBUG_VFP
					printf("[Control::vfpMove] FPConvOp_CVT_ItoF(32) / fltval: %f, intval: 0x%llx\n",fltval,intval);
#endif					
	                               }
	                               break;
                              case 64: {
	                                unsigned long long intval = packet->Nreg.Value();
	                                double fltval = vfp_helper.FixedToFP64(intval,scale,is_unsigned,rounding,intsize);
                                        packet->VDreg.Double(fltval);
#ifdef DEBUG_VFP
					printf("[Control::vfpMove] FPConvOp_CVT_ItoF(64) / fltval: %f, intval: 0x%llx\n",fltval,intval);
#endif
	                               }
	                               break;
			    default: break;
                            }
                            break;

    case FPConvOp_MOV_FtoI: {
	                     unsigned long long intval = (part == 1) ? packet->VNreg.ValueHi() : packet->VNreg.Value();
                             packet->Dreg.Value(intval);
#ifdef DEBUG_VFP
			     printf("[Control::vfpMove] FPConvOp_MOV_FtoI / intval: 0x%llx\n",intval);
#endif					
                            }
	                    break;
         
    case FPConvOp_MOV_ItoF: {
	                     unsigned long long intval = packet->Nreg.Value();
                             if (part == 1)
                               packet->VDreg.ValueHi(intval);
                             else {
                               packet->VDreg.Value(intval);
			       packet->VDreg.SetType(FL_DOUBLE);
                               packet->VDreg.ValueHi(0);
			     }
#ifdef DEBUG_VFP
			     printf("[Control::vfpMove] FPConvOp_MOV_ItoF / part: %d intval: 0x%llx\n",part,intval);
#endif					
                            }
	                    break;

    default: throw INTERNAL_ERROR;
    break;
  }
}

//---------------------------------------------------------------------------------------------------------------------------
// vfp load/store pair...
//---------------------------------------------------------------------------------------------------------------------------

void Control::vfpLoadStorePair() {
  bool wback = false;
  bool postindex = false;
  
  switch(instrID) {
    case SIMD_LDP_REG_PRE_32:
    case SIMD_LDP_REG_PRE_64:
    case SIMD_LDP_REG_PRE_8_128:  
    case SIMD_STP_REG_PRE_32:
    case SIMD_STP_REG_PRE_64:
    case SIMD_STP_REG_PRE_8_128:  wback = true;
                                  postindex = false;
                                  break;
    case SIMD_LDP_REG_OFF_32:
    case SIMD_LDP_REG_OFF_64:
    case SIMD_LDP_REG_OFF_8_128:  
    case SIMD_LDNP_OFF_32:
    case SIMD_LDNP_OFF_64:
    case SIMD_LDNP_OFF_8_128:     
    case SIMD_STP_REG_OFF_32:
    case SIMD_STP_REG_OFF_64:
    case SIMD_STP_REG_OFF_8_128:  
    case SIMD_STNP_OFF_32:
    case SIMD_STNP_OFF_64:
    case SIMD_STNP_OFF_8_128:     wback = false;
                                  postindex = false;
                                  break;
    case SIMD_STP_REG_POST_32:
    case SIMD_STP_REG_POST_64:
    case SIMD_STP_REG_POST_8_128: wback = true;
                                  postindex = true;
                                  break;
    default: throw INTERNAL_ERROR;
             break;
  }

  bool is_load = packet->L.Value() == 1;

  if (packet->opc.Value() == 3) {
    packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
    throw ARCH_EXCEPTION;
  }

  if (is_load && (packet->Rt.Value() == packet->Rt2.Value())) {
    // disallow unpredictable case...
    packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
    throw ARCH_EXCEPTION;
  }
 
  int scale    = 2 + (int) packet->opc.Value();
  int datasize = 8<<scale; //<---# of bits for one item accessed (32 or 64 or 128)...

  long long offset = LSL(SignExtend(packet->imm7.Value(),7),scale);

  unsigned long long address = lsOffsetBaseAddress(packet->Rn.Value(),postindex ? 0 : offset,false);

  int  dbytes         = datasize / 8; //<---# of bytes per access (4 or 8 or 16)...
  int  total_bytes    = dbytes * 2;   // <---total # of bytes accessed (8 or 16 or 32)
  int  acctype        = VECTOR;       // Vector access
  bool excl           = false;        // not an exclusive op...
  int  memop          = is_load ? FOR_READ : FOR_WRITE;
  int  word_size      = dbytes;       // total # of bytes accessed divided by # of registers loaded (2 of course)
  bool do_sign_extend = false;        // no sign extension
  int  signextend_to  = 32;           // if ignored
  bool pair           = true;
  bool privileged     = packet->Pstate.Privileged();

  MemoryAccess memacc(address,total_bytes,acctype,excl,memop,BigEndian(),word_size,do_sign_extend,signextend_to,pair,privileged);

  if (memop == FOR_WRITE) {
    // ST(VTreg), ST2(VT2reg) <---SHOULD BE SAVING THESE REGISTERS...
    if (datasize == 128) {
      // Q register pair, each register is 128 bits...
      SaveRegisterPair(packet->VTreg.Value(), packet->VTreg.ValueHi(),  memacc.membuffer,     word_size,BigEndian(),excl);
      SaveRegisterPair(packet->VT2reg.Value(),packet->VT2reg.ValueHi(),&memacc.membuffer[16], word_size,BigEndian(),excl);
    } else {
      // two register values, each no more than 64 bits...
      SaveRegisterPair(packet->VTreg.Value(),packet->VT2reg.Value(),memacc.membuffer,word_size,BigEndian(),excl);
    }
  }

  packet->mOpsMemory.push_back(memacc);

  if (wback) {
    if (postindex) {
      address = lsOffsetBaseAddress(packet->Rn.Value(),offset,false);
    }  
    packet->Nreg.Value(address);
    packet->mOpsWriteback.push_back(XNSP);
  }
}

//---------------------------------------------------------------------------------------------------------------------------
// vfp loads...
//---------------------------------------------------------------------------------------------------------------------------

void Control::vfpLoadLiteral() {
  int memop = FOR_READ;
  int acctype = VECTOR;
  int size = 0;
  bool do_sign_extend = false;
  int signextend_to = 64;

  switch((int) packet->opc.Value()) {
    case 0: size = 4;  break;
    case 1: size = 8;  break;
    case 2: size = 16; break;
    default: packet->recordExceptionCondition(INVALID_OPC_FIELD,LOAD_REG_LITERAL);
             throw INTERNAL_ERROR;
             break;
  }

  int regsize = size;

  long long offset = SignExtend(packet->imm19.Value()<<2,21);

  unsigned long long address = PCrelativeAddress(offset);

  MemoryAccess memacc(address,size,acctype,false,memop,BigEndian(),regsize,do_sign_extend,signextend_to,false,packet->Pstate.Privileged());

  packet->mOpsMemory.push_back(memacc);
}

//---------------------------------------------------------------------------------------------------------------------------
// vfp load/store register (immediate offset)...
//---------------------------------------------------------------------------------------------------------------------------

void Control::vfpLoadStore() {
  bool wback = false;
  bool postindex = false;
  int scale = (packet->opc.Value()&2)<<1 | packet->size.Value();
  if (scale > 4) {
    packet->recordExceptionCondition(INVALID_OPC_FIELD,LOAD_REG_LITERAL);
    throw INTERNAL_ERROR;
  }
  long long offset = 0;

  switch(instrID) {
    case SIMD_LDR_IMM_REG_POST_8:
    case SIMD_LDR_IMM_REG_POST_16: 
    case SIMD_LDR_IMM_REG_POST_32: 
    case SIMD_LDR_IMM_REG_POST_64: 
    case SIMD_LDR_IMM_REG_POST_8_128: 
    case SIMD_STR_IMM_REG_POST_8:
    case SIMD_STR_IMM_REG_POST_16: 
    case SIMD_STR_IMM_REG_POST_32: 
    case SIMD_STR_IMM_REG_POST_64: 
    case SIMD_STR_IMM_REG_POST_8_128: wback = true;
                                      postindex = true;
                                      offset = SignExtend(packet->imm9.Value(),9);
                                      break;

    case SIMD_LDR_IMM_REG_PRE_8:
    case SIMD_LDR_IMM_REG_PRE_16: 
    case SIMD_LDR_IMM_REG_PRE_32: 
    case SIMD_LDR_IMM_REG_PRE_64: 
    case SIMD_LDR_IMM_REG_PRE_8_128: 
    case SIMD_STR_IMM_REG_PRE_8:
    case SIMD_STR_IMM_REG_PRE_16: 
    case SIMD_STR_IMM_REG_PRE_32: 
    case SIMD_STR_IMM_REG_PRE_64: 
    case SIMD_STR_IMM_REG_PRE_8_128: wback = true;
                                     postindex = false;
                                     offset = SignExtend(packet->imm9.Value(),9);
                                     break;

    case SIMD_LDR_IMM_REG_8:
    case SIMD_LDR_IMM_REG_16: 
    case SIMD_LDR_IMM_REG_32: 
    case SIMD_LDR_IMM_REG_64: 
    case SIMD_LDR_IMM_REG_8_128: 
    case SIMD_STR_IMM_REG_8:
    case SIMD_STR_IMM_REG_16: 
    case SIMD_STR_IMM_REG_32: 
    case SIMD_STR_IMM_REG_64: 
    case SIMD_STR_IMM_REG_8_128:     postindex = false;
                                     offset = LSL(packet->imm12.Value(),scale);
                                     break;

    default: throw INTERNAL_ERROR;
             break;
  }

  int datasize = 8<<scale;

  unsigned long long address = lsOffsetBaseAddress(packet->Rn.Value(),postindex ? 0 : offset,false);

  int  dbytes         = datasize / 8;
  int  acctype        = VECTOR; // Vector access
  bool excl           = false;
  int  memop          = ((packet->opc.Value() & 1) == 1) ? FOR_READ : FOR_WRITE;
  int  word_size      = dbytes;
  bool do_sign_extend = false;
  int  signextend_to  = 32;
  bool pair           = false;
  bool privileged     = packet->Pstate.Privileged();

  MemoryAccess memacc(address,dbytes,acctype,excl,memop,BigEndian(),word_size,do_sign_extend,signextend_to,pair,privileged);

  if (memop == FOR_WRITE) {
    unsigned long long data1 = packet->VTreg.Value();
    if (dbytes == 16) {
      unsigned long long data2 = packet->VTreg.ValueHi();
      SaveRegisterPair(data1,data2,memacc.membuffer,8,BigEndian(),excl);
    } else {
      SaveRegister(data1,memacc.membuffer,word_size,BigEndian());
    }
  }

  packet->mOpsMemory.push_back(memacc);

  if (wback) {
    if (postindex) {
      address = lsOffsetBaseAddress(packet->Rn.Value(),offset,false);
    }  
    packet->Nreg.Value(address);
    packet->mOpsWriteback.push_back(XNSP);
  }
}

//---------------------------------------------------------------------------------------------------------------------------
// vfp load/stores - register offset...
//---------------------------------------------------------------------------------------------------------------------------

void Control::vfpLoadStoreRegisterOffset() {
  int scale = (packet->opc.Value()&2)<<1 | packet->size.Value();

  if (scale > 4) {
    packet->recordExceptionCondition(INVALID_OPC_FIELD,LOAD_REG_LITERAL);
    throw INTERNAL_ERROR;
  }

  if ( (packet->option.Value() & 2) == 0) {
    // sub-word index...
    packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
    throw ARCH_EXCEPTION;
  }

  int extend_type = DecodeRegExtend(packet->option.Value());
  int shift = packet->S.Value() == 1 ? scale : 0;

  int acctype = VECTOR;

  bool excl = false;

  int memop = ((packet->opc.Value() & 1) == 1) ? FOR_READ : FOR_WRITE;
  int datasize = 8<<scale;

  int index_width = ((packet->option.Value() & 1) == 1) ? 64 : 32;
  bool is_signed = false;
  int signextend_to = 32;

  int dbytes = datasize / 8;
  int word_size = dbytes;

  // retreive index register value; constrain to 32 bits if necessary...
  unsigned long long index_rval = packet->Mreg.Value();
  if (index_width == 32)
    index_rval &= 0xffffffffull;
  
  unsigned long long off = ExtendReg(index_rval,extend_type,shift,64); // offset always extended to 64 bits

  long long offset = (long long) off;

  unsigned long long address = lsOffsetBaseAddress(packet->Rn.Value(),offset,false);

  MemoryAccess memacc(address,dbytes,acctype,false,memop,BigEndian(),word_size,is_signed,signextend_to,false,packet->Pstate.Privileged());

  if (memop == FOR_WRITE) {
    unsigned long long data1 = packet->VTreg.Value();
    if (dbytes == 16) {
      unsigned long long data2 = packet->VTreg.ValueHi();
      SaveRegisterPair(data1,data2,memacc.membuffer,8,BigEndian(),excl);
    } else {
      SaveRegister(data1,memacc.membuffer,word_size,BigEndian());
    }
  }

  packet->mOpsMemory.push_back(memacc);
}
