// $Id: Scanner.cpp,v 1.3 2004/05/01 22:41:07 jmr8223 Exp $
// Author: James Heliotis
// Contributors: {}

// Description: Scans *and*interprets* tiny language programs

// Revisions:
//	$Log: Scanner.cpp,v $
//	Revision 1.3  2004/05/01 22:41:07  jmr8223
//	 - completed lab
//	
//	Revision 1.1  2004/05/01 21:10:25  jmr8223
//	 - initial commit
//	
//

#include <iostream>
#include "Scanner.h"

using namespace std;

namespace RITCS4 {

const string Scanner::Declare( "declare" );
const string Scanner::Set( "set" );
const string Scanner::Print( "print" );
const string Scanner::End( "end" );

// constructor
//
Scanner::Scanner(): table() {
}

// readAndInterpret
//
void Scanner::readAndInterpret( istream &inFile ) {

	string token;
	string variable;
	int number;

	inFile >> token;
	while( !inFile.eof() && token != End ) {
		if ( token == Declare ) {
			inFile >> variable;
			
			table.declare( variable );
		}
		else if ( token == Set ) {
			inFile >> variable;
			inFile >> number;
			if ( inFile.fail() ) {
			    cerr << "Illegal integer value.\nExiting." << endl;
			    exit(1);
			}
			else if ( ! table.contains ( variable ) ) {
			    cerr << "Variable " << variable 
			         << " has not been declared." << endl;
			}
			else {
			    table.set( variable, number );
			}
		}
		else if ( token == Print ) {
			inFile >> variable;
			cout << table.get( variable ) << endl;
		}
		else {
		    cerr << "Illegal token: " << token << endl;
		}
		inFile >> token;
	}
	if (inFile.eof()) {
	    cerr << "Premature end of file." << endl;
	}
}

// postMortem
//
void Scanner::postMortem() {
	cout << endl;
	cout << "Post-Mortem:";
	cout << endl;
	cout << "============";
	cout << endl;
	cout << endl;
	table.dump( cout );
}

}
