  packet->A64InstrIndex = A64_UNALLOCATED;

  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xffffffff) {
      // 0xd503201f, NOP: ' L=21 op0=20,19 op1=18,16 CRn=15,12 CRm=11,8 op2=7,5 Rt=4,0' - 'System/NOP -'
      case 0xd503201f: packet->A64InstrIndex = NOP;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->op0 = (packet->Opcode >> 19) & 0x3;
          packet->op1 = (packet->Opcode >> 16) & 0x7;
          packet->CRn = (packet->Opcode >> 12) & 0xf;
          packet->CRm = (packet->Opcode >> 8) & 0xf;
          packet->op2 = (packet->Opcode >> 5) & 0x7;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xd503209f, SEV: ' L=21 op0=20,19 op1=18,16 CRn=15,12 CRm=11,8 op2=7,5 Rt=4,0' - 'System/SEV -'
      case 0xd503209f: packet->A64InstrIndex = SEV;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->op0 = (packet->Opcode >> 19) & 0x3;
          packet->op1 = (packet->Opcode >> 16) & 0x7;
          packet->CRn = (packet->Opcode >> 12) & 0xf;
          packet->CRm = (packet->Opcode >> 8) & 0xf;
          packet->op2 = (packet->Opcode >> 5) & 0x7;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xd50320bf, SEVL: ' L=21 op0=20,19 op1=18,16 CRn=15,12 CRm=11,8 op2=7,5 Rt=4,0' - 'System/SEVL -'
      case 0xd50320bf: packet->A64InstrIndex = SEVL;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->op0 = (packet->Opcode >> 19) & 0x3;
          packet->op1 = (packet->Opcode >> 16) & 0x7;
          packet->CRn = (packet->Opcode >> 12) & 0xf;
          packet->CRm = (packet->Opcode >> 8) & 0xf;
          packet->op2 = (packet->Opcode >> 5) & 0x7;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xd503205f, WFE: ' L=21 op0=20,19 op1=18,16 CRn=15,12 CRm=11,8 op2=7,5 Rt=4,0' - 'System/WFE -'
      case 0xd503205f: packet->A64InstrIndex = WFE;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->op0 = (packet->Opcode >> 19) & 0x3;
          packet->op1 = (packet->Opcode >> 16) & 0x7;
          packet->CRn = (packet->Opcode >> 12) & 0xf;
          packet->CRm = (packet->Opcode >> 8) & 0xf;
          packet->op2 = (packet->Opcode >> 5) & 0x7;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xd503207f, WFI: ' L=21 op0=20,19 op1=18,16 CRn=15,12 CRm=11,8 op2=7,5 Rt=4,0' - 'System/WFI -'
      case 0xd503207f: packet->A64InstrIndex = WFI;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->op0 = (packet->Opcode >> 19) & 0x3;
          packet->op1 = (packet->Opcode >> 16) & 0x7;
          packet->CRn = (packet->Opcode >> 12) & 0xf;
          packet->CRm = (packet->Opcode >> 8) & 0xf;
          packet->op2 = (packet->Opcode >> 5) & 0x7;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xd503203f, YIELD: ' L=21 op0=20,19 op1=18,16 CRn=15,12 CRm=11,8 op2=7,5 Rt=4,0' - 'System/YIELD -'
      case 0xd503203f: packet->A64InstrIndex = YIELD;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->op0 = (packet->Opcode >> 19) & 0x3;
          packet->op1 = (packet->Opcode >> 16) & 0x7;
          packet->CRn = (packet->Opcode >> 12) & 0xf;
          packet->CRm = (packet->Opcode >> 8) & 0xf;
          packet->op2 = (packet->Opcode >> 5) & 0x7;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xd6bf03e0, DRPS: ' opc=24,21 op2=20,16 op3=15,10 Rn=9,5 op4=4,0' - 'Unconditional branch (register)/DRPS -'
      case 0xd6bf03e0: packet->A64InstrIndex = DRPS;
          packet->opc = (packet->Opcode >> 21) & 0xf;
          packet->op2 = (packet->Opcode >> 16) & 0x1f;
          packet->op3 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->op4 = packet->Opcode & 0x1f;
          break;
      // 0xd69f03e0, ERET: ' opc=24,21 op2=20,16 op3=15,10 Rn=9,5 op4=4,0' - 'Unconditional branch (register)/ERET -'
      case 0xd69f03e0: packet->A64InstrIndex = ERET;
          packet->opc = (packet->Opcode >> 21) & 0xf;
          packet->op2 = (packet->Opcode >> 16) & 0x1f;
          packet->op3 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->op4 = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xfffff0ff) {
      // 0xd503305f, CLREX: ' L=21 op0=20,19 op1=18,16 CRn=15,12 CRm=11,8 op2=7,5 Rt=4,0' - 'System/CLREX -'
      case 0xd503305f: packet->A64InstrIndex = CLREX;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->op0 = (packet->Opcode >> 19) & 0x3;
          packet->op1 = (packet->Opcode >> 16) & 0x7;
          packet->CRn = (packet->Opcode >> 12) & 0xf;
          packet->CRm = (packet->Opcode >> 8) & 0xf;
          packet->op2 = (packet->Opcode >> 5) & 0x7;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xd50330bf, DMB: ' L=21 op0=20,19 op1=18,16 CRn=15,12 CRm=11,8 op2=7,5 Rt=4,0' - 'System/DMB -'
      case 0xd50330bf: packet->A64InstrIndex = DMB;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->op0 = (packet->Opcode >> 19) & 0x3;
          packet->op1 = (packet->Opcode >> 16) & 0x7;
          packet->CRn = (packet->Opcode >> 12) & 0xf;
          packet->CRm = (packet->Opcode >> 8) & 0xf;
          packet->op2 = (packet->Opcode >> 5) & 0x7;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xd503309f, DSB: ' L=21 op0=20,19 op1=18,16 CRn=15,12 CRm=11,8 op2=7,5 Rt=4,0' - 'System/DSB -'
      case 0xd503309f: packet->A64InstrIndex = DSB;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->op0 = (packet->Opcode >> 19) & 0x3;
          packet->op1 = (packet->Opcode >> 16) & 0x7;
          packet->CRn = (packet->Opcode >> 12) & 0xf;
          packet->CRm = (packet->Opcode >> 8) & 0xf;
          packet->op2 = (packet->Opcode >> 5) & 0x7;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xd50330df, ISB: ' L=21 op0=20,19 op1=18,16 CRn=15,12 CRm=11,8 op2=7,5 Rt=4,0' - 'System/ISB -'
      case 0xd50330df: packet->A64InstrIndex = ISB;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->op0 = (packet->Opcode >> 19) & 0x3;
          packet->op1 = (packet->Opcode >> 16) & 0x7;
          packet->CRn = (packet->Opcode >> 12) & 0xf;
          packet->CRm = (packet->Opcode >> 8) & 0xf;
          packet->op2 = (packet->Opcode >> 5) & 0x7;
          packet->Rt = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xfffffc1f) {
      // 0xd63f0000, BLR: ' opc=24,21 op2=20,16 op3=15,10 Rn=9,5 op4=4,0' - 'Unconditional branch (register)/BLR -'
      case 0xd63f0000: packet->A64InstrIndex = BLR;
          packet->opc = (packet->Opcode >> 21) & 0xf;
          packet->op2 = (packet->Opcode >> 16) & 0x1f;
          packet->op3 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->op4 = packet->Opcode & 0x1f;
          break;
      // 0xd61f0000, BR: ' opc=24,21 op2=20,16 op3=15,10 Rn=9,5 op4=4,0' - 'Unconditional branch (register)/BR -'
      case 0xd61f0000: packet->A64InstrIndex = BR;
          packet->opc = (packet->Opcode >> 21) & 0xf;
          packet->op2 = (packet->Opcode >> 16) & 0x1f;
          packet->op3 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->op4 = packet->Opcode & 0x1f;
          break;
      // 0xd65f0000, RET: ' opc=24,21 op2=20,16 op3=15,10 Rn=9,5 op4=4,0' - 'Unconditional branch (register)/RET -'
      case 0xd65f0000: packet->A64InstrIndex = RET;
          packet->opc = (packet->Opcode >> 21) & 0xf;
          packet->op2 = (packet->Opcode >> 16) & 0x1f;
          packet->op3 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->op4 = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xfffff01f) {
      // 0xd503201f, HINT: ' L=21 op0=20,19 op1=18,16 CRn=15,12 CRm=11,8 op2=7,5 Rt=4,0' - 'System/HINT -'
      case 0xd503201f: packet->A64InstrIndex = HINT;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->op0 = (packet->Opcode >> 19) & 0x3;
          packet->op1 = (packet->Opcode >> 16) & 0x7;
          packet->CRn = (packet->Opcode >> 12) & 0xf;
          packet->CRm = (packet->Opcode >> 8) & 0xf;
          packet->op2 = (packet->Opcode >> 5) & 0x7;
          packet->Rt = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xffe0fc1f) {
      // 0x1e602000, FCMP_FROM_DP: ' M=31 S=29 type=23,22 Rm=20,16 op=15,14 Rn=9,5 opcode2=4,0' - 'Floating-point compare/FCMP Double-precision'
      case 0x1e602000: packet->A64InstrIndex = FCMP_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->op = (packet->Opcode >> 14) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->opcode2 = packet->Opcode & 0x1f;
          break;
      // 0x1e602008, FCMP_FROM_DP_ZERO: ' M=31 S=29 type=23,22 Rm=20,16 op=15,14 Rn=9,5 opcode2=4,0' - 'Floating-point compare/FCMP Double-precision, zero'
      case 0x1e602008: packet->A64InstrIndex = FCMP_FROM_DP_ZERO;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->op = (packet->Opcode >> 14) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->opcode2 = packet->Opcode & 0x1f;
          break;
      // 0x1e202000, FCMP_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 Rm=20,16 op=15,14 Rn=9,5 opcode2=4,0' - 'Floating-point compare/FCMP Single-precision'
      case 0x1e202000: packet->A64InstrIndex = FCMP_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->op = (packet->Opcode >> 14) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->opcode2 = packet->Opcode & 0x1f;
          break;
      // 0x1e202008, FCMP_SINGLE_FROM_SP_ZERO: ' M=31 S=29 type=23,22 Rm=20,16 op=15,14 Rn=9,5 opcode2=4,0' - 'Floating-point compare/FCMP Single-precision, zero'
      case 0x1e202008: packet->A64InstrIndex = FCMP_SINGLE_FROM_SP_ZERO;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->op = (packet->Opcode >> 14) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->opcode2 = packet->Opcode & 0x1f;
          break;
      // 0x1e602010, FCMPE_FROM_DP: ' M=31 S=29 type=23,22 Rm=20,16 op=15,14 Rn=9,5 opcode2=4,0' - 'Floating-point compare/FCMPE Double-precision'
      case 0x1e602010: packet->A64InstrIndex = FCMPE_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->op = (packet->Opcode >> 14) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->opcode2 = packet->Opcode & 0x1f;
          break;
      // 0x1e602018, FCMPE_FROM_DP_ZERO: ' M=31 S=29 type=23,22 Rm=20,16 op=15,14 Rn=9,5 opcode2=4,0' - 'Floating-point compare/FCMPE Double-precision, zero'
      case 0x1e602018: packet->A64InstrIndex = FCMPE_FROM_DP_ZERO;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->op = (packet->Opcode >> 14) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->opcode2 = packet->Opcode & 0x1f;
          break;
      // 0x1e202010, FCMPE_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 Rm=20,16 op=15,14 Rn=9,5 opcode2=4,0' - 'Floating-point compare/FCMPE Single-precision'
      case 0x1e202010: packet->A64InstrIndex = FCMPE_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->op = (packet->Opcode >> 14) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->opcode2 = packet->Opcode & 0x1f;
          break;
      // 0x1e202018, FCMPE_SINGLE_FROM_SP_ZERO: ' M=31 S=29 type=23,22 Rm=20,16 op=15,14 Rn=9,5 opcode2=4,0' - 'Floating-point compare/FCMPE Single-precision, zero'
      case 0x1e202018: packet->A64InstrIndex = FCMPE_SINGLE_FROM_SP_ZERO;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->op = (packet->Opcode >> 14) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->opcode2 = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xfffffc00) {
      // 0x1e640000, FCVTAS_FROM_DP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTAS (scalar) Double-precision to 32-bit'
      case 0x1e640000: packet->A64InstrIndex = FCVTAS_FROM_DP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e640000, FCVTAS_FROM_DP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTAS (scalar) Double-precision to 64-bit'
      case 0x9e640000: packet->A64InstrIndex = FCVTAS_FROM_DP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e240000, FCVTAS_SINGLE_FROM_SP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTAS (scalar) Single-precision to 32-bit'
      case 0x1e240000: packet->A64InstrIndex = FCVTAS_SINGLE_FROM_SP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e240000, FCVTAS_SINGLE_FROM_SP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTAS (scalar) Single-precision to 64-bit'
      case 0x9e240000: packet->A64InstrIndex = FCVTAS_SINGLE_FROM_SP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e650000, FCVTAU_FROM_DP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTAU (scalar) Double-precision to 32-bit'
      case 0x1e650000: packet->A64InstrIndex = FCVTAU_FROM_DP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e650000, FCVTAU_FROM_DP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTAU (scalar) Double-precision to 64-bit'
      case 0x9e650000: packet->A64InstrIndex = FCVTAU_FROM_DP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e250000, FCVTAU_SINGLE_FROM_SP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTAU (scalar) Single-precision to 32-bit'
      case 0x1e250000: packet->A64InstrIndex = FCVTAU_SINGLE_FROM_SP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e250000, FCVTAU_SINGLE_FROM_SP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTAU (scalar) Single-precision to 64-bit'
      case 0x9e250000: packet->A64InstrIndex = FCVTAU_SINGLE_FROM_SP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e700000, FCVTMS_FROM_DP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTMS (scalar) Double-precision to 32-bit'
      case 0x1e700000: packet->A64InstrIndex = FCVTMS_FROM_DP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e700000, FCVTMS_FROM_DP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTMS (scalar) Double-precision to 64-bit'
      case 0x9e700000: packet->A64InstrIndex = FCVTMS_FROM_DP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e300000, FCVTMS_SINGLE_FROM_SP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTMS (scalar) Single-precision to 32-bit'
      case 0x1e300000: packet->A64InstrIndex = FCVTMS_SINGLE_FROM_SP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e300000, FCVTMS_SINGLE_FROM_SP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTMS (scalar) Single-precision to 64-bit'
      case 0x9e300000: packet->A64InstrIndex = FCVTMS_SINGLE_FROM_SP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e710000, FCVTMU_FROM_DP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTMU (scalar) Double-precision to 32-bit'
      case 0x1e710000: packet->A64InstrIndex = FCVTMU_FROM_DP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e710000, FCVTMU_FROM_DP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTMU (scalar) Double-precision to 64-bit'
      case 0x9e710000: packet->A64InstrIndex = FCVTMU_FROM_DP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e310000, FCVTMU_SINGLE_FROM_SP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTMU (scalar) Single-precision to 32-bit'
      case 0x1e310000: packet->A64InstrIndex = FCVTMU_SINGLE_FROM_SP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e310000, FCVTMU_SINGLE_FROM_SP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTMU (scalar) Single-precision to 64-bit'
      case 0x9e310000: packet->A64InstrIndex = FCVTMU_SINGLE_FROM_SP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e600000, FCVTNS_FROM_DP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTNS (scalar) Double-precision to 32-bit'
      case 0x1e600000: packet->A64InstrIndex = FCVTNS_FROM_DP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e600000, FCVTNS_FROM_DP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTNS (scalar) Double-precision to 64-bit'
      case 0x9e600000: packet->A64InstrIndex = FCVTNS_FROM_DP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e200000, FCVTNS_SINGLE_FROM_SP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTNS (scalar) Single-precision to 32-bit'
      case 0x1e200000: packet->A64InstrIndex = FCVTNS_SINGLE_FROM_SP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e200000, FCVTNS_SINGLE_FROM_SP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTNS (scalar) Single-precision to 64-bit'
      case 0x9e200000: packet->A64InstrIndex = FCVTNS_SINGLE_FROM_SP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e610000, FCVTNU_FROM_DP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTNU (scalar) Double-precision to 32-bit'
      case 0x1e610000: packet->A64InstrIndex = FCVTNU_FROM_DP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e610000, FCVTNU_FROM_DP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTNU (scalar) Double-precision to 64-bit'
      case 0x9e610000: packet->A64InstrIndex = FCVTNU_FROM_DP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e210000, FCVTNU_SINGLE_FROM_SP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTNU (scalar) Single-precision to 32-bit'
      case 0x1e210000: packet->A64InstrIndex = FCVTNU_SINGLE_FROM_SP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e210000, FCVTNU_SINGLE_FROM_SP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTNU (scalar) Single-precision to 64-bit'
      case 0x9e210000: packet->A64InstrIndex = FCVTNU_SINGLE_FROM_SP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e680000, FCVTPS_FROM_DP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTPS (scalar) Double-precision to 32-bit'
      case 0x1e680000: packet->A64InstrIndex = FCVTPS_FROM_DP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e680000, FCVTPS_FROM_DP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTPS (scalar) Double-precision to 64-bit'
      case 0x9e680000: packet->A64InstrIndex = FCVTPS_FROM_DP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e280000, FCVTPS_SINGLE_FROM_SP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTPS (scalar) Single-precision to 32-bit'
      case 0x1e280000: packet->A64InstrIndex = FCVTPS_SINGLE_FROM_SP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e280000, FCVTPS_SINGLE_FROM_SP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTPS (scalar) Single-precision to 64-bit'
      case 0x9e280000: packet->A64InstrIndex = FCVTPS_SINGLE_FROM_SP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e690000, FCVTPU_FROM_DP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTPU (scalar) Double-precision to 32-bit'
      case 0x1e690000: packet->A64InstrIndex = FCVTPU_FROM_DP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e690000, FCVTPU_FROM_DP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTPU (scalar) Double-precision to 64-bit'
      case 0x9e690000: packet->A64InstrIndex = FCVTPU_FROM_DP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e290000, FCVTPU_SINGLE_FROM_SP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTPU (scalar) Single-precision to 32-bit'
      case 0x1e290000: packet->A64InstrIndex = FCVTPU_SINGLE_FROM_SP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e290000, FCVTPU_SINGLE_FROM_SP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTPU (scalar) Single-precision to 64-bit'
      case 0x9e290000: packet->A64InstrIndex = FCVTPU_SINGLE_FROM_SP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e780000, FCVTZS_FROM_DP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTZS (scalar, integer) Double-precision to 32-bit'
      case 0x1e780000: packet->A64InstrIndex = FCVTZS_FROM_DP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e780000, FCVTZS_FROM_DP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTZS (scalar, integer) Double-precision to 64-bit'
      case 0x9e780000: packet->A64InstrIndex = FCVTZS_FROM_DP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e380000, FCVTZS_SINGLE_FROM_SP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTZS (scalar, integer) Single-precision to 32-bit'
      case 0x1e380000: packet->A64InstrIndex = FCVTZS_SINGLE_FROM_SP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e380000, FCVTZS_SINGLE_FROM_SP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTZS (scalar, integer) Single-precision to 64-bit'
      case 0x9e380000: packet->A64InstrIndex = FCVTZS_SINGLE_FROM_SP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e790000, FCVTZU_FROM_DP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTZU (scalar, integer) Double-precision to 32-bit'
      case 0x1e790000: packet->A64InstrIndex = FCVTZU_FROM_DP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e790000, FCVTZU_FROM_DP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTZU (scalar, integer) Double-precision to 64-bit'
      case 0x9e790000: packet->A64InstrIndex = FCVTZU_FROM_DP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e390000, FCVTZU_SINGLE_FROM_SP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTZU (scalar, integer) Single-precision to 32-bit'
      case 0x1e390000: packet->A64InstrIndex = FCVTZU_SINGLE_FROM_SP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e390000, FCVTZU_SINGLE_FROM_SP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FCVTZU (scalar, integer) Single-precision to 64-bit'
      case 0x9e390000: packet->A64InstrIndex = FCVTZU_SINGLE_FROM_SP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e270000, FMOV_SINGLE_TO_SP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FMOV (general) 32-bit to single-precision'
      case 0x1e270000: packet->A64InstrIndex = FMOV_SINGLE_TO_SP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e670000, FMOV_TO_DP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FMOV (general) 64-bit to double-precision'
      case 0x9e670000: packet->A64InstrIndex = FMOV_TO_DP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9eaf0000, FMOV_FP_8_64_128_TO_TOP: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FMOV (general) 64-bit to top half of 128-bit'
      case 0x9eaf0000: packet->A64InstrIndex = FMOV_FP_8_64_128_TO_TOP;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e660000, FMOV_FROM_DP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FMOV (general) Double-precision to 64-bit'
      case 0x9e660000: packet->A64InstrIndex = FMOV_FROM_DP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e260000, FMOV_SINGLE_FROM_SP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FMOV (general) Single-precision to 32-bit'
      case 0x1e260000: packet->A64InstrIndex = FMOV_SINGLE_FROM_SP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9eae0000, FMOV_FP_8_64_128: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/FMOV (general) Top half of 128-bit to 64-bit'
      case 0x9eae0000: packet->A64InstrIndex = FMOV_FP_8_64_128;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e620000, SCVTF_TO_DP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/SCVTF (scalar, integer) 32-bit to double-precision'
      case 0x1e620000: packet->A64InstrIndex = SCVTF_TO_DP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e220000, SCVTF_SINGLE_TO_SP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/SCVTF (scalar, integer) 32-bit to single-precision'
      case 0x1e220000: packet->A64InstrIndex = SCVTF_SINGLE_TO_SP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e620000, SCVTF_TO_DP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/SCVTF (scalar, integer) 64-bit to double-precision'
      case 0x9e620000: packet->A64InstrIndex = SCVTF_TO_DP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e220000, SCVTF_SINGLE_TO_SP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/SCVTF (scalar, integer) 64-bit to single-precision'
      case 0x9e220000: packet->A64InstrIndex = SCVTF_SINGLE_TO_SP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e630000, UCVTF_TO_DP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/UCVTF (scalar, integer) 32-bit to double-precision'
      case 0x1e630000: packet->A64InstrIndex = UCVTF_TO_DP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e230000, UCVTF_SINGLE_TO_SP_FP_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/UCVTF (scalar, integer) 32-bit to single-precision'
      case 0x1e230000: packet->A64InstrIndex = UCVTF_SINGLE_TO_SP_FP_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e630000, UCVTF_TO_DP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/UCVTF (scalar, integer) 64-bit to double-precision'
      case 0x9e630000: packet->A64InstrIndex = UCVTF_TO_DP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e230000, UCVTF_SINGLE_TO_SP_FP_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and integer/UCVTF (scalar, integer) 64-bit to single-precision'
      case 0x9e230000: packet->A64InstrIndex = UCVTF_SINGLE_TO_SP_FP_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x4e285800, AESD: ' size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Cryptographic AES/AESD -'
      case 0x4e285800: packet->A64InstrIndex = AESD;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x4e284800, AESE: ' size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Cryptographic AES/AESE -'
      case 0x4e284800: packet->A64InstrIndex = AESE;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x4e287800, AESIMC: ' size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Cryptographic AES/AESIMC -'
      case 0x4e287800: packet->A64InstrIndex = AESIMC;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x4e286800, AESMC: ' size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Cryptographic AES/AESMC -'
      case 0x4e286800: packet->A64InstrIndex = AESMC;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e280800, SHA1H_REG: ' size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Cryptographic two-register SHA/SHA1H -'
      case 0x5e280800: packet->A64InstrIndex = SHA1H_REG;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e281800, SHA1SU1_REG: ' size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Cryptographic two-register SHA/SHA1SU1 -'
      case 0x5e281800: packet->A64InstrIndex = SHA1SU1_REG;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e282800, SHA256SU0_REG: ' size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Cryptographic two-register SHA/SHA256SU0 -'
      case 0x5e282800: packet->A64InstrIndex = SHA256SU0_REG;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5ac01400, CLS_32: ' sf=31 S=29 opcode2=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (1 source)/CLS 32-bit'
      case 0x5ac01400: packet->A64InstrIndex = CLS_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->opcode2 = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xdac01400, CLS_64: ' sf=31 S=29 opcode2=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (1 source)/CLS 64-bit'
      case 0xdac01400: packet->A64InstrIndex = CLS_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->opcode2 = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5ac01000, CLZ_32: ' sf=31 S=29 opcode2=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (1 source)/CLZ 32-bit'
      case 0x5ac01000: packet->A64InstrIndex = CLZ_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->opcode2 = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xdac01000, CLZ_64: ' sf=31 S=29 opcode2=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (1 source)/CLZ 64-bit'
      case 0xdac01000: packet->A64InstrIndex = CLZ_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->opcode2 = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5ac00000, RBIT_32: ' sf=31 S=29 opcode2=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (1 source)/RBIT 32-bit'
      case 0x5ac00000: packet->A64InstrIndex = RBIT_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->opcode2 = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xdac00000, RBIT_64: ' sf=31 S=29 opcode2=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (1 source)/RBIT 64-bit'
      case 0xdac00000: packet->A64InstrIndex = RBIT_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->opcode2 = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5ac00800, REV_32: ' sf=31 S=29 opcode2=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (1 source)/REV 32-bit'
      case 0x5ac00800: packet->A64InstrIndex = REV_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->opcode2 = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xdac00c00, REV_64: ' sf=31 S=29 opcode2=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (1 source)/REV 64-bit'
      case 0xdac00c00: packet->A64InstrIndex = REV_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->opcode2 = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5ac00400, REV16_32: ' sf=31 S=29 opcode2=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (1 source)/REV16 32-bit'
      case 0x5ac00400: packet->A64InstrIndex = REV16_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->opcode2 = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xdac00400, REV16_64: ' sf=31 S=29 opcode2=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (1 source)/REV16 64-bit'
      case 0xdac00400: packet->A64InstrIndex = REV16_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->opcode2 = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xdac00800, REV32: ' sf=31 S=29 opcode2=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (1 source)/REV32 -'
      case 0xdac00800: packet->A64InstrIndex = REV32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->opcode2 = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e60c000, FABS_FROM_DP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FABS (scalar) Double-precision'
      case 0x1e60c000: packet->A64InstrIndex = FABS_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e20c000, FABS_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FABS (scalar) Single-precision'
      case 0x1e20c000: packet->A64InstrIndex = FABS_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e63c000, FCVT_FROM_DP_TO_HP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FCVT Double-precision to half-precision'
      case 0x1e63c000: packet->A64InstrIndex = FCVT_FROM_DP_TO_HP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e624000, FCVT_SINGLE_FROM_DP_TO_SP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FCVT Double-precision to single-precision'
      case 0x1e624000: packet->A64InstrIndex = FCVT_SINGLE_FROM_DP_TO_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1ee2c000, FCVT_FROM_HP_TO_DP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FCVT Half-precision to double-precision'
      case 0x1ee2c000: packet->A64InstrIndex = FCVT_FROM_HP_TO_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1ee24000, FCVT_SINGLE_FROM_HP_TO_SP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FCVT Half-precision to single-precision'
      case 0x1ee24000: packet->A64InstrIndex = FCVT_SINGLE_FROM_HP_TO_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e22c000, FCVT_SINGLE_FROM_SP_TO_DP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FCVT Single-precision to double-precision'
      case 0x1e22c000: packet->A64InstrIndex = FCVT_SINGLE_FROM_SP_TO_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e23c000, FCVT_SINGLE_FROM_SP_TO_HP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FCVT Single-precision to half-precision'
      case 0x1e23c000: packet->A64InstrIndex = FCVT_SINGLE_FROM_SP_TO_HP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e604000, FMOV_REG_FROM_DP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FMOV (register) Double-precision'
      case 0x1e604000: packet->A64InstrIndex = FMOV_REG_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e204000, FMOV_SINGLE_REG_FROM_SP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FMOV (register) Single-precision'
      case 0x1e204000: packet->A64InstrIndex = FMOV_SINGLE_REG_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e614000, FNEG_FROM_DP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FNEG (scalar) Double-precision'
      case 0x1e614000: packet->A64InstrIndex = FNEG_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e214000, FNEG_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FNEG (scalar) Single-precision'
      case 0x1e214000: packet->A64InstrIndex = FNEG_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e664000, FRINTA_FROM_DP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FRINTA (scalar) Double-precision'
      case 0x1e664000: packet->A64InstrIndex = FRINTA_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e264000, FRINTA_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FRINTA (scalar) Single-precision'
      case 0x1e264000: packet->A64InstrIndex = FRINTA_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e67c000, FRINTI_FROM_DP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FRINTI (scalar) Double-precision'
      case 0x1e67c000: packet->A64InstrIndex = FRINTI_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e27c000, FRINTI_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FRINTI (scalar) Single-precision'
      case 0x1e27c000: packet->A64InstrIndex = FRINTI_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e654000, FRINTM_FROM_DP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FRINTM (scalar) Double-precision'
      case 0x1e654000: packet->A64InstrIndex = FRINTM_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e254000, FRINTM_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FRINTM (scalar) Single-precision'
      case 0x1e254000: packet->A64InstrIndex = FRINTM_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e644000, FRINTN_FROM_DP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FRINTN (scalar) Double-precision'
      case 0x1e644000: packet->A64InstrIndex = FRINTN_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e244000, FRINTN_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FRINTN (scalar) Single-precision'
      case 0x1e244000: packet->A64InstrIndex = FRINTN_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e64c000, FRINTP_FROM_DP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FRINTP (scalar) Double-precision'
      case 0x1e64c000: packet->A64InstrIndex = FRINTP_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e24c000, FRINTP_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FRINTP (scalar) Single-precision'
      case 0x1e24c000: packet->A64InstrIndex = FRINTP_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e674000, FRINTX_FROM_DP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FRINTX (scalar) Double-precision'
      case 0x1e674000: packet->A64InstrIndex = FRINTX_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e274000, FRINTX_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FRINTX (scalar) Single-precision'
      case 0x1e274000: packet->A64InstrIndex = FRINTX_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e65c000, FRINTZ_FROM_DP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FRINTZ (scalar) Double-precision'
      case 0x1e65c000: packet->A64InstrIndex = FRINTZ_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e25c000, FRINTZ_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FRINTZ (scalar) Single-precision'
      case 0x1e25c000: packet->A64InstrIndex = FRINTZ_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e61c000, FSQRT_FROM_DP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FSQRT (scalar) Double-precision'
      case 0x1e61c000: packet->A64InstrIndex = FSQRT_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e21c000, FSQRT_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 opcode=20,15 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (1 source)/FSQRT (scalar) Single-precision'
      case 0x1e21c000: packet->A64InstrIndex = FSQRT_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 15) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xfff8f01f) {
      // 0xd500401f, MSR_IMM: ' L=21 op0=20,19 op1=18,16 CRn=15,12 CRm=11,8 op2=7,5 Rt=4,0' - 'System/MSR (immediate) -'
      case 0xd500401f: packet->A64InstrIndex = MSR_IMM;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->op0 = (packet->Opcode >> 19) & 0x3;
          packet->op1 = (packet->Opcode >> 16) & 0x7;
          packet->CRn = (packet->Opcode >> 12) & 0xf;
          packet->CRm = (packet->Opcode >> 8) & 0xf;
          packet->op2 = (packet->Opcode >> 5) & 0x7;
          packet->Rt = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xffbffc00) {
      // 0x7e30d800, SIMD_FADDP: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar pairwise/FADDP (scalar) -'
      case 0x7e30d800: packet->A64InstrIndex = SIMD_FADDP;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e30c800, SIMD_FMAXNMP: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar pairwise/FMAXNMP (scalar) -'
      case 0x7e30c800: packet->A64InstrIndex = SIMD_FMAXNMP;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e30f800, SIMD_FMAXP: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar pairwise/FMAXP (scalar) -'
      case 0x7e30f800: packet->A64InstrIndex = SIMD_FMAXP;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7eb0c800, SIMD_FMINNMP: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar pairwise/FMINNMP (scalar) -'
      case 0x7eb0c800: packet->A64InstrIndex = SIMD_FMINNMP;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7eb0f800, SIMD_FMINP: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar pairwise/FMINP (scalar) -'
      case 0x7eb0f800: packet->A64InstrIndex = SIMD_FMINP;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5ea0d800, SIMD_FCMEQ_REG_SCALAR_ZERO: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FCMEQ (zero) Scalar'
      case 0x5ea0d800: packet->A64InstrIndex = SIMD_FCMEQ_REG_SCALAR_ZERO;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7ea0c800, SIMD_FCMGE_REG_SCALAR_ZERO: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FCMGE (zero) Scalar'
      case 0x7ea0c800: packet->A64InstrIndex = SIMD_FCMGE_REG_SCALAR_ZERO;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5ea0c800, SIMD_FCMGT_REG_SCALAR_ZERO: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FCMGT (zero) Scalar'
      case 0x5ea0c800: packet->A64InstrIndex = SIMD_FCMGT_REG_SCALAR_ZERO;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7ea0d800, SIMD_FCMLE_REG_SCALAR_ZERO: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FCMLE (zero) Scalar'
      case 0x7ea0d800: packet->A64InstrIndex = SIMD_FCMLE_REG_SCALAR_ZERO;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5ea0e800, SIMD_FCMLT_REG_SCALAR_ZERO: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FCMLT (zero) Scalar'
      case 0x5ea0e800: packet->A64InstrIndex = SIMD_FCMLT_REG_SCALAR_ZERO;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e21c800, SIMD_FCVTAS_REG_SCALAR_VEC: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FCVTAS (vector) Scalar'
      case 0x5e21c800: packet->A64InstrIndex = SIMD_FCVTAS_REG_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e21c800, SIMD_FCVTAU_REG_SCALAR_VEC: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FCVTAU (vector) Scalar'
      case 0x7e21c800: packet->A64InstrIndex = SIMD_FCVTAU_REG_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e21b800, SIMD_FCVTMS_REG_SCALAR_VEC: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FCVTMS (vector) Scalar'
      case 0x5e21b800: packet->A64InstrIndex = SIMD_FCVTMS_REG_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e21b800, SIMD_FCVTMU_REG_SCALAR_VEC: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FCVTMU (vector) Scalar'
      case 0x7e21b800: packet->A64InstrIndex = SIMD_FCVTMU_REG_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e21a800, SIMD_FCVTNS_REG_SCALAR_VEC: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FCVTNS (vector) Scalar'
      case 0x5e21a800: packet->A64InstrIndex = SIMD_FCVTNS_REG_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e21a800, SIMD_FCVTNU_REG_SCALAR_VEC: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FCVTNU (vector) Scalar'
      case 0x7e21a800: packet->A64InstrIndex = SIMD_FCVTNU_REG_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5ea1a800, SIMD_FCVTPS_REG_SCALAR_VEC: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FCVTPS (vector) Scalar'
      case 0x5ea1a800: packet->A64InstrIndex = SIMD_FCVTPS_REG_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7ea1a800, SIMD_FCVTPU_REG_SCALAR_VEC: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FCVTPU (vector) Scalar'
      case 0x7ea1a800: packet->A64InstrIndex = SIMD_FCVTPU_REG_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e216800, SIMD_FCVTXN_REG_SCALAR: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FCVTXN, FCVTXN2 Scalar'
      case 0x7e216800: packet->A64InstrIndex = SIMD_FCVTXN_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5ea1b800, SIMD_FCVTZS_REG_SCALAR_VEC: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FCVTZS (vector, integer) Scalar'
      case 0x5ea1b800: packet->A64InstrIndex = SIMD_FCVTZS_REG_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7ea1b800, SIMD_FCVTZU_REG_SCALAR_VEC: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FCVTZU (vector, integer) Scalar'
      case 0x7ea1b800: packet->A64InstrIndex = SIMD_FCVTZU_REG_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5ea1d800, SIMD_FRECPE_REG_SCALAR: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FRECPE Scalar'
      case 0x5ea1d800: packet->A64InstrIndex = SIMD_FRECPE_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5ea1f800, SIMD_FRECPX_REG: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FRECPX -'
      case 0x5ea1f800: packet->A64InstrIndex = SIMD_FRECPX_REG;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7ea1d800, SIMD_FRSQRTE_REG_SCALAR: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/FRSQRTE Scalar'
      case 0x7ea1d800: packet->A64InstrIndex = SIMD_FRSQRTE_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e21d800, SIMD_SCVTF_REG_SCALAR_VEC: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/SCVTF (vector, integer) Scalar'
      case 0x5e21d800: packet->A64InstrIndex = SIMD_SCVTF_REG_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e21d800, SIMD_UCVTF_REG_SCALAR_VEC: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/UCVTF (vector, integer) Scalar'
      case 0x7e21d800: packet->A64InstrIndex = SIMD_UCVTF_REG_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbffffc00) {
      // 0x0ddf8400, SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_64: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 64-bit, immediate offset'
      case 0x0ddf8400: packet->A64InstrIndex = SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dff8400, SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_64: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 64-bit, immediate offset'
      case 0x0dff8400: packet->A64InstrIndex = SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0ddfa400, SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_64: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 64-bit, immediate offset'
      case 0x0ddfa400: packet->A64InstrIndex = SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dffa400, SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_64: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 64-bit, immediate offset'
      case 0x0dffa400: packet->A64InstrIndex = SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d9f8400, SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_64: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 64-bit, immediate offset'
      case 0x0d9f8400: packet->A64InstrIndex = SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dbf8400, SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_64: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 64-bit, immediate offset'
      case 0x0dbf8400: packet->A64InstrIndex = SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d9fa400, SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_64: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 64-bit, immediate offset'
      case 0x0d9fa400: packet->A64InstrIndex = SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dbfa400, SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_64: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 64-bit, immediate offset'
      case 0x0dbfa400: packet->A64InstrIndex = SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d408400, SIMD_LD1_SINGLE_STRUCT_64: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD1 (single structure) 64-bit'
      case 0x0d408400: packet->A64InstrIndex = SIMD_LD1_SINGLE_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d608400, SIMD_LD2_SINGLE_STRUCT_64: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD2 (single structure) 64-bit'
      case 0x0d608400: packet->A64InstrIndex = SIMD_LD2_SINGLE_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d40a400, SIMD_LD3_SINGLE_STRUCT_64: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD3 (single structure) 64-bit'
      case 0x0d40a400: packet->A64InstrIndex = SIMD_LD3_SINGLE_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d60a400, SIMD_LD4_SINGLE_STRUCT_64: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD4 (single structure) 64-bit'
      case 0x0d60a400: packet->A64InstrIndex = SIMD_LD4_SINGLE_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d008400, SIMD_ST1_SINGLE_STRUCT_64: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/ST1 (single structure) 64-bit'
      case 0x0d008400: packet->A64InstrIndex = SIMD_ST1_SINGLE_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d208400, SIMD_ST2_SINGLE_STRUCT_64: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/ST2 (single structure) 64-bit'
      case 0x0d208400: packet->A64InstrIndex = SIMD_ST2_SINGLE_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d00a400, SIMD_ST3_SINGLE_STRUCT_64: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/ST3 (single structure) 64-bit'
      case 0x0d00a400: packet->A64InstrIndex = SIMD_ST3_SINGLE_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d20a400, SIMD_ST4_SINGLE_STRUCT_64: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/ST4 (single structure) 64-bit'
      case 0x0d20a400: packet->A64InstrIndex = SIMD_ST4_SINGLE_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x2e205800, SIMD_NOT_REG: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/NOT -'
      case 0x2e205800: packet->A64InstrIndex = SIMD_NOT_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e605800, SIMD_RBIT_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/RBIT (vector) -'
      case 0x2e605800: packet->A64InstrIndex = SIMD_RBIT_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xff3ffc00) {
      // 0x5e31b800, SIMD_ADDP: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar pairwise/ADDP (scalar) -'
      case 0x5e31b800: packet->A64InstrIndex = SIMD_ADDP;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e20b800, SIMD_ABS_REG_SCALAR: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/ABS Scalar'
      case 0x5e20b800: packet->A64InstrIndex = SIMD_ABS_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e209800, SIMD_CMEQ_REG_SCALAR_ZERO: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/CMEQ (zero) Scalar'
      case 0x5e209800: packet->A64InstrIndex = SIMD_CMEQ_REG_SCALAR_ZERO;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e208800, SIMD_CMGE_REG_SCALAR_ZERO: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/CMGE (zero) Scalar'
      case 0x7e208800: packet->A64InstrIndex = SIMD_CMGE_REG_SCALAR_ZERO;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e208800, SIMD_CMGT_REG_SCALAR_ZERO: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/CMGT (zero) Scalar'
      case 0x5e208800: packet->A64InstrIndex = SIMD_CMGT_REG_SCALAR_ZERO;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e209800, SIMD_CMLE_REG_SCALAR_ZERO: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/CMLE (zero) Scalar'
      case 0x7e209800: packet->A64InstrIndex = SIMD_CMLE_REG_SCALAR_ZERO;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e20a800, SIMD_CMLT_REG_SCALAR_ZERO: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/CMLT (zero) Scalar'
      case 0x5e20a800: packet->A64InstrIndex = SIMD_CMLT_REG_SCALAR_ZERO;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e20b800, SIMD_NEG_REG_SCALAR_VEC: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/NEG (vector) Scalar'
      case 0x7e20b800: packet->A64InstrIndex = SIMD_NEG_REG_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e207800, SIMD_SQABS_REG_SCALAR: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/SQABS Scalar'
      case 0x5e207800: packet->A64InstrIndex = SIMD_SQABS_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e207800, SIMD_SQNEG_REG_SCALAR: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/SQNEG Scalar'
      case 0x7e207800: packet->A64InstrIndex = SIMD_SQNEG_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e214800, SIMD_SQXTN_REG_SCALAR: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/SQXTN, SQXTN2 Scalar'
      case 0x5e214800: packet->A64InstrIndex = SIMD_SQXTN_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e212800, SIMD_SQXTUN_REG_SCALAR: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/SQXTUN, SQXTUN2 Scalar'
      case 0x7e212800: packet->A64InstrIndex = SIMD_SQXTUN_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e203800, SIMD_SUQADD_REG_SCALAR: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/SUQADD Scalar'
      case 0x5e203800: packet->A64InstrIndex = SIMD_SUQADD_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e214800, SIMD_UQXTN_REG_SCALAR: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/UQXTN, UQXTN2 Scalar'
      case 0x7e214800: packet->A64InstrIndex = SIMD_UQXTN_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e203800, SIMD_USQADD_REG_SCALAR: ' U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar two-register miscellaneous/USQADD Scalar'
      case 0x7e203800: packet->A64InstrIndex = SIMD_USQADD_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbfffec00) {
      // 0x0ddf8000, SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_32: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 32-bit, immediate offset'
      case 0x0ddf8000: packet->A64InstrIndex = SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dff8000, SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_32: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 32-bit, immediate offset'
      case 0x0dff8000: packet->A64InstrIndex = SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0ddfa000, SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_32: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 32-bit, immediate offset'
      case 0x0ddfa000: packet->A64InstrIndex = SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dffa000, SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_32: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 32-bit, immediate offset'
      case 0x0dffa000: packet->A64InstrIndex = SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d9f8000, SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_32: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 32-bit, immediate offset'
      case 0x0d9f8000: packet->A64InstrIndex = SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dbf8000, SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_32: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 32-bit, immediate offset'
      case 0x0dbf8000: packet->A64InstrIndex = SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d9fa000, SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_32: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 32-bit, immediate offset'
      case 0x0d9fa000: packet->A64InstrIndex = SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dbfa000, SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_32: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 32-bit, immediate offset'
      case 0x0dbfa000: packet->A64InstrIndex = SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d408000, SIMD_LD1_SINGLE_STRUCT_32: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD1 (single structure) 32-bit'
      case 0x0d408000: packet->A64InstrIndex = SIMD_LD1_SINGLE_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d608000, SIMD_LD2_SINGLE_STRUCT_32: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD2 (single structure) 32-bit'
      case 0x0d608000: packet->A64InstrIndex = SIMD_LD2_SINGLE_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d40a000, SIMD_LD3_SINGLE_STRUCT_32: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD3 (single structure) 32-bit'
      case 0x0d40a000: packet->A64InstrIndex = SIMD_LD3_SINGLE_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d60a000, SIMD_LD4_SINGLE_STRUCT_32: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD4 (single structure) 32-bit'
      case 0x0d60a000: packet->A64InstrIndex = SIMD_LD4_SINGLE_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d008000, SIMD_ST1_SINGLE_STRUCT_32: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/ST1 (single structure) 32-bit'
      case 0x0d008000: packet->A64InstrIndex = SIMD_ST1_SINGLE_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d208000, SIMD_ST2_SINGLE_STRUCT_32: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/ST2 (single structure) 32-bit'
      case 0x0d208000: packet->A64InstrIndex = SIMD_ST2_SINGLE_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d00a000, SIMD_ST3_SINGLE_STRUCT_32: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/ST3 (single structure) 32-bit'
      case 0x0d00a000: packet->A64InstrIndex = SIMD_ST3_SINGLE_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d20a000, SIMD_ST4_SINGLE_STRUCT_32: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/ST4 (single structure) 32-bit'
      case 0x0d20a000: packet->A64InstrIndex = SIMD_ST4_SINGLE_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbfbffc00) {
      // 0x2e30c800, SIMD_FMAXNMV: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD across lanes/FMAXNMV -'
      case 0x2e30c800: packet->A64InstrIndex = SIMD_FMAXNMV;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e30f800, SIMD_FMAXV: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD across lanes/FMAXV -'
      case 0x2e30f800: packet->A64InstrIndex = SIMD_FMAXV;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2eb0c800, SIMD_FMINNMV: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD across lanes/FMINNMV -'
      case 0x2eb0c800: packet->A64InstrIndex = SIMD_FMINNMV;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2eb0f800, SIMD_FMINV: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD across lanes/FMINV -'
      case 0x2eb0f800: packet->A64InstrIndex = SIMD_FMINV;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0ea0f800, SIMD_FABS_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FABS (vector) -'
      case 0x0ea0f800: packet->A64InstrIndex = SIMD_FABS_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0ea0d800, SIMD_FCMEQ_REG_VEC_ZERO: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FCMEQ (zero) Vector'
      case 0x0ea0d800: packet->A64InstrIndex = SIMD_FCMEQ_REG_VEC_ZERO;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2ea0c800, SIMD_FCMGE_REG_VEC_ZERO: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FCMGE (zero) Vector'
      case 0x2ea0c800: packet->A64InstrIndex = SIMD_FCMGE_REG_VEC_ZERO;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0ea0c800, SIMD_FCMGT_REG_VEC_ZERO: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FCMGT (zero) Vector'
      case 0x0ea0c800: packet->A64InstrIndex = SIMD_FCMGT_REG_VEC_ZERO;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2ea0d800, SIMD_FCMLE_REG_VEC_ZERO: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FCMLE (zero) Vector'
      case 0x2ea0d800: packet->A64InstrIndex = SIMD_FCMLE_REG_VEC_ZERO;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0ea0e800, SIMD_FCMLT_REG_VEC_ZERO: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FCMLT (zero) Vector'
      case 0x0ea0e800: packet->A64InstrIndex = SIMD_FCMLT_REG_VEC_ZERO;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e21c800, SIMD_FCVTAS_REG_VEC_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FCVTAS (vector) Vector'
      case 0x0e21c800: packet->A64InstrIndex = SIMD_FCVTAS_REG_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e21c800, SIMD_FCVTAU_REG_VEC_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FCVTAU (vector) Vector'
      case 0x2e21c800: packet->A64InstrIndex = SIMD_FCVTAU_REG_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e217800, SIMD_FCVTL_REG: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FCVTL, FCVTL2 -'
      case 0x0e217800: packet->A64InstrIndex = SIMD_FCVTL_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e21b800, SIMD_FCVTMS_REG_VEC_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FCVTMS (vector) Vector'
      case 0x0e21b800: packet->A64InstrIndex = SIMD_FCVTMS_REG_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e21b800, SIMD_FCVTMU_REG_VEC_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FCVTMU (vector) Vector'
      case 0x2e21b800: packet->A64InstrIndex = SIMD_FCVTMU_REG_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e216800, SIMD_FCVTN_REG: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FCVTN, FCVTN2 -'
      case 0x0e216800: packet->A64InstrIndex = SIMD_FCVTN_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e21a800, SIMD_FCVTNS_REG_VEC_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FCVTNS (vector) Vector'
      case 0x0e21a800: packet->A64InstrIndex = SIMD_FCVTNS_REG_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e21a800, SIMD_FCVTNU_REG_VEC_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FCVTNU (vector) Vector'
      case 0x2e21a800: packet->A64InstrIndex = SIMD_FCVTNU_REG_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0ea1a800, SIMD_FCVTPS_REG_VEC_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FCVTPS (vector) Vector'
      case 0x0ea1a800: packet->A64InstrIndex = SIMD_FCVTPS_REG_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2ea1a800, SIMD_FCVTPU_REG_VEC_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FCVTPU (vector) Vector'
      case 0x2ea1a800: packet->A64InstrIndex = SIMD_FCVTPU_REG_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e216800, SIMD_FCVTXN_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FCVTXN, FCVTXN2 Vector'
      case 0x2e216800: packet->A64InstrIndex = SIMD_FCVTXN_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0ea1b800, SIMD_FCVTZS_REG_VEC_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FCVTZS (vector, integer) Vector'
      case 0x0ea1b800: packet->A64InstrIndex = SIMD_FCVTZS_REG_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2ea1b800, SIMD_FCVTZU_REG_VEC_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FCVTZU (vector, integer) Vector'
      case 0x2ea1b800: packet->A64InstrIndex = SIMD_FCVTZU_REG_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2ea0f800, SIMD_FNEG_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FNEG (vector) -'
      case 0x2ea0f800: packet->A64InstrIndex = SIMD_FNEG_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0ea1d800, SIMD_FRECPE_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FRECPE Vector'
      case 0x0ea1d800: packet->A64InstrIndex = SIMD_FRECPE_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e218800, SIMD_FRINTA_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FRINTA (vector) -'
      case 0x2e218800: packet->A64InstrIndex = SIMD_FRINTA_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2ea19800, SIMD_FRINTI_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FRINTI (vector) -'
      case 0x2ea19800: packet->A64InstrIndex = SIMD_FRINTI_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e219800, SIMD_FRINTM_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FRINTM (vector) -'
      case 0x0e219800: packet->A64InstrIndex = SIMD_FRINTM_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e218800, SIMD_FRINTN_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FRINTN (vector) -'
      case 0x0e218800: packet->A64InstrIndex = SIMD_FRINTN_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0ea18800, SIMD_FRINTP_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FRINTP (vector) -'
      case 0x0ea18800: packet->A64InstrIndex = SIMD_FRINTP_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e219800, SIMD_FRINTX_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FRINTX (vector) -'
      case 0x2e219800: packet->A64InstrIndex = SIMD_FRINTX_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0ea19800, SIMD_FRINTZ_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FRINTZ (vector) -'
      case 0x0ea19800: packet->A64InstrIndex = SIMD_FRINTZ_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2ea1d800, SIMD_FRSQRTE_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FRSQRTE Vector'
      case 0x2ea1d800: packet->A64InstrIndex = SIMD_FRSQRTE_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2ea1f800, SIMD_FSQRT_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/FSQRT (vector) -'
      case 0x2ea1f800: packet->A64InstrIndex = SIMD_FSQRT_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e21d800, SIMD_SCVTF_REG_VEC_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/SCVTF (vector, integer) Vector'
      case 0x0e21d800: packet->A64InstrIndex = SIMD_SCVTF_REG_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e21d800, SIMD_UCVTF_REG_VEC_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/UCVTF (vector, integer) Vector'
      case 0x2e21d800: packet->A64InstrIndex = SIMD_UCVTF_REG_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0ea1c800, SIMD_URECPE_REG: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/URECPE -'
      case 0x0ea1c800: packet->A64InstrIndex = SIMD_URECPE_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2ea1c800, SIMD_URSQRTE_REG: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/URSQRTE -'
      case 0x2ea1c800: packet->A64InstrIndex = SIMD_URSQRTE_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbfffe400) {
      // 0x0ddf4000, SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_16: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 16-bit, immediate offset'
      case 0x0ddf4000: packet->A64InstrIndex = SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dff4000, SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_16: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 16-bit, immediate offset'
      case 0x0dff4000: packet->A64InstrIndex = SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0ddf6000, SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_16: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 16-bit, immediate offset'
      case 0x0ddf6000: packet->A64InstrIndex = SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dff6000, SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_16: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 16-bit, immediate offset'
      case 0x0dff6000: packet->A64InstrIndex = SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d9f4000, SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_16: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 16-bit, immediate offset'
      case 0x0d9f4000: packet->A64InstrIndex = SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dbf4000, SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_16: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 16-bit, immediate offset'
      case 0x0dbf4000: packet->A64InstrIndex = SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d9f6000, SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_16: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 16-bit, immediate offset'
      case 0x0d9f6000: packet->A64InstrIndex = SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dbf6000, SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_16: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 16-bit, immediate offset'
      case 0x0dbf6000: packet->A64InstrIndex = SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d404000, SIMD_LD1_SINGLE_STRUCT_16: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD1 (single structure) 16-bit'
      case 0x0d404000: packet->A64InstrIndex = SIMD_LD1_SINGLE_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d604000, SIMD_LD2_SINGLE_STRUCT_16: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD2 (single structure) 16-bit'
      case 0x0d604000: packet->A64InstrIndex = SIMD_LD2_SINGLE_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d406000, SIMD_LD3_SINGLE_STRUCT_16: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD3 (single structure) 16-bit'
      case 0x0d406000: packet->A64InstrIndex = SIMD_LD3_SINGLE_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d606000, SIMD_LD4_SINGLE_STRUCT_16: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD4 (single structure) 16-bit'
      case 0x0d606000: packet->A64InstrIndex = SIMD_LD4_SINGLE_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d004000, SIMD_ST1_SINGLE_STRUCT_16: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/ST1 (single structure) 16-bit'
      case 0x0d004000: packet->A64InstrIndex = SIMD_ST1_SINGLE_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d204000, SIMD_ST2_SINGLE_STRUCT_16: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/ST2 (single structure) 16-bit'
      case 0x0d204000: packet->A64InstrIndex = SIMD_ST2_SINGLE_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d006000, SIMD_ST3_SINGLE_STRUCT_16: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/ST3 (single structure) 16-bit'
      case 0x0d006000: packet->A64InstrIndex = SIMD_ST3_SINGLE_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d206000, SIMD_ST4_SINGLE_STRUCT_16: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/ST4 (single structure) 16-bit'
      case 0x0d206000: packet->A64InstrIndex = SIMD_ST4_SINGLE_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbf3ffc00) {
      // 0x0e31b800, SIMD_ADDV: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD across lanes/ADDV -'
      case 0x0e31b800: packet->A64InstrIndex = SIMD_ADDV;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e303800, SIMD_SADDLV: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD across lanes/SADDLV -'
      case 0x0e303800: packet->A64InstrIndex = SIMD_SADDLV;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e30a800, SIMD_SMAXV: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD across lanes/SMAXV -'
      case 0x0e30a800: packet->A64InstrIndex = SIMD_SMAXV;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e31a800, SIMD_SMINV: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD across lanes/SMINV -'
      case 0x0e31a800: packet->A64InstrIndex = SIMD_SMINV;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e303800, SIMD_UADDLV: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD across lanes/UADDLV -'
      case 0x2e303800: packet->A64InstrIndex = SIMD_UADDLV;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e30a800, SIMD_UMAXV: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD across lanes/UMAXV -'
      case 0x2e30a800: packet->A64InstrIndex = SIMD_UMAXV;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e31a800, SIMD_UMINV: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD across lanes/UMINV -'
      case 0x2e31a800: packet->A64InstrIndex = SIMD_UMINV;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e20b800, SIMD_ABS_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/ABS Vector'
      case 0x0e20b800: packet->A64InstrIndex = SIMD_ABS_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e204800, SIMD_CLS_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/CLS (vector) -'
      case 0x0e204800: packet->A64InstrIndex = SIMD_CLS_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e204800, SIMD_CLZ_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/CLZ (vector) -'
      case 0x2e204800: packet->A64InstrIndex = SIMD_CLZ_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e209800, SIMD_CMEQ_REG_VEC_ZERO: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/CMEQ (zero) Vector'
      case 0x0e209800: packet->A64InstrIndex = SIMD_CMEQ_REG_VEC_ZERO;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e208800, SIMD_CMGE_REG_VEC_ZERO: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/CMGE (zero) Vector'
      case 0x2e208800: packet->A64InstrIndex = SIMD_CMGE_REG_VEC_ZERO;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e208800, SIMD_CMGT_REG_VEC_ZERO: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/CMGT (zero) Vector'
      case 0x0e208800: packet->A64InstrIndex = SIMD_CMGT_REG_VEC_ZERO;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e209800, SIMD_CMLE_REG_VEC_ZERO: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/CMLE (zero) Vector'
      case 0x2e209800: packet->A64InstrIndex = SIMD_CMLE_REG_VEC_ZERO;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e20a800, SIMD_CMLT_REG_VEC_ZERO: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/CMLT (zero) Vector'
      case 0x0e20a800: packet->A64InstrIndex = SIMD_CMLT_REG_VEC_ZERO;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e205800, SIMD_CNT_REG: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/CNT -'
      case 0x0e205800: packet->A64InstrIndex = SIMD_CNT_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e20b800, SIMD_NEG_REG_VEC_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/NEG (vector) Vector'
      case 0x2e20b800: packet->A64InstrIndex = SIMD_NEG_REG_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e201800, SIMD_REV16_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/REV16 (vector) -'
      case 0x0e201800: packet->A64InstrIndex = SIMD_REV16_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e200800, SIMD_REV32_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/REV32 (vector) -'
      case 0x2e200800: packet->A64InstrIndex = SIMD_REV32_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e200800, SIMD_REV64_REG: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/REV64 -'
      case 0x0e200800: packet->A64InstrIndex = SIMD_REV64_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e206800, SIMD_SADALP_REG: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/SADALP -'
      case 0x0e206800: packet->A64InstrIndex = SIMD_SADALP_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e202800, SIMD_SADDLP_REG: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/SADDLP -'
      case 0x0e202800: packet->A64InstrIndex = SIMD_SADDLP_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e213800, SIMD_SHLL_REG: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/SHLL, SHLL2 -'
      case 0x2e213800: packet->A64InstrIndex = SIMD_SHLL_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e207800, SIMD_SQABS_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/SQABS Vector'
      case 0x0e207800: packet->A64InstrIndex = SIMD_SQABS_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e207800, SIMD_SQNEG_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/SQNEG Vector'
      case 0x2e207800: packet->A64InstrIndex = SIMD_SQNEG_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e214800, SIMD_SQXTN_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/SQXTN, SQXTN2 Vector'
      case 0x0e214800: packet->A64InstrIndex = SIMD_SQXTN_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e212800, SIMD_SQXTUN_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/SQXTUN, SQXTUN2 Vector'
      case 0x2e212800: packet->A64InstrIndex = SIMD_SQXTUN_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e203800, SIMD_SUQADD_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/SUQADD Vector'
      case 0x0e203800: packet->A64InstrIndex = SIMD_SUQADD_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e206800, SIMD_UADALP_REG: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/UADALP -'
      case 0x2e206800: packet->A64InstrIndex = SIMD_UADALP_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e202800, SIMD_UADDLP_REG: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/UADDLP -'
      case 0x2e202800: packet->A64InstrIndex = SIMD_UADDLP_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e214800, SIMD_UQXTN_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/UQXTN, UQXTN2 Vector'
      case 0x2e214800: packet->A64InstrIndex = SIMD_UQXTN_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e203800, SIMD_USQADD_REG_VEC: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/USQADD Vector'
      case 0x2e203800: packet->A64InstrIndex = SIMD_USQADD_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e212800, SIMD_XTN_REG: ' Q=30 U=29 size=23,22 opcode=16,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD two-register miscellaneous/XTN, XTN2 -'
      case 0x0e212800: packet->A64InstrIndex = SIMD_XTN_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->opcode = (packet->Opcode >> 12) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xfff8fc00) {
      // 0x6f00f400, SIMD_FMOV_IMM_MOD_VEC_FROM_DP: ' Q=30 op=29 a=18 b=17 c=16 cmode=15,12 o2=11 d=9 e=8 f=7 g=6 h=5 Rd=4,0' - 'Advanced SIMD modified immediate/FMOV (vector, immediate) Double-precision'
      case 0x6f00f400: packet->A64InstrIndex = SIMD_FMOV_IMM_MOD_VEC_FROM_DP;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->a = (packet->Opcode >> 18) & 0x1;
          packet->b = (packet->Opcode >> 17) & 0x1;
          packet->c = (packet->Opcode >> 16) & 0x1;
          packet->cmode = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 11) & 0x1;
          packet->d = (packet->Opcode >> 9) & 0x1;
          packet->e = (packet->Opcode >> 8) & 0x1;
          packet->f = (packet->Opcode >> 7) & 0x1;
          packet->g = (packet->Opcode >> 6) & 0x1;
          packet->h = (packet->Opcode >> 5) & 0x1;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f00e400, SIMD_MOVI_IMM_MOD_64: ' Q=30 op=29 a=18 b=17 c=16 cmode=15,12 o2=11 d=9 e=8 f=7 g=6 h=5 Rd=4,0' - 'Advanced SIMD modified immediate/MOVI 64-bit scalar'
      case 0x2f00e400: packet->A64InstrIndex = SIMD_MOVI_IMM_MOD_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->a = (packet->Opcode >> 18) & 0x1;
          packet->b = (packet->Opcode >> 17) & 0x1;
          packet->c = (packet->Opcode >> 16) & 0x1;
          packet->cmode = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 11) & 0x1;
          packet->d = (packet->Opcode >> 9) & 0x1;
          packet->e = (packet->Opcode >> 8) & 0x1;
          packet->f = (packet->Opcode >> 7) & 0x1;
          packet->g = (packet->Opcode >> 6) & 0x1;
          packet->h = (packet->Opcode >> 5) & 0x1;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x6f00e400, SIMD_MOVI_IMM_MOD_VEC_64: ' Q=30 op=29 a=18 b=17 c=16 cmode=15,12 o2=11 d=9 e=8 f=7 g=6 h=5 Rd=4,0' - 'Advanced SIMD modified immediate/MOVI 64-bit vector'
      case 0x6f00e400: packet->A64InstrIndex = SIMD_MOVI_IMM_MOD_VEC_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->a = (packet->Opcode >> 18) & 0x1;
          packet->b = (packet->Opcode >> 17) & 0x1;
          packet->c = (packet->Opcode >> 16) & 0x1;
          packet->cmode = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 11) & 0x1;
          packet->d = (packet->Opcode >> 9) & 0x1;
          packet->e = (packet->Opcode >> 8) & 0x1;
          packet->f = (packet->Opcode >> 7) & 0x1;
          packet->g = (packet->Opcode >> 6) & 0x1;
          packet->h = (packet->Opcode >> 5) & 0x1;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbffff000) {
      // 0x0cdf2000, SIMD_LD1_IMM_FOUR_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) Four registers, immediate offset'
      case 0x0cdf2000: packet->A64InstrIndex = SIMD_LD1_IMM_FOUR_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0cdf7000, SIMD_LD1_IMM_ONE_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) One register, immediate offset'
      case 0x0cdf7000: packet->A64InstrIndex = SIMD_LD1_IMM_ONE_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0cdf6000, SIMD_LD1_IMM_THREE_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) Three registers, immediate offset'
      case 0x0cdf6000: packet->A64InstrIndex = SIMD_LD1_IMM_THREE_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0cdfa000, SIMD_LD1_IMM_TWO_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) Two registers, immediate offset'
      case 0x0cdfa000: packet->A64InstrIndex = SIMD_LD1_IMM_TWO_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0cdf8000, SIMD_LD2_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/LD2 (multiple structures) Immediate offset'
      case 0x0cdf8000: packet->A64InstrIndex = SIMD_LD2_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0cdf4000, SIMD_LD3_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/LD3 (multiple structures) Immediate offset'
      case 0x0cdf4000: packet->A64InstrIndex = SIMD_LD3_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0cdf0000, SIMD_LD4_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/LD4 (multiple structures) Immediate offset'
      case 0x0cdf0000: packet->A64InstrIndex = SIMD_LD4_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c9f2000, SIMD_ST1_IMM_FOUR_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) Four registers, immediate offset'
      case 0x0c9f2000: packet->A64InstrIndex = SIMD_ST1_IMM_FOUR_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c9f7000, SIMD_ST1_IMM_ONE_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) One register, immediate offset'
      case 0x0c9f7000: packet->A64InstrIndex = SIMD_ST1_IMM_ONE_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c9f6000, SIMD_ST1_IMM_THREE_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) Three registers, immediate offset'
      case 0x0c9f6000: packet->A64InstrIndex = SIMD_ST1_IMM_THREE_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c9fa000, SIMD_ST1_IMM_TWO_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) Two registers, immediate offset'
      case 0x0c9fa000: packet->A64InstrIndex = SIMD_ST1_IMM_TWO_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c9f8000, SIMD_ST2_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/ST2 (multiple structures) Immediate offset'
      case 0x0c9f8000: packet->A64InstrIndex = SIMD_ST2_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c9f4000, SIMD_ST3_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/ST3 (multiple structures) Immediate offset'
      case 0x0c9f4000: packet->A64InstrIndex = SIMD_ST3_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c9f0000, SIMD_ST4_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/ST4 (multiple structures) Immediate offset'
      case 0x0c9f0000: packet->A64InstrIndex = SIMD_ST4_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c402000, SIMD_LD1_FOUR_REG_MULT_STRUCT: ' Q=30 L=22 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures/LD1 (multiple structures) Four registers'
      case 0x0c402000: packet->A64InstrIndex = SIMD_LD1_FOUR_REG_MULT_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c407000, SIMD_LD1_ONE_REG_MULT_STRUCT: ' Q=30 L=22 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures/LD1 (multiple structures) One register'
      case 0x0c407000: packet->A64InstrIndex = SIMD_LD1_ONE_REG_MULT_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c406000, SIMD_LD1_THREE_REG_MULT_STRUCT: ' Q=30 L=22 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures/LD1 (multiple structures) Three registers'
      case 0x0c406000: packet->A64InstrIndex = SIMD_LD1_THREE_REG_MULT_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c40a000, SIMD_LD1_TWO_REG_MULT_STRUCT: ' Q=30 L=22 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures/LD1 (multiple structures) Two registers'
      case 0x0c40a000: packet->A64InstrIndex = SIMD_LD1_TWO_REG_MULT_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c408000, SIMD_LD2_OFF_MULT_STRUCT: ' Q=30 L=22 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures/LD2 (multiple structures) No offset'
      case 0x0c408000: packet->A64InstrIndex = SIMD_LD2_OFF_MULT_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c404000, SIMD_LD3_OFF_MULT_STRUCT: ' Q=30 L=22 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures/LD3 (multiple structures) No offset'
      case 0x0c404000: packet->A64InstrIndex = SIMD_LD3_OFF_MULT_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c400000, SIMD_LD4_OFF_MULT_STRUCT: ' Q=30 L=22 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures/LD4 (multiple structures) No offset'
      case 0x0c400000: packet->A64InstrIndex = SIMD_LD4_OFF_MULT_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c002000, SIMD_ST1_FOUR_REG_MULT_STRUCT: ' Q=30 L=22 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures/ST1 (multiple structures) Four registers'
      case 0x0c002000: packet->A64InstrIndex = SIMD_ST1_FOUR_REG_MULT_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c007000, SIMD_ST1_ONE_REG_MULT_STRUCT: ' Q=30 L=22 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures/ST1 (multiple structures) One register'
      case 0x0c007000: packet->A64InstrIndex = SIMD_ST1_ONE_REG_MULT_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c006000, SIMD_ST1_THREE_REG_MULT_STRUCT: ' Q=30 L=22 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures/ST1 (multiple structures) Three registers'
      case 0x0c006000: packet->A64InstrIndex = SIMD_ST1_THREE_REG_MULT_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c00a000, SIMD_ST1_TWO_REG_MULT_STRUCT: ' Q=30 L=22 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures/ST1 (multiple structures) Two registers'
      case 0x0c00a000: packet->A64InstrIndex = SIMD_ST1_TWO_REG_MULT_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c008000, SIMD_ST2_OFF_MULT_STRUCT: ' Q=30 L=22 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures/ST2 (multiple structures) No offset'
      case 0x0c008000: packet->A64InstrIndex = SIMD_ST2_OFF_MULT_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c004000, SIMD_ST3_OFF_MULT_STRUCT: ' Q=30 L=22 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures/ST3 (multiple structures) No offset'
      case 0x0c004000: packet->A64InstrIndex = SIMD_ST3_OFF_MULT_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c000000, SIMD_ST4_OFF_MULT_STRUCT: ' Q=30 L=22 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures/ST4 (multiple structures) No offset'
      case 0x0c000000: packet->A64InstrIndex = SIMD_ST4_OFF_MULT_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0ddfc000, SIMD_LD1R_OFF_SINGLE_POST_STRUCT: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD1R Immediate offset'
      case 0x0ddfc000: packet->A64InstrIndex = SIMD_LD1R_OFF_SINGLE_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dffc000, SIMD_LD2R_OFF_SINGLE_POST_STRUCT: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD2R Immediate offset'
      case 0x0dffc000: packet->A64InstrIndex = SIMD_LD2R_OFF_SINGLE_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0ddfe000, SIMD_LD3R_OFF_SINGLE_POST_STRUCT: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD3R Immediate offset'
      case 0x0ddfe000: packet->A64InstrIndex = SIMD_LD3R_OFF_SINGLE_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dffe000, SIMD_LD4R_OFF_SINGLE_POST_STRUCT: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD4R Immediate offset'
      case 0x0dffe000: packet->A64InstrIndex = SIMD_LD4R_OFF_SINGLE_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d40c000, SIMD_LD1R_OFF_SINGLE_STRUCT: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD1R No offset'
      case 0x0d40c000: packet->A64InstrIndex = SIMD_LD1R_OFF_SINGLE_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d60c000, SIMD_LD2R_OFF_SINGLE_STRUCT: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD2R No offset'
      case 0x0d60c000: packet->A64InstrIndex = SIMD_LD2R_OFF_SINGLE_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d40e000, SIMD_LD3R_OFF_SINGLE_STRUCT: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD3R No offset'
      case 0x0d40e000: packet->A64InstrIndex = SIMD_LD3R_OFF_SINGLE_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d60e000, SIMD_LD4R_OFF_SINGLE_STRUCT: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD4R No offset'
      case 0x0d60e000: packet->A64InstrIndex = SIMD_LD4R_OFF_SINGLE_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xffe01fe0) {
      // 0x1e601000, FMOV_IMM_FROM_DP: ' M=31 S=29 type=23,22 imm8=20,13 imm5=9,5 Rd=4,0' - 'Floating-point immediate/FMOV (scalar, immediate) Double-precision'
      case 0x1e601000: packet->A64InstrIndex = FMOV_IMM_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->imm8 = (packet->Opcode >> 13) & 0xff;
          packet->imm5 = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e201000, FMOV_IMM_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 imm8=20,13 imm5=9,5 Rd=4,0' - 'Floating-point immediate/FMOV (scalar, immediate) Single-precision'
      case 0x1e201000: packet->A64InstrIndex = FMOV_IMM_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->imm8 = (packet->Opcode >> 13) & 0xff;
          packet->imm5 = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbff8fc00) {
      // 0x0f00f400, SIMD_FMOV_IMM_MOD_SINGLE_VEC_FROM_SP: ' Q=30 op=29 a=18 b=17 c=16 cmode=15,12 o2=11 d=9 e=8 f=7 g=6 h=5 Rd=4,0' - 'Advanced SIMD modified immediate/FMOV (vector, immediate) Single-precision'
      case 0x0f00f400: packet->A64InstrIndex = SIMD_FMOV_IMM_MOD_SINGLE_VEC_FROM_SP;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->a = (packet->Opcode >> 18) & 0x1;
          packet->b = (packet->Opcode >> 17) & 0x1;
          packet->c = (packet->Opcode >> 16) & 0x1;
          packet->cmode = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 11) & 0x1;
          packet->d = (packet->Opcode >> 9) & 0x1;
          packet->e = (packet->Opcode >> 8) & 0x1;
          packet->f = (packet->Opcode >> 7) & 0x1;
          packet->g = (packet->Opcode >> 6) & 0x1;
          packet->h = (packet->Opcode >> 5) & 0x1;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f00e400, SIMD_MOVI_IMM_MOD_8: ' Q=30 op=29 a=18 b=17 c=16 cmode=15,12 o2=11 d=9 e=8 f=7 g=6 h=5 Rd=4,0' - 'Advanced SIMD modified immediate/MOVI 8-bit'
      case 0x0f00e400: packet->A64InstrIndex = SIMD_MOVI_IMM_MOD_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->a = (packet->Opcode >> 18) & 0x1;
          packet->b = (packet->Opcode >> 17) & 0x1;
          packet->c = (packet->Opcode >> 16) & 0x1;
          packet->cmode = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 11) & 0x1;
          packet->d = (packet->Opcode >> 9) & 0x1;
          packet->e = (packet->Opcode >> 8) & 0x1;
          packet->f = (packet->Opcode >> 7) & 0x1;
          packet->g = (packet->Opcode >> 6) & 0x1;
          packet->h = (packet->Opcode >> 5) & 0x1;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbfffe000) {
      // 0x0ddf0000, SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_8: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 8-bit, immediate offset'
      case 0x0ddf0000: packet->A64InstrIndex = SIMD_LD1_IMM_OFF_SINGLE_POST_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dff0000, SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_8: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 8-bit, immediate offset'
      case 0x0dff0000: packet->A64InstrIndex = SIMD_LD2_IMM_OFF_SINGLE_POST_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0ddf2000, SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_8: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 8-bit, immediate offset'
      case 0x0ddf2000: packet->A64InstrIndex = SIMD_LD3_IMM_OFF_SINGLE_POST_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dff2000, SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_8: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 8-bit, immediate offset'
      case 0x0dff2000: packet->A64InstrIndex = SIMD_LD4_IMM_OFF_SINGLE_POST_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d9f0000, SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_8: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 8-bit, immediate offset'
      case 0x0d9f0000: packet->A64InstrIndex = SIMD_ST1_IMM_OFF_SINGLE_POST_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dbf0000, SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_8: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 8-bit, immediate offset'
      case 0x0dbf0000: packet->A64InstrIndex = SIMD_ST2_IMM_OFF_SINGLE_POST_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d9f2000, SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_8: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 8-bit, immediate offset'
      case 0x0d9f2000: packet->A64InstrIndex = SIMD_ST3_IMM_OFF_SINGLE_POST_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dbf2000, SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_8: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 8-bit, immediate offset'
      case 0x0dbf2000: packet->A64InstrIndex = SIMD_ST4_IMM_OFF_SINGLE_POST_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d400000, SIMD_LD1_SINGLE_STRUCT_8: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD1 (single structure) 8-bit'
      case 0x0d400000: packet->A64InstrIndex = SIMD_LD1_SINGLE_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d600000, SIMD_LD2_SINGLE_STRUCT_8: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD2 (single structure) 8-bit'
      case 0x0d600000: packet->A64InstrIndex = SIMD_LD2_SINGLE_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d402000, SIMD_LD3_SINGLE_STRUCT_8: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD3 (single structure) 8-bit'
      case 0x0d402000: packet->A64InstrIndex = SIMD_LD3_SINGLE_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d602000, SIMD_LD4_SINGLE_STRUCT_8: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/LD4 (single structure) 8-bit'
      case 0x0d602000: packet->A64InstrIndex = SIMD_LD4_SINGLE_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d000000, SIMD_ST1_SINGLE_STRUCT_8: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/ST1 (single structure) 8-bit'
      case 0x0d000000: packet->A64InstrIndex = SIMD_ST1_SINGLE_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d200000, SIMD_ST2_SINGLE_STRUCT_8: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/ST2 (single structure) 8-bit'
      case 0x0d200000: packet->A64InstrIndex = SIMD_ST2_SINGLE_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d002000, SIMD_ST3_SINGLE_STRUCT_8: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/ST3 (single structure) 8-bit'
      case 0x0d002000: packet->A64InstrIndex = SIMD_ST3_SINGLE_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d202000, SIMD_ST4_SINGLE_STRUCT_8: ' Q=30 L=22 R=21 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure/ST4 (single structure) 8-bit'
      case 0x0d202000: packet->A64InstrIndex = SIMD_ST4_SINGLE_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbff8ec00) {
      // 0x0f00c400, SIMD_MOVI_SHIFT_IMM_ONES_MOD_32: ' Q=30 op=29 a=18 b=17 c=16 cmode=15,12 o2=11 d=9 e=8 f=7 g=6 h=5 Rd=4,0' - 'Advanced SIMD modified immediate/MOVI 32-bit shifting ones'
      case 0x0f00c400: packet->A64InstrIndex = SIMD_MOVI_SHIFT_IMM_ONES_MOD_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->a = (packet->Opcode >> 18) & 0x1;
          packet->b = (packet->Opcode >> 17) & 0x1;
          packet->c = (packet->Opcode >> 16) & 0x1;
          packet->cmode = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 11) & 0x1;
          packet->d = (packet->Opcode >> 9) & 0x1;
          packet->e = (packet->Opcode >> 8) & 0x1;
          packet->f = (packet->Opcode >> 7) & 0x1;
          packet->g = (packet->Opcode >> 6) & 0x1;
          packet->h = (packet->Opcode >> 5) & 0x1;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f00c400, SIMD_MVNI_SHIFT_IMM_ONES_MOD_32: ' Q=30 op=29 a=18 b=17 c=16 cmode=15,12 o2=11 d=9 e=8 f=7 g=6 h=5 Rd=4,0' - 'Advanced SIMD modified immediate/MVNI 32-bit shifting ones'
      case 0x2f00c400: packet->A64InstrIndex = SIMD_MVNI_SHIFT_IMM_ONES_MOD_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->a = (packet->Opcode >> 18) & 0x1;
          packet->b = (packet->Opcode >> 17) & 0x1;
          packet->c = (packet->Opcode >> 16) & 0x1;
          packet->cmode = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 11) & 0x1;
          packet->d = (packet->Opcode >> 9) & 0x1;
          packet->e = (packet->Opcode >> 8) & 0x1;
          packet->f = (packet->Opcode >> 7) & 0x1;
          packet->g = (packet->Opcode >> 6) & 0x1;
          packet->h = (packet->Opcode >> 5) & 0x1;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbff8dc00) {
      // 0x2f009400, SIMD_BIC_IMM_MOD_VEC_16: ' Q=30 op=29 a=18 b=17 c=16 cmode=15,12 o2=11 d=9 e=8 f=7 g=6 h=5 Rd=4,0' - 'Advanced SIMD modified immediate/BIC (vector, immediate) 16-bit'
      case 0x2f009400: packet->A64InstrIndex = SIMD_BIC_IMM_MOD_VEC_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->a = (packet->Opcode >> 18) & 0x1;
          packet->b = (packet->Opcode >> 17) & 0x1;
          packet->c = (packet->Opcode >> 16) & 0x1;
          packet->cmode = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 11) & 0x1;
          packet->d = (packet->Opcode >> 9) & 0x1;
          packet->e = (packet->Opcode >> 8) & 0x1;
          packet->f = (packet->Opcode >> 7) & 0x1;
          packet->g = (packet->Opcode >> 6) & 0x1;
          packet->h = (packet->Opcode >> 5) & 0x1;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f008400, SIMD_MOVI_SHIFT_IMM_MOD_16: ' Q=30 op=29 a=18 b=17 c=16 cmode=15,12 o2=11 d=9 e=8 f=7 g=6 h=5 Rd=4,0' - 'Advanced SIMD modified immediate/MOVI 16-bit shifted immediate'
      case 0x0f008400: packet->A64InstrIndex = SIMD_MOVI_SHIFT_IMM_MOD_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->a = (packet->Opcode >> 18) & 0x1;
          packet->b = (packet->Opcode >> 17) & 0x1;
          packet->c = (packet->Opcode >> 16) & 0x1;
          packet->cmode = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 11) & 0x1;
          packet->d = (packet->Opcode >> 9) & 0x1;
          packet->e = (packet->Opcode >> 8) & 0x1;
          packet->f = (packet->Opcode >> 7) & 0x1;
          packet->g = (packet->Opcode >> 6) & 0x1;
          packet->h = (packet->Opcode >> 5) & 0x1;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f008400, SIMD_MVNI_SHIFT_IMM_MOD_16: ' Q=30 op=29 a=18 b=17 c=16 cmode=15,12 o2=11 d=9 e=8 f=7 g=6 h=5 Rd=4,0' - 'Advanced SIMD modified immediate/MVNI 16-bit shifted immediate'
      case 0x2f008400: packet->A64InstrIndex = SIMD_MVNI_SHIFT_IMM_MOD_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->a = (packet->Opcode >> 18) & 0x1;
          packet->b = (packet->Opcode >> 17) & 0x1;
          packet->c = (packet->Opcode >> 16) & 0x1;
          packet->cmode = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 11) & 0x1;
          packet->d = (packet->Opcode >> 9) & 0x1;
          packet->e = (packet->Opcode >> 8) & 0x1;
          packet->f = (packet->Opcode >> 7) & 0x1;
          packet->g = (packet->Opcode >> 6) & 0x1;
          packet->h = (packet->Opcode >> 5) & 0x1;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f009400, SIMD_ORR_IMM_MOD_VEC_16: ' Q=30 op=29 a=18 b=17 c=16 cmode=15,12 o2=11 d=9 e=8 f=7 g=6 h=5 Rd=4,0' - 'Advanced SIMD modified immediate/ORR (vector, immediate) 16-bit'
      case 0x0f009400: packet->A64InstrIndex = SIMD_ORR_IMM_MOD_VEC_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->a = (packet->Opcode >> 18) & 0x1;
          packet->b = (packet->Opcode >> 17) & 0x1;
          packet->c = (packet->Opcode >> 16) & 0x1;
          packet->cmode = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 11) & 0x1;
          packet->d = (packet->Opcode >> 9) & 0x1;
          packet->e = (packet->Opcode >> 8) & 0x1;
          packet->f = (packet->Opcode >> 7) & 0x1;
          packet->g = (packet->Opcode >> 6) & 0x1;
          packet->h = (packet->Opcode >> 5) & 0x1;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xffe0fc00) {
      // 0x1a000000, ADC_32: ' sf=31 op=30 S=29 Rm=20,16 opcode2=15,10 Rn=9,5 Rd=4,0' - 'Add/subtract (with carry)/ADC 32-bit'
      case 0x1a000000: packet->A64InstrIndex = ADC_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode2 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9a000000, ADC_64: ' sf=31 op=30 S=29 Rm=20,16 opcode2=15,10 Rn=9,5 Rd=4,0' - 'Add/subtract (with carry)/ADC 64-bit'
      case 0x9a000000: packet->A64InstrIndex = ADC_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode2 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x3a000000, ADCS_32: ' sf=31 op=30 S=29 Rm=20,16 opcode2=15,10 Rn=9,5 Rd=4,0' - 'Add/subtract (with carry)/ADCS 32-bit'
      case 0x3a000000: packet->A64InstrIndex = ADCS_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode2 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xba000000, ADCS_64: ' sf=31 op=30 S=29 Rm=20,16 opcode2=15,10 Rn=9,5 Rd=4,0' - 'Add/subtract (with carry)/ADCS 64-bit'
      case 0xba000000: packet->A64InstrIndex = ADCS_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode2 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5a000000, SBC_32: ' sf=31 op=30 S=29 Rm=20,16 opcode2=15,10 Rn=9,5 Rd=4,0' - 'Add/subtract (with carry)/SBC 32-bit'
      case 0x5a000000: packet->A64InstrIndex = SBC_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode2 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xda000000, SBC_64: ' sf=31 op=30 S=29 Rm=20,16 opcode2=15,10 Rn=9,5 Rd=4,0' - 'Add/subtract (with carry)/SBC 64-bit'
      case 0xda000000: packet->A64InstrIndex = SBC_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode2 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7a000000, SBCS_32: ' sf=31 op=30 S=29 Rm=20,16 opcode2=15,10 Rn=9,5 Rd=4,0' - 'Add/subtract (with carry)/SBCS 32-bit'
      case 0x7a000000: packet->A64InstrIndex = SBCS_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode2 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xfa000000, SBCS_64: ' sf=31 op=30 S=29 Rm=20,16 opcode2=15,10 Rn=9,5 Rd=4,0' - 'Add/subtract (with carry)/SBCS 64-bit'
      case 0xfa000000: packet->A64InstrIndex = SBCS_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode2 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x4e001c00, SIMD_INS: ' Q=30 op=29 imm5=20,16 imm4=14,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD copy/INS (general) -'
      case 0x4e001c00: packet->A64InstrIndex = SIMD_INS;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->imm5 = (packet->Opcode >> 16) & 0x1f;
          packet->imm4 = (packet->Opcode >> 11) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e002c00, SIMD_SMOV_32: ' Q=30 op=29 imm5=20,16 imm4=14,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD copy/SMOV 32-bit'
      case 0x0e002c00: packet->A64InstrIndex = SIMD_SMOV_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->imm5 = (packet->Opcode >> 16) & 0x1f;
          packet->imm4 = (packet->Opcode >> 11) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x4e002c00, SIMD_SMOV_64: ' Q=30 op=29 imm5=20,16 imm4=14,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD copy/SMOV 64-bit'
      case 0x4e002c00: packet->A64InstrIndex = SIMD_SMOV_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->imm5 = (packet->Opcode >> 16) & 0x1f;
          packet->imm4 = (packet->Opcode >> 11) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e003c00, SIMD_UMOV_32: ' Q=30 op=29 imm5=20,16 imm4=14,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD copy/UMOV 32-bit'
      case 0x0e003c00: packet->A64InstrIndex = SIMD_UMOV_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->imm5 = (packet->Opcode >> 16) & 0x1f;
          packet->imm4 = (packet->Opcode >> 11) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x4e003c00, SIMD_UMOV_64: ' Q=30 op=29 imm5=20,16 imm4=14,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD copy/UMOV 64-bit'
      case 0x4e003c00: packet->A64InstrIndex = SIMD_UMOV_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->imm5 = (packet->Opcode >> 16) & 0x1f;
          packet->imm4 = (packet->Opcode >> 11) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e000400, SIMD_DUP_SCALAR_ELEM: ' op=29 imm5=20,16 imm4=14,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar copy/DUP (element) Scalar'
      case 0x5e000400: packet->A64InstrIndex = SIMD_DUP_SCALAR_ELEM;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->imm5 = (packet->Opcode >> 16) & 0x1f;
          packet->imm4 = (packet->Opcode >> 11) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e000000, SHA1C_REG: ' size=23,22 Rm=20,16 opcode=14,12 Rn=9,5 Rd=4,0' - 'Cryptographic three-register SHA/SHA1C -'
      case 0x5e000000: packet->A64InstrIndex = SHA1C_REG;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e002000, SHA1M_REG: ' size=23,22 Rm=20,16 opcode=14,12 Rn=9,5 Rd=4,0' - 'Cryptographic three-register SHA/SHA1M -'
      case 0x5e002000: packet->A64InstrIndex = SHA1M_REG;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e001000, SHA1P_REG: ' size=23,22 Rm=20,16 opcode=14,12 Rn=9,5 Rd=4,0' - 'Cryptographic three-register SHA/SHA1P -'
      case 0x5e001000: packet->A64InstrIndex = SHA1P_REG;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e003000, SHA1SU0_REG: ' size=23,22 Rm=20,16 opcode=14,12 Rn=9,5 Rd=4,0' - 'Cryptographic three-register SHA/SHA1SU0 -'
      case 0x5e003000: packet->A64InstrIndex = SHA1SU0_REG;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e004000, SHA256H_REG: ' size=23,22 Rm=20,16 opcode=14,12 Rn=9,5 Rd=4,0' - 'Cryptographic three-register SHA/SHA256H -'
      case 0x5e004000: packet->A64InstrIndex = SHA256H_REG;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e005000, SHA256H2_REG: ' size=23,22 Rm=20,16 opcode=14,12 Rn=9,5 Rd=4,0' - 'Cryptographic three-register SHA/SHA256H2 -'
      case 0x5e005000: packet->A64InstrIndex = SHA256H2_REG;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e006000, SHA256SU1_REG: ' size=23,22 Rm=20,16 opcode=14,12 Rn=9,5 Rd=4,0' - 'Cryptographic three-register SHA/SHA256SU1 -'
      case 0x5e006000: packet->A64InstrIndex = SHA256SU1_REG;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1ac02800, ASRV_32: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/ASRV 32-bit'
      case 0x1ac02800: packet->A64InstrIndex = ASRV_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9ac02800, ASRV_64: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/ASRV 64-bit'
      case 0x9ac02800: packet->A64InstrIndex = ASRV_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1ac04000, CRC32B: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/CRC32B'
      case 0x1ac04000: packet->A64InstrIndex = CRC32B;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1ac05000, CRC32CB: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/CRC32CB'
      case 0x1ac05000: packet->A64InstrIndex = CRC32CB;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1ac05400, CRC32CH: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/CRC32CH'
      case 0x1ac05400: packet->A64InstrIndex = CRC32CH;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1ac05800, CRC32CW: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/CRC32CW'
      case 0x1ac05800: packet->A64InstrIndex = CRC32CW;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9ac05c00, CRC32CX: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/CRC32CX'
      case 0x9ac05c00: packet->A64InstrIndex = CRC32CX;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1ac04400, CRC32H: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/CRC32H'
      case 0x1ac04400: packet->A64InstrIndex = CRC32H;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1ac04800, CRC32W: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/CRC32W'
      case 0x1ac04800: packet->A64InstrIndex = CRC32W;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9ac04c00, CRC32X: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/CRC32X'
      case 0x9ac04c00: packet->A64InstrIndex = CRC32X;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1ac02000, LSLV_32: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/LSLV 32-bit'
      case 0x1ac02000: packet->A64InstrIndex = LSLV_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9ac02000, LSLV_64: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/LSLV 64-bit'
      case 0x9ac02000: packet->A64InstrIndex = LSLV_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1ac02400, LSRV_32: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/LSRV 32-bit'
      case 0x1ac02400: packet->A64InstrIndex = LSRV_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9ac02400, LSRV_64: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/LSRV 64-bit'
      case 0x9ac02400: packet->A64InstrIndex = LSRV_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1ac02c00, RORV_32: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/RORV 32-bit'
      case 0x1ac02c00: packet->A64InstrIndex = RORV_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9ac02c00, RORV_64: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/RORV 64-bit'
      case 0x9ac02c00: packet->A64InstrIndex = RORV_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1ac00c00, SDIV_32: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/SDIV 32-bit'
      case 0x1ac00c00: packet->A64InstrIndex = SDIV_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9ac00c00, SDIV_64: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/SDIV 64-bit'
      case 0x9ac00c00: packet->A64InstrIndex = SDIV_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1ac00800, UDIV_32: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/UDIV 32-bit'
      case 0x1ac00800: packet->A64InstrIndex = UDIV_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9ac00800, UDIV_64: ' sf=31 S=29 Rm=20,16 opcode=15,10 Rn=9,5 Rd=4,0' - 'Data-processing (2 source)/UDIV 64-bit'
      case 0x9ac00800: packet->A64InstrIndex = UDIV_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e602800, FADD_FROM_DP: ' M=31 S=29 type=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (2 source)/FADD (scalar) Double-precision'
      case 0x1e602800: packet->A64InstrIndex = FADD_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e202800, FADD_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (2 source)/FADD (scalar) Single-precision'
      case 0x1e202800: packet->A64InstrIndex = FADD_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e601800, FDIV_FROM_DP: ' M=31 S=29 type=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (2 source)/FDIV (scalar) Double-precision'
      case 0x1e601800: packet->A64InstrIndex = FDIV_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e201800, FDIV_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (2 source)/FDIV (scalar) Single-precision'
      case 0x1e201800: packet->A64InstrIndex = FDIV_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e604800, FMAX_FROM_DP: ' M=31 S=29 type=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (2 source)/FMAX (scalar) Double-precision'
      case 0x1e604800: packet->A64InstrIndex = FMAX_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e204800, FMAX_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (2 source)/FMAX (scalar) Single-precision'
      case 0x1e204800: packet->A64InstrIndex = FMAX_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e606800, FMAXNM_FROM_DP: ' M=31 S=29 type=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (2 source)/FMAXNM (scalar) Double-precision'
      case 0x1e606800: packet->A64InstrIndex = FMAXNM_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e206800, FMAXNM_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (2 source)/FMAXNM (scalar) Single-precision'
      case 0x1e206800: packet->A64InstrIndex = FMAXNM_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e605800, FMIN_FROM_DP: ' M=31 S=29 type=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (2 source)/FMIN (scalar) Double-precision'
      case 0x1e605800: packet->A64InstrIndex = FMIN_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e205800, FMIN_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (2 source)/FMIN (scalar) Single-precision'
      case 0x1e205800: packet->A64InstrIndex = FMIN_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e607800, FMINNM_FROM_DP: ' M=31 S=29 type=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (2 source)/FMINNM (scalar) Double-precision'
      case 0x1e607800: packet->A64InstrIndex = FMINNM_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e207800, FMINNM_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (2 source)/FMINNM (scalar) Single-precision'
      case 0x1e207800: packet->A64InstrIndex = FMINNM_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e600800, FMUL_FROM_DP: ' M=31 S=29 type=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (2 source)/FMUL (scalar) Double-precision'
      case 0x1e600800: packet->A64InstrIndex = FMUL_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e200800, FMUL_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (2 source)/FMUL (scalar) Single-precision'
      case 0x1e200800: packet->A64InstrIndex = FMUL_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e608800, FNMUL_FROM_DP: ' M=31 S=29 type=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (2 source)/FNMUL Double-precision'
      case 0x1e608800: packet->A64InstrIndex = FNMUL_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e208800, FNMUL_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (2 source)/FNMUL Single-precision'
      case 0x1e208800: packet->A64InstrIndex = FNMUL_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e603800, FSUB_FROM_DP: ' M=31 S=29 type=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (2 source)/FSUB (scalar) Double-precision'
      case 0x1e603800: packet->A64InstrIndex = FSUB_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e203800, FSUB_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (2 source)/FSUB (scalar) Single-precision'
      case 0x1e203800: packet->A64InstrIndex = FSUB_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbff89c00) {
      // 0x2f001400, SIMD_BIC_IMM_MOD_VEC_32: ' Q=30 op=29 a=18 b=17 c=16 cmode=15,12 o2=11 d=9 e=8 f=7 g=6 h=5 Rd=4,0' - 'Advanced SIMD modified immediate/BIC (vector, immediate) 32-bit'
      case 0x2f001400: packet->A64InstrIndex = SIMD_BIC_IMM_MOD_VEC_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->a = (packet->Opcode >> 18) & 0x1;
          packet->b = (packet->Opcode >> 17) & 0x1;
          packet->c = (packet->Opcode >> 16) & 0x1;
          packet->cmode = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 11) & 0x1;
          packet->d = (packet->Opcode >> 9) & 0x1;
          packet->e = (packet->Opcode >> 8) & 0x1;
          packet->f = (packet->Opcode >> 7) & 0x1;
          packet->g = (packet->Opcode >> 6) & 0x1;
          packet->h = (packet->Opcode >> 5) & 0x1;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f000400, SIMD_MOVI_SHIFT_IMM_MOD_32: ' Q=30 op=29 a=18 b=17 c=16 cmode=15,12 o2=11 d=9 e=8 f=7 g=6 h=5 Rd=4,0' - 'Advanced SIMD modified immediate/MOVI 32-bit shifted immediate'
      case 0x0f000400: packet->A64InstrIndex = SIMD_MOVI_SHIFT_IMM_MOD_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->a = (packet->Opcode >> 18) & 0x1;
          packet->b = (packet->Opcode >> 17) & 0x1;
          packet->c = (packet->Opcode >> 16) & 0x1;
          packet->cmode = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 11) & 0x1;
          packet->d = (packet->Opcode >> 9) & 0x1;
          packet->e = (packet->Opcode >> 8) & 0x1;
          packet->f = (packet->Opcode >> 7) & 0x1;
          packet->g = (packet->Opcode >> 6) & 0x1;
          packet->h = (packet->Opcode >> 5) & 0x1;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f000400, SIMD_MVNI_SHIFT_IMM_MOD_32: ' Q=30 op=29 a=18 b=17 c=16 cmode=15,12 o2=11 d=9 e=8 f=7 g=6 h=5 Rd=4,0' - 'Advanced SIMD modified immediate/MVNI 32-bit shifted immediate'
      case 0x2f000400: packet->A64InstrIndex = SIMD_MVNI_SHIFT_IMM_MOD_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->a = (packet->Opcode >> 18) & 0x1;
          packet->b = (packet->Opcode >> 17) & 0x1;
          packet->c = (packet->Opcode >> 16) & 0x1;
          packet->cmode = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 11) & 0x1;
          packet->d = (packet->Opcode >> 9) & 0x1;
          packet->e = (packet->Opcode >> 8) & 0x1;
          packet->f = (packet->Opcode >> 7) & 0x1;
          packet->g = (packet->Opcode >> 6) & 0x1;
          packet->h = (packet->Opcode >> 5) & 0x1;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f001400, SIMD_ORR_IMM_MOD_VEC_32: ' Q=30 op=29 a=18 b=17 c=16 cmode=15,12 o2=11 d=9 e=8 f=7 g=6 h=5 Rd=4,0' - 'Advanced SIMD modified immediate/ORR (vector, immediate) 32-bit'
      case 0x0f001400: packet->A64InstrIndex = SIMD_ORR_IMM_MOD_VEC_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->a = (packet->Opcode >> 18) & 0x1;
          packet->b = (packet->Opcode >> 17) & 0x1;
          packet->c = (packet->Opcode >> 16) & 0x1;
          packet->cmode = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 11) & 0x1;
          packet->d = (packet->Opcode >> 9) & 0x1;
          packet->e = (packet->Opcode >> 8) & 0x1;
          packet->f = (packet->Opcode >> 7) & 0x1;
          packet->g = (packet->Opcode >> 6) & 0x1;
          packet->h = (packet->Opcode >> 5) & 0x1;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xffa0fc00) {
      // 0x7ea0d400, SIMD_FABD_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/FABD Scalar'
      case 0x7ea0d400: packet->A64InstrIndex = SIMD_FABD_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e20ec00, SIMD_FACGE_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/FACGE Scalar'
      case 0x7e20ec00: packet->A64InstrIndex = SIMD_FACGE_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7ea0ec00, SIMD_FACGT_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/FACGT Scalar'
      case 0x7ea0ec00: packet->A64InstrIndex = SIMD_FACGT_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e20e400, SIMD_FCMEQ_REG_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/FCMEQ (register) Scalar'
      case 0x5e20e400: packet->A64InstrIndex = SIMD_FCMEQ_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e20e400, SIMD_FCMGE_REG_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/FCMGE (register) Scalar'
      case 0x7e20e400: packet->A64InstrIndex = SIMD_FCMGE_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7ea0e400, SIMD_FCMGT_REG_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/FCMGT (register) Scalar'
      case 0x7ea0e400: packet->A64InstrIndex = SIMD_FCMGT_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e20dc00, SIMD_FMULX_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/FMULX Scalar'
      case 0x5e20dc00: packet->A64InstrIndex = SIMD_FMULX_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e20fc00, SIMD_FRECPS_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/FRECPS Scalar'
      case 0x5e20fc00: packet->A64InstrIndex = SIMD_FRECPS_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5ea0fc00, SIMD_FRSQRTS_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/FRSQRTS Scalar'
      case 0x5ea0fc00: packet->A64InstrIndex = SIMD_FRSQRTS_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xffff0000) {
      // 0x1e580000, FCVTZS_FROM_DP_FP_FIXED_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 scale=15,10 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and fixed-point/FCVTZS (scalar, fixed-point) Double-precision to 32-bit'
      case 0x1e580000: packet->A64InstrIndex = FCVTZS_FROM_DP_FP_FIXED_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->scale = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e580000, FCVTZS_FROM_DP_FP_FIXED_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 scale=15,10 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and fixed-point/FCVTZS (scalar, fixed-point) Double-precision to 64-bit'
      case 0x9e580000: packet->A64InstrIndex = FCVTZS_FROM_DP_FP_FIXED_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->scale = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e180000, FCVTZS_SINGLE_FROM_SP_FP_FIXED_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 scale=15,10 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and fixed-point/FCVTZS (scalar, fixed-point) Single-precision to 32-bit'
      case 0x1e180000: packet->A64InstrIndex = FCVTZS_SINGLE_FROM_SP_FP_FIXED_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->scale = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e180000, FCVTZS_SINGLE_FROM_SP_FP_FIXED_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 scale=15,10 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and fixed-point/FCVTZS (scalar, fixed-point) Single-precision to 64-bit'
      case 0x9e180000: packet->A64InstrIndex = FCVTZS_SINGLE_FROM_SP_FP_FIXED_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->scale = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e590000, FCVTZU_FROM_DP_FP_FIXED_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 scale=15,10 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and fixed-point/FCVTZU (scalar, fixed-point) Double-precision to 32-bit'
      case 0x1e590000: packet->A64InstrIndex = FCVTZU_FROM_DP_FP_FIXED_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->scale = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e590000, FCVTZU_FROM_DP_FP_FIXED_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 scale=15,10 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and fixed-point/FCVTZU (scalar, fixed-point) Double-precision to 64-bit'
      case 0x9e590000: packet->A64InstrIndex = FCVTZU_FROM_DP_FP_FIXED_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->scale = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e190000, FCVTZU_SINGLE_FROM_SP_FP_FIXED_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 scale=15,10 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and fixed-point/FCVTZU (scalar, fixed-point) Single-precision to 32-bit'
      case 0x1e190000: packet->A64InstrIndex = FCVTZU_SINGLE_FROM_SP_FP_FIXED_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->scale = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e190000, FCVTZU_SINGLE_FROM_SP_FP_FIXED_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 scale=15,10 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and fixed-point/FCVTZU (scalar, fixed-point) Single-precision to 64-bit'
      case 0x9e190000: packet->A64InstrIndex = FCVTZU_SINGLE_FROM_SP_FP_FIXED_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->scale = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e420000, SCVTF_TO_DP_FP_FIXED_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 scale=15,10 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and fixed-point/SCVTF (scalar, fixed-point) 32-bit to double-precision'
      case 0x1e420000: packet->A64InstrIndex = SCVTF_TO_DP_FP_FIXED_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->scale = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e020000, SCVTF_SINGLE_TO_SP_FP_FIXED_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 scale=15,10 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and fixed-point/SCVTF (scalar, fixed-point) 32-bit to single-precision'
      case 0x1e020000: packet->A64InstrIndex = SCVTF_SINGLE_TO_SP_FP_FIXED_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->scale = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e420000, SCVTF_TO_DP_FP_FIXED_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 scale=15,10 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and fixed-point/SCVTF (scalar, fixed-point) 64-bit to double-precision'
      case 0x9e420000: packet->A64InstrIndex = SCVTF_TO_DP_FP_FIXED_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->scale = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e020000, SCVTF_SINGLE_TO_SP_FP_FIXED_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 scale=15,10 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and fixed-point/SCVTF (scalar, fixed-point) 64-bit to single-precision'
      case 0x9e020000: packet->A64InstrIndex = SCVTF_SINGLE_TO_SP_FP_FIXED_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->scale = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e430000, UCVTF_TO_DP_FP_FIXED_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 scale=15,10 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and fixed-point/UCVTF (scalar, fixed-point) 32-bit to double-precision'
      case 0x1e430000: packet->A64InstrIndex = UCVTF_TO_DP_FP_FIXED_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->scale = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e030000, UCVTF_SINGLE_TO_SP_FP_FIXED_32: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 scale=15,10 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and fixed-point/UCVTF (scalar, fixed-point) 32-bit to single-precision'
      case 0x1e030000: packet->A64InstrIndex = UCVTF_SINGLE_TO_SP_FP_FIXED_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->scale = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e430000, UCVTF_TO_DP_FP_FIXED_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 scale=15,10 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and fixed-point/UCVTF (scalar, fixed-point) 64-bit to double-precision'
      case 0x9e430000: packet->A64InstrIndex = UCVTF_TO_DP_FP_FIXED_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->scale = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9e030000, UCVTF_SINGLE_TO_SP_FP_FIXED_64: ' sf=31 S=29 type=23,22 rmode=20,19 opcode=18,16 scale=15,10 Rn=9,5 Rd=4,0' - 'Conversions between floating-point and fixed-point/UCVTF (scalar, fixed-point) 64-bit to single-precision'
      case 0x9e030000: packet->A64InstrIndex = UCVTF_SINGLE_TO_SP_FP_FIXED_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->rmode = (packet->Opcode >> 19) & 0x3;
          packet->opcode = (packet->Opcode >> 16) & 0x7;
          packet->scale = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xffe0001f) {
      // 0xd4200000, BRK: ' opc=23,21 imm16=20,5 op2=4,2 LL=1,0' - 'Exception generation/BRK -'
      case 0xd4200000: packet->A64InstrIndex = BRK;
          packet->opc = (packet->Opcode >> 21) & 0x7;
          packet->imm16 = (packet->Opcode >> 5) & 0xffff;
          packet->op2 = (packet->Opcode >> 2) & 0x7;
          packet->LL = packet->Opcode & 0x3;
          break;
      // 0xd4a00001, DCPS1: ' opc=23,21 imm16=20,5 op2=4,2 LL=1,0' - 'Exception generation/DCPS1 -'
      case 0xd4a00001: packet->A64InstrIndex = DCPS1;
          packet->opc = (packet->Opcode >> 21) & 0x7;
          packet->imm16 = (packet->Opcode >> 5) & 0xffff;
          packet->op2 = (packet->Opcode >> 2) & 0x7;
          packet->LL = packet->Opcode & 0x3;
          break;
      // 0xd4a00002, DCPS2: ' opc=23,21 imm16=20,5 op2=4,2 LL=1,0' - 'Exception generation/DCPS2 -'
      case 0xd4a00002: packet->A64InstrIndex = DCPS2;
          packet->opc = (packet->Opcode >> 21) & 0x7;
          packet->imm16 = (packet->Opcode >> 5) & 0xffff;
          packet->op2 = (packet->Opcode >> 2) & 0x7;
          packet->LL = packet->Opcode & 0x3;
          break;
      // 0xd4a00003, DCPS3: ' opc=23,21 imm16=20,5 op2=4,2 LL=1,0' - 'Exception generation/DCPS3 -'
      case 0xd4a00003: packet->A64InstrIndex = DCPS3;
          packet->opc = (packet->Opcode >> 21) & 0x7;
          packet->imm16 = (packet->Opcode >> 5) & 0xffff;
          packet->op2 = (packet->Opcode >> 2) & 0x7;
          packet->LL = packet->Opcode & 0x3;
          break;
      // 0xd4400000, HLT: ' opc=23,21 imm16=20,5 op2=4,2 LL=1,0' - 'Exception generation/HLT -'
      case 0xd4400000: packet->A64InstrIndex = HLT;
          packet->opc = (packet->Opcode >> 21) & 0x7;
          packet->imm16 = (packet->Opcode >> 5) & 0xffff;
          packet->op2 = (packet->Opcode >> 2) & 0x7;
          packet->LL = packet->Opcode & 0x3;
          break;
      // 0xd4000002, HVC: ' opc=23,21 imm16=20,5 op2=4,2 LL=1,0' - 'Exception generation/HVC -'
      case 0xd4000002: packet->A64InstrIndex = HVC;
          packet->opc = (packet->Opcode >> 21) & 0x7;
          packet->imm16 = (packet->Opcode >> 5) & 0xffff;
          packet->op2 = (packet->Opcode >> 2) & 0x7;
          packet->LL = packet->Opcode & 0x3;
          break;
      // 0xd4000003, SMC: ' opc=23,21 imm16=20,5 op2=4,2 LL=1,0' - 'Exception generation/SMC -'
      case 0xd4000003: packet->A64InstrIndex = SMC;
          packet->opc = (packet->Opcode >> 21) & 0x7;
          packet->imm16 = (packet->Opcode >> 5) & 0xffff;
          packet->op2 = (packet->Opcode >> 2) & 0x7;
          packet->LL = packet->Opcode & 0x3;
          break;
      // 0xd4000001, SVC: ' opc=23,21 imm16=20,5 op2=4,2 LL=1,0' - 'Exception generation/SVC -'
      case 0xd4000001: packet->A64InstrIndex = SVC;
          packet->opc = (packet->Opcode >> 21) & 0x7;
          packet->imm16 = (packet->Opcode >> 5) & 0xffff;
          packet->op2 = (packet->Opcode >> 2) & 0x7;
          packet->LL = packet->Opcode & 0x3;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbfe0fc00) {
      // 0x0e000400, SIMD_DUP_VEC_ELEM: ' Q=30 op=29 imm5=20,16 imm4=14,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD copy/DUP (element) Vector'
      case 0x0e000400: packet->A64InstrIndex = SIMD_DUP_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->imm5 = (packet->Opcode >> 16) & 0x1f;
          packet->imm4 = (packet->Opcode >> 11) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e000c00, SIMD_DUP: ' Q=30 op=29 imm5=20,16 imm4=14,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD copy/DUP (general) -'
      case 0x0e000c00: packet->A64InstrIndex = SIMD_DUP;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->imm5 = (packet->Opcode >> 16) & 0x1f;
          packet->imm4 = (packet->Opcode >> 11) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0dc08400, SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_64: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 64-bit, register offset'
      case 0x0dc08400: packet->A64InstrIndex = SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0de08400, SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_64: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 64-bit, register offset'
      case 0x0de08400: packet->A64InstrIndex = SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dc0a400, SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_64: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 64-bit, register offset'
      case 0x0dc0a400: packet->A64InstrIndex = SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0de0a400, SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_64: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 64-bit, register offset'
      case 0x0de0a400: packet->A64InstrIndex = SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d808400, SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_64: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 64-bit, register offset'
      case 0x0d808400: packet->A64InstrIndex = SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0da08400, SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_64: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 64-bit, register offset'
      case 0x0da08400: packet->A64InstrIndex = SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d80a400, SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_64: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 64-bit, register offset'
      case 0x0d80a400: packet->A64InstrIndex = SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0da0a400, SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_64: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 64-bit, register offset'
      case 0x0da0a400: packet->A64InstrIndex = SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_64;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0e006000, SIMD_TBL_FOUR_REG: ' Q=30 op2=23,22 Rm=20,16 len=14,13 op=12 Rn=9,5 Rd=4,0' - 'Advanced SIMD table lookup/TBL Four register table'
      case 0x0e006000: packet->A64InstrIndex = SIMD_TBL_FOUR_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op2 = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->len = (packet->Opcode >> 13) & 0x3;
          packet->op = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e000000, SIMD_TBL_SINGLE_REG: ' Q=30 op2=23,22 Rm=20,16 len=14,13 op=12 Rn=9,5 Rd=4,0' - 'Advanced SIMD table lookup/TBL Single register table'
      case 0x0e000000: packet->A64InstrIndex = SIMD_TBL_SINGLE_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op2 = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->len = (packet->Opcode >> 13) & 0x3;
          packet->op = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e004000, SIMD_TBL_THREE_REG: ' Q=30 op2=23,22 Rm=20,16 len=14,13 op=12 Rn=9,5 Rd=4,0' - 'Advanced SIMD table lookup/TBL Three register table'
      case 0x0e004000: packet->A64InstrIndex = SIMD_TBL_THREE_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op2 = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->len = (packet->Opcode >> 13) & 0x3;
          packet->op = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e002000, SIMD_TBL_TWO_REG: ' Q=30 op2=23,22 Rm=20,16 len=14,13 op=12 Rn=9,5 Rd=4,0' - 'Advanced SIMD table lookup/TBL Two register table'
      case 0x0e002000: packet->A64InstrIndex = SIMD_TBL_TWO_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op2 = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->len = (packet->Opcode >> 13) & 0x3;
          packet->op = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e007000, SIMD_TBX_FOUR_REG: ' Q=30 op2=23,22 Rm=20,16 len=14,13 op=12 Rn=9,5 Rd=4,0' - 'Advanced SIMD table lookup/TBX Four register table'
      case 0x0e007000: packet->A64InstrIndex = SIMD_TBX_FOUR_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op2 = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->len = (packet->Opcode >> 13) & 0x3;
          packet->op = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e001000, SIMD_TBX_SINGLE_REG: ' Q=30 op2=23,22 Rm=20,16 len=14,13 op=12 Rn=9,5 Rd=4,0' - 'Advanced SIMD table lookup/TBX Single register table'
      case 0x0e001000: packet->A64InstrIndex = SIMD_TBX_SINGLE_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op2 = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->len = (packet->Opcode >> 13) & 0x3;
          packet->op = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e005000, SIMD_TBX_THREE_REG: ' Q=30 op2=23,22 Rm=20,16 len=14,13 op=12 Rn=9,5 Rd=4,0' - 'Advanced SIMD table lookup/TBX Three register table'
      case 0x0e005000: packet->A64InstrIndex = SIMD_TBX_THREE_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op2 = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->len = (packet->Opcode >> 13) & 0x3;
          packet->op = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e003000, SIMD_TBX_TWO_REG: ' Q=30 op2=23,22 Rm=20,16 len=14,13 op=12 Rn=9,5 Rd=4,0' - 'Advanced SIMD table lookup/TBX Two register table'
      case 0x0e003000: packet->A64InstrIndex = SIMD_TBX_TWO_REG;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op2 = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->len = (packet->Opcode >> 13) & 0x3;
          packet->op = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e201c00, SIMD_AND_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/AND (vector) -'
      case 0x0e201c00: packet->A64InstrIndex = SIMD_AND_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e601c00, SIMD_BIC_REG_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/BIC (vector, register) -'
      case 0x0e601c00: packet->A64InstrIndex = SIMD_BIC_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2ee01c00, SIMD_BIF: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/BIF -'
      case 0x2ee01c00: packet->A64InstrIndex = SIMD_BIF;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2ea01c00, SIMD_BIT: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/BIT -'
      case 0x2ea01c00: packet->A64InstrIndex = SIMD_BIT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e601c00, SIMD_BSL: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/BSL -'
      case 0x2e601c00: packet->A64InstrIndex = SIMD_BSL;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e201c00, SIMD_EOR_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/EOR (vector) -'
      case 0x2e201c00: packet->A64InstrIndex = SIMD_EOR_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0ee01c00, SIMD_ORN_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/ORN (vector) -'
      case 0x0ee01c00: packet->A64InstrIndex = SIMD_ORN_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0ea01c00, SIMD_ORR_REG_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/ORR (vector, register) -'
      case 0x0ea01c00: packet->A64InstrIndex = SIMD_ORR_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xff80fc00) {
      // 0x5f00fc00, SIMD_FCVTZS_SHIFT_IMM_SCALAR_VEC_FIXED: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/FCVTZS (vector, fixed-point) Scalar'
      case 0x5f00fc00: packet->A64InstrIndex = SIMD_FCVTZS_SHIFT_IMM_SCALAR_VEC_FIXED;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7f00fc00, SIMD_FCVTZU_SHIFT_IMM_SCALAR_VEC_FIXED: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/FCVTZU (vector, fixed-point) Scalar'
      case 0x7f00fc00: packet->A64InstrIndex = SIMD_FCVTZU_SHIFT_IMM_SCALAR_VEC_FIXED;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5f00e400, SIMD_SCVTF_SHIFT_IMM_SCALAR_VEC_FIXED: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/SCVTF (vector, fixed-point) Scalar'
      case 0x5f00e400: packet->A64InstrIndex = SIMD_SCVTF_SHIFT_IMM_SCALAR_VEC_FIXED;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5f005400, SIMD_SHL_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/SHL Scalar'
      case 0x5f005400: packet->A64InstrIndex = SIMD_SHL_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7f005400, SIMD_SLI_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/SLI Scalar'
      case 0x7f005400: packet->A64InstrIndex = SIMD_SLI_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5f009c00, SIMD_SQRSHRN_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/SQRSHRN, SQRSHRN2 Scalar'
      case 0x5f009c00: packet->A64InstrIndex = SIMD_SQRSHRN_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7f008c00, SIMD_SQRSHRUN_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/SQRSHRUN, SQRSHRUN2 Scalar'
      case 0x7f008c00: packet->A64InstrIndex = SIMD_SQRSHRUN_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5f007400, SIMD_SQSHL_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/SQSHL (immediate) Scalar'
      case 0x5f007400: packet->A64InstrIndex = SIMD_SQSHL_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7f006400, SIMD_SQSHLU_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/SQSHLU Scalar'
      case 0x7f006400: packet->A64InstrIndex = SIMD_SQSHLU_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5f009400, SIMD_SQSHRN_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/SQSHRN, SQSHRN2 Scalar'
      case 0x5f009400: packet->A64InstrIndex = SIMD_SQSHRN_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7f008400, SIMD_SQSHRUN_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/SQSHRUN, SQSHRUN2 Scalar'
      case 0x7f008400: packet->A64InstrIndex = SIMD_SQSHRUN_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7f004400, SIMD_SRI_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/SRI Scalar'
      case 0x7f004400: packet->A64InstrIndex = SIMD_SRI_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5f002400, SIMD_SRSHR_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/SRSHR Scalar'
      case 0x5f002400: packet->A64InstrIndex = SIMD_SRSHR_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5f003400, SIMD_SRSRA_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/SRSRA Scalar'
      case 0x5f003400: packet->A64InstrIndex = SIMD_SRSRA_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5f000400, SIMD_SSHR_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/SSHR Scalar'
      case 0x5f000400: packet->A64InstrIndex = SIMD_SSHR_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5f001400, SIMD_SSRA_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/SSRA Scalar'
      case 0x5f001400: packet->A64InstrIndex = SIMD_SSRA_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7f00e400, SIMD_UCVTF_SHIFT_IMM_SCALAR_VEC_FIXED: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/UCVTF (vector, fixed-point) Scalar'
      case 0x7f00e400: packet->A64InstrIndex = SIMD_UCVTF_SHIFT_IMM_SCALAR_VEC_FIXED;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7f009c00, SIMD_UQRSHRN_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/UQRSHRN, UQRSHRN2 Scalar'
      case 0x7f009c00: packet->A64InstrIndex = SIMD_UQRSHRN_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7f007400, SIMD_UQSHL_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/UQSHL (immediate) Scalar'
      case 0x7f007400: packet->A64InstrIndex = SIMD_UQSHL_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7f009400, SIMD_UQSHRN_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/UQSHRN Scalar'
      case 0x7f009400: packet->A64InstrIndex = SIMD_UQSHRN_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7f002400, SIMD_URSHR_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/URSHR Scalar'
      case 0x7f002400: packet->A64InstrIndex = SIMD_URSHR_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7f003400, SIMD_URSRA_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/URSRA Scalar'
      case 0x7f003400: packet->A64InstrIndex = SIMD_URSRA_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7f000400, SIMD_USHR_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/USHR Scalar'
      case 0x7f000400: packet->A64InstrIndex = SIMD_USHR_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7f001400, SIMD_USRA_SHIFT_IMM_SCALAR: ' U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar shift by immediate/USRA Scalar'
      case 0x7f001400: packet->A64InstrIndex = SIMD_USRA_SHIFT_IMM_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xff20fc00) {
      // 0x5e209000, SIMD_SQDMLAL_SCALAR_VEC: ' U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three different/SQDMLAL, SQDMLAL2 (vector) Scalar'
      case 0x5e209000: packet->A64InstrIndex = SIMD_SQDMLAL_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e20b000, SIMD_SQDMLSL_SCALAR_VEC: ' U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three different/SQDMLSL, SQDMLSL2 (vector) Scalar'
      case 0x5e20b000: packet->A64InstrIndex = SIMD_SQDMLSL_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e20d000, SIMD_SQDMULL_SCALAR_VEC: ' U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three different/SQDMULL, SQDMULL2 (vector) Scalar'
      case 0x5e20d000: packet->A64InstrIndex = SIMD_SQDMULL_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e208400, SIMD_ADD_SCALAR_VEC: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/ADD (vector) Scalar'
      case 0x5e208400: packet->A64InstrIndex = SIMD_ADD_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e208c00, SIMD_CMEQ_REG_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/CMEQ (register) Scalar'
      case 0x7e208c00: packet->A64InstrIndex = SIMD_CMEQ_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e203c00, SIMD_CMGE_REG_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/CMGE (register) Scalar'
      case 0x5e203c00: packet->A64InstrIndex = SIMD_CMGE_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e203400, SIMD_CMGT_REG_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/CMGT (register) Scalar'
      case 0x5e203400: packet->A64InstrIndex = SIMD_CMGT_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e203400, SIMD_CMHI_REG_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/CMHI (register) Scalar'
      case 0x7e203400: packet->A64InstrIndex = SIMD_CMHI_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e203c00, SIMD_CMHS_REG_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/CMHS (register) Scalar'
      case 0x7e203c00: packet->A64InstrIndex = SIMD_CMHS_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e208c00, SIMD_CMTST_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/CMTST Scalar'
      case 0x5e208c00: packet->A64InstrIndex = SIMD_CMTST_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e200c00, SIMD_SQADD_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/SQADD Scalar'
      case 0x5e200c00: packet->A64InstrIndex = SIMD_SQADD_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e20b400, SIMD_SQDMULH_SCALAR_VEC: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/SQDMULH (vector) Scalar'
      case 0x5e20b400: packet->A64InstrIndex = SIMD_SQDMULH_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e20b400, SIMD_SQRDMULH_SCALAR_VEC: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/SQRDMULH (vector) Scalar'
      case 0x7e20b400: packet->A64InstrIndex = SIMD_SQRDMULH_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e205c00, SIMD_SQRSHL_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/SQRSHL Scalar'
      case 0x5e205c00: packet->A64InstrIndex = SIMD_SQRSHL_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e204c00, SIMD_SQSHL_REG_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/SQSHL (register) Scalar'
      case 0x5e204c00: packet->A64InstrIndex = SIMD_SQSHL_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e202c00, SIMD_SQSUB_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/SQSUB Scalar'
      case 0x5e202c00: packet->A64InstrIndex = SIMD_SQSUB_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e205400, SIMD_SRSHL_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/SRSHL Scalar'
      case 0x5e205400: packet->A64InstrIndex = SIMD_SRSHL_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5e204400, SIMD_SSHL_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/SSHL Scalar'
      case 0x5e204400: packet->A64InstrIndex = SIMD_SSHL_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e208400, SIMD_SUB_SCALAR_VEC: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/SUB (vector) Scalar'
      case 0x7e208400: packet->A64InstrIndex = SIMD_SUB_SCALAR_VEC;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e200c00, SIMD_UQADD_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/UQADD Scalar'
      case 0x7e200c00: packet->A64InstrIndex = SIMD_UQADD_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e205c00, SIMD_UQRSHL_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/UQRSHL Scalar'
      case 0x7e205c00: packet->A64InstrIndex = SIMD_UQRSHL_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e204c00, SIMD_UQSHL_REG_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/UQSHL (register) Scalar'
      case 0x7e204c00: packet->A64InstrIndex = SIMD_UQSHL_REG_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e202c00, SIMD_UQSUB_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/UQSUB Scalar'
      case 0x7e202c00: packet->A64InstrIndex = SIMD_UQSUB_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e205400, SIMD_URSHL_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/URSHL Scalar'
      case 0x7e205400: packet->A64InstrIndex = SIMD_URSHL_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7e204400, SIMD_USHL_SCALAR: ' U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar three same/USHL Scalar'
      case 0x7e204400: packet->A64InstrIndex = SIMD_USHL_SCALAR;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbfa0fc00) {
      // 0x2ea0d400, SIMD_FABD_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FABD Vector'
      case 0x2ea0d400: packet->A64InstrIndex = SIMD_FABD_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e20ec00, SIMD_FACGE_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FACGE Vector'
      case 0x2e20ec00: packet->A64InstrIndex = SIMD_FACGE_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2ea0ec00, SIMD_FACGT_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FACGT Vector'
      case 0x2ea0ec00: packet->A64InstrIndex = SIMD_FACGT_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e20d400, SIMD_FADD_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FADD (vector) -'
      case 0x0e20d400: packet->A64InstrIndex = SIMD_FADD_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e20d400, SIMD_FADDP_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FADDP (vector) -'
      case 0x2e20d400: packet->A64InstrIndex = SIMD_FADDP_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e20e400, SIMD_FCMEQ_REG_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FCMEQ (register) Vector'
      case 0x0e20e400: packet->A64InstrIndex = SIMD_FCMEQ_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e20e400, SIMD_FCMGE_REG_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FCMGE (register) Vector'
      case 0x2e20e400: packet->A64InstrIndex = SIMD_FCMGE_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2ea0e400, SIMD_FCMGT_REG_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FCMGT (register) Vector'
      case 0x2ea0e400: packet->A64InstrIndex = SIMD_FCMGT_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e20fc00, SIMD_FDIV_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FDIV (vector) -'
      case 0x2e20fc00: packet->A64InstrIndex = SIMD_FDIV_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e20f400, SIMD_FMAX_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FMAX (vector) -'
      case 0x0e20f400: packet->A64InstrIndex = SIMD_FMAX_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e20c400, SIMD_FMAXNM_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FMAXNM (vector) -'
      case 0x0e20c400: packet->A64InstrIndex = SIMD_FMAXNM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e20c400, SIMD_FMAXNMP_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FMAXNMP (vector) -'
      case 0x2e20c400: packet->A64InstrIndex = SIMD_FMAXNMP_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e20f400, SIMD_FMAXP_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FMAXP (vector) -'
      case 0x2e20f400: packet->A64InstrIndex = SIMD_FMAXP_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0ea0f400, SIMD_FMIN_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FMIN (vector) -'
      case 0x0ea0f400: packet->A64InstrIndex = SIMD_FMIN_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0ea0c400, SIMD_FMINNM_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FMINNM (vector) -'
      case 0x0ea0c400: packet->A64InstrIndex = SIMD_FMINNM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2ea0c400, SIMD_FMINNMP_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FMINNMP (vector) -'
      case 0x2ea0c400: packet->A64InstrIndex = SIMD_FMINNMP_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2ea0f400, SIMD_FMINP_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FMINP (vector) -'
      case 0x2ea0f400: packet->A64InstrIndex = SIMD_FMINP_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e20cc00, SIMD_FMLA_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FMLA (vector) -'
      case 0x0e20cc00: packet->A64InstrIndex = SIMD_FMLA_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0ea0cc00, SIMD_FMLS_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FMLS (vector) -'
      case 0x0ea0cc00: packet->A64InstrIndex = SIMD_FMLS_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e20dc00, SIMD_FMUL_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FMUL (vector) -'
      case 0x2e20dc00: packet->A64InstrIndex = SIMD_FMUL_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e20dc00, SIMD_FMULX_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FMULX Vector'
      case 0x0e20dc00: packet->A64InstrIndex = SIMD_FMULX_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e20fc00, SIMD_FRECPS_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FRECPS Vector'
      case 0x0e20fc00: packet->A64InstrIndex = SIMD_FRECPS_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0ea0fc00, SIMD_FRSQRTS_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FRSQRTS Vector'
      case 0x0ea0fc00: packet->A64InstrIndex = SIMD_FRSQRTS_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0ea0d400, SIMD_FSUB_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/FSUB (vector) -'
      case 0x0ea0d400: packet->A64InstrIndex = SIMD_FSUB_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbfe0ec00) {
      // 0x0dc08000, SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_32: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 32-bit, register offset'
      case 0x0dc08000: packet->A64InstrIndex = SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0de08000, SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_32: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 32-bit, register offset'
      case 0x0de08000: packet->A64InstrIndex = SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dc0a000, SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_32: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 32-bit, register offset'
      case 0x0dc0a000: packet->A64InstrIndex = SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0de0a000, SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_32: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 32-bit, register offset'
      case 0x0de0a000: packet->A64InstrIndex = SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d808000, SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_32: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 32-bit, register offset'
      case 0x0d808000: packet->A64InstrIndex = SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0da08000, SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_32: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 32-bit, register offset'
      case 0x0da08000: packet->A64InstrIndex = SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d80a000, SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_32: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 32-bit, register offset'
      case 0x0d80a000: packet->A64InstrIndex = SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0da0a000, SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_32: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 32-bit, register offset'
      case 0x0da0a000: packet->A64InstrIndex = SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_32;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbfe0f000) {
      // 0x0cc02000, SIMD_LD1_FOUR_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) Four registers, register offset'
      case 0x0cc02000: packet->A64InstrIndex = SIMD_LD1_FOUR_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0cc07000, SIMD_LD1_ONE_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) One register, register offset'
      case 0x0cc07000: packet->A64InstrIndex = SIMD_LD1_ONE_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0cc06000, SIMD_LD1_THREE_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) Three registers, register offset'
      case 0x0cc06000: packet->A64InstrIndex = SIMD_LD1_THREE_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0cc0a000, SIMD_LD1_TWO_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/LD1 (multiple structures) Two registers, register offset'
      case 0x0cc0a000: packet->A64InstrIndex = SIMD_LD1_TWO_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0cc08000, SIMD_LD2_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/LD2 (multiple structures) Register offset'
      case 0x0cc08000: packet->A64InstrIndex = SIMD_LD2_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0cc04000, SIMD_LD3_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/LD3 (multiple structures) Register offset'
      case 0x0cc04000: packet->A64InstrIndex = SIMD_LD3_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0cc00000, SIMD_LD4_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/LD4 (multiple structures) Register offset'
      case 0x0cc00000: packet->A64InstrIndex = SIMD_LD4_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c802000, SIMD_ST1_FOUR_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) Four registers, register offset'
      case 0x0c802000: packet->A64InstrIndex = SIMD_ST1_FOUR_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c807000, SIMD_ST1_ONE_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) One register, register offset'
      case 0x0c807000: packet->A64InstrIndex = SIMD_ST1_ONE_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c806000, SIMD_ST1_THREE_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) Three registers, register offset'
      case 0x0c806000: packet->A64InstrIndex = SIMD_ST1_THREE_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c80a000, SIMD_ST1_TWO_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/ST1 (multiple structures) Two registers, register offset'
      case 0x0c80a000: packet->A64InstrIndex = SIMD_ST1_TWO_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c808000, SIMD_ST2_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/ST2 (multiple structures) Register offset'
      case 0x0c808000: packet->A64InstrIndex = SIMD_ST2_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c804000, SIMD_ST3_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/ST3 (multiple structures) Register offset'
      case 0x0c804000: packet->A64InstrIndex = SIMD_ST3_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0c800000, SIMD_ST4_REG_OFF_MULT_POST_STRUCT: ' Q=30 L=22 Rm=20,16 opcode=15,12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store multiple structures (post-indexed)/ST4 (multiple structures) Register offset'
      case 0x0c800000: packet->A64InstrIndex = SIMD_ST4_REG_OFF_MULT_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dc0c000, SIMD_LD1R_REG_OFF_SINGLE_POST_STRUCT: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD1R Register offset'
      case 0x0dc0c000: packet->A64InstrIndex = SIMD_LD1R_REG_OFF_SINGLE_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0de0c000, SIMD_LD2R_REG_OFF_SINGLE_POST_STRUCT: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD2R Register offset'
      case 0x0de0c000: packet->A64InstrIndex = SIMD_LD2R_REG_OFF_SINGLE_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dc0e000, SIMD_LD3R_REG_OFF_SINGLE_POST_STRUCT: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD3R Register offset'
      case 0x0dc0e000: packet->A64InstrIndex = SIMD_LD3R_REG_OFF_SINGLE_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0de0e000, SIMD_LD4R_REG_OFF_SINGLE_POST_STRUCT: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD4R Register offset'
      case 0x0de0e000: packet->A64InstrIndex = SIMD_LD4R_REG_OFF_SINGLE_POST_STRUCT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbf80fc00) {
      // 0x0f00fc00, SIMD_FCVTZS_SHIFT_IMM_VEC_VEC_FIXED: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/FCVTZS (vector, fixed-point) Vector'
      case 0x0f00fc00: packet->A64InstrIndex = SIMD_FCVTZS_SHIFT_IMM_VEC_VEC_FIXED;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f00fc00, SIMD_FCVTZU_SHIFT_IMM_VEC_VEC_FIXED: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/FCVTZU (vector, fixed-point) Vector'
      case 0x2f00fc00: packet->A64InstrIndex = SIMD_FCVTZU_SHIFT_IMM_VEC_VEC_FIXED;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f008c00, SIMD_RSHRN_SHIFT_IMM: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/RSHRN, RSHRN2 -'
      case 0x0f008c00: packet->A64InstrIndex = SIMD_RSHRN_SHIFT_IMM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f00e400, SIMD_SCVTF_SHIFT_IMM_VEC_VEC_FIXED: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/SCVTF (vector, fixed-point) Vector'
      case 0x0f00e400: packet->A64InstrIndex = SIMD_SCVTF_SHIFT_IMM_VEC_VEC_FIXED;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f005400, SIMD_SHL_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/SHL Vector'
      case 0x0f005400: packet->A64InstrIndex = SIMD_SHL_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f008400, SIMD_SHRN_SHIFT_IMM: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/SHRN, SHRN2 -'
      case 0x0f008400: packet->A64InstrIndex = SIMD_SHRN_SHIFT_IMM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f005400, SIMD_SLI_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/SLI Vector'
      case 0x2f005400: packet->A64InstrIndex = SIMD_SLI_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f009c00, SIMD_SQRSHRN_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/SQRSHRN, SQRSHRN2 Vector'
      case 0x0f009c00: packet->A64InstrIndex = SIMD_SQRSHRN_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f008c00, SIMD_SQRSHRUN_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/SQRSHRUN, SQRSHRUN2 Vector'
      case 0x2f008c00: packet->A64InstrIndex = SIMD_SQRSHRUN_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f007400, SIMD_SQSHL_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/SQSHL (immediate) Vector'
      case 0x0f007400: packet->A64InstrIndex = SIMD_SQSHL_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f006400, SIMD_SQSHLU_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/SQSHLU Vector'
      case 0x2f006400: packet->A64InstrIndex = SIMD_SQSHLU_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f009400, SIMD_SQSHRN_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/SQSHRN, SQSHRN2 Vector'
      case 0x0f009400: packet->A64InstrIndex = SIMD_SQSHRN_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f008400, SIMD_SQSHRUN_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/SQSHRUN, SQSHRUN2 Vector'
      case 0x2f008400: packet->A64InstrIndex = SIMD_SQSHRUN_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f004400, SIMD_SRI_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/SRI Vector'
      case 0x2f004400: packet->A64InstrIndex = SIMD_SRI_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f002400, SIMD_SRSHR_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/SRSHR Vector'
      case 0x0f002400: packet->A64InstrIndex = SIMD_SRSHR_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f003400, SIMD_SRSRA_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/SRSRA Vector'
      case 0x0f003400: packet->A64InstrIndex = SIMD_SRSRA_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f00a400, SIMD_SSHLL_SHIFT_IMM: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/SSHLL, SSHLL2 -'
      case 0x0f00a400: packet->A64InstrIndex = SIMD_SSHLL_SHIFT_IMM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f000400, SIMD_SSHR_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/SSHR Vector'
      case 0x0f000400: packet->A64InstrIndex = SIMD_SSHR_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f001400, SIMD_SSRA_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/SSRA Vector'
      case 0x0f001400: packet->A64InstrIndex = SIMD_SSRA_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f00e400, SIMD_UCVTF_SHIFT_IMM_VEC_VEC_FIXED: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/UCVTF (vector, fixed-point) Vector'
      case 0x2f00e400: packet->A64InstrIndex = SIMD_UCVTF_SHIFT_IMM_VEC_VEC_FIXED;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f009c00, SIMD_UQRSHRN_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/UQRSHRN, UQRSHRN2 Vector'
      case 0x2f009c00: packet->A64InstrIndex = SIMD_UQRSHRN_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f007400, SIMD_UQSHL_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/UQSHL (immediate) Vector'
      case 0x2f007400: packet->A64InstrIndex = SIMD_UQSHL_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f009400, SIMD_UQSHRN_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/UQSHRN Vector'
      case 0x2f009400: packet->A64InstrIndex = SIMD_UQSHRN_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f002400, SIMD_URSHR_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/URSHR Vector'
      case 0x2f002400: packet->A64InstrIndex = SIMD_URSHR_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f003400, SIMD_URSRA_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/URSRA Vector'
      case 0x2f003400: packet->A64InstrIndex = SIMD_URSRA_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f00a400, SIMD_USHLL_SHIFT_IMM: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/USHLL, USHLL2 -'
      case 0x2f00a400: packet->A64InstrIndex = SIMD_USHLL_SHIFT_IMM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f000400, SIMD_USHR_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/USHR Vector'
      case 0x2f000400: packet->A64InstrIndex = SIMD_USHR_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f001400, SIMD_USRA_SHIFT_IMM_VEC: ' Q=30 U=29 immh=22,19 immb=18,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD shift by immediate/USRA Vector'
      case 0x2f001400: packet->A64InstrIndex = SIMD_USRA_SHIFT_IMM_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->immh = (packet->Opcode >> 19) & 0xf;
          packet->immb = (packet->Opcode >> 16) & 0x7;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbfe0e400) {
      // 0x0dc04000, SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_16: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 16-bit, register offset'
      case 0x0dc04000: packet->A64InstrIndex = SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0de04000, SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_16: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 16-bit, register offset'
      case 0x0de04000: packet->A64InstrIndex = SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dc06000, SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_16: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 16-bit, register offset'
      case 0x0dc06000: packet->A64InstrIndex = SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0de06000, SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_16: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 16-bit, register offset'
      case 0x0de06000: packet->A64InstrIndex = SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d804000, SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_16: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 16-bit, register offset'
      case 0x0d804000: packet->A64InstrIndex = SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0da04000, SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_16: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 16-bit, register offset'
      case 0x0da04000: packet->A64InstrIndex = SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d806000, SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_16: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 16-bit, register offset'
      case 0x0d806000: packet->A64InstrIndex = SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0da06000, SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_16: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 16-bit, register offset'
      case 0x0da06000: packet->A64InstrIndex = SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_16;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbf20fc00) {
      // 0x0e002800, SIMD_TRN1: ' Q=30 size=23,22 Rm=20,16 opcode=14,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD permute/TRN1 -'
      case 0x0e002800: packet->A64InstrIndex = SIMD_TRN1;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e006800, SIMD_TRN2: ' Q=30 size=23,22 Rm=20,16 opcode=14,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD permute/TRN2 -'
      case 0x0e006800: packet->A64InstrIndex = SIMD_TRN2;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e001800, SIMD_UZP1: ' Q=30 size=23,22 Rm=20,16 opcode=14,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD permute/UZP1 -'
      case 0x0e001800: packet->A64InstrIndex = SIMD_UZP1;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e005800, SIMD_UZP2: ' Q=30 size=23,22 Rm=20,16 opcode=14,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD permute/UZP2 -'
      case 0x0e005800: packet->A64InstrIndex = SIMD_UZP2;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e003800, SIMD_ZIP1: ' Q=30 size=23,22 Rm=20,16 opcode=14,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD permute/ZIP1 -'
      case 0x0e003800: packet->A64InstrIndex = SIMD_ZIP1;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e007800, SIMD_ZIP2: ' Q=30 size=23,22 Rm=20,16 opcode=14,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD permute/ZIP2 -'
      case 0x0e007800: packet->A64InstrIndex = SIMD_ZIP2;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e204000, SIMD_ADDHN: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/ADDHN, ADDHN2 -'
      case 0x0e204000: packet->A64InstrIndex = SIMD_ADDHN;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e20e000, SIMD_PMULL: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/PMULL, PMULL2 -'
      case 0x0e20e000: packet->A64InstrIndex = SIMD_PMULL;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e204000, SIMD_RADDHN: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/RADDHN, RADDHN2 -'
      case 0x2e204000: packet->A64InstrIndex = SIMD_RADDHN;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e206000, SIMD_RSUBHN: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/RSUBHN, RSUBHN2 -'
      case 0x2e206000: packet->A64InstrIndex = SIMD_RSUBHN;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e205000, SIMD_SABAL: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/SABAL, SABAL2 -'
      case 0x0e205000: packet->A64InstrIndex = SIMD_SABAL;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e207000, SIMD_SABDL: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/SABDL, SABDL2 -'
      case 0x0e207000: packet->A64InstrIndex = SIMD_SABDL;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e200000, SIMD_SADDL: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/SADDL, SADDL2 -'
      case 0x0e200000: packet->A64InstrIndex = SIMD_SADDL;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e201000, SIMD_SADDW: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/SADDW, SADDW2 -'
      case 0x0e201000: packet->A64InstrIndex = SIMD_SADDW;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e208000, SIMD_SMLAL_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/SMLAL, SMLAL2 (vector) -'
      case 0x0e208000: packet->A64InstrIndex = SIMD_SMLAL_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e20a000, SIMD_SMLSL_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/SMLSL, SMLSL2 (vector) -'
      case 0x0e20a000: packet->A64InstrIndex = SIMD_SMLSL_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e20c000, SIMD_SMULL_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/SMULL, SMULL2 (vector) -'
      case 0x0e20c000: packet->A64InstrIndex = SIMD_SMULL_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e209000, SIMD_SQDMLAL_VEC_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/SQDMLAL, SQDMLAL2 (vector) Vector'
      case 0x0e209000: packet->A64InstrIndex = SIMD_SQDMLAL_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e20b000, SIMD_SQDMLSL_VEC_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/SQDMLSL, SQDMLSL2 (vector) Vector'
      case 0x0e20b000: packet->A64InstrIndex = SIMD_SQDMLSL_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e20d000, SIMD_SQDMULL_VEC_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/SQDMULL, SQDMULL2 (vector) Vector'
      case 0x0e20d000: packet->A64InstrIndex = SIMD_SQDMULL_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e202000, SIMD_SSUBL: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/SSUBL, SSUBL2 -'
      case 0x0e202000: packet->A64InstrIndex = SIMD_SSUBL;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e203000, SIMD_SSUBW: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/SSUBW, SSUBW2 -'
      case 0x0e203000: packet->A64InstrIndex = SIMD_SSUBW;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e206000, SIMD_SUBHN: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/SUBHN, SUBHN2 -'
      case 0x0e206000: packet->A64InstrIndex = SIMD_SUBHN;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e205000, SIMD_UABAL: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/UABAL, UABAL2 -'
      case 0x2e205000: packet->A64InstrIndex = SIMD_UABAL;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e207000, SIMD_UABDL: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/UABDL, UABDL2 -'
      case 0x2e207000: packet->A64InstrIndex = SIMD_UABDL;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e200000, SIMD_UADDL: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/UADDL, UADDL2 -'
      case 0x2e200000: packet->A64InstrIndex = SIMD_UADDL;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e201000, SIMD_UADDW: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/UADDW, UADDW2 -'
      case 0x2e201000: packet->A64InstrIndex = SIMD_UADDW;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e208000, SIMD_UMLAL_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/UMLAL, UMLAL2 (vector) -'
      case 0x2e208000: packet->A64InstrIndex = SIMD_UMLAL_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e20a000, SIMD_UMLSL_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/UMLSL, UMLSL2 (vector) -'
      case 0x2e20a000: packet->A64InstrIndex = SIMD_UMLSL_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e20c000, SIMD_UMULL_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/UMULL, UMULL2 (vector) -'
      case 0x2e20c000: packet->A64InstrIndex = SIMD_UMULL_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e202000, SIMD_USUBL: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/USUBL, USUBL2 -'
      case 0x2e202000: packet->A64InstrIndex = SIMD_USUBL;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e203000, SIMD_USUBW: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,12 Rn=9,5 Rd=4,0' - 'Advanced SIMD three different/USUBW, USUBW2 -'
      case 0x2e203000: packet->A64InstrIndex = SIMD_USUBW;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e208400, SIMD_ADD_VEC_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/ADD (vector) Vector'
      case 0x0e208400: packet->A64InstrIndex = SIMD_ADD_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e20bc00, SIMD_ADDP_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/ADDP (vector) -'
      case 0x0e20bc00: packet->A64InstrIndex = SIMD_ADDP_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e208c00, SIMD_CMEQ_REG_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/CMEQ (register) Vector'
      case 0x2e208c00: packet->A64InstrIndex = SIMD_CMEQ_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e203c00, SIMD_CMGE_REG_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/CMGE (register) Vector'
      case 0x0e203c00: packet->A64InstrIndex = SIMD_CMGE_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e203400, SIMD_CMGT_REG_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/CMGT (register) Vector'
      case 0x0e203400: packet->A64InstrIndex = SIMD_CMGT_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e203400, SIMD_CMHI_REG_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/CMHI (register) Vector'
      case 0x2e203400: packet->A64InstrIndex = SIMD_CMHI_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e203c00, SIMD_CMHS_REG_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/CMHS (register) Vector'
      case 0x2e203c00: packet->A64InstrIndex = SIMD_CMHS_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e208c00, SIMD_CMTST_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/CMTST Vector'
      case 0x0e208c00: packet->A64InstrIndex = SIMD_CMTST_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e209400, SIMD_MLA_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/MLA (vector) -'
      case 0x0e209400: packet->A64InstrIndex = SIMD_MLA_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e209400, SIMD_MLS_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/MLS (vector) -'
      case 0x2e209400: packet->A64InstrIndex = SIMD_MLS_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e209c00, SIMD_MUL_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/MUL (vector) -'
      case 0x0e209c00: packet->A64InstrIndex = SIMD_MUL_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e209c00, SIMD_PMUL: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/PMUL -'
      case 0x2e209c00: packet->A64InstrIndex = SIMD_PMUL;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e207c00, SIMD_SABA: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/SABA -'
      case 0x0e207c00: packet->A64InstrIndex = SIMD_SABA;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e207400, SIMD_SABD: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/SABD -'
      case 0x0e207400: packet->A64InstrIndex = SIMD_SABD;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e200400, SIMD_SHADD: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/SHADD -'
      case 0x0e200400: packet->A64InstrIndex = SIMD_SHADD;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e202400, SIMD_SHSUB: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/SHSUB -'
      case 0x0e202400: packet->A64InstrIndex = SIMD_SHSUB;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e206400, SIMD_SMAX: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/SMAX -'
      case 0x0e206400: packet->A64InstrIndex = SIMD_SMAX;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e20a400, SIMD_SMAXP: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/SMAXP -'
      case 0x0e20a400: packet->A64InstrIndex = SIMD_SMAXP;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e206c00, SIMD_SMIN: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/SMIN -'
      case 0x0e206c00: packet->A64InstrIndex = SIMD_SMIN;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e20ac00, SIMD_SMINP: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/SMINP -'
      case 0x0e20ac00: packet->A64InstrIndex = SIMD_SMINP;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e200c00, SIMD_SQADD_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/SQADD Vector'
      case 0x0e200c00: packet->A64InstrIndex = SIMD_SQADD_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e20b400, SIMD_SQDMULH_VEC_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/SQDMULH (vector) Vector'
      case 0x0e20b400: packet->A64InstrIndex = SIMD_SQDMULH_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e20b400, SIMD_SQRDMULH_VEC_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/SQRDMULH (vector) Vector'
      case 0x2e20b400: packet->A64InstrIndex = SIMD_SQRDMULH_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e205c00, SIMD_SQRSHL_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/SQRSHL Vector'
      case 0x0e205c00: packet->A64InstrIndex = SIMD_SQRSHL_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e204c00, SIMD_SQSHL_REG_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/SQSHL (register) Vector'
      case 0x0e204c00: packet->A64InstrIndex = SIMD_SQSHL_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e202c00, SIMD_SQSUB_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/SQSUB Vector'
      case 0x0e202c00: packet->A64InstrIndex = SIMD_SQSUB_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e201400, SIMD_SRHADD: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/SRHADD -'
      case 0x0e201400: packet->A64InstrIndex = SIMD_SRHADD;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e205400, SIMD_SRSHL_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/SRSHL Vector'
      case 0x0e205400: packet->A64InstrIndex = SIMD_SRSHL_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0e204400, SIMD_SSHL_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/SSHL Vector'
      case 0x0e204400: packet->A64InstrIndex = SIMD_SSHL_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e208400, SIMD_SUB_VEC_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/SUB (vector) Vector'
      case 0x2e208400: packet->A64InstrIndex = SIMD_SUB_VEC_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e207c00, SIMD_UABA: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/UABA -'
      case 0x2e207c00: packet->A64InstrIndex = SIMD_UABA;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e207400, SIMD_UABD: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/UABD -'
      case 0x2e207400: packet->A64InstrIndex = SIMD_UABD;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e200400, SIMD_UHADD: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/UHADD -'
      case 0x2e200400: packet->A64InstrIndex = SIMD_UHADD;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e202400, SIMD_UHSUB: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/UHSUB -'
      case 0x2e202400: packet->A64InstrIndex = SIMD_UHSUB;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e206400, SIMD_UMAX: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/UMAX -'
      case 0x2e206400: packet->A64InstrIndex = SIMD_UMAX;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e20a400, SIMD_UMAXP: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/UMAXP -'
      case 0x2e20a400: packet->A64InstrIndex = SIMD_UMAXP;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e206c00, SIMD_UMIN: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/UMIN -'
      case 0x2e206c00: packet->A64InstrIndex = SIMD_UMIN;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e20ac00, SIMD_UMINP: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/UMINP -'
      case 0x2e20ac00: packet->A64InstrIndex = SIMD_UMINP;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e200c00, SIMD_UQADD_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/UQADD Vector'
      case 0x2e200c00: packet->A64InstrIndex = SIMD_UQADD_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e205c00, SIMD_UQRSHL_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/UQRSHL Vector'
      case 0x2e205c00: packet->A64InstrIndex = SIMD_UQRSHL_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e204c00, SIMD_UQSHL_REG_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/UQSHL (register) Vector'
      case 0x2e204c00: packet->A64InstrIndex = SIMD_UQSHL_REG_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e202c00, SIMD_UQSUB_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/UQSUB Vector'
      case 0x2e202c00: packet->A64InstrIndex = SIMD_UQSUB_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e201400, SIMD_URHADD: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/URHADD -'
      case 0x2e201400: packet->A64InstrIndex = SIMD_URHADD;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e205400, SIMD_URSHL_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/URSHL Vector'
      case 0x2e205400: packet->A64InstrIndex = SIMD_URSHL_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2e204400, SIMD_USHL_VEC: ' Q=30 U=29 size=23,22 Rm=20,16 opcode=15,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD three same/USHL Vector'
      case 0x2e204400: packet->A64InstrIndex = SIMD_USHL_VEC;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 11) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xff80f400) {
      // 0x5f801000, SIMD_FMLA_SCALAR_ELEM: ' U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar x indexed element/FMLA (by element) Scalar'
      case 0x5f801000: packet->A64InstrIndex = SIMD_FMLA_SCALAR_ELEM;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5f805000, SIMD_FMLS_SCALAR_ELEM: ' U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar x indexed element/FMLS (by element) Scalar'
      case 0x5f805000: packet->A64InstrIndex = SIMD_FMLS_SCALAR_ELEM;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5f809000, SIMD_FMUL_SCALAR_ELEM: ' U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar x indexed element/FMUL (by element) Scalar'
      case 0x5f809000: packet->A64InstrIndex = SIMD_FMUL_SCALAR_ELEM;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x7f809000, SIMD_FMULX_SCALAR_ELEM: ' U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar x indexed element/FMULX (by element) Scalar'
      case 0x7f809000: packet->A64InstrIndex = SIMD_FMULX_SCALAR_ELEM;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xffe00c10) {
      // 0x3a400800, CCMN_IMM_32: ' sf=31 op=30 S=29 imm5=20,16 cond=15,12 o2=10 Rn=9,5 o3=4 nzcv=3,0' - 'Conditional compare (immediate)/CCMN (immediate) 32-bit'
      case 0x3a400800: packet->A64InstrIndex = CCMN_IMM_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->imm5 = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 10) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->o3 = (packet->Opcode >> 4) & 0x1;
          packet->nzcv = packet->Opcode & 0xf;
          break;
      // 0xba400800, CCMN_IMM_64: ' sf=31 op=30 S=29 imm5=20,16 cond=15,12 o2=10 Rn=9,5 o3=4 nzcv=3,0' - 'Conditional compare (immediate)/CCMN (immediate) 64-bit'
      case 0xba400800: packet->A64InstrIndex = CCMN_IMM_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->imm5 = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 10) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->o3 = (packet->Opcode >> 4) & 0x1;
          packet->nzcv = packet->Opcode & 0xf;
          break;
      // 0x7a400800, CCMP_IMM_32: ' sf=31 op=30 S=29 imm5=20,16 cond=15,12 o2=10 Rn=9,5 o3=4 nzcv=3,0' - 'Conditional compare (immediate)/CCMP (immediate) 32-bit'
      case 0x7a400800: packet->A64InstrIndex = CCMP_IMM_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->imm5 = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 10) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->o3 = (packet->Opcode >> 4) & 0x1;
          packet->nzcv = packet->Opcode & 0xf;
          break;
      // 0xfa400800, CCMP_IMM_64: ' sf=31 op=30 S=29 imm5=20,16 cond=15,12 o2=10 Rn=9,5 o3=4 nzcv=3,0' - 'Conditional compare (immediate)/CCMP (immediate) 64-bit'
      case 0xfa400800: packet->A64InstrIndex = CCMP_IMM_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->imm5 = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 10) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->o3 = (packet->Opcode >> 4) & 0x1;
          packet->nzcv = packet->Opcode & 0xf;
          break;
      // 0x3a400000, CCMN_REG_32: ' sf=31 op=30 S=29 Rm=20,16 cond=15,12 o2=10 Rn=9,5 o3=4 nzcv=3,0' - 'Conditional compare (register)/CCMN (register) 32-bit'
      case 0x3a400000: packet->A64InstrIndex = CCMN_REG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 10) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->o3 = (packet->Opcode >> 4) & 0x1;
          packet->nzcv = packet->Opcode & 0xf;
          break;
      // 0xba400000, CCMN_REG_64: ' sf=31 op=30 S=29 Rm=20,16 cond=15,12 o2=10 Rn=9,5 o3=4 nzcv=3,0' - 'Conditional compare (register)/CCMN (register) 64-bit'
      case 0xba400000: packet->A64InstrIndex = CCMN_REG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 10) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->o3 = (packet->Opcode >> 4) & 0x1;
          packet->nzcv = packet->Opcode & 0xf;
          break;
      // 0x7a400000, CCMP_REG_32: ' sf=31 op=30 S=29 Rm=20,16 cond=15,12 o2=10 Rn=9,5 o3=4 nzcv=3,0' - 'Conditional compare (register)/CCMP (register) 32-bit'
      case 0x7a400000: packet->A64InstrIndex = CCMP_REG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 10) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->o3 = (packet->Opcode >> 4) & 0x1;
          packet->nzcv = packet->Opcode & 0xf;
          break;
      // 0xfa400000, CCMP_REG_64: ' sf=31 op=30 S=29 Rm=20,16 cond=15,12 o2=10 Rn=9,5 o3=4 nzcv=3,0' - 'Conditional compare (register)/CCMP (register) 64-bit'
      case 0xfa400000: packet->A64InstrIndex = CCMP_REG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->o2 = (packet->Opcode >> 10) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->o3 = (packet->Opcode >> 4) & 0x1;
          packet->nzcv = packet->Opcode & 0xf;
          break;
      // 0x1e600400, FCCMP_FROM_DP: ' M=31 S=29 type=23,22 Rm=20,16 cond=15,12 Rn=9,5 op=4 nzcv=3,0' - 'Floating-point conditional compare/FCCMP Double-precision'
      case 0x1e600400: packet->A64InstrIndex = FCCMP_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->op = (packet->Opcode >> 4) & 0x1;
          packet->nzcv = packet->Opcode & 0xf;
          break;
      // 0x1e200400, FCCMP_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 Rm=20,16 cond=15,12 Rn=9,5 op=4 nzcv=3,0' - 'Floating-point conditional compare/FCCMP Single-precision'
      case 0x1e200400: packet->A64InstrIndex = FCCMP_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->op = (packet->Opcode >> 4) & 0x1;
          packet->nzcv = packet->Opcode & 0xf;
          break;
      // 0x1e600410, FCCMPE_FROM_DP: ' M=31 S=29 type=23,22 Rm=20,16 cond=15,12 Rn=9,5 op=4 nzcv=3,0' - 'Floating-point conditional compare/FCCMPE Double-precision'
      case 0x1e600410: packet->A64InstrIndex = FCCMPE_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->op = (packet->Opcode >> 4) & 0x1;
          packet->nzcv = packet->Opcode & 0xf;
          break;
      // 0x1e200410, FCCMPE_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 Rm=20,16 cond=15,12 Rn=9,5 op=4 nzcv=3,0' - 'Floating-point conditional compare/FCCMPE Single-precision'
      case 0x1e200410: packet->A64InstrIndex = FCCMPE_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->op = (packet->Opcode >> 4) & 0x1;
          packet->nzcv = packet->Opcode & 0xf;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbfe0e000) {
      // 0x0dc00000, SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_8: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD1 (single structure) 8-bit, register offset'
      case 0x0dc00000: packet->A64InstrIndex = SIMD_LD1_REG_OFF_SINGLE_POST_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0de00000, SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_8: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD2 (single structure) 8-bit, register offset'
      case 0x0de00000: packet->A64InstrIndex = SIMD_LD2_REG_OFF_SINGLE_POST_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0dc02000, SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_8: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD3 (single structure) 8-bit, register offset'
      case 0x0dc02000: packet->A64InstrIndex = SIMD_LD3_REG_OFF_SINGLE_POST_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0de02000, SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_8: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/LD4 (single structure) 8-bit, register offset'
      case 0x0de02000: packet->A64InstrIndex = SIMD_LD4_REG_OFF_SINGLE_POST_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d800000, SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_8: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST1 (single structure) 8-bit, register offset'
      case 0x0d800000: packet->A64InstrIndex = SIMD_ST1_REG_OFF_SINGLE_POST_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0da00000, SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_8: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST2 (single structure) 8-bit, register offset'
      case 0x0da00000: packet->A64InstrIndex = SIMD_ST2_REG_OFF_SINGLE_POST_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0d802000, SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_8: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST3 (single structure) 8-bit, register offset'
      case 0x0d802000: packet->A64InstrIndex = SIMD_ST3_REG_OFF_SINGLE_POST_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x0da02000, SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_8: ' Q=30 L=22 R=21 Rm=20,16 opcode=15,13 S=12 size=11,10 Rn=9,5 Rt=4,0' - 'Advanced SIMD load/store single structure (post-indexed)/ST4 (single structure) 8-bit, register offset'
      case 0x0da02000: packet->A64InstrIndex = SIMD_ST4_REG_OFF_SINGLE_POST_STRUCT_8;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->R = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->opcode = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->size = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xfff80000) {
      // 0xd5080000, SYS: ' L=21 op0=20,19 op1=18,16 CRn=15,12 CRm=11,8 op2=7,5 Rt=4,0' - 'System/SYS -'
      case 0xd5080000: packet->A64InstrIndex = SYS;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->op0 = (packet->Opcode >> 19) & 0x3;
          packet->op1 = (packet->Opcode >> 16) & 0x7;
          packet->CRn = (packet->Opcode >> 12) & 0xf;
          packet->CRm = (packet->Opcode >> 8) & 0xf;
          packet->op2 = (packet->Opcode >> 5) & 0x7;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xd5280000, SYSL: ' L=21 op0=20,19 op1=18,16 CRn=15,12 CRm=11,8 op2=7,5 Rt=4,0' - 'System/SYSL -'
      case 0xd5280000: packet->A64InstrIndex = SYSL;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->op0 = (packet->Opcode >> 19) & 0x3;
          packet->op1 = (packet->Opcode >> 16) & 0x7;
          packet->CRn = (packet->Opcode >> 12) & 0xf;
          packet->CRm = (packet->Opcode >> 8) & 0xf;
          packet->op2 = (packet->Opcode >> 5) & 0x7;
          packet->Rt = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xff00f400) {
      // 0x5f003000, SIMD_SQDMLAL_SCALAR_ELEM: ' U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar x indexed element/SQDMLAL, SQDMLAL2 (by element) Scalar'
      case 0x5f003000: packet->A64InstrIndex = SIMD_SQDMLAL_SCALAR_ELEM;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5f007000, SIMD_SQDMLSL_SCALAR_ELEM: ' U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar x indexed element/SQDMLSL, SQDMLSL2 (by element) Scalar'
      case 0x5f007000: packet->A64InstrIndex = SIMD_SQDMLSL_SCALAR_ELEM;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5f00c000, SIMD_SQDMULH_SCALAR_ELEM: ' U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar x indexed element/SQDMULH (by element) Scalar'
      case 0x5f00c000: packet->A64InstrIndex = SIMD_SQDMULH_SCALAR_ELEM;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5f00b000, SIMD_SQDMULL_SCALAR_ELEM: ' U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar x indexed element/SQDMULL, SQDMULL2 (by element) Scalar'
      case 0x5f00b000: packet->A64InstrIndex = SIMD_SQDMULL_SCALAR_ELEM;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5f00d000, SIMD_SQRDMULH_SCALAR_ELEM: ' U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD scalar x indexed element/SQRDMULH (by element) Scalar'
      case 0x5f00d000: packet->A64InstrIndex = SIMD_SQRDMULH_SCALAR_ELEM;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbf80f400) {
      // 0x0f801000, SIMD_FMLA_VEC_VEC_ELEM: ' Q=30 U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD vector x indexed element/FMLA (by element) Vector'
      case 0x0f801000: packet->A64InstrIndex = SIMD_FMLA_VEC_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f805000, SIMD_FMLS_VEC_VEC_ELEM: ' Q=30 U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD vector x indexed element/FMLS (by element) Vector'
      case 0x0f805000: packet->A64InstrIndex = SIMD_FMLS_VEC_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f809000, SIMD_FMUL_VEC_VEC_ELEM: ' Q=30 U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD vector x indexed element/FMUL (by element) Vector'
      case 0x0f809000: packet->A64InstrIndex = SIMD_FMUL_VEC_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f809000, SIMD_FMULX_VEC_VEC_ELEM: ' Q=30 U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD vector x indexed element/FMULX (by element) Vector'
      case 0x2f809000: packet->A64InstrIndex = SIMD_FMULX_VEC_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xffe00c00) {
      // 0x1a800000, CSEL_32: ' sf=31 op=30 S=29 Rm=20,16 cond=15,12 op2=11,10 Rn=9,5 Rd=4,0' - 'Conditional select/CSEL 32-bit'
      case 0x1a800000: packet->A64InstrIndex = CSEL_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->op2 = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9a800000, CSEL_64: ' sf=31 op=30 S=29 Rm=20,16 cond=15,12 op2=11,10 Rn=9,5 Rd=4,0' - 'Conditional select/CSEL 64-bit'
      case 0x9a800000: packet->A64InstrIndex = CSEL_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->op2 = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1a800400, CSINC_32: ' sf=31 op=30 S=29 Rm=20,16 cond=15,12 op2=11,10 Rn=9,5 Rd=4,0' - 'Conditional select/CSINC 32-bit'
      case 0x1a800400: packet->A64InstrIndex = CSINC_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->op2 = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9a800400, CSINC_64: ' sf=31 op=30 S=29 Rm=20,16 cond=15,12 op2=11,10 Rn=9,5 Rd=4,0' - 'Conditional select/CSINC 64-bit'
      case 0x9a800400: packet->A64InstrIndex = CSINC_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->op2 = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5a800000, CSINV_32: ' sf=31 op=30 S=29 Rm=20,16 cond=15,12 op2=11,10 Rn=9,5 Rd=4,0' - 'Conditional select/CSINV 32-bit'
      case 0x5a800000: packet->A64InstrIndex = CSINV_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->op2 = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xda800000, CSINV_64: ' sf=31 op=30 S=29 Rm=20,16 cond=15,12 op2=11,10 Rn=9,5 Rd=4,0' - 'Conditional select/CSINV 64-bit'
      case 0xda800000: packet->A64InstrIndex = CSINV_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->op2 = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x5a800400, CSNEG_32: ' sf=31 op=30 S=29 Rm=20,16 cond=15,12 op2=11,10 Rn=9,5 Rd=4,0' - 'Conditional select/CSNEG 32-bit'
      case 0x5a800400: packet->A64InstrIndex = CSNEG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->op2 = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xda800400, CSNEG_64: ' sf=31 op=30 S=29 Rm=20,16 cond=15,12 op2=11,10 Rn=9,5 Rd=4,0' - 'Conditional select/CSNEG 64-bit'
      case 0xda800400: packet->A64InstrIndex = CSNEG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->op2 = (packet->Opcode >> 10) & 0x3;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e600c00, FCSEL_FROM_DP: ' M=31 S=29 type=23,22 Rm=20,16 cond=15,12 Rn=9,5 Rd=4,0' - 'Floating-point conditional select/FCSEL Double-precision'
      case 0x1e600c00: packet->A64InstrIndex = FCSEL_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1e200c00, FCSEL_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 Rm=20,16 cond=15,12 Rn=9,5 Rd=4,0' - 'Floating-point conditional select/FCSEL Single-precision'
      case 0x1e200c00: packet->A64InstrIndex = FCSEL_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->cond = (packet->Opcode >> 12) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xb8400400, LDR_IMM_REG_POST_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/LDR (immediate) 32-bit'
      case 0xb8400400: packet->A64InstrIndex = LDR_IMM_REG_POST_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xf8400400, LDR_IMM_REG_POST_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/LDR (immediate) 64-bit'
      case 0xf8400400: packet->A64InstrIndex = LDR_IMM_REG_POST_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3cc00400, SIMD_LDR_IMM_REG_POST_8_128: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/LDR (immediate, SIMD&FP) 128-bit'
      case 0x3cc00400: packet->A64InstrIndex = SIMD_LDR_IMM_REG_POST_8_128;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x7c400400, SIMD_LDR_IMM_REG_POST_16: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/LDR (immediate, SIMD&FP) 16-bit'
      case 0x7c400400: packet->A64InstrIndex = SIMD_LDR_IMM_REG_POST_16;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xbc400400, SIMD_LDR_IMM_REG_POST_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/LDR (immediate, SIMD&FP) 32-bit'
      case 0xbc400400: packet->A64InstrIndex = SIMD_LDR_IMM_REG_POST_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xfc400400, SIMD_LDR_IMM_REG_POST_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/LDR (immediate, SIMD&FP) 64-bit'
      case 0xfc400400: packet->A64InstrIndex = SIMD_LDR_IMM_REG_POST_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3c400400, SIMD_LDR_IMM_REG_POST_8: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/LDR (immediate, SIMD&FP) 8-bit'
      case 0x3c400400: packet->A64InstrIndex = SIMD_LDR_IMM_REG_POST_8;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38400400, LDRB_IMM_REG_POST: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/LDRB (immediate) Post-index'
      case 0x38400400: packet->A64InstrIndex = LDRB_IMM_REG_POST;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78400400, LDRH_IMM_REG_POST: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/LDRH (immediate) Post-index'
      case 0x78400400: packet->A64InstrIndex = LDRH_IMM_REG_POST;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38c00400, LDRSB_IMM_REG_POST_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/LDRSB (immediate) 32-bit'
      case 0x38c00400: packet->A64InstrIndex = LDRSB_IMM_REG_POST_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38800400, LDRSB_IMM_REG_POST_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/LDRSB (immediate) 64-bit'
      case 0x38800400: packet->A64InstrIndex = LDRSB_IMM_REG_POST_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78c00400, LDRSH_IMM_REG_POST_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/LDRSH (immediate) 32-bit'
      case 0x78c00400: packet->A64InstrIndex = LDRSH_IMM_REG_POST_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78800400, LDRSH_IMM_REG_POST_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/LDRSH (immediate) 64-bit'
      case 0x78800400: packet->A64InstrIndex = LDRSH_IMM_REG_POST_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb8800400, LDRSW_IMM_REG_POST: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/LDRSW (immediate) Post-index'
      case 0xb8800400: packet->A64InstrIndex = LDRSW_IMM_REG_POST;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb8000400, STR_IMM_REG_POST_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/STR (immediate) 32-bit'
      case 0xb8000400: packet->A64InstrIndex = STR_IMM_REG_POST_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xf8000400, STR_IMM_REG_POST_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/STR (immediate) 64-bit'
      case 0xf8000400: packet->A64InstrIndex = STR_IMM_REG_POST_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3c800400, SIMD_STR_IMM_REG_POST_8_128: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/STR (immediate, SIMD&FP) 128-bit'
      case 0x3c800400: packet->A64InstrIndex = SIMD_STR_IMM_REG_POST_8_128;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x7c000400, SIMD_STR_IMM_REG_POST_16: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/STR (immediate, SIMD&FP) 16-bit'
      case 0x7c000400: packet->A64InstrIndex = SIMD_STR_IMM_REG_POST_16;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xbc000400, SIMD_STR_IMM_REG_POST_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/STR (immediate, SIMD&FP) 32-bit'
      case 0xbc000400: packet->A64InstrIndex = SIMD_STR_IMM_REG_POST_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xfc000400, SIMD_STR_IMM_REG_POST_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/STR (immediate, SIMD&FP) 64-bit'
      case 0xfc000400: packet->A64InstrIndex = SIMD_STR_IMM_REG_POST_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3c000400, SIMD_STR_IMM_REG_POST_8: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/STR (immediate, SIMD&FP) 8-bit'
      case 0x3c000400: packet->A64InstrIndex = SIMD_STR_IMM_REG_POST_8;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38000400, STRB_IMM_REG_POST: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/STRB (immediate) Post-index'
      case 0x38000400: packet->A64InstrIndex = STRB_IMM_REG_POST;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78000400, STRH_IMM_REG_POST: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate post-indexed)/STRH (immediate) Post-index'
      case 0x78000400: packet->A64InstrIndex = STRH_IMM_REG_POST;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb8400c00, LDR_IMM_REG_PRE_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/LDR (immediate) 32-bit'
      case 0xb8400c00: packet->A64InstrIndex = LDR_IMM_REG_PRE_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xf8400c00, LDR_IMM_REG_PRE_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/LDR (immediate) 64-bit'
      case 0xf8400c00: packet->A64InstrIndex = LDR_IMM_REG_PRE_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3cc00c00, SIMD_LDR_IMM_REG_PRE_8_128: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/LDR (immediate, SIMD&FP) 128-bit'
      case 0x3cc00c00: packet->A64InstrIndex = SIMD_LDR_IMM_REG_PRE_8_128;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x7c400c00, SIMD_LDR_IMM_REG_PRE_16: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/LDR (immediate, SIMD&FP) 16-bit'
      case 0x7c400c00: packet->A64InstrIndex = SIMD_LDR_IMM_REG_PRE_16;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xbc400c00, SIMD_LDR_IMM_REG_PRE_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/LDR (immediate, SIMD&FP) 32-bit'
      case 0xbc400c00: packet->A64InstrIndex = SIMD_LDR_IMM_REG_PRE_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xfc400c00, SIMD_LDR_IMM_REG_PRE_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/LDR (immediate, SIMD&FP) 64-bit'
      case 0xfc400c00: packet->A64InstrIndex = SIMD_LDR_IMM_REG_PRE_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3c400c00, SIMD_LDR_IMM_REG_PRE_8: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/LDR (immediate, SIMD&FP) 8-bit'
      case 0x3c400c00: packet->A64InstrIndex = SIMD_LDR_IMM_REG_PRE_8;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38400c00, LDRB_IMM_REG_PRE: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/LDRB (immediate) Pre-index'
      case 0x38400c00: packet->A64InstrIndex = LDRB_IMM_REG_PRE;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78400c00, LDRH_IMM_REG_PRE: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/LDRH (immediate) Pre-index'
      case 0x78400c00: packet->A64InstrIndex = LDRH_IMM_REG_PRE;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38c00c00, LDRSB_IMM_REG_PRE_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/LDRSB (immediate) 32-bit'
      case 0x38c00c00: packet->A64InstrIndex = LDRSB_IMM_REG_PRE_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38800c00, LDRSB_IMM_REG_PRE_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/LDRSB (immediate) 64-bit'
      case 0x38800c00: packet->A64InstrIndex = LDRSB_IMM_REG_PRE_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78c00c00, LDRSH_IMM_REG_PRE_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/LDRSH (immediate) 32-bit'
      case 0x78c00c00: packet->A64InstrIndex = LDRSH_IMM_REG_PRE_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78800c00, LDRSH_IMM_REG_PRE_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/LDRSH (immediate) 64-bit'
      case 0x78800c00: packet->A64InstrIndex = LDRSH_IMM_REG_PRE_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb8800c00, LDRSW_IMM_REG_PRE: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/LDRSW (immediate) Pre-index'
      case 0xb8800c00: packet->A64InstrIndex = LDRSW_IMM_REG_PRE;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb8000c00, STR_IMM_REG_PRE_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/STR (immediate) 32-bit'
      case 0xb8000c00: packet->A64InstrIndex = STR_IMM_REG_PRE_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xf8000c00, STR_IMM_REG_PRE_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/STR (immediate) 64-bit'
      case 0xf8000c00: packet->A64InstrIndex = STR_IMM_REG_PRE_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3c800c00, SIMD_STR_IMM_REG_PRE_8_128: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/STR (immediate, SIMD&FP) 128-bit'
      case 0x3c800c00: packet->A64InstrIndex = SIMD_STR_IMM_REG_PRE_8_128;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x7c000c00, SIMD_STR_IMM_REG_PRE_16: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/STR (immediate, SIMD&FP) 16-bit'
      case 0x7c000c00: packet->A64InstrIndex = SIMD_STR_IMM_REG_PRE_16;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xbc000c00, SIMD_STR_IMM_REG_PRE_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/STR (immediate, SIMD&FP) 32-bit'
      case 0xbc000c00: packet->A64InstrIndex = SIMD_STR_IMM_REG_PRE_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xfc000c00, SIMD_STR_IMM_REG_PRE_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/STR (immediate, SIMD&FP) 64-bit'
      case 0xfc000c00: packet->A64InstrIndex = SIMD_STR_IMM_REG_PRE_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3c000c00, SIMD_STR_IMM_REG_PRE_8: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/STR (immediate, SIMD&FP) 8-bit'
      case 0x3c000c00: packet->A64InstrIndex = SIMD_STR_IMM_REG_PRE_8;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38000c00, STRB_IMM_REG_PRE: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/STRB (immediate) Pre-index'
      case 0x38000c00: packet->A64InstrIndex = STRB_IMM_REG_PRE;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78000c00, STRH_IMM_REG_PRE: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (immediate pre-indexed)/STRH (immediate) Pre-index'
      case 0x78000c00: packet->A64InstrIndex = STRH_IMM_REG_PRE;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb8600800, LDR_REG_OFF_32: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/LDR (register) 32-bit'
      case 0xb8600800: packet->A64InstrIndex = LDR_REG_OFF_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xf8600800, LDR_REG_OFF_64: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/LDR (register) 64-bit'
      case 0xf8600800: packet->A64InstrIndex = LDR_REG_OFF_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3ce00800, SIMD_LDR_REG_OFF_8_128: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/LDR (register, SIMD&FP) 128-bit'
      case 0x3ce00800: packet->A64InstrIndex = SIMD_LDR_REG_OFF_8_128;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x7c600800, SIMD_LDR_REG_OFF_16: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/LDR (register, SIMD&FP) 16-bit'
      case 0x7c600800: packet->A64InstrIndex = SIMD_LDR_REG_OFF_16;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xbc600800, SIMD_LDR_REG_OFF_32: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/LDR (register, SIMD&FP) 32-bit'
      case 0xbc600800: packet->A64InstrIndex = SIMD_LDR_REG_OFF_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xfc600800, SIMD_LDR_REG_OFF_64: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/LDR (register, SIMD&FP) 64-bit'
      case 0xfc600800: packet->A64InstrIndex = SIMD_LDR_REG_OFF_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3c600800, SIMD_LDR_REG_OFF_8: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/LDR (register, SIMD&FP) 8-bit'
      case 0x3c600800: packet->A64InstrIndex = SIMD_LDR_REG_OFF_8;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38600800, LDRB_REG_OFF: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/LDRB (register) -'
      case 0x38600800: packet->A64InstrIndex = LDRB_REG_OFF;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78600800, LDRH_REG_OFF: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/LDRH (register) -'
      case 0x78600800: packet->A64InstrIndex = LDRH_REG_OFF;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38e00800, LDRSB_REG_OFF_32: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/LDRSB (register) 32-bit'
      case 0x38e00800: packet->A64InstrIndex = LDRSB_REG_OFF_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38a00800, LDRSB_REG_OFF_64: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/LDRSB (register) 64-bit'
      case 0x38a00800: packet->A64InstrIndex = LDRSB_REG_OFF_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78e00800, LDRSH_REG_OFF_32: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/LDRSH (register) 32-bit'
      case 0x78e00800: packet->A64InstrIndex = LDRSH_REG_OFF_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78a00800, LDRSH_REG_OFF_64: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/LDRSH (register) 64-bit'
      case 0x78a00800: packet->A64InstrIndex = LDRSH_REG_OFF_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb8a00800, LDRSW_REG_OFF: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/LDRSW (register) -'
      case 0xb8a00800: packet->A64InstrIndex = LDRSW_REG_OFF;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xf8a00800, PRFM_REG_OFF: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/PRFM (register) -'
      case 0xf8a00800: packet->A64InstrIndex = PRFM_REG_OFF;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb8200800, STR_REG_OFF_32: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/STR (register) 32-bit'
      case 0xb8200800: packet->A64InstrIndex = STR_REG_OFF_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xf8200800, STR_REG_OFF_64: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/STR (register) 64-bit'
      case 0xf8200800: packet->A64InstrIndex = STR_REG_OFF_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3ca00800, SIMD_STR_REG_OFF_8_128: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/STR (register, SIMD&FP) 128-bit'
      case 0x3ca00800: packet->A64InstrIndex = SIMD_STR_REG_OFF_8_128;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x7c200800, SIMD_STR_REG_OFF_16: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/STR (register, SIMD&FP) 16-bit'
      case 0x7c200800: packet->A64InstrIndex = SIMD_STR_REG_OFF_16;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xbc200800, SIMD_STR_REG_OFF_32: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/STR (register, SIMD&FP) 32-bit'
      case 0xbc200800: packet->A64InstrIndex = SIMD_STR_REG_OFF_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xfc200800, SIMD_STR_REG_OFF_64: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/STR (register, SIMD&FP) 64-bit'
      case 0xfc200800: packet->A64InstrIndex = SIMD_STR_REG_OFF_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3c200800, SIMD_STR_REG_OFF_8: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/STR (register, SIMD&FP) 8-bit'
      case 0x3c200800: packet->A64InstrIndex = SIMD_STR_REG_OFF_8;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38200800, STRB_REG_OFF: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/STRB (register) -'
      case 0x38200800: packet->A64InstrIndex = STRB_REG_OFF;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78200800, STRH_REG_OFF: ' size=31,30 V=26 opc=23,22 Rm=20,16 option=15,13 S=12 Rn=9,5 Rt=4,0' - 'Load/store register (register offset)/STRH (register) -'
      case 0x78200800: packet->A64InstrIndex = STRH_REG_OFF;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->S = (packet->Opcode >> 12) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb8400800, LDTR_REG_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unprivileged)/LDTR 32-bit'
      case 0xb8400800: packet->A64InstrIndex = LDTR_REG_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xf8400800, LDTR_REG_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unprivileged)/LDTR 64-bit'
      case 0xf8400800: packet->A64InstrIndex = LDTR_REG_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38400800, LDTRB_REG: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unprivileged)/LDTRB -'
      case 0x38400800: packet->A64InstrIndex = LDTRB_REG;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78400800, LDTRH_REG: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unprivileged)/LDTRH -'
      case 0x78400800: packet->A64InstrIndex = LDTRH_REG;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38c00800, LDTRSB_REG_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unprivileged)/LDTRSB 32-bit'
      case 0x38c00800: packet->A64InstrIndex = LDTRSB_REG_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38800800, LDTRSB_REG_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unprivileged)/LDTRSB 64-bit'
      case 0x38800800: packet->A64InstrIndex = LDTRSB_REG_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78c00800, LDTRSH_REG_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unprivileged)/LDTRSH 32-bit'
      case 0x78c00800: packet->A64InstrIndex = LDTRSH_REG_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78800800, LDTRSH_REG_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unprivileged)/LDTRSH 64-bit'
      case 0x78800800: packet->A64InstrIndex = LDTRSH_REG_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb8800800, LDTRSW_REG: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unprivileged)/LDTRSW -'
      case 0xb8800800: packet->A64InstrIndex = LDTRSW_REG;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb8000800, STTR_REG_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unprivileged)/STTR 32-bit'
      case 0xb8000800: packet->A64InstrIndex = STTR_REG_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xf8000800, STTR_REG_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unprivileged)/STTR 64-bit'
      case 0xf8000800: packet->A64InstrIndex = STTR_REG_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38000800, STTRB_REG: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unprivileged)/STTRB -'
      case 0x38000800: packet->A64InstrIndex = STTRB_REG;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78000800, STTRH_REG: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unprivileged)/STTRH -'
      case 0x78000800: packet->A64InstrIndex = STTRH_REG;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3cc00000, SIMD_LDUR_IMM_REG_8_128: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/LDUR (SIMD&FP) 128-bit'
      case 0x3cc00000: packet->A64InstrIndex = SIMD_LDUR_IMM_REG_8_128;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x7c400000, SIMD_LDUR_IMM_REG_16: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/LDUR (SIMD&FP) 16-bit'
      case 0x7c400000: packet->A64InstrIndex = SIMD_LDUR_IMM_REG_16;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xbc400000, SIMD_LDUR_IMM_REG_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/LDUR (SIMD&FP) 32-bit'
      case 0xbc400000: packet->A64InstrIndex = SIMD_LDUR_IMM_REG_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xfc400000, SIMD_LDUR_IMM_REG_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/LDUR (SIMD&FP) 64-bit'
      case 0xfc400000: packet->A64InstrIndex = SIMD_LDUR_IMM_REG_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3c400000, SIMD_LDUR_IMM_REG_8: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/LDUR (SIMD&FP) 8-bit'
      case 0x3c400000: packet->A64InstrIndex = SIMD_LDUR_IMM_REG_8;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb8400000, LDUR_IMM_REG_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/LDUR 32-bit'
      case 0xb8400000: packet->A64InstrIndex = LDUR_IMM_REG_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xf8400000, LDUR_IMM_REG_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/LDUR 64-bit'
      case 0xf8400000: packet->A64InstrIndex = LDUR_IMM_REG_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38400000, LDURB_IMM_REG: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/LDURB -'
      case 0x38400000: packet->A64InstrIndex = LDURB_IMM_REG;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78400000, LDURH_IMM_REG: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/LDURH -'
      case 0x78400000: packet->A64InstrIndex = LDURH_IMM_REG;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38c00000, LDURSB_IMM_REG_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/LDURSB 32-bit'
      case 0x38c00000: packet->A64InstrIndex = LDURSB_IMM_REG_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38800000, LDURSB_IMM_REG_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/LDURSB 64-bit'
      case 0x38800000: packet->A64InstrIndex = LDURSB_IMM_REG_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78c00000, LDURSH_IMM_REG_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/LDURSH 32-bit'
      case 0x78c00000: packet->A64InstrIndex = LDURSH_IMM_REG_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78800000, LDURSH_IMM_REG_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/LDURSH 64-bit'
      case 0x78800000: packet->A64InstrIndex = LDURSH_IMM_REG_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb8800000, LDURSW_IMM_REG: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/LDURSW -'
      case 0xb8800000: packet->A64InstrIndex = LDURSW_IMM_REG;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xf8800000, PRFUM_IMM_REG: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/PRFUM -'
      case 0xf8800000: packet->A64InstrIndex = PRFUM_IMM_REG;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3c800000, SIMD_STUR_IMM_REG_8_128: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/STUR (SIMD&FP) 128-bit'
      case 0x3c800000: packet->A64InstrIndex = SIMD_STUR_IMM_REG_8_128;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x7c000000, SIMD_STUR_IMM_REG_16: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/STUR (SIMD&FP) 16-bit'
      case 0x7c000000: packet->A64InstrIndex = SIMD_STUR_IMM_REG_16;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xbc000000, SIMD_STUR_IMM_REG_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/STUR (SIMD&FP) 32-bit'
      case 0xbc000000: packet->A64InstrIndex = SIMD_STUR_IMM_REG_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xfc000000, SIMD_STUR_IMM_REG_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/STUR (SIMD&FP) 64-bit'
      case 0xfc000000: packet->A64InstrIndex = SIMD_STUR_IMM_REG_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3c000000, SIMD_STUR_IMM_REG_8: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/STUR (SIMD&FP) 8-bit'
      case 0x3c000000: packet->A64InstrIndex = SIMD_STUR_IMM_REG_8;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb8000000, STUR_IMM_REG_32: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/STUR 32-bit'
      case 0xb8000000: packet->A64InstrIndex = STUR_IMM_REG_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xf8000000, STUR_IMM_REG_64: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/STUR 64-bit'
      case 0xf8000000: packet->A64InstrIndex = STUR_IMM_REG_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x38000000, STURB_IMM_REG: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/STURB -'
      case 0x38000000: packet->A64InstrIndex = STURB_IMM_REG;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x78000000, STURH_IMM_REG: ' size=31,30 V=26 opc=23,22 imm9=20,12 Rn=9,5 Rt=4,0' - 'Load/store register (unscaled immediate)/STURH -'
      case 0x78000000: packet->A64InstrIndex = STURH_IMM_REG;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm9 = (packet->Opcode >> 12) & 0x1ff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xffe08400) {
      // 0x6e000400, SIMD_INS_ELEM: ' Q=30 op=29 imm5=20,16 imm4=14,11 Rn=9,5 Rd=4,0' - 'Advanced SIMD copy/INS (element) -'
      case 0x6e000400: packet->A64InstrIndex = SIMD_INS_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op = (packet->Opcode >> 29) & 0x1;
          packet->imm5 = (packet->Opcode >> 16) & 0x1f;
          packet->imm4 = (packet->Opcode >> 11) & 0xf;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xfff00000) {
      // 0xd5300000, MRS: ' L=21 op0=20,19 op1=18,16 CRn=15,12 CRm=11,8 op2=7,5 Rt=4,0' - 'System/MRS -'
      case 0xd5300000: packet->A64InstrIndex = MRS;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->op0 = (packet->Opcode >> 19) & 0x3;
          packet->op1 = (packet->Opcode >> 16) & 0x7;
          packet->CRn = (packet->Opcode >> 12) & 0xf;
          packet->CRm = (packet->Opcode >> 8) & 0xf;
          packet->op2 = (packet->Opcode >> 5) & 0x7;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xd5100000, MSR_REG: ' L=21 op0=20,19 op1=18,16 CRn=15,12 CRm=11,8 op2=7,5 Rt=4,0' - 'System/MSR (register) -'
      case 0xd5100000: packet->A64InstrIndex = MSR_REG;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->op0 = (packet->Opcode >> 19) & 0x3;
          packet->op1 = (packet->Opcode >> 16) & 0x7;
          packet->CRn = (packet->Opcode >> 12) & 0xf;
          packet->CRm = (packet->Opcode >> 8) & 0xf;
          packet->op2 = (packet->Opcode >> 5) & 0x7;
          packet->Rt = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbf00f400) {
      // 0x2f000000, SIMD_MLA_VEC_ELEM: ' Q=30 U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD vector x indexed element/MLA (by element) -'
      case 0x2f000000: packet->A64InstrIndex = SIMD_MLA_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f004000, SIMD_MLS_VEC_ELEM: ' Q=30 U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD vector x indexed element/MLS (by element) -'
      case 0x2f004000: packet->A64InstrIndex = SIMD_MLS_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f008000, SIMD_MUL_VEC_ELEM: ' Q=30 U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD vector x indexed element/MUL (by element) -'
      case 0x0f008000: packet->A64InstrIndex = SIMD_MUL_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f002000, SIMD_SMLAL_VEC_ELEM: ' Q=30 U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD vector x indexed element/SMLAL, SMLAL2 (by element) -'
      case 0x0f002000: packet->A64InstrIndex = SIMD_SMLAL_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f006000, SIMD_SMLSL_VEC_ELEM: ' Q=30 U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD vector x indexed element/SMLSL, SMLSL2 (by element) -'
      case 0x0f006000: packet->A64InstrIndex = SIMD_SMLSL_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f00a000, SIMD_SMULL_VEC_ELEM: ' Q=30 U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD vector x indexed element/SMULL, SMULL2 (by element) -'
      case 0x0f00a000: packet->A64InstrIndex = SIMD_SMULL_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f003000, SIMD_SQDMLAL_VEC_VEC_ELEM: ' Q=30 U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD vector x indexed element/SQDMLAL, SQDMLAL2 (by element) Vector'
      case 0x0f003000: packet->A64InstrIndex = SIMD_SQDMLAL_VEC_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f007000, SIMD_SQDMLSL_VEC_VEC_ELEM: ' Q=30 U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD vector x indexed element/SQDMLSL, SQDMLSL2 (by element) Vector'
      case 0x0f007000: packet->A64InstrIndex = SIMD_SQDMLSL_VEC_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f00c000, SIMD_SQDMULH_VEC_VEC_ELEM: ' Q=30 U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD vector x indexed element/SQDMULH (by element) Vector'
      case 0x0f00c000: packet->A64InstrIndex = SIMD_SQDMULH_VEC_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f00b000, SIMD_SQDMULL_VEC_VEC_ELEM: ' Q=30 U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD vector x indexed element/SQDMULL, SQDMULL2 (by element) Vector'
      case 0x0f00b000: packet->A64InstrIndex = SIMD_SQDMULL_VEC_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0f00d000, SIMD_SQRDMULH_VEC_VEC_ELEM: ' Q=30 U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD vector x indexed element/SQRDMULH (by element) Vector'
      case 0x0f00d000: packet->A64InstrIndex = SIMD_SQRDMULH_VEC_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f002000, SIMD_UMLAL_VEC_ELEM: ' Q=30 U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD vector x indexed element/UMLAL, UMLAL2 (by element) -'
      case 0x2f002000: packet->A64InstrIndex = SIMD_UMLAL_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f006000, SIMD_UMLSL_VEC_ELEM: ' Q=30 U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD vector x indexed element/UMLSL, UMLSL2 (by element) -'
      case 0x2f006000: packet->A64InstrIndex = SIMD_UMLSL_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2f00a000, SIMD_UMULL_VEC_ELEM: ' Q=30 U=29 size=23,22 L=21 M=20 Rm=19,16 opcode=15,12 H=11 Rn=9,5 Rd=4,0' - 'Advanced SIMD vector x indexed element/UMULL, UMULL2 (by element) -'
      case 0x2f00a000: packet->A64InstrIndex = SIMD_UMULL_VEC_ELEM;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->U = (packet->Opcode >> 29) & 0x1;
          packet->size = (packet->Opcode >> 22) & 0x3;
          packet->L = (packet->Opcode >> 21) & 0x1;
          packet->M = (packet->Opcode >> 20) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0xf;
          packet->opcode = (packet->Opcode >> 12) & 0xf;
          packet->H = (packet->Opcode >> 11) & 0x1;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xbfe08400) {
      // 0x2e000000, SIMD_EXT: ' Q=30 op2=23,22 Rm=20,16 imm4=14,10 Rn=9,5 Rd=4,0' - 'Advanced SIMD extract/EXT -'
      case 0x2e000000: packet->A64InstrIndex = SIMD_EXT;
          packet->Q = (packet->Opcode >> 30) & 0x1;
          packet->op2 = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm4 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xffe08000) {
      // 0x1b000000, MADD_32: ' sf=31 op54=30,29 op31=23,21 Rm=20,16 o0=15 Ra=14,10 Rn=9,5 Rd=4,0' - 'Data-processing (3 source)/MADD 32-bit'
      case 0x1b000000: packet->A64InstrIndex = MADD_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op54 = (packet->Opcode >> 29) & 0x3;
          packet->op31 = (packet->Opcode >> 21) & 0x7;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Ra = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9b000000, MADD_64: ' sf=31 op54=30,29 op31=23,21 Rm=20,16 o0=15 Ra=14,10 Rn=9,5 Rd=4,0' - 'Data-processing (3 source)/MADD 64-bit'
      case 0x9b000000: packet->A64InstrIndex = MADD_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op54 = (packet->Opcode >> 29) & 0x3;
          packet->op31 = (packet->Opcode >> 21) & 0x7;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Ra = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1b008000, MSUB_32: ' sf=31 op54=30,29 op31=23,21 Rm=20,16 o0=15 Ra=14,10 Rn=9,5 Rd=4,0' - 'Data-processing (3 source)/MSUB 32-bit'
      case 0x1b008000: packet->A64InstrIndex = MSUB_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op54 = (packet->Opcode >> 29) & 0x3;
          packet->op31 = (packet->Opcode >> 21) & 0x7;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Ra = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9b008000, MSUB_64: ' sf=31 op54=30,29 op31=23,21 Rm=20,16 o0=15 Ra=14,10 Rn=9,5 Rd=4,0' - 'Data-processing (3 source)/MSUB 64-bit'
      case 0x9b008000: packet->A64InstrIndex = MSUB_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op54 = (packet->Opcode >> 29) & 0x3;
          packet->op31 = (packet->Opcode >> 21) & 0x7;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Ra = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9b200000, SMADDL: ' sf=31 op54=30,29 op31=23,21 Rm=20,16 o0=15 Ra=14,10 Rn=9,5 Rd=4,0' - 'Data-processing (3 source)/SMADDL -'
      case 0x9b200000: packet->A64InstrIndex = SMADDL;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op54 = (packet->Opcode >> 29) & 0x3;
          packet->op31 = (packet->Opcode >> 21) & 0x7;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Ra = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9b208000, SMSUBL: ' sf=31 op54=30,29 op31=23,21 Rm=20,16 o0=15 Ra=14,10 Rn=9,5 Rd=4,0' - 'Data-processing (3 source)/SMSUBL -'
      case 0x9b208000: packet->A64InstrIndex = SMSUBL;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op54 = (packet->Opcode >> 29) & 0x3;
          packet->op31 = (packet->Opcode >> 21) & 0x7;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Ra = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9b400000, SMULH: ' sf=31 op54=30,29 op31=23,21 Rm=20,16 o0=15 Ra=14,10 Rn=9,5 Rd=4,0' - 'Data-processing (3 source)/SMULH -'
      case 0x9b400000: packet->A64InstrIndex = SMULH;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op54 = (packet->Opcode >> 29) & 0x3;
          packet->op31 = (packet->Opcode >> 21) & 0x7;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Ra = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9ba00000, UMADDL: ' sf=31 op54=30,29 op31=23,21 Rm=20,16 o0=15 Ra=14,10 Rn=9,5 Rd=4,0' - 'Data-processing (3 source)/UMADDL -'
      case 0x9ba00000: packet->A64InstrIndex = UMADDL;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op54 = (packet->Opcode >> 29) & 0x3;
          packet->op31 = (packet->Opcode >> 21) & 0x7;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Ra = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9ba08000, UMSUBL: ' sf=31 op54=30,29 op31=23,21 Rm=20,16 o0=15 Ra=14,10 Rn=9,5 Rd=4,0' - 'Data-processing (3 source)/UMSUBL -'
      case 0x9ba08000: packet->A64InstrIndex = UMSUBL;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op54 = (packet->Opcode >> 29) & 0x3;
          packet->op31 = (packet->Opcode >> 21) & 0x7;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Ra = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x9bc00000, UMULH: ' sf=31 op54=30,29 op31=23,21 Rm=20,16 o0=15 Ra=14,10 Rn=9,5 Rd=4,0' - 'Data-processing (3 source)/UMULH -'
      case 0x9bc00000: packet->A64InstrIndex = UMULH;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op54 = (packet->Opcode >> 29) & 0x3;
          packet->op31 = (packet->Opcode >> 21) & 0x7;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Ra = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x13800000, EXTR_32: ' sf=31 op21=30,29 N=22 o0=21 Rm=20,16 imms=15,10 Rn=9,5 Rd=4,0' - 'Extract/EXTR 32-bit'
      case 0x13800000: packet->A64InstrIndex = EXTR_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op21 = (packet->Opcode >> 29) & 0x3;
          packet->N = (packet->Opcode >> 22) & 0x1;
          packet->o0 = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imms = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1f400000, FMADD_FROM_DP: ' M=31 S=29 type=23,22 o1=21 Rm=20,16 o0=15 Ra=14,10 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (3 source)/FMADD Double-precision'
      case 0x1f400000: packet->A64InstrIndex = FMADD_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Ra = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1f000000, FMADD_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 o1=21 Rm=20,16 o0=15 Ra=14,10 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (3 source)/FMADD Single-precision'
      case 0x1f000000: packet->A64InstrIndex = FMADD_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Ra = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1f408000, FMSUB_FROM_DP: ' M=31 S=29 type=23,22 o1=21 Rm=20,16 o0=15 Ra=14,10 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (3 source)/FMSUB Double-precision'
      case 0x1f408000: packet->A64InstrIndex = FMSUB_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Ra = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1f008000, FMSUB_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 o1=21 Rm=20,16 o0=15 Ra=14,10 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (3 source)/FMSUB Single-precision'
      case 0x1f008000: packet->A64InstrIndex = FMSUB_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Ra = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1f600000, FNMADD_FROM_DP: ' M=31 S=29 type=23,22 o1=21 Rm=20,16 o0=15 Ra=14,10 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (3 source)/FNMADD Double-precision'
      case 0x1f600000: packet->A64InstrIndex = FNMADD_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Ra = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1f200000, FNMADD_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 o1=21 Rm=20,16 o0=15 Ra=14,10 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (3 source)/FNMADD Single-precision'
      case 0x1f200000: packet->A64InstrIndex = FNMADD_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Ra = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1f608000, FNMSUB_FROM_DP: ' M=31 S=29 type=23,22 o1=21 Rm=20,16 o0=15 Ra=14,10 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (3 source)/FNMSUB Double-precision'
      case 0x1f608000: packet->A64InstrIndex = FNMSUB_FROM_DP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Ra = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x1f208000, FNMSUB_SINGLE_FROM_SP: ' M=31 S=29 type=23,22 o1=21 Rm=20,16 o0=15 Ra=14,10 Rn=9,5 Rd=4,0' - 'Floating-point data-processing (3 source)/FNMSUB Single-precision'
      case 0x1f208000: packet->A64InstrIndex = FNMSUB_SINGLE_FROM_SP;
          packet->M = (packet->Opcode >> 31) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->type = (packet->Opcode >> 22) & 0x3;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Ra = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x88c08000, LDAR_32: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/LDAR 32-bit'
      case 0x88c08000: packet->A64InstrIndex = LDAR_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xc8c08000, LDAR_64: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/LDAR 64-bit'
      case 0xc8c08000: packet->A64InstrIndex = LDAR_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x08c08000, LDARB: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/LDARB -'
      case 0x08c08000: packet->A64InstrIndex = LDARB;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x48c08000, LDARH: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/LDARH -'
      case 0x48c08000: packet->A64InstrIndex = LDARH;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x88608000, LDAXP_32: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/LDAXP 32-bit'
      case 0x88608000: packet->A64InstrIndex = LDAXP_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xc8608000, LDAXP_64: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/LDAXP 64-bit'
      case 0xc8608000: packet->A64InstrIndex = LDAXP_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x88408000, LDAXR_32: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/LDAXR 32-bit'
      case 0x88408000: packet->A64InstrIndex = LDAXR_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xc8408000, LDAXR_64: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/LDAXR 64-bit'
      case 0xc8408000: packet->A64InstrIndex = LDAXR_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x08408000, LDAXRB: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/LDAXRB -'
      case 0x08408000: packet->A64InstrIndex = LDAXRB;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x48408000, LDAXRH: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/LDAXRH -'
      case 0x48408000: packet->A64InstrIndex = LDAXRH;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x88600000, LDXP_32: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/LDXP 32-bit'
      case 0x88600000: packet->A64InstrIndex = LDXP_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xc8600000, LDXP_64: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/LDXP 64-bit'
      case 0xc8600000: packet->A64InstrIndex = LDXP_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x88400000, LDXR_32: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/LDXR 32-bit'
      case 0x88400000: packet->A64InstrIndex = LDXR_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xc8400000, LDXR_64: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/LDXR 64-bit'
      case 0xc8400000: packet->A64InstrIndex = LDXR_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x08400000, LDXRB: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/LDXRB -'
      case 0x08400000: packet->A64InstrIndex = LDXRB;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x48400000, LDXRH: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/LDXRH -'
      case 0x48400000: packet->A64InstrIndex = LDXRH;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x88808000, STLR_32: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/STLR 32-bit'
      case 0x88808000: packet->A64InstrIndex = STLR_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xc8808000, STLR_64: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/STLR 64-bit'
      case 0xc8808000: packet->A64InstrIndex = STLR_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x08808000, STLRB: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/STLRB -'
      case 0x08808000: packet->A64InstrIndex = STLRB;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x48808000, STLRH: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/STLRH -'
      case 0x48808000: packet->A64InstrIndex = STLRH;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x88208000, STLXP_32: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/STLXP 32-bit'
      case 0x88208000: packet->A64InstrIndex = STLXP_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xc8208000, STLXP_64: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/STLXP 64-bit'
      case 0xc8208000: packet->A64InstrIndex = STLXP_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x88008000, STLXR_32: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/STLXR 32-bit'
      case 0x88008000: packet->A64InstrIndex = STLXR_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xc8008000, STLXR_64: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/STLXR 64-bit'
      case 0xc8008000: packet->A64InstrIndex = STLXR_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x08008000, STLXRB: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/STLXRB -'
      case 0x08008000: packet->A64InstrIndex = STLXRB;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x48008000, STLXRH: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/STLXRH -'
      case 0x48008000: packet->A64InstrIndex = STLXRH;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x88200000, STXP_32: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/STXP 32-bit'
      case 0x88200000: packet->A64InstrIndex = STXP_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xc8200000, STXP_64: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/STXP 64-bit'
      case 0xc8200000: packet->A64InstrIndex = STXP_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x88000000, STXR_32: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/STXR 32-bit'
      case 0x88000000: packet->A64InstrIndex = STXR_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xc8000000, STXR_64: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/STXR 64-bit'
      case 0xc8000000: packet->A64InstrIndex = STXR_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x08000000, STXRB: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/STXRB -'
      case 0x08000000: packet->A64InstrIndex = STXRB;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x48000000, STXRH: ' size=31,30 o2=23 L=22 o1=21 Rs=20,16 o0=15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store exclusive/STXRH -'
      case 0x48000000: packet->A64InstrIndex = STXRH;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->o2 = (packet->Opcode >> 23) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->o1 = (packet->Opcode >> 21) & 0x1;
          packet->Rs = (packet->Opcode >> 16) & 0x1f;
          packet->o0 = (packet->Opcode >> 15) & 0x1;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xffe00000) {
      // 0x0b200000, ADD_REG_32: ' sf=31 op=30 S=29 Rm=20,16 option=15,13 imm3=12,10 Rn=9,5 Rd=4,0' - 'Add/subtract (extended register)/ADD (extended register) 32-bit'
      case 0x0b200000: packet->A64InstrIndex = ADD_REG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->imm3 = (packet->Opcode >> 10) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x8b200000, ADD_REG_64: ' sf=31 op=30 S=29 Rm=20,16 option=15,13 imm3=12,10 Rn=9,5 Rd=4,0' - 'Add/subtract (extended register)/ADD (extended register) 64-bit'
      case 0x8b200000: packet->A64InstrIndex = ADD_REG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->imm3 = (packet->Opcode >> 10) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2b200000, ADDS_REG_32: ' sf=31 op=30 S=29 Rm=20,16 option=15,13 imm3=12,10 Rn=9,5 Rd=4,0' - 'Add/subtract (extended register)/ADDS (extended register) 32-bit'
      case 0x2b200000: packet->A64InstrIndex = ADDS_REG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->imm3 = (packet->Opcode >> 10) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xab200000, ADDS_REG_64: ' sf=31 op=30 S=29 Rm=20,16 option=15,13 imm3=12,10 Rn=9,5 Rd=4,0' - 'Add/subtract (extended register)/ADDS (extended register) 64-bit'
      case 0xab200000: packet->A64InstrIndex = ADDS_REG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->imm3 = (packet->Opcode >> 10) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x4b200000, SUB_REG_32: ' sf=31 op=30 S=29 Rm=20,16 option=15,13 imm3=12,10 Rn=9,5 Rd=4,0' - 'Add/subtract (extended register)/SUB (extended register) 32-bit'
      case 0x4b200000: packet->A64InstrIndex = SUB_REG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->imm3 = (packet->Opcode >> 10) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xcb200000, SUB_REG_64: ' sf=31 op=30 S=29 Rm=20,16 option=15,13 imm3=12,10 Rn=9,5 Rd=4,0' - 'Add/subtract (extended register)/SUB (extended register) 64-bit'
      case 0xcb200000: packet->A64InstrIndex = SUB_REG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->imm3 = (packet->Opcode >> 10) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x6b200000, SUBS_REG_32: ' sf=31 op=30 S=29 Rm=20,16 option=15,13 imm3=12,10 Rn=9,5 Rd=4,0' - 'Add/subtract (extended register)/SUBS (extended register) 32-bit'
      case 0x6b200000: packet->A64InstrIndex = SUBS_REG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->imm3 = (packet->Opcode >> 10) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xeb200000, SUBS_REG_64: ' sf=31 op=30 S=29 Rm=20,16 option=15,13 imm3=12,10 Rn=9,5 Rd=4,0' - 'Add/subtract (extended register)/SUBS (extended register) 64-bit'
      case 0xeb200000: packet->A64InstrIndex = SUBS_REG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->option = (packet->Opcode >> 13) & 0x7;
          packet->imm3 = (packet->Opcode >> 10) & 0x7;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x93c00000, EXTR_64: ' sf=31 op21=30,29 N=22 o0=21 Rm=20,16 imms=15,10 Rn=9,5 Rd=4,0' - 'Extract/EXTR 64-bit'
      case 0x93c00000: packet->A64InstrIndex = EXTR_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op21 = (packet->Opcode >> 29) & 0x3;
          packet->N = (packet->Opcode >> 22) & 0x1;
          packet->o0 = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imms = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xffc00000) {
      // 0x33000000, BFM_32: ' sf=31 opc=30,29 N=22 immr=21,16 imms=15,10 Rn=9,5 Rd=4,0' - 'Bitfield/BFM 32-bit'
      case 0x33000000: packet->A64InstrIndex = BFM_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->N = (packet->Opcode >> 22) & 0x1;
          packet->immr = (packet->Opcode >> 16) & 0x3f;
          packet->imms = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xb3400000, BFM_64: ' sf=31 opc=30,29 N=22 immr=21,16 imms=15,10 Rn=9,5 Rd=4,0' - 'Bitfield/BFM 64-bit'
      case 0xb3400000: packet->A64InstrIndex = BFM_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->N = (packet->Opcode >> 22) & 0x1;
          packet->immr = (packet->Opcode >> 16) & 0x3f;
          packet->imms = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x13000000, SBFM_32: ' sf=31 opc=30,29 N=22 immr=21,16 imms=15,10 Rn=9,5 Rd=4,0' - 'Bitfield/SBFM 32-bit'
      case 0x13000000: packet->A64InstrIndex = SBFM_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->N = (packet->Opcode >> 22) & 0x1;
          packet->immr = (packet->Opcode >> 16) & 0x3f;
          packet->imms = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x93400000, SBFM_64: ' sf=31 opc=30,29 N=22 immr=21,16 imms=15,10 Rn=9,5 Rd=4,0' - 'Bitfield/SBFM 64-bit'
      case 0x93400000: packet->A64InstrIndex = SBFM_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->N = (packet->Opcode >> 22) & 0x1;
          packet->immr = (packet->Opcode >> 16) & 0x3f;
          packet->imms = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x53000000, UBFM_32: ' sf=31 opc=30,29 N=22 immr=21,16 imms=15,10 Rn=9,5 Rd=4,0' - 'Bitfield/UBFM 32-bit'
      case 0x53000000: packet->A64InstrIndex = UBFM_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->N = (packet->Opcode >> 22) & 0x1;
          packet->immr = (packet->Opcode >> 16) & 0x3f;
          packet->imms = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xd3400000, UBFM_64: ' sf=31 opc=30,29 N=22 immr=21,16 imms=15,10 Rn=9,5 Rd=4,0' - 'Bitfield/UBFM 64-bit'
      case 0xd3400000: packet->A64InstrIndex = UBFM_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->N = (packet->Opcode >> 22) & 0x1;
          packet->immr = (packet->Opcode >> 16) & 0x3f;
          packet->imms = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xac400000, SIMD_LDNP_OFF_8_128: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store no-allocate pair (offset)/LDNP (SIMD&FP) 128-bit'
      case 0xac400000: packet->A64InstrIndex = SIMD_LDNP_OFF_8_128;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x2c400000, SIMD_LDNP_OFF_32: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store no-allocate pair (offset)/LDNP (SIMD&FP) 32-bit'
      case 0x2c400000: packet->A64InstrIndex = SIMD_LDNP_OFF_32;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x6c400000, SIMD_LDNP_OFF_64: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store no-allocate pair (offset)/LDNP (SIMD&FP) 64-bit'
      case 0x6c400000: packet->A64InstrIndex = SIMD_LDNP_OFF_64;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x28400000, LDNP_OFF_32: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store no-allocate pair (offset)/LDNP 32-bit'
      case 0x28400000: packet->A64InstrIndex = LDNP_OFF_32;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xa8400000, LDNP_OFF_64: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store no-allocate pair (offset)/LDNP 64-bit'
      case 0xa8400000: packet->A64InstrIndex = LDNP_OFF_64;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xac000000, SIMD_STNP_OFF_8_128: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store no-allocate pair (offset)/STNP (SIMD&FP) 128-bit'
      case 0xac000000: packet->A64InstrIndex = SIMD_STNP_OFF_8_128;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x2c000000, SIMD_STNP_OFF_32: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store no-allocate pair (offset)/STNP (SIMD&FP) 32-bit'
      case 0x2c000000: packet->A64InstrIndex = SIMD_STNP_OFF_32;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x6c000000, SIMD_STNP_OFF_64: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store no-allocate pair (offset)/STNP (SIMD&FP) 64-bit'
      case 0x6c000000: packet->A64InstrIndex = SIMD_STNP_OFF_64;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x28000000, STNP_OFF_32: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store no-allocate pair (offset)/STNP 32-bit'
      case 0x28000000: packet->A64InstrIndex = STNP_OFF_32;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xa8000000, STNP_OFF_64: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store no-allocate pair (offset)/STNP 64-bit'
      case 0xa8000000: packet->A64InstrIndex = STNP_OFF_64;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb9400000, LDR_IMM_REG_32: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/LDR (immediate) 32-bit'
      case 0xb9400000: packet->A64InstrIndex = LDR_IMM_REG_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xf9400000, LDR_IMM_REG_64: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/LDR (immediate) 64-bit'
      case 0xf9400000: packet->A64InstrIndex = LDR_IMM_REG_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3dc00000, SIMD_LDR_IMM_REG_8_128: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/LDR (immediate, SIMD&FP) 128-bit'
      case 0x3dc00000: packet->A64InstrIndex = SIMD_LDR_IMM_REG_8_128;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x7d400000, SIMD_LDR_IMM_REG_16: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/LDR (immediate, SIMD&FP) 16-bit'
      case 0x7d400000: packet->A64InstrIndex = SIMD_LDR_IMM_REG_16;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xbd400000, SIMD_LDR_IMM_REG_32: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/LDR (immediate, SIMD&FP) 32-bit'
      case 0xbd400000: packet->A64InstrIndex = SIMD_LDR_IMM_REG_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xfd400000, SIMD_LDR_IMM_REG_64: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/LDR (immediate, SIMD&FP) 64-bit'
      case 0xfd400000: packet->A64InstrIndex = SIMD_LDR_IMM_REG_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3d400000, SIMD_LDR_IMM_REG_8: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/LDR (immediate, SIMD&FP) 8-bit'
      case 0x3d400000: packet->A64InstrIndex = SIMD_LDR_IMM_REG_8;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x39400000, LDRB_IMM_REG_OFF: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/LDRB (immediate) Unsigned offset'
      case 0x39400000: packet->A64InstrIndex = LDRB_IMM_REG_OFF;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x79400000, LDRH_IMM_REG_OFF: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/LDRH (immediate) Unsigned offset'
      case 0x79400000: packet->A64InstrIndex = LDRH_IMM_REG_OFF;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x39c00000, LDRSB_IMM_REG_32: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/LDRSB (immediate) 32-bit'
      case 0x39c00000: packet->A64InstrIndex = LDRSB_IMM_REG_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x39800000, LDRSB_IMM_REG_64: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/LDRSB (immediate) 64-bit'
      case 0x39800000: packet->A64InstrIndex = LDRSB_IMM_REG_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x79c00000, LDRSH_IMM_REG_32: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/LDRSH (immediate) 32-bit'
      case 0x79c00000: packet->A64InstrIndex = LDRSH_IMM_REG_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x79800000, LDRSH_IMM_REG_64: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/LDRSH (immediate) 64-bit'
      case 0x79800000: packet->A64InstrIndex = LDRSH_IMM_REG_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb9800000, LDRSW_IMM_REG_OFF: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/LDRSW (immediate) Unsigned offset'
      case 0xb9800000: packet->A64InstrIndex = LDRSW_IMM_REG_OFF;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xf9800000, PRFM_IMM_REG: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/PRFM (immediate) -'
      case 0xf9800000: packet->A64InstrIndex = PRFM_IMM_REG;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb9000000, STR_IMM_REG_32: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/STR (immediate) 32-bit'
      case 0xb9000000: packet->A64InstrIndex = STR_IMM_REG_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xf9000000, STR_IMM_REG_64: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/STR (immediate) 64-bit'
      case 0xf9000000: packet->A64InstrIndex = STR_IMM_REG_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3d800000, SIMD_STR_IMM_REG_8_128: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/STR (immediate, SIMD&FP) 128-bit'
      case 0x3d800000: packet->A64InstrIndex = SIMD_STR_IMM_REG_8_128;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x7d000000, SIMD_STR_IMM_REG_16: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/STR (immediate, SIMD&FP) 16-bit'
      case 0x7d000000: packet->A64InstrIndex = SIMD_STR_IMM_REG_16;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xbd000000, SIMD_STR_IMM_REG_32: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/STR (immediate, SIMD&FP) 32-bit'
      case 0xbd000000: packet->A64InstrIndex = SIMD_STR_IMM_REG_32;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xfd000000, SIMD_STR_IMM_REG_64: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/STR (immediate, SIMD&FP) 64-bit'
      case 0xfd000000: packet->A64InstrIndex = SIMD_STR_IMM_REG_64;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x3d000000, SIMD_STR_IMM_REG_8: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/STR (immediate, SIMD&FP) 8-bit'
      case 0x3d000000: packet->A64InstrIndex = SIMD_STR_IMM_REG_8;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x39000000, STRB_IMM_REG_OFF: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/STRB (immediate) Unsigned offset'
      case 0x39000000: packet->A64InstrIndex = STRB_IMM_REG_OFF;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x79000000, STRH_IMM_REG_OFF: ' size=31,30 V=26 opc=23,22 imm12=21,10 Rn=9,5 Rt=4,0' - 'Load/store register (unsigned immediate)/STRH (immediate) Unsigned offset'
      case 0x79000000: packet->A64InstrIndex = STRH_IMM_REG_OFF;
          packet->size = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->opc = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xad400000, SIMD_LDP_REG_OFF_8_128: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (offset)/LDP (SIMD&FP) 128-bit'
      case 0xad400000: packet->A64InstrIndex = SIMD_LDP_REG_OFF_8_128;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x2d400000, SIMD_LDP_REG_OFF_32: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (offset)/LDP (SIMD&FP) 32-bit'
      case 0x2d400000: packet->A64InstrIndex = SIMD_LDP_REG_OFF_32;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x6d400000, SIMD_LDP_REG_OFF_64: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (offset)/LDP (SIMD&FP) 64-bit'
      case 0x6d400000: packet->A64InstrIndex = SIMD_LDP_REG_OFF_64;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x29400000, LDP_REG_OFF_32: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (offset)/LDP 32-bit'
      case 0x29400000: packet->A64InstrIndex = LDP_REG_OFF_32;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xa9400000, LDP_REG_OFF_64: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (offset)/LDP 64-bit'
      case 0xa9400000: packet->A64InstrIndex = LDP_REG_OFF_64;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x69400000, LDPSW_REG_OFF: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (offset)/LDPSW Signed offset'
      case 0x69400000: packet->A64InstrIndex = LDPSW_REG_OFF;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xad000000, SIMD_STP_REG_OFF_8_128: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (offset)/STP (SIMD&FP) 128-bit'
      case 0xad000000: packet->A64InstrIndex = SIMD_STP_REG_OFF_8_128;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x2d000000, SIMD_STP_REG_OFF_32: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (offset)/STP (SIMD&FP) 32-bit'
      case 0x2d000000: packet->A64InstrIndex = SIMD_STP_REG_OFF_32;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x6d000000, SIMD_STP_REG_OFF_64: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (offset)/STP (SIMD&FP) 64-bit'
      case 0x6d000000: packet->A64InstrIndex = SIMD_STP_REG_OFF_64;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x29000000, STP_REG_OFF_32: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (offset)/STP 32-bit'
      case 0x29000000: packet->A64InstrIndex = STP_REG_OFF_32;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xa9000000, STP_REG_OFF_64: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (offset)/STP 64-bit'
      case 0xa9000000: packet->A64InstrIndex = STP_REG_OFF_64;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xacc00000, SIMD_LDP_REG_POST_8_128: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (post-indexed)/LDP (SIMD&FP) 128-bit'
      case 0xacc00000: packet->A64InstrIndex = SIMD_LDP_REG_POST_8_128;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x2cc00000, SIMD_LDP_REG_POST_32: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (post-indexed)/LDP (SIMD&FP) 32-bit'
      case 0x2cc00000: packet->A64InstrIndex = SIMD_LDP_REG_POST_32;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x6cc00000, SIMD_LDP_REG_POST_64: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (post-indexed)/LDP (SIMD&FP) 64-bit'
      case 0x6cc00000: packet->A64InstrIndex = SIMD_LDP_REG_POST_64;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x28c00000, LDP_REG_POST_32: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (post-indexed)/LDP 32-bit'
      case 0x28c00000: packet->A64InstrIndex = LDP_REG_POST_32;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xa8c00000, LDP_REG_POST_64: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (post-indexed)/LDP 64-bit'
      case 0xa8c00000: packet->A64InstrIndex = LDP_REG_POST_64;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x68c00000, LDPSW_REG_POST: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (post-indexed)/LDPSW Post-index'
      case 0x68c00000: packet->A64InstrIndex = LDPSW_REG_POST;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xac800000, SIMD_STP_REG_POST_8_128: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (post-indexed)/STP (SIMD&FP) 128-bit'
      case 0xac800000: packet->A64InstrIndex = SIMD_STP_REG_POST_8_128;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x2c800000, SIMD_STP_REG_POST_32: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (post-indexed)/STP (SIMD&FP) 32-bit'
      case 0x2c800000: packet->A64InstrIndex = SIMD_STP_REG_POST_32;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x6c800000, SIMD_STP_REG_POST_64: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (post-indexed)/STP (SIMD&FP) 64-bit'
      case 0x6c800000: packet->A64InstrIndex = SIMD_STP_REG_POST_64;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x28800000, STP_REG_POST_32: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (post-indexed)/STP 32-bit'
      case 0x28800000: packet->A64InstrIndex = STP_REG_POST_32;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xa8800000, STP_REG_POST_64: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (post-indexed)/STP 64-bit'
      case 0xa8800000: packet->A64InstrIndex = STP_REG_POST_64;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xadc00000, SIMD_LDP_REG_PRE_8_128: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (pre-indexed)/LDP (SIMD&FP) 128-bit'
      case 0xadc00000: packet->A64InstrIndex = SIMD_LDP_REG_PRE_8_128;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x2dc00000, SIMD_LDP_REG_PRE_32: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (pre-indexed)/LDP (SIMD&FP) 32-bit'
      case 0x2dc00000: packet->A64InstrIndex = SIMD_LDP_REG_PRE_32;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x6dc00000, SIMD_LDP_REG_PRE_64: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (pre-indexed)/LDP (SIMD&FP) 64-bit'
      case 0x6dc00000: packet->A64InstrIndex = SIMD_LDP_REG_PRE_64;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x29c00000, LDP_REG_PRE_32: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (pre-indexed)/LDP 32-bit'
      case 0x29c00000: packet->A64InstrIndex = LDP_REG_PRE_32;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xa9c00000, LDP_REG_PRE_64: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (pre-indexed)/LDP 64-bit'
      case 0xa9c00000: packet->A64InstrIndex = LDP_REG_PRE_64;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x69c00000, LDPSW_REG_PRE: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (pre-indexed)/LDPSW Pre-index'
      case 0x69c00000: packet->A64InstrIndex = LDPSW_REG_PRE;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xad800000, SIMD_STP_REG_PRE_8_128: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (pre-indexed)/STP (SIMD&FP) 128-bit'
      case 0xad800000: packet->A64InstrIndex = SIMD_STP_REG_PRE_8_128;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x2d800000, SIMD_STP_REG_PRE_32: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (pre-indexed)/STP (SIMD&FP) 32-bit'
      case 0x2d800000: packet->A64InstrIndex = SIMD_STP_REG_PRE_32;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x6d800000, SIMD_STP_REG_PRE_64: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (pre-indexed)/STP (SIMD&FP) 64-bit'
      case 0x6d800000: packet->A64InstrIndex = SIMD_STP_REG_PRE_64;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x29800000, STP_REG_PRE_32: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (pre-indexed)/STP 32-bit'
      case 0x29800000: packet->A64InstrIndex = STP_REG_PRE_32;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xa9800000, STP_REG_PRE_64: ' opc=31,30 V=26 L=22 imm7=21,15 Rt2=14,10 Rn=9,5 Rt=4,0' - 'Load/store register pair (pre-indexed)/STP 64-bit'
      case 0xa9800000: packet->A64InstrIndex = STP_REG_PRE_64;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->L = (packet->Opcode >> 22) & 0x1;
          packet->imm7 = (packet->Opcode >> 15) & 0x7f;
          packet->Rt2 = (packet->Opcode >> 10) & 0x1f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x12000000, AND_IMM_32: ' sf=31 opc=30,29 N=22 immr=21,16 imms=15,10 Rn=9,5 Rd=4,0' - 'Logical (immediate)/AND (immediate) 32-bit'
      case 0x12000000: packet->A64InstrIndex = AND_IMM_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->N = (packet->Opcode >> 22) & 0x1;
          packet->immr = (packet->Opcode >> 16) & 0x3f;
          packet->imms = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x72000000, ANDS_IMM_32: ' sf=31 opc=30,29 N=22 immr=21,16 imms=15,10 Rn=9,5 Rd=4,0' - 'Logical (immediate)/ANDS (immediate) 32-bit'
      case 0x72000000: packet->A64InstrIndex = ANDS_IMM_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->N = (packet->Opcode >> 22) & 0x1;
          packet->immr = (packet->Opcode >> 16) & 0x3f;
          packet->imms = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x52000000, EOR_IMM_32: ' sf=31 opc=30,29 N=22 immr=21,16 imms=15,10 Rn=9,5 Rd=4,0' - 'Logical (immediate)/EOR (immediate) 32-bit'
      case 0x52000000: packet->A64InstrIndex = EOR_IMM_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->N = (packet->Opcode >> 22) & 0x1;
          packet->immr = (packet->Opcode >> 16) & 0x3f;
          packet->imms = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x32000000, ORR_IMM_32: ' sf=31 opc=30,29 N=22 immr=21,16 imms=15,10 Rn=9,5 Rd=4,0' - 'Logical (immediate)/ORR (immediate) 32-bit'
      case 0x32000000: packet->A64InstrIndex = ORR_IMM_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->N = (packet->Opcode >> 22) & 0x1;
          packet->immr = (packet->Opcode >> 16) & 0x3f;
          packet->imms = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xff000010) {
      // 0x54000000, B_COND_IMM: ' o1=24 imm19=23,5 o0=4 cond=3,0' - 'Conditional branch (immediate)/B.cond -'
      case 0x54000000: packet->A64InstrIndex = B_COND_IMM;
          packet->o1 = (packet->Opcode >> 24) & 0x1;
          packet->imm19 = (packet->Opcode >> 5) & 0x7ffff;
          packet->o0 = (packet->Opcode >> 4) & 0x1;
          packet->cond = packet->Opcode & 0xf;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xff200000) {
      // 0x0b000000, ADD_SHIFT_REG_32: ' sf=31 op=30 S=29 shift=23,22 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Add/subtract (shifted register)/ADD (shifted register) 32-bit'
      case 0x0b000000: packet->A64InstrIndex = ADD_SHIFT_REG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x8b000000, ADD_SHIFT_REG_64: ' sf=31 op=30 S=29 shift=23,22 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Add/subtract (shifted register)/ADD (shifted register) 64-bit'
      case 0x8b000000: packet->A64InstrIndex = ADD_SHIFT_REG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2b000000, ADDS_SHIFT_REG_32: ' sf=31 op=30 S=29 shift=23,22 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Add/subtract (shifted register)/ADDS (shifted register) 32-bit'
      case 0x2b000000: packet->A64InstrIndex = ADDS_SHIFT_REG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xab000000, ADDS_SHIFT_REG_64: ' sf=31 op=30 S=29 shift=23,22 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Add/subtract (shifted register)/ADDS (shifted register) 64-bit'
      case 0xab000000: packet->A64InstrIndex = ADDS_SHIFT_REG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x4b000000, SUB_SHIFT_REG_32: ' sf=31 op=30 S=29 shift=23,22 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Add/subtract (shifted register)/SUB (shifted register) 32-bit'
      case 0x4b000000: packet->A64InstrIndex = SUB_SHIFT_REG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xcb000000, SUB_SHIFT_REG_64: ' sf=31 op=30 S=29 shift=23,22 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Add/subtract (shifted register)/SUB (shifted register) 64-bit'
      case 0xcb000000: packet->A64InstrIndex = SUB_SHIFT_REG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x6b000000, SUBS_SHIFT_REG_32: ' sf=31 op=30 S=29 shift=23,22 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Add/subtract (shifted register)/SUBS (shifted register) 32-bit'
      case 0x6b000000: packet->A64InstrIndex = SUBS_SHIFT_REG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xeb000000, SUBS_SHIFT_REG_64: ' sf=31 op=30 S=29 shift=23,22 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Add/subtract (shifted register)/SUBS (shifted register) 64-bit'
      case 0xeb000000: packet->A64InstrIndex = SUBS_SHIFT_REG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0a000000, AND_SHIFT_REG_32: ' sf=31 opc=30,29 shift=23,22 N=21 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Logical (shifted register)/AND (shifted register) 32-bit'
      case 0x0a000000: packet->A64InstrIndex = AND_SHIFT_REG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->N = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x8a000000, AND_SHIFT_REG_64: ' sf=31 opc=30,29 shift=23,22 N=21 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Logical (shifted register)/AND (shifted register) 64-bit'
      case 0x8a000000: packet->A64InstrIndex = AND_SHIFT_REG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->N = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x6a000000, ANDS_SHIFT_REG_32: ' sf=31 opc=30,29 shift=23,22 N=21 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Logical (shifted register)/ANDS (shifted register) 32-bit'
      case 0x6a000000: packet->A64InstrIndex = ANDS_SHIFT_REG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->N = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xea000000, ANDS_SHIFT_REG_64: ' sf=31 opc=30,29 shift=23,22 N=21 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Logical (shifted register)/ANDS (shifted register) 64-bit'
      case 0xea000000: packet->A64InstrIndex = ANDS_SHIFT_REG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->N = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x0a200000, BIC_SHIFT_REG_32: ' sf=31 opc=30,29 shift=23,22 N=21 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Logical (shifted register)/BIC (shifted register) 32-bit'
      case 0x0a200000: packet->A64InstrIndex = BIC_SHIFT_REG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->N = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x8a200000, BIC_SHIFT_REG_64: ' sf=31 opc=30,29 shift=23,22 N=21 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Logical (shifted register)/BIC (shifted register) 64-bit'
      case 0x8a200000: packet->A64InstrIndex = BIC_SHIFT_REG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->N = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x6a200000, BICS_SHIFT_REG_32: ' sf=31 opc=30,29 shift=23,22 N=21 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Logical (shifted register)/BICS (shifted register) 32-bit'
      case 0x6a200000: packet->A64InstrIndex = BICS_SHIFT_REG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->N = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xea200000, BICS_SHIFT_REG_64: ' sf=31 opc=30,29 shift=23,22 N=21 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Logical (shifted register)/BICS (shifted register) 64-bit'
      case 0xea200000: packet->A64InstrIndex = BICS_SHIFT_REG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->N = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x4a200000, EON_SHIFT_REG_32: ' sf=31 opc=30,29 shift=23,22 N=21 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Logical (shifted register)/EON (shifted register) 32-bit'
      case 0x4a200000: packet->A64InstrIndex = EON_SHIFT_REG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->N = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xca200000, EON_SHIFT_REG_64: ' sf=31 opc=30,29 shift=23,22 N=21 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Logical (shifted register)/EON (shifted register) 64-bit'
      case 0xca200000: packet->A64InstrIndex = EON_SHIFT_REG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->N = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x4a000000, EOR_SHIFT_REG_32: ' sf=31 opc=30,29 shift=23,22 N=21 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Logical (shifted register)/EOR (shifted register) 32-bit'
      case 0x4a000000: packet->A64InstrIndex = EOR_SHIFT_REG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->N = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xca000000, EOR_SHIFT_REG_64: ' sf=31 opc=30,29 shift=23,22 N=21 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Logical (shifted register)/EOR (shifted register) 64-bit'
      case 0xca000000: packet->A64InstrIndex = EOR_SHIFT_REG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->N = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2a200000, ORN_SHIFT_REG_32: ' sf=31 opc=30,29 shift=23,22 N=21 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Logical (shifted register)/ORN (shifted register) 32-bit'
      case 0x2a200000: packet->A64InstrIndex = ORN_SHIFT_REG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->N = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xaa200000, ORN_SHIFT_REG_64: ' sf=31 opc=30,29 shift=23,22 N=21 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Logical (shifted register)/ORN (shifted register) 64-bit'
      case 0xaa200000: packet->A64InstrIndex = ORN_SHIFT_REG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->N = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x2a000000, ORR_SHIFT_REG_32: ' sf=31 opc=30,29 shift=23,22 N=21 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Logical (shifted register)/ORR (shifted register) 32-bit'
      case 0x2a000000: packet->A64InstrIndex = ORR_SHIFT_REG_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->N = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xaa000000, ORR_SHIFT_REG_64: ' sf=31 opc=30,29 shift=23,22 N=21 Rm=20,16 imm6=15,10 Rn=9,5 Rd=4,0' - 'Logical (shifted register)/ORR (shifted register) 64-bit'
      case 0xaa000000: packet->A64InstrIndex = ORR_SHIFT_REG_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->N = (packet->Opcode >> 21) & 0x1;
          packet->Rm = (packet->Opcode >> 16) & 0x1f;
          packet->imm6 = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xff800000) {
      // 0x92000000, AND_IMM_64: ' sf=31 opc=30,29 N=22 immr=21,16 imms=15,10 Rn=9,5 Rd=4,0' - 'Logical (immediate)/AND (immediate) 64-bit'
      case 0x92000000: packet->A64InstrIndex = AND_IMM_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->N = (packet->Opcode >> 22) & 0x1;
          packet->immr = (packet->Opcode >> 16) & 0x3f;
          packet->imms = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xf2000000, ANDS_IMM_64: ' sf=31 opc=30,29 N=22 immr=21,16 imms=15,10 Rn=9,5 Rd=4,0' - 'Logical (immediate)/ANDS (immediate) 64-bit'
      case 0xf2000000: packet->A64InstrIndex = ANDS_IMM_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->N = (packet->Opcode >> 22) & 0x1;
          packet->immr = (packet->Opcode >> 16) & 0x3f;
          packet->imms = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xd2000000, EOR_IMM_64: ' sf=31 opc=30,29 N=22 immr=21,16 imms=15,10 Rn=9,5 Rd=4,0' - 'Logical (immediate)/EOR (immediate) 64-bit'
      case 0xd2000000: packet->A64InstrIndex = EOR_IMM_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->N = (packet->Opcode >> 22) & 0x1;
          packet->immr = (packet->Opcode >> 16) & 0x3f;
          packet->imms = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xb2000000, ORR_IMM_64: ' sf=31 opc=30,29 N=22 immr=21,16 imms=15,10 Rn=9,5 Rd=4,0' - 'Logical (immediate)/ORR (immediate) 64-bit'
      case 0xb2000000: packet->A64InstrIndex = ORR_IMM_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->N = (packet->Opcode >> 22) & 0x1;
          packet->immr = (packet->Opcode >> 16) & 0x3f;
          packet->imms = (packet->Opcode >> 10) & 0x3f;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x72800000, MOVK_IMM_32: ' sf=31 opc=30,29 hw=22,21 imm16=20,5 Rd=4,0' - 'Move wide (immediate)/MOVK 32-bit'
      case 0x72800000: packet->A64InstrIndex = MOVK_IMM_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->hw = (packet->Opcode >> 21) & 0x3;
          packet->imm16 = (packet->Opcode >> 5) & 0xffff;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xf2800000, MOVK_IMM_64: ' sf=31 opc=30,29 hw=22,21 imm16=20,5 Rd=4,0' - 'Move wide (immediate)/MOVK 64-bit'
      case 0xf2800000: packet->A64InstrIndex = MOVK_IMM_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->hw = (packet->Opcode >> 21) & 0x3;
          packet->imm16 = (packet->Opcode >> 5) & 0xffff;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x12800000, MOVN_IMM_32: ' sf=31 opc=30,29 hw=22,21 imm16=20,5 Rd=4,0' - 'Move wide (immediate)/MOVN 32-bit'
      case 0x12800000: packet->A64InstrIndex = MOVN_IMM_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->hw = (packet->Opcode >> 21) & 0x3;
          packet->imm16 = (packet->Opcode >> 5) & 0xffff;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x92800000, MOVN_IMM_64: ' sf=31 opc=30,29 hw=22,21 imm16=20,5 Rd=4,0' - 'Move wide (immediate)/MOVN 64-bit'
      case 0x92800000: packet->A64InstrIndex = MOVN_IMM_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->hw = (packet->Opcode >> 21) & 0x3;
          packet->imm16 = (packet->Opcode >> 5) & 0xffff;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x52800000, MOVZ_IMM_32: ' sf=31 opc=30,29 hw=22,21 imm16=20,5 Rd=4,0' - 'Move wide (immediate)/MOVZ 32-bit'
      case 0x52800000: packet->A64InstrIndex = MOVZ_IMM_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->hw = (packet->Opcode >> 21) & 0x3;
          packet->imm16 = (packet->Opcode >> 5) & 0xffff;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xd2800000, MOVZ_IMM_64: ' sf=31 opc=30,29 hw=22,21 imm16=20,5 Rd=4,0' - 'Move wide (immediate)/MOVZ 64-bit'
      case 0xd2800000: packet->A64InstrIndex = MOVZ_IMM_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->opc = (packet->Opcode >> 29) & 0x3;
          packet->hw = (packet->Opcode >> 21) & 0x3;
          packet->imm16 = (packet->Opcode >> 5) & 0xffff;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xff000000) {
      // 0x11000000, ADD_IMM_32: ' sf=31 op=30 S=29 shift=23,22 imm12=21,10 Rn=9,5 Rd=4,0' - 'Add/subtract (immediate)/ADD (immediate) 32-bit'
      case 0x11000000: packet->A64InstrIndex = ADD_IMM_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x91000000, ADD_IMM_64: ' sf=31 op=30 S=29 shift=23,22 imm12=21,10 Rn=9,5 Rd=4,0' - 'Add/subtract (immediate)/ADD (immediate) 64-bit'
      case 0x91000000: packet->A64InstrIndex = ADD_IMM_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x31000000, ADDS_IMM_32: ' sf=31 op=30 S=29 shift=23,22 imm12=21,10 Rn=9,5 Rd=4,0' - 'Add/subtract (immediate)/ADDS (immediate) 32-bit'
      case 0x31000000: packet->A64InstrIndex = ADDS_IMM_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xb1000000, ADDS_IMM_64: ' sf=31 op=30 S=29 shift=23,22 imm12=21,10 Rn=9,5 Rd=4,0' - 'Add/subtract (immediate)/ADDS (immediate) 64-bit'
      case 0xb1000000: packet->A64InstrIndex = ADDS_IMM_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x51000000, SUB_IMM_32: ' sf=31 op=30 S=29 shift=23,22 imm12=21,10 Rn=9,5 Rd=4,0' - 'Add/subtract (immediate)/SUB (immediate) 32-bit'
      case 0x51000000: packet->A64InstrIndex = SUB_IMM_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xd1000000, SUB_IMM_64: ' sf=31 op=30 S=29 shift=23,22 imm12=21,10 Rn=9,5 Rd=4,0' - 'Add/subtract (immediate)/SUB (immediate) 64-bit'
      case 0xd1000000: packet->A64InstrIndex = SUB_IMM_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x71000000, SUBS_IMM_32: ' sf=31 op=30 S=29 shift=23,22 imm12=21,10 Rn=9,5 Rd=4,0' - 'Add/subtract (immediate)/SUBS (immediate) 32-bit'
      case 0x71000000: packet->A64InstrIndex = SUBS_IMM_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0xf1000000, SUBS_IMM_64: ' sf=31 op=30 S=29 shift=23,22 imm12=21,10 Rn=9,5 Rd=4,0' - 'Add/subtract (immediate)/SUBS (immediate) 64-bit'
      case 0xf1000000: packet->A64InstrIndex = SUBS_IMM_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 30) & 0x1;
          packet->S = (packet->Opcode >> 29) & 0x1;
          packet->shift = (packet->Opcode >> 22) & 0x3;
          packet->imm12 = (packet->Opcode >> 10) & 0xfff;
          packet->Rn = (packet->Opcode >> 5) & 0x1f;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x35000000, CBNZ_IMM_32: ' sf=31 op=24 imm19=23,5 Rt=4,0' - 'Compare & branch (immediate)/CBNZ 32-bit'
      case 0x35000000: packet->A64InstrIndex = CBNZ_IMM_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 24) & 0x1;
          packet->imm19 = (packet->Opcode >> 5) & 0x7ffff;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb5000000, CBNZ_IMM_64: ' sf=31 op=24 imm19=23,5 Rt=4,0' - 'Compare & branch (immediate)/CBNZ 64-bit'
      case 0xb5000000: packet->A64InstrIndex = CBNZ_IMM_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 24) & 0x1;
          packet->imm19 = (packet->Opcode >> 5) & 0x7ffff;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x34000000, CBZ_IMM_32: ' sf=31 op=24 imm19=23,5 Rt=4,0' - 'Compare & branch (immediate)/CBZ 32-bit'
      case 0x34000000: packet->A64InstrIndex = CBZ_IMM_32;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 24) & 0x1;
          packet->imm19 = (packet->Opcode >> 5) & 0x7ffff;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xb4000000, CBZ_IMM_64: ' sf=31 op=24 imm19=23,5 Rt=4,0' - 'Compare & branch (immediate)/CBZ 64-bit'
      case 0xb4000000: packet->A64InstrIndex = CBZ_IMM_64;
          packet->sf = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 24) & 0x1;
          packet->imm19 = (packet->Opcode >> 5) & 0x7ffff;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x18000000, LDR_REG_32: ' opc=31,30 V=26 imm19=23,5 Rt=4,0' - 'Load register (literal)/LDR (literal) 32-bit'
      case 0x18000000: packet->A64InstrIndex = LDR_REG_32;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->imm19 = (packet->Opcode >> 5) & 0x7ffff;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x58000000, LDR_REG_64: ' opc=31,30 V=26 imm19=23,5 Rt=4,0' - 'Load register (literal)/LDR (literal) 64-bit'
      case 0x58000000: packet->A64InstrIndex = LDR_REG_64;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->imm19 = (packet->Opcode >> 5) & 0x7ffff;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x9c000000, SIMD_LDR_REG_8_128: ' opc=31,30 V=26 imm19=23,5 Rt=4,0' - 'Load register (literal)/LDR (literal, SIMD&FP) 128-bit'
      case 0x9c000000: packet->A64InstrIndex = SIMD_LDR_REG_8_128;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->imm19 = (packet->Opcode >> 5) & 0x7ffff;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x1c000000, SIMD_LDR_REG_32: ' opc=31,30 V=26 imm19=23,5 Rt=4,0' - 'Load register (literal)/LDR (literal, SIMD&FP) 32-bit'
      case 0x1c000000: packet->A64InstrIndex = SIMD_LDR_REG_32;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->imm19 = (packet->Opcode >> 5) & 0x7ffff;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x5c000000, SIMD_LDR_REG_64: ' opc=31,30 V=26 imm19=23,5 Rt=4,0' - 'Load register (literal)/LDR (literal, SIMD&FP) 64-bit'
      case 0x5c000000: packet->A64InstrIndex = SIMD_LDR_REG_64;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->imm19 = (packet->Opcode >> 5) & 0x7ffff;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x98000000, LDRSW_REG: ' opc=31,30 V=26 imm19=23,5 Rt=4,0' - 'Load register (literal)/LDRSW (literal) -'
      case 0x98000000: packet->A64InstrIndex = LDRSW_REG;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->imm19 = (packet->Opcode >> 5) & 0x7ffff;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0xd8000000, PRFM_REG: ' opc=31,30 V=26 imm19=23,5 Rt=4,0' - 'Load register (literal)/PRFM (literal) -'
      case 0xd8000000: packet->A64InstrIndex = PRFM_REG;
          packet->opc = (packet->Opcode >> 30) & 0x3;
          packet->V = (packet->Opcode >> 26) & 0x1;
          packet->imm19 = (packet->Opcode >> 5) & 0x7ffff;
          packet->Rt = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0x7f000000) {
      // 0x37000000, TBNZ: ' b5=31 op=24 b40=23,19 imm14=18,5 Rt=4,0' - 'Test & branch (immediate)/TBNZ -'
      case 0x37000000: packet->A64InstrIndex = TBNZ;
          packet->b5 = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 24) & 0x1;
          packet->b40 = (packet->Opcode >> 19) & 0x1f;
          packet->imm14 = (packet->Opcode >> 5) & 0x3fff;
          packet->Rt = packet->Opcode & 0x1f;
          break;
      // 0x36000000, TBZ: ' b5=31 op=24 b40=23,19 imm14=18,5 Rt=4,0' - 'Test & branch (immediate)/TBZ -'
      case 0x36000000: packet->A64InstrIndex = TBZ;
          packet->b5 = (packet->Opcode >> 31) & 0x1;
          packet->op = (packet->Opcode >> 24) & 0x1;
          packet->b40 = (packet->Opcode >> 19) & 0x1f;
          packet->imm14 = (packet->Opcode >> 5) & 0x3fff;
          packet->Rt = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0xfc000000) {
      // 0x14000000, B_IMM: ' op=31 imm26=25,0' - 'Unconditional branch (immediate)/B -'
      case 0x14000000: packet->A64InstrIndex = B_IMM;
          packet->op = (packet->Opcode >> 31) & 0x1;
          packet->imm26 = packet->Opcode & 0x3ffffff;
          break;
      // 0x94000000, BL: ' op=31 imm26=25,0' - 'Unconditional branch (immediate)/BL -'
      case 0x94000000: packet->A64InstrIndex = BL;
          packet->op = (packet->Opcode >> 31) & 0x1;
          packet->imm26 = packet->Opcode & 0x3ffffff;
          break;
    default: break;
    }
  }
  if (packet->A64InstrIndex==A64_UNALLOCATED) {
    switch(packet->Opcode & 0x9f000000) {
      // 0x10000000, ADR: ' op=31 immlo=30,29 immhi=23,5 Rd=4,0' - 'PC-relative addressing/ADR -'
      case 0x10000000: packet->A64InstrIndex = ADR;
          packet->op = (packet->Opcode >> 31) & 0x1;
          packet->immlo = (packet->Opcode >> 29) & 0x3;
          packet->immhi = (packet->Opcode >> 5) & 0x7ffff;
          packet->Rd = packet->Opcode & 0x1f;
          break;
      // 0x90000000, ADRP: ' op=31 immlo=30,29 immhi=23,5 Rd=4,0' - 'PC-relative addressing/ADRP -'
      case 0x90000000: packet->A64InstrIndex = ADRP;
          packet->op = (packet->Opcode >> 31) & 0x1;
          packet->immlo = (packet->Opcode >> 29) & 0x3;
          packet->immhi = (packet->Opcode >> 5) & 0x7ffff;
          packet->Rd = packet->Opcode & 0x1f;
          break;
    default: break;
    }
  }
