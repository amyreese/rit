/*
** File:	allocate.h
** Author:	K. Reek
** Contributor: Warren R. Carithers
** Description: These functions perform dynamic memory allocation in a
**		controlled fashion.  Their interfaces are identical to
**		malloc and free.
**
**		If the environment variable SPF_ALLOCATE_MAX is set,
**		then its value is interpreted as the maximum amount of
**		dynamically allocated memory that the program will be
**		allowed to have at any time.  If the variable is not
**		set, there is no limit on the program's memory requests.
*/

#ifndef _ALLOCATE_H
#define _ALLOCATE_H

#include <stdlib.h>

/*
** These defines help guard against calling malloc (or any of the other
** allocation functions) directly.  The defined value causes a syntax
** error if the functions are called accidentally.
*/
#define	malloc	DO NOT CALL MALLOC OR FREE DIRECTLY!
#define	free	DO NOT CALL MALLOC OR FREE DIRECTLY!
#define	calloc	DO NOT CALL CALLOC EITHER!
#define	realloc	DO NOT CALL REALLOC EITHER!


/*
** allocate: used to obtain "nbytes" of uninitialized memory.  Returns
**	NULL if the memory could not be obtained or if the request would
**	cause the program's memory consumption to exceed the limit.
*/
void *allocate( size_t nbytes );

/*
** unallocate: used to return a previously allocated block of memory.
*/	
void unallocate( void *pointer );

#endif
