#ifndef _SEMIHOSTING_

enum SEMIHOST_OPS { 
  SYS_OPEN=0x01, SYS_CLOSE=0x02, SYS_WRITEC=0x03, SYS_WRITE0=0x04, SYS_WRITE=0x05,
  SYS_READ=0x06, SYS_READC=0x07, SYS_ISERROR=0x08, SYS_ISTTY=0x09, SYS_SEEK=0x0a, SYS_FLEN=0x0c,
  SYS_TMPNAME=0x0d, SYS_REMOVE=0x0e, SYS_RENAME=0x0f, SYS_CLOCK=0x10, SYS_TIME=0x11, SYS_SYSTEM=0x12,
  SYS_ERRNO=0x13, SYS_GET_CMDLINE=0x15, SYS_HEAPINFO=0x16, SYS_ELAPSED=0x30, SYS_TICKFREQ=0x31, 
  SYS_REPORT_EXCEPTION=0x18,  
  // a64sim define semihosting ops:                 
  SYS_EXIT=0x100, SYS_CHECKPOINT=0x101, SYS_SELFCHECK=0x102
};

enum SWI_REPORT_EXCEPTION_REASONS {
  ADP_Stopped_BranchThroughZero=0x20000,
  ADP_Stopped_UndefinedInstr=0x20001,
  ADP_Stopped_SoftwareInterrupt=0x20002,
  ADP_Stopped_PrefetchAbort=0x20003,
  ADP_Stopped_DataAbort=0x20004,
  ADP_Stopped_AddressException=0x20005,
  ADP_Stopped_IRQ=0x20006,
  ADP_Stopped_FIQ=0x20007,
  ADP_Stopped_BreakPoint=0x20020,
  ADP_Stopped_WatchPoint=0x20021,
  ADP_Stopped_StepComplete=0x20022,
  ADP_Stopped_RunTimeErrorUnknown=0x20023,
  ADP_Stopped_InternalError=0x20024,
  ADP_Stopped_UserInterruption=0x20025,
  ADP_Stopped_ApplicationExit=0x20026,
  ADP_Stopped_StackOverflow=0x20027,
  ADP_Stopped_DivisionByZero=0x20028,
  ADP_Stopped_OSSpecific=0x20029
};

#define MAX_STRING_LENGTH 1024

class SemiHosting {
 public:
  SemiHosting() {};
  virtual ~SemiHosting() {};

  int SysOpen(char *filename, int mode_index, unsigned long long &file_no);
  int SysClose(unsigned long long fileHandle);
  int SysWrite(unsigned long long fileHandle, const char *src_buffer, int num_bytes);
  int SysRead(unsigned long long fileHandle, unsigned char *dest_buffer, int num_bytes);
  int IsTTY(unsigned long long fileHandle);
  int SysSeek(unsigned long long fileHandle, unsigned long long byte_position);
  int SysFlen(unsigned long long fileHandle);

  int SysWriteC(char src_char);
  int SysWrite0(const char *src_buffer);
  int SysReadC();
  int IsError(long long *errcode);

  int SysTmpName(char *tmp_filename,unsigned int target_id,int buflen);
  int SysRemove(char *src_filename);
  int SysRename(char *old_filename,char *new_filename);
  unsigned long long SysTime();
  int SysSystem(char *cmdline);
  int SysErrNo();

  // semihosting calls specific to this simulator:

  virtual long long SysClock();
  virtual int SysGetCmdline(char *cmdline);
  virtual int SysHeapInfo(unsigned long long **heap_base,int *heap_limit,unsigned long long **stack_base,int *stack_limit);
  virtual unsigned long long SysElapsed();
  virtual int SysTickFreq();

  virtual int  SysExit(int exit_code);
  virtual void SysCheckpoint();
  virtual int  SelfCheck(int reg_type, int reg_index, unsigned long long mask);

 protected:
  int SysOpenMode(char *mode,int mode_index);
};

#endif
#define _SEMIHOSTING_ 1

