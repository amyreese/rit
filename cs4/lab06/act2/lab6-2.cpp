// File:	$Id: lab6-2.C,v 1.2 2002/01/21 14:13:15 cs4 Exp $
// Author:	Margaret Reek
// Contributors: idea borrowed from Neil Graham book, and enhanced
// Description:
//	Test the figure classes by creating some and
//	moving them around on the screen.
// Revision History:
//	$Log: lab6-2.C,v $
//	Revision 1.2  2002/01/21 14:13:15  cs4
//	Changed name of ListController to FigureList (jeh)
//
//	Revision 1.1  2000/10/11 12:46:20  cs4
//	Initial revision
//
//	Revision 1.2  2000/07/24 15:52:34  cs4
//	Working version using STL
//	Changed FigureList to use ctor/dtor
//	Change Figure to count its instances
//	(jeh)
//
//	Revision 1.1  2000/07/24 14:43:21  cs4
//	Initial revision
//
//

#include "FigureList.h"
#include <list>

using namespace std;
using namespace RITCSFigures;

int main() {

	{
		FigureList controller;

		controller.display_object_list();
	}

	cout << "There are " << Figure::how_many() <<
		" figures left." << endl;

	return 0;
} 
