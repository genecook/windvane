#include "Real.h"

//******************************************************************************************
// Real - class used to manage real numbers. Includes methods to unpack half/single/double
//        precision numbers into a 'real' (64 bits worth of binary digits with sign and
//        decimal place).
//
// half-precision float stored in low order 16 bits...
//
// for half-precision:
//    sign bit is 16
//    5 bit exponent
//    low order bit of exponent is then bit 15
//    low order 12 bits are mantissa
//
// single-precision float stored in low order 32 bits...
//
// for single-precision:
//    sign bit is 31
//    8 bit exponent
//    low order bit of exponent is then bit 23
//    low order 23 bits are mantissa
//
// double-precision is 64 bits...
//
// for double-precision:
//    sign bit is 63
//    11 bit exponent
//    low order bit of exponent is then bit 52
//    low order 52 bits are mantissa
//******************************************************************************************

//******************************************************************************************
// _unpack - unpack floating point value into its constitute parts, characterize the
//           value, convert to real...
//******************************************************************************************

double Real::infinity() {
  return HUGE_VAL;
}

void Real::unpack(int _input_type, unsigned long long _fpval) {
  input_type = _input_type;
  fpval      = _fpval;
  
  breakout_parts(); // sign, exponent, fractional values split out here
  
  if (exp==0) {
    // exponent is zero...
    if ( (frac==0) || flush_to_zero() ) {
      // exponent and fraction are zero, ie, value is indeed zero...
      type = FPType_Zero;
      dval = 0.0;
      real = 0;
    } else {
      // exponent is zero, but fraction is not...
      type = FPType_NonZero;
      // normalize it, then make it real...
      dval = normalize();
      double2real(dval);
    }
  } else if (exponent_is_all_ones()) {
    // exponent is all ones...
    if (frac==0) {
      // exponent is all ones and fraction is all zeros, ie, infinity...
      type = FPType_Infinity;
      dval = infinity();
      real = 0;
    } else {
      // exponent is all ones with non-zero fraction, ie, NaN...
      type = is_signaling_nan() ? FPType_QNaN : FPType_SNaN;
      dval = 0.0;
      real = 0;
    }
  } else {
    // convert 'normal' number...
    type = FPType_NonZero;
    unpack_normal();
  }
}

//******************************************************************************************
// _breakout_parts() - break out sign, exponent, and fractional part from floating point
//                     (binary) value...
//******************************************************************************************

void Real::breakout_parts() {
  switch(input_type) {
    case FP_HALF:     sign = (fpval>>15) & 1;  
                      exp  = (fpval>>10) & 0x1f;  
                      frac = fpval & 0x3ff;     
                      break;
    case FP_SINGLE:   sign = (fpval>>31) & 1;
                      exp  = (fpval>>23) & 0xff;
                      frac = fpval & 0x7fffff;
                      break;
    case FP_DOUBLE:   sign = (fpval>>63) & 1;
                      exp = (fpval>>52) & 0x7ff;
                      frac = fpval & 0xffffffffffffull;
                      break;
    default: // should throw some sort of exception here...
             break;
  }
}

//******************************************************************************************
// _flush_to_zero() - return true if flush-to-zero mode enabled...
//******************************************************************************************

bool Real::flush_to_zero() {
  bool do_flush = false;

  switch(input_type) {
    case FP_HALF:   // no flush to zero for half-precision...
                    break;
    case FP_SINGLE:
    case FP_DOUBLE: do_flush = (FTZ==1);
                    break;
    default: // should throw some sort of exception here...
             break;
  }

  return do_flush;
}

//******************************************************************************************
// _normalize() - convert a 'denormal' floating point value into normal form...
//******************************************************************************************

double Real::normalize() {
  double fv = 0.0;
  
  switch(input_type) {
    case FP_HALF:   fv = powf(2.0,-14.0)  * ldexpf(frac,-10.0); break;
    case FP_SINGLE: fv = powf(2.0,-126.0) * ldexpf(frac,-23.0); break;
    case FP_DOUBLE: fv = powf(2.0,-126.0) * ldexpl(frac,-23.0); break;
    default: // should throw some sort of exception here...
    break;
  }

  return fv;
}

//******************************************************************************************
// convert double precision floating point value to real ('string' of binary digits and
// decimal point index)...
//******************************************************************************************

void Real::double2real(double _fp) {
   double fp = fabs(_fp);  // we already recorded the sign
  
   // Separate integer and fractional parts...

   double fp_int, fp_frac;

   fp_frac = modf(fp,&fp_int);

   // start with integer part...

   real = (unsigned long long) fp_int; // coerce to ull

   if (real != fp_int) // if real does not equal integer portion of original #
     overflow = true;  // ASSUME overflow...
   
   // now fraction...

   decimal_point = 0;

   // add in bits from fraction, shifting real bits left each time
   // but only as long as there is 'room' in the result, ie,
   // as long as no significant bits are shifted out... 
   
   while((fp_frac > 0) && ( (real>>63) != 1 ) ) {
     fp_frac *= 2;
     fp_frac = modf(fp_frac,&fp_int);
     real = (real<<1) | ( (lrint(fp_int) > 0) ? 1 : 0 );
     decimal_point += 1;
   }

   // if resulting real is zero then ASSUME underflow has occurred...

   if (real == 0)
     underflow = true;
}

//******************************************************************************************
// _exponent_is_all_ones() - return true if exponent is all ones...
//******************************************************************************************

bool Real::exponent_is_all_ones() {
  bool all_ones = false;
  
  switch(input_type) { 
    case FP_HALF:   // FPCR.AHP - if set, then alternate (non-IEEE) mode...
                    all_ones = (exp==0x1f) && (AHP==0);
                    break;
    case FP_SINGLE: all_ones = (exp==0xff);
                    break;
    case FP_DOUBLE: all_ones = (exp==0x7ff);
                    break;
    default: // should throw some sort of exception here...
             break;
  }

  return all_ones;
}

//******************************************************************************************
// _is_signaling_nan() - Not-a-Number detected, return true if a Signaling NaN...
//******************************************************************************************

bool Real::is_signaling_nan() {
  bool is_snan = false;
  
  switch(input_type) {
    case FP_HALF:   is_snan = ((frac>>9)  & 1)==1;  break;
    case FP_SINGLE: is_snan = ((frac>>22) & 1)==1;  break;
    case FP_DOUBLE: is_snan = ((frac>>51) & 1)==1;  break;
    default: // should throw some sort of exception here...
             break;
  }

  return is_snan;
}

//******************************************************************************************
// _unpack_normal() - convert 'normal' (not zero or infinity or NaN) floating point value
//                    into real binary number with decimal place...
//******************************************************************************************

void Real::unpack_normal() {
  switch(input_type) {
    case FP_HALF:   {
                     // convert half-precision value into double precision, then to real... 
                     dval = powf(2.0,exp-15) * (1.0 + ldexpf(frac,-10.0));
                     double2real(dval);
                    }
                    break;
    case FP_SINGLE: {
                     // work from 'original' number...
                     union {
                       float fv;
                       unsigned int uv;
                     } tmp;
                     tmp.uv = fpval;
		     dval = tmp.fv;
                     double2real(dval);
                    }
                    break;
    case FP_DOUBLE: {
                     // work from 'original' number...
                     union {
                       double fv;
                       unsigned long long uv;
                     } tmp;
                     tmp.uv = fpval;
		     dval = tmp.fv;
                     double2real(dval);
                    }
                    break;
    default:        // should throw some sort of exception here...
    break;
  }
}

//******************************************************************************************
// Type() - return real number tgype as string...
//******************************************************************************************

std::string Real::Type() {
  std::string _type;
  
  switch(type) {
    case FPType_Zero:     _type = "ZERO";     break;
    case FPType_NonZero:  _type = "NON-ZERO"; break;
    case FPType_Infinity: _type = "INFINITY"; break;
    case FPType_QNaN:     _type = "QNAN";     break;
    case FPType_SNaN:     _type = "SNAN";     break; 
    default:              _type = "UNKNOWN";  break;
  }

  return _type;
}


//******************************************************************************************
// RealToDouble(), RealToInt() - operate on real number to result either double or int...
//******************************************************************************************

double Real::RealToDouble() {
  double result = 0.0;
  
  if (type == FPType_NonZero) {
    unsigned long long int_bits  = real >> decimal_point;
    unsigned long long frac_bits = (real & (1<<decimal_point)) - 1; 
    double fb = (double) frac_bits;
    for (int i = 0; i < decimal_point; i++) {
       fb = fb / 2;
    }
    result = (double) int_bits + fb;
    if (sign)
      result = -result;
  }
  
  return result;
}

long long Real::RealToInt(/*bool round_up*/) {
  long long result = (long long) (real >> decimal_point); // effectively rounding to zero or down
/*
  if (round_up) {
    double diff = dval - (double) result;
    if (diff >= 0.5)
      result += 1;
  }
*/  
  if (sign)
    result = -result;
  
  return result;
}
