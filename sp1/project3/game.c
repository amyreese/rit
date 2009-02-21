/**
 * Timed Response Game
 *
 * @author John Reese
 * @author Adam Risi
 */

#include "game.h"

/**
 * Entry point into the game's main processing sequence.
 */
void game_run( void ) {
	c_puts( "Starting game...\n" );

	// Intro banner
	s_puts( "Timed Response Game\n\nJohn Reese (jmr8223)\nAdam Risi (ajr7708)\n\n" );

	// Seed the RNG
	game_seed_rng();

	// Keep playing a round until the user is done
	int repeat;
	do {
	} while ( repeat );

	c_puts( "Game completed.\n" );
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

