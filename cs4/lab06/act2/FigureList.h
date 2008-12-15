// File:	$Id: FigureList.h,v 1.5 2002/10/23 18:40:52 cs4 Exp $
// Author:	Margaret Reek
// Contributors: idea borrowed from Neil Graham book, and enhanced
// Description:
//	Test the figure classes by creating some and
//	moving them around on the screen.
// Revision History:
//	$Log: FigureList.h,v $
//	Revision 1.5  2002/10/23 18:40:52  cs4
//	Moved Display to be attribute, not automatic var. (jeh)
//
//	Revision 1.4  2002/01/21 14:13:15  cs4
//	Changed name of ListController to FigureList (jeh)
//
//	Revision 1.3  2000/10/11 12:45:05  cs4
//	Removed EXP/SOLN lines (jeh)
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

#ifndef _LISTCONTROLLER_H
#define _LISTCONTROLLER_H

#include <iostream>
#include "Display.h"
#include "Figure.h"
#include <list>

using namespace std;
using namespace RITCSFigures;

class FigureList {

public: // creation

	// Name:        (constructor)
	//
	// Description: create a list of figure objects in a particular order
	// Arguments:   reference to the list to build
	// Modified:	creates the list refered to in the argument
	//
	FigureList();

	// Name:        (destructor)
	//
	// Description: Free up memory allocated by all figures created for
	//		the object list.
	// Modified:	contents of list
	//
	~FigureList();

	// Name:        display_object_list
	//
	// Description: display an arbirtrary list of objects
	// Arguments:   reference to the list
	// Modified:	the display shows the objects in the order they
	//		appear in the list
	//
	void display_object_list();

private: // data

	list< Figure * > l;

	Display canvas;

}; // FigureList

#endif
