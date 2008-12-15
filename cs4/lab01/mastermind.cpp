// File:	 $Id: mastermind.cpp,v 1.3 2004/03/09 01:25:12 jmr8223 Exp $
// Author	 Swami Natarajan
// Contributors: Jim Heliotis
// Description:  main program for the MasterMind game
// Revision History:
//	$Log: mastermind.cpp,v $
//	Revision 1.3  2004/03/09 01:25:12  jmr8223
//	 - allowed for dynamic number of digits to play with
//	
//	Revision 1.2  2004/03/09 01:04:44  jmr8223
//	 - added output of secret number when "quit"ing
//	
//	Revision 1.1  2004/03/09 00:26:24  jmr8223
//	 - initial commit
//	:
//	

	// In C++, class declarations are in header files - .h files
	// Implementation files (.cpp files) must explicitly include the
	// header files for the classes they use

#include "NumberPair.h"
#include "NumberToGuess.h"

	// The include files below are all from the C++ standard library
	// (STL).  <iostream> provides basic i/o capabilities.  cin and cout
	// are the standard input and standard output in C++ respectively.
	// <string> is a very convenient string class.  <fstream> provides
	// file I/O capabilities.  All are very easy to use, as you can
	// see below.
	// The using line avoids having to put std:: in front of every
	// class name from the library.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

	// In C++, execution always starts at a function called main().
	// Note that this is non-object-oriented - this is not a method within
	// any class, but a "global" function.

	// The responsibility of this main program is to provide the user
	// interface.  The real work is all done by the NumberToGuess class
	// (with help from the NumberPair class).  In general, it is best to
	// put practically no functionality in main(), as a matter of good
	// object-oriented design practice.

	// argc is the number of command line arguments and the command itself
	// argv is an array of null terminated byte strings which are the
	//      command line arguments

int main( int argc, char *argv[] ) {
    int numTurns = 0;

	// The game's instructions are in the file welcome.txt. We use
	// the STL file I/O capabilities to display the contents of the
	// file.  All we do is read a series of lines and display them.  

    ifstream infile( "welcome.txt" );	// open the file
    do {
       string line;
       getline( infile, line );	// read a line from the input file
       if ( infile ) {		// check if successful - fails on end-of-file
           cout << line << endl;	// display the line
					// endl adds a newline character
       }
    } while ( infile );		// keep going until end of file

		int numDigits;

		cout << "How many digits? ";
		cin >> numDigits;

		// create the secret number that must be guessed.

    NumberToGuess secretNumber(numDigits);

		// get a series of guesses from the user and score them
		// allow users to quit in the middle if they prefer

    bool done = false;		// whether program is done
    while( !done ) {
        string guess;
        cout << "Enter a " << numDigits;
				cout << "-digit guess, with no repeated digits: ";
        cin >> guess;		// read the guess from the standard input

		// exit on end-of-input or "quit" typed.
	if ( !cin || guess == "quit" ) {
	    done = true;
	    cout << "Sorry, but the number was ";
			cout << secretNumber.getNumberToGuess() << "." << endl;
		// check that it is a valid guess
	} else if ( ! secretNumber.isValid( guess ) ) {
	    cout << secretNumber.validityRules() << endl;

	} else {
		// compute score
	    const NumberPair score = secretNumber.computeScore( guess );
	    cout << "Score: " << score.getFirst() << " " << score.getSecond()
		 << endl;

	    if ( score.getFirst() == numDigits ) {	// 4 bulls is a perfect score
		cout << "Congratulations!  You have won!" << endl;
		if ( numTurns < 6 ) {
		    cout << "And quickly too! "
		         << "You must be a mastermind!" << endl;
		}
		done = true;
	    }
	    numTurns++;
	}
   }	// while (! done )
   cout << endl;
}
