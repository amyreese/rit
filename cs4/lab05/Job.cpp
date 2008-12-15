// $Id: Job.cpp,v 1.1 2004/04/05 22:55:32 jmr8223 Exp $
// Author: James Heliotis
// Description:  A simple class to demonstrate assertions
//               and constructors.
// Revisions:
//	$Log: Job.cpp,v $
//	Revision 1.1  2004/04/05 22:55:32  jmr8223
//	Initial revision
//
//	Revision 1.2  2001/09/21 15:47:43  cs4
//	assert.h -> cassert.  tmh
//
//	Revision 1.1  2001/09/19 14:18:35  cs4
//	Initial revision
//

#include <cassert>
#include "Job.h"
#include "Person.h"

// constructor
//
Job::Job( string what ): name(what) {
	assert( what != Person::emptyString );
}

// copy constructor
//
Job::Job( const Job &other ): name(other.name) {
}

// getName
//
string Job::getName() const {
	return name;
}

// output inserter
//
ostream &operator<<( ostream &os, const Job &job ) {
	os << "Job{" << job.getName() << '}';
	return os;
}

