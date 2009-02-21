/**
 * Timed Response Game
 *
 * @author John Reese
 * @author Adam Risi
 */

#include "c_io.h"
#include "game.h"
#include "helper.h"
#include "rngs.h"
#include "s_io.h"
#include "timer.h"

/**
 * Entry point into the game's main processing sequence.
 */
void game_run( void ) {
	c_puts( "Starting game...\n" );

	// Clear the screen
	int i;
	for ( i = 0; i < 24; i++ ) { s_puts( "\n" ); }

	// Intro banner
	s_puts( "Timed Response Game\n\nJohn Reese (jmr8223)\nAdam Risi (ajr7708)\n\n" );

	// Seed the RNG
	game_seed_rng();

	// Keep playing a round until the user is done
	int repeat;
	do {
		game_play_round();
	} while ( repeat );

	c_puts( "Game completed.\n" );
}

/**
 * Play a round of timed response.
 * Wait for the user to be ready, then display a character and time how long
 * it takes for the user to respond correctly.
 */
void game_play_round( void ) {
	int count;
	char input;
	char target;
	double random;

	// Random target character
	random = Random() * (double) 26.0;
	target = (char) ( (int) random ) + 'a';

	// Reset the timer
	timer_reset( 0 );

	// Prompt the user
	s_puts( "Press the enter key when you are ready" );

	// Wait for the user to press enter
	do {
		input = (char) s_getchar();
	} while ( input != '\n' );

	// DING!
	s_putchar( '\a' );

	// Show the target character
	s_putchar( target );

	// Turn on the timer
	timer_start();

	// Get user input
	do {
		input = (char) s_getchar();

		// Check for a match
		if ( input == target ) {
			break;

		// Wrong!
		} else {
			// DING!
			s_putchar( '\a' );
		}

	} while ( TRUE );

	// Turn off the timer
	timer_stop();

	// Results
	count = timer_count();
}

/**
 * Initialize and seed the random number generator.
 */
void game_seed_rng( void ) {
	int i;
	unsigned long x, y, z, seed;
	char input[12];

	// Output the user prompt
	s_puts( "Enter twelve-character seed: " );

	// Get 12 characters of input
	for ( i = 0; i < 12; i++ ) {
		input[i] = (char) s_getchar();
	}

	// Pull out 4 long words
	x = (unsigned long) input[0];
	y = (unsigned long) input[1];
	z = (unsigned long) input[2];

	c_printf( "Input values: %u %u %u\n", x, y, z );

	// XOR input words to create a seed value
	seed = x ^ y ^ z;

	c_printf( "Seed value: %u\n", seed );

	// Seed the RNG
	PutSeed( seed );
}

