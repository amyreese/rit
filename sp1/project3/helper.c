/**
 * Helper Function Library
 * Generic functions useful to the project.
 *
 * @author John Reese
 */

#include "helper.h"

/**
 * Enable CPU interrupts.
 */
void interrupts_on( void ) {
	asm("sti");
}


