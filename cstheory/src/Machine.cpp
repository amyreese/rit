/**
 * Machine.cpp
 * Automata Simulator
 *
 * @author John Reese
 */

#include <stdio.h>
#include <stack>
#include <string>
#include <vector>

#include "Machine.h"

using namespace std;

Machine::Machine()
{
	start = NULL;
	debug = MACHINE_DEBUG;
}

/**
 * Go through and cleanup all states and transitions in the machine
 */
Machine::~Machine()
{
	// Go through all states
	vector<State*>::iterator i;
	for (i = states.begin(); i < states.end(); i++)
	{
		State* s = *i;

		// Go through all transitions from each state
		vector<Transition*>::iterator j;
		for (j = s -> transits.begin(); j < s -> transits.end(); j++)
		{
			// Cleanup transition
			delete *j;
		}
		s -> transits.clear();

		// Cleanup state
		delete s;
	}

	states.clear();
}

void Machine::setDebug( int level )
{
	this -> debug = level;
}

/**
 * Add a symbol to the alphabet
 */
bool Machine::addSymbol( char symbol )
{
	// Check for duplicates
	if ( alphabet.end() != find( alphabet.begin(), alphabet.end(), symbol ) ) {
		error( "Duplicate alphabet character specified." );
		return false;
	} else {
		if ( symbol == LAMBDA || symbol == EMPTY_STACK ) {
			return false;
		} else {
			alphabet.push_back( symbol );
			if ( debug > 4 ) {
				dumpMachine();
			}
			return true;
		}
	}
}

bool Machine::addSymbol( string symbol )
{
	if ( symbol.length() == 1 ) {
		return addSymbol( symbol[0] );
	} else {
		return false;
	}
}

/**
 * Add a state to the machine with given name
 */
bool Machine::addState( string name, bool accepting, bool starting )
{
	if ( starting == false || ( starting == true && this -> start == NULL ) ) {
		State* s = new State;
		s->name = name;
		s->accepting = accepting;
		states.push_back( s );
	
		if ( starting == true ) {
			this -> start = s;
		}

		if ( debug > 2 ) {
			dumpMachine();
		}

		return true;
	} else {
		return false;
	}
}

/**
 * Add transition from the origin state to destination state on symbol
 */
bool Machine::addTransition( string origin, string destination, string symbol, string read, string write )
{
	// Make sure we have single characters
	if ( symbol.length() != 1 || read.length() > 1 ) {
		return false;
	}

	// Make sure the transition character is in the machine alphabet
	bool inAlphabet = ( symbol[0] == LAMBDA );
	for ( vector<char>::iterator i = alphabet.begin(); i < alphabet.end(); i++ ) {
		if ( symbol[0] == *i ) { inAlphabet = true; }
	}
	if ( !inAlphabet ) { return false; }

	// Make sure the states are defined
	State* o = findState( origin );
	State* d = findState( destination );
	if ( o == NULL || d == NULL ) {
		return false;
	} else {
		Transition* t = new Transition;
		t -> destination = destination;
		t -> symbol = symbol[0];
		t -> read = read;
		t -> write = write;
		
		o -> transits.push_back(t);

		if ( debug > 3 ) {
			dumpMachine();
		}

		return true;
	}
}

/**
 * Set an existing state as the starting state
 */
bool Machine::setStarting( string name, bool starting )
{
	State* s = findState( name );
	if ( s == NULL || (starting && start != NULL && start != s) ) {
		return false;
	}

	if ( starting && start == NULL ) {
		start = s;
	}
	
	if ( !starting && start == s ) {
		start = NULL;
	}

	return true;
}

/**
 * Set an existing state as the starting state
 */
bool Machine::setAccepting( string name, bool accepting )
{
	State* s = findState( name );
	if ( s == NULL ) {
		return false;
	} else {
		s -> accepting = accepting;
		return true;
	}
}

/**
 * Main point of entry to traversing the machine with a given string
 */
bool Machine::accepts( string test )
{
	if ( debug > 0 ) {
		printf( "Processing string '%s': \n", test.data() );
	}

	if ( start == NULL ) {
		if ( debug > 0 ) {
			printf( "  No starting state. \n" );
		}
		return false;
	} else {
		// Initialize the stack 
		stack<char> history;
		history.push(EMPTY_STACK);

		// Begin recursive search
		bool accepted = process( start, test, history );

		if ( debug > 0 ) {
			printf( "String '%s' %s. \n\n", test.data(), (accepted?"accepted":"rejected") );
		}

		return accepted;
	}
}

/**
 * Recursive processing function to perform depth-first string acceptance
 */
bool Machine::process( State* position, string value, stack<char> history )
{
	if (debug > 1) {
		printf( "  In state '%s' \n", position->name.data() );
	}

	// Base case state, we've gotten here by processing the whole string
	if ( value.length() == 0 ) {
		if ( debug > 0 ) {
			printf( "  String processing complete in state '%s' \n", position->name.data() );
		}
		
		// Make sure our stack is empty, continue recursing on Lambdas otherwise
		if ( history.top() == EMPTY_STACK ) {
			if ( debug > 0 ) {
				printf( "  Stack is empty, and '%s' %s an accepting state. \n", position->name.data(), (position->accepting?"is":"is not") );
			}
			if ( position->accepting ) {
				return true;
			}
		} else {
			if ( debug > 0 ) {
				printf( "  Stack is not empty. \n" );
			}
			// Continue searching with an empty string
			// return false;
		}
	}

	// "Fudge" the next symbol for when we have no more input
	char symbol = LAMBDA;
	if ( value.length() > 0 ) {
		symbol = value[0];
	}

	vector<Transition*>::iterator i;
	stack<char> newhistory;

	// Find transitions from this state with this symbol
	for (i = position->transits.begin(); i < position->transits.end(); i++)
	{
		// Preserve our stack contents (idiot)
		newhistory = history;

		Transition* t = *i;

		// Make sure we're transitioning on the right input symbol (or Lambda) 
		// and we have the right symbol on the top of the stack (or we're not using the stack)
		if ( (t->symbol == symbol || t->symbol == LAMBDA) && (t->read == "" || t->read[0] == history.top()) ) {

			// Buncha debug output
			if (debug > 2) {
				printf( "  String contents: '%s' \n", value.data() );
			}
			if ( debug > 1 ) {
				printf( "    Transition from '%s' to '%s' on '%c' reading '%c' writing '%s' \n", position->name.data(), t->destination.data(), t->symbol, t->read[0], t->write.data() );
			}
			if ( debug > 2 ) {
				printf( "      Stack contents before: '%s' \n", stack2string(newhistory).data() );
			}

			// Pop the read contents from the stack
			if ( t->read.length() > 0 ) {
				newhistory.pop();
			} 
			
			// Push the write string onto the stack
			for ( unsigned int i = t->write.length(); i > 0; i-- ) {
				newhistory.push( t->write[i-1] );
			}
					
			if ( debug > 2 ) {
				printf( "      Stack contents after:  '%s' \n", stack2string(newhistory).data() );
			}

			// Determine where in the input string to start the next step .
			// Pass the whole string on Lambda, or after the first character otherwise
			int substr = ( t->symbol == LAMBDA ? 0 : 1 );

			// Recursive step
			return process( findState(t->destination), value.substr(substr), newhistory );
		}
	}

	// Fall through case, no transitions to follow
	return false;
}

/**
 * Dump a textual representation of the machine to stdout
 */
void Machine::dumpMachine()
{
	printf( "Machine Information: \n" );

	if ( alphabet.size() == 0 ) {
		printf( "  No alphabet defined.\n" );
	} else {
		printf( "  Alphabet: " );
		for (vector<char>::iterator i = alphabet.begin(); i < alphabet.end(); i++)
		{
			printf( "%c ", *i );
		}
		printf( "\n" );
	}

	if ( states.size() == 0 ) {
		printf( "  No states defined.\n" );
	} else {
		for (vector<State*>::iterator i = states.begin(); i < states.end(); i++)
		{
			State* s = *i;
			printf( "  State '%s' ", s -> name.data() );
			if ( s == this -> start ) { 
				printf( "starting " ); 
				if ( s -> accepting ) 
					printf( "and "); 
			}
			if ( s -> accepting ) {
				printf( "accepting" );
			}
			printf( "\n" );

			if ( s -> transits.size() == 0 ) {
				printf( "    No transitions defined.\n" );
			} else {
				for (vector<Transition*>::iterator j = s->transits.begin(); j < s -> transits.end(); j++)
				{
					Transition* t = *j;
					printf( "    Transition to '%s' on '%c' reading '%s' and writing '%s' \n", t->destination.data(), t->symbol, t->read.data(), t->write.data() );
				}
			}
		}
	}

	printf( "\n" );
}

/**
 * Output a message to stderr, and terminate execution based on the 'ignore' parameter
 */
void Machine::error( string message, bool ignore )
{
	fprintf( stderr, (message+"\n").data() );
	if ( ! ignore ) {
		exit( 1 );
	}
}

/**
 * Get a pointer to the first state in the machine with a matching name
 */
State* Machine::findState( string name )
{
	for (vector<State*>::iterator i = states.begin(); i < states.end(); i++)
	{
		State* s = *i;
		if (s -> name == name)
			return s;
	}

	return NULL;
}

/**
 * Dump stack to stdout for debugging
 */
string Machine::stack2string( stack<char> value )
{
	stack<char> dumpstack = value;
	string dumpstring;
	while( ! dumpstack.empty() ) {
		dumpstring.push_back(dumpstack.top());
		dumpstack.pop();
	}
	return dumpstring;
}


//EOF

