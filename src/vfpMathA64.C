#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <cfenv>
#include <math.h>

//#pragma STDC FENV_ACCESS ON

#include "a64_vfpMath.h"


//#define DEBUG_VFP 1

#define INTERNAL_ERROR 6

//---------------------------------------------------------------------------------------------------------------------------
// Here are the actual vfp math methods, implemented via c/c++99 functions. Thus these may not (probably won't) match exactly
// some particular (any?) arm implementation... 
//---------------------------------------------------------------------------------------------------------------------------

float vfpMath::FPAbs(float src) {
  return fabs(src);
}

float vfpMath::FPNeg(float src) {
  return -src;
}

float vfpMath::FPSqrt(float src) {
  float result = sqrt(src);

  if ((src < 0.0) && std::isnan(result) && std::signbit(result)) // sqrt of negative number yields -=NaN. for arm, make positive, ie, FPDefaultNaN
    result = -result;

  return result;
}

float vfpMath::FPAdd(float src1,float src2) { 
  float result;
  try {
     result = src1 + src2;
  } catch(...) {
     printf("[vfpMath::FPAdd] TOOK EXCEPTION???\n");
  }

  return result; 
}

float vfpMath::FPNeg(float src1,float src2) {
  return src1 - src2;
}

float vfpMath::FPDiv(float src1,float src2) { 
  float result = src1 / src2; 

  if ( (std::fpclassify(src2) == FP_ZERO) ) { // division by zero should yield positive NaN
    result = fabs(result);
  }
  
  return result;
}

float vfpMath::FPMulAdd(float src1,float src2,float src3) {
  return src1 + src2 * src3;
}

float vfpMath::FPMax(float src1,float src2) {
  float result;
  
  if (std::isnan(src1))
    result = src1;
  else if (std::isnan(src2))
    result = src2;
  else
    result = fmax(src1,src2);

  return result;
}

float vfpMath::FPMaxNum(float src1,float src2) { 
  if (std::isnan(src1) && !std::isnan(src2))      src1 = -INFINITY;
  else if (!std::isnan(src1) && std::isnan(src2)) src2 = -INFINITY;
  return FPMax(src1,src2); 
}

float vfpMath::FPMin(float src1,float src2) {
  float result = fminf(src1,src2);
  if (std::fpclassify(result) == FP_ZERO) {
    // if result is zero use 'most negative' sign bit...
    if ( (std::signbit(src1) || std::signbit(src2)) && !std::signbit(result) ) {
      result = -result;
    }
  }
  return result;
}

float vfpMath::FPMinNum(float src1,float src2) { 
  if (std::isnan(src1) && !std::isnan(src2))      src1 = INFINITY;
  else if (!std::isnan(src1) && std::isnan(src2)) src2 = INFINITY;
  return FPMin(src1,src2); 
}

float vfpMath::FPMul(float src1,float src2) {
  return src1 * src2;
}

#define ARM_ROUNDDOWN 2
#define FE_TIEAWAY FE_TONEAREST
void vfpMath::setFPRoundingMode(int rmode) {
  switch(rmode) {
    case 0:  std::fesetround(FE_TONEAREST);  
#ifdef DEBUG_VFP
             printf("[Control::setFPRoundingMode] rmode: 0 (FE_TONEAREST)\n");
#endif
             break;
    case 1:  std::fesetround(FE_UPWARD);
#ifdef DEBUG_VFP
             printf("[Control::setFPRoundingMode] rmode: 1 (FE_UPWARD)\n");
#endif
             break;
    case 2:  std::fesetround(FE_DOWNWARD);   
#ifdef DEBUG_VFP
             printf("[Control::setFPRoundingMode] rmode: 2 (FE_DOWNWARD)\n");
#endif
             break;
    case 3:  std::fesetround(FE_TOWARDZERO); 
#ifdef DEBUG_VFP
             printf("[Control::setFPRoundingMode] rmode: 3 (FE_TOWARDZERO)\n");
#endif
             break;
    case 4:  std::fesetround(FE_TIEAWAY);  
#ifdef DEBUG_VFP
             printf("[Control::setFPRoundingMode] rmode: 4 (FE_TIEAWAY - using FE_TONEAREST instead)\n");
#endif
             break;
    default:
#ifdef DEBUG_VFP
             printf("[setFPRoundingMode] invalid rounding mode: %d\n",rmode);
#endif
             throw INTERNAL_ERROR;
             break;
  }
}


float vfpMath::FPRoundInt(float src1, int rounding, bool /* exact*/) {
  if (src1 == 0.0) return src1; // always return zero for zero, irregardless of rounding mode...

#ifdef DEBUG_VFP
  union {
    float fs;
    unsigned int fu;
  } tmp;
  tmp.fs = src1;

  printf("[vfpMath::FPRoundInt] src1: %f (0x%x) rounding: %d\n",src1,tmp.fu,rounding);
#endif
  
  setFPRoundingMode(rounding);

  return nearbyint(src1); // NOTE: we do NOT support exceptions and thus 'exact' arg ignored...
}

double vfpMath::FPAbs(double src) {
  return fabs(src);
}

double vfpMath::FPNeg(double src) {
  return -src; }

double vfpMath::FPSqrt(double src) {
  long double sr = sqrtl(src);

  if (src < 0.0 && std::isnan(sr) && std::signbit(sr))    // sqrt of negative number yields -=NaN. for arm, make positive, ie, FPDefaultNaN
    sr = -sr;

#ifdef DEBUG_VFP
  printf("[vfpMath::FPSqrt/double] src: %g, result: %Lf\n\n",src,sr);
#endif
  
  return (double) sr;
}

double vfpMath::FPAdd(double src1,double src2) { 
    return src1 + src2; 
}

double vfpMath::FPNeg(double src1,double src2) {
  return src1 - src2;
}

double vfpMath::FPDiv(double src1,double src2) {
  double result = src1 / src2; 

  if ( (std::fpclassify(src2) == FP_ZERO) ) { // division by zero should yield positive NaN
    result = fabs(result); 
  }

  return result;
}

double vfpMath::FPMulAdd(double src1,double src2,double src3) {
  return src1 + src2 * src3;
}

double vfpMath::FPMax(double src1,double src2) {
  double result;
  
  if (std::isnan(src1))
    result = src1;
  else if (std::isnan(src2))
    result = src2;
  else
    result = fmax(src1,src2);

  return result;
}

double vfpMath::FPMaxNum(double src1,double src2) { 
  if (std::isnan(src1) && !std::isnan(src2))      src1 = -INFINITY;
  else if (!std::isnan(src1) && std::isnan(src2)) src2 = -INFINITY;
  return FPMax(src1,src2); 
}

double vfpMath::FPMin(double src1,double src2) {
  double result = fminl(src1,src2);
  if (std::fpclassify(result) == FP_ZERO) {
    // if result is zero use 'most negative' sign bit...
    if ( (std::signbit(src1) || std::signbit(src2)) && !std::signbit(result) ) {
      result = -result;
    }
  }
  return result;
}

double vfpMath::FPMinNum(double src1,double src2) { 
  if (std::isnan(src1) && !std::isnan(src2)) {
    src1 = INFINITY;
  } else if (!std::isnan(src1) && std::isnan(src2)) { 
    src2 = INFINITY;
  }
  
  return FPMin(src1,src2); 
}

double vfpMath::FPMul(double src1,double src2) { 
  double result = src1 * src2; 
  return result;
}

double vfpMath::FPRoundInt(double src1, int rounding, bool /*exact*/) {
#ifdef DEBUG_VFP
  printf("[vfpMath::FPRoundInt] src1: %g (0x%llx) rounding: %d\n",src1,(unsigned long long) src1,rounding);
#endif
  
  setFPRoundingMode(rounding);

  return nearbyint(src1); // NOTE: we do NOT support exceptions and thus 'exact' arg ignored...
}

unsigned long long vfpMath::underflow(bool &saturate, double fv, unsigned long long uv, bool is_unsigned, int size) {
  // set min possible value...
  unsigned long long min_val = (size==64) ? 0x8000000000000000ull : 0x80000000ull;

  // if result is to be signed, then check fp value against minimum int value...
  if (!is_unsigned && (round(fv) < min_val)) {
    saturate = true;
    return 0;
  }
  
  // we ASSUME a negative value will underflow if converted to unsigned(?)...
  //if (is_unsigned && fv < 0.0) {
  //  saturate = true;
  //  return 0;
  //}
  
  // we think no underflow...
  return uv;
}
unsigned long long vfpMath::overflow(bool &saturate, double fv, unsigned long long uv, bool is_unsigned, int size) {
  // set maximum possible value...
  unsigned long long max_val = (size==64) ? 0xffffffffffffffffull : 0xffffffffull;
  if (!is_unsigned)
    max_val = (size==64) ? 0x7fffffffffffffffull : 0x7fffffffull;

  // check for overflow on positive value...
  
  if ((fv >= 0.0) && roundf(fv) > max_val) {
    saturate = true;
    return max_val;
  }
  
  // if unsigned result desired and input value is negative, see if coercing
  // to unsigned overflows...
  
  if (is_unsigned && (fv < 0.0) && ( ((unsigned long long) fv ) > max_val)) {
    saturate = true;
    return max_val;
  }
  
  // we think no overflow...
  return uv;
}
unsigned long long vfpMath::roundUp(bool &inexact, double fv, bool is_unsigned, int rounding) {
  // we ASSUME overflow or underflow checked elsewhere...

  union {
    unsigned long long ur;
    long long lr;
  } rx;

  double err = 0; // difference between float value and int value...
  
  if (is_unsigned) {
    rx.ur = (unsigned long long) fv;
    err = fv - rx.ur;
  } else {
    rx.lr = (long long) fv;
    err = fv - rx.lr;
  }

  inexact = err != 0.0;
  
  unsigned long long r = rx.ur;

  // apply arm-defined rounding...
  
  int roundup = 0;
  
  switch(rounding) {
    case 0:  // FProunding_TIEEVEN
             if ( (err > 0.5) || ( (err == 0.5) && ((r & 1) == 1) ) )
	       roundup = 1;
             break;
    case 1:  // FProunding_POSINF
             if (err != 0.0)    //<---any fractional value results in rounding up
	       roundup = 1;
             break;
    case 2:  // FProunding_NEGINF
             // roundup = 0;      //<---float value already rounded down///
             break;
    case 3:  // FProunding_ZERO
             if ( (err != 0.0) && (r < 0) )
	       roundup = 1;       //<---any fractional negative value results in rounding up
             break;
    case 4:  // FProunding_TIEAWAY
             if ((err > 0.5) || ((err == 0.5) && (r >= 0)) )
	       roundup = 1;
             break;
    default: // invalid case...
             throw INTERNAL_ERROR;
             break;
  }

  r += roundup;

  return r;
}

float vfpMath::FixedToFP32(unsigned long long intval_in, int fbits, bool is_unsigned,int rounding, int intsize) {
#ifdef DEBUG_VFP
  printf("[vfpMath::FixedToFP32] intval_in: 0x%llx, fbits: %d, unsigned? %d, rounding: %d, intsize: %d\n",
	 intval_in,fbits,is_unsigned,rounding,intsize);
#endif
  
  setFPRoundingMode(rounding);

  float df = 0.0;

  if (intsize == 32) {
    intval_in = intval_in & 0xffffffffull;
    if (is_unsigned)
      df = intval_in;
    else
      df = (int) intval_in;
  } else {
    if (is_unsigned)
      df = intval_in;
    else
      df = (long long int) intval_in;
  }
  
#ifdef DEBUG_VFP
  printf("[vfpMath::FixedToFP32] df: %f (0x%llx)\n",df, (unsigned long long) df);
#endif
  
//  df = (fbits != 0) ? df / powf(2.0, (float) fbits) : df;

  df = (fbits != 0) ? df / std::exp2( fbits ) : df;

#ifdef DEBUG_VFP
  printf("[vfpMath::FixedToFP32] df (rounded): %f\n",df);
#endif
  
  return df;
}

double vfpMath::FixedToFP64(unsigned long long intval_in, int fbits, bool is_unsigned,int rounding, int intsize) {
#ifdef DEBUG_VFP
  printf("[vfpMath::FixedToFP64] intval_in: 0x%llx, fbits: %d, unsigned? %d, rounding: %d, intsize: %d\n",
	 intval_in,fbits,is_unsigned,rounding,intsize);
#endif
  
  setFPRoundingMode(rounding);

  double df = 0.0;

  if (intsize == 32) {
    intval_in = intval_in & 0xffffffffull;
    if (is_unsigned)
      df = intval_in;
    else
      df = (int) intval_in;
  } else {
    if (is_unsigned)
      df = intval_in;
    else
      df = (long long int) intval_in;
  }
  
#ifdef DEBUG_VFP
  printf("[vfpMath::FixedToFP64] df: %g (0x%llx)\n", df, (unsigned long long) df);
#endif
  
  //df = (fbits != 0) ? df / pow(2.0, (double) fbits) : df;

  df = (fbits != 0) ? df / std::exp2( fbits ) : df;

#ifdef DEBUG_VFP
  printf("[vfpMath::FixedToFP64] df (rounded): %g\n",df);
#endif
  
  return df;
}

unsigned int vfpMath::FPCompare(float operand1,float operand2,bool /*signal_all_nans*/) {
  unsigned int result = 0;

  if (std::isnan(operand1) || std::isnan(operand2)) {
    result = 3;
    // NOTE: vfp exceptions NOT supported and thus NOT checking signaling NaNs...
  } else {
    if (operand1 == operand2)
      result = 6;
    else if (operand1 < operand2)
      result = 8;
    else // operand1 > operand2
      result = 2;
  }
  
#ifdef DEBUG_VFP
  printf("[vfpMath::FPCompare] operand1: %f, operand2: %f, result: %u\n",operand1,operand2,result);
#endif
  
  return result;
}

unsigned int vfpMath::FPCompare(double operand1,double operand2,bool /*signal_all_nans*/) {
  unsigned int result = 0;

  if (std::isnan(operand1) || std::isnan(operand2)) {
    result = 3;
    // NOTE: vfp exceptions NOT supported and thus NOT checking signaling NaNs...
  } else {
    if (operand1 == operand2)
      result = 6;
    else if (operand1 < operand2)
      result = 8;
    else // operand1 > operand2
      result = 2;
  }
  
  return result;
}
