#ifndef __A64CONTROL__

//------------------------------------------------------------------------------------------------------------------- 
// control logic for instruction execution...
//------------------------------------------------------------------------------------------------------------------- 

enum { 
      FREERUN_INIT, FREERUN_RESERVE_MEMORY, FREERUN_SELECT_INSTRUCTION, FREERUN_ENCODE_INSTRUCTION, FREERUN_WRITE_INSTRUCTION, FREERUN_END_INSTRUCTION,
      FETCH_STATE, DECODE_STATE, FETCH_OPERANDS_STATE, EXECUTE_STATE, MEMORY_ACCESS_STATE, WRITEBACK_STATE, RETIRE_STATE
};

//enum { NO_ERROR=0, FETCH_ERROR=1, DECODE_ERROR=2, OPERANDS_ERROR=3, EXECUTE_ERROR=4, MEMORY_ACCESS_ERROR=5, WRITEBACK_ERROR=6, INTERNAL_ERROR=99 };

enum { ADDSUB_OP, MRS_MSR_OP, MOVE_IMM_OP, LOGICAL_OP, LABEL_OP, SHIFT_OP, HINT_OP, CLREX_OP, BRANCH_OP, BIT_FIELD_OP,
       DEBUG_OP, COMPARE_OP, CHECKSUM_OP, CONDITIONAL_OP, SYSTEM_OP, LS_EXCL_OP, LS_REG_PAIR_OP, LS_REG_PAIR_HINT_OP,
       LS_REG_IMM_OP, LOAD_REG_LITERAL_OP, LS_REG_UNPRIVILEGED_OP, LS_REG_UNSCALED_OP, LS_REG_OFFSET_OP, MUL_DIV_OP,
       FLOAT_OP, SIMD_OP,
       UNKNOWN_OP
     };


class Control {
 public:
  Control(State *_cpu,Memory *_memory,Packet *_packet,ExceptionEnables *exception_enables, A64SimMonitor *_sim_monitor=NULL);
  ~Control() {};

  State            *cpu;
  Memory           *memory;
  Packet           *packet;
  ExceptionEnables *exception_enables;
  A64SimMonitor    *sim_monitor;

  int instrID;  // set by Execute method

  bool allow_uninitialized_reg_access; // don't allow unitialized sourceregister to be accessed

  bool Privileged() { return cpu->Pstate.Privileged(); };

  int InstrState(void);
  int InstrState(int _state);

  int InstrLength();

  int NextState(unsigned int &multiplier);
  string StateName();
  void Step(int state = FETCH_STATE, bool start_recording = true);

  void Fetch(unsigned int &multiplier);                   // fetch instruction
  void Decode(unsigned int &multiplier);                  // decode instruction opcode + fields
  void FetchOperands(unsigned int &multiplier);           // fetch (register) operands
  void Execute(unsigned int &multiplier);                 // execute fixed/
  void executeFloatSIMD(unsigned int &multiplier);        //    float/simd ALU ops
  void AccessMemory(unsigned int &multiplier);            // load/store accesses
  void Writeback(unsigned int &multiplier, bool commit);  // update (register) operands
  void Retire(unsigned int &multiplier);                  // retire instruction

  void FreerunInit();                                     // freerun setup for next instruction...                      
  void FreerunReserveMemory();                            // reserve memory for next instruction...
  void FreerunSelectInstruction();                        // select instruction group, instruction opcode...
  void FreerunEncodeInstruction();                        // complete instruction encoding...
  void FreerunWriteInstruction();                         // write instruction to memory...
  void FreerunEndInstruction();                           // freerun instruction complete...

  void DirectRecordSPRaccess(int system_reg_index,unsigned long long system_reg_val,bool updated=false);

  void DecodeA32();
  void DecodeA64();

  void ScheduleFetchOpsA64();
  void ScheduleWriteBackOpsA64();

  void IdentifyMachineOP();

  void Disassemble(char *tbuf);

  string MachineOpName(int mop);

  void handleException(SIM_EXCEPTION_CLASS eclass);
  bool allowException();
  void processException();
  void SystemRegisterTrap(unsigned target_el,unsigned op0, unsigned op2, unsigned op1, unsigned crn, unsigned rt, unsigned crm, unsigned dir);
  void TakeException(unsigned int EL,ExceptionRecord exception,unsigned long long preferred_exception_return,unsigned long long vector_offset);
  void BranchTo(unsigned long long target,BranchType branch_type,int N);
  void ExceptionClass(unsigned int &ec,unsigned int &il,unsigned int type,unsigned int target_el);
  void ReportException(ExceptionRecord exception, int target_el);

  void RaiseIRQ();
  void RaiseFIQ();

  unsigned long long VBAR(int EL);
  unsigned long long ELR(int EL);
  void SetELR(int target_el,unsigned long long return_addr);
  void SetESR(unsigned int ec,unsigned int il,unsigned int iss);
  void SetFAR(int target_el,unsigned long long address);
  void SetSPSR(int target_el,unsigned int rval);
  unsigned int SPSRval(int target_el);

  void SetPSTATEFromSPSR(unsigned int spsr_val);
  unsigned int GetPSRFromPSTATE();
  unsigned int ProcessorID();

  void ExceptionReturn();
  unsigned long long NextInstrAddr();
  void SSAdvance();
  void CallSecureMonitor(unsigned int imm);
  void CallSupervisor(unsigned int imm);

  bool uadd64_overflow(unsigned long long op1,unsigned long long op2,unsigned long long Cin);

  void AddWithCarry32(unsigned long long &result, unsigned int &nzcv, unsigned long long op1,unsigned long long op2,unsigned long long carry);
  void AddWithCarry64(unsigned long long &result, unsigned int &nzcv, unsigned long long op1,unsigned long long op2,unsigned long long carry);
  void AddWithCarry(unsigned long long &result, unsigned int &nzcv, unsigned long long op1,unsigned long long op2,unsigned long long carry);

  unsigned long long srcRegValue(unsigned long long rval);
  void SizeSourceOperands();
  void SizeDestOperands();

  long long SignExtend(unsigned long long op,int sbit,int rwidth=64);
  unsigned long long Ones(int count);

  int DecodeRegExtend(int op);
  unsigned long long ExtendReg(unsigned long long rval,int extend_type,int shift,int N);
  unsigned long long ShiftReg(unsigned long long rval,int shift_type,int shift_amount);
  unsigned long long LSL(unsigned long long rval,int shift_amount);
  unsigned long long LSR(unsigned long long rval,int shift_amount);
  unsigned long long ASR(unsigned long long rval,int shift_amount);
  unsigned long long ROR(unsigned long long rval,int shift_amount, int data_size=0);

  bool IsZero(unsigned long long rval);
  unsigned long long Not(unsigned long long rval);

  int LoadStoreSignExtendTo(unsigned int instrID, unsigned int opc);

  int HighestBitSet(unsigned long long imm, int size);
  int count_leading_zeros(unsigned long long rval,int dsize);
  int count_leading_sign_bits(unsigned long long rval,int dsize);
  unsigned long long Replicate(unsigned long long bits,unsigned int esize);
  unsigned long long DecodeBitMasks(unsigned long long &tmask, unsigned int immN, unsigned imms, unsigned immr, bool immediate);
  bool ConditionHolds(unsigned int cond);
  void CheckBranchTargetAlignment(unsigned long long nextPC);
  void CheckStackAlignment();
  bool BigEndian();

  void ExecuteAddSubtract();
  void ExecuteMoveImmediate();
  void ExecuteMRS_MSR();
  void ExecuteLogical();
  void Branch();
  void LabelOrPageAddress();
  void FloatSIMD();
  void Hint();
  void ShiftOps();
  void BitFieldOrCounts();
  void DebugOp();
  void Comparison();

  void EventRegisterSet();
  void CheckSum();
  void Conditional();
  void System();
  void MultiplyDivide();
  void ClearExclusiveMonitor();
  void LoadStoreExclusive();
  void LoadStoreRegisterPair();
  void LoadStoreRegisterPairWithHint();
  void LoadStoreRegisterImmediate();
  void LoadRegisterLiteral();
  void LoadStoreRegisterUnprivileged();
  void LoadStoreRegisterUnscaled();
  void LoadStoreRegisterOffset();

  void TrapFPaccess();

  void vfpMath();
  void vfpRounding();
  void vfpConditionalCompare();
  void vfpCompare();
  void vfpConditionalSelect();
  void vfpMoveImm();
  void vfpMove();
  void vfpFPConvert();
  void vfpFPConvertToSignedInt();
  void vfpLoadStore();
  void vfpLoadLiteral();
  void vfpLoadStorePair();
  void vfpLoadStoreRegisterOffset();

  // save register value(s) to read/write buffer...

  void SaveRegister(unsigned long long t, unsigned char *mb, int size, bool endianness);
  void SaveRegisterPair(unsigned long long t,unsigned long long t2, unsigned char *mbuf, int size, bool endianness, bool swap_regs);
 
  // load register value(s) from read/write buffer...

  void LoadRegister(unsigned long long &t, unsigned char *mb, int size, bool endianness);
  void LoadRegisterPair(unsigned long long &t,unsigned long long &t2, unsigned char *mbuf, int size, bool endianness, bool swap_regs);

  // generic timer methods:
  
  bool TimerTick(); // advance timers

  enum timer_event { EVENT_STREAM_VIRTUAL=1, EVENT_STREAM_PHYSICAL=2, TIMER_ASSERTED_PHYSICAL=4,
	             TIMER_ASSERTED_VIRTUAL=8, TIMER_ASSERTED_SECURE=16, NO_EVENT=0 };

  //bool TimerAsserts(unsigned int &events_physical) {}; // return true if timer condition asserted. events indicates which conditions
  
 private:
  bool _event_stream(TIMER_CNTCTL &kctl, TIMER_CNT &counter);
  bool _timer_tick(TIMER_CTL &ctl, TIMER_CVAL &cval, TIMER_TVAL &tval, TIMER_CNT &tcnt, TIMER_CNTOFF &toff);
  
  long long lsBaseAddress(int n, bool for_prefetch);
  unsigned long long lsOffsetBaseAddress(int n,long long offset, bool for_prefetch);
  unsigned long long PCrelativeAddress(long long offset);

  bool executeFloatSIMD_inner(unsigned int &multiplier);

  float FPHalfPrecisionToFloat(unsigned int hp_fpval);
  unsigned int FPFloatToHalfPrecision(float src);

  double FPHalfPrecisionToDouble(unsigned int hp_fpval);
  unsigned int FPDoubleToHalfPrecision(double src);

  unsigned long long VFPExpandImm(int dsize, unsigned int imm8);

  int FPDecodeRM(unsigned int rm);
  int FPRoundingMode();

  void SetupFloatExecEnv();                        // setup floating point "execution env" (exc flags + rounding mode)
  void RestoreFloatExecEnv();                      // restore floating point "execution env"
  void UpdateSimulatorFloatFlags(bool do_update);  // after floating pt operation, update simulator floating pt flags
  void GetEnvFloatFlags(_FPSR &fp_flags);          // transfer float flags from C++ env to FPSR copy
};


#endif
#define __A64CONTROL__ 1
