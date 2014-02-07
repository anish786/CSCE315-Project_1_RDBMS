#include <cstdlib>
#include "Parser.h"

using namespace std;

Parser::Parser(){
}

Parser::~Parser(){
}

void Parser::parse(const string& input) {
	if (input.substr(0, 10) == "OPEN ") {
		sscanf_s(input.c_str() + 10, "%s", playerId);
		int q1 = input.find('"');
		int q2 = input.rfind('"');
		if (q1 != string::npos
			&& q2 != string::npos
			&& q2 - q1 > 2) {
			*playerName = input.substr(q1 + 1, q2 - q1 - 1);
		}
	}
}
