#ifndef __A64_SEMIHOSTING__

#include <string>
#include "SemiHosting.h"

class State;
class Memory;
class Packet;

// a64 specific semihosting...

// perhaps not linux limits, but seem reasonable for standalone C apps:
#define SH_ENV_MAX_LEN      4096
#define SH_CMDLINE_MAX_LEN  4096
#define SH_FILENAME_MAX_LEN 4096
#define SH_STRING_MAX_LEN   4096

class semihostParams {
 public:
  semihostParams()
  : heap_base(0),heap_limit(0),stack_base(0),stack_limit(0),env_ptr(0),cmdline_ptr(0),
    env_max_len(SH_ENV_MAX_LEN),cmdline_max_len(SH_CMDLINE_MAX_LEN),filename_max_len(SH_FILENAME_MAX_LEN),
    string_max_len(SH_STRING_MAX_LEN), are_set(false)
  {
   memset(env,'\0',SH_ENV_MAX_LEN);
   memset(cmdline,'\0',SH_CMDLINE_MAX_LEN);  
  }

  semihostParams(semihostParams &src)
  : heap_base(src.heap_base),heap_limit(src.heap_limit),stack_base(src.stack_base),stack_limit(src.stack_limit),
      env_ptr(src.env_ptr),cmdline_ptr(src.cmdline_ptr),
    env_max_len(src.env_max_len),cmdline_max_len(src.cmdline_max_len),filename_max_len(src.filename_max_len),
    string_max_len(src.string_max_len), are_set(src.are_set)
  {
   memset(env,'\0',SH_ENV_MAX_LEN);
   strcpy(env,src.env);
   memset(cmdline,'\0',SH_CMDLINE_MAX_LEN);
   strcpy(cmdline,src.cmdline);
  }

  void Dump();

  bool AreSet() { return are_set; };
  void MarkAsSet() { are_set = true; };

  bool AreValid();
  
  unsigned long long heap_base;    //
  unsigned long long heap_limit;   //
  unsigned long long stack_base;   // addresses in memory
  unsigned long long stack_limit;  //
  unsigned long long env_ptr;      //
  unsigned long long cmdline_ptr;  //
  
  int env_max_len;
  int cmdline_max_len;
  int filename_max_len;
  int string_max_len;
  
  char env[SH_ENV_MAX_LEN];
  char cmdline[SH_CMDLINE_MAX_LEN];

  bool are_set;  
};

class a64SemiHosting {
 public:
  a64SemiHosting(State *_cpu, Memory *_memory, class semihostParams &_params)
    : cpu(_cpu), memory(_memory), packet(NULL), params(_params), verbose(false), semihost_op(-1), rcode(1) {};

  virtual ~a64SemiHosting() {};
  
  virtual int Dispatch(Packet *_packet, bool _verbose);

  // we support these semihosting ops:
  
  void Open();
  void Close();
  void WriteC();
  void Write0();
  void Write();
  void Read();
  void ReadC();
  void IsError();
  void IsTTY();
  void Seek();
  void Flen();
  void Clock();
  void Time();
  void Errno();
  void GetCmdline();
  void HeapInfo();
  void ReportException();
  
  // these are unimplemented:

  virtual void  TmpName() {};
  virtual void  Remove() {};
  virtual void  Rename() {};
  virtual void  System() {};
  virtual void  Elapsed() {};
  virtual void  TickFreq() {};

  std::string opname(int semihost_op);

  int ReadSimulatorMemory(unsigned long long address,unsigned char *dest, int num_bytes);
  int WriteSimulatorMemory(unsigned long long address,unsigned char *src, int num_bytes);

  unsigned long long ReadULL(unsigned long long src_addr);
  void ReadString(unsigned char *dest, unsigned long long src_addr, int len);
  void WriteULL(unsigned long long dest_addr, unsigned long long src_val);

  void dumpParms();
  
 private:

  State  *cpu;
  Memory *memory;
  Packet *packet;
  semihostParams params;

  SemiHosting semihost_helper;

  bool verbose;
  
  int semihost_op;
  unsigned long long rcode;
};

#endif
#define __A64_SEMIHOSTING__ 1
