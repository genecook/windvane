// A64 Data Processing...
    ADD_REG_32: //Add/subtract (extended register)/ADD (extended register) 32-bit
    ADD_REG_64: //Add/subtract (extended register)/ADD (extended register) 64-bit
    ADDS_REG_32: //Add/subtract (extended register)/ADDS (extended register) 32-bit
    ADDS_REG_64: //Add/subtract (extended register)/ADDS (extended register) 64-bit
    SUB_REG_32: //Add/subtract (extended register)/SUB (extended register) 32-bit
    SUB_REG_64: //Add/subtract (extended register)/SUB (extended register) 64-bit
    SUBS_REG_32: //Add/subtract (extended register)/SUBS (extended register) 32-bit
    SUBS_REG_64: //Add/subtract (extended register)/SUBS (extended register) 64-bit
    ADD_IMM_32: //Add/subtract (immediate)/ADD (immediate) 32-bit
    ADD_IMM_64: //Add/subtract (immediate)/ADD (immediate) 64-bit
    ADDS_IMM_32: //Add/subtract (immediate)/ADDS (immediate) 32-bit
    ADDS_IMM_64: //Add/subtract (immediate)/ADDS (immediate) 64-bit
    SUB_IMM_32: //Add/subtract (immediate)/SUB (immediate) 32-bit
    SUB_IMM_64: //Add/subtract (immediate)/SUB (immediate) 64-bit
    SUBS_IMM_32: //Add/subtract (immediate)/SUBS (immediate) 32-bit
    SUBS_IMM_64: //Add/subtract (immediate)/SUBS (immediate) 64-bit
    ADD_SHIFT_REG_32: //Add/subtract (shifted register)/ADD (shifted register) 32-bit
    ADD_SHIFT_REG_64: //Add/subtract (shifted register)/ADD (shifted register) 64-bit
    ADDS_SHIFT_REG_32: //Add/subtract (shifted register)/ADDS (shifted register) 32-bit
    ADDS_SHIFT_REG_64: //Add/subtract (shifted register)/ADDS (shifted register) 64-bit
    SUB_SHIFT_REG_32: //Add/subtract (shifted register)/SUB (shifted register) 32-bit
    SUB_SHIFT_REG_64: //Add/subtract (shifted register)/SUB (shifted register) 64-bit
    SUBS_SHIFT_REG_32: //Add/subtract (shifted register)/SUBS (shifted register) 32-bit
    SUBS_SHIFT_REG_64: //Add/subtract (shifted register)/SUBS (shifted register) 64-bit
    ADC_32: //Add/subtract (with carry)/ADC 32-bit
    ADC_64: //Add/subtract (with carry)/ADC 64-bit
    ADCS_32: //Add/subtract (with carry)/ADCS 32-bit
    ADCS_64: //Add/subtract (with carry)/ADCS 64-bit
    SBC_32: //Add/subtract (with carry)/SBC 32-bit
    SBC_64: //Add/subtract (with carry)/SBC 64-bit
    SBCS_32: //Add/subtract (with carry)/SBCS 32-bit
    SBCS_64: //Add/subtract (with carry)/SBCS 64-bit
    BFM_32: //Bitfield/BFM 32-bit
    BFM_64: //Bitfield/BFM 64-bit
    SBFM_32: //Bitfield/SBFM 32-bit
    SBFM_64: //Bitfield/SBFM 64-bit
    UBFM_32: //Bitfield/UBFM 32-bit
    UBFM_64: //Bitfield/UBFM 64-bit
    CCMN_IMM_32: //Conditional compare (immediate)/CCMN (immediate) 32-bit
    CCMN_IMM_64: //Conditional compare (immediate)/CCMN (immediate) 64-bit
    CCMP_IMM_32: //Conditional compare (immediate)/CCMP (immediate) 32-bit
    CCMP_IMM_64: //Conditional compare (immediate)/CCMP (immediate) 64-bit
    CCMN_REG_32: //Conditional compare (register)/CCMN (register) 32-bit
    CCMN_REG_64: //Conditional compare (register)/CCMN (register) 64-bit
    CCMP_REG_32: //Conditional compare (register)/CCMP (register) 32-bit
    CCMP_REG_64: //Conditional compare (register)/CCMP (register) 64-bit
    CSEL_32: //Conditional select/CSEL 32-bit
    CSEL_64: //Conditional select/CSEL 64-bit
    CSINC_32: //Conditional select/CSINC 32-bit
    CSINC_64: //Conditional select/CSINC 64-bit
    CSINV_32: //Conditional select/CSINV 32-bit
    CSINV_64: //Conditional select/CSINV 64-bit
    CSNEG_32: //Conditional select/CSNEG 32-bit
    CSNEG_64: //Conditional select/CSNEG 64-bit
    CLS_32: //Data-processing (1 source)/CLS 32-bit
    CLS_64: //Data-processing (1 source)/CLS 64-bit
    CLZ_32: //Data-processing (1 source)/CLZ 32-bit
    CLZ_64: //Data-processing (1 source)/CLZ 64-bit
    RBIT_32: //Data-processing (1 source)/RBIT 32-bit
    RBIT_64: //Data-processing (1 source)/RBIT 64-bit
    REV_32: //Data-processing (1 source)/REV 32-bit
    REV_64: //Data-processing (1 source)/REV 64-bit
    REV16_32: //Data-processing (1 source)/REV16 32-bit
    REV16_64: //Data-processing (1 source)/REV16 64-bit
    REV32: //Data-processing (1 source)/REV32 -
    ASRV_32: //Data-processing (2 source)/ASRV 32-bit
    ASRV_64: //Data-processing (2 source)/ASRV 64-bit
    CRC32B: //Data-processing (2 source)/CRC32B
    CRC32CB: //Data-processing (2 source)/CRC32CB
    CRC32CH: //Data-processing (2 source)/CRC32CH
    CRC32CW: //Data-processing (2 source)/CRC32CW
    CRC32CX: //Data-processing (2 source)/CRC32CX
    CRC32H: //Data-processing (2 source)/CRC32H
    CRC32W: //Data-processing (2 source)/CRC32W
    CRC32X: //Data-processing (2 source)/CRC32X
    LSLV_32: //Data-processing (2 source)/LSLV 32-bit
    LSLV_64: //Data-processing (2 source)/LSLV 64-bit
    LSRV_32: //Data-processing (2 source)/LSRV 32-bit
    LSRV_64: //Data-processing (2 source)/LSRV 64-bit
    RORV_32: //Data-processing (2 source)/RORV 32-bit
    RORV_64: //Data-processing (2 source)/RORV 64-bit
    SDIV_32: //Data-processing (2 source)/SDIV 32-bit
    SDIV_64: //Data-processing (2 source)/SDIV 64-bit
    UDIV_32: //Data-processing (2 source)/UDIV 32-bit
    UDIV_64: //Data-processing (2 source)/UDIV 64-bit
    MADD_32: //Data-processing (3 source)/MADD 32-bit
    MADD_64: //Data-processing (3 source)/MADD 64-bit
    MSUB_32: //Data-processing (3 source)/MSUB 32-bit
    MSUB_64: //Data-processing (3 source)/MSUB 64-bit
    SMADDL: //Data-processing (3 source)/SMADDL -
    SMSUBL: //Data-processing (3 source)/SMSUBL -
    SMULH: //Data-processing (3 source)/SMULH -
    UMADDL: //Data-processing (3 source)/UMADDL -
    UMSUBL: //Data-processing (3 source)/UMSUBL -
    UMULH: //Data-processing (3 source)/UMULH -
    EXTR_32: //Extract/EXTR 32-bit
    EXTR_64: //Extract/EXTR 64-bit

// A64 Logical...
    AND_IMM_32: //Logical (immediate)/AND (immediate) 32-bit
    AND_IMM_64: //Logical (immediate)/AND (immediate) 64-bit
    ANDS_IMM_32: //Logical (immediate)/ANDS (immediate) 32-bit
    ANDS_IMM_64: //Logical (immediate)/ANDS (immediate) 64-bit
    EOR_IMM_32: //Logical (immediate)/EOR (immediate) 32-bit
    EOR_IMM_64: //Logical (immediate)/EOR (immediate) 64-bit
    ORR_IMM_32: //Logical (immediate)/ORR (immediate) 32-bit
    ORR_IMM_64: //Logical (immediate)/ORR (immediate) 64-bit
    AND_SHIFT_REG_32: //Logical (shifted register)/AND (shifted register) 32-bit
    AND_SHIFT_REG_64: //Logical (shifted register)/AND (shifted register) 64-bit
    ANDS_SHIFT_REG_32: //Logical (shifted register)/ANDS (shifted register) 32-bit
    ANDS_SHIFT_REG_64: //Logical (shifted register)/ANDS (shifted register) 64-bit
    BIC_SHIFT_REG_32: //Logical (shifted register)/BIC (shifted register) 32-bit
    BIC_SHIFT_REG_64: //Logical (shifted register)/BIC (shifted register) 64-bit
    BICS_SHIFT_REG_32: //Logical (shifted register)/BICS (shifted register) 32-bit
    BICS_SHIFT_REG_64: //Logical (shifted register)/BICS (shifted register) 64-bit
    EON_SHIFT_REG_32: //Logical (shifted register)/EON (shifted register) 32-bit
    EON_SHIFT_REG_64: //Logical (shifted register)/EON (shifted register) 64-bit
    EOR_SHIFT_REG_32: //Logical (shifted register)/EOR (shifted register) 32-bit
    EOR_SHIFT_REG_64: //Logical (shifted register)/EOR (shifted register) 64-bit
    ORN_SHIFT_REG_32: //Logical (shifted register)/ORN (shifted register) 32-bit
    ORN_SHIFT_REG_64: //Logical (shifted register)/ORN (shifted register) 64-bit
    ORR_SHIFT_REG_32: //Logical (shifted register)/ORR (shifted register) 32-bit
    ORR_SHIFT_REG_64: //Logical (shifted register)/ORR (shifted register) 64-bit

// A64 Move Wide...
    MOVK_IMM_32: //Move wide (immediate)/MOVK 32-bit
    MOVK_IMM_64: //Move wide (immediate)/MOVK 64-bit
    MOVN_IMM_32: //Move wide (immediate)/MOVN 32-bit
    MOVN_IMM_64: //Move wide (immediate)/MOVN 64-bit
    MOVZ_IMM_32: //Move wide (immediate)/MOVZ 32-bit
    MOVZ_IMM_64: //Move wide (immediate)/MOVZ 64-bit

// A64 PC Relative...
    ADR: //PC-relative addressing/ADR -
    ADRP: //PC-relative addressing/ADRP -

// A64 PC Branch...
    CBNZ_IMM_32: //Compare & branch (immediate)/CBNZ 32-bit
    CBNZ_IMM_64: //Compare & branch (immediate)/CBNZ 64-bit
    CBZ_IMM_32: //Compare & branch (immediate)/CBZ 32-bit
    CBZ_IMM_64: //Compare & branch (immediate)/CBZ 64-bit
    B_COND_IMM: //Conditional branch (immediate)/B.cond -
    TBNZ: //Test & branch (immediate)/TBNZ -
    TBZ: //Test & branch (immediate)/TBZ -
    B_IMM: //Unconditional branch (immediate)/B -
    BL: //Unconditional branch (immediate)/BL -
    BLR: //Unconditional branch (register)/BLR -
    BR: //Unconditional branch (register)/BR -
    DRPS: //Unconditional branch (register)/DRPS -
    ERET: //Unconditional branch (register)/ERET -
    RET: //Unconditional branch (register)/RET -

// A64 Load/Store...
    LDR_REG_32: //Load register (literal)/LDR (literal) 32-bit
    LDR_REG_64: //Load register (literal)/LDR (literal) 64-bit
    LDRSW_REG: //Load register (literal)/LDRSW (literal) -
    PRFM_REG: //Load register (literal)/PRFM (literal) -
    LDNP_OFF_32: //Load/store no-allocate pair (offset)/LDNP 32-bit
    LDNP_OFF_64: //Load/store no-allocate pair (offset)/LDNP 64-bit
    STNP_OFF_32: //Load/store no-allocate pair (offset)/STNP 32-bit
    STNP_OFF_64: //Load/store no-allocate pair (offset)/STNP 64-bit
    LDR_IMM_REG_POST_32: //Load/store register (immediate post-indexed)/LDR (immediate) 32-bit
    LDR_IMM_REG_POST_64: //Load/store register (immediate post-indexed)/LDR (immediate) 64-bit
    LDRB_IMM_REG_POST: //Load/store register (immediate post-indexed)/LDRB (immediate) Post-index
    LDRH_IMM_REG_POST: //Load/store register (immediate post-indexed)/LDRH (immediate) Post-index
    LDRSB_IMM_REG_POST_32: //Load/store register (immediate post-indexed)/LDRSB (immediate) 32-bit
    LDRSB_IMM_REG_POST_64: //Load/store register (immediate post-indexed)/LDRSB (immediate) 64-bit
    LDRSH_IMM_REG_POST_32: //Load/store register (immediate post-indexed)/LDRSH (immediate) 32-bit
    LDRSH_IMM_REG_POST_64: //Load/store register (immediate post-indexed)/LDRSH (immediate) 64-bit
    LDRSW_IMM_REG_POST: //Load/store register (immediate post-indexed)/LDRSW (immediate) Post-index
    STR_IMM_REG_POST_32: //Load/store register (immediate post-indexed)/STR (immediate) 32-bit
    STR_IMM_REG_POST_64: //Load/store register (immediate post-indexed)/STR (immediate) 64-bit
    STRB_IMM_REG_POST: //Load/store register (immediate post-indexed)/STRB (immediate) Post-index
    STRH_IMM_REG_POST: //Load/store register (immediate post-indexed)/STRH (immediate) Post-index
    LDR_IMM_REG_PRE_32: //Load/store register (immediate pre-indexed)/LDR (immediate) 32-bit
    LDR_IMM_REG_PRE_64: //Load/store register (immediate pre-indexed)/LDR (immediate) 64-bit
    LDRB_IMM_REG_PRE: //Load/store register (immediate pre-indexed)/LDRB (immediate) Pre-index
    LDRH_IMM_REG_PRE: //Load/store register (immediate pre-indexed)/LDRH (immediate) Pre-index
    LDRSB_IMM_REG_PRE_32: //Load/store register (immediate pre-indexed)/LDRSB (immediate) 32-bit
    LDRSB_IMM_REG_PRE_64: //Load/store register (immediate pre-indexed)/LDRSB (immediate) 64-bit
    LDRSH_IMM_REG_PRE_32: //Load/store register (immediate pre-indexed)/LDRSH (immediate) 32-bit
    LDRSH_IMM_REG_PRE_64: //Load/store register (immediate pre-indexed)/LDRSH (immediate) 64-bit
    LDRSW_IMM_REG_PRE: //Load/store register (immediate pre-indexed)/LDRSW (immediate) Pre-index
    STR_IMM_REG_PRE_32: //Load/store register (immediate pre-indexed)/STR (immediate) 32-bit
    STR_IMM_REG_PRE_64: //Load/store register (immediate pre-indexed)/STR (immediate) 64-bit
    STRB_IMM_REG_PRE: //Load/store register (immediate pre-indexed)/STRB (immediate) Pre-index
    STRH_IMM_REG_PRE: //Load/store register (immediate pre-indexed)/STRH (immediate) Pre-index
    LDR_REG_OFF_32: //Load/store register (register offset)/LDR (register) 32-bit
    LDR_REG_OFF_64: //Load/store register (register offset)/LDR (register) 64-bit
    LDRB_REG_OFF: //Load/store register (register offset)/LDRB (register) -
    LDRH_REG_OFF: //Load/store register (register offset)/LDRH (register) -
    LDRSB_REG_OFF_32: //Load/store register (register offset)/LDRSB (register) 32-bit
    LDRSB_REG_OFF_64: //Load/store register (register offset)/LDRSB (register) 64-bit
    LDRSH_REG_OFF_32: //Load/store register (register offset)/LDRSH (register) 32-bit
    LDRSH_REG_OFF_64: //Load/store register (register offset)/LDRSH (register) 64-bit
    LDRSW_REG_OFF: //Load/store register (register offset)/LDRSW (register) -
    PRFM_REG_OFF: //Load/store register (register offset)/PRFM (register) -
    STR_REG_OFF_32: //Load/store register (register offset)/STR (register) 32-bit
    STR_REG_OFF_64: //Load/store register (register offset)/STR (register) 64-bit
    STRB_REG_OFF: //Load/store register (register offset)/STRB (register) -
    STRH_REG_OFF: //Load/store register (register offset)/STRH (register) -
    LDTR_REG_32: //Load/store register (unprivileged)/LDTR 32-bit
    LDTR_REG_64: //Load/store register (unprivileged)/LDTR 64-bit
    LDTRB_REG: //Load/store register (unprivileged)/LDTRB -
    LDTRH_REG: //Load/store register (unprivileged)/LDTRH -
    LDTRSB_REG_32: //Load/store register (unprivileged)/LDTRSB 32-bit
    LDTRSB_REG_64: //Load/store register (unprivileged)/LDTRSB 64-bit
    LDTRSH_REG_32: //Load/store register (unprivileged)/LDTRSH 32-bit
    LDTRSH_REG_64: //Load/store register (unprivileged)/LDTRSH 64-bit
    LDTRSW_REG: //Load/store register (unprivileged)/LDTRSW -
    STTR_REG_32: //Load/store register (unprivileged)/STTR 32-bit
    STTR_REG_64: //Load/store register (unprivileged)/STTR 64-bit
    STTRB_REG: //Load/store register (unprivileged)/STTRB -
    STTRH_REG: //Load/store register (unprivileged)/STTRH -
    LDUR_IMM_REG_32: //Load/store register (unscaled immediate)/LDUR 32-bit
    LDUR_IMM_REG_64: //Load/store register (unscaled immediate)/LDUR 64-bit
    LDURB_IMM_REG: //Load/store register (unscaled immediate)/LDURB -
    LDURH_IMM_REG: //Load/store register (unscaled immediate)/LDURH -
    LDURSB_IMM_REG_32: //Load/store register (unscaled immediate)/LDURSB 32-bit
    LDURSB_IMM_REG_64: //Load/store register (unscaled immediate)/LDURSB 64-bit
    LDURSH_IMM_REG_32: //Load/store register (unscaled immediate)/LDURSH 32-bit
    LDURSH_IMM_REG_64: //Load/store register (unscaled immediate)/LDURSH 64-bit
    LDURSW_IMM_REG: //Load/store register (unscaled immediate)/LDURSW -
    PRFUM_IMM_REG: //Load/store register (unscaled immediate)/PRFUM -
    STUR_IMM_REG_32: //Load/store register (unscaled immediate)/STUR 32-bit
    STUR_IMM_REG_64: //Load/store register (unscaled immediate)/STUR 64-bit
    STURB_IMM_REG: //Load/store register (unscaled immediate)/STURB -
    STURH_IMM_REG: //Load/store register (unscaled immediate)/STURH -
    LDR_IMM_REG_32: //Load/store register (unsigned immediate)/LDR (immediate) 32-bit
    LDR_IMM_REG_64: //Load/store register (unsigned immediate)/LDR (immediate) 64-bit
    LDRB_IMM_REG_OFF: //Load/store register (unsigned immediate)/LDRB (immediate) Unsigned offset
    LDRH_IMM_REG_OFF: //Load/store register (unsigned immediate)/LDRH (immediate) Unsigned offset
    LDRSB_IMM_REG_32: //Load/store register (unsigned immediate)/LDRSB (immediate) 32-bit
    LDRSB_IMM_REG_64: //Load/store register (unsigned immediate)/LDRSB (immediate) 64-bit
    LDRSH_IMM_REG_32: //Load/store register (unsigned immediate)/LDRSH (immediate) 32-bit
    LDRSH_IMM_REG_64: //Load/store register (unsigned immediate)/LDRSH (immediate) 64-bit
    LDRSW_IMM_REG_OFF: //Load/store register (unsigned immediate)/LDRSW (immediate) Unsigned offset
    PRFM_IMM_REG: //Load/store register (unsigned immediate)/PRFM (immediate) -
    STR_IMM_REG_32: //Load/store register (unsigned immediate)/STR (immediate) 32-bit
    STR_IMM_REG_64: //Load/store register (unsigned immediate)/STR (immediate) 64-bit
    STRB_IMM_REG_OFF: //Load/store register (unsigned immediate)/STRB (immediate) Unsigned offset
    STRH_IMM_REG_OFF: //Load/store register (unsigned immediate)/STRH (immediate) Unsigned offset
    LDP_REG_OFF_32: //Load/store register pair (offset)/LDP 32-bit
    LDP_REG_OFF_64: //Load/store register pair (offset)/LDP 64-bit
    LDPSW_REG_OFF: //Load/store register pair (offset)/LDPSW Signed offset
    STP_REG_OFF_32: //Load/store register pair (offset)/STP 32-bit
    STP_REG_OFF_64: //Load/store register pair (offset)/STP 64-bit
    LDP_REG_POST_32: //Load/store register pair (post-indexed)/LDP 32-bit
    LDP_REG_POST_64: //Load/store register pair (post-indexed)/LDP 64-bit
    LDPSW_REG_POST: //Load/store register pair (post-indexed)/LDPSW Post-index
    STP_REG_POST_32: //Load/store register pair (post-indexed)/STP 32-bit
    STP_REG_POST_64: //Load/store register pair (post-indexed)/STP 64-bit
    LDP_REG_PRE_32: //Load/store register pair (pre-indexed)/LDP 32-bit
    LDP_REG_PRE_64: //Load/store register pair (pre-indexed)/LDP 64-bit
    LDPSW_REG_PRE: //Load/store register pair (pre-indexed)/LDPSW Pre-index
    STP_REG_PRE_32: //Load/store register pair (pre-indexed)/STP 32-bit
    STP_REG_PRE_64: //Load/store register pair (pre-indexed)/STP 64-bit

// A64 Load/Store Exclusive...
    LDAR_32: //Load/store exclusive/LDAR 32-bit
    LDAR_64: //Load/store exclusive/LDAR 64-bit
    LDARB: //Load/store exclusive/LDARB -
    LDARH: //Load/store exclusive/LDARH -
    LDAXP_32: //Load/store exclusive/LDAXP 32-bit
    LDAXP_64: //Load/store exclusive/LDAXP 64-bit
    LDAXR_32: //Load/store exclusive/LDAXR 32-bit
    LDAXR_64: //Load/store exclusive/LDAXR 64-bit
    LDAXRB: //Load/store exclusive/LDAXRB -
    LDAXRH: //Load/store exclusive/LDAXRH -
    LDXP_32: //Load/store exclusive/LDXP 32-bit
    LDXP_64: //Load/store exclusive/LDXP 64-bit
    LDXR_32: //Load/store exclusive/LDXR 32-bit
    LDXR_64: //Load/store exclusive/LDXR 64-bit
    LDXRB: //Load/store exclusive/LDXRB -
    LDXRH: //Load/store exclusive/LDXRH -
    STLR_32: //Load/store exclusive/STLR 32-bit
    STLR_64: //Load/store exclusive/STLR 64-bit
    STLRB: //Load/store exclusive/STLRB -
    STLRH: //Load/store exclusive/STLRH -
    STLXP_32: //Load/store exclusive/STLXP 32-bit
    STLXP_64: //Load/store exclusive/STLXP 64-bit
    STLXR_32: //Load/store exclusive/STLXR 32-bit
    STLXR_64: //Load/store exclusive/STLXR 64-bit
    STLXRB: //Load/store exclusive/STLXRB -
    STLXRH: //Load/store exclusive/STLXRH -
    STXP_32: //Load/store exclusive/STXP 32-bit
    STXP_64: //Load/store exclusive/STXP 64-bit
    STXR_32: //Load/store exclusive/STXR 32-bit
    STXR_64: //Load/store exclusive/STXR 64-bit
    STXRB: //Load/store exclusive/STXRB -
    STXRH: //Load/store exclusive/STXRH -

// A64 Exception...
    BRK: //Exception generation/BRK -
    DCPS1: //Exception generation/DCPS1 -
    DCPS2: //Exception generation/DCPS2 -
    DCPS3: //Exception generation/DCPS3 -
    HLT: //Exception generation/HLT -
    HVC: //Exception generation/HVC -
    SMC: //Exception generation/SMC -
    SVC: //Exception generation/SVC -

// A64 System...
    CLREX: //System/CLREX -
    DMB: //System/DMB -
    DSB: //System/DSB -
    HINT: //System/HINT -
    ISB: //System/ISB -
    MRS: //System/MRS -
    MSR_IMM: //System/MSR (immediate) -
    MSR_REG: //System/MSR (register) -
    NOP: //System/NOP -
    SEV: //System/SEV -
    SEVL: //System/SEVL -
    SYS: //System/SYS -
    SYSL: //System/SYSL -
    WFE: //System/WFE -
    WFI: //System/WFI -
    YIELD: //System/YIELD -

// A64 SIMD...
    AESD: //Cryptographic AES/AESD -
    AESE: //Cryptographic AES/AESE -
    AESIMC: //Cryptographic AES/AESIMC -
    AESMC: //Cryptographic AES/AESMC -
    SHA1C_REG: //Cryptographic three-register SHA/SHA1C -
    SHA1M_REG: //Cryptographic three-register SHA/SHA1M -
    SHA1P_REG: //Cryptographic three-register SHA/SHA1P -
    SHA1SU0_REG: //Cryptographic three-register SHA/SHA1SU0 -
    SHA256H_REG: //Cryptographic three-register SHA/SHA256H -
    SHA256H2_REG: //Cryptographic three-register SHA/SHA256H2 -
    SHA256SU1_REG: //Cryptographic three-register SHA/SHA256SU1 -
    SHA1H_REG: //Cryptographic two-register SHA/SHA1H -
    SHA1SU1_REG: //Cryptographic two-register SHA/SHA1SU1 -
    SHA256SU0_REG: //Cryptographic two-register SHA/SHA256SU0 -

// A64 ASIMD...
    SIMD_ADDV: //Advanced SIMD across lanes/ADDV -
    SIMD_FMAXNMV: //Advanced SIMD across lanes/FMAXNMV -
    SIMD_FMAXV: //Advanced SIMD across lanes/FMAXV -
    SIMD_FMINNMV: //Advanced SIMD across lanes/FMINNMV -
    SIMD_FMINV: //Advanced SIMD across lanes/FMINV -
    SIMD_SADDLV: //Advanced SIMD across lanes/SADDLV -
    SIMD_SMAXV: //Advanced SIMD across lanes/SMAXV -
    SIMD_SMINV: //Advanced SIMD across lanes/SMINV -
    SIMD_UADDLV: //Advanced SIMD across lanes/UADDLV -
    SIMD_UMAXV: //Advanced SIMD across lanes/UMAXV -
    SIMD_UMINV: //Advanced SIMD across lanes/UMINV -
    SIMD_DUP_VEC_ELEM: //Advanced SIMD copy/DUP (element) Vector
    SIMD_DUP: //Advanced SIMD copy/DUP (general) -
    SIMD_INS_ELEM: //Advanced SIMD copy/INS (element) -
    SIMD_INS: //Advanced SIMD copy/INS (general) -
    SIMD_SMOV_32: //Advanced SIMD copy/SMOV 32-bit
    SIMD_SMOV_64: //Advanced SIMD copy/SMOV 64-bit
    SIMD_UMOV_32: //Advanced SIMD copy/UMOV 32-bit
    SIMD_UMOV_64: //Advanced SIMD copy/UMOV 64-bit
    SIMD_EXT: //Advanced SIMD extract/EXT -
    SIMD_BIC_IMM_MOD_VEC_16: //Advanced SIMD modified immediate/BIC (vector, immediate) 16-bit
    SIMD_BIC_IMM_MOD_VEC_32: //Advanced SIMD modified immediate/BIC (vector, immediate) 32-bit
    SIMD_FMOV_IMM_MOD_VEC_FROM_DP: //Advanced SIMD modified immediate/FMOV (vector, immediate) Double-precision
    SIMD_FMOV_IMM_MOD_SINGLE_VEC_FROM_SP: //Advanced SIMD modified immediate/FMOV (vector, immediate) Single-precision
    SIMD_MOVI_SHIFT_IMM_MOD_16: //Advanced SIMD modified immediate/MOVI 16-bit shifted immediate
    SIMD_MOVI_SHIFT_IMM_MOD_32: //Advanced SIMD modified immediate/MOVI 32-bit shifted immediate
    SIMD_MOVI_SHIFT_IMM_ONES_MOD_32: //Advanced SIMD modified immediate/MOVI 32-bit shifting ones
    SIMD_MOVI_IMM_MOD_64: //Advanced SIMD modified immediate/MOVI 64-bit scalar
    SIMD_MOVI_IMM_MOD_VEC_64: //Advanced SIMD modified immediate/MOVI 64-bit vector
    SIMD_MOVI_IMM_MOD_8: //Advanced SIMD modified immediate/MOVI 8-bit
    SIMD_MVNI_SHIFT_IMM_MOD_16: //Advanced SIMD modified immediate/MVNI 16-bit shifted immediate
    SIMD_MVNI_SHIFT_IMM_MOD_32: //Advanced SIMD modified immediate/MVNI 32-bit shifted immediate
    SIMD_MVNI_SHIFT_IMM_ONES_MOD_32: //Advanced SIMD modified immediate/MVNI 32-bit shifting ones
    SIMD_ORR_IMM_MOD_VEC_16: //Advanced SIMD modified immediate/ORR (vector, immediate) 16-bit
    SIMD_ORR_IMM_MOD_VEC_32: //Advanced SIMD modified immediate/ORR (vector, immediate) 32-bit
    SIMD_TRN1: //Advanced SIMD permute/TRN1 -
    SIMD_TRN2: //Advanced SIMD permute/TRN2 -
    SIMD_UZP1: //Advanced SIMD permute/UZP1 -
    SIMD_UZP2: //Advanced SIMD permute/UZP2 -
    SIMD_ZIP1: //Advanced SIMD permute/ZIP1 -
    SIMD_ZIP2: //Advanced SIMD permute/ZIP2 -
    SIMD_DUP_SCALAR_ELEM: //Advanced SIMD scalar copy/DUP (element) Scalar
    SIMD_ADDP: //Advanced SIMD scalar pairwise/ADDP (scalar) -
    SIMD_FADDP: //Advanced SIMD scalar pairwise/FADDP (scalar) -
    SIMD_FMAXNMP: //Advanced SIMD scalar pairwise/FMAXNMP (scalar) -
    SIMD_FMAXP: //Advanced SIMD scalar pairwise/FMAXP (scalar) -
    SIMD_FMINNMP: //Advanced SIMD scalar pairwise/FMINNMP (scalar) -
    SIMD_FMINP: //Advanced SIMD scalar pairwise/FMINP (scalar) -
    SIMD_FCVTZS_SHIFT_IMM_SCALAR_VEC_FIXED: //Advanced SIMD scalar shift by immediate/FCVTZS (vector, fixed-point) Scalar
    SIMD_FCVTZU_SHIFT_IMM_SCALAR_VEC_FIXED: //Advanced SIMD scalar shift by immediate/FCVTZU (vector, fixed-point) Scalar
    SIMD_SCVTF_SHIFT_IMM_SCALAR_VEC_FIXED: //Advanced SIMD scalar shift by immediate/SCVTF (vector, fixed-point) Scalar
    SIMD_SHL_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/SHL Scalar
    SIMD_SLI_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/SLI Scalar
    SIMD_SQRSHRN_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/SQRSHRN, SQRSHRN2 Scalar
    SIMD_SQRSHRUN_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/SQRSHRUN, SQRSHRUN2 Scalar
    SIMD_SQSHL_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/SQSHL (immediate) Scalar
    SIMD_SQSHLU_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/SQSHLU Scalar
    SIMD_SQSHRN_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/SQSHRN, SQSHRN2 Scalar
    SIMD_SQSHRUN_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/SQSHRUN, SQSHRUN2 Scalar
    SIMD_SRI_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/SRI Scalar
    SIMD_SRSHR_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/SRSHR Scalar
    SIMD_SRSRA_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/SRSRA Scalar
    SIMD_SSHR_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/SSHR Scalar
    SIMD_SSRA_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/SSRA Scalar
    SIMD_UCVTF_SHIFT_IMM_SCALAR_VEC_FIXED: //Advanced SIMD scalar shift by immediate/UCVTF (vector, fixed-point) Scalar
    SIMD_UQRSHRN_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/UQRSHRN, UQRSHRN2 Scalar
    SIMD_UQSHL_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/UQSHL (immediate) Scalar
    SIMD_UQSHRN_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/UQSHRN Scalar
    SIMD_URSHR_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/URSHR Scalar
    SIMD_URSRA_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/URSRA Scalar
    SIMD_USHR_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/USHR Scalar
    SIMD_USRA_SHIFT_IMM_SCALAR: //Advanced SIMD scalar shift by immediate/USRA Scalar
    SIMD_SQDMLAL_SCALAR_VEC: //Advanced SIMD scalar three different/SQDMLAL, SQDMLAL2 (vector) Scalar
    SIMD_SQDMLSL_SCALAR_VEC: //Advanced SIMD scalar three different/SQDMLSL, SQDMLSL2 (vector) Scalar
    SIMD_SQDMULL_SCALAR_VEC: //Advanced SIMD scalar three different/SQDMULL, SQDMULL2 (vector) Scalar
    SIMD_ADD_SCALAR_VEC: //Advanced SIMD scalar three same/ADD (vector) Scalar
    SIMD_CMEQ_REG_SCALAR: //Advanced SIMD scalar three same/CMEQ (register) Scalar
    SIMD_CMGE_REG_SCALAR: //Advanced SIMD scalar three same/CMGE (register) Scalar
    SIMD_CMGT_REG_SCALAR: //Advanced SIMD scalar three same/CMGT (register) Scalar
    SIMD_CMHI_REG_SCALAR: //Advanced SIMD scalar three same/CMHI (register) Scalar
    SIMD_CMHS_REG_SCALAR: //Advanced SIMD scalar three same/CMHS (register) Scalar
    SIMD_CMTST_SCALAR: //Advanced SIMD scalar three same/CMTST Scalar
    SIMD_FABD_SCALAR: //Advanced SIMD scalar three same/FABD Scalar
    SIMD_FACGE_SCALAR: //Advanced SIMD scalar three same/FACGE Scalar
    SIMD_FACGT_SCALAR: //Advanced SIMD scalar three same/FACGT Scalar
    SIMD_FCMEQ_REG_SCALAR: //Advanced SIMD scalar three same/FCMEQ (register) Scalar
    SIMD_FCMGE_REG_SCALAR: //Advanced SIMD scalar three same/FCMGE (register) Scalar
    SIMD_FCMGT_REG_SCALAR: //Advanced SIMD scalar three same/FCMGT (register) Scalar
    SIMD_FMULX_SCALAR: //Advanced SIMD scalar three same/FMULX Scalar
    SIMD_FRECPS_SCALAR: //Advanced SIMD scalar three same/FRECPS Scalar
    SIMD_FRSQRTS_SCALAR: //Advanced SIMD scalar three same/FRSQRTS Scalar
    SIMD_SQADD_SCALAR: //Advanced SIMD scalar three same/SQADD Scalar
    SIMD_SQDMULH_SCALAR_VEC: //Advanced SIMD scalar three same/SQDMULH (vector) Scalar
    SIMD_SQRDMULH_SCALAR_VEC: //Advanced SIMD scalar three same/SQRDMULH (vector) Scalar
    SIMD_SQRSHL_SCALAR: //Advanced SIMD scalar three same/SQRSHL Scalar
    SIMD_SQSHL_REG_SCALAR: //Advanced SIMD scalar three same/SQSHL (register) Scalar
    SIMD_SQSUB_SCALAR: //Advanced SIMD scalar three same/SQSUB Scalar
    SIMD_SRSHL_SCALAR: //Advanced SIMD scalar three same/SRSHL Scalar
    SIMD_SSHL_SCALAR: //Advanced SIMD scalar three same/SSHL Scalar
    SIMD_SUB_SCALAR_VEC: //Advanced SIMD scalar three same/SUB (vector) Scalar
    SIMD_UQADD_SCALAR: //Advanced SIMD scalar three same/UQADD Scalar
    SIMD_UQRSHL_SCALAR: //Advanced SIMD scalar three same/UQRSHL Scalar
    SIMD_UQSHL_REG_SCALAR: //Advanced SIMD scalar three same/UQSHL (register) Scalar
    SIMD_UQSUB_SCALAR: //Advanced SIMD scalar three same/UQSUB Scalar
    SIMD_URSHL_SCALAR: //Advanced SIMD scalar three same/URSHL Scalar
    SIMD_USHL_SCALAR: //Advanced SIMD scalar three same/USHL Scalar
    SIMD_ABS_REG_SCALAR: //Advanced SIMD scalar two-register miscellaneous/ABS Scalar
    SIMD_CMEQ_REG_SCALAR_ZERO: //Advanced SIMD scalar two-register miscellaneous/CMEQ (zero) Scalar
    SIMD_CMGE_REG_SCALAR_ZERO: //Advanced SIMD scalar two-register miscellaneous/CMGE (zero) Scalar
    SIMD_CMGT_REG_SCALAR_ZERO: //Advanced SIMD scalar two-register miscellaneous/CMGT (zero) Scalar
    SIMD_CMLE_REG_SCALAR_ZERO: //Advanced SIMD scalar two-register miscellaneous/CMLE (zero) Scalar
    SIMD_CMLT_REG_SCALAR_ZERO: //Advanced SIMD scalar two-register miscellaneous/CMLT (zero) Scalar
    SIMD_FCMEQ_REG_SCALAR_ZERO: //Advanced SIMD scalar two-register miscellaneous/FCMEQ (zero) Scalar
    SIMD_FCMGE_REG_SCALAR_ZERO: //Advanced SIMD scalar two-register miscellaneous/FCMGE (zero) Scalar
    SIMD_FCMGT_REG_SCALAR_ZERO: //Advanced SIMD scalar two-register miscellaneous/FCMGT (zero) Scalar
    SIMD_FCMLE_REG_SCALAR_ZERO: //Advanced SIMD scalar two-register miscellaneous/FCMLE (zero) Scalar
    SIMD_FCMLT_REG_SCALAR_ZERO: //Advanced SIMD scalar two-register miscellaneous/FCMLT (zero) Scalar
    SIMD_FCVTAS_REG_SCALAR_VEC: //Advanced SIMD scalar two-register miscellaneous/FCVTAS (vector) Scalar
    SIMD_FCVTAU_REG_SCALAR_VEC: //Advanced SIMD scalar two-register miscellaneous/FCVTAU (vector) Scalar
    SIMD_FCVTMS_REG_SCALAR_VEC: //Advanced SIMD scalar two-register miscellaneous/FCVTMS (vector) Scalar
    SIMD_FCVTMU_REG_SCALAR_VEC: //Advanced SIMD scalar two-register miscellaneous/FCVTMU (vector) Scalar
    SIMD_FCVTNS_REG_SCALAR_VEC: //Advanced SIMD scalar two-register miscellaneous/FCVTNS (vector) Scalar
    SIMD_FCVTNU_REG_SCALAR_VEC: //Advanced SIMD scalar two-register miscellaneous/FCVTNU (vector) Scalar
    SIMD_FCVTPS_REG_SCALAR_VEC: //Advanced SIMD scalar two-register miscellaneous/FCVTPS (vector) Scalar
    SIMD_FCVTPU_REG_SCALAR_VEC: //Advanced SIMD scalar two-register miscellaneous/FCVTPU (vector) Scalar
    SIMD_FCVTXN_REG_SCALAR: //Advanced SIMD scalar two-register miscellaneous/FCVTXN, FCVTXN2 Scalar
    SIMD_FCVTZS_REG_SCALAR_VEC: //Advanced SIMD scalar two-register miscellaneous/FCVTZS (vector, integer) Scalar
    SIMD_FCVTZU_REG_SCALAR_VEC: //Advanced SIMD scalar two-register miscellaneous/FCVTZU (vector, integer) Scalar
    SIMD_FRECPE_REG_SCALAR: //Advanced SIMD scalar two-register miscellaneous/FRECPE Scalar
    SIMD_FRECPX_REG: //Advanced SIMD scalar two-register miscellaneous/FRECPX -
    SIMD_FRSQRTE_REG_SCALAR: //Advanced SIMD scalar two-register miscellaneous/FRSQRTE Scalar
    SIMD_NEG_REG_SCALAR_VEC: //Advanced SIMD scalar two-register miscellaneous/NEG (vector) Scalar
    SIMD_SCVTF_REG_SCALAR_VEC: //Advanced SIMD scalar two-register miscellaneous/SCVTF (vector, integer) Scalar
    SIMD_SQABS_REG_SCALAR: //Advanced SIMD scalar two-register miscellaneous/SQABS Scalar
    SIMD_SQNEG_REG_SCALAR: //Advanced SIMD scalar two-register miscellaneous/SQNEG Scalar
    SIMD_SQXTN_REG_SCALAR: //Advanced SIMD scalar two-register miscellaneous/SQXTN, SQXTN2 Scalar
    SIMD_SQXTUN_REG_SCALAR: //Advanced SIMD scalar two-register miscellaneous/SQXTUN, SQXTUN2 Scalar
    SIMD_SUQADD_REG_SCALAR: //Advanced SIMD scalar two-register miscellaneous/SUQADD Scalar
    SIMD_UCVTF_REG_SCALAR_VEC: //Advanced SIMD scalar two-register miscellaneous/UCVTF (vector, integer) Scalar
    SIMD_UQXTN_REG_SCALAR: //Advanced SIMD scalar two-register miscellaneous/UQXTN, UQXTN2 Scalar
    SIMD_USQADD_REG_SCALAR: //Advanced SIMD scalar two-register miscellaneous/USQADD Scalar
    SIMD_FMLA_SCALAR_ELEM: //Advanced SIMD scalar x indexed element/FMLA (by element) Scalar
    SIMD_FMLS_SCALAR_ELEM: //Advanced SIMD scalar x indexed element/FMLS (by element) Scalar
    SIMD_FMUL_SCALAR_ELEM: //Advanced SIMD scalar x indexed element/FMUL (by element) Scalar
    SIMD_FMULX_SCALAR_ELEM: //Advanced SIMD scalar x indexed element/FMULX (by element) Scalar
    SIMD_SQDMLAL_SCALAR_ELEM: //Advanced SIMD scalar x indexed element/SQDMLAL, SQDMLAL2 (by element) Scalar
    SIMD_SQDMLSL_SCALAR_ELEM: //Advanced SIMD scalar x indexed element/SQDMLSL, SQDMLSL2 (by element) Scalar
    SIMD_SQDMULH_SCALAR_ELEM: //Advanced SIMD scalar x indexed element/SQDMULH (by element) Scalar
    SIMD_SQDMULL_SCALAR_ELEM: //Advanced SIMD scalar x indexed element/SQDMULL, SQDMULL2 (by element) Scalar
    SIMD_SQRDMULH_SCALAR_ELEM: //Advanced SIMD scalar x indexed element/SQRDMULH (by element) Scalar
    SIMD_FCVTZS_SHIFT_IMM_VEC_VEC_FIXED: //Advanced SIMD shift by immediate/FCVTZS (vector, fixed-point) Vector
    SIMD_FCVTZU_SHIFT_IMM_VEC_VEC_FIXED: //Advanced SIMD shift by immediate/FCVTZU (vector, fixed-point) Vector
    SIMD_RSHRN_SHIFT_IMM: //Advanced SIMD shift by immediate/RSHRN, RSHRN2 -
    SIMD_SCVTF_SHIFT_IMM_VEC_VEC_FIXED: //Advanced SIMD shift by immediate/SCVTF (vector, fixed-point) Vector
    SIMD_SHL_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/SHL Vector
    SIMD_SHRN_SHIFT_IMM: //Advanced SIMD shift by immediate/SHRN, SHRN2 -
    SIMD_SLI_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/SLI Vector
    SIMD_SQRSHRN_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/SQRSHRN, SQRSHRN2 Vector
    SIMD_SQRSHRUN_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/SQRSHRUN, SQRSHRUN2 Vector
    SIMD_SQSHL_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/SQSHL (immediate) Vector
    SIMD_SQSHLU_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/SQSHLU Vector
    SIMD_SQSHRN_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/SQSHRN, SQSHRN2 Vector
    SIMD_SQSHRUN_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/SQSHRUN, SQSHRUN2 Vector
    SIMD_SRI_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/SRI Vector
    SIMD_SRSHR_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/SRSHR Vector
    SIMD_SRSRA_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/SRSRA Vector
    SIMD_SSHLL_SHIFT_IMM: //Advanced SIMD shift by immediate/SSHLL, SSHLL2 -
    SIMD_SSHR_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/SSHR Vector
    SIMD_SSRA_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/SSRA Vector
    SIMD_UCVTF_SHIFT_IMM_VEC_VEC_FIXED: //Advanced SIMD shift by immediate/UCVTF (vector, fixed-point) Vector
    SIMD_UQRSHRN_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/UQRSHRN, UQRSHRN2 Vector
    SIMD_UQSHL_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/UQSHL (immediate) Vector
    SIMD_UQSHRN_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/UQSHRN Vector
    SIMD_URSHR_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/URSHR Vector
    SIMD_URSRA_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/URSRA Vector
    SIMD_USHLL_SHIFT_IMM: //Advanced SIMD shift by immediate/USHLL, USHLL2 -
    SIMD_USHR_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/USHR Vector
    SIMD_USRA_SHIFT_IMM_VEC: //Advanced SIMD shift by immediate/USRA Vector
    SIMD_TBL_FOUR_REG: //Advanced SIMD table lookup/TBL Four register table
    SIMD_TBL_SINGLE_REG: //Advanced SIMD table lookup/TBL Single register table
    SIMD_TBL_THREE_REG: //Advanced SIMD table lookup/TBL Three register table
    SIMD_TBL_TWO_REG: //Advanced SIMD table lookup/TBL Two register table
    SIMD_TBX_FOUR_REG: //Advanced SIMD table lookup/TBX Four register table
    SIMD_TBX_SINGLE_REG: //Advanced SIMD table lookup/TBX Single register table
    SIMD_TBX_THREE_REG: //Advanced SIMD table lookup/TBX Three register table
    SIMD_TBX_TWO_REG: //Advanced SIMD table lookup/TBX Two register table
    SIMD_ADDHN: //Advanced SIMD three different/ADDHN, ADDHN2 -
    SIMD_PMULL: //Advanced SIMD three different/PMULL, PMULL2 -
    SIMD_RADDHN: //Advanced SIMD three different/RADDHN, RADDHN2 -
    SIMD_RSUBHN: //Advanced SIMD three different/RSUBHN, RSUBHN2 -
    SIMD_SABAL: //Advanced SIMD three different/SABAL, SABAL2 -
    SIMD_SABDL: //Advanced SIMD three different/SABDL, SABDL2 -
    SIMD_SADDL: //Advanced SIMD three different/SADDL, SADDL2 -
    SIMD_SADDW: //Advanced SIMD three different/SADDW, SADDW2 -
    SIMD_SMLAL_VEC: //Advanced SIMD three different/SMLAL, SMLAL2 (vector) -
    SIMD_SMLSL_VEC: //Advanced SIMD three different/SMLSL, SMLSL2 (vector) -
    SIMD_SMULL_VEC: //Advanced SIMD three different/SMULL, SMULL2 (vector) -
    SIMD_SQDMLAL_VEC_VEC: //Advanced SIMD three different/SQDMLAL, SQDMLAL2 (vector) Vector
    SIMD_SQDMLSL_VEC_VEC: //Advanced SIMD three different/SQDMLSL, SQDMLSL2 (vector) Vector
    SIMD_SQDMULL_VEC_VEC: //Advanced SIMD three different/SQDMULL, SQDMULL2 (vector) Vector
    SIMD_SSUBL: //Advanced SIMD three different/SSUBL, SSUBL2 -
    SIMD_SSUBW: //Advanced SIMD three different/SSUBW, SSUBW2 -
    SIMD_SUBHN: //Advanced SIMD three different/SUBHN, SUBHN2 -
    SIMD_UABAL: //Advanced SIMD three different/UABAL, UABAL2 -
    SIMD_UABDL: //Advanced SIMD three different/UABDL, UABDL2 -
    SIMD_UADDL: //Advanced SIMD three different/UADDL, UADDL2 -
    SIMD_UADDW: //Advanced SIMD three different/UADDW, UADDW2 -
    SIMD_UMLAL_VEC: //Advanced SIMD three different/UMLAL, UMLAL2 (vector) -
    SIMD_UMLSL_VEC: //Advanced SIMD three different/UMLSL, UMLSL2 (vector) -
    SIMD_UMULL_VEC: //Advanced SIMD three different/UMULL, UMULL2 (vector) -
    SIMD_USUBL: //Advanced SIMD three different/USUBL, USUBL2 -
    SIMD_USUBW: //Advanced SIMD three different/USUBW, USUBW2 -
    SIMD_ADD_VEC_VEC: //Advanced SIMD three same/ADD (vector) Vector
    SIMD_ADDP_VEC: //Advanced SIMD three same/ADDP (vector) -
    SIMD_AND_VEC: //Advanced SIMD three same/AND (vector) -
    SIMD_BIC_REG_VEC: //Advanced SIMD three same/BIC (vector, register) -
    SIMD_BIF: //Advanced SIMD three same/BIF -
    SIMD_BIT: //Advanced SIMD three same/BIT -
    SIMD_BSL: //Advanced SIMD three same/BSL -
    SIMD_CMEQ_REG_VEC: //Advanced SIMD three same/CMEQ (register) Vector
    SIMD_CMGE_REG_VEC: //Advanced SIMD three same/CMGE (register) Vector
    SIMD_CMGT_REG_VEC: //Advanced SIMD three same/CMGT (register) Vector
    SIMD_CMHI_REG_VEC: //Advanced SIMD three same/CMHI (register) Vector
    SIMD_CMHS_REG_VEC: //Advanced SIMD three same/CMHS (register) Vector
    SIMD_CMTST_VEC: //Advanced SIMD three same/CMTST Vector
    SIMD_EOR_VEC: //Advanced SIMD three same/EOR (vector) -
    SIMD_FABD_VEC: //Advanced SIMD three same/FABD Vector
    SIMD_FACGE_VEC: //Advanced SIMD three same/FACGE Vector
    SIMD_FACGT_VEC: //Advanced SIMD three same/FACGT Vector
    SIMD_FADD_VEC: //Advanced SIMD three same/FADD (vector) -
    SIMD_FADDP_VEC: //Advanced SIMD three same/FADDP (vector) -
    SIMD_FCMEQ_REG_VEC: //Advanced SIMD three same/FCMEQ (register) Vector
    SIMD_FCMGE_REG_VEC: //Advanced SIMD three same/FCMGE (register) Vector
    SIMD_FCMGT_REG_VEC: //Advanced SIMD three same/FCMGT (register) Vector
    SIMD_FDIV_VEC: //Advanced SIMD three same/FDIV (vector) -
    SIMD_FMAX_VEC: //Advanced SIMD three same/FMAX (vector) -
    SIMD_FMAXNM_VEC: //Advanced SIMD three same/FMAXNM (vector) -
    SIMD_FMAXNMP_VEC: //Advanced SIMD three same/FMAXNMP (vector) -
    SIMD_FMAXP_VEC: //Advanced SIMD three same/FMAXP (vector) -
    SIMD_FMIN_VEC: //Advanced SIMD three same/FMIN (vector) -
    SIMD_FMINNM_VEC: //Advanced SIMD three same/FMINNM (vector) -
    SIMD_FMINNMP_VEC: //Advanced SIMD three same/FMINNMP (vector) -
    SIMD_FMINP_VEC: //Advanced SIMD three same/FMINP (vector) -
    SIMD_FMLA_VEC: //Advanced SIMD three same/FMLA (vector) -
    SIMD_FMLS_VEC: //Advanced SIMD three same/FMLS (vector) -
    SIMD_FMUL_VEC: //Advanced SIMD three same/FMUL (vector) -
    SIMD_FMULX_VEC: //Advanced SIMD three same/FMULX Vector
    SIMD_FRECPS_VEC: //Advanced SIMD three same/FRECPS Vector
    SIMD_FRSQRTS_VEC: //Advanced SIMD three same/FRSQRTS Vector
    SIMD_FSUB_VEC: //Advanced SIMD three same/FSUB (vector) -
    SIMD_MLA_VEC: //Advanced SIMD three same/MLA (vector) -
    SIMD_MLS_VEC: //Advanced SIMD three same/MLS (vector) -
    SIMD_MUL_VEC: //Advanced SIMD three same/MUL (vector) -
    SIMD_ORN_VEC: //Advanced SIMD three same/ORN (vector) -
    SIMD_ORR_REG_VEC: //Advanced SIMD three same/ORR (vector, register) -
    SIMD_PMUL: //Advanced SIMD three same/PMUL -
    SIMD_SABA: //Advanced SIMD three same/SABA -
    SIMD_SABD: //Advanced SIMD three same/SABD -
    SIMD_SHADD: //Advanced SIMD three same/SHADD -
    SIMD_SHSUB: //Advanced SIMD three same/SHSUB -
    SIMD_SMAX: //Advanced SIMD three same/SMAX -
    SIMD_SMAXP: //Advanced SIMD three same/SMAXP -
    SIMD_SMIN: //Advanced SIMD three same/SMIN -
    SIMD_SMINP: //Advanced SIMD three same/SMINP -
    SIMD_SQADD_VEC: //Advanced SIMD three same/SQADD Vector
    SIMD_SQDMULH_VEC_VEC: //Advanced SIMD three same/SQDMULH (vector) Vector
    SIMD_SQRDMULH_VEC_VEC: //Advanced SIMD three same/SQRDMULH (vector) Vector
    SIMD_SQRSHL_VEC: //Advanced SIMD three same/SQRSHL Vector
    SIMD_SQSHL_REG_VEC: //Advanced SIMD three same/SQSHL (register) Vector
    SIMD_SQSUB_VEC: //Advanced SIMD three same/SQSUB Vector
    SIMD_SRHADD: //Advanced SIMD three same/SRHADD -
    SIMD_SRSHL_VEC: //Advanced SIMD three same/SRSHL Vector
    SIMD_SSHL_VEC: //Advanced SIMD three same/SSHL Vector
    SIMD_SUB_VEC_VEC: //Advanced SIMD three same/SUB (vector) Vector
    SIMD_UABA: //Advanced SIMD three same/UABA -
    SIMD_UABD: //Advanced SIMD three same/UABD -
    SIMD_UHADD: //Advanced SIMD three same/UHADD -
    SIMD_UHSUB: //Advanced SIMD three same/UHSUB -
    SIMD_UMAX: //Advanced SIMD three same/UMAX -
    SIMD_UMAXP: //Advanced SIMD three same/UMAXP -
    SIMD_UMIN: //Advanced SIMD three same/UMIN -
    SIMD_UMINP: //Advanced SIMD three same/UMINP -
    SIMD_UQADD_VEC: //Advanced SIMD three same/UQADD Vector
    SIMD_UQRSHL_VEC: //Advanced SIMD three same/UQRSHL Vector
    SIMD_UQSHL_REG_VEC: //Advanced SIMD three same/UQSHL (register) Vector
    SIMD_UQSUB_VEC: //Advanced SIMD three same/UQSUB Vector
    SIMD_URHADD: //Advanced SIMD three same/URHADD -
    SIMD_URSHL_VEC: //Advanced SIMD three same/URSHL Vector
    SIMD_USHL_VEC: //Advanced SIMD three same/USHL Vector
    SIMD_ABS_REG_VEC: //Advanced SIMD two-register miscellaneous/ABS Vector
    SIMD_CLS_REG_VEC: //Advanced SIMD two-register miscellaneous/CLS (vector) -
    SIMD_CLZ_REG_VEC: //Advanced SIMD two-register miscellaneous/CLZ (vector) -
    SIMD_CMEQ_REG_VEC_ZERO: //Advanced SIMD two-register miscellaneous/CMEQ (zero) Vector
    SIMD_CMGE_REG_VEC_ZERO: //Advanced SIMD two-register miscellaneous/CMGE (zero) Vector
    SIMD_CMGT_REG_VEC_ZERO: //Advanced SIMD two-register miscellaneous/CMGT (zero) Vector
    SIMD_CMLE_REG_VEC_ZERO: //Advanced SIMD two-register miscellaneous/CMLE (zero) Vector
    SIMD_CMLT_REG_VEC_ZERO: //Advanced SIMD two-register miscellaneous/CMLT (zero) Vector
    SIMD_CNT_REG: //Advanced SIMD two-register miscellaneous/CNT -
    SIMD_FABS_REG_VEC: //Advanced SIMD two-register miscellaneous/FABS (vector) -
    SIMD_FCMEQ_REG_VEC_ZERO: //Advanced SIMD two-register miscellaneous/FCMEQ (zero) Vector
    SIMD_FCMGE_REG_VEC_ZERO: //Advanced SIMD two-register miscellaneous/FCMGE (zero) Vector
    SIMD_FCMGT_REG_VEC_ZERO: //Advanced SIMD two-register miscellaneous/FCMGT (zero) Vector
    SIMD_FCMLE_REG_VEC_ZERO: //Advanced SIMD two-register miscellaneous/FCMLE (zero) Vector
    SIMD_FCMLT_REG_VEC_ZERO: //Advanced SIMD two-register miscellaneous/FCMLT (zero) Vector
    SIMD_FCVTAS_REG_VEC_VEC: //Advanced SIMD two-register miscellaneous/FCVTAS (vector) Vector
    SIMD_FCVTAU_REG_VEC_VEC: //Advanced SIMD two-register miscellaneous/FCVTAU (vector) Vector
    SIMD_FCVTL_REG: //Advanced SIMD two-register miscellaneous/FCVTL, FCVTL2 -
    SIMD_FCVTMS_REG_VEC_VEC: //Advanced SIMD two-register miscellaneous/FCVTMS (vector) Vector
    SIMD_FCVTMU_REG_VEC_VEC: //Advanced SIMD two-register miscellaneous/FCVTMU (vector) Vector
    SIMD_FCVTN_REG: //Advanced SIMD two-register miscellaneous/FCVTN, FCVTN2 -
    SIMD_FCVTNS_REG_VEC_VEC: //Advanced SIMD two-register miscellaneous/FCVTNS (vector) Vector
    SIMD_FCVTNU_REG_VEC_VEC: //Advanced SIMD two-register miscellaneous/FCVTNU (vector) Vector
    SIMD_FCVTPS_REG_VEC_VEC: //Advanced SIMD two-register miscellaneous/FCVTPS (vector) Vector
    SIMD_FCVTPU_REG_VEC_VEC: //Advanced SIMD two-register miscellaneous/FCVTPU (vector) Vector
    SIMD_FCVTXN_REG_VEC: //Advanced SIMD two-register miscellaneous/FCVTXN, FCVTXN2 Vector
    SIMD_FCVTZS_REG_VEC_VEC: //Advanced SIMD two-register miscellaneous/FCVTZS (vector, integer) Vector
    SIMD_FCVTZU_REG_VEC_VEC: //Advanced SIMD two-register miscellaneous/FCVTZU (vector, integer) Vector
    SIMD_FNEG_REG_VEC: //Advanced SIMD two-register miscellaneous/FNEG (vector) -
    SIMD_FRECPE_REG_VEC: //Advanced SIMD two-register miscellaneous/FRECPE Vector
    SIMD_FRINTA_REG_VEC: //Advanced SIMD two-register miscellaneous/FRINTA (vector) -
    SIMD_FRINTI_REG_VEC: //Advanced SIMD two-register miscellaneous/FRINTI (vector) -
    SIMD_FRINTM_REG_VEC: //Advanced SIMD two-register miscellaneous/FRINTM (vector) -
    SIMD_FRINTN_REG_VEC: //Advanced SIMD two-register miscellaneous/FRINTN (vector) -
    SIMD_FRINTP_REG_VEC: //Advanced SIMD two-register miscellaneous/FRINTP (vector) -
    SIMD_FRINTX_REG_VEC: //Advanced SIMD two-register miscellaneous/FRINTX (vector) -
    SIMD_FRINTZ_REG_VEC: //Advanced SIMD two-register miscellaneous/FRINTZ (vector) -
    SIMD_FRSQRTE_REG_VEC: //Advanced SIMD two-register miscellaneous/FRSQRTE Vector
    SIMD_FSQRT_REG_VEC: //Advanced SIMD two-register miscellaneous/FSQRT (vector) -
    SIMD_NEG_REG_VEC_VEC: //Advanced SIMD two-register miscellaneous/NEG (vector) Vector
    SIMD_NOT_REG: //Advanced SIMD two-register miscellaneous/NOT -
    SIMD_RBIT_REG_VEC: //Advanced SIMD two-register miscellaneous/RBIT (vector) -
    SIMD_REV16_REG_VEC: //Advanced SIMD two-register miscellaneous/REV16 (vector) -
    SIMD_REV32_REG_VEC: //Advanced SIMD two-register miscellaneous/REV32 (vector) -
    SIMD_REV64_REG: //Advanced SIMD two-register miscellaneous/REV64 -
    SIMD_SADALP_REG: //Advanced SIMD two-register miscellaneous/SADALP -
    SIMD_SADDLP_REG: //Advanced SIMD two-register miscellaneous/SADDLP -
    SIMD_SCVTF_REG_VEC_VEC: //Advanced SIMD two-register miscellaneous/SCVTF (vector, integer) Vector
    SIMD_SHLL_REG: //Advanced SIMD two-register miscellaneous/SHLL, SHLL2 -
    SIMD_SQABS_REG_VEC: //Advanced SIMD two-register miscellaneous/SQABS Vector
    SIMD_SQNEG_REG_VEC: //Advanced SIMD two-register miscellaneous/SQNEG Vector
    SIMD_SQXTN_REG_VEC: //Advanced SIMD two-register miscellaneous/SQXTN, SQXTN2 Vector
    SIMD_SQXTUN_REG_VEC: //Advanced SIMD two-register miscellaneous/SQXTUN, SQXTUN2 Vector
    SIMD_SUQADD_REG_VEC: //Advanced SIMD two-register miscellaneous/SUQADD Vector
    SIMD_UADALP_REG: //Advanced SIMD two-register miscellaneous/UADALP -
    SIMD_UADDLP_REG: //Advanced SIMD two-register miscellaneous/UADDLP -
    SIMD_UCVTF_REG_VEC_VEC: //Advanced SIMD two-register miscellaneous/UCVTF (vector, integer) Vector
    SIMD_UQXTN_REG_VEC: //Advanced SIMD two-register miscellaneous/UQXTN, UQXTN2 Vector
    SIMD_URECPE_REG: //Advanced SIMD two-register miscellaneous/URECPE -
    SIMD_URSQRTE_REG: //Advanced SIMD two-register miscellaneous/URSQRTE -
    SIMD_USQADD_REG_VEC: //Advanced SIMD two-register miscellaneous/USQADD Vector
    SIMD_XTN_REG: //Advanced SIMD two-register miscellaneous/XTN, XTN2 -
    SIMD_FMLA_VEC_VEC_ELEM: //Advanced SIMD vector x indexed element/FMLA (by element) Vector
    SIMD_FMLS_VEC_VEC_ELEM: //Advanced SIMD vector x indexed element/FMLS (by element) Vector
    SIMD_FMUL_VEC_VEC_ELEM: //Advanced SIMD vector x indexed element/FMUL (by element) Vector
    SIMD_FMULX_VEC_VEC_ELEM: //Advanced SIMD vector x indexed element/FMULX (by element) Vector
    SIMD_MLA_VEC_ELEM: //Advanced SIMD vector x indexed element/MLA (by element) -
    SIMD_MLS_VEC_ELEM: //Advanced SIMD vector x indexed element/MLS (by element) -
    SIMD_MUL_VEC_ELEM: //Advanced SIMD vector x indexed element/MUL (by element) -
    SIMD_SMLAL_VEC_ELEM: //Advanced SIMD vector x indexed element/SMLAL, SMLAL2 (by element) -
    SIMD_SMLSL_VEC_ELEM: //Advanced SIMD vector x indexed element/SMLSL, SMLSL2 (by element) -
    SIMD_SMULL_VEC_ELEM: //Advanced SIMD vector x indexed element/SMULL, SMULL2 (by element) -
    SIMD_SQDMLAL_VEC_VEC_ELEM: //Advanced SIMD vector x indexed element/SQDMLAL, SQDMLAL2 (by element) Vector
    SIMD_SQDMLSL_VEC_VEC_ELEM: //Advanced SIMD vector x indexed element/SQDMLSL, SQDMLSL2 (by element) Vector
    SIMD_SQDMULH_VEC_VEC_ELEM: //Advanced SIMD vector x indexed element/SQDMULH (by element) Vector
    SIMD_SQDMULL_VEC_VEC_ELEM: //Advanced SIMD vector x indexed element/SQDMULL, SQDMULL2 (by element) Vector
    SIMD_SQRDMULH_VEC_VEC_ELEM: //Advanced SIMD vector x indexed element/SQRDMULH (by element) Vector
    SIMD_UMLAL_VEC_ELEM: //Advanced SIMD vector x indexed element/UMLAL, UMLAL2 (by element) -
    SIMD_UMLSL_VEC_ELEM: //Advanced SIMD vector x indexed element/UMLSL, UMLSL2 (by element) -
    SIMD_UMULL_VEC_ELEM: //Advanced SIMD vector x indexed element/UMULL, UMULL2 (by element) -

// Advanced SIMD load/store...
    SIMD_LD1_IMM_FOUR_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) Four registers, immediate offset
    SIMD_LD1_FOUR_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) Four registers, register offset
    SIMD_LD1_IMM_ONE_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) One register, immediate offset
    SIMD_LD1_ONE_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) One register, register offset
    SIMD_LD1_IMM_THREE_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) Three registers, immediate offset
    SIMD_LD1_THREE_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) Three registers, register offset
    SIMD_LD1_IMM_TWO_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) Two registers, immediate offset
    SIMD_LD1_TWO_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) Two registers, register offset
    SIMD_LD2_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/LD2 (multiple structures) Immediate offset
    SIMD_LD2_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/LD2 (multiple structures) Register offset
    SIMD_LD3_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/LD3 (multiple structures) Immediate offset
    SIMD_LD3_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/LD3 (multiple structures) Register offset
    SIMD_LD4_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/LD4 (multiple structures) Immediate offset
    SIMD_LD4_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/LD4 (multiple structures) Register offset
    SIMD_ST1_IMM_FOUR_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) Four registers, immediate offset
    SIMD_ST1_FOUR_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) Four registers, register offset
    SIMD_ST1_IMM_ONE_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) One register, immediate offset
    SIMD_ST1_ONE_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) One register, register offset
    SIMD_ST1_IMM_THREE_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) Three registers, immediate offset
    SIMD_ST1_THREE_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) Three registers, register offset
    SIMD_ST1_IMM_TWO_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) Two registers, immediate offset
    SIMD_ST1_TWO_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) Two registers, register offset
    SIMD_ST2_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/ST2 (multiple structures) Immediate offset
    SIMD_ST2_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/ST2 (multiple structures) Register offset
    SIMD_ST3_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/ST3 (multiple structures) Immediate offset
    SIMD_ST3_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/ST3 (multiple structures) Register offset
    SIMD_ST4_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/ST4 (multiple structures) Immediate offset
    SIMD_ST4_REG_OFF_MULT_POST_STRUCT: //Advanced SIMD load/store multiple structures (post-indexed)/ST4 (multiple structures) Register offset
    SIMD_LD1_FOUR_REG_MULT_STRUCT: //Advanced SIMD load/store multiple structures/LD1 (multiple structures) Four registers
    SIMD_LD1_ONE_REG_MULT_STRUCT: //Advanced SIMD load/store multiple structures/LD1 (multiple structures) One register
    SIMD_LD1_THREE_REG_MULT_STRUCT: //Advanced SIMD load/store multiple structures/LD1 (multiple structures) Three registers
    SIMD_LD1_TWO_REG_MULT_STRUCT: //Advanced SIMD load/store multiple structures/LD1 (multiple structures) Two registers
    SIMD_LD2_OFF_MULT_STRUCT: //Advanced SIMD load/store multiple structures/LD2 (multiple structures) No offset
    SIMD_LD3_OFF_MULT_STRUCT: //Advanced SIMD load/store multiple structures/LD3 (multiple structures) No offset
    SIMD_LD4_OFF_MULT_STRUCT: //Advanced SIMD load/store multiple structures/LD4 (multiple structures) No offset
    SIMD_ST1_FOUR_REG_MULT_STRUCT: //Advanced SIMD load/store multiple structures/ST1 (multiple structures) Four registers
    SIMD_ST1_ONE_REG_MULT_STRUCT: //Advanced SIMD load/store multiple structures/ST1 (multiple structures) One register
    SIMD_ST1_THREE_REG_MULT_STRUCT: //Advanced SIMD load/store multiple structures/ST1 (multiple structures) Three registers
    SIMD_ST1_TWO_REG_MULT_STRUCT: //Advanced SIMD load/store multiple structures/ST1 (multiple structures) Two registers
    SIMD_ST2_OFF_MULT_STRUCT: //Advanced SIMD load/store multiple structures/ST2 (multiple structures) No offset
    SIMD_ST3_OFF_MULT_STRUCT: //Advanced SIMD load/store multiple structures/ST3 (multiple structures) No offset
    SIMD_ST4_OFF_MULT_STRUCT: //Advanced SIMD load/store multiple structures/ST4 (multiple structures) No offset
    SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_16: //Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 16-bit, immediate offset
    SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_16: //Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 16-bit, register offset
    SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_32: //Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 32-bit, immediate offset
    SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_32: //Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 32-bit, register offset
    SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_64: //Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 64-bit, immediate offset
    SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_64: //Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 64-bit, register offset
    SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_8: //Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 8-bit, immediate offset
    SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_8: //Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 8-bit, register offset
    SIMD_LD1R_OFF_SINGLE_POST_STRUCT: //Advanced SIMD load/store single structure (post-indexed)/LD1R Immediate offset
    SIMD_LD1R_REG_OFF_SINGLE_POST_STRUCT: //Advanced SIMD load/store single structure (post-indexed)/LD1R Register offset
    SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_16: //Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 16-bit, immediate offset
    SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_16: //Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 16-bit, register offset
    SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_32: //Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 32-bit, immediate offset
    SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_32: //Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 32-bit, register offset
    SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_64: //Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 64-bit, immediate offset
    SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_64: //Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 64-bit, register offset
    SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_8: //Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 8-bit, immediate offset
    SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_8: //Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 8-bit, register offset
    SIMD_LD2R_OFF_SINGLE_POST_STRUCT: //Advanced SIMD load/store single structure (post-indexed)/LD2R Immediate offset
    SIMD_LD2R_REG_OFF_SINGLE_POST_STRUCT: //Advanced SIMD load/store single structure (post-indexed)/LD2R Register offset
    SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_16: //Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 16-bit, immediate offset
    SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_16: //Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 16-bit, register offset
    SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_32: //Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 32-bit, immediate offset
    SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_32: //Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 32-bit, register offset
    SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_64: //Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 64-bit, immediate offset
    SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_64: //Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 64-bit, register offset
    SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_8: //Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 8-bit, immediate offset
    SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_8: //Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 8-bit, register offset
    SIMD_LD3R_OFF_SINGLE_POST_STRUCT: //Advanced SIMD load/store single structure (post-indexed)/LD3R Immediate offset
    SIMD_LD3R_REG_OFF_SINGLE_POST_STRUCT: //Advanced SIMD load/store single structure (post-indexed)/LD3R Register offset
    SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_16: //Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 16-bit, immediate offset
    SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_16: //Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 16-bit, register offset
    SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_32: //Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 32-bit, immediate offset
    SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_32: //Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 32-bit, register offset
    SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_64: //Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 64-bit, immediate offset
    SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_64: //Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 64-bit, register offset
    SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_8: //Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 8-bit, immediate offset
    SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_8: //Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 8-bit, register offset
    SIMD_LD4R_OFF_SINGLE_POST_STRUCT: //Advanced SIMD load/store single structure (post-indexed)/LD4R Immediate offset
    SIMD_LD4R_REG_OFF_SINGLE_POST_STRUCT: //Advanced SIMD load/store single structure (post-indexed)/LD4R Register offset
    SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_16: //Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 16-bit, immediate offset
    SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_16: //Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 16-bit, register offset
    SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_32: //Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 32-bit, immediate offset
    SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_32: //Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 32-bit, register offset
    SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_64: //Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 64-bit, immediate offset
    SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_64: //Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 64-bit, register offset
    SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_8: //Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 8-bit, immediate offset
    SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_8: //Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 8-bit, register offset
    SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_16: //Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 16-bit, immediate offset
    SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_16: //Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 16-bit, register offset
    SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_32: //Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 32-bit, immediate offset
    SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_32: //Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 32-bit, register offset
    SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_64: //Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 64-bit, immediate offset
    SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_64: //Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 64-bit, register offset
    SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_8: //Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 8-bit, immediate offset
    SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_8: //Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 8-bit, register offset
    SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_16: //Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 16-bit, immediate offset
    SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_16: //Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 16-bit, register offset
    SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_32: //Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 32-bit, immediate offset
    SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_32: //Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 32-bit, register offset
    SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_64: //Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 64-bit, immediate offset
    SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_64: //Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 64-bit, register offset
    SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_8: //Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 8-bit, immediate offset
    SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_8: //Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 8-bit, register offset
    SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_16: //Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 16-bit, immediate offset
    SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_16: //Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 16-bit, register offset
    SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_32: //Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 32-bit, immediate offset
    SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_32: //Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 32-bit, register offset
    SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_64: //Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 64-bit, immediate offset
    SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_64: //Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 64-bit, register offset
    SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_8: //Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 8-bit, immediate offset
    SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_8: //Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 8-bit, register offset
    SIMD_LD1_SINGLE_STRUCT_16: //Advanced SIMD load/store single structure/LD1 (single structure) 16-bit
    SIMD_LD1_SINGLE_STRUCT_32: //Advanced SIMD load/store single structure/LD1 (single structure) 32-bit
    SIMD_LD1_SINGLE_STRUCT_64: //Advanced SIMD load/store single structure/LD1 (single structure) 64-bit
    SIMD_LD1_SINGLE_STRUCT_8: //Advanced SIMD load/store single structure/LD1 (single structure) 8-bit
    SIMD_LD1R_OFF_SINGLE_STRUCT: //Advanced SIMD load/store single structure/LD1R No offset
    SIMD_LD2_SINGLE_STRUCT_16: //Advanced SIMD load/store single structure/LD2 (single structure) 16-bit
    SIMD_LD2_SINGLE_STRUCT_32: //Advanced SIMD load/store single structure/LD2 (single structure) 32-bit
    SIMD_LD2_SINGLE_STRUCT_64: //Advanced SIMD load/store single structure/LD2 (single structure) 64-bit
    SIMD_LD2_SINGLE_STRUCT_8: //Advanced SIMD load/store single structure/LD2 (single structure) 8-bit
    SIMD_LD2R_OFF_SINGLE_STRUCT: //Advanced SIMD load/store single structure/LD2R No offset
    SIMD_LD3_SINGLE_STRUCT_16: //Advanced SIMD load/store single structure/LD3 (single structure) 16-bit
    SIMD_LD3_SINGLE_STRUCT_32: //Advanced SIMD load/store single structure/LD3 (single structure) 32-bit
    SIMD_LD3_SINGLE_STRUCT_64: //Advanced SIMD load/store single structure/LD3 (single structure) 64-bit
    SIMD_LD3_SINGLE_STRUCT_8: //Advanced SIMD load/store single structure/LD3 (single structure) 8-bit
    SIMD_LD3R_OFF_SINGLE_STRUCT: //Advanced SIMD load/store single structure/LD3R No offset
    SIMD_LD4_SINGLE_STRUCT_16: //Advanced SIMD load/store single structure/LD4 (single structure) 16-bit
    SIMD_LD4_SINGLE_STRUCT_32: //Advanced SIMD load/store single structure/LD4 (single structure) 32-bit
    SIMD_LD4_SINGLE_STRUCT_64: //Advanced SIMD load/store single structure/LD4 (single structure) 64-bit
    SIMD_LD4_SINGLE_STRUCT_8: //Advanced SIMD load/store single structure/LD4 (single structure) 8-bit
    SIMD_LD4R_OFF_SINGLE_STRUCT: //Advanced SIMD load/store single structure/LD4R No offset
    SIMD_ST1_SINGLE_STRUCT_16: //Advanced SIMD load/store single structure/ST1 (single structure) 16-bit
    SIMD_ST1_SINGLE_STRUCT_32: //Advanced SIMD load/store single structure/ST1 (single structure) 32-bit
    SIMD_ST1_SINGLE_STRUCT_64: //Advanced SIMD load/store single structure/ST1 (single structure) 64-bit
    SIMD_ST1_SINGLE_STRUCT_8: //Advanced SIMD load/store single structure/ST1 (single structure) 8-bit
    SIMD_ST2_SINGLE_STRUCT_16: //Advanced SIMD load/store single structure/ST2 (single structure) 16-bit
    SIMD_ST2_SINGLE_STRUCT_32: //Advanced SIMD load/store single structure/ST2 (single structure) 32-bit
    SIMD_ST2_SINGLE_STRUCT_64: //Advanced SIMD load/store single structure/ST2 (single structure) 64-bit
    SIMD_ST2_SINGLE_STRUCT_8: //Advanced SIMD load/store single structure/ST2 (single structure) 8-bit
    SIMD_ST3_SINGLE_STRUCT_16: //Advanced SIMD load/store single structure/ST3 (single structure) 16-bit
    SIMD_ST3_SINGLE_STRUCT_32: //Advanced SIMD load/store single structure/ST3 (single structure) 32-bit
    SIMD_ST3_SINGLE_STRUCT_64: //Advanced SIMD load/store single structure/ST3 (single structure) 64-bit
    SIMD_ST3_SINGLE_STRUCT_8: //Advanced SIMD load/store single structure/ST3 (single structure) 8-bit
    SIMD_ST4_SINGLE_STRUCT_16: //Advanced SIMD load/store single structure/ST4 (single structure) 16-bit
    SIMD_ST4_SINGLE_STRUCT_32: //Advanced SIMD load/store single structure/ST4 (single structure) 32-bit
    SIMD_ST4_SINGLE_STRUCT_64: //Advanced SIMD load/store single structure/ST4 (single structure) 64-bit
    SIMD_ST4_SINGLE_STRUCT_8: //Advanced SIMD load/store single structure/ST4 (single structure) 8-bit

// A64 Floating point...
    FCVTZS_FROM_DP_FP_FIXED_32: //Conversions between floating-point and fixed-point/FCVTZS (scalar, fixed-point) Double-precision to 32-bit
    FCVTZS_FROM_DP_FP_FIXED_64: //Conversions between floating-point and fixed-point/FCVTZS (scalar, fixed-point) Double-precision to 64-bit
    FCVTZS_SINGLE_FROM_SP_FP_FIXED_32: //Conversions between floating-point and fixed-point/FCVTZS (scalar, fixed-point) Single-precision to 32-bit
    FCVTZS_SINGLE_FROM_SP_FP_FIXED_64: //Conversions between floating-point and fixed-point/FCVTZS (scalar, fixed-point) Single-precision to 64-bit
    FCVTZU_FROM_DP_FP_FIXED_32: //Conversions between floating-point and fixed-point/FCVTZU (scalar, fixed-point) Double-precision to 32-bit
    FCVTZU_FROM_DP_FP_FIXED_64: //Conversions between floating-point and fixed-point/FCVTZU (scalar, fixed-point) Double-precision to 64-bit
    FCVTZU_SINGLE_FROM_SP_FP_FIXED_32: //Conversions between floating-point and fixed-point/FCVTZU (scalar, fixed-point) Single-precision to 32-bit
    FCVTZU_SINGLE_FROM_SP_FP_FIXED_64: //Conversions between floating-point and fixed-point/FCVTZU (scalar, fixed-point) Single-precision to 64-bit
    SCVTF_TO_DP_FP_FIXED_32: //Conversions between floating-point and fixed-point/SCVTF (scalar, fixed-point) 32-bit to double-precision
    SCVTF_SINGLE_TO_SP_FP_FIXED_32: //Conversions between floating-point and fixed-point/SCVTF (scalar, fixed-point) 32-bit to single-precision
    SCVTF_TO_DP_FP_FIXED_64: //Conversions between floating-point and fixed-point/SCVTF (scalar, fixed-point) 64-bit to double-precision
    SCVTF_SINGLE_TO_SP_FP_FIXED_64: //Conversions between floating-point and fixed-point/SCVTF (scalar, fixed-point) 64-bit to single-precision
    UCVTF_TO_DP_FP_FIXED_32: //Conversions between floating-point and fixed-point/UCVTF (scalar, fixed-point) 32-bit to double-precision
    UCVTF_SINGLE_TO_SP_FP_FIXED_32: //Conversions between floating-point and fixed-point/UCVTF (scalar, fixed-point) 32-bit to single-precision
    UCVTF_TO_DP_FP_FIXED_64: //Conversions between floating-point and fixed-point/UCVTF (scalar, fixed-point) 64-bit to double-precision
    UCVTF_SINGLE_TO_SP_FP_FIXED_64: //Conversions between floating-point and fixed-point/UCVTF (scalar, fixed-point) 64-bit to single-precision
    FCVTAS_FROM_DP_FP_32: //Conversions between floating-point and integer/FCVTAS (scalar) Double-precision to 32-bit
    FCVTAS_FROM_DP_FP_64: //Conversions between floating-point and integer/FCVTAS (scalar) Double-precision to 64-bit
    FCVTAS_SINGLE_FROM_SP_FP_32: //Conversions between floating-point and integer/FCVTAS (scalar) Single-precision to 32-bit
    FCVTAS_SINGLE_FROM_SP_FP_64: //Conversions between floating-point and integer/FCVTAS (scalar) Single-precision to 64-bit
    FCVTAU_FROM_DP_FP_32: //Conversions between floating-point and integer/FCVTAU (scalar) Double-precision to 32-bit
    FCVTAU_FROM_DP_FP_64: //Conversions between floating-point and integer/FCVTAU (scalar) Double-precision to 64-bit
    FCVTAU_SINGLE_FROM_SP_FP_32: //Conversions between floating-point and integer/FCVTAU (scalar) Single-precision to 32-bit
    FCVTAU_SINGLE_FROM_SP_FP_64: //Conversions between floating-point and integer/FCVTAU (scalar) Single-precision to 64-bit
    FCVTMS_FROM_DP_FP_32: //Conversions between floating-point and integer/FCVTMS (scalar) Double-precision to 32-bit
    FCVTMS_FROM_DP_FP_64: //Conversions between floating-point and integer/FCVTMS (scalar) Double-precision to 64-bit
    FCVTMS_SINGLE_FROM_SP_FP_32: //Conversions between floating-point and integer/FCVTMS (scalar) Single-precision to 32-bit
    FCVTMS_SINGLE_FROM_SP_FP_64: //Conversions between floating-point and integer/FCVTMS (scalar) Single-precision to 64-bit
    FCVTMU_FROM_DP_FP_32: //Conversions between floating-point and integer/FCVTMU (scalar) Double-precision to 32-bit
    FCVTMU_FROM_DP_FP_64: //Conversions between floating-point and integer/FCVTMU (scalar) Double-precision to 64-bit
    FCVTMU_SINGLE_FROM_SP_FP_32: //Conversions between floating-point and integer/FCVTMU (scalar) Single-precision to 32-bit
    FCVTMU_SINGLE_FROM_SP_FP_64: //Conversions between floating-point and integer/FCVTMU (scalar) Single-precision to 64-bit
    FCVTNS_FROM_DP_FP_32: //Conversions between floating-point and integer/FCVTNS (scalar) Double-precision to 32-bit
    FCVTNS_FROM_DP_FP_64: //Conversions between floating-point and integer/FCVTNS (scalar) Double-precision to 64-bit
    FCVTNS_SINGLE_FROM_SP_FP_32: //Conversions between floating-point and integer/FCVTNS (scalar) Single-precision to 32-bit
    FCVTNS_SINGLE_FROM_SP_FP_64: //Conversions between floating-point and integer/FCVTNS (scalar) Single-precision to 64-bit
    FCVTNU_FROM_DP_FP_32: //Conversions between floating-point and integer/FCVTNU (scalar) Double-precision to 32-bit
    FCVTNU_FROM_DP_FP_64: //Conversions between floating-point and integer/FCVTNU (scalar) Double-precision to 64-bit
    FCVTNU_SINGLE_FROM_SP_FP_32: //Conversions between floating-point and integer/FCVTNU (scalar) Single-precision to 32-bit
    FCVTNU_SINGLE_FROM_SP_FP_64: //Conversions between floating-point and integer/FCVTNU (scalar) Single-precision to 64-bit
    FCVTPS_FROM_DP_FP_32: //Conversions between floating-point and integer/FCVTPS (scalar) Double-precision to 32-bit
    FCVTPS_FROM_DP_FP_64: //Conversions between floating-point and integer/FCVTPS (scalar) Double-precision to 64-bit
    FCVTPS_SINGLE_FROM_SP_FP_32: //Conversions between floating-point and integer/FCVTPS (scalar) Single-precision to 32-bit
    FCVTPS_SINGLE_FROM_SP_FP_64: //Conversions between floating-point and integer/FCVTPS (scalar) Single-precision to 64-bit
    FCVTPU_FROM_DP_FP_32: //Conversions between floating-point and integer/FCVTPU (scalar) Double-precision to 32-bit
    FCVTPU_FROM_DP_FP_64: //Conversions between floating-point and integer/FCVTPU (scalar) Double-precision to 64-bit
    FCVTPU_SINGLE_FROM_SP_FP_32: //Conversions between floating-point and integer/FCVTPU (scalar) Single-precision to 32-bit
    FCVTPU_SINGLE_FROM_SP_FP_64: //Conversions between floating-point and integer/FCVTPU (scalar) Single-precision to 64-bit
    FCVTZS_FROM_DP_FP_32: //Conversions between floating-point and integer/FCVTZS (scalar, integer) Double-precision to 32-bit
    FCVTZS_FROM_DP_FP_64: //Conversions between floating-point and integer/FCVTZS (scalar, integer) Double-precision to 64-bit
    FCVTZS_SINGLE_FROM_SP_FP_32: //Conversions between floating-point and integer/FCVTZS (scalar, integer) Single-precision to 32-bit
    FCVTZS_SINGLE_FROM_SP_FP_64: //Conversions between floating-point and integer/FCVTZS (scalar, integer) Single-precision to 64-bit
    FCVTZU_FROM_DP_FP_32: //Conversions between floating-point and integer/FCVTZU (scalar, integer) Double-precision to 32-bit
    FCVTZU_FROM_DP_FP_64: //Conversions between floating-point and integer/FCVTZU (scalar, integer) Double-precision to 64-bit
    FCVTZU_SINGLE_FROM_SP_FP_32: //Conversions between floating-point and integer/FCVTZU (scalar, integer) Single-precision to 32-bit
    FCVTZU_SINGLE_FROM_SP_FP_64: //Conversions between floating-point and integer/FCVTZU (scalar, integer) Single-precision to 64-bit
    FMOV_SINGLE_TO_SP_FP_32: //Conversions between floating-point and integer/FMOV (general) 32-bit to single-precision
    FMOV_TO_DP_FP_64: //Conversions between floating-point and integer/FMOV (general) 64-bit to double-precision
    FMOV_FP_8_64_128_TO_TOP: //Conversions between floating-point and integer/FMOV (general) 64-bit to top half of 128-bit
    FMOV_FROM_DP_FP_64: //Conversions between floating-point and integer/FMOV (general) Double-precision to 64-bit
    FMOV_SINGLE_FROM_SP_FP_32: //Conversions between floating-point and integer/FMOV (general) Single-precision to 32-bit
    FMOV_FP_8_64_128: //Conversions between floating-point and integer/FMOV (general) Top half of 128-bit to 64-bit
    SCVTF_TO_DP_FP_32: //Conversions between floating-point and integer/SCVTF (scalar, integer) 32-bit to double-precision
    SCVTF_SINGLE_TO_SP_FP_32: //Conversions between floating-point and integer/SCVTF (scalar, integer) 32-bit to single-precision
    SCVTF_TO_DP_FP_64: //Conversions between floating-point and integer/SCVTF (scalar, integer) 64-bit to double-precision
    SCVTF_SINGLE_TO_SP_FP_64: //Conversions between floating-point and integer/SCVTF (scalar, integer) 64-bit to single-precision
    UCVTF_TO_DP_FP_32: //Conversions between floating-point and integer/UCVTF (scalar, integer) 32-bit to double-precision
    UCVTF_SINGLE_TO_SP_FP_32: //Conversions between floating-point and integer/UCVTF (scalar, integer) 32-bit to single-precision
    UCVTF_TO_DP_FP_64: //Conversions between floating-point and integer/UCVTF (scalar, integer) 64-bit to double-precision
    UCVTF_SINGLE_TO_SP_FP_64: //Conversions between floating-point and integer/UCVTF (scalar, integer) 64-bit to single-precision
    FCMP_FROM_DP: //Floating-point compare/FCMP Double-precision
    FCMP_FROM_DP_ZERO: //Floating-point compare/FCMP Double-precision, zero
    FCMP_SINGLE_FROM_SP: //Floating-point compare/FCMP Single-precision
    FCMP_SINGLE_FROM_SP_ZERO: //Floating-point compare/FCMP Single-precision, zero
    FCMPE_FROM_DP: //Floating-point compare/FCMPE Double-precision
    FCMPE_FROM_DP_ZERO: //Floating-point compare/FCMPE Double-precision, zero
    FCMPE_SINGLE_FROM_SP: //Floating-point compare/FCMPE Single-precision
    FCMPE_SINGLE_FROM_SP_ZERO: //Floating-point compare/FCMPE Single-precision, zero
    FCCMP_FROM_DP: //Floating-point conditional compare/FCCMP Double-precision
    FCCMP_SINGLE_FROM_SP: //Floating-point conditional compare/FCCMP Single-precision
    FCCMPE_FROM_DP: //Floating-point conditional compare/FCCMPE Double-precision
    FCCMPE_SINGLE_FROM_SP: //Floating-point conditional compare/FCCMPE Single-precision
    FCSEL_FROM_DP: //Floating-point conditional select/FCSEL Double-precision
    FCSEL_SINGLE_FROM_SP: //Floating-point conditional select/FCSEL Single-precision
    FABS_FROM_DP: //Floating-point data-processing (1 source)/FABS (scalar) Double-precision
    FABS_SINGLE_FROM_SP: //Floating-point data-processing (1 source)/FABS (scalar) Single-precision
    FCVT_FROM_DP_TO_HP: //Floating-point data-processing (1 source)/FCVT Double-precision to half-precision
    FCVT_SINGLE_FROM_DP_TO_SP: //Floating-point data-processing (1 source)/FCVT Double-precision to single-precision
    FCVT_FROM_HP_TO_DP: //Floating-point data-processing (1 source)/FCVT Half-precision to double-precision
    FCVT_SINGLE_FROM_HP_TO_SP: //Floating-point data-processing (1 source)/FCVT Half-precision to single-precision
    FCVT_SINGLE_FROM_SP_TO_DP: //Floating-point data-processing (1 source)/FCVT Single-precision to double-precision
    FCVT_SINGLE_FROM_SP_TO_HP: //Floating-point data-processing (1 source)/FCVT Single-precision to half-precision
    FMOV_REG_FROM_DP: //Floating-point data-processing (1 source)/FMOV (register) Double-precision
    FMOV_SINGLE_REG_FROM_SP: //Floating-point data-processing (1 source)/FMOV (register) Single-precision
    FNEG_FROM_DP: //Floating-point data-processing (1 source)/FNEG (scalar) Double-precision
    FNEG_SINGLE_FROM_SP: //Floating-point data-processing (1 source)/FNEG (scalar) Single-precision
    FRINTA_FROM_DP: //Floating-point data-processing (1 source)/FRINTA (scalar) Double-precision
    FRINTA_SINGLE_FROM_SP: //Floating-point data-processing (1 source)/FRINTA (scalar) Single-precision
    FRINTI_FROM_DP: //Floating-point data-processing (1 source)/FRINTI (scalar) Double-precision
    FRINTI_SINGLE_FROM_SP: //Floating-point data-processing (1 source)/FRINTI (scalar) Single-precision
    FRINTM_FROM_DP: //Floating-point data-processing (1 source)/FRINTM (scalar) Double-precision
    FRINTM_SINGLE_FROM_SP: //Floating-point data-processing (1 source)/FRINTM (scalar) Single-precision
    FRINTN_FROM_DP: //Floating-point data-processing (1 source)/FRINTN (scalar) Double-precision
    FRINTN_SINGLE_FROM_SP: //Floating-point data-processing (1 source)/FRINTN (scalar) Single-precision
    FRINTP_FROM_DP: //Floating-point data-processing (1 source)/FRINTP (scalar) Double-precision
    FRINTP_SINGLE_FROM_SP: //Floating-point data-processing (1 source)/FRINTP (scalar) Single-precision
    FRINTX_FROM_DP: //Floating-point data-processing (1 source)/FRINTX (scalar) Double-precision
    FRINTX_SINGLE_FROM_SP: //Floating-point data-processing (1 source)/FRINTX (scalar) Single-precision
    FRINTZ_FROM_DP: //Floating-point data-processing (1 source)/FRINTZ (scalar) Double-precision
    FRINTZ_SINGLE_FROM_SP: //Floating-point data-processing (1 source)/FRINTZ (scalar) Single-precision
    FSQRT_FROM_DP: //Floating-point data-processing (1 source)/FSQRT (scalar) Double-precision
    FSQRT_SINGLE_FROM_SP: //Floating-point data-processing (1 source)/FSQRT (scalar) Single-precision
    FADD_FROM_DP: //Floating-point data-processing (2 source)/FADD (scalar) Double-precision
    FADD_SINGLE_FROM_SP: //Floating-point data-processing (2 source)/FADD (scalar) Single-precision
    FDIV_FROM_DP: //Floating-point data-processing (2 source)/FDIV (scalar) Double-precision
    FDIV_SINGLE_FROM_SP: //Floating-point data-processing (2 source)/FDIV (scalar) Single-precision
    FMAX_FROM_DP: //Floating-point data-processing (2 source)/FMAX (scalar) Double-precision
    FMAX_SINGLE_FROM_SP: //Floating-point data-processing (2 source)/FMAX (scalar) Single-precision
    FMAXNM_FROM_DP: //Floating-point data-processing (2 source)/FMAXNM (scalar) Double-precision
    FMAXNM_SINGLE_FROM_SP: //Floating-point data-processing (2 source)/FMAXNM (scalar) Single-precision
    FMIN_FROM_DP: //Floating-point data-processing (2 source)/FMIN (scalar) Double-precision
    FMIN_SINGLE_FROM_SP: //Floating-point data-processing (2 source)/FMIN (scalar) Single-precision
    FMINNM_FROM_DP: //Floating-point data-processing (2 source)/FMINNM (scalar) Double-precision
    FMINNM_SINGLE_FROM_SP: //Floating-point data-processing (2 source)/FMINNM (scalar) Single-precision
    FMUL_FROM_DP: //Floating-point data-processing (2 source)/FMUL (scalar) Double-precision
    FMUL_SINGLE_FROM_SP: //Floating-point data-processing (2 source)/FMUL (scalar) Single-precision
    FNMUL_FROM_DP: //Floating-point data-processing (2 source)/FNMUL Double-precision
    FNMUL_SINGLE_FROM_SP: //Floating-point data-processing (2 source)/FNMUL Single-precision
    FSUB_FROM_DP: //Floating-point data-processing (2 source)/FSUB (scalar) Double-precision
    FSUB_SINGLE_FROM_SP: //Floating-point data-processing (2 source)/FSUB (scalar) Single-precision
    FMADD_FROM_DP: //Floating-point data-processing (3 source)/FMADD Double-precision
    FMADD_SINGLE_FROM_SP: //Floating-point data-processing (3 source)/FMADD Single-precision
    FMSUB_FROM_DP: //Floating-point data-processing (3 source)/FMSUB Double-precision
    FMSUB_SINGLE_FROM_SP: //Floating-point data-processing (3 source)/FMSUB Single-precision
    FNMADD_FROM_DP: //Floating-point data-processing (3 source)/FNMADD Double-precision
    FNMADD_SINGLE_FROM_SP: //Floating-point data-processing (3 source)/FNMADD Single-precision
    FNMSUB_FROM_DP: //Floating-point data-processing (3 source)/FNMSUB Double-precision
    FNMSUB_SINGLE_FROM_SP: //Floating-point data-processing (3 source)/FNMSUB Single-precision
    FMOV_IMM_FROM_DP: //Floating-point immediate/FMOV (scalar, immediate) Double-precision
    FMOV_IMM_SINGLE_FROM_SP: //Floating-point immediate/FMOV (scalar, immediate) Single-precision

// A64 SIMD&FP Load/Store...
    SIMD_LDR_REG_8_128: //Load register (literal)/LDR (literal, SIMD&FP) 128-bit
    SIMD_LDR_REG_32: //Load register (literal)/LDR (literal, SIMD&FP) 32-bit
    SIMD_LDR_REG_64: //Load register (literal)/LDR (literal, SIMD&FP) 64-bit
    SIMD_LDNP_OFF_8_128: //Load/store no-allocate pair (offset)/LDNP (SIMD&FP) 128-bit
    SIMD_LDNP_OFF_32: //Load/store no-allocate pair (offset)/LDNP (SIMD&FP) 32-bit
    SIMD_LDNP_OFF_64: //Load/store no-allocate pair (offset)/LDNP (SIMD&FP) 64-bit
    SIMD_STNP_OFF_8_128: //Load/store no-allocate pair (offset)/STNP (SIMD&FP) 128-bit
    SIMD_STNP_OFF_32: //Load/store no-allocate pair (offset)/STNP (SIMD&FP) 32-bit
    SIMD_STNP_OFF_64: //Load/store no-allocate pair (offset)/STNP (SIMD&FP) 64-bit
    SIMD_LDR_IMM_REG_POST_8_128: //Load/store register (immediate post-indexed)/LDR (immediate, SIMD&FP) 128-bit
    SIMD_LDR_IMM_REG_POST_16: //Load/store register (immediate post-indexed)/LDR (immediate, SIMD&FP) 16-bit
    SIMD_LDR_IMM_REG_POST_32: //Load/store register (immediate post-indexed)/LDR (immediate, SIMD&FP) 32-bit
    SIMD_LDR_IMM_REG_POST_64: //Load/store register (immediate post-indexed)/LDR (immediate, SIMD&FP) 64-bit
    SIMD_LDR_IMM_REG_POST_8: //Load/store register (immediate post-indexed)/LDR (immediate, SIMD&FP) 8-bit
    SIMD_STR_IMM_REG_POST_8_128: //Load/store register (immediate post-indexed)/STR (immediate, SIMD&FP) 128-bit
    SIMD_STR_IMM_REG_POST_16: //Load/store register (immediate post-indexed)/STR (immediate, SIMD&FP) 16-bit
    SIMD_STR_IMM_REG_POST_32: //Load/store register (immediate post-indexed)/STR (immediate, SIMD&FP) 32-bit
    SIMD_STR_IMM_REG_POST_64: //Load/store register (immediate post-indexed)/STR (immediate, SIMD&FP) 64-bit
    SIMD_STR_IMM_REG_POST_8: //Load/store register (immediate post-indexed)/STR (immediate, SIMD&FP) 8-bit
    SIMD_LDR_IMM_REG_PRE_8_128: //Load/store register (immediate pre-indexed)/LDR (immediate, SIMD&FP) 128-bit
    SIMD_LDR_IMM_REG_PRE_16: //Load/store register (immediate pre-indexed)/LDR (immediate, SIMD&FP) 16-bit
    SIMD_LDR_IMM_REG_PRE_32: //Load/store register (immediate pre-indexed)/LDR (immediate, SIMD&FP) 32-bit
    SIMD_LDR_IMM_REG_PRE_64: //Load/store register (immediate pre-indexed)/LDR (immediate, SIMD&FP) 64-bit
    SIMD_LDR_IMM_REG_PRE_8: //Load/store register (immediate pre-indexed)/LDR (immediate, SIMD&FP) 8-bit
    SIMD_STR_IMM_REG_PRE_8_128: //Load/store register (immediate pre-indexed)/STR (immediate, SIMD&FP) 128-bit
    SIMD_STR_IMM_REG_PRE_16: //Load/store register (immediate pre-indexed)/STR (immediate, SIMD&FP) 16-bit
    SIMD_STR_IMM_REG_PRE_32: //Load/store register (immediate pre-indexed)/STR (immediate, SIMD&FP) 32-bit
    SIMD_STR_IMM_REG_PRE_64: //Load/store register (immediate pre-indexed)/STR (immediate, SIMD&FP) 64-bit
    SIMD_STR_IMM_REG_PRE_8: //Load/store register (immediate pre-indexed)/STR (immediate, SIMD&FP) 8-bit
    SIMD_LDR_REG_OFF_8_128: //Load/store register (register offset)/LDR (register, SIMD&FP) 128-bit
    SIMD_LDR_REG_OFF_16: //Load/store register (register offset)/LDR (register, SIMD&FP) 16-bit
    SIMD_LDR_REG_OFF_32: //Load/store register (register offset)/LDR (register, SIMD&FP) 32-bit
    SIMD_LDR_REG_OFF_64: //Load/store register (register offset)/LDR (register, SIMD&FP) 64-bit
    SIMD_LDR_REG_OFF_8: //Load/store register (register offset)/LDR (register, SIMD&FP) 8-bit
    SIMD_STR_REG_OFF_8_128: //Load/store register (register offset)/STR (register, SIMD&FP) 128-bit
    SIMD_STR_REG_OFF_16: //Load/store register (register offset)/STR (register, SIMD&FP) 16-bit
    SIMD_STR_REG_OFF_32: //Load/store register (register offset)/STR (register, SIMD&FP) 32-bit
    SIMD_STR_REG_OFF_64: //Load/store register (register offset)/STR (register, SIMD&FP) 64-bit
    SIMD_STR_REG_OFF_8: //Load/store register (register offset)/STR (register, SIMD&FP) 8-bit
    SIMD_LDUR_IMM_REG_8_128: //Load/store register (unscaled immediate)/LDUR (SIMD&FP) 128-bit
    SIMD_LDUR_IMM_REG_16: //Load/store register (unscaled immediate)/LDUR (SIMD&FP) 16-bit
    SIMD_LDUR_IMM_REG_32: //Load/store register (unscaled immediate)/LDUR (SIMD&FP) 32-bit
    SIMD_LDUR_IMM_REG_64: //Load/store register (unscaled immediate)/LDUR (SIMD&FP) 64-bit
    SIMD_LDUR_IMM_REG_8: //Load/store register (unscaled immediate)/LDUR (SIMD&FP) 8-bit
    SIMD_STUR_IMM_REG_8_128: //Load/store register (unscaled immediate)/STUR (SIMD&FP) 128-bit
    SIMD_STUR_IMM_REG_16: //Load/store register (unscaled immediate)/STUR (SIMD&FP) 16-bit
    SIMD_STUR_IMM_REG_32: //Load/store register (unscaled immediate)/STUR (SIMD&FP) 32-bit
    SIMD_STUR_IMM_REG_64: //Load/store register (unscaled immediate)/STUR (SIMD&FP) 64-bit
    SIMD_STUR_IMM_REG_8: //Load/store register (unscaled immediate)/STUR (SIMD&FP) 8-bit
    SIMD_LDR_IMM_REG_8_128: //Load/store register (unsigned immediate)/LDR (immediate, SIMD&FP) 128-bit
    SIMD_LDR_IMM_REG_16: //Load/store register (unsigned immediate)/LDR (immediate, SIMD&FP) 16-bit
    SIMD_LDR_IMM_REG_32: //Load/store register (unsigned immediate)/LDR (immediate, SIMD&FP) 32-bit
    SIMD_LDR_IMM_REG_64: //Load/store register (unsigned immediate)/LDR (immediate, SIMD&FP) 64-bit
    SIMD_LDR_IMM_REG_8: //Load/store register (unsigned immediate)/LDR (immediate, SIMD&FP) 8-bit
    SIMD_STR_IMM_REG_8_128: //Load/store register (unsigned immediate)/STR (immediate, SIMD&FP) 128-bit
    SIMD_STR_IMM_REG_16: //Load/store register (unsigned immediate)/STR (immediate, SIMD&FP) 16-bit
    SIMD_STR_IMM_REG_32: //Load/store register (unsigned immediate)/STR (immediate, SIMD&FP) 32-bit
    SIMD_STR_IMM_REG_64: //Load/store register (unsigned immediate)/STR (immediate, SIMD&FP) 64-bit
    SIMD_STR_IMM_REG_8: //Load/store register (unsigned immediate)/STR (immediate, SIMD&FP) 8-bit
    SIMD_LDP_REG_OFF_8_128: //Load/store register pair (offset)/LDP (SIMD&FP) 128-bit
    SIMD_LDP_REG_OFF_32: //Load/store register pair (offset)/LDP (SIMD&FP) 32-bit
    SIMD_LDP_REG_OFF_64: //Load/store register pair (offset)/LDP (SIMD&FP) 64-bit
    SIMD_STP_REG_OFF_8_128: //Load/store register pair (offset)/STP (SIMD&FP) 128-bit
    SIMD_STP_REG_OFF_32: //Load/store register pair (offset)/STP (SIMD&FP) 32-bit
    SIMD_STP_REG_OFF_64: //Load/store register pair (offset)/STP (SIMD&FP) 64-bit
    SIMD_LDP_REG_POST_8_128: //Load/store register pair (post-indexed)/LDP (SIMD&FP) 128-bit
    SIMD_LDP_REG_POST_32: //Load/store register pair (post-indexed)/LDP (SIMD&FP) 32-bit
    SIMD_LDP_REG_POST_64: //Load/store register pair (post-indexed)/LDP (SIMD&FP) 64-bit
    SIMD_STP_REG_POST_8_128: //Load/store register pair (post-indexed)/STP (SIMD&FP) 128-bit
    SIMD_STP_REG_POST_32: //Load/store register pair (post-indexed)/STP (SIMD&FP) 32-bit
    SIMD_STP_REG_POST_64: //Load/store register pair (post-indexed)/STP (SIMD&FP) 64-bit
    SIMD_LDP_REG_PRE_8_128: //Load/store register pair (pre-indexed)/LDP (SIMD&FP) 128-bit
    SIMD_LDP_REG_PRE_32: //Load/store register pair (pre-indexed)/LDP (SIMD&FP) 32-bit
    SIMD_LDP_REG_PRE_64: //Load/store register pair (pre-indexed)/LDP (SIMD&FP) 64-bit
    SIMD_STP_REG_PRE_8_128: //Load/store register pair (pre-indexed)/STP (SIMD&FP) 128-bit
    SIMD_STP_REG_PRE_32: //Load/store register pair (pre-indexed)/STP (SIMD&FP) 32-bit
    SIMD_STP_REG_PRE_64: //Load/store register pair (pre-indexed)/STP (SIMD&FP) 64-bit

