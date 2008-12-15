// File:	$Id: lab6-1.C,v 1.2 2002/01/21 12:52:12 cs4 Exp $
// Author:	Margaret Reek
// Contributors: idea borrowed from Neil Graham book, and enhanced
// Description:
//	Test the figure classes by creating some and
//	moving them around on the screen.
// Revision History:
//	$Log: lab6-1.C,v $
//	Revision 1.2  2002/01/21 12:52:12  cs4
//	Changed final pause to 10 units
//
//	Revision 1.1  2000/10/11 12:46:20  cs4
//	Initial revision
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

#include "Block.h"
#include "Display.h"
#include "Triangle.h"
#include "TextString.h"

using namespace std;

using namespace RITCSFigures;

int main() {

	Display canvas;
	Block block1( 10, 30, canvas, 4, 7 );
	Block block2( 1, 10, canvas, 20, 5 );
	Triangle triangle( 5, 8, canvas, 5 );
	TextString text( 0, 3, canvas, "wait for the next picture" );

	canvas.clear();
	block1.show();
	block2.show();
	text.show_moving( 10, 0, 5, .8 );

	text.hide();
	block1.move_by( 0 ,-15 );
	block2.move_to( 5, 30 );
	text.move_to( 0, 3 );
	text.show_moving( 10, 0, 5, .8 );
	canvas.pause( 5 );

	text.hide();
	canvas.clear();
	block1.show_moving( 7, 1, 5, 1 );
	triangle.show_moving(  7, 1, 5, 1 );
	triangle.change_char( '$' );
	triangle.show_moving(  7, -1, 5, 1 );
	canvas.pause( 5 );

	text.clear_value();
	text.move_to( 0, 3 );
	text.set_value( "All done!" );
	text.show();
	canvas.pause( 10 );

	canvas.clear();

	return 0;
} // main
