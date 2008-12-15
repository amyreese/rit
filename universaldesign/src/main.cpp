/**
 * main.cpp
 * Program startup.
 *
 * @author John Reese
 */

#include <QApplication>

#include "Unicalc.h"

/**
 * This function initializes the Qt application handler.  It then spawns the 
 * Unicalc main window and passes execution to the Qt framework.
 */
int main ( int argc, char *argv[] )
{
	Q_INIT_RESOURCE(images);

	QApplication app(argc, argv);
	Unicalc unicalc;
	unicalc.show();

	return app.exec();
}

// EOF

