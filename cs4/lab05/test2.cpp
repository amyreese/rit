// test2.C

// For your amusement.
// Use this for ideas for your own tests.

#include <string>
#include <iostream>
#include <vector>

#include "Person.h"

using namespace std;

const unsigned int Count( 3 );

static
void printPeople( vector< Person > &pv ) {
	for ( unsigned int i=0; i<pv.size(); i+=1 ) {
		cout << (i+1) << ". " << flush;
		if ( !(pv[i].isNull()) ) {
			cout << pv[i];
		}
		cout << endl;
	}
	cout << endl;
}

int main() {

	vector< Person > people( Count );

	people[ 0 ] = Person( "Doe", "John", 19, "**none**" );
	people[ 2 ] = Person( "Roe", "Jane", 27, "unemployed" );

	printPeople( people );

	people[0].changeLastName( "Po" );
	people[2].passBirthday();
	people[2].passBirthday();

	printPeople( people );
}

