/**
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

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

/**
 * mAsh - my Awesome shell
 * Very basic pass-through shell.
 *
 * @author John Reese
 */

#define DEBUG 0

#define LINE_SIZE 80 // 80 bytes should be enough for anybody
#define ARGS_SIZE LINE_SIZE/2 + 1

char* error_string = "Error!\n";
int error_string_len = 7;

/**
 * "Safe" write: call write() as needed to make sure all bytes are written.
 */
void swrite( int file, void *buf, size_t count ) {
	int written = 0;
	while ( written < count ) {
		written += write( file, buf + written, count - written );
	}
}

/**
 * Parse an input line into a list of arguments.
 */
int parse_input( char* input, char *args[] ) {
	int length = 0; // characters input from stdin
	int count = 0;  // number of arguments parsed
	int i = 0;      // current position of parsing
	int space = 1;  // are we parsing whitespace

	// Gather input from user
	length = read( STDIN_FILENO, input, LINE_SIZE );

	// EOF sent by user
	if( length < 1 ) {
		return -1;
	}

	// Start parsing argument tokens
	for( i = 0; i < length; i++ ) {
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

	// Nullify next argument
	args[count] = NULL;

#if DEBUG
	printf( "\n" );
	for ( i = 0; i < count; i++ ) {
		printf( "%d: '%s'\n", i, args[i] );
	}
	printf( "Total: %d\n", count );
#endif

	return count;
}

int main( void ) {
	char input[LINE_SIZE]; // input buffer
	char *args[ARGS_SIZE]; // array of pointers into input buffer

	int count; // number of arguments
	int pid;   // process ID from fork()
	int error; // error from exec()

	// parse and execute input until EOF
	while(1) {
		swrite( STDOUT_FILENO, ">> ", 3 );
		count = parse_input( input, args );

		// EOF from user, quit shell
		if ( count < 0 ) {
			swrite( STDOUT_FILENO, "\nGood bye!\n", 11 );
			return 0;
		}

		// Fork to execute command
		pid = fork();

#if DEBUG
		printf( "Fork pid: %d\n", pid );
#endif

		// Child
		if ( pid == 0 ) {
			error = execvp( input, args );
			perror( "Error" );
			return 0;

		// Parent
		} else {
			wait(0);
		}
	}

	return 0;
}
