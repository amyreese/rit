// File:	$Id: Figure.C,v 1.4 2001/10/03 13:10:17 cs4 Exp $
// Author:	Margaret Reek
// Contributors: idea borrowed from Neill Graham book, and enhanced
// Description:
// 	Generic class to manage figures.
// 	Actions specific to any individual shape are deferred.
// Revison History:
//	$Log: Figure.C,v $
//	Revision 1.4  2001/10/03 13:10:17  cs4
//	changed assert.h to cassert.  tmh
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

#include "Display.h"
#include "Figure.h"
#include <string>
#include <iostream>
#include <cassert>


using namespace std;

namespace RITCSFigures {

//
// Name:	(constructor)
//
Figure::Figure( int r, int c, Display &d ):
    row( r ), column( c ), canvas( d ), paint_char( '*' ) {
	assert( ( r >= 0 ) && ( c >= 0 ) );
	object_count += 1;
} // (constructor)


//
// Name:        (copy constructor)
//
Figure::Figure( const Figure &other ) :
    row( other.row ), column( other.column ), canvas( other.canvas ), 
    paint_char( other.paint_char ) {
	object_count += 1;
} // copy constructor

//
// Name:	(destructor)
//
Figure::~Figure() {
	object_count -= 1;
}

unsigned int Figure::object_count( 0 );

//
// Name:	how_many
//
unsigned int Figure::how_many() {
	return object_count;
}

//
// Name:        operator= 
//
void Figure::operator=( const Figure &other ) {
	if( &other != this ){
		row = other.row;
		column = other.column;
		canvas = other.canvas;
		paint_char = other.paint_char;
	}
} // operator=

//
// Name:        operator==
//
bool Figure::operator==( const Figure &other ) const {
	return	( row == other.row ) &&
		( column == other.column ) &&
		( canvas == other.canvas ) &&
		( paint_char == other.paint_char );
} // operator==

//
// Name:	change_char
//
void Figure::change_char( char ch ) {
	paint_char = ch;
} // change_char

//
// Name:	show
//
void Figure::show() {
        display( paint_char );
} // show

//
// Name:	hide
//
void Figure::hide() {
        display( ' ' );
} // hide


//
// Name:	move_by
//
void Figure::move_by(  int delta_r, int delta_c ){
        hide();
        row = row + delta_r;
        column = column + delta_c;
        show();
} // move_by

//
// Name:	move_to
//
void Figure::move_to( int r, int c ) {
	assert( (r >= 0 ) && (c >= 0 ) );
        hide();
        row = r;
        column = c;
        show();
	assert( (row == r) && (column == c) );
} // move_to


//
// Name:	show_moving
//
void Figure::show_moving( unsigned int repeats, int delta_r, int delta_c,
                          float time) {

        unsigned int count;
        show();

        for( count = 1; count <= repeats; count += 1 ) {
        	canvas.pause( time );
        	move_by( delta_r, delta_c );
        } 
    } // show_moving



//
// Name:	get_row
//
int Figure::get_row() const {
	return row;
} // get_row

//
// Name:	get_column
//
int Figure::get_column() const {
	return column;
} // get_column

//
// Name:	get_canvas
//
Display& Figure::get_canvas() {
	return canvas;
} // get_canvas

}

