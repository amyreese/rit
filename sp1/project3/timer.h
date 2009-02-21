/**
 * Timer Library
 * Functions to handle basic timer usage.
 *
 * @author John Reese
 * @author Adam Risi
 */

#ifndef __TIMER_H__
#define __TIMER_H__

/**
 * The current timer tick count.
 */
extern nsigned int timer_tick_count;

/**
 * The timer is (or is not) running.
 */
extern int timer_running;

/**
 * Initialize the timer.
 */
void timer_init( void );

/**
 * Reset the timer count to a given value, or zero.
 */
void timer_reset( int count=0 );

/**
 * Start the timer.
 */
void timer_start( void );

/**
 * Stop the timer
 */
void timer_stop( void );

/**
 * Get the timer's current count.
 */
int timer_count( void );

#endif // __TIMER_H__

