#include "a64sim.h"

// APP_LEVEL_ONLY - used to limit spr access during initial simulator bringup...

//#define APP_LEVEL_ONLY 1

// check accessibility of system register based on current PL, etc.

enum SREG_GENERIC_CHECK_OUTCOMES { ACCESS_OKAY, UNALLOCATED_ENCODING_SYSOP, UNALLOCATED_ENCODING_EL, UNALLOCATED_ENCODING_SECURE,
                                   SYSTEM_REG_TRAP };

bool State::SystemRegisterTrapOutcome(int rcode) {
  return rcode == SYSTEM_REG_TRAP;
}

int State::CheckSystemRegisterAccess(unsigned int sys_op1) {
  int outcome = ACCESS_OKAY;

  unsigned min_EL = 0;
  bool need_secure = false;

  switch((int) sys_op1) {
    case 0:
    case 1:
    case 2: min_EL = 1; 
            break;
    case 3: min_EL = 0; 
            break;
    case 4: min_EL = 2; 
            break;
    case 5: outcome = UNALLOCATED_ENCODING_SYSOP; 
            break;
    case 6: min_EL = 3; 
            break;
    case 7: min_EL = 1; need_secure = true; 
            break;
    default: break;
  }
  if (outcome == UNALLOCATED_ENCODING_SYSOP) {
    // bad op1 encoding...
  } else if (Pstate.EL() < min_EL) {
    // access not valid for current privilege level...
    outcome = UNALLOCATED_ENCODING_EL;
  } else if (need_secure && !IsSecure()) {
    // secure state violation...
    outcome = UNALLOCATED_ENCODING_SECURE;
  }

  return outcome;
}

int State::EncodeRegisterID(unsigned int op0,unsigned int op1,unsigned int CRn,unsigned int CRm,unsigned int op2) {
  return (op0 << 16) | (op1 << 12) | (CRn << 8) | (CRm << 4) | op2;
}

int State::GetSPindex() {
  return (int) (Pstate.SP() == 0) ? 0 : Pstate.EL();
}

Register State::GetSP() {
  Register SP;
  int stack_ptr_index = (int) (Pstate.SP() == 0) ? 0 : Pstate.EL();
  switch(stack_ptr_index) {
    case 0: SP = SP_EL0; break;
    case 1: SP = SP_EL1; break;
    case 2: SP = SP_EL2; break;
    case 3: SP = SP_EL3; break;
    default: break; // internal error
  }
  return SP;
}

void State::UpdateSP(Register SP) {
  int stack_ptr_index = (int) (Pstate.SP() == 0) ? 0 : Pstate.EL();
  switch(stack_ptr_index) {
    case 0: SP_EL0 = SP; break;
    case 1: SP_EL1 = SP; break;
    case 2: SP_EL2 = SP; break;
    case 3: SP_EL3 = SP; break;
    default: break; // internal error
  }
}

int State::SystemRegisterGet(int &sysreg_id,unsigned long long &rval,unsigned int op0,unsigned int op1,unsigned int crn,unsigned int crm,unsigned int op2) {
  //printf("[State::SystemRegisterGet] op0: %u op1: %u crn: %u crm: %u op2: %u\n",op0,op1,crn,crm,op2);
  //fflush(stdout);
  
  int rcode = CheckSystemRegisterAccess(op1);
  
  if (rcode != ACCESS_OKAY) {
    //printf("OOPS! can 't access system reg at this EL level?\n");
    return rcode;
  }
  
  sysreg_id = EncodeRegisterID(op0,op1,crn,crm,op2);

  // op0 << 16) | (op1 << 12) | (CRn << 8) | (CRm << 4) | op2;

  //printf("sys reg id: 0x%x\n",sysreg_id);
  
  switch(sysreg_id) {      
    case 0x33440: rval = FPCR.Value(); break;
    case 0x33441: rval = FPSR.Value(); break; 
    case 0x36110: rval = SCR_EL3.Value(); break;
    case 0x30400: rval = SPSR_EL1.Value(); break; 
    case 0x30420: rval = Pstate.SP(); break;
    case 0x30422: rval = Pstate.CurrentEL(); break;
    case 0x33420: rval = Pstate.NZCV()<<28; break;
#ifndef APP_LEVEL_ONLY
    case 0x33421: rval = Pstate.DAIF(); break;
#endif
    case 0x34400: rval = SPSR_EL2.Value(); break;
    case 0x36400: rval = SPSR_EL3.Value(); break;
    case 0x30050: rval = ID_AA64DFR0_EL1.Value();  break; 
    case 0x30070: rval = ID_AA64MMFR0_EL1.Value(); break; 
    case 0x30040: rval = ID_AA64PFR0_EL1.Value();  break;
    case 0x30060: rval = ID_AA64ISAR0_EL1.Value(); break;
    case 0x30102: rval = CPACR_EL1.Value(); break;
    case 0x34112: rval = CPTR_EL2.Value(); break;
    case 0x36112: rval = CPTR_EL3.Value(); break;
    case 0x30000: rval = MIDR_EL1.Value(); break;
    case 0x34000: rval = VPIDR_EL2.Value(); break; 
    case 0x30006: rval = REVIDR_EL1.Value(); break;
    case 0x30005: rval = MPIDR_EL1.Value(); break; 
    case 0x34005: rval = VMPIDR_EL2.Value(); break;
#ifndef APP_LEVEL_ONLY
    case 0x33001: rval = CTR_EL0.Value(); break;
    case 0x33007: rval = DCZID_EL0.Value(); break;
#endif
    case 0x30c01: rval = RVBAR_EL1.Value(); break;
    case 0x34c01: rval = RVBAR_EL2.Value(); break;
    case 0x36c01: rval = RVBAR_EL3.Value(); break;
#ifndef APP_LEVEL_ONLY
    case 0x23010: rval = MDCCSR_EL0.Value(); break; 
    case 0x20022: rval = MDSCR_EL1.Value(); break;
    case 0x36131: rval = MDCR_EL3.Value(); break;
    case 0x20134: rval = OSDLR_EL1.Value(); break;
    case 0x20104: rval = OSLAR_EL1.Value(); break;
    case 0x20114: rval = OSLSR_EL1.Value(); break;
    case 0x23040: rval = DBGDTR_EL0.Value(); break;  
    case 0x23050: rval = DBGDTRRX_EL0.Value(); break;
    case 0x33451: rval = DLR_EL0.Value(); break;
    case 0x33450: rval = DSPSR_EL0.Value(); break;
#endif
    case 0x30d01: rval = CONTEXTIDR_EL1.Value(); break;
    case 0x30740: rval = PAR_EL1.Value(); break;
#ifndef APP_LEVEL_ONLY
    case 0x33d02: rval = TPIDR_EL0.Value(); break;
#endif
    case 0x30d04: rval = TPIDR_EL1.Value(); break;
    case 0x34d02: rval = TPIDR_EL2.Value(); break;
    case 0x36d02: rval = TPIDR_EL3.Value(); break;
    case 0x30401: rval = ELR_EL1.Value(); break;
    case 0x34401: rval = ELR_EL2.Value(); break;
    case 0x36401: rval = ELR_EL3.Value(); break;
    case 0x30520: rval = ESR_EL1.Value(); break;
    case 0x34520: rval = ESR_EL2.Value(); break;
    case 0x36520: rval = ESR_EL3.Value(); break;
    case 0x30600: rval = FAR_EL1.Value(); break; 
    case 0x34600: rval = FAR_EL2.Value(); break;
    case 0x36600: rval = FAR_EL3.Value(); break;
    case 0x30c00: rval = VBAR_EL1.Value(); break;
    case 0x34c00: rval = VBAR_EL2.Value(); break;
    case 0x36c00: rval = VBAR_EL3.Value(); break;
    case 0x30202: rval = TCR_EL1.Value(); break;
    case 0x34202: rval = TCR_EL2.Value(); break;
    case 0x36202: rval = TCR_EL3.Value(); break;
    case 0x30a20: rval = MAIR_EL1.Value(); break;
    case 0x34a20: rval = MAIR_EL2.Value(); break; 
    case 0x36a20: rval = MAIR_EL3.Value(); break;
    case 0x30c02: rval = RMR_EL1.Value(); break;
    case 0x34c02: rval = RMR_EL2.Value(); break;
    case 0x36c02: rval = RMR_EL3.Value(); break;
    case 0x30510: rval = AFSR0_EL1.Value(); break;
    case 0x34510: rval = AFSR0_EL2.Value(); break;
    case 0x36510: rval = AFSR0_EL3.Value(); break;
    case 0x30511: rval = AFSR1_EL1.Value(); break;
    case 0x34511: rval = AFSR1_EL2.Value(); break; 
    case 0x36511: rval = AFSR1_EL3.Value(); break; 
    case 0x30410: rval = SP_EL0.Value(); break;
    case 0x34410: rval = SP_EL1.Value(); break;
    case 0x36410: rval = SP_EL2.Value(); break;
    case 0x36411: rval = SP_EL3.Value(); break;
    case 0x30100: rval = SCTLR_EL1.Value(); break;
    case 0x34100: rval = SCTLR_EL2.Value(); break;
    case 0x36100: rval = SCTLR_EL3.Value(); break;
    case 0x30200: rval = TTBR0_EL1.Value(); break;
    case 0x30201: rval = TTBR1_EL1.Value(); break;
    case 0x34200: rval = TTBR0_EL2.Value(); break;
    case 0x36200: rval = TTBR0_EL3.Value(); break;
    case 0x34110: rval = HCR_EL2.Value(); break;
    case 0x36101: rval = ACTLR_EL3.Value(); break;

      
    // timer related regs:
      
  case 0x33e00: if ( (CNTKCTL_EL1.EL0PCTEN() == 0) && (CNTKCTL_EL1.EL0VCTEN() == 0) && (Pstate.EL() == 0) )
	            rcode = SYSTEM_REG_TRAP;
                  else
                    rval = CNTFRQ_EL0.Value();
                  break;
		  
    case 0x34e10: rval = CNTHCTL_EL2.Value();    break;        
    case 0x34e21: rval = CNTHP_CTL_EL2.Value();  break;   // hypervisor regs - not supported
    case 0x34e22: rval = CNTHP_CVAL_EL2.Value(); break;
    case 0x34e20: rval = CNTHP_TVAL_EL2.Value(); break;
      
    case 0x30E10: rval = CNTKCTL_EL1.Value(); break;

    case 0x33e21: if ( (CNTKCTL_EL1.EL0PTEN() == 0) && (Pstate.EL() == 0) )
	            rcode = SYSTEM_REG_TRAP;
		  else
		    rval = CNTP_CTL_EL0.Value();
                  break;
    case 0x33e22: if ( (CNTKCTL_EL1.EL0PTEN() == 0) && (Pstate.EL() == 0) )
	            rcode = SYSTEM_REG_TRAP;
		  else
		    rval = CNTP_CVAL_EL0.Value();
                  break;
    case 0x33e20: if ( (CNTKCTL_EL1.EL0PTEN() == 0) && (Pstate.EL() == 0) )
	            rcode = SYSTEM_REG_TRAP;
		  else
		    rval = CNTP_TVAL_EL0.Value();
		  break;
      
    case 0x33e01: if ( (CNTKCTL_EL1.EL0PCTEN() == 0) && (Pstate.EL() == 0) )
	            rcode = SYSTEM_REG_TRAP;
		  else
		    rval = CNTPCT_EL0.Value();
                  break;
      
    case 0x37e21: if (SCR_EL3.ST() == 0)
		    rcode = SYSTEM_REG_TRAP;
		  else
		    rval = CNTPS_CTL_EL1.Value();  // in this implementation is same as CNTP_CTL_EL1
                  break;
    case 0x37e22: if (SCR_EL3.ST() == 0)
		    rcode = SYSTEM_REG_TRAP;
		  else
		    rval = CNTPS_CVAL_EL1.Value(); // in this implementation is same as CNTP_CVAL_EL1
                  break;
    case 0x37e20: if (SCR_EL3.ST() == 0)
		    rcode = SYSTEM_REG_TRAP;
		  else
		    rval = CNTPS_TVAL_EL1.Value(); // in this implementation is same as CNTP_TVAL_EL1
                  break;

    case 0x33e31: if ( (CNTKCTL_EL1.EL0VTEN() == 0) && (Pstate.EL() == 0) )
	            rcode = SYSTEM_REG_TRAP;
		  else
		    rval = CNTV_CTL_EL0.Value();
                  break;
    case 0x33e32: if ( (CNTKCTL_EL1.EL0VTEN() == 0) && (Pstate.EL() == 0) )
	            rcode = SYSTEM_REG_TRAP;
		  else
		    rval = CNTV_CVAL_EL0.Value();
                  break;
    case 0x33e30: if ( (CNTKCTL_EL1.EL0VTEN() == 0) && (Pstate.EL() == 0) )
	            rcode = SYSTEM_REG_TRAP;
		  else
		    rval = CNTV_TVAL_EL0.Value();
                  break;
      
    case 0x33e02: if ( (CNTKCTL_EL1.EL0VCTEN() == 0) && (Pstate.EL() == 0) )
	            rcode = SYSTEM_REG_TRAP;
		  else
		    rval = CNTVCT_EL0.Value();
                  break;
		  
    case 0x34e03: rval = CNTVOFF_EL2.Value(); break;  // hypervisor reg - not supported

      
    case 0x30460: rval = ICC_PMR_EL1.Value(); break;
    case 0x30c80: rval = ICC_IAR0_EL1.Value(); break;
    case 0x30c81: rval = ICC_EORI0_EL1.Value(); break;
    case 0x30c82: rval = ICC_HPPIR0_EL1.Value(); break;
    case 0x30c83: rval = ICC_BPR0_EL1.Value(); break;     
    case 0x30c84: rval = ICC_AP0R0_EL1.Value(); break;
    case 0x30c85: rval = ICC_AP0R1_EL1.Value(); break;
    case 0x30c86: rval = ICC_AP0R2_EL1.Value(); break;
    case 0x30c87: rval = ICC_AP0R3_EL1.Value(); break;
    case 0x30c90: rval = ICC_AP1R0_EL1.Value(); break;
    case 0x30c91: rval = ICC_AP1R1_EL1.Value(); break;
    case 0x30c92: rval = ICC_AP1R2_EL1.Value(); break;
    case 0x30c93: rval = ICC_AP1R3_EL1.Value(); break;
    case 0x30cb1: rval = ICC_DIR_EL1.Value(); break;
    case 0x30cb3: rval = ICC_RPR_EL1.Value(); break;
    case 0x30cb5: rval = ICC_SGI1R_EL1.Value(); break;
    case 0x30cb6: rval = ICC_ASGI1R_EL1.Value(); break;
    case 0x30cb7: rval = ICC_SGI0R_EL1.Value(); break;
    case 0x30cc0: rval = ICC_IAR1_EL1.Value(); break;
    case 0x30cc1: rval = ICC_EOIR1_EL1.Value(); break;
    case 0x30cc2: rval = ICC_HPPIR1_EL1.Value(); break;
    case 0x30cc3: rval = ICC_BPR1_EL1.Value(); break;
    case 0x30cc4: rval = ICC_CTLR_EL1.Value(); break;
    case 0x30cc5: rval = ICC_SRE_EL1.Value(); break;
    case 0x30cc6: rval = ICC_IGRPEN0_EL1.Value(); break;
    case 0x30cc7: rval = ICC_IGRPEN1_EL1.Value(); break;
    case 0x30c95: rval = ICC_SRE_EL2.Value(); break;
    case 0x36cc4: rval = ICC_CTLR_EL3.Value(); break;
    case 0x36cc5: rval = ICC_SRE_EL3.Value(); break;
    case 0x36cc7: rval = ICC_IGRPEN1_EL3.Value(); break;

    default: rcode = UNALLOCATED_ENCODING_SYSOP; break;
  }

  return rcode;
}

// decode cache or tlb maintenance op...

bool State::SysOp(int &sysop_type, int &sysop_index, unsigned int op0,unsigned int op1,unsigned int CRn,unsigned int CRm,unsigned int op2) {
  sysop_type = SYSOP_UNKNOWN;
  sysop_index = EncodeRegisterID(0 /* ignore op0 */,op1,CRn,CRm,op2);
  
  bool have_sysop = false;

  switch(sysop_index) {
    // Sys_AT...
    case S1E1R: case S1E2R: case S1E3R: case S1E1W: case S1E2W: case S1E3W: case S1E0R: case S1E0W:
    case S12E1R: case S12E1W: case S12E0R: case S12E0W:
      sysop_type = SYSOP_AT;
      have_sysop = true;
      break;
      
    // Sys_DC...
    case ZVA: case IVAC: case ISW: case CVAC: case CSW: case CVAU: case CIVAC: case CISW:
      sysop_type = SYSOP_DC;
      have_sysop = true;
      break;
      
    // Sys_IC...
    case IALLUIS: case IALLU: case IVAU:
      sysop_type = SYSOP_IC;
      have_sysop = true;
      break;
      
    // Sys_TLBI
    case IPAS2E1IS: case IPAS2LE1IS: case VMALLE1IS: case ALLE2IS: case ALLE3IS: case VAE1IS: case VAE2IS:
    case VAEEIS: case ASIDE1IS: case VAAE1IS: case ALLE1IS: case VALE1IS: case VALE2IS: case VALE3IS:
    case VMALLS12E1IS: case VALLE1IS: case IPAS2E1: case IPAS2LE1: case VMALLE1: case ALLE2: case ALLE3:
    case VAE1: case VAE2: case VAE3: case ASIDE1: case VAAE1: case ALLE1: case VALE1: case VALE2: case VALE3:
    case VMALLS12E1: case VAALE1:
      sysop_type = SYSOP_TLBI;
      have_sysop = true;
      break;

    default: break;
  }

  return have_sysop;
}

// PstateAccess - used by MSR_IMM instruction...

int State::PstateAccess(int &rindex, unsigned int op1,unsigned int op2) {
  int rcode = UNALLOCATED_ENCODING_SYSOP;

  switch( (int)((op1<<3) | op2) ) {
    case 0x5:  rindex = 0x30420; rcode = ACCESS_OKAY; break; //SP
    case 0x1e: rindex = 0x33421; rcode = ACCESS_OKAY; break; //DAIF
    case 0x1f: rindex = 0x33421; rcode = ACCESS_OKAY; break; //DAIF too

    default: break;
  }

  return rcode;
}

// PstateUpdate - update referenced Pstate, return indicator that system register
//                access was indeed to pstate...

bool State::PstateUpdate(PSTATE &pstate, int sysreg_id,unsigned long long &rval) {
  bool msr_to_pstate = false;

  switch(sysreg_id) {
    case 0x30420:  pstate.SP(rval & 1);
                   rval = pstate.SP();             
                   msr_to_pstate = true; 
                   break;

    case 0x33421:  pstate.DAIF(rval);
                   rval = pstate.DAIF();         
                   msr_to_pstate = true; 
                   break;

    case 0x33420:  pstate.NZCV( (rval>>28) & 0xf );
                   rval = pstate.NZCV()<<28; 
                   msr_to_pstate = true; 
                   break; 

    default: break;
  }

  return msr_to_pstate;
}

// SystemRegisterPut - update all supported system registers, including Pstate...

int State::SystemRegisterPut(int sysreg_id,unsigned long long rval) {
  int rcode = ACCESS_OKAY;

  switch(sysreg_id) {
    case 0x30420:  Pstate.SP(rval & 1);            break;
    case 0x33421:  Pstate.DAIF(rval);              break;
    case 0x33420:  Pstate.NZCV( (rval>>28) & 0xf); break;

    case 0x33440:  FPCR.Value(rval); break;
    case 0x33441:  FPSR.Value(rval); break; 

    case 0x36110:  SCR_EL3.Value(rval); break;
    case 0x30400:  SPSR_EL1.Value(rval); break; 
    case 0x34400:  SPSR_EL2.Value(rval); break;
    case 0x36400:  SPSR_EL3.Value(rval); break;
    case 0x30102:  CPACR_EL1.Value(rval); break;
    case 0x34112:  CPTR_EL2.Value(rval); break;
    case 0x36112:  CPTR_EL3.Value(rval); break;
    case 0x34000:  VPIDR_EL2.Value(rval); break; 
    case 0x34005:  VMPIDR_EL2.Value(rval); break;
    case 0x33001:  CTR_EL0.Value(rval); break;
    case 0x33007:  DCZID_EL0.Value(rval); break;
    case 0x30c01:  RVBAR_EL1.Value(rval); break;
    case 0x34c01:  RVBAR_EL2.Value(rval); break;
    case 0x36c01:  RVBAR_EL3.Value(rval); break;
    case 0x23010:  MDCCSR_EL0.Value(rval); break;
    case 0x20022:  MDSCR_EL1.Value(rval); break;
    case 0x36131:  MDCR_EL3.Value(rval); break;
    case 0x20134:  OSDLR_EL1.Value(rval); break;
    case 0x20104:  OSLAR_EL1.Value(rval); break;
    case 0x20114:  OSLSR_EL1.Value(rval); break;
    case 0x23040:  DBGDTR_EL0.Value(rval); break;  
    case 0x23050:  DBGDTRTX_EL0.Value(rval); break;
    case 0x33451:  DLR_EL0.Value(rval); break;
    case 0x33450:  DSPSR_EL0.Value(rval); break;
    case 0x30d01:  CONTEXTIDR_EL1.Value(rval); break;
    case 0x30740:  PAR_EL1.Value(rval); break;
    case 0x33d02:  TPIDR_EL0.Value(rval); break;
    case 0x30d04:  TPIDR_EL1.Value(rval); break;
    case 0x34d02:  TPIDR_EL2.Value(rval); break;
    case 0x36d02:  TPIDR_EL3.Value(rval); break;
    case 0x30401:  ELR_EL1.Value(rval); break;
    case 0x34401:  ELR_EL2.Value(rval); break;
    case 0x36401:  ELR_EL3.Value(rval); break;
    case 0x30520:  ESR_EL1.Value(rval); break;
    case 0x34520:  ESR_EL2.Value(rval); break;
    case 0x36520:  ESR_EL3.Value(rval); break;
    case 0x30600:  FAR_EL1.Value(rval); break; 
    case 0x34600:  FAR_EL2.Value(rval); break;
    case 0x36600:  FAR_EL3.Value(rval); break;
    case 0x30c00:  VBAR_EL1.Value(rval); break;
    case 0x34c00:  VBAR_EL2.Value(rval); break;
    case 0x36c00:  VBAR_EL3.Value(rval); break;
    case 0x30202:  TCR_EL1.Value(rval); break;
    case 0x34202:  TCR_EL2.Value(rval); break;
    case 0x36202:  TCR_EL3.Value(rval); break;
    case 0x30a20:  MAIR_EL1.Value(rval); break;
    case 0x34a20:  MAIR_EL2.Value(rval); break; 
    case 0x36a20:  MAIR_EL3.Value(rval); break;
    case 0x30c02:  RMR_EL1.Value(rval); break;
    case 0x34c02:  RMR_EL2.Value(rval); break;
    case 0x36c02:  RMR_EL3.Value(rval); break;
    case 0x30510:  AFSR0_EL1.Value(rval); break;
    case 0x34510:  AFSR0_EL2.Value(rval); break;
    case 0x36510:  AFSR0_EL3.Value(rval); break;
    case 0x30511:  AFSR1_EL1.Value(rval); break;
    case 0x34511:  AFSR1_EL2.Value(rval); break; 
    case 0x36511:  AFSR1_EL3.Value(rval); break; 
    case 0x30410:  SP_EL0.Value(rval); break;
    case 0x34410:  SP_EL1.Value(rval); break;
    case 0x36410:  SP_EL2.Value(rval); break;
    case 0x36411:  SP_EL3.Value(rval); break;
    case 0x34100:  SCTLR_EL2.Value(rval); break;
    case 0x36100:  SCTLR_EL3.Value(rval); break;
    case 0x30200:  TTBR0_EL1.Value(rval); break;
    case 0x30201:  TTBR1_EL1.Value(rval); break;
    case 0x34200:  TTBR0_EL2.Value(rval); break;
    case 0x36200:  TTBR0_EL3.Value(rval); break;
    case 0x34110:  HCR_EL2.Value(rval);   break;

    case 0x36101:  ACTLR_EL3.Value(rval); break;

    case 0x33e00: CNTFRQ_EL0.Value(rval); break;
    case 0x34e10: CNTHCTL_EL2.Value(rval); break;
    case 0x34e21: CNTHP_CTL_EL2.Value(rval); break;
    case 0x34e22: CNTHP_CVAL_EL2.Value(rval); break;
    case 0x34e20: CNTHP_TVAL_EL2.Value(rval); break;
    case 0x30E10: CNTKCTL_EL1.Value(rval); break;
      
    case 0x33e01: CNTPCT_EL0.Value(rval); break;
      
    case 0x33e21: CNTP_CTL_EL0.Value(rval);   CNTPS_CTL_EL1.Value(rval);  break;  //
    case 0x33e22: CNTP_CVAL_EL0.Value(rval);  CNTPS_CVAL_EL1.Value(rval); break;  //
    case 0x33e20: CNTP_TVAL_EL0.Value(rval);  CNTPS_TVAL_EL1.Value(rval); break;  // in this implementation, the
                                                                                  //  physical timer and the 'secure' 
    case 0x37e21: CNTPS_CTL_EL1.Value(rval);  CNTP_CTL_EL0.Value(rval);   break;  //    physical timer are the same
    case 0x37e22: CNTPS_CVAL_EL1.Value(rval); CNTP_CVAL_EL0.Value(rval);  break;  //
    case 0x37e20: CNTPS_TVAL_EL1.Value(rval); CNTP_TVAL_EL0.Value(rval);  break;  //
      
    case 0x33e31: CNTV_CTL_EL0.Value(rval); break;
    case 0x33e32: CNTV_CVAL_EL0.Value(rval); break;
    case 0x33e30: CNTV_TVAL_EL0.Value(rval); break;
    case 0x33e02: CNTVCT_EL0.Value(rval); break;
    case 0x34e03: CNTVOFF_EL2.Value(rval); break;
      
    case 0x30460: ICC_PMR_EL1.Value(rval); break;
    case 0x30c80: ICC_IAR0_EL1.Value(rval); break;
    case 0x30c81: ICC_EORI0_EL1.Value(rval); break;
    case 0x30c82: ICC_HPPIR0_EL1.Value(rval); break;
    case 0x30c83: ICC_BPR0_EL1.Value(rval); break;     
    case 0x30c84: ICC_AP0R0_EL1.Value(rval); break;
    case 0x30c85: ICC_AP0R1_EL1.Value(rval); break;
    case 0x30c86: ICC_AP0R2_EL1.Value(rval); break;
    case 0x30c87: ICC_AP0R3_EL1.Value(rval); break;
    case 0x30c90: ICC_AP1R0_EL1.Value(rval); break;
    case 0x30c91: ICC_AP1R1_EL1.Value(rval); break;
    case 0x30c92: ICC_AP1R2_EL1.Value(rval); break;
    case 0x30c93: ICC_AP1R3_EL1.Value(rval); break;
    case 0x30cb1: ICC_DIR_EL1.Value(rval); break;      
    case 0x30cb3: ICC_RPR_EL1.Value(rval); break;
    case 0x30cb5: ICC_SGI1R_EL1.Value(rval); break;
    case 0x30cb6: ICC_ASGI1R_EL1.Value(rval); break;
    case 0x30cb7: ICC_SGI0R_EL1.Value(rval); break;
    case 0x30cc0: ICC_IAR1_EL1.Value(rval); break;
    case 0x30cc1: ICC_EOIR1_EL1.Value(rval); break;
    case 0x30cc2: ICC_HPPIR1_EL1.Value(rval); break;
    case 0x30cc3: ICC_BPR1_EL1.Value(rval); break;
    case 0x30cc4: ICC_CTLR_EL1.Value(rval); break;
    case 0x30cc5: ICC_SRE_EL1.Value(rval); break;
    case 0x30cc6: ICC_IGRPEN0_EL1.Value(rval); break;
    case 0x30cc7: ICC_IGRPEN1_EL1.Value(rval); break;
    case 0x30c95: ICC_SRE_EL2.Value(rval); break;
    case 0x36cc4: ICC_CTLR_EL3.Value(rval); break;
    case 0x36cc5: ICC_SRE_EL3.Value(rval); break;
    case 0x36cc7: ICC_IGRPEN1_EL3.Value(rval); break;
      
    case 0x30100:
      // in our implementation ACTLR_EL1.DC bit controls access to SCTLR_EL1.M (paging enable) bit:
      // if ACTLR_EL1.DC==1 then SCTLR_EL1.M is read-only...
      {
	bool Mbit_readonly = false;       // will assume we can write this bit
	
	if ( (Pstate.EL() < 3)            // BUT if not at EL3,
	     && (SCR_EL3.NS() == 1)       //   and non-secure mode,
	     && (ACTLR_EL3.DC() == 1) )   //     and access to M bit is restricted
	  Mbit_readonly = true;           // then CANNOT set SCTLR_EL1.M bit
	
        SCTLR_EL1.Value(Mbit_readonly ? (rval & ~1ull) : rval);
      }
      break;
      
    default: rcode = UNALLOCATED_ENCODING_SYSOP;  break;
  }

  return rcode;
}

string State::SystemRegisterName(int rindex) {
  string rname;

  switch(rindex) {
    case 0x30420:  rname = "SPSel";            break;
    case 0x30422:  rname = "CurrentEL";        break;
    case 0x33421:  rname = "DAIF";             break;
    case 0x33420:  rname = "NZCV";             break;
    case 0x33440:  rname = "FPCR";             break;
    case 0x33441:  rname = "FPSR";             break; 
    case 0x36110:  rname = "SCR_EL3";          break;
    case 0x30400:  rname = "SPSR_EL1";         break; 
    case 0x34400:  rname = "SPSR_EL2";         break;
    case 0x36400:  rname = "SPSR_EL3";         break;
    case 0x30050:  rname = "ID_AA64DFR0_EL1";  break; 
    case 0x30070:  rname = "ID_AA64MMFR0_EL1"; break; 
    case 0x30040:  rname = "ID_AA64PFR0_EL1";  break;
    case 0x30060:  rname = "ID_AA64ISAR0_EL1"; break;
    case 0x30102:  rname = "CPACR_EL1";        break;
    case 0x34112:  rname = "CPTR_EL2";         break;
    case 0x36112:  rname = "CPTR_EL3";         break;
    case 0x30000:  rname = "MIDR_EL1";         break;
    case 0x34000:  rname = "VPIDR_EL2";        break; 
    case 0x30006:  rname = "REVIDR_EL1";       break;
    case 0x30005:  rname = "MPIDR_EL1";        break; 
    case 0x34005:  rname = "VMPIDR_EL2";       break;
    case 0x33001:  rname = "CTR_EL0";          break;
    case 0x33007:  rname = "DCZID_EL0";        break;
    case 0x30c01:  rname = "RVBAR_EL1";        break;
    case 0x34c01:  rname = "RVBAR_EL2";        break;
    case 0x36c01:  rname = "RVBAR_EL3";        break;
    case 0x23010:  rname = "MDCCSR_EL0";       break;
    case 0x20022:  rname = "MDSCR_EL1";        break;
    case 0x36131:  rname = "MDCR_EL3";         break;
    case 0x20134:  rname = "OSDLR_EL1";        break;
    case 0x20104:  rname = "OSLAR_EL1";        break;
    case 0x20114:  rname = "OSLSR_EL1";        break;
    case 0x23040:  rname = "DBGDTR_EL0";       break;  
    case 0x23050:  rname = "DBGDTRTX_EL0";     break;
    case 0x33451:  rname = "DLR_EL0";          break;
    case 0x33450:  rname = "DSPSR_EL0";        break;
    case 0x30d01:  rname = "CONTEXTIDR_EL1";   break;
    case 0x30740:  rname = "PAR_EL1";          break;
    case 0x33d02:  rname = "TPIDR_EL0";        break;
    case 0x30d04:  rname = "TPIDR_EL1";        break;
    case 0x34d02:  rname = "TPIDR_EL2";        break;
    case 0x36d02:  rname = "TPIDR_EL3";        break;
    case 0x30401:  rname = "ELR_EL1";          break;
    case 0x34401:  rname = "ELR_EL2";          break;
    case 0x36401:  rname = "ELR_EL3";          break;
    case 0x30520:  rname = "ESR_EL1";          break;
    case 0x34520:  rname = "ESR_EL2";          break;
    case 0x36520:  rname = "ESR_EL3";          break;
    case 0x30600:  rname = "FAR_EL1";          break; 
    case 0x34600:  rname = "FAR_EL2";          break;
    case 0x36600:  rname = "FAR_EL3";          break;
    case 0x30c00:  rname = "VBAR_EL1";         break;
    case 0x34c00:  rname = "VBAR_EL2";         break;
    case 0x36c00:  rname = "VBAR_EL3";         break;
    case 0x30202:  rname = "TCR_EL1";          break;
    case 0x34202:  rname = "TCR_EL2";          break;
    case 0x36202:  rname = "TCR_EL3";          break;
    case 0x30a20:  rname = "MAIR_EL1";         break;
    case 0x34a20:  rname = "MAIR_EL2";         break; 
    case 0x36a20:  rname = "MAIR_EL3";         break;
    case 0x30c02:  rname = "RMR_EL1";          break;
    case 0x34c02:  rname = "RMR_EL2";          break;
    case 0x36c02:  rname = "RMR_EL3";          break;
    case 0x30510:  rname = "AFSR0_EL1";        break;
    case 0x34510:  rname = "AFSR0_EL2";        break;
    case 0x36510:  rname = "AFSR0_EL3";        break;
    case 0x30511:  rname = "AFSR1_EL1";        break;
    case 0x34511:  rname = "AFSR1_EL2";        break; 
    case 0x36511:  rname = "AFSR1_EL3";        break; 
    case 0x30410:  rname = "SP_EL0";           break;
    case 0x34410:  rname = "SP_EL1";           break;
    case 0x36410:  rname = "SP_EL2";           break;
    case 0x36411:  rname = "SP_EL3";           break;
    case 0x30100:  rname = "SCTLR_EL1";        break;
    case 0x34100:  rname = "SCTLR_EL2";        break;
    case 0x36100:  rname = "SCTLR_EL3";        break;
    case 0x30200:  rname = "TTBR0_EL1";        break;
    case 0x30201:  rname = "TTBR1_EL1";        break;
    case 0x34200:  rname = "TTBR0_EL2";        break;
    case 0x36200:  rname = "TTBR0_EL3";        break;
    case 0x34110:  rname = "HCR_EL2";          break;
    case 0x36101:  rname = "ACTLR_EL3";        break;
    case 0x33e00:  rname = "CNTFRQ_EL0";       break;
    case 0x34e10:  rname = "CNTHCTL_EL2";      break;
    case 0x34e21:  rname = "CNTHP_CTL_EL2";    break;
    case 0x34e22:  rname = "CNTHP_CVAL_EL2";   break;
    case 0x34e20:  rname = "CNTHP_TVAL_EL2";   break;
    case 0x30E10:  rname = "CNTKCTL_EL1";      break;
    case 0x33e21:  rname = "CNTP_CTL_EL0";     break;
    case 0x33e22:  rname = "CNTP_CVAL_EL0";    break;
    case 0x33e20:  rname = "CNTP_TVAL_EL0";    break;
    case 0x33e01:  rname = "CNTPCT_EL0";       break;
    case 0x37e21:  rname = "CNTPS_CTL_EL1";    break;
    case 0x37e22:  rname = "CNTPS_CVAL_EL1";   break;
    case 0x37e20:  rname = "CNTPS_TVAL_EL1";   break;
    case 0x33e31:  rname = "CNTV_CTL_EL0";     break;
    case 0x33e32:  rname = "CNTV_CVAL_EL0";    break;
    case 0x33e30:  rname = "CNTV_TVAL_EL0";    break;
    case 0x33e02:  rname = "CNTVCT_EL0";       break;
    case 0x34e03:  rname = "CNTVOFF_EL2";      break;

    case 0x30460:  rname = "ICC_PMR_EL1";      break;
    case 0x30c80:  rname = "ICC_IAR0_EL1";     break;
    case 0x30c81:  rname = "ICC_EORI0_EL1";    break;
    case 0x30c82:  rname = "ICC_HPPIR0_EL1";   break;
    case 0x30c83:  rname = "ICC_BPR0_EL1";     break;     
    case 0x30c84:  rname = "ICC_AP0R0_EL1";    break;
    case 0x30c85:  rname = "ICC_AP0R1_EL1";    break;
    case 0x30c86:  rname = "ICC_AP0R2_EL1";    break;
    case 0x30c87:  rname = "ICC_AP0R3_EL1";    break;
    case 0x30c90:  rname = "ICC_AP1R0_EL1";    break;
    case 0x30c91:  rname = "ICC_AP1R1_EL1";    break;
    case 0x30c92:  rname = "ICC_AP1R2_EL1";    break;
    case 0x30c93:  rname = "ICC_AP1R3_EL1";    break;
    case 0x30cb1:  rname = "ICC_DIR_EL1";      break;
    case 0x30cb3:  rname = "ICC_RPR_EL1";      break;
    case 0x30cb5:  rname = "ICC_SGI1R_EL1";    break;
    case 0x30cb6:  rname = "ICC_ASGI1R_EL1";   break;
    case 0x30cb7:  rname = "ICC_SGI0R_EL1";    break;
    case 0x30cc0:  rname = "ICC_IAR1_EL1";     break;
    case 0x30cc1:  rname = "ICC_EOIR1_EL1";    break;
    case 0x30cc2:  rname = "ICC_HPPIR1_EL1";   break;
    case 0x30cc3:  rname = "ICC_BPR1_EL1";     break;
    case 0x30cc4:  rname = "ICC_CTLR_EL1";     break;
    case 0x30cc5:  rname = "ICC_SRE_EL1";      break;
    case 0x30cc6:  rname = "ICC_IGRPEN0_EL1";  break;
    case 0x30cc7:  rname = "ICC_IGRPEN1_EL1";  break;
    case 0x30c95:  rname = "ICC_SRE_EL2";      break;
    case 0x36cc4:  rname = "ICC_CTLR_EL3";     break;
    case 0x36cc5:  rname = "ICC_SRE_EL3";      break;
    case 0x36cc7:  rname = "ICC_IGRPEN1_EL3";  break;

    default: rname = "?";  break;
  }

  return rname;
}

void State::SysOpNames(string &sysop_alias, string &sysop_name, int sysop_type, int sysop_index) {
  switch(sysop_type) {
    case SYSOP_AT:   sysop_alias = "AT";   break;
    case SYSOP_DC:   sysop_alias = "DC";   break;
    case SYSOP_IC:   sysop_alias = "IC";   break;
    case SYSOP_TLBI: sysop_alias = "TLBI"; break;
    default: break;
  }
  
  switch(sysop_index) {
    case S1E1R:        sysop_name = "S1E1R";        break;
    case S1E2R:        sysop_name = "S1E2R";        break;
    case S1E3R:        sysop_name = "S1E3R";        break;
    case S1E1W:        sysop_name = "S1E1W";        break;
    case S1E2W:        sysop_name = "S1E2W";        break;
    case S1E3W:        sysop_name = "S1E3W";        break;
    case S1E0R:        sysop_name = "S1E0R";        break;
    case S1E0W:        sysop_name = "S1E0W";        break;
    case S12E1R:       sysop_name = "S12E1R";       break;
    case S12E1W:       sysop_name = "S12E1W";       break;
    case S12E0R:       sysop_name = "S12E0R";       break;
    case S12E0W:       sysop_name = "S12E0W";       break;
    case ZVA:          sysop_name = "ZVA";          break;
    case IVAC:         sysop_name = "IVAC";         break;
    case ISW:          sysop_name = "ISW";          break;
    case CVAC:         sysop_name = "CVAC";         break;
    case CSW:          sysop_name = "CSW";          break;
    case CVAU:         sysop_name = "CVAU";         break;
    case CIVAC:        sysop_name = "CIVAC";        break;
    case CISW:         sysop_name = "CISW";         break;
    case IALLUIS:      sysop_name = "IALLUIS";      break;
    case IALLU:        sysop_name = "IALLU";        break;
    case IVAU:         sysop_name = "IVAU";         break;
    case IPAS2E1IS:    sysop_name = "IPAS2E1IS";    break;
    case IPAS2LE1IS:   sysop_name = "IPAS2LE1IS";   break;
    case VMALLE1IS:    sysop_name = "VMALLE1IS";    break;
    case ALLE2IS:      sysop_name = "ALLE2IS";      break;
    case ALLE3IS:      sysop_name = "ALLE3IS";      break;
    case VAE1IS:       sysop_name = "VAE1IS";       break;
    case VAE2IS:       sysop_name = "VAE2IS";       break;
    case VAEEIS:       sysop_name = "VAEEIS";       break;
    case ASIDE1IS:     sysop_name = "ASIDE1IS";     break;
    case VAAE1IS:      sysop_name = "VAAE1IS";      break;
    case ALLE1IS:      sysop_name = "ALLE1IS";      break;
    case VALE1IS:      sysop_name = "VALE1IS";      break;
    case VALE2IS:      sysop_name = "VALE2IS";      break;
    case VALE3IS:      sysop_name = "VALE3IS";      break;
    case VMALLS12E1IS: sysop_name = "VMALLS12E1IS"; break;
    case VALLE1IS:     sysop_name = "VALLE1IS";     break;
    case IPAS2E1:      sysop_name = "IPAS2E1";      break;
    case IPAS2LE1:     sysop_name = "IPAS2LE1";     break;
    case VMALLE1:      sysop_name = "VMALLE1";      break;
    case ALLE2:        sysop_name = "ALLE2";        break;
    case ALLE3:        sysop_name = "ALLE3";        break;
    case VAE1:         sysop_name = "VAE1";         break;
    case VAE2:         sysop_name = "VAE2";         break;
    case VAE3:         sysop_name = "VAE3";         break;
    case ASIDE1:       sysop_name = "ASIDE1";       break;
    case VAAE1:        sysop_name = "VAAE1";        break;
    case ALLE1:        sysop_name = "ALLE1";        break;
    case VALE1:        sysop_name = "VALE1";        break;
    case VALE2:        sysop_name = "VALE2";        break;
    case VALE3:        sysop_name = "VALE3";        break;
    case VMALLS12E1:   sysop_name = "VMALLS12E1";   break;
    case VAALE1:       sysop_name = "VAALE1";       break;

    default: break;
  }
}

