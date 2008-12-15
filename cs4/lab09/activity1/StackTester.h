// $Id$
// Author: James Heliotis
// Contributors: {}

// $Log$

#ifndef STACKTESTER
#define STACKTESTER

#include <string>
#include "Stack.h"

using namespace std;

namespace RITCS {

/**
 * Run some tests on a stack implementation.
 *
 * @author James Heliotis
 * @author A STUDENT WHO FORGOT TO PUT HER/HIS NAME IN THE PROGRAM
 */

class StackTester {

public: // setup

	/**
	 * Create this stack tester.
	 */
	StackTester();

public: // test execution

	/**
	 * Establish the target of the test.
	 *
	 * @param testee pointer to Stack to be tested
	 */
	void setTarget( Stack *testee );

	/**
	 * See if this tester has a test of the given number.
	 *
	 * @param testNum the number of the test
	 */
	bool legalTestNum( int testNum );

	/**
	 * Execute the indicated test on the stack.
	 *
	 * @param testNum the number of the test to be performed
	 * @pre legalTestNum( testNum )
	 */
	void runTest( int testNum );

private: // utility functions

	/**
	 * Print to standard out all relevant information
	 * on the stack being tested.
	 */
	void printStatus();

private: // data storage

	const int NumTests;

	Stack *t;

};

} // RITCS

#endif
