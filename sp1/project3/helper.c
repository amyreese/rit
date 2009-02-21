/**
 * Helper Function Library
 * Generic functions useful to the project.
 *
 * @author John Reese
 * @author Adam Risi
 */

#include "helper.h"

/**
 * Enable CPU interrupts.
 */
void interrupts_on( void ) {
	asm("sti");
}


