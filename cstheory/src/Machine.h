#ifndef _AT_MACHINE_H_
#define _AT_MACHINE_H_

/**
 * Machine.h
 * Automata Simulator
 *
 * @author John Reese
 */

#include <stack>
#include <string>
#include <vector>

using namespace std;

/**
 * Constants and type definitions
 */

#ifndef MACHINE_DEBUG
#  define MACHINE_DEBUG 0
#endif

#define LAMBDA '_'
#define EMPTY_STACK '_'

struct Transition {
	string destination;
	char symbol;
	string read;
	string write;
};

struct State {
	string name;
	bool accepting;
	vector<Transition*> transits;
};

/**
 * Manages simulated machine, using array of States with arrays of transitions
 */
class Machine 
{

public:
	Machine();
	~Machine();

	void setDebug( int level = MACHINE_DEBUG );

	bool addSymbol( char symbol );
	bool addSymbol( string symbol );

	bool addState( string name, bool accepting = false, bool starting = false );
	bool addTransition( string state, string destination, string symbol, string read = "", string write = "" );

	bool setStarting( string name, bool starting = true );
	bool setAccepting( string name, bool accepting = true );

	bool accepts( string test );

	void dumpMachine();

	static void error( string message, bool ignore = false );

private:
	State* findState( string name );
	bool process( State* position, string value, stack<char> history );
	string stack2string( stack<char> value );

	int debug;

	vector<char> alphabet;
	vector<State*> states;

	State* start;
	State* current;

};

#endif //_AT_MACHINE_H_

