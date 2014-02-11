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
	void insert(Cell c);
	void update_cell(string value, int position);
	
	/*operators*/
	bool operator==(const Tuple &t) const;
	friend ostream &operator<<(ostream &os, Tuple t){
		for (size_t i = 0; i < t.cells.size(); i++){
			os << t.get_cell_data(i) << '\t';
		}
		os << endl;
		return os;
	}

};

/* End of the Tuple Class */
