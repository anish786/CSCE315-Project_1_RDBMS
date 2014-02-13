#pragma once

#include "Cell.h"

/* Declaration of the Tuple Class */

using namespace std;

class Tuple{
private:
	vector<Cell>cells;

public:
	/*constructors*/
	Tuple(vector<Attribute> attributes, vector<string> values);
	
	/*accessors*/
	vector<string> get_values() const;
	vector<Cell>get_cells() const;
	string get_cell_data(int position) const;
	int get_num_cells() const;

	/*modifiers*/
	void update_cell(string value, int position);
	
	/*operators*/
	bool operator==(const Tuple &t) const;
	friend ostream &operator<<(ostream &os, Tuple t);

};

/* End of the Tuple Class */
