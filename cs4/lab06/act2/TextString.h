// File:	$Id: TextString.h,v 1.3 2000/10/11 12:46:20 cs4 Exp $
// Author:	Margaret Reek
// Contributors: idea borrowed from Neill Graham book, and enhanced
// Description:
//	Place a text string on the canvas and erase it
// Revision History: 
//	$Log: TextString.h,v $
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

#ifndef RITCSFIGURES_TEXTSTRING_H
#define RITCSFIGURES_TEXTSTRING_H

#include "Figure.h"
#include <string>

using namespace std;

namespace RITCSFigures {

class TextString : public Figure {


public: // creation

	//
	// Name:	(constructor)
	//
	// Description:	create the string s at location r(ow), c(olumn)
        // 		on display d
	// Arguments:	row, column, display area, string to print
	// Modified:    row, column, height, width and display are
	//              initialized to argument values
	// Assertions:	row and column arguments must be >= 0
	//
	TextString( int r, int c, Display &d, string s );

public: // accessor functions

	//
	// Name:	set_value
	//
	// Description:	give a new value for the string
	// Argument:	new string
	// Modified:	text_string takes on value of argument
	//
	void set_value( string s ) ;

	//
	// Name:	clear_value
	//
	// Description:	make the string empty
	// Modified:	text_string is set to null string
	//
	void clear_value() ;


public: // identification

	//
	// Name:	what_am_i
	//
	// Description:	identify the kind of object
	// Returned:	a string containing the name of the class
	//
 	virtual string what_am_i() const ;

private: // canvas changes

	//
	// Name:	display
	//
	// Description:	paint the string on the canvas.
	// Argument:	a space - if we wish to "hide" the string
	//		anything else - if we wish to show the string
	// Modified:	the canvas is changed
	//
	virtual void display( char ch ) ;

private: // representation

        // The text string to display
	string text_value;

}; // Text_string

}

#endif
