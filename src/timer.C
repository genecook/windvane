#include <math.h>
#include "a64sim.h"

// generic timer methods:

// 
// advance timers

//#define DEBUG_TIMER 1

//*************************************************************************************************************
//*************************************************************************************************************

// the master system clock is 1 Ghz...

#define MASTER_CLOCK_FREQUENCY 1000000000.0;

void State::AdvanceTimers(unsigned long long _clock_advance) {
  CNTPCT_EL0.Value( CNTPCT_EL0.Value() + _clock_advance);
  CNTVCT_EL0.Value( CNTVCT_EL0.Value() + _clock_advance);

  if (CNTFRQ_EL0.Value() > 0) {
    SetTimerClock(TimerClock() + 1);  // not really a clock. value 'rolls over' based on system counter and timer frequencies
  } else {
    // timer clock does not advance if no timer clock frequency...
  }

#ifdef DEBUG_TIMER
  printf("[Control::AdvanceTimers] physical/virtual clock: %llu, timer clock: %llu\n",_clock_advance,timer_clock);
#endif
}

//*************************************************************************************************************
//*************************************************************************************************************

bool Control::TimerTick() {
#ifdef DEBUG_TIMER
  printf("[Control::TimerTick] entered...\n");
#endif

  double master_clock_frequency = MASTER_CLOCK_FREQUENCY;

  unsigned long long timer_rollover_count = master_clock_frequency / cpu->CNTFRQ_EL0.Value();
  
#ifdef DEBUG_TIMER
  printf("[Control::TimerTick] master clock frequency: %g, timer frequency: %u\n",
	   master_clock_frequency, cpu->CNTFRQ_EL0.Value());

  printf("[Control::TimerTick] timer clock: %llu, rollover value: %llu\n", cpu->TimerClock(), timer_rollover_count );
#endif
  
  if (cpu->TimerClock() < timer_rollover_count) {
#ifdef DEBUG_TIMER
    printf("[Control::TimerTick] exited, NO timer event.\n");
#endif
    return false;
  }

  // if we got here, then the timer clock has 'ticked'...
  
  cpu->SetTimerClock(0);
  
  // 'tick' the physical timer, then the virtual timer...

  bool timer_event = false;

  if ((timer_event = _event_stream(cpu->CNTHCTL_EL2,cpu->CNTPCT_EL0) || _event_stream(cpu->CNTKCTL_EL1,cpu->CNTVCT_EL0))) {
      // wake this cpu, if sleeping...
    if (cpu->IsWaiting()) {
#ifdef DEBUG_TIMER
        printf("[Control::TimerTick] clearing wait state...\n");
#endif
	cpu->SetWakeup();
    }
  }
    
#ifdef DEBUG_TIMER
  printf("[Control::TimerTick] check physical timer...\n");
#endif

  TIMER_CNTOFF toff; // physical timer has no offset. fake it...
  
  if ((timer_event = _timer_tick(cpu->CNTP_CTL_EL0, cpu->CNTP_CVAL_EL0, cpu->CNTP_TVAL_EL0, cpu->CNTPCT_EL0, toff))) {
    cpu->CNTPS_CTL_EL1  = cpu->CNTP_CTL_EL0;   //
    cpu->CNTPS_CVAL_EL1 = cpu->CNTP_CVAL_EL0;  // update the 'secure' physical timer
    cpu->CNTPS_TVAL_EL1 = cpu->CNTP_TVAL_EL0;  // 
  }

#ifdef DEBUG_TIMER
  printf("[Control::TimerTick] check virtual timer...\n");
#endif

  timer_event |= _timer_tick(cpu->CNTV_CTL_EL0, cpu->CNTV_CVAL_EL0, cpu->CNTV_TVAL_EL0, cpu->CNTVCT_EL0, cpu->CNTVOFF_EL2);

#ifdef DEBUG_TIMER
  printf("[Control::TimerTick] exited, timer event? %d.\n", timer_event);
#endif
  return timer_event;
}

// WHAT ABOUT EVENT STREAMS???

//*************************************************************************************************************
//*************************************************************************************************************

bool Control::_event_stream(TIMER_CNTCTL &ctl, TIMER_CNT &counter) {
#ifdef DEBUG_TIMER
  printf("[Control::_event_stream] entered...\n");
#endif

  bool have_event = false;
  
  if (ctl.EVNTEN()) {
#ifdef DEBUG_TIMER
    printf("[Control::_event_stream] is enabled, bit-index: %u...\n",ctl.EVNTI());
#endif
    unsigned int bit_n = 1<<ctl.EVNTI();
#ifdef DEBUG_TIMER
    printf("[Control::_event_stream] bit N mask: 0x%x, counter value: 0x%llx, previous counter value: 0x%llx...\n",
	   bit_n,counter.Value(),counter.PreviousValue());
#endif
    if ( (counter.Value() - counter.PreviousValue()) > bit_n ) {
#ifdef DEBUG_TIMER
      printf("[Control::_event_stream] event is past due...\n");
#endif
      have_event = true; // if clock was advanced past event-stream bit, then the event is "past-due"...
    } else {
      // check for transition...
      bool previousBit = (counter.PreviousValue() & bit_n) != 0;
      bool sampleBit   = (counter.Value() & bit_n) != 0;
      bool leadingEdge = ctl.EVNTDIR() == 0;
      if (leadingEdge) {
	have_event = !previousBit && sampleBit;
      } else {
	have_event = previousBit && !sampleBit;
      }
#ifdef DEBUG_TIMER
      printf("[Control::_event_stream] previous-bit: %d, sample-bit: %d, leading-edge? %d, have-event? %d\n",
	     previousBit,sampleBit,leadingEdge,have_event);
#endif
      
    }
  }
  
#ifdef DEBUG_TIMER
  printf("[Control::_event_stream] exited, have-event? %d\n",have_event);
#endif
    
  return have_event;
}

//*************************************************************************************************************
//*************************************************************************************************************

bool Control::_timer_tick(TIMER_CTL &ctl, TIMER_CVAL &compare, TIMER_TVAL &timer, TIMER_CNT &counter, TIMER_CNTOFF &offset) {
  // tick, tick, tick...tock?

  // the timer-compare and timer-values are always updated...

#ifdef DEBUG_TIMER
  printf("[Control::timer_tick] 'up' counter compare-value: 0x%llx...\n", compare.Value());
#endif

  long tval = ((long) timer.Value()) - 1;  // timer value ('down' counter)
  timer.Value((unsigned long long) tval);  //   always decremented...

#ifdef DEBUG_TIMER
  printf("[Control::timer_tick] (updated 'down' counter) timer-value: %d...\n", timer.Value());
#endif

  
  // timer events checked only if timer is enabled...

  bool timer_is_enabled = false;
  
  if (ctl.ENABLE()) {
#ifdef DEBUG_TIMER
    timer_is_enabled = true;
    printf("[Control::timer_tick] this timer is enabled...\n");
#endif

  } else {
#ifdef DEBUG_TIMER
    printf("[Control::timer_tick] this timer is disabled...\n");
#endif
  }

  // check for event streams...

#ifdef DEBUG_TIMER
  printf("[Control::timer_tick] counter-value: 0x%llx, offset: 0x%llx, compare-value: 0x%llx\n",counter.Value(),offset.Value(),compare.Value());
#endif
    
  bool upcounter_event = (counter.Value() - offset.Value() - compare.Value()) >= 0;
  
  bool downcounter_event = timer.Value() <= 0;

#ifdef DEBUG_TIMER
  printf("[Control::timer_tick] up-counter event? %d, down-counter event? %d...\n",upcounter_event,downcounter_event);
#endif

  if (timer_is_enabled)
    ctl.ISTATUS( upcounter_event || downcounter_event ); // status bit set if event occurs

#ifdef DEBUG_TIMER
  printf("[Control::timer_tick] int-mask: %d, int-status: %d...\n",ctl.IMASK(),ctl.ISTATUS());
#endif

  bool do_assert = timer_is_enabled && !ctl.IMASK() && ctl.ISTATUS();  // assert only if enabled and output signal is not masked and if condition is asserted...
  
#ifdef DEBUG_TIMER
  printf("[Control::timer_tick] enabled? %d, interrupt? %d, interrupt-masked?: %d, assert? %d...\n",timer_is_enabled,ctl.ISTATUS(),ctl.IMASK(),do_assert);
#endif

  return do_assert;
}

