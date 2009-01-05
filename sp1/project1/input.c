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

#include "project1.h"
#include "input.h"

#include <allocate.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Tokenize an input line into a list of arguments.
 */
int tokenize_input( char* input, char *args[] ) {
	int length = 0; // characters input from stdin
	int count = 0;  // number of arguments parsed
	int i = 0;      // current position of parsing
	int space = 1;  // are we parsing whitespace

	// Gather input from user, checking for EOF
	if ( fgets( input, LINE_SIZE, stdin ) == NULL ) {
		return -1;
	}

	length = strlen( input );

	// Start parsing argument tokens
	for ( i = 0; i < length; i++ ) {
		switch( input[i] ) {
			// argument delimiters
			case ' ':
			case '\t':
				input[i] = '\0';
				space = 1;
				break;

			// end of input
			case '\n':
			case '\0':
				input[i] = '\0';
				i = length;
				break;

			// argument content
			default:
				if ( space ) {
					args[count++] = &input[i];
				}
				space = 0;
		}
	}

	// Nullify remaining argument pointers
	for ( int i = count; i < ARGS_SIZE; i++ ) {
		args[i] = NULL;
	}

#if DEBUG
		printf( "\n" );
		for ( i = 0; i < count; i++ ) {
			printf( "%d: '%s'\n", i, args[i] );
		}
		printf( "Total: %d, Length: %d\n", count, length );
#endif

	return count;
}

