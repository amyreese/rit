/**
 * Timed Response Game
 *
 * @author John Reese
 * @author Adam Risi
 */

#ifndef __GAME_H__
#define __GAME_H__

/**
 * The cumulative user round count.
 */
extern int game_round_count;

/**
 * The cumulative user reaction time.
 */
extern int game_timer_count;

/**
 * Entry point into the game's main processing sequence.
 */
void game_run( void );

/**
 * Play a round of timed response.
 * Wait for the user to be ready, then display a character and time how long
 * it takes for the user to respond correctly.
 */
void game_play_round( void );

/**
 * Initialize and seed the random number generator.
 */
void game_seed_rng( void );

#endif // __GAME_H__

