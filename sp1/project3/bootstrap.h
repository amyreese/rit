/*
** SCCS ID:	@(#)bootstrap.h	1.2	03/15/05
**
** File:	bootstrap.h
**
** Author:	K. Reek
**
** Contributor:	Warren R. Carithers
**
** Description:	Addresses where various stuff goes in memory.
*/

#ifndef	_BOOTSTRAP_H
#define	_BOOTSTRAP_H


/*
** The target program itself
*/
#define TARGET_SEGMENT	0x00001000	/* 0001:0000 */
#define TARGET_ADDRESS	0x00010000	/* and upward */
#define	TARGET_STACK	0x00010000	/* and downward */

/*
** The Global Descriptor Table (0000:0400 - 0000:2400)
*/
#define	GDT_SEGMENT	0x00000040
#define	GDT_ADDRESS	0x00000400

#define	GDT_LINEAR	0x08		/* All of memory, R/W */
#define	GDT_CODE	0x10		/* All of memory, R/E */
#define	GDT_DATA	0x18		/* All of memory, R/W */
#define	GDT_STACK	0x20		/* All of memory, R/W */

/*
** The Interrupt Descriptor Table (0000:2400 - 0000:2C00)
*/
#define	IDT_SEGMENT	0x00000240
#define IDT_ADDRESS	0x00002400

#endif
