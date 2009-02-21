/**
 * PageSim
 * Page replacement simulation for FIFO and LRU algorithms.
 * Operating Systems I
 *
 * @author John Reese
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Max line size
#define LINE 100

// Max number of frames
#define MAX_FRAMES 20

// Algo types
#define FIFO 1
#define LRU 2

/**
 * Page frame structure, including frame count, current frame values, and last frame usage.
 */
typedef struct page_frames {
	int count;
	int value[MAX_FRAMES];
	int usage[MAX_FRAMES];
} page_frames;

/**
 * Create and initialize a new page frame structure.
 */
page_frames* pf_new( int count ) {
	page_frames* pf = malloc( sizeof( page_frames ) );
	pf->count = count;

	int i;
	for ( i = 0; i < MAX_FRAMES; i++ ) {
		pf->value[i] = -1;
		pf->usage[i] = -1;
	}

	return pf;
}

/**
 * Removes newline characters in place from the given string.
 */
void strmunge( char* string ) {
	int i;
	int len = strlen( string );

	for ( i = 0; i < len; i++ ) {
		string[i] = ( string[i] == '\n' ? '\0' : string[i] );
	}
}

/**
 * Converts the given C string in place to lowercase via the library tolower()
 */
void strtolower( char* string ) {
	int i;
	int len = strlen( string );

	for ( i = 0; i < len; i++ ) {
		string[i] = tolower( string[i] );
	}
}

/**
 * Prompt the user for the algorithm type.
 */
int get_algo( char* name ) {
	char input[LINE];
	char* status = NULL;

	int type = 0;

	while ( type == 0 ) {

		// Prompt the user
		printf( "Enter a page replacement algorithm (fifo or lru) >> " );
		status = fgets( input, LINE, stdin );

		do {

			// EOI
			if ( status == NULL ) {
				printf("\n");
				type = -1;
				break;
			}

			// Convert the string to lowercase and remove newlines
			strmunge( input );
			strncpy( name, input, 20 );
			strtolower( input );

			// User quit
			if ( strcmp( "q", input ) == 0 ) {
				type = -1;
				break;
			}


			// FIFO
			if ( strcmp( "fifo", input ) == 0 ) {
				type = FIFO;
			}

			// LRU
			if ( strcmp( "lru", input ) == 0 ) {
				type = LRU;
			}

			// Bad input
			if ( type == 0 ) {
				// Prompt the user
				printf( "*ERROR* Algorithm mut be lru or fifo >> " );
				status = fgets( input, LINE, stdin );
			}

		} while ( type == 0 );

	}

	return type;
}

/**
 * Prompt the user for the number of page frames.
 */
int get_frames() {
	char input[LINE];
	char* status = NULL;

	int count = 0;

	while ( count == 0 ) {

		// Prompt the user
		printf( "Enter the number of frames available >> " );
		status = fgets( input, LINE, stdin );

		do {

			// EOI
			if ( status == NULL ) {
				printf("\n");
				count = -1;
				break;
			}

			// Convert the string to lowercase and remove newlines
			strtolower( input );
			strmunge( input );

			// User quit
			if ( strcmp( "q", input ) == 0 ) {
				count = -1;
				break;
			}

			// Convert the string to a number
			count = atoi( input );

			// Bad input
			if ( count < 1 || count > 20 ) {
				count = 0;

				// Prompt the user
				printf( "*ERROR* Number of frames must be greater than 0 and less than 21 >> " );
				status = fgets( input, LINE, stdin );
			}

		} while ( count == 0 );

	}

	return count;
}

/**
 * Prompt the user for the reference string
 */
int get_references( int* references ) {
	char input[LINE];
	char* status = NULL;

	int count = 0;

	while ( count == 0 ) {

		// Prompt the user
		printf( "Enter the reference string, each character must be 0-7 >> " );
		status = fgets( input, LINE, stdin );

		do {

			// EOI
			if ( status == NULL ) {
				printf("\n");
				count = -1;
				break;
			}

			// Convert the string to lowercase and remove newlines
			strtolower( input );
			strmunge( input );

			// User quit
			if ( strcmp( "q", input ) == 0 ) {
				count = -1;
				break;
			}

			// Get the string length
			count = strlen( input );

			// Bad input length
			if ( count < 1 || count > 20 ) {
				count = 0;

				// Prompt the user
				printf( "*ERROR* Length of reference string must be greater than 0 and less than 21 >> " );
				status = fgets( input, LINE, stdin );
			}

			// Bad input
			int i, value;
			char c;
			for ( i = 0; i < count; i++ ) {
				c = input[i];
				value = c - '0';

				if ( value < 0 || value > 7 ) {
					count = 0;

					// Prompt the user
					printf( "*ERROR* Reference string characters must be 0-7 >> " );
					status = fgets( input, LINE, stdin );
					break;
				} else {
					references[i] = value;
				}
			}

		} while ( count == 0 );

	}

	return count;
}

/**
 * Output the current page frame status
 */
print_frames( page_frames* frames ) {
	int i;
	int value;
	char c;
	for ( i = 0; i < frames->count; i++ ) {
		value = frames->value[i];

		if ( value < 0 ) {
			c = 'E';
		} else {
			c = value + '0';
		}

		printf( "[%c]", c );
	}
	printf( "\n" );
}

int fifo_algo( page_frames* frames, int ref ) {
	return 0;
}

int lru_algo( page_frames* frames, int ref ) {
	return 0;
}

/**
 * Main dispatch loop.  Get user input and sstart the simulation.
 */
int main( int argc, char* argv[] ) {

	while(1) {
		// get the algo type
		char algo_name[20];
		int type = get_algo( algo_name );
		if ( type < 0 ) {
			return 0;
		}

		// get the frame count
		int frame_count = get_frames();
		if ( frame_count < 0 ) {
			return 0;
		}

		// get the reference string
		int references[20];
		memset( references, -1, 20 );

		int reference_count = get_references( references );
		if ( reference_count < 0 ) {
			return 0;
		}

		// determine which algorithm function to use
		int (* algo ) ( page_frames*, int );
		switch ( type ) {
			case FIFO:
				algo = &fifo_algo;
				break;
			case LRU:
				algo = &lru_algo;
				break;
		}

		// Pre-sim output
		printf( "\nAlgorithm: %s\nNumber of frames: %d\nReference string: ", algo_name, frame_count );
		int i;
		for ( i = 0; i < reference_count; i++ ) {
			printf( "%d", references[i] );
		}
		printf( "\n\n" );

		// prepare the simulation
		int fault_count = 0;
		page_frames* frames = pf_new( frame_count );

		printf( "**********************\n" );
		printf( "Starting Simulation...\n" );
		printf( "**********************\n" );

		// initial page frame status
		print_frames( frames );

		int fault;
		for ( i = 0; i < reference_count; i++ ) {
			fault = algo( frames, references[i] );

			if ( fault ) {
				fault_count++;
				print_frames( frames );
			}
		}

		printf( "\n" );
		printf( "Number of page faults: %d\n", fault_count );
		printf( "\n" );

		printf( "***************************************************\n" );
		printf( "***************************************************\n" );

		// garbage collection
		free( frames );
	}

	return 0;
}

