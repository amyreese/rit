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
#include "x86arch.h"

/**
 * Timer interrupt service routine.
 */
void isr_timer( int vector, int code ) {
	c_puts( "Timer interrupt\n" );

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

	interrupts_on();
}


