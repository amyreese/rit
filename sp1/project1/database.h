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

#include <stdarg.h>
#include <stdio.h>

#define DB_STUDENT_MAX_COURSES 5

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
	struct db_enrollment* students;

	struct db_course* last;
	struct db_course* next;
} db_course;

/**
 * Student information node.
 */
typedef struct db_student {
	char* id;
	char* name;
	struct db_enrollment* courses;

	struct db_student* last;
	struct db_student* next;
} db_student;

/**
 * Student enrolled in a course.
 */
typedef struct db_enrollment {
	struct db_course* course;
	struct db_student* student;

	struct db_enrollment* next_course;
	struct db_enrollment* next_student;
} db_enrollment;

/**
 * Allocate memory.
 * If failed, print error message, and terminate.
 */
void* db_allocate( size_t size );

/**
 * Create a new database.
 */
db_database* db_init();

/**
 * Destroy an existing database.
 */
void db_destroy( db_database* db );

/**
 * Create a new course.
 */
int db_new_course( db_database* db, char* tokens[] );

/**
 * Create a new student.
 */
int db_new_student( db_database* db, char* tokens[] );

/**
 * Cancel an existing course.
 */
int db_cancel_course( db_database* db, char* tokens[] );

/**
 * Enroll an existing student in an existing course.
 */
int db_enroll_student( db_database* db, char* tokens[] );

/**
 * Withdraw an enrolled student from a course.
 */
int db_withdraw_student( db_database* db, char* tokens[] );

/**
 * Dump the database contents to output.
 */
void db_dump( db_database* db );

/**
 * Message handling for database functions.
 */
int db_message( int message, ... );

/**
 * Error handling for database functions.
 */
int db_error( int error, ... );

//// Private course API

db_course* db_course_get( db_database* db, char* id );
int db_course_exists( db_database* db, char* id );
int db_course_insert( db_database* db, char* id, int size );
int db_course_remove( db_database* db, char* id );

int db_course_count( db_database* db, char* id );
int db_course_free( db_database* db, char* id );

//// Private student API

db_student* db_student_get( db_database* db, char* id );
int db_student_exists( db_database* db, char* id );
int db_student_insert( db_database* db, char* id, char* name );
int db_student_remove( db_database* db, char* id );

int db_student_count( db_database* db, char* id );
int db_student_free( db_database* db, char* id );

//// Private enrollment API

db_enrollment* db_enrollment_get( db_database* db, char* course_id, char* student_id );
int db_enrollment_exists( db_database* db, char* course_id, char* student_id );
int db_enrollment_insert( db_database* db, char* course_id, char* student_id );
int db_enrollment_remove( db_database* db, char* course_id, char* student_id );
int db_enrollment_remove_course( db_database* db, char* course_id );

/**
 * Database messages.
 */
char* db_messages[6];
#define DBMSG_STUDENT_NEW 0
#define DBMSG_COURSE_NEW 1
#define DBMSG_COURSE_CANCELLED 2
#define DBMSG_STUDENT_ENROLLED 3
#define DBMSG_STUDENT_WITHDRAWN 4

/**
 * Database error messages.
 */
char* db_errors[10];
#define DBERR_OUT_OF_MEMORY 0
#define DBERR_STUDENT_EXISTS 1
#define DBERR_STUDENT_NOT_EXISTS 2
#define DBERR_COURSE_EXISTS 3
#define DBERR_COURSE_NOT_EXISTS 4
#define DBERR_STUDENT_IS_FULL 5
#define DBERR_COURSE_IS_FULL 6
#define DBERR_STUDENT_ENROLLED 7
#define DBERR_STUDENT_NOT_ENROLLED 8

#endif // __PROJECT1_DATABASE__
