#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "a64sim.h"
#include "a64_instr_enums.h"
#include "disasm_utils.h"

//#define KERNEL_DEBUG 1

//---------------------------------------------------------------------------------------------------------------------------
// utulity methods used with DP ops...
//---------------------------------------------------------------------------------------------------------------------------

// 2nd argument indicates sign bit position in src op...

long long Control::SignExtend(unsigned long long op,int field_width,int rwidth /* defaults to 64 */) {
  //printf("[SignExtend] op: 0x%llx field-width: %d, register-width: %d\n",op,field_width,rwidth);
  
  int sign_bit = field_width - 1;

  bool sbit_set = ( (op>>sign_bit) & 1 ) == 1;

  //printf("[SignExtend] op: 0x%llx sbit: %d (set?: %d) rwidth: %d, ",op,sign_bit,sbit_set,rwidth);

  if (sbit_set) {
    for (int i = sign_bit; i < rwidth; i++) {
      op = op | (1ull<<i);
    }
  }

  //long long int rval = (long long int) op;
  //printf("[SignExtend] rval: %lld (0x%llx)\n",rval,op);

  return (long long int) op;
}

unsigned long long Control::Ones(int count) {
  //printf("[Control::Ones] count: %d dsize: %d\n",count,dsize);
  unsigned long long mask = (packet->Dsize()==64) ? 0xffffffffffffffffull : 0xffffffffull;
  unsigned long long rval = (count==64) ? 0xffffffffffffffffull : ( ((1ull<<count) - 1) & mask );
  //printf("        [Control::Ones] count: %d, dsize: %d ---> mask: 0x%llx rval: 0x%llx\n",count,packet->Dsize(),mask,rval);
  return rval;
}

#define A32_MASK 0xffffffffull
#define A32_SIGN_BIT 0x80000000ull

void Control::AddWithCarry32(unsigned long long &result, unsigned int &nzcv, unsigned long long op1,unsigned long long op2,unsigned long long carry_in) {
    op1 &= A32_MASK;
    op2 &= A32_MASK;
  
    unsigned long long unsigned_sum = op1 + op2 + carry_in;
    
    result = unsigned_sum & 0xffffffffull;

    unsigned long long op1_sign = op1 & A32_SIGN_BIT;
    unsigned long long op2_sign = op2 & A32_SIGN_BIT;
    unsigned long long result_sign = result & A32_SIGN_BIT;

    //printf("[AddWithCarry32] op1 sign: 0x%llx, op2 sign: 0x%llx, result sign: 0x%llx\n",op1_sign,op2_sign,result_sign);
    
    int N = (unsigned_sum & A32_SIGN_BIT) > 0; // result<N-1> set Negative flag
    int Z = (result == 0) ? 1 : 0;           // set zero flag...
    int C = (result != unsigned_sum);        // set Carry out flag if unsigned result exceeds 32 bits
    int V = (op1_sign == op2_sign) && (result_sign != op1_sign);  // set V if signed result differs from unsigned result
    
    nzcv = (N<<3) | (Z<<2) | (C<<1) | V;

    //printf("[AddWithCarry32] op1: 0x%llx op2: 0x%llx C: 0x%llx unsigned-sum: 0x%llx, result: 0x%llx nzcv: %u (%d/%d/%d/%d)\n",
    //       op1,op2,carry_in,unsigned_sum,result,nzcv,N,Z,C,V);
}

bool Control::uadd64_overflow(unsigned long long op1,unsigned long long op2,unsigned long long Cin) {
  unsigned long long A = op1>>32;                   // hi order 32 bits of operand1
  unsigned long long B = op1 & 0xffffffffull;       // lo           "

  unsigned long long C = op2>>32;                   // hi order 32 bits of operand1
  unsigned long long D = op2 & 0xffffffffull;       // lo           "

  unsigned long long resLo = B + D + Cin;           // low order 32 bit addition with carry in, 
  unsigned long long resLoOverflow = resLo >> 32;   //    overflow will be to upper 32 bits, shift to lo order 32 bits

  unsigned long long resHi = A + C + resLoOverflow; // hi order 32 bit addition with overflow from lo order addition,
  unsigned long long resHiOverflow = resHi >> 32;   //    overflow will be to upper 32 bits

  return (resHiOverflow > 0);
}

void Control::AddWithCarry64(unsigned long long &result, unsigned int &nzcv, unsigned long long op1,unsigned long long op2,unsigned long long carry_in) {
    unsigned long long unsigned_sum = op1 + op2 + carry_in; 
    long long int      signed_sum   = SignExtend(op1,packet->Dsize()) + SignExtend(op2,packet->Dsize()) + carry_in;

    result = unsigned_sum;

    int N = (unsigned_sum>>63) == 1;              // result<N-1> set Negative flag
    int Z = (result == 0);                        // set Zero flag
    int C = uadd64_overflow(op1,op2,carry_in);    // use out own function to check for overflow
    int V = (long long int) result != signed_sum; // set V if signed result differs from unsigned result
    
    nzcv = (N<<3) | (Z<<2) | (C<<1) | V;

    //printf("[AddWithCarry64] op1: 0x%llx op2: 0x%llx C: 0x%llx result: 0x%llx nzcv: %u (%d/%d/%d/%d)\n",op1,op2,carry_in,result,nzcv,N,Z,C,V);
}

void Control::AddWithCarry(unsigned long long &result, unsigned int &nzcv, unsigned long long op1,unsigned long long op2,unsigned long long carry_in) {
  if (packet->Dsize()==64) 
    AddWithCarry64(result,nzcv,op1,op2,carry_in);
  else
    AddWithCarry32(result,nzcv,op1,op2,carry_in);

  //printf("[AddWithCarry] op1: 0x%llx op2: 0x%llx C: 0x%llx\n",op1,op2,carry_in);
}

//**************************************************************************************************************
// ExtendReg - shift left register value, then sign extend...
//
//    rval        - the register value
//    extend_type - indicates the size of the value held by the register in bits. also indicates whether or
//                  not the value is signed
//    shift       - the shift amount
//    N           - the register width (32 vs 64 bits)
//
//  process:
//    1. according to the value size, mask off left shifted high order bits, ie, the bits shifted out of the value
//    2. left shift the value
//    3. sign extend the masked-off value if necessary
//**************************************************************************************************************

unsigned long long Control::ExtendReg(unsigned long long rval,int extend_type,int shift, int N) {
  //printf("[Control::ExtendReg] rval: 0x%llx extend-type: %d, shift: %d, register-width: %d\n",rval,extend_type,shift,N);

  bool is_signed = false;
  int len = 0;
  unsigned long long mask = 0;
  
  switch(extend_type) {
    case 0: is_signed = false; len = 8;  mask = 0xffull;               break; //
    case 1: is_signed = false; len = 16; mask = 0xffffull;             break; // low order m bits of register (of width N)
    case 2: is_signed = false; len = 32; mask = 0xffffffffull;         break; //  represent an unsigned quantity
    case 3: is_signed = false; len = 64; mask = 0xffffffffffffffffull; break; //

    case 4: is_signed = true;  len = 8;  mask = 0xffull;               break; //
    case 5: is_signed = true;  len = 16; mask = 0xffffull;             break; // low order m bits of register (of width N)
    case 6: is_signed = true;  len = 32; mask = 0xffffffffull;         break; //  represent a signed quantity
    case 7: is_signed = true;  len = 64; mask = 0xffffffffffffffffull; break; //

    default: break;
  }

  //printf("[ExtendReg] N: %d shift: %d extend type: %d len: %d, rval (in): 0x%llx mask: 0x%llx is-signed? %d\n",
  //       N, shift, extend_type, len, rval, mask, is_signed);

  rval = (rval & mask) << shift; // val<len-1:0> : Zeros(shift)

  if (is_signed) {
    int field_width = len + shift;
    rval = (unsigned long long) SignExtend(rval,field_width,N); // Extend(val<len-1:0> : Zeros(shift), N, unsigned)
  }

  //printf("[ExtendReg] rval: 0x%llx\n",rval);

  return rval;
}

unsigned long long Control::LSL(unsigned long long rval,int shift_amount) {
  //printf("[LSL] rval: 0x%llx, shift: %d, dsize: %d\n",rval,shift_amount,dsize);

  if (shift_amount == 0) {
    // nothing to do...
  } else {
    rval = rval<<shift_amount; // left shift
    if (packet->Dsize() == 32) rval &= 0xffffffff;    // retain low order 32 bits if length is 32 bits
  }

  //printf("[LSL] result: 0x%llx\n",rval);

  return rval;
}

unsigned long long Control::LSR(unsigned long long rval,int shift_amount) {
  //printf("[LSR] rval: 0x%llx, shift: %d\n",rval,shift_amount);

  if (shift_amount == 0) {
    // nothing to do...
  } else {
    rval = rval>>shift_amount; // right shift
  }

  return rval;
}

unsigned long long Control::ASR(unsigned long long rval,int shift_amount) {
  if (shift_amount == 0) {
    // nothing to do...
  } else {
    unsigned long long sbit = (packet->Dsize() == 64) ? (rval & 0x8000000000000000ull) : (rval & 0x80000000ull);
    for (int i = 0; i < shift_amount; i++) {
      rval = (rval >> 1) | sbit; // shift right, retaining sign bit
    } 
  }

  return rval;
}

unsigned long long Control::ROR(unsigned long long rval,int shift_amount, int data_size) {
  if (data_size == 0)
    data_size = packet->Dsize();
  
  if (shift_amount == 0) {
    // nothing to do...
  } else {
    int m = shift_amount % data_size;
    unsigned long long mask = (data_size==64) ? 0xffffffffffffffffull : 0xffffffffull;
    rval = (rval>>m) | ( (rval<<(data_size - m)) & mask);
  }

  return rval;
}

unsigned long long Control::ShiftReg(unsigned long long rval,int shift_type,int shift_amount) {
  switch(shift_type) {
    case 0: rval = LSL(rval,shift_amount); break;
    case 1: rval = LSR(rval,shift_amount); break;
    case 2: rval = ASR(rval,shift_amount); break;
    case 3: rval = ROR(rval,shift_amount); break;
    default: break;
  }

  return rval;
}

int Control::HighestBitSet( unsigned long long imm, int size ) {
  int rval = -1;

  for (int i = size - 1; i >= 0; i--) {
    if ( ((imm>>i) & 1) == 1) {
        rval = i;
	break;
      }
  }
  
  //printf("     HighestBitSet(0x%llx,%d) ---> %d\n",imm,size,rval);

  return rval;
}

int Control::count_leading_zeros(unsigned long long rval,int dsize) {
   return dsize - 1 - HighestBitSet(rval,dsize);
}

// count leading sign bits - count the # of consecutive bits following
// the top-most bit, that are the same as the topmost bit...

int Control::count_leading_sign_bits(unsigned long long x,int dsize) {
  if (dsize == 32)
    return count_leading_zeros( x ^ ((int) x >> 1), dsize ) - 1;
  
  return count_leading_zeros( x ^ ((long long int) x >> 1), dsize ) - 1;
}


unsigned long long Control::Replicate(unsigned long long bits,unsigned int esize) {
  if ((packet->Dsize() % esize) != 0) {
    // element size should divide evenly into data size...
    packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
    throw ARCH_EXCEPTION;
  }

  unsigned long long rval = 0;

  for (int i = 0; i < packet->Dsize(); i += esize) {
    rval |= bits<<i;
  }

  unsigned long long mask = (packet->Dsize()==64) ? 0xffffffffffffffffull : 0xffffffffull;

  rval &= mask;

  //printf("      Replicate: dsize: %d, esize: %d, bits: 0x%llx returns: 0x%llx\n",packet->Dsize(),esize,bits,rval);

  return rval;
}

unsigned long long Control::DecodeBitMasks(unsigned long long &tmask, unsigned int immN, unsigned int imms, unsigned immr, bool immediate) {
  //printf("[Control::DecodeBitMasks] immN: %d imms: %d immr: %d, imm: %d\n",immN,imms,immr,immediate);

  int len = HighestBitSet( (immN<<6) | ( (~imms) & ( (1<<6)-1) ), 32 );

  //printf("   len: %d\n",len);

  if (len < 1) {
    // reserved value...
    packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
    throw ARCH_EXCEPTION;
  }

  unsigned int levels = Ones(len);  //ZeroExtend(Ones(len),6);

  //printf("   levels: %u\n",levels);

  if (immediate && ((imms & levels)==levels)) {
    // reserved value...
    packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
    throw ARCH_EXCEPTION;
  }

  unsigned int S = imms & levels;
  unsigned int R = immr & levels;

  unsigned int diff = 0;  

  if (R > S) {
    diff = S + 0x40 - R; //6-bit subtract with borrow
  } else {
    diff = S - R;
  }

  unsigned int esize = 1<<len;

  //printf("   S: 0x%x, R: 0x%x, diff: 0x%x, esize: 0x%x\n",S,R,diff,esize);

  unsigned int d = diff & ((1<<len) - 1);

  //printf("   d: 0x%x\n",d);

  unsigned long long welem = Ones(S + 1); //ZeroExtend(Ones(S + 1),esize);
  unsigned long long telem = Ones(d + 1); //ZeroExtend(Ones(d + 1),esize);

  //printf("   welem: 0x%llx telem: 0x%llx\n",welem,telem);

  welem = ROR(welem,R,esize);

  unsigned long long wmask = Replicate(welem,esize);

  tmask = Replicate(telem,esize);

  //printf("[Control::DecodeBitMasks] tmask: 0x%llx, wmask: 0x%llx\n",tmask,wmask);

  return wmask;
}

bool Control::IsZero(unsigned long long rval) {
  if (packet->Dsize() == 64)
    return rval == 0;
  return (rval & 0xffffffffull) == 0;
}

unsigned long long Control::Not(unsigned long long rval) {
  rval = ~rval;
  if (packet->Dsize() == 32) rval &= 0xffffffffull;
  return rval;
}

// 'sized' (sf field present in instruction encoding) instructions operate on registers of either 32 or 64 bits...
unsigned long long Control::srcRegValue(unsigned long long rval) {
  return (packet->Dsize()==64) ? rval : rval & 0xffffffff;
}

//---------------------------------------------------------------------------------------------------------------------------
// all register values stored as unsigned long long. Size register values according to current instruction size...
//---------------------------------------------------------------------------------------------------------------------------

void Control::SizeSourceOperands() {
  if (packet->sf.IsDefined()) { 
    packet->setDsize( packet->sf.Value()==1 ? 64 : 32 );
    
    if (packet->Nreg.IsSet())  packet->Nreg.Value(  srcRegValue(packet->Nreg.Value())  );
    if (packet->Mreg.IsSet())  packet->Mreg.Value(  srcRegValue(packet->Mreg.Value())  );
    if (packet->Treg.IsSet())  packet->Treg.Value(  srcRegValue(packet->Treg.Value())  );
    if (packet->T2reg.IsSet()) packet->T2reg.Value( srcRegValue(packet->T2reg.Value()) );
    if (packet->RSreg.IsSet()) packet->RSreg.Value( srcRegValue(packet->RSreg.Value()) );
    if (packet->RAreg.IsSet()) packet->RAreg.Value( srcRegValue(packet->RAreg.Value()) );
  }
}

void Control::SizeDestOperands() {
  if (packet->sf.IsDefined()) {
    if (packet->Dreg.IsSet())   packet->Dreg.Value(  srcRegValue(packet->Dreg.Value())  );
    if (packet->Dreg2.IsSet())  packet->Dreg2.Value( srcRegValue(packet->Dreg2.Value()) );
  }
}


//---------------------------------------------------------------------------------------------------------------------------
// add/subtract...
//---------------------------------------------------------------------------------------------------------------------------

void Control::ExecuteAddSubtract() {
  //printf("[ExecuteAddSubtract] entered...\n");
  
    bool sub_op = (packet->op.Value()==1);

    unsigned long long operand1 = packet->Nreg.Value();
    unsigned long long operand2 = 0;
    unsigned long long carry_in = 0;

    int regsize = packet->Dsize(); // width specifier

    switch(instrID) {
       case ADD_IMM_32: case ADD_IMM_64: case ADDS_IMM_32: case ADDS_IMM_64:
       case SUB_IMM_32: case SUB_IMM_64: case SUBS_IMM_32: case SUBS_IMM_64: 
                         if (packet->shift.Value() > 1) {
                            // invalid shift...
                            packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                            throw ARCH_EXCEPTION;
                         }
                         operand2 = packet->shift.Value()==1 ? packet->imm12.Value()<<12 : packet->imm12.Value();
		         carry_in = sub_op ? 1 : 0;
		         break;

       case ADC_32: case ADC_64: case ADCS_32: case ADCS_64: case SBC_32:
       case SBC_64: case SBCS_32: case SBCS_64:     
	                 operand2 = packet->Mreg.Value();
		         carry_in = packet->Pstate.C();
                         break;

       case ADD_REG_32: case ADD_REG_64: case ADDS_REG_32: case ADDS_REG_64:
       case SUB_REG_32: case SUB_REG_64: case SUBS_REG_32: case SUBS_REG_64: 
                         {
                         int shift = packet->imm3.Value();
		         if (shift > 4) {
                             // invalid shift...
                             packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                             throw ARCH_EXCEPTION;
                         }
			 
 		         int extend_type = packet->option.Value();

			 int reg_width = regsize;
                         if ( (packet->option.Value() & 3) != 3 )
                           reg_width = 32;

			 unsigned long long operand2_src = packet->Mreg.Value();

			 //printf("operand2_src: 0x%llx\n",operand2_src);
			 if (reg_width == 32)
			   operand2_src &= 0xffffffff;
			 
                         operand2 = ExtendReg(operand2_src,extend_type,shift,regsize);

			 //printf("operand2: 0x%llx\n",operand2);
			 
		         carry_in = sub_op ? 1 : 0;
		         }
                         break;

       case ADD_SHIFT_REG_32: case ADD_SHIFT_REG_64: case ADDS_SHIFT_REG_32: case ADDS_SHIFT_REG_64:
       case SUB_SHIFT_REG_32: case SUB_SHIFT_REG_64: case SUBS_SHIFT_REG_32: case SUBS_SHIFT_REG_64: 
                         {
		         int shift_type = packet->shift.Value();
		         int shift_amount = packet->imm6.Value();
		         if (shift_type == 3) {
                             // invalid shift...
                             packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                             throw ARCH_EXCEPTION;
                         }
                         if (packet->Dsize() == 32 && shift_amount >= 32) {
                             // shift greater than invalid shift...
                             packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                             throw ARCH_EXCEPTION;
                         }
                         operand2 = ShiftReg(packet->Mreg.Value(),shift_type,shift_amount);
		         carry_in = sub_op ? 1 : 0;
		         }
                         break;

	default: break;
	}

        if (sub_op) { 
          operand2 = ~operand2; 
          if (packet->Dsize() == 32) {
	    operand1 &= 0xffffffffull;
	    operand2 &= 0xffffffffull;
	  }
        }

	unsigned long long result;
        unsigned int nzcv_in = packet->Pstate.NZCV();
        unsigned int nzcv = nzcv_in;

        AddWithCarry(result,nzcv,operand1,operand2,carry_in);

	if (regsize == 32)           // we think
	  result &= 0xffffffffull;   //  width specifier affects result???
	
        //printf("[ExecuteAddSubtract] NZCV (in): 0x%x dsize: %d op1: 0x%llx op2: 0x%llx C(in): 0x%llx, result: 0x%llx, NZCV (out): 0x%x\n",
        //       nzcv_in,regsize,operand1,operand2,carry_in,result,nzcv);

        packet->Dreg.Value(result);

        if (packet->S.Value()==1) 
            packet->NextPstate.NZCV(nzcv);

	//printf("[ExecuteAddSubtract] exited.\n");
}


//---------------------------------------------------------------------------------------------------------------------------
// move immediate...
//---------------------------------------------------------------------------------------------------------------------------

void Control::ExecuteMoveImmediate() {
   if ( (packet->sf.Value()==0) && ((packet->hw.Value() & 2) == 2) ) {
      // illegal shift value for target operand size...
      packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
      throw ARCH_EXCEPTION;
   }             

   int shift = 0;

   switch(instrID) {
     case MOVN_IMM_32: 
     case MOVZ_IMM_32:
     case MOVK_IMM_32:
     case MOVN_IMM_64:
     case MOVZ_IMM_64:
     case MOVK_IMM_64: shift = packet->hw.Value() * 16; // shift is 0, 16, 32, 48
		       break;

     default:          break;
   }

   switch(packet->A64InstrIndex) {
     case MOVN_IMM_32:
     case MOVN_IMM_64: {
                       unsigned long long result = ~( ((unsigned long long) packet->imm16.Value())<<shift);
                       if (packet->sf.Value()==0) result &= 0xffffffffull;
                       packet->Dreg.Value(result); 
                       }
                       break;
     case MOVZ_IMM_32:
     case MOVZ_IMM_64: packet->Dreg.Value(((unsigned long long) packet->imm16.Value()) << shift);
                       break;
     case MOVK_IMM_32:
     case MOVK_IMM_64: {
                       unsigned long long replace_bits        = 0xffffull<<shift;
                       unsigned long long bits_to_retain_mask = ~replace_bits;
                       unsigned long long insert_bits         = ((unsigned long long) packet->imm16.Value())<<shift;
                       //printf("[MOVK] hw: %u shift: %u replace-bits: 0x%llx retain-bits: 0x%llx insert-bits: 0x%llx\n",
                       //       packet->hw.Value(),shift,replace_bits,bits_to_retain_mask,insert_bits);
                       packet->Dreg.Value((packet->Dreg.Value() & bits_to_retain_mask) | insert_bits);
		       }
                       break;
     default: break;
   }
}


//---------------------------------------------------------------------------------------------------------------------------
// MSR, MRS...
//---------------------------------------------------------------------------------------------------------------------------

void Control::ExecuteMRS_MSR() {
  switch(instrID) {
  case MRS:     {
                int rindex;
                unsigned long long rval;

                int rcode = cpu->SystemRegisterGet(rindex,rval,packet->op0.Value(),packet->op1.Value(),packet->CRn.Value(),packet->CRm.Value(),packet->op2.Value());

                packet->srcRegDep.push_back(RegDep(DEP_SPR | rindex,rval)); // record spr accessed even if exception results

                if (rcode) {
		  if (cpu->SystemRegisterTrapOutcome(rcode)) {
		   //printf("[MRS] Exception: trap on access to system-register exception...\n");
                   packet->recordExceptionCondition(TRAP);
		  } else {
		   //printf("[MRS] Exception: inability to access system register results in undef exception...\n");
                   packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
		  }
                  throw ARCH_EXCEPTION;
                }             

                packet->Dreg.Value(rval);
                }
                break;

  case MSR_IMM: {
                int rindex = 0;
                if (cpu->PstateAccess(rindex,packet->op1.Value(),packet->op2.Value())) {
                   // invalid op1:op2 combo...
                   packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                   throw ARCH_EXCEPTION;
                }

                if (cpu->CheckSystemRegisterAccess(rindex)) {
                   // inability to access system register results in undef exception...
                   packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                   throw ARCH_EXCEPTION;
                }

		// check that MSR/MRS access to DAIF flags is permitted...
		if (packet->op1.Value()==3 && packet->Pstate.EL()==0 && cpu->SCTLR_EL1.UMA()==0) {
		  SystemRegisterTrap(1,0,packet->op2.Value(),packet->op1.Value(),packet->CRn.Value(),packet->Rt.Value(),packet->CRm.Value(),0);
                }

                unsigned int operand = packet->CRm.Value(); // four bit immediate
                unsigned int pstate_field_value = 0; //<---will update only SP or DAIF fields of Pstate

                switch((int) (packet->op1.Value()<<3 | packet->op2.Value())) {
		  case 0x5:   // PSTATEfield_SPSel;
		              if (operand > 1) {
                                // imm4<3:1> values are reserved...
                                packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                                throw ARCH_EXCEPTION;
		              }
		              pstate_field_value = operand & 1;
		              break;

		  case 0x1e:  // PSTATEfield_DAIFSet;
		              operand = (operand & 0xf)<<6; // isolate/move lo order 4 bits of operand to pstate DAIF...
		              pstate_field_value = packet->Pstate.DAIF() | operand; // set one or more DAIF flags...
		              break;

                  case 0x1f:  // PSTATEfield_DAIFClr;
		              operand = (~operand & 0xf)<<6; // invert/isolate/move lo order 4 bits of operand to pstate DAIF...
		              pstate_field_value = packet->Pstate.DAIF() | operand; // clear one or more DAIF flags...
		              break;

		  default:    // probably an internal error...
                              packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                              throw ARCH_EXCEPTION;
		              break;
		}

                packet->Sreg.Value(rindex);              // Pstate field (encoded system register index),
                packet->Treg.Value(pstate_field_value);  //    Pstate field value
                }
                break;

  case MSR_REG: {
                int rindex = -1;
                unsigned long long rval = 0;

		// read system register to get its index and check its accessibility (discard value read)...

                int rcode = cpu->SystemRegisterGet(rindex,rval,packet->op0.Value(),packet->op1.Value(),packet->CRn.Value(),packet->CRm.Value(),packet->op2.Value());

                if (rcode) {
		  if (cpu->SystemRegisterTrapOutcome(rcode)) {
		    //printf("[MRS] Exception: trap on access to system-register exception...\n");
                    packet->recordExceptionCondition(TRAP);
		  } else {
                    // inability to access system register results in undef exception...
                    packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
		  }
                  throw ARCH_EXCEPTION;
		}

                packet->Sreg.Value(rindex);                        // encoded system register index, 
                //unsigned long long rval = packet->Treg.Value();  //   already available value
                }
                break;

   default:     break;
  }
}


//---------------------------------------------------------------------------------------------------------------------------
// Logical - OR, AND, EOR
//---------------------------------------------------------------------------------------------------------------------------

void Control::ExecuteLogical() {
  //printf("\n[Control::ExecuteLogical] entered...\n");

  unsigned long long operand1 = packet->Nreg.Value();
  //printf("\toperand1: 0x%llx\n",operand1);

  //unsigned long long src_operand2 = packet->Mreg.Value();
  //printf("\tsrc operand2: 0x%llx\n",src_operand2);

  int op = -1;
  bool set_flags = false;

  enum {DO_AND,DO_ORR,DO_EOR};

  string ops = "?";

  switch(packet->opc.Value()) {
    case 0: op = DO_AND; /* ops = "AND"; */ set_flags = false; break;
    case 1: op = DO_ORR; /* ops = "ORR"; */ set_flags = false; break;
    case 2: op = DO_EOR; /* ops = "EOR"; */ set_flags = false; break;
    case 3: op = DO_AND; /* ops = "AND"; */ set_flags = true;  break;
    default: break;
  }

  //printf("\top: %s dsize: %d N: %d sf: %d imm6: %d\n",ops.c_str(),packet->Dsize(),packet->N.Value(),packet->sf.Value(),packet->imm6.Value());

  unsigned long long operand2 = 0;

  switch(instrID) {
     case AND_IMM_32: case AND_IMM_64: case ANDS_IMM_32: case ANDS_IMM_64: case ORR_IMM_32: case ORR_IMM_64: case EOR_IMM_32: case EOR_IMM_64:
            {
            if ( (packet->Dsize()==32) && (packet->N.Value()==1) ) {
	       // N bit set with 32 bit data size - reserved value...
               packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
               throw ARCH_EXCEPTION;
            }
            unsigned long long imm_mask;
            unsigned long long imm = DecodeBitMasks(imm_mask, packet->N.Value(),packet->imms.Value(),packet->immr.Value(), true);
            //printf("[Control::ExecuteLogical] logical immediate op, imm: 0x%llx...\n",imm);          
            operand2 = imm;
            }
            break;
     case AND_SHIFT_REG_32: case AND_SHIFT_REG_64: case ANDS_SHIFT_REG_32: case ANDS_SHIFT_REG_64: case ORR_SHIFT_REG_32: 
     case ORR_SHIFT_REG_64: case ORN_SHIFT_REG_32: case ORN_SHIFT_REG_64: case EOR_SHIFT_REG_32: case EOR_SHIFT_REG_64: 
     case EON_SHIFT_REG_32: case EON_SHIFT_REG_64:
            {
	    //printf("\tshifted register...\n");
            if ( (packet->sf.Value()==0) & (packet->imm6.Value() >= 32) ) {
	       // shift amount too large...
               packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
               throw ARCH_EXCEPTION;
            }
            int shift_type = packet->shift.Value();
            unsigned int shift_amount = packet->imm6.Value();
            bool invert = packet->N.Value() == 1;
            //printf("\tshift-type: %d shift-amount: %d invert? %d\n",shift_type,shift_amount,invert);
            //printf("[Control::ExecuteLogical] shifted register, M op: 0x%llx\n",packet->Mreg.Value()); 
            //printf("\tM val: 0x%llx\n",packet->Mreg.Value());
            operand2 = ShiftReg(packet->Mreg.Value(),shift_type,shift_amount);
            //printf("\toperand2: 0x%llx invert? %d\n",operand2,invert);
            if (invert) operand2 = Not(operand2);
            //printf("\toperand2 (inverted): 0x%llx\n",operand2);
            }
	    break;

    default: break;
  }

  unsigned long long result = 0;

  switch(op) {
     case DO_AND: result = operand1 & operand2; 
                  break;
     case DO_ORR: result = operand1 | operand2; 
                  break;
     case DO_EOR: result = operand1 ^ operand2; 
                  break;
     default: break;
  }

  packet->Dreg.Value(result);

  //printf("[Control::ExecuteLogical] exited, operand1: 0x%llx operand2: 0x%llx result:0x%llx\n\n",operand1,operand2,result);

  if (set_flags) {
    // set all flags...
    // check sign bit of result...
    unsigned long long Nbit = (packet->Dsize()==64) ? 0x8000000000000000ull : 0x80000000ull;
    int Nflag = ( (result & Nbit)==Nbit ) ? 1 : 0;
    packet->NextPstate.N(Nflag);            // result could be negative
    packet->NextPstate.Z(IsZero(result));   //  or zero
    packet->NextPstate.C(0);                // but no overflow
    packet->NextPstate.V(0);                //  or underflow
 }
}


bool Control::ConditionHolds(unsigned int cond) {
  bool result = false;

  switch( (int) (cond>>1) ) {
    case 0:  result = packet->Pstate.Z() == 1;                                                      break; // EQ or NE
    case 1:  result = packet->Pstate.C() == 1;                                                      break; // CS or CC
    case 2:  result = packet->Pstate.N() == 1;                                                      break; // MI or PL
    case 3:  result = packet->Pstate.V() == 1;                                                      break; // VS or VC
    case 4:  result = (packet->Pstate.C() == 1) && (packet->Pstate.Z() == 0);                       break; // HI or LS
    case 5:  result = packet->Pstate.N() == packet->Pstate.V();                                     break; // GE or LT
    case 6:  result = (packet->Pstate.N() == packet->Pstate.V()) && (packet->Pstate.Z() == 0);      break; // GT or LE
    case 7:  result = true;                                                                         break; // AL

    default: packet->recordExceptionCondition(INVALID_CONDITION); 
             throw INTERNAL_ERROR; 
             break;
  }

  if ( ((cond & 1) == 1) && (cond != 0xf) )
    result = !result;

  //printf("[Control::ConditionHolds] PC: 0x%llx Z/C/N/V: %u/%u/%u/%u cond: %u (%u/%u) result: %u\n",
  //       packet->PC.Value(), packet->Pstate.Z(),packet->Pstate.C(),packet->Pstate.N(),packet->Pstate.V(),
  //       cond,(cond>>1),(cond&1),result);

  return result;
}

void Control::CheckBranchTargetAlignment(unsigned long long nextPC) {
  if ((nextPC & 3) != 0) {
      // RESULT IS MISALIGNED PC...
      packet->recordExceptionCondition(MISALIGNED_PC); 
      throw ARCH_EXCEPTION;
  }
}


void Control::CheckStackAlignment() {
  bool stack_align_check = false;

  switch((int) packet->Pstate.EL()) {
    case 0: stack_align_check = cpu->SCTLR_EL1.SA0()==1; 
            break;
    case 1: stack_align_check = cpu->SCTLR_EL1.SA()==1;  
            break;
    case 2: stack_align_check = cpu->HaveEL(EL2) && cpu->SCTLR_EL2.SA()==1;  
            break;
    case 3: stack_align_check = cpu->HaveEL(EL3) && cpu->SCTLR_EL3.SA()==1; 
            break;
    default: packet->recordExceptionCondition(INVALID_EXCEPTION_LEVEL); 
             throw INTERNAL_ERROR; 
             break;
  }

  if (stack_align_check) {
    if ( ((cpu->GetSP()).Value() & 0x7) != 0) {
      // current stack is not aligned to 16 bit boundary...
      packet->recordExceptionCondition(STACK_POINTER_ALIGNMENT); 
      throw ARCH_EXCEPTION;
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------------
// branch, conditional branch, return...
//---------------------------------------------------------------------------------------------------------------------------

void Control::Branch() {
  switch(instrID) {
    case BL:    packet->Dreg.Value( packet->PC.Value() + 4); // branch and link - set return address

    case B_IMM:      
    case B_COND_IMM:
    case CBNZ_IMM_32: 
    case CBNZ_IMM_64: 
    case CBZ_IMM_32: 
    case CBZ_IMM_64:
    case TBNZ: 
    case TBZ:
                {
                int bit_position = packet->b5.Value()<<4|packet->b40.Value();
                int bit = (packet->Treg.Value()>>bit_position) & 1;

		if (instrID==B_COND_IMM && !ConditionHolds(packet->cond.Value())) {
                  break;
		}
		if ((instrID==CBNZ_IMM_32 || instrID==CBNZ_IMM_64) && IsZero(packet->Treg.Value())) break;
		if ((instrID==CBZ_IMM_32  || instrID==CBZ_IMM_64)  && !IsZero(packet->Treg.Value())) break;
                if (instrID==TBNZ && bit==0) break;
                if (instrID==TBZ && bit==1) break;

                long long offset = 0;
                switch(instrID) {
                  case B_IMM:         offset = SignExtend(packet->imm26.Value()<<2,28); break;
		  case TBNZ:case TBZ: offset = SignExtend(packet->imm14.Value()<<2,16); break;
                  case BL:            offset = SignExtend(packet->imm26.Value()<<2,28); break;
		  default:            offset = SignExtend(packet->imm19.Value()<<2,21); break;
		}
                long long base = packet->PC.Value();
                unsigned long long nextPC = (unsigned long long) (base + offset);
                CheckBranchTargetAlignment(nextPC);
                packet->NextPC.Value( nextPC );
                //printf("[Branch] base (current PC): 0x%llx offset: 0x%llx (imm19: 0x%x) resulting (next) PC: 0x%llx\n",
                //       base,offset,packet->imm19.Value(),packet->NextPC.Value()); 
                }
                break;

              
    case BLR:   packet->Dreg.Value( packet->PC.Value() + 4); // branch and link register - set return address
    case BR:                                                 // just branch                                      
                // in the absence of architectual 'hints' BR and RET are equivalent instructions insofar as branch address is concerned...
    case RET:   {
                unsigned long long nextPC = packet->Nreg.Value();
                CheckBranchTargetAlignment(nextPC);
                packet->NextPC.Value( nextPC );
                }
                break;

    default: 
                packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                throw ARCH_EXCEPTION;
                break;
  }
}


//---------------------------------------------------------------------------------------------------------------------------
// generate label or page address...
//---------------------------------------------------------------------------------------------------------------------------

void Control::LabelOrPageAddress() {
  unsigned long long imm_val = ( ((unsigned long long) packet->immhi.Value())<<2 ) | ((unsigned long long) packet->immlo.Value());
  
  switch(instrID) {
    case ADR:  {
                long long signed_imm = SignExtend( imm_val, 21 );
                long long base = packet->PC.Value();
                unsigned long long page_address = (unsigned long long)(base + signed_imm);
                CheckBranchTargetAlignment(page_address); // will ASSUME resulting PC-relative address must be aligned...
                packet->Dreg.Value(page_address); 
               }	     
               break;

    case ADRP: {
                long long signed_imm = SignExtend( imm_val<<12, 33 );
                long long base = (long long) ((packet->PC.Value()>>12)<<12); //<---shift off low order 12 bits to yield 4k page address
	        //printf("[ADRP] immhi: 0x%x immlo: 0x%x signed-imm: %lld (0x%llx) PC: 0x%llx base: %lld (0x%llx) addr: %lld (0x%llx)\n",
	       	//       packet->immhi.Value(),packet->immlo.Value(),signed_imm,signed_imm,packet->PC.Value(),base,base,(base + signed_imm),(base + signed_imm));
                packet->Dreg.Value((unsigned long long) (base + signed_imm)); 
               }	     
               break;
  default:     packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
               throw ARCH_EXCEPTION;
               break;
  }
}


//---------------------------------------------------------------------------------------------------------------------------
// All float or SIMD opcodes now handled elsewhere...
//--------------------------------------------------------------------------------------------------------------------------

void Control::FloatSIMD() {
  // add some code dude!...
  printf("WARNING: attempted execution of unimplemented float/simd instruction. Ignored (for now)...\n");
}

//---------------------------------------------------------------------------------------------------------------------------
// All Hint opcodes...
//---------------------------------------------------------------------------------------------------------------------------

void Control::Hint() {
  switch(instrID) {
  case HINT:         // effectively a NOP since interesting aliases picked off separately...
                     break;

  case NOP:          // my favorite instruction...
                     break;
		     		     
  case WFE:          // event notification...
#ifdef KERNEL_DEBUG
                     printf("WFE - CORE IS WAITING FOR EVENT!!!\n");
                     fflush(stdout);
#endif
                     throw WAIT_FOR_EVENT;
                     break;
  case WFI:
#ifdef KERNEL_DEBUG
                     printf("WFI - CORE IS WAITING FOR INTERRUPT!!!\n");
                     fflush(stdout);
#endif
                     throw WAIT_FOR_INTERRUPT;
                     break;
		     
  case SEV:
#ifdef KERNEL_DEBUG
                     printf("SEV - WAKE UP CORES!!!\n");
                     fflush(stdout);
#endif
                     throw EVENT_NOTICE;
                     break;

  case SEVL:
#ifdef KERNEL_DEBUG
                     printf("SEVL - WAKE UP LOCAL(?) CORES!!!\n");
                     fflush(stdout);
#endif
                     throw EVENT_NOTICE_LOCAL;
                     break;

  case YIELD:
                     break;
  case DSB:
                     break;
  case ISB:
                     break;
  case DMB:
                     break;

  default:    packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
              throw ARCH_EXCEPTION;
              break;
  }
}


//---------------------------------------------------------------------------------------------------------------------------
// shift ops...
//---------------------------------------------------------------------------------------------------------------------------

void Control::ShiftOps() {
  switch(instrID) {
  case ASRV_32: 
  case ASRV_64: 
  case LSLV_32: 
  case LSLV_64:
  case LSRV_32: 
  case LSRV_64:
  case RORV_32: 
  case RORV_64:
                     {
		     int opc = packet->opcode.Value() & 0x3;    // opcode 'field' is bits 15..10, opc is 11,10

		     int shift_type   = opc;
                     int shift_amount = packet->Mreg.Value() % packet->Dsize();

                     unsigned long long result = ShiftReg(packet->Nreg.Value(),shift_type,shift_amount);
                     packet->Dreg.Value(result);
                     }
                     break;
  case EXTR_32: 
  case EXTR_64:
                     {
                     if (packet->N.Value() != packet->sf.Value()) {
		        // unallocated encoding...
                        packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                        throw ARCH_EXCEPTION;
                     } 
                     if (packet->sf.Value()==0 && (packet->imms.Value()>>5)==1) {
		        // reserved value...
                        packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                        throw ARCH_EXCEPTION;
                     } 
                     unsigned lsb = packet->imms.Value();
                     unsigned long long operand1 = packet->Nreg.Value();
                     unsigned long long operand2 = packet->Mreg.Value();

                     int dwidth = (packet->sf.Value() == 1) ? 64 : 32;

		     // shift operand1 left, retaining low ordered bits positioned to or into low-order bits
		     unsigned long long upper_bits = ( (dwidth-lsb) < 64 ) ? operand1<<(dwidth-lsb) : 0;  // shift value greater than operand width is undefined
		     unsigned long long lower_bits = operand2>>lsb; //<---heres the low order bits
		     
                     unsigned long long result = upper_bits | lower_bits;  //<---(op1:op2)>>lsb

                     packet->Dreg.Value(result);
                     }
                     break;

  default:           packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                     throw ARCH_EXCEPTION;
                     break;
  }
}


//---------------------------------------------------------------------------------------------------------------------------
// conditional...
//---------------------------------------------------------------------------------------------------------------------------

void Control::Conditional() {
  switch(instrID) {
    case CSEL_32: 
    case CSEL_64: 
    case CSINC_32: 
    case CSINC_64: 
    case CSINV_32: 
    case CSINV_64: 
    case CSNEG_32: 
    case CSNEG_64:
                     {
                       unsigned int cond = packet->cond.Value();
	               bool else_inv = packet->op.Value()==1;
                       bool else_inc = packet->op2.Value()==1;

	               unsigned long long operand1 = packet->Nreg.Value();
	               unsigned long long operand2 = packet->Mreg.Value();

                       unsigned long long result = 0;

                       if (ConditionHolds(cond)) {
	                 result = operand1;
	               } else {
	                 result = operand2;
                         if (else_inv) result = Not(result);
                         if (else_inc) result = result + 1;
	               }
                       packet->Dreg.Value(result);
                     }
                     break;

    default:         packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                     throw ARCH_EXCEPTION;
                     break;
  }
}


//---------------------------------------------------------------------------------------------------------------------------
// comparison...
//---------------------------------------------------------------------------------------------------------------------------

void Control::Comparison() {
  unsigned int carry_in = 0;
  bool sub_op = packet->op.Value()==1;
  unsigned long long operand1 = packet->Nreg.Value();
  unsigned int condition = packet->cond.Value();
  unsigned int nzcv = packet->nzcv.Value();

  unsigned long long operand2;

  switch(instrID) {
    case CCMN_IMM_32: 
    case CCMN_IMM_64: 
    case CCMP_IMM_32: 
    case CCMP_IMM_64: operand2 = packet->imm5.Value();
                      break;
    case CCMN_REG_32: 
    case CCMN_REG_64: 
    case CCMP_REG_32: 
    case CCMP_REG_64: operand2 = packet->Mreg.Value(); 
                      break;

    default:          packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                      throw ARCH_EXCEPTION;
                      break;
  }

  if (ConditionHolds(condition)) {
    if (sub_op) {
      operand2 = Not(operand2);
      carry_in = 1;
    }
    unsigned long long result; //<---will ignore results (just want flags)
    AddWithCarry(result,nzcv,operand1,operand2,carry_in);
  }

  packet->NextPstate.NZCV(nzcv);
}


//---------------------------------------------------------------------------------------------------------------------------
// bit field, bit counting, reverse byte...
//---------------------------------------------------------------------------------------------------------------------------

void Control::BitFieldOrCounts() {
  switch(instrID) {
    case BFM_32: 
    case BFM_64: 
    case SBFM_32: 
    case SBFM_64: 
    case UBFM_32: 
    case UBFM_64: 
                     {
                     bool inzero,extend;
                     switch(packet->opc.Value()) {
                       case 0: inzero=true;  extend = true;  break; // SBFM
                       case 1: inzero=false; extend = false; break; // BFM
                       case 2: inzero=true;  extend = false; break; // UBFM
                       default: // unallocated encoding...
                                packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                                throw ARCH_EXCEPTION;
                                break;
                     }
                     if (packet->sf.Value()==1 && packet->N.Value()!=1) {
	                 // reserved value...
                         packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                         throw ARCH_EXCEPTION;
                     }
                     if ( packet->sf.Value()==0 && (packet->N.Value()!=0 || packet->immr.Value()>=32 || packet->imms.Value()>=32) ) {
	                 // reserved value...
                         packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                         throw ARCH_EXCEPTION;
                     }
                     unsigned int N = packet->N.Value();
                     unsigned int R = packet->immr.Value();
                     unsigned int S = packet->imms.Value();

                     //printf("   N = %u, R = %u, S = %u\n",N,R,S);

                     unsigned long long tmask = 0;
                     unsigned long long wmask = DecodeBitMasks(tmask,N,S,R,false);

                     //printf("  tmask: 0x%llx wmask: 0x%llx\n",tmask,wmask);

                     unsigned long long dst = (inzero) ? 0 : packet->Dreg.Value();
                     unsigned long long src = packet->Nreg.Value();

                     //printf(" src: 0x%llx R: 0x%x ROR(src,R): 0x%llx\n",src,R,ROR(src,R));

                     unsigned long long bot = (dst & Not(wmask)) | (ROR(src,R) & wmask);

                     unsigned long long top = 0;

                     if (extend) {
		        //printf("  extend = true, dsize: %d\n",dsize);
		        unsigned long long sign_bit = (1ull<<S) & src;
		        bool sign_bit_set = sign_bit != 0ull;
		        if (sign_bit_set) {
                          //printf("  sign bit IS set...\n");
                          sign_bit = ROR(sign_bit,R);
                          for (unsigned int i = packet->Dsize() - 1; (1ull<<i) != sign_bit; i--) {
			     top = top | (1ull<<i);
			  }
		        } else {
                          //printf("  sign bit is NOT set...\n");
                        }
		     } else {
		        //printf("  extend = false...\n");
                        top = dst;
		     }

                     //printf("  bot: 0x%llx top: 0x%llx\n",bot,top);

                     unsigned long long result = (top & Not(tmask)) | (bot & tmask);

                     //printf("  result: 0x%llx\n",result);

                     packet->Dreg.Value(result);
                     }
                     break;

    case BIC_SHIFT_REG_32:
    case BIC_SHIFT_REG_64: 
    case BICS_SHIFT_REG_32: 
    case BICS_SHIFT_REG_64:
                     {
	             if ( packet->sf.Value()==0 && packet->imm6.Value()>=32 ) {
	                // reserved value...
                        packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                        throw ARCH_EXCEPTION;
                     }

                     bool invert = packet->N.Value()==1;

                     bool set_flags = packet->opc.Value()==3;

                     unsigned long long operand1 = packet->Nreg.Value();
                     unsigned long long operand2 = ShiftReg(packet->Mreg.Value(),packet->shift.Value(),packet->imm6.Value());

	             if (invert) operand2 = Not(operand2);

                     unsigned long long result = 0;
                     switch(packet->opc.Value()) {
                        case 0: result = operand1 & operand2; break;
                        case 1: result = operand1 | operand2; break;
                        case 2: result = operand1 ^ operand2; break;
                        case 3: result = operand1 & operand2; break;
	                default: break;
	             }

                     packet->Dreg.Value(result);
      
                     if (set_flags) {
                       unsigned int N = (result>>(packet->Dsize()-1)) & 1;
                       unsigned int Z = (result==0) ? 1 : 0;
                       unsigned int flags = (N<<3) | (Z<<2) | 0; 
	               packet->NextPstate.NZCV(flags);
	             }
                     }
                     break;

    case CLS_32: 
    case CLS_64: 
    case CLZ_32: 
    case CLZ_64:
                     {
                     unsigned long long operand1 = packet->Nreg.Value();

		     //printf("operand1: 0x%llx, dsize: %d\n",operand1,packet->Dsize());
		     
                     int count = 0;

                     if (instrID==CLZ_32 || instrID==CLZ_64) {
                       count = count_leading_zeros(operand1,packet->Dsize());
		       //printf("# of leading zeros = %d\n",count);
	             } else {
                       count = count_leading_sign_bits(operand1,packet->Dsize());
		       //printf("# of leading sign bits = %d\n",count);
	             }
		     
                     unsigned long long result = (unsigned long long) count;

                     //printf("dsize: %d %s Nval: 0x%llx, count: 0x%llx\n",
                     //       packet->Dsize(),( (instrID==CLZ_32 || instrID==CLZ_64) ? "CLZ" : "CLS"), operand1, result);

                     packet->Dreg.Value(result);
                     }
                     break;
    case RBIT_32: 
    case RBIT_64:
    case REV_32: 
    case REV_64: 
    case REV16_32: 
    case REV16_64: 
    case REV32:
                     {
	             enum {RevOp_RBIT,RevOp_REV16,RevOp_REV32,RevOp_REV64};

                     unsigned int opc = packet->opcode.Value() & 3;

                     int op = 0;

                     switch((int) opc) {
		       case 0: op = RevOp_RBIT;
                               break;
                       case 1: op = RevOp_REV16; 
                               break;
                       case 2: op = RevOp_REV32;
                               break;
                       case 3: if (packet->sf.Value()==0) {
                                  // unallocated encoding...
                                  packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                                  throw ARCH_EXCEPTION;
	                       }
                               op = RevOp_REV64; 
                               break;
		       default:   // unallocated encoding...
                                  packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                                  throw ARCH_EXCEPTION;
	             }

                     unsigned int V = 0;

	             switch(op) {
                       case RevOp_REV16: V = 0x8;  // 001000
			                 break;
                       case RevOp_REV32: V = 0x18; // 011000
			                 break;
                       case RevOp_REV64: V = 0x38; // 111000
			                 break;
	               case RevOp_RBIT:  V = (packet->Dsize()==64) ? 0x3f : 0x1f; // 111111 or 011111
			                 break;
		       default:          // unallocated encoding...
                                         packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                                         throw ARCH_EXCEPTION;
	             }
 
                     unsigned long long result = packet->Nreg.Value();

                     //printf("[REV] src value: 0x%08llx, op: %d, V: 0x%x\n",result,op,V);

                     for (int vbit = 0; vbit <= 5; vbit++) {
	                // swap pairs of 2^vbit bits in result...
		        if ( ((V>>vbit) & 1) == 1) {
			   //printf("  next iter: vbit: %d..., dsize: %u\n",vbit,packet->Dsize());
			   unsigned long long tmp = result;
                           int vsize = 1<<vbit;
                           int base = 0;
                           while(base < packet->Dsize()) {
			     //printf("  base: %d...\n",base);
                             // result<base+vsize-1:base> = tmp<base+(2*vsize)-1:base+vsize>
			     {
			                                                                        // result
			       int res_hi    = base + vsize - 1;                                //   hi-bit,
			       int res_lo    = base;                                            //     lo-bit,
			       int res_width = res_hi - res_lo + 1;                             //       # of bits to replace,
			       unsigned long long res_mask  = ( (1ull<<res_width) - 1)<<res_lo; //         hi/lo bit mask
			                                                                        // tmp (source)
			       int tmp_hi    = base + (2 * vsize) - 1;                          //   hi-bit,
			       int tmp_lo    = base + vsize;                                    //     lo-bit,
			       int tmp_width = tmp_hi - tmp_lo + 1;                             //       # of bits to replace,
			       unsigned long long tmp_mask  = ( (1ull<<tmp_width) - 1)<<tmp_lo; //         hi/lo bit mask

                               // tmp_part - src bits extracted from tmp, shifted into place to combine with result...
                               unsigned long long tmp_part = ( (tmp & tmp_mask) >> tmp_lo) << res_lo;

			       //printf("  [LO?] tmp_part: 0x%llx (tmp: 0x%llx, tmp-mask: 0x%llx, tmp_lo: %d, res_lo: %d)\n",
			       //      tmp_part,tmp,tmp_mask,tmp_lo,res_lo);
                               // res_mask_inv - res_mask inverted to allow bits to be replaced in result to be stripped out...
                               unsigned long long res_mask_inv = ~((unsigned long long) res_mask);
                               //printf("        res_mask_inv: 0x%llx (res_mask: 0x%llx)\n",res_mask_inv,res_mask);
                               result = (result & res_mask_inv) | tmp_part; //<---replace bits in result with bits from tmp...
			       //printf("        result: 0x%llx\n",result);
			     }

                             // result<base+(2*vsize)-1:base+vsize> = tmp<base+vsize-1:base>
			     {
			       int res_hi    = base + (2 * vsize) - 1;                          //
			       int res_lo    = base + vsize;                                    // ditto rush...
			       int res_width = res_hi - res_lo + 1;                             // 
			       unsigned long long res_mask  = ( (1ull<<res_width) - 1)<<res_lo; //

			       int tmp_hi    = base + vsize - 1;                                //
			       int tmp_lo    = base;                                            //
			       int tmp_width = tmp_hi - tmp_lo + 1;                             //
			       unsigned long long tmp_mask  = ( (1ull<<tmp_width) - 1)<<tmp_lo; //

                               unsigned long long tmp_part = ( (tmp & tmp_mask) >> tmp_lo) << res_lo;
			       //printf("  [HI?] tmp_part: 0x%llx (tmp: 0x%llx, tmp-mask: 0x%llx, tmp_lo: %d, res_lo: %d)\n",
			       //      tmp_part,tmp,tmp_mask,tmp_lo,res_lo);
                               unsigned long long res_mask_inv = ~((unsigned long long) res_mask);
                               //printf("        res_mask_inv: 0x%llx (res_mask: 0x%llx)\n",res_mask_inv,res_mask);
                               result = (result & res_mask_inv) | tmp_part;
			       //printf("        result: 0x%llx\n",result);
			     }

                             base += 2 * vsize;
			   }
			}
		     }

                     //printf("[REV] dest value: 0x%08llx\n",result); // i code with crayons and printfs...

                     packet->Dreg.Value(result);
                     }
                     break;

    default:         packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                     throw ARCH_EXCEPTION;
                     break;
  }
}


//---------------------------------------------------------------------------------------------------------------------------
// multiply divide...
//---------------------------------------------------------------------------------------------------------------------------

void Control:: MultiplyDivide() {
  switch(instrID) {
    case MADD_32: 
    case MSUB_32: 
                     // unsigned 32 bit operation...
                     {
                     bool sub_op = packet->o0.Value()==1;

                     unsigned int operand1 = (unsigned int) packet->Nreg.Value();
                     unsigned int operand2 = (unsigned int) packet->Mreg.Value();
                     unsigned int operand3 = (unsigned int) packet->RAreg.Value();

                     unsigned int result;
     
                     if (sub_op)
	               result = operand3 - (operand1 * operand2);
                     else
	               result = operand3 + (operand1 * operand2);

                     packet->Dreg.Value((unsigned long long) result);
                     }
                     break;

    case MADD_64: 
    case MSUB_64: 
                     // unsigned 64 bit operation...
                     {
                     bool sub_op = packet->o0.Value()==1;

                     unsigned long long operand1 = packet->Nreg.Value();
                     unsigned long long operand2 = packet->Mreg.Value();
                     unsigned long long operand3 = packet->RAreg.Value();

                     unsigned long long result;

                     if (sub_op)
	                result = operand3 - (operand1 * operand2);
                     else
	                result = operand3 + (operand1 * operand2);

                     packet->Dreg.Value(result);
                     }
                     break;

    case UMADDL:
    case UMSUBL:
    case SMADDL: 
    case SMSUBL: 
                     // 64 bit operation only, unsigned or signed... 
                     {
                     bool sub_op = packet->o0.Value()==1;
                     bool unsigned_op = (instrID==UMADDL) || (instrID==UMSUBL);

                     unsigned long long operand1 = packet->Nreg.Value() & 0xffffffff;  // force to Wn
                     unsigned long long operand2 = packet->Mreg.Value() & 0xffffffff;  //    "     Wm
                     unsigned long long operand3 = packet->RAreg.Value();              // IS Xa

                     unsigned long long result;

                     if (unsigned_op) {
                        if (sub_op)
	                   result = operand3 - (operand1 * operand2);
                        else
	                   result = operand3 + (operand1 * operand2);
                     } else {
                        long long signed_result;
	                if (sub_op)
			  signed_result = SignExtend(operand3,64) - (SignExtend(operand1,32) * SignExtend(operand2,32));
                        else
                          signed_result = SignExtend(operand3,64) + (SignExtend(operand1,32) * SignExtend(operand2,32));
                        result = (unsigned long long) signed_result; 
                     }

                     packet->Dreg.Value(result);
                     }
                     break;

    case SDIV_32: 
    case UDIV_32: 
                     {
	             bool unsigned_op = (instrID==UDIV_32);

                     unsigned long long result;

                     if (unsigned_op) {
	                unsigned int operand1 = (unsigned int) packet->Nreg.Value();
	                unsigned int operand2 = (unsigned int) packet->Mreg.Value();
                        unsigned int ures = operand2==0 ? 0 : ( operand1 / operand2 );
                        result = (unsigned long long) ures;
	             } else {
	                int operand1 = (int) SignExtend(packet->Nreg.Value(),packet->Dsize());
	                int operand2 = (int) SignExtend(packet->Mreg.Value(),packet->Dsize());

		        // int divide can cause SIGFPE exception when result is too large to store...
			if ( (operand1 == INT_MIN) && (operand2 == -1) ) {
			  // INT_MIN / -1 YIELDS INT_MAX+1 WHICH OVERFLOWS WHEN STORED...
                          result = (unsigned long long) INT_MAX;
			} else {
                          int ures = operand2==0 ? 0 : ( operand1 / operand2 );
                          result = (unsigned long long) ures;
			}
	             }

                     packet->Dreg.Value(result);
                     }
                     break;

    case SDIV_64:
    case UDIV_64:
                     {
	             bool unsigned_op = (instrID==UDIV_64);

                     unsigned long long result;

                     if (unsigned_op) {
	               unsigned long long operand1 = packet->Nreg.Value();
	               unsigned long long operand2 = packet->Mreg.Value();
                       result = operand2==0 ? 0 : ( operand1 / operand2 );
	             } else {
	               long long int operand1 = (long long int) SignExtend(packet->Nreg.Value(),packet->Dsize());
	               long long int operand2 = (long long int) SignExtend(packet->Mreg.Value(),packet->Dsize());

		       // long long divide can cause SIGFPE exception when result is too large to store...
			if ( (operand1 == LONG_MIN) && (operand2 == -1) ) {
                          result = (unsigned long long) LONG_MAX;
			} else {
                          long long int ures = operand2==0 ? 0 : ( operand1 / operand2 );
                          result = (unsigned long long) ures;
			}
	             }

                     packet->Dreg.Value(result);
                     }
                     break;

    case UMULH:
                     {
	             unsigned long long operand1 = packet->Nreg.Value();
	             unsigned long long operand2 = packet->Mreg.Value();
#ifdef NO_128_T
		     uint64_t u1 = (operand1 & 0xffffffff);
                     uint64_t v1 = (operand2 & 0xffffffff);
                     uint64_t t = (u1 * v1);
                     uint64_t k = (t >> 32);

                     operand1 >>= 32;
                     t = (operand1 * v1) + k;
                     k = (t & 0xffffffff);
                     uint64_t w1 = (t >> 32);

                     operand2 >>= 32;
                     t = (u1 * operand2) + k;
                     k = (t >> 32);

                     unsigned long long result = (operand1 * operand2) + w1 + k;
#else
                     unsigned long long result = operand2==0 ? 0 : ( ((__int128_t) operand1 * operand2) >> 64 );
#endif
                     packet->Dreg.Value(result);
                     }
                     break;

    default:         packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                     throw ARCH_EXCEPTION;
                     break;
  }
}


//---------------------------------------------------------------------------------------------------------------------------
// checksum...
//---------------------------------------------------------------------------------------------------------------------------

void Control::CheckSum() {
  switch(instrID) {
    case CRC32B: 
    case CRC32CB: 
    case CRC32CH: 
    case CRC32CW: 
    case CRC32CX: 
    case CRC32H: 
    case CRC32W: 
    case CRC32X:
                     // in this 'implementation' CRC instructions are NOT present...
    default:         packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                     throw ARCH_EXCEPTION;
                     break;
  }
}


//---------------------------------------------------------------------------------------------------------------------------
// system...
//---------------------------------------------------------------------------------------------------------------------------

void Control::System() {
  switch(instrID) {
    case SYS: 
    case SYSL:       if (cpu->CheckSystemRegisterAccess(packet->op1.Value())) {
                        // inability to access system register results in undef exception...
                        packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                        throw ARCH_EXCEPTION;
                     }
		     // pick off sys ops (cache, tlb, etc)...
                     {
                       int sysop_type  = SYSOP_TYPE_UNKNOWN;
                       int sysop_index = SYSOP_UNKNOWN;
                       if (cpu->SysOp(sysop_type,sysop_index,packet->op0.Value(),packet->op1.Value(),packet->CRn.Value(),packet->CRm.Value(),packet->op2.Value())) {
		         // recognized sys-op. treat as NOPs for now...
			 if (packet->L.Value()==1) {
                           // has result, write dummy value for now...
			   packet->Dreg.Value(0);
			 }

		       } else {
                         packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING);
                         throw ARCH_EXCEPTION;
		       }
                     }
		     break;

    case ERET:       if (packet->Pstate.EL()==0) {
		        // unallocated encoding...
                        packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                        throw ARCH_EXCEPTION;
		     }
                     ExceptionReturn();
                     break;

    case SMC:        if (!cpu->HaveEL(EL3) || packet->Pstate.EL()==0) {
		        // unallocated encoding...
                        packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                        throw ARCH_EXCEPTION;
		     }
                     cpu->checkForSMCTrap();
                     if (cpu->SMCdisabled()) {    
                       // SMC disabled...just make this one throw unallocated-encoding exception...
                       packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                       throw ARCH_EXCEPTION;
		     } else
                       CallSecureMonitor(packet->imm16.Value());
		     break;

    case SVC:        CallSupervisor(packet->imm16.Value());
                     break;

    case HVC:        // Hypervisor not present in this implementation...
                     packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                     throw ARCH_EXCEPTION;
                     break;

    default:         packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                     throw ARCH_EXCEPTION;
                     break;
  }
}


//---------------------------------------------------------------------------------------------------------------------------
// debug ops...
//---------------------------------------------------------------------------------------------------------------------------

void Control::DebugOp() {
  bool is_undef = true; // by default will throw UNDEF exception...

  switch(instrID) {
    case HLT:        // check immediate - if this is a semihosting request then (for now) NOP...
                     if (packet->imm16.Value() == 0xf000) {
	               is_undef = false;
                     }
                     break;
    case BRK: 
    case DCPS1: 
    case DCPS2: 
    case DCPS3:
    default:
                     break;
  }

  if (is_undef) {
    packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
    throw ARCH_EXCEPTION;
  }
}


//---------------------------------------------------------------------------------------------------------------------------
// MemoryAccess methods...
//---------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------
// load/stores and related code...
//---------------------------------------------------------------------------------------------------------------------------

enum {ExtendType_UXTB,ExtendType_UXTH,ExtendType_UXTW,ExtendType_UXTX,ExtendType_SXTB,ExtendType_SXTH,ExtendType_SXTW,ExtendType_SXTX};

int Control::DecodeRegExtend(int op) {
  int ext_type;
  switch(op) {
    case 0: ext_type = ExtendType_UXTB; break;
    case 1: ext_type = ExtendType_UXTH; break;
    case 2: ext_type = ExtendType_UXTW; break;
    case 3: ext_type = ExtendType_UXTX; break;
    case 4: ext_type = ExtendType_SXTB; break;
    case 5: ext_type = ExtendType_SXTH; break;
    case 6: ext_type = ExtendType_SXTW; break;
    case 7: ext_type = ExtendType_SXTX; break;
    default: packet->recordExceptionCondition(INVALID_REG_EXTEND_FIELD); 
             throw INTERNAL_ERROR; 
             break;
  }
  return ext_type;
}

bool Control::BigEndian() {
  bool big_endian = true;

  switch((int) packet->Pstate.EL()) {
    case 0: big_endian = cpu->SCTLR_EL1.E0E() != 0; break;
    case 1: big_endian = cpu->SCTLR_EL1.EE() != 0;  break;
    case 2: big_endian = cpu->SCTLR_EL2.EE() != 0;  break;
    case 3: big_endian = cpu->SCTLR_EL3.EE() != 0;  break;
    default: packet->recordExceptionCondition(INVALID_EXCEPTION_LEVEL,ENDIANNESS_STATE); 
             throw INTERNAL_ERROR; 
             break;
  }

  return big_endian;
}

long long Control::lsBaseAddress(int n, bool for_prefetch) {
  long long base_address;
  if (n == 31) {
    if (!for_prefetch)
      CheckStackAlignment();
    base_address = cpu->GetSP().Value();
  } else {
    base_address = packet->Nreg.Value();
  }
  //printf("[lsBaseAddress] rval: 0x%llx base_address: %lld\n",packet->Nreg.Value(),base_address);
  return (long long) base_address;
}

unsigned long long Control::lsOffsetBaseAddress(int n,long long offset, bool for_prefetch) {
  long long base_address = (long long) lsBaseAddress(n,for_prefetch);
  long long address = base_address + offset;
  //printf("[lsOffsetBaseAddress] base address: %lld offset: %lld address: %lld (0x%llx)\n",
  //       base_address,offset,address,(unsigned long long) address);
  return (unsigned long long) address;
}

unsigned long long Control::PCrelativeAddress(long long offset) {
  long long pcval = (long long) packet->PC.Value();
  long long address = pcval + offset;
  return (unsigned long long) address;
}

int Control::LoadStoreSignExtendTo(unsigned int instrID, unsigned int opc) {
  int rwidth = 32;

  switch(instrID) {
    case LDRSW_IMM_REG_POST:
    case LDRSW_IMM_REG_PRE:
    case LDRSW_IMM_REG_OFF:  
    case LDTRSW_REG:
    case LDURSW_IMM_REG:
    case LDRSW_REG_OFF:
                             rwidth = 64; // for these cases always extend to 64 bits 
                             break;

    default:                 rwidth = (opc == 3) ? 32 : 64; 
                             break;
  }

  return rwidth;
}

//---------------------------------------------------------------------------------------------------------------------------
// Load Store Exclusives
//---------------------------------------------------------------------------------------------------------------------------

void Control::ClearExclusiveMonitor() {
  // create dummy memory access of zero bytes, set as exclusive access...
  MemoryAccess memacc(0,0,ATOMIC,true,FOR_READ,BigEndian(),0,false,0,false,packet->Pstate.Privileged());
  packet->mOpsMemory.push_back(memacc);
}

void Control::LoadStoreExclusive() {
  int n  = packet->Rn.Value();
  int t  = packet->Rt.Value();
  int t2 = packet->Rt2.Value();
  int s  = packet->Rs.Value();

  unsigned int tval = (packet->o2.Value()<<2) | (packet->o1.Value()<<1) | packet->o0.Value();

  if (tval == 4 || tval == 6 || tval == 7) {
    // invalid encoding...
    packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
    throw ARCH_EXCEPTION;
  }
  if (packet->o1.Value()==1 && packet->size.Value()<2) {
    // invalid encoding...
    packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
    throw ARCH_EXCEPTION;
  }

  int acctype  = packet->o0.Value()==1 ? ORDERED : ATOMIC;
  bool excl    = packet->o2.Value()==0;
  bool pair    = packet->o1.Value()==1;
  int memop    = packet->L.Value()==1 ? FOR_READ : FOR_WRITE;
  int elsize   = 8<<packet->size.Value();
  //int regsize  = elsize==64 ? 64 : 32;
  int datasize = pair ? elsize * 2 : elsize;

  if (memop==FOR_WRITE && excl && s==31) {
    // in this implementation will not allow exclusive monitor status to be written to
    // 'zeros' register or stack...
    packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
    throw ARCH_EXCEPTION;
  }
 
  int dbytes    = datasize / 8;                        // total # of memory bytes
  int word_size = (pair==true) ? dbytes / 2 : dbytes;  // # of memory bytes per register 

  if (memop==FOR_READ && pair && t == t2) {
      // unpredictable case NOT allowed...
      packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
      throw ARCH_EXCEPTION;
  }
  if (memop==FOR_WRITE && excl) {
    if (s == t || (pair && s == t2)) {
        // unpredictable case NOT allowed...
        packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
        throw ARCH_EXCEPTION;
    }
    if (s == n && n != 31) {
        // unpredictable case NOT allowed...
        packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
        throw ARCH_EXCEPTION;
    }
  }

  bool do_sign_extend = false; // load exclusives don't sign extend
  int  signextend_to = 32;     // value doesn't matter

  unsigned long long address = lsBaseAddress(n,false);

  MemoryAccess memacc(address,dbytes,acctype,excl,memop,BigEndian(),word_size,do_sign_extend,signextend_to,pair,packet->Pstate.Privileged());

  if (memop == FOR_WRITE) {
      bool do_write = true;
      if (excl) {
	// for exclusive op, go ahead and set return code here...
        if (memory->IsExclusive(cpu,packet,address,dbytes,packet->Pstate.Privileged()))
          packet->Dreg.Value(0);
        else {
          packet->Dreg.Value(1);
          do_write = false;
	}
        packet->mOpsWriteback.push_back(XS); //<---always record status from exclusive monitor access
      }
      if (do_write) {
        // move register(s) value into memory write buffer...
        if (pair) {
          // pair of registers...
          SaveRegisterPair(packet->Treg.Value(),packet->T2reg.Value(),memacc.membuffer,word_size,BigEndian(),excl);
        } else {
          // a single register...
          SaveRegister(packet->Treg.Value(),memacc.membuffer,word_size,BigEndian());
        }
      } else {
        // exclusive op failed so no data to move...
        memacc.ClearBuffer();
      }
  }

  if (memop == FOR_READ) {
    if (excl) {
      // its an exclusive op. its a read. we know the size of the access...
      // processing the memory access will set the exclusize monitor
    }

    if (pair) {
      // pair of registers...
      if (!excl) {
	// expect only paired register for exclusive ops...
        packet->recordExceptionCondition(PAIRED_REGISTERS_INVALID,EXCLUSIVE_OP); 
        throw INTERNAL_ERROR;
      }
      // designate register pair to update after memory read...
      //packet->mOpsWriteback.push_back(XT);    // NOTE: register to update already recorded as part of instruction decode
      //packet->mOpsWriteback.push_back(XT2);
    } else {
      // a single register...
      // designate register target for load...
      //packet->mOpsWriteback.push_back(XT);
    }
  }

  packet->mOpsMemory.push_back(memacc);
}


//---------------------------------------------------------------------------------------------------------------------------
// Load Store Register Pair...
//---------------------------------------------------------------------------------------------------------------------------

void Control::LoadStoreRegisterPair() {
  bool wback = false;
  bool postindex = false;

  switch(instrID) {
    case LDP_REG_POST_32: case LDP_REG_POST_64: case LDPSW_REG_POST: case STP_REG_POST_32: case STP_REG_POST_64:
      wback = true;
      postindex = true;
      break;
    case LDP_REG_PRE_32: case LDP_REG_PRE_64: case LDPSW_REG_PRE: case STP_REG_PRE_32: case STP_REG_PRE_64: 
      wback = true;
      postindex = false;
      break;
    case LDP_REG_OFF_32: case LDP_REG_OFF_64: case LDPSW_REG_OFF: case STP_REG_OFF_32: case STP_REG_OFF_64:
      wback = false;
      postindex = false;
      break;
    default: break;
  }

  int n          = packet->Rn.Value();
  int t          = packet->Rt.Value();
  int t2         = packet->Rt2.Value();
  int acctype    = NORMAL;
  int memop      = packet->L.Value()==1 ? FOR_READ : FOR_WRITE;

  bool is_signed = (packet->opc.Value() & 1) == 1;  //<---signed or not depending on low order bit of opc

  int signextend_to = 64;  // if sign-extended value, always extend to 64 bits

  int scale      = 2 + ((packet->opc.Value() & 2)>>1);

  int regsize    = (packet->opc.Value()==1 || packet->opc.Value()==2) ? 64 : 32;
  int datasize   = 8 << scale;

  long long offset = LSL(SignExtend(packet->imm7.Value(),7),scale);

  int dbytes    = datasize / 8; // for each register value to read

  int word_size = regsize / 8;        

  // LDPSW - load signed word (load 32 bit signed value, extend to 64 bits)...
  switch(instrID) {
    case LDPSW_REG_POST:
    case LDPSW_REG_PRE:
    case LDPSW_REG_OFF:  word_size = 4;
                         break;
    default: break;
  }
  
  int num_bytes_to_read = dbytes * 2; // there are two register values to be loaded

  if (memop == FOR_READ && wback && (t == n || t2 == n) && n != 31) {
      // unpredictable case NOT allowed...
      packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
      throw ARCH_EXCEPTION;
  }
  if (memop == FOR_WRITE && wback && (t == n || t2 == n) && n != 31) {
      // unpredictable case NOT allowed...
      packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
      throw ARCH_EXCEPTION;
  }
  if (memop == FOR_READ && t == t2) {
      // unpredictable case NOT allowed...
      packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
      throw ARCH_EXCEPTION;
  }

  // NOTE: offset NOT applied if post-indexed mode...

  unsigned long long address = lsOffsetBaseAddress(n,postindex ? 0 : offset,false);

  MemoryAccess memacc(address,num_bytes_to_read,acctype,false,memop,BigEndian(),word_size,is_signed,signextend_to,true,packet->Pstate.Privileged());

  if (memop == FOR_WRITE) {
    unsigned long long data1 = packet->Treg.Value();
    unsigned long long data2 = packet->T2reg.Value();
    SaveRegisterPair(data1,data2,memacc.membuffer,word_size,BigEndian(),false);
  }
  if (memop == FOR_READ) {
     // designate register targets for load...
     //packet->mOpsWriteback.push_back(XT);     // NOTE: register to update already recorded as part of instruction decode
     //packet->mOpsWriteback.push_back(XT2);
  }

  packet->mOpsMemory.push_back(memacc);

  if (wback) {
    if (postindex) {
      address = lsOffsetBaseAddress(n,offset,false);
    }    
    packet->Nreg.Value(address);
    packet->mOpsWriteback.push_back(XNSP);
  }
}


//---------------------------------------------------------------------------------------------------------------------------
// Load Store Register Pair with Hint
//---------------------------------------------------------------------------------------------------------------------------

void Control::LoadStoreRegisterPairWithHint() {
  int n        = packet->Rn.Value();
  int t        = packet->Rt.Value();
  int t2       = packet->Rt2.Value();
  int acctype  = STREAM;
  int memop    = packet->L.Value()==1 ? FOR_READ : FOR_WRITE;
  int scale    = 2 + (packet->opc.Value()>>1); //= 2 or 3
  //int regsize  = packet->opc.Value()==2 ? 64 : 32;
  int datasize = 8 << scale; // == 32 or 64

  long long offset = LSL(SignExtend(packet->imm7.Value(),7),scale);

  int dbytes    = datasize / 8;
  int word_size = datasize / 8;

  int num_bytes = dbytes * 2;      //<---total # of bytes to load

  if (memop==FOR_READ && t == t2) {
     // unpredictable case NOT allowed...
     packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
     throw ARCH_EXCEPTION;
  }

  bool do_sign_extend = false; // no sign extend for LDNP
  int  signextend_to = 32;     // value doesn't matter

  unsigned long long address = lsOffsetBaseAddress(n,offset,false);

  MemoryAccess memacc(address,num_bytes,acctype,false,memop,BigEndian(),word_size,do_sign_extend,signextend_to,true,packet->Pstate.Privileged());

  if (memop == FOR_WRITE) {
    unsigned long long data1 = packet->Treg.Value();
    unsigned long long data2 = packet->T2reg.Value();
    SaveRegisterPair(data1,data2,memacc.membuffer,word_size,BigEndian(),false);
  }

  if (memop == FOR_READ) {
     // designate register targets for load...
     //packet->mOpsWriteback.push_back(XT);   // NOTE: register to update already recorded as part of instruction decode
     //packet->mOpsWriteback.push_back(XT2);
  }

  packet->mOpsMemory.push_back(memacc);
}


//---------------------------------------------------------------------------------------------------------------------------
// Load Stores - register immediate addressing modes...
//---------------------------------------------------------------------------------------------------------------------------

void Control::LoadStoreRegisterImmediate() {
  //printf("[Control::LoadStoreRegisterImmediate] entered, PC: 0x%llx...\n",packet->PC.Value());
  
  bool wback = false;
  bool postindex = false;
  int scale = packet->size.Value(); // 0==byte, 1==hword, 2==word, 3==dword
  long long offset = 0;

  switch(instrID) {
    case LDR_IMM_REG_POST_32: case LDR_IMM_REG_POST_64: 
    case LDRB_IMM_REG_POST: case LDRH_IMM_REG_POST: case LDRSW_IMM_REG_POST: 
    case LDRSB_IMM_REG_POST_32: case LDRSB_IMM_REG_POST_64: 
    case LDRSH_IMM_REG_POST_32: case LDRSH_IMM_REG_POST_64: 
    case STR_IMM_REG_POST_32: case STR_IMM_REG_POST_64: 
    case STRB_IMM_REG_POST: case STRH_IMM_REG_POST: 
      wback = true;
      postindex = true;
      offset = SignExtend(packet->imm9.Value(),9);
      break;
    case LDR_IMM_REG_PRE_32: case LDR_IMM_REG_PRE_64: 
    case LDRB_IMM_REG_PRE: case LDRH_IMM_REG_PRE: case LDRSW_IMM_REG_PRE:
    case LDRSB_IMM_REG_PRE_32: case LDRSB_IMM_REG_PRE_64: 
    case LDRSH_IMM_REG_PRE_32: case LDRSH_IMM_REG_PRE_64: 
    case STR_IMM_REG_PRE_32: case STR_IMM_REG_PRE_64: 
    case STRB_IMM_REG_PRE: case STRH_IMM_REG_PRE: 
      wback = true;
      postindex = false;
      offset = SignExtend(packet->imm9.Value(),9);
      break;
    case LDR_IMM_REG_32: case LDR_IMM_REG_64: 
    case LDRB_IMM_REG_OFF: case LDRH_IMM_REG_OFF: case LDRSW_IMM_REG_OFF:
    case LDRSB_IMM_REG_32: case LDRSB_IMM_REG_64: 
    case LDRSH_IMM_REG_32: case LDRSH_IMM_REG_64: 
    case STR_IMM_REG_32: case STR_IMM_REG_64: 
    case STRB_IMM_REG_OFF: case STRH_IMM_REG_OFF: 
    case PRFM_REG_OFF: 
      wback = false;
      postindex = false;
      offset = LSL(packet->imm12.Value(),scale); //<---zero extend is same as immediate itself...

      //printf("[Control::LoadStoreRegisterImmediate] imm12: 0x%x, scale: %d, offset: %lld\n", packet->imm12.Value(),scale, offset);
      
      break;
    default: break;
  }

  int n = packet->Rn.Value();
  int t = packet->Rt.Value();
  int acctype = NORMAL;
  int memop = 0;
  bool is_signed = false;
  int signextend_to = 32;

  if ((packet->opc.Value() & 2) == 0) {
    // store or zero-extending load...
    int Lbit = packet->opc.Value() & 1; //<---L bit is bit 22 or low order bit of opc
    memop = Lbit==1 ? FOR_READ : FOR_WRITE;
    is_signed = false;
  } else {
    if (packet->size.Value()==3) {
      memop = FOR_PREFETCH;
      if (packet->opc.Value() != 2) {
        packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
        throw ARCH_EXCEPTION;
      } 
    } else {
	// sign-extending load...
        memop = FOR_READ;
        if (packet->size.Value() == 2 && (packet->opc.Value() & 1)==1) {
  	   // NOT prefetch instruction...
           packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
           throw ARCH_EXCEPTION;
	}
        is_signed = true;
        signextend_to = LoadStoreSignExtendTo(instrID,packet->opc.Value());
    }
  }
   
  int datasize  = 8 << scale; // scale: 0==byte, 1==hword, 2==word, 3==dword

  int dbytes    = datasize / 8;
  int word_size = datasize / 8;

  if (memop == FOR_READ && wback && n == t && n != 31) {
      // unpredictable case NOT allowed...
      packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
      throw ARCH_EXCEPTION;
  }
  if (memop == FOR_WRITE && wback && n == t && n != 31) {
      // unpredictable case NOT allowed...
      packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
      throw ARCH_EXCEPTION;
  }

  unsigned long long address;

  if (!postindex)
    address = lsOffsetBaseAddress(n,offset,memop==FOR_PREFETCH);
  else
    address = lsBaseAddress(n,memop==FOR_PREFETCH);

  //printf("[Control::LoadStoreRegisterImmediate] N: %d, address: 0x%llx, size: %d, word-size: %d\n",n, address,dbytes,word_size);

  MemoryAccess memacc(address,dbytes,acctype,false,memop,BigEndian(),word_size,is_signed,signextend_to,false,packet->Pstate.Privileged());

  if (memop == FOR_WRITE) {
    unsigned long long data1 = packet->Treg.Value();
    SaveRegister(data1,memacc.membuffer,word_size,BigEndian());
  }
  if (memop == FOR_READ) {
     // designate register target for load...
     //packet->mOpsWriteback.push_back(XT);  // NOTE: register to update already recorded as part of instruction decode
  }

  packet->mOpsMemory.push_back(memacc);

  if (wback) {
    address = lsOffsetBaseAddress(n,offset,memop==FOR_PREFETCH);  
    packet->Nreg.Value(address);
    packet->mOpsWriteback.push_back(XNSP);
  }

  //printf("[Control::LoadStoreRegisterImmediate] exited, PC: 0x%llx...\n",packet->PC.Value());  
}


//---------------------------------------------------------------------------------------------------------------------------
// Loads - PC relative addressing mode...
//---------------------------------------------------------------------------------------------------------------------------

void Control::LoadRegisterLiteral() {
  //int t = packet->Rt.Value();
  int memop = FOR_READ;
  int acctype = NORMAL;
  int size = 0;
  bool do_sign_extend = (instrID == LDRSW_REG);
  int signextend_to   = 64;

  switch((int) packet->opc.Value()) {
    case 0: size = 4; break;
    case 1: size = 8; break;
    case 2: size = 4; do_sign_extend = true; break;
    case 3: memop = FOR_PREFETCH; 
            acctype = DATA; 
            break;
    default: packet->recordExceptionCondition(INVALID_OPC_FIELD,LOAD_REG_LITERAL); 
             throw INTERNAL_ERROR; 
             break;
  }
  
  int regsize = size;
 
 long long offset = SignExtend(packet->imm19.Value()<<2,21);

  unsigned long long address = PCrelativeAddress(offset);

  MemoryAccess memacc(address,size,acctype,false,memop,BigEndian(),regsize,do_sign_extend,signextend_to,false,packet->Pstate.Privileged());

  if (memop == FOR_READ) {
     // designate register target for load...
     //packet->mOpsWriteback.push_back(XT);  // NOTE: register to update already recorded as part of instruction decode
  }

  packet->mOpsMemory.push_back(memacc);
}


//---------------------------------------------------------------------------------------------------------------------------
// Load Stores - unprivileged...
//---------------------------------------------------------------------------------------------------------------------------

void Control::LoadStoreRegisterUnprivileged() {
  int scale = packet->size.Value();
  
  long long offset = SignExtend(packet->imm9.Value(),9);

  int n = packet->Rn.Value();
  int acctype = UNPRIVILEGED;
  int memop;
  bool is_signed = false;
  int signextend_to = 32;

  if ((packet->opc.Value() & 2) == 0) {
    // store or zero-extending load...
    memop = (packet->opc.Value() & 1) == 1 ? FOR_READ : FOR_WRITE;
    is_signed = false;
  } else {
    if (packet->size.Value() == 3) {
      // no unprivileged prefetch...
      packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
      throw ARCH_EXCEPTION;
    } else {
      // sign-extending load...
      memop = FOR_READ;
      if ( packet->size.Value()==2 && (packet->opc.Value() & 1) == 1 ) {
        // invalid size/opc combo...
        packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
        throw ARCH_EXCEPTION;
      }
      is_signed = true;
      signextend_to = LoadStoreSignExtendTo(instrID,packet->opc.Value());
    }
  }

  int datasize = 8 << scale; // scale: 0==byte,1==hword,2==word,3==dword

  int dbytes = datasize / 8;
  int word_size = dbytes;

  unsigned long long address = lsOffsetBaseAddress(n,offset,false);

  MemoryAccess memacc(address,dbytes,acctype,false,memop,BigEndian(),word_size,is_signed,signextend_to,false,false);

  if (memop == FOR_WRITE) {
     unsigned long long data1 = packet->Treg.Value();
     SaveRegister(data1,memacc.membuffer,word_size,BigEndian());
  }
  if (memop == FOR_READ) {
     // designate register target for load...
     //packet->mOpsWriteback.push_back(XT);  // NOTE: register to update already recorded as part of instruction decode
  }

  packet->mOpsMemory.push_back(memacc);
}


//---------------------------------------------------------------------------------------------------------------------------
// Load Stores - unscaled addressing mode...
//---------------------------------------------------------------------------------------------------------------------------

void Control::LoadStoreRegisterUnscaled() {
  int scale = packet->size.Value();
  
  long long offset = SignExtend(packet->imm9.Value(),9);

  int n = packet->Rn.Value();
  int acctype = NORMAL;
  int memop;
  bool is_signed = false;
  int signextend_to = 32;

  if ((packet->opc.Value() & 2) == 0) {
    // store or zero-extending load...
    memop = (packet->opc.Value() & 1) == 1 ? FOR_READ : FOR_WRITE;
    is_signed = false;
  } else {
    if (packet->size.Value() == 3) {
      memop = FOR_PREFETCH;
      if ( (packet->opc.Value() & 1) == 1 ) {
        packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
        throw ARCH_EXCEPTION;
      }
    } else {
      // sign-extending load...
      memop = FOR_READ;
      if ( packet->size.Value()==2 && (packet->opc.Value() & 1) == 1 ) {
        // invalid size/opc combo...
        packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
        throw ARCH_EXCEPTION;
      }
      //regsize = (packet->opc.Value() & 1) == 1 ? 32 : 64;
      is_signed = true;
      signextend_to = LoadStoreSignExtendTo(instrID,packet->opc.Value());
    }
  }

  int datasize = 8 << scale; // scale: 0==byte,1==hword,2==word,3==dword

  int dbytes = datasize / 8;
  int word_size = dbytes;

  unsigned long long address = lsOffsetBaseAddress(n,offset,memop==FOR_PREFETCH);

  MemoryAccess memacc(address,dbytes,acctype,false,memop,BigEndian(),word_size,is_signed,signextend_to,false,packet->Pstate.Privileged());

  if (memop == FOR_WRITE) {
     unsigned long long data1 = packet->Treg.Value();
     SaveRegister(data1,memacc.membuffer,word_size,BigEndian());
  }

  if (memop == FOR_READ) {
     // designate register target for load...
     //packet->mOpsWriteback.push_back(XT);  // NOTE: register to update already recorded as part of instruction decode
  }

  if (memop == FOR_PREFETCH) {
     // prefetch memory addres only, ie, no data xfer...
  }

  packet->mOpsMemory.push_back(memacc);
}


//---------------------------------------------------------------------------------------------------------------------------
// Load Stores - register offset addressing mode...
//---------------------------------------------------------------------------------------------------------------------------

void Control::LoadStoreRegisterOffset() {
  int scale = packet->size.Value();

  switch((int) packet->option.Value()) {
     case 0:
     case 1:
     case 4:
     case 5:  // option values 00x or 10x are RESERVED...
              packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
              throw ARCH_EXCEPTION;
              break;
     default: // valid option value for these instructions...
              break;
  }

  int extend_type = DecodeRegExtend(packet->option.Value());
  int shift = packet->S.Value() == 1 ? scale : 0;

  int n = packet->Rn.Value();
  int acctype = NORMAL;
  int memop = 0;
  bool is_signed = false;
  //int index_width = 0;
  int signextend_to = 32;

  if ((packet->opc.Value() & 2) == 0) {
    // store or zero-extending load...
    memop = (packet->opc.Value() & 1) == 1 ? FOR_READ : FOR_WRITE;
    //index_width = ((packet->option.Value() & 1) == 1) ? 64 : 32;
    is_signed = false;
  } else {
    if (packet->size.Value() == 3) {
      memop = FOR_PREFETCH;
      if ( (packet->opc.Value() & 1) == 1 ) {
        packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
        throw ARCH_EXCEPTION;
      }
    } else {
      // sign-extending load...
      memop = FOR_READ;
      if ( packet->size.Value()==2 && (packet->opc.Value() & 1) == 1 ) {
        // invalid size/opc combo...
        packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
        throw ARCH_EXCEPTION;
      }
      //index_width = ((packet->option.Value() & 1) == 1) ? 64 : 32;
      is_signed = true;
      signextend_to = LoadStoreSignExtendTo(instrID,packet->opc.Value());
    }
  }

  /*
  switch(memop) {
    case FOR_READ:
      printf("[Control::LoadStoreRegisterOffset] memop: FOR_READ\n");
      break;
    case FOR_WRITE:
      printf("[Control::LoadStoreRegisterOffset] memop: FOR_WRITE\n");
      break;
    case FOR_PREFETCH:
      printf("[Control::LoadStoreRegisterOffset] memop: FOR_PREFETCH\n");
      break;
    default:
      printf("[Control::LoadStoreRegisterOffset] memop: ?\n");
      break;
  }
  */
  
  int datasize = 8 << scale; // scale: 0==byte,1==hword,2==word,3==dword
  int dbytes = datasize / 8;
  int word_size = dbytes;

  int N = 64; // NOT index_width as sign extension always needs to be to 64 bits...
  
  unsigned long long off = ExtendReg(packet->Mreg.Value(),extend_type,shift,N);

  long long offset = (long long) off;

  unsigned long long address = lsOffsetBaseAddress(n,offset,memop==FOR_PREFETCH);

  MemoryAccess memacc(address,dbytes,acctype,false,memop,BigEndian(),word_size,is_signed,signextend_to,false,packet->Pstate.Privileged());

  if (memop == FOR_WRITE) {
     unsigned long long data1 = packet->Treg.Value();
     SaveRegister(data1,memacc.membuffer,word_size,BigEndian());
  }
  if (memop == FOR_READ) {
     // designate register target for load...
     //packet->mOpsWriteback.push_back(XT);  // NOTE: register to update already recorded as part of instruction decode
  }
  if (memop == FOR_PREFETCH) {
     // prefetch memory address only, ie, no data xfer...
  }

  packet->mOpsMemory.push_back(memacc);
}


//---------------------------------------------------------------------------------------------------------------------------
// identify machine op to be performed...
//---------------------------------------------------------------------------------------------------------------------------

void Control::IdentifyMachineOP() {
  packet->execute_op = UNKNOWN_OP;

  switch(packet->A64InstrIndex) {
    case ADC_32: case ADC_64: case ADCS_32: case ADCS_64: case SBC_32: case SBC_64: case SBCS_32: case SBCS_64: 
    case ADD_REG_32: case ADD_REG_64: case ADDS_REG_32: case ADDS_REG_64: case SUB_REG_32: case SUB_REG_64: 
    case SUBS_REG_32: case SUBS_REG_64: case ADD_SHIFT_REG_32: case ADD_SHIFT_REG_64: case ADDS_SHIFT_REG_32: 
    case ADDS_SHIFT_REG_64: case SUB_SHIFT_REG_32: case SUB_SHIFT_REG_64: case SUBS_SHIFT_REG_32: case SUBS_SHIFT_REG_64:
    case ADD_IMM_32: case ADD_IMM_64: case ADDS_IMM_32: case ADDS_IMM_64: case SUB_IMM_32: case SUB_IMM_64: 
    case SUBS_IMM_32: case SUBS_IMM_64:  
                     packet->execute_op = ADDSUB_OP;
                     break;
    case MRS: case MSR_IMM: case MSR_REG:      
                     packet->execute_op = MRS_MSR_OP;
                     break;
    case MOVN_IMM_32: case MOVZ_IMM_32: case MOVK_IMM_32: case MOVN_IMM_64: case MOVZ_IMM_64: case MOVK_IMM_64:  
                     packet->execute_op = MOVE_IMM_OP;
                     break;
    case AND_IMM_32: case AND_IMM_64: case ANDS_IMM_32: case ANDS_IMM_64: case ORR_IMM_32: case ORR_IMM_64:
    case EOR_IMM_32: case EOR_IMM_64: case AND_SHIFT_REG_32: case AND_SHIFT_REG_64: case ANDS_SHIFT_REG_32: 
    case ANDS_SHIFT_REG_64: case ORR_SHIFT_REG_32: case ORR_SHIFT_REG_64: case ORN_SHIFT_REG_32: case ORN_SHIFT_REG_64:
    case EOR_SHIFT_REG_32: case EOR_SHIFT_REG_64: case EON_SHIFT_REG_32: case EON_SHIFT_REG_64:
                     packet->execute_op = LOGICAL_OP;
		     break;
    case ADR: case ADRP: 
                     packet->execute_op = LABEL_OP;
                     break;
    case ASRV_32: case ASRV_64: case EXTR_32: case EXTR_64: case LSLV_32: case LSLV_64: case LSRV_32: case LSRV_64:
    case RORV_32: case RORV_64:
                     packet->execute_op = SHIFT_OP;
                     break;
    case HINT: case NOP: case SEVL: case SEV: case WFE: case WFI: case YIELD: case DSB: case ISB: case DMB:
                     packet->execute_op = HINT_OP;
                     break;
    case CLREX:
                     packet->execute_op = CLREX_OP;
                     break;
    case B_IMM: case B_COND_IMM: case BL: case BLR: case BR: case CBNZ_IMM_32: case CBNZ_IMM_64: case CBZ_IMM_32: case CBZ_IMM_64: case RET:
    case TBNZ: case TBZ:
                     packet->execute_op = BRANCH_OP;
                     break;
    case BFM_32: case BFM_64: case SBFM_32: case SBFM_64: case UBFM_32: case UBFM_64: case BIC_SHIFT_REG_32:
    case BIC_SHIFT_REG_64: case BICS_SHIFT_REG_32: case BICS_SHIFT_REG_64: case CLS_32: case CLS_64: case CLZ_32: case CLZ_64:
    case RBIT_32: case RBIT_64: case REV_32: case REV_64: case REV16_32: case REV16_64: case REV32:
                     packet->execute_op = BIT_FIELD_OP;
                     break;
    case BRK: case DCPS1: case DCPS2: case DCPS3: case DRPS: case HLT:
                     packet->execute_op = DEBUG_OP;
                     break;
    case CCMN_IMM_32: case CCMN_IMM_64: case CCMN_REG_32: case CCMN_REG_64: case CCMP_IMM_32: case CCMP_IMM_64: case CCMP_REG_32: 
    case CCMP_REG_64:
                     packet->execute_op = COMPARE_OP;
                     break;
    case CRC32B: case CRC32CB: case CRC32CH: case CRC32CW: case CRC32CX: case CRC32H: case CRC32W: case CRC32X:
                     packet->execute_op = CHECKSUM_OP;
                     break;
    case CSEL_32: case CSEL_64: case CSINC_32: case CSINC_64: case CSINV_32: case CSINV_64: case CSNEG_32: case CSNEG_64:
                     packet->execute_op = CONDITIONAL_OP;
                     break;
    case SYS: case SYSL: case ERET: case HVC: case SMC: case SVC:
                     packet->execute_op = SYSTEM_OP;
                     break;
    case LDAR_32: case LDAR_64: case LDARB: case LDARH: case LDAXP_32: case LDAXP_64: case LDAXR_32: case LDAXR_64: case LDAXRB: case LDAXRH: 
    case LDXP_32: case LDXP_64: case LDXR_32: case LDXR_64: case LDXRB: case LDXRH: case STLR_32: case STLR_64: case STLRB: case STLRH: 
    case STLXP_32: case STLXP_64: case STLXR_32: case STLXR_64: case STLXRB: case STLXRH: case STXP_32: case STXP_64: case STXR_32: 
    case STXR_64: case STXRB: case STXRH:
                     packet->execute_op = LS_EXCL_OP;
                     break;
    case LDP_REG_POST_32: case LDP_REG_POST_64: case LDPSW_REG_POST: case LDP_REG_PRE_32: case LDP_REG_PRE_64: case LDPSW_REG_PRE:
    case LDP_REG_OFF_32: case LDP_REG_OFF_64: case LDPSW_REG_OFF: case STP_REG_OFF_32: case STP_REG_OFF_64: case STP_REG_POST_32: 
    case STP_REG_POST_64: case STP_REG_PRE_32: case STP_REG_PRE_64: 
                     packet->execute_op = LS_REG_PAIR_OP;
		     break;
    case LDNP_OFF_32: case LDNP_OFF_64: case STNP_OFF_32: case STNP_OFF_64:  
                     packet->execute_op = LS_REG_PAIR_HINT_OP;
		     break;		     
    case LDR_IMM_REG_POST_32: case LDR_IMM_REG_POST_64: case LDR_IMM_REG_PRE_32: case LDR_IMM_REG_PRE_64: case LDR_IMM_REG_32: 
    case LDR_IMM_REG_64: case LDRB_IMM_REG_POST: case LDRB_IMM_REG_PRE: case LDRB_IMM_REG_OFF: case LDRH_IMM_REG_POST: 
    case LDRH_IMM_REG_PRE: case LDRH_IMM_REG_OFF: case LDRSB_IMM_REG_POST_32: case LDRSB_IMM_REG_POST_64: case LDRSB_IMM_REG_PRE_32: 
    case LDRSB_IMM_REG_PRE_64: case LDRSB_IMM_REG_32: case LDRSB_IMM_REG_64: case LDRSH_IMM_REG_POST_32: case LDRSH_IMM_REG_POST_64: 
    case LDRSH_IMM_REG_PRE_32: case LDRSH_IMM_REG_PRE_64: case LDRSH_IMM_REG_32: case LDRSH_IMM_REG_64: case LDRSW_IMM_REG_POST: 
    case LDRSW_IMM_REG_PRE: case LDRSW_IMM_REG_OFF: case STR_IMM_REG_POST_32: case STR_IMM_REG_POST_64: case STR_IMM_REG_PRE_32: 
    case STR_IMM_REG_PRE_64: case STR_IMM_REG_32: case STR_IMM_REG_64: case STRB_IMM_REG_POST: case STRB_IMM_REG_PRE: case STRB_IMM_REG_OFF: 
    case STRH_IMM_REG_POST: case STRH_IMM_REG_PRE: case STRH_IMM_REG_OFF: case PRFM_REG_OFF: 
                     packet->execute_op = LS_REG_IMM_OP;
                     break;
    case LDR_REG_32: case LDR_REG_64: case LDRSW_REG: case PRFM_REG:
                     packet->execute_op = LOAD_REG_LITERAL_OP;
		     break;
    case LDTR_REG_32: case LDTR_REG_64: case LDTRB_REG: case LDTRH_REG: case LDTRSB_REG_32: case LDTRSB_REG_64: case LDTRSH_REG_32: 
    case LDTRSH_REG_64: case LDTRSW_REG: case STTR_REG_32: case STTR_REG_64: case STTRB_REG: case STTRH_REG: 
                     packet->execute_op = LS_REG_UNPRIVILEGED_OP;
                     break;
    case LDUR_IMM_REG_32: case LDUR_IMM_REG_64: case LDURB_IMM_REG: case LDURH_IMM_REG: case LDURSB_IMM_REG_32: case LDURSB_IMM_REG_64:
    case LDURSH_IMM_REG_32: case LDURSH_IMM_REG_64: case LDURSW_IMM_REG: case STUR_IMM_REG_32: case STUR_IMM_REG_64: case STURB_IMM_REG: 
    case STURH_IMM_REG: case PRFUM_IMM_REG:
                     packet->execute_op = LS_REG_UNSCALED_OP;
                     break;
    case LDR_REG_OFF_32: case LDR_REG_OFF_64: case LDRB_REG_OFF: case LDRH_REG_OFF: case LDRSB_REG_OFF_32: case LDRSB_REG_OFF_64: 
    case LDRSH_REG_OFF_32: case LDRSH_REG_OFF_64: case LDRSW_REG_OFF: case STR_REG_OFF_32: case STR_REG_OFF_64: case STRB_REG_OFF: 
    case STRH_REG_OFF: case PRFM_IMM_REG:
                     packet->execute_op = LS_REG_OFFSET_OP;
                     break;

    case MADD_32: case MADD_64: case SMADDL: case UMADDL: case MSUB_32: case MSUB_64: case SMSUBL: case UMSUBL: case SDIV_32: case SDIV_64:
    case UDIV_32: case UDIV_64: case UMULH:
                     packet->execute_op = MUL_DIV_OP;
                     break;

#include "VFP_CASES.C"
                     packet->execute_op = FLOAT_OP;
		     break;

#include "SIMD_CASES.C"
                     packet->execute_op = SIMD_OP;
		     break;

    default:           
                     packet->execute_op = UNKNOWN_OP;
                     packet->recordExceptionCondition(UNDEFINED_INSTRUCTION,UNALLOCATED_ENCODING); 
                     throw ARCH_EXCEPTION;
                     break;
  }
}

//---------------------------------------------------------------------------------------------------------------------------
// 'dispatch' A64 instructions. no floating pt or simd yet (ever?) sigh...
//---------------------------------------------------------------------------------------------------------------------------

void Control::Execute(unsigned int &multiplier) {
  //printf("[Execute] instruction index: %d...\n",packet->A64InstrIndex);

  SizeSourceOperands();

  instrID = packet->A64InstrIndex; //<---used for convenience within control class...

  IdentifyMachineOP();

  //printf("[Execute] go...\n");

  // execute machine op...

   multiplier = 1; // default clock phase multiplier of 1

  switch(packet->execute_op) {
    case ADDSUB_OP:              ExecuteAddSubtract();            break;
    case MRS_MSR_OP:             ExecuteMRS_MSR();                break;
    case MOVE_IMM_OP:            ExecuteMoveImmediate();          break;
    case LOGICAL_OP:             ExecuteLogical();                break;
    case LABEL_OP:               LabelOrPageAddress();            break;
    case SHIFT_OP:               ShiftOps();                      break;
    case HINT_OP:                Hint();                          break;
    case CLREX_OP:               ClearExclusiveMonitor();         break;
    case BRANCH_OP:              Branch();                        break;
    case BIT_FIELD_OP:           BitFieldOrCounts();              break;
    case DEBUG_OP:               DebugOp();                       break;
    case COMPARE_OP:             Comparison();                    break;
    case CHECKSUM_OP:            CheckSum();                      break;
    case CONDITIONAL_OP:         Conditional();                   break;
    case SYSTEM_OP:              System();                        break;
    case LS_EXCL_OP:             LoadStoreExclusive();            break;
    case LS_REG_PAIR_OP:         LoadStoreRegisterPair();         break;
    case LS_REG_PAIR_HINT_OP:    LoadStoreRegisterPairWithHint(); break;
    case LS_REG_IMM_OP:          LoadStoreRegisterImmediate();    break;
    case LOAD_REG_LITERAL_OP:    LoadRegisterLiteral();           break;
    case LS_REG_UNPRIVILEGED_OP: LoadStoreRegisterUnprivileged(); break;
    case LS_REG_UNSCALED_OP:     LoadStoreRegisterUnscaled();     break;
    case LS_REG_OFFSET_OP:       LoadStoreRegisterOffset();       break;

    case MUL_DIV_OP:             MultiplyDivide();                
                                 multiplier = 4;   // multi-phase multiply/divide
                                 break;

    case FLOAT_OP: 
    case SIMD_OP:                executeFloatSIMD(multiplier); 
                                 break;
                                     
    default: // should have already caught during decode, thus here is internal error...
             packet->recordExceptionCondition(UNIMPLEMENTED_INSTRUCTION); 
             throw INTERNAL_ERROR;
             break;
  }

  SizeDestOperands();

  if (sim_monitor) sim_monitor->Step(cpu,memory,packet,cpu->Clock(),cpu->GetID()); //<---allow exception to be traced

  InstrState(MEMORY_ACCESS_STATE); 
}


string Control::MachineOpName(int mop_id) {
  string _mop;

  switch(mop_id) {
    case ADDSUB_OP:              _mop = "ADDSUB";              break;
    case MRS_MSR_OP:             _mop = "MRS_MSR";             break;
    case MOVE_IMM_OP:            _mop = "MOVE_IMM";            break;
    case LOGICAL_OP:             _mop = "LOGICAL";             break;
    case LABEL_OP:               _mop = "LABEL";               break;
    case SHIFT_OP:               _mop = "SHIFT";               break;
    case HINT_OP:                _mop = "HINT";                break;
    case CLREX_OP:               _mop = "CLREX";               break;
    case BRANCH_OP:              _mop = "BRANCH";              break;
    case BIT_FIELD_OP:           _mop = "BIT_FIELD";           break;
    case DEBUG_OP:               _mop = "DEBUG";               break;
    case COMPARE_OP:             _mop = "COMPARE";             break;
    case CHECKSUM_OP:            _mop = "CHECKSUM";            break;
    case CONDITIONAL_OP:         _mop = "CONDITIONAL";         break;
    case SYSTEM_OP:              _mop = "SYSTEM";              break;
    case LS_EXCL_OP:             _mop = "LS_EXCL";             break;
    case LS_REG_PAIR_OP:         _mop = "LS_REG_PAIR";         break;
    case LS_REG_PAIR_HINT_OP:    _mop = "LS_REG_PAIR_HINT";    break;
    case LS_REG_IMM_OP:          _mop = "LS_REG_IMM";          break;
    case LOAD_REG_LITERAL_OP:    _mop = "LOAD_REG_LITERAL";    break;
    case LS_REG_UNPRIVILEGED_OP: _mop = "LS_REG_UNPRIVILEGED"; break;
    case LS_REG_UNSCALED_OP:     _mop = "LS_REG_UNSCALED";     break;
    case LS_REG_OFFSET_OP:       _mop = "LS_REG_OFFSET";       break;
    case MUL_DIV_OP:             _mop = "MUL_DIV";             break;

    default:                     _mop = "NONE";                break;
  }
 
  return _mop;
}

