// $Id: Stack.cpp,v 1.1 2003/04/27 02:02:26 cs4 Exp cs4 $
// Partial Implementation of Abstract Class Stack
// Author: James Heliotis
// Contributors: {}

// Description: This file holds the implementations of portions of the
//	Stack abstraction that are considered "universal", i.e., independent
//	of the rest of the implementation.

// $Log: Stack.cpp,v $
// Revision 1.1  2003/04/27 02:02:26  cs4
// Initial revision
//

#include <cassert>

#include "Stack.h"

// "Stack" is a common name, so let's avoid name clashes.
namespace RITCS {

Stack::~Stack() {
	// this cannot be made pure virtual!
}

Stack &Stack::operator=( const Stack & ) {
	// (should never get called)
	assert( false );
	return *this;
}

bool Stack::empty() const {
	return size() == 0;
}

}
