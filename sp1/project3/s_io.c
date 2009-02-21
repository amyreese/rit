/**
 * Serial I/O Library
 * Manages basic input and output functionality for the serial terminal, as
 * well as initialization routines for the local serial ports.
 *
 * @author John Reese
 * @author Adam Risi
 */

#include "uart.h"
#include "startup.h"
#include "support.h"
#include "s_io.h"

/*
 * Global Variables 
 */
char input_buffer[80] = {0};
char output_buffer[80] = {0};
int output_index = 0;
int read_characters = 0;

unsigned int S_IO_DONE = 0;
char next_output_char = '\0';

/**
 * Initialize the serial I/O controller.
 */
void s_io_init() {
  __outb(UA4_FIFO_CTL, 0);
  __outb(UA4_FIFO_CTL, UA5_FCR_FIFO_EN);
  __outb(UA4_FIFO_CTL, UA5_FCR_FIFO_EN | UA5_FCR_RXSR);
  __outb(UA4_FIFO_CTL, UA5_FCR_FIFO_EN | UA5_FCR_RXSR | UA5_FCR_TXSR);

  /* turn off the enable bits in the Interrupt Enable Register (IER) for all interrupts */
  __outb(UA4_IER, !(UA4_IER_RX_INT_ENABLE | UA4_IER_TX_INT_ENABLE | UA4_IER_LINE_STATUS_INT_ENABLE | UA4_IER_MODEM_STATUS_INT_ENABLE));
  
  /* set the data rate in bank 1 to 9600 */
  __outb(UA4_BANK_SELECT, UA4_LCR_BANK1);
  __outb(UA4_LBGD_L, BAUD_LOW_BYTE(BAUD_9600));
  __outb(UA4_LBGD_H, BAUD_HIGH_BYTE(BAUD_9600));

  /* set the character format in bank 0 */
  __outb(UA4_LCR, UA4_LCR_BANK0 | UA4_LCR_BITS_8 | UA4_LCR_1_STOP_BIT | UA4_LCR_NO_PARITY);

  /* set up FCR to interrupt on 1 character */
  __outb(UA4_FCR, UA5_FCR_TX_FIFO_1 | UA5_FCR_RX_FIFO_1);

  /* turn on ISEN DTR and RTS in the modem control register */
  __outb(UA4_MCR, UA4_MCR_ISEN | UA4_MCR_DTR | UA4_MCR_RTS);
  
}

void s_putchar( char ch ) {
  /* if this is a newline, send a carriage return first */
  if(ch == '\n') {
    s_putchar('\r');
  }
  
  /* move this character into the output buffer and null terminate it */
  output_buffer[0] = ch;
  output_buffer[1] = '\0';
  output_index = 0;

  /* enable TX interrupt */
  __outb(UA4_IER, UA4_IER_TX_INT_ENABLE);

  /* wait for the output index to be equal to 1 */
  while(output_index < 1)
    ;

  /* disable TX interrupt */
  char interrupts = __inb(UA4_IER);
  __outb(UA4_IER, interrupts & !(UA4_IER_TX_INT_ENABLE));

}

unsigned int s_getchar( void ) {
  read_characters = 0;
  
  /* enable char RX */
  __outb(UA4_IER, UA4_IER_RX_INT_ENABLE);

  /* wait for read_characters to be 1 */
  while(read_characters < 1)
    ;

  /* disable RX */
  char interrupts = __inb(UA4_IER);
  __outb(UA4_IER, interrupts & !(UA4_IER_RX_INT_ENABLE));
  
  return (unsigned int)*input_buffer;
}

void s_puts(char *str) {
  for(;*str!='\0';str++) {
    s_putchar(*str);
  }
}

char *s_gets( void ) {
  read_characters = 0;
  S_IO_DONE = 0;

  /* enable the serial interrupt */


  /* S_IO_DONE is set by the ISR when read_characters is 80 or a \n or \r is read */
  while(!S_IO_DONE)
    ;

  /* disable the interrupt */


  return input_buffer;
}

