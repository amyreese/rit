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

#ifndef __PROJECT1_DATABASE__
#define __PROJECT1_DATABASE__

#include <stdio.h>
#include <stdarg.h>

/**
 * General database, set of courses and students.
 */
typedef struct db_database {
	struct db_course* courses;
	struct db_student* students;
} db_database;

/**
 * Course information node.
 */
typedef struct db_course {
	char* id;

	int size;

	struct db_course* next;
} db_course;

/**
 * Student information node.
 */
typedef struct db_student {
	char* id;

	char* last_name;
	char* first_name;
	char* middle_name;
	char* formatted_name;

	struct db_enrollment* courses;

	struct db_student* next;
} db_student;

/**
 * Student enrolled in a course.
 */
typedef struct db_enrollment {
	struct db_course* course;
	struct db_student* student;

	struct db_course* next_course;
	struct db_student* next_student;
} db_enrollment;

/**
 * Create a new course.
 */
int db_new_course( char* tokens[] );

/**
 * Create a new student.
 */
int db_new_student( char* tokens[] );

/**
 * Cancel an existing course.
 */
int db_cancel_course( char* tokens[] );

/**
 * Enroll an existing student in an existing course.
 */
int db_enroll_student( char* tokens[] );

/**
 * Withdraw an enrolled student from a course.
 */
int db_withdraw_student( char* tokens[] );

/**
 * Error handling for database functions.
 */
int db_error( int error, ... );

/**
 * Database error messages.
 */
char* db_errors[10];
#define DBERR_STUDENT_EXISTS 1
#define DBERR_STUDENT_NOT_EXISTS 2
#define DBERR_COURSE_EXISTS 3
#define DBERR_COURSE_NOT_EXISTS 4
#define DBERR_STUDENT_IS_FULL 5
#define DBERR_COURSE_IS_FULL 6
#define DBERR_STUDENT_ENROLLED 7
#define DBERR_STUDENT_NOT_ENROLLED 8

#endif // __PROJECT1_DATABASE__
