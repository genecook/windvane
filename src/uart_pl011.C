#include "uart_pl011.h"

#define PL011_DEBUG 1

//-------------------------------------------------------------------------------------------
// return index to valid uart register...
//-------------------------------------------------------------------------------------------
int UART_pl011::register_index(unsigned long long PA) {
  int reg_index = UART_RESERVED;
  
  switch( (int) (PA & 0xfff) ) {
    case 0x000: reg_index = DR;     break;
    case 0x004: reg_index = RSR;    break;
    case 0x018: reg_index = FR;     break;
    case 0x020: reg_index = ILPR;   break;
    case 0x024: reg_index = IBRD;   break;
    case 0x028: reg_index = FBRD;   break;
    case 0x02c: reg_index = LCR_H;  break;
    case 0x030: reg_index = TCR;    break;
    case 0x034: reg_index = IFLS;   break;
    case 0x038: reg_index = IMSC;   break;
    case 0x03c: reg_index = TRIS;   break;
    case 0x040: reg_index = TMIS;   break;
    case 0x044: reg_index = TICR;   break;
    case 0x048: reg_index = TDMACR; break;
    case 0xfe0: reg_index = PID0;   break;
    case 0xfe4: reg_index = PID1;   break;
    case 0xfe8: reg_index = PID2;   break;
    case 0xfec: reg_index = PID3;   break;
    case 0xff0: reg_index = CID0;   break;
    case 0xff4: reg_index = CID1;   break;
    case 0xff8: reg_index = CID2;   break;
    case 0xffc: reg_index = CID3;   break;
    default: // either access to reserved uart address, or misaligned address...
             break;
  }

#ifdef PL011_DEBUG
  printf("[UART_pl011::register_index] index: 0x%x\n",reg_index);
#endif
  
  return reg_index;
}

std::string UART_pl011::RegisterName(unsigned long long PA) {
  std::string rn = "?";

  switch(register_index(PA)) {
    case DR:     rn = "UART_DR";     break;
    case RSR:    rn = "UART_RSR";    break;
    case FR:     rn = "UART_FR";     break;
    case ILPR:   rn = "UART_ILPR";   break;
    case IBRD:   rn = "UART_IBRD";   break;
    case FBRD:   rn = "UART_FBRD";   break;
    case LCR_H:  rn = "UART_LCR_H";  break;
    case TCR:    rn = "UART_TCR";    break;
    case IFLS:   rn = "UART_IFLS";   break;
    case IMSC:   rn = "UART_IMSC";   break;
    case TRIS:   rn = "UART_TRIS";   break;
    case TMIS:   rn = "UART_TMIS";   break;
    case TICR:   rn = "UART_TICR";   break;
    case TDMACR: rn = "UART_TDMACR"; break;
    case PID0:   rn = "UART_PID0";   break;
    case PID1:   rn = "UART_PID1";   break;
    case PID2:   rn = "UART_PID2";   break;
    case PID3:   rn = "UART_PID3";   break;
    case CID0:   rn = "UART_CID0";   break;
    case CID1:   rn = "UART_CID1";   break;
    case CID2:   rn = "UART_CID2";   break;
    case CID3:   rn = "UART_CID3";   break;
    default: // either access to reserved uart address, or misaligned address...
             break;
  }

  return rn;
}

//-------------------------------------------------------------------------------------------
// read from memory-mapped uart register...
//-------------------------------------------------------------------------------------------

// for now, only handle word (32 bit) aligned access...

int UART_pl011::Read(unsigned long long PA,unsigned char *buffer,int access_size) {
#ifdef PL011_DEBUG
  printf("[UART_pl011::Read] entered, PA: 0x%llx, size: %d\n",PA,access_size);
#endif
  
  if (access_size != 4)
    return -1;

  int rcode = Read(PA,(unsigned int *) buffer);
#ifdef PL011_DEBUG
  printf("[UART_pl011::Read] exited, rcode: 0x%x\n",rcode);
#endif

  return rcode;
}


int UART_pl011::Read(unsigned long long PA,unsigned int *rval) {
  int rcode = 0;

  *rval = 0;

  
  switch( register_index(PA) ) {
    case DR:   GetChar(rval);
               break;
	       
    case RSR:  // receive status register should be up to date...
               *rval = UARTRSR;
               break;
      
    case FR:   // update anytime accessed...
               UARTFR |= (RI()<<8) | (Transmit_empty()<<7) | (Receive_full()<<6) | (Transmit_full()<<5) 
		 | (Receive_empty()<<4) | (UART_busy()<<3) | (DCD()<<2) | (DSR()<<1) | CTS();
	       *rval = UARTFR;
               break;
	       
    case ILPR: *rval = UARTILPR;
               break;
	       
    case IBRD: *rval = IBRD;
               break;
	       
    case FBRD: *rval = FBRD;
               break;
	       
    case LCR_H: *rval = UARTLCR_H;
                break;
		
    case TCR: *rval = UARTTCR;
              break;
	      
    case IFLS: *rval = UARTIFLS;
               break;
	       
    case IMSC: *rval = UARTIMSC; break;
    case TRIS: *rval = UARTRIS; break;
    case TMIS: break;
    case TICR: break;
    case TDMACR: break;

    case PID0: *rval = UARTPeriphID0; break;
    case PID1: *rval = UARTPeriphID1; break;
    case PID2: *rval = UARTPeriphID2; break;
    case PID3: *rval = UARTPeriphID3; break;
    case CID0: *rval = UARTCellID0;   break;
    case CID1: *rval = UARTCellID1;   break;
    case CID2: *rval = UARTCellID2;   break;
    case CID3: *rval = UARTCellID3;   break;

    default: // either access to reserved uart address, or misaligned address...
             rcode = -1;
             break;
  }
  
  return rcode;
}

//-------------------------------------------------------------------------------------------
// write to memory-mapped uart register...
//-------------------------------------------------------------------------------------------

int UART_pl011::Write(unsigned long long PA,unsigned char *buffer,int access_size) {
#ifdef PL011_DEBUG
  printf("[UART_pl011::Write] entered, PA: 0x%llx, size: %d\n",PA,access_size);
#endif
  
  if (access_size != 4)
    return -1;

  int rcode = Write(PA,*( (unsigned int *) buffer));

#ifdef PL011_DEBUG
  printf("[UART_pl011::Write] exited, rcode: 0x%x\n",rcode);
#endif

  return rcode;
}

int UART_pl011::Write(unsigned long long PA,unsigned int rval) {
  
  int rcode = 0;

  switch( register_index(PA) ) {
    case DR:           PutChar(rval);
                       break;
    case RSR:          UARTRSR = 0;
                       break;
    case FR:           // Flag register assumed to be read-only...
                       break;
    case ILPR:         UARTILPR = rval & 0xff;
                       break;  
    case IBRD:         UARTIBRD = rval & 0xffff;
                       break;
    case FBRD:         UARTFBRD = rval & 0x1f;
                       break;
    case LCR_H:        UARTLCR_H = rval & 0xff;
#ifdef PL011_DEBUG
                       printf("[UART_pl011::Write] UARTLCR_H = 0x%x\n",UARTLCR_H);
#endif
		       {
			 bool FEN = ( (UARTLCR_H>>4) & 1 ) == 1;
#ifdef PL011_DEBUG
                         printf("[UART_pl011::Write] FIFOs enabled? %d\n",FEN);
#endif
                         SetFIFOenable(FEN);
                       }
                       break;
    case TCR:          UARTTCR = rval & 0xffff;
                       break;
    case IFLS:         UARTIFLS = rval & 0x3f;
                       {
                        int receive_threshhold_select  = (UARTIFLS>>3) & 0x7;
                        int transmit_threshhold_select = UARTIFLS & 0x7;
		        SelectThreshhold(receive_threshhold_select, transmit_threshhold_select);
                       }
                       break;
    case IMSC:         UARTIMSC = rval & 0x7ff;
                       break;
    case TRIS:         // read-only...
                       break;
    case TMIS:         // read-only...
                       break;
    case TICR:         // write to Interrupt Clear 'register' clears interrupt bits
                       // in Raw Interrupt status register...
                       UARTRIS = rval & 0x7ff;
                       break;
    case TDMACR:       UARTDMACR = rval & 0x3;
                       break;
    case PID0:
    case PID1:
    case PID2:
    case PID3:
    case CID0:
    case CID1:
    case CID2:
    case CID3:         // uart ID registers are read-only...
                       break;
  
    default: // either access to reserved uart address, or misaligned address...
             rcode = -1;
             break;
  }
  
  printf("[UART_pl011::Write] exited, rcode: %d\n",rcode);
  
  return rcode;
}

//-------------------------------------------------------------------------------------------
// return indicator that one or more uart interrupts are pending, and which ones...
//-------------------------------------------------------------------------------------------

bool UART_pl011::InterruptPending(int &pending_interrupts) {
  pending_interrupts = 0;

  if (overrun_interrupts_enabled() && overrun_interrupt_set()) {
    pending_interrupts |= UART_OVERRUN;
#ifdef PL011_DEBUG
  printf("[UART_pl011::InterruptPending] UART_OVERRUN\n");
#endif
  }
  
  if (transmit_interrupts_enabled() && transmit_interrupt_set()) {
    pending_interrupts |= UART_TRANSMIT;
#ifdef PL011_DEBUG
  printf("[UART_pl011::InterruptPending] UART_TRANSMIT\n");
#endif
  }

  if (receive_interrupts_enabled() && receive_interrupt_set()) {
    pending_interrupts |= UART_RECEIVE;
#ifdef PL011_DEBUG
  printf("[UART_pl011::InterruptPending] UART_RECEIVE\n");
#endif
  }
  
  return pending_interrupts != 0;
}
