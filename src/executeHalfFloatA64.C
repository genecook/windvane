#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <cfenv>
#include <math.h>

//#pragma STDC FENV_ACCESS ON

#include "a64sim.h"
#include "half.hpp"

//#define DEBUG_VFP 1

float Control::FPHalfPrecisionToFloat(unsigned int hp_fpval) {
  half_float::half mfh(1.0);

  unsigned int *up = (unsigned int *) &mfh;

  *up = hp_fpval;
 
  return (float) mfh;
}

double Control::FPHalfPrecisionToDouble(unsigned int hp_fpval) {
  half_float::half mfh(1.0);

  unsigned int *up = (unsigned int *) &mfh;

  *up = hp_fpval;

  return (double) mfh;
}

unsigned int Control::FPFloatToHalfPrecision(float src) {
  half_float::half mfh2;

  switch((int) cpu->FPCR.RMode()) {
    case FE_TOWARDZERO: { half_float::half mfh = half_float::half_cast<half_float::half,std::round_toward_zero>(src);
                          mfh2 = mfh;
                        }
                        break;
    case FE_TONEAREST:  { half_float::half mfh = half_float::half_cast<half_float::half,std::round_to_nearest>(src);
                          mfh2 = mfh;
                        }
                        break;
    case FE_UPWARD:     { half_float::half mfh = half_float::half_cast<half_float::half,std::round_toward_infinity>(src);
                          mfh2 = mfh;
                        }
                        break;
    case FE_DOWNWARD:   { half_float::half mfh = half_float::half_cast<half_float::half,std::round_toward_neg_infinity>(src);
                          mfh2 = mfh;
                        }
                        break;
    default:            { half_float::half mfh = half_float::half_cast<half_float::half>(src);
                          mfh2 = mfh;
                        }
                        break;
  }

#ifdef DEBUG_VFP
  std::cout << "[Control::FPSingleToHalfPrecision TZ] src: " << src << " half-result: " << mfh2 << std::endl;
#endif
  
  unsigned int *up = (unsigned int *) &mfh2;
  unsigned int result = *up & 0xffff;

#ifdef DEBUG_VFP
  printf("[Control::FPSingleToHalfPrecision] src: %g result: 0x%x\n",src, result);
#endif

  if (fabsf(src) > 65504)
    std::feraiseexcept(FE_OVERFLOW);
  
  return result;
}

unsigned int Control::FPDoubleToHalfPrecision(double src) {
  half_float::half mfh2;

  switch((int) cpu->FPCR.RMode()) {
    case FE_TOWARDZERO: { half_float::half mfh = half_float::half_cast<half_float::half,std::round_toward_zero>(src);
                          mfh2 = mfh;
                        }
                        break;
    case FE_TONEAREST:  { half_float::half mfh = half_float::half_cast<half_float::half,std::round_to_nearest>(src);
                          mfh2 = mfh;
                        }
                        break;
    case FE_UPWARD:     { half_float::half mfh = half_float::half_cast<half_float::half,std::round_toward_infinity>(src);
                          mfh2 = mfh;
                        }
                        break;
    case FE_DOWNWARD:   { half_float::half mfh = half_float::half_cast<half_float::half,std::round_toward_neg_infinity>(src);
                          mfh2 = mfh;
                        }
                        break;
    default:            { half_float::half mfh = half_float::half_cast<half_float::half>(src);
                          mfh2 = mfh;
                        }
                        break;
  }

#ifdef DEBUG_VFP
  std::cout << "[Control::FPDoubleToHalfPrecision TZ] src: " << src << " half-result: " << mfh2 << std::endl;
#endif
  
  unsigned int *up = (unsigned int *) &mfh2;
  unsigned int result = *up & 0xffff;

#ifdef DEBUG_VFP
  printf("[Control::FPDoubleToHalfPrecision] src: %g result: 0x%x\n",src, result);
#endif
  
  if (fabs(src) > 65504)
    std::feraiseexcept(FE_OVERFLOW);
  
  return result;
}
