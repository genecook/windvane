#ifndef __A64REGISTERS__

#include <string>

class REGISTER_BASE {
 protected:
  bool is_set;
  bool is_reserved;
 public:
  REGISTER_BASE() : is_set(false), is_reserved(false) {};
  
  bool IsSet() { return is_set; };
  void Set() { is_set = true; };
  
  bool IsReserved() { return is_reserved; };
  void SetReserved(bool do_reserve = true) { is_reserved = do_reserve; };
};

// A64 cpu 'pstate'...

#define A32_MONITOR_MODE 0x16

class PSTATE_COMMON : public REGISTER_BASE {
 protected:
  unsigned int pstate;
 public:
  PSTATE_COMMON() : pstate(0) {};

  unsigned Value() { return pstate; };
  unsigned Value(unsigned long long rval) { pstate = (unsigned) rval; Set(); return pstate; };

  unsigned IT()  { return 0; }; //<---IT block not supported in this implementation

  unsigned N()   { return (pstate >> 31) & 1; };  // negative condition flag
  unsigned N(unsigned int _N) { pstate = (pstate & ~(1<<31)) | (_N << 31); Set(); return _N; };
  unsigned Z()   { return (pstate >> 30) & 1; };    // zero condition flag
  unsigned Z(unsigned int _Z) { pstate = (pstate & ~(1<<30)) | (_Z << 30); Set(); return _Z; };
  unsigned C()   { return (pstate >> 29) & 1; };    // carry condition flag
  unsigned C(unsigned int _C) { pstate = (pstate & ~(1<<29)) | (_C << 29); Set(); return _C; };
  unsigned V()   { return (pstate >> 28) & 1; };    // overflow condition flag 
  unsigned V(unsigned int _V) { pstate = (pstate & ~(1<<28)) | (_V << 28); Set(); return _V; };
  unsigned NZCV() { return (pstate >> 28) & 0xf; };
  unsigned NZCV(unsigned int _NZCV) { pstate = (pstate & ~(0xf<<28)) | (_NZCV << 28); Set(); return _NZCV; };
  unsigned Q()   { return (pstate >> 27) & 1; };    // cumulative saturation flag
  unsigned Q(unsigned int _Q) { pstate = (pstate & ~(1<<27)) | (_Q << 27); Set(); return _Q; };
  unsigned J()   { return (pstate >> 21) & 1; };    // always zero
  unsigned J(unsigned int _J) { pstate = (pstate & ~(1<<21)) | (_J << 21); Set(); return _J; };
  unsigned IL()  { return (pstate >> 17) & 1; };    // illegal state bit
  unsigned IL(unsigned int _IL) { pstate = (pstate & ~(1<<17)) | (_IL << 17); Set(); return _IL; };
  unsigned GE()  { return (pstate >> 16) & 0xf; };  // greater than or equal flags
  unsigned GE(unsigned int _GE) { pstate = (pstate & ~(0xf<<16)) | (_GE << 17); Set(); return _GE; };
  unsigned E()   { return (pstate >> 9)  & 1; };    // endian state
  unsigned E(unsigned int _E) { pstate = (pstate & ~(1<<9)) | (_E << 9); Set(); return _E; };
  unsigned A()   { return (pstate >> 8)  & 1; };    // asynchronous abort bit mask
  unsigned A(unsigned int _A) { pstate = (pstate & ~(1<<8)) | (_A << 8); Set(); return _A; };
  unsigned I()   { return (pstate >> 7)  & 1; };    // IRQ mask bit
  unsigned I(unsigned int _I) { pstate = (pstate & ~(1<<7)) | (_I << 7); Set(); return _I; };
  unsigned F()   { return (pstate >> 6)  & 1; };    // FIQ mask bit
  unsigned F(unsigned int _F) { pstate = (pstate & ~(1<<6)) | (_F << 6); Set(); return _F; };
  unsigned T()   { return (pstate >> 5)  & 1; };    // always zero
  unsigned T(unsigned int _T) { pstate = (pstate & ~(1<<5)) | (_T << 5); Set(); return _T; };
};


class PSTATE : public PSTATE_COMMON {
 public:
  unsigned ValueAsSPSR() { return pstate & 0xffffe7ff; }; //<---strip D,SS

  // any gaps are either Res0 or IT (not supported in this implementation)...

  unsigned D()   { return (pstate >> 11) & 1; };    // debug mask bit
  unsigned D(unsigned int _D) { pstate = (pstate & ~(1<<11)) | (_D << 11); Set(); return _D; };
  unsigned SS()  { return (pstate >> 10) & 1; };    // single step bit
  unsigned SS(unsigned int _SS) { pstate = (pstate & ~(1<<10)) | (_SS << 10); Set(); return _SS; };
  unsigned nRW() { return (pstate >> 4)  & 1; };    // register width (0==64,1==32)
  unsigned nRW(unsigned int _nRW) { pstate = (pstate & ~(1<<4)) | (_nRW << 4); Set(); return _nRW; };
  
  unsigned EL()  { return (pstate >> 2)  & 3; };    // exception level
  
  unsigned DAIF() { return ( ((pstate & 0x800)>>2) | (pstate & 0x1c0) ); }; // DAIF - bits 
  unsigned DAIF(unsigned int _DAIF) { D((_DAIF>>9)&1); A((_DAIF>>8)&1); I((_DAIF>>7)&1); F((_DAIF>>6)&1); return _DAIF; };
  unsigned CurrentEL() { return (pstate & 0xc); };  // current EL, as returned by MRS Xn,CurrentEL

  unsigned EL(unsigned int _EL) { pstate = (pstate & ~(3<<2)) | (_EL << 2); Set(); return _EL; };
  
  unsigned SP()  { return pstate & 1; };            // stack pointer select (0==SP0, 1==SPx)
  unsigned SP(unsigned int _SP) { pstate = (pstate & ~1) | _SP; Set(); return _SP; };

  bool ThumbMode() { return nRW()==1 && T()==1; };
  bool A64Mode()   { return nRW()==0; };

  unsigned int M() { return pstate & 0x1f; }; // when PSTATE intepreted as A32 CPSR...

  bool Privileged() { return EL() > EL0; };
};

class SPSR : public PSTATE_COMMON {
 public:

  unsigned M() { return pstate & 0x1f; };
  unsigned M(unsigned int _M) { pstate = (pstate & ~0x1f) | _M; Set(); return _M; };
};

class SCTLR_BASE : public REGISTER_BASE {
 protected:
  unsigned int sctlr;
 public:
  SCTLR_BASE() : sctlr(0) {};

  unsigned Value() { return sctlr; };
  unsigned Value(unsigned long long rval) { sctlr = (unsigned) rval; Set(); return sctlr; };

  unsigned EE()  { return (sctlr >> 25)  & 1; };
  unsigned EE(unsigned int _EE) { sctlr = (sctlr & ~(1<<25)) | (_EE << 25); Set(); return _EE; };

  unsigned WXN()  { return (sctlr >> 19)  & 1; };
  unsigned WXN(unsigned int _WXN) { sctlr = (sctlr & ~(1<<19)) | (_WXN << 19); Set(); return _WXN; };

  unsigned I()  { return (sctlr >> 12)  & 1; };
  unsigned I(unsigned int _I) { sctlr = (sctlr & ~(1<<12)) | (_I << 12); Set(); return _I; };

  unsigned SA()  { return (sctlr >> 3)  & 1; };
  unsigned SA(unsigned int _SA) { sctlr = (sctlr & ~(1<<3)) | (_SA << 3); Set(); return _SA; };
 
  unsigned C()  { return (sctlr >> 2)  & 1; };
  unsigned C(unsigned int _C) { sctlr = (sctlr & ~(1<<2)) | (_C << 2); Set(); return _C; };

  unsigned A()  { return (sctlr >> 1)  & 1; };
  unsigned A(unsigned int _A) { sctlr = (sctlr & ~(1<<1)) | (_A << 1); Set(); return _A; };

  unsigned M()  { return sctlr & 1; };
  unsigned M(unsigned int _M) { sctlr = (sctlr & ~1) | _M; Set(); return _M; };
};

class _SCTLR_EL1 : public SCTLR_BASE {
 public: 
  unsigned UCI()  { return (sctlr >> 26)  & 1; };
  unsigned UCI(unsigned int _UCI) { sctlr = (sctlr & ~(1<<26)) | (_UCI << 26); Set(); return _UCI; };

  unsigned E0E()  { return (sctlr >> 24)  & 1; };
  unsigned E0E(unsigned int _E0E) { sctlr = (sctlr & ~(1<<24)) | (_E0E << 24); Set(); return _E0E; };

  unsigned WXN()  { return (sctlr >> 19)  & 1; };
  unsigned WXN(unsigned int _WXN) { sctlr = (sctlr & ~(1<<19)) | (_WXN << 19); Set(); return _WXN; };

  unsigned nTWE()  { return (sctlr >> 18)  & 1; };
  unsigned nTWE(unsigned int _nTWE) { sctlr = (sctlr & ~(1<<18)) | (_nTWE << 18); Set(); return _nTWE; };

  unsigned nTWI()  { return (sctlr >> 16)  & 1; };
  unsigned nTWI(unsigned int _nTWI) { sctlr = (sctlr & ~(1<<16)) | (_nTWI << 16); Set(); return _nTWI; };

  unsigned UCT()  { return (sctlr >> 15)  & 1; };
  unsigned UCT(unsigned int _UCT) { sctlr = (sctlr & ~(1<<15)) | (_UCT << 15); Set(); return _UCT; };

  unsigned DZE()  { return (sctlr >> 14)  & 1; };
  unsigned DZE(unsigned int _DZE) { sctlr = (sctlr & ~(1<<14)) | (_DZE << 14); Set(); return _DZE; };

  unsigned UMA()  { return (sctlr >> 9)  & 1; };
  unsigned UMA(unsigned int _UMA) { sctlr = (sctlr & ~(1<<9)) | (_UMA << 9); Set(); return _UMA; };

  unsigned SED()  { return (sctlr >> 8)  & 1; };
  unsigned SED(unsigned int _SED) { sctlr = (sctlr & ~(1<<8)) | (_SED << 8); Set(); return _SED; };

  unsigned ITD()  { return (sctlr >> 7)  & 1; };
  unsigned ITD(unsigned int _ITD) { sctlr = (sctlr & ~(1<<7)) | (_ITD << 7); Set(); return _ITD; };

  unsigned CP15BEN()  { return (sctlr >> 5)  & 1; };
  unsigned CP15BEN(unsigned int _CP15BEN) { sctlr = (sctlr & ~(1<<5)) | (_CP15BEN << 5); Set(); return _CP15BEN; };

  unsigned SA0()  { return (sctlr >> 4)  & 1; };
  unsigned SA0(unsigned int _SA0) { sctlr = (sctlr & ~(1<<4)) | (_SA0 << 4); Set(); return _SA0; };
};

class _SCTLR_EL2 : public SCTLR_BASE {
 public: 
  _SCTLR_EL2() {};
};

class _SCTLR_EL3 : public SCTLR_BASE {
 public: 
  _SCTLR_EL3() {};
};
 
class AA64DFR0 : public REGISTER_BASE {
 private:
  unsigned long long dval;
 public:
  AA64DFR0() : dval(0) {};

  unsigned long long Value() { return dval; };
  unsigned Value(unsigned long long rval) { dval = (unsigned) rval; Set(); return dval; };

  // CTX_CMPs - # of context aware breakpoints, minus 1
  unsigned CTX_CMPs() { return (dval >> 28) & 0xf; };
  unsigned CTX_CMPs(unsigned int nval) { dval = (dval & ~(0xf<<28)) | (nval << 28); Set(); return dval; };
  // WRPs - # of watchpoints, minus 1
  unsigned WRPs() { return (dval >> 20) & 0xf; };
  unsigned WRPs(unsigned int nval) { dval = (dval & ~(0xf<<20)) | (nval << 20); Set(); return dval; };
  // BRPs - # of breakpoints, minus 1
  unsigned BRPs() { return (dval >> 12) & 0xf; };
  unsigned BRPs(unsigned int nval) { dval = (dval & ~(0xf<<12)) | (nval << 12); Set(); return dval; };
  unsigned PMUVer() { return 0; }; // no performance monitors
  unsigned TraceVer() { return 0; }; // no trace
  //DebugVer - debug version 
  unsigned DebugVer() { return dval & 0xf; };
  unsigned DebugVer(unsigned int nval) { dval = (dval & 0xfffffff0) | nval; Set(); return dval; };
};

class AA64MMFR0 : public REGISTER_BASE {
 private:
  unsigned long long dval;
 public:
  AA64MMFR0() : dval(0) {};

  unsigned long long Value() { return dval; };
  unsigned Value(unsigned long long rval) { dval = (unsigned) rval; Set(); return dval; };

  int physical_memory_size_in_bits() {
    int size;
    switch((int) PARange()) {
      case 0: size = 32; break;
      case 1: size = 36; break;
      case 2: size = 40; break;
      case 3: size = 42; break;
      case 4: size = 44; break;
      case 5: size = 48; break;
      default: throw INTERNAL_ERROR; break;
    }
    return size;
  };

  unsigned TGran4() { return (dval >> 28) & 0xf; };
  unsigned TGran4(unsigned int nval) { dval = (dval & ~(0xf<<28)) | (nval << 28); Set(); return dval; };
  unsigned TGran64() { return (dval >> 24) & 0xf; };
  unsigned TGran64(unsigned int nval) { dval = (dval & ~(0xf<<24)) | (nval << 24); Set(); return dval; };
  unsigned TGran16() { return (dval >> 20) & 0xf; };
  unsigned TGran16(unsigned int nval) { dval = (dval & ~(0xf<<20)) | (nval << 20); Set(); return dval; };
  unsigned BigEndEL0() { return (dval >> 16) & 0xf; };
  unsigned BigEndEL0(unsigned int nval) { dval = (dval & ~(0xf<<16)) | (nval << 16); Set(); return dval; };
  unsigned SNSMem() { return (dval >> 12) & 0xf; };
  unsigned SNSMem(unsigned int nval) { dval = (dval & ~(0xf<<12)) | (nval << 12); Set(); return dval; };
  unsigned BigEnd() { return (dval >> 8) & 0xf; };
  unsigned BigEnd(unsigned int nval) { dval = (dval & ~(0xf<<8)) | (nval << 8); Set(); return dval; };
  unsigned ASIDBits() { return (dval >> 4) & 0xf; };
  unsigned ASIDBits(unsigned int nval) { dval = (dval & ~(0xf<<4)) | (nval << 4); Set(); return dval; };
  unsigned PARange() { return dval & 0xf; };
  unsigned PARange(unsigned int nval) { dval = (dval & 0xfffffff0) | nval; Set(); return dval; };
};

class AA64PFR0 : public REGISTER_BASE {
 private:
  unsigned long long dval;
 public:
  AA64PFR0() : dval(0) {};

  unsigned long long Value() { return dval; };
  unsigned Value(unsigned long long rval) { dval = (unsigned) rval; Set(); return dval; };

  unsigned GIC() { return (dval >> 24) & 0xf; };
  unsigned GIC(unsigned int nval) { dval = (dval & ~(0xf<<24)) | (nval << 24); Set(); return dval; };
  unsigned AdvSIMD() { return (dval >> 20) & 0xf; };
  unsigned AdvSIMD(unsigned int nval) { dval = (dval & ~(0xf<<20)) | (nval << 20); Set(); return dval; };
  unsigned FP() { return (dval >> 16) & 0xf; };
  unsigned FP(unsigned int nval) { dval = (dval & ~(0xf<<16)) | (nval << 16); Set(); return dval; };
  unsigned EL3() { return (dval >> 12) & 0xf; };
  unsigned EL3(unsigned int nval) { dval = (dval & ~(0xf<<12)) | (nval << 12); Set(); return dval; };
  unsigned EL2() { return (dval >> 8) & 0xf; };
  unsigned EL2(unsigned int nval) { dval = (dval & ~(0xf<<8)) | (nval << 8); Set(); return dval; };
  unsigned EL1() { return (dval >> 4) & 0xf; };
  unsigned EL1(unsigned int nval) { dval = (dval & ~(0xf<<4)) | (nval << 4); Set(); return dval; };
  unsigned EL0() { return dval & 0xf; };
  unsigned EL0(unsigned int nval) { dval = (dval & 0xfffffff0) | nval; Set(); return dval; };
};

class AA64ISAR0 : public REGISTER_BASE {
 private:
  unsigned long long dval;
 public:
  AA64ISAR0() : dval(0) {};

  unsigned long long Value() { return dval; };
  unsigned Value(unsigned long long rval) { dval = (unsigned) rval; Set(); return dval; };

  unsigned CRC32() { return (dval >> 16) & 0xf; };
  unsigned CRC32(unsigned int nval) { dval = (dval & ~(0xf<<16)) | (nval << 16); Set(); return dval; };
  unsigned SHA2() { return (dval >> 12) & 0xf; };
  unsigned SHA2(unsigned int nval) { dval = (dval & ~(0xf<<12)) | (nval << 12); Set(); return dval; };
  unsigned SHA1() { return (dval >> 8) & 0xf; };
  unsigned SHA1(unsigned int nval) { dval = (dval & ~(0xf<<8)) | (nval << 8); Set(); return dval; };
  unsigned AES() { return (dval >> 4) & 0xf; };
  unsigned AES(unsigned int nval) { dval = (dval & ~(0xf<<4)) | (nval << 4); Set(); return dval; };
};

class CPACR : public REGISTER_BASE {
 private:
  unsigned int dval;
 public:
  CPACR() : dval(0) {};

  unsigned int Value() { return dval; };
  unsigned Value(unsigned long long _dval) { dval = _dval; Set(); return dval; };

  unsigned TTA() { return (dval >> 28) & 0x1; };
  unsigned TTA(unsigned int nval) { dval = (dval & ~(0x1<<28)) | (nval << 28); Set(); return dval; };
  
  unsigned FPEN() { return (dval >> 20) & 0x3; };
  unsigned FPEN(unsigned int nval) { dval = (dval & ~(0x3<<20)) | (nval << 20); Set(); return dval; };
};

class _ACTLR_EL3 : public REGISTER_BASE {
 private:
  unsigned int dval;
 public:
  _ACTLR_EL3() : dval(0) {};

  unsigned int Value() { return dval; };
  // NOTE: only one bit is implemented thusfar, so ignore writes to other bits...
  unsigned Value(unsigned long long _dval) { dval = _dval & 1; Set(); return dval; };

  unsigned DC() { return (dval & 0x1); };
  unsigned DC(unsigned int nval) { dval = (dval & 0xfffffffe) | (nval & 1); Set(); return dval; };
};
  
class CPTR : public REGISTER_BASE {
 private:
  unsigned int dval;
 public:
  CPTR() : dval(0) {};

  unsigned int Value() { return dval; };
  unsigned Value(unsigned long long _dval) { dval = (unsigned int) _dval; Set(); return dval; };

  unsigned TCPAC() { return (dval >> 31) & 0x1; };
  unsigned TCPAC(unsigned int nval) { dval = (dval & ~(0x1<<31)) | (nval << 31); Set(); return dval; };
  
  unsigned TTA() { return (dval >> 20) & 0x1; };
  unsigned TTA(unsigned int nval) { dval = (dval & ~(0x1<<20)) | (nval << 20); Set(); return dval; };

  unsigned TFP() { return (dval >> 10) & 0x1; };
  unsigned TFP(unsigned int nval) { dval = (dval & ~(0x1<<10)) | (nval << 10); Set(); return dval; };
};

class _FPCR : public REGISTER_BASE {
 private:
  unsigned int dval;
 public:
  _FPCR() : dval(0) {};

  unsigned int Value() { return dval; };
  unsigned Value(unsigned int _dval) { 
     dval = _dval & 0xffff0000;  // all fp trap enables are RES0 
     Set();
     return dval; 
  };

  unsigned AHP() { return (dval >> 26) & 0x1; };
  unsigned AHP(unsigned int nval) { dval = (dval & ~(0x1<<26)) | (nval << 26); Set(); return dval; };

  unsigned DN() { return (dval >> 25) & 0x1; };
  unsigned DN(unsigned int nval) { dval = (dval & ~(0x1<<25)) | (nval << 25); Set(); return dval; };

  unsigned FZ() { return (dval >> 24) & 0x1; };
  unsigned FZ(unsigned int nval) { dval = (dval & ~(0x1<<24)) | (nval << 24); Set(); return dval; };

  unsigned RMode() { return (dval >> 22) & 0x3; };
  unsigned RMode(unsigned int nval) { dval = (dval & ~(0x3<<22)) | (nval << 22); Set(); return dval; };

  unsigned IDE() { return 0; };  //
  unsigned IXE() { return 0; };  //
  unsigned UFE() { return 0; };  // this implementation does NOT support these floating pt traps...
  unsigned OFE() { return 0; };  //
  unsigned DZE() { return 0; };  //
  unsigned IOE() { return 0; };  //
};

class _FPSR : public REGISTER_BASE {
 private:
  unsigned int dval;
 public:
  _FPSR() : dval(0) {};

  unsigned int Value() { return dval; };
  unsigned Value(unsigned int _dval) { dval = _dval; Set(); return dval; };

  unsigned QC() { return (dval >> 27) & 0x1; };
  unsigned QC(unsigned int nval) { dval = (dval & ~(0x1<<27)) | (nval << 27); Set(); return dval; };

  unsigned IDC() { return (dval >> 7) & 0x1; };
  unsigned IDC(unsigned int nval) { dval = (dval & ~(0x1<<7)) | (nval << 7); Set(); return dval; };

  unsigned IXC() { return (dval >> 4) & 0x1; };
  unsigned IXC(unsigned int nval) { dval = (dval & ~(0x1<<4)) | (nval << 4); Set(); return dval; };

  unsigned UFC() { return (dval >> 3) & 0x1; };
  unsigned UFC(unsigned int nval) { dval = (dval & ~(0x1<<3)) | (nval << 3); Set(); return dval; };

  unsigned OFC() { return (dval >> 2) & 0x1; };
  unsigned OFC(unsigned int nval) { dval = (dval & ~(0x1<<2)) | (nval << 2); Set(); return dval; };

  unsigned DZC() { return (dval >> 1) & 0x1; };
  unsigned DZC(unsigned int nval) { dval = (dval & ~(0x1<<1)) | (nval << 1); Set(); return dval; };

  unsigned IOC() { return dval & 0x1; };
  unsigned IOC(unsigned int nval) { dval = (dval & ~0x1) | nval; Set(); return dval; };
};

class MIDR : public REGISTER_BASE {
 private:
  unsigned int dval;
 public:
  MIDR() : dval(0) {};

  unsigned int Value() { return dval; };
  unsigned int Value(unsigned long long _dval) { dval = (unsigned) _dval; Set(); return dval; };

  unsigned Implementer() { return (dval >> 24) & 0xff; };
  unsigned Implementer(unsigned int nval) { dval = (dval & ~(0xff<<24)) | (nval << 24); Set(); return dval; };
  
  unsigned Variant() { return (dval >> 20) & 0xf; };
  unsigned Variant(unsigned int nval) { dval = (dval & ~(0xf<<20)) | (nval << 20); Set(); return dval; };

  unsigned Architecture() { return (dval >> 16) & 0xf; };
  unsigned Architecture(unsigned int nval) { dval = (dval & ~(0xf<<16)) | (nval << 16); Set(); return dval; };

  unsigned PartNum() { return (dval >> 4) & 0xfff; };
  unsigned PartNum(unsigned int nval) { dval = (dval & ~(0xfff<<4)) | (nval << 4); Set(); return dval; };

  unsigned Revision() { return dval & 0xf; };
  unsigned Revision(unsigned int nval) { dval = (dval & ~0xf) | nval; Set(); return dval; };
};
 
class MPIDR : public REGISTER_BASE {
 private:
  unsigned long long dval;
 public:
  MPIDR() : dval(0x80000000ull) {};  // bit 31 is RES1

  unsigned long long Value() { return dval; };
  unsigned long long Value(unsigned long long _dval) { dval = _dval; Set(); return dval; };

  unsigned Aff3() { return (dval >> 32) & 0xff; };
  unsigned Aff3(unsigned int nval) { dval = (dval & ~(0xffull<<32)) | ((unsigned long long) nval << 32); Set(); return dval; };
  
  unsigned U() { return (dval >> 30) & 0x1; };
  unsigned U(unsigned int nval) { dval = (dval & ~(0x1<<30)) | (nval << 30); Set(); return dval; };

  unsigned MT() { return (dval >> 24) & 0x1; };
  unsigned MT(unsigned int nval) { dval = (dval & ~(1<<24)) | (nval << 24); Set(); return dval; };

  unsigned Aff2() { return (dval >> 16) & 0xff; };
  unsigned Aff2(unsigned int nval) { dval = (dval & ~(0xff<<16)) | (nval << 16); Set(); return dval; };

  unsigned Aff1() { return (dval >> 8) & 0xff; };
  unsigned Aff1(unsigned int nval) { dval = (dval & ~(0xff<<8)) | (nval << 8); Set(); return dval; };

  unsigned Aff0() { return dval & 0xff; };
  unsigned Aff0(unsigned int nval) { dval = (dval & ~0xff) | nval; Set(); return dval; };
};

class MDCR : public REGISTER_BASE {
 private:
  unsigned int dval;
 public:
  MDCR() {};

  unsigned int Value() { return dval; };
  unsigned Value(unsigned long long _dval) { dval = _dval; Set(); return dval; };
};

class MDSCR : public REGISTER_BASE {
 private:
  unsigned int dval;
 public:
  MDSCR() {};

  unsigned int Value() { return dval; };
  unsigned Value(unsigned long long _dval) { dval = _dval; Set(); return dval; };

  unsigned KDE() { return Value() & (1<<13); };
  unsigned SS() { return Value() & 0x1; };
};


class OSDLR : public REGISTER_BASE {
 private:
  unsigned int dval;
 public:
  OSDLR() {};

  unsigned int Value() { return dval; };
  unsigned Value(unsigned long long _dval) { dval = _dval; Set(); return dval; };
};

class OSLAR : public REGISTER_BASE {
 private:
  unsigned int dval;
 public:
  OSLAR() {};

  unsigned int Value() { return dval; };
  unsigned Value(unsigned long long _dval) { dval = _dval; Set(); return dval; };
};

class OSLSR : public REGISTER_BASE {
 private:
  unsigned int dval;
 public:
  OSLSR() {};

  unsigned int Value() { return dval; };
  unsigned Value(unsigned long long _dval) { dval = _dval; Set(); return dval; };
};


class CTR : public REGISTER_BASE {
 private:
  unsigned int dval;
 public:
  CTR() : dval(0) {};

  unsigned int Value() { return dval; };
  unsigned int Value(unsigned long long _dval) { dval = (unsigned) _dval; Set(); return dval; };

  unsigned CWG() { return (dval >> 24) & 0xf; };
  unsigned CWG(unsigned int nval) { dval = (dval & ~(0xf<<24)) | (nval << 24); Set(); return dval; };

  unsigned ERG() { return (dval >> 20) & 0xf; };
  unsigned ERG(unsigned int nval) { dval = (dval & ~(0xf<<20)) | (nval << 20); Set(); return dval; };

  unsigned DminLine() { return (dval >> 16) & 0xf; };
  unsigned DminLine(unsigned int nval) { dval = (dval & ~(0xf<<16)) | (nval << 16); Set(); return dval; };

  unsigned L1Ip() { return (dval >> 14) & 0x3; };
  unsigned L1Ip(unsigned int nval) { dval = (dval & ~(0x3<<14)) | (nval << 14); Set(); return dval; };

  unsigned IminLine() { return dval & 0xf; };
  unsigned IminLine(unsigned int nval) { dval = (dval & ~0xf) | nval; Set(); return dval; };
};

class DCZID : public REGISTER_BASE {
 private:
  unsigned int dval;
 public:
  DCZID() : dval(0) {};

  unsigned int Value() { return dval; };
  unsigned int Value(unsigned long long _dval) { dval = (unsigned) _dval; Set(); return dval; };

  unsigned DZP() { return (dval >> 4) & 0x1; };
  unsigned DZP(unsigned int nval) { dval = (dval & ~(0x1<<4)) | (nval << 4); Set(); return dval; };

  unsigned BS() { return dval & 0xf; };
  unsigned BS(unsigned int nval) { dval = (dval & ~0xf) | nval; Set(); return dval; };
};

class SCR : public REGISTER_BASE {
 private:
  unsigned int dval;
 public:
  SCR() {};
  
  unsigned int Value() { return dval; };
  unsigned int Value(unsigned int _val) { dval = _val; Set(); return dval; };

  unsigned TWE() { return (dval >> 13) & 0x1; };
  unsigned TWE(unsigned int nval) { dval = (dval & ~(0x1<<13)) | (nval << 13); Set(); return dval; };

  unsigned TWI() { return (dval >> 12) & 0x1; };
  unsigned TWI(unsigned int nval) { dval = (dval & ~(0x1<<12)) | (nval << 12); Set(); return dval; };

  unsigned ST() { return (dval >> 11) & 0x1; };
  unsigned ST(unsigned int nval) { dval = (dval & ~(0x1<<11)) | (nval << 11); Set(); return dval; };

  unsigned RW() { return (dval >> 10) & 0x1; };
  unsigned RW(unsigned int nval) { dval = (dval & ~(0x1<<10)) | (nval << 10); Set(); return dval; };

  unsigned SIF() { return (dval >> 9) & 0x1; };
  unsigned SIF(unsigned int nval) { dval = (dval & ~(0x1<<9)) | (nval << 9); Set(); return dval; };

  unsigned HCE() { return (dval >> 8) & 0x1; };
  unsigned HCE(unsigned int nval) { dval = (dval & ~(0x1<<8)) | (nval << 8); Set(); return dval; };

  unsigned SMD() { return (dval >> 7) & 0x1; };
  unsigned SMD(unsigned int nval) { dval = (dval & ~(0x1<<7)) | (nval << 7); Set(); return dval; };

  unsigned EA() { return (dval >> 3) & 0x1; };
  unsigned EA(unsigned int nval) { dval = (dval & ~(0x1<<3)) | (nval << 3); Set(); return dval; };

  unsigned FIQ() { return (dval >> 2) & 0x1; };
  unsigned FIQ(unsigned int nval) { dval = (dval & ~(0x1<<2)) | (nval << 2); Set(); return dval; };

  unsigned IRQ() { return (dval >> 1) & 0x1; };
  unsigned IRQ(unsigned int nval) { dval = (dval & ~(0x1<<1)) | (nval << 1); Set(); return dval; };

  unsigned NS() { return dval & 0x1; };
  unsigned NS(unsigned int nval) { dval = (dval & ~0x1) | nval; Set(); return dval; };
};

class HCR : public REGISTER_BASE {
 private:
  unsigned long long dval;
 public:
  HCR() : dval(0) {};

  unsigned long long Value() { return dval; };
  unsigned long long Value(unsigned long long  _val) { dval = _val; Set(); return dval; };

  unsigned TGE() { return (dval >> 27) & 0x1; };
  unsigned DC() { return (dval >> 12) & 0x1; };
  unsigned VM() { return dval & 0x1; };
};

class TTBR : public REGISTER_BASE {
 private:
  unsigned long long dval;
 public:
  TTBR() : dval(0) {};

  unsigned long long Value() { return dval; };
  unsigned long long Value(unsigned long long  _val) { dval = _val; Set(); return dval; };

  unsigned ASID()  { return (dval >> 48) & 0xffff; };
  unsigned long long BADDR() { return dval & 0xffffffffffffull; };

  unsigned long long baseAddress() { return BADDR(); };
};

class _TCR_EL1 : public REGISTER_BASE {
 private:
  unsigned long long dval;
 public:
  _TCR_EL1() {};

  unsigned long long Value() { return dval; };
  unsigned long long Value(unsigned long long _val) { dval = _val; Set(); return dval; };

  int physical_memory_size_in_bits() {
    int size;
    switch((int) IPS()) {
      case 0: size = 32; break;
      case 1: size = 36; break;
      case 2: size = 40; break;
      case 3: size = 42; break;
      case 4: size = 44; break;
      case 5: size = 48; break;
      default: throw INTERNAL_ERROR; break;
    }
    return size;
  };

  unsigned TBI1()  { return (dval >> 38) & 0x1;  };
  unsigned TBI1(unsigned int nval) { dval = (dval & ~(0x38<<1)) | ((unsigned long long) nval << 38); Set(); return dval; };

  unsigned TBI0()  { return (dval >> 37) & 0x1;  };
  unsigned TBI0(unsigned int nval) { dval = (dval & ~(0x37<<1)) | ((unsigned long long) nval << 37); Set(); return dval; };

  unsigned AS()    { return (dval >> 36) & 0x1;  };
  unsigned AS(unsigned int nval) { dval = (dval & ~(0x36<<1)) | ((unsigned long long) nval << 36); Set(); return dval; };

  unsigned IPS()   { return (dval >> 32) & 0x7;  };
  unsigned IPS(unsigned int nval) { dval = (dval & ~(0x32<<1)) | ((unsigned long long) nval << 32); Set(); return dval; };

  unsigned TG1()   { return (dval >> 30) & 0x3;  };
  unsigned TG1(unsigned int nval) { dval = (dval & ~(0x30<<1)) | (nval << 30); Set(); return dval; };

  unsigned SH1()   { return (dval >> 28) & 0x3;  };
  unsigned SH1(unsigned int nval) { dval = (dval & ~(0x28<<1)) | (nval << 28); Set(); return dval; };

  unsigned ORGN1() { return (dval >> 26) & 0x3;  };
  unsigned ORGN1(unsigned int nval) { dval = (dval & ~(0x26<<1)) | (nval << 26); Set(); return dval; };

  unsigned IRGN1() { return (dval >> 24) & 0x3;  };
  unsigned IRGN1(unsigned int nval) { dval = (dval & ~(0x24<<1)) | (nval << 24); Set(); return dval; };

  unsigned EPD1()  { return (dval >> 23) & 0x1;  };
  unsigned EPD1(unsigned int nval) { dval = (dval & ~(0x23<<1)) | (nval << 23); Set(); return dval; };

  unsigned A1()    { return (dval >> 22) & 0x1;  };
  unsigned A1(unsigned int nval) { dval = (dval & ~(0x22<<1)) | (nval << 22); Set(); return dval; };

  unsigned T1SZ()  { return (dval >> 16) & 0x3f; };
  unsigned T1SZ(unsigned int nval) { dval = (dval & ~(0x16<<1)) | (nval << 16); Set(); return dval; };

  unsigned TG0()   { return (dval >> 14) & 0x3;  };
  unsigned TG0(unsigned int nval) { dval = (dval & ~(0x14<<1)) | (nval << 14); Set(); return dval; };

  unsigned SH0()   { return (dval >> 12) & 0x3;  };
  unsigned SH0(unsigned int nval) { dval = (dval & ~(0x12<<1)) | (nval << 12); Set(); return dval; };

  unsigned ORGN0() { return (dval >> 10) & 0x3;  };
  unsigned ORGN0(unsigned int nval) { dval = (dval & ~(0x10<<1)) | (nval << 10); Set(); return dval; };

  unsigned IRGN0() { return (dval >> 8)  & 0x3;  };
  unsigned IRGN0(unsigned int nval) { dval = (dval & ~(0x8<<1)) | (nval << 8); Set(); return dval; };

  unsigned EPD0()  { return (dval >> 7) & 0x1;   };
  unsigned EPD0(unsigned int nval) { dval = (dval & ~(0x7<<1)) | (nval << 7); Set(); return dval; };

  unsigned T0SZ()  { return dval & 0x3f;         };
  unsigned T0SZ(unsigned int nval) { dval = (dval & ~(0x3f)) | (nval & 0x3f); Set(); return dval; };
};

class _TCR_EL2_3 : public REGISTER_BASE {
 private:
  unsigned long long dval;
 public:
  _TCR_EL2_3() {};

  unsigned long long Value() { return dval; };
  unsigned long long Value(unsigned long long _val) { dval = _val; Set(); return dval; };

  int physical_memory_size_in_bits() {
    int size;
    switch((int) PS()) {
      case 0: size = 32; break;
      case 1: size = 36; break;
      case 2: size = 40; break;
      case 3: size = 42; break;
      case 4: size = 44; break;
      case 5: size = 48; break;
      default: throw INTERNAL_ERROR; break;
    }
    return size;
  };

  unsigned TBI()   { return (dval >> 20) & 0x1;  };
  unsigned PS()    { return (dval >> 16) & 0x3f; };
  unsigned TG0()   { return (dval >> 14) & 0x3;  };
  unsigned SH0()   { return (dval >> 12) & 0x3;  };
  unsigned ORGN0() { return (dval >> 10) & 0x3;  };
  unsigned IRGN0() { return (dval >> 8)  & 0x3;  };
  unsigned T0SZ()  { return dval & 0x3f;         };
};

class ESR : public REGISTER_BASE {
 private:
  unsigned int dval;
 public:
  ESR() {};

  unsigned int Value() { return dval; };
  unsigned int Value(unsigned long long _dval) { dval = (unsigned) _dval; Set(); return dval; };

  unsigned int EC()  { return (dval>>26) & 0x3f; };
  unsigned int IL()  { return (dval>>25) & 1;    };
  unsigned int ISS() { return dval & 0x1ffffff;  };
};


enum MEMORY_TYPES       { DEVICE_MEMORY=0 ,NORMAL_MEMORY=1, UNKNOWN_MEMORY=99 };
enum DEVICE_TYPES       { DEVICETYPE_nGnRnE=0, DEVICETYPE_nGnRE=4, DEVICETYPE_nGRE=8, DEVICETYPE_GRE=12, DEVICETYPE_UNKNOWN=99 };
enum CACHE_TYPES        { MEMATTR_WT, MEMATTR_WB, MEMATTR_NONCACHEABLE, MEMATTR_UNKNOWN=99 };
enum MEMORY_HINTS       { MEMHINT_RWA, MEMHINT_RA };
enum ACCESS_PERMISSIONS { AP_UNKNOWN };

struct AttrXcacheHints {
  AttrXcacheHints() : 
    outer_cache_type(MEMATTR_NONCACHEABLE),outer_transient(false),outer_read_allocate(false),outer_write_allocate(false),
    inner_cache_type(MEMATTR_NONCACHEABLE),inner_transient(false),inner_read_allocate(false),inner_write_allocate(false) {};

  int  outer_cache_type;
  bool outer_transient;
  bool outer_read_allocate;
  bool outer_write_allocate;

  int  inner_cache_type;
  bool inner_transient;
  bool inner_read_allocate;
  bool inner_write_allocate;
};

class MAIR : public REGISTER_BASE {
 private:
  unsigned long long dval;
 public:
  MAIR() {};

  unsigned long long Value() { return dval; };
  unsigned long long Value(unsigned long long _val) { dval = _val; Set(); return dval; };

  unsigned int Attr7() { return (dval>>56) & 0xff; };
  unsigned int Attr6() { return (dval>>48) & 0xff; };
  unsigned int Attr5() { return (dval>>40) & 0xff; };
  unsigned int Attr4() { return (dval>>32) & 0xff; };
  unsigned int Attr3() { return (dval>>24) & 0xff; };
  unsigned int Attr2() { return (dval>>16) & 0xff; };
  unsigned int Attr1() { return (dval>>8)  & 0xff; };
  unsigned int Attr0() { return dval & 0xff;       };

  bool Attributes(int &mem_type,int &device_type,struct AttrXcacheHints &cache_hints, int attr_index);
};

// a cpu 'general purpose'...

class GPRegister : public REGISTER_BASE {
 public:
  GPRegister() {};
  
  unsigned long long Value() { return rval; };
  unsigned long long Value(unsigned long long nval) { rval = nval; Set(); return rval; };
  
 private:  
  unsigned long long rval;
};

// a cpu 'register' - floating pt or simd

class Register : public REGISTER_BASE {
 public:
  Register() {};
  
  Register(unsigned long long nval) : REGISTER_BASE(), rval(nval) {};
  Register(unsigned long long nval_hi,unsigned long long nval_lo) : REGISTER_BASE(), rval_hi(nval_hi),rval(nval_lo) {};

  unsigned long long Value() { return rval; };
  unsigned long long ValueHi() { return rval_hi; };
  
  unsigned long long Value(unsigned long long nval) { rval = nval; Set(); return rval; };
  unsigned long long ValueHi(unsigned long long nval_hi) { rval_hi = nval_hi; Set(); return rval_hi; };
  
 protected:
  unsigned long long rval_hi;  // extended value when asimd
  unsigned long long rval;     // value
};

// XRegister - uncategorized register reference (used during translations from 'foreign' sim trace format such as tarmac...

class XRegister : public Register {
 public:
  XRegister(std::string _rname, int _type, int _id, unsigned long long rval_lo,unsigned long long rval_hi) : Register(rval_hi,rval_lo), rname(_rname), type(_type), id(_id) {};
  
  string Name() { return rname; };
  enum { IS_GPR, IS_SPR, IS_FLOAT, IS_SP, IS_PSTATE };
  int Type() { return type; };
  int ID() { return id; };
  
 private:
  std::string rname;
  int type;
  int id;
};


enum float_type { FL_UNKNOWN, FL_BYTE, FL_HALFWORD, FL_SINGLE, FL_DOUBLE, FL_QUAD };

class FloatRegister : public Register {
 public:
 FloatRegister() : Register(), ftype(FL_UNKNOWN) {};

  int Type() { return ftype; };
  int SetType(float_type _ftype) { ftype = _ftype; return ftype; };
  
  union flpack {
        float fl_foo[2];
        double db_foo;      
        unsigned long long ull_foo;
  };
 
  float Single(float fval) { 
    flpack uval;
    uval.ull_foo = 0ull;
    uval.fl_foo[0] = fval; // value (when accessed) will be low order 32 bits of rval
    rval = uval.ull_foo;
    rval_hi = 0ull;
    ftype = FL_SINGLE; 

    return Single();
  };

  unsigned int Unsigned(unsigned int fval) { 
    rval = (unsigned long long) fval;
    rval_hi = 0ull;

    return rval;
  };

  unsigned int Half(unsigned long long hval) { 
    rval = hval;
    rval_hi = 0ull;

    return rval;
  };

  double Double(double fval) {
    flpack uval;
    uval.db_foo = fval;
    rval = uval.ull_foo;
    rval_hi = 0ull;
    ftype = FL_DOUBLE;

    return Double();
  };

  unsigned long long UnsignedLong(unsigned long long fval) {
    rval = fval;
    rval_hi = 0ull;

    return rval;
  };

  float Single() {
    flpack uval;
    uval.ull_foo = rval;
    return uval.fl_foo[0];
  }
  
  double Double() {
    flpack uval;
    uval.ull_foo = rval;
    return uval.db_foo;
  }
  
  double DoubleHi() {
    flpack uval;
    uval.ull_foo = rval_hi;
    return uval.db_foo;
  }

 private:
  float_type ftype;
};

class RVBAR : public REGISTER_BASE {
 private:
  unsigned long long dval;
 public:
  RVBAR() : dval(0) {};

  unsigned long long Value() { return dval; };
  unsigned long long Value(unsigned long long _dval) { dval = _dval; Set(); return dval; };

  unsigned long long ResetAddress() { return dval; };
  unsigned long long ResetAddress(unsigned long long nval) { dval = nval & ~0x7ull; Set(); return dval; };
};

class ProgramCounter : public REGISTER_BASE {
 public:
  ProgramCounter() {};

  unsigned long long Value() { validate(); return rval; };
  unsigned long long Value(unsigned long long nval) { rval = nval; Set(); return rval; };

  ProgramCounter& operator=( RVBAR &rhs ) { this->Value(rhs.Value()); Set(); return *this; }; 
  ProgramCounter& operator=(unsigned long long rhs ) { this->Value(rhs); Set(); return *this; };
  
 private:
  void validate() { if (!IsSet()) throw INTERNAL_ERROR; };
  unsigned long long rval; // value
};


class TIMER_CNTFRQ : public REGISTER_BASE {
 protected:
  unsigned int clock_freq;
 public:
  TIMER_CNTFRQ() : clock_freq(0) {};

  unsigned Value() { return clock_freq; };
  unsigned Value(unsigned long long rval) { clock_freq = (unsigned) rval; return clock_freq; };
};

class TIMER_CNTCTL : public REGISTER_BASE {
 protected:
  unsigned int dval;
 public:
  TIMER_CNTCTL() : dval(0) {};

  unsigned Value() { return dval; };
  unsigned Value(unsigned long long rval) { dval = (unsigned) rval; Set(); return dval; };

  unsigned EVNTI() { return (dval >> 4) & 0xf; };
  unsigned EVNTI(unsigned int _N) { dval = (dval & ~(0xf<<4)) | (_N << 4); Set(); return _N; };
  
  unsigned EVNTDIR() { return (dval >> 3) & 1; };
  unsigned EVNTDIR(unsigned int _N) { dval = (dval & ~(1<<3)) | (_N << 3); Set(); return _N; };
  
  unsigned EVNTEN() { return (dval >> 2) & 1; };
  unsigned EVNTEN(unsigned int _N) { dval = (dval & ~(1<<2)) | (_N << 2); Set(); return _N; };
};

class TIMER_CNTHCTL : public TIMER_CNTCTL {
 protected:
  unsigned int dval;
 public:
  TIMER_CNTHCTL() : dval(0) {};

  unsigned EL1PCEN() { return (dval >> 1) & 1; };
  unsigned EL1PCEN(unsigned int _N) { dval = (dval & ~(1<<1)) | (_N << 1); Set(); return _N; };
  
  unsigned EL1PCTEN() { return (dval & 1); };
  unsigned EL1PCTEN(unsigned int _N) { dval = (dval & ~1) | _N; Set(); return _N; };
};

class TIMER_CNTKCTL : public TIMER_CNTCTL {
 protected:
  unsigned int dval;
 public:
  TIMER_CNTKCTL() : dval(0) {};

  unsigned Value() { return dval; };
  unsigned Value(unsigned long long rval) { dval = (unsigned) rval; Set(); return dval; };

  unsigned EL0PTEN() { return (dval >> 9) & 1; };
  unsigned EL0PTEN(unsigned int _N) { dval = (dval & ~(1<<9)) | (_N << 9); Set(); return _N; };
  
  unsigned EL0VTEN() { return (dval >> 8) & 1; };
  unsigned EL0VTEN(unsigned int _N) { dval = (dval & ~(1<<8)) | (_N << 8); Set(); return _N; };
  
  unsigned EL0VCTEN() { return (dval >> 1) & 1; };
  unsigned EL0VCTEN(unsigned int _N) { dval = (dval & ~(1<<1)) | (_N << 1); Set(); return _N; };
  
  unsigned EL0PCTEN() { return (dval & 1); };
  unsigned EL0PCTEN(unsigned int _N) { dval = (dval & ~1) | _N; Set(); return _N; };
};

class TIMER_CTL : public REGISTER_BASE {
 protected:
  unsigned int dval;
 public:
  TIMER_CTL() : dval(0) {};

  unsigned Value() { return dval; };
  unsigned Value(unsigned long long rval) { dval = (unsigned) rval; Set(); return dval; };

  unsigned ISTATUS() { return (dval >> 2) & 1; };
  unsigned ISTATUS(unsigned int _N) { dval = (dval & ~(1<<2)) | (_N << 2); Set(); return _N; };

  unsigned IMASK() { return (dval >> 1) & 1; };
  unsigned IMASK(unsigned int _N) { dval = (dval & ~(1<<1)) | (_N << 1); Set(); return _N; };

  unsigned ENABLE() { return (dval & 1); };
  unsigned ENABLE(unsigned int _N) { dval = (dval & ~1) | _N; Set(); return _N; };
};

class TIMER_CVAL : public REGISTER_BASE {
 private:
  unsigned long long dval;
 public:
  TIMER_CVAL() : dval(0) {};

  unsigned long long Value() { return dval; };
  unsigned long long Value(unsigned long long _dval) { dval = _dval; Set(); return dval; };
};

class TIMER_TVAL : public REGISTER_BASE {
 protected:
  unsigned int dval;
 public:
  TIMER_TVAL() : dval(0) {};

  unsigned Value() { return dval; };
  unsigned Value(unsigned long long rval) { dval = (unsigned) rval; Set(); return dval; };
};

class TIMER_CNT : public REGISTER_BASE {
 private:
  unsigned long long dval;
  unsigned long long dval_prev;
 public:
 TIMER_CNT() : dval(0), dval_prev(0) {};

  unsigned long long Value() { return dval; };
  unsigned long long Value(unsigned long long _dval) { dval_prev = dval; dval = _dval; Set(); return dval; };
  unsigned long long PreviousValue() { return dval_prev; };  
};

class TIMER_CNTOFF : public REGISTER_BASE {
 private:
  unsigned long long dval;
 public:
  TIMER_CNTOFF() : dval(0) {};

  unsigned long long Value() { return dval; };
  unsigned long long Value(unsigned long long _dval) { dval = _dval; Set(); return dval; };
};


class GIC_SYSREG32 : public REGISTER_BASE {
 protected:
  unsigned int dval;
 public:
  GIC_SYSREG32() : dval(0) {};

  unsigned Value() { return dval; };
  unsigned Value(unsigned long long rval) { dval = (unsigned) rval; Set(); return dval; };
};
class GIC_SYSREG64 : public REGISTER_BASE {
 private:
  unsigned long long dval;
 public:
  GIC_SYSREG64() : dval(0) {};

  unsigned long long Value() { return dval; };
  unsigned long long Value(unsigned long long _dval) { dval = _dval; Set(); return dval; };
};

class ICC_PMR  : public GIC_SYSREG32 { };
class ICC_IAR0 : public GIC_SYSREG32 { };

class ICC_EORI0 : public GIC_SYSREG32 { };
class ICC_HPPIR0 : public GIC_SYSREG32 { };
class ICC_BPR0 : public GIC_SYSREG32 { };
class ICC_AP0R : public GIC_SYSREG32 { };
class ICC_APR  : public GIC_SYSREG32 { };
class ICC_DIR : public GIC_SYSREG32 { };
class ICC_RPR : public GIC_SYSREG32 { };
class ICC_SGI1R : public GIC_SYSREG64 { };
class ICC_ASGI1R : public GIC_SYSREG32 { };
class ICC_SGI0R : public GIC_SYSREG32 { };
class ICC_IAR1 : public GIC_SYSREG32 { };
class ICC_EOIR1 : public GIC_SYSREG32 { };
class ICC_HPPIR1 : public GIC_SYSREG32 { };
class ICC_BPR1 : public GIC_SYSREG32 { };
class ICC_CTLR : public GIC_SYSREG32 { };
class ICC_SRE : public GIC_SYSREG32 { };
class ICC_IGRPEN0 : public GIC_SYSREG32 { };
class ICC_IGRPEN1 : public GIC_SYSREG32 { };

#endif
#define __A64REGISTERS__ 1

