#ifndef RITCS_SCANNEREXCEPTION_H
#define RITCS_SCANNEREXCEPTION_H

#include <iostream>
#include <string>

using namespace std;

namespace RITCS4 {

class ScannerException {

public: // error codes

	enum Error { illegalCommand, undeclaredVariable,
	             prematureEOF, redeclaredVariable };

public:	// Constructors/destructors

	//
	// Be sure that you handle memory clean up!
	//


	// constructor
	//
	// Create a scanner exception.
	// Arguments:	code:     what the creator thinks is the problem
	// 		badItem:  the token read that appears to be wrong
	//			(not used for prematureEOF)
	//
	ScannerException( Error errorCode, char *badItem = 0 );

	// copy constructor
	//
	// To be used only when propagating an exception.
	//
	ScannerException( const ScannerException &other );

	// destructor
	//
	// Cleanup a scanner exception.
	//
	virtual ~ScannerException();

public: // Input/output operators

	// Print out an error message based on the data
	// stored in this instance.
	// (See sample solution for format)
	//
	friend ostream &operator<<( ostream &out, const ScannerException &e );

private: // data

	char *item;

	const Error code;

}; //ScannerException

} // namespace RITCS4

#endif
