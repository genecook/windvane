   case ADC_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ADC_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ADCS_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ADCS_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ADD_REG_32:
      packet->mOpsWriteback.push_back(XDSP);
      break;
   case ADD_REG_64:
      packet->mOpsWriteback.push_back(XDSP);
      break;
   case ADD_IMM_32:
      packet->mOpsWriteback.push_back(XDSP);
      break;
   case ADD_IMM_64:
      packet->mOpsWriteback.push_back(XDSP);
      break;
   case ADD_SHIFT_REG_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ADD_SHIFT_REG_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ADDS_REG_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ADDS_REG_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ADDS_IMM_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ADDS_IMM_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ADDS_SHIFT_REG_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ADDS_SHIFT_REG_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ADR:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ADRP:
      packet->mOpsWriteback.push_back(XD);
      break;
   case AND_IMM_32:
      packet->mOpsWriteback.push_back(XDSP);
      break;
   case AND_IMM_64:
      packet->mOpsWriteback.push_back(XDSP);
      break;
   case AND_SHIFT_REG_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case AND_SHIFT_REG_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ANDS_IMM_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ANDS_IMM_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ANDS_SHIFT_REG_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ANDS_SHIFT_REG_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ASRV_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ASRV_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case B_COND_IMM:
      break;
   case B_IMM:
      break;
   case BFM_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case BFM_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case BIC_SHIFT_REG_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case BIC_SHIFT_REG_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case BICS_SHIFT_REG_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case BICS_SHIFT_REG_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case BL:
      break;
   case BLR:
      break;
   case BR:
      break;
   case BRK:
      break;
   case CBNZ_IMM_32:
      break;
   case CBNZ_IMM_64:
      break;
   case CBZ_IMM_32:
      break;
   case CBZ_IMM_64:
      break;
   case CCMN_IMM_32:
      break;
   case CCMN_IMM_64:
      break;
   case CCMN_REG_32:
      break;
   case CCMN_REG_64:
      break;
   case CCMP_IMM_32:
      break;
   case CCMP_IMM_64:
      break;
   case CCMP_REG_32:
      break;
   case CCMP_REG_64:
      break;
   case CLREX:
      break;
   case CLS_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case CLS_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case CLZ_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case CLZ_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case CRC32B:
      break;
   case CRC32H:
      break;
   case CRC32W:
      break;
   case CRC32X:
      break;
   case CRC32CB:
      break;
   case CRC32CH:
      break;
   case CRC32CW:
      break;
   case CRC32CX:
      break;
   case CSEL_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case CSEL_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case CSINC_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case CSINC_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case CSINV_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case CSINV_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case CSNEG_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case CSNEG_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case DCPS1:
      break;
   case DCPS2:
      break;
   case DCPS3:
      break;
   case DMB:
      break;
   case DRPS:
      break;
   case DSB:
      break;
   case EON_SHIFT_REG_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case EON_SHIFT_REG_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case EOR_IMM_32:
      packet->mOpsWriteback.push_back(XDSP);
      break;
   case EOR_IMM_64:
      packet->mOpsWriteback.push_back(XDSP);
      break;
   case EOR_SHIFT_REG_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case EOR_SHIFT_REG_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ERET:
      break;
   case EXTR_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case EXTR_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case HINT:
      break;
   case HLT:
      break;
   case HVC:
      break;
   case ISB:
      break;
   case LDAR_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDAR_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDARB:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDARH:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDAXP_32:
      packet->mOpsWriteback.push_back(XT);
      packet->mOpsWriteback.push_back(XT2);
      break;
   case LDAXP_64:
      packet->mOpsWriteback.push_back(XT);
      packet->mOpsWriteback.push_back(XT2);
      break;
   case LDAXR_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDAXR_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDAXRB:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDAXRH:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDNP_OFF_32:
      packet->mOpsWriteback.push_back(XT);
      packet->mOpsWriteback.push_back(XT2);
      break;
   case LDNP_OFF_64:
      packet->mOpsWriteback.push_back(XT);
      packet->mOpsWriteback.push_back(XT2);
      break;
   case LDP_REG_POST_32:
      packet->mOpsWriteback.push_back(XT);
      packet->mOpsWriteback.push_back(XT2);
      break;
   case LDP_REG_POST_64:
      packet->mOpsWriteback.push_back(XT);
      packet->mOpsWriteback.push_back(XT2);
      break;
   case LDP_REG_PRE_32:
      packet->mOpsWriteback.push_back(XT);
      packet->mOpsWriteback.push_back(XT2);
      break;
   case LDP_REG_PRE_64:
      packet->mOpsWriteback.push_back(XT);
      packet->mOpsWriteback.push_back(XT2);
      break;
   case LDP_REG_OFF_32:
      packet->mOpsWriteback.push_back(XT);
      packet->mOpsWriteback.push_back(XT2);
      break;
   case LDP_REG_OFF_64:
      packet->mOpsWriteback.push_back(XT);
      packet->mOpsWriteback.push_back(XT2);
      break;
   case LDPSW_REG_POST:
      packet->mOpsWriteback.push_back(XT);
      packet->mOpsWriteback.push_back(XT2);
      break;
   case LDPSW_REG_PRE:
      packet->mOpsWriteback.push_back(XT);
      packet->mOpsWriteback.push_back(XT2);
      break;
   case LDPSW_REG_OFF:
      packet->mOpsWriteback.push_back(XT);
      packet->mOpsWriteback.push_back(XT2);
      break;
   case LDR_IMM_REG_POST_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDR_IMM_REG_POST_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDR_IMM_REG_PRE_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDR_IMM_REG_PRE_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDR_IMM_REG_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDR_IMM_REG_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDR_REG_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDR_REG_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDR_REG_OFF_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDR_REG_OFF_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRB_IMM_REG_POST:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRB_IMM_REG_PRE:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRB_IMM_REG_OFF:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRB_REG_OFF:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRH_IMM_REG_POST:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRH_IMM_REG_PRE:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRH_IMM_REG_OFF:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRH_REG_OFF:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSB_IMM_REG_POST_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSB_IMM_REG_POST_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSB_IMM_REG_PRE_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSB_IMM_REG_PRE_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSB_IMM_REG_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSB_IMM_REG_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSB_REG_OFF_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSB_REG_OFF_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSH_IMM_REG_POST_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSH_IMM_REG_POST_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSH_IMM_REG_PRE_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSH_IMM_REG_PRE_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSH_IMM_REG_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSH_IMM_REG_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSH_REG_OFF_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSH_REG_OFF_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSW_IMM_REG_POST:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSW_IMM_REG_PRE:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSW_IMM_REG_OFF:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSW_REG:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDRSW_REG_OFF:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDTR_REG_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDTR_REG_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDTRB_REG:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDTRH_REG:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDTRSB_REG_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDTRSB_REG_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDTRSH_REG_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDTRSH_REG_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDTRSW_REG:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDUR_IMM_REG_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDUR_IMM_REG_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDURB_IMM_REG:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDURH_IMM_REG:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDURSB_IMM_REG_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDURSB_IMM_REG_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDURSH_IMM_REG_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDURSH_IMM_REG_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDURSW_IMM_REG:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDXP_32:
      packet->mOpsWriteback.push_back(XT);
      packet->mOpsWriteback.push_back(XT2);
      break;
   case LDXP_64:
      packet->mOpsWriteback.push_back(XT);
      packet->mOpsWriteback.push_back(XT2);
      break;
   case LDXR_32:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDXR_64:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDXRB:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LDXRH:
      packet->mOpsWriteback.push_back(XT);
      break;
   case LSLV_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case LSLV_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case LSRV_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case LSRV_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case MADD_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case MADD_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case MOVK_IMM_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case MOVK_IMM_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case MOVN_IMM_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case MOVN_IMM_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case MOVZ_IMM_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case MOVZ_IMM_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case MRS:
      packet->mOpsWriteback.push_back(XT);
      break;
   case MSR_IMM:
      break;
   case MSR_REG:
      break;
   case MSUB_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case MSUB_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case NOP:
      break;
   case ORN_SHIFT_REG_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ORN_SHIFT_REG_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ORR_IMM_32:
      packet->mOpsWriteback.push_back(XDSP);
      break;
   case ORR_IMM_64:
      packet->mOpsWriteback.push_back(XDSP);
      break;
   case ORR_SHIFT_REG_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case ORR_SHIFT_REG_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case PRFM_REG_OFF:
      break;
   case PRFM_REG:
      break;
   case PRFM_IMM_REG:
      break;
   case PRFUM_IMM_REG:
      break;
   case RBIT_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case RBIT_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case RET:
      break;
   case REV_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case REV_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case REV16_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case REV16_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case REV32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case RORV_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case RORV_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SBC_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SBC_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SBCS_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SBCS_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SBFM_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SBFM_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SDIV_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SDIV_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SEV:
      break;
   case SEVL:
      break;
   case SMADDL:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SMC:
      break;
   case SMSUBL:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SMULH:
      packet->mOpsWriteback.push_back(XD);
      break;
   case STLR_32:
      break;
   case STLR_64:
      break;
   case STLRB:
      break;
   case STLRH:
      break;
   case STLXP_32:
      break;
   case STLXP_64:
      break;
   case STLXR_32:
      break;
   case STLXR_64:
      break;
   case STLXRB:
      break;
   case STLXRH:
      break;
   case STNP_OFF_32:
      break;
   case STNP_OFF_64:
      break;
   case STP_REG_POST_32:
      break;
   case STP_REG_POST_64:
      break;
   case STP_REG_PRE_32:
      break;
   case STP_REG_PRE_64:
      break;
   case STP_REG_OFF_32:
      break;
   case STP_REG_OFF_64:
      break;
   case STR_IMM_REG_POST_32:
      break;
   case STR_IMM_REG_POST_64:
      break;
   case STR_IMM_REG_PRE_32:
      break;
   case STR_IMM_REG_PRE_64:
      break;
   case STR_IMM_REG_32:
      break;
   case STR_IMM_REG_64:
      break;
   case STR_REG_OFF_32:
      break;
   case STR_REG_OFF_64:
      break;
   case STRB_IMM_REG_POST:
      break;
   case STRB_IMM_REG_PRE:
      break;
   case STRB_IMM_REG_OFF:
      break;
   case STRB_REG_OFF:
      break;
   case STRH_IMM_REG_POST:
      break;
   case STRH_IMM_REG_PRE:
      break;
   case STRH_IMM_REG_OFF:
      break;
   case STRH_REG_OFF:
      break;
   case STTR_REG_32:
      break;
   case STTR_REG_64:
      break;
   case STTRB_REG:
      break;
   case STTRH_REG:
      break;
   case STUR_IMM_REG_32:
      break;
   case STUR_IMM_REG_64:
      break;
   case STURB_IMM_REG:
      break;
   case STURH_IMM_REG:
      break;
   case STXP_32:
      break;
   case STXP_64:
      break;
   case STXR_32:
      break;
   case STXR_64:
      break;
   case STXRB:
      break;
   case STXRH:
      break;
   case SUB_REG_32:
      packet->mOpsWriteback.push_back(XDSP);
      break;
   case SUB_REG_64:
      packet->mOpsWriteback.push_back(XDSP);
      break;
   case SUB_IMM_32:
      packet->mOpsWriteback.push_back(XDSP);
      break;
   case SUB_IMM_64:
      packet->mOpsWriteback.push_back(XDSP);
      break;
   case SUB_SHIFT_REG_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SUB_SHIFT_REG_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SUBS_REG_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SUBS_REG_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SUBS_IMM_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SUBS_IMM_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SUBS_SHIFT_REG_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SUBS_SHIFT_REG_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SVC:
      break;
   case SYS:
      break;
   case SYSL:
      packet->mOpsWriteback.push_back(XT);
      break;
   case TBNZ:
      break;
   case TBZ:
      break;
   case UBFM_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case UBFM_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case UDIV_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case UDIV_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case UMADDL:
      packet->mOpsWriteback.push_back(XD);
      break;
   case UMSUBL:
      packet->mOpsWriteback.push_back(XD);
      break;
   case UMULH:
      packet->mOpsWriteback.push_back(XD);
      break;
   case WFE:
      break;
   case WFI:
      break;
   case YIELD:
      break;
   case SIMD_ABS_REG_SCALAR:
      break;
   case SIMD_ABS_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_ADD_SCALAR_VEC:
      break;
   case SIMD_ADD_VEC_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_ADDHN:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_ADDP:
      break;
   case SIMD_ADDP_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_ADDV:
      break;
   case AESD:
      packet->mOpsWriteback.push_back(VD);
      break;
   case AESE:
      packet->mOpsWriteback.push_back(VD);
      break;
   case AESIMC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case AESMC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_AND_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_BIC_IMM_MOD_VEC_32:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_BIC_IMM_MOD_VEC_16:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_BIC_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_BIF:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_BIT:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_BSL:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_CLS_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_CLZ_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_CMEQ_REG_SCALAR:
      break;
   case SIMD_CMEQ_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_CMEQ_REG_SCALAR_ZERO:
      break;
   case SIMD_CMEQ_REG_VEC_ZERO:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_CMGE_REG_SCALAR:
      break;
   case SIMD_CMGE_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_CMGE_REG_SCALAR_ZERO:
      break;
   case SIMD_CMGE_REG_VEC_ZERO:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_CMGT_REG_SCALAR:
      break;
   case SIMD_CMGT_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_CMGT_REG_SCALAR_ZERO:
      break;
   case SIMD_CMGT_REG_VEC_ZERO:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_CMHI_REG_SCALAR:
      break;
   case SIMD_CMHI_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_CMHS_REG_SCALAR:
      break;
   case SIMD_CMHS_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_CMLE_REG_SCALAR_ZERO:
      break;
   case SIMD_CMLE_REG_VEC_ZERO:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_CMLT_REG_SCALAR_ZERO:
      break;
   case SIMD_CMLT_REG_VEC_ZERO:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_CMTST_SCALAR:
      break;
   case SIMD_CMTST_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_CNT_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_DUP_SCALAR_ELEM:
      break;
   case SIMD_DUP_VEC_ELEM:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_DUP:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_EOR_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_EXT:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FABD_SCALAR:
      break;
   case SIMD_FABD_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FABS_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FABS_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FABS_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_FACGE_SCALAR:
      break;
   case SIMD_FACGE_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FACGT_SCALAR:
      break;
   case SIMD_FACGT_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FADD_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FADD_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FADD_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_FADDP:
      break;
   case SIMD_FADDP_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FCCMP_SINGLE_FROM_SP:
      break;
   case FCCMP_FROM_DP:
      break;
   case FCCMPE_SINGLE_FROM_SP:
      break;
   case FCCMPE_FROM_DP:
      break;
   case SIMD_FCMEQ_REG_SCALAR:
      break;
   case SIMD_FCMEQ_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FCMEQ_REG_SCALAR_ZERO:
      break;
   case SIMD_FCMEQ_REG_VEC_ZERO:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FCMGE_REG_SCALAR:
      break;
   case SIMD_FCMGE_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FCMGE_REG_SCALAR_ZERO:
      break;
   case SIMD_FCMGE_REG_VEC_ZERO:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FCMGT_REG_SCALAR:
      break;
   case SIMD_FCMGT_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FCMGT_REG_SCALAR_ZERO:
      break;
   case SIMD_FCMGT_REG_VEC_ZERO:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FCMLE_REG_SCALAR_ZERO:
      break;
   case SIMD_FCMLE_REG_VEC_ZERO:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FCMLT_REG_SCALAR_ZERO:
      break;
   case SIMD_FCMLT_REG_VEC_ZERO:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FCMP_SINGLE_FROM_SP:
      break;
   case FCMP_FROM_DP:
      break;
   case FCMPE_SINGLE_FROM_SP:
      break;
   case FCMPE_FROM_DP:
      break;
   case FCSEL_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FCSEL_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case FCVT_SINGLE_FROM_HP_TO_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FCVT_FROM_HP_TO_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case FCVT_SINGLE_FROM_SP_TO_HP:
      packet->mOpsWriteback.push_back(HD);
      break;
   case FCVT_SINGLE_FROM_SP_TO_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case FCVT_FROM_DP_TO_HP:
      packet->mOpsWriteback.push_back(HD);
      break;
   case FCVT_SINGLE_FROM_DP_TO_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case SIMD_FCVTAS_REG_SCALAR_VEC:
      break;
   case SIMD_FCVTAS_REG_VEC_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FCVTAS_SINGLE_FROM_SP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTAS_SINGLE_FROM_SP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTAS_FROM_DP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTAS_FROM_DP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SIMD_FCVTAU_REG_SCALAR_VEC:
      break;
   case SIMD_FCVTAU_REG_VEC_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FCVTAU_SINGLE_FROM_SP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTAU_SINGLE_FROM_SP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTAU_FROM_DP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTAU_FROM_DP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SIMD_FCVTL_REG:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_FCVTMS_REG_SCALAR_VEC:
      break;
   case SIMD_FCVTMS_REG_VEC_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FCVTMS_SINGLE_FROM_SP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTMS_SINGLE_FROM_SP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTMS_FROM_DP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTMS_FROM_DP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SIMD_FCVTMU_REG_SCALAR_VEC:
      break;
   case SIMD_FCVTMU_REG_VEC_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FCVTMU_SINGLE_FROM_SP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTMU_SINGLE_FROM_SP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTMU_FROM_DP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTMU_FROM_DP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SIMD_FCVTN_REG:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_FCVTNS_REG_SCALAR_VEC:
      break;
   case SIMD_FCVTNS_REG_VEC_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FCVTNS_SINGLE_FROM_SP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTNS_SINGLE_FROM_SP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTNS_FROM_DP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTNS_FROM_DP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SIMD_FCVTNU_REG_SCALAR_VEC:
      break;
   case SIMD_FCVTNU_REG_VEC_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FCVTNU_SINGLE_FROM_SP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTNU_SINGLE_FROM_SP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTNU_FROM_DP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTNU_FROM_DP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SIMD_FCVTPS_REG_SCALAR_VEC:
      break;
   case SIMD_FCVTPS_REG_VEC_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FCVTPS_SINGLE_FROM_SP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTPS_SINGLE_FROM_SP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTPS_FROM_DP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTPS_FROM_DP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SIMD_FCVTPU_REG_SCALAR_VEC:
      break;
   case SIMD_FCVTPU_REG_VEC_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FCVTPU_SINGLE_FROM_SP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTPU_SINGLE_FROM_SP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTPU_FROM_DP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTPU_FROM_DP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SIMD_FCVTXN_REG_SCALAR:
      break;
   case SIMD_FCVTXN_REG_VEC:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_FCVTZS_SHIFT_IMM_SCALAR_VEC_FIXED:
      break;
   case SIMD_FCVTZS_SHIFT_IMM_VEC_VEC_FIXED:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FCVTZS_REG_SCALAR_VEC:
      break;
   case SIMD_FCVTZS_REG_VEC_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FCVTZS_SINGLE_FROM_SP_FP_FIXED_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTZS_SINGLE_FROM_SP_FP_FIXED_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTZS_FROM_DP_FP_FIXED_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTZS_FROM_DP_FP_FIXED_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTZS_SINGLE_FROM_SP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTZS_SINGLE_FROM_SP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTZS_FROM_DP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTZS_FROM_DP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SIMD_FCVTZU_SHIFT_IMM_SCALAR_VEC_FIXED:
      break;
   case SIMD_FCVTZU_SHIFT_IMM_VEC_VEC_FIXED:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FCVTZU_REG_SCALAR_VEC:
      break;
   case SIMD_FCVTZU_REG_VEC_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FCVTZU_SINGLE_FROM_SP_FP_FIXED_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTZU_SINGLE_FROM_SP_FP_FIXED_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTZU_FROM_DP_FP_FIXED_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTZU_FROM_DP_FP_FIXED_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTZU_SINGLE_FROM_SP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTZU_SINGLE_FROM_SP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTZU_FROM_DP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FCVTZU_FROM_DP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SIMD_FDIV_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FDIV_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FDIV_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case FMADD_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FMADD_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_FMAX_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FMAX_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FMAX_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_FMAXNM_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FMAXNM_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FMAXNM_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_FMAXNMP:
      break;
   case SIMD_FMAXNMP_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FMAXNMV:
      break;
   case SIMD_FMAXP:
      break;
   case SIMD_FMAXP_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FMAXV:
      break;
   case SIMD_FMIN_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FMIN_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FMIN_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_FMINNM_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FMINNM_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FMINNM_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_FMINNMP:
      break;
   case SIMD_FMINNMP_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FMINNMV:
      break;
   case SIMD_FMINP:
      break;
   case SIMD_FMINP_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FMINV:
      break;
   case SIMD_FMLA_SCALAR_ELEM:
      break;
   case SIMD_FMLA_VEC_VEC_ELEM:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FMLA_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FMLS_SCALAR_ELEM:
      break;
   case SIMD_FMLS_VEC_VEC_ELEM:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FMLS_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FMOV_IMM_MOD_SINGLE_VEC_FROM_SP:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FMOV_IMM_MOD_VEC_FROM_DP:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FMOV_SINGLE_REG_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FMOV_REG_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case FMOV_SINGLE_TO_SP_FP_32:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FMOV_SINGLE_FROM_SP_FP_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FMOV_TO_DP_FP_64:
      packet->mOpsWriteback.push_back(DD);
      break;
   case FMOV_FP_8_64_128_TO_TOP:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FMOV_FROM_DP_FP_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FMOV_FP_8_64_128:
      packet->mOpsWriteback.push_back(XD);
      break;
   case FMOV_IMM_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FMOV_IMM_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case FMSUB_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FMSUB_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_FMUL_SCALAR_ELEM:
      break;
   case SIMD_FMUL_VEC_VEC_ELEM:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FMUL_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FMUL_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FMUL_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_FMULX_SCALAR_ELEM:
      break;
   case SIMD_FMULX_VEC_VEC_ELEM:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FMULX_SCALAR:
      break;
   case SIMD_FMULX_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FNEG_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FNEG_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FNEG_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case FNMADD_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FNMADD_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case FNMSUB_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FNMSUB_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case FNMUL_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FNMUL_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_FRECPE_REG_SCALAR:
      break;
   case SIMD_FRECPE_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FRECPS_SCALAR:
      break;
   case SIMD_FRECPS_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FRECPX_REG:
      break;
   case SIMD_FRINTA_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FRINTA_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FRINTA_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_FRINTI_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FRINTI_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FRINTI_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_FRINTM_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FRINTM_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FRINTM_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_FRINTN_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FRINTN_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FRINTN_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_FRINTP_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FRINTP_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FRINTP_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_FRINTX_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FRINTX_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FRINTX_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_FRINTZ_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FRINTZ_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FRINTZ_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_FRSQRTE_REG_SCALAR:
      break;
   case SIMD_FRSQRTE_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FRSQRTS_SCALAR:
      break;
   case SIMD_FRSQRTS_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_FSQRT_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FSQRT_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FSQRT_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_FSUB_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case FSUB_SINGLE_FROM_SP:
      packet->mOpsWriteback.push_back(SD);
      break;
   case FSUB_FROM_DP:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_INS_ELEM:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_INS:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_LD1_FOUR_REG_MULT_STRUCT:
      break;
   case SIMD_LD1_THREE_REG_MULT_STRUCT:
      break;
   case SIMD_LD1_TWO_REG_MULT_STRUCT:
      break;
   case SIMD_LD1_ONE_REG_MULT_STRUCT:
      break;
   case SIMD_LD1_ONE_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_LD1_IMM_ONE_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_LD1_TWO_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_LD1_IMM_TWO_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_LD1_THREE_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_LD1_IMM_THREE_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_LD1_FOUR_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_LD1_IMM_FOUR_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_LD1_SINGLE_STRUCT_8:
      break;
   case SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_8:
      break;
   case SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_8:
      break;
   case SIMD_LD1_SINGLE_STRUCT_64:
      break;
   case SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_64:
      break;
   case SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_64:
      break;
   case SIMD_LD1_SINGLE_STRUCT_16:
      break;
   case SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_16:
      break;
   case SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_16:
      break;
   case SIMD_LD1_SINGLE_STRUCT_32:
      break;
   case SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_32:
      break;
   case SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_32:
      break;
   case SIMD_LD1R_OFF_SINGLE_STRUCT:
      break;
   case SIMD_LD1R_REG_OFF_SINGLE_POST_STRUCT:
      break;
   case SIMD_LD1R_OFF_SINGLE_POST_STRUCT:
      break;
   case SIMD_LD2_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_LD2_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_LD2_SINGLE_STRUCT_8:
      break;
   case SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_8:
      break;
   case SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_8:
      break;
   case SIMD_LD2_SINGLE_STRUCT_64:
      break;
   case SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_64:
      break;
   case SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_64:
      break;
   case SIMD_LD2_SINGLE_STRUCT_16:
      break;
   case SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_16:
      break;
   case SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_16:
      break;
   case SIMD_LD2_SINGLE_STRUCT_32:
      break;
   case SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_32:
      break;
   case SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_32:
      break;
   case SIMD_LD2R_OFF_SINGLE_STRUCT:
      break;
   case SIMD_LD2R_REG_OFF_SINGLE_POST_STRUCT:
      break;
   case SIMD_LD2R_OFF_SINGLE_POST_STRUCT:
      break;
   case SIMD_LD3_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_LD3_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_LD3_SINGLE_STRUCT_8:
      break;
   case SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_8:
      break;
   case SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_8:
      break;
   case SIMD_LD3_SINGLE_STRUCT_64:
      break;
   case SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_64:
      break;
   case SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_64:
      break;
   case SIMD_LD3_SINGLE_STRUCT_16:
      break;
   case SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_16:
      break;
   case SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_16:
      break;
   case SIMD_LD3_SINGLE_STRUCT_32:
      break;
   case SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_32:
      break;
   case SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_32:
      break;
   case SIMD_LD3R_OFF_SINGLE_STRUCT:
      break;
   case SIMD_LD3R_REG_OFF_SINGLE_POST_STRUCT:
      break;
   case SIMD_LD3R_OFF_SINGLE_POST_STRUCT:
      break;
   case SIMD_LD4_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_LD4_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_LD4_SINGLE_STRUCT_8:
      break;
   case SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_8:
      break;
   case SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_8:
      break;
   case SIMD_LD4_SINGLE_STRUCT_64:
      break;
   case SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_64:
      break;
   case SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_64:
      break;
   case SIMD_LD4_SINGLE_STRUCT_16:
      break;
   case SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_16:
      break;
   case SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_16:
      break;
   case SIMD_LD4_SINGLE_STRUCT_32:
      break;
   case SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_32:
      break;
   case SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_32:
      break;
   case SIMD_LD4R_OFF_SINGLE_STRUCT:
      break;
   case SIMD_LD4R_REG_OFF_SINGLE_POST_STRUCT:
      break;
   case SIMD_LD4R_OFF_SINGLE_POST_STRUCT:
      break;
   case SIMD_LDNP_OFF_64:
      packet->mOpsWriteback.push_back(DT);
      packet->mOpsWriteback.push_back(DT2);
      break;
   case SIMD_LDNP_OFF_8_128:
      packet->mOpsWriteback.push_back( QT );
      break;
   case SIMD_LDNP_OFF_32:
      packet->mOpsWriteback.push_back(ST);
      packet->mOpsWriteback.push_back(ST2);
      break;
   case SIMD_LDP_REG_POST_64:
      packet->mOpsWriteback.push_back(DT);
      packet->mOpsWriteback.push_back(DT2);
      break;
   case SIMD_LDP_REG_POST_8_128:
      packet->mOpsWriteback.push_back( QT );
      packet->mOpsWriteback.push_back( QT2 );
      break;
   case SIMD_LDP_REG_POST_32:
      packet->mOpsWriteback.push_back(ST);
      packet->mOpsWriteback.push_back(ST2);
      break;
   case SIMD_LDP_REG_PRE_64:
      packet->mOpsWriteback.push_back(DT);
      packet->mOpsWriteback.push_back(DT2);
      break;
   case SIMD_LDP_REG_PRE_8_128:
      packet->mOpsWriteback.push_back( QT );
      packet->mOpsWriteback.push_back( QT2 );
      break;
   case SIMD_LDP_REG_PRE_32:
      packet->mOpsWriteback.push_back(ST);
      packet->mOpsWriteback.push_back(ST2);
      break;
   case SIMD_LDP_REG_OFF_64:
      packet->mOpsWriteback.push_back(DT);
      packet->mOpsWriteback.push_back(DT2);
      break;
   case SIMD_LDP_REG_OFF_8_128:
      packet->mOpsWriteback.push_back( QT );
      packet->mOpsWriteback.push_back( QT2 );
      break;
   case SIMD_LDP_REG_OFF_32:
      packet->mOpsWriteback.push_back(ST);
      packet->mOpsWriteback.push_back(ST2);
      break;
   case SIMD_LDR_IMM_REG_PRE_8:
      packet->mOpsWriteback.push_back(BT);
      break;
   case SIMD_LDR_IMM_REG_POST_8:
      packet->mOpsWriteback.push_back(BT);
      break;
   case SIMD_LDR_IMM_REG_8:
      packet->mOpsWriteback.push_back(BT);
      break;
   case SIMD_LDR_IMM_REG_PRE_64:
      packet->mOpsWriteback.push_back(DT);
      break;
   case SIMD_LDR_IMM_REG_POST_64:
      packet->mOpsWriteback.push_back(DT);
      break;
   case SIMD_LDR_IMM_REG_64:
      packet->mOpsWriteback.push_back(DT);
      break;
   case SIMD_LDR_IMM_REG_PRE_16:
      packet->mOpsWriteback.push_back(HT);
      break;
   case SIMD_LDR_IMM_REG_POST_16:
      packet->mOpsWriteback.push_back(HT);
      break;
   case SIMD_LDR_IMM_REG_16:
      packet->mOpsWriteback.push_back(HT);
      break;
   case SIMD_LDR_IMM_REG_PRE_8_128:
      packet->mOpsWriteback.push_back( QT );
      break;
   case SIMD_LDR_IMM_REG_POST_8_128:
      packet->mOpsWriteback.push_back( QT );
      break;
   case SIMD_LDR_IMM_REG_8_128:
      packet->mOpsWriteback.push_back( QT );
      break;
   case SIMD_LDR_IMM_REG_PRE_32:
      packet->mOpsWriteback.push_back(ST);
      break;
   case SIMD_LDR_IMM_REG_POST_32:
      packet->mOpsWriteback.push_back(ST);
      break;
   case SIMD_LDR_IMM_REG_32:
      packet->mOpsWriteback.push_back(ST);
      break;
   case SIMD_LDR_REG_64:
      packet->mOpsWriteback.push_back(DT);
      break;
   case SIMD_LDR_REG_8_128:
      packet->mOpsWriteback.push_back( QT );
      break;
   case SIMD_LDR_REG_32:
      packet->mOpsWriteback.push_back(ST);
      break;
   case SIMD_LDR_REG_OFF_8:
      packet->mOpsWriteback.push_back(BT);
      break;
   case SIMD_LDR_REG_OFF_64:
      packet->mOpsWriteback.push_back(DT);
      break;
   case SIMD_LDR_REG_OFF_16:
      packet->mOpsWriteback.push_back(HT);
      break;
   case SIMD_LDR_REG_OFF_8_128:
      packet->mOpsWriteback.push_back( QT );
      break;
   case SIMD_LDR_REG_OFF_32:
      packet->mOpsWriteback.push_back(ST);
      break;
   case SIMD_LDUR_IMM_REG_8:
      break;
   case SIMD_LDUR_IMM_REG_64:
      break;
   case SIMD_LDUR_IMM_REG_16:
      break;
   case SIMD_LDUR_IMM_REG_8_128:
      break;
   case SIMD_LDUR_IMM_REG_32:
      break;
   case SIMD_MLA_VEC_ELEM:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_MLA_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_MLS_VEC_ELEM:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_MLS_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_MOVI_SHIFT_IMM_MOD_16:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_MOVI_SHIFT_IMM_MOD_32:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_MOVI_SHIFT_IMM_ONES_MOD_32:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_MOVI_IMM_MOD_64:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_MOVI_IMM_MOD_VEC_64:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_MOVI_IMM_MOD_8:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_MUL_VEC_ELEM:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_MUL_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_MVNI_SHIFT_IMM_MOD_16:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_MVNI_SHIFT_IMM_MOD_32:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_MVNI_SHIFT_IMM_ONES_MOD_32:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_NEG_REG_SCALAR_VEC:
      break;
   case SIMD_NEG_REG_VEC_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_NOT_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_ORN_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_ORR_IMM_MOD_VEC_32:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_ORR_IMM_MOD_VEC_16:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_ORR_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_PMUL:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_PMULL:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_RADDHN:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_RBIT_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_REV16_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_REV32_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_REV64_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_RSHRN_SHIFT_IMM:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_RSUBHN:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SABA:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SABAL:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SABD:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SABDL:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SADALP_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SADDL:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SADDLP_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SADDLV:
      break;
   case SIMD_SADDW:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SCVTF_SHIFT_IMM_SCALAR_VEC_FIXED:
      break;
   case SIMD_SCVTF_SHIFT_IMM_VEC_VEC_FIXED:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SCVTF_REG_SCALAR_VEC:
      break;
   case SIMD_SCVTF_REG_VEC_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SCVTF_SINGLE_TO_SP_FP_FIXED_32:
      packet->mOpsWriteback.push_back(SD);
      break;
   case SCVTF_TO_DP_FP_FIXED_32:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SCVTF_SINGLE_TO_SP_FP_FIXED_64:
      packet->mOpsWriteback.push_back(SD);
      break;
   case SCVTF_TO_DP_FP_FIXED_64:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SCVTF_SINGLE_TO_SP_FP_32:
      packet->mOpsWriteback.push_back(SD);
      break;
   case SCVTF_TO_DP_FP_32:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SCVTF_SINGLE_TO_SP_FP_64:
      packet->mOpsWriteback.push_back(SD);
      break;
   case SCVTF_TO_DP_FP_64:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SHA1C_REG:
      break;
   case SHA1H_REG:
      packet->mOpsWriteback.push_back(SD);
      break;
   case SHA1M_REG:
      break;
   case SHA1P_REG:
      break;
   case SHA1SU0_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SHA1SU1_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SHA256H2_REG:
      break;
   case SHA256H_REG:
      break;
   case SHA256SU0_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SHA256SU1_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SHADD:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SHL_SHIFT_IMM_SCALAR:
      break;
   case SIMD_SHL_SHIFT_IMM_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SHLL_REG:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SHRN_SHIFT_IMM:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SHSUB:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SLI_SHIFT_IMM_SCALAR:
      break;
   case SIMD_SLI_SHIFT_IMM_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SMAX:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SMAXP:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SMAXV:
      break;
   case SIMD_SMIN:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SMINP:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SMINV:
      break;
   case SIMD_SMLAL_VEC_ELEM:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SMLAL_VEC:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SMLSL_VEC_ELEM:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SMLSL_VEC:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SMOV_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SIMD_SMOV_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SIMD_SMULL_VEC_ELEM:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SMULL_VEC:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SQABS_REG_SCALAR:
      break;
   case SIMD_SQABS_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SQADD_SCALAR:
      break;
   case SIMD_SQADD_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SQDMLAL_SCALAR_ELEM:
      break;
   case SIMD_SQDMLAL_VEC_VEC_ELEM:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SQDMLAL_SCALAR_VEC:
      break;
   case SIMD_SQDMLAL_VEC_VEC:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SQDMLSL_SCALAR_ELEM:
      break;
   case SIMD_SQDMLSL_VEC_VEC_ELEM:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SQDMLSL_SCALAR_VEC:
      break;
   case SIMD_SQDMLSL_VEC_VEC:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SQDMULH_SCALAR_ELEM:
      break;
   case SIMD_SQDMULH_VEC_VEC_ELEM:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SQDMULH_SCALAR_VEC:
      break;
   case SIMD_SQDMULH_VEC_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SQDMULL_SCALAR_ELEM:
      break;
   case SIMD_SQDMULL_VEC_VEC_ELEM:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SQDMULL_SCALAR_VEC:
      break;
   case SIMD_SQDMULL_VEC_VEC:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SQNEG_REG_SCALAR:
      break;
   case SIMD_SQNEG_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SQRDMULH_SCALAR_ELEM:
      break;
   case SIMD_SQRDMULH_VEC_VEC_ELEM:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SQRDMULH_SCALAR_VEC:
      break;
   case SIMD_SQRDMULH_VEC_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SQRSHL_SCALAR:
      break;
   case SIMD_SQRSHL_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SQRSHRN_SHIFT_IMM_SCALAR:
      break;
   case SIMD_SQRSHRN_SHIFT_IMM_VEC:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SQRSHRUN_SHIFT_IMM_SCALAR:
      break;
   case SIMD_SQRSHRUN_SHIFT_IMM_VEC:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SQSHL_SHIFT_IMM_SCALAR:
      break;
   case SIMD_SQSHL_SHIFT_IMM_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SQSHL_REG_SCALAR:
      break;
   case SIMD_SQSHL_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SQSHLU_SHIFT_IMM_SCALAR:
      break;
   case SIMD_SQSHLU_SHIFT_IMM_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SQSHRN_SHIFT_IMM_SCALAR:
      break;
   case SIMD_SQSHRN_SHIFT_IMM_VEC:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SQSHRUN_SHIFT_IMM_SCALAR:
      break;
   case SIMD_SQSHRUN_SHIFT_IMM_VEC:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SQSUB_SCALAR:
      break;
   case SIMD_SQSUB_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SQXTN_REG_SCALAR:
      break;
   case SIMD_SQXTN_REG_VEC:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SQXTUN_REG_SCALAR:
      break;
   case SIMD_SQXTUN_REG_VEC:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SRHADD:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SRI_SHIFT_IMM_SCALAR:
      break;
   case SIMD_SRI_SHIFT_IMM_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SRSHL_SCALAR:
      break;
   case SIMD_SRSHL_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SRSHR_SHIFT_IMM_SCALAR:
      break;
   case SIMD_SRSHR_SHIFT_IMM_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SRSRA_SHIFT_IMM_SCALAR:
      break;
   case SIMD_SRSRA_SHIFT_IMM_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SSHL_SCALAR:
      break;
   case SIMD_SSHL_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SSHLL_SHIFT_IMM:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SSHR_SHIFT_IMM_SCALAR:
      break;
   case SIMD_SSHR_SHIFT_IMM_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SSRA_SHIFT_IMM_SCALAR:
      break;
   case SIMD_SSRA_SHIFT_IMM_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SSUBL:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SSUBW:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_ST1_ONE_REG_MULT_STRUCT:
      break;
   case SIMD_ST1_TWO_REG_MULT_STRUCT:
      break;
   case SIMD_ST1_THREE_REG_MULT_STRUCT:
      break;
   case SIMD_ST1_FOUR_REG_MULT_STRUCT:
      break;
   case SIMD_ST1_ONE_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_ST1_IMM_ONE_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_ST1_TWO_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_ST1_IMM_TWO_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_ST1_THREE_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_ST1_IMM_THREE_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_ST1_FOUR_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_ST1_IMM_FOUR_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_ST1_SINGLE_STRUCT_8:
      break;
   case SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_8:
      break;
   case SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_8:
      break;
   case SIMD_ST1_SINGLE_STRUCT_64:
      break;
   case SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_64:
      break;
   case SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_64:
      break;
   case SIMD_ST1_SINGLE_STRUCT_16:
      break;
   case SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_16:
      break;
   case SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_16:
      break;
   case SIMD_ST1_SINGLE_STRUCT_32:
      break;
   case SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_32:
      break;
   case SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_32:
      break;
   case SIMD_ST2_OFF_MULT_STRUCT:
      break;
   case SIMD_ST2_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_ST2_SINGLE_STRUCT_8:
      break;
   case SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_8:
      break;
   case SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_8:
      break;
   case SIMD_ST2_SINGLE_STRUCT_64:
      break;
   case SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_64:
      break;
   case SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_64:
      break;
   case SIMD_ST2_SINGLE_STRUCT_16:
      break;
   case SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_16:
      break;
   case SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_16:
      break;
   case SIMD_ST2_SINGLE_STRUCT_32:
      break;
   case SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_32:
      break;
   case SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_32:
      break;
   case SIMD_ST3_OFF_MULT_STRUCT:
      break;
   case SIMD_ST3_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_ST3_SINGLE_STRUCT_8:
      break;
   case SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_8:
      break;
   case SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_8:
      break;
   case SIMD_ST3_SINGLE_STRUCT_64:
      break;
   case SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_64:
      break;
   case SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_64:
      break;
   case SIMD_ST3_SINGLE_STRUCT_16:
      break;
   case SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_16:
      break;
   case SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_16:
      break;
   case SIMD_ST3_SINGLE_STRUCT_32:
      break;
   case SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_32:
      break;
   case SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_32:
      break;
   case SIMD_ST4_OFF_MULT_STRUCT:
      break;
   case SIMD_ST4_REG_OFF_MULT_POST_STRUCT:
      break;
   case SIMD_ST4_SINGLE_STRUCT_8:
      break;
   case SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_8:
      break;
   case SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_8:
      break;
   case SIMD_ST4_SINGLE_STRUCT_64:
      break;
   case SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_64:
      break;
   case SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_64:
      break;
   case SIMD_ST4_SINGLE_STRUCT_16:
      break;
   case SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_16:
      break;
   case SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_16:
      break;
   case SIMD_ST4_SINGLE_STRUCT_32:
      break;
   case SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_32:
      break;
   case SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_32:
      break;
   case SIMD_STNP_OFF_64:
      break;
   case SIMD_STNP_OFF_8_128:
      break;
   case SIMD_STNP_OFF_32:
      break;
   case SIMD_STP_REG_POST_64:
      break;
   case SIMD_STP_REG_POST_8_128:
      break;
   case SIMD_STP_REG_POST_32:
      break;
   case SIMD_STP_REG_PRE_64:
      break;
   case SIMD_STP_REG_PRE_8_128:
      break;
   case SIMD_STP_REG_PRE_32:
      break;
   case SIMD_STP_REG_OFF_64:
      break;
   case SIMD_STP_REG_OFF_8_128:
      break;
   case SIMD_STP_REG_OFF_32:
      break;
   case SIMD_STR_IMM_REG_PRE_8:
      break;
   case SIMD_STR_IMM_REG_POST_8:
      break;
   case SIMD_STR_IMM_REG_8:
      break;
   case SIMD_STR_IMM_REG_PRE_64:
      break;
   case SIMD_STR_IMM_REG_POST_64:
      break;
   case SIMD_STR_IMM_REG_64:
      break;
   case SIMD_STR_IMM_REG_PRE_16:
      break;
   case SIMD_STR_IMM_REG_POST_16:
      break;
   case SIMD_STR_IMM_REG_16:
      break;
   case SIMD_STR_IMM_REG_PRE_8_128:
      break;
   case SIMD_STR_IMM_REG_POST_8_128:
      break;
   case SIMD_STR_IMM_REG_8_128:
      break;
   case SIMD_STR_IMM_REG_PRE_32:
      break;
   case SIMD_STR_IMM_REG_POST_32:
      break;
   case SIMD_STR_IMM_REG_32:
      break;
   case SIMD_STR_REG_OFF_8:
      break;
   case SIMD_STR_REG_OFF_64:
      break;
   case SIMD_STR_REG_OFF_16:
      break;
   case SIMD_STR_REG_OFF_8_128:
      break;
   case SIMD_STR_REG_OFF_32:
      break;
   case SIMD_STUR_IMM_REG_8:
      break;
   case SIMD_STUR_IMM_REG_64:
      break;
   case SIMD_STUR_IMM_REG_16:
      break;
   case SIMD_STUR_IMM_REG_8_128:
      break;
   case SIMD_STUR_IMM_REG_32:
      break;
   case SIMD_SUB_SCALAR_VEC:
      break;
   case SIMD_SUB_VEC_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_SUBHN:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_SUQADD_REG_SCALAR:
      break;
   case SIMD_SUQADD_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_TBL_FOUR_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_TBL_SINGLE_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_TBL_THREE_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_TBL_TWO_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_TBX_FOUR_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_TBX_SINGLE_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_TBX_THREE_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_TBX_TWO_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_TRN1:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_TRN2:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UABA:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UABAL:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_UABD:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UABDL:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_UADALP_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UADDL:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_UADDLP_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UADDLV:
      break;
   case SIMD_UADDW:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_UCVTF_SHIFT_IMM_SCALAR_VEC_FIXED:
      break;
   case SIMD_UCVTF_SHIFT_IMM_VEC_VEC_FIXED:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UCVTF_REG_SCALAR_VEC:
      break;
   case SIMD_UCVTF_REG_VEC_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case UCVTF_SINGLE_TO_SP_FP_FIXED_32:
      packet->mOpsWriteback.push_back(SD);
      break;
   case UCVTF_TO_DP_FP_FIXED_32:
      packet->mOpsWriteback.push_back(DD);
      break;
   case UCVTF_SINGLE_TO_SP_FP_FIXED_64:
      packet->mOpsWriteback.push_back(SD);
      break;
   case UCVTF_TO_DP_FP_FIXED_64:
      packet->mOpsWriteback.push_back(DD);
      break;
   case UCVTF_SINGLE_TO_SP_FP_32:
      packet->mOpsWriteback.push_back(SD);
      break;
   case UCVTF_TO_DP_FP_32:
      packet->mOpsWriteback.push_back(DD);
      break;
   case UCVTF_SINGLE_TO_SP_FP_64:
      packet->mOpsWriteback.push_back(SD);
      break;
   case UCVTF_TO_DP_FP_64:
      packet->mOpsWriteback.push_back(DD);
      break;
   case SIMD_UHADD:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UHSUB:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UMAX:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UMAXP:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UMAXV:
      break;
   case SIMD_UMIN:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UMINP:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UMINV:
      break;
   case SIMD_UMLAL_VEC_ELEM:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_UMLAL_VEC:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_UMLSL_VEC_ELEM:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_UMLSL_VEC:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_UMOV_32:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SIMD_UMOV_64:
      packet->mOpsWriteback.push_back(XD);
      break;
   case SIMD_UMULL_VEC_ELEM:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_UMULL_VEC:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_UQADD_SCALAR:
      break;
   case SIMD_UQADD_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UQRSHL_SCALAR:
      break;
   case SIMD_UQRSHL_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UQRSHRN_SHIFT_IMM_SCALAR:
      break;
   case SIMD_UQRSHRN_SHIFT_IMM_VEC:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_UQSHL_SHIFT_IMM_SCALAR:
      break;
   case SIMD_UQSHL_SHIFT_IMM_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UQSHL_REG_SCALAR:
      break;
   case SIMD_UQSHL_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UQSHRN_SHIFT_IMM_SCALAR:
      break;
   case SIMD_UQSHRN_SHIFT_IMM_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UQSUB_SCALAR:
      break;
   case SIMD_UQSUB_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UQXTN_REG_SCALAR:
      break;
   case SIMD_UQXTN_REG_VEC:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_URECPE_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_URHADD:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_URSHL_SCALAR:
      break;
   case SIMD_URSHL_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_URSHR_SHIFT_IMM_SCALAR:
      break;
   case SIMD_URSHR_SHIFT_IMM_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_URSQRTE_REG:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_URSRA_SHIFT_IMM_SCALAR:
      break;
   case SIMD_URSRA_SHIFT_IMM_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_USHL_SCALAR:
      break;
   case SIMD_USHL_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_USHLL_SHIFT_IMM:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_USHR_SHIFT_IMM_SCALAR:
      break;
   case SIMD_USHR_SHIFT_IMM_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_USQADD_REG_SCALAR:
      break;
   case SIMD_USQADD_REG_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_USRA_SHIFT_IMM_SCALAR:
      break;
   case SIMD_USRA_SHIFT_IMM_VEC:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_USUBL:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_USUBW:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_UZP1:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_UZP2:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_XTN_REG:
      if (packet->Q==0) {
      packet->mOpsWriteback.push_back(VD);
      }
      if (packet->Q==1) {
      packet->mOpsWriteback.push_back(VD);
      }
      break;
   case SIMD_ZIP1:
      packet->mOpsWriteback.push_back(VD);
      break;
   case SIMD_ZIP2:
      packet->mOpsWriteback.push_back(VD);
      break;
