// Scanner.h
// Author: James Heliotis
// Contributors: {}

// Description: Scans *and*interprets* tiny language programs

#ifndef RITCS4_SCANNER_H
#define RITCS4_SCANNER_H

#include <iostream>
#include "SymbolTable.h"

namespace RITCS4 {

class Scanner {
public: // creation

	// constructor
	//
	// Initialize the scanner to an "empty" state
	//
	Scanner();

	// readAndInterpret
	//
	// Read a Tiny Language (TL) program from the given file
	// and execute it.
	// Arguments:	inFile:	the source program
	// Pre:	inFile is open (not checkable for all types of streams)
	//
	void readAndInterpret( std::istream &inFile );

	// postMortem
	//
	// Dump out the final values of all the variables in
	// this format:
	//	<empty line>
	//	Post-Mortem:
	//	============
	//	<do a SymbolTable dump>
	// Pre:	readAndInterpret has been called
	//
	void postMortem();

private: // storage

	SymbolTable table;

private: // keywords

	static const string Declare;
	static const string Set;
	static const string Print;
	static const string End;

}; // Scanner

}

#endif
