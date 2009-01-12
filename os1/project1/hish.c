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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

/**
 * Hish - History shell
 * Very basic pass-through shell with history support.
 *
 * @author John Reese
 */

#define DEBUG 0

#define LINE_SIZE 80 // 80 bytes should be enough for anybody
#define ARGS_SIZE LINE_SIZE/2 + 1

char* error_string = "Error!\n";
int error_string_len = 7;

int signal_handled = 0;
char shell_history[10][LINE_SIZE];
int shell_history_count = 0;

/**
 * "Safe" write: call write() as needed to make sure all bytes are written.
 */
void swrite( int file, void *buf ) {
	int count = strlen( buf );
	int written = 0;
	while ( written < count ) {
		written += write( file, buf + written, count - written );
	}
}

/**
 * Parse an input line into a list of arguments.
 */
int parse_input( char* input, char* parsed, char *args[] ) {
	int length = 0; // characters input from stdin
	int count = 0;  // number of arguments parsed
	int i = 0;      // current position of parsing
	int space = 1;  // are we parsing whitespace

	// Copy to parsed string
	strncpy( parsed, input, LINE_SIZE );
	length = strlen( parsed );

	// Start parsing argument tokens
	for( i = 0; i < length; i++ ) {
		switch( parsed[i] ) {
			// argument delimiters
			case ' ':
			case '\t':
				parsed[i] = '\0';
				space = 1;
				break;

			// end of input
			case '\n':
			case '\0':
				parsed[i] = '\0';
				i = length;
				break;

			// argument content
			default:
				if ( space ) {
					args[count++] = &parsed[i];
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

/**
 * Return a pointer to either a direct or relative-offset history entry.
 */
char* history_entry( int index ) {
	if ( index < 0 ) {
		index = shell_history_count + index;
#if DEBUG
		printf( "Negative history index: %d\n", index );
#endif
	}
	
	if ( index < 0 || index < shell_history_count - 10 ) {
		return NULL;
	}

	return shell_history[index % 10];
}

/**
 * Return a pointer to the next history entry, and increment the history count.
 */
char* history_next() {
	return shell_history[ shell_history_count++ % 10 ];
}

/**
 * Handle the SIGINT signal and print a list of history entries.
 */
void history_signal() {
	signal( SIGINT, history_signal );
	signal_handled = 1;

	char output[LINE_SIZE + 25];
	int i = shell_history_count - 10;
	i = ( i < 0 ? 0 : i );

	swrite( STDOUT_FILENO, "\n" );

	while ( i < shell_history_count ) {
		sprintf( output, "\ncommand %d is %s", i+1, history_entry( i ) );
		swrite( STDOUT_FILENO, output );

		i++;
	}
}

int main( void ) {
	char input[LINE_SIZE];  // input buffer
	char parsed[LINE_SIZE]; // parsed input buffer
	char* args[ARGS_SIZE];  // array of pointers into input buffer
	char* entry;            // pointer to history entry string
	char history_char;      // history character requested

	int length;// number of characters read from input
	int count; // number of input tokens parsed
	int pid;   // process ID from fork()
	int error; // error from exec()
	int found = 0; // history request found
	int i = -1;
	
	// hook the signal handler
	signal( SIGINT, history_signal );

	// parse and execute input until EOF
	while(1) {
		swrite( STDOUT_FILENO, "\n>> " );

		// Gather input from user
		length = read( STDIN_FILENO, input, LINE_SIZE );

#if DEBUG
		printf( "Input length: '%d', sig: '%d'\n", length, signal_handled );
#endif

		// EOF from user, quit shell
		if( length == 0 ) {
			swrite( STDOUT_FILENO, "\nGood bye!\n" );
			return 0;
		} else if ( length < 0 ) {
			continue;
		} else {
			input[length] = '\0';
		}

		// Parse input for arguments
		count = parse_input( input, parsed, args );

		// Handle blank lines
		if ( count < 1 ) {
			continue;
		}

		// Check for history requests
		if ( args[0][0] == '#' ) {
			history_char = args[0][1];

			if ( history_char == '#' ) {
				entry = history_entry( -1 );
				if ( entry == NULL ) {
					swrite( STDOUT_FILENO, "Error: history entry not found.\n" );
					continue;
				}

				parse_input( entry, parsed, args );

			} else {
#if DEBUG
			printf( "Searching command history for '%c'\n", history_char );
#endif

				found = 0;
				i = -1;
				while ( ( entry = history_entry( i ) ) != NULL ) {
					parse_input( entry, parsed, args );
					if ( args[0][0] == history_char ) {
						found = 1;
						break;
					}
					i--;
				}

				if ( found == 0 ) {
					swrite( STDOUT_FILENO, "Error: history entry not found.\n" );
					continue;
				}
			}

			// Add to history and output command
			strncpy( history_next(), entry, LINE_SIZE );
			swrite( STDOUT_FILENO, entry );

		} else {
			// Add to history
			strncpy( history_next(), input, LINE_SIZE );
		}

		// Fork to execute command
		pid = fork();

#if DEBUG
		printf( "Fork pid: %d\n", pid );
#endif

		// Child
		if ( pid == 0 ) {
			error = execvp( parsed, args );
			perror( "Error" );
			return 0;

		// Parent
		} else {
			wait(0);
		}
	}

	return 0;
}
