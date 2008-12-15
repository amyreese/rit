// $Id: Job.h,v 1.1 2004/04/05 22:55:32 jmr8223 Exp $
// Author: James Heliotis
//
// Description: an oversimplified description of a type of employment
//	for use in a laboratory exercise

// Revisions
//	$Log: Job.h,v $
//	Revision 1.1  2004/04/05 22:55:32  jmr8223
//	Initial revision
//
//	Revision 1.2  2001/09/19 14:30:37  cs4
//	2001-1 changes.  tmh.
//
//	Revision 1.1  2001/09/19 14:18:42  cs4
//	Initial revision
//

#ifndef _JOB_H
#define _JOB_H

#include <iostream>
#include <string>

using namespace std;

class Job {

public: // constructors

	// constructor
	//
	// Create a job of the given name
	//
	// Arguments:
	//	jobName: job name
	//
	// Preconditions:
	//	jobName is not empty
	//
	Job( string jobName );


	// copy constructor 
	//
	// Create a copy of the given job
	//
	// Arguments:
	//	other: job to be copied
	//
	Job( const Job &other );


public: // attribute queries

	// getName
	//
	// Return the name of the job
	//
	string getName() const;

private: // attributes

	string name;		// the name (title) of this job

	int id;			//  this job's identifier

	static int instCount;	//  static counter of the # of jobs created

}; // Job

// output inserter
//
ostream &operator<<( ostream &os, const Job &job );

#endif
