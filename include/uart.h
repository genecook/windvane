#ifndef __UART__

#include <queue>
#include <stdio.h>
#include <stdlib.h>

//-------------------------------------------------------------------------------------
// uart queue...
//-------------------------------------------------------------------------------------

class uart_queue {
 public:
   uart_queue() { Reset(); };
  
   const unsigned int configured_size = 16; // this uart fifo is really for the pl011 uart,
                                            //   thus the fixed size and threshholds...
   
   void Reset() {
     while(!fifo.empty())
       fifo.pop();
     
     threshhold = configured_size;
     fifo_enabled = false;
     holding_register_primed = false;
     holding_register = 0;
   };

   void SetFIFOenable(bool _enable) { fifo_enabled = _enable; }; 
   bool FIFO_enabled() { return fifo_enabled; };

   void SelectThreshhold(int threshhold_select) {
     threshhold = configured_size;
     switch(threshhold_select) {
       case 0: threshhold = 2;   break; // 1/8 full
       case 1: threshhold = 4;   break; // 1/4  "
       case 2: threshhold = 8;   break; // 1/2  "
       case 3: threshhold = 12;  break; // 3/4  "
       case 4: threshhold = 14;  break; // 7/8  "
       default: break;
     }     
   }

   unsigned int Threshhold() { return threshhold; };

   bool BelowThreshhold() { // check after removing char from queue...
     return FIFO_enabled() ? fifo.size() <= Threshhold() : holding_register_empty();
   }
   
   bool AboveThreshhold() { // check after adding char to queue...
     return FIFO_enabled() ? fifo.size() >= Threshhold() : holding_register_full();
   };

   // Full - either the fifo is full, or the holding register...
   
   bool Full() {
     return FIFO_enabled() ? (fifo.size() >= configured_size) : holding_register_full();
   };
   
   // Empty - either the fifo is empty, or the holding register...
   
   bool Empty() {
     return FIFO_enabled() ? fifo.empty() : holding_register_empty();
   };
   
   // 'get' next char either from the FIFO, or from the holding register...
   //
   // return true if a received character was available
   
   bool GetChar(unsigned int *rv) {
     if (FIFO_enabled()) {
       unsigned char sc = 0;
       bool have_char = get_fifo_char(sc);
       *rv = (unsigned int) sc;
       return have_char;
     }
     
     if (holding_register_empty())
       return false; // no receive character available...

     // take receive character from holding buffer...
     unsigned char sc = flush_holding_register();
     *rv = (unsigned int) sc;
     return true;
   };

   // put 'next' char if there is room in the transmit queue...

   bool PutChar(unsigned char sc) {
     printf("[PutChar] FIFO enabled? %d\n",FIFO_enabled());
     if (FIFO_enabled())
       return put_fifo_char(sc);

     // if FIFO is disabled, then stuff the character into the holding register...

     prime_holding_buffer(sc);
     return true;
   };
   
 private:
   // return fifo front, remove same; return 'true' if successful, ie, if fifo is NOT empty...
   
   bool get_fifo_char(unsigned char &sc) {     
     if (fifo.empty())
       return false;
     
     sc = fifo.front();
     fifo.pop();
     
     return true;
   };
   
   // add char to fifo back; return 'true' if successful, ie, if was able to add the new char...
   
   bool put_fifo_char(unsigned char sc) {
     if ( fifo.size() >= configured_size )
       return false;
     
     fifo.push(sc);

     return true;
   };

   bool holding_register_full() { return holding_register_primed; };
   bool holding_register_empty() { return !holding_register_primed; };

   void prime_holding_buffer(unsigned char sc) {
     holding_register = sc;
     holding_register_primed = true;
   }
   
   unsigned char flush_holding_register() {
     holding_register_primed = false;
     return holding_register;
   };

   std::queue<unsigned char> fifo;
   unsigned int threshhold;
   bool fifo_enabled;
   bool holding_register_primed;
   unsigned int holding_register;
};


//-------------------------------------------------------------------------------------
// Base UART model has a transmit and receive queue...
//-------------------------------------------------------------------------------------

class uart {
 public:
   uart() { Reset(); };
   virtual ~uart() {};

   virtual void Reset() {
     transmit_queue.Reset();
     receive_queue.Reset();
   };

   // default transmit/receive methods that use stdin/stdout are provided...
   
   virtual void Transmit();
   virtual void Receive();

   // sub-class deals with transmit/receive, overrun...
   
   virtual void SetTransmitInterrupt() { };
   virtual void SetReceiveInterrupt() { };
   virtual void SetOverrun(bool new_overrun_state) { };

   bool Transmit_empty() { return transmit_queue.Empty(); };
   bool Transmit_full()  { return transmit_queue.Full();  };
   
   bool Receive_full()   { return receive_queue.Full();   };
   bool Receive_empty()  { return receive_queue.Empty();  };

   bool GetChar(unsigned int *rv) { return receive_queue.GetChar(rv); };
   bool PutChar(unsigned char sc) { return transmit_queue.PutChar(sc); };

   void SetFIFOenable(bool _enable) {
     receive_queue.SetFIFOenable(_enable);
     transmit_queue.SetFIFOenable(_enable);
   }; 

   void SelectThreshhold(int rcv_threshhold_select,int tx_threshhold_select) {
     receive_queue.SelectThreshhold(rcv_threshhold_select);
     transmit_queue.SelectThreshhold(tx_threshhold_select);
   };

 protected:
   uart_queue transmit_queue;
   uart_queue receive_queue;

 private:
   bool input_chars_available(void);
};

#define __UART__
#endif
