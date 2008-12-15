// File:         $Id$
// Author:       J. Heliotis
// Contributors: {L. Rixner}
// Description:	 A class that represents a calculator. Commands can be
//               set and computed.
// Revisions:
//              $Log$
//

#ifndef _CALCULATOR_H
#define _CALCULATOR_H

#include <string>

class Calculator {
public: // Constructor

	// Name:	(constructor)
	//
	// Description: Creates the object, initializing the
  // 		'command' to the empty string.

	Calculator();

public: // State changes

	// Name:        set_command
	// Description: Store a command in the calculator's local storage.
  // Modifies:    The internal command.
	//

  void set_command( std::string cmd );

public: // queries

	// 
	// Name:        process
	// Description: Performs the arithmetic operation indicated by
	//              stored command, on the given argument value.
	//		Assumes that the command is legal.
	//		Note that, for the trigonometric functions,
	//		'value' is assumed to be expressed in degrees.
  // Modifies:    Nothing
	// Returns:	The value of the computation on the given argument.
	//

	double process( double value ) const;

	// Name: 	is_legal_command
  // Description: Is the stored command one that can be handled
	// 		by this class? -
	//		("sin", "cos", "tan", "log", or "log10"?)
	// Returns: 	False if the command has never been set or 
	//		if it is not one of the legal commands.

  bool is_legal_command() const; 

	// Name: 	is_trig_command
  // Description: Is the stored command a trig function handled
	// 		by this class? - sin, cos, tan? 
	// Returns: 	False if the command has never been set or 
	//		if it is not one of the trig operations.

  bool is_trig_command() const; 

private: // data members

  std::string command; 	// which operation is to be performed

private: // useful constants

	static const double PI;

	// constants for the various operations, to avoid hardcoding

  static const std::string SIN;
	static const std::string COS;
	static const std::string TAN;
	static const std::string LOG;
	static const std::string LOG10;

}; // Calculator

#endif

