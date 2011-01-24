/**
 * automata.cpp
 * Automata Simulator
 *
 * @author John Reese
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <options.h>

#include "Machine.h"

#define VERSION "0.5"
#define YEAR 2007

using namespace std;

/**
 * External function implemented elsewhere.
 */
int tolua_machine_open( lua_State* tolua_S );

/**
 * Return position of next word in a string
 */
int nextWord( string line )
{
	unsigned int pos,space,tab;

	// Get position of next tab or space
	space = line.find_first_of(" ");
	tab = line.find_first_of("\t");

	// Decide which one is closest
	if ( tab == string::npos ) {
		pos = space;
	} else if ( space == string::npos ) {
		pos = tab;
	} else {
		pos = min( tab, space );
	}

	while ( line[pos] == ' ' || line[pos] == '\t' ) {
		pos++;
	}
	
	return pos;
}
	
/**
 * Remove whitespace surrounding a string
 */
string trim( string line )
{
	unsigned int pos = 0;
	unsigned int rpos = line.length() - 1;

	while ( line[pos] == ' ' || line[pos] == '\t' || line[pos] == '\n' ) {
		pos++;
	}

	while ( line[rpos] == ' ' || line[rpos] == '\t' || line[rpos] == '\n' ) {
		rpos--;
	}

	string result = line.substr( pos, rpos-pos+1 );
	return result; 
}

/**
 * Function exported to Lua.  Given a string as input, breaks the string into
 * individual words and returns an integer indexed table.
 */
int tokenize( lua_State* lua )
{
	// Make sure we've been passed a string
	string input = luaL_checkstring( lua, -1 );

	// Initialize a Lua table
	lua_newtable( lua );

	int i = 1;
	unsigned int pos;

	// Loop through string removing tokens one at a time
	while ( input.length() > 0 )
	{
		pos = nextWord( input );

		// Extract the token and erase it from the string
		string tmp = input.substr( 0, pos-1 );
		if ( pos != string::npos ) {
			input = input.erase( 0, pos );
		} else {
			input.clear();
		}

		// Append the token to a Lua table
		if ( tmp != "" && tmp != " " && tmp != "\t" && tmp != "\n" ) {
			lua_pushnumber( lua, i++ ); //key
			lua_pushstring( lua, trim(tmp).data() ); //value
			lua_settable( lua, -3 ); //table
		}
	}

	return 1; // One return value (table)
}

/**
 * Function exported to Lua.  Grabs a line of input from stdin.  
 * At EOF, returns nil.
 */
int inputLine( lua_State* lua )
{
	int inputSize = 1024;
	char input[inputSize];
	char* result;

	// Read a line from stdin
	result = fgets( input, inputSize, stdin );

	// Check for EOF
	if ( NULL == result && feof( stdin ) ) {
		lua_pushnil( lua ); 
	} else {
		int length = inputSize;

		// Find the end of the input line
		for (int i = 0; i < inputSize; i++)
		{
			if ( input[i] == '\n' ) {
				length = i;
				break;
			}
		}

		lua_pushlstring( lua, trim(input).data(), length );
	}	

	return 1; // One return value (string)
}

/**
 * Function exported to Lua.  Simple printf to stderr.
 */
int machine_printerr( lua_State* lua )
{
	// Get string to print out
	string input = luaL_checkstring( lua, -1 );

	fprintf( stderr, "%s\n", input.data() );

	return 0;
}

/**
 * Function exported to Lua.  Simply here for interactive users' benefit.
 */
int machine_help( lua_State* lua )
{
	printf("\n");
	printf("  Machine object API - Lua modules Base, Math, String, and Table loaded.\n");
	printf(" ------------------------------------------------------------------------------\n");
	printf("  Create a new Machine object:    m = Machine:new()\n");
	printf("  Add a symbol to the alphabet:   m:addSymbol(symbol)\n");
	printf("  Add a state to the machine:     m:addState(name,accept=false,start=false)\n");
	printf("  Add a transition:        m:addTransition(start,symbol,dest,read='',write='')\n");
	printf("  Set the starting state:         m:setStarting(name)\n");
	printf("  Set an accepting state:         m:setAccepting(name)\n");
	printf("  Test a string:                  value = m:accepts(string)\n");
	printf("  Set debugging level (0,1,2,3):  m:setDebug(level)\n");
	printf("  Print out machine structure:    m:dumpMachine()\n");
	printf("\n");

	return 0; // No return values
}

/**
 * Initialize Lua interpreter with packages and one-off exports. 
 */
lua_State* lua_init()
{
	char buff[256];
	int error;

	lua_State *l = lua_open();

	// Load base functions
	lua_pushcfunction( l, luaopen_base );
	lua_pushstring( l, "" );
	lua_call( l, 1, 0 );

	// Load math functions
	lua_pushcfunction( l, luaopen_math );
	lua_pushstring( l, "" );
	lua_call( l, 1, 0 );

	// Load string functions
	lua_pushcfunction( l, luaopen_string );
	lua_pushstring( l, "" );
	lua_call( l, 1, 0 );

	// Load table functions
	lua_pushcfunction( l, luaopen_table );
	lua_pushstring( l, "" );
	lua_call( l, 1, 0 );

	// One-off exports
	lua_register( l, "inputLine", inputLine );
	lua_register( l, "tokenize", tokenize );
	lua_register( l, "help", machine_help );
	lua_register( l, "printerr", machine_printerr );

	// Machine object interface
	tolua_machine_open( l );

	return l;
}

/**
 * Print usage message.  Must be updated by hand to match optv[].
 */
void usage()
{
	printf( "Usage: automata [-i | -l <filename>] [-h] \n" );
}

/**
 * Print author/version information. Based on preprocessor flags.
 */
void version()
{
	printf( "Automata Version %s\nJohn Reese, %i\n", VERSION, YEAR );
}

/**
 * Available command line options
 */
const char* optv[] = {
	"i|interactive",
	"l:lua-file <filename>",
	"h|help",
	"v|version",
	NULL };

/**
 * Parse command line options, set up Lua interpreter, and intiate control method.
 */
int main ( int argc, char* argv[] )
{
	// Prepare for options parsing
	Options opts( *argv, optv );
	OptArgvIter optsiter( --argc, ++argv );
	const char *optarg, *str = NULL;
	int optchar;

	int errors = 0;
	bool interactive = false;
	string luafile = "";

	// Parse command line options 
	while ( optchar = opts( optsiter, optarg ) )
	{
		switch( optchar )
		{
		case 'i': 
			interactive = true;
			if (luafile != "") { errors++; }
			break;
		case 'l':
			luafile = optarg;
			if (interactive || luafile == "") { errors++; }
			break;
		case 'h': 
			usage();
			exit(0);
			break;
		case 'v':
			version();
			exit(0);
			break;
		default: errors++;
		}
	}

	// Output usage information if there are any options input errors.
	if (errors > 0) {
		usage();
		exit(1);
	}

	// Set up the Lua interpreter
	lua_State* lua = lua_init();

	if ( interactive ) { // Interactive mode
		printf( "Automata interactive Lua interpreter version %s.\n", VERSION );
		printf( "Execute 'help()' for API info. Use Ctrl-D to send EOF and quit. \n" );

		int inputSize = 1024;
		char input[inputSize];
		char* result;

		do { // Continuously get lines of input and execute it in the interpreter
			printf( "> " );
			result = fgets( input, inputSize, stdin );
			if (result != NULL ) {
				luaL_loadstring( lua, input );
				int error = lua_pcall( lua, 0, 0, 0 );
				if (error) { // Pass Lua errors to console and continue.
					fprintf( stderr, "Lua Error: %s \n", lua_tostring( lua, -1 ) );
					lua_pop( lua, 1 );
				}
			}

		} while ( result != NULL && !feof(stdin) );
		printf( "\n" );

	} else { // Use a Lua control file
		if (luafile == "") { luafile = "automata.lua"; }
		luaL_loadfile( lua, luafile.data() );
		int error = lua_pcall( lua, 0, 0, 0 );

		if (error) { // Pass Lua errors to console and terminate.
			fprintf( stderr, "Lua Error: %s \n", lua_tostring( lua, -1 ) );
			lua_pop( lua, 1 );
			lua_close(lua);
			return 1;
		}
	}

	// Done
	lua_close(lua);
	return 0;
}


