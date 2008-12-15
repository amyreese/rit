// File:	$Id$
// Author:	Margaret Reek
// Contributors: {Neil Graham, Jim Heliotis, }
// Description:
//	Test the figure classes by creating some and
//	moving them around on the screen.

// Revisions:
//	$Log$

#include <iostream>
#include "Figure.h"
#include "Block.h"
#include "Triangle.h"
#include "TextString.h"
#include "FigureList.h"
#include <list>
#include <iterator>

using namespace std;
using namespace RITCSFigures;

//
// Name:	constructor
//
FigureList::FigureList(): l(), canvas() {
	Block *block1, *block2;
	Triangle *triangle;
	TextString *text;

    block1 = new Block( 5, 10, canvas, 4, 7 );
    l.push_back ( block1 );
    
    triangle = new Triangle( 5, 8, canvas, 5 );
    l.push_back ( triangle );
    
    text = new TextString( 5, 3, canvas, "Hello, world!" );
    l.push_back ( text );
    
    block2 = new Block( 5, 10, canvas, 20, 5 );
    l.push_back ( block2 );
    
} // create_object_list


//
// Name:	display_object_list
//
void FigureList::display_object_list() {

    canvas.clear();

    for( list< Figure * >::iterator cursor( l.begin() );
	     cursor != l.end();
	     ++cursor ) {
		
	    canvas.set_cur_pos( 1,1 );
	        
	    string s = "I am a ";
	    s += (*cursor)->what_am_i();
	    
	    for ( int x = 0; x < s.size(); x++ ) {
	        canvas.put(s[x]);
	    }
	    
	    (*cursor)->show();
	    
	    canvas.pause(2);
	    canvas.clear();
	    
	}

	// set up a loop that will do the following for each figure
	// in the list.
	// set the screen cursor position to row 1, column 1; 
	// print the words "I am a " followed by the results of 
	// doing a what_am_i on the current object in the list, 
	// and terminate with a new line.
	// Then show the figure, pause the display for 2 units and then
	// clear the canvas before proceeding to the next figure.
	//
	// To learn how to set up an iterator over the list, look
	// at the code below for the destructor. Note the use of
	// four member functions: begin, end, operators ++ and *.
}

//
// Name:	destructor
//
FigureList::~FigureList() {
	for( list< Figure * >::iterator cursor( l.begin() );
	     cursor != l.end();
	     ++cursor ) {
		delete (*cursor);
	}
}

