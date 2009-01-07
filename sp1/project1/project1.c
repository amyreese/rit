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

#include <allocate.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"
#include "input.h"

int verbose = 0;

// Pointer to the database to be used by cleanun_db()
db_database* database = NULL;

/**
 * Function to be executed before at exit, to cleanup the database if needed.
 */
void cleanup_db( void ) {
	if ( database != NULL ) {
		db_destroy( database );
	}
}

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

	// Initialize database and setup error function
	db_database* db = db_init();
	database = db;
	atexit( cleanup_db );

	// Main loop, get input and process it line by line
	char input[ LINE_SIZE ];   // input buffer
	char* tokens[ ARGS_SIZE ]; // array of pointers into input buffer
	int count;                 // count of input tokens
	char* command;             // the command string
	while ( ( count = tokenize_input( input, tokens ) ) >= 0 ) {

		// Dispatch processing based on the inputted command
		command = tokens[0];

		if ( strcmp( "student", command ) == 0 ) {
			db_new_student( db, tokens[1], tokens + 2 );

		} else if ( strcmp( "open", command ) == 0 ) {
			db_new_course( db, tokens[1], atoi( tokens[2] ) );

		} else if ( strcmp( "cancel", command ) == 0 ) {
			db_cancel_course( db, tokens[1] );

		} else if ( strcmp( "enroll", command ) == 0 ) {
			db_enroll_student( db, tokens[1], tokens[2] );

		} else if ( strcmp( "withdraw", command ) == 0 ) {
			db_withdraw_student( db, tokens[1], tokens[2] );

		}
	}

	// Done processing input
	db_dump( db );
	db_destroy( db );
	database = NULL;

	return 0;
}
