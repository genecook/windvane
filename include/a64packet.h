#ifndef __A64PACKET__

#include <fenv.h>

class InstructionField {
 public:
 InstructionField() : fval(0),is_set(false) {}; 
  unsigned int Value() { return fval; };
  unsigned int Value(unsigned int _fval) { fval = _fval; is_set = true; return fval; };
  bool IsDefined() { return is_set; };

  InstructionField& operator=( InstructionField &rhs ) { this->Value(rhs.Value()); return *this; }; 
  InstructionField& operator=(unsigned long long rhs ) { this->Value(rhs); return *this; }; 

  bool operator==( InstructionField &other) { return fval == other.fval; };
  bool operator!=( InstructionField &other) { return fval != other.fval; };
  bool operator==( int other) { return fval == (unsigned int) other; };

  friend unsigned int operator<<( InstructionField &, unsigned int );
  friend unsigned int operator<<( InstructionField &, int );
  friend unsigned int operator|( unsigned int lhs,InstructionField &instr_field );

  friend std::ostream& operator<< (std::ostream &os, InstructionField &fld);

  unsigned int fval;     // value
  bool is_set;           //   is set during instruction decode
};

// exception types...

enum { UNDEFINED_FAULT=1,RESERVED_VALUE=2 };

// packet filled out during course of simulating a single instruction...

enum { 
  // src ops from instruction encodings...
  DA,DM,DN,DT,DT2,HN,HT,BT,SA,SM,SN,ST,ST2,QT,QT2, VN,VM,VT2,VT3,VT4,VT,RA,RM,RN,RS,RT2,RNSP,RT1,RT,
  // dest ops from instruction encoding...
  DD,HD,SD,VD,XD,XT,XT2,XDSP,X30,XNSP,XS,SREG,
  // other ops...
  NZCV,PC_OP,SYS_REG_OP
};


// MemoryAccess - used with data read/write operations only, ie, NOT for instruction access...

enum { FOR_READ, FOR_WRITE, FOR_PREFETCH };

class MemoryAccess {
 public:
 MemoryAccess(unsigned long long _address, // logical address
              int  _size,                  // total number of bytes 
              int  _type,                  // memory type
              bool _exclusive,             // is exclusive access
              int  _direction,             // read vs write
              bool _big_endian,            // true if big endian
	      int  _word_size,             // element size in bytes
              bool _sign_extend,           // sign-extend after loading
              int  _rwidth,                // when sign-extending, # of bits to extend to - 32 or 64
              bool _paired,                // true if register pair access
              bool _privileged             // privileged
             )            
   : address(_address), size(_size), type(_type), exclusive(_exclusive), direction(_direction), big_endian(_big_endian),
    word_size(_word_size), sign_extend(_sign_extend), rwidth(_rwidth), paired(_paired), privileged(_privileged),
    exclusive_passed(false) {};

  friend std::ostream& operator<< (std::ostream &os, MemoryAccess &ma);

  // SignBit - when sign-extending, which bit is the (input) sign bit 
  int SignBit() { 
    if (word_size==1) return 8;
    if (word_size==2) return 16;
    if (word_size==4) return 32;
    return 64;
  }
  // SignExtendTo - when sign-extending, how far to extend the sign to (either to bit 32 or bit 64)
  int SignExtendTo() {
    return rwidth;
  }

  void ClearBuffer() { for (int i = 0; i < size; i++) { membuffer[i] = 0; } };

  unsigned long long Address() { return address; };
  int Size() { return size; };
  int WordSize() { return word_size; };

  bool Aligned() { return (word_size==1) || ( ((word_size - 1) & address) == 0 ); };
  
  unsigned long long address;     // memory address
  int  size;                      // size of access in bytes
  int  type;                      // see ACCESS_TYPE
  bool exclusive;                 // set if access to exclusive monitor/memory
  int  direction;                 // read (0) vs write (1)
  bool big_endian;                // true if big endianness
      // NOTE: for exclusive register-pair access and little endian need to swap data (word) values
  int  word_size;                 // word size to use for endianness
  bool sign_extend;               // whether or not to sign extend value read from memory
  int rwidth;                     // when sign-extending, # of bits to extend to - 32 or 64
  bool paired;                    // true if paired register access
  bool privileged;                // privileged vs unprivileged
  int  exclusive_passed;          // true if exclusive write succeeds
  unsigned char membuffer[1024];  // source or dest of access - matches memory (and byte order) at address
};

enum { PACKET_DREG1, PACKET_DREG2 };

enum SIM_GOAL { FOR_SIMULATION, FOR_TEST };


// RegDep - use to record register dependency. used in downstream tools for dependency analysis...

enum REG_DEP { DEP_GP=0x10000000, DEP_SP=0x20000000, DEP_SPR=0x30000000, DEP_PSTATE=0x40000000,
	       DEP_FP_SP=0x50000000, DEP_FP_DP=0x60000000, DEP_ASIMD=0x70000000,
	       DEP_TYPE=0xf0000000, DEP_INDEX=0xfffffff };

struct RegDep {
  int id;
  unsigned long long rval;
  unsigned long long rval_hi; //<---in case of SIMD reg, hold upper 64 bits

  RegDep(int _id, unsigned long long _rval) : id(_id), rval(_rval) {};
  RegDep(int _id, unsigned long long _rval, unsigned long long _rval_hi) : id(_id), rval(_rval), rval_hi(_rval_hi) {};

  int TYPE() { return id & DEP_TYPE; };
  int ID() { return id & DEP_INDEX; };
  unsigned long long RVAL() { return rval; };
  unsigned long long RVAL_HI() { return rval_hi; };
  static int DEP_NONE() { return DEP_TYPE; };
};


class Packet {
 public:

  Packet(SIM_GOAL _goal) : Goal(_goal) {
   Init();
  };
  
  ~Packet();

  Packet(SIM_GOAL _goal, unsigned long long _iaddr, unsigned int _opcode, std::string _disasm) {
    Goal = _goal;
    PC = _iaddr;
    Opcode = _opcode;
    instr_size_in_bytes = 4;
    big_endian = false;
    access_size_in_bytes = 4;
    instr_group[0] = '\0';
    recordDisassembly(_disasm);
  }
  
  void Init() {
    _dsize = 64;
    exception_class = NO_SIM_EXCEPTION;
    exception_type = NO_EXCEPTION;
    exception_subtype = NO_EXCEPTION;
    clear_exclusive_monitor = false;
    set_exclusive_monitor = false;
    disassembly[0] = '\0';
    instr_group[0] = '\0'; 
  };
  
  bool ForTest() { return Goal == FOR_TEST; };

  string InstrName();
  string InstrEnumName();

  string FetchOpName(int fop_id);
  string WritebackOpName(int fop_id);
  void recordExceptionCondition(int type, int stype=0, unsigned int imm=0);

  string exceptionClass();

  string exceptionType();
  string exceptionSubtype();

  string archExceptionType();
  string archExceptionSubtype();

  string internalExceptionType();
  string internalExceptionSubtype();

  string exceptionImmediate();

  string testBenchError();

  int lastState() { return last_state; };
    
  void recordDisassembly(string &disasm) { strcpy(disassembly,disasm.c_str()); };
  string Disassembly() { return string(disassembly); };

  void recordInstrGroup(string &group) { strcpy(instr_group,group.c_str()); };
  string instrGroup() { return string(instr_group); };

  void recordInstrEncoding(unsigned int _encoding) { encoding = _encoding; };
  unsigned int instrEncoding() { return encoding; };

  void setOpcode(unsigned int _opcode) { Opcode = _opcode; };
  
  void DumpMemoryAccesses();

  void AddRegisterAccess(std::string &rname,int type,int id,unsigned long long rval_lo,unsigned long long rval_hi,bool for_write);
  void AddMemoryAccess(MemoryAccess &my_access);
  void SetState(int _state);
  
  friend std::ostream& operator<< (std::ostream &os, Packet &pkt);

  ProgramCounter PC;               // PC address for instruction in this packet 
  ProgramCounter NextPC;           // PC update value when instruction executes normally
  unsigned int   Opcode;           // instruction encoding read from memory
  int            A64InstrIndex;    // decoded A64 instruction index - 1st level - see section C4.1

  unsigned int   encoding;         // intended instruction encoding

  int instr_size_in_bytes;         // size of current instruction according to currrent Pstate
  int access_size_in_bytes;        // # of memory bytes to access when reading current instruction

  unsigned char mbuf[80];          // hold instruction bytes read from memory

  bool big_endian;                 // instruction endianness (always false on arm processor)

  unsigned int primary_opcode;     // instruction opcode bits 28..25

  char disassembly[256];           // record disassembly here from app
  char instr_group[256];           // record target instruction group

  int execute_op;                  // which machine op to perform

  // rmode is NOT set during instruction decode...

  unsigned RMode() { 
    if (!rmode.IsDefined()) {
      rmode = (Opcode >> 15) & 0x7;
    }
    return rmode.Value();
  };

  InstructionField sf;
  InstructionField op;
  InstructionField op0;
  InstructionField op1;

  InstructionField op2;
  InstructionField op3;
  InstructionField op4;
  InstructionField op21;
  InstructionField op31;
  InstructionField op54;

  InstructionField opc;
  InstructionField o0;
  InstructionField o1;
  InstructionField o2;
  InstructionField o3;
  InstructionField o4;

  InstructionField a;
  InstructionField b;
  InstructionField b40;
  InstructionField b5;
  InstructionField c;
  InstructionField d;
  InstructionField e;
  InstructionField f;
  InstructionField g;
  InstructionField h;
  InstructionField H;
  InstructionField L;
  InstructionField LL;
  InstructionField S;
  InstructionField M;
  InstructionField N;
  InstructionField hw;
  InstructionField Q;
  InstructionField R;
  InstructionField U;
  InstructionField V;
  InstructionField Rd;
  InstructionField Rn;
  InstructionField Rs;
  InstructionField Rt;
  InstructionField Rt2;
  InstructionField Ra;
  InstructionField CRn;
  InstructionField Rm;
  InstructionField CRm;
  InstructionField shift;
  InstructionField size;
  InstructionField cmode;
  InstructionField rmode;
  InstructionField cond;
  InstructionField nzcv;
  InstructionField opcode;
  InstructionField opcode2;
  InstructionField opt;
  InstructionField option;
  InstructionField type;
  InstructionField scale;
  InstructionField len;
  InstructionField imm3;
  InstructionField imm4;
  InstructionField imm5;
  InstructionField imm6;
  InstructionField imm7;
  InstructionField imm8;
  InstructionField imm9;
  InstructionField imm12;
  InstructionField imm14;
  InstructionField imm16;
  InstructionField imm19;
  InstructionField imm26;
  InstructionField immlo;
  InstructionField immhi;
  InstructionField immr;
  InstructionField imms;
  InstructionField immb;
  InstructionField immh;


  int saveFloatFlags()    { return fegetenv(&_float_flags); };
  int restoreFloatFlags() { return fesetenv(&_float_flags); };
  
  std::fenv_t _float_flags;
  
  int setDsize(int dz) { _dsize = dz; return _dsize; };
  int Dsize() { return _dsize; };
  
  int _dsize;    // 32 bit or 64 bit - used with dp ops

  
  vector<int>           mOpsFetch;     // used to indicate which operands to fetch
  vector<int>           mOpsWriteback; // used to indicate which operands to write back after execution
  vector<int>           mOpExec;       // not sure yet if needed for execution
  vector<MemoryAccess>  mOpsMemory;    // memory accesses

  // NOTE: translations are transient, ie, are pointers into an ever changing list of translations
  //       (which may be a fixed list, ie, a TLB table). Once a packet is consumed the translation
  //       entries are invalid. As each instruction is executed then if desired, maintain your
  //       own list of transactions...

  vector<Translation *> translations;  // address translations

  void discardTransactions();

  vector<struct RegDep> srcRegDep;     // derived source register dependency
  vector<struct RegDep> destRegDep;    // derived dest register dependency

  int            Goal;                // simulation goal
  int            State;               // current instruction execution state

  int            exception_class;     // arch vs internal vs generation
  int            exception_type;      // A64 exception type (if exception)
  int            exception_subtype;   // exception subtype
  int            exception_imm;       // specifically for SVC or SMC
  int            last_state;          // state on which exception (if any) occurred
  
  TESTBED_ERROR  testbench_error;     // example: looping
 
  PSTATE         Pstate;              // pstate before instruction executes
  PSTATE         NextPstate;          // pstate updated value

  _FPSR          FPSR;                // FPSR before instruction executes
  _FPSR          Next_FPSR;           // FPSR updated value

  GPRegister     Nreg;                // source N register operand if any
  GPRegister     Mreg;                // source M register operand if any

  GPRegister     Treg;                // source Rt register operand if any
  GPRegister     T2reg;               // source Rt2 register operand if any
  GPRegister     RSreg;               // source Rs register operand if any
  GPRegister     RAreg;               // source Ra register operand if any

  GPRegister     Dreg;                // dest D register operand if any
  GPRegister     Dreg2;               // 2nd dest D register operand if any
  GPRegister     Dreg3;               // used only for
  GPRegister     Dreg4;               //   quad register loads
  
  GPRegister     Sreg;                // dest system register operand if any
                                      // value is system register ID

  FloatRegister  VAreg;               // source float/simd register
  FloatRegister  VMreg;               // source float/simd register
  FloatRegister  VNreg;               // source float/simd register
  FloatRegister  VDreg;               // dest   float/simd register
  FloatRegister  VTreg;               // dest   float/simd register
  FloatRegister  VT2reg;              // dest   float/simd register
  FloatRegister  VT3reg;              // dest   float/simd register
  FloatRegister  VT4reg;              // dest   float/simd register


  vector<XRegister> srcXreg;           // uncategorized source register
  vector<XRegister> destXreg;          // uncategorized dest register
  
  
  bool               clear_exclusive_monitor; // set
  bool               set_exclusive_monitor;   //   by memory accesses
  unsigned long long excl_la;                 //     la,
  int                excl_size;               //       size,
  bool               excl_priv;               //        privilege state of access to use at commit time
};

#endif
#define __A64PACKET__ 1
