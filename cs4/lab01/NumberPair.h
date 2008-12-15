// File:	 $Id: NumberPair.h,v 1.1 2004/03/09 00:26:24 jmr8223 Exp $
// Author	 Swami Natarajan
// Contributors: Jim Heliotis
// Description:  Class that represents a pair of numbers
// Revision History:
//	$Log: NumberPair.h,v $
//	Revision 1.1  2004/03/09 00:26:24  jmr8223
//	 - initial commit
//	:
//	
//

	// These two lines are used to prevent problems if the header file
	// gets included repeatedly.

#ifndef NUMBER_PAIR_H
#define NUMBER_PAIR_H

	/***************************************************************
	 *
	 * This class represents a pair of numbers.  Note that it is
	 * redundant: STL, the standard C++ library, already has a 
	 * pair<> class that does this.  We are rewriting it just to
	 * illustrate some things.
	 * 
	 * @author	 Swami Natarajan
	 **************************************************************/

class NumberPair {
    public:
	
	/***************************************************************
	 * Constructor: Creates a NumberPair containing the two provided
	 *    numbers.
	 * @param num1: the first number
	 * @param num1: the second number
	 ****************************************************************/

	NumberPair( int num1, int num2 );

	/****************************************************************
	 * get the first number of the pair
	 * @return the first number
	 ****************************************************************/

	// The word "const" at the end of the method declaration indicates
	// that this method is not allowed to modify the Numberpair object

        int getFirst() const;

	/****************************************************************
	 * get the second number of the pair
	 * @return the second number
	 ****************************************************************/

	// The word "const" at the end of the method declaration indicates
	// that this method is not allowed to modify the Numberpair object

        int getSecond() const;

    private:

	int first;	// The first number

	int second;	// the second number
};

#endif
