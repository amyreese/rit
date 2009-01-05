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

#include <allocate.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#  undef malloc
#  undef free
#  define allocate malloc
#  define unallocate free
#endif

////// Private API specification

int db_course_is_valid( db_database* db, char* id, int size );
int db_course_insert( db_database* db, char* id, int size );
int db_course_remove( db_database* db, char* id );

////// Public Interface

db_database* db_init() {
	db_database* db = allocate( sizeof( db_database ) );
	db->courses = NULL;
	db->students = NULL;

	return db;
}

void db_destroy( db_database* db ) {
	unallocate( db );
}

int db_new_course( db_database* db, char* tokens[] ) {
	char* id = tokens[0];
	int size = atoi( tokens[1] );
	int error;

#if DEBUG
	printf( "Creating course '%s' with limit %d\n", id, size );
#endif

	if ( ( error = db_course_is_valid( db, id, size ) ) ) {
		return db_error( error );
	}

	if ( ( error = db_course_insert( db, id, size ) ) ) {
		return db_error( error );
	}

	return db_message( DBMSG_COURSE_NEW, id, size );
}

int db_new_student( db_database* db, char* tokens[] ) {
	return db_message( DBMSG_STUDENT_NEW, "", "" );
}

int db_cancel_course( db_database* db, char* tokens[] ) {
	char* id = tokens[0];
	int error;

	if ( ( error = db_course_remove( db, id ) ) ) {
		return db_error( error );
	}

	return db_message( DBMSG_COURSE_CANCELLED, id );
}

int db_enroll_student( db_database* db, char* tokens[] ) {
	return db_message( DBMSG_STUDENT_ENROLLED, "", "" );
}

int db_withdraw_student( db_database* db, char* tokens[] ) {
	return db_message( DBMSG_STUDENT_WITHDRAWN, "", "" );
}

void db_dump( db_database* db ) {
	// Per-course listing
	db_course* course = db->courses;
	while ( course != NULL ) {
		printf( "Course %s (limit %d) is empty\n", course->id, course->size );
		course = course->next;
	}
}

int db_message( int message, ... ) {
	if ( verbose ) {
		va_list args;
		va_start( args, message );

		vfprintf( stdout, db_messages[ message ], args );

		va_end( args );
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

/////// Private API

int db_course_is_valid( db_database* db, char* id, int size ) {
	return 0; // short circuit if we don't need to validate
#if 0
	if ( size < 0 || size > 99 ) {
		return -1;
	}

	if ( strlen( id ) != 5 ) {
		return -1;
	}

	int i = 0;
	for ( i; i < 2; i++ ) {
		char c = id[i];
		if ( c < 'A' || c > 'Z' ) {
			return -1;
		}
	}
	for ( i; i < 5; i++ ) {
		char c = id[i];
		if ( c < '0' || c > '9' ) {
			return -1;
		}
	}
#endif
}

int db_course_insert( db_database* db, char* id, int size ) {
	int cmp;

	// Find the appropriate spot in the list, and check for duplicate ID
	db_course* last = NULL;
	db_course* next = db->courses;
	while ( next != NULL ) {
		cmp = strcmp( id, next->id );
		if ( cmp == 0 ) {
			return DBERR_COURSE_EXISTS;
		} else if ( cmp < 1 ) {
			break;
		} else {
			last = next;
			next = next->next;
		}
	}

	// Initialize new course
	db_course* course = allocate( sizeof( db_course ) );
	course->id = allocate( strlen( id ) );
	course->size = size;
	course->next = NULL;
	course->last = NULL;
	strcpy( course->id, id );

	// Insert new course into the list as appropriate
	if ( last == NULL ) {
		if ( db->courses != NULL ) {
			course->next = db->courses;
			course->next->last = course;
		}
		db->courses = course;
	} else {
		course->last = last;
		course->next = last->next;
		last->next = course;

		if ( course->next != NULL ) {
			course->next->last = course;
		}
	}

	return 0;
}

int db_course_remove( db_database* db, char* id ) {
	int cmp;

	db_course* course = db->courses;
	while ( course != NULL ) {
		cmp = strcmp( course->id, id );
		if ( cmp == 0 ) {
			break;
		}
		
		course = course->next;
	}

	if ( course == NULL ) {
		return DBERR_COURSE_NOT_EXISTS;
	}

	if ( course->last == NULL && course->next == NULL ) {
		db->courses = NULL;
	} else if ( course->last == NULL ) {
		db->courses = course->next;
		course->next->last = NULL;
	} else if ( course->next == NULL ) {
		course->last->next = NULL;
	} else {
		course->last->next = course->next;
		course->next->last = course->last;
	}

	unallocate( course );
	return 0;
}

char* db_messages[] = {
	"new student %s (%s)\n",
	"%s created with limit %d\n",
	"%s cancelled\n",
	"%s enrolled in %s\n",
	"%s withdrawn from %s\n",
	NULL
};

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

