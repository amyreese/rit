// File: LinkedStack.h
// Author: John Reese, Brian Flood

// Revisions:
//   $Log: LinkedStack.h,v $
//   Revision 1.2  2004/05/15 21:09:31  jmr8223
//    - stack implementation completed
//    - stack works properly, no memory leaks found
//


#ifndef RITCS_LINKED_STACK
#define RITCS_LINKED_STACK

#include "Stack.h"
#include "Watcher.h"

namespace RITCS {

class LinkedNode;

class LinkedStack : public Stack {

public: // creation

    // constructor
    //
    // Description: allocates a C array to use for the stack
    //
    // Postconditions: size() = 0

    LinkedStack();

	// (Because this class has no data and no mutators, it
	//  does not require a constructor.)

	// destructor
	//
	// Description: deallocates any resources dynamically
	//              allocated by this object
	//
	// (This is a well-advised standard C++ coding practice.)
	//
	~LinkedStack();

private: // prohibited standard operations

	// assignment operator
	//
	// This has not been implemented, so we are disallowing
	// it by making it private. The problem is that it is
	// difficult to allow the copying of one type of stack
	// into another (efficiently).
	//
	LinkedStack &operator=( const LinkedStack & );

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

	int currentsize;
	
	LinkedNode* myTop;

};

class LinkedNode {
        
        public:
        
            LinkedNode( LinkedNode *l, char d );
            
            ~LinkedNode();
            
        public:
        
            LinkedNode *last;
            char data;
        
        private:
        
            Watcher w;
    };

}

#endif
