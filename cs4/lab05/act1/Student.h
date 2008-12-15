// File:          $Id: Student.h,v 1.1 2003/04/03 17:49:40 cs4 Exp $
// Author:        Jeremiah D. Brazeau
// Contributors:
// Description:   
// Revisions:     $Log: Student.h,v $
// Revisions:     Revision 1.1  2003/04/03 17:49:40  cs4
// Revisions:     Initial revision
// Revisions:

#ifndef _PERSON_H
#define _PERSON_H

#include <string>

using namespace std;

class Student{

 public: // constructors

  //
  // constructor
  //
  // Create a person with no name and a height of -1.
  //
  Student();	// default constructor needed when creating array

  //
  // constructor
  //
  // Create a person with a default name and the given height
  //
  // Arguments:
  //    howTall:  The height of the person in inches.
  //
  Student( int howTall );

  //
  // destructor
  // 
  // Clean up any dynamically allocated memory associated with this
  // object.
  //
  ~Student();

public: // attribute queries

  //
  // getHeight
  //
  // Return the height of the person in inches
  //
  int getHeight() const;

  //
  // getName
  //
  // Return the persons name
  //
  string getName() const;


private: // attributes
  string name;  // person's full name
  int height;   // person height rounded to the nearest inch

};


#endif
