// tli.cpp
// Author: James Heliotis

// Description: Execute programs written in TL (Tiny Language)

#include "Scanner.h"

using namespace RITCS4;

int main() {
	Scanner scanner;
	scanner.readAndInterpret( std::cin );
	scanner.postMortem();

	return EXIT_SUCCESS;
}
