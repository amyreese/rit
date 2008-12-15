// File: SymbolTable.cpp
// Author: John Reese
//
// Revisions:
//   $Log: SymbolTable.cpp,v $
//   Revision 1.3  2004/05/01 21:05:33  jmr8223
//   *** empty log message ***
//
//   Revision 1.2  2004/05/01 20:26:55  jmr8223
//   *** empty log message ***
//
//   Revision 1.1  2004/04/19 23:28:30  jmr8223
//    - initial commit
//

#include <string>
#include <map>
#include <iostream>
#include <cassert>

#include "SymbolTable.h"

using namespace std;
using RITCS4::SymbolTable;

typedef map<string, int> SymbolMap;
typedef SymbolMap::value_type value_type;

SymbolTable::SymbolTable () : symbolmap() {
    // postconditions
    assert ( size() == 0 );
}

void SymbolTable::declare ( string name, int init ) {
    // preconditons
    assert ( ! contains(name) );
    
    // add the variable to the table
    symbolmap.insert(value_type( name, init ));
    
    // postconditions
    assert ( contains(name) );
    assert ( get(name) == init );
}

void SymbolTable::set ( string name, int val ) {
    // preconditions
    assert ( contains(name) );
    
    // edit the value in the table
    symbolmap[name] = val;
    
    // postconditions
    assert ( contains(name) );
    assert ( get(name) == val );
}

int SymbolTable::get ( string name ) const {
    // preconditions
    assert ( contains(name) );
    
    SymbolMap::const_iterator it = symbolmap.find(name);
    
    // return the value from the table
    return it->second;
}

unsigned int SymbolTable::size() const {
    return symbolmap.size();
}

bool SymbolTable::contains( string name ) const {
    // its in there if find returns ! end()
    return symbolmap.find(name) != symbolmap.end();
}

void SymbolTable::dump( std::ostream &out ) const {
    for (SymbolMap::const_iterator it = symbolmap.begin(); 
        it != symbolmap.end(); it++ ) {
        
        out << it->first << ": " << it->second << endl;
    }
}
