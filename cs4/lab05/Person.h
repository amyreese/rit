// $Id: Person.h,v 1.1 2004/04/05 22:55:32 jmr8223 Exp $
// Author: James Heliotis
//
// Description:
//	A simple class representing some attributes of a person: their
//	name, age, and employment status

// Revisions:
//	$Log: Person.h,v $
//	Revision 1.1  2004/04/05 22:55:32  jmr8223
//	Initial revision
//
//	Revision 1.3  2002/01/14 14:59:19  cs4
//	Added operator=() - jeh
//
//	Revision 1.2  2001/09/19 14:30:27  cs4
//	Changes for 2001-1.  tmh
//
//	Revision 1.1  2001/09/19 14:18:58  cs4
//	Initial revision
//

#include <string>

using namespace std;

class Job;

class Person {

public: // constructors

	// constructor 
	//
	// Create a person with the given name, age, and job.
	// If the job name is "**NONE**" (noJob), the job is internally
	// set to NULL (0).
	// The understanding is that the job object belongs
	// to the person object, for memory management purposes.
	//
	// Arguments:
	//	last: last (family) name
	//	first: first (given) name
	//	age: current age of person
	//	firstJobName: name of initial job (noJob implies unemployed)
	//
	// Preconditions:
	//	last & first are not empty (emptyString)
	//	age is not negative
	//
	Person( string last, string first, int age, string firstJobName );

	// copy constructor 
	//
	// Create a Person with the same attributes as the argument
	// Note that two Persons may not share the same job instance.
	//
	// Arguments:
	//	orig: the object to be copied
	//
	Person( const Person &orig );

	// default constructor 
	//
	// Create a Person with illegal attributes.
	// (useful as an "empty object")
	// Sets first and last name to empty string (emptyString),
	// age to -1, and job to null (0).
	//
	Person();

	// destructor 
	//
	// Clean up any dynamically allocated memory
	// associated with this object.
	//
	~Person();

public: // attribute queries

	// getName
	//
	// Return the name of the person: first, a blank,
	// and last, concatenated together.
	//
	// Preconditions:
	//	object is not the default "empty" object
	//
	string getName() const;

	// getAge
	//
	// Return the age of the person.
	//
	// Preconditions:
	//	object is not the default "empty" object
	//
	int getAge() const;

	// getJob
	//
	// Return the person's job. If unemployed, return null (0).
	//
	// Preconditions:
	//	object is not the default "empty" object
	//
	const Job *getJob() const;

	// isNull
	//
	// Return true only if the object is the default "empty" object.
	//
	bool isNull() const;

public: // modifiers

	// assignment operator
	//
	// Modify this Person to have the same attributes as the argument.
	// Note that two Persons may not share the same job instance.
	// This operation does nothing if the argument and target are
	// the same object (this == &orig).
	//
	// Arguments:
	//	orig: the object to be copied
	// Returns:	a reference to the target, to allow
	//		cascading assignments
	//
	Person &operator=( const Person &orig );

	// changeLastName
	//
	// Change the last name attribute of this person.
	//
	// Preconditions:
	//	object is not the default "empty" object
	//
	void changeLastName( string newLast );

	// changeJob
	//
	// Change this person's job. If the new job is noJob ("**NONE**"),
	// this person has become unemployed. The old job object, if
	// there was one, is deallocated.
	//
	// Preconditions:
	//	object is not the default "empty" object
	//
	void changeJob( string newJobName );

	// passBirthday
	//
	// Increase the person's current age by 1.
	//
	// Preconditions:
	//	object is not the default "empty" object
	//
	void passBirthday();

public: // useful constants

	// emptyString
	//
	// the string you get from string's default constructor
	//
	static const string emptyString;

	// noJob
	//
	// the string indicating a Person is unemployed
	// (This is sometimes known as "in-band" signalling; it
	// creates a data value that may not be used as regular
	// data (like "$" in a UNIX shell command, or the
	// infamous "9/9/99" in some 20th century databases).)
	//
	static const string noJob;

private: // attributes

	string lastName;                 // person's last name
	string firstName;		 // person's first name
	int currentAge;			 // person's age
	const Job *currentJob;	         // person's current job

}; // Person


// output inserter
//
ostream &operator<<( ostream &os, const Person &person );
