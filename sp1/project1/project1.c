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

#include <allocate.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "database.h"
#include "input.h"

#define DEBUG 1

/**
 * Global values
 */
int verbose = 0;
char* commands[] = {
	"student",
	"open",
	"cancel",
	"enroll",
	"withdraw",
	NULL
};

/**
 * Program dispatch; get a line of input, and call the appropriate
 * command function.
 */
int main( int argc, char** argv ) {
#if DEBUG
	printf( "Program executed with %d arguments: \n", argc-1 );
	for ( int i = 1; i < argc; i++ ) {
		printf( "Argument: %s \n", argv[i] );
	}
	printf( "\n" );
#endif

	// Check for -v argument
	char* verbose_arg = "-v";
	for ( int i = 1; i < argc; i++ ) {
		if ( strcmp( verbose_arg, argv[i] ) == 0 ) {
			verbose = 1;
		}
	}

	// Main loop, get input and process it line by line
	char input[ LINE_SIZE ];   // input buffer
	char* tokens[ ARGS_SIZE ]; // array of pointers into input buffer
	int count;                 // count of input tokens
	int command;               // the command number
	while ( ( count = tokenize_input( input, tokens ) ) >= 0 ) {
		command = -1;
		for ( int i = 0; commands[i] != NULL; i++ ) {
			if ( strcmp( commands[i], tokens[0] ) == 0 ) {
				command = i;
			}
		}

#if DEBUG
		printf( "Command number: %d\n", command );
#endif

		switch ( command ) {
			case 0: // student
				break;

			case 1: // open
				break;

			case 2: // cancel
				break;

			case 3: //enroll
				break;

			case 4: //withdraw
				break;

			default: // error?
				break;
		}
	}

	// Done processing input
#if DEBUG
	printf( "Goodbye!\n" );
#endif

	return 0;
}
