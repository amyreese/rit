// DumbStack.h
// Dysfunctional Stack
// Author: James Heliotis
// Contributors: {}

// Description: A simple class to allow the student's stack tester to compile

// NOTE TO STUDENTS: This class is not up to the standards we require
//	for real code. Almost all proper comments are lacking, and
//	the class's features are not divided into sections
//	("responsibilities").


// To use this, include it in your test program, and link your code
// with DumbStack.o.

#ifndef RITCS_DUMBSTACK
#define RITCS_DUMBSTACK

#include "Stack.h"

namespace RITCS {

class DumbStack: public Stack {

public:

  DumbStack();
  ~DumbStack();

  virtual char top() const;

  virtual bool full() const;

  virtual unsigned int size() const;

  virtual void push( char newElement );

  virtual void pop();

};

}

#endif
