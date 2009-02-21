/**
 * Interrupt Service Routines
 *
 * @autho John Reese
 * @author Adam Risi
 */

#ifndef __ISR_H__
#define __ISR_H__

/**
 * Timer interrupt service routine.
 */
void isr_timer( int vector, int code );

/**
 * Serial I/O interrupt service routine.
 */
void isr_serial( int vector, int code );

/**
 * Register all needed ISR vectors, then enable interrupts.
 */
void isr_register_all( void );

#endif // __ISR_H__

