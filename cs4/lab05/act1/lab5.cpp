// File:          $Id: lab5.C,v 1.2 2003/04/07 17:01:13 cs4 Exp cs4 $
// Author:        Jeremiah D. Brazeau
// Contributors:
// Description:   
// Revisions:     $Log: lab5.C,v $
// Revisions:     Revision 1.2  2003/04/07 17:01:13  cs4
// Revisions:     Changed the number of students created to 30
// Revisions:
// Revisions:     Revision 1.1  2003/04/03 17:49:40  cs4
// Revisions:     Initial revision
// Revisions:

//#include <SubtractiveRG.h>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "StudentCounter.h"
#include "Student.h"

int main() {

  // Create a PeopleCounter
  StudentCounter pplCount;

  // Create a random number generator
  //SubtractiveRG randomGen;
  //randomGen.randomizeSeed();	// initialize random number generator
  srand( (int)time(0) );

  for( int i = 0; i < 30; i++ ) {

    //    int tempPersonHeight = 20 + randomGen.pick( 60 );
    int tempPersonHeight = 20 + (int)(60*(rand()/(double)RAND_MAX));
		// height chosen randomly to be between 20 and 80 inches

    Student temp( tempPersonHeight );	// create a temporary Person object

    // add ther person to the people counter.
    pplCount.addPerson( temp );
  }

  // Sort and print the people counter.
  pplCount.sort();
  pplCount.print();

}
