/*
 * sharevar.h
 *
 * Constant and type definitions needed for creating the shared memory
 * segment to implement Peterson's algorithm.
 *
 */

#define PERMS 0666    /* Access rights */
#define SHMKEY ((key_t) 1781247478)  /* Change this to a unique key */
#define FALSE 0
#define TRUE 1

typedef struct {
  int flag[2];
  int turn;
} syncvars;
