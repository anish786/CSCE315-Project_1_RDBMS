#pragma once

#include <vector>
#include <string>
#include "Conjunction.h"

using namespace std;

class Condition
{
	vector<Conjunction> conjunctions;
public:
	Condition(vector<Conjunction> con);
	~Condition(void);
	bool evaluate(vector<string> variables, vector<string> values);
};

