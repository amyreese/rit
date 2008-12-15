#include <stdio.h>

#include "constants.h"
#include "Thread.h"
#include "Allocator.h"
#include "Client.h"

/**
 * Start up an allocator and some clients.
 */

int main( int argc, char* argv[] ) {
	srand( time( NULL ) );

	Allocator a = Allocator( POOLSIZE, NCLIENTS );
	a.start();

	a.join();
}

/**
 * Get a random integer between two numbers (inclusive).
 * @param bottom
 * @param top
 * @return random integer
 */
int randint( int bottom, int top ) {
	int range = top - bottom + 1;
	int value = (rand() % range) + bottom;
	return value;
}


