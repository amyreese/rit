// File:	$Id: Display.h,v 1.3 2000/10/11 12:46:20 cs4 Exp $
// Author:	Margaret Reek
// Contributors: idea borrowed from Neill Graham book, and enhanced
// Description:
//	Manipulate the display and the cursor in the display.
//	ANSI character sequences are used to achieve this.
// Revision History: 
//	$Log: Display.h,v $
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

#ifndef RITCSFIGURES_DISPLAY_H
#define RITCSFIGURES_DISPLAY_H

using namespace std;

namespace RITCSFigures {

class Display{

public: // changes to the display

	//
	// Name:	clear
	//
	// Description:	clear the display area
	// Modified:	the display
	//
	void clear();

	//
	// Name:	put
	//
	// Description:	have the argument appear at the current position
	// Arguments:	the character to be shown
	// Modified:	the display
	//
	void put( char ch );

public: // changes to the cursor position

	//
	// Name:	set_cur_postition
	//
	// Description:	move cursor to position specified by r(ow ) and c(column)
	// Arguments:	row and column to move to
	// Modified:	changes the cursor on the display
	//
	void set_cur_pos( int r, int c)  ;


public:  // pause the display

	//
        // Name:        pause
        //
        // Description:     waste time for specified interval
        // Arguments:   the seconds to pause
	// 
        void pause( float time ) const;

public: // queries

	//
	// Name: operator==
	//
	// Description: is the target equal to the argument?
	//              (Answer is always yes, since Display objects
	//               in reality mainain no discernable state.)
	// Arguments:	the object to which to compare the target
	//
	bool operator==( const Display &other );

}; // class DISPLAY

}

#endif
