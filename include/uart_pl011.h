#ifndef __UART_PL011__

#include <string>
#include "memmap_device.h"
#include "uart.h"

class UART_pl011 : public uart, public memmap_device {
 public:
  UART_pl011() : clock(0), clock_advance_interval(10000) {
    Reset();
  };

  std::string Name() { return std::string("UART/PL011"); };
  std::string RegisterName(unsigned long long PA);

  // reset - reset uart registers to default values...  
  void Reset() {
    uart::Reset();
    
    UARTDR = 0;
    UARTRSR = 0;
    UARTFR = 0x48;
    UARTILPR = 0;
    UARTIBRD = 0;
    UARTFBRD = 0;
    UARTLCR_H = 0;
    UARTTCR = 0x300;
    UARTIFLS = 0x12;
    UARTIMSC = 0;
    UARTRIS = 0;
    UARTMIS = 0;
    UARTDMACR = 0;
    UARTPeriphID0 = 0x11;
    UARTPeriphID1 = 0x10;
    UARTPeriphID2 = 0x24;
    UARTPeriphID3 = 0x00;
    UARTCellID0 = 0x0d;
    UARTCellID1 = 0xf0;
    UARTCellID2 = 0x05;
    UARTCellID3 = 0xb1;

    clock = 0;
    clock_advance_interval = 10000;
  };

  unsigned long long Clock() { return clock; };
  void advanceClock() { clock += clock_advance_interval; };

  void setClock(unsigned long long _clock, unsigned long long _clock_advance_interval) {
        clock = _clock;
        clock_advance_interval = _clock_advance_interval;
  };

  void ServiceIOs() { Transmit(); Receive(); };
  
  int Read(unsigned long long PA,unsigned char *buffer,int access_size);
  int Write(unsigned long long PA,unsigned char *buffer,int access_size);

  enum UART_SUPPORTED_INTERRUPTS { UART_OVERRUN=1, UART_TRANSMIT=2, UART_RECEIVE=4 };
  
  bool InterruptPending(int &pending_interrupts);
  
  // (memory-mapped uart) register offsets from uart memory base address:

  enum { DR=0x0, RSR=0x4, FR=0x18, ILPR=0x20, IBRD=0x24, FBRD=0x28, LCR_H=0x2c, TCR=0x30,
	 IFLS=0x34, IMSC=0x38, TRIS=0x3c, TMIS=0x40, TICR=0x44, TDMACR=0x48,
	 PID0=0xfe0,PID1=0xfe4,PID2=0xfe8,PID3=0xfec,
	 CID0=0xff0,CID1=0xff4,CID2=0xff8,CID3=0xffc,
	 UART_RESERVED=-1
       };
  
  int register_index(unsigned long long PA);

 protected:
  int Read(unsigned long long PA,unsigned int *rval);
  int Write(unsigned long long PA,unsigned int rval);

  bool UART_busy() { return false; };
  
  bool RI()  { return true; }; // ring indicator
  bool DCD() { return true; }; // data carrier detect
  bool DSR() { return true; }; // data set ready
  bool CTS() { return true; }; // clear to send

  // overrun is set or cleared (from base uart class) to reflect receive fifo full state
  
  void SetOverrun(bool overrun) {
  // update receive status register overrun (OE) bit...
    if (overrun) {
      UARTRSR |= 0x8;    // set UARTRSR.OE,
      UARTRIS |= 0x400;  //     UARTRIS.OERIS
    } else {
      UARTRSR &= ~0x8;   // clear UARTRSR.OE,
      UARTRIS &= ~0x400; //     UARTRIS.OERIS
    }
  };

  void SetTransmitInterrupt() {
    printf("TRANSMIT INTERRUPT!\n");
  };
  void SetReceiveInterrupt() {
    printf("RECEIVE INTERRUPT\n");
  };

  bool overrun_interrupt_set() { return (UARTRIS & 0x400) != 0; };

  // transmit/receive interrupt 'raw' state are set until manually cleared...
  void set_receive_interrupt()  { UARTRIS |= 0x10; };
  bool receive_interrupt_set()  { return (UARTRIS & 0x10) != 0; };
  
  void set_transmit_interrupt() { UARTRIS |= 0x20; };
  bool transmit_interrupt_set() { return (UARTRIS & 0x20) != 0; };

  // an interrupt is 'enabled' if it is NOT masked...
  bool overrun_interrupts_enabled()  { return (UARTIMSC & 0x400) == 0; };  // 
  bool transmit_interrupts_enabled() { return (UARTIMSC & 0x020) == 0; };  // these are the only uart 
  bool receive_interrupts_enabled()  { return (UARTIMSC & 0x010) == 0; };  //   interrupts supported

  int receive_int_FIFO_level()  { return (UARTIFLS >> 3) & 0x7; };  // RXIFLSEL
  int transmit_int_FIFO_level() { return UARTIFLS & 0x7;        };  // TXIFLSEL

 private:
  unsigned int UARTDR;
  unsigned int UARTRSR;   // is UARTECR too
  unsigned int UARTFR;
  unsigned int UARTILPR;
  unsigned int UARTIBRD;
  unsigned int UARTFBRD;
  unsigned int UARTLCR_H;
  unsigned int UARTTCR;
  unsigned int UARTIFLS;
  unsigned int UARTIMSC;   // interrupt mask set/clear - used to mask 'raw' interrupts - read/write
  unsigned int UARTRIS;    // raw interrupt status register - raw (unmasked) interrupt state - read-only
  unsigned int UARTMIS;    // masked interrupt status register = UARTRIS & UARTIMSC - read-only
  //unsigned int UARTICR;     // write-only. accessed only to update bits in UARTRIS
  unsigned int UARTDMACR;
  unsigned int UARTPeriphID0; //
  unsigned int UARTPeriphID1; //
  unsigned int UARTPeriphID2; // read-only.
  unsigned int UARTPeriphID3; //
  unsigned int UARTCellID0;   //
  unsigned int UARTCellID1;   //
  unsigned int UARTCellID2;   //
  unsigned int UARTCellID3;   //

  unsigned long long clock;
  unsigned long long clock_advance_interval;
};

#define __UART_PL011__
#endif
