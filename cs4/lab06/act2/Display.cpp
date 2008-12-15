// File:	$Id: Display.C,v 1.3 2000/10/11 12:45:05 cs4 Exp $
// Author:	Margaret Reek
// Contributors: idea borrowed from Neill Graham book, and enhanced
// Description:
// 	Manipulate the display and the cursor in the display.
// 	ANSI character sequences are used to achieve this.
// Revision History: 
//	$Log: Display.C,v $
//	Revision 1.3  2000/10/11 12:45:05  cs4
//	Lengthened pause time (jeh)
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

#include "Display.h"
#include <iostream>

using namespace std;

namespace RITCSFigures {

//
// Name:	clear
//
void Display::clear() {
	cout << "\033[2J" << flush;
} // clear

//
// Name:	put
//
void Display::put( char ch ) {
	cout << ch << flush;
} // clear

//
// Name:	set_cur_postition
//
void Display::set_cur_pos( int r, int c) {
	cout << "\033[" <<  r << ';'  << c << 'H'  ;
} // set_cur_pos

//
// Name:        pause
//
void Display::pause( float time ) const {
        long count, x;

        cout << flush;
        for( count = 0; count < 6000000L * time; count += 1) {
                x = x + count;
                // do nothing but waste time
        }
} // pause

//
// Name: operator==
//
bool Display::operator==( const Display &other ) {
	//We are using tty control codes, so there is no state we can check.

	return true;
} // display

}

