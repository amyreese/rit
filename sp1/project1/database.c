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
#include "database.h"

#include <stdio.h>
#include <stdarg.h>

////// Public Interface

int db_new_course( char* tokens[] ) {
	if ( verbose ) {
		printf( "%s created with limit %d\n", "", 0 );
	}
	return 0;
}

int db_new_student( char* tokens[] ) {
	if ( verbose ) {
		printf( "new student %s (%s)\n", "", "" );
	}
	return 0;
}

int db_cancel_course( char* tokens[] ) {
	if ( verbose ) {
		printf( "%s cancelled\n", "" );
	}
	return 0;
}

int db_enroll_student( char* tokens[] ) {
	if ( verbose ) {
		printf( "%s enrolled in %s", "", "" );
	}
	return 0;
}

int db_withdraw_student( char* tokens[] ) {
	if ( verbose ) {
		printf( "%s withdrawn from %s", "", "" );
	}
	return 0;
}

int db_error( int error, ... ) {
	va_list args;
	va_start( args, error );

	vfprintf( stdout, db_errors[ error ], args );

	va_end( args );
	return error;
}

/**
 * Database error messages.
 */
char* db_errors[] = {
	"", 
	"%s already exists\n",
	"%s does not exists\n",
	"%s already exists\n",
	"%s does not exists\n",
	"%s has a full schedule\n",
	"%s is full\n",
	"%s already enrolled in %s\n",
	"%s not enrolled in %s\n",

	NULL
};

