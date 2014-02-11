#pragma once

#include <vector>
#include <string>
#include "Comparison.h"

using namespace std;

class Conjunction
{
	vector<Comparison> comparisons;
public:
	Conjunction(vector<Comparison> comp);
	~Conjunction(void);
	bool evaluate(vector<string> variables, vector<string> values);
};
