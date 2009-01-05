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

typedef struct db_database {
	struct db_course* courses;
	struct db_student* students;
} db_database;

typedef struct db_course {
	char* id;

	int size;

	struct db_course* next;
} db_course;

typedef struct db_student {
	char* id;

	char* last_name;
	char* first_name;
	char* middle_name;

	struct db_enrollment* courses;

	struct db_student* next;
} db_student;

typedef struct db_enrollment {
	struct db_course* course;
	struct db_student* student;

	struct db_course* next_course;
	struct db_student* next_student;
} db_enrollment;


#endif // __PROJECT1_DATABASE__
