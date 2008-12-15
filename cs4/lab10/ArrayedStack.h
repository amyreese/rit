// File: ArrayedStack.h
// Author: John Reese, Brian Flood

// Revisions:
//   $Log: ArrayedStack.h,v $
//   Revision 1.3  2004/05/15 20:26:53  jmr8223
//    - fixed implementation / logic errors
//
//   Revision 1.2  2004/05/15 20:02:52  jmr8223
//    - completed basic implementation of ArrayedStack
//
//   Revision 1.1  2004/05/15 19:47:33  jmr8223
//    - initial commit
//


#ifndef RITCS_ARRAYED_STACK
#define RITCS_ARRAYED_STACK

#include "Stack.h"
#include "Watcher.h"

namespace RITCS {

class ArrayedStack : public Stack {

public: // creation

    // constructor
    //
    // Description: allocates a C array to use for the stack
    //
    // Preconditions: startsize >= 0
    // Postconditions: size() = startsize

    ArrayedStack( int startsize );

	// (Because this class has no data and no mutators, it
	//  does not require a constructor.)

	// destructor
	//
	// Description: deallocates any resources dynamically
	//              allocated by this object
	//
	// (This is a well-advised standard C++ coding practice.)
	//
	~ArrayedStack();

private: // prohibited standard operations

	// assignment operator
	//
	// This has not been implemented, so we are disallowing
	// it by making it private. The problem is that it is
	// difficult to allow the copying of one type of stack
	// into another (efficiently).
	//
	ArrayedStack &operator=( const ArrayedStack & );

public: // queries

	// top
	//
	// Returns:	the item most recently pushed on the stack
	// Pre:		stack is not empty
	// Post:	stack is unchanged
	//
	char top() const;

	// empty
	//
	// Returns:	true iff the stack contains no elements
	// Post:	stack is unchanged
	//
	bool empty() const;

	// full
	//
	// Returns:	true iff the stack cannot accept furter elements
	// Post:	stack is unchanged
	//
	bool full() const;

	// size
	//
	// Returns:	the number of elements in the stack
	// Post:	stack is unchanged
	//
	unsigned int size() const;

public: // modifiers

	// push
	//
	// Description:	adds a new element to "the top of" the stack
	// Arguments:	the element to be added
	// Pre:		stack is not full
	// Post:	size has increased by one
	// Post:	top is equal to the argument newElement
	//
	void push( char newElement );

	// pop
	//
	// Description:	removes an element from "the top of" the stack,
	//		i.e., the one most recently added but not yet popped
	// Pre:		stack is not empty
	// Post:	size has decreased by one
	//
	void pop();

private: // garbage memory watcher

	RITCS::Watcher w;
	
	int capacity;
	int currentsize;
	
	char* myStack;

};

}

#endif
