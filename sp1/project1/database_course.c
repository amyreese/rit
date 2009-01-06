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
	db_course* course = db_allocate( sizeof( db_course ) );
	course->id = db_allocate( strlen( id ) );
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

