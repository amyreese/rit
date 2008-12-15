// $Id: SymbolTable.h,v 1.3 2004/05/01 20:26:55 jmr8223 Exp $
// Author: James Heliotis
// Contributors: John Reese
// Description: A symbol table whose symbols are integer variables

// Revisions:
//	$Log: SymbolTable.h,v $
//	Revision 1.3  2004/05/01 20:26:55  jmr8223
//	*** empty log message ***
//	
//	Revision 1.1  2004/04/19 23:28:30  jmr8223
//	 - initial commit
//	
//
//

#ifndef RITCS4_SYMBOLTABLE
#define RITCS4_SYMBOLTABLE

#include <iostream>
#include <string>
#include <map>

using std::string;

namespace RITCS4 {

class SymbolTable {

public: // creation

	// constructor
	//
	// Description:	creates an empty symbol table
	// Post:	size() is 0
	//
	SymbolTable();

public: // element operations

	// declare
	//
	// Description:	Add a newly declared variable to the table
	// Arguments:	name: variable name
	//		init: initial integer value
	// Pre:		!contains( name )
	// Post:	contains( name )
	// Post:	variable named by 'name' has the value of 'init'
	//
	void declare( string name, int init = 0 );

	// set
	//
	// Description:	Change the value of a variable in the table
	// Arguments:	name: variable name
	// 		val: new integer value
	// Pre:		contains( name )
	// Post:	contains( name )
	// Post:	variable named by 'name' has the value of 'val'
	//
	void set( string name, int val );

	// get
	//
	// Returns:	The value of the variable
	// Argument:	name: variable name
	// Pre:		contains( name )
	// Post:	table is unchanged
	//
	int get( string name ) const;

public: // table queries

	// size
	//
	// Returns:	the number of variables currently in the table
	// Post:	returned value >= 0
	//
	unsigned int size() const;

	// contains
	//
	// Returns:	true iff a variable with given name is in the table
	// Argument:	name: name of variable being sought
	// Post:	table is unchanged
	//
	bool contains( string name ) const;

	// dump
	//
	// Description: display the contents of the table on the given
	//		output stream. Each line contains one variable
	//		listing of the form "<variable>: <value>"
	//		The listing is sorted by variable name.
	// Arguments:	out:	where the dump will be written
	// Post:	table is unchanged
	void dump( std::ostream &out ) const;

private: // storage

  // using a map for the key/value pair abilities and built in functions
  std::map < string, int > symbolmap;

}; // SymbolTable

} // RITCS4

#endif
