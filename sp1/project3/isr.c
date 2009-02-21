/**
 * Interrupt Service Routines
 *
 * @author John Reese
 * @author Adam Risi
 */

#include "isr.h"
#include "s_io.h"
#include "c_io.h"
#include "helper.h"
#include "startup.h"
#include "support.h"
#include "timer.h"
#include "x86arch.h"

/**
 * Timer interrupt service routine.
 */
void isr_timer( int vector, int code ) {
	c_puts( "Tick\n" );

	// Increment the timer counter
	if ( timer_running ) {
		++timer_tick_count;
	}

	__outw( PIC_MASTER_CMD_PORT, PIC_EOI );
}

/**
 * Serial I/O interrupt service routine.
 */
void isr_serial( int vector, int code ) {
  char interrupts = __inb(UA4_EIR) & UA4_EIR_INT_PRI_MASK;
  if((interrupts & UA4_EIR_NO_INT_PENDING) != 0) {
  }

  if((interrupts & UA4_EIR_LINE_STATUS_INT_PENDING) != 0) {
  }

  /* if this interrupt trips, then there is a character waiting for us */
  if((interrupts & UA4_EIR_RX_INT_PENDING) != 0) {
    *input = __inb(UA4_RX_DATA) & 0x7f;
    read_characters = 1;
  }

  if((interrupts & UA5_EIR_RX_FIFO_TIMEOUT_INT_PENDING) != 0) {
    *input = __inb(UA4_RX_DATA) & 0x7f;
    read_characters = 1;
  }

  /* if this trips, then the transmit fifo is empty */
  if((interrupts & UA4_EIR_TX_INT_PENDING) != 0) {
    __outb(UA4_TXD, output_buffer[output_index]);
  }

  if((interrupts & UA4_EIR_MODEM_STATUS_INT_PENDING) != 0) {
  }
  
  __outw( PIC_MASTER_CMD_PORT, PIC_EOI );
}

/**
 * Register all needed ISR vectors, then enable interrupts.
 */
void isr_register_all( void ) {
	__install_isr( INT_VEC_TIMER, &isr_timer );

	s_io_init();
	__install_isr( INT_VEC_SERIAL_PORT_1, &isr_serial );

	interrupts_on();
}


