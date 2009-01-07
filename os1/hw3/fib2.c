/*
 * Copyright (C) 2008	John Reese
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

#define MAX_SEQUENCE 45

typedef struct {
	long sequence[ MAX_SEQUENCE ];
	int count;
} shdata;

void fibseq ( shdata* shm, int n ) {
	int i;
	int f;
	int p = 0;
	int q = 1;

	for ( i = 0; i < n; i++ ) {
		switch ( i ) {
			case 0:
				f = p;
				break;
			case 1:
				f = q;
				break;
			default:
				f = p + q;
				p = q;
				q = f;
		}

		shm->sequence[i] = f;
	}
}

int main ( int argc, char* argv[] ) {
	int i;
	int count;
	int shmid;
	shdata* shm;

	if ( argc < 2 ) {
		exit( 1 );
	}

	count = atoi( argv[1] );

	if ( count < 0 || count > MAX_SEQUENCE ) {
		exit( 2 );
	}

	// Shared memory
	if ( ( shmid = shmget( 1, sizeof( shdata ), IPC_CREAT | 0666 ) ) < 0 ) {
		perror( "error" );
		exit( -1 );
	}
	shm = ( shdata* ) shmat( shmid, NULL, 0 );
	shm->count = count;

	// Fork you
	int pid = fork();

	// Parent
	if ( pid ) {
		wait( NULL );

		for ( i = 0; i < count; i++ ) {
			printf( "%d\n", shm->sequence[i] );
		}

		shmdt( (char*) shm );

	// Child
	} else {
		fibseq( shm, count );	
		shmdt( (char*) shm );
	}

	return 0;
}

