// File:          $Id: StudentCounter.C,v 1.3 2003/04/08 21:52:26 cs4 Exp cs4 $
// Author:        Jeremiah D. Brazeau
// Contributors:
// Description:   
// Revisions:     $Log: StudentCounter.C,v $
// Revisions:     Revision 1.3  2003/04/08 21:52:26  cs4
// Revisions:     Initialize numPeople to -1
// Revisions:
// Revisions:     Revision 1.2  2003/04/08 21:42:51  cs4
// Revisions:     Changed the first error that the students see to be a definition error in
// Revisions:     the header file
// Revisions:
// Revisions:     Revision 1.1  2003/04/03 17:49:40  cs4
// Revisions:     Initial revision
// Revisions:

#include <iostream>
//#include <ctime>
//#include <cstdlib>
#include "StudentCounter.h"

using namespace std;

StudentCounter::StudentCounter() :
  numPeople( 0 ),
  currentMax( 10 ),
  personArray( new Student[currentMax] ) {
}


StudentCounter::~StudentCounter() {
}


void StudentCounter::addPerson( Student &person ) {

  // Increase the size of the array if we have outgrown the
  // current one.
  if( numPeople >= currentMax ) {

    // Create a new array which is 10 larger then the last.
    Student* temp = new Student[currentMax + 10];

    // Copy over everyone from the old array.
    for( int i = 0; i < currentMax; i++ ) {
      temp[i] = personArray[i];
    }

    // Delete the old array
    delete[] personArray;	// delete the old array

    // Assign the new array back to personArray
    personArray = temp;

    // Increase the count specifing the size of our array.
    currentMax += 10;
  }

  // Add the new person to the end of the array.
  personArray[numPeople] = person;
  numPeople++;

}


void StudentCounter::print() const {

  // Loop through the array and print the persons name and height
  for( int i = 0; i < numPeople; i++ ){
    cout << personArray[i].getName() << " " 
	 << personArray[i].getHeight() << endl;
  }
}



void StudentCounter::sort(){

  // Perform an insert sort.
  for( int i = 0; i < numPeople; i++ ){
    for( int j = 0; j < numPeople; j++ ){
      if( personArray[j].getHeight() < personArray[i].getHeight() ){
	Student temp = personArray[i];
	personArray[i] = personArray[j];
	personArray[j] = temp;
      }
    }
  }

}




