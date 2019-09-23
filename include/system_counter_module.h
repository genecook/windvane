#ifndef __SYSTEM_COUNTER_MODULE__

#include <string>
#include "memmap_device.h"

class SystemCounterModule : public memmap_device {
 public:
 SystemCounterModule() : CNTCR(0),CNTSR(0),CNTCV(0),CNTCV_prev(0),CNTFID0(0) {
 };

  std::string Name() { return std::string("System Counter Module"); };
  std::string RegisterName(unsigned long long PA);

  // reset - reset system counter module registers to default values...  
  void Reset() {
    CNTCR = 0;
    CNTSR = 0;
    CNTCV = 0;
    CNTFID0 = 0;
  };

  unsigned long long Clock() { return CNTCV; };
  void advanceClock(unsigned long long clock_advance_interval = 1);

  unsigned long long ElapsedTime() { return CNTCV - CNTCV_prev; };

  void setClock(unsigned long long _clock) {
     CNTCV = _clock;
  };

  int Read(unsigned long long PA,unsigned char *buffer,int access_size);
  int Write(unsigned long long PA,unsigned char *buffer,int access_size);

  // (memory-mapped system counter module) register offsets from memory base address:

  enum { _CNTCR=0x0, _CNTSR=0x4, _CNTCV_LO=0x8, _CNTCV_HI=0xc, _CNTFID0=0x20, _CNTFIDn=0x24,
	 _CounterID=0xfd0, COUNTER_RESERVED=-1
       };
  
  int register_index(unsigned long long PA);

 protected:
  int Read(unsigned long long PA,unsigned int *rval);
  int Write(unsigned long long PA,unsigned int rval);

 private:
  unsigned int CNTCR;
  unsigned int CNTSR;
  
  unsigned long long CNTCV;
  unsigned long long CNTCV_prev;

  unsigned int CNTFID0;
};

#define __SYSTEM_COUNTER_MODULE__
#endif
