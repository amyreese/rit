// $Id$
// Good implementation of Stack, used to check test code
// Author: James Heliotis
// Contributors: {}

// $Log$

#ifndef RITCS_GOODSTACK
#define RITCS_GOODSTACK

#include "Stack.h"

namespace RITCS {

class GoodStack: public Stack {

public: // creation

	// constructor
	//
	// Description: creates stack whose maximum size is given
	//		by the argument
	// Pre:		maxSize >= 0
	// Post:	empty()
	GoodStack( unsigned int maxSize );

	// destructor
	//
	// Description: deallocates any resources dynamically
	//              allocated by this object
	//
	virtual ~GoodStack();

public: // queries

	// top
	//
	// Returns:	the item most recently pushed on the stack
	// Pre:		stack is not empty
	// Post:	stack is unchanged
	//
	virtual char top() const;

	// full
	//
	// Returns:	true iff the stack cannot accept furter elements
	// Post:	stack is unchanged
	//
	virtual bool full() const;

	// size
	//
	// Returns:	the number of elements in the stack
	// Post:	stack is unchanged
	//
	virtual unsigned int size() const;

public: // modifiers

	// push
	//
	// Description:	adds a new element to "the top of" the stack
	// Arguments:	the element to be added
	// Pre:		stack is not full
	// Post:	size has increased by one
	// Post:	top is equal to the argument newElement
	//
	virtual void push( char newElement );

	// pop
	//
	// Description:	removes an element from "the top of" the stack,
	//		i.e., the one most recently added but not yet popped
	// Pre:		stack is not empty
	// Post:	size has decreased by one
	//
	virtual void pop();

private: // representation

	char *data;
	int topIndex;
	unsigned int maxTop;
};

}

#endif
