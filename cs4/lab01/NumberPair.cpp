// File:	 $Id: NumberPair.cpp,v 1.2 2004/03/09 01:04:44 jmr8223 Exp $
// Author	 Swami Natarajan
// Contributors: Jim Heliotis
// Description:  Implementation of the NumberPair class
// Revision History:
//	$Log: NumberPair.cpp,v $
//	Revision 1.2  2004/03/09 01:04:44  jmr8223
//	 - added output of secret number when "quit"ing
//	
//	Revision 1.1  2004/03/09 00:26:24  jmr8223
//	 - initial commit
//	:
//	
//

#include "NumberPair.h"

	// The constructor initializes the data members using the arguments.
	// The syntax is a special "member initialization" syntax, that
	// allows data members to be initialized "during construction".
	// On the other hand, code that is placed between the { and }
	// executes after the object has been constructed.

NumberPair::NumberPair( int num1, int num2 ) :
    first( num1 ),
    second( num2 ) {
}


	// The accessors are trivial

int NumberPair::getFirst() const {
    return first;
}

int NumberPair::getSecond() const {
    return second;
}
