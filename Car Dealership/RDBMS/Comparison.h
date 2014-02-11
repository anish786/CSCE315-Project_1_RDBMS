#pragma once

#include <vector>
#include <string>

using namespace std;

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

