/**
 * nosyncupdate.c
 * Fork two unsynchronized child processes to update datafile
 * with a new, incremented value.
 *
 * @author John Reese
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( int argc, char* argv[] ) {
	int count, initial, final;
	int pid1, pid2;
	char arg[10] = "         ";
	FILE* f;

	// Usage
	if ( argc != 2 ) {
		printf( "Usage: nosyncupdate count\n" );
		return 1;
	}

	// Count
	count = atoi( argv[1] );

#if DEBUG
	// Debug / test mode
	int run;
	FILE* r;

	// Create basic table for test results
	r = fopen( "nosync.txt", "w" );
	fprintf( r, "%8s%10s%25s%25s\n\n", "Run #", "Count", "Expected Final Value", "Actual Final Value" );

	// Run 100 tests
	for ( run = 0; run < 100; run++ ) {
		// Reset the datafile
		f = fopen( "datafile", "w" );
		fprintf( f, "%d\n", 0 );
		fclose( f );

		// Set a new count every ten tests
		switch( run ) {
			case 0:
				count = 10;
				break;
			case 10:
				count = 100;
				break;
			case 20:
				count = 1000;
				break;
			case 30:
				count = 5000;
				break;
			case 40:
				count = 10000;
				break;
			case 50:
				count = 50000;
				break;
			case 60:
				count = 100000;
				break;
			case 70:
				count = 500000;
				break;
			case 80:
				count = 800000;
				break;
			case 90:
				count = 1000000;
				break;
			default:
				break;
		}

		// Put the count into a string
		sprintf( arg, "%d", count );
#else
	sprintf( arg, "%d", count );
#endif

	// Initial value
	f = fopen( "datafile", "r" );
	fscanf( f, "%d", &initial );
	fclose( f );
	printf( "Initial value: %d\n", initial );

	// First fork
	pid1 = fork();
	if ( ! pid1 ) {
		execlp( "nosync0", "nosync0", arg, (char*) NULL );
		return 0;
	}

	// Second fork
	pid2 = fork();
	if ( ! pid2 ) {
		execlp( "nosync1", "nosync1", arg, (char*) NULL );
		return 0;
	}

	// Wait for children
	waitpid( pid1, NULL, 0 );
	waitpid( pid2, NULL, 0 );

	// Final value
	f = fopen( "datafile", "r" );
	fscanf( f, "%d", &final );
	fclose( f );
	printf( "Final value: %d\n", final );

#if DEBUG
		// Output the test results
		fprintf( r, "%8d%10d%25d%25d\n", run, count, count*2, final );
		fflush( r );
	} // for

	fclose( r );
#endif

	return 0;
}

