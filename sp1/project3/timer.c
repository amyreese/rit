/**
 * Timer Library
 * Functions to handle basic timer usage.
 *
 * @author John Reese
 * @author Adam Risi
 */

#include "helper.h"
#include "timer.h"

/**
 * Initialize the timer.
 */
void timer_init( void ) {
	// Initialize timer gobals
	timer_running = FALSE;
	timer_tick_count = 0;
}

/**
 * Reset the timer count to a given value, or zero.
 */
void timer_reset( int count=0 ) {
	// Stop the timer
	if ( timer_running ) {
		timer_stop();
	}

	// Set the timer counter
	timer_tick_count = count;
}

/**
 * Start the timer.
 */
void timer_start( void ) {
	timer_running = true;
}

/**
 * Stop the timer
 */
void timer_stop( void ) {
	timer_running = false;
}

/**
 * Get the timer's current count.
 */
int timer_count( void ) {
	return timer_tick_count;
}


