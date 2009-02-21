/**
 * Interrupt Service Routines
 *
 * @author John Reese
 * @author Adam Risi
 */

#include "isr.h"
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


