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

db_enrollment* db_enrollment_get( db_database* db, char* course_id, char* student_id ) {
	// Get student and course data
	db_course* course = db_course_get( db, course_id );
	db_student* student = db_student_get( db, student_id );

	// Either course or student not found
	if ( course == NULL || student == NULL ) {
		return NULL;
	}

	// Search the student's enrollments for course
	db_enrollment* enrollment = student->courses;
	while ( enrollment != NULL ) {
		if ( enrollment->course == course ) {
			break;
		}

		enrollment = enrollment->next_course;
	}

	return enrollment;
}

int db_enrollment_exists( db_database* db, char* course_id, char* student_id ) {
	db_enrollment* enrollment = db_enrollment_get( db, course_id, student_id );

	return ( enrollment != NULL );
}

int db_enrollment_insert( db_database* db, char* course_id, char* student_id ) {
	db_course* course;
	db_student* student;
	db_enrollment* enrollment;
	db_enrollment* next;

	// Make sure the student exists
	student = db_student_get( db, student_id );
	if ( student == NULL ) {
		return DBERR_STUDENT_NOT_EXISTS;
	}

	// Make sure the course exists
	course = db_course_get( db, course_id );
	if ( course == NULL ) {
		return DBERR_COURSE_NOT_EXISTS;
	}

	// Make sure the student has a free slot
	if ( db_student_free( db, student_id ) < 1 ) {
		return DBERR_STUDENT_IS_FULL;
	}

	// Make sure the course has a free slot
	if ( db_course_free( db, course_id ) < 1 ) {
		return DBERR_COURSE_IS_FULL;
	}

	// Make sure the enrollment doesn't already exist
	enrollment = db_enrollment_get( db, course_id, student_id );
	if ( enrollment != NULL ) {
		return DBERR_STUDENT_ENROLLED;
	}

	// Now we can create the enrollment
	enrollment = db_allocate( sizeof( db_enrollment ) );
	enrollment->course = course;
	enrollment->student = student;
	enrollment->last_course = NULL;
	enrollment->last_student = NULL;

	// Insert the enrollment at the beginning of the course list
	next = course->students;
	if ( next != NULL ) {
		next->last_student = enrollment;
	}
	enrollment->next_student = next;
	course->students = enrollment;

	// Insert the enrollment at the beginning of the student list
	next = student->courses;
	if ( next != NULL ) {
		next->last_course = enrollment;
	}
	enrollment->next_course = next;
	student->courses = enrollment;

	return 0;
}

int db_enrollment_remove( db_database* db, char* course_id, char* student_id ) {
	db_course* course;
	db_student* student;
	db_enrollment* enrollment;

	// Make sure the student exists
	student = db_student_get( db, student_id );
	if ( student == NULL ) {
		return DBERR_STUDENT_NOT_EXISTS;
	}

	// Make sure the course exists
	course = db_course_get( db, course_id );
	if ( course == NULL ) {
		return DBERR_COURSE_NOT_EXISTS;
	}

	// Make sure the enrollment already exists
	enrollment = db_enrollment_get( db, course_id, student_id );
	if ( enrollment == NULL ) {
		return DBERR_STUDENT_NOT_ENROLLED;
	}

	// Remove the enrollment from course and student lists
	db_enrollment_pluck( db, enrollment );

	unallocate( enrollment );
	return 0;
}

int db_enrollment_remove_course( db_database* db, char* course_id ) {
	db_course* course;
	db_enrollment* enrollment;
	db_enrollment* next;

	// Make sure the course exists
	course = db_course_get( db, course_id );
	if ( course == NULL ) {
		return DBERR_COURSE_NOT_EXISTS;
	}

	// Remove all enrollments for the class
	enrollment = course->students;
	while ( enrollment != NULL ) {
		next = enrollment->next_student;

		db_enrollment_pluck( db, enrollment );
		unallocate( enrollment );

		enrollment = next;
	}

	return 0;
}

int db_enrollment_pluck( db_database* db, db_enrollment* enrollment ) {
	db_course* course = enrollment->course;
	db_student* student = enrollment->student;
	db_enrollment* last;
	db_enrollment* next;

	// Remove the enrollment from the course list
	last = enrollment->last_student;
	next = enrollment->next_student;
	if ( last == NULL && next == NULL ) {
		course->students = NULL;
	} else if ( last == NULL ) {
		next->last_student = NULL;
		course->students = next;
	} else if ( next == NULL ) {
		last->next_student = NULL;
	} else {
		last->next_student = next;
		next->last_student = last;
	}

	// Remove the enrollment from the student list
	last = enrollment->last_course;
	next = enrollment->next_course;
	if ( last == NULL && next == NULL ) {
		student->courses = NULL;
	} else if ( last == NULL ) {
		next->last_course = NULL;
		student->courses = next;
	} else if ( next == NULL ) {
		last->next_course = NULL;
	} else {
		last->next_course = next;
		next->last_course = last;
	}

	return 0;
}

