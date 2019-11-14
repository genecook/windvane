#include <stdio.h>
#include <stdlib.h>
#include <time.h> /* struct timeval for select() */
#include <unistd.h> /* select() */
#include <poll.h> /* poll() */
#include <sys/ioctl.h> /* FIONREAD ioctl() */
#include <termios.h> /* tcgetattr() and tcsetattr() */
#include <fcntl.h> /* fnctl() */
#include <termios.h>

#include "uart.h"

//#define UART_DEBUG 1

#define UNBUFFERED 1

//--------------------------------------------------------------------------------
// Transmit - write to stdout one char from transmit queue.
//
//  Set transmit-interrupt if transmit queue size falls below its threshhold.
//
// NOTE: We ASSUME stdout is always ready.
//--------------------------------------------------------------------------------

void uart::Transmit() {
#ifdef UART_DEBUG
  printf("[uart::Transmit] entered...\n");
#endif
  unsigned int nc = 0;
    
  if (transmit_queue.GetChar(&nc)) {
#ifdef UART_DEBUG
    printf("[uart::Transmit] next char to transmit: '%c'\n",nc);
#endif
    putchar(nc); // we ASSUME stdout is always ready...
    fflush(stdout);
    if (transmit_queue.BelowThreshhold()) {
#ifdef UART_DEBUG
      printf("[uart::Transmit] set transmit interrupt...\n");
#endif
      SetTransmitInterrupt();
    }
  }
}

//--------------------------------------------------------------------------------
// Receive - read from (unbuffered) stdin one char, append to receive queue.
//
// Set receive-interrupt if receive queue size reaches its threshhold.
//--------------------------------------------------------------------------------


void uart::Receive() {
#ifdef UART_DEBUG
  printf("[uart::Receive] entered...\n");
#endif
  
  if (receive_queue.Full()) {
#ifdef UART_DEBUG
    printf("   receive queue is full. set overrun...\n");
#endif
    SetOverrun(true);
#ifdef UART_DEBUG
  printf("[uart::Receive] exited.\n");
#endif
    return;
  }

  SetOverrun(false);

#ifdef UART_DEBUG
  printf("   there is room in the queue so no overrun...\n");
#endif

#ifdef UART_DEBUG
  printf("  setup unbuffered state...\n");
#endif

  
#ifdef UNBUFFERED
  struct termios old_tio, new_tio;

  /* get the terminal settings for stdin */
  tcgetattr(STDIN_FILENO,&old_tio);

  /* we want to keep the old setting to restore them at the end */
  new_tio=old_tio;

  /* disable canonical mode (buffered i/o) and local echo */
  //new_tio.c_lflag &=(~ICANON & ~ECHO);
  new_tio.c_lflag &=(~ICANON);

  /* set the new settings immediately */
  tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
#endif

  
  if ( input_chars_available() ) {
#ifdef UART_DEBUG
    printf("  get next (unbuffered) input char, queue it up...\n");
#endif
    unsigned char nc = getchar();
//#ifdef UART_DEBUG
    //printf("  char read: '%c' (0x%x)\n", nc, nc);
//#endif
    receive_queue.PutChar(nc);
    if (receive_queue.AboveThreshhold()) {
#ifdef UART_DEBUG
        printf("  receive queue above threshhold...\n");
#endif
        SetReceiveInterrupt();
    }
  } else {
#ifdef UART_DEBUG
    printf("  no char available...\n");
#endif
  }

#ifdef UNBUFFERED
  /* restore the former settings */
  tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
#endif

#ifdef UART_DEBUG
  printf("[uart::Receive] exited.\n");
#endif
}

//--------------------------------------------------------------------------------
// checks if stdin has input available...
//--------------------------------------------------------------------------------

bool uart::input_chars_available(void) {
    fd_set rd;
    struct timeval tv={0};
    int ret;

    FD_ZERO(&rd);
    FD_SET(STDIN_FILENO, &rd);
    
    ret = select(1, &rd, NULL, NULL, &tv);

    return (ret>0);
}

