// File:	$Id: Block.h,v 1.3 2000/10/11 12:46:20 cs4 Exp $
// Author:	Margaret Reek
// Contributors: idea borrowed from Neill Graham book, and enhanced
// Description:
//	A class that can create and draw a solid rectangular block
// Revision History: 
//	$Log: Block.h,v $
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

#ifndef RITCSFIGURES_BLOCK_H
#define RITCSFIGURES_BLOCK_H

#include <string>
#include "Figure.h"

using namespace std;

namespace RITCSFigures {

class Block: public Figure {


public: // creation
	//
	// Name:	(constructor)
	//
        // Description:	create block at position r(ow), c(column), on display d
        // 		of h(eight) and w(idth) specified
	// Arguments:	row, column, display object, height and width
	// Modified:	row, column, height, width and display are
	//		initialized to argument values
	// Assertions:	row, column, height and width in args. must each be
	//		>= 0
	//
	Block ( int r, int c, Display &d, int h, int w );

public: // identification

	//
        // Name:        what_am_i
        //
        // Description: return a string that tells what kind of object this is
        // Returned:    a string containing the name of the class
	//
	virtual string what_am_i() const;

private:  // canvas changes

	//
	// Name:	display
	// 
	// Description:	paint the figure on the canvas using ch as the "brush"
	// Arguments:	the character to draw the figure with
	// Modified:	the canvas is changed
	//
	virtual void display( char ch ) ;

private:   // Representation

	int height, width;

}; // class Block

}

#endif
