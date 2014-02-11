#pragma once

#include "Cell.h"

/* Declaration of the Tuple Class */

using namespace std;

class Tuple{
private:
	vector<Cell>cells;

public:
	/*constructors*/
	Tuple(vector<Cell> c);
	Tuple(vector<Attribute*> attributes, vector<string> values);
	
	/*accessors*/
	vector<string> get_values();
	vector<string> get_values() const;
	vector<Cell>get_cells();
	vector<Cell>get_cells() const;
	string get_cell_data(int position);

	/*modifiers*/
	void update_cell(string value, int position);
	
	/*operators*/
	bool operator==(const Tuple &t) const;
	friend ostream &operator<<(ostream &os, Tuple t);

};

/* End of the Tuple Class */
