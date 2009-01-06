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

