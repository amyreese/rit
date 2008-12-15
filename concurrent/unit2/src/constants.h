#include <stdlib.h>
#include <time.h>

/**
 * Allocator / Client constants
 * @author John Reese
 * @author Stephen Wright
 */

#define POOLSIZE	8
#define NCLIENTS	2

#define REQUEST_MAX	3

#ifndef __RAND_INT__
#define __RAND_INT__

int randint( int bottom, int top );

#endif
