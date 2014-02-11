#pragma once

#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Helper function
int string_to_int(string s);

class Comparison
{
	string operand1;
	string operand2;
	string op;
public:
	Comparison(string o1, string o2, string o);
	~Comparison(void);
	bool evaluate(vector<string> variables, vector<string> values);
};

