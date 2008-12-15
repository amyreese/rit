// File:          $Id: StudentCounter.h,v 1.4 2003/04/08 21:51:20 cs4 Exp cs4 $
// Author:        Jeremiah D. Brazeau
// Contributors:
// Description:   
// Revisions:     $Log: StudentCounter.h,v $
// Revisions:     Revision 1.4  2003/04/08 21:51:20  cs4
// Revisions:     *** empty log message ***
// Revisions:
// Revisions:     Revision 1.2  2003/04/07 17:01:30  cs4
// Revisions:     Initialized the currentMax before the array is declared.
// Revisions:
// Revisions:     Revision 1.1  2003/04/03 17:49:40  cs4
// Revisions:     Initial revision
// Revisions:

#ifndef _PEOPLECOUNTER_H
#define _PEOPLECOUNTER_H

#include <string>
#include "Student.h"

class StudentCounter{

public: // constructors  

  //
  // constructor
  // 
  // Create a people counter and initialize all data
  // members. 
  //
  StudentCounter();

  //
  // destructor
  //
  // Clean up any dynamicall allocated memory associated with 
  // this object.
  //
  ~StudentCounter();


public: // modifiers/queries

  //
  // addPerson 
  // 
  // Add a person to this counter.
  //
  // Attributes:
  //   person:  The person to add.
  //
  void addPerson( Student &person );

  //
  // print
  // 
  // Print all the members of this person counter.
  //
  void print() const;
  
  //
  // sort
  //  
  // Sort all of the people in the person counter by
  // their height.
  //
  void sort();


private: // attributes

  int currentMax; // The current size of the array
  Student*  personArray; //The array of people.
  int numPeople;         //The number of people in the array

};

#endif 

