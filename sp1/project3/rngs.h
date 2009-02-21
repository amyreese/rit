/* ----------------------------------------------------------------------- 
 * Adapted from a multiple-stream RNG developed by Steve Park and Dave
 * Geyer.  This version only has a single stream, and supplies only the
 * Random() and PutSeed() functions, with PutSeed() modified so that a
 * value > 0 is the seed, and for any other value the original default
 * seed value is used.
 * -------------------------------------------------------------------------
 * Name            : rngs.h  (header file for the library file rngs.c) 
 * Author          : Steve Park & Dave Geyer
 * Language        : ANSI C
 * Latest Revision : 09-22-98
 * ----------------------------------------------------------------------- 
 */

#if !defined( _RNGS_ )
#define _RNGS_

double Random(void);
void   PutSeed(long x);

#endif
