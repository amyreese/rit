// File:	$Id: Triangle.C,v 1.4 2001/10/03 13:14:29 cs4 Exp $
// Author:	Margaret Reek
// Contributors: idea borrowed from Neill Graham book, and enhanced
// Description:
//	A class that can create and draw a solid triangle
// Revision History: 
//	$Log: Triangle.C,v $
//	Revision 1.4  2001/10/03 13:14:29  cs4
//	assert.h to cassert.  tmh
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

#include <string>
#include "Triangle.h"
#include <cassert>

using namespace std;

namespace RITCSFigures {

//
// Name:	(constructor)
//
Triangle::Triangle ( int r, int c, Display &d, int h ):
    height( h ), Figure( r, c, d ) {
        assert( h >= 0 );
} // constructor


//
// Name:	what_am_i
//
string Triangle::what_am_i() const {
	return "Triangle";
} // what_am_i


//
// Name:	display
//
void Triangle::display( char ch ) {
        int index, index2;

	// for each row in the height, determine the position to start
	// drawing from, and then draw the appropriate number of characters
	// to represent the width of the triange
	//
        for ( index = 0; index < height; index += 1 ) {
    		get_canvas().set_cur_pos( ( get_row() + index ), 
					  ( get_column() - index ) );

		for ( index2 = -index; index2 < index; index2 += 1 ) {
                	get_canvas().put( ch );
                } 
        }
} // display

}

