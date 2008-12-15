// File:	 $Id: NumberToGuess.cpp,v 1.2 2004/03/09 01:25:12 jmr8223 Exp $
// Author	 Swami Natarajan
// Contributors: Jim Heliotis
// Description:  Implementation of the NumberToGuess class
// Revision History:
//	$Log: NumberToGuess.cpp,v $
//	Revision 1.2  2004/03/09 01:25:12  jmr8223
//	 - allowed for dynamic number of digits to play with
//	
//	Revision 1.1  2004/03/09 00:26:24  jmr8223
//	 - initial commit
//	:
//	
//

	// Include the header file for our class.  In C++, class
	// declarations (method and data member declarations) are separated
	// from class definitions (code for the methods).  The .h file
	// contains the class declarations, while .C files contain class
	// definitions.  The C++ compiler compiles one .C file at a time,
	// and this .C file must #include all the .h files that are needed
	// by it (all the declarations for all the classes and methods
	// referred to in it).

#include "NumberToGuess.h"

	// Include a random number generator class from the RITCS library
	// All the class names in this library are prefixed with RITCS::,
	// but the "using" line avoids the need for us to keep using
	// this prefix.
	
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std; // all library functions are in the std namespace

	// The constructor creates the number to guess.  To do this, it
	// uses a random number generator class, SubtractiveRG.  This class
	// is part of a library of classes created for the use of students
	// in this course, that can be accessed from the Utility Classes
	// link in the course home page.

	// The pick(n) method returns a number in the range [0, n)
	// i.e. 0 <= returnedValue < n

	// Note: We can use the [] operator on strings.

NumberToGuess::NumberToGuess( int x ):numberOfDigits(x) {

  srand( (int)time(0));

  //randomGen.randomizeSeed();		// make it different each time
    const string digits( "0123456789" );

		// generate over and over till there are no repeated digits
    do {
        numberToGuess = "";			// initialize to null string
	for ( int i=0; i<numberOfDigits; i++ ) {
	  int nextDigit = (int) (10 * (rand() / (double)RAND_MAX));
	  //int nextDigit = randomGen.pick (10);
                // append digit to string
            numberToGuess = numberToGuess + digits[ nextDigit ];
	}
    } while ( ! isValid( numberToGuess ) );
    //cout << numberToGuess << endl;
}



	// The destructor is empty - no special cleanup needed
NumberToGuess::~NumberToGuess() {
}



	// This method scores guesses.  It compares each digit of the
	// guess with each digit of the numberToGuess

NumberPair NumberToGuess::computeScore( string guess ) const {
    int numBulls ( 0 );
    int numCows ( 0 );
    for( int i=0; i<numberOfDigits; i++ ) {
	for( int j=0; j<numberOfDigits; j++ ) {
	    if ( guess[i] == numberToGuess[j] ) { 	// digit matched
		if ( i == j ) {			// position matched
		    numBulls++;
	   	}
		else {
		    numCows++;
		}
	    }
	}
    }
	// construct a NumberPair object containing the results and return it
    return NumberPair( numBulls, numCows );
}

			
	// Check validity: non-numerics and repeated digits are invalid

string NumberToGuess::validityRules() const {
	return string( "the guess must be " ) +
	       (char)( '0' + numberOfDigits ) +
	       " digits, and contain no repeated digits";
}

bool NumberToGuess::isValid( string num ) const {
    bool valid = false;
    if ( num.length() == numberOfDigits ) {
        valid = true;
        for ( int i=0; i<num.length(); i++ ) {
           if ( num[i] < '0' || num[i] > '9' ) {
	       valid = false;
           }
           for (int j=0; j<num.length(); j++ ) {
	       if ( i != j && num[i] == num[j] ) {
	           valid = false;
	       }
           }
        }
    }
    return valid;
}

// getNumberToGuess
string NumberToGuess::getNumberToGuess() {
	return numberToGuess;
}
