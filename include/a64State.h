#ifndef __A64STATE__

#include <map>

//------------------------------------------------------------------------------------------------------------------- 
// state for each CPU...
//------------------------------------------------------------------------------------------------------------------- 

enum { SPR_ID_AA64PFR0_EL1=0x30040,
       SPR_ID_HCR_EL2=0x34110,
       
       SPR_VBAR_EL1=0x30c00,
       SPR_VBAR_EL2=0x34c00,
       SPR_VBAR_EL3=0x36c00,
       
       SPR_ELR_EL1=0x30401,
       SPR_ELR_EL2=0x34401,
       SPR_ELR_EL3=0x36401,
       
       SPR_ESR_EL1=0x30520,
       SPR_ESR_EL2=0x34520,
       SPR_ESR_EL3=0x36520,
       
       SPR_FAR_EL1=0x30600,
       SPR_FAR_EL2=0x34600,
       SPR_FAR_EL3=0x36600,
       
       SPR_SPSR_EL1=0x30400,
       SPR_SPSR_EL2=0x34400,
       SPR_SPSR_EL3=0x36400,
       
       SPR_TCR_EL1=0x30202,
       SPR_TCR_EL2=0x34202,
       SPR_TCR_EL3=0x36202
};

class State {
  ExceptionEnables *exception_enables;

 public:
   State() : clock(0), halted(false), waiting(false), wakeup(false), timer_clock(0) {
    Init();
  };

  //State(State *ref_state) : reference_state(ref_state) {};

  ~State() {};

  void Init();
  int RegNameIndex(std::string register_name);
  void InitializeRegister(std::string &rname,unsigned long long rval, unsigned long long rval_hi = 0);
  void ReserveAppRegister(std::string &);
  
  int WriteResource(std::string &rname,unsigned long long rval, unsigned long long rval_hi);
  int ReadResource(std::string &rname,unsigned long long &rval, unsigned long long &rval_hi);

  void SetID(unsigned int _id) { MPIDR_EL1.Aff0(_id); VMPIDR_EL2.Aff0(_id); };

  int GetID() { return MPIDR_EL1.Aff0(); };
  
  string SystemRegisterName(int rindex);

  int SystemRegisterGet(int &rindex, unsigned long long &rval,unsigned int sys_op0,unsigned int sys_op1,unsigned int sys_crn,unsigned int sys_crm,unsigned int sys_op2);
  int SystemRegisterPut(int rindex, unsigned long long rval);

  int CheckSystemRegisterAccess(unsigned int sys_op1); //<---check accessibility of system register based on current PL, etc.

  bool SystemRegisterTrapOutcome(int rcode); //<--added late to distinguish 'trap' return code from CheckSystemRegisterAccess (sigh)


  int EncodeRegisterID(unsigned int op0,unsigned int op1,unsigned int CRn,unsigned int CRm,unsigned int op2);
  int PstateAccess(int &rindex, unsigned int op1,unsigned int op2);
  bool PstateUpdate(PSTATE &pstate, int sysreg_id,unsigned long long &rval);

  bool SysOp(int &sysop_type, int &sysop_index, unsigned int op0,unsigned int op1,unsigned int CRn,unsigned int CRm,unsigned int op2);
  void SysOpNames(string &sysop_alias, string &sysop_name, int sysop_type, int sysop_index);
  
  int GetSPindex();
  Register GetSP();
  void UpdateSP(Register SP);

  bool UsingAArch32() { return false; };
  bool ELUsingAArch32(int /*EL*/) { return false; };
  
  bool HaveEL(unsigned int _EL) { return _EL==0 || _EL==1 || ( (_EL==3) && (ID_AA64PFR0_EL1.EL3()==1) ); };
  
  bool IsSecure() { bool in_secure_mode = UsingAArch32() ? (Pstate.M()==A32_MONITOR_MODE) : (Pstate.EL()==EL3);
                    bool in_secure_state = SCR_EL3.NS()==0;
                    return HaveEL(EL3) && (in_secure_mode || in_secure_state);
  };
  bool SMCdisabled() { return SCR_EL3.SMD()==1; };
  void checkForSMCTrap() { /* no EL2, so no trap of SMC instruction...*/ };
  bool Privileged() { return Pstate.EL() > EL0; };

  
  bool IsHalted() { return halted; };               //
  void Halt()     { halted = true; };               // provided for convenience for the application,
                                                    //  does NOT affect internal simulation state
  bool IsWaiting() { return waiting; };             //
  void EnterWaitState() { waiting = true; };        //
  void ClearWaitState() { waiting = false; };       //
  void SetWakeup() { wakeup = true; };              //
  bool WakeupPending() { return wakeup; };          //
  void ClearWakeup() { wakeup = false; };           //
  
  unsigned long long clock;                    // counter that more or less represents a cpu clock
  unsigned long long clock_advance_interval;   // minimal cpu phase advance interval
                                               // each instruction phase will advance the clock by a multiple of the clock interval

  void setClock(unsigned long long _clock, unsigned long long _clock_advance_interval) { 
        clock = _clock; 
        clock_advance_interval = _clock_advance_interval; 
  }; 
  unsigned long long Clock() { return clock; };
  void advanceClock(unsigned int multiplier = 1) { clock += clock_advance_interval * multiplier; };

  unsigned long long AdvancePC() { unsigned long long next_pc = PC.Value() + 4; return PC.Value(next_pc); };
  
  PSTATE    Pstate;

  GPRegister GP[31];  //<---GP31 is stack NO ITS NOT!!!

  ProgramCounter PC;

  SCR       SCR_EL3;

  _ACTLR_EL3 ACTLR_EL3;
  
  SPSR      SPSR_EL1;
  SPSR      SPSR_EL2;
  SPSR      SPSR_EL3;

  AA64DFR0  ID_AA64DFR0_EL1;
  AA64MMFR0 ID_AA64MMFR0_EL1;
  AA64PFR0  ID_AA64PFR0_EL1;
  AA64ISAR0 ID_AA64ISAR0_EL1;

  CPACR     CPACR_EL1;
  CPTR      CPTR_EL2;
  CPTR      CPTR_EL3;

  MIDR      MIDR_EL1;
  MIDR      VPIDR_EL2;
  Register  REVIDR_EL1;

  MPIDR     MPIDR_EL1;
  MPIDR     VMPIDR_EL2;

  CTR       CTR_EL0;
  DCZID     DCZID_EL0;

  RVBAR     RVBAR_EL1;
  RVBAR     RVBAR_EL2;
  RVBAR     RVBAR_EL3;

  FloatRegister V[32];
  _FPCR         FPCR;
  _FPSR         FPSR;

  MDCR     MDCR_EL3;         //
  MDSCR    MDSCR_EL1;        // debug related
  OSDLR    OSDLR_EL1;        //
  OSLAR    OSLAR_EL1;        //
  OSLSR    OSLSR_EL1;        //
    
  Register MDCCSR_EL0;       //
  Register DBGDTR_EL0;       // debug
  Register DBGDTRRX_EL0;     //  comm channel
  Register DBGDTRTX_EL0;     //

  Register DLR_EL0;          // debug link register
  Register DSPSR_EL0;        // debug saved program status register
  Register CONTEXTIDR_EL1;   // context ID register

  Register PAR_EL1;          // physical address register

  Register TPIDR_EL0;        // thread pointer/ID register
  Register TPIDR_EL1;
  Register TPIDR_EL2;
  Register TPIDR_EL3;

  Register ELR_EL1;          // exception return address
  Register ELR_EL2;
  Register ELR_EL3;

  ESR ESR_EL1;          // exception status
  ESR ESR_EL2;
  ESR ESR_EL3;

  Register FAR_EL1;          // fault address register
  Register FAR_EL2;
  Register FAR_EL3;

  Register VBAR_EL1;         // vector base address register
  Register VBAR_EL2;
  Register VBAR_EL3;

  _TCR_EL1   TCR_EL1;          // translation control register
  _TCR_EL2_3 TCR_EL2;
  _TCR_EL2_3 TCR_EL3;

  MAIR MAIR_EL1;             // memory attribute indirection register
  MAIR MAIR_EL2;
  MAIR MAIR_EL3;

  Register RMR_EL1;          // reset management register
  Register RMR_EL2;
  Register RMR_EL3;

  Register AFSR0_EL1;        // auxiliary fault status register 0
  Register AFSR0_EL2;
  Register AFSR0_EL3;

  Register AFSR1_EL1;        // auxiliary fault status register 1
  Register AFSR1_EL2;
  Register AFSR1_EL3;

  Register SP_EL0;           // stack pointer
  Register SP_EL1;
  Register SP_EL2;
  Register SP_EL3;

  _SCTLR_EL1 SCTLR_EL1;        // system control including mmu enable
  _SCTLR_EL2 SCTLR_EL2;        // system control including mmu enable
  _SCTLR_EL3 SCTLR_EL3;        // system control including mmu enable

  TTBR TTBR0_EL1;        // translation table base registers
  TTBR TTBR1_EL1;
  TTBR TTBR0_EL2;
  TTBR TTBR0_EL3;

  HCR HCR_EL2;             // NOTE: EL2 NOT implemented...

  TLB itlb;
  TLB dtlb;

  TIMER_CNTFRQ    CNTFRQ_EL0;          //
  TIMER_CNTHCTL   CNTHCTL_EL2;         //
  TIMER_CTL       CNTHP_CTL_EL2;       //
  TIMER_CVAL      CNTHP_CVAL_EL2;      //
  TIMER_TVAL      CNTHP_TVAL_EL2;      //
  TIMER_CNTKCTL   CNTKCTL_EL1;         // system counter, timer related...
  TIMER_CTL       CNTP_CTL_EL0;        //
  TIMER_CVAL      CNTP_CVAL_EL0;       //
  TIMER_TVAL      CNTP_TVAL_EL0;       //
  TIMER_CNT       CNTPCT_EL0;          //
  TIMER_CTL       CNTPS_CTL_EL1;       //
  TIMER_CVAL      CNTPS_CVAL_EL1;      //
  TIMER_TVAL      CNTPS_TVAL_EL1;      //
  TIMER_CTL       CNTV_CTL_EL0;        //
  TIMER_CVAL      CNTV_CVAL_EL0;       //
  TIMER_TVAL      CNTV_TVAL_EL0;       //
  TIMER_CNT       CNTVCT_EL0;          //
  TIMER_CNTOFF    CNTVOFF_EL2;         //

  ICC_PMR         ICC_PMR_EL1;         //
  ICC_IAR0        ICC_IAR0_EL1;        //
  ICC_EORI0       ICC_EORI0_EL1;       //
  ICC_HPPIR0      ICC_HPPIR0_EL1;      //
  ICC_BPR0        ICC_BPR0_EL1;        //     
  ICC_APR         ICC_AP0R0_EL1;       //
  ICC_APR         ICC_AP0R1_EL1;       //
  ICC_APR         ICC_AP0R2_EL1;       //
  ICC_APR         ICC_AP0R3_EL1;       //
  ICC_APR         ICC_AP1R0_EL1;       //
  ICC_APR         ICC_AP1R1_EL1;       //
  ICC_APR         ICC_AP1R2_EL1;       //
  ICC_APR         ICC_AP1R3_EL1;       // GIC system registers...
  ICC_DIR         ICC_DIR_EL1;         //
  ICC_RPR         ICC_RPR_EL1;         //
  ICC_SGI1R       ICC_SGI1R_EL1;       //
  ICC_ASGI1R      ICC_ASGI1R_EL1;      //
  ICC_SGI0R       ICC_SGI0R_EL1;       //
  ICC_IAR1        ICC_IAR1_EL1;        //
  ICC_EOIR1       ICC_EOIR1_EL1;       //
  ICC_HPPIR1      ICC_HPPIR1_EL1;      //
  ICC_BPR1        ICC_BPR1_EL1;        //
  ICC_CTLR        ICC_CTLR_EL1;        //
  ICC_SRE         ICC_SRE_EL1;         //
  ICC_IGRPEN0     ICC_IGRPEN0_EL1;     //
  ICC_IGRPEN1     ICC_IGRPEN1_EL1;     //
  ICC_SRE         ICC_SRE_EL2;         //
  ICC_CTLR        ICC_CTLR_EL3;        //
  ICC_SRE         ICC_SRE_EL3;         //
  ICC_IGRPEN1     ICC_IGRPEN1_EL3;     //

  exclMonitor local_monitor; // each CPU has a local monitor
  
  void AdvanceTimers(unsigned long long _clock_advance = 1);

  unsigned long long TimerClock() { return timer_clock; };
  void SetTimerClock(unsigned long long new_value) { timer_clock = new_value; };

 private:
  std::map<std::string,int> all_supported_registers;

  bool halted;
  bool waiting;
  bool wakeup;
  
  unsigned long long timer_clock;
};


#endif
#define __A64STATE__ 1
