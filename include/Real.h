#include <cmath>
#include <cfenv>
#include <math.h>

#include <string>

// keep it real...

class Real {
 public:
  Real(bool _AHP, bool _FTZ) : AHP(_AHP), FTZ(_FTZ), real(0),
     overflow(false), underflow(false) {};

  enum FPINTYPES { FP_HALF, FP_SINGLE, FP_DOUBLE };
  enum FPTYPES { FPType_Zero, FPType_NonZero, FPType_Infinity, FPType_QNaN, FPType_SNaN };

  void UnpackHalf(unsigned long long _fpval)   { unpack(FP_HALF,  _fpval); };
  void UnpackFloat(unsigned long long _fpval)  { unpack(FP_SINGLE,_fpval); };
  void UnpackDouble(unsigned long long _fpval) { unpack(FP_SINGLE,_fpval); };

  void Scale(int _scale);

  bool IsNormal()   { return type==FPType_NonZero;  };
  bool IsZero()     { return type==FPType_Zero;     };
  bool IsInfinity() { return type==FPType_Infinity; };
  bool IsQNaN()     { return type==FPType_QNaN;     };
  bool IsSNaN()     { return type==FPType_SNaN;     };

  bool Overflow()   { return overflow; };
  bool Underflow()  { return underflow; };
  
  std::string Type();
  
  int Sign() { return sign; };
  unsigned long long ValueAsReal() { return real; };
  double ValueAsDouble() { return (sign == 0) ? dval : -dval; };

  double RealToDouble();
  long long RealToInt();
  
 private:

  void   unpack(int _input_type, unsigned long long _fpval);
  void   double2real(double fp);
  double normalize();
  void   unpack_normal();
  bool   exponent_is_all_ones();
  bool   is_signaling_nan();
  double infinity();
  bool   flush_to_zero();
  void   breakout_parts();
  void   unpackHalf(int _input_type, unsigned long long _fpval);
 
  bool AHP;                 // alternate (non-IEE compliant) half-precision mode
  bool FTZ;                 // flush-to-zero (non-IEE compliant) mode

  int input_type;           // half vs single vs double
  unsigned long long fpval; // input floating point number stored in binary
  
  int sign;                 // number sign
  unsigned int exp;         // exponent bits
  unsigned long long frac;  // fractional bits

  int type;                 // zero vs infinity vs NaN vs normal number

  double dval;              // resulting double-precision number
  
  unsigned long long real;  // resulting real (binary) number
  int decimal_point;        // decimal place within real number
  bool overflow;            // set if conversion of normal float mantissa into real is zero
  bool underflow;           // set if conversion of normal float number into real is zero
};

