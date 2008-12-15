// File:	 $Id: NumberToGuess.h,v 1.2 2004/03/09 01:25:12 jmr8223 Exp $
// Author	 Swami Natarajan
// Contributors: Jim Heliotis
// Description:  Class that represents a number to be guessed
// Revision History:
//	$Log: NumberToGuess.h,v $
//	Revision 1.2  2004/03/09 01:25:12  jmr8223
//	 - allowed for dynamic number of digits to play with
//	
//	Revision 1.1  2004/03/09 00:26:24  jmr8223
//	 - initial commit
//	:
//	
//

	// These two lines are used to prevent problems if the header file
	// gets included repeatedly.

#ifndef NUMBER_TO_GUESS_H
#define NUMBER_TO_GUESS_H

	// We include the string class from the C++ standard library (STL)
	// The using line avoids having to put std:: in front of string
	// and all the other names from the library.

#include <string>
using namespace std;

	// The NumberPair class represents a pair of numbers.
	// This is used to return the score.

#include "NumberPair.h"

	/***************************************************************
	 *
	 * This class represents a Number that is to be guessed.  It is
	 * generated automatically using a random number generator.
	 * The program is currently written to use 4-digit numbers.
	 * 
	 * The user provides guesses that are other 4-digit numbers.
	 * The program scores a "bull" (perfect match) for each of the digits
	 * of the guess that match the Number perfectly i.e. same digit, same
	 * position.  It scores a "cow" (partial match) for other digits
	 * of the guess that are present in the Number, but in the wrong
	 * position.
	 * e.g. if the original number is 3094, and the guess is 0491, 
	 * the score is (1, 2) - 9 is a bull, while 0 and 4 are cows.
	 *
	 * The program will not allow repeated digits in the number or
	 * the guess.
	 *
	 * @author	 Swami Natarajan
	 **************************************************************/

class NumberToGuess {
    public:
	
	/***************************************************************
	 * Constructor: Creates a NumberToGuess using a RandomNumberGenerator.
	 ****************************************************************/

	NumberToGuess( int numDigits );

	/***************************************************************
	 * Destructor: performs any special clean up needed.
	 ****************************************************************/

	~NumberToGuess();


	/***************************************************************
	 * Determines the score for the guess.  Assumes the guess is valid
	 * @param guess: the guessed number to be scored
	 * @return A NumberPair containing the score.
	 ****************************************************************/

	// The word "const" at the end of the method declaration indicates
	// that this method is not allowed to modify the NumberToGuess object

        NumberPair computeScore( string guess ) const;


	/***************************************************************
	 * This method checks if the given number is valid i.e. there are
	 * no repeated digits e.g. 2723 has '2' as a repeated digit.
	 * Numbers with repeated digits are avoided, because they can
	 * confuse the scoring and make playing hard.  This method also
	 * checks for non-numeric guesses.
	 * @return false if there are repeated digits or non-numeric
	 *    stuff, true otherwise
	 ****************************************************************/

	bool isValid (string num) const;

	/***************************************************************
	 * Provide a string suitable for printing when a submitted
	 * number is invalid. Since this class is responsible for
	 * determining the validity of a string, it is also in the
	 * best position to explain what a valid string's properties
	 * are.
	 *
	 * @return a string explaining what makes a number valid
	 ***************************************************************/

	string validityRules() const;

	/***************************************************************
	 * Accessor for the secret number.
	 *
	 * @return the number the user is trying to guess
	 ***************************************************************/
	
	string getNumberToGuess();

    private:

	    // The numberToGuess is stored as a string!  This seems
	    // strange, but the fact is, we only use the individual
	    // digits, never the number itself.  So it is convenient
	    // to use a string for the number

	int numberOfDigits;

	string numberToGuess;

};

#endif
