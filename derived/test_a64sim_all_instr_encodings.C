int get_next_instr_encoding(int instr_index,unsigned int set_mask,string &group,unsigned int &encoding,unsigned int &mask) {
switch(instr_index) {
  case NOP: group = "System/NOP -"; mask = 0xffffffff; encoding = (set_mask & ~mask) | 0xd503201f; break; // 
  case SEV: group = "System/SEV -"; mask = 0xffffffff; encoding = (set_mask & ~mask) | 0xd503209f; break; // 
  case SEVL: group = "System/SEVL -"; mask = 0xffffffff; encoding = (set_mask & ~mask) | 0xd50320bf; break; // 
  case WFE: group = "System/WFE -"; mask = 0xffffffff; encoding = (set_mask & ~mask) | 0xd503205f; break; // 
  case WFI: group = "System/WFI -"; mask = 0xffffffff; encoding = (set_mask & ~mask) | 0xd503207f; break; // 
  case YIELD: group = "System/YIELD -"; mask = 0xffffffff; encoding = (set_mask & ~mask) | 0xd503203f; break; // 
  case DRPS: group = "Unconditional branch (register)/DRPS -"; mask = 0xffffffff; encoding = (set_mask & ~mask) | 0xd6bf03e0; break; // 
  case ERET: group = "Unconditional branch (register)/ERET -"; mask = 0xffffffff; encoding = (set_mask & ~mask) | 0xd69f03e0; break; // 
  case CLREX: group = "System/CLREX -"; mask = 0xfffff0ff; encoding = (set_mask & ~mask) | 0xd503305f; break; // 
  case DMB: group = "System/DMB -"; mask = 0xfffff0ff; encoding = (set_mask & ~mask) | 0xd50330bf; break; // 
  case DSB: group = "System/DSB -"; mask = 0xfffff0ff; encoding = (set_mask & ~mask) | 0xd503309f; break; // 
  case ISB: group = "System/ISB -"; mask = 0xfffff0ff; encoding = (set_mask & ~mask) | 0xd50330df; break; // 
  case BLR: group = "Unconditional branch (register)/BLR -"; mask = 0xfffffc1f; encoding = (set_mask & ~mask) | 0xd63f0000; break; // 
  case BR: group = "Unconditional branch (register)/BR -"; mask = 0xfffffc1f; encoding = (set_mask & ~mask) | 0xd61f0000; break; // 
  case RET: group = "Unconditional branch (register)/RET -"; mask = 0xfffffc1f; encoding = (set_mask & ~mask) | 0xd65f0000; break; // 
  case HINT: group = "System/HINT -"; mask = 0xfffff01f; encoding = (set_mask & ~mask) | 0xd503201f; break; // 
  case FCMP_FROM_DP: group = "Floating-point compare/FCMP Double-precision"; mask = 0xffe0fc1f; encoding = (set_mask & ~mask) | 0x1e602000; break; // 
  case FCMP_FROM_DP_ZERO: group = "Floating-point compare/FCMP Double-precision, zero"; mask = 0xffe0fc1f; encoding = (set_mask & ~mask) | 0x1e602008; break; // 
  case FCMP_SINGLE_FROM_SP: group = "Floating-point compare/FCMP Single-precision"; mask = 0xffe0fc1f; encoding = (set_mask & ~mask) | 0x1e202000; break; // 
  case FCMP_SINGLE_FROM_SP_ZERO: group = "Floating-point compare/FCMP Single-precision, zero"; mask = 0xffe0fc1f; encoding = (set_mask & ~mask) | 0x1e202008; break; // 
  case FCMPE_FROM_DP: group = "Floating-point compare/FCMPE Double-precision"; mask = 0xffe0fc1f; encoding = (set_mask & ~mask) | 0x1e602010; break; // 
  case FCMPE_FROM_DP_ZERO: group = "Floating-point compare/FCMPE Double-precision, zero"; mask = 0xffe0fc1f; encoding = (set_mask & ~mask) | 0x1e602018; break; // 
  case FCMPE_SINGLE_FROM_SP: group = "Floating-point compare/FCMPE Single-precision"; mask = 0xffe0fc1f; encoding = (set_mask & ~mask) | 0x1e202010; break; // 
  case FCMPE_SINGLE_FROM_SP_ZERO: group = "Floating-point compare/FCMPE Single-precision, zero"; mask = 0xffe0fc1f; encoding = (set_mask & ~mask) | 0x1e202018; break; // 
  case FCVTAS_FROM_DP_FP_32: group = "Conversions between floating-point and integer/FCVTAS (scalar) Double-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e640000; break; // 
  case FCVTAS_FROM_DP_FP_64: group = "Conversions between floating-point and integer/FCVTAS (scalar) Double-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e640000; break; // 
  case FCVTAS_SINGLE_FROM_SP_FP_32: group = "Conversions between floating-point and integer/FCVTAS (scalar) Single-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e240000; break; // 
  case FCVTAS_SINGLE_FROM_SP_FP_64: group = "Conversions between floating-point and integer/FCVTAS (scalar) Single-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e240000; break; // 
  case FCVTAU_FROM_DP_FP_32: group = "Conversions between floating-point and integer/FCVTAU (scalar) Double-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e650000; break; // 
  case FCVTAU_FROM_DP_FP_64: group = "Conversions between floating-point and integer/FCVTAU (scalar) Double-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e650000; break; // 
  case FCVTAU_SINGLE_FROM_SP_FP_32: group = "Conversions between floating-point and integer/FCVTAU (scalar) Single-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e250000; break; // 
  case FCVTAU_SINGLE_FROM_SP_FP_64: group = "Conversions between floating-point and integer/FCVTAU (scalar) Single-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e250000; break; // 
  case FCVTMS_FROM_DP_FP_32: group = "Conversions between floating-point and integer/FCVTMS (scalar) Double-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e700000; break; // 
  case FCVTMS_FROM_DP_FP_64: group = "Conversions between floating-point and integer/FCVTMS (scalar) Double-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e700000; break; // 
  case FCVTMS_SINGLE_FROM_SP_FP_32: group = "Conversions between floating-point and integer/FCVTMS (scalar) Single-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e300000; break; // 
  case FCVTMS_SINGLE_FROM_SP_FP_64: group = "Conversions between floating-point and integer/FCVTMS (scalar) Single-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e300000; break; // 
  case FCVTMU_FROM_DP_FP_32: group = "Conversions between floating-point and integer/FCVTMU (scalar) Double-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e710000; break; // 
  case FCVTMU_FROM_DP_FP_64: group = "Conversions between floating-point and integer/FCVTMU (scalar) Double-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e710000; break; // 
  case FCVTMU_SINGLE_FROM_SP_FP_32: group = "Conversions between floating-point and integer/FCVTMU (scalar) Single-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e310000; break; // 
  case FCVTMU_SINGLE_FROM_SP_FP_64: group = "Conversions between floating-point and integer/FCVTMU (scalar) Single-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e310000; break; // 
  case FCVTNS_FROM_DP_FP_32: group = "Conversions between floating-point and integer/FCVTNS (scalar) Double-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e600000; break; // 
  case FCVTNS_FROM_DP_FP_64: group = "Conversions between floating-point and integer/FCVTNS (scalar) Double-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e600000; break; // 
  case FCVTNS_SINGLE_FROM_SP_FP_32: group = "Conversions between floating-point and integer/FCVTNS (scalar) Single-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e200000; break; // 
  case FCVTNS_SINGLE_FROM_SP_FP_64: group = "Conversions between floating-point and integer/FCVTNS (scalar) Single-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e200000; break; // 
  case FCVTNU_FROM_DP_FP_32: group = "Conversions between floating-point and integer/FCVTNU (scalar) Double-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e610000; break; // 
  case FCVTNU_FROM_DP_FP_64: group = "Conversions between floating-point and integer/FCVTNU (scalar) Double-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e610000; break; // 
  case FCVTNU_SINGLE_FROM_SP_FP_32: group = "Conversions between floating-point and integer/FCVTNU (scalar) Single-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e210000; break; // 
  case FCVTNU_SINGLE_FROM_SP_FP_64: group = "Conversions between floating-point and integer/FCVTNU (scalar) Single-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e210000; break; // 
  case FCVTPS_FROM_DP_FP_32: group = "Conversions between floating-point and integer/FCVTPS (scalar) Double-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e680000; break; // 
  case FCVTPS_FROM_DP_FP_64: group = "Conversions between floating-point and integer/FCVTPS (scalar) Double-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e680000; break; // 
  case FCVTPS_SINGLE_FROM_SP_FP_32: group = "Conversions between floating-point and integer/FCVTPS (scalar) Single-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e280000; break; // 
  case FCVTPS_SINGLE_FROM_SP_FP_64: group = "Conversions between floating-point and integer/FCVTPS (scalar) Single-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e280000; break; // 
  case FCVTPU_FROM_DP_FP_32: group = "Conversions between floating-point and integer/FCVTPU (scalar) Double-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e690000; break; // 
  case FCVTPU_FROM_DP_FP_64: group = "Conversions between floating-point and integer/FCVTPU (scalar) Double-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e690000; break; // 
  case FCVTPU_SINGLE_FROM_SP_FP_32: group = "Conversions between floating-point and integer/FCVTPU (scalar) Single-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e290000; break; // 
  case FCVTPU_SINGLE_FROM_SP_FP_64: group = "Conversions between floating-point and integer/FCVTPU (scalar) Single-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e290000; break; // 
  case FCVTZS_FROM_DP_FP_32: group = "Conversions between floating-point and integer/FCVTZS (scalar, integer) Double-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e780000; break; // 
  case FCVTZS_FROM_DP_FP_64: group = "Conversions between floating-point and integer/FCVTZS (scalar, integer) Double-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e780000; break; // 
  case FCVTZS_SINGLE_FROM_SP_FP_32: group = "Conversions between floating-point and integer/FCVTZS (scalar, integer) Single-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e380000; break; // 
  case FCVTZS_SINGLE_FROM_SP_FP_64: group = "Conversions between floating-point and integer/FCVTZS (scalar, integer) Single-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e380000; break; // 
  case FCVTZU_FROM_DP_FP_32: group = "Conversions between floating-point and integer/FCVTZU (scalar, integer) Double-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e790000; break; // 
  case FCVTZU_FROM_DP_FP_64: group = "Conversions between floating-point and integer/FCVTZU (scalar, integer) Double-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e790000; break; // 
  case FCVTZU_SINGLE_FROM_SP_FP_32: group = "Conversions between floating-point and integer/FCVTZU (scalar, integer) Single-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e390000; break; // 
  case FCVTZU_SINGLE_FROM_SP_FP_64: group = "Conversions between floating-point and integer/FCVTZU (scalar, integer) Single-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e390000; break; // 
  case FMOV_SINGLE_TO_SP_FP_32: group = "Conversions between floating-point and integer/FMOV (general) 32-bit to single-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e270000; break; // 
  case FMOV_TO_DP_FP_64: group = "Conversions between floating-point and integer/FMOV (general) 64-bit to double-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e670000; break; // 
  case FMOV_FP_8_64_128_TO_TOP: group = "Conversions between floating-point and integer/FMOV (general) 64-bit to top half of 128-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9eaf0000; break; // 
  case FMOV_FROM_DP_FP_64: group = "Conversions between floating-point and integer/FMOV (general) Double-precision to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e660000; break; // 
  case FMOV_SINGLE_FROM_SP_FP_32: group = "Conversions between floating-point and integer/FMOV (general) Single-precision to 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e260000; break; // 
  case FMOV_FP_8_64_128: group = "Conversions between floating-point and integer/FMOV (general) Top half of 128-bit to 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9eae0000; break; // 
  case SCVTF_TO_DP_FP_32: group = "Conversions between floating-point and integer/SCVTF (scalar, integer) 32-bit to double-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e620000; break; // 
  case SCVTF_SINGLE_TO_SP_FP_32: group = "Conversions between floating-point and integer/SCVTF (scalar, integer) 32-bit to single-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e220000; break; // 
  case SCVTF_TO_DP_FP_64: group = "Conversions between floating-point and integer/SCVTF (scalar, integer) 64-bit to double-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e620000; break; // 
  case SCVTF_SINGLE_TO_SP_FP_64: group = "Conversions between floating-point and integer/SCVTF (scalar, integer) 64-bit to single-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e220000; break; // 
  case UCVTF_TO_DP_FP_32: group = "Conversions between floating-point and integer/UCVTF (scalar, integer) 32-bit to double-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e630000; break; // 
  case UCVTF_SINGLE_TO_SP_FP_32: group = "Conversions between floating-point and integer/UCVTF (scalar, integer) 32-bit to single-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e230000; break; // 
  case UCVTF_TO_DP_FP_64: group = "Conversions between floating-point and integer/UCVTF (scalar, integer) 64-bit to double-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e630000; break; // 
  case UCVTF_SINGLE_TO_SP_FP_64: group = "Conversions between floating-point and integer/UCVTF (scalar, integer) 64-bit to single-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x9e230000; break; // 
  case AESD: group = "Cryptographic AES/AESD -"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x4e285800; break; // 
  case AESE: group = "Cryptographic AES/AESE -"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x4e284800; break; // 
  case AESIMC: group = "Cryptographic AES/AESIMC -"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x4e287800; break; // 
  case AESMC: group = "Cryptographic AES/AESMC -"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x4e286800; break; // 
  case SHA1H_REG: group = "Cryptographic two-register SHA/SHA1H -"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x5e280800; break; // 
  case SHA1SU1_REG: group = "Cryptographic two-register SHA/SHA1SU1 -"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x5e281800; break; // 
  case SHA256SU0_REG: group = "Cryptographic two-register SHA/SHA256SU0 -"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x5e282800; break; // 
  case CLS_32: group = "Data-processing (1 source)/CLS 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x5ac01400; break; // 
  case CLS_64: group = "Data-processing (1 source)/CLS 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0xdac01400; break; // 
  case CLZ_32: group = "Data-processing (1 source)/CLZ 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x5ac01000; break; // 
  case CLZ_64: group = "Data-processing (1 source)/CLZ 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0xdac01000; break; // 
  case RBIT_32: group = "Data-processing (1 source)/RBIT 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x5ac00000; break; // 
  case RBIT_64: group = "Data-processing (1 source)/RBIT 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0xdac00000; break; // 
  case REV_32: group = "Data-processing (1 source)/REV 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x5ac00800; break; // 
  case REV_64: group = "Data-processing (1 source)/REV 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0xdac00c00; break; // 
  case REV16_32: group = "Data-processing (1 source)/REV16 32-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x5ac00400; break; // 
  case REV16_64: group = "Data-processing (1 source)/REV16 64-bit"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0xdac00400; break; // 
  case REV32: group = "Data-processing (1 source)/REV32 -"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0xdac00800; break; // 
  case FABS_FROM_DP: group = "Floating-point data-processing (1 source)/FABS (scalar) Double-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e60c000; break; // 
  case FABS_SINGLE_FROM_SP: group = "Floating-point data-processing (1 source)/FABS (scalar) Single-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e20c000; break; // 
  case FCVT_FROM_DP_TO_HP: group = "Floating-point data-processing (1 source)/FCVT Double-precision to half-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e63c000; break; // 
  case FCVT_SINGLE_FROM_DP_TO_SP: group = "Floating-point data-processing (1 source)/FCVT Double-precision to single-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e624000; break; // 
  case FCVT_FROM_HP_TO_DP: group = "Floating-point data-processing (1 source)/FCVT Half-precision to double-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1ee2c000; break; // 
  case FCVT_SINGLE_FROM_HP_TO_SP: group = "Floating-point data-processing (1 source)/FCVT Half-precision to single-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1ee24000; break; // 
  case FCVT_SINGLE_FROM_SP_TO_DP: group = "Floating-point data-processing (1 source)/FCVT Single-precision to double-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e22c000; break; // 
  case FCVT_SINGLE_FROM_SP_TO_HP: group = "Floating-point data-processing (1 source)/FCVT Single-precision to half-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e23c000; break; // 
  case FMOV_REG_FROM_DP: group = "Floating-point data-processing (1 source)/FMOV (register) Double-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e604000; break; // 
  case FMOV_SINGLE_REG_FROM_SP: group = "Floating-point data-processing (1 source)/FMOV (register) Single-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e204000; break; // 
  case FNEG_FROM_DP: group = "Floating-point data-processing (1 source)/FNEG (scalar) Double-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e614000; break; // 
  case FNEG_SINGLE_FROM_SP: group = "Floating-point data-processing (1 source)/FNEG (scalar) Single-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e214000; break; // 
  case FRINTA_FROM_DP: group = "Floating-point data-processing (1 source)/FRINTA (scalar) Double-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e664000; break; // 
  case FRINTA_SINGLE_FROM_SP: group = "Floating-point data-processing (1 source)/FRINTA (scalar) Single-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e264000; break; // 
  case FRINTI_FROM_DP: group = "Floating-point data-processing (1 source)/FRINTI (scalar) Double-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e67c000; break; // 
  case FRINTI_SINGLE_FROM_SP: group = "Floating-point data-processing (1 source)/FRINTI (scalar) Single-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e27c000; break; // 
  case FRINTM_FROM_DP: group = "Floating-point data-processing (1 source)/FRINTM (scalar) Double-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e654000; break; // 
  case FRINTM_SINGLE_FROM_SP: group = "Floating-point data-processing (1 source)/FRINTM (scalar) Single-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e254000; break; // 
  case FRINTN_FROM_DP: group = "Floating-point data-processing (1 source)/FRINTN (scalar) Double-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e644000; break; // 
  case FRINTN_SINGLE_FROM_SP: group = "Floating-point data-processing (1 source)/FRINTN (scalar) Single-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e244000; break; // 
  case FRINTP_FROM_DP: group = "Floating-point data-processing (1 source)/FRINTP (scalar) Double-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e64c000; break; // 
  case FRINTP_SINGLE_FROM_SP: group = "Floating-point data-processing (1 source)/FRINTP (scalar) Single-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e24c000; break; // 
  case FRINTX_FROM_DP: group = "Floating-point data-processing (1 source)/FRINTX (scalar) Double-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e674000; break; // 
  case FRINTX_SINGLE_FROM_SP: group = "Floating-point data-processing (1 source)/FRINTX (scalar) Single-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e274000; break; // 
  case FRINTZ_FROM_DP: group = "Floating-point data-processing (1 source)/FRINTZ (scalar) Double-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e65c000; break; // 
  case FRINTZ_SINGLE_FROM_SP: group = "Floating-point data-processing (1 source)/FRINTZ (scalar) Single-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e25c000; break; // 
  case FSQRT_FROM_DP: group = "Floating-point data-processing (1 source)/FSQRT (scalar) Double-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e61c000; break; // 
  case FSQRT_SINGLE_FROM_SP: group = "Floating-point data-processing (1 source)/FSQRT (scalar) Single-precision"; mask = 0xfffffc00; encoding = (set_mask & ~mask) | 0x1e21c000; break; // 
  case MSR_IMM: group = "System/MSR (immediate) -"; mask = 0xfff8f01f; encoding = (set_mask & ~mask) | 0xd500401f; break; // 
  case SIMD_FADDP: group = "Advanced SIMD scalar pairwise/FADDP (scalar) -"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x7e30d800; break; // 
  case SIMD_FMAXNMP: group = "Advanced SIMD scalar pairwise/FMAXNMP (scalar) -"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x7e30c800; break; // 
  case SIMD_FMAXP: group = "Advanced SIMD scalar pairwise/FMAXP (scalar) -"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x7e30f800; break; // 
  case SIMD_FMINNMP: group = "Advanced SIMD scalar pairwise/FMINNMP (scalar) -"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x7eb0c800; break; // 
  case SIMD_FMINP: group = "Advanced SIMD scalar pairwise/FMINP (scalar) -"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x7eb0f800; break; // 
  case SIMD_FCMEQ_REG_SCALAR_ZERO: group = "Advanced SIMD scalar two-register miscellaneous/FCMEQ (zero) Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x5ea0d800; break; // 
  case SIMD_FCMGE_REG_SCALAR_ZERO: group = "Advanced SIMD scalar two-register miscellaneous/FCMGE (zero) Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x7ea0c800; break; // 
  case SIMD_FCMGT_REG_SCALAR_ZERO: group = "Advanced SIMD scalar two-register miscellaneous/FCMGT (zero) Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x5ea0c800; break; // 
  case SIMD_FCMLE_REG_SCALAR_ZERO: group = "Advanced SIMD scalar two-register miscellaneous/FCMLE (zero) Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x7ea0d800; break; // 
  case SIMD_FCMLT_REG_SCALAR_ZERO: group = "Advanced SIMD scalar two-register miscellaneous/FCMLT (zero) Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x5ea0e800; break; // 
  case SIMD_FCVTAS_REG_SCALAR_VEC: group = "Advanced SIMD scalar two-register miscellaneous/FCVTAS (vector) Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x5e21c800; break; // 
  case SIMD_FCVTAU_REG_SCALAR_VEC: group = "Advanced SIMD scalar two-register miscellaneous/FCVTAU (vector) Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x7e21c800; break; // 
  case SIMD_FCVTMS_REG_SCALAR_VEC: group = "Advanced SIMD scalar two-register miscellaneous/FCVTMS (vector) Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x5e21b800; break; // 
  case SIMD_FCVTMU_REG_SCALAR_VEC: group = "Advanced SIMD scalar two-register miscellaneous/FCVTMU (vector) Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x7e21b800; break; // 
  case SIMD_FCVTNS_REG_SCALAR_VEC: group = "Advanced SIMD scalar two-register miscellaneous/FCVTNS (vector) Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x5e21a800; break; // 
  case SIMD_FCVTNU_REG_SCALAR_VEC: group = "Advanced SIMD scalar two-register miscellaneous/FCVTNU (vector) Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x7e21a800; break; // 
  case SIMD_FCVTPS_REG_SCALAR_VEC: group = "Advanced SIMD scalar two-register miscellaneous/FCVTPS (vector) Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x5ea1a800; break; // 
  case SIMD_FCVTPU_REG_SCALAR_VEC: group = "Advanced SIMD scalar two-register miscellaneous/FCVTPU (vector) Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x7ea1a800; break; // 
  case SIMD_FCVTXN_REG_SCALAR: group = "Advanced SIMD scalar two-register miscellaneous/FCVTXN, FCVTXN2 Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x7e216800; break; // 
  case SIMD_FCVTZS_REG_SCALAR_VEC: group = "Advanced SIMD scalar two-register miscellaneous/FCVTZS (vector, integer) Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x5ea1b800; break; // 
  case SIMD_FCVTZU_REG_SCALAR_VEC: group = "Advanced SIMD scalar two-register miscellaneous/FCVTZU (vector, integer) Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x7ea1b800; break; // 
  case SIMD_FRECPE_REG_SCALAR: group = "Advanced SIMD scalar two-register miscellaneous/FRECPE Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x5ea1d800; break; // 
  case SIMD_FRECPX_REG: group = "Advanced SIMD scalar two-register miscellaneous/FRECPX -"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x5ea1f800; break; // 
  case SIMD_FRSQRTE_REG_SCALAR: group = "Advanced SIMD scalar two-register miscellaneous/FRSQRTE Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x7ea1d800; break; // 
  case SIMD_SCVTF_REG_SCALAR_VEC: group = "Advanced SIMD scalar two-register miscellaneous/SCVTF (vector, integer) Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x5e21d800; break; // 
  case SIMD_UCVTF_REG_SCALAR_VEC: group = "Advanced SIMD scalar two-register miscellaneous/UCVTF (vector, integer) Scalar"; mask = 0xffbffc00; encoding = (set_mask & ~mask) | 0x7e21d800; break; // 
  case SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_64: group = "Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 64-bit, immediate offset"; mask = 0xbffffc00; encoding = (set_mask & ~mask) | 0xddf8400; break; // 
  case SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_64: group = "Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 64-bit, immediate offset"; mask = 0xbffffc00; encoding = (set_mask & ~mask) | 0xdff8400; break; // 
  case SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_64: group = "Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 64-bit, immediate offset"; mask = 0xbffffc00; encoding = (set_mask & ~mask) | 0xddfa400; break; // 
  case SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_64: group = "Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 64-bit, immediate offset"; mask = 0xbffffc00; encoding = (set_mask & ~mask) | 0xdffa400; break; // 
  case SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_64: group = "Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 64-bit, immediate offset"; mask = 0xbffffc00; encoding = (set_mask & ~mask) | 0xd9f8400; break; // 
  case SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_64: group = "Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 64-bit, immediate offset"; mask = 0xbffffc00; encoding = (set_mask & ~mask) | 0xdbf8400; break; // 
  case SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_64: group = "Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 64-bit, immediate offset"; mask = 0xbffffc00; encoding = (set_mask & ~mask) | 0xd9fa400; break; // 
  case SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_64: group = "Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 64-bit, immediate offset"; mask = 0xbffffc00; encoding = (set_mask & ~mask) | 0xdbfa400; break; // 
  case SIMD_LD1_SINGLE_STRUCT_64: group = "Advanced SIMD load/store single structure/LD1 (single structure) 64-bit"; mask = 0xbffffc00; encoding = (set_mask & ~mask) | 0xd408400; break; // 
  case SIMD_LD2_SINGLE_STRUCT_64: group = "Advanced SIMD load/store single structure/LD2 (single structure) 64-bit"; mask = 0xbffffc00; encoding = (set_mask & ~mask) | 0xd608400; break; // 
  case SIMD_LD3_SINGLE_STRUCT_64: group = "Advanced SIMD load/store single structure/LD3 (single structure) 64-bit"; mask = 0xbffffc00; encoding = (set_mask & ~mask) | 0xd40a400; break; // 
  case SIMD_LD4_SINGLE_STRUCT_64: group = "Advanced SIMD load/store single structure/LD4 (single structure) 64-bit"; mask = 0xbffffc00; encoding = (set_mask & ~mask) | 0xd60a400; break; // 
  case SIMD_ST1_SINGLE_STRUCT_64: group = "Advanced SIMD load/store single structure/ST1 (single structure) 64-bit"; mask = 0xbffffc00; encoding = (set_mask & ~mask) | 0xd008400; break; // 
  case SIMD_ST2_SINGLE_STRUCT_64: group = "Advanced SIMD load/store single structure/ST2 (single structure) 64-bit"; mask = 0xbffffc00; encoding = (set_mask & ~mask) | 0xd208400; break; // 
  case SIMD_ST3_SINGLE_STRUCT_64: group = "Advanced SIMD load/store single structure/ST3 (single structure) 64-bit"; mask = 0xbffffc00; encoding = (set_mask & ~mask) | 0xd00a400; break; // 
  case SIMD_ST4_SINGLE_STRUCT_64: group = "Advanced SIMD load/store single structure/ST4 (single structure) 64-bit"; mask = 0xbffffc00; encoding = (set_mask & ~mask) | 0xd20a400; break; // 
  case SIMD_NOT_REG: group = "Advanced SIMD two-register miscellaneous/NOT -"; mask = 0xbffffc00; encoding = (set_mask & ~mask) | 0x2e205800; break; // 
  case SIMD_RBIT_REG_VEC: group = "Advanced SIMD two-register miscellaneous/RBIT (vector) -"; mask = 0xbffffc00; encoding = (set_mask & ~mask) | 0x2e605800; break; // 
  case SIMD_ADDP: group = "Advanced SIMD scalar pairwise/ADDP (scalar) -"; mask = 0xff3ffc00; encoding = (set_mask & ~mask) | 0x5e31b800; break; // 
  case SIMD_ABS_REG_SCALAR: group = "Advanced SIMD scalar two-register miscellaneous/ABS Scalar"; mask = 0xff3ffc00; encoding = (set_mask & ~mask) | 0x5e20b800; break; // 
  case SIMD_CMEQ_REG_SCALAR_ZERO: group = "Advanced SIMD scalar two-register miscellaneous/CMEQ (zero) Scalar"; mask = 0xff3ffc00; encoding = (set_mask & ~mask) | 0x5e209800; break; // 
  case SIMD_CMGE_REG_SCALAR_ZERO: group = "Advanced SIMD scalar two-register miscellaneous/CMGE (zero) Scalar"; mask = 0xff3ffc00; encoding = (set_mask & ~mask) | 0x7e208800; break; // 
  case SIMD_CMGT_REG_SCALAR_ZERO: group = "Advanced SIMD scalar two-register miscellaneous/CMGT (zero) Scalar"; mask = 0xff3ffc00; encoding = (set_mask & ~mask) | 0x5e208800; break; // 
  case SIMD_CMLE_REG_SCALAR_ZERO: group = "Advanced SIMD scalar two-register miscellaneous/CMLE (zero) Scalar"; mask = 0xff3ffc00; encoding = (set_mask & ~mask) | 0x7e209800; break; // 
  case SIMD_CMLT_REG_SCALAR_ZERO: group = "Advanced SIMD scalar two-register miscellaneous/CMLT (zero) Scalar"; mask = 0xff3ffc00; encoding = (set_mask & ~mask) | 0x5e20a800; break; // 
  case SIMD_NEG_REG_SCALAR_VEC: group = "Advanced SIMD scalar two-register miscellaneous/NEG (vector) Scalar"; mask = 0xff3ffc00; encoding = (set_mask & ~mask) | 0x7e20b800; break; // 
  case SIMD_SQABS_REG_SCALAR: group = "Advanced SIMD scalar two-register miscellaneous/SQABS Scalar"; mask = 0xff3ffc00; encoding = (set_mask & ~mask) | 0x5e207800; break; // 
  case SIMD_SQNEG_REG_SCALAR: group = "Advanced SIMD scalar two-register miscellaneous/SQNEG Scalar"; mask = 0xff3ffc00; encoding = (set_mask & ~mask) | 0x7e207800; break; // 
  case SIMD_SQXTN_REG_SCALAR: group = "Advanced SIMD scalar two-register miscellaneous/SQXTN, SQXTN2 Scalar"; mask = 0xff3ffc00; encoding = (set_mask & ~mask) | 0x5e214800; break; // 
  case SIMD_SQXTUN_REG_SCALAR: group = "Advanced SIMD scalar two-register miscellaneous/SQXTUN, SQXTUN2 Scalar"; mask = 0xff3ffc00; encoding = (set_mask & ~mask) | 0x7e212800; break; // 
  case SIMD_SUQADD_REG_SCALAR: group = "Advanced SIMD scalar two-register miscellaneous/SUQADD Scalar"; mask = 0xff3ffc00; encoding = (set_mask & ~mask) | 0x5e203800; break; // 
  case SIMD_UQXTN_REG_SCALAR: group = "Advanced SIMD scalar two-register miscellaneous/UQXTN, UQXTN2 Scalar"; mask = 0xff3ffc00; encoding = (set_mask & ~mask) | 0x7e214800; break; // 
  case SIMD_USQADD_REG_SCALAR: group = "Advanced SIMD scalar two-register miscellaneous/USQADD Scalar"; mask = 0xff3ffc00; encoding = (set_mask & ~mask) | 0x7e203800; break; // 
  case SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_32: group = "Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 32-bit, immediate offset"; mask = 0xbfffec00; encoding = (set_mask & ~mask) | 0xddf8000; break; // 
  case SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_32: group = "Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 32-bit, immediate offset"; mask = 0xbfffec00; encoding = (set_mask & ~mask) | 0xdff8000; break; // 
  case SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_32: group = "Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 32-bit, immediate offset"; mask = 0xbfffec00; encoding = (set_mask & ~mask) | 0xddfa000; break; // 
  case SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_32: group = "Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 32-bit, immediate offset"; mask = 0xbfffec00; encoding = (set_mask & ~mask) | 0xdffa000; break; // 
  case SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_32: group = "Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 32-bit, immediate offset"; mask = 0xbfffec00; encoding = (set_mask & ~mask) | 0xd9f8000; break; // 
  case SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_32: group = "Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 32-bit, immediate offset"; mask = 0xbfffec00; encoding = (set_mask & ~mask) | 0xdbf8000; break; // 
  case SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_32: group = "Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 32-bit, immediate offset"; mask = 0xbfffec00; encoding = (set_mask & ~mask) | 0xd9fa000; break; // 
  case SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_32: group = "Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 32-bit, immediate offset"; mask = 0xbfffec00; encoding = (set_mask & ~mask) | 0xdbfa000; break; // 
  case SIMD_LD1_SINGLE_STRUCT_32: group = "Advanced SIMD load/store single structure/LD1 (single structure) 32-bit"; mask = 0xbfffec00; encoding = (set_mask & ~mask) | 0xd408000; break; // 
  case SIMD_LD2_SINGLE_STRUCT_32: group = "Advanced SIMD load/store single structure/LD2 (single structure) 32-bit"; mask = 0xbfffec00; encoding = (set_mask & ~mask) | 0xd608000; break; // 
  case SIMD_LD3_SINGLE_STRUCT_32: group = "Advanced SIMD load/store single structure/LD3 (single structure) 32-bit"; mask = 0xbfffec00; encoding = (set_mask & ~mask) | 0xd40a000; break; // 
  case SIMD_LD4_SINGLE_STRUCT_32: group = "Advanced SIMD load/store single structure/LD4 (single structure) 32-bit"; mask = 0xbfffec00; encoding = (set_mask & ~mask) | 0xd60a000; break; // 
  case SIMD_ST1_SINGLE_STRUCT_32: group = "Advanced SIMD load/store single structure/ST1 (single structure) 32-bit"; mask = 0xbfffec00; encoding = (set_mask & ~mask) | 0xd008000; break; // 
  case SIMD_ST2_SINGLE_STRUCT_32: group = "Advanced SIMD load/store single structure/ST2 (single structure) 32-bit"; mask = 0xbfffec00; encoding = (set_mask & ~mask) | 0xd208000; break; // 
  case SIMD_ST3_SINGLE_STRUCT_32: group = "Advanced SIMD load/store single structure/ST3 (single structure) 32-bit"; mask = 0xbfffec00; encoding = (set_mask & ~mask) | 0xd00a000; break; // 
  case SIMD_ST4_SINGLE_STRUCT_32: group = "Advanced SIMD load/store single structure/ST4 (single structure) 32-bit"; mask = 0xbfffec00; encoding = (set_mask & ~mask) | 0xd20a000; break; // 
  case SIMD_FMAXNMV: group = "Advanced SIMD across lanes/FMAXNMV -"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2e30c800; break; // 
  case SIMD_FMAXV: group = "Advanced SIMD across lanes/FMAXV -"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2e30f800; break; // 
  case SIMD_FMINNMV: group = "Advanced SIMD across lanes/FMINNMV -"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2eb0c800; break; // 
  case SIMD_FMINV: group = "Advanced SIMD across lanes/FMINV -"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2eb0f800; break; // 
  case SIMD_FABS_REG_VEC: group = "Advanced SIMD two-register miscellaneous/FABS (vector) -"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0xea0f800; break; // 
  case SIMD_FCMEQ_REG_VEC_ZERO: group = "Advanced SIMD two-register miscellaneous/FCMEQ (zero) Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0xea0d800; break; // 
  case SIMD_FCMGE_REG_VEC_ZERO: group = "Advanced SIMD two-register miscellaneous/FCMGE (zero) Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2ea0c800; break; // 
  case SIMD_FCMGT_REG_VEC_ZERO: group = "Advanced SIMD two-register miscellaneous/FCMGT (zero) Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0xea0c800; break; // 
  case SIMD_FCMLE_REG_VEC_ZERO: group = "Advanced SIMD two-register miscellaneous/FCMLE (zero) Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2ea0d800; break; // 
  case SIMD_FCMLT_REG_VEC_ZERO: group = "Advanced SIMD two-register miscellaneous/FCMLT (zero) Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0xea0e800; break; // 
  case SIMD_FCVTAS_REG_VEC_VEC: group = "Advanced SIMD two-register miscellaneous/FCVTAS (vector) Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0xe21c800; break; // 
  case SIMD_FCVTAU_REG_VEC_VEC: group = "Advanced SIMD two-register miscellaneous/FCVTAU (vector) Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2e21c800; break; // 
  case SIMD_FCVTL_REG: group = "Advanced SIMD two-register miscellaneous/FCVTL, FCVTL2 -"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0xe217800; break; // 
  case SIMD_FCVTMS_REG_VEC_VEC: group = "Advanced SIMD two-register miscellaneous/FCVTMS (vector) Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0xe21b800; break; // 
  case SIMD_FCVTMU_REG_VEC_VEC: group = "Advanced SIMD two-register miscellaneous/FCVTMU (vector) Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2e21b800; break; // 
  case SIMD_FCVTN_REG: group = "Advanced SIMD two-register miscellaneous/FCVTN, FCVTN2 -"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0xe216800; break; // 
  case SIMD_FCVTNS_REG_VEC_VEC: group = "Advanced SIMD two-register miscellaneous/FCVTNS (vector) Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0xe21a800; break; // 
  case SIMD_FCVTNU_REG_VEC_VEC: group = "Advanced SIMD two-register miscellaneous/FCVTNU (vector) Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2e21a800; break; // 
  case SIMD_FCVTPS_REG_VEC_VEC: group = "Advanced SIMD two-register miscellaneous/FCVTPS (vector) Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0xea1a800; break; // 
  case SIMD_FCVTPU_REG_VEC_VEC: group = "Advanced SIMD two-register miscellaneous/FCVTPU (vector) Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2ea1a800; break; // 
  case SIMD_FCVTXN_REG_VEC: group = "Advanced SIMD two-register miscellaneous/FCVTXN, FCVTXN2 Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2e216800; break; // 
  case SIMD_FCVTZS_REG_VEC_VEC: group = "Advanced SIMD two-register miscellaneous/FCVTZS (vector, integer) Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0xea1b800; break; // 
  case SIMD_FCVTZU_REG_VEC_VEC: group = "Advanced SIMD two-register miscellaneous/FCVTZU (vector, integer) Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2ea1b800; break; // 
  case SIMD_FNEG_REG_VEC: group = "Advanced SIMD two-register miscellaneous/FNEG (vector) -"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2ea0f800; break; // 
  case SIMD_FRECPE_REG_VEC: group = "Advanced SIMD two-register miscellaneous/FRECPE Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0xea1d800; break; // 
  case SIMD_FRINTA_REG_VEC: group = "Advanced SIMD two-register miscellaneous/FRINTA (vector) -"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2e218800; break; // 
  case SIMD_FRINTI_REG_VEC: group = "Advanced SIMD two-register miscellaneous/FRINTI (vector) -"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2ea19800; break; // 
  case SIMD_FRINTM_REG_VEC: group = "Advanced SIMD two-register miscellaneous/FRINTM (vector) -"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0xe219800; break; // 
  case SIMD_FRINTN_REG_VEC: group = "Advanced SIMD two-register miscellaneous/FRINTN (vector) -"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0xe218800; break; // 
  case SIMD_FRINTP_REG_VEC: group = "Advanced SIMD two-register miscellaneous/FRINTP (vector) -"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0xea18800; break; // 
  case SIMD_FRINTX_REG_VEC: group = "Advanced SIMD two-register miscellaneous/FRINTX (vector) -"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2e219800; break; // 
  case SIMD_FRINTZ_REG_VEC: group = "Advanced SIMD two-register miscellaneous/FRINTZ (vector) -"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0xea19800; break; // 
  case SIMD_FRSQRTE_REG_VEC: group = "Advanced SIMD two-register miscellaneous/FRSQRTE Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2ea1d800; break; // 
  case SIMD_FSQRT_REG_VEC: group = "Advanced SIMD two-register miscellaneous/FSQRT (vector) -"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2ea1f800; break; // 
  case SIMD_SCVTF_REG_VEC_VEC: group = "Advanced SIMD two-register miscellaneous/SCVTF (vector, integer) Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0xe21d800; break; // 
  case SIMD_UCVTF_REG_VEC_VEC: group = "Advanced SIMD two-register miscellaneous/UCVTF (vector, integer) Vector"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2e21d800; break; // 
  case SIMD_URECPE_REG: group = "Advanced SIMD two-register miscellaneous/URECPE -"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0xea1c800; break; // 
  case SIMD_URSQRTE_REG: group = "Advanced SIMD two-register miscellaneous/URSQRTE -"; mask = 0xbfbffc00; encoding = (set_mask & ~mask) | 0x2ea1c800; break; // 
  case SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_16: group = "Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 16-bit, immediate offset"; mask = 0xbfffe400; encoding = (set_mask & ~mask) | 0xddf4000; break; // 
  case SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_16: group = "Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 16-bit, immediate offset"; mask = 0xbfffe400; encoding = (set_mask & ~mask) | 0xdff4000; break; // 
  case SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_16: group = "Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 16-bit, immediate offset"; mask = 0xbfffe400; encoding = (set_mask & ~mask) | 0xddf6000; break; // 
  case SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_16: group = "Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 16-bit, immediate offset"; mask = 0xbfffe400; encoding = (set_mask & ~mask) | 0xdff6000; break; // 
  case SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_16: group = "Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 16-bit, immediate offset"; mask = 0xbfffe400; encoding = (set_mask & ~mask) | 0xd9f4000; break; // 
  case SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_16: group = "Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 16-bit, immediate offset"; mask = 0xbfffe400; encoding = (set_mask & ~mask) | 0xdbf4000; break; // 
  case SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_16: group = "Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 16-bit, immediate offset"; mask = 0xbfffe400; encoding = (set_mask & ~mask) | 0xd9f6000; break; // 
  case SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_16: group = "Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 16-bit, immediate offset"; mask = 0xbfffe400; encoding = (set_mask & ~mask) | 0xdbf6000; break; // 
  case SIMD_LD1_SINGLE_STRUCT_16: group = "Advanced SIMD load/store single structure/LD1 (single structure) 16-bit"; mask = 0xbfffe400; encoding = (set_mask & ~mask) | 0xd404000; break; // 
  case SIMD_LD2_SINGLE_STRUCT_16: group = "Advanced SIMD load/store single structure/LD2 (single structure) 16-bit"; mask = 0xbfffe400; encoding = (set_mask & ~mask) | 0xd604000; break; // 
  case SIMD_LD3_SINGLE_STRUCT_16: group = "Advanced SIMD load/store single structure/LD3 (single structure) 16-bit"; mask = 0xbfffe400; encoding = (set_mask & ~mask) | 0xd406000; break; // 
  case SIMD_LD4_SINGLE_STRUCT_16: group = "Advanced SIMD load/store single structure/LD4 (single structure) 16-bit"; mask = 0xbfffe400; encoding = (set_mask & ~mask) | 0xd606000; break; // 
  case SIMD_ST1_SINGLE_STRUCT_16: group = "Advanced SIMD load/store single structure/ST1 (single structure) 16-bit"; mask = 0xbfffe400; encoding = (set_mask & ~mask) | 0xd004000; break; // 
  case SIMD_ST2_SINGLE_STRUCT_16: group = "Advanced SIMD load/store single structure/ST2 (single structure) 16-bit"; mask = 0xbfffe400; encoding = (set_mask & ~mask) | 0xd204000; break; // 
  case SIMD_ST3_SINGLE_STRUCT_16: group = "Advanced SIMD load/store single structure/ST3 (single structure) 16-bit"; mask = 0xbfffe400; encoding = (set_mask & ~mask) | 0xd006000; break; // 
  case SIMD_ST4_SINGLE_STRUCT_16: group = "Advanced SIMD load/store single structure/ST4 (single structure) 16-bit"; mask = 0xbfffe400; encoding = (set_mask & ~mask) | 0xd206000; break; // 
  case SIMD_ADDV: group = "Advanced SIMD across lanes/ADDV -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0xe31b800; break; // 
  case SIMD_SADDLV: group = "Advanced SIMD across lanes/SADDLV -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0xe303800; break; // 
  case SIMD_SMAXV: group = "Advanced SIMD across lanes/SMAXV -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0xe30a800; break; // 
  case SIMD_SMINV: group = "Advanced SIMD across lanes/SMINV -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0xe31a800; break; // 
  case SIMD_UADDLV: group = "Advanced SIMD across lanes/UADDLV -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0x2e303800; break; // 
  case SIMD_UMAXV: group = "Advanced SIMD across lanes/UMAXV -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0x2e30a800; break; // 
  case SIMD_UMINV: group = "Advanced SIMD across lanes/UMINV -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0x2e31a800; break; // 
  case SIMD_ABS_REG_VEC: group = "Advanced SIMD two-register miscellaneous/ABS Vector"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0xe20b800; break; // 
  case SIMD_CLS_REG_VEC: group = "Advanced SIMD two-register miscellaneous/CLS (vector) -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0xe204800; break; // 
  case SIMD_CLZ_REG_VEC: group = "Advanced SIMD two-register miscellaneous/CLZ (vector) -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0x2e204800; break; // 
  case SIMD_CMEQ_REG_VEC_ZERO: group = "Advanced SIMD two-register miscellaneous/CMEQ (zero) Vector"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0xe209800; break; // 
  case SIMD_CMGE_REG_VEC_ZERO: group = "Advanced SIMD two-register miscellaneous/CMGE (zero) Vector"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0x2e208800; break; // 
  case SIMD_CMGT_REG_VEC_ZERO: group = "Advanced SIMD two-register miscellaneous/CMGT (zero) Vector"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0xe208800; break; // 
  case SIMD_CMLE_REG_VEC_ZERO: group = "Advanced SIMD two-register miscellaneous/CMLE (zero) Vector"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0x2e209800; break; // 
  case SIMD_CMLT_REG_VEC_ZERO: group = "Advanced SIMD two-register miscellaneous/CMLT (zero) Vector"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0xe20a800; break; // 
  case SIMD_CNT_REG: group = "Advanced SIMD two-register miscellaneous/CNT -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0xe205800; break; // 
  case SIMD_NEG_REG_VEC_VEC: group = "Advanced SIMD two-register miscellaneous/NEG (vector) Vector"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0x2e20b800; break; // 
  case SIMD_REV16_REG_VEC: group = "Advanced SIMD two-register miscellaneous/REV16 (vector) -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0xe201800; break; // 
  case SIMD_REV32_REG_VEC: group = "Advanced SIMD two-register miscellaneous/REV32 (vector) -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0x2e200800; break; // 
  case SIMD_REV64_REG: group = "Advanced SIMD two-register miscellaneous/REV64 -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0xe200800; break; // 
  case SIMD_SADALP_REG: group = "Advanced SIMD two-register miscellaneous/SADALP -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0xe206800; break; // 
  case SIMD_SADDLP_REG: group = "Advanced SIMD two-register miscellaneous/SADDLP -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0xe202800; break; // 
  case SIMD_SHLL_REG: group = "Advanced SIMD two-register miscellaneous/SHLL, SHLL2 -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0x2e213800; break; // 
  case SIMD_SQABS_REG_VEC: group = "Advanced SIMD two-register miscellaneous/SQABS Vector"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0xe207800; break; // 
  case SIMD_SQNEG_REG_VEC: group = "Advanced SIMD two-register miscellaneous/SQNEG Vector"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0x2e207800; break; // 
  case SIMD_SQXTN_REG_VEC: group = "Advanced SIMD two-register miscellaneous/SQXTN, SQXTN2 Vector"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0xe214800; break; // 
  case SIMD_SQXTUN_REG_VEC: group = "Advanced SIMD two-register miscellaneous/SQXTUN, SQXTUN2 Vector"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0x2e212800; break; // 
  case SIMD_SUQADD_REG_VEC: group = "Advanced SIMD two-register miscellaneous/SUQADD Vector"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0xe203800; break; // 
  case SIMD_UADALP_REG: group = "Advanced SIMD two-register miscellaneous/UADALP -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0x2e206800; break; // 
  case SIMD_UADDLP_REG: group = "Advanced SIMD two-register miscellaneous/UADDLP -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0x2e202800; break; // 
  case SIMD_UQXTN_REG_VEC: group = "Advanced SIMD two-register miscellaneous/UQXTN, UQXTN2 Vector"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0x2e214800; break; // 
  case SIMD_USQADD_REG_VEC: group = "Advanced SIMD two-register miscellaneous/USQADD Vector"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0x2e203800; break; // 
  case SIMD_XTN_REG: group = "Advanced SIMD two-register miscellaneous/XTN, XTN2 -"; mask = 0xbf3ffc00; encoding = (set_mask & ~mask) | 0xe212800; break; // 
  case SIMD_FMOV_IMM_MOD_VEC_FROM_DP: group = "Advanced SIMD modified immediate/FMOV (vector, immediate) Double-precision"; mask = 0xfff8fc00; encoding = (set_mask & ~mask) | 0x6f00f400; break; // 
  case SIMD_MOVI_IMM_MOD_64: group = "Advanced SIMD modified immediate/MOVI 64-bit scalar"; mask = 0xfff8fc00; encoding = (set_mask & ~mask) | 0x2f00e400; break; // 
  case SIMD_MOVI_IMM_MOD_VEC_64: group = "Advanced SIMD modified immediate/MOVI 64-bit vector"; mask = 0xfff8fc00; encoding = (set_mask & ~mask) | 0x6f00e400; break; // 
  case SIMD_LD1_IMM_FOUR_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) Four registers, immediate offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xcdf2000; break; // 
  case SIMD_LD1_IMM_ONE_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) One register, immediate offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xcdf7000; break; // 
  case SIMD_LD1_IMM_THREE_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) Three registers, immediate offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xcdf6000; break; // 
  case SIMD_LD1_IMM_TWO_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) Two registers, immediate offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xcdfa000; break; // 
  case SIMD_LD2_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/LD2 (multiple structures) Immediate offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xcdf8000; break; // 
  case SIMD_LD3_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/LD3 (multiple structures) Immediate offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xcdf4000; break; // 
  case SIMD_LD4_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/LD4 (multiple structures) Immediate offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xcdf0000; break; // 
  case SIMD_ST1_IMM_FOUR_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) Four registers, immediate offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc9f2000; break; // 
  case SIMD_ST1_IMM_ONE_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) One register, immediate offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc9f7000; break; // 
  case SIMD_ST1_IMM_THREE_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) Three registers, immediate offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc9f6000; break; // 
  case SIMD_ST1_IMM_TWO_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) Two registers, immediate offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc9fa000; break; // 
  case SIMD_ST2_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/ST2 (multiple structures) Immediate offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc9f8000; break; // 
  case SIMD_ST3_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/ST3 (multiple structures) Immediate offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc9f4000; break; // 
  case SIMD_ST4_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/ST4 (multiple structures) Immediate offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc9f0000; break; // 
  case SIMD_LD1_FOUR_REG_MULT_STRUCT: group = "Advanced SIMD load/store multiple structures/LD1 (multiple structures) Four registers"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc402000; break; // 
  case SIMD_LD1_ONE_REG_MULT_STRUCT: group = "Advanced SIMD load/store multiple structures/LD1 (multiple structures) One register"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc407000; break; // 
  case SIMD_LD1_THREE_REG_MULT_STRUCT: group = "Advanced SIMD load/store multiple structures/LD1 (multiple structures) Three registers"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc406000; break; // 
  case SIMD_LD1_TWO_REG_MULT_STRUCT: group = "Advanced SIMD load/store multiple structures/LD1 (multiple structures) Two registers"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc40a000; break; // 
  case SIMD_LD2_OFF_MULT_STRUCT: group = "Advanced SIMD load/store multiple structures/LD2 (multiple structures) No offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc408000; break; // 
  case SIMD_LD3_OFF_MULT_STRUCT: group = "Advanced SIMD load/store multiple structures/LD3 (multiple structures) No offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc404000; break; // 
  case SIMD_LD4_OFF_MULT_STRUCT: group = "Advanced SIMD load/store multiple structures/LD4 (multiple structures) No offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc400000; break; // 
  case SIMD_ST1_FOUR_REG_MULT_STRUCT: group = "Advanced SIMD load/store multiple structures/ST1 (multiple structures) Four registers"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc002000; break; // 
  case SIMD_ST1_ONE_REG_MULT_STRUCT: group = "Advanced SIMD load/store multiple structures/ST1 (multiple structures) One register"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc007000; break; // 
  case SIMD_ST1_THREE_REG_MULT_STRUCT: group = "Advanced SIMD load/store multiple structures/ST1 (multiple structures) Three registers"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc006000; break; // 
  case SIMD_ST1_TWO_REG_MULT_STRUCT: group = "Advanced SIMD load/store multiple structures/ST1 (multiple structures) Two registers"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc00a000; break; // 
  case SIMD_ST2_OFF_MULT_STRUCT: group = "Advanced SIMD load/store multiple structures/ST2 (multiple structures) No offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc008000; break; // 
  case SIMD_ST3_OFF_MULT_STRUCT: group = "Advanced SIMD load/store multiple structures/ST3 (multiple structures) No offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc004000; break; // 
  case SIMD_ST4_OFF_MULT_STRUCT: group = "Advanced SIMD load/store multiple structures/ST4 (multiple structures) No offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xc000000; break; // 
  case SIMD_LD1R_OFF_SINGLE_POST_STRUCT: group = "Advanced SIMD load/store single structure (post-indexed)/LD1R Immediate offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xddfc000; break; // 
  case SIMD_LD2R_OFF_SINGLE_POST_STRUCT: group = "Advanced SIMD load/store single structure (post-indexed)/LD2R Immediate offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xdffc000; break; // 
  case SIMD_LD3R_OFF_SINGLE_POST_STRUCT: group = "Advanced SIMD load/store single structure (post-indexed)/LD3R Immediate offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xddfe000; break; // 
  case SIMD_LD4R_OFF_SINGLE_POST_STRUCT: group = "Advanced SIMD load/store single structure (post-indexed)/LD4R Immediate offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xdffe000; break; // 
  case SIMD_LD1R_OFF_SINGLE_STRUCT: group = "Advanced SIMD load/store single structure/LD1R No offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xd40c000; break; // 
  case SIMD_LD2R_OFF_SINGLE_STRUCT: group = "Advanced SIMD load/store single structure/LD2R No offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xd60c000; break; // 
  case SIMD_LD3R_OFF_SINGLE_STRUCT: group = "Advanced SIMD load/store single structure/LD3R No offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xd40e000; break; // 
  case SIMD_LD4R_OFF_SINGLE_STRUCT: group = "Advanced SIMD load/store single structure/LD4R No offset"; mask = 0xbffff000; encoding = (set_mask & ~mask) | 0xd60e000; break; // 
  case FMOV_IMM_FROM_DP: group = "Floating-point immediate/FMOV (scalar, immediate) Double-precision"; mask = 0xffe01fe0; encoding = (set_mask & ~mask) | 0x1e601000; break; // 
  case FMOV_IMM_SINGLE_FROM_SP: group = "Floating-point immediate/FMOV (scalar, immediate) Single-precision"; mask = 0xffe01fe0; encoding = (set_mask & ~mask) | 0x1e201000; break; // 
  case SIMD_FMOV_IMM_MOD_SINGLE_VEC_FROM_SP: group = "Advanced SIMD modified immediate/FMOV (vector, immediate) Single-precision"; mask = 0xbff8fc00; encoding = (set_mask & ~mask) | 0xf00f400; break; // 
  case SIMD_MOVI_IMM_MOD_8: group = "Advanced SIMD modified immediate/MOVI 8-bit"; mask = 0xbff8fc00; encoding = (set_mask & ~mask) | 0xf00e400; break; // 
  case SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_8: group = "Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 8-bit, immediate offset"; mask = 0xbfffe000; encoding = (set_mask & ~mask) | 0xddf0000; break; // 
  case SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_8: group = "Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 8-bit, immediate offset"; mask = 0xbfffe000; encoding = (set_mask & ~mask) | 0xdff0000; break; // 
  case SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_8: group = "Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 8-bit, immediate offset"; mask = 0xbfffe000; encoding = (set_mask & ~mask) | 0xddf2000; break; // 
  case SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_8: group = "Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 8-bit, immediate offset"; mask = 0xbfffe000; encoding = (set_mask & ~mask) | 0xdff2000; break; // 
  case SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_8: group = "Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 8-bit, immediate offset"; mask = 0xbfffe000; encoding = (set_mask & ~mask) | 0xd9f0000; break; // 
  case SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_8: group = "Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 8-bit, immediate offset"; mask = 0xbfffe000; encoding = (set_mask & ~mask) | 0xdbf0000; break; // 
  case SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_8: group = "Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 8-bit, immediate offset"; mask = 0xbfffe000; encoding = (set_mask & ~mask) | 0xd9f2000; break; // 
  case SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_8: group = "Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 8-bit, immediate offset"; mask = 0xbfffe000; encoding = (set_mask & ~mask) | 0xdbf2000; break; // 
  case SIMD_LD1_SINGLE_STRUCT_8: group = "Advanced SIMD load/store single structure/LD1 (single structure) 8-bit"; mask = 0xbfffe000; encoding = (set_mask & ~mask) | 0xd400000; break; // 
  case SIMD_LD2_SINGLE_STRUCT_8: group = "Advanced SIMD load/store single structure/LD2 (single structure) 8-bit"; mask = 0xbfffe000; encoding = (set_mask & ~mask) | 0xd600000; break; // 
  case SIMD_LD3_SINGLE_STRUCT_8: group = "Advanced SIMD load/store single structure/LD3 (single structure) 8-bit"; mask = 0xbfffe000; encoding = (set_mask & ~mask) | 0xd402000; break; // 
  case SIMD_LD4_SINGLE_STRUCT_8: group = "Advanced SIMD load/store single structure/LD4 (single structure) 8-bit"; mask = 0xbfffe000; encoding = (set_mask & ~mask) | 0xd602000; break; // 
  case SIMD_ST1_SINGLE_STRUCT_8: group = "Advanced SIMD load/store single structure/ST1 (single structure) 8-bit"; mask = 0xbfffe000; encoding = (set_mask & ~mask) | 0xd000000; break; // 
  case SIMD_ST2_SINGLE_STRUCT_8: group = "Advanced SIMD load/store single structure/ST2 (single structure) 8-bit"; mask = 0xbfffe000; encoding = (set_mask & ~mask) | 0xd200000; break; // 
  case SIMD_ST3_SINGLE_STRUCT_8: group = "Advanced SIMD load/store single structure/ST3 (single structure) 8-bit"; mask = 0xbfffe000; encoding = (set_mask & ~mask) | 0xd002000; break; // 
  case SIMD_ST4_SINGLE_STRUCT_8: group = "Advanced SIMD load/store single structure/ST4 (single structure) 8-bit"; mask = 0xbfffe000; encoding = (set_mask & ~mask) | 0xd202000; break; // 
  case SIMD_MOVI_SHIFT_IMM_ONES_MOD_32: group = "Advanced SIMD modified immediate/MOVI 32-bit shifting ones"; mask = 0xbff8ec00; encoding = (set_mask & ~mask) | 0xf00c400; break; // 
  case SIMD_MVNI_SHIFT_IMM_ONES_MOD_32: group = "Advanced SIMD modified immediate/MVNI 32-bit shifting ones"; mask = 0xbff8ec00; encoding = (set_mask & ~mask) | 0x2f00c400; break; // 
  case SIMD_BIC_IMM_MOD_VEC_16: group = "Advanced SIMD modified immediate/BIC (vector, immediate) 16-bit"; mask = 0xbff8dc00; encoding = (set_mask & ~mask) | 0x2f009400; break; // 
  case SIMD_MOVI_SHIFT_IMM_MOD_16: group = "Advanced SIMD modified immediate/MOVI 16-bit shifted immediate"; mask = 0xbff8dc00; encoding = (set_mask & ~mask) | 0xf008400; break; // 
  case SIMD_MVNI_SHIFT_IMM_MOD_16: group = "Advanced SIMD modified immediate/MVNI 16-bit shifted immediate"; mask = 0xbff8dc00; encoding = (set_mask & ~mask) | 0x2f008400; break; // 
  case SIMD_ORR_IMM_MOD_VEC_16: group = "Advanced SIMD modified immediate/ORR (vector, immediate) 16-bit"; mask = 0xbff8dc00; encoding = (set_mask & ~mask) | 0xf009400; break; // 
  case ADC_32: group = "Add/subtract (with carry)/ADC 32-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1a000000; break; // 
  case ADC_64: group = "Add/subtract (with carry)/ADC 64-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x9a000000; break; // 
  case ADCS_32: group = "Add/subtract (with carry)/ADCS 32-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x3a000000; break; // 
  case ADCS_64: group = "Add/subtract (with carry)/ADCS 64-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0xba000000; break; // 
  case SBC_32: group = "Add/subtract (with carry)/SBC 32-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x5a000000; break; // 
  case SBC_64: group = "Add/subtract (with carry)/SBC 64-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0xda000000; break; // 
  case SBCS_32: group = "Add/subtract (with carry)/SBCS 32-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x7a000000; break; // 
  case SBCS_64: group = "Add/subtract (with carry)/SBCS 64-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0xfa000000; break; // 
  case SIMD_INS: group = "Advanced SIMD copy/INS (general) -"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x4e001c00; break; // 
  case SIMD_SMOV_32: group = "Advanced SIMD copy/SMOV 32-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0xe002c00; break; // 
  case SIMD_SMOV_64: group = "Advanced SIMD copy/SMOV 64-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x4e002c00; break; // 
  case SIMD_UMOV_32: group = "Advanced SIMD copy/UMOV 32-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0xe003c00; break; // 
  case SIMD_UMOV_64: group = "Advanced SIMD copy/UMOV 64-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x4e003c00; break; // 
  case SIMD_DUP_SCALAR_ELEM: group = "Advanced SIMD scalar copy/DUP (element) Scalar"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x5e000400; break; // 
  case SHA1C_REG: group = "Cryptographic three-register SHA/SHA1C -"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x5e000000; break; // 
  case SHA1M_REG: group = "Cryptographic three-register SHA/SHA1M -"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x5e002000; break; // 
  case SHA1P_REG: group = "Cryptographic three-register SHA/SHA1P -"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x5e001000; break; // 
  case SHA1SU0_REG: group = "Cryptographic three-register SHA/SHA1SU0 -"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x5e003000; break; // 
  case SHA256H_REG: group = "Cryptographic three-register SHA/SHA256H -"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x5e004000; break; // 
  case SHA256H2_REG: group = "Cryptographic three-register SHA/SHA256H2 -"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x5e005000; break; // 
  case SHA256SU1_REG: group = "Cryptographic three-register SHA/SHA256SU1 -"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x5e006000; break; // 
  case ASRV_32: group = "Data-processing (2 source)/ASRV 32-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1ac02800; break; // 
  case ASRV_64: group = "Data-processing (2 source)/ASRV 64-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x9ac02800; break; // 
  case CRC32B: group = "Data-processing (2 source)/CRC32B"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1ac04000; break; // 
  case CRC32CB: group = "Data-processing (2 source)/CRC32CB"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1ac05000; break; // 
  case CRC32CH: group = "Data-processing (2 source)/CRC32CH"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1ac05400; break; // 
  case CRC32CW: group = "Data-processing (2 source)/CRC32CW"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1ac05800; break; // 
  case CRC32CX: group = "Data-processing (2 source)/CRC32CX"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x9ac05c00; break; // 
  case CRC32H: group = "Data-processing (2 source)/CRC32H"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1ac04400; break; // 
  case CRC32W: group = "Data-processing (2 source)/CRC32W"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1ac04800; break; // 
  case CRC32X: group = "Data-processing (2 source)/CRC32X"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x9ac04c00; break; // 
  case LSLV_32: group = "Data-processing (2 source)/LSLV 32-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1ac02000; break; // 
  case LSLV_64: group = "Data-processing (2 source)/LSLV 64-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x9ac02000; break; // 
  case LSRV_32: group = "Data-processing (2 source)/LSRV 32-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1ac02400; break; // 
  case LSRV_64: group = "Data-processing (2 source)/LSRV 64-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x9ac02400; break; // 
  case RORV_32: group = "Data-processing (2 source)/RORV 32-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1ac02c00; break; // 
  case RORV_64: group = "Data-processing (2 source)/RORV 64-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x9ac02c00; break; // 
  case SDIV_32: group = "Data-processing (2 source)/SDIV 32-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1ac00c00; break; // 
  case SDIV_64: group = "Data-processing (2 source)/SDIV 64-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x9ac00c00; break; // 
  case UDIV_32: group = "Data-processing (2 source)/UDIV 32-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1ac00800; break; // 
  case UDIV_64: group = "Data-processing (2 source)/UDIV 64-bit"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x9ac00800; break; // 
  case FADD_FROM_DP: group = "Floating-point data-processing (2 source)/FADD (scalar) Double-precision"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1e602800; break; // 
  case FADD_SINGLE_FROM_SP: group = "Floating-point data-processing (2 source)/FADD (scalar) Single-precision"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1e202800; break; // 
  case FDIV_FROM_DP: group = "Floating-point data-processing (2 source)/FDIV (scalar) Double-precision"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1e601800; break; // 
  case FDIV_SINGLE_FROM_SP: group = "Floating-point data-processing (2 source)/FDIV (scalar) Single-precision"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1e201800; break; // 
  case FMAX_FROM_DP: group = "Floating-point data-processing (2 source)/FMAX (scalar) Double-precision"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1e604800; break; // 
  case FMAX_SINGLE_FROM_SP: group = "Floating-point data-processing (2 source)/FMAX (scalar) Single-precision"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1e204800; break; // 
  case FMAXNM_FROM_DP: group = "Floating-point data-processing (2 source)/FMAXNM (scalar) Double-precision"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1e606800; break; // 
  case FMAXNM_SINGLE_FROM_SP: group = "Floating-point data-processing (2 source)/FMAXNM (scalar) Single-precision"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1e206800; break; // 
  case FMIN_FROM_DP: group = "Floating-point data-processing (2 source)/FMIN (scalar) Double-precision"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1e605800; break; // 
  case FMIN_SINGLE_FROM_SP: group = "Floating-point data-processing (2 source)/FMIN (scalar) Single-precision"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1e205800; break; // 
  case FMINNM_FROM_DP: group = "Floating-point data-processing (2 source)/FMINNM (scalar) Double-precision"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1e607800; break; // 
  case FMINNM_SINGLE_FROM_SP: group = "Floating-point data-processing (2 source)/FMINNM (scalar) Single-precision"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1e207800; break; // 
  case FMUL_FROM_DP: group = "Floating-point data-processing (2 source)/FMUL (scalar) Double-precision"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1e600800; break; // 
  case FMUL_SINGLE_FROM_SP: group = "Floating-point data-processing (2 source)/FMUL (scalar) Single-precision"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1e200800; break; // 
  case FNMUL_FROM_DP: group = "Floating-point data-processing (2 source)/FNMUL Double-precision"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1e608800; break; // 
  case FNMUL_SINGLE_FROM_SP: group = "Floating-point data-processing (2 source)/FNMUL Single-precision"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1e208800; break; // 
  case FSUB_FROM_DP: group = "Floating-point data-processing (2 source)/FSUB (scalar) Double-precision"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1e603800; break; // 
  case FSUB_SINGLE_FROM_SP: group = "Floating-point data-processing (2 source)/FSUB (scalar) Single-precision"; mask = 0xffe0fc00; encoding = (set_mask & ~mask) | 0x1e203800; break; // 
  case SIMD_BIC_IMM_MOD_VEC_32: group = "Advanced SIMD modified immediate/BIC (vector, immediate) 32-bit"; mask = 0xbff89c00; encoding = (set_mask & ~mask) | 0x2f001400; break; // 
  case SIMD_MOVI_SHIFT_IMM_MOD_32: group = "Advanced SIMD modified immediate/MOVI 32-bit shifted immediate"; mask = 0xbff89c00; encoding = (set_mask & ~mask) | 0xf000400; break; // 
  case SIMD_MVNI_SHIFT_IMM_MOD_32: group = "Advanced SIMD modified immediate/MVNI 32-bit shifted immediate"; mask = 0xbff89c00; encoding = (set_mask & ~mask) | 0x2f000400; break; // 
  case SIMD_ORR_IMM_MOD_VEC_32: group = "Advanced SIMD modified immediate/ORR (vector, immediate) 32-bit"; mask = 0xbff89c00; encoding = (set_mask & ~mask) | 0xf001400; break; // 
  case SIMD_FABD_SCALAR: group = "Advanced SIMD scalar three same/FABD Scalar"; mask = 0xffa0fc00; encoding = (set_mask & ~mask) | 0x7ea0d400; break; // 
  case SIMD_FACGE_SCALAR: group = "Advanced SIMD scalar three same/FACGE Scalar"; mask = 0xffa0fc00; encoding = (set_mask & ~mask) | 0x7e20ec00; break; // 
  case SIMD_FACGT_SCALAR: group = "Advanced SIMD scalar three same/FACGT Scalar"; mask = 0xffa0fc00; encoding = (set_mask & ~mask) | 0x7ea0ec00; break; // 
  case SIMD_FCMEQ_REG_SCALAR: group = "Advanced SIMD scalar three same/FCMEQ (register) Scalar"; mask = 0xffa0fc00; encoding = (set_mask & ~mask) | 0x5e20e400; break; // 
  case SIMD_FCMGE_REG_SCALAR: group = "Advanced SIMD scalar three same/FCMGE (register) Scalar"; mask = 0xffa0fc00; encoding = (set_mask & ~mask) | 0x7e20e400; break; // 
  case SIMD_FCMGT_REG_SCALAR: group = "Advanced SIMD scalar three same/FCMGT (register) Scalar"; mask = 0xffa0fc00; encoding = (set_mask & ~mask) | 0x7ea0e400; break; // 
  case SIMD_FMULX_SCALAR: group = "Advanced SIMD scalar three same/FMULX Scalar"; mask = 0xffa0fc00; encoding = (set_mask & ~mask) | 0x5e20dc00; break; // 
  case SIMD_FRECPS_SCALAR: group = "Advanced SIMD scalar three same/FRECPS Scalar"; mask = 0xffa0fc00; encoding = (set_mask & ~mask) | 0x5e20fc00; break; // 
  case SIMD_FRSQRTS_SCALAR: group = "Advanced SIMD scalar three same/FRSQRTS Scalar"; mask = 0xffa0fc00; encoding = (set_mask & ~mask) | 0x5ea0fc00; break; // 
  case FCVTZS_FROM_DP_FP_FIXED_32: group = "Conversions between floating-point and fixed-point/FCVTZS (scalar, fixed-point) Double-precision to 32-bit"; mask = 0xffff0000; encoding = (set_mask & ~mask) | 0x1e580000; break; // 
  case FCVTZS_FROM_DP_FP_FIXED_64: group = "Conversions between floating-point and fixed-point/FCVTZS (scalar, fixed-point) Double-precision to 64-bit"; mask = 0xffff0000; encoding = (set_mask & ~mask) | 0x9e580000; break; // 
  case FCVTZS_SINGLE_FROM_SP_FP_FIXED_32: group = "Conversions between floating-point and fixed-point/FCVTZS (scalar, fixed-point) Single-precision to 32-bit"; mask = 0xffff0000; encoding = (set_mask & ~mask) | 0x1e180000; break; // 
  case FCVTZS_SINGLE_FROM_SP_FP_FIXED_64: group = "Conversions between floating-point and fixed-point/FCVTZS (scalar, fixed-point) Single-precision to 64-bit"; mask = 0xffff0000; encoding = (set_mask & ~mask) | 0x9e180000; break; // 
  case FCVTZU_FROM_DP_FP_FIXED_32: group = "Conversions between floating-point and fixed-point/FCVTZU (scalar, fixed-point) Double-precision to 32-bit"; mask = 0xffff0000; encoding = (set_mask & ~mask) | 0x1e590000; break; // 
  case FCVTZU_FROM_DP_FP_FIXED_64: group = "Conversions between floating-point and fixed-point/FCVTZU (scalar, fixed-point) Double-precision to 64-bit"; mask = 0xffff0000; encoding = (set_mask & ~mask) | 0x9e590000; break; // 
  case FCVTZU_SINGLE_FROM_SP_FP_FIXED_32: group = "Conversions between floating-point and fixed-point/FCVTZU (scalar, fixed-point) Single-precision to 32-bit"; mask = 0xffff0000; encoding = (set_mask & ~mask) | 0x1e190000; break; // 
  case FCVTZU_SINGLE_FROM_SP_FP_FIXED_64: group = "Conversions between floating-point and fixed-point/FCVTZU (scalar, fixed-point) Single-precision to 64-bit"; mask = 0xffff0000; encoding = (set_mask & ~mask) | 0x9e190000; break; // 
  case SCVTF_TO_DP_FP_FIXED_32: group = "Conversions between floating-point and fixed-point/SCVTF (scalar, fixed-point) 32-bit to double-precision"; mask = 0xffff0000; encoding = (set_mask & ~mask) | 0x1e420000; break; // 
  case SCVTF_SINGLE_TO_SP_FP_FIXED_32: group = "Conversions between floating-point and fixed-point/SCVTF (scalar, fixed-point) 32-bit to single-precision"; mask = 0xffff0000; encoding = (set_mask & ~mask) | 0x1e020000; break; // 
  case SCVTF_TO_DP_FP_FIXED_64: group = "Conversions between floating-point and fixed-point/SCVTF (scalar, fixed-point) 64-bit to double-precision"; mask = 0xffff0000; encoding = (set_mask & ~mask) | 0x9e420000; break; // 
  case SCVTF_SINGLE_TO_SP_FP_FIXED_64: group = "Conversions between floating-point and fixed-point/SCVTF (scalar, fixed-point) 64-bit to single-precision"; mask = 0xffff0000; encoding = (set_mask & ~mask) | 0x9e020000; break; // 
  case UCVTF_TO_DP_FP_FIXED_32: group = "Conversions between floating-point and fixed-point/UCVTF (scalar, fixed-point) 32-bit to double-precision"; mask = 0xffff0000; encoding = (set_mask & ~mask) | 0x1e430000; break; // 
  case UCVTF_SINGLE_TO_SP_FP_FIXED_32: group = "Conversions between floating-point and fixed-point/UCVTF (scalar, fixed-point) 32-bit to single-precision"; mask = 0xffff0000; encoding = (set_mask & ~mask) | 0x1e030000; break; // 
  case UCVTF_TO_DP_FP_FIXED_64: group = "Conversions between floating-point and fixed-point/UCVTF (scalar, fixed-point) 64-bit to double-precision"; mask = 0xffff0000; encoding = (set_mask & ~mask) | 0x9e430000; break; // 
  case UCVTF_SINGLE_TO_SP_FP_FIXED_64: group = "Conversions between floating-point and fixed-point/UCVTF (scalar, fixed-point) 64-bit to single-precision"; mask = 0xffff0000; encoding = (set_mask & ~mask) | 0x9e030000; break; // 
  case BRK: group = "Exception generation/BRK -"; mask = 0xffe0001f; encoding = (set_mask & ~mask) | 0xd4200000; break; // 
  case DCPS1: group = "Exception generation/DCPS1 -"; mask = 0xffe0001f; encoding = (set_mask & ~mask) | 0xd4a00001; break; // 
  case DCPS2: group = "Exception generation/DCPS2 -"; mask = 0xffe0001f; encoding = (set_mask & ~mask) | 0xd4a00002; break; // 
  case DCPS3: group = "Exception generation/DCPS3 -"; mask = 0xffe0001f; encoding = (set_mask & ~mask) | 0xd4a00003; break; // 
  case HLT: group = "Exception generation/HLT -"; mask = 0xffe0001f; encoding = (set_mask & ~mask) | 0xd4400000; break; // 
  case HVC: group = "Exception generation/HVC -"; mask = 0xffe0001f; encoding = (set_mask & ~mask) | 0xd4000002; break; // 
  case SMC: group = "Exception generation/SMC -"; mask = 0xffe0001f; encoding = (set_mask & ~mask) | 0xd4000003; break; // 
  case SVC: group = "Exception generation/SVC -"; mask = 0xffe0001f; encoding = (set_mask & ~mask) | 0xd4000001; break; // 
  case SIMD_DUP_VEC_ELEM: group = "Advanced SIMD copy/DUP (element) Vector"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xe000400; break; // 
  case SIMD_DUP: group = "Advanced SIMD copy/DUP (general) -"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xe000c00; break; // 
  case SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_64: group = "Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 64-bit, register offset"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xdc08400; break; // 
  case SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_64: group = "Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 64-bit, register offset"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xde08400; break; // 
  case SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_64: group = "Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 64-bit, register offset"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xdc0a400; break; // 
  case SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_64: group = "Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 64-bit, register offset"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xde0a400; break; // 
  case SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_64: group = "Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 64-bit, register offset"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xd808400; break; // 
  case SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_64: group = "Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 64-bit, register offset"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xda08400; break; // 
  case SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_64: group = "Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 64-bit, register offset"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xd80a400; break; // 
  case SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_64: group = "Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 64-bit, register offset"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xda0a400; break; // 
  case SIMD_TBL_FOUR_REG: group = "Advanced SIMD table lookup/TBL Four register table"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xe006000; break; // 
  case SIMD_TBL_SINGLE_REG: group = "Advanced SIMD table lookup/TBL Single register table"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xe000000; break; // 
  case SIMD_TBL_THREE_REG: group = "Advanced SIMD table lookup/TBL Three register table"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xe004000; break; // 
  case SIMD_TBL_TWO_REG: group = "Advanced SIMD table lookup/TBL Two register table"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xe002000; break; // 
  case SIMD_TBX_FOUR_REG: group = "Advanced SIMD table lookup/TBX Four register table"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xe007000; break; // 
  case SIMD_TBX_SINGLE_REG: group = "Advanced SIMD table lookup/TBX Single register table"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xe001000; break; // 
  case SIMD_TBX_THREE_REG: group = "Advanced SIMD table lookup/TBX Three register table"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xe005000; break; // 
  case SIMD_TBX_TWO_REG: group = "Advanced SIMD table lookup/TBX Two register table"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xe003000; break; // 
  case SIMD_AND_VEC: group = "Advanced SIMD three same/AND (vector) -"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xe201c00; break; // 
  case SIMD_BIC_REG_VEC: group = "Advanced SIMD three same/BIC (vector, register) -"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xe601c00; break; // 
  case SIMD_BIF: group = "Advanced SIMD three same/BIF -"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0x2ee01c00; break; // 
  case SIMD_BIT: group = "Advanced SIMD three same/BIT -"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0x2ea01c00; break; // 
  case SIMD_BSL: group = "Advanced SIMD three same/BSL -"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0x2e601c00; break; // 
  case SIMD_EOR_VEC: group = "Advanced SIMD three same/EOR (vector) -"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0x2e201c00; break; // 
  case SIMD_ORN_VEC: group = "Advanced SIMD three same/ORN (vector) -"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xee01c00; break; // 
  case SIMD_ORR_REG_VEC: group = "Advanced SIMD three same/ORR (vector, register) -"; mask = 0xbfe0fc00; encoding = (set_mask & ~mask) | 0xea01c00; break; // 
  case SIMD_FCVTZS_SHIFT_IMM_SCALAR_VEC_FIXED: group = "Advanced SIMD scalar shift by immediate/FCVTZS (vector, fixed-point) Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x5f00fc00; break; // 
  case SIMD_FCVTZU_SHIFT_IMM_SCALAR_VEC_FIXED: group = "Advanced SIMD scalar shift by immediate/FCVTZU (vector, fixed-point) Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x7f00fc00; break; // 
  case SIMD_SCVTF_SHIFT_IMM_SCALAR_VEC_FIXED: group = "Advanced SIMD scalar shift by immediate/SCVTF (vector, fixed-point) Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x5f00e400; break; // 
  case SIMD_SHL_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/SHL Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x5f005400; break; // 
  case SIMD_SLI_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/SLI Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x7f005400; break; // 
  case SIMD_SQRSHRN_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/SQRSHRN, SQRSHRN2 Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x5f009c00; break; // 
  case SIMD_SQRSHRUN_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/SQRSHRUN, SQRSHRUN2 Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x7f008c00; break; // 
  case SIMD_SQSHL_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/SQSHL (immediate) Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x5f007400; break; // 
  case SIMD_SQSHLU_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/SQSHLU Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x7f006400; break; // 
  case SIMD_SQSHRN_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/SQSHRN, SQSHRN2 Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x5f009400; break; // 
  case SIMD_SQSHRUN_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/SQSHRUN, SQSHRUN2 Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x7f008400; break; // 
  case SIMD_SRI_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/SRI Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x7f004400; break; // 
  case SIMD_SRSHR_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/SRSHR Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x5f002400; break; // 
  case SIMD_SRSRA_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/SRSRA Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x5f003400; break; // 
  case SIMD_SSHR_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/SSHR Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x5f000400; break; // 
  case SIMD_SSRA_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/SSRA Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x5f001400; break; // 
  case SIMD_UCVTF_SHIFT_IMM_SCALAR_VEC_FIXED: group = "Advanced SIMD scalar shift by immediate/UCVTF (vector, fixed-point) Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x7f00e400; break; // 
  case SIMD_UQRSHRN_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/UQRSHRN, UQRSHRN2 Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x7f009c00; break; // 
  case SIMD_UQSHL_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/UQSHL (immediate) Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x7f007400; break; // 
  case SIMD_UQSHRN_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/UQSHRN Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x7f009400; break; // 
  case SIMD_URSHR_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/URSHR Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x7f002400; break; // 
  case SIMD_URSRA_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/URSRA Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x7f003400; break; // 
  case SIMD_USHR_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/USHR Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x7f000400; break; // 
  case SIMD_USRA_SHIFT_IMM_SCALAR: group = "Advanced SIMD scalar shift by immediate/USRA Scalar"; mask = 0xff80fc00; encoding = (set_mask & ~mask) | 0x7f001400; break; // 
  case SIMD_SQDMLAL_SCALAR_VEC: group = "Advanced SIMD scalar three different/SQDMLAL, SQDMLAL2 (vector) Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x5e209000; break; // 
  case SIMD_SQDMLSL_SCALAR_VEC: group = "Advanced SIMD scalar three different/SQDMLSL, SQDMLSL2 (vector) Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x5e20b000; break; // 
  case SIMD_SQDMULL_SCALAR_VEC: group = "Advanced SIMD scalar three different/SQDMULL, SQDMULL2 (vector) Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x5e20d000; break; // 
  case SIMD_ADD_SCALAR_VEC: group = "Advanced SIMD scalar three same/ADD (vector) Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x5e208400; break; // 
  case SIMD_CMEQ_REG_SCALAR: group = "Advanced SIMD scalar three same/CMEQ (register) Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x7e208c00; break; // 
  case SIMD_CMGE_REG_SCALAR: group = "Advanced SIMD scalar three same/CMGE (register) Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x5e203c00; break; // 
  case SIMD_CMGT_REG_SCALAR: group = "Advanced SIMD scalar three same/CMGT (register) Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x5e203400; break; // 
  case SIMD_CMHI_REG_SCALAR: group = "Advanced SIMD scalar three same/CMHI (register) Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x7e203400; break; // 
  case SIMD_CMHS_REG_SCALAR: group = "Advanced SIMD scalar three same/CMHS (register) Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x7e203c00; break; // 
  case SIMD_CMTST_SCALAR: group = "Advanced SIMD scalar three same/CMTST Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x5e208c00; break; // 
  case SIMD_SQADD_SCALAR: group = "Advanced SIMD scalar three same/SQADD Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x5e200c00; break; // 
  case SIMD_SQDMULH_SCALAR_VEC: group = "Advanced SIMD scalar three same/SQDMULH (vector) Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x5e20b400; break; // 
  case SIMD_SQRDMULH_SCALAR_VEC: group = "Advanced SIMD scalar three same/SQRDMULH (vector) Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x7e20b400; break; // 
  case SIMD_SQRSHL_SCALAR: group = "Advanced SIMD scalar three same/SQRSHL Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x5e205c00; break; // 
  case SIMD_SQSHL_REG_SCALAR: group = "Advanced SIMD scalar three same/SQSHL (register) Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x5e204c00; break; // 
  case SIMD_SQSUB_SCALAR: group = "Advanced SIMD scalar three same/SQSUB Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x5e202c00; break; // 
  case SIMD_SRSHL_SCALAR: group = "Advanced SIMD scalar three same/SRSHL Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x5e205400; break; // 
  case SIMD_SSHL_SCALAR: group = "Advanced SIMD scalar three same/SSHL Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x5e204400; break; // 
  case SIMD_SUB_SCALAR_VEC: group = "Advanced SIMD scalar three same/SUB (vector) Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x7e208400; break; // 
  case SIMD_UQADD_SCALAR: group = "Advanced SIMD scalar three same/UQADD Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x7e200c00; break; // 
  case SIMD_UQRSHL_SCALAR: group = "Advanced SIMD scalar three same/UQRSHL Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x7e205c00; break; // 
  case SIMD_UQSHL_REG_SCALAR: group = "Advanced SIMD scalar three same/UQSHL (register) Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x7e204c00; break; // 
  case SIMD_UQSUB_SCALAR: group = "Advanced SIMD scalar three same/UQSUB Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x7e202c00; break; // 
  case SIMD_URSHL_SCALAR: group = "Advanced SIMD scalar three same/URSHL Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x7e205400; break; // 
  case SIMD_USHL_SCALAR: group = "Advanced SIMD scalar three same/USHL Scalar"; mask = 0xff20fc00; encoding = (set_mask & ~mask) | 0x7e204400; break; // 
  case SIMD_FABD_VEC: group = "Advanced SIMD three same/FABD Vector"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0x2ea0d400; break; // 
  case SIMD_FACGE_VEC: group = "Advanced SIMD three same/FACGE Vector"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0x2e20ec00; break; // 
  case SIMD_FACGT_VEC: group = "Advanced SIMD three same/FACGT Vector"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0x2ea0ec00; break; // 
  case SIMD_FADD_VEC: group = "Advanced SIMD three same/FADD (vector) -"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0xe20d400; break; // 
  case SIMD_FADDP_VEC: group = "Advanced SIMD three same/FADDP (vector) -"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0x2e20d400; break; // 
  case SIMD_FCMEQ_REG_VEC: group = "Advanced SIMD three same/FCMEQ (register) Vector"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0xe20e400; break; // 
  case SIMD_FCMGE_REG_VEC: group = "Advanced SIMD three same/FCMGE (register) Vector"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0x2e20e400; break; // 
  case SIMD_FCMGT_REG_VEC: group = "Advanced SIMD three same/FCMGT (register) Vector"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0x2ea0e400; break; // 
  case SIMD_FDIV_VEC: group = "Advanced SIMD three same/FDIV (vector) -"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0x2e20fc00; break; // 
  case SIMD_FMAX_VEC: group = "Advanced SIMD three same/FMAX (vector) -"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0xe20f400; break; // 
  case SIMD_FMAXNM_VEC: group = "Advanced SIMD three same/FMAXNM (vector) -"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0xe20c400; break; // 
  case SIMD_FMAXNMP_VEC: group = "Advanced SIMD three same/FMAXNMP (vector) -"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0x2e20c400; break; // 
  case SIMD_FMAXP_VEC: group = "Advanced SIMD three same/FMAXP (vector) -"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0x2e20f400; break; // 
  case SIMD_FMIN_VEC: group = "Advanced SIMD three same/FMIN (vector) -"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0xea0f400; break; // 
  case SIMD_FMINNM_VEC: group = "Advanced SIMD three same/FMINNM (vector) -"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0xea0c400; break; // 
  case SIMD_FMINNMP_VEC: group = "Advanced SIMD three same/FMINNMP (vector) -"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0x2ea0c400; break; // 
  case SIMD_FMINP_VEC: group = "Advanced SIMD three same/FMINP (vector) -"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0x2ea0f400; break; // 
  case SIMD_FMLA_VEC: group = "Advanced SIMD three same/FMLA (vector) -"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0xe20cc00; break; // 
  case SIMD_FMLS_VEC: group = "Advanced SIMD three same/FMLS (vector) -"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0xea0cc00; break; // 
  case SIMD_FMUL_VEC: group = "Advanced SIMD three same/FMUL (vector) -"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0x2e20dc00; break; // 
  case SIMD_FMULX_VEC: group = "Advanced SIMD three same/FMULX Vector"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0xe20dc00; break; // 
  case SIMD_FRECPS_VEC: group = "Advanced SIMD three same/FRECPS Vector"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0xe20fc00; break; // 
  case SIMD_FRSQRTS_VEC: group = "Advanced SIMD three same/FRSQRTS Vector"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0xea0fc00; break; // 
  case SIMD_FSUB_VEC: group = "Advanced SIMD three same/FSUB (vector) -"; mask = 0xbfa0fc00; encoding = (set_mask & ~mask) | 0xea0d400; break; // 
  case SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_32: group = "Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 32-bit, register offset"; mask = 0xbfe0ec00; encoding = (set_mask & ~mask) | 0xdc08000; break; // 
  case SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_32: group = "Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 32-bit, register offset"; mask = 0xbfe0ec00; encoding = (set_mask & ~mask) | 0xde08000; break; // 
  case SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_32: group = "Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 32-bit, register offset"; mask = 0xbfe0ec00; encoding = (set_mask & ~mask) | 0xdc0a000; break; // 
  case SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_32: group = "Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 32-bit, register offset"; mask = 0xbfe0ec00; encoding = (set_mask & ~mask) | 0xde0a000; break; // 
  case SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_32: group = "Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 32-bit, register offset"; mask = 0xbfe0ec00; encoding = (set_mask & ~mask) | 0xd808000; break; // 
  case SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_32: group = "Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 32-bit, register offset"; mask = 0xbfe0ec00; encoding = (set_mask & ~mask) | 0xda08000; break; // 
  case SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_32: group = "Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 32-bit, register offset"; mask = 0xbfe0ec00; encoding = (set_mask & ~mask) | 0xd80a000; break; // 
  case SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_32: group = "Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 32-bit, register offset"; mask = 0xbfe0ec00; encoding = (set_mask & ~mask) | 0xda0a000; break; // 
  case SIMD_LD1_FOUR_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) Four registers, register offset"; mask = 0xbfe0f000; encoding = (set_mask & ~mask) | 0xcc02000; break; // 
  case SIMD_LD1_ONE_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) One register, register offset"; mask = 0xbfe0f000; encoding = (set_mask & ~mask) | 0xcc07000; break; // 
  case SIMD_LD1_THREE_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) Three registers, register offset"; mask = 0xbfe0f000; encoding = (set_mask & ~mask) | 0xcc06000; break; // 
  case SIMD_LD1_TWO_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) Two registers, register offset"; mask = 0xbfe0f000; encoding = (set_mask & ~mask) | 0xcc0a000; break; // 
  case SIMD_LD2_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/LD2 (multiple structures) Register offset"; mask = 0xbfe0f000; encoding = (set_mask & ~mask) | 0xcc08000; break; // 
  case SIMD_LD3_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/LD3 (multiple structures) Register offset"; mask = 0xbfe0f000; encoding = (set_mask & ~mask) | 0xcc04000; break; // 
  case SIMD_LD4_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/LD4 (multiple structures) Register offset"; mask = 0xbfe0f000; encoding = (set_mask & ~mask) | 0xcc00000; break; // 
  case SIMD_ST1_FOUR_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) Four registers, register offset"; mask = 0xbfe0f000; encoding = (set_mask & ~mask) | 0xc802000; break; // 
  case SIMD_ST1_ONE_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) One register, register offset"; mask = 0xbfe0f000; encoding = (set_mask & ~mask) | 0xc807000; break; // 
  case SIMD_ST1_THREE_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) Three registers, register offset"; mask = 0xbfe0f000; encoding = (set_mask & ~mask) | 0xc806000; break; // 
  case SIMD_ST1_TWO_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) Two registers, register offset"; mask = 0xbfe0f000; encoding = (set_mask & ~mask) | 0xc80a000; break; // 
  case SIMD_ST2_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/ST2 (multiple structures) Register offset"; mask = 0xbfe0f000; encoding = (set_mask & ~mask) | 0xc808000; break; // 
  case SIMD_ST3_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/ST3 (multiple structures) Register offset"; mask = 0xbfe0f000; encoding = (set_mask & ~mask) | 0xc804000; break; // 
  case SIMD_ST4_REG_OFF_MULT_POST_STRUCT: group = "Advanced SIMD load/store multiple structures (post-indexed)/ST4 (multiple structures) Register offset"; mask = 0xbfe0f000; encoding = (set_mask & ~mask) | 0xc800000; break; // 
  case SIMD_LD1R_REG_OFF_SINGLE_POST_STRUCT: group = "Advanced SIMD load/store single structure (post-indexed)/LD1R Register offset"; mask = 0xbfe0f000; encoding = (set_mask & ~mask) | 0xdc0c000; break; // 
  case SIMD_LD2R_REG_OFF_SINGLE_POST_STRUCT: group = "Advanced SIMD load/store single structure (post-indexed)/LD2R Register offset"; mask = 0xbfe0f000; encoding = (set_mask & ~mask) | 0xde0c000; break; // 
  case SIMD_LD3R_REG_OFF_SINGLE_POST_STRUCT: group = "Advanced SIMD load/store single structure (post-indexed)/LD3R Register offset"; mask = 0xbfe0f000; encoding = (set_mask & ~mask) | 0xdc0e000; break; // 
  case SIMD_LD4R_REG_OFF_SINGLE_POST_STRUCT: group = "Advanced SIMD load/store single structure (post-indexed)/LD4R Register offset"; mask = 0xbfe0f000; encoding = (set_mask & ~mask) | 0xde0e000; break; // 
  case SIMD_FCVTZS_SHIFT_IMM_VEC_VEC_FIXED: group = "Advanced SIMD shift by immediate/FCVTZS (vector, fixed-point) Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0xf00fc00; break; // 
  case SIMD_FCVTZU_SHIFT_IMM_VEC_VEC_FIXED: group = "Advanced SIMD shift by immediate/FCVTZU (vector, fixed-point) Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0x2f00fc00; break; // 
  case SIMD_RSHRN_SHIFT_IMM: group = "Advanced SIMD shift by immediate/RSHRN, RSHRN2 -"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0xf008c00; break; // 
  case SIMD_SCVTF_SHIFT_IMM_VEC_VEC_FIXED: group = "Advanced SIMD shift by immediate/SCVTF (vector, fixed-point) Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0xf00e400; break; // 
  case SIMD_SHL_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/SHL Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0xf005400; break; // 
  case SIMD_SHRN_SHIFT_IMM: group = "Advanced SIMD shift by immediate/SHRN, SHRN2 -"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0xf008400; break; // 
  case SIMD_SLI_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/SLI Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0x2f005400; break; // 
  case SIMD_SQRSHRN_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/SQRSHRN, SQRSHRN2 Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0xf009c00; break; // 
  case SIMD_SQRSHRUN_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/SQRSHRUN, SQRSHRUN2 Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0x2f008c00; break; // 
  case SIMD_SQSHL_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/SQSHL (immediate) Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0xf007400; break; // 
  case SIMD_SQSHLU_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/SQSHLU Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0x2f006400; break; // 
  case SIMD_SQSHRN_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/SQSHRN, SQSHRN2 Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0xf009400; break; // 
  case SIMD_SQSHRUN_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/SQSHRUN, SQSHRUN2 Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0x2f008400; break; // 
  case SIMD_SRI_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/SRI Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0x2f004400; break; // 
  case SIMD_SRSHR_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/SRSHR Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0xf002400; break; // 
  case SIMD_SRSRA_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/SRSRA Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0xf003400; break; // 
  case SIMD_SSHLL_SHIFT_IMM: group = "Advanced SIMD shift by immediate/SSHLL, SSHLL2 -"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0xf00a400; break; // 
  case SIMD_SSHR_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/SSHR Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0xf000400; break; // 
  case SIMD_SSRA_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/SSRA Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0xf001400; break; // 
  case SIMD_UCVTF_SHIFT_IMM_VEC_VEC_FIXED: group = "Advanced SIMD shift by immediate/UCVTF (vector, fixed-point) Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0x2f00e400; break; // 
  case SIMD_UQRSHRN_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/UQRSHRN, UQRSHRN2 Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0x2f009c00; break; // 
  case SIMD_UQSHL_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/UQSHL (immediate) Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0x2f007400; break; // 
  case SIMD_UQSHRN_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/UQSHRN Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0x2f009400; break; // 
  case SIMD_URSHR_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/URSHR Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0x2f002400; break; // 
  case SIMD_URSRA_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/URSRA Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0x2f003400; break; // 
  case SIMD_USHLL_SHIFT_IMM: group = "Advanced SIMD shift by immediate/USHLL, USHLL2 -"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0x2f00a400; break; // 
  case SIMD_USHR_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/USHR Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0x2f000400; break; // 
  case SIMD_USRA_SHIFT_IMM_VEC: group = "Advanced SIMD shift by immediate/USRA Vector"; mask = 0xbf80fc00; encoding = (set_mask & ~mask) | 0x2f001400; break; // 
  case SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_16: group = "Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 16-bit, register offset"; mask = 0xbfe0e400; encoding = (set_mask & ~mask) | 0xdc04000; break; // 
  case SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_16: group = "Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 16-bit, register offset"; mask = 0xbfe0e400; encoding = (set_mask & ~mask) | 0xde04000; break; // 
  case SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_16: group = "Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 16-bit, register offset"; mask = 0xbfe0e400; encoding = (set_mask & ~mask) | 0xdc06000; break; // 
  case SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_16: group = "Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 16-bit, register offset"; mask = 0xbfe0e400; encoding = (set_mask & ~mask) | 0xde06000; break; // 
  case SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_16: group = "Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 16-bit, register offset"; mask = 0xbfe0e400; encoding = (set_mask & ~mask) | 0xd804000; break; // 
  case SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_16: group = "Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 16-bit, register offset"; mask = 0xbfe0e400; encoding = (set_mask & ~mask) | 0xda04000; break; // 
  case SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_16: group = "Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 16-bit, register offset"; mask = 0xbfe0e400; encoding = (set_mask & ~mask) | 0xd806000; break; // 
  case SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_16: group = "Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 16-bit, register offset"; mask = 0xbfe0e400; encoding = (set_mask & ~mask) | 0xda06000; break; // 
  case SIMD_TRN1: group = "Advanced SIMD permute/TRN1 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe002800; break; // 
  case SIMD_TRN2: group = "Advanced SIMD permute/TRN2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe006800; break; // 
  case SIMD_UZP1: group = "Advanced SIMD permute/UZP1 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe001800; break; // 
  case SIMD_UZP2: group = "Advanced SIMD permute/UZP2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe005800; break; // 
  case SIMD_ZIP1: group = "Advanced SIMD permute/ZIP1 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe003800; break; // 
  case SIMD_ZIP2: group = "Advanced SIMD permute/ZIP2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe007800; break; // 
  case SIMD_ADDHN: group = "Advanced SIMD three different/ADDHN, ADDHN2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe204000; break; // 
  case SIMD_PMULL: group = "Advanced SIMD three different/PMULL, PMULL2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe20e000; break; // 
  case SIMD_RADDHN: group = "Advanced SIMD three different/RADDHN, RADDHN2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e204000; break; // 
  case SIMD_RSUBHN: group = "Advanced SIMD three different/RSUBHN, RSUBHN2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e206000; break; // 
  case SIMD_SABAL: group = "Advanced SIMD three different/SABAL, SABAL2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe205000; break; // 
  case SIMD_SABDL: group = "Advanced SIMD three different/SABDL, SABDL2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe207000; break; // 
  case SIMD_SADDL: group = "Advanced SIMD three different/SADDL, SADDL2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe200000; break; // 
  case SIMD_SADDW: group = "Advanced SIMD three different/SADDW, SADDW2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe201000; break; // 
  case SIMD_SMLAL_VEC: group = "Advanced SIMD three different/SMLAL, SMLAL2 (vector) -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe208000; break; // 
  case SIMD_SMLSL_VEC: group = "Advanced SIMD three different/SMLSL, SMLSL2 (vector) -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe20a000; break; // 
  case SIMD_SMULL_VEC: group = "Advanced SIMD three different/SMULL, SMULL2 (vector) -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe20c000; break; // 
  case SIMD_SQDMLAL_VEC_VEC: group = "Advanced SIMD three different/SQDMLAL, SQDMLAL2 (vector) Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe209000; break; // 
  case SIMD_SQDMLSL_VEC_VEC: group = "Advanced SIMD three different/SQDMLSL, SQDMLSL2 (vector) Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe20b000; break; // 
  case SIMD_SQDMULL_VEC_VEC: group = "Advanced SIMD three different/SQDMULL, SQDMULL2 (vector) Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe20d000; break; // 
  case SIMD_SSUBL: group = "Advanced SIMD three different/SSUBL, SSUBL2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe202000; break; // 
  case SIMD_SSUBW: group = "Advanced SIMD three different/SSUBW, SSUBW2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe203000; break; // 
  case SIMD_SUBHN: group = "Advanced SIMD three different/SUBHN, SUBHN2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe206000; break; // 
  case SIMD_UABAL: group = "Advanced SIMD three different/UABAL, UABAL2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e205000; break; // 
  case SIMD_UABDL: group = "Advanced SIMD three different/UABDL, UABDL2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e207000; break; // 
  case SIMD_UADDL: group = "Advanced SIMD three different/UADDL, UADDL2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e200000; break; // 
  case SIMD_UADDW: group = "Advanced SIMD three different/UADDW, UADDW2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e201000; break; // 
  case SIMD_UMLAL_VEC: group = "Advanced SIMD three different/UMLAL, UMLAL2 (vector) -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e208000; break; // 
  case SIMD_UMLSL_VEC: group = "Advanced SIMD three different/UMLSL, UMLSL2 (vector) -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e20a000; break; // 
  case SIMD_UMULL_VEC: group = "Advanced SIMD three different/UMULL, UMULL2 (vector) -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e20c000; break; // 
  case SIMD_USUBL: group = "Advanced SIMD three different/USUBL, USUBL2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e202000; break; // 
  case SIMD_USUBW: group = "Advanced SIMD three different/USUBW, USUBW2 -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e203000; break; // 
  case SIMD_ADD_VEC_VEC: group = "Advanced SIMD three same/ADD (vector) Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe208400; break; // 
  case SIMD_ADDP_VEC: group = "Advanced SIMD three same/ADDP (vector) -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe20bc00; break; // 
  case SIMD_CMEQ_REG_VEC: group = "Advanced SIMD three same/CMEQ (register) Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e208c00; break; // 
  case SIMD_CMGE_REG_VEC: group = "Advanced SIMD three same/CMGE (register) Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe203c00; break; // 
  case SIMD_CMGT_REG_VEC: group = "Advanced SIMD three same/CMGT (register) Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe203400; break; // 
  case SIMD_CMHI_REG_VEC: group = "Advanced SIMD three same/CMHI (register) Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e203400; break; // 
  case SIMD_CMHS_REG_VEC: group = "Advanced SIMD three same/CMHS (register) Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e203c00; break; // 
  case SIMD_CMTST_VEC: group = "Advanced SIMD three same/CMTST Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe208c00; break; // 
  case SIMD_MLA_VEC: group = "Advanced SIMD three same/MLA (vector) -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe209400; break; // 
  case SIMD_MLS_VEC: group = "Advanced SIMD three same/MLS (vector) -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e209400; break; // 
  case SIMD_MUL_VEC: group = "Advanced SIMD three same/MUL (vector) -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe209c00; break; // 
  case SIMD_PMUL: group = "Advanced SIMD three same/PMUL -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e209c00; break; // 
  case SIMD_SABA: group = "Advanced SIMD three same/SABA -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe207c00; break; // 
  case SIMD_SABD: group = "Advanced SIMD three same/SABD -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe207400; break; // 
  case SIMD_SHADD: group = "Advanced SIMD three same/SHADD -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe200400; break; // 
  case SIMD_SHSUB: group = "Advanced SIMD three same/SHSUB -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe202400; break; // 
  case SIMD_SMAX: group = "Advanced SIMD three same/SMAX -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe206400; break; // 
  case SIMD_SMAXP: group = "Advanced SIMD three same/SMAXP -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe20a400; break; // 
  case SIMD_SMIN: group = "Advanced SIMD three same/SMIN -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe206c00; break; // 
  case SIMD_SMINP: group = "Advanced SIMD three same/SMINP -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe20ac00; break; // 
  case SIMD_SQADD_VEC: group = "Advanced SIMD three same/SQADD Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe200c00; break; // 
  case SIMD_SQDMULH_VEC_VEC: group = "Advanced SIMD three same/SQDMULH (vector) Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe20b400; break; // 
  case SIMD_SQRDMULH_VEC_VEC: group = "Advanced SIMD three same/SQRDMULH (vector) Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e20b400; break; // 
  case SIMD_SQRSHL_VEC: group = "Advanced SIMD three same/SQRSHL Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe205c00; break; // 
  case SIMD_SQSHL_REG_VEC: group = "Advanced SIMD three same/SQSHL (register) Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe204c00; break; // 
  case SIMD_SQSUB_VEC: group = "Advanced SIMD three same/SQSUB Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe202c00; break; // 
  case SIMD_SRHADD: group = "Advanced SIMD three same/SRHADD -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe201400; break; // 
  case SIMD_SRSHL_VEC: group = "Advanced SIMD three same/SRSHL Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe205400; break; // 
  case SIMD_SSHL_VEC: group = "Advanced SIMD three same/SSHL Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0xe204400; break; // 
  case SIMD_SUB_VEC_VEC: group = "Advanced SIMD three same/SUB (vector) Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e208400; break; // 
  case SIMD_UABA: group = "Advanced SIMD three same/UABA -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e207c00; break; // 
  case SIMD_UABD: group = "Advanced SIMD three same/UABD -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e207400; break; // 
  case SIMD_UHADD: group = "Advanced SIMD three same/UHADD -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e200400; break; // 
  case SIMD_UHSUB: group = "Advanced SIMD three same/UHSUB -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e202400; break; // 
  case SIMD_UMAX: group = "Advanced SIMD three same/UMAX -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e206400; break; // 
  case SIMD_UMAXP: group = "Advanced SIMD three same/UMAXP -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e20a400; break; // 
  case SIMD_UMIN: group = "Advanced SIMD three same/UMIN -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e206c00; break; // 
  case SIMD_UMINP: group = "Advanced SIMD three same/UMINP -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e20ac00; break; // 
  case SIMD_UQADD_VEC: group = "Advanced SIMD three same/UQADD Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e200c00; break; // 
  case SIMD_UQRSHL_VEC: group = "Advanced SIMD three same/UQRSHL Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e205c00; break; // 
  case SIMD_UQSHL_REG_VEC: group = "Advanced SIMD three same/UQSHL (register) Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e204c00; break; // 
  case SIMD_UQSUB_VEC: group = "Advanced SIMD three same/UQSUB Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e202c00; break; // 
  case SIMD_URHADD: group = "Advanced SIMD three same/URHADD -"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e201400; break; // 
  case SIMD_URSHL_VEC: group = "Advanced SIMD three same/URSHL Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e205400; break; // 
  case SIMD_USHL_VEC: group = "Advanced SIMD three same/USHL Vector"; mask = 0xbf20fc00; encoding = (set_mask & ~mask) | 0x2e204400; break; // 
  case SIMD_FMLA_SCALAR_ELEM: group = "Advanced SIMD scalar x indexed element/FMLA (by element) Scalar"; mask = 0xff80f400; encoding = (set_mask & ~mask) | 0x5f801000; break; // 
  case SIMD_FMLS_SCALAR_ELEM: group = "Advanced SIMD scalar x indexed element/FMLS (by element) Scalar"; mask = 0xff80f400; encoding = (set_mask & ~mask) | 0x5f805000; break; // 
  case SIMD_FMUL_SCALAR_ELEM: group = "Advanced SIMD scalar x indexed element/FMUL (by element) Scalar"; mask = 0xff80f400; encoding = (set_mask & ~mask) | 0x5f809000; break; // 
  case SIMD_FMULX_SCALAR_ELEM: group = "Advanced SIMD scalar x indexed element/FMULX (by element) Scalar"; mask = 0xff80f400; encoding = (set_mask & ~mask) | 0x7f809000; break; // 
  case CCMN_IMM_32: group = "Conditional compare (immediate)/CCMN (immediate) 32-bit"; mask = 0xffe00c10; encoding = (set_mask & ~mask) | 0x3a400800; break; // 
  case CCMN_IMM_64: group = "Conditional compare (immediate)/CCMN (immediate) 64-bit"; mask = 0xffe00c10; encoding = (set_mask & ~mask) | 0xba400800; break; // 
  case CCMP_IMM_32: group = "Conditional compare (immediate)/CCMP (immediate) 32-bit"; mask = 0xffe00c10; encoding = (set_mask & ~mask) | 0x7a400800; break; // 
  case CCMP_IMM_64: group = "Conditional compare (immediate)/CCMP (immediate) 64-bit"; mask = 0xffe00c10; encoding = (set_mask & ~mask) | 0xfa400800; break; // 
  case CCMN_REG_32: group = "Conditional compare (register)/CCMN (register) 32-bit"; mask = 0xffe00c10; encoding = (set_mask & ~mask) | 0x3a400000; break; // 
  case CCMN_REG_64: group = "Conditional compare (register)/CCMN (register) 64-bit"; mask = 0xffe00c10; encoding = (set_mask & ~mask) | 0xba400000; break; // 
  case CCMP_REG_32: group = "Conditional compare (register)/CCMP (register) 32-bit"; mask = 0xffe00c10; encoding = (set_mask & ~mask) | 0x7a400000; break; // 
  case CCMP_REG_64: group = "Conditional compare (register)/CCMP (register) 64-bit"; mask = 0xffe00c10; encoding = (set_mask & ~mask) | 0xfa400000; break; // 
  case FCCMP_FROM_DP: group = "Floating-point conditional compare/FCCMP Double-precision"; mask = 0xffe00c10; encoding = (set_mask & ~mask) | 0x1e600400; break; // 
  case FCCMP_SINGLE_FROM_SP: group = "Floating-point conditional compare/FCCMP Single-precision"; mask = 0xffe00c10; encoding = (set_mask & ~mask) | 0x1e200400; break; // 
  case FCCMPE_FROM_DP: group = "Floating-point conditional compare/FCCMPE Double-precision"; mask = 0xffe00c10; encoding = (set_mask & ~mask) | 0x1e600410; break; // 
  case FCCMPE_SINGLE_FROM_SP: group = "Floating-point conditional compare/FCCMPE Single-precision"; mask = 0xffe00c10; encoding = (set_mask & ~mask) | 0x1e200410; break; // 
  case SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_8: group = "Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 8-bit, register offset"; mask = 0xbfe0e000; encoding = (set_mask & ~mask) | 0xdc00000; break; // 
  case SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_8: group = "Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 8-bit, register offset"; mask = 0xbfe0e000; encoding = (set_mask & ~mask) | 0xde00000; break; // 
  case SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_8: group = "Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 8-bit, register offset"; mask = 0xbfe0e000; encoding = (set_mask & ~mask) | 0xdc02000; break; // 
  case SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_8: group = "Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 8-bit, register offset"; mask = 0xbfe0e000; encoding = (set_mask & ~mask) | 0xde02000; break; // 
  case SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_8: group = "Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 8-bit, register offset"; mask = 0xbfe0e000; encoding = (set_mask & ~mask) | 0xd800000; break; // 
  case SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_8: group = "Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 8-bit, register offset"; mask = 0xbfe0e000; encoding = (set_mask & ~mask) | 0xda00000; break; // 
  case SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_8: group = "Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 8-bit, register offset"; mask = 0xbfe0e000; encoding = (set_mask & ~mask) | 0xd802000; break; // 
  case SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_8: group = "Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 8-bit, register offset"; mask = 0xbfe0e000; encoding = (set_mask & ~mask) | 0xda02000; break; // 
  case SYS: group = "System/SYS -"; mask = 0xfff80000; encoding = (set_mask & ~mask) | 0xd5080000; break; // 
  case SYSL: group = "System/SYSL -"; mask = 0xfff80000; encoding = (set_mask & ~mask) | 0xd5280000; break; // 
  case SIMD_SQDMLAL_SCALAR_ELEM: group = "Advanced SIMD scalar x indexed element/SQDMLAL, SQDMLAL2 (by element) Scalar"; mask = 0xff00f400; encoding = (set_mask & ~mask) | 0x5f003000; break; // 
  case SIMD_SQDMLSL_SCALAR_ELEM: group = "Advanced SIMD scalar x indexed element/SQDMLSL, SQDMLSL2 (by element) Scalar"; mask = 0xff00f400; encoding = (set_mask & ~mask) | 0x5f007000; break; // 
  case SIMD_SQDMULH_SCALAR_ELEM: group = "Advanced SIMD scalar x indexed element/SQDMULH (by element) Scalar"; mask = 0xff00f400; encoding = (set_mask & ~mask) | 0x5f00c000; break; // 
  case SIMD_SQDMULL_SCALAR_ELEM: group = "Advanced SIMD scalar x indexed element/SQDMULL, SQDMULL2 (by element) Scalar"; mask = 0xff00f400; encoding = (set_mask & ~mask) | 0x5f00b000; break; // 
  case SIMD_SQRDMULH_SCALAR_ELEM: group = "Advanced SIMD scalar x indexed element/SQRDMULH (by element) Scalar"; mask = 0xff00f400; encoding = (set_mask & ~mask) | 0x5f00d000; break; // 
  case SIMD_FMLA_VEC_VEC_ELEM: group = "Advanced SIMD vector x indexed element/FMLA (by element) Vector"; mask = 0xbf80f400; encoding = (set_mask & ~mask) | 0xf801000; break; // 
  case SIMD_FMLS_VEC_VEC_ELEM: group = "Advanced SIMD vector x indexed element/FMLS (by element) Vector"; mask = 0xbf80f400; encoding = (set_mask & ~mask) | 0xf805000; break; // 
  case SIMD_FMUL_VEC_VEC_ELEM: group = "Advanced SIMD vector x indexed element/FMUL (by element) Vector"; mask = 0xbf80f400; encoding = (set_mask & ~mask) | 0xf809000; break; // 
  case SIMD_FMULX_VEC_VEC_ELEM: group = "Advanced SIMD vector x indexed element/FMULX (by element) Vector"; mask = 0xbf80f400; encoding = (set_mask & ~mask) | 0x2f809000; break; // 
  case CSEL_32: group = "Conditional select/CSEL 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x1a800000; break; // 
  case CSEL_64: group = "Conditional select/CSEL 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x9a800000; break; // 
  case CSINC_32: group = "Conditional select/CSINC 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x1a800400; break; // 
  case CSINC_64: group = "Conditional select/CSINC 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x9a800400; break; // 
  case CSINV_32: group = "Conditional select/CSINV 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x5a800000; break; // 
  case CSINV_64: group = "Conditional select/CSINV 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xda800000; break; // 
  case CSNEG_32: group = "Conditional select/CSNEG 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x5a800400; break; // 
  case CSNEG_64: group = "Conditional select/CSNEG 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xda800400; break; // 
  case FCSEL_FROM_DP: group = "Floating-point conditional select/FCSEL Double-precision"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x1e600c00; break; // 
  case FCSEL_SINGLE_FROM_SP: group = "Floating-point conditional select/FCSEL Single-precision"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x1e200c00; break; // 
  case LDR_IMM_REG_POST_32: group = "Load/store register (immediate post-indexed)/LDR (immediate) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xb8400400; break; // 
  case LDR_IMM_REG_POST_64: group = "Load/store register (immediate post-indexed)/LDR (immediate) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xf8400400; break; // 
  case SIMD_LDR_IMM_REG_POST_8_128: group = "Load/store register (immediate post-indexed)/LDR (immediate, SIMD&FP) 128-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x3cc00400; break; // 
  case SIMD_LDR_IMM_REG_POST_16: group = "Load/store register (immediate post-indexed)/LDR (immediate, SIMD&FP) 16-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x7c400400; break; // 
  case SIMD_LDR_IMM_REG_POST_32: group = "Load/store register (immediate post-indexed)/LDR (immediate, SIMD&FP) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xbc400400; break; // 
  case SIMD_LDR_IMM_REG_POST_64: group = "Load/store register (immediate post-indexed)/LDR (immediate, SIMD&FP) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xfc400400; break; // 
  case SIMD_LDR_IMM_REG_POST_8: group = "Load/store register (immediate post-indexed)/LDR (immediate, SIMD&FP) 8-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x3c400400; break; // 
  case LDRB_IMM_REG_POST: group = "Load/store register (immediate post-indexed)/LDRB (immediate) Post-index"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38400400; break; // 
  case LDRH_IMM_REG_POST: group = "Load/store register (immediate post-indexed)/LDRH (immediate) Post-index"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78400400; break; // 
  case LDRSB_IMM_REG_POST_32: group = "Load/store register (immediate post-indexed)/LDRSB (immediate) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38c00400; break; // 
  case LDRSB_IMM_REG_POST_64: group = "Load/store register (immediate post-indexed)/LDRSB (immediate) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38800400; break; // 
  case LDRSH_IMM_REG_POST_32: group = "Load/store register (immediate post-indexed)/LDRSH (immediate) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78c00400; break; // 
  case LDRSH_IMM_REG_POST_64: group = "Load/store register (immediate post-indexed)/LDRSH (immediate) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78800400; break; // 
  case LDRSW_IMM_REG_POST: group = "Load/store register (immediate post-indexed)/LDRSW (immediate) Post-index"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xb8800400; break; // 
  case STR_IMM_REG_POST_32: group = "Load/store register (immediate post-indexed)/STR (immediate) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xb8000400; break; // 
  case STR_IMM_REG_POST_64: group = "Load/store register (immediate post-indexed)/STR (immediate) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xf8000400; break; // 
  case SIMD_STR_IMM_REG_POST_8_128: group = "Load/store register (immediate post-indexed)/STR (immediate, SIMD&FP) 128-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x3c800400; break; // 
  case SIMD_STR_IMM_REG_POST_16: group = "Load/store register (immediate post-indexed)/STR (immediate, SIMD&FP) 16-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x7c000400; break; // 
  case SIMD_STR_IMM_REG_POST_32: group = "Load/store register (immediate post-indexed)/STR (immediate, SIMD&FP) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xbc000400; break; // 
  case SIMD_STR_IMM_REG_POST_64: group = "Load/store register (immediate post-indexed)/STR (immediate, SIMD&FP) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xfc000400; break; // 
  case SIMD_STR_IMM_REG_POST_8: group = "Load/store register (immediate post-indexed)/STR (immediate, SIMD&FP) 8-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x3c000400; break; // 
  case STRB_IMM_REG_POST: group = "Load/store register (immediate post-indexed)/STRB (immediate) Post-index"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38000400; break; // 
  case STRH_IMM_REG_POST: group = "Load/store register (immediate post-indexed)/STRH (immediate) Post-index"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78000400; break; // 
  case LDR_IMM_REG_PRE_32: group = "Load/store register (immediate pre-indexed)/LDR (immediate) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xb8400c00; break; // 
  case LDR_IMM_REG_PRE_64: group = "Load/store register (immediate pre-indexed)/LDR (immediate) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xf8400c00; break; // 
  case SIMD_LDR_IMM_REG_PRE_8_128: group = "Load/store register (immediate pre-indexed)/LDR (immediate, SIMD&FP) 128-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x3cc00c00; break; // 
  case SIMD_LDR_IMM_REG_PRE_16: group = "Load/store register (immediate pre-indexed)/LDR (immediate, SIMD&FP) 16-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x7c400c00; break; // 
  case SIMD_LDR_IMM_REG_PRE_32: group = "Load/store register (immediate pre-indexed)/LDR (immediate, SIMD&FP) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xbc400c00; break; // 
  case SIMD_LDR_IMM_REG_PRE_64: group = "Load/store register (immediate pre-indexed)/LDR (immediate, SIMD&FP) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xfc400c00; break; // 
  case SIMD_LDR_IMM_REG_PRE_8: group = "Load/store register (immediate pre-indexed)/LDR (immediate, SIMD&FP) 8-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x3c400c00; break; // 
  case LDRB_IMM_REG_PRE: group = "Load/store register (immediate pre-indexed)/LDRB (immediate) Pre-index"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38400c00; break; // 
  case LDRH_IMM_REG_PRE: group = "Load/store register (immediate pre-indexed)/LDRH (immediate) Pre-index"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78400c00; break; // 
  case LDRSB_IMM_REG_PRE_32: group = "Load/store register (immediate pre-indexed)/LDRSB (immediate) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38c00c00; break; // 
  case LDRSB_IMM_REG_PRE_64: group = "Load/store register (immediate pre-indexed)/LDRSB (immediate) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38800c00; break; // 
  case LDRSH_IMM_REG_PRE_32: group = "Load/store register (immediate pre-indexed)/LDRSH (immediate) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78c00c00; break; // 
  case LDRSH_IMM_REG_PRE_64: group = "Load/store register (immediate pre-indexed)/LDRSH (immediate) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78800c00; break; // 
  case LDRSW_IMM_REG_PRE: group = "Load/store register (immediate pre-indexed)/LDRSW (immediate) Pre-index"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xb8800c00; break; // 
  case STR_IMM_REG_PRE_32: group = "Load/store register (immediate pre-indexed)/STR (immediate) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xb8000c00; break; // 
  case STR_IMM_REG_PRE_64: group = "Load/store register (immediate pre-indexed)/STR (immediate) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xf8000c00; break; // 
  case SIMD_STR_IMM_REG_PRE_8_128: group = "Load/store register (immediate pre-indexed)/STR (immediate, SIMD&FP) 128-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x3c800c00; break; // 
  case SIMD_STR_IMM_REG_PRE_16: group = "Load/store register (immediate pre-indexed)/STR (immediate, SIMD&FP) 16-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x7c000c00; break; // 
  case SIMD_STR_IMM_REG_PRE_32: group = "Load/store register (immediate pre-indexed)/STR (immediate, SIMD&FP) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xbc000c00; break; // 
  case SIMD_STR_IMM_REG_PRE_64: group = "Load/store register (immediate pre-indexed)/STR (immediate, SIMD&FP) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xfc000c00; break; // 
  case SIMD_STR_IMM_REG_PRE_8: group = "Load/store register (immediate pre-indexed)/STR (immediate, SIMD&FP) 8-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x3c000c00; break; // 
  case STRB_IMM_REG_PRE: group = "Load/store register (immediate pre-indexed)/STRB (immediate) Pre-index"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38000c00; break; // 
  case STRH_IMM_REG_PRE: group = "Load/store register (immediate pre-indexed)/STRH (immediate) Pre-index"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78000c00; break; // 
  case LDR_REG_OFF_32: group = "Load/store register (register offset)/LDR (register) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xb8600800; break; // 
  case LDR_REG_OFF_64: group = "Load/store register (register offset)/LDR (register) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xf8600800; break; // 
  case SIMD_LDR_REG_OFF_8_128: group = "Load/store register (register offset)/LDR (register, SIMD&FP) 128-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x3ce00800; break; // 
  case SIMD_LDR_REG_OFF_16: group = "Load/store register (register offset)/LDR (register, SIMD&FP) 16-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x7c600800; break; // 
  case SIMD_LDR_REG_OFF_32: group = "Load/store register (register offset)/LDR (register, SIMD&FP) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xbc600800; break; // 
  case SIMD_LDR_REG_OFF_64: group = "Load/store register (register offset)/LDR (register, SIMD&FP) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xfc600800; break; // 
  case SIMD_LDR_REG_OFF_8: group = "Load/store register (register offset)/LDR (register, SIMD&FP) 8-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x3c600800; break; // 
  case LDRB_REG_OFF: group = "Load/store register (register offset)/LDRB (register) -"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38600800; break; // 
  case LDRH_REG_OFF: group = "Load/store register (register offset)/LDRH (register) -"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78600800; break; // 
  case LDRSB_REG_OFF_32: group = "Load/store register (register offset)/LDRSB (register) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38e00800; break; // 
  case LDRSB_REG_OFF_64: group = "Load/store register (register offset)/LDRSB (register) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38a00800; break; // 
  case LDRSH_REG_OFF_32: group = "Load/store register (register offset)/LDRSH (register) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78e00800; break; // 
  case LDRSH_REG_OFF_64: group = "Load/store register (register offset)/LDRSH (register) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78a00800; break; // 
  case LDRSW_REG_OFF: group = "Load/store register (register offset)/LDRSW (register) -"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xb8a00800; break; // 
  case PRFM_REG_OFF: group = "Load/store register (register offset)/PRFM (register) -"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xf8a00800; break; // 
  case STR_REG_OFF_32: group = "Load/store register (register offset)/STR (register) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xb8200800; break; // 
  case STR_REG_OFF_64: group = "Load/store register (register offset)/STR (register) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xf8200800; break; // 
  case SIMD_STR_REG_OFF_8_128: group = "Load/store register (register offset)/STR (register, SIMD&FP) 128-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x3ca00800; break; // 
  case SIMD_STR_REG_OFF_16: group = "Load/store register (register offset)/STR (register, SIMD&FP) 16-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x7c200800; break; // 
  case SIMD_STR_REG_OFF_32: group = "Load/store register (register offset)/STR (register, SIMD&FP) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xbc200800; break; // 
  case SIMD_STR_REG_OFF_64: group = "Load/store register (register offset)/STR (register, SIMD&FP) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xfc200800; break; // 
  case SIMD_STR_REG_OFF_8: group = "Load/store register (register offset)/STR (register, SIMD&FP) 8-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x3c200800; break; // 
  case STRB_REG_OFF: group = "Load/store register (register offset)/STRB (register) -"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38200800; break; // 
  case STRH_REG_OFF: group = "Load/store register (register offset)/STRH (register) -"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78200800; break; // 
  case LDTR_REG_32: group = "Load/store register (unprivileged)/LDTR 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xb8400800; break; // 
  case LDTR_REG_64: group = "Load/store register (unprivileged)/LDTR 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xf8400800; break; // 
  case LDTRB_REG: group = "Load/store register (unprivileged)/LDTRB -"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38400800; break; // 
  case LDTRH_REG: group = "Load/store register (unprivileged)/LDTRH -"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78400800; break; // 
  case LDTRSB_REG_32: group = "Load/store register (unprivileged)/LDTRSB 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38c00800; break; // 
  case LDTRSB_REG_64: group = "Load/store register (unprivileged)/LDTRSB 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38800800; break; // 
  case LDTRSH_REG_32: group = "Load/store register (unprivileged)/LDTRSH 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78c00800; break; // 
  case LDTRSH_REG_64: group = "Load/store register (unprivileged)/LDTRSH 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78800800; break; // 
  case LDTRSW_REG: group = "Load/store register (unprivileged)/LDTRSW -"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xb8800800; break; // 
  case STTR_REG_32: group = "Load/store register (unprivileged)/STTR 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xb8000800; break; // 
  case STTR_REG_64: group = "Load/store register (unprivileged)/STTR 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xf8000800; break; // 
  case STTRB_REG: group = "Load/store register (unprivileged)/STTRB -"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38000800; break; // 
  case STTRH_REG: group = "Load/store register (unprivileged)/STTRH -"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78000800; break; // 
  case SIMD_LDUR_IMM_REG_8_128: group = "Load/store register (unscaled immediate)/LDUR (SIMD&FP) 128-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x3cc00000; break; // 
  case SIMD_LDUR_IMM_REG_16: group = "Load/store register (unscaled immediate)/LDUR (SIMD&FP) 16-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x7c400000; break; // 
  case SIMD_LDUR_IMM_REG_32: group = "Load/store register (unscaled immediate)/LDUR (SIMD&FP) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xbc400000; break; // 
  case SIMD_LDUR_IMM_REG_64: group = "Load/store register (unscaled immediate)/LDUR (SIMD&FP) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xfc400000; break; // 
  case SIMD_LDUR_IMM_REG_8: group = "Load/store register (unscaled immediate)/LDUR (SIMD&FP) 8-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x3c400000; break; // 
  case LDUR_IMM_REG_32: group = "Load/store register (unscaled immediate)/LDUR 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xb8400000; break; // 
  case LDUR_IMM_REG_64: group = "Load/store register (unscaled immediate)/LDUR 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xf8400000; break; // 
  case LDURB_IMM_REG: group = "Load/store register (unscaled immediate)/LDURB -"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38400000; break; // 
  case LDURH_IMM_REG: group = "Load/store register (unscaled immediate)/LDURH -"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78400000; break; // 
  case LDURSB_IMM_REG_32: group = "Load/store register (unscaled immediate)/LDURSB 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38c00000; break; // 
  case LDURSB_IMM_REG_64: group = "Load/store register (unscaled immediate)/LDURSB 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38800000; break; // 
  case LDURSH_IMM_REG_32: group = "Load/store register (unscaled immediate)/LDURSH 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78c00000; break; // 
  case LDURSH_IMM_REG_64: group = "Load/store register (unscaled immediate)/LDURSH 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78800000; break; // 
  case LDURSW_IMM_REG: group = "Load/store register (unscaled immediate)/LDURSW -"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xb8800000; break; // 
  case PRFUM_IMM_REG: group = "Load/store register (unscaled immediate)/PRFUM -"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xf8800000; break; // 
  case SIMD_STUR_IMM_REG_8_128: group = "Load/store register (unscaled immediate)/STUR (SIMD&FP) 128-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x3c800000; break; // 
  case SIMD_STUR_IMM_REG_16: group = "Load/store register (unscaled immediate)/STUR (SIMD&FP) 16-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x7c000000; break; // 
  case SIMD_STUR_IMM_REG_32: group = "Load/store register (unscaled immediate)/STUR (SIMD&FP) 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xbc000000; break; // 
  case SIMD_STUR_IMM_REG_64: group = "Load/store register (unscaled immediate)/STUR (SIMD&FP) 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xfc000000; break; // 
  case SIMD_STUR_IMM_REG_8: group = "Load/store register (unscaled immediate)/STUR (SIMD&FP) 8-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x3c000000; break; // 
  case STUR_IMM_REG_32: group = "Load/store register (unscaled immediate)/STUR 32-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xb8000000; break; // 
  case STUR_IMM_REG_64: group = "Load/store register (unscaled immediate)/STUR 64-bit"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0xf8000000; break; // 
  case STURB_IMM_REG: group = "Load/store register (unscaled immediate)/STURB -"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x38000000; break; // 
  case STURH_IMM_REG: group = "Load/store register (unscaled immediate)/STURH -"; mask = 0xffe00c00; encoding = (set_mask & ~mask) | 0x78000000; break; // 
  case SIMD_INS_ELEM: group = "Advanced SIMD copy/INS (element) -"; mask = 0xffe08400; encoding = (set_mask & ~mask) | 0x6e000400; break; // 
  case MRS: group = "System/MRS -"; mask = 0xfff00000; encoding = (set_mask & ~mask) | 0xd5300000; break; // 
  case MSR_REG: group = "System/MSR (register) -"; mask = 0xfff00000; encoding = (set_mask & ~mask) | 0xd5100000; break; // 
  case SIMD_MLA_VEC_ELEM: group = "Advanced SIMD vector x indexed element/MLA (by element) -"; mask = 0xbf00f400; encoding = (set_mask & ~mask) | 0x2f000000; break; // 
  case SIMD_MLS_VEC_ELEM: group = "Advanced SIMD vector x indexed element/MLS (by element) -"; mask = 0xbf00f400; encoding = (set_mask & ~mask) | 0x2f004000; break; // 
  case SIMD_MUL_VEC_ELEM: group = "Advanced SIMD vector x indexed element/MUL (by element) -"; mask = 0xbf00f400; encoding = (set_mask & ~mask) | 0xf008000; break; // 
  case SIMD_SMLAL_VEC_ELEM: group = "Advanced SIMD vector x indexed element/SMLAL, SMLAL2 (by element) -"; mask = 0xbf00f400; encoding = (set_mask & ~mask) | 0xf002000; break; // 
  case SIMD_SMLSL_VEC_ELEM: group = "Advanced SIMD vector x indexed element/SMLSL, SMLSL2 (by element) -"; mask = 0xbf00f400; encoding = (set_mask & ~mask) | 0xf006000; break; // 
  case SIMD_SMULL_VEC_ELEM: group = "Advanced SIMD vector x indexed element/SMULL, SMULL2 (by element) -"; mask = 0xbf00f400; encoding = (set_mask & ~mask) | 0xf00a000; break; // 
  case SIMD_SQDMLAL_VEC_VEC_ELEM: group = "Advanced SIMD vector x indexed element/SQDMLAL, SQDMLAL2 (by element) Vector"; mask = 0xbf00f400; encoding = (set_mask & ~mask) | 0xf003000; break; // 
  case SIMD_SQDMLSL_VEC_VEC_ELEM: group = "Advanced SIMD vector x indexed element/SQDMLSL, SQDMLSL2 (by element) Vector"; mask = 0xbf00f400; encoding = (set_mask & ~mask) | 0xf007000; break; // 
  case SIMD_SQDMULH_VEC_VEC_ELEM: group = "Advanced SIMD vector x indexed element/SQDMULH (by element) Vector"; mask = 0xbf00f400; encoding = (set_mask & ~mask) | 0xf00c000; break; // 
  case SIMD_SQDMULL_VEC_VEC_ELEM: group = "Advanced SIMD vector x indexed element/SQDMULL, SQDMULL2 (by element) Vector"; mask = 0xbf00f400; encoding = (set_mask & ~mask) | 0xf00b000; break; // 
  case SIMD_SQRDMULH_VEC_VEC_ELEM: group = "Advanced SIMD vector x indexed element/SQRDMULH (by element) Vector"; mask = 0xbf00f400; encoding = (set_mask & ~mask) | 0xf00d000; break; // 
  case SIMD_UMLAL_VEC_ELEM: group = "Advanced SIMD vector x indexed element/UMLAL, UMLAL2 (by element) -"; mask = 0xbf00f400; encoding = (set_mask & ~mask) | 0x2f002000; break; // 
  case SIMD_UMLSL_VEC_ELEM: group = "Advanced SIMD vector x indexed element/UMLSL, UMLSL2 (by element) -"; mask = 0xbf00f400; encoding = (set_mask & ~mask) | 0x2f006000; break; // 
  case SIMD_UMULL_VEC_ELEM: group = "Advanced SIMD vector x indexed element/UMULL, UMULL2 (by element) -"; mask = 0xbf00f400; encoding = (set_mask & ~mask) | 0x2f00a000; break; // 
  case SIMD_EXT: group = "Advanced SIMD extract/EXT -"; mask = 0xbfe08400; encoding = (set_mask & ~mask) | 0x2e000000; break; // 
  case MADD_32: group = "Data-processing (3 source)/MADD 32-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x1b000000; break; // 
  case MADD_64: group = "Data-processing (3 source)/MADD 64-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x9b000000; break; // 
  case MSUB_32: group = "Data-processing (3 source)/MSUB 32-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x1b008000; break; // 
  case MSUB_64: group = "Data-processing (3 source)/MSUB 64-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x9b008000; break; // 
  case SMADDL: group = "Data-processing (3 source)/SMADDL -"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x9b200000; break; // 
  case SMSUBL: group = "Data-processing (3 source)/SMSUBL -"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x9b208000; break; // 
  case SMULH: group = "Data-processing (3 source)/SMULH -"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x9b400000; break; // 
  case UMADDL: group = "Data-processing (3 source)/UMADDL -"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x9ba00000; break; // 
  case UMSUBL: group = "Data-processing (3 source)/UMSUBL -"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x9ba08000; break; // 
  case UMULH: group = "Data-processing (3 source)/UMULH -"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x9bc00000; break; // 
  case EXTR_32: group = "Extract/EXTR 32-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x13800000; break; // 
  case FMADD_FROM_DP: group = "Floating-point data-processing (3 source)/FMADD Double-precision"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x1f400000; break; // 
  case FMADD_SINGLE_FROM_SP: group = "Floating-point data-processing (3 source)/FMADD Single-precision"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x1f000000; break; // 
  case FMSUB_FROM_DP: group = "Floating-point data-processing (3 source)/FMSUB Double-precision"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x1f408000; break; // 
  case FMSUB_SINGLE_FROM_SP: group = "Floating-point data-processing (3 source)/FMSUB Single-precision"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x1f008000; break; // 
  case FNMADD_FROM_DP: group = "Floating-point data-processing (3 source)/FNMADD Double-precision"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x1f600000; break; // 
  case FNMADD_SINGLE_FROM_SP: group = "Floating-point data-processing (3 source)/FNMADD Single-precision"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x1f200000; break; // 
  case FNMSUB_FROM_DP: group = "Floating-point data-processing (3 source)/FNMSUB Double-precision"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x1f608000; break; // 
  case FNMSUB_SINGLE_FROM_SP: group = "Floating-point data-processing (3 source)/FNMSUB Single-precision"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x1f208000; break; // 
  case LDAR_32: group = "Load/store exclusive/LDAR 32-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x88c08000; break; // 
  case LDAR_64: group = "Load/store exclusive/LDAR 64-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0xc8c08000; break; // 
  case LDARB: group = "Load/store exclusive/LDARB -"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x8c08000; break; // 
  case LDARH: group = "Load/store exclusive/LDARH -"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x48c08000; break; // 
  case LDAXP_32: group = "Load/store exclusive/LDAXP 32-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x88608000; break; // 
  case LDAXP_64: group = "Load/store exclusive/LDAXP 64-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0xc8608000; break; // 
  case LDAXR_32: group = "Load/store exclusive/LDAXR 32-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x88408000; break; // 
  case LDAXR_64: group = "Load/store exclusive/LDAXR 64-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0xc8408000; break; // 
  case LDAXRB: group = "Load/store exclusive/LDAXRB -"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x8408000; break; // 
  case LDAXRH: group = "Load/store exclusive/LDAXRH -"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x48408000; break; // 
  case LDXP_32: group = "Load/store exclusive/LDXP 32-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x88600000; break; // 
  case LDXP_64: group = "Load/store exclusive/LDXP 64-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0xc8600000; break; // 
  case LDXR_32: group = "Load/store exclusive/LDXR 32-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x88400000; break; // 
  case LDXR_64: group = "Load/store exclusive/LDXR 64-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0xc8400000; break; // 
  case LDXRB: group = "Load/store exclusive/LDXRB -"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x8400000; break; // 
  case LDXRH: group = "Load/store exclusive/LDXRH -"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x48400000; break; // 
  case STLR_32: group = "Load/store exclusive/STLR 32-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x88808000; break; // 
  case STLR_64: group = "Load/store exclusive/STLR 64-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0xc8808000; break; // 
  case STLRB: group = "Load/store exclusive/STLRB -"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x8808000; break; // 
  case STLRH: group = "Load/store exclusive/STLRH -"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x48808000; break; // 
  case STLXP_32: group = "Load/store exclusive/STLXP 32-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x88208000; break; // 
  case STLXP_64: group = "Load/store exclusive/STLXP 64-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0xc8208000; break; // 
  case STLXR_32: group = "Load/store exclusive/STLXR 32-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x88008000; break; // 
  case STLXR_64: group = "Load/store exclusive/STLXR 64-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0xc8008000; break; // 
  case STLXRB: group = "Load/store exclusive/STLXRB -"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x8008000; break; // 
  case STLXRH: group = "Load/store exclusive/STLXRH -"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x48008000; break; // 
  case STXP_32: group = "Load/store exclusive/STXP 32-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x88200000; break; // 
  case STXP_64: group = "Load/store exclusive/STXP 64-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0xc8200000; break; // 
  case STXR_32: group = "Load/store exclusive/STXR 32-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x88000000; break; // 
  case STXR_64: group = "Load/store exclusive/STXR 64-bit"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0xc8000000; break; // 
  case STXRB: group = "Load/store exclusive/STXRB -"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x8000000; break; // 
  case STXRH: group = "Load/store exclusive/STXRH -"; mask = 0xffe08000; encoding = (set_mask & ~mask) | 0x48000000; break; // 
  case ADD_REG_32: group = "Add/subtract (extended register)/ADD (extended register) 32-bit"; mask = 0xffe00000; encoding = (set_mask & ~mask) | 0xb200000; break; // 
  case ADD_REG_64: group = "Add/subtract (extended register)/ADD (extended register) 64-bit"; mask = 0xffe00000; encoding = (set_mask & ~mask) | 0x8b200000; break; // 
  case ADDS_REG_32: group = "Add/subtract (extended register)/ADDS (extended register) 32-bit"; mask = 0xffe00000; encoding = (set_mask & ~mask) | 0x2b200000; break; // 
  case ADDS_REG_64: group = "Add/subtract (extended register)/ADDS (extended register) 64-bit"; mask = 0xffe00000; encoding = (set_mask & ~mask) | 0xab200000; break; // 
  case SUB_REG_32: group = "Add/subtract (extended register)/SUB (extended register) 32-bit"; mask = 0xffe00000; encoding = (set_mask & ~mask) | 0x4b200000; break; // 
  case SUB_REG_64: group = "Add/subtract (extended register)/SUB (extended register) 64-bit"; mask = 0xffe00000; encoding = (set_mask & ~mask) | 0xcb200000; break; // 
  case SUBS_REG_32: group = "Add/subtract (extended register)/SUBS (extended register) 32-bit"; mask = 0xffe00000; encoding = (set_mask & ~mask) | 0x6b200000; break; // 
  case SUBS_REG_64: group = "Add/subtract (extended register)/SUBS (extended register) 64-bit"; mask = 0xffe00000; encoding = (set_mask & ~mask) | 0xeb200000; break; // 
  case EXTR_64: group = "Extract/EXTR 64-bit"; mask = 0xffe00000; encoding = (set_mask & ~mask) | 0x93c00000; break; // 
  case BFM_32: group = "Bitfield/BFM 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x33000000; break; // 
  case BFM_64: group = "Bitfield/BFM 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xb3400000; break; // 
  case SBFM_32: group = "Bitfield/SBFM 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x13000000; break; // 
  case SBFM_64: group = "Bitfield/SBFM 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x93400000; break; // 
  case UBFM_32: group = "Bitfield/UBFM 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x53000000; break; // 
  case UBFM_64: group = "Bitfield/UBFM 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xd3400000; break; // 
  case SIMD_LDNP_OFF_8_128: group = "Load/store no-allocate pair (offset)/LDNP (SIMD&FP) 128-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xac400000; break; // 
  case SIMD_LDNP_OFF_32: group = "Load/store no-allocate pair (offset)/LDNP (SIMD&FP) 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x2c400000; break; // 
  case SIMD_LDNP_OFF_64: group = "Load/store no-allocate pair (offset)/LDNP (SIMD&FP) 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x6c400000; break; // 
  case LDNP_OFF_32: group = "Load/store no-allocate pair (offset)/LDNP 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x28400000; break; // 
  case LDNP_OFF_64: group = "Load/store no-allocate pair (offset)/LDNP 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xa8400000; break; // 
  case SIMD_STNP_OFF_8_128: group = "Load/store no-allocate pair (offset)/STNP (SIMD&FP) 128-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xac000000; break; // 
  case SIMD_STNP_OFF_32: group = "Load/store no-allocate pair (offset)/STNP (SIMD&FP) 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x2c000000; break; // 
  case SIMD_STNP_OFF_64: group = "Load/store no-allocate pair (offset)/STNP (SIMD&FP) 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x6c000000; break; // 
  case STNP_OFF_32: group = "Load/store no-allocate pair (offset)/STNP 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x28000000; break; // 
  case STNP_OFF_64: group = "Load/store no-allocate pair (offset)/STNP 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xa8000000; break; // 
  case LDR_IMM_REG_32: group = "Load/store register (unsigned immediate)/LDR (immediate) 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xb9400000; break; // 
  case LDR_IMM_REG_64: group = "Load/store register (unsigned immediate)/LDR (immediate) 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xf9400000; break; // 
  case SIMD_LDR_IMM_REG_8_128: group = "Load/store register (unsigned immediate)/LDR (immediate, SIMD&FP) 128-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x3dc00000; break; // 
  case SIMD_LDR_IMM_REG_16: group = "Load/store register (unsigned immediate)/LDR (immediate, SIMD&FP) 16-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x7d400000; break; // 
  case SIMD_LDR_IMM_REG_32: group = "Load/store register (unsigned immediate)/LDR (immediate, SIMD&FP) 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xbd400000; break; // 
  case SIMD_LDR_IMM_REG_64: group = "Load/store register (unsigned immediate)/LDR (immediate, SIMD&FP) 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xfd400000; break; // 
  case SIMD_LDR_IMM_REG_8: group = "Load/store register (unsigned immediate)/LDR (immediate, SIMD&FP) 8-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x3d400000; break; // 
  case LDRB_IMM_REG_OFF: group = "Load/store register (unsigned immediate)/LDRB (immediate) Unsigned offset"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x39400000; break; // 
  case LDRH_IMM_REG_OFF: group = "Load/store register (unsigned immediate)/LDRH (immediate) Unsigned offset"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x79400000; break; // 
  case LDRSB_IMM_REG_32: group = "Load/store register (unsigned immediate)/LDRSB (immediate) 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x39c00000; break; // 
  case LDRSB_IMM_REG_64: group = "Load/store register (unsigned immediate)/LDRSB (immediate) 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x39800000; break; // 
  case LDRSH_IMM_REG_32: group = "Load/store register (unsigned immediate)/LDRSH (immediate) 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x79c00000; break; // 
  case LDRSH_IMM_REG_64: group = "Load/store register (unsigned immediate)/LDRSH (immediate) 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x79800000; break; // 
  case LDRSW_IMM_REG_OFF: group = "Load/store register (unsigned immediate)/LDRSW (immediate) Unsigned offset"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xb9800000; break; // 
  case PRFM_IMM_REG: group = "Load/store register (unsigned immediate)/PRFM (immediate) -"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xf9800000; break; // 
  case STR_IMM_REG_32: group = "Load/store register (unsigned immediate)/STR (immediate) 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xb9000000; break; // 
  case STR_IMM_REG_64: group = "Load/store register (unsigned immediate)/STR (immediate) 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xf9000000; break; // 
  case SIMD_STR_IMM_REG_8_128: group = "Load/store register (unsigned immediate)/STR (immediate, SIMD&FP) 128-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x3d800000; break; // 
  case SIMD_STR_IMM_REG_16: group = "Load/store register (unsigned immediate)/STR (immediate, SIMD&FP) 16-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x7d000000; break; // 
  case SIMD_STR_IMM_REG_32: group = "Load/store register (unsigned immediate)/STR (immediate, SIMD&FP) 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xbd000000; break; // 
  case SIMD_STR_IMM_REG_64: group = "Load/store register (unsigned immediate)/STR (immediate, SIMD&FP) 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xfd000000; break; // 
  case SIMD_STR_IMM_REG_8: group = "Load/store register (unsigned immediate)/STR (immediate, SIMD&FP) 8-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x3d000000; break; // 
  case STRB_IMM_REG_OFF: group = "Load/store register (unsigned immediate)/STRB (immediate) Unsigned offset"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x39000000; break; // 
  case STRH_IMM_REG_OFF: group = "Load/store register (unsigned immediate)/STRH (immediate) Unsigned offset"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x79000000; break; // 
  case SIMD_LDP_REG_OFF_8_128: group = "Load/store register pair (offset)/LDP (SIMD&FP) 128-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xad400000; break; // 
  case SIMD_LDP_REG_OFF_32: group = "Load/store register pair (offset)/LDP (SIMD&FP) 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x2d400000; break; // 
  case SIMD_LDP_REG_OFF_64: group = "Load/store register pair (offset)/LDP (SIMD&FP) 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x6d400000; break; // 
  case LDP_REG_OFF_32: group = "Load/store register pair (offset)/LDP 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x29400000; break; // 
  case LDP_REG_OFF_64: group = "Load/store register pair (offset)/LDP 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xa9400000; break; // 
  case LDPSW_REG_OFF: group = "Load/store register pair (offset)/LDPSW Signed offset"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x69400000; break; // 
  case SIMD_STP_REG_OFF_8_128: group = "Load/store register pair (offset)/STP (SIMD&FP) 128-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xad000000; break; // 
  case SIMD_STP_REG_OFF_32: group = "Load/store register pair (offset)/STP (SIMD&FP) 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x2d000000; break; // 
  case SIMD_STP_REG_OFF_64: group = "Load/store register pair (offset)/STP (SIMD&FP) 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x6d000000; break; // 
  case STP_REG_OFF_32: group = "Load/store register pair (offset)/STP 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x29000000; break; // 
  case STP_REG_OFF_64: group = "Load/store register pair (offset)/STP 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xa9000000; break; // 
  case SIMD_LDP_REG_POST_8_128: group = "Load/store register pair (post-indexed)/LDP (SIMD&FP) 128-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xacc00000; break; // 
  case SIMD_LDP_REG_POST_32: group = "Load/store register pair (post-indexed)/LDP (SIMD&FP) 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x2cc00000; break; // 
  case SIMD_LDP_REG_POST_64: group = "Load/store register pair (post-indexed)/LDP (SIMD&FP) 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x6cc00000; break; // 
  case LDP_REG_POST_32: group = "Load/store register pair (post-indexed)/LDP 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x28c00000; break; // 
  case LDP_REG_POST_64: group = "Load/store register pair (post-indexed)/LDP 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xa8c00000; break; // 
  case LDPSW_REG_POST: group = "Load/store register pair (post-indexed)/LDPSW Post-index"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x68c00000; break; // 
  case SIMD_STP_REG_POST_8_128: group = "Load/store register pair (post-indexed)/STP (SIMD&FP) 128-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xac800000; break; // 
  case SIMD_STP_REG_POST_32: group = "Load/store register pair (post-indexed)/STP (SIMD&FP) 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x2c800000; break; // 
  case SIMD_STP_REG_POST_64: group = "Load/store register pair (post-indexed)/STP (SIMD&FP) 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x6c800000; break; // 
  case STP_REG_POST_32: group = "Load/store register pair (post-indexed)/STP 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x28800000; break; // 
  case STP_REG_POST_64: group = "Load/store register pair (post-indexed)/STP 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xa8800000; break; // 
  case SIMD_LDP_REG_PRE_8_128: group = "Load/store register pair (pre-indexed)/LDP (SIMD&FP) 128-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xadc00000; break; // 
  case SIMD_LDP_REG_PRE_32: group = "Load/store register pair (pre-indexed)/LDP (SIMD&FP) 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x2dc00000; break; // 
  case SIMD_LDP_REG_PRE_64: group = "Load/store register pair (pre-indexed)/LDP (SIMD&FP) 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x6dc00000; break; // 
  case LDP_REG_PRE_32: group = "Load/store register pair (pre-indexed)/LDP 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x29c00000; break; // 
  case LDP_REG_PRE_64: group = "Load/store register pair (pre-indexed)/LDP 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xa9c00000; break; // 
  case LDPSW_REG_PRE: group = "Load/store register pair (pre-indexed)/LDPSW Pre-index"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x69c00000; break; // 
  case SIMD_STP_REG_PRE_8_128: group = "Load/store register pair (pre-indexed)/STP (SIMD&FP) 128-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xad800000; break; // 
  case SIMD_STP_REG_PRE_32: group = "Load/store register pair (pre-indexed)/STP (SIMD&FP) 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x2d800000; break; // 
  case SIMD_STP_REG_PRE_64: group = "Load/store register pair (pre-indexed)/STP (SIMD&FP) 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x6d800000; break; // 
  case STP_REG_PRE_32: group = "Load/store register pair (pre-indexed)/STP 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x29800000; break; // 
  case STP_REG_PRE_64: group = "Load/store register pair (pre-indexed)/STP 64-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0xa9800000; break; // 
  case AND_IMM_32: group = "Logical (immediate)/AND (immediate) 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x12000000; break; // 
  case ANDS_IMM_32: group = "Logical (immediate)/ANDS (immediate) 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x72000000; break; // 
  case EOR_IMM_32: group = "Logical (immediate)/EOR (immediate) 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x52000000; break; // 
  case ORR_IMM_32: group = "Logical (immediate)/ORR (immediate) 32-bit"; mask = 0xffc00000; encoding = (set_mask & ~mask) | 0x32000000; break; // 
  case B_COND_IMM: group = "Conditional branch (immediate)/B.cond -"; mask = 0xff000010; encoding = (set_mask & ~mask) | 0x54000000; break; // 
  case ADD_SHIFT_REG_32: group = "Add/subtract (shifted register)/ADD (shifted register) 32-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0xb000000; break; // 
  case ADD_SHIFT_REG_64: group = "Add/subtract (shifted register)/ADD (shifted register) 64-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0x8b000000; break; // 
  case ADDS_SHIFT_REG_32: group = "Add/subtract (shifted register)/ADDS (shifted register) 32-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0x2b000000; break; // 
  case ADDS_SHIFT_REG_64: group = "Add/subtract (shifted register)/ADDS (shifted register) 64-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0xab000000; break; // 
  case SUB_SHIFT_REG_32: group = "Add/subtract (shifted register)/SUB (shifted register) 32-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0x4b000000; break; // 
  case SUB_SHIFT_REG_64: group = "Add/subtract (shifted register)/SUB (shifted register) 64-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0xcb000000; break; // 
  case SUBS_SHIFT_REG_32: group = "Add/subtract (shifted register)/SUBS (shifted register) 32-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0x6b000000; break; // 
  case SUBS_SHIFT_REG_64: group = "Add/subtract (shifted register)/SUBS (shifted register) 64-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0xeb000000; break; // 
  case AND_SHIFT_REG_32: group = "Logical (shifted register)/AND (shifted register) 32-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0xa000000; break; // 
  case AND_SHIFT_REG_64: group = "Logical (shifted register)/AND (shifted register) 64-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0x8a000000; break; // 
  case ANDS_SHIFT_REG_32: group = "Logical (shifted register)/ANDS (shifted register) 32-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0x6a000000; break; // 
  case ANDS_SHIFT_REG_64: group = "Logical (shifted register)/ANDS (shifted register) 64-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0xea000000; break; // 
  case BIC_SHIFT_REG_32: group = "Logical (shifted register)/BIC (shifted register) 32-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0xa200000; break; // 
  case BIC_SHIFT_REG_64: group = "Logical (shifted register)/BIC (shifted register) 64-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0x8a200000; break; // 
  case BICS_SHIFT_REG_32: group = "Logical (shifted register)/BICS (shifted register) 32-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0x6a200000; break; // 
  case BICS_SHIFT_REG_64: group = "Logical (shifted register)/BICS (shifted register) 64-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0xea200000; break; // 
  case EON_SHIFT_REG_32: group = "Logical (shifted register)/EON (shifted register) 32-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0x4a200000; break; // 
  case EON_SHIFT_REG_64: group = "Logical (shifted register)/EON (shifted register) 64-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0xca200000; break; // 
  case EOR_SHIFT_REG_32: group = "Logical (shifted register)/EOR (shifted register) 32-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0x4a000000; break; // 
  case EOR_SHIFT_REG_64: group = "Logical (shifted register)/EOR (shifted register) 64-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0xca000000; break; // 
  case ORN_SHIFT_REG_32: group = "Logical (shifted register)/ORN (shifted register) 32-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0x2a200000; break; // 
  case ORN_SHIFT_REG_64: group = "Logical (shifted register)/ORN (shifted register) 64-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0xaa200000; break; // 
  case ORR_SHIFT_REG_32: group = "Logical (shifted register)/ORR (shifted register) 32-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0x2a000000; break; // 
  case ORR_SHIFT_REG_64: group = "Logical (shifted register)/ORR (shifted register) 64-bit"; mask = 0xff200000; encoding = (set_mask & ~mask) | 0xaa000000; break; // 
  case AND_IMM_64: group = "Logical (immediate)/AND (immediate) 64-bit"; mask = 0xff800000; encoding = (set_mask & ~mask) | 0x92000000; break; // 
  case ANDS_IMM_64: group = "Logical (immediate)/ANDS (immediate) 64-bit"; mask = 0xff800000; encoding = (set_mask & ~mask) | 0xf2000000; break; // 
  case EOR_IMM_64: group = "Logical (immediate)/EOR (immediate) 64-bit"; mask = 0xff800000; encoding = (set_mask & ~mask) | 0xd2000000; break; // 
  case ORR_IMM_64: group = "Logical (immediate)/ORR (immediate) 64-bit"; mask = 0xff800000; encoding = (set_mask & ~mask) | 0xb2000000; break; // 
  case MOVK_IMM_32: group = "Move wide (immediate)/MOVK 32-bit"; mask = 0xff800000; encoding = (set_mask & ~mask) | 0x72800000; break; // 
  case MOVK_IMM_64: group = "Move wide (immediate)/MOVK 64-bit"; mask = 0xff800000; encoding = (set_mask & ~mask) | 0xf2800000; break; // 
  case MOVN_IMM_32: group = "Move wide (immediate)/MOVN 32-bit"; mask = 0xff800000; encoding = (set_mask & ~mask) | 0x12800000; break; // 
  case MOVN_IMM_64: group = "Move wide (immediate)/MOVN 64-bit"; mask = 0xff800000; encoding = (set_mask & ~mask) | 0x92800000; break; // 
  case MOVZ_IMM_32: group = "Move wide (immediate)/MOVZ 32-bit"; mask = 0xff800000; encoding = (set_mask & ~mask) | 0x52800000; break; // 
  case MOVZ_IMM_64: group = "Move wide (immediate)/MOVZ 64-bit"; mask = 0xff800000; encoding = (set_mask & ~mask) | 0xd2800000; break; // 
  case ADD_IMM_32: group = "Add/subtract (immediate)/ADD (immediate) 32-bit"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0x11000000; break; // 
  case ADD_IMM_64: group = "Add/subtract (immediate)/ADD (immediate) 64-bit"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0x91000000; break; // 
  case ADDS_IMM_32: group = "Add/subtract (immediate)/ADDS (immediate) 32-bit"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0x31000000; break; // 
  case ADDS_IMM_64: group = "Add/subtract (immediate)/ADDS (immediate) 64-bit"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0xb1000000; break; // 
  case SUB_IMM_32: group = "Add/subtract (immediate)/SUB (immediate) 32-bit"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0x51000000; break; // 
  case SUB_IMM_64: group = "Add/subtract (immediate)/SUB (immediate) 64-bit"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0xd1000000; break; // 
  case SUBS_IMM_32: group = "Add/subtract (immediate)/SUBS (immediate) 32-bit"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0x71000000; break; // 
  case SUBS_IMM_64: group = "Add/subtract (immediate)/SUBS (immediate) 64-bit"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0xf1000000; break; // 
  case CBNZ_IMM_32: group = "Compare & branch (immediate)/CBNZ 32-bit"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0x35000000; break; // 
  case CBNZ_IMM_64: group = "Compare & branch (immediate)/CBNZ 64-bit"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0xb5000000; break; // 
  case CBZ_IMM_32: group = "Compare & branch (immediate)/CBZ 32-bit"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0x34000000; break; // 
  case CBZ_IMM_64: group = "Compare & branch (immediate)/CBZ 64-bit"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0xb4000000; break; // 
  case LDR_REG_32: group = "Load register (literal)/LDR (literal) 32-bit"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0x18000000; break; // 
  case LDR_REG_64: group = "Load register (literal)/LDR (literal) 64-bit"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0x58000000; break; // 
  case SIMD_LDR_REG_8_128: group = "Load register (literal)/LDR (literal, SIMD&FP) 128-bit"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0x9c000000; break; // 
  case SIMD_LDR_REG_32: group = "Load register (literal)/LDR (literal, SIMD&FP) 32-bit"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0x1c000000; break; // 
  case SIMD_LDR_REG_64: group = "Load register (literal)/LDR (literal, SIMD&FP) 64-bit"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0x5c000000; break; // 
  case LDRSW_REG: group = "Load register (literal)/LDRSW (literal) -"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0x98000000; break; // 
  case PRFM_REG: group = "Load register (literal)/PRFM (literal) -"; mask = 0xff000000; encoding = (set_mask & ~mask) | 0xd8000000; break; // 
  case TBNZ: group = "Test & branch (immediate)/TBNZ -"; mask = 0x7f000000; encoding = (set_mask & ~mask) | 0x37000000; break; // 
  case TBZ: group = "Test & branch (immediate)/TBZ -"; mask = 0x7f000000; encoding = (set_mask & ~mask) | 0x36000000; break; // 
  case B_IMM: group = "Unconditional branch (immediate)/B -"; mask = 0xfc000000; encoding = (set_mask & ~mask) | 0x14000000; break; // 
  case BL: group = "Unconditional branch (immediate)/BL -"; mask = 0xfc000000; encoding = (set_mask & ~mask) | 0x94000000; break; // 
  case ADR: group = "PC-relative addressing/ADR -"; mask = 0x9f000000; encoding = (set_mask & ~mask) | 0x10000000; break; // 
  case ADRP: group = "PC-relative addressing/ADRP -"; mask = 0x9f000000; encoding = (set_mask & ~mask) | 0x90000000; break; // 
default: return -1; break;
}
return 0;
}
