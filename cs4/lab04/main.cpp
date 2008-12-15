// File:        main.cpp
// Author:      John Reese
// Description: Creates an interface for the Calculator class

/**
 *
 * $Id: main.cpp,v 1.4 2004/04/03 20:52:44 jmr8223 Exp $
 *
 * $Log: main.cpp,v $
 * Revision 1.4  2004/04/03 20:52:44  jmr8223
 *  - tweaked output to match specs
 *  - lab completed
 *
 * Revision 1.3  2004/04/03 20:49:02  jmr8223
 *  - completed main function interface
 *  - modified assignment in Calculator.process for readability
 *
 * Revision 1.2  2004/04/03 20:01:31  jmr8223
 *  - initial commit for Calculator.cpp
 *
 * Revision 1.1  2004/03/30 00:36:01  jmr8223
 *  - initial commit of main.cpp
 *
 *
 */

#include "Calculator.h"
#include <string>
#include <iostream>

using namespace std;

int main (int argc, char *argv) {
	Calculator calc;
	string cmd;

  cout << "Starting the calculator simulation\n";
  

	cout << "Enter the operation to be performed: ";
  cin >> cmd;
	
  while (cin) {
    calc.set_command(cmd);
    if ( calc.is_legal_command() ) {
			
      double value, result;

      if ( calc.is_trig_command() ) 
        cout << "Enter the angle in degrees: ";
      else 
        cout << "Enter the parameter for the operation: ";
      
      cin >> value;
      result = calc.process( value );

      cout << "The " << cmd << " of " << value << " is: " << result << endl;
    }
    else {
      cout << cmd << " is not a legal operation!\n";
    }
    cout << "Enter the operation to be performed: ";
    cin >> cmd;
	}

	cout << "\nSimulation complete\n";

	return 0;
}
