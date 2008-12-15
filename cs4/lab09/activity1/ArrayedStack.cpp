// File: ArrayedStack.cpp
// Author: John Reese, Brian Flood

// Revisions:
//   $Log: ArrayedStack.cpp,v $
//   Revision 1.2  2004/05/15 20:02:52  jmr8223
//    - completed basic implementation of ArrayedStack
//
//   Revision 1.1  2004/05/15 19:47:33  jmr8223
//    - initial commit
//

#include <cassert>

#include "ArrayedStack.h"

namespace RITCS {

ArrayedStack::ArrayedStack( int startsize ) {
    assert(startsize >= 0);
    
    currentsize = 0;
    capacity = startsize;
    myStack = new char(startsize);
    
    assert(size() == 0);
}

// nothing to clean up
ArrayedStack::~ArrayedStack() {
    delete [] myStack;
}

ArrayedStack &ArrayedStack::operator=( const ArrayedStack & ) {
	// (should never get called)
	assert( false );
	return *this;
}

char ArrayedStack::top() const {
    assert (! empty() );
    return myStack[currentsize-1];
}

bool ArrayedStack::empty() const {
	return size() == 0;
}

bool ArrayedStack::full() const {
    return currentsize == capacity;
}

unsigned int ArrayedStack::size() const {
    return currentsize;
}

void ArrayedStack::push( char newElement ) {
    assert (! full() );
    myStack[currentsize] = newElement;
    currentsize++;
    assert (! empty() );
    assert ( newElement == top() );
}

void ArrayedStack::pop() {
    assert (! empty() );
    currentsize--;
    assert (! full() );
}

}
