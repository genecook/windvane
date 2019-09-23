// hand-crafted assembler to correct auto-generated assembler or missing assembler...

   case FCMP_SINGLE_FROM_SP:
      sprintf(tbuf,"FCMP S%u, S%u\n",packet->Rn.Value(),packet->Rm.Value());
      have_hc_case = true;
      break;

  case FCMPE_SINGLE_FROM_SP:
      sprintf(tbuf,"FCMPE S%u, S%u\n",packet->Rn.Value(),packet->Rm.Value());
      have_hc_case = true;
      break;

   case FCSEL_SINGLE_FROM_SP:
      sprintf(tbuf,"FCSEL S%u, S%u, S%u, %s\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value(),Bcond(packet->cond.Value()).c_str());
      have_hc_case = true;
      break;

   case FCMP_SINGLE_FROM_SP_ZERO:
      sprintf(tbuf,"FCMP S%u, #0.0\n",packet->Rn.Value());
      have_hc_case = true;
      break;

   case FCMP_FROM_DP_ZERO:
      sprintf(tbuf,"FCMP D%u, #0.0\n",packet->Rn.Value());
      have_hc_case = true;
      break;

   case FCMPE_FROM_DP_ZERO:
      sprintf(tbuf,"FCMPE D%u, #0.0\n",packet->Rn.Value());
      have_hc_case = true;
      break;

   case FCMPE_SINGLE_FROM_SP_ZERO:
      sprintf(tbuf,"FCMPE S%u, #0.0\n",packet->Rn.Value());
      have_hc_case = true;
      break;

    case FMOV_IMM_FROM_DP: 
      {
      unsigned long long fltimm = VFPExpandImm(64, packet->imm8.Value());
      union {
        double y;
        unsigned long long res;
      } tmp;
      tmp.res = fltimm;
      sprintf(tbuf,"FMOV D%d, #0x%llx // %f\n",packet->Rd.Value(),fltimm,tmp.y);
      }
      have_hc_case = true;
      break;

    case FMOV_IMM_SINGLE_FROM_SP: 
      {
      unsigned long long fltimm = VFPExpandImm(32, packet->imm8.Value());
      union {
        float x[2];
        unsigned long long res;
      } tmp;
      tmp.res = fltimm;
      sprintf(tbuf,"FMOV S%d, #0x%llx // %f\n",packet->Rd.Value(),fltimm,tmp.x[0]);
      }
      have_hc_case = true;
      break;

    case FDIV_SINGLE_FROM_SP:
      sprintf(tbuf,"FDIV S%d, S%u, S%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      have_hc_case = true;
      break;

    case FMADD_SINGLE_FROM_SP:
      sprintf(tbuf,"FMADD S%d, S%u, S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value(),packet->Ra.Value());
      have_hc_case = true;
      break;

   case FRINTM_SINGLE_FROM_SP:
      sprintf(tbuf,"FRINTM S%d, S%u\n",packet->Rd.Value(),packet->Rn.Value());
      have_hc_case = true;
      break;

   case ADDS_REG_32:
      if (packet->Rd.Value() == 31) {
        sprintf(tbuf,"CMN %s, W%d, %s #%u\n",XnSP(packet->Rn.Value(),true).c_str(),packet->Rm.Value(),
		extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),true).c_str(),packet->imm3.Value());
	have_hc_case = true;
      }
      break;
   case ADDS_REG_64:
      if (packet->Rd.Value() == 31) {
        sprintf(tbuf,"CMN %s, %c%s, %s #%u\n",XnSP(packet->Rn.Value(),false).c_str(),
	      ((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),
		extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),true).c_str(),packet->imm3.Value());
	have_hc_case = true;
      }
      break;


   case ADD_IMM_32:
      sprintf(tbuf,"ADD %s, %s, #%s\n",XnSP(packet->Rd.Value(),true).c_str(),XnSP(packet->Rn.Value(),true).c_str(),ZeroExtend(packet->imm12.Value(),12,packet->shift.Value()).c_str());
      have_hc_case = true;
      break;
   case ADD_IMM_64:
      sprintf(tbuf,"ADD %s, %s, #%s\n",XnSP(packet->Rd.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),ZeroExtend(packet->imm12.Value(),12,packet->shift.Value()).c_str());
      have_hc_case = true;
      break;

   case ADDS_IMM_32:
      if (packet->Rd.Value() == 31) {
        sprintf(tbuf,"CMN %s, #%s, %s\n",XnSP(packet->Rn.Value(),true).c_str(),
	      ZeroExtend(packet->imm12.Value(),12,0).c_str(),as_imm_shift(packet->shift.Value()).c_str());
	have_hc_case = true;
      }
      break;
   case ADDS_IMM_64:
      if (packet->Rd.Value() == 31) {
        sprintf(tbuf,"CMN %s, #%s, %s\n",XnSP(packet->Rn.Value(),false).c_str(),
	      ZeroExtend(packet->imm12.Value(),12,0).c_str(),as_imm_shift(packet->shift.Value()).c_str());
	have_hc_case = true;
      }
      break;

   case ADDS_SHIFT_REG_32:
      if (packet->Rd.Value() == 31) {
        sprintf(tbuf,"CMN W%d, W%d, %s #%u\n",packet->Rn.Value(),packet->Rm.Value(),
	      as_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
	have_hc_case = true;
      }
      break;
   case ADDS_SHIFT_REG_64:
      if (packet->Rd.Value() == 31) {
        sprintf(tbuf,"CMN X%d, X%d, %s #%u\n",packet->Rn.Value(),packet->Rm.Value(),
	      as_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
	have_hc_case = true;
      }
      break;

  case SUBS_REG_32:
      if (packet->Rd.Value() == 31) {
        sprintf(tbuf,"CMP %s, W%d, %s #%u\n",XnSP(packet->Rn.Value(),true).c_str(),packet->Rm.Value(),
		extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),true).c_str(),packet->imm3.Value());
	have_hc_case = true;
      }
      break;
   case SUBS_REG_64:
      if (packet->Rd.Value() == 31) {
        sprintf(tbuf,"CMP %s, %c%s, %s #%u\n",XnSP(packet->Rn.Value(),false).c_str(),
	        ((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),
	        extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),true).c_str(),packet->imm3.Value());
	have_hc_case = true;
      }
      break;

   case SUBS_IMM_32:
      if (packet->Rd.Value() == 31) {
        sprintf(tbuf,"CMP %s, #%u, %s\n",XnSP(packet->Rn.Value(),true).c_str(),packet->imm12.Value(),as_imm_shift(packet->shift.Value()).c_str());
	have_hc_case = true;
      }
      break;
   case SUBS_IMM_64:
      if (packet->Rd.Value() == 31) {
        sprintf(tbuf,"CMP %s, #%u, %s\n",XnSP(packet->Rn.Value(),false).c_str(),packet->imm12.Value(),as_imm_shift(packet->shift.Value()).c_str());
	have_hc_case = true;
      }
      break;
   case SUBS_SHIFT_REG_32:
      if (packet->Rd.Value() == 31) {
        sprintf(tbuf,"CMP W%d, W%d, %s #%u\n",packet->Rn.Value(),packet->Rm.Value(),as_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
	have_hc_case = true;
      }
      break;
   case SUBS_SHIFT_REG_64:
      if (packet->Rd.Value() == 31) {
        sprintf(tbuf,"CMP X%d, X%d, %s #%u\n",packet->Rn.Value(),packet->Rm.Value(),as_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
	have_hc_case = true;
      }
      break;

   case SYS:
      {
       int sysop_type, sysop_index;
       if (cpu->SysOp(sysop_type,sysop_index,packet->op0.Value(),packet->op1.Value(),packet->CRn.Value(),packet->CRm.Value(),packet->op2.Value())) {
	 string sysop_alias, sysop_name;
	 cpu->SysOpNames(sysop_alias,sysop_name,sysop_type,sysop_index);
	 // for IC, TLBI sys ops, Xt (Rt) is optional (default value for Xt is 11111)...
	 if ( ((sysop_type == SYSOP_IC) || (sysop_type == SYSOP_TLBI)) && (packet->Rt.Value() == 0x1f))
	   sprintf(tbuf,"%s %s\n",sysop_alias.c_str(),sysop_name.c_str());
	 else
	   sprintf(tbuf,"%s %s,X%d\n",sysop_alias.c_str(),sysop_name.c_str(),packet->Rt.Value());
       } else {	  
         sprintf(tbuf,"SYS #%d, C%u, C%u, #%d, X%d\n",packet->op1.Value(),packet->CRn.Value(),packet->CRm.Value(),packet->op2.Value(),packet->Rt.Value());
       }
       have_hc_case = true;
      }
      break;

   case SYSL:
      sprintf(tbuf,"SYSL X%d, #%d, C%u, C%u, #%d\n",packet->Rt.Value(),packet->op1.Value(),packet->CRn.Value(),packet->CRm.Value(),packet->op2.Value());
      have_hc_case = true;
      break;

  case MSR_REG:
      sprintf(tbuf,"MSR %s, %s\n",systemRegisterName(packet->op0.Value(),packet->op1.Value(),packet->CRn.Value(),packet->CRm.Value(),packet->op2.Value(),false).c_str(),XnXZR(packet->Rt.Value(),false).c_str());
      have_hc_case = true;
      break;

  case UMSUBL:
      if (packet->Ra.Value() == 31) 
        sprintf(tbuf,"UMNEGL %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str());
      else
        sprintf(tbuf,"UMSUBL %s, %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),XnXZR(packet->Ra.Value(),false).c_str());
      have_hc_case = true;
      break;

   case FSQRT_SINGLE_FROM_SP:
      sprintf(tbuf,"FSQRT S%d, S%u\n",packet->Rd.Value(),packet->Rn.Value());
      have_hc_case = true;
      break;
  case FRINTZ_SINGLE_FROM_SP:
      sprintf(tbuf,"FRINTZ S%d, S%u\n",packet->Rd.Value(),packet->Rn.Value());
      have_hc_case = true;
      break;

// smaddl
   case SMADDL:
      if (packet->Ra.Value() == 31)
        sprintf(tbuf,"SMULL %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str());
      else
        sprintf(tbuf,"SMADDL %s, %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),XnXZR(packet->Ra.Value(),false).c_str());
      have_hc_case = true;
      break;

// PC relative branches...
   case B_COND_IMM:
      sprintf(tbuf,"B.%s 0x%llx\n",Bcond(packet->cond.Value()).c_str(),packet->PC.Value() + SignExtend(packet->imm19.Value()<<2,21));
      have_hc_case = true;
      break;
   case B_IMM:
      sprintf(tbuf,"B 0x%llx\n",packet->PC.Value() + SignExtend(packet->imm26.Value()<<2,28));
      have_hc_case = true;
      break;
   case BL:
      sprintf(tbuf,"BL 0x%llx\n",packet->PC.Value() + SignExtend(packet->imm26.Value()<<2,28));
      have_hc_case = true;
      break;
   case CBNZ_IMM_32:
      sprintf(tbuf,"CBNZ %s, 0x%llx\n",XnXZR(packet->Rt.Value(),true).c_str(),packet->PC.Value() + SignExtend(packet->imm19.Value()<<2,21));
      have_hc_case = true;
      break;
   case CBNZ_IMM_64:
      sprintf(tbuf,"CBNZ %s, 0x%llx\n",XnXZR(packet->Rt.Value(),false).c_str(),packet->PC.Value() + SignExtend(packet->imm19.Value()<<2,21));
      have_hc_case = true;
      break;
   case CBZ_IMM_32:
      sprintf(tbuf,"CBZ %s, 0x%llx\n",XnXZR(packet->Rt.Value(),true).c_str(),packet->PC.Value() + SignExtend(packet->imm19.Value()<<2,21));
      have_hc_case = true;
      break;
   case CBZ_IMM_64:
      sprintf(tbuf,"CBZ %s, 0x%llx\n",XnXZR(packet->Rt.Value(),false).c_str(),packet->PC.Value() + SignExtend(packet->imm19.Value()<<2,21));
      have_hc_case = true;
      break;
