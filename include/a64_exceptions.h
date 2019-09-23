#ifndef __A64_EXCEPTIONS__

#include <unordered_map>

enum PRIVILEGE_LEVELS { PL0, PL1, PL2, PL3 };
enum EXCEPTION_LEVELS { EL0, EL1, EL2, EL3 };

// see Section D1.13

// no EL2 related stuff...

enum SIM_EXCEPTION_CLASS { NO_SIM_EXCEPTION=0, ARCH_EXCEPTION=1,
                           WAIT_FOR_EVENT=2, WAIT_FOR_INTERRUPT=3, EVENT_NOTICE=4, EVENT_NOTICE_LOCAL=5,
			   INTERNAL_ERROR=6, GENERATION_ERROR=7 };

enum TESTBED_ERROR { NO_TESTBED_ERROR=0, UNEXPECTED_REEXECUTION, MALFORMED_INSTRUCTION, UNEXPECTED_EXCEPTION };

enum A64_EXCEPTION { NO_EXCEPTION=0, 
                     SOFTWARE_STEP, // 4961
                     MISALIGNED_PC, // 4957
                     INSTRUCTION_ABORT, // 4956
                     BREAKPOINT, // breakpoint instruction
                     DEBUG_BREAKPOINT, // 4960 - debug breakpoint
                     ILLEGAL_EXECUTION_STATE, // 4966
                     UNDEFINED_INSTRUCTION, // 4966
                     SMC_UNDEFINED, // 4966
                     EXCEPTION_GENERATING_INSTRUCTION, // SVC, HVC, SMC
                     EXCEPTIONS_TO_EL3, // what is this???
                     FLOATING_POINT_EXCEPTIONS, // including FP/ASID enable? access? in CPACR_EL1??? - 4964 4968
                     STACK_POINTER_ALIGNMENT, // 4957
                     DATA_ABORT, // 4957
                     DEBUG_WATCHPOINT, // 4961
                     ADDRESS_SPACE_ERROR, // MADE THIS ONE UP FOR CASE WHEN PHYSICAL MEMORY RANGE EXCEEDED (MMU OFF)
                     TRAP, // any instruction trap,
		     // trap on WFEI WFI??? - el2
		     // system register trap??? - el2
                     IRQ,
                     FIQ
                   };

enum A64_UNDEFINED_EXCEPTION { NO_UNDEF=0, UNALLOCATED_ENCODING, INACCESSIBLE_INSTRUCTION_AT_CURRENT_EL, 
                               UNALLOCATED_ENCODING_DBG_STATE, NON_DEBUG_STATE_EXECUTION, HVC_EXECUTION_DISABLED, 
                               MSR_MRS_SP_EL0, HLT_EXECUTION_DISABLED,
                               DCPS1_NON_SECURE_EL0, DCPS2_NO_EL2, DCPS3_NO_EL3 
                             };

enum A64_DATA_ABORT_EXCEPTION { ALIGNMENT, READ_PERMISSIONS, WRITE_PERMISSIONS };
enum A64_INSTRUCTION_ABORT_EXCEPTION { PERMISSIONS, EXECUTE_NEVER, SECURE_INSTRUCTION_FETCH };

enum INTERNAL_ERRORS {
  INVALID_CONDITION, INVALID_EXCEPTION_LEVEL, INVALID_REG_EXTEND_FIELD,PAIRED_REGISTERS_INVALID,INVALID_OPC_FIELD,
  OPERANDS_ERROR,INVALID_REGISTER,UNINITIALIZED_REGISTER,INVALID_REGISTER_INDEX,UNIMPLEMENTED_INSTRUCTION,RESERVED_REGISTER
};

enum INTERNAL_ERROR_SUBTYPES {
  ENDIANNESS_STATE,EXCLUSIVE_OP,LOAD_REG_LITERAL
};

enum Exception_Type {
  EXCEPTION_Uncategorized=0x00, // D7-1837
  EXCEPTION_WFxTrap=0x01, // WFE/WFI when trapped - D7-1837

  EXCEPTION_CP15RTTrap=0x03,
  EXCEPTION_CP15RRTrap=0x04,
  EXCEPTION_CP14RTTrap=0x05,
  EXCEPTION_CP14DTTrap=0x06,
  EXCEPTION_AdvSIMDFPAccessTrap=0x07,
  EXCEPTION_FPIDTrap=0x08,
  EXCEPTION_CP14RRTTrap=0x0c,

  EXCEPTION_IllegalState=0x0e,

  EXCEPTION_SupervisorCall=0x11, 
  EXCEPTION_HypervisorCall=0x12,
  EXCEPTION_MonitorCall=0x13,

  EXCEPTION_SystemRegisterTrap=0x18,

  EXCEPTION_InstructionAbort=0x20,
  EXCEPTION_PCAlignment=0x22,
  EXCEPTION_DataAbort=0x24,
  EXCEPTION_SPAlignment=0x26,

  EXCEPTION_FPTrappedException=0x28,

  EXCEPTION_SError=0x2f, // D7-1854

  EXCEPTION_Breakpoint=0x30,
  EXCEPTION_SoftwareStep=0x32,
  EXCEPTION_Watchpoint=0x34,
  EXCEPTION_SoftwareBreakpoint=0x38,
  EXCEPTION_VectorCatch=0x3a,

  EXCEPTION_IRQ=0xf0,
  EXCEPTION_FIQ=0xf1
};

enum BranchType {
  BranchType_CALL,
  BranchType_ERET,
  BranchType_DBGEXIT,
  BranchType_RET,
  BranchType_JMP,
  BranchType_EXCEPTION,
  BranchType_UNKNOWN
};

class ExceptionEnables {
 public:
  ExceptionEnables() {};
  ExceptionEnables(ExceptionEnables &_src);
  
  void Add(bool _is_enabled, int _sim_excep_type, int _main_excep, int _excep_subtype=NO_UNDEF);
  bool Enabled(int _sim_excep_type, int _main_excep, int _excep_subtype=NO_UNDEF);
  
 private:
  int Index(int _sim_excep_type, int _main_excep, int _excep_subtype=NO_UNDEF);

  unordered_map<int,bool> enables;
};

class ExceptionRecord {
 public:
  
 ExceptionRecord(unsigned int _type) : type(_type), subtype(0), syndrome(1<<24 | 0xe<<20), vaddress(0), ipvalid(false), ipaddress(0) {};
  
  ExceptionRecord(ExceptionRecord &_src) : type(_src.type), subtype(_src.subtype), syndrome(_src.syndrome), vaddress(_src.vaddress),
       ipvalid(_src.ipvalid), ipaddress(_src.ipaddress) {};

  void SetType(unsigned int _type) { type = _type; };
  void SetSubtype(unsigned int _subtype) { subtype = _subtype; };
  void SetSyndrome(unsigned int _syndrome) { syndrome = _syndrome; };
  void SetVaddress(unsigned long long _vaddress) { vaddress = _vaddress; };
  void SetIpaddress(unsigned long long _ipaddress) { ipaddress = _ipaddress; };

  unsigned int Type() { return type; };
  unsigned int Subtype() { return subtype; };
  unsigned int Syndrome() { return syndrome; };
  unsigned long long Vaddress() { return vaddress; };
  unsigned long long Ipaddress() { return ipaddress; };
  
 private:
  unsigned int       type;
  unsigned int       subtype;

  unsigned int       syndrome;   // low order 25 bits only
  unsigned long long vaddress;   // virtual fault address
  bool               ipvalid;    // physical fault address is valid
  unsigned long long ipaddress;  // 48 bit physical fault address
};

#define __A64_EXCEPTIONS__ 1
#endif

