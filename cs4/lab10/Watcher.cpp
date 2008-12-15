// $Id$
//
// Author: Jim Heliotis
//	(November 1991)

// Description:
//	a nice object component to make sure all instances get destroyed

// Revisions:
//	$Log$

#include "Watcher.h"

namespace RITCS {

// Watcher::active
//
int Watcher::active( 0 );

// for testing
int Watcher::getActive() {
    return active;
 }
 

// ShutDown::instance
//
ShutDown ShutDown::instance;

// Watcher::report
//
void Watcher::report() {
    std::cerr << std::endl << "Watcher report: "<< active << " active instances\n";
}

// Watcher ctor
//
Watcher::Watcher() {
	active++;
}

// Watcher dtor
//
Watcher::~Watcher() {
	active--;
}

// ShutDown ctor
//
ShutDown::ShutDown() {
}

// ShutDown dtor
//
ShutDown::~ShutDown() {
	Watcher::report();
}

}

