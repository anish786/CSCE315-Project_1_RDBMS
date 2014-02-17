#pragma once

#include <iostream>
#include <string>

using namespace std;

// generic run-time exception
class RuntimeException {
	// An error message
	string errorMsg;
public:
	// Contructor that takes a string for the error message
	RuntimeException(const string& err) { errorMsg = err; }
	// Returns a the error message
	string getMessage() const { return errorMsg; }
};

// Prints the error message out to a output stream
inline std::ostream& operator<<(std::ostream& out, const RuntimeException& e)
{
   out << e.getMessage();
   return out;
}

