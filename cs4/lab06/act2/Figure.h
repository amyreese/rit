// File:	$Id: Figure.h,v 1.5 2001/10/03 13:11:48 cs4 Exp $
// Author:	James Heliotis
// Contributors: idea borrowed from Neill Graham book,
//	and enhanced by Margaret Reek
// Description:
//	Generic class to manage figures.
//	Actions specific to any individual shape are deferred.
//	NOTE!! Computer graphics standard is that Y (row#) increases
//		downward, and X (col#) increases to the right!
// Revison History:
//	$Log: Figure.h,v $
//	Revision 1.5  2001/10/03 13:11:48  cs4
//	coding standards.  tmh
//
//	Revision 1.4  2001/10/03 13:10:42  cs4
//	*** empty log message ***
//
//	Revision 1.3  2000/10/11 12:46:20  cs4
//	term 20001 (jeh)
//
//	Revision 1.2  2000/07/24 15:52:34  cs4
//	Working version using STL
//	Changed ListController to use ctor/dtor
//	Change Figure to count its instances
//	(jeh)
//
//	Revision 1.1  2000/07/24 14:43:21  cs4
//	Initial revision
//
//

#ifndef RITCSFIGURES_FIGURE_H
#define RITCSFIGURES_FIGURE_H

#include "Display.h"
#include <string>

using namespace std;

namespace RITCSFigures {

class Figure  {

public:  // creation

	//
	// Name:	(constructor)
	//
	// Description:	create a figure specifying where to put it 
	//		via r(ow), c(olumn)
	// 		and d(display)
	//		update the count of allocated figures
	// Arguments:	row, column, display object
	// Modified:	row, column and display are initialized to arguments
	//
	Figure( int r, int c, Display &d );

	//
	// Name:	(copy constructor)
	//
	// Description:	create a figure as a copy of another
	//		update the count of allocated figures
	// Arguments:	reference to the other object
	// Modified:	makes this object same as other
	//
	Figure( const Figure &other );

	//
	// Name:	(destructor)
	//
	// Description: update the count of allocated figures
	//
	~Figure();

private: // creation statistics

	static unsigned int object_count;

public: // creation statistics

	//
	// Name:	how_many
	//
	// Description:	answers how many figures have been allocated
	//		but not yet deallocated
	//
	static unsigned int how_many();

public:	// operators

	//
	// Name:	operator= 
	//
	// Description:	make a copy of a figure
	// Arguments:	figure to make a copy of
	// Modified:	data members of this object are same as other's
	//
	void operator=( const Figure &other ) ;

	//
	// Name:	operator== 
	//
	// Description:	compare this object to another
	// Arguments:	reference to another object
	// Returned:	TRUE is same, else FALSE
	//
	bool operator==( const Figure &other ) const;

public: // state changes

	//
	// Name:	change_char
	//
	// Description:	change the drawing character (used in show())
	//		to a new one
	// Argument:	character to draw with
	// Modified:	paint_char takes on value of ch
	//
	void change_char( char ch ) ;

public: // Canvas changes

	//
	// Name:	show
	//
	// Description:	show the current figure as a series of  characters
	// Modified:	the display is updated to show the figure
	//
	void show() ;

	//
	// Name:	hide
	//
	// Description:	hide the current figure by rewriting with blanks
	// Modified:	the display is updated to remove the figure
	//
	void hide() ;


	//
	// Name:	move_by
	//
	// Description:	move the current figure 'delta_r' rows and
	// 		'delta_c' columns.
	// Arguments:	the number of rows and columns to move by
	// Modified:	the display shows the figure in a new position
	//
	void move_by( int delta_r, int delta_c ) ;

	//
	// Name:	move_to
	//
	// Description:	move the current figure to the row and column specified
	// Arguments:	the row and column to move to

	void move_to( int r, int c ) ;

	//
	// Name:	show_moving
	//
	// Description:	show a figure moving across the canvas for the number of
	//		times in repeats, moving by the amount in delta_r (rows)
	// 		and delta_c (columns) and pausing by the time indicated 
	//		between each move
	// Modified:	the display shows the figure in a series of new 
	//		positions
	// Arguments:	the number of repeats, the change in rows, change 
	//		in columns
	//		how much time between moves
	//
	void show_moving( unsigned int repeats, int delta_r, int delta_c,
	                  float time );


public: // deferred public features

	//
	// Name:	what_am_i
	//
	// Description:	tell what kind of figure this is
	// Returned:	String containing name of class - deferred
	//
	virtual string what_am_i() const = 0;

public:	// Accessor functions

	//
	// Name:	(accessors)
	//
	// Description:	accessor functions
	// Returned:	the corresponding data member
	//
	int get_row() const;
	int get_column() const;
	Display &get_canvas();

private: // deferred features

	//
	// Name:	display
	//
	// Description:	Paint the specific figure on the canvas
	// Arguments:	the character to draw with
	//		(argument is included so hide() can call this
	//		with a blank character)
	// Modified:	the display is updated with the figure
	//
	virtual void display( char ch )  = 0 ;

private: // representation

	// character to use as the "paint brush"- default is '*'
	char paint_char;

	// Position on the screen
	int row;		//  coordinate for row (across)
	int column;		//  coordinate for col (up/down)

	// Screen manipulation
	Display &canvas;

}; // class Figure

}

#endif
