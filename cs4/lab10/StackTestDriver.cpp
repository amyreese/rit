// $Id$
// Author: James Heliotis
// Contributors: {John Reese, Brian Flood}
// Description: Drives the stack test program with a specific kind of
// stack. This files must be edited on lines marked "/****/" when a
// different kind of stack is chosen. Note that the size parameter is
// to be ignored if the stack's constructor does not take an argument,
// i.e., if it does not have a maximum size.

// $Log$

#include <iostream>
#include <string>
#include "Stack.h"
#include "LinkedStack.h"
#include "StackTester.h"

using namespace RITCS;
using std::cout;
using std::cerr;

int main( int argc, char *argv[] ) {

	const int MAX_SIZE_TO_TEST = 20;
	int size = MAX_SIZE_TO_TEST;

	switch ( argc ) {
	case 1:
		// Keep defaults.
		break;
	case 2:
		// Set different stack size.
		// (ignored if stack size is unlimited)
		size = atoi( argv[ 1 ] );
		break;
	default:
		cerr << "Usage: " << argv[0] << "[ max-stack-size ]" << endl;
		exit( 1 );
	}

	// Set up the tester.
	
	StackTester tester;

	// Run all the tests.
	Stack *target = ( new LinkedStack() ); 
	
	for ( int testNum( 1 ); tester.legalTestNum( testNum ); ++testNum ) {
		// Note that, in this style of testing, each test
		// starts with a fresh new stack. That may or may
		// not be good.
		tester.setTarget( target );
		cout << "Test " << testNum << endl;
		tester.runTest( testNum );

		}

	delete target;

	return 0;
}

