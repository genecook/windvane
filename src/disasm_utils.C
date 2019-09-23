#include <stdio.h>
#include <string>
#include <string.h>
#include "a64sim.h"
#include "disasm_utils.h"

std::string Tparm(unsigned size,unsigned Q) {
   std::string tval = "?";
   switch((int)(size<<1|Q)) {
   case 0: tval = "8B";  break;
   case 1: tval = "16B"; break;
   case 2: tval = "4H";  break;
   case 3: tval = "8H";  break;
   case 4: tval = "2S";  break;
   case 5: tval = "4S";  break;
   case 7: tval = "2D";  break;
   default: break;
   }
   return tval;
}

std::string Ta_parm(unsigned size) {
   std::string taval = "?";
   switch(size) {
   case 0: taval = "8H"; break;
   case 1: taval = "4S"; break;
   case 2: taval = "2D"; break;
   default: break;
   }
   return taval;
}

std::string simdElementIndex(unsigned imm5) {
  std::string elem_id; 
  int id = -1;
  char tbuf[128];
  if (imm5 & 1)      id = imm5>>1;
  else if (imm5 & 2) id = imm5>>2;
  else if (imm5 & 4) id = imm5>>3;
  else if (imm5 & 8) id = imm5>>4;
  if (id >= 0) { 
    sprintf(tbuf,"%d",id);
    elem_id = std::string(tbuf);
  } else
    elem_id = "?";
  return elem_id;  
}

std::string simdElementIndex2(unsigned imm5,unsigned imm4) {
  std::string elem_id; 
  int id = -1;
  char tbuf[128];
  if (imm5 & 1)      id = imm4;
  else if (imm5 & 2) id = imm4>>1;
  else if (imm5 & 4) id = imm4>>2;
  else if (imm5 & 8) id = imm4>>3;
  if (id >= 0) { 
    sprintf(tbuf,"%d",id);
    elem_id = std::string(tbuf);
  } else
    elem_id = "?";
  return elem_id;  
}

std::string fpElementIndex(unsigned sz,unsigned L,unsigned H) {
  std::string elem_id;
  int id = 1;
  char tbuf[128];
  if (sz==0)
    id = H<<1|L;
  else if (sz==1 && L==0)
    id = H;
  if (id >= 0) { 
    sprintf(tbuf,"%d",id);
    elem_id = std::string(tbuf);
  } else
    elem_id = "?";
  return elem_id;    
}

std::string simdElementIndex3(unsigned size,unsigned H,unsigned L,unsigned M) {
  std::string elem_id; 
  int id = -1;
  char tbuf[128];
  if (size == 1)
    elem_id = H<<2|L<<1|M;
  else if (size == 2)
    elem_id = H<<1|M;
  if (id >= 0) { 
    sprintf(tbuf,"%d",id);
    elem_id = std::string(tbuf);
  } else
    elem_id = "?";
  return elem_id;    
}

unsigned int simd_ld1_imm(unsigned Q,unsigned S,unsigned size,int width) {
  unsigned element_index = 0;
  switch(width) {
    case 8:  element_index = (Q<<3) | (S<<2) | size; break;
    case 16: element_index = (Q<<2) | (S<<1) | (size>>1); break;
    case 32: element_index = (Q<<1) | S<<1; break;
    case 64: element_index = Q; break;
    default: break;
  }
  return element_index;
}

std::string simd_rshift1(unsigned immh,unsigned immb) {
  std::string rs;
  if (immh < 8) {
    char tbuf[128];
    sprintf(tbuf,"%d",immh<<3|immb);
    rs = std::string(tbuf);
  } else 
    rs = "?";
  return rs;
}

std::string simd_rshift2(unsigned immh,unsigned immb) {
  char tbuf[128];
  if (immh & 1)
    sprintf(tbuf,"%d",(immh<<3|immb) - 8);
  else if (immh & 2)
    sprintf(tbuf,"%d",(immh<<3|immb) - 16);
  else if (immh & 4)
    sprintf(tbuf,"%d",(immh<<3|immb) - 32);
  else
    strcpy(tbuf,"?");
  return std::string(tbuf);
} 

std::string simd_lshift_scalar(unsigned immh,unsigned immb) {
  char tbuf[128];
  if ((immh & 8) == 8)  // immh = 1xxx
    sprintf(tbuf,"%u",(immh<<3|immb) - 64);
    else
    strcpy(tbuf,"?");
  return std::string(tbuf);
}

std::string simd_lshift_vector(unsigned immh,unsigned immb) {
  char tbuf[128];
  unsigned ewidth = 99;
  if (immh & 1)      ewidth = 8;
  else if (immh & 2) ewidth = 16;
  else if (immh & 4) ewidth = 32;
  else if (immh & 8) ewidth = 64;
  if (ewidth == 99)
    strcpy(tbuf,"?"); //<---oops! wrong encoding
  else
    sprintf(tbuf,"%u",(immh<<3|immb) - ewidth);
  return std::string(tbuf);
}
  
std::string simdLowByteNum(unsigned Q,unsigned imm4) {
  std::string byte_num;
  char tbuf[128];
  if (Q==1 and (imm4 & 8)==0) {
    sprintf(tbuf,"%u",imm4 & 7);
    byte_num = std::string(tbuf);
  } else if (Q==1) {
    sprintf(tbuf,"%u",imm4);
    byte_num = std::string(tbuf);
  } else {
    byte_num = "?";    
  }
  return byte_num;
}

std::string Tscale(unsigned imm5) {
   std::string ts = "?";
   if ((imm5 & 1) == 1) ts = "B";
   else if ((imm5 & 3) == 2) ts = "H";
   else if ((imm5 & 7) == 4) ts = "S";
   else if ((imm5 & 0xf) == 8) ts = "D";
   return ts;
}

std::string Tvect(unsigned imm5,unsigned Q) {
   std::string tv = "?";  
   unsigned sp = (imm5<<1) | Q;
   if ((sp & 3) == 2) tv = "8B";
   else if ((sp & 3) == 3) tv = "16B";
   else if ((sp & 7) == 4) tv = "4H";
   else if ((sp & 7) == 5) tv = "8H";
   else if ((sp & 0xf) == 8) tv = "2S";
   else if ((sp & 0xf) == 9) tv = "4S";
   else if ((sp & 0x1f) == 0x11) tv = "2D";
   return tv;
}

std::string XnSP(unsigned Rn,bool W) {
   if (Rn == 31) {
     if (W) 
       return std::string("WSP");
     else
       return std::string("SP");
   }
   
   char tbuf[128];
   if (W) 
     sprintf(tbuf,"W%d",Rn);
   else
     sprintf(tbuf,"X%d",Rn);
   
   return std::string(tbuf);
}

std::string XnXZR(unsigned Rn,bool W) {
   if (Rn == 31) {
     if (W) 
       return std::string("WZR");
     else
       return std::string("XZR");
   }
   
   char tbuf[128];
   if (W) 
     sprintf(tbuf,"W%d",Rn);
   else
     sprintf(tbuf,"X%d",Rn);
   
   return std::string(tbuf);
}

std::string extendOption(unsigned option,unsigned Rd,unsigned Rn, bool has_imm3) {
  std::string etype = "?";

  if (has_imm3) {
    // ADD/SUB/CMN...
    switch(option) {
      case 0: etype = "UXTB"; break;
      case 1: etype = "UXTH"; break;
      case 2: etype = "UXTW"; break;
      case 3: (Rd==31 || Rn==31) ? etype = "LSL" : etype = "UXTX"; break;
      case 4: etype = "SXTB"; break;
      case 5: etype = "SXTH"; break;
      case 6: etype = "SXTW"; break;
      case 7: etype = "SXTX"; break;
      default: break;
    }
  } else {
    // SIMD_STR...
    switch(option) {
      case 2: etype = "UXTW"; break;
      case 3: etype = "LSL";  break;
      case 6: etype = "SXTW"; break;
      case 7: etype = "SXTX"; break;
      default: break;
    }
  }
  
  return etype;
}

std::string as_imm_shift(unsigned shift) {
  if (shift == 0) return "LSL #0";
  if (shift == 1) return "LSL #12";
  return "?";
}

std::string as_reg_shift(unsigned shift) {
  if (shift == 0) return "LSL";
  if (shift == 1) return "LSR";
  if (shift == 2) return "ASR";
  if (shift == 3) return "ROR";
  return "?";
}

std::string eon_reg_shift(unsigned shift) {
  if (shift == 0) return "LSL";
  if (shift == 1) return "LSR";
  if (shift == 2) return "ASR";
  if (shift == 3) return "ROR";
  return "?";
}

unsigned decodeFbits(unsigned immh,unsigned immb,unsigned scale,bool use_scale) {
  unsigned fbits = 0;
  if (use_scale) {
    // example: FCVTZS (scalar, fixed-point)...
    fbits = 64 - scale;
  } else {
    // example: 
    fbits = (immh<<3) | immb;
  }
  return fbits;
}

unsigned decode_pimm(unsigned imm12,unsigned size,unsigned opc) {
/*
  unsigned pimm = 0;

  switch(size<<2|opc) {
    case 0:
    case 0x1: pimm = imm12 * 1;  break; // 8-bit variant...
    case 0x4:
    case 0x5: pimm = imm12 * 2;  break; // 16-bit variant...
    case 0x8:
    case 0x9: pimm = imm12 * 4;  break; // 32-bit variant...
    case 0xc:
    case 0xd: pimm = imm12 * 8;  break; // 64-bit variant...
    case 0x3: pimm = imm12 * 16; break; // 128-bit variant...
    default:  break;
  }
*/
  unsigned pimm = imm12 * (2<<(size-1));
  
  return pimm;
}

std::string Bcond(unsigned cond) {
   // see arm arm section C1.2.3 on page 112
   std::string cs = "?";
   switch((int) cond) {
   case 0:  cs = "EQ"; break;
   case 1:  cs = "NE"; break;
   case 2:  cs = "CS"; break;
   case 3:  cs = "CC"; break;
   case 4:  cs = "MI"; break;
   case 5:  cs = "PL"; break;
   case 6:  cs = "VS"; break;
   case 7:  cs = "VC"; break;
   case 8:  cs = "HI"; break;
   case 9:  cs = "LS"; break;
   case 10: cs = "GE"; break;
   case 11: cs = "LT"; break;
   case 12: cs = "GT"; break;
   case 13: cs = "LE"; break;
   case 14: cs = "AL"; break;
   case 15: cs = "NV"; break;
   default: break;
   }
   return cs;
}

std::string ZR(unsigned Rm) {
   if (Rm==31) return std::string("ZR");
   char tbuf[128];
   sprintf(tbuf,"%d",Rm);
   return std::string(tbuf);
}

std::string barrier_option(unsigned CRm, bool is_isb) {
   std::string bo;
   if (is_isb) {
     if (CRm == 15)
       bo = "SY";
     else {
       char tbuf[128]; 
       sprintf(tbuf,"#%d",CRm); 
       bo = std::string(tbuf); 
     } 
   } else {
     switch((int) CRm) {
       case 1:  bo = "OSHLD"; break;
       case 2:  bo = "OSHST"; break;
       case 3:  bo = "OSH";   break;
       case 5:  bo = "NSHLD"; break;
       case 6:  bo = "NSHST"; break;
       case 7:  bo = "NSH";   break;
       case 9:  bo = "ISHLD"; break;
       case 10: bo = "ISHST"; break;
       case 11: bo = "ISH";   break;
       case 13: bo = "LD";    break;
       case 14: bo = "ST";    break;
       case 15: bo = "SY";    break;
       default: { char tbuf[128]; 
                  sprintf(tbuf,"#%d",CRm); 
                  bo = std::string(tbuf); 
                } 
                break;
     }
   }
   return bo;
}

std::string ZeroExtend(unsigned imm,unsigned nbits,unsigned shift) {
   char tbuf[128];
   unsigned shifted_imm = imm;
   switch((int) shift) {
   case 0:  sprintf(tbuf,"%d",shifted_imm); 
            break;
   case 1:  sprintf(tbuf,"%d,LSL #12",shifted_imm); 
            break;
   default: strcpy(tbuf,"?");
            break;
   }
   return std::string(tbuf);
}
 
int HighestSetBit(unsigned bval,int len) {
  int i = 0;
  for (i = len-1; i >= 0; i--) {
    if ((bval>>i) == 1)
      break;
  }  
  return i;
}

unsigned Ones(int len) {
  return (1<<len)-1;
}

unsigned zeroExtend(unsigned tval,int /*nbits*/) {
   return tval;
}

long long SignExtend(unsigned long long tval,int len) {
  int sbit = len - 1;

  if ((tval>>sbit) == 1) {
    for (int i = 63; i > sbit; i--) {
      tval |= (1ull<<i);
    }
  }

  long long int rval = (long long int) tval;

  return(rval);
}

std::string systemRegisterName(unsigned o0,unsigned op1,unsigned CRn,unsigned CRm,unsigned op2,bool is_read) {
  //printf("[systemRegisterName] o0: 0x%x op1: 0x%x CRn: 0x%x CRm: 0x%x op2: 0x%x read? %d\n",o0,op1,CRn,CRm,op2,is_read);

  int sreg_index = o0<<16|op1<<12|CRn<<8|CRm<<4|op2;

  //printf("[systemRegisterName] index: %d\n",sreg_index);

  std::string rname = "?";
  switch(sreg_index) {
#include "v8_sregs_decode.C"
  default: break;
  }

  return rname;
}

std::string pstateFieldName(unsigned op1,unsigned op2) {
  std::string ps_field_name;
    switch(op1<<4|op2) {
    case 5:    ps_field_name = "SPSel";    break;
    case 0x36: ps_field_name = "DAIFSet";  break;
    case 0x37: ps_field_name = "DAIFClr";  break;
    default:   ps_field_name = "?";        break;
  }
  return ps_field_name;
}

std::string sysop_name(unsigned op1,unsigned CRn,unsigned CRm,unsigned op2) {
  std::string sysop;
  int sysop_case = (int) op1<<12|CRn<<8|CRm<<3|op2; // each field is hex digit (see arm arm page 4987
  switch(sysop_case) {
    case 0x0780: sysop = "S1E1R";        break;
    case 0x4780: sysop = "S1E2R";        break;
    case 0x6780: sysop = "S1E3R";        break;
    case 0x0781: sysop = "S1E1W";        break;
    case 0x4781: sysop = "S1E2W";        break;
    case 0x6781: sysop = "S1E3W";        break;
    case 0x0782: sysop = "S1E0R";        break;
    case 0x0783: sysop = "S1E0W";        break;
    case 0x4784: sysop = "S12E1R";       break;
    case 0x4785: sysop = "S12E1W";       break;
    case 0x4786: sysop = "S12E0R";       break;
    case 0x4787: sysop = "S12E0W";       break;
    case 0x3741: sysop = "ZVA";          break;
    case 0x0761: sysop = "IVAC";         break;
    case 0x0762: sysop = "ISW";          break;
    case 0x37a1: sysop = "CVAC";         break;
    case 0x07a2: sysop = "CSW";          break;
    case 0x37b1: sysop = "CVAU";         break;
    case 0x37e1: sysop = "CIVAC";        break;
    case 0x07e2: sysop = "CISW";         break;
    case 0x0710: sysop = "IALLUIS";      break;
    case 0x0750: sysop = "IALLU";        break;
    case 0x3751: sysop = "IVAU";         break;
    case 0x4801: sysop = "IPAS2E1IS";    break;
    case 0x4805: sysop = "IPAS2LE1IS";   break;
    case 0x0830: sysop = "VMALLE1IS";    break;
    case 0x4830: sysop = "ALLE2IS";      break;
    case 0x6830: sysop = "ALLE3IS";      break;
    case 0x0831: sysop = "VAE1IS";       break;
    case 0x4831: sysop = "VAE2IS";       break;
    case 0x6831: sysop = "VAE3IS";       break;
    case 0x0832: sysop = "ASIDE1IS";     break;
    case 0x0833: sysop = "VAAE1IS";      break;
    case 0x4834: sysop = "ALLE1IS";      break;
    case 0x0835: sysop = "VALE1IS";      break;
    case 0x4835: sysop = "VALE2IS";      break;
    case 0x6835: sysop = "VALE3IS";      break;
    case 0x4836: sysop = "VMALLS12E1IS"; break;
    case 0x0837: sysop = "VAALE1IS";     break;
    case 0x4841: sysop = "IPAS2E1";      break;
    case 0x4845: sysop = "IPAS2LE1";     break;
    case 0x0870: sysop = "VMALLE1";      break;
    case 0x4870: sysop = "ALLE2";        break;
    case 0x6870: sysop = "ALLE3";        break;
    case 0x0871: sysop = "VAE1";         break;
    case 0x4871: sysop = "VAE2";         break;
    case 0x6871: sysop = "VAE3";         break;
    case 0x0872: sysop = "ASIDE1";       break;
    case 0x0873: sysop = "VAAE1";        break;
    case 0x4874: sysop = "ALLE1";        break;
    case 0x0875: sysop = "VALE1";        break;
    case 0x4875: sysop = "VALE2";        break;
    case 0x6875: sysop = "VALE3";        break;
    default: {
      int sysop_case = (int) op1<<11|CRn<<7|CRm<<3|op2; // actual value
              char tbuf[128];
              sprintf(tbuf,"#%d",sysop_case);
              sysop = std::string(tbuf);
              }
              break;
  }

  return sysop;
}

std::string prfop_name(unsigned Rt) {
  std::string prfop;
  switch(Rt) {
    case 0:  prfop = "PLDL1KEEP"; break; // PLDL1KEEP when Rt = 00000
    case 1:  prfop = "PLDL1STRM"; break; // PLDL1STRM when Rt = 00001
    case 2:  prfop = "PLDL2KEEP"; break; // PLDL2KEEP when Rt = 00010
    case 3:  prfop = "PLDL2STRM"; break; // PLDL2STRM when Rt = 00011
    case 4:  prfop = "PLDL3KEEP"; break; // PLDL3KEEP when Rt = 00100
    case 5:  prfop = "PLDL3STRM"; break; // PLDL3STRM when Rt = 00101
    case 8:  prfop = "PLIL1KEEP"; break; // PLIL1KEEP when Rt = 01000
    case 9:  prfop = "PLIL1STRM"; break; // PLIL1STRM when Rt = 01001
    case 10: prfop = "PLIL2KEEP"; break; // PLIL2KEEP when Rt = 01010
    case 11: prfop = "PLIL2STRM"; break; // PLIL2STRM when Rt = 01011
    case 12: prfop = "PLIL3KEEP"; break; // PLIL3KEEP when Rt = 01100
    case 13: prfop = "PLIL3STRM"; break; // PLIL3STRM when Rt = 01101
    case 16: prfop = "PSTL1KEEP"; break; // PSTL1KEEP when Rt = 10000
    case 17: prfop = "PSTL1STRM"; break; // PSTL1STRM when Rt = 10001
    case 18: prfop = "PSTL2KEEP"; break; // PSTL2KEEP when Rt = 10010
    case 19: prfop = "PSTL2STRM"; break; // PSTL2STRM when Rt = 10011
    case 20: prfop = "PSTL3KEEP"; break; // PSTL3KEEP when Rt = 10100
    case 21: prfop = "PSTL3STRM"; break; // PSTL3STRM when Rt = 10101
    default:  {
              // #uimm5 when Rt = 0011x
              // #uimm5 when Rt = 0111x
              // #uimm5 when Rt = 1011x
              // #uimm5 when Rt = 11xxx
              char tbuf[128];
              sprintf(tbuf,"#%d",Rt);
              prfop = std::string(tbuf);
              }
              break;
  }
  return prfop;
}

std::string t_or_sp(unsigned Rt) {
  std::string rn;
  if (Rt == 31)
    rn = "ZR";
  else {
    char tbuf[128];
    sprintf(tbuf,"%d",Rt);
    rn = std::string(tbuf);
  }
  return rn;
}

std::string simdScalarWidth(unsigned size) {
  std::string width;
  if (size == 3) 
     width = "D";
  else
    width = "?";
  return width;
}

std::string simdArrangementB(unsigned size,unsigned Q) {
  std::string arrangement;
  int specifier = size<<1 | Q;
  switch(specifier) {
    case 0: arrangement = "8B";  break;
    case 1: arrangement = "16B"; break;
    case 2: arrangement = "4H";  break;
    case 3: arrangement = "8H";  break;
    case 4: arrangement = "2S";  break;
    case 5: arrangement = "4S";  break;
    default: arrangement = "?"; break;
  }
  return arrangement;
}

std::string simdArrangementA(unsigned size) {
  std::string arrangement;
  switch((int) size) {
    case 0: arrangement = "8H";  break;
    case 1: arrangement = "4S";  break;
    case 2: arrangement = "2D";  break;
    default: arrangement = "?"; break;
  }
  return arrangement;
}

unsigned long long FP8exp(unsigned a,unsigned b,unsigned c,unsigned d,unsigned e,unsigned f,unsigned g,unsigned h) {
  unsigned long long result = 0;
  if (a) result |= 0xffULL<<56;
  if (b) result |= 0xffULL<<48;
  if (c) result |= 0xffULL<<40;
  if (d) result |= 0xffULL<<32;
  if (e) result |= 0xffULL<<24;
  if (f) result |= 0xffULL<<16;
  if (g) result |= 0xffULL<<8;
  if (h) result |= 0xffULL;
  return result;
}

void ROR_C(unsigned &result, unsigned &carry, unsigned x, int len, int shift) {
  unsigned m = shift % len;
  result = x>>m | x<<(len-m);
  carry  = result>>len & 1;
}

unsigned ROR(unsigned x, int len, int shift) {
   unsigned result;
   if (shift == 0) {
     result = x;
   } else {
     unsigned carry;
     ROR_C(result,carry,x,len,shift);
   }
   return result;
}

unsigned Replicate(unsigned x) {
  return x;
}

void decodeBitMasks(unsigned &wmask,unsigned &tmask, unsigned immN,unsigned imms,unsigned immr,int nbits,bool immediate) {
   //unsigned decode_val = 0;
   unsigned levels;

   //compute log2 of element size...
   int len = HighestSetBit(immN<<6 | ((~imms) & 0x3f),  nbits); //<---imms,immr are 6 bit fields

   if (len < 1) {
     // reserved value...
     throw RESERVED_VALUE;
   }
   // determine S, R, and S-R parameters...
   levels = zeroExtend(Ones(len),nbits);
   // for logical immediates an all-ones value of S is reserved
   // since would generate a useless all-ones result (many times)
   if (immediate && (imms & levels) == levels) {
     throw RESERVED_VALUE;
   }

   unsigned S = immr & levels;
   unsigned R = immr & levels;
   unsigned diff = S - R; // 6-bit subtract with borrow(?)

   //unsigned esize = 1<< len;
   unsigned d = diff & (Ones(len)-1); // d = Uint(diff<len-1:0>)
   unsigned welem = Ones(S + 1);      // welem = ZeroExtend(Ones(S + 1), esize)
   unsigned telem = Ones(d + 1);      // telem = ZeroExtend(Ones(d + 1), esize)

   wmask = Replicate(ROR(welem,R,0));   // see arm arm page 5088. implied (missing) parameter seems to be target length (32 or 64)
   tmask = Replicate(telem);
}
/*
std::string DecodeBitMasks(unsigned immN,unsigned imms,unsigned immr,int len,bool immediate) {
  char tbuf[128];
  sprintf(tbuf,"%d",decodeBitMasks(immN,imms,immr,len,immediate));
  return std::string(tbuf);
}
*/

