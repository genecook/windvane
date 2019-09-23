#include "system_counter_module.h"

//#define SC_DEBUG 1

//-------------------------------------------------------------------------------------------
// return index to supported system counter register...
//-------------------------------------------------------------------------------------------
int SystemCounterModule::register_index(unsigned long long PA) {
  int reg_index = COUNTER_RESERVED;

  unsigned long long offset = PA & 0xfff;

  if ( (offset >= 0x24) && (offset <= 0x40c) ) {
    reg_index = _CNTFIDn;
  } else if ( (offset >= 0xfd0) && (offset <= 0xffc) ) {
    reg_index = _CounterID;
  } else switch( (int) offset ) {
      case 0x000: reg_index = _CNTCR;       break;
      case 0x004: reg_index = _CNTSR;       break;
      case 0x008: reg_index = _CNTCV_LO;    break;
      case 0x00c: reg_index = _CNTCV_HI;    break;
      case 0x020: reg_index = _CNTFID0;     break;  // <--- system counter base frequency
      default: // either access to reserved system counter address, or misaligned address...
               break;
  }

#ifdef SC_DEBUG
  printf("[SystemCounterModule::register_index] index: 0x%x\n",reg_index);
#endif
  
  return reg_index;
}

std::string SystemCounterModule::RegisterName(unsigned long long PA) {
  std::string rn = "?";

  switch(register_index(PA)) {
    case _CNTCR:     rn = "CNTCR";         break;
    case _CNTSR:     rn = "CNTSR";         break;
    case _CNTCV_LO:  rn = "CNTCV[31:0]";   break;
    case _CNTCV_HI:  rn = "CNTCV[63:32]";  break;
    case _CNTFID0:   rn = "CNTFID0";       break;
    case _CNTFIDn:   rn = "CNTFIDn";       break;
    case _CounterID: rn = "_CounterID<n>"; break;
    default: // either access to reserved address, or misaligned address...
             break;
  }

  return rn;
}

//-------------------------------------------------------------------------------------------
// read from memory-mapped system counter register...
//-------------------------------------------------------------------------------------------

// for now, only handle word (32 bit) aligned access...

int SystemCounterModule::Read(unsigned long long PA,unsigned char *buffer,int access_size) {
#ifdef SC_DEBUG
  printf("[SystemCounterModule::Read] entered, PA: 0x%llx, size: %d\n",PA,access_size);
#endif
  
  if (access_size != 4)
    return -1;

  int rcode = Read(PA,(unsigned int *) buffer);
#ifdef SC_DEBUG
  printf("[SystemCounterModule::Read] exited, rcode: 0x%x\n",rcode);
#endif

  return rcode;
}


int SystemCounterModule::Read(unsigned long long PA,unsigned int *rval) {
  int rcode = 0;

  *rval = 0;

  switch( register_index(PA) ) {
    case _CNTCR:     *rval = CNTCR;              break;
    case _CNTSR:     *rval = CNTSR;              break;
    case _CNTCV_LO:  *rval = CNTCV & 0xffffffff; break;
    case _CNTCV_HI:  *rval = CNTCV >> 32;        break;
    case _CNTFID0:   *rval = CNTFID0;            break;
    case _CNTFIDn:   *rval = 0;                  break;
    case _CounterID: *rval = 0;                  break;
    default: rcode = -1; // either access to reserved address, or misaligned address...
             break;
  }
  
  return rcode;
}

//-------------------------------------------------------------------------------------------
// write to memory-mapped uart register...
//-------------------------------------------------------------------------------------------

int SystemCounterModule::Write(unsigned long long PA,unsigned char *buffer,int access_size) {
#ifdef SC_DEBUG
  printf("[SystemCounterModule::Write] entered, PA: 0x%llx, size: %d\n",PA,access_size);
#endif
  
  if (access_size != 4)
    return -1;

  int rcode = Write(PA,*( (unsigned int *) buffer));

#ifdef SC_DEBUG
  printf("[SystemCounterModule::Write] exited, rcode: 0x%x\n",rcode);
#endif

  return rcode;
}

int SystemCounterModule::Write(unsigned long long PA,unsigned int rval) {
  
  int rcode = 0;

  switch( register_index(PA) ) {
    case _CNTCR:     CNTCR   = rval; break;
    case _CNTSR:     CNTSR   = rval; break;
    case _CNTCV_LO:  CNTCV   = (CNTCV & 0xffffffff00000000) | rval; break;
    case _CNTCV_HI:  CNTCV   = (CNTCV & 0xffffffff) | (((unsigned long long)rval)<<32); break;
    case _CNTFID0:   CNTFID0 = rval; break;
    default: rcode = -1; // either access to read-only register, reserved address, or misaligned address...
             break;
  }

#ifdef SC_DEBUG
  printf("[SystemCounterModule::Write] %s = 0x%x\n",RegisterName(PA).c_str(),rval);
    
  printf("[SystemCounterModule::Write] exited, rcode: %d\n",rcode);
#endif
    
  return rcode;
}


void SystemCounterModule::advanceClock(unsigned long long clock_advance_interval) {
  CNTCV_prev = CNTCV;
  CNTCV += clock_advance_interval;

#ifdef SC_DEBUG
    printf("[SystemCounterModule::advanceClock] advance: 0x%llx, new clock val: 0x%llx, elapsed 'time': %lld\n",
	   clock_advance_interval,CNTCV,ElapsedTime());
#endif
};

