// File:	$Id: TextString.C,v 1.4 2001/10/03 13:12:23 cs4 Exp $
// Author:	Margaret Reek
// Contributors: idea borrowed from Neill Graham book, and enhanced
// Description:
//	Place a text string on the canvas and erase it
// Revision History: 
//	$Log: TextString.C,v $
//	Revision 1.4  2001/10/03 13:12:23  cs4
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

#include "TextString.h"
#include <string>
#include <cassert>

using namespace std;

namespace RITCSFigures {

//
// Name:	(constructor)
//
TextString::TextString( int r, int c, Display &d, 
			string s ):
    text_value( s ), Figure( r, c, d ) {
} // (constructor)


//
// Name:	set_value
//
void TextString::set_value( string s ) {
        text_value =  s ;
} // set_value

//
// Name:	clear_value
//	
void TextString::clear_value() {
        text_value = " ";
} // clear_value


//
// Name:	what_am_i
//
string TextString::what_am_i() const {
        return "TextString";
} // what_am_i


//
// Name:	display
//
void TextString::display( char ch ) {
        // Note: because strings have their own value, we use "ch"
        // not as the "brush" but as an indicator of whether the
        // string should be displayed or hidden.  If "ch" is a space
        // we hide the string, else display it.

        unsigned int count;

	unsigned int the_row( get_row() );
	unsigned int start_column( get_column() );

        for( count = 0; count < text_value.length(); count += 1 ) {
		get_canvas().set_cur_pos( the_row, start_column+count );
        	if ( ch != ' ' ) {
        		// Paint the string
        		get_canvas().put( text_value[ count ] );
		}
        	else {
        		// Hide the string from the canvas
        		get_canvas().put( ' ' );
        	}
        }
} // display

}
