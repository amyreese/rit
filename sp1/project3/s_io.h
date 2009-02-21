/**
 * Serial I/O Library
 * Manages basic input and output functionality for the serial terminal, as
 * well as initialization routines for the local serial ports.
 *
 * @author John Reese
 * @author Adam Risi
 */

#ifndef __S_IO_H__
#define __S_IO_H__

/**
 * Global external variable def's
 */
extern char input[];
extern unsigned int S_IO_DONE;

/**
 * Initialize the serial I/O controller.
 */
void s_io_init( void );

/**
 * Enables the serial input interrupt and blocks until a single character is read.
 * Disables serial input interrupt when done
 * 
 * @return the unsigned int value of the read char
 */
unsigned int s_getchar( void );

/**
 * Enables the serial interrupt, reads until a \r or \n is found, or until the buffer
 * is full, disables the serial interrupt, and returns the address of the read string
 *
 * @return the read in string
 */
char *s_gets( void );

/**
 * Enables serial interrupt and sends out a string. Disables interrupt when done
 *
 * @param str the string to send over serial device
 */
void s_puts(char *str);

#endif // __S_IO_H__

