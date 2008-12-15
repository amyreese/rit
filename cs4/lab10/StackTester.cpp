// $Id: StackTester.cpp,v 1.1 2004/05/07 01:54:17 jmr8223 Exp $
// Author: James Heliotis
// Contributors: {John Reese, Brian Flood}

// Description: Run some tests on a stack implementation.

// $Log: StackTester.cpp,v $
// Revision 1.1  2004/05/07 01:54:17  jmr8223
//  - completed Stack testing bull shizzle
//  - found issues with all stacks
//  - docced issues in chart file
//

#include <iostream>
#include <cassert>
#include "Stack.h"
#include "StackTester.h"

using namespace std;

namespace RITCS {

// constructor (nothing to do)
//
StackTester::StackTester(): NumTests( 5 ), t( 0 ) {
}

// setTarget
//
void StackTester::setTarget( RITCS::Stack *testee ) {
	assert( testee );
	t = testee;
}

// legalTestNum
//
bool StackTester::legalTestNum( int n ) {
	return n > 0 && n <= NumTests;
}

// runTest
//
void StackTester::runTest( int testNum ) {
	assert( legalTestNum( testNum ) );
	switch( testNum ) {
	case 1:
	    printStatus();
		break;	
 
	case 2:
	    printStatus();	
	    t->push( 'a' );
	    printStatus();
	    t->push( 'b' );
	    printStatus();
	    t->push( 'c' );
	    printStatus();    
		break;
		
    case 3:
	    printStatus();
	    t->pop();
	    printStatus();
	    t->pop();
	    printStatus();
	    t->pop();
	    printStatus(); 
		break; 
			
	case 4:
	    for ( char a = 'd' ; a < 'x'; a ++ ) {
	        t->push( a );	        
    	  }
	    printStatus();
		break; 
		
	case 5:
	    while ( !t->empty() ) {
	        t->pop();	        
	      }
	    printStatus();
		break; 
		
	default:
		cerr << "Bad test number (see precondition)." << endl;
	}
}

// printStatus
//
void StackTester::printStatus() {
	cout << t->size() << " elements (" <<
	     (t->empty()?"*** EMPTY":"not empty") << ',' <<
	     (t->full()?"*** FULL":"not full") << ')';
	if ( !t->empty() ) {
		cout << " Top is " << t->top();
	}
	cout << endl << flush;
}

} // RITCS
