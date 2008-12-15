// $Id: Person.cpp,v 1.1 2004/04/05 22:55:32 jmr8223 Exp $
// Author:  James Heliotis
// Author:  John Reese
// Author:  Brian Flood - bmf2627
// Description:  A simple Person class for use as a
//               lab exercise to demonstrate the use
//		 of assertions and constructors.
// $Log: Person.cpp,v $
// Revision 1.1  2004/04/05 22:55:32  jmr8223
// Initial revision
//
// Revision 1.5  2002/01/14 14:59:00  cs4
// Added operator=() - jeh
//
// Revision 1.4  2001/09/21 15:50:57  cs4
// fixed typo.
// tmh
//
// Revision 1.3  2001/09/21 15:47:28  cs4
// assert.h -> cassert.  tmh
//
// Revision 1.2  2001/09/19 14:25:09  cs4
// 2001-1 changes.  tmh
//
// Revision 1.1  2001/09/19 14:18:49  cs4
// Initial revision
//


#include <cassert>
#include <string>
#include "Person.h"
#include "Job.h"

using namespace std;

Person::Person () {
  lastName = emptyString;
  firstName = emptyString;
  currentAge = -1;
  currentJob = NULL;
}

Person::Person ( const Person &orig ) {
  lastName = orig.lastName;
  firstName = orig.firstName;
  currentAge = orig.currentAge;
  if ( orig.currentJob == NULL ) {
    currentJob = NULL;
  }
  else {
    currentJob = new Job( *orig.currentJob );
  }
}

Person::Person ( string last, string first, int age, string firstJobName ) {
  assert (first != emptyString);
  assert (last != emptyString);
  assert (age >= 0);

  lastName = last;
	firstName = first;
  currentAge = age;
  if ( firstJobName != noJob ) {
    currentJob = new Job( firstJobName );
  }
  else {
    currentJob = NULL;
  }
}

Person::~Person () {
	delete currentJob;
}

const string Person::emptyString( "" );

const string Person::noJob( "**NONE**" );

int Person::getAge() const {
  assert( lastName != emptyString );
  assert( firstName != emptyString );
  assert( currentAge >= 0 );

  return currentAge;
}

string Person::getName() const {
	assert( lastName != emptyString );
	assert( firstName != emptyString );
	assert( currentAge >= 0 );
	string result( firstName );
	result += " ";
	result += lastName;
	return result;
}

const Job *Person::getJob() const {
  assert( lastName != emptyString );
  assert( firstName != emptyString );
  assert( currentAge >= 0 );


	if (currentJob == NULL) {
    return NULL;
  }
  else {
    return currentJob;
  }
}

bool Person::isNull() const {
  return lastName == emptyString && firstName == emptyString &&
         currentAge == -1 && currentJob == NULL;
}

void Person::changeLastName ( string newLast ) {
  assert ( !isNull() );

	lastName = newLast;
}

void Person::changeJob ( string newJobName ) {
  assert ( !isNull() );

  delete currentJob;
  if ( newJobName == noJob ) {
    currentJob = NULL;
  }
  else {
    currentJob = new Job( newJobName );
  }
}

void Person::passBirthday () {
  assert ( !isNull() );

  currentAge += 1;
}

Person &Person::operator= ( const Person &orig ) {
  if ( this == &orig ) {
    delete currentJob;

    this->lastName = orig.lastName;
    this->firstName = orig.firstName;
    this->currentAge = orig.currentAge;
    if ( orig.currentJob != NULL ) 
      this->currentJob = orig.currentJob;
    else 
      this->currentJob = NULL;
  }

  return *this;
}

ostream &operator<<( ostream &os, const Person &p ) {
	if ( p.isNull() ) {
		os << "NaP";
	}
	else {
		os << p.getName() << " is " <<
		     p.getAge() << " years old and works at " <<
		     (p.getJob()?p.getJob()->getName():string("nothing"));
	}
	return os;
}
