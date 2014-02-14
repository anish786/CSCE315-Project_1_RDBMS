#pragma once

#include <vector>
#include <string>
#include <sstream>
#include "RuntimeException.h"

using namespace std;

// Converts a string to an integer
int string_to_int(string s);

//Forward Declarations
class Conjunction;
class Comparison;

class Condition
{
	// Alist of Conjunctions to || together
	vector<Conjunction> conjunctions; 
public:
	// Default Constructor
	Condition();
	// Constructor that takes in a list of conjuctions
	Condition(vector<Conjunction> con);
	// ||'s the evaluation of all Conjuctions together
	// input is variables and corresponding values for replacement in comparisons
	// returns a bool
	bool evaluate(vector<string> variables, vector<string> values);
};

class Conjunction
{
	// A list of Comparisons to && together
	vector<Comparison> comparisons;
public:
	// Constructor that takes in a list of comparisons
	Conjunction(vector<Comparison> comp);
	// &&'s the evaluation of all Comparisons together
	// input is variables and corresponding values for replacement in comparisons
	// returns a bool
	bool evaluate(vector<string> variables, vector<string> values);
};

class Comparison
{
	// Operands can be strings or integers, and if they match a variable they will be replaced during evalutation

	// First operand
	string operand1;
	// Second operand
	string operand2;
	// The operation to perform
	string op;

	// If this is true then this comparison is actually a condition
	bool is_condition;
	// The condition that this comparison is if is_condition is true
	Condition condition;

public:
	// Constructor to make this comparison a condition
	Comparison(Condition cond);
	// Constructor to make this comparsion a comparison
	Comparison(string o1, string o2, string o);
	// Evaluates operand1 op operand2 or if is_condition is true evaluates condition
	// inputs variables and corresponding values for replacement during comparsion
	// returns a bool
	bool evaluate(vector<string> variables, vector<string> values);
};

