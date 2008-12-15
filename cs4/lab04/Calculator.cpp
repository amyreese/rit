// File:         $Id: Calculator.cpp,v 1.4 2004/04/03 20:49:02 jmr8223 Exp $
// Author:       J. Heliotis
// Author:       John Reese
// Contributors: {L. Rixner}
// Description:	 A class that represents a calculator. Commands can be
//               read, processed, and the results printed by the calculator.
// Revisions:
//              $Log: Calculator.cpp,v $
//              Revision 1.4  2004/04/03 20:49:02  jmr8223
//               - completed main function interface
//               - modified assignment in Calculator.process for readability
//
//              Revision 1.3  2004/04/03 20:18:37  jmr8223
//               - completed is_trig_command() and is_legal()
//               - modified if / else structure in process()
//
//              Revision 1.2  2004/04/03 20:14:15  jmr8223
//               - completed process method
//
//              Revision 1.1  2004/04/03 20:01:31  jmr8223
//               - initial commit for Calculator.cpp
//
//

#include <cmath>
#include "Calculator.h" 


const double Calculator::PI( atan2( 0, -0.1 ) );

const std::string Calculator::SIN( "" );
const std::string Calculator::COS( "" );
const std::string Calculator::TAN( "" );
const std::string Calculator::LOG( "" );
const std::string Calculator::LOG10( "" );


//
// Name:	(constructor)
//

Calculator::Calculator() {
	command = "";
}

//
// Name:  process
//

double Calculator::process( double value ) const {
	double result = 0;

  if ( is_trig_command () ) {
    value = ( value / 180 ) * PI;
    if ( command == "sin" ) 
      result = sin ( value );
    
    else if ( command == "cos" ) 
      result = cos ( value );
    
    else 
      result = tan ( value );
  }

  else if ( command == "log" )
    result = log ( value );
    
  else 
    result = log10 ( value );

	return result;
}

//  
// Name:  set_command
//

void Calculator::set_command( std::string cmd ) {
  command = cmd;
}

//
// Name: 	is_legal
//

bool Calculator::is_legal_command() const {
  return command == "log" || command == "log10" || is_trig_command();
}

// Name: 	is_trig

bool Calculator::is_trig_command() const {
  return command == "sin" || command == "cos" || command == "tan";
}

