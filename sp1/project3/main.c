/**
 * SP1 Project 3
 * Create a timed-response game accross serial I/O with an ADDS terminal.
 *
 * @author John Reese
 * @author Adam Risi
 */

#include "isr.h"
#include "c_io.h"
#include "support.h"

/**
 * Intialize the program and handle main event flow.
 */
int main( void ) {
	c_puts( "Starting Project 3...\n" );

	// Enable timer and serial controller interrupts
	isr_register_all();

	// Start the game
	game_run();

	c_puts( "Project 3 ended...\n" );
	return( 0 );
}

