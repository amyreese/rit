// $Id: Stack.h,v 1.1 2003/04/27 02:02:26 cs4 Exp cs4 $
// Abstract Class Stack
// Author: James Heliotis
// Contributors: {}

// Description: The abstraction for a Last-In-First-Out data structure
//	In order to avoid template issues, classes implementing this
//	abstraction can only hold items of type char.

// $Log: Stack.h,v $
// Revision 1.1  2003/04/27 02:02:26  cs4
// Initial revision
//

#ifndef RITCS_STACK
#define RITCS_STACK

#include "Watcher.h"

// "Stack" is a common name, so let's avoid name clashes.
namespace RITCS {

class Stack {

public: // creation

	// (Because this class has no data and no mutators, it
	//  does not require a constructor.)

	// destructor
	//
	// Description: deallocates any resources dynamically
	//              allocated by this object
	//
	// (This is a well-advised standard C++ coding practice.)
	//
	virtual ~Stack();

private: // prohibited standard operations

	// assignment operator
	//
	// This has not been implemented, so we are disallowing
	// it by making it private. The problem is that it is
	// difficult to allow the copying of one type of stack
	// into another (efficiently).
	//
	Stack &operator=( const Stack & );

public: // queries

	// top
	//
	// Returns:	the item most recently pushed on the stack
	// Pre:		stack is not empty
	// Post:	stack is unchanged
	//
	virtual char top() const = 0;

	// empty
	//
	// Returns:	true iff the stack contains no elements
	// Post:	stack is unchanged
	//
	virtual bool empty() const;

	// full
	//
	// Returns:	true iff the stack cannot accept furter elements
	// Post:	stack is unchanged
	//
	virtual bool full() const = 0;

	// size
	//
	// Returns:	the number of elements in the stack
	// Post:	stack is unchanged
	//
	virtual unsigned int size() const = 0;

public: // modifiers

	// push
	//
	// Description:	adds a new element to "the top of" the stack
	// Arguments:	the element to be added
	// Pre:		stack is not full
	// Post:	size has increased by one
	// Post:	top is equal to the argument newElement
	//
	virtual void push( char newElement ) = 0;

	// pop
	//
	// Description:	removes an element from "the top of" the stack,
	//		i.e., the one most recently added but not yet popped
	// Pre:		stack is not empty
	// Post:	size has decreased by one
	//
	virtual void pop() = 0;

private: // garbage memory watcher

	RITCS::Watcher w;

};

}

#endif
