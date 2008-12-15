// File: LinkedStack.cpp
// Author: John Reese, Brian Flood

// Revisions:
//   $Log: LinkedStack.cpp,v $
//   Revision 1.2  2004/05/15 21:09:31  jmr8223
//    - stack implementation completed
//    - stack works properly, no memory leaks found
//

#include <cassert>

#include "LinkedStack.h"

namespace RITCS {

LinkedStack::LinkedStack() : myTop(0) {
    currentsize = 0;
    
    assert(size() == 0);
}

// nothing to clean up
LinkedStack::~LinkedStack() {
    while (size() != 0) {
        pop();
    }
}

LinkedStack &LinkedStack::operator=( const LinkedStack & ) {
	// (should never get called)
	assert( false );
	return *this;
}

char LinkedStack::top() const {
    assert (! empty() );
    return myTop->data;
}

bool LinkedStack::empty() const {
	return size() == 0;
}

bool LinkedStack::full() const {
    return false;
}

unsigned int LinkedStack::size() const {
    return currentsize;
}

void LinkedStack::push( char newElement ) {
    assert (! full() );
    
    LinkedNode *newTop = new LinkedNode(myTop, newElement);
    myTop = newTop;
    
    currentsize++;
    assert (! empty() );
    assert ( newElement == top() );
}

void LinkedStack::pop() {
    assert (! empty() );
    
    LinkedNode *newTop = myTop->last;
    delete myTop;
    myTop = newTop;
    
    currentsize--;
    assert (! full() );
}

LinkedNode::LinkedNode( LinkedNode *l, char d ) : last(l), data(d), w() {
                
}

LinkedNode::~LinkedNode() {
    //delete this;
}

}
