#pragma once

#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Helper function
int string_to_int(string s);

class Conjunction;
class Comparison;

class Condition
{
	vector<Conjunction> conjunctions;
public:
	Condition();
	Condition(vector<Conjunction> con);
	bool evaluate(vector<string> variables, vector<string> values);
};

class Conjunction
{
	vector<Comparison> comparisons;
public:
	Conjunction(vector<Comparison> comp);
	bool evaluate(vector<string> variables, vector<string> values);
};

class Comparison
{
	string operand1;
	string operand2;
	string op;
	bool is_condition;
	Condition condition;

public:
	Comparison(Condition cond);
	Comparison(string o1, string o2, string o);
	bool evaluate(vector<string> variables, vector<string> values);
};

