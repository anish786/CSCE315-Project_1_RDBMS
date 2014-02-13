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
	bool is_condition;
	//Condition condition;

public:
	//Comparison(Condition cond);
	Comparison(string o1, string o2, string o);
	bool evaluate(vector<string> variables, vector<string> values);
};

