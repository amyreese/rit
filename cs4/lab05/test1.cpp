// test1.C

// For your amusement.
// Use this for ideas for your own tests.

#include <string>
#include <iostream>

#include "Person.h"

using namespace std;

int main() {
	Person john( "Doe", "John", 19, "Internal Affairs" );
	Person jane( "Roe", "Jane", 27, "External Affairs" );
	Person santa( "Ho", "Ho", 500, "**NONE**" );

	cout << john << endl;
	cout << jane << endl;
	cout << santa << endl;

	john.changeLastName( "Po" );
	jane.passBirthday();
	jane.passBirthday();
	jane.changeJob( "President" );
	santa.changeJob( "Venizen Butcher" );

	cout << john << endl;
	cout << jane << endl;
	cout << santa << endl;

}

