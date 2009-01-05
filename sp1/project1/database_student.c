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

