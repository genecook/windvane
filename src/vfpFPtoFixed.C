#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <cfenv>
#include <math.h>
#include <limits.h>
#include <assert.h>

#include "a64_vfpMath.h"

//#define DEBUG_VFP 1

#define INTERNAL_ERROR 6


//*****************************************************************************************************
// return whole part, fractional part of floating pt value, also overflow/underflow indicators...
//*****************************************************************************************************

unsigned int vfpMath::ToUnsignedInt(double src, double &err, bool &overflow, bool &underflow) {
#ifdef DEBUG_VFP
  printf("[vfpMath::ToUnsignedInt] src: %g\n",src);
#endif
  
  double intval = nearbyint(src);
  err = src - intval;

  unsigned int ix = 0;
  
  if (Is_NaN(src)) {
    ix = 0;
    err = 0;
  } else if (intval > 2.0*(UINT_MAX/2 + 1)) {
    overflow = true;
    ix = UINT_MAX;
  } else if (intval < 0) {
    underflow = true;
    ix = 0;
  } else {
    ix = intval;
  }

#ifdef DEBUG_VFP
  printf("[vfpMath::ToUnsignedInt] src: %g, intval: %g, err: %g, ix: %u (0x%x), overflow: %d, underflow: %d\n",
	 src,intval,err,ix,ix,overflow,underflow);
#endif

  return ix;
}
  
unsigned long long vfpMath::ToUnsignedLong(double src, double &err, bool &overflow, bool &underflow) {
#ifdef DEBUG_VFP
  printf("[vfpMath::ToUnsignedLong] src: %g\n",src);
#endif
  
  double intval = nearbyint(src);
  err = src - intval;

  unsigned long long ix = 0;
  
  if (Is_NaN(src)) {
    ix = 0;
    err = 0;
  } else if (intval > 2.0*(ULONG_MAX/2 + 1)) {
    overflow = true;
    ix = ULONG_MAX;
  } else if (intval < 0) {
    underflow = true;
    ix = 0;
  } else {
    ix = (unsigned long long) intval;
  }
  
#ifdef DEBUG_VFP
  printf("[vfpMath::ToUnsignedLong] src: %g, intval: %g, err: %g, ix: %llu (0x%llx), overflow: %d, underflow: %d\n",
	 src,intval,err,ix,ix,overflow,underflow);
#endif
  
  return (unsigned long long) ix;
}

// std::isnan seems to fail depending (anecdotely) on what compile flags are set.
// lets cut to the chase...

bool vfpMath::Is_NaN(double src) {
  union {
    double d;
    unsigned long long u;
  } xx;
  
  xx.d = src;
  
  bool is_nan = ( ( (xx.u >> 52) & 0x7ff) == 0x7ff) && ( (xx.u & 0xfffffffffffff) != 0);

#ifdef DEBUG_VFP
  printf("[vfpMath::ToInt] is NaN? %s (xx.u: 0x%llx, exp: 0x%llx, mantissa: 0x%llx)\n",
	 (is_nan ? "yes" : "no"),xx.u, ((xx.u >> 52) & 0x7ff), (xx.u & 0xfffffffffffff) );
#endif
  
  return is_nan;
}

int vfpMath::ToInt(double src, double &err, bool &overflow, bool &underflow) {
#ifdef DEBUG_VFP
  printf("[vfpMath::ToInt] src: %g\n",src);
#endif
  
  double intval = nearbyint(src);
  err = src - intval;

  int ix = 0;

  if (Is_NaN(src)) {
    ix = 0;
    err = 0;
  } else if (intval > 2.0*(INT_MAX/2 + 1)) {
    overflow = true;
    ix = INT_MAX;
  } else if (intval < 2.0*(INT_MIN/2 - 1)) {
    underflow = true;
    ix = intval;
  } else {
    ix = intval;
  }

#ifdef DEBUG_VFP
  printf("[vfpMath::ToInt] src: %g, intval: %g, err: %g, ix: %d (0x%x), overflow: %d, underflow: %d\n",
	 src,intval,err,ix,(unsigned) ix,overflow,underflow);
#endif
  
  return ix;
}

long long vfpMath::ToLong(double src, double &err, bool &overflow, bool &underflow) {
  double intval = nearbyint(src);
  err = src - intval;

  long long ix = 0;

  if (Is_NaN(src)) {
    ix = 0;
    err = 0;
  } else if (intval > 2.0*(LLONG_MAX/2 + 1)) {
    overflow = true;
    ix = LLONG_MAX;
  } else if (intval < 2.0*(LLONG_MIN/2 - 1)) {
    underflow = true;
    ix = intval;
  } else {
    ix = intval;
  }
  
#ifdef DEBUG_VFP
  printf("[vfpMath::ToLong] src: %g, intval: %g, err: %g, ix: %lld (0x%llx), overflow: %d, underflow: %d\n",
	 src,intval,err,ix,(unsigned long long) ix,overflow,underflow);
#endif
  
  return ix;
}

//*****************************************************************************************************
// vfpMath::FPToFixed64
//*****************************************************************************************************

unsigned long long vfpMath::FPToFixed64(double fltval_in, int fbits, bool is_unsigned, int rounding, int intsize) {
#ifdef DEBUG_VFP
  printf("[vfpMath::FPToFixed64] fltval_in: %g, fbits: %d, unsigned? %d, rounding: %d, intsize: %d\n",
	 fltval_in, fbits, is_unsigned, rounding, intsize);
#endif

  assert((intsize == 32) || (intsize == 64));
  
  setFPRoundingMode(rounding);
  
  unsigned long long rval = 0;
  
  double dbl_value = (fbits != 0) ? fltval_in * pow(2.0, (double) fbits) : fltval_in;
  
  double err = 0.0;
  bool overflow = false;
  bool underflow = false;

  int fpcase = ((is_unsigned) ? 1 : 0) | intsize;

  enum { UNSIGNED_32=0x21, UNSIGNED_64=0x41, SIGNED_32=0x20,SIGNED_64=0x40 };
  
  switch(fpcase) {
    case UNSIGNED_32: rval = ToUnsignedInt(dbl_value,err,overflow,underflow);
                      break;
		      
    case UNSIGNED_64: rval = ToUnsignedLong(dbl_value,err,overflow,underflow);
                      break;
		      
    case SIGNED_32:   rval = ToInt(dbl_value,err,overflow,underflow) & 0xffffffff;
                      break;
		      
    case SIGNED_64:   rval = ToLong(dbl_value,err,overflow,underflow);
                      break;
		      
    default: throw(INTERNAL_ERROR);
             break;
  }

  if (fltval_in == 0.0) {
    // C float methods could have set Inexact bit, but if err (difference between original float value and int value) is zero, then
    //  clear Inexact...
    std::feclearexcept(FE_INEXACT);
  }

  if (overflow) {
    // we know overflow results in invalid-op flag being set...
    std::feraiseexcept(FE_INVALID);
    std::feclearexcept(FE_OVERFLOW);
  } else if (underflow) {
    // we think underflow does too(?)...
    std::feraiseexcept(FE_INVALID);
  }
  
  
#ifdef DEBUG_VFP
  printf("[vfpMath::FPToFixed64] rval: %llu (0x%llx), err: %g, overflow? %s, underflow: %s\n",
         rval,rval,err,(overflow ? "yes" : "no"), (underflow ? "yes" : "no"));
#endif
  
  return rval;
}

//*****************************************************************************************************
// vfpMath::FPToFixed32
//*****************************************************************************************************

unsigned long long vfpMath::FPToFixed32(float fltval_in, int fbits, bool is_unsigned, int rounding, int intsize) {
#ifdef DEBUG_VFP
  printf("[vfpMath::FPToFixed32] fltval_in: %f, fbits: %d, unsigned? %d, rounding: %d, intsize: %d\n",
	 fltval_in, fbits, is_unsigned, rounding, intsize);  
#endif

  unsigned long long rval = FPToFixed64((double) fltval_in,fbits,is_unsigned,rounding,intsize);

#ifdef DEBUG_VFP
  printf("[vfpMath::FPToFixed32] rval: %llu (0x%llx)\n", rval,rval);
#endif

  return rval;
}


