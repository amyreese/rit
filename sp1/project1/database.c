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

void* db_allocate( size_t size ) {
	void* ptr = allocate( size );

	if ( ptr == NULL ) {
		db_error( DBERR_OUT_OF_MEMORY );
		exit(-1);
	}

	return ptr;
}

db_database* db_init() {
	db_database* db = db_allocate( sizeof( db_database ) );
	db->courses = NULL;
	db->students = NULL;

	return db;
}

void db_destroy( db_database* db ) {
	// Destroy all courses
	db_course* course = db->courses;
	db_course* next_course;
	while ( course != NULL ) {
		next_course = course->next;
		db_course_remove( db, course->id );

		course = next_course;
	}

	// Destroy all students
	db_student* student = db->students;
	db_student* next_student;
	while ( student != NULL ) {
		next_student = student->next;
		db_student_remove( db, student->id );

		student = next_student;
	}

	// Destroy the database
	unallocate( db );
}

int db_new_course( db_database* db, char* tokens[] ) {
	char* id = tokens[0];
	int size = atoi( tokens[1] );
	int error;

	// Insert course into the database
	if ( ( error = db_course_insert( db, id, size ) ) ) {
		return db_error( error );
	}

	return db_message( DBMSG_COURSE_NEW, id, size );
}

int db_new_student( db_database* db, char* tokens[] ) {
	char* id = tokens[0];
	char name[120];
	int index = 0;
	char* token;
	int token_length;

	// Truncate and concatenate name tokens
	for ( int i = 1; i <= 3; i++ ) {
		if ( tokens[i] == NULL ) {
			break;
		}

		token = tokens[i];
		token_length = strlen( token );
		token_length = token_length > 39 ? 39 : token_length;

		strncpy( &(name[index]), tokens[i], token_length );
		index += token_length;
		if ( tokens[i+1] != NULL ) {
			name[index++] = ' ';
		} else {
			name[index] = '\0';
			break;
		}
	}

	// Insert student into database
	int error;
	if ( ( error = db_student_insert( db, id, name ) ) ) {
		return db_error( error );
	}

	return db_message( DBMSG_STUDENT_NEW, id, name );
}

int db_cancel_course( db_database* db, char* tokens[] ) {
	char* id = tokens[0];
	int error;

	// Remove the course from the database
	if ( ( error = db_course_remove( db, id ) ) ) {
		return db_error( error );
	}

	return db_message( DBMSG_COURSE_CANCELLED, id );
}

int db_enroll_student( db_database* db, char* tokens[] ) {
	char* student_id = tokens[0];
	char* course_id = tokens[1];
	int error;

	if ( ( error = db_enrollment_insert( db, course_id, student_id ) ) ) {
		return db_error( error );
	}

	return db_message( DBMSG_STUDENT_ENROLLED, student_id, course_id );
}

int db_withdraw_student( db_database* db, char* tokens[] ) {
	char* student_id = tokens[0];
	char* course_id = tokens[1];
	int error;

	if ( ( error = db_enrollment_remove( db, course_id, student_id ) ) ) {
		return db_error( error );
	}

	return db_message( DBMSG_STUDENT_WITHDRAWN, student_id, course_id );
}

void db_dump( db_database* db ) {
	// Per-student listing
	db_student* student = db->students;
	while ( student != NULL ) {
		printf( "Student %s (%s) is taking no courses\n", student->id, student->name );
		student = student->next;
	}

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

char* db_messages[] = {
	"new student %s (%s)\n",
	"%s created with limit %d\n",
	"%s cancelled\n",
	"%s enrolled in %s\n",
	"%s withdrawn from %s\n",
	NULL
};

char* db_errors[] = {
	"Memory allocation failed!\n",
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

