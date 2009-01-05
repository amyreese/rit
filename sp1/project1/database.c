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

#if 0
#  undef malloc
#  undef free
#  define allocate malloc
#  define unallocate free
#endif

////// Private API specification

db_course* db_course_get( db_database* db, char* id );
int db_course_exists( db_database* db, char* id );
int db_course_insert( db_database* db, char* id, int size );
int db_course_remove( db_database* db, char* id );

int db_course_count( db_database* db, char* id );
int db_course_free( db_database* db, char* id );

int db_course_enroll( db_database* db, char* id, char* student_id );
int db_course_withdraw( db_database* db, char* id, char* student_id );

int db_student_exists( db_database* db, char* id );
int db_student_insert( db_database* db, char* id, char* name );
int db_student_remove( db_database* db, char* id );

int db_student_count( db_database* db, char* id );
int db_student_free( db_database* db, char* id );

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

#if DEBUG
	printf( "Creating new student, id '%s'\n", id );
#endif

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

#if DEBUG
	printf( "Student name is '%s'\n", name );
#endif

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

	// TODO: unenroll students from the course

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

	// Enroll the student
	//if ( ( error = db_course_enroll( db, course_id, student_id ) ) ) {
	//	return db_error( error );
	//}

	return db_message( DBMSG_STUDENT_ENROLLED, "", "" );
}

int db_withdraw_student( db_database* db, char* tokens[] ) {
	return db_message( DBMSG_STUDENT_WITHDRAWN, "", "" );
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

/////// Private API

db_course* db_course_get( db_database* db, char* id ) {
	int cmp;
	db_course* course = db->courses;
	while ( course != NULL ) {
		cmp = strcmp( course->id, id );
		if ( cmp == 0 ) {
			break;
		}

		course = course->next;
	}

	return course;
}

int db_course_exists( db_database* db, char* id ) {
	db_course* course = db_course_get( db, id );

	return ( course != NULL );
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
	// Find the course in the database
	db_course* course = db_course_get( db, id );

	// Course not found
	if ( course == NULL ) {
		return DBERR_COURSE_NOT_EXISTS;
	}

	// Remove course from the list
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

	unallocate( course->id );
	unallocate( course );
	return 0;
}

int db_course_count( db_database* db, char* id ) {
	int count = 0;
	db_course* course = db_course_get( db, id );
	db_enrollment* student = course->students;
}

int db_course_enroll( db_database* db, char* id, char* student_id ) {
	int error;

	if ( ! db_student_exists( db, student_id ) ) {
		return DBERR_STUDENT_NOT_EXISTS;
	}

	if ( ! db_course_exists( db, id ) ) {
		return DBERR_COURSE_NOT_EXISTS;
	}
}

int db_student_exists( db_database* db, char* id ) {
	int cmp;
	db_student* next = db->students;
	while ( next != NULL ) {
		cmp = strcmp( id, next->id );
		if ( cmp == 0 ) {
			return 1;
		}

		next = next->next;
	}

	return 0;
}

int db_student_insert( db_database* db, char* id, char* name ) {
	int cmp;

	// Check for duplicate ID
	db_student* last = NULL;
	db_student* next = db->students;
	while ( next != NULL ) {
		cmp = strcmp( id, next->id );
		if ( cmp == 0 ) {
			return DBERR_STUDENT_EXISTS;
		}

		next = next->next;
	}

	// Find the appropriate spot in the list
	last = NULL;
	next = db->students;
	while ( next != NULL ) {
		cmp = strcmp( name, next->name );
		if ( cmp == 0 ) {
			cmp = strcmp( id, next->id );
			if ( cmp == 0 ) {
				return DBERR_STUDENT_EXISTS;
			} else if ( cmp < 1 ) {
				break;
			} else {
				last = next;
				next = next->next;
			}
		} else if ( cmp < 1 ) {
			break;
		} else {
			last = next;
			next = next->next;
		}
	}

	// Initialize new student
	db_student* student = allocate( sizeof( db_student ) );
	student->id = allocate( strlen( id ) );
	student->name = allocate( strlen( name ) );
	student->next = NULL;
	student->last = NULL;
	strcpy( student->id, id );
	strcpy( student->name, name );

	// Insert new student into the list as appropriate
	if ( last == NULL ) {
		if ( db->students != NULL ) {
			student->next = db->students;
			student->next->last = student;
		}
		db->students = student;
	} else {
		student->last = last;
		student->next = last->next;
		last->next = student;

		if ( student->next != NULL ) {
			student->next->last = student;
		}
	}

	return 0;
}

int db_student_remove( db_database* db, char* id ) {
	int cmp;

	// Find student in the database
	db_student* student = db->students;
	while ( student != NULL ) {
		cmp = strcmp( student->id, id );
		if ( cmp == 0 ) {
			break;
		}

		student = student->next;
	}

	// Student not found
	if ( student == NULL ) {
		return DBERR_STUDENT_NOT_EXISTS;
	}

	// Remove student from the list
	if ( student->last == NULL && student->next == NULL ) {
		db->students = NULL;
	} else if ( student->last == NULL ) {
		db->students = student->next;
		student->next->last = NULL;
	} else if ( student->next == NULL ) {
		student->last->next = NULL;
	} else {
		student->last->next = student->next;
		student->next->last = student->last;
	}

	unallocate( student );
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

