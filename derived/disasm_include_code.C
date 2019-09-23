   case ADC_32:
      sprintf(tbuf,"ADC %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str());
      break;
   case ADC_64:
      sprintf(tbuf,"ADC %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case ADCS_32:
      sprintf(tbuf,"ADCS %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str());
      break;
   case ADCS_64:
      sprintf(tbuf,"ADCS %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case ADD_REG_32:
      sprintf(tbuf,"ADD %s, %s, %s, %s #%u\n",XnSP(packet->Rd.Value(),true).c_str(),XnSP(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case ADD_REG_64:
      sprintf(tbuf,"ADD %s, %s, %c%s, %s #%u\n",XnSP(packet->Rd.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case ADD_IMM_32:
      sprintf(tbuf,"ADD %s, %s, #%s, %s\n",XnSP(packet->Rd.Value(),true).c_str(),XnSP(packet->Rn.Value(),true).c_str(),ZeroExtend(packet->imm12.Value(),12,0).c_str(),as_imm_shift(packet->shift.Value()).c_str());
      break;
   case ADD_IMM_64:
      sprintf(tbuf,"ADD %s, %s, #%s, %s\n",XnSP(packet->Rd.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),ZeroExtend(packet->imm12.Value(),12,0).c_str(),as_imm_shift(packet->shift.Value()).c_str());
      break;
   case ADD_SHIFT_REG_32:
      sprintf(tbuf,"ADD %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),as_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case ADD_SHIFT_REG_64:
      sprintf(tbuf,"ADD %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),as_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case ADDS_REG_32:
      sprintf(tbuf,"ADDS %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),XnSP(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case ADDS_REG_64:
      sprintf(tbuf,"ADDS %s, %s, %c%s, %s #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case ADDS_IMM_32:
      sprintf(tbuf,"ADDS %s, %s, #%s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnSP(packet->Rn.Value(),true).c_str(),ZeroExtend(packet->imm12.Value(),12,0).c_str(),as_imm_shift(packet->shift.Value()).c_str());
      break;
   case ADDS_IMM_64:
      sprintf(tbuf,"ADDS %s, %s, #%s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),ZeroExtend(packet->imm12.Value(),12,0).c_str(),as_imm_shift(packet->shift.Value()).c_str());
      break;
   case ADDS_SHIFT_REG_32:
      sprintf(tbuf,"ADDS %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),as_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case ADDS_SHIFT_REG_64:
      sprintf(tbuf,"ADDS %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),as_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case ADR:
      sprintf(tbuf,"ADR %s, %lld\n",XnXZR(packet->Rd.Value(),false).c_str(),(packet->op.Value() == 1) ? SignExtend((packet->immhi.Value()<<2 | packet->immlo.Value())<<12,32) : SignExtend(packet->immhi.Value()<<2 | packet->immlo.Value(),21));
      break;
   case ADRP:
      sprintf(tbuf,"ADRP %s, %lld\n",XnXZR(packet->Rd.Value(),false).c_str(),(packet->op.Value() == 1) ? SignExtend((packet->immhi.Value()<<2 | packet->immlo.Value())<<12,32) : SignExtend(packet->immhi.Value()<<2 | packet->immlo.Value(),21));
      break;
   case AND_IMM_32:
      sprintf(tbuf,"AND %s, %s, #%llu\n",XnSP(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),DecodeBitMasks(tmask,packet->N.Value(),packet->imms.Value(),packet->immr.Value(),true));
      break;
   case AND_IMM_64:
      sprintf(tbuf,"AND %s, %s, #%llu\n",XnSP(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),DecodeBitMasks(tmask,packet->N.Value(),packet->imms.Value(),packet->immr.Value(),true));
      break;
   case AND_SHIFT_REG_32:
      sprintf(tbuf,"AND %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),as_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case AND_SHIFT_REG_64:
      sprintf(tbuf,"AND %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),as_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case ANDS_IMM_32:
      sprintf(tbuf,"ANDS %s, %s, #%llu\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),DecodeBitMasks(tmask,packet->N.Value(),packet->imms.Value(),packet->immr.Value(),true));
      break;
   case ANDS_IMM_64:
      sprintf(tbuf,"ANDS %s, %s, #%llu\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),DecodeBitMasks(tmask,packet->N.Value(),packet->imms.Value(),packet->immr.Value(),true));
      break;
   case ANDS_SHIFT_REG_32:
      sprintf(tbuf,"ANDS %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),as_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case ANDS_SHIFT_REG_64:
      sprintf(tbuf,"ANDS %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),as_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case ASRV_32:
      sprintf(tbuf,"ASRV %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str());
      break;
   case ASRV_64:
      sprintf(tbuf,"ASRV %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case B_COND_IMM:
      sprintf(tbuf,"B.%s %lld\n",Bcond(packet->cond.Value()).c_str(),SignExtend(packet->imm19.Value()<<2,21));
      break;
   case B_IMM:
      sprintf(tbuf,"B %lld\n",SignExtend(packet->imm26.Value()<<2,28));
      break;
   case BFM_32:
      sprintf(tbuf,"BFM %s, %s, #%u, #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),packet->immr.Value(),packet->imms.Value());
      break;
   case BFM_64:
      sprintf(tbuf,"BFM %s, %s, #%u, #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),packet->immr.Value(),packet->imms.Value());
      break;
   case BIC_SHIFT_REG_32:
      sprintf(tbuf,"BIC %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),as_reg_shift(packet->shift.Value()).c_str(),packet->imm3.Value());
      break;
   case BIC_SHIFT_REG_64:
      sprintf(tbuf,"BIC %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),as_reg_shift(packet->shift.Value()).c_str(),packet->imm3.Value());
      break;
   case BICS_SHIFT_REG_32:
      sprintf(tbuf,"BICS %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),as_reg_shift(packet->shift.Value()).c_str(),packet->imm3.Value());
      break;
   case BICS_SHIFT_REG_64:
      sprintf(tbuf,"BICS %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),as_reg_shift(packet->shift.Value()).c_str(),packet->imm3.Value());
      break;
   case BL:
      sprintf(tbuf,"BL %lld\n",SignExtend(packet->imm26.Value()<<2,28));
      break;
   case BLR:
      sprintf(tbuf,"BLR %s\n",XnXZR(packet->Rn.Value(),false).c_str());
      break;
   case BR:
      sprintf(tbuf,"BR %s\n",XnXZR(packet->Rn.Value(),false).c_str());
      break;
   case BRK:
      sprintf(tbuf,"BRK #%d\n",packet->imm16.Value());
      break;
   case CBNZ_IMM_32:
      sprintf(tbuf,"CBNZ %s, %lld\n",XnXZR(packet->Rt.Value(),true).c_str(),SignExtend(packet->imm19.Value()<<2,21));
      break;
   case CBNZ_IMM_64:
      sprintf(tbuf,"CBNZ %s, %lld\n",XnXZR(packet->Rt.Value(),false).c_str(),SignExtend(packet->imm19.Value()<<2,21));
      break;
   case CBZ_IMM_32:
      sprintf(tbuf,"CBZ %s, %lld\n",XnXZR(packet->Rt.Value(),true).c_str(),SignExtend(packet->imm19.Value()<<2,21));
      break;
   case CBZ_IMM_64:
      sprintf(tbuf,"CBZ %s, %lld\n",XnXZR(packet->Rt.Value(),false).c_str(),SignExtend(packet->imm19.Value()<<2,21));
      break;
   case CCMN_IMM_32:
      sprintf(tbuf,"CCMN %s, #%d, #%u, %s\n",XnXZR(packet->Rn.Value(),true).c_str(),packet->imm5.Value(),packet->nzcv.Value(),Bcond(packet->cond.Value()).c_str());
      break;
   case CCMN_IMM_64:
      sprintf(tbuf,"CCMN %s, #%d, #%u, %s\n",XnXZR(packet->Rn.Value(),false).c_str(),packet->imm5.Value(),packet->nzcv.Value(),Bcond(packet->cond.Value()).c_str());
      break;
   case CCMN_REG_32:
      sprintf(tbuf,"CCMN %s, %s, #%u, %s\n",XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),packet->nzcv.Value(),Bcond(packet->cond.Value()).c_str());
      break;
   case CCMN_REG_64:
      sprintf(tbuf,"CCMN %s, %s, #%u, %s\n",XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),packet->nzcv.Value(),Bcond(packet->cond.Value()).c_str());
      break;
   case CCMP_IMM_32:
      sprintf(tbuf,"CCMP %s, #%d, #%u, %s\n",XnXZR(packet->Rn.Value(),true).c_str(),packet->imm5.Value(),packet->nzcv.Value(),Bcond(packet->cond.Value()).c_str());
      break;
   case CCMP_IMM_64:
      sprintf(tbuf,"CCMP %s, #%d, #%u, %s\n",XnXZR(packet->Rn.Value(),false).c_str(),packet->imm5.Value(),packet->nzcv.Value(),Bcond(packet->cond.Value()).c_str());
      break;
   case CCMP_REG_32:
      sprintf(tbuf,"CCMP %s, %s, #%u, %s\n",XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),packet->nzcv.Value(),Bcond(packet->cond.Value()).c_str());
      break;
   case CCMP_REG_64:
      sprintf(tbuf,"CCMP %s, %s, #%u, %s\n",XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),packet->nzcv.Value(),Bcond(packet->cond.Value()).c_str());
      break;
   case CLREX:
      sprintf(tbuf,"CLREX #%u\n",packet->CRm.Value());
      break;
   case CLS_32:
      sprintf(tbuf,"CLS %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str());
      break;
   case CLS_64:
      sprintf(tbuf,"CLS %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str());
      break;
   case CLZ_32:
      sprintf(tbuf,"CLZ %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str());
      break;
   case CLZ_64:
      sprintf(tbuf,"CLZ %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str());
      break;
   case CRC32B:
      sprintf(tbuf,"CRC32B %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str());
      break;
   case CRC32H:
      sprintf(tbuf,"CRC32H %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str());
      break;
   case CRC32W:
      sprintf(tbuf,"CRC32W %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str());
      break;
   case CRC32X:
      sprintf(tbuf,"CRC32X %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case CRC32CB:
      sprintf(tbuf,"CRC32CB %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str());
      break;
   case CRC32CH:
      sprintf(tbuf,"CRC32CH %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str());
      break;
   case CRC32CW:
      sprintf(tbuf,"CRC32CW %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str());
      break;
   case CRC32CX:
      sprintf(tbuf,"CRC32CX %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case CSEL_32:
      sprintf(tbuf,"CSEL %s, %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),Bcond(packet->cond.Value()).c_str());
      break;
   case CSEL_64:
      sprintf(tbuf,"CSEL %s, %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),Bcond(packet->cond.Value()).c_str());
      break;
   case CSINC_32:
      sprintf(tbuf,"CSINC %s, %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),Bcond(packet->cond.Value()).c_str());
      break;
   case CSINC_64:
      sprintf(tbuf,"CSINC %s, %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),Bcond(packet->cond.Value()).c_str());
      break;
   case CSINV_32:
      sprintf(tbuf,"CSINV %s, %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),Bcond(packet->cond.Value()).c_str());
      break;
   case CSINV_64:
      sprintf(tbuf,"CSINV %s, %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),Bcond(packet->cond.Value()).c_str());
      break;
   case CSNEG_32:
      sprintf(tbuf,"CSNEG %s, %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),Bcond(packet->cond.Value()).c_str());
      break;
   case CSNEG_64:
      sprintf(tbuf,"CSNEG %s, %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),Bcond(packet->cond.Value()).c_str());
      break;
   case DCPS1:
      sprintf(tbuf,"DCPS1 #%d\n",packet->imm16.Value());
      break;
   case DCPS2:
      sprintf(tbuf,"DCPS2 #%d\n",packet->imm16.Value());
      break;
   case DCPS3:
      sprintf(tbuf,"DCPS3 #%d\n",packet->imm16.Value());
      break;
   case DMB:
      sprintf(tbuf,"DMB %s\n",barrier_option(packet->CRm.Value(), packet->op2.Value()==6).c_str());
      break;
   case DRPS:
      sprintf(tbuf,"DRPS\n");
      break;
   case DSB:
      sprintf(tbuf,"DSB %s\n",barrier_option(packet->CRm.Value(), packet->op2.Value()==6).c_str());
      break;
   case EON_SHIFT_REG_32:
      sprintf(tbuf,"EON %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),eon_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case EON_SHIFT_REG_64:
      sprintf(tbuf,"EON %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),eon_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case EOR_IMM_32:
      sprintf(tbuf,"EOR %s, %s, #%llu\n",XnSP(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),DecodeBitMasks(tmask,packet->N.Value(),packet->imms.Value(),packet->immr.Value(),true));
      break;
   case EOR_IMM_64:
      sprintf(tbuf,"EOR %s, %s, #%llu\n",XnSP(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),DecodeBitMasks(tmask,packet->N.Value(),packet->imms.Value(),packet->immr.Value(),true));
      break;
   case EOR_SHIFT_REG_32:
      sprintf(tbuf,"EOR %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),eon_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case EOR_SHIFT_REG_64:
      sprintf(tbuf,"EOR %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),eon_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case ERET:
      sprintf(tbuf,"ERET\n");
      break;
   case EXTR_32:
      sprintf(tbuf,"EXTR %s, %s, %s, #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),packet->imms.Value());
      break;
   case EXTR_64:
      sprintf(tbuf,"EXTR %s, %s, %s, #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),packet->imms.Value());
      break;
   case HINT:
      sprintf(tbuf,"HINT #%u\n",packet->CRm.Value()<<3 | packet->op2.Value());
      break;
   case HLT:
      sprintf(tbuf,"HLT #%u\n",packet->imm16.Value());
      break;
   case HVC:
      sprintf(tbuf,"HVC #%d\n",packet->imm16.Value());
      break;
   case ISB:
      sprintf(tbuf,"ISB %s\n",barrier_option(packet->CRm.Value(), packet->op2.Value()==6).c_str());
      break;
   case LDAR_32:
      sprintf(tbuf,"LDAR %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case LDAR_64:
      sprintf(tbuf,"LDAR %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case LDARB:
      sprintf(tbuf,"LDARB %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case LDARH:
      sprintf(tbuf,"LDARH %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case LDAXP_32:
      sprintf(tbuf,"LDAXP %s, %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnXZR(packet->Rt2.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case LDAXP_64:
      sprintf(tbuf,"LDAXP %s, %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnXZR(packet->Rt2.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case LDAXR_32:
      sprintf(tbuf,"LDAXR %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case LDAXR_64:
      sprintf(tbuf,"LDAXR %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case LDAXRB:
      sprintf(tbuf,"LDAXRB %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case LDAXRH:
      sprintf(tbuf,"LDAXRH %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case LDNP_OFF_32:
      sprintf(tbuf,"LDNP %s, %s, [%s, #%lld]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnXZR(packet->Rt2.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case LDNP_OFF_64:
      sprintf(tbuf,"LDNP %s, %s, [%s, #%lld]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnXZR(packet->Rt2.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 8);
      break;
   case LDP_REG_POST_32:
      sprintf(tbuf,"LDP %s, %s, [%s], #%lld\n",XnXZR(packet->Rt.Value(),true).c_str(),XnXZR(packet->Rt2.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case LDP_REG_POST_64:
      sprintf(tbuf,"LDP %s, %s, [%s], #%lld\n",XnXZR(packet->Rt.Value(),false).c_str(),XnXZR(packet->Rt2.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 8);
      break;
   case LDP_REG_PRE_32:
      sprintf(tbuf,"LDP %s, %s, [%s, #%lld]!\n",XnXZR(packet->Rt.Value(),true).c_str(),XnXZR(packet->Rt2.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case LDP_REG_PRE_64:
      sprintf(tbuf,"LDP %s, %s, [%s, #%lld]!\n",XnXZR(packet->Rt.Value(),false).c_str(),XnXZR(packet->Rt2.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 8);
      break;
   case LDP_REG_OFF_32:
      sprintf(tbuf,"LDP %s, %s, [%s, #%lld]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnXZR(packet->Rt2.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case LDP_REG_OFF_64:
      sprintf(tbuf,"LDP %s, %s, [%s, #%lld]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnXZR(packet->Rt2.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 8);
      break;
   case LDPSW_REG_POST:
      sprintf(tbuf,"LDPSW %s, %s, [%s], #%lld\n",XnXZR(packet->Rt.Value(),false).c_str(),XnXZR(packet->Rt2.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case LDPSW_REG_PRE:
      sprintf(tbuf,"LDPSW %s, %s, [%s], #%lld\n",XnXZR(packet->Rt.Value(),false).c_str(),XnXZR(packet->Rt2.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case LDPSW_REG_OFF:
      sprintf(tbuf,"LDPSW %s, %s, [%s], #%lld\n",XnXZR(packet->Rt.Value(),false).c_str(),XnXZR(packet->Rt2.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case LDR_IMM_REG_POST_32:
      sprintf(tbuf,"LDR %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case LDR_IMM_REG_POST_64:
      sprintf(tbuf,"LDR %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case LDR_IMM_REG_PRE_32:
      sprintf(tbuf,"LDR %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case LDR_IMM_REG_PRE_64:
      sprintf(tbuf,"LDR %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case LDR_IMM_REG_32:
      sprintf(tbuf,"LDR %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case LDR_IMM_REG_64:
      sprintf(tbuf,"LDR %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case LDR_REG_32:
      sprintf(tbuf,"LDR %s, %lld\n",XnXZR(packet->Rt.Value(),true).c_str(),SignExtend(packet->imm19.Value()<<2,21));
      break;
   case LDR_REG_64:
      sprintf(tbuf,"LDR %s, %lld\n",XnXZR(packet->Rt.Value(),false).c_str(),SignExtend(packet->imm19.Value()<<2,21));
      break;
   case LDR_REG_OFF_32:
      sprintf(tbuf,"LDR %s, [%s, %c%s, %s %u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case LDR_REG_OFF_64:
      sprintf(tbuf,"LDR %s, [%s, %c%s, %s %u]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case LDRB_IMM_REG_POST:
      sprintf(tbuf,"LDRB %s, [%s], #%d\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDRB_IMM_REG_PRE:
      sprintf(tbuf,"LDRB %s, [%s, #%d]!\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDRB_IMM_REG_OFF:
      sprintf(tbuf,"LDRB %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case LDRB_REG_OFF:
      sprintf(tbuf,"LDRB %s, [%s, %c%s, %s %u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case LDRH_IMM_REG_POST:
      sprintf(tbuf,"LDRH %s, [%s], #%d\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDRH_IMM_REG_PRE:
      sprintf(tbuf,"LDRH %s, [%s, #%d]!\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDRH_IMM_REG_OFF:
      sprintf(tbuf,"LDRH %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case LDRH_REG_OFF:
      sprintf(tbuf,"LDRH %s, [%s, %c%s, %s %u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case LDRSB_IMM_REG_POST_32:
      sprintf(tbuf,"LDRSB %s, [%s], #%d\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDRSB_IMM_REG_POST_64:
      sprintf(tbuf,"LDRSB %s, [%s], #%d\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDRSB_IMM_REG_PRE_32:
      sprintf(tbuf,"LDRSB %s, [%s, #%d]!\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDRSB_IMM_REG_PRE_64:
      sprintf(tbuf,"LDRSB %s, [%s, #%d]!\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDRSB_IMM_REG_32:
      sprintf(tbuf,"LDRSB %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case LDRSB_IMM_REG_64:
      sprintf(tbuf,"LDRSB %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case LDRSB_REG_OFF_32:
      sprintf(tbuf,"LDRSB %s, [%s, %c%s, %s %u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case LDRSB_REG_OFF_64:
      sprintf(tbuf,"LDRSB %s, [%s, %c%s, %s %u]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case LDRSH_IMM_REG_POST_32:
      sprintf(tbuf,"LDRSH %s, [%s], #%d\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDRSH_IMM_REG_POST_64:
      sprintf(tbuf,"LDRSH %s, [%s], #%d\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDRSH_IMM_REG_PRE_32:
      sprintf(tbuf,"LDRSH %s, [%s, #%d]!\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDRSH_IMM_REG_PRE_64:
      sprintf(tbuf,"LDRSH %s, [%s, #%d]!\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDRSH_IMM_REG_32:
      sprintf(tbuf,"LDRSH %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case LDRSH_IMM_REG_64:
      sprintf(tbuf,"LDRSH %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case LDRSH_REG_OFF_32:
      sprintf(tbuf,"LDRSH %s, [%s, %c%s, %s %u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case LDRSH_REG_OFF_64:
      sprintf(tbuf,"LDRSH %s, [%s, %c%s, %s %u]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case LDRSW_IMM_REG_POST:
      sprintf(tbuf,"LDRSW %s, [%s], #%d\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDRSW_IMM_REG_PRE:
      sprintf(tbuf,"LDRSW %s, [%s, #%d]!\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDRSW_IMM_REG_OFF:
      sprintf(tbuf,"LDRSW %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case LDRSW_REG:
      sprintf(tbuf,"LDRSW %s, %lld\n",XnXZR(packet->Rt.Value(),false).c_str(),SignExtend(packet->imm19.Value()<<2,21));
      break;
   case LDRSW_REG_OFF:
      sprintf(tbuf,"LDRSW %s, [%s, %c%s, %s %u]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case LDTR_REG_32:
      sprintf(tbuf,"LDTR %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDTR_REG_64:
      sprintf(tbuf,"LDTR %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDTRB_REG:
      sprintf(tbuf,"LDTRB %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDTRH_REG:
      sprintf(tbuf,"LDTRH %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDTRSB_REG_32:
      sprintf(tbuf,"LDTRSB %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDTRSB_REG_64:
      sprintf(tbuf,"LDTRSB %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDTRSH_REG_32:
      sprintf(tbuf,"LDTRSH %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDTRSH_REG_64:
      sprintf(tbuf,"LDTRSH %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDTRSW_REG:
      sprintf(tbuf,"LDTRSW %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDUR_IMM_REG_32:
      sprintf(tbuf,"LDUR %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDUR_IMM_REG_64:
      sprintf(tbuf,"LDUR %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDURB_IMM_REG:
      sprintf(tbuf,"LDURB %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDURH_IMM_REG:
      sprintf(tbuf,"LDURH %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDURSB_IMM_REG_32:
      sprintf(tbuf,"LDURSB %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDURSB_IMM_REG_64:
      sprintf(tbuf,"LDURSB %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDURSH_IMM_REG_32:
      sprintf(tbuf,"LDURSH %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDURSH_IMM_REG_64:
      sprintf(tbuf,"LDURSH %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDURSW_IMM_REG:
      sprintf(tbuf,"LDURSW %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case LDXP_32:
      sprintf(tbuf,"LDXP %s, %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnXZR(packet->Rt2.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case LDXP_64:
      sprintf(tbuf,"LDXP %s, %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnXZR(packet->Rt2.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case LDXR_32:
      sprintf(tbuf,"LDXR %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case LDXR_64:
      sprintf(tbuf,"LDXR %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case LDXRB:
      sprintf(tbuf,"LDXRB %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case LDXRH:
      sprintf(tbuf,"LDXRH %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case LSLV_32:
      sprintf(tbuf,"LSLV %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str());
      break;
   case LSLV_64:
      sprintf(tbuf,"LSLV %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case LSRV_32:
      sprintf(tbuf,"LSRV %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str());
      break;
   case LSRV_64:
      sprintf(tbuf,"LSRV %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case MADD_32:
      sprintf(tbuf,"MADD %s, %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),XnXZR(packet->Ra.Value(),true).c_str());
      break;
   case MADD_64:
      sprintf(tbuf,"MADD %s, %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),XnXZR(packet->Ra.Value(),false).c_str());
      break;
   case MOVK_IMM_32:
      sprintf(tbuf,"MOVK %s, #%d, LSL #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->imm16.Value(),packet->hw.Value()<<4);
      break;
   case MOVK_IMM_64:
      sprintf(tbuf,"MOVK %s, #%d, LSL #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->imm16.Value(),packet->hw.Value()<<4);
      break;
   case MOVN_IMM_32:
      sprintf(tbuf,"MOVN %s, #%d, LSL #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->imm16.Value(),packet->hw.Value()<<4);
      break;
   case MOVN_IMM_64:
      sprintf(tbuf,"MOVN %s, #%d, LSL #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->imm16.Value(),packet->hw.Value()<<4);
      break;
   case MOVZ_IMM_32:
      sprintf(tbuf,"MOVZ %s, #%d, LSL #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->imm16.Value(),packet->hw.Value()<<4);
      break;
   case MOVZ_IMM_64:
      sprintf(tbuf,"MOVZ %s, #%d, LSL #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->imm16.Value(),packet->hw.Value()<<4);
      break;
   case MRS:
      sprintf(tbuf,"MRS %s, %s\n",XnXZR(packet->Rt.Value(),false).c_str(),systemRegisterName(packet->op0.Value(),packet->op1.Value(),packet->CRn.Value(),packet->CRm.Value(),packet->op2.Value(),true).c_str());
      break;
   case MSR_IMM:
      sprintf(tbuf,"MSR %s, #%u\n",pstateFieldName(packet->op1.Value(),packet->op2.Value()).c_str(),packet->CRm.Value());
      break;
   case MSR_REG:
      sprintf(tbuf,"MSR %s, %s\n",systemRegisterName(packet->op0.Value(),packet->op1.Value(),packet->CRn.Value(),packet->CRm.Value(),packet->op2.Value(),false).c_str(),XnXZR(packet->Rt.Value(),false).c_str());
      break;
   case MSUB_32:
      sprintf(tbuf,"MSUB %s, %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),XnXZR(packet->Ra.Value(),true).c_str());
      break;
   case MSUB_64:
      sprintf(tbuf,"MSUB %s, %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),XnXZR(packet->Ra.Value(),false).c_str());
      break;
   case NOP:
      sprintf(tbuf,"NOP\n");
      break;
   case ORN_SHIFT_REG_32:
      sprintf(tbuf,"ORN %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),eon_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case ORN_SHIFT_REG_64:
      sprintf(tbuf,"ORN %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),eon_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case ORR_IMM_32:
      sprintf(tbuf,"ORR %s, %s, #%llu\n",XnSP(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),DecodeBitMasks(tmask,packet->N.Value(),packet->imms.Value(),packet->immr.Value(),true));
      break;
   case ORR_IMM_64:
      sprintf(tbuf,"ORR %s, %s, #%llu\n",XnSP(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),DecodeBitMasks(tmask,packet->N.Value(),packet->imms.Value(),packet->immr.Value(),true));
      break;
   case ORR_SHIFT_REG_32:
      sprintf(tbuf,"ORR %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),eon_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case ORR_SHIFT_REG_64:
      sprintf(tbuf,"ORR %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),eon_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case PRFM_REG_OFF:
      sprintf(tbuf,"PRFM %s, [%s, #%u]\n",prfop_name(packet->Rt.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case PRFM_REG:
      sprintf(tbuf,"PRFM %s, %lld\n",prfop_name(packet->Rt.Value()).c_str(),SignExtend(packet->imm19.Value()<<2,21));
      break;
   case PRFM_IMM_REG:
      sprintf(tbuf,"PRFM %s, [%s, %c%s, %s %u]\n",prfop_name(packet->Rt.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case PRFUM_IMM_REG:
      sprintf(tbuf,"PRFUM %s, [%s, #%d]\n",prfop_name(packet->Rt.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case RBIT_32:
      sprintf(tbuf,"RBIT %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str());
      break;
   case RBIT_64:
      sprintf(tbuf,"RBIT %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str());
      break;
   case RET:
      sprintf(tbuf,"RET %s\n",XnXZR(packet->Rn.Value(),false).c_str());
      break;
   case REV_32:
      sprintf(tbuf,"REV %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str());
      break;
   case REV_64:
      sprintf(tbuf,"REV %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str());
      break;
   case REV16_32:
      sprintf(tbuf,"REV16 %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str());
      break;
   case REV16_64:
      sprintf(tbuf,"REV16 %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str());
      break;
   case REV32:
      sprintf(tbuf,"REV32 %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str());
      break;
   case RORV_32:
      sprintf(tbuf,"RORV %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str());
      break;
   case RORV_64:
      sprintf(tbuf,"RORV %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SBC_32:
      sprintf(tbuf,"SBC %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str());
      break;
   case SBC_64:
      sprintf(tbuf,"SBC %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SBCS_32:
      sprintf(tbuf,"SBCS %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str());
      break;
   case SBCS_64:
      sprintf(tbuf,"SBCS %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SBFM_32:
      sprintf(tbuf,"SBFM %s, %s, #%u, #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),packet->immr.Value(),packet->imms.Value());
      break;
   case SBFM_64:
      sprintf(tbuf,"SBFM %s, %s, #%u, #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),packet->immr.Value(),packet->imms.Value());
      break;
   case SDIV_32:
      sprintf(tbuf,"SDIV %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str());
      break;
   case SDIV_64:
      sprintf(tbuf,"SDIV %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SEV:
      sprintf(tbuf,"SEV\n");
      break;
   case SEVL:
      sprintf(tbuf,"SEVL\n");
      break;
   case SMADDL:
      sprintf(tbuf,"SMADDL %s, %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),XnXZR(packet->Ra.Value(),false).c_str());
      break;
   case SMC:
      sprintf(tbuf,"SMC #%d\n",packet->imm16.Value());
      break;
   case SMSUBL:
      sprintf(tbuf,"SMSUBL %s, %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),XnXZR(packet->Ra.Value(),false).c_str());
      break;
   case SMULH:
      sprintf(tbuf,"SMULH %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case STLR_32:
      sprintf(tbuf,"STLR %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case STLR_64:
      sprintf(tbuf,"STLR %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case STLRB:
      sprintf(tbuf,"STLRB %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case STLRH:
      sprintf(tbuf,"STLRH %s, [%s,#0]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case STLXP_32:
      sprintf(tbuf,"STLXP %s, %s, %s, [%s,#0]\n",XnXZR(packet->Rs.Value(),true).c_str(),XnXZR(packet->Rt.Value(),true).c_str(),XnXZR(packet->Rt2.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case STLXP_64:
      sprintf(tbuf,"STLXP %s, %s, %s, [%s,#0]\n",XnXZR(packet->Rs.Value(),true).c_str(),XnXZR(packet->Rt.Value(),false).c_str(),XnXZR(packet->Rt2.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case STLXR_32:
      sprintf(tbuf,"STLXR %s, %s, [%s,#0]\n",XnXZR(packet->Rs.Value(),true).c_str(),XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case STLXR_64:
      sprintf(tbuf,"STLXR %s, %s, [%s,#0]\n",XnXZR(packet->Rs.Value(),true).c_str(),XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case STLXRB:
      sprintf(tbuf,"STLXRB %s, %s, [%s,#0]\n",XnXZR(packet->Rs.Value(),true).c_str(),XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case STLXRH:
      sprintf(tbuf,"STLXRH %s, %s, [%s,#0]\n",XnXZR(packet->Rs.Value(),true).c_str(),XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case STNP_OFF_32:
      sprintf(tbuf,"STNP %s, %s, [%s, #%lld]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnXZR(packet->Rt2.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case STNP_OFF_64:
      sprintf(tbuf,"STNP %s, %s, [%s, #%lld]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnXZR(packet->Rt2.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 8);
      break;
   case STP_REG_POST_32:
      sprintf(tbuf,"STP %s, %s, [%s], #%lld\n",XnXZR(packet->Rt.Value(),true).c_str(),XnXZR(packet->Rt2.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case STP_REG_POST_64:
      sprintf(tbuf,"STP %s, %s, [%s], #%lld\n",XnXZR(packet->Rt.Value(),false).c_str(),XnXZR(packet->Rt2.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 8);
      break;
   case STP_REG_PRE_32:
      sprintf(tbuf,"STP %s, %s, [%s, #%lld]!\n",XnXZR(packet->Rt.Value(),true).c_str(),XnXZR(packet->Rt2.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case STP_REG_PRE_64:
      sprintf(tbuf,"STP %s, %s, [%s, #%lld]!\n",XnXZR(packet->Rt.Value(),false).c_str(),XnXZR(packet->Rt2.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 8);
      break;
   case STP_REG_OFF_32:
      sprintf(tbuf,"STP %s, %s, [%s, #%lld]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnXZR(packet->Rt2.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case STP_REG_OFF_64:
      sprintf(tbuf,"STP %s, %s, [%s, #%lld]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnXZR(packet->Rt2.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 8);
      break;
   case STR_IMM_REG_POST_32:
      sprintf(tbuf,"STR %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case STR_IMM_REG_POST_64:
      sprintf(tbuf,"STR %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case STR_IMM_REG_PRE_32:
      sprintf(tbuf,"STR %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case STR_IMM_REG_PRE_64:
      sprintf(tbuf,"STR %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case STR_IMM_REG_32:
      sprintf(tbuf,"STR %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case STR_IMM_REG_64:
      sprintf(tbuf,"STR %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case STR_REG_OFF_32:
      sprintf(tbuf,"STR %s, [%s, %c%s, %s %u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case STR_REG_OFF_64:
      sprintf(tbuf,"STR %s, [%s, %c%s, %s %u]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case STRB_IMM_REG_POST:
      sprintf(tbuf,"STRB %s, [%s], #%d\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case STRB_IMM_REG_PRE:
      sprintf(tbuf,"STRB %s, [%s, #%d]!\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case STRB_IMM_REG_OFF:
      sprintf(tbuf,"STRB %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case STRB_REG_OFF:
      sprintf(tbuf,"STRB %s, [%s, %c%s, %s %u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case STRH_IMM_REG_POST:
      sprintf(tbuf,"STRH %s, [%s], #%d\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case STRH_IMM_REG_PRE:
      sprintf(tbuf,"STRH %s, [%s, #%d]!\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case STRH_IMM_REG_OFF:
      sprintf(tbuf,"STRH %s, [%s, #%u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case STRH_REG_OFF:
      sprintf(tbuf,"STRH %s, [%s, %c%s, %s %u]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case STTR_REG_32:
      sprintf(tbuf,"STTR %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case STTR_REG_64:
      sprintf(tbuf,"STTR %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case STTRB_REG:
      sprintf(tbuf,"STTRB %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case STTRH_REG:
      sprintf(tbuf,"STTRH %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case STUR_IMM_REG_32:
      sprintf(tbuf,"STUR %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case STUR_IMM_REG_64:
      sprintf(tbuf,"STUR %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case STURB_IMM_REG:
      sprintf(tbuf,"STURB %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case STURH_IMM_REG:
      sprintf(tbuf,"STURH %s, [%s, #%d]\n",XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case STXP_32:
      sprintf(tbuf,"STXP %s, %s, %s, [%s,#0]\n",XnXZR(packet->Rs.Value(),true).c_str(),XnXZR(packet->Rt.Value(),true).c_str(),XnXZR(packet->Rt2.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case STXP_64:
      sprintf(tbuf,"STXP %s, %s, %s, [%s,#0]\n",XnXZR(packet->Rs.Value(),true).c_str(),XnXZR(packet->Rt.Value(),false).c_str(),XnXZR(packet->Rt2.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case STXR_32:
      sprintf(tbuf,"STXR %s, %s, [%s,#0]\n",XnXZR(packet->Rs.Value(),true).c_str(),XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case STXR_64:
      sprintf(tbuf,"STXR %s, %s, [%s,#0]\n",XnXZR(packet->Rs.Value(),true).c_str(),XnXZR(packet->Rt.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case STXRB:
      sprintf(tbuf,"STXRB %s, %s, [%s,#0]\n",XnXZR(packet->Rs.Value(),true).c_str(),XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case STXRH:
      sprintf(tbuf,"STXRH %s, %s, [%s,#0]\n",XnXZR(packet->Rs.Value(),true).c_str(),XnXZR(packet->Rt.Value(),true).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SUB_REG_32:
      sprintf(tbuf,"SUB %s, %s, %s, %s #%u\n",XnSP(packet->Rd.Value(),true).c_str(),XnSP(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case SUB_REG_64:
      sprintf(tbuf,"SUB %s, %s, %c%s, %s #%u\n",XnSP(packet->Rd.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case SUB_IMM_32:
      sprintf(tbuf,"SUB %s, %s, #%u, %s\n",XnSP(packet->Rd.Value(),true).c_str(),XnSP(packet->Rn.Value(),true).c_str(),packet->imm12.Value(),as_imm_shift(packet->shift.Value()).c_str());
      break;
   case SUB_IMM_64:
      sprintf(tbuf,"SUB %s, %s, #%u, %s\n",XnSP(packet->Rd.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),packet->imm12.Value(),as_imm_shift(packet->shift.Value()).c_str());
      break;
   case SUB_SHIFT_REG_32:
      sprintf(tbuf,"SUB %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),as_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case SUB_SHIFT_REG_64:
      sprintf(tbuf,"SUB %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),as_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case SUBS_REG_32:
      sprintf(tbuf,"SUBS %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),XnSP(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case SUBS_REG_64:
      sprintf(tbuf,"SUBS %s, %s, %c%s, %s #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case SUBS_IMM_32:
      sprintf(tbuf,"SUBS %s, %s, #%u, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnSP(packet->Rn.Value(),true).c_str(),packet->imm12.Value(),as_imm_shift(packet->shift.Value()).c_str());
      break;
   case SUBS_IMM_64:
      sprintf(tbuf,"SUBS %s, %s, #%u, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnSP(packet->Rn.Value(),false).c_str(),packet->imm12.Value(),as_imm_shift(packet->shift.Value()).c_str());
      break;
   case SUBS_SHIFT_REG_32:
      sprintf(tbuf,"SUBS %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),as_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case SUBS_SHIFT_REG_64:
      sprintf(tbuf,"SUBS %s, %s, %s, %s #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str(),as_reg_shift(packet->shift.Value()).c_str(),packet->imm6.Value());
      break;
   case SVC:
      sprintf(tbuf,"SVC #%d\n",packet->imm16.Value());
      break;
   case SYS:
      sprintf(tbuf,"SYS #%d, C%u, C%u, #%d, %s\n",packet->op1.Value(),packet->CRm.Value(),packet->CRm.Value(),packet->op2.Value(),XnXZR(packet->Rt.Value(),false).c_str());
      break;
   case SYSL:
      sprintf(tbuf,"SYSL %s, #%d, C%u, C%u, #%d\n",XnXZR(packet->Rt.Value(),false).c_str(),packet->op1.Value(),packet->CRm.Value(),packet->CRm.Value(),packet->op2.Value());
      break;
   case TBNZ:
      sprintf(tbuf,"TBNZ %c%s, #%u, %lld\n",((packet->option.Value() & 3)==3) ? 'X' : 'W',t_or_sp(packet->Rt.Value()).c_str(),packet->b5.Value()<<4 | packet->b40.Value(),SignExtend(packet->imm14.Value()<<2,16));
      break;
   case TBZ:
      sprintf(tbuf,"TBZ %c%s, #%u, %lld\n",((packet->option.Value() & 3)==3) ? 'X' : 'W',t_or_sp(packet->Rt.Value()).c_str(),packet->b5.Value()<<4 | packet->b40.Value(),SignExtend(packet->imm14.Value()<<2,16));
      break;
   case UBFM_32:
      sprintf(tbuf,"UBFM %s, %s, #%u, #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),packet->immr.Value(),packet->imms.Value());
      break;
   case UBFM_64:
      sprintf(tbuf,"UBFM %s, %s, #%u, #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),packet->immr.Value(),packet->imms.Value());
      break;
   case UDIV_32:
      sprintf(tbuf,"UDIV %s, %s, %s\n",XnXZR(packet->Rd.Value(),true).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str());
      break;
   case UDIV_64:
      sprintf(tbuf,"UDIV %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case UMADDL:
      sprintf(tbuf,"UMADDL %s, %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),XnXZR(packet->Ra.Value(),false).c_str());
      break;
   case UMSUBL:
      sprintf(tbuf,"UMSUBL %s, %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),true).c_str(),XnXZR(packet->Rm.Value(),true).c_str(),XnXZR(packet->Ra.Value(),false).c_str());
      break;
   case UMULH:
      sprintf(tbuf,"UMULH %s, %s, %s\n",XnXZR(packet->Rd.Value(),false).c_str(),XnXZR(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case WFE:
      sprintf(tbuf,"WFE\n");
      break;
   case WFI:
      sprintf(tbuf,"WFI\n");
      break;
   case YIELD:
      sprintf(tbuf,"YIELD\n");
      break;
   case SIMD_ABS_REG_SCALAR:
      sprintf(tbuf,"ABS %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_ABS_REG_VEC:
      sprintf(tbuf,"ABS V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_ADD_SCALAR_VEC:
      sprintf(tbuf,"ADD %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_ADD_VEC_VEC:
      sprintf(tbuf,"ADD V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_ADDHN:
      if (packet->Q==0) sprintf(tbuf,"ADDHN V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rm.Value(),simdArrangementA(packet->size.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"ADDHN2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rm.Value(),simdArrangementA(packet->size.Value()).c_str());
      break;
   case SIMD_ADDP:
      sprintf(tbuf,"ADDP %s%u, V%d.%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_ADDP_VEC:
      sprintf(tbuf,"ADDP V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_ADDV:
      sprintf(tbuf,"ADDV %s%u, V%d.%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case AESD:
      sprintf(tbuf,"AESD V%d.16B, V%d.16B\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case AESE:
      sprintf(tbuf,"AESE V%d.16B, V%d.16B\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case AESIMC:
      sprintf(tbuf,"AESIMC V%d.16B, V%d.16B\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case AESMC:
      sprintf(tbuf,"AESMC V%d.16B, V%d.16B\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case SIMD_AND_VEC:
      sprintf(tbuf,"AND V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_BIC_IMM_MOD_VEC_32:
      sprintf(tbuf,"BIC V%d.%s, #%d, LSL #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->imm8.Value(),packet->imm3.Value());
      break;
   case SIMD_BIC_IMM_MOD_VEC_16:
      sprintf(tbuf,"BIC V%d.%s, #%d, LSL #%u   \n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->imm8.Value(),packet->imm3.Value());
      break;
   case SIMD_BIC_REG_VEC:
      sprintf(tbuf,"BIC V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_BIF:
      sprintf(tbuf,"BIF V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_BIT:
      sprintf(tbuf,"BIT V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_BSL:
      sprintf(tbuf,"BSL V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_CLS_REG_VEC:
      sprintf(tbuf,"CLS V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_CLZ_REG_VEC:
      sprintf(tbuf,"CLZ V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_CMEQ_REG_SCALAR:
      sprintf(tbuf,"CMEQ %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_CMEQ_REG_VEC:
      sprintf(tbuf,"CMEQ V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_CMEQ_REG_SCALAR_ZERO:
      sprintf(tbuf,"CMEQ %s%u, %s%u, #0\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_CMEQ_REG_VEC_ZERO:
      sprintf(tbuf,"CMEQ V%d.%s, V%d.%s, #0\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_CMGE_REG_SCALAR:
      sprintf(tbuf,"CMGE %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_CMGE_REG_VEC:
      sprintf(tbuf,"CMGE V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_CMGE_REG_SCALAR_ZERO:
      sprintf(tbuf,"CMGE %s%u, %s%u, #0\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_CMGE_REG_VEC_ZERO:
      sprintf(tbuf,"CMGE V%d.%s, V%d.%s, #0\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_CMGT_REG_SCALAR:
      sprintf(tbuf,"CMGT %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_CMGT_REG_VEC:
      sprintf(tbuf,"CMGT V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_CMGT_REG_SCALAR_ZERO:
      sprintf(tbuf,"CMGT %s%u, %s%u, #0\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_CMGT_REG_VEC_ZERO:
      sprintf(tbuf,"CMGT V%d.%s, V%d.%s, #0\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_CMHI_REG_SCALAR:
      sprintf(tbuf,"CMHI %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_CMHI_REG_VEC:
      sprintf(tbuf,"CMHI V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_CMHS_REG_SCALAR:
      sprintf(tbuf,"CMHS %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_CMHS_REG_VEC:
      sprintf(tbuf,"CMHS V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_CMLE_REG_SCALAR_ZERO:
      sprintf(tbuf,"CMLE %s%u, %s%u, #0\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_CMLE_REG_VEC_ZERO:
      sprintf(tbuf,"CMLE V%d.%s, V%d.%s, #0\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_CMLT_REG_SCALAR_ZERO:
      sprintf(tbuf,"CMLT %s%u, %s%u, #0\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_CMLT_REG_VEC_ZERO:
      sprintf(tbuf,"CMLT V%d.%s, V%d.%s, #0\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_CMTST_SCALAR:
      sprintf(tbuf,"CMTST %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_CMTST_VEC:
      sprintf(tbuf,"CMTST V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_CNT_REG:
      sprintf(tbuf,"CNT V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_DUP_SCALAR_ELEM:
      sprintf(tbuf,"DUP %s%u, V%d.%s[%s]\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),packet->Rn.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex(packet->imm5.Value()).c_str());
      break;
   case SIMD_DUP_VEC_ELEM:
      sprintf(tbuf,"DUP V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),Tvect(packet->imm5.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex(packet->imm5.Value()).c_str());
      break;
   case SIMD_DUP:
      sprintf(tbuf,"DUP V%d.%s, %c%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',packet->Rn.Value());
      break;
   case SIMD_EOR_VEC:
      sprintf(tbuf,"EOR V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_EXT:
      sprintf(tbuf,"EXT V%d.%s, V%d.%s, V%d.%s, #%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),simdLowByteNum(packet->Q.Value(),packet->imm4.Value()).c_str());
      break;
   case SIMD_FABD_SCALAR:
      sprintf(tbuf,"FABD %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_FABD_VEC:
      sprintf(tbuf,"FABD V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FABS_REG_VEC:
      sprintf(tbuf,"FABS V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FABS_SINGLE_FROM_SP:
      sprintf(tbuf,"FABS S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case FABS_FROM_DP:
      sprintf(tbuf,"FABS D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case SIMD_FACGE_SCALAR:
      sprintf(tbuf,"FACGE %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_FACGE_VEC:
      sprintf(tbuf,"FACGE V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FACGT_SCALAR:
      sprintf(tbuf,"FACGT %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_FACGT_VEC:
      sprintf(tbuf,"FACGT V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FADD_VEC:
      sprintf(tbuf,"FADD V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FADD_SINGLE_FROM_SP:
      sprintf(tbuf,"FADD S%d, S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case FADD_FROM_DP:
      sprintf(tbuf,"FADD D%d, D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case SIMD_FADDP:
      sprintf(tbuf,"FADDP %s%u, V%d.%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FADDP_VEC:
      sprintf(tbuf,"FADDP V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FCCMP_SINGLE_FROM_SP:
      sprintf(tbuf,"FCCMP S%d, S%d, #%u, %s\n",packet->Rn.Value(),packet->Rm.Value(),packet->nzcv.Value(),Bcond(packet->cond.Value()).c_str());
      break;
   case FCCMP_FROM_DP:
      sprintf(tbuf,"FCCMP D%d, D%d, #%u, %s\n",packet->Rn.Value(),packet->Rm.Value(),packet->nzcv.Value(),Bcond(packet->cond.Value()).c_str());
      break;
   case FCCMPE_SINGLE_FROM_SP:
      sprintf(tbuf,"FCCMPE S%d, S%d, #%u, %s\n",packet->Rn.Value(),packet->Rm.Value(),packet->nzcv.Value(),Bcond(packet->cond.Value()).c_str());
      break;
   case FCCMPE_FROM_DP:
      sprintf(tbuf,"FCCMPE D%d, D%d, #%u, %s\n",packet->Rn.Value(),packet->Rm.Value(),packet->nzcv.Value(),Bcond(packet->cond.Value()).c_str());
      break;
   case SIMD_FCMEQ_REG_SCALAR:
      sprintf(tbuf,"FCMEQ %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_FCMEQ_REG_VEC:
      sprintf(tbuf,"FCMEQ V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FCMEQ_REG_SCALAR_ZERO:
      sprintf(tbuf,"FCMEQ %s%u, %s%u, #0.0\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCMEQ_REG_VEC_ZERO:
      sprintf(tbuf,"FCMEQ V%d.%s, V%d.%s, #0.0\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FCMGE_REG_SCALAR:
      sprintf(tbuf,"FCMGE %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_FCMGE_REG_VEC:
      sprintf(tbuf,"FCMGE V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FCMGE_REG_SCALAR_ZERO:
      sprintf(tbuf,"FCMGE %s%u, %s%u, #0.0\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCMGE_REG_VEC_ZERO:
      sprintf(tbuf,"FCMGE V%d.%s, V%d.%s, #0.0\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FCMGT_REG_SCALAR:
      sprintf(tbuf,"FCMGT %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_FCMGT_REG_VEC:
      sprintf(tbuf,"FCMGT V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FCMGT_REG_SCALAR_ZERO:
      sprintf(tbuf,"FCMGT %s%u, %s%u, #0.0\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCMGT_REG_VEC_ZERO:
      sprintf(tbuf,"FCMGT V%d.%s, V%d.%s, #0.0\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FCMLE_REG_SCALAR_ZERO:
      sprintf(tbuf,"FCMLE %s%u, %s%u, #0.0\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCMLE_REG_VEC_ZERO:
      sprintf(tbuf,"FCMLE V%d.%s, V%d.%s, #0.0\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FCMLT_REG_SCALAR_ZERO:
      sprintf(tbuf,"FCMLT %s%u, %s%u, #0.0\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCMLT_REG_VEC_ZERO:
      sprintf(tbuf,"FCMLT V%d.%s, V%d.%s, #0.0\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FCMP_SINGLE_FROM_SP:
      sprintf(tbuf,"FCMP S%d, S%d\n",packet->Rn.Value(),packet->Rm.Value());
      break;
   case FCMP_FROM_DP:
      sprintf(tbuf,"FCMP D%d, D%d\n",packet->Rn.Value(),packet->Rm.Value());
      break;
   case FCMPE_SINGLE_FROM_SP:
      sprintf(tbuf,"FCMPE S%d, S%d\n",packet->Rn.Value(),packet->Rm.Value());
      break;
   case FCMPE_FROM_DP:
      sprintf(tbuf,"FCMPE D%d, D%d\n",packet->Rn.Value(),packet->Rm.Value());
      break;
   case FCSEL_SINGLE_FROM_SP:
      sprintf(tbuf,"FCSEL S%d, S%d, S%d, %s\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value(),Bcond(packet->cond.Value()).c_str());
      break;
   case FCSEL_FROM_DP:
      sprintf(tbuf,"FCSEL D%d, D%d, D%d, %s\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value(),Bcond(packet->cond.Value()).c_str());
      break;
   case FCVT_SINGLE_FROM_HP_TO_SP:
      sprintf(tbuf,"FCVT S%d, H%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case FCVT_FROM_HP_TO_DP:
      sprintf(tbuf,"FCVT D%d, H%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case FCVT_SINGLE_FROM_SP_TO_HP:
      sprintf(tbuf,"FCVT H%d, S%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case FCVT_SINGLE_FROM_SP_TO_DP:
      sprintf(tbuf,"FCVT D%d, S%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case FCVT_FROM_DP_TO_HP:
      sprintf(tbuf,"FCVT H%d, D%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case FCVT_SINGLE_FROM_DP_TO_SP:
      sprintf(tbuf,"FCVT S%d, D%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case SIMD_FCVTAS_REG_SCALAR_VEC:
      sprintf(tbuf,"FCVTAS %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTAS_REG_VEC_VEC:
      sprintf(tbuf,"FCVTAS V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FCVTAS_SINGLE_FROM_SP_FP_32:
      sprintf(tbuf,"FCVTAS %s, S%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTAS_SINGLE_FROM_SP_FP_64:
      sprintf(tbuf,"FCVTAS %s, S%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case FCVTAS_FROM_DP_FP_32:
      sprintf(tbuf,"FCVTAS %s, D%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTAS_FROM_DP_FP_64:
      sprintf(tbuf,"FCVTAS %s, D%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTAU_REG_SCALAR_VEC:
      sprintf(tbuf,"FCVTAU %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTAU_REG_VEC_VEC:
      sprintf(tbuf,"FCVTAU V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FCVTAU_SINGLE_FROM_SP_FP_32:
      sprintf(tbuf,"FCVTAU %s, S%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTAU_SINGLE_FROM_SP_FP_64:
      sprintf(tbuf,"FCVTAU %s, S%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case FCVTAU_FROM_DP_FP_32:
      sprintf(tbuf,"FCVTAU %s, D%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTAU_FROM_DP_FP_64:
      sprintf(tbuf,"FCVTAU %s, D%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTL_REG:
      if (packet->Q==0) sprintf(tbuf,"FCVTL V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"FCVTL2 V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FCVTMS_REG_SCALAR_VEC:
      sprintf(tbuf,"FCVTMS %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTMS_REG_VEC_VEC:
      sprintf(tbuf,"FCVTMS V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FCVTMS_SINGLE_FROM_SP_FP_32:
      sprintf(tbuf,"FCVTMS %s, S%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTMS_SINGLE_FROM_SP_FP_64:
      sprintf(tbuf,"FCVTMS %s, S%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case FCVTMS_FROM_DP_FP_32:
      sprintf(tbuf,"FCVTMS %s, D%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTMS_FROM_DP_FP_64:
      sprintf(tbuf,"FCVTMS %s, D%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTMU_REG_SCALAR_VEC:
      sprintf(tbuf,"FCVTMU %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTMU_REG_VEC_VEC:
      sprintf(tbuf,"FCVTMU V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FCVTMU_SINGLE_FROM_SP_FP_32:
      sprintf(tbuf,"FCVTMU %s, S%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTMU_SINGLE_FROM_SP_FP_64:
      sprintf(tbuf,"FCVTMU %s, S%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case FCVTMU_FROM_DP_FP_32:
      sprintf(tbuf,"FCVTMU %s, D%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTMU_FROM_DP_FP_64:
      sprintf(tbuf,"FCVTMU %s, D%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTN_REG:
      if (packet->Q==0) sprintf(tbuf,"FCVTN V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"FCVTN2 V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str());
      break;
   case SIMD_FCVTNS_REG_SCALAR_VEC:
      sprintf(tbuf,"FCVTNS %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTNS_REG_VEC_VEC:
      sprintf(tbuf,"FCVTNS V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FCVTNS_SINGLE_FROM_SP_FP_32:
      sprintf(tbuf,"FCVTNS %s, S%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTNS_SINGLE_FROM_SP_FP_64:
      sprintf(tbuf,"FCVTNS %s, S%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case FCVTNS_FROM_DP_FP_32:
      sprintf(tbuf,"FCVTNS %s, D%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTNS_FROM_DP_FP_64:
      sprintf(tbuf,"FCVTNS %s, D%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTNU_REG_SCALAR_VEC:
      sprintf(tbuf,"FCVTNU %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTNU_REG_VEC_VEC:
      sprintf(tbuf,"FCVTNU V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FCVTNU_SINGLE_FROM_SP_FP_32:
      sprintf(tbuf,"FCVTNU %s, S%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTNU_SINGLE_FROM_SP_FP_64:
      sprintf(tbuf,"FCVTNU %s, S%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case FCVTNU_FROM_DP_FP_32:
      sprintf(tbuf,"FCVTNU %s, D%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTNU_FROM_DP_FP_64:
      sprintf(tbuf,"FCVTNU %s, D%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTPS_REG_SCALAR_VEC:
      sprintf(tbuf,"FCVTPS %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTPS_REG_VEC_VEC:
      sprintf(tbuf,"FCVTPS V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FCVTPS_SINGLE_FROM_SP_FP_32:
      sprintf(tbuf,"FCVTPS %s, S%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTPS_SINGLE_FROM_SP_FP_64:
      sprintf(tbuf,"FCVTPS %s, S%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case FCVTPS_FROM_DP_FP_32:
      sprintf(tbuf,"FCVTPS %s, D%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTPS_FROM_DP_FP_64:
      sprintf(tbuf,"FCVTPS %s, D%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTPU_REG_SCALAR_VEC:
      sprintf(tbuf,"FCVTPU %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTPU_REG_VEC_VEC:
      sprintf(tbuf,"FCVTPU V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FCVTPU_SINGLE_FROM_SP_FP_32:
      sprintf(tbuf,"FCVTPU %s, S%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTPU_SINGLE_FROM_SP_FP_64:
      sprintf(tbuf,"FCVTPU %s, S%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case FCVTPU_FROM_DP_FP_32:
      sprintf(tbuf,"FCVTPU %s, D%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTPU_FROM_DP_FP_64:
      sprintf(tbuf,"FCVTPU %s, D%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTXN_REG_SCALAR:
      sprintf(tbuf,"FCVTXN %s%u, %s%u\n",(packet->size.Value()==1) ? "S" : "?",packet->Rd.Value(),(packet->size.Value()==1) ? "D" : "?",packet->Rn.Value());
      break;
   case SIMD_FCVTXN_REG_VEC:
      if (packet->Q==0) sprintf(tbuf,"FCVTXN V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"FCVTXN2 V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str());
      break;
   case SIMD_FCVTZS_SHIFT_IMM_SCALAR_VEC_FIXED:
      sprintf(tbuf,"FCVTZS %s%u, %s%u, #%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case SIMD_FCVTZS_SHIFT_IMM_VEC_VEC_FIXED:
      sprintf(tbuf,"FCVTZS V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case SIMD_FCVTZS_REG_SCALAR_VEC:
      sprintf(tbuf,"FCVTZS %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTZS_REG_VEC_VEC:
      sprintf(tbuf,"FCVTZS V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FCVTZS_SINGLE_FROM_SP_FP_FIXED_32:
      sprintf(tbuf,"FCVTZS %s, S%d, #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case FCVTZS_SINGLE_FROM_SP_FP_FIXED_64:
      sprintf(tbuf,"FCVTZS %s, S%d, #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case FCVTZS_FROM_DP_FP_FIXED_32:
      sprintf(tbuf,"FCVTZS %s, D%d, #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case FCVTZS_FROM_DP_FP_FIXED_64:
      sprintf(tbuf,"FCVTZS %s, D%d, #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case FCVTZS_SINGLE_FROM_SP_FP_32:
      sprintf(tbuf,"FCVTZS %s, S%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTZS_SINGLE_FROM_SP_FP_64:
      sprintf(tbuf,"FCVTZS %s, S%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case FCVTZS_FROM_DP_FP_32:
      sprintf(tbuf,"FCVTZS %s, D%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTZS_FROM_DP_FP_64:
      sprintf(tbuf,"FCVTZS %s, D%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTZU_SHIFT_IMM_SCALAR_VEC_FIXED:
      sprintf(tbuf,"FCVTZU %s%u, %s%u, #%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case SIMD_FCVTZU_SHIFT_IMM_VEC_VEC_FIXED:
      sprintf(tbuf,"FCVTZU V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case SIMD_FCVTZU_REG_SCALAR_VEC:
      sprintf(tbuf,"FCVTZU %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_FCVTZU_REG_VEC_VEC:
      sprintf(tbuf,"FCVTZU V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FCVTZU_SINGLE_FROM_SP_FP_FIXED_32:
      sprintf(tbuf,"FCVTZU %s, S%d, #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case FCVTZU_SINGLE_FROM_SP_FP_FIXED_64:
      sprintf(tbuf,"FCVTZU %s, S%d, #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case FCVTZU_FROM_DP_FP_FIXED_32:
      sprintf(tbuf,"FCVTZU %s, D%d, #%u\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case FCVTZU_FROM_DP_FP_FIXED_64:
      sprintf(tbuf,"FCVTZU %s, D%d, #%u\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case FCVTZU_SINGLE_FROM_SP_FP_32:
      sprintf(tbuf,"FCVTZU %s, S%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTZU_SINGLE_FROM_SP_FP_64:
      sprintf(tbuf,"FCVTZU %s, S%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case FCVTZU_FROM_DP_FP_32:
      sprintf(tbuf,"FCVTZU %s, D%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FCVTZU_FROM_DP_FP_64:
      sprintf(tbuf,"FCVTZU %s, D%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case SIMD_FDIV_VEC:
      sprintf(tbuf,"FDIV V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FDIV_SINGLE_FROM_SP:
      sprintf(tbuf,"FDIV S%d, S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case FDIV_FROM_DP:
      sprintf(tbuf,"FDIV D%d, D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case FMADD_SINGLE_FROM_SP:
      sprintf(tbuf,"FMADD S%d, S%d, S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value(),packet->Ra.Value());
      break;
   case FMADD_FROM_DP:
      sprintf(tbuf,"FMADD D%d, D%d, D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value(),packet->Ra.Value());
      break;
   case SIMD_FMAX_VEC:
      sprintf(tbuf,"FMAX V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FMAX_SINGLE_FROM_SP:
      sprintf(tbuf,"FMAX S%d, S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case FMAX_FROM_DP:
      sprintf(tbuf,"FMAX D%d, D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case SIMD_FMAXNM_VEC:
      sprintf(tbuf,"FMAXNM V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FMAXNM_SINGLE_FROM_SP:
      sprintf(tbuf,"FMAXNM S%d, S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case FMAXNM_FROM_DP:
      sprintf(tbuf,"FMAXNM D%d, D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case SIMD_FMAXNMP:
      sprintf(tbuf,"FMAXNMP %s%u, V%d.%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FMAXNMP_VEC:
      sprintf(tbuf,"FMAXNMP V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FMAXNMV:
      sprintf(tbuf,"FMAXNMV %s%u, V%d.%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FMAXP:
      sprintf(tbuf,"FMAXP %s%u, V%d.%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FMAXP_VEC:
      sprintf(tbuf,"FMAXP V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FMAXV:
      sprintf(tbuf,"FMAXV %s%u, V%d.%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FMIN_VEC:
      sprintf(tbuf,"FMIN V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FMIN_SINGLE_FROM_SP:
      sprintf(tbuf,"FMIN S%d, S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case FMIN_FROM_DP:
      sprintf(tbuf,"FMIN D%d, D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case SIMD_FMINNM_VEC:
      sprintf(tbuf,"FMINNM V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FMINNM_SINGLE_FROM_SP:
      sprintf(tbuf,"FMINNM S%d, S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case FMINNM_FROM_DP:
      sprintf(tbuf,"FMINNM D%d, D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case SIMD_FMINNMP:
      sprintf(tbuf,"FMINNMP %s%u, V%d.%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FMINNMP_VEC:
      sprintf(tbuf,"FMINNMP V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FMINNMV:
      sprintf(tbuf,"FMINNMV %s%u, V%d.%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FMINP:
      sprintf(tbuf,"FMINP %s%u, V%d.%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FMINP_VEC:
      sprintf(tbuf,"FMINP V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FMINV:
      sprintf(tbuf,"FMINV %s%u, V%d.%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FMLA_SCALAR_ELEM:
      sprintf(tbuf,"FMLA %s%u, %s%u, V%d.%s[%s]\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),fpElementIndex(packet->size.Value(),packet->L.Value(),packet->H.Value()).c_str());
      break;
   case SIMD_FMLA_VEC_VEC_ELEM:
      sprintf(tbuf,"FMLA V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),fpElementIndex(packet->size.Value(),packet->L.Value(),packet->H.Value()).c_str());
      break;
   case SIMD_FMLA_VEC:
      sprintf(tbuf,"FMLA V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FMLS_SCALAR_ELEM:
      sprintf(tbuf,"FMLS %s%u, %s%u, V%d.%s[%s]\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),fpElementIndex(packet->size.Value(),packet->L.Value(),packet->H.Value()).c_str());
      break;
   case SIMD_FMLS_VEC_VEC_ELEM:
      sprintf(tbuf,"FMLS V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),fpElementIndex(packet->size.Value(),packet->L.Value(),packet->H.Value()).c_str());
      break;
   case SIMD_FMLS_VEC:
      sprintf(tbuf,"FMLS V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FMOV_IMM_MOD_SINGLE_VEC_FROM_SP:
      sprintf(tbuf,"FMOV V%d.%s, #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->a.Value()<<7|packet->b.Value()<<6|packet->c.Value()<<5|packet->d.Value()<<4|packet->e.Value()<<3|packet->f.Value()<<2|packet->g.Value()<<1|packet->h.Value());
      break;
   case SIMD_FMOV_IMM_MOD_VEC_FROM_DP:
      sprintf(tbuf,"FMOV V%d.2D, #%u\n",packet->Rd.Value(),packet->a.Value()<<7|packet->b.Value()<<6|packet->c.Value()<<5|packet->d.Value()<<4|packet->e.Value()<<3|packet->f.Value()<<2|packet->g.Value()<<1|packet->h.Value());
      break;
   case FMOV_SINGLE_REG_FROM_SP:
      sprintf(tbuf,"FMOV S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case FMOV_REG_FROM_DP:
      sprintf(tbuf,"FMOV D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case FMOV_SINGLE_TO_SP_FP_32:
      sprintf(tbuf,"FMOV S%d, %s\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),true).c_str());
      break;
   case FMOV_SINGLE_FROM_SP_FP_32:
      sprintf(tbuf,"FMOV %s, S%d\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value());
      break;
   case FMOV_TO_DP_FP_64:
      sprintf(tbuf,"FMOV D%d, %s\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),false).c_str());
      break;
   case FMOV_FP_8_64_128_TO_TOP:
      sprintf(tbuf,"FMOV V%d.D[1], %s\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),false).c_str());
      break;
   case FMOV_FROM_DP_FP_64:
      sprintf(tbuf,"FMOV %s, D%d\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case FMOV_FP_8_64_128:
      sprintf(tbuf,"FMOV %s, V%d.D[1]\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value());
      break;
   case FMOV_IMM_SINGLE_FROM_SP:
      sprintf(tbuf,"FMOV S%d, #%u\n",packet->Rd.Value(),packet->imm8.Value());
      break;
   case FMOV_IMM_FROM_DP:
      sprintf(tbuf,"FMOV D%d, #%u\n",packet->Rd.Value(),packet->imm8.Value());
      break;
   case FMSUB_SINGLE_FROM_SP:
      sprintf(tbuf,"FMSUB S%d, S%d, S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value(),packet->Ra.Value());
      break;
   case FMSUB_FROM_DP:
      sprintf(tbuf,"FMSUB D%d, D%d, D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value(),packet->Ra.Value());
      break;
   case SIMD_FMUL_SCALAR_ELEM:
      sprintf(tbuf,"FMUL %s%u, %s%u, V%d.%s[%s]\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),fpElementIndex(packet->size.Value(),packet->L.Value(),packet->H.Value()).c_str());
      break;
   case SIMD_FMUL_VEC_VEC_ELEM:
      sprintf(tbuf,"FMUL V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),fpElementIndex(packet->size.Value(),packet->L.Value(),packet->H.Value()).c_str());
      break;
   case SIMD_FMUL_VEC:
      sprintf(tbuf,"FMUL V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FMUL_SINGLE_FROM_SP:
      sprintf(tbuf,"FMUL S%d, S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case FMUL_FROM_DP:
      sprintf(tbuf,"FMUL D%d, D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case SIMD_FMULX_SCALAR_ELEM:
      sprintf(tbuf,"FMULX %s%u, %s%u, V%d.%s[%s]\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),fpElementIndex(packet->size.Value(),packet->L.Value(),packet->H.Value()).c_str());
      break;
   case SIMD_FMULX_VEC_VEC_ELEM:
      sprintf(tbuf,"FMULX V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),fpElementIndex(packet->size.Value(),packet->L.Value(),packet->H.Value()).c_str());
      break;
   case SIMD_FMULX_SCALAR:
      sprintf(tbuf,"FMULX %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_FMULX_VEC:
      sprintf(tbuf,"FMULX V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FNEG_REG_VEC:
      sprintf(tbuf,"FNEG V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FNEG_SINGLE_FROM_SP:
      sprintf(tbuf,"FNEG S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case FNEG_FROM_DP:
      sprintf(tbuf,"FNEG D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case FNMADD_SINGLE_FROM_SP:
      sprintf(tbuf,"FNMADD S%d, S%d, S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value(),packet->Ra.Value());
      break;
   case FNMADD_FROM_DP:
      sprintf(tbuf,"FNMADD D%d, D%d, D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value(),packet->Ra.Value());
      break;
   case FNMSUB_SINGLE_FROM_SP:
      sprintf(tbuf,"FNMSUB S%d, S%d, S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value(),packet->Ra.Value());
      break;
   case FNMSUB_FROM_DP:
      sprintf(tbuf,"FNMSUB D%d, D%d, D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value(),packet->Ra.Value());
      break;
   case FNMUL_SINGLE_FROM_SP:
      sprintf(tbuf,"FNMUL S%d, S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case FNMUL_FROM_DP:
      sprintf(tbuf,"FNMUL D%d, D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case SIMD_FRECPE_REG_SCALAR:
      sprintf(tbuf,"FRECPE %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_FRECPE_REG_VEC:
      sprintf(tbuf,"FRECPE V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FRECPS_SCALAR:
      sprintf(tbuf,"FRECPS %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_FRECPS_VEC:
      sprintf(tbuf,"FRECPS V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FRECPX_REG:
      sprintf(tbuf,"FRECPX %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_FRINTA_REG_VEC:
      sprintf(tbuf,"FRINTA V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FRINTA_SINGLE_FROM_SP:
      sprintf(tbuf,"FRINTA S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case FRINTA_FROM_DP:
      sprintf(tbuf,"FRINTA D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case SIMD_FRINTI_REG_VEC:
      sprintf(tbuf,"FRINTI V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FRINTI_SINGLE_FROM_SP:
      sprintf(tbuf,"FRINTI S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case FRINTI_FROM_DP:
      sprintf(tbuf,"FRINTI D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case SIMD_FRINTM_REG_VEC:
      sprintf(tbuf,"FRINTM V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FRINTM_SINGLE_FROM_SP:
      sprintf(tbuf,"FRINTM S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case FRINTM_FROM_DP:
      sprintf(tbuf,"FRINTM D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case SIMD_FRINTN_REG_VEC:
      sprintf(tbuf,"FRINTN V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FRINTN_SINGLE_FROM_SP:
      sprintf(tbuf,"FRINTN S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case FRINTN_FROM_DP:
      sprintf(tbuf,"FRINTN D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case SIMD_FRINTP_REG_VEC:
      sprintf(tbuf,"FRINTP V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FRINTP_SINGLE_FROM_SP:
      sprintf(tbuf,"FRINTP S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case FRINTP_FROM_DP:
      sprintf(tbuf,"FRINTP D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case SIMD_FRINTX_REG_VEC:
      sprintf(tbuf,"FRINTX V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FRINTX_SINGLE_FROM_SP:
      sprintf(tbuf,"FRINTX S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case FRINTX_FROM_DP:
      sprintf(tbuf,"FRINTX D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case SIMD_FRINTZ_REG_VEC:
      sprintf(tbuf,"FRINTZ V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FRINTZ_SINGLE_FROM_SP:
      sprintf(tbuf,"FRINTZ S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case FRINTZ_FROM_DP:
      sprintf(tbuf,"FRINTZ D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case SIMD_FRSQRTE_REG_SCALAR:
      sprintf(tbuf,"FRSQRTE %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_FRSQRTE_REG_VEC:
      sprintf(tbuf,"FRSQRTE V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FRSQRTS_SCALAR:
      sprintf(tbuf,"FRSQRTS %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_FRSQRTS_VEC:
      sprintf(tbuf,"FRSQRTS V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_FSQRT_REG_VEC:
      sprintf(tbuf,"FSQRT V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FSQRT_SINGLE_FROM_SP:
      sprintf(tbuf,"FSQRT S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case FSQRT_FROM_DP:
      sprintf(tbuf,"FSQRT D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case SIMD_FSUB_VEC:
      sprintf(tbuf,"FSUB V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case FSUB_SINGLE_FROM_SP:
      sprintf(tbuf,"FSUB S%d, S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case FSUB_FROM_DP:
      sprintf(tbuf,"FSUB D%d, D%d, D%d\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case SIMD_INS_ELEM:
      sprintf(tbuf,"INS V%d.%s[%s], V%d.%s[%s]\n",packet->Rd.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex(packet->imm5.Value()).c_str(),packet->Rn.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex2(packet->imm5.Value(),packet->imm4.Value()).c_str());
      break;
   case SIMD_INS:
      sprintf(tbuf,"INS V%d.%s[%s], %c%u\n",packet->Rd.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex(packet->imm5.Value()).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',packet->Rn.Value());
      break;
   case SIMD_LD1_FOUR_REG_MULT_STRUCT:
      sprintf(tbuf,"LD1 V%d.%s, V%d.%s, V%d.%s, V%d.%s, [%s]\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 3) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD1_THREE_REG_MULT_STRUCT:
      sprintf(tbuf,"LD1 V%d.%s, V%d.%s, V%d.%s, [%s]\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD1_TWO_REG_MULT_STRUCT:
      sprintf(tbuf,"LD1 V%d.%s, V%d.%s, [%s]\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD1_ONE_REG_MULT_STRUCT:
      sprintf(tbuf,"LD1 V%d.%s, [%s]\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD1_ONE_REG_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"LD1  V%d.%s , [%s], %s\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD1_IMM_ONE_REG_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"LD1  V%d.%s , [%s], %u\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(packet->Q.Value()==1 ? 16 : 8));
      break;
   case SIMD_LD1_TWO_REG_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"LD1  V%d.%s, V%d.%s , [%s], %s\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD1_IMM_TWO_REG_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"LD1  V%d.%s, V%d.%s , [%s], %u\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(packet->Q.Value()==1 ? 32 : 16));
      break;
   case SIMD_LD1_THREE_REG_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"LD1  V%d.%s, V%d.%s, V%d.%s , [%s], %s\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD1_IMM_THREE_REG_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"LD1  V%d.%s, V%d.%s, V%d.%s , [%s], %u\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(packet->Q.Value()==1 ? 48 : 24));
      break;
   case SIMD_LD1_FOUR_REG_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"LD1  V%d.%s, V%d.%s, V%d.%s, V%d.%s , [%s], %s\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 3) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD1_IMM_FOUR_REG_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"LD1  V%d.%s, V%d.%s, V%d.%s, V%d.%s , [%s], %u\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 3) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(packet->Q.Value()==1 ? 64 : 32));
      break;
   case SIMD_LD1_SINGLE_STRUCT_8:
      sprintf(tbuf,"LD1  V%d.B [%u], [%s]\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_8:
      sprintf(tbuf,"LD1  V%d.B [%u], [%s], #1\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_8:
      sprintf(tbuf,"LD1  V%d.B [%u], [%s], %s\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD1_SINGLE_STRUCT_64:
      sprintf(tbuf,"LD1  V%d.D [%u], [%s]\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_64:
      sprintf(tbuf,"LD1  V%d.D [%u], [%s], #8\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_64:
      sprintf(tbuf,"LD1  V%d.D [%u], [%s], %s\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD1_SINGLE_STRUCT_16:
      sprintf(tbuf,"LD1  V%d.H [%u], [%s]\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_16:
      sprintf(tbuf,"LD1  V%d.H [%u], [%s], #2\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_16:
      sprintf(tbuf,"LD1  V%d.H [%u], [%s], %s\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD1_SINGLE_STRUCT_32:
      sprintf(tbuf,"LD1  V%d.S [%u], [%s]\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_32:
      sprintf(tbuf,"LD1  V%d.S [%u], [%s], #4\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_32:
      sprintf(tbuf,"LD1  V%d.S [%u], [%s], %s\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD1R_OFF_SINGLE_STRUCT:
      sprintf(tbuf,"LD1R  V%d.%s , [%s]\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD1R_REG_OFF_SINGLE_POST_STRUCT:
      sprintf(tbuf,"LD1R  V%d.%s , [%s], %s\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD1R_OFF_SINGLE_POST_STRUCT:
      sprintf(tbuf,"LD1R  V%d.%s , [%s], %u\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),1<<packet->size.Value());
      break;
   case SIMD_LD2_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"LD2  V%d.%s, V%d.%s , [%s]\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD2_REG_OFF_MULT_POST_STRUCT:
      if (packet->Rm.Value() != 0x1f) sprintf(tbuf,"LD2  V%d.%s, V%d.%s , [%s], %s\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      if (packet->Rm.Value() == 0x1f) sprintf(tbuf,"LD2  V%d.%s, V%d.%s , [%s], %u\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(packet->Q.Value()==1 ? 32 : 16));
      break;
   case SIMD_LD2_SINGLE_STRUCT_8:
      sprintf(tbuf,"LD2  V%d.B, V%d.B [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_8:
      sprintf(tbuf,"LD2  V%d.B, V%d.B [%u], [%s], #2\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_8:
      sprintf(tbuf,"LD2  V%d.B, V%d.B [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD2_SINGLE_STRUCT_64:
      sprintf(tbuf,"LD2  V%d.D, V%d.D [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_64:
      sprintf(tbuf,"LD2  V%d.D, V%d.D [%u], [%s], #16\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_64:
      sprintf(tbuf,"LD2  V%d.D, V%d.D [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD2_SINGLE_STRUCT_16:
      sprintf(tbuf,"LD2  V%d.H, V%d.H [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_16:
      sprintf(tbuf,"LD2  V%d.H, V%d.H [%u], [%s], #4\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_16:
      sprintf(tbuf,"LD2  V%d.H, V%d.H [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD2_SINGLE_STRUCT_32:
      sprintf(tbuf,"LD2  V%d.S, V%d.S [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_32:
      sprintf(tbuf,"LD2  V%d.S, V%d.S [%u], [%s], #8\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_32:
      sprintf(tbuf,"LD2  V%d.S, V%d.S [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD2R_OFF_SINGLE_STRUCT:
      sprintf(tbuf,"LD2R  V%d.%s, V%d.%s , [%s]\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD2R_REG_OFF_SINGLE_POST_STRUCT:
      sprintf(tbuf,"LD2R  V%d.%s, V%d.%s , [%s], %s\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD2R_OFF_SINGLE_POST_STRUCT:
      sprintf(tbuf,"LD2R  V%d.%s, V%d.%s , [%s], %u\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),1<<packet->size.Value());
      break;
   case SIMD_LD3_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"LD3  V%d.%s, V%d.%s, V%d.%s , [%s]\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD3_REG_OFF_MULT_POST_STRUCT:
      if (packet->Rm.Value() != 0x1f) sprintf(tbuf,"LD3  V%d.%s, V%d.%s, V%d.%s , [%s], %s\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      if (packet->Rm.Value() == 0x1f) sprintf(tbuf,"LD3  V%d.%s, V%d.%s, V%d.%s , [%s], %u\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(packet->Q.Value()==1 ? 48 : 24));
      break;
   case SIMD_LD3_SINGLE_STRUCT_8:
      sprintf(tbuf,"LD3  V%d.B, V%d.B, V%d.B [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_8:
      sprintf(tbuf,"LD3  V%d.B, V%d.B, V%d.B [%u], [%s], #3\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_8:
      sprintf(tbuf,"LD3  V%d.B, V%d.B, V%d.B [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD3_SINGLE_STRUCT_64:
      sprintf(tbuf,"LD3  V%d.D, V%d.D, V%d.D [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_64:
      sprintf(tbuf,"LD3  V%d.D, V%d.D, V%d.D [%u], [%s], #24\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_64:
      sprintf(tbuf,"LD3  V%d.D, V%d.D, V%d.D [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD3_SINGLE_STRUCT_16:
      sprintf(tbuf,"LD3  V%d.H, V%d.H, V%d.H [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_16:
      sprintf(tbuf,"LD3  V%d.H, V%d.H, V%d.H [%u], [%s], #6\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_16:
      sprintf(tbuf,"LD3  V%d.H, V%d.H, V%d.H [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD3_SINGLE_STRUCT_32:
      sprintf(tbuf,"LD3  V%d.S, V%d.S, V%d.S [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_32:
      sprintf(tbuf,"LD3  V%d.S, V%d.S, V%d.S [%u], [%s], #12\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_32:
      sprintf(tbuf,"LD3  V%d.S, V%d.S, V%d.S [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD3R_OFF_SINGLE_STRUCT:
      sprintf(tbuf,"LD3R  V%d.%s, V%d.%s, V%d.%s , [%s]\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD3R_REG_OFF_SINGLE_POST_STRUCT:
      sprintf(tbuf,"LD3R  V%d.%s, V%d.%s, V%d.%s , [%s], %s\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD3R_OFF_SINGLE_POST_STRUCT:
      sprintf(tbuf,"LD3R  V%d.%s, V%d.%s, V%d.%s , [%s], %u\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),1<<packet->size.Value());
      break;
   case SIMD_LD4_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"LD4  V%d.%s, V%d.%s, V%d.%s, V%d.%s , [%s]\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 3) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD4_REG_OFF_MULT_POST_STRUCT:
      if (packet->Rm.Value() != 0x1f) sprintf(tbuf,"LD4  V%d.%s, V%d.%s, V%d.%s, V%d.%s , [%s], %s\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 3) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      if (packet->Rm.Value() == 0x1f) sprintf(tbuf,"LD4  V%d.%s, V%d.%s, V%d.%s, V%d.%s , [%s], %u\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 3) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(packet->Q.Value()==1 ? 64 : 32));
      break;
   case SIMD_LD4_SINGLE_STRUCT_8:
      sprintf(tbuf,"LD4  V%d.B, V%d.B, V%d.B, V%d.B [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_8:
      sprintf(tbuf,"LD4  V%d.B, V%d.B, V%d.B, V%d.B [%u], [%s], #4\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_8:
      sprintf(tbuf,"LD4  V%d.B, V%d.B, V%d.B, V%d.B [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD4_SINGLE_STRUCT_64:
      sprintf(tbuf,"LD4  V%d.D, V%d.D, V%d.D, V%d.D [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_64:
      sprintf(tbuf,"LD4  V%d.D, V%d.D, V%d.D, V%d.D [%u], [%s], #32\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_64:
      sprintf(tbuf,"LD4  V%d.D, V%d.D, V%d.D, V%d.D [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD4_SINGLE_STRUCT_16:
      sprintf(tbuf,"LD4  V%d.H, V%d.H, V%d.H, V%d.H [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_16:
      sprintf(tbuf,"LD4  V%d.H, V%d.H, V%d.H, V%d.H [%u], [%s], #8\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_16:
      sprintf(tbuf,"LD4  V%d.H, V%d.H, V%d.H, V%d.H [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD4_SINGLE_STRUCT_32:
      sprintf(tbuf,"LD4  V%d.S, V%d.S, V%d.S, V%d.S [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_32:
      sprintf(tbuf,"LD4  V%d.S, V%d.S, V%d.S, V%d.S [%u], [%s], #16\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_32:
      sprintf(tbuf,"LD4  V%d.S, V%d.S, V%d.S, V%d.S [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD4R_OFF_SINGLE_STRUCT:
      sprintf(tbuf,"LD4R  V%d.%s, V%d.%s, V%d.%s, V%d.%s , [%s]\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 3) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_LD4R_REG_OFF_SINGLE_POST_STRUCT:
      sprintf(tbuf,"LD4R  V%d.%s, V%d.%s, V%d.%s, V%d.%s , [%s], %s\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 3) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_LD4R_OFF_SINGLE_POST_STRUCT:
      sprintf(tbuf,"LD4R  V%d.%s, V%d.%s, V%d.%s, V%d.%s , [%s], %u\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 3) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),1<<packet->size.Value());
      break;
   case SIMD_LDNP_OFF_64:
      sprintf(tbuf,"LDNP D%d, D%d, [%s, #%lld]\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 8);
      break;
   case SIMD_LDNP_OFF_8_128:
      sprintf(tbuf,"LDNP Q%d, Q%d, [%s, #%lld]\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 16);
      break;
   case SIMD_LDNP_OFF_32:
      sprintf(tbuf,"LDNP S%d, S%d, [%s, #%lld]\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case SIMD_LDP_REG_POST_64:
      sprintf(tbuf,"LDP D%d, D%d, [%s], #%lld\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 8);
      break;
   case SIMD_LDP_REG_POST_8_128:
      sprintf(tbuf,"LDP Q%d, Q%d, [%s], #%lld\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 16);
      break;
   case SIMD_LDP_REG_POST_32:
      sprintf(tbuf,"LDP S%d, S%d, [%s], #%lld\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case SIMD_LDP_REG_PRE_64:
      sprintf(tbuf,"LDP D%d, D%d, [%s, #%lld]!\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 8);
      break;
   case SIMD_LDP_REG_PRE_8_128:
      sprintf(tbuf,"LDP Q%d, Q%d, [%s, #%lld]!\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 16);
      break;
   case SIMD_LDP_REG_PRE_32:
      sprintf(tbuf,"LDP S%d, S%d, [%s, #%lld]!\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case SIMD_LDP_REG_OFF_64:
      sprintf(tbuf,"LDP D%d, D%d, [%s, #%lld]\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 8);
      break;
   case SIMD_LDP_REG_OFF_8_128:
      sprintf(tbuf,"LDP Q%d, Q%d, [%s, #%lld]\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 16);
      break;
   case SIMD_LDP_REG_OFF_32:
      sprintf(tbuf,"LDP S%d, S%d, [%s, #%lld]\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case SIMD_LDR_IMM_REG_PRE_8:
      sprintf(tbuf,"LDR B%d, [%s, #%d]!\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_LDR_IMM_REG_POST_8:
      sprintf(tbuf,"LDR B%d, [%s], #%d\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_LDR_IMM_REG_8:
      sprintf(tbuf,"LDR B%d, [%s, #%u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case SIMD_LDR_IMM_REG_PRE_64:
      sprintf(tbuf,"LDR D%d, [%s, #%d]!\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_LDR_IMM_REG_POST_64:
      sprintf(tbuf,"LDR D%d, [%s], #%d\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_LDR_IMM_REG_64:
      sprintf(tbuf,"LDR D%d, [%s, #%u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case SIMD_LDR_IMM_REG_PRE_16:
      sprintf(tbuf,"LDR H%d, [%s, #%d]!\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_LDR_IMM_REG_POST_16:
      sprintf(tbuf,"LDR H%d, [%s], #%d\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_LDR_IMM_REG_16:
      sprintf(tbuf,"LDR H%d, [%s, #%u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case SIMD_LDR_IMM_REG_PRE_8_128:
      sprintf(tbuf,"LDR Q%d, [%s, #%d]!\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_LDR_IMM_REG_POST_8_128:
      sprintf(tbuf,"LDR Q%d, [%s], #%d\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_LDR_IMM_REG_8_128:
      sprintf(tbuf,"LDR Q%d, [%s, #%u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case SIMD_LDR_IMM_REG_PRE_32:
      sprintf(tbuf,"LDR S%d, [%s, #%d]!\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_LDR_IMM_REG_POST_32:
      sprintf(tbuf,"LDR S%d, [%s], #%d\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_LDR_IMM_REG_32:
      sprintf(tbuf,"LDR S%d, [%s, #%u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case SIMD_LDR_REG_64:
      sprintf(tbuf,"LDR D%d, %lld\n",packet->Rt.Value(),SignExtend(packet->imm19.Value()<<2,21));
      break;
   case SIMD_LDR_REG_8_128:
      sprintf(tbuf,"LDR Q%d, %lld\n",packet->Rt.Value(),SignExtend(packet->imm19.Value()<<2,21));
      break;
   case SIMD_LDR_REG_32:
      sprintf(tbuf,"LDR S%d, %lld\n",packet->Rt.Value(),SignExtend(packet->imm19.Value()<<2,21));
      break;
   case SIMD_LDR_REG_OFF_8:
      sprintf(tbuf,"LDR B%d, [%s, %c%s, %s %u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case SIMD_LDR_REG_OFF_64:
      sprintf(tbuf,"LDR D%d, [%s, %c%s, %s %u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case SIMD_LDR_REG_OFF_16:
      sprintf(tbuf,"LDR H%d, [%s, %c%s, %s %u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case SIMD_LDR_REG_OFF_8_128:
      sprintf(tbuf,"LDR Q%d, [%s, %c%s, %s %u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case SIMD_LDR_REG_OFF_32:
      sprintf(tbuf,"LDR S%d, [%s, %c%s, %s %u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case SIMD_LDUR_IMM_REG_8:
      sprintf(tbuf,"LDUR B%d, [%s, #%d]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_LDUR_IMM_REG_64:
      sprintf(tbuf,"LDUR D%d, [%s, #%d]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_LDUR_IMM_REG_16:
      sprintf(tbuf,"LDUR H%d, [%s, #%d]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_LDUR_IMM_REG_8_128:
      sprintf(tbuf,"LDUR Q%d, [%s, #%d]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_LDUR_IMM_REG_32:
      sprintf(tbuf,"LDUR S%d, [%s, #%d]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_MLA_VEC_ELEM:
      sprintf(tbuf,"MLA V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_MLA_VEC:
      sprintf(tbuf,"MLA V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_MLS_VEC_ELEM:
      sprintf(tbuf,"MLS V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_MLS_VEC:
      sprintf(tbuf,"MLS V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_MOVI_SHIFT_IMM_MOD_16:
      sprintf(tbuf,"MOVI V%d.%s, #%u, LSL #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->a.Value()<<7|packet->b.Value()<<6|packet->c.Value()<<5|packet->d.Value()<<4|packet->e.Value()<<3|packet->f.Value()<<2|packet->g.Value()<<1|packet->h.Value(),packet->imm3.Value());
      break;
   case SIMD_MOVI_SHIFT_IMM_MOD_32:
      sprintf(tbuf,"MOVI V%d.%s, #%u, LSL #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->a.Value()<<7|packet->b.Value()<<6|packet->c.Value()<<5|packet->d.Value()<<4|packet->e.Value()<<3|packet->f.Value()<<2|packet->g.Value()<<1|packet->h.Value(),packet->imm3.Value());
      break;
   case SIMD_MOVI_SHIFT_IMM_ONES_MOD_32:
      sprintf(tbuf,"MOVI V%d.%s, #%u, MSL #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->a.Value()<<7|packet->b.Value()<<6|packet->c.Value()<<5|packet->d.Value()<<4|packet->e.Value()<<3|packet->f.Value()<<2|packet->g.Value()<<1|packet->h.Value(),packet->imm3.Value());
      break;
   case SIMD_MOVI_IMM_MOD_64:
      sprintf(tbuf,"MOVI D%d, #%llu\n",packet->Rd.Value(),FP8exp(packet->a.Value(),packet->b.Value(),packet->c.Value(),packet->d.Value(),packet->e.Value(),packet->f.Value(),packet->g.Value(),packet->h.Value()));
      break;
   case SIMD_MOVI_IMM_MOD_VEC_64:
      sprintf(tbuf,"MOVI V%d.2D, #%llu\n",packet->Rd.Value(),FP8exp(packet->a.Value(),packet->b.Value(),packet->c.Value(),packet->d.Value(),packet->e.Value(),packet->f.Value(),packet->g.Value(),packet->h.Value()));
      break;
   case SIMD_MOVI_IMM_MOD_8:
      sprintf(tbuf,"MOVI V%d.%s, #%u, LSL #0\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->a.Value()<<7|packet->b.Value()<<6|packet->c.Value()<<5|packet->d.Value()<<4|packet->e.Value()<<3|packet->f.Value()<<2|packet->g.Value()<<1|packet->h.Value());
      break;
   case SIMD_MUL_VEC_ELEM:
      sprintf(tbuf,"MUL V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_MUL_VEC:
      sprintf(tbuf,"MUL V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_MVNI_SHIFT_IMM_MOD_16:
      sprintf(tbuf,"MVNI V%d.%s, #%d, LSL #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->imm8.Value(),packet->imm3.Value());
      break;
   case SIMD_MVNI_SHIFT_IMM_MOD_32:
      sprintf(tbuf,"MVNI V%d.%s, #%d, LSL #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->imm8.Value(),packet->imm3.Value());
      break;
   case SIMD_MVNI_SHIFT_IMM_ONES_MOD_32:
      sprintf(tbuf,"MVNI V%d.%s, #%d, MSL #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->imm8.Value(),packet->imm3.Value());
      break;
   case SIMD_NEG_REG_SCALAR_VEC:
      sprintf(tbuf,"NEG %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_NEG_REG_VEC_VEC:
      sprintf(tbuf,"NEG V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_NOT_REG:
      sprintf(tbuf,"NOT V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_ORN_VEC:
      sprintf(tbuf,"ORN V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_ORR_IMM_MOD_VEC_32:
      sprintf(tbuf,"ORR V%d.%s, #%d, LSL #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->imm8.Value(),packet->imm3.Value());
      break;
   case SIMD_ORR_IMM_MOD_VEC_16:
      sprintf(tbuf,"ORR V%d.%s, #%d, LSL #%u   \n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->imm8.Value(),packet->imm3.Value());
      break;
   case SIMD_ORR_REG_VEC:
      sprintf(tbuf,"ORR V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_PMUL:
      sprintf(tbuf,"PMUL V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_PMULL:
      if (packet->Q==0) sprintf(tbuf,"PMULL V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"PMULL2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_RADDHN:
      if (packet->Q==0) sprintf(tbuf,"RADDHN V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rm.Value(),simdArrangementA(packet->size.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"RADDHN2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rm.Value(),simdArrangementA(packet->size.Value()).c_str());
      break;
   case SIMD_RBIT_REG_VEC:
      sprintf(tbuf,"RBIT V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_REV16_REG_VEC:
      sprintf(tbuf,"REV16 V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_REV32_REG_VEC:
      sprintf(tbuf,"REV32 V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_REV64_REG:
      sprintf(tbuf,"REV64 V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_RSHRN_SHIFT_IMM:
      if (packet->Q==0) sprintf(tbuf,"RSHRN V%d.%s, V%d.%s, #%s\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),simd_rshift1(packet->immh.Value(),packet->immb.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"RSHRN2 V%d.%s, V%d.%s, #%s\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),simd_rshift1(packet->immh.Value(),packet->immb.Value()).c_str());
      break;
   case SIMD_RSUBHN:
      if (packet->Q==0) sprintf(tbuf,"RSUBHN V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rm.Value(),simdArrangementA(packet->size.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"RSUBHN2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rm.Value(),simdArrangementA(packet->size.Value()).c_str());
      break;
   case SIMD_SABA:
      sprintf(tbuf,"SABA V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SABAL:
      if (packet->Q==0) sprintf(tbuf,"SABAL V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SABAL2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SABD:
      sprintf(tbuf,"SABD V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SABDL:
      if (packet->Q==0) sprintf(tbuf,"SABDL V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SABDL2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SADALP_REG:
      sprintf(tbuf,"SADALP V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SADDL:
      if (packet->Q==0) sprintf(tbuf,"SADDL V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SADDL2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SADDLP_REG:
      sprintf(tbuf,"SADDLP V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SADDLV:
      sprintf(tbuf,"SADDLV %s%u, V%d.%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SADDW:
      if (packet->Q==0) sprintf(tbuf,"SADDW V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SADDW2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SCVTF_SHIFT_IMM_SCALAR_VEC_FIXED:
      sprintf(tbuf,"SCVTF %s%u, %s%u, #%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case SIMD_SCVTF_SHIFT_IMM_VEC_VEC_FIXED:
      sprintf(tbuf,"SCVTF V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case SIMD_SCVTF_REG_SCALAR_VEC:
      sprintf(tbuf,"SCVTF %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_SCVTF_REG_VEC_VEC:
      sprintf(tbuf,"SCVTF V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SCVTF_SINGLE_TO_SP_FP_FIXED_32:
      sprintf(tbuf,"SCVTF S%d, %s, #%u\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),true).c_str(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case SCVTF_TO_DP_FP_FIXED_32:
      sprintf(tbuf,"SCVTF D%d, %s, #%u\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),true).c_str(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case SCVTF_SINGLE_TO_SP_FP_FIXED_64:
      sprintf(tbuf,"SCVTF S%d, %s, #%u\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),false).c_str(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case SCVTF_TO_DP_FP_FIXED_64:
      sprintf(tbuf,"SCVTF D%d, %s, #%u\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),false).c_str(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case SCVTF_SINGLE_TO_SP_FP_32:
      sprintf(tbuf,"SCVTF S%d, %s\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),true).c_str());
      break;
   case SCVTF_TO_DP_FP_32:
      sprintf(tbuf,"SCVTF D%d, %s\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),true).c_str());
      break;
   case SCVTF_SINGLE_TO_SP_FP_64:
      sprintf(tbuf,"SCVTF S%d, %s\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),false).c_str());
      break;
   case SCVTF_TO_DP_FP_64:
      sprintf(tbuf,"SCVTF D%d, %s\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),false).c_str());
      break;
   case SHA1C_REG:
      sprintf(tbuf,"SHA1C Q%d, S%d, V%d.4S\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case SHA1H_REG:
      sprintf(tbuf,"SHA1H S%d, S%d\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case SHA1M_REG:
      sprintf(tbuf,"SHA1M Q%d, S%d, V%d.4S\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case SHA1P_REG:
      sprintf(tbuf,"SHA1P Q%d, S%d, V%d.4S\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case SHA1SU0_REG:
      sprintf(tbuf,"SHA1SU0 V%d.4S, V%d.4S, V%d.4S\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case SHA1SU1_REG:
      sprintf(tbuf,"SHA1SU1 V%d.4S, V%d.4S\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case SHA256H2_REG:
      sprintf(tbuf,"SHA256H2 Q%d, Q%d, V%d.4S\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case SHA256H_REG:
      sprintf(tbuf,"SHA256H Q%d, Q%d, V%d.4S\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case SHA256SU0_REG:
      sprintf(tbuf,"SHA256SU0 V%d.4S, V%d.4S\n",packet->Rd.Value(),packet->Rn.Value());
      break;
   case SHA256SU1_REG:
      sprintf(tbuf,"SHA256SU1 V%d.4S, V%d.4S, V%d.4S\n",packet->Rd.Value(),packet->Rn.Value(),packet->Rm.Value());
      break;
   case SIMD_SHADD:
      sprintf(tbuf,"SHADD V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SHL_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"SHL %s%u, %s%u, #%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simd_lshift_scalar(packet->immh.Value(),packet->immb.Value()).c_str());
      break;
   case SIMD_SHL_SHIFT_IMM_VEC:
      sprintf(tbuf,"SHL V%d.%s, V%d.%s, #%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),simd_lshift_vector(packet->immh.Value(),packet->immb.Value()).c_str());
      break;
   case SIMD_SHLL_REG:
      if (packet->Q==0) sprintf(tbuf,"SHLL V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),(packet->immh.Value()<<3|packet->immb.Value()) - (8<<HighestSetBit(packet->immh.Value(),4)));
      if (packet->Q==1) sprintf(tbuf,"SHLL2 V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),(packet->immh.Value()<<3|packet->immb.Value()) - (8<<HighestSetBit(packet->immh.Value(),4)));
      break;
   case SIMD_SHRN_SHIFT_IMM:
      if (packet->Q==0) sprintf(tbuf,"SHRN V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),(packet->immh.Value()<<3|packet->immb.Value()) - (8<<HighestSetBit(packet->immh.Value(),4)));
      if (packet->Q==1) sprintf(tbuf,"SHRN2 V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),(packet->immh.Value()<<3|packet->immb.Value()) - (8<<HighestSetBit(packet->immh.Value(),4)));
      break;
   case SIMD_SHSUB:
      sprintf(tbuf,"SHSUB V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SLI_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"SLI %s%u, %s%u, #%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),(packet->immh.Value()<<3|packet->immb.Value()) - (8<<3));
      break;
   case SIMD_SLI_SHIFT_IMM_VEC:
      sprintf(tbuf,"SLI V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->immh.Value()<<3|packet->immb.Value()) - (8<<HighestSetBit(packet->immh.Value(),4)));
      break;
   case SIMD_SMAX:
      sprintf(tbuf,"SMAX V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SMAXP:
      sprintf(tbuf,"SMAXP V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SMAXV:
      sprintf(tbuf,"SMAXV %s%u, V%d.%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SMIN:
      sprintf(tbuf,"SMIN V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SMINP:
      sprintf(tbuf,"SMINP V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SMINV:
      sprintf(tbuf,"SMINV %s%u, V%d.%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SMLAL_VEC_ELEM:
      if (packet->Q==0) sprintf(tbuf,"SMLAL V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SMLAL2 V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_SMLAL_VEC:
      if (packet->Q==0) sprintf(tbuf,"SMLAL V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SMLAL2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SMLSL_VEC_ELEM:
      if (packet->Q==0) sprintf(tbuf,"SMLSL V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SMLSL2 V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_SMLSL_VEC:
      if (packet->Q==0) sprintf(tbuf,"SMLSL V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SMLSL2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SMOV_32:
      sprintf(tbuf,"SMOV %s, V%d.%s[%s]\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex2(packet->imm5.Value(),packet->imm4.Value()).c_str());
      break;
   case SIMD_SMOV_64:
      sprintf(tbuf,"SMOV %s, V%d.%s[%s]\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex(packet->imm5.Value()).c_str());
      break;
   case SIMD_SMULL_VEC_ELEM:
      if (packet->Q==0) sprintf(tbuf,"SMULL V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SMULL2 V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_SMULL_VEC:
      if (packet->Q==0) sprintf(tbuf,"SMULL V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SMULL2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SQABS_REG_SCALAR:
      sprintf(tbuf,"SQABS %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_SQABS_REG_VEC:
      sprintf(tbuf,"SQABS V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SQADD_SCALAR:
      sprintf(tbuf,"SQADD %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_SQADD_VEC:
      sprintf(tbuf,"SQADD V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SQDMLAL_SCALAR_ELEM:
      sprintf(tbuf,"SQDMLAL %s%u, %s%u, V%d.%s[%s]\n",(packet->size.Value()==1) ? "D" : "?",packet->Rd.Value(),(packet->size.Value()==1) ? "S" : "?",packet->Rn.Value(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_SQDMLAL_VEC_VEC_ELEM:
      if (packet->Q==0) sprintf(tbuf,"SQDMLAL V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SQDMLAL2 V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_SQDMLAL_SCALAR_VEC:
      sprintf(tbuf,"SQDMLAL %s%u, %s%u, %s%s\n",(packet->size.Value()==1) ? "D" : "?",packet->Rd.Value(),(packet->size.Value()==1) ? "S" : "?",packet->Rn.Value(),(packet->size.Value()==1) ? "S" : "?",ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_SQDMLAL_VEC_VEC:
      if (packet->Q==0) sprintf(tbuf,"SQDMLAL V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SQDMLAL2 V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SQDMLSL_SCALAR_ELEM:
      sprintf(tbuf,"SQDMLSL %s%u, %s%u, V%d.%s[%s]\n",(packet->size.Value()==1) ? "D" : "?",packet->Rd.Value(),(packet->size.Value()==1) ? "S" : "?",packet->Rn.Value(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_SQDMLSL_VEC_VEC_ELEM:
      if (packet->Q==0) sprintf(tbuf,"SQDMLSL V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SQDMLSL2 V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_SQDMLSL_SCALAR_VEC:
      sprintf(tbuf,"SQDMLSL %s%u, %s%u, %s%s\n",(packet->size.Value()==1) ? "D" : "?",packet->Rd.Value(),(packet->size.Value()==1) ? "S" : "?",packet->Rn.Value(),(packet->size.Value()==1) ? "S" : "?",ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_SQDMLSL_VEC_VEC:
      if (packet->Q==0) sprintf(tbuf,"SQDMLSL V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SQDMLSL2 V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SQDMULH_SCALAR_ELEM:
      sprintf(tbuf,"SQDMULH %s%u, %s%u, V%d.%s[%s]\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_SQDMULH_VEC_VEC_ELEM:
      sprintf(tbuf,"SQDMULH V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_SQDMULH_SCALAR_VEC:
      sprintf(tbuf,"SQDMULH %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_SQDMULH_VEC_VEC:
      sprintf(tbuf,"SQDMULH V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SQDMULL_SCALAR_ELEM:
      sprintf(tbuf,"SQDMULL %s%u, %s%u, V%d.%s[%s]\n",(packet->size.Value()==1) ? "D" : "?",packet->Rd.Value(),(packet->size.Value()==1) ? "S" : "?",packet->Rn.Value(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_SQDMULL_VEC_VEC_ELEM:
      if (packet->Q==0) sprintf(tbuf,"SQDMULL V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SQDMULL2 V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_SQDMULL_SCALAR_VEC:
      sprintf(tbuf,"SQDMULL %s%u, %s%u, %s%s\n",(packet->size.Value()==1) ? "D" : "?",packet->Rd.Value(),(packet->size.Value()==1) ? "S" : "?",packet->Rn.Value(),(packet->size.Value()==1) ? "S" : "?",ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_SQDMULL_VEC_VEC:
      if (packet->Q==0) sprintf(tbuf,"SQDMULL V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SQDMULL2 V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SQNEG_REG_SCALAR:
      sprintf(tbuf,"SQNEG %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_SQNEG_REG_VEC:
      sprintf(tbuf,"SQNEG V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SQRDMULH_SCALAR_ELEM:
      sprintf(tbuf,"SQRDMULH %s%u, %s%u, V%d.%s[%s]\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_SQRDMULH_VEC_VEC_ELEM:
      sprintf(tbuf,"SQRDMULH V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_SQRDMULH_SCALAR_VEC:
      sprintf(tbuf,"SQRDMULH %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_SQRDMULH_VEC_VEC:
      sprintf(tbuf,"SQRDMULH V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SQRSHL_SCALAR:
      sprintf(tbuf,"SQRSHL %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_SQRSHL_VEC:
      sprintf(tbuf,"SQRSHL V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SQRSHRN_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"SQRSHRN %s%u, %s%u, #%u\n",(packet->size.Value()==1) ? "S" : "?",packet->Rd.Value(),(packet->size.Value()==1) ? "D" : "?",packet->Rn.Value(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_SQRSHRN_SHIFT_IMM_VEC:
      if (packet->Q==0) sprintf(tbuf,"SQRSHRN V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      if (packet->Q==1) sprintf(tbuf,"SQRSHRN2 V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_SQRSHRUN_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"SQRSHRUN %s%u, %s%u, #%u\n",(packet->size.Value()==1) ? "S" : "?",packet->Rd.Value(),(packet->size.Value()==1) ? "D" : "?",packet->Rn.Value(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_SQRSHRUN_SHIFT_IMM_VEC:
      if (packet->Q==0) sprintf(tbuf,"SQRSHRUN V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      if (packet->Q==1) sprintf(tbuf,"SQRSHRUN2 V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_SQSHL_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"SQSHL %s%u, %s%u, #%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),(packet->immh.Value()<<3|packet->immb.Value()) - (8<<HighestSetBit(packet->immh.Value(),4)));
      break;
   case SIMD_SQSHL_SHIFT_IMM_VEC:
      sprintf(tbuf,"SQSHL V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->immh.Value()<<3|packet->immb.Value()) - (8<<HighestSetBit(packet->immh.Value(),4)));
      break;
   case SIMD_SQSHL_REG_SCALAR:
      sprintf(tbuf,"SQSHL %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_SQSHL_REG_VEC:
      sprintf(tbuf,"SQSHL V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SQSHLU_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"SQSHLU %s%u, %s%u, #%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),(packet->immh.Value()<<3|packet->immb.Value()) - (8<<HighestSetBit(packet->immh.Value(),4)));
      break;
   case SIMD_SQSHLU_SHIFT_IMM_VEC:
      sprintf(tbuf,"SQSHLU V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->immh.Value()<<3|packet->immb.Value()) - (8<<HighestSetBit(packet->immh.Value(),4)));
      break;
   case SIMD_SQSHRN_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"SQSHRN %s%u, %s%u, #%u\n",(packet->size.Value()==1) ? "S" : "?",packet->Rd.Value(),(packet->size.Value()==1) ? "D" : "?",packet->Rn.Value(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_SQSHRN_SHIFT_IMM_VEC:
      if (packet->Q==0) sprintf(tbuf,"SQSHRN V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      if (packet->Q==1) sprintf(tbuf,"SQSHRN2 V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_SQSHRUN_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"SQSHRUN %s%u, %s%u, #%u\n",(packet->size.Value()==1) ? "S" : "?",packet->Rd.Value(),(packet->size.Value()==1) ? "D" : "?",packet->Rn.Value(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_SQSHRUN_SHIFT_IMM_VEC:
      if (packet->Q==0) sprintf(tbuf,"SQSHRUN V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      if (packet->Q==1) sprintf(tbuf,"SQSHRUN2 V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_SQSUB_SCALAR:
      sprintf(tbuf,"SQSUB %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_SQSUB_VEC:
      sprintf(tbuf,"SQSUB V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SQXTN_REG_SCALAR:
      sprintf(tbuf,"SQXTN %s%u, %s%u\n",(packet->size.Value()==1) ? "S" : "?",packet->Rd.Value(),(packet->size.Value()==1) ? "D" : "?",packet->Rn.Value());
      break;
   case SIMD_SQXTN_REG_VEC:
      if (packet->Q==0) sprintf(tbuf,"SQXTN V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SQXTN2 V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str());
      break;
   case SIMD_SQXTUN_REG_SCALAR:
      sprintf(tbuf,"SQXTUN %s%u, %s%u\n",(packet->size.Value()==1) ? "S" : "?",packet->Rd.Value(),(packet->size.Value()==1) ? "D" : "?",packet->Rn.Value());
      break;
   case SIMD_SQXTUN_REG_VEC:
      if (packet->Q==0) sprintf(tbuf,"SQXTUN V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SQXTUN2 V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str());
      break;
   case SIMD_SRHADD:
      sprintf(tbuf,"SRHADD V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SRI_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"SRI %s%u, %s%u, #%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_SRI_SHIFT_IMM_VEC:
      sprintf(tbuf,"SRI V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_SRSHL_SCALAR:
      sprintf(tbuf,"SRSHL %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_SRSHL_VEC:
      sprintf(tbuf,"SRSHL V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SRSHR_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"SRSHR %s%u, %s%u, #%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_SRSHR_SHIFT_IMM_VEC:
      sprintf(tbuf,"SRSHR V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_SRSRA_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"SRSRA %s%u, %s%u, #%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_SRSRA_SHIFT_IMM_VEC:
      sprintf(tbuf,"SRSRA V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_SSHL_SCALAR:
      sprintf(tbuf,"SSHL %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_SSHL_VEC:
      sprintf(tbuf,"SSHL V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SSHLL_SHIFT_IMM:
      if (packet->Q==0) sprintf(tbuf,"SSHLL V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),(packet->immh.Value()<<3|packet->immb.Value()) - (8<<HighestSetBit(packet->immh.Value(),4)));
      if (packet->Q==1) sprintf(tbuf,"SSHLL2 V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),(packet->immh.Value()<<3|packet->immb.Value()) - (8<<HighestSetBit(packet->immh.Value(),4)));
      break;
   case SIMD_SSHR_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"SSHR %s%u, %s%u, #%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_SSHR_SHIFT_IMM_VEC:
      sprintf(tbuf,"SSHR V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_SSRA_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"SSRA %s%u, %s%u, #%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simd_rshift1(packet->immh.Value(),packet->immb.Value()).c_str());
      break;
   case SIMD_SSRA_SHIFT_IMM_VEC:
      sprintf(tbuf,"SSRA V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_SSUBL:
      if (packet->Q==0) sprintf(tbuf,"SSUBL V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SSUBL2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SSUBW:
      if (packet->Q==0) sprintf(tbuf,"SSUBW V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SSUBW2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_ST1_ONE_REG_MULT_STRUCT:
      sprintf(tbuf,"ST1  V%d.%s , [%s]\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST1_TWO_REG_MULT_STRUCT:
      sprintf(tbuf,"ST1  V%d.%s, V%d.%s , [%s]\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST1_THREE_REG_MULT_STRUCT:
      sprintf(tbuf,"ST1  V%d.%s, V%d.%s, V%d.%s , [%s]\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST1_FOUR_REG_MULT_STRUCT:
      sprintf(tbuf,"ST1  V%d.%s, V%d.%s, V%d.%s, V%d.%s , [%s]\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 3) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST1_ONE_REG_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"ST1  V%d.%s , [%s], %s\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST1_IMM_ONE_REG_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"ST1  V%d.%s , [%s], %u\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(packet->Q.Value()==1 ? 48 : 24));
      break;
   case SIMD_ST1_TWO_REG_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"ST1  V%d.%s, V%d.%s , [%s], %s\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST1_IMM_TWO_REG_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"ST1  V%d.%s, V%d.%s , [%s], %u\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(packet->Q.Value()==1 ? 64 : 32));
      break;
   case SIMD_ST1_THREE_REG_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"ST1  V%d.%s, V%d.%s, V%d.%s , [%s], %s\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST1_IMM_THREE_REG_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"ST1  V%d.%s, V%d.%s, V%d.%s , [%s], %u\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(packet->Q.Value()==1 ? 16 : 8));
      break;
   case SIMD_ST1_FOUR_REG_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"ST1  V%d.%s, V%d.%s, V%d.%s, V%d.%s , [%s], %s\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 3) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST1_IMM_FOUR_REG_OFF_MULT_POST_STRUCT:
      sprintf(tbuf,"ST1  V%d.%s, V%d.%s, V%d.%s, V%d.%s , [%s], %u\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 3) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(packet->Q.Value()==1 ? 32 : 16));
      break;
   case SIMD_ST1_SINGLE_STRUCT_8:
      sprintf(tbuf,"ST1  V%d.B [%u], [%s]\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_8:
      sprintf(tbuf,"ST1  V%d.B [%u], [%s], #1\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_8:
      sprintf(tbuf,"ST1  V%d.B [%u], [%s], %s\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST1_SINGLE_STRUCT_64:
      sprintf(tbuf,"ST1  V%d.D [%u], [%s]\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_64:
      sprintf(tbuf,"ST1  V%d.D [%u], [%s], #8\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_64:
      sprintf(tbuf,"ST1  V%d.D [%u], [%s], %s\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST1_SINGLE_STRUCT_16:
      sprintf(tbuf,"ST1  V%d.H [%u], [%s]\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_16:
      sprintf(tbuf,"ST1  V%d.H [%u], [%s], #2\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_16:
      sprintf(tbuf,"ST1  V%d.H [%u], [%s], %s\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST1_SINGLE_STRUCT_32:
      sprintf(tbuf,"ST1  V%d.S [%u], [%s]\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_32:
      sprintf(tbuf,"ST1  V%d.S [%u], [%s], #4\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_32:
      sprintf(tbuf,"ST1  V%d.S [%u], [%s], %s\n",packet->Rt.Value(),simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST2_OFF_MULT_STRUCT:
      sprintf(tbuf,"ST2  V%d.%s, V%d.%s , [%s]\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST2_REG_OFF_MULT_POST_STRUCT:
      if (packet->Rm.Value() != 0x1f) sprintf(tbuf,"ST2  V%d.%s, V%d.%s , [%s], %s\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      if (packet->Rm.Value() == 0x1f) sprintf(tbuf,"ST2  V%d.%s, V%d.%s , [%s], %u\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(packet->Q.Value()==1 ? 32 : 16));
      break;
   case SIMD_ST2_SINGLE_STRUCT_8:
      sprintf(tbuf,"ST2  V%d.B, V%d.B [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_8:
      sprintf(tbuf,"ST2  V%d.B, V%d.B [%u], [%s], #2\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_8:
      sprintf(tbuf,"ST2  V%d.B, V%d.B [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST2_SINGLE_STRUCT_64:
      sprintf(tbuf,"ST2  V%d.D, V%d.D [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_64:
      sprintf(tbuf,"ST2  V%d.D, V%d.D [%u], [%s], #16\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_64:
      sprintf(tbuf,"ST2  V%d.D, V%d.D [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST2_SINGLE_STRUCT_16:
      sprintf(tbuf,"ST2  V%d.H, V%d.H [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_16:
      sprintf(tbuf,"ST2  V%d.H, V%d.H [%u], [%s], #4\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_16:
      sprintf(tbuf,"ST2  V%d.H, V%d.H [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST2_SINGLE_STRUCT_32:
      sprintf(tbuf,"ST2  V%d.S, V%d.S [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_32:
      sprintf(tbuf,"ST2  V%d.S, V%d.S [%u], [%s], #8\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_32:
      sprintf(tbuf,"ST2  V%d.S, V%d.S [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST3_OFF_MULT_STRUCT:
      sprintf(tbuf,"ST3  V%d.%s, V%d.%s, V%d.%s , [%s]\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST3_REG_OFF_MULT_POST_STRUCT:
      if (packet->Rm.Value() != 0x1f) sprintf(tbuf,"ST3  V%d.%s, V%d.%s, V%d.%s , [%s], %s\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      if (packet->Rm.Value() == 0x1f) sprintf(tbuf,"ST3  V%d.%s, V%d.%s, V%d.%s , [%s], %u\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(packet->Q.Value()==1 ? 48 : 24));
      break;
   case SIMD_ST3_SINGLE_STRUCT_8:
      sprintf(tbuf,"ST3  V%d.B, V%d.B, V%d.B [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_8:
      sprintf(tbuf,"ST3  V%d.B, V%d.B, V%d.B [%u], [%s], #3\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_8:
      sprintf(tbuf,"ST3  V%d.B, V%d.B, V%d.B [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST3_SINGLE_STRUCT_64:
      sprintf(tbuf,"ST3  V%d.D, V%d.D, V%d.D [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_64:
      sprintf(tbuf,"ST3  V%d.D, V%d.D, V%d.D [%u], [%s], #24\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_64:
      sprintf(tbuf,"ST3  V%d.D, V%d.D, V%d.D [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST3_SINGLE_STRUCT_16:
      sprintf(tbuf,"ST3  V%d.H, V%d.H, V%d.H [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_16:
      sprintf(tbuf,"ST3  V%d.H, V%d.H, V%d.H [%u], [%s], #6\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_16:
      sprintf(tbuf,"ST3  V%d.H, V%d.H, V%d.H [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST3_SINGLE_STRUCT_32:
      sprintf(tbuf,"ST3  V%d.S, V%d.S, V%d.S [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_32:
      sprintf(tbuf,"ST3  V%d.S, V%d.S, V%d.S [%u], [%s], #12\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_32:
      sprintf(tbuf,"ST3  V%d.S, V%d.S, V%d.S [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST4_OFF_MULT_STRUCT:
      sprintf(tbuf,"ST4  V%d.%s, V%d.%s, V%d.%s, V%d.%s , [%s]\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 3) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST4_REG_OFF_MULT_POST_STRUCT:
      if (packet->Rm.Value() != 0x1f) sprintf(tbuf,"ST4  V%d.%s, V%d.%s, V%d.%s, V%d.%s , [%s], %s\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 3) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      if (packet->Rm.Value() == 0x1f) sprintf(tbuf,"ST4  V%d.%s, V%d.%s, V%d.%s, V%d.%s , [%s], %u\n",packet->Rt.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 1) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 2) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->Rt.Value() + 3) % 32,Tparm(packet->size.Value(),packet->Q.Value()).c_str(),XnSP(packet->Rn.Value(),false).c_str(),(packet->Q.Value()==1 ? 64 : 32));
      break;
   case SIMD_ST4_SINGLE_STRUCT_8:
      sprintf(tbuf,"ST4  V%d.B, V%d.B, V%d.B, V%d.B [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_8:
      sprintf(tbuf,"ST4  V%d.B, V%d.B, V%d.B, V%d.B [%u], [%s], #4\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_8:
      sprintf(tbuf,"ST4  V%d.B, V%d.B, V%d.B, V%d.B [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),packet->size.Value(),8),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST4_SINGLE_STRUCT_64:
      sprintf(tbuf,"ST4  V%d.D, V%d.D, V%d.D, V%d.D [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_64:
      sprintf(tbuf,"ST4  V%d.D, V%d.D, V%d.D, V%d.D [%u], [%s], #32\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_64:
      sprintf(tbuf,"ST4  V%d.D, V%d.D, V%d.D, V%d.D [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),0,0,64),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST4_SINGLE_STRUCT_16:
      sprintf(tbuf,"ST4  V%d.H, V%d.H, V%d.H, V%d.H [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_16:
      sprintf(tbuf,"ST4  V%d.H, V%d.H, V%d.H, V%d.H [%u], [%s], #8\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_16:
      sprintf(tbuf,"ST4  V%d.H, V%d.H, V%d.H, V%d.H [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),(packet->size.Value()>>1)&1,16),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_ST4_SINGLE_STRUCT_32:
      sprintf(tbuf,"ST4  V%d.S, V%d.S, V%d.S, V%d.S [%u], [%s]\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_32:
      sprintf(tbuf,"ST4  V%d.S, V%d.S, V%d.S, V%d.S [%u], [%s], #16\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_32:
      sprintf(tbuf,"ST4  V%d.S, V%d.S, V%d.S, V%d.S [%u], [%s], %s\n",packet->Rt.Value(),(packet->Rt.Value() + 1) % 32,(packet->Rt.Value() + 2) % 32,(packet->Rt.Value() + 3) % 32,simd_ld1_imm(packet->Q.Value(),packet->S.Value(),0,32),XnSP(packet->Rn.Value(),false).c_str(),XnXZR(packet->Rm.Value(),false).c_str());
      break;
   case SIMD_STNP_OFF_64:
      sprintf(tbuf,"STNP D%d, D%d, [%s, #%lld]\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 8);
      break;
   case SIMD_STNP_OFF_8_128:
      sprintf(tbuf,"STNP Q%d, Q%d, [%s, #%lld]\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 16);
      break;
   case SIMD_STNP_OFF_32:
      sprintf(tbuf,"STNP S%d, S%d, [%s, #%lld]\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case SIMD_STP_REG_POST_64:
      sprintf(tbuf,"STP D%d, D%d, [%s], #%lld\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 8);
      break;
   case SIMD_STP_REG_POST_8_128:
      sprintf(tbuf,"STP Q%d, Q%d, [%s], #%lld\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 16);
      break;
   case SIMD_STP_REG_POST_32:
      sprintf(tbuf,"STP S%d, S%d, [%s], #%lld\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case SIMD_STP_REG_PRE_64:
      sprintf(tbuf,"STP D%d, D%d, [%s, #%lld]!\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 8);
      break;
   case SIMD_STP_REG_PRE_8_128:
      sprintf(tbuf,"STP Q%d, Q%d, [%s, #%lld]!\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 16);
      break;
   case SIMD_STP_REG_PRE_32:
      sprintf(tbuf,"STP S%d, S%d, [%s, #%lld]!\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case SIMD_STP_REG_OFF_64:
      sprintf(tbuf,"STP D%d, D%d, [%s, #%lld]\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 8);
      break;
   case SIMD_STP_REG_OFF_8_128:
      sprintf(tbuf,"STP Q%d, Q%d, [%s, #%lld]\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 16);
      break;
   case SIMD_STP_REG_OFF_32:
      sprintf(tbuf,"STP S%d, S%d, [%s, #%lld]\n",packet->Rt.Value(),packet->Rt2.Value(),XnSP(packet->Rn.Value(),false).c_str(),SignExtend(packet->imm7.Value(),7) * 4);
      break;
   case SIMD_STR_IMM_REG_PRE_8:
      sprintf(tbuf,"STR B%d, [%s, #%d]!\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_STR_IMM_REG_POST_8:
      sprintf(tbuf,"STR B%d, [%s], #%d\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_STR_IMM_REG_8:
      sprintf(tbuf,"STR B%d, [%s, #%u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case SIMD_STR_IMM_REG_PRE_64:
      sprintf(tbuf,"STR D%d, [%s, #%d]!\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_STR_IMM_REG_POST_64:
      sprintf(tbuf,"STR D%d, [%s], #%d\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_STR_IMM_REG_64:
      sprintf(tbuf,"STR D%d, [%s, #%u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case SIMD_STR_IMM_REG_PRE_16:
      sprintf(tbuf,"STR H%d, [%s, #%d]!\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_STR_IMM_REG_POST_16:
      sprintf(tbuf,"STR H%d, [%s], #%d\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_STR_IMM_REG_16:
      sprintf(tbuf,"STR H%d, [%s, #%u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case SIMD_STR_IMM_REG_PRE_8_128:
      sprintf(tbuf,"STR Q%d, [%s, #%d]!\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_STR_IMM_REG_POST_8_128:
      sprintf(tbuf,"STR Q%d, [%s], #%d\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_STR_IMM_REG_8_128:
      sprintf(tbuf,"STR Q%d, [%s, #%u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case SIMD_STR_IMM_REG_PRE_32:
      sprintf(tbuf,"STR S%d, [%s, #%d]!\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_STR_IMM_REG_POST_32:
      sprintf(tbuf,"STR S%d, [%s], #%d\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_STR_IMM_REG_32:
      sprintf(tbuf,"STR S%d, [%s, #%u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),decode_pimm(packet->imm12.Value(),packet->size.Value(),packet->opc.Value()));
      break;
   case SIMD_STR_REG_OFF_8:
      sprintf(tbuf,"STR B%d, [%s, %c%s, %s %u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case SIMD_STR_REG_OFF_64:
      sprintf(tbuf,"STR D%d, [%s, %c%s, %s %u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case SIMD_STR_REG_OFF_16:
      sprintf(tbuf,"STR H%d, [%s, %c%s, %s %u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case SIMD_STR_REG_OFF_8_128:
      sprintf(tbuf,"STR Q%d, [%s, %c%s, %s %u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case SIMD_STR_REG_OFF_32:
      sprintf(tbuf,"STR S%d, [%s, %c%s, %s %u]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),((packet->option.Value() & 3)==3) ? 'X' : 'W',ZR(packet->Rm.Value()).c_str(),extendOption(packet->option.Value(),packet->Rd.Value(),packet->Rn.Value(),packet->imm3.IsDefined()).c_str(),packet->imm3.Value());
      break;
   case SIMD_STUR_IMM_REG_8:
      sprintf(tbuf,"STUR B%d, [%s, #%d]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_STUR_IMM_REG_64:
      sprintf(tbuf,"STUR D%d, [%s, #%d]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_STUR_IMM_REG_16:
      sprintf(tbuf,"STUR H%d, [%s, #%d]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_STUR_IMM_REG_8_128:
      sprintf(tbuf,"STUR Q%d, [%s, #%d]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_STUR_IMM_REG_32:
      sprintf(tbuf,"STUR S%d, [%s, #%d]\n",packet->Rt.Value(),XnSP(packet->Rn.Value(),false).c_str(),(int) SignExtend(packet->imm9.Value(),9));
      break;
   case SIMD_SUB_SCALAR_VEC:
      sprintf(tbuf,"SUB %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_SUB_VEC_VEC:
      sprintf(tbuf,"SUB V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_SUBHN:
      if (packet->Q==0) sprintf(tbuf,"SUBHN V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rm.Value(),simdArrangementA(packet->size.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"SUBHN2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rm.Value(),simdArrangementA(packet->size.Value()).c_str());
      break;
   case SIMD_SUQADD_REG_SCALAR:
      sprintf(tbuf,"SUQADD %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_SUQADD_REG_VEC:
      sprintf(tbuf,"SUQADD V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_TBL_FOUR_REG:
      sprintf(tbuf,"TBL V%d.%s,  V%d.16B, V%d.16B, V%d.16B, V%d.16B , V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),(packet->Rn.Value() + 1) % 32,(packet->Rn.Value() + 2) % 32,(packet->Rn.Value() + 3) % 32,packet->Rm.Value(),simdArrangementA(packet->size.Value()).c_str());
      break;
   case SIMD_TBL_SINGLE_REG:
      sprintf(tbuf,"TBL V%d.%s,  V%d.16B , V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),packet->Rm.Value(),simdArrangementA(packet->size.Value()).c_str());
      break;
   case SIMD_TBL_THREE_REG:
      sprintf(tbuf,"TBL V%d.%s,  V%d.16B, V%d.16B, V%d.16B , V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),(packet->Rn.Value() + 1) % 32,(packet->Rn.Value() + 2) % 32,packet->Rm.Value(),simdArrangementA(packet->size.Value()).c_str());
      break;
   case SIMD_TBL_TWO_REG:
      sprintf(tbuf,"TBL V%d.%s,  V%d.16B, V%d.16B , V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),(packet->Rn.Value() + 1) % 32,packet->Rm.Value(),simdArrangementA(packet->size.Value()).c_str());
      break;
   case SIMD_TBX_FOUR_REG:
      sprintf(tbuf,"TBX V%d.%s,  V%d.16B, V%d.16B, V%d.16B, V%d.16B , V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),(packet->Rn.Value() + 1) % 32,(packet->Rn.Value() + 2) % 32,(packet->Rn.Value() + 3) % 32,packet->Rm.Value(),simdArrangementA(packet->size.Value()).c_str());
      break;
   case SIMD_TBX_SINGLE_REG:
      sprintf(tbuf,"TBX V%d.%s,  V%d.16B , V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),packet->Rm.Value(),simdArrangementA(packet->size.Value()).c_str());
      break;
   case SIMD_TBX_THREE_REG:
      sprintf(tbuf,"TBX V%d.%s,  V%d.16B, V%d.16B, V%d.16B , V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),(packet->Rn.Value() + 1) % 32,(packet->Rn.Value() + 2) % 32,packet->Rm.Value(),simdArrangementA(packet->size.Value()).c_str());
      break;
   case SIMD_TBX_TWO_REG:
      sprintf(tbuf,"TBX V%d.%s,  V%d.16B, V%d.16B , V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),(packet->Rn.Value() + 1) % 32,packet->Rm.Value(),simdArrangementA(packet->size.Value()).c_str());
      break;
   case SIMD_TRN1:
      sprintf(tbuf,"TRN1 V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_TRN2:
      sprintf(tbuf,"TRN2 V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UABA:
      sprintf(tbuf,"UABA V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UABAL:
      if (packet->Q==0) sprintf(tbuf,"UABAL V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"UABAL2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UABD:
      sprintf(tbuf,"UABD V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UABDL:
      if (packet->Q==0) sprintf(tbuf,"UABDL V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"UABDL2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UADALP_REG:
      sprintf(tbuf,"UADALP V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UADDL:
      if (packet->Q==0) sprintf(tbuf,"UADDL V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"UADDL2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UADDLP_REG:
      sprintf(tbuf,"UADDLP V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UADDLV:
      sprintf(tbuf,"UADDLV %s%u, V%d.%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UADDW:
      if (packet->Q==0) sprintf(tbuf,"UADDW V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"UADDW2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UCVTF_SHIFT_IMM_SCALAR_VEC_FIXED:
      sprintf(tbuf,"UCVTF %s%u, %s%u, #%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case SIMD_UCVTF_SHIFT_IMM_VEC_VEC_FIXED:
      sprintf(tbuf,"UCVTF V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case SIMD_UCVTF_REG_SCALAR_VEC:
      sprintf(tbuf,"UCVTF %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_UCVTF_REG_VEC_VEC:
      sprintf(tbuf,"UCVTF V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case UCVTF_SINGLE_TO_SP_FP_FIXED_32:
      sprintf(tbuf,"UCVTF S%d, %s, #%u\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),true).c_str(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case UCVTF_TO_DP_FP_FIXED_32:
      sprintf(tbuf,"UCVTF D%d, %s, #%u\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),true).c_str(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case UCVTF_SINGLE_TO_SP_FP_FIXED_64:
      sprintf(tbuf,"UCVTF S%d, %s, #%u\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),false).c_str(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case UCVTF_TO_DP_FP_FIXED_64:
      sprintf(tbuf,"UCVTF D%d, %s, #%u\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),false).c_str(),decodeFbits(packet->immh.Value(),packet->immb.Value(),packet->scale.Value(),packet->scale.IsDefined()));
      break;
   case UCVTF_SINGLE_TO_SP_FP_32:
      sprintf(tbuf,"UCVTF S%d, %s\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),true).c_str());
      break;
   case UCVTF_TO_DP_FP_32:
      sprintf(tbuf,"UCVTF D%d, %s\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),true).c_str());
      break;
   case UCVTF_SINGLE_TO_SP_FP_64:
      sprintf(tbuf,"UCVTF S%d, %s\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),false).c_str());
      break;
   case UCVTF_TO_DP_FP_64:
      sprintf(tbuf,"UCVTF D%d, %s\n",packet->Rd.Value(),XnXZR(packet->Rn.Value(),false).c_str());
      break;
   case SIMD_UHADD:
      sprintf(tbuf,"UHADD V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UHSUB:
      sprintf(tbuf,"UHSUB V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UMAX:
      sprintf(tbuf,"UMAX V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UMAXP:
      sprintf(tbuf,"UMAXP V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UMAXV:
      sprintf(tbuf,"UMAXV %s%u, V%d.%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UMIN:
      sprintf(tbuf,"UMIN V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UMINP:
      sprintf(tbuf,"UMINP V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UMINV:
      sprintf(tbuf,"UMINV %s%u, V%d.%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UMLAL_VEC_ELEM:
      if (packet->Q==0) sprintf(tbuf,"UMLAL V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"UMLAL2 V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_UMLAL_VEC:
      if (packet->Q==0) sprintf(tbuf,"UMLAL V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"UMLAL2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UMLSL_VEC_ELEM:
      if (packet->Q==0) sprintf(tbuf,"UMLSL V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"UMLSL2 V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_UMLSL_VEC:
      if (packet->Q==0) sprintf(tbuf,"UMLSL V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"UMLSL2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UMOV_32:
      sprintf(tbuf,"UMOV %s, V%d.%s[%s]\n",XnXZR(packet->Rd.Value(),true).c_str(),packet->Rn.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex(packet->imm5.Value()).c_str());
      break;
   case SIMD_UMOV_64:
      sprintf(tbuf,"UMOV %s, V%d.%s[%u]\n",XnXZR(packet->Rd.Value(),false).c_str(),packet->Rn.Value(),Tscale(packet->imm5.Value()).c_str(),packet->imm5.Value()>>4);
      break;
   case SIMD_UMULL_VEC_ELEM:
      if (packet->Q==0) sprintf(tbuf,"UMULL V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"UMULL2 V%d.%s, V%d.%s, V%d.%s[%s]\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tscale(packet->imm5.Value()).c_str(),simdElementIndex3(packet->size.Value(),packet->H.Value(),packet->L.Value(),packet->M.Value()).c_str());
      break;
   case SIMD_UMULL_VEC:
      if (packet->Q==0) sprintf(tbuf,"UMULL V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"UMULL2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UQADD_SCALAR:
      sprintf(tbuf,"UQADD %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_UQADD_VEC:
      sprintf(tbuf,"UQADD V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UQRSHL_SCALAR:
      sprintf(tbuf,"UQRSHL %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_UQRSHL_VEC:
      sprintf(tbuf,"UQRSHL V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UQRSHRN_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"UQRSHRN %s%u, %s%u, #%u\n",(packet->size.Value()==1) ? "S" : "?",packet->Rd.Value(),(packet->size.Value()==1) ? "D" : "?",packet->Rn.Value(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_UQRSHRN_SHIFT_IMM_VEC:
      if (packet->Q==0) sprintf(tbuf,"UQRSHRN V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      if (packet->Q==1) sprintf(tbuf,"UQRSHRN2 V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_UQSHL_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"UQSHL %s%u, %s%u, #%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),(packet->immh.Value()<<3|packet->immb.Value()) - (8<<HighestSetBit(packet->immh.Value(),4)));
      break;
   case SIMD_UQSHL_SHIFT_IMM_VEC:
      sprintf(tbuf,"UQSHL V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(packet->immh.Value()<<3|packet->immb.Value()) - (8<<HighestSetBit(packet->immh.Value(),4)));
      break;
   case SIMD_UQSHL_REG_SCALAR:
      sprintf(tbuf,"UQSHL %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_UQSHL_REG_VEC:
      sprintf(tbuf,"UQSHL V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UQSHRN_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"UQSHRN %s%u, %s%u, #%u\n",(packet->size.Value()==1) ? "S" : "?",packet->Rd.Value(),(packet->size.Value()==1) ? "D" : "?",packet->Rn.Value(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_UQSHRN_SHIFT_IMM_VEC:
      sprintf(tbuf,"UQSHRN2 V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_UQSUB_SCALAR:
      sprintf(tbuf,"UQSUB %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_UQSUB_VEC:
      sprintf(tbuf,"UQSUB V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UQXTN_REG_SCALAR:
      sprintf(tbuf,"UQXTN %s%u, %s%u\n",(packet->size.Value()==1) ? "S" : "?",packet->Rd.Value(),(packet->size.Value()==1) ? "D" : "?",packet->Rn.Value());
      break;
   case SIMD_UQXTN_REG_VEC:
      if (packet->Q==0) sprintf(tbuf,"UQXTN V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"UQXTN2 V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str());
      break;
   case SIMD_URECPE_REG:
      sprintf(tbuf,"URECPE V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_URHADD:
      sprintf(tbuf,"URHADD V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_URSHL_SCALAR:
      sprintf(tbuf,"URSHL %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_URSHL_VEC:
      sprintf(tbuf,"URSHL V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_URSHR_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"URSHR %s%u, %s%u, #%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_URSHR_SHIFT_IMM_VEC:
      sprintf(tbuf,"URSHR V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_URSQRTE_REG:
      sprintf(tbuf,"URSQRTE V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_URSRA_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"URSRA %s%u, %s%u, #%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_URSRA_SHIFT_IMM_VEC:
      sprintf(tbuf,"URSRA V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_USHL_SCALAR:
      sprintf(tbuf,"USHL %s%u, %s%u, %s%s\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),simdScalarWidth(packet->size.Value()).c_str(),ZR(packet->Rm.Value()).c_str());
      break;
   case SIMD_USHL_VEC:
      sprintf(tbuf,"USHL V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_USHLL_SHIFT_IMM:
      if (packet->Q==0) sprintf(tbuf,"USHLL V%d.%s, V%d.%s, #%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),simd_rshift2(packet->immh.Value(),packet->immb.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"USHLL2 V%d.%s, V%d.%s, #%s\n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),simd_rshift2(packet->immh.Value(),packet->immb.Value()).c_str());
      break;
   case SIMD_USHR_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"USHR %s%u, %s%u, #%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_USHR_SHIFT_IMM_VEC:
      sprintf(tbuf,"USHR V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_USQADD_REG_SCALAR:
      sprintf(tbuf,"USQADD %s%u, %s%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value());
      break;
   case SIMD_USQADD_REG_VEC:
      sprintf(tbuf,"USQADD V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_USRA_SHIFT_IMM_SCALAR:
      sprintf(tbuf,"USRA %s%u, %s%u, #%u\n",simdScalarWidth(packet->size.Value()).c_str(),packet->Rd.Value(),simdScalarWidth(packet->size.Value()).c_str(),packet->Rn.Value(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_USRA_SHIFT_IMM_VEC:
      sprintf(tbuf,"USRA V%d.%s, V%d.%s, #%u\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),(2 * (8<<HighestSetBit(packet->immh.Value(),4))) - (packet->immh.Value()<<3|packet->immb.Value()));
      break;
   case SIMD_USUBL:
      if (packet->Q==0) sprintf(tbuf,"USUBL V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"USUBL2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_USUBW:
      if (packet->Q==0) sprintf(tbuf,"USUBW V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"USUBW2 V%d.%s, V%d.%s, V%d.%s \n",packet->Rd.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str(),packet->Rm.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UZP1:
      sprintf(tbuf,"UZP1 V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_UZP2:
      sprintf(tbuf,"UZP2 V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_XTN_REG:
      if (packet->Q==0) sprintf(tbuf,"XTN V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str());
      if (packet->Q==1) sprintf(tbuf,"XTN2 V%d.%s, V%d.%s\n",packet->Rd.Value(),simdArrangementB(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),simdArrangementA(packet->size.Value()).c_str());
      break;
   case SIMD_ZIP1:
      sprintf(tbuf,"ZIP1 V%d.%s, V%d.%s, V%d.%s\n",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
   case SIMD_ZIP2:
      sprintf(tbuf,"ZIP1 V%d.%s, V%d.%s, V%d.%s",packet->Rd.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rn.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str(),packet->Rm.Value(),Tparm(packet->size.Value(),packet->Q.Value()).c_str());
      break;
