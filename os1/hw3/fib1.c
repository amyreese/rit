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

void fibseq ( int n ) {
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

		printf( "%d\n", f );
	}
}

int main ( int argc, char* argv[] ) {
	int i;
	int count;

	// Fork you
	int pid = fork();

	// Parent
	if ( pid ) {
		wait( NULL );

	// Child
	} else {
		if ( argc < 2 ) {
			exit( 1 );
		}

		count = atoi( argv[1] );

		if ( count < 0 ) {
			exit( 2 );
		}

		fibseq( count );	
	}

	return 0;
}

