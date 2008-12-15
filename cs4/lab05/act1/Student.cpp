// File:          $Id: Student.C,v 1.1 2003/04/03 17:49:40 cs4 Exp $
// Author:        Jeremiah D. Brazeau
// Contributors:
// Description:   
// Revisions:     $Log: Student.C,v $
// Revisions:     Revision 1.1  2003/04/03 17:49:40  cs4
// Revisions:     Initial revision
// Revisions:

#include <cassert>

#include "Student.h"

using namespace std;

Student::Student( int howTall ):
  name( "someName" ), height( howTall ){

  assert( height >= 0 );

}


Student::Student() :
  name("noName"), height( -1 ) {	// dummy invalid values
}


Student::~Student(){
}


string Student::getName() const {
  return name;
}

int Student::getHeight() const {
  return height;
}
