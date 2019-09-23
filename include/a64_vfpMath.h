#ifndef __VFPMATH__

class vfpMath {
 public:
  vfpMath() {};
  ~vfpMath() {};

  void setFPRoundingMode(int rmode);

  float  FPAbs(float src);
  float  FPNeg(float src);
  float  FPSqrt(float src);
  float  FPAdd(float src1,float src2);
  float  FPNeg(float src1,float src2);
  float  FPDiv(float src1,float src2);
  float  FPMulAdd(float src1,float src2,float src3);
  float  FPMax(float src1,float src2);
  float  FPMaxNum(float src1,float src2);
  float  FPMin(float src1,float src2);
  float  FPMinNum(float src1,float src2);
  float  FPMul(float src1,float src2);
  float  FPRoundInt(float src1, int rounding, bool exact);
  unsigned int FPCompare(float operand1,float operand2,bool signal_all_nans);

  double FPAbs(double src);
  double FPNeg(double src);
  double FPSqrt(double src);
  double FPAdd(double src1,double src2);
  double FPNeg(double src1,double src2);
  double FPDiv(double src1,double src2);
  double FPMulAdd(double src1,double src2,double src3);
  double FPMax(double src1,double src2);
  double FPMaxNum(double src1,double src2);
  double FPMin(double src1,double src2);
  double FPMinNum(double src1,double src2);
  double FPMul(double src1,double src2);
  double FPRoundInt(double src1, int rounding, bool exact);
  unsigned int FPCompare(double operand1,double operand2,bool signal_all_nans);

  unsigned long long FPToFixed32(float fltval, int fbits, bool is_unsigned,int rounding, int intsize);
  unsigned long long FPToFixed64(double fltval, int fbits, bool is_unsigned,int rounding, int intsize);
  
  float FixedToFP32(unsigned long long intval, int fbits, bool is_unsigned,int rounding, int intsize);
  double FixedToFP64(unsigned long long intval, int fbits, bool is_unsigned,int rounding, int intsize);


 private:

  int FPUnpack32(int &type,unsigned int &sign,double &real_value,float fltval_in,int intsize);

  unsigned int ToUnsignedInt(double dbl_value, double &err, bool &overflow, bool &underflow);
  unsigned long long ToUnsignedLong(double dbl_value, double &err, bool &overflow, bool &underflow);
  int ToInt(double dbl_value, double &err, bool &overflow, bool &underflow);
  long long ToLong(double dbl_value, double &err, bool &overflow, bool &underflow);

  bool Is_NaN(double src);

  unsigned long long underflow(bool &saturate, double fv, unsigned long long uv, bool is_unsigned, int size);
  unsigned long long overflow(bool &saturate, double fv, unsigned long long uv, bool is_unsigned, int size);
  unsigned long long roundUp(bool &inexact, double fv, bool is_unsigned, int rounding);
};

#endif
#define __VFPMATH__ 1
