#pragma once

#include "Cell.h"

/* Declaration of the Tuple Class */

using namespace std;

class Tuple{
private:
	// A vector of the cells in this tuple
	vector<Cell>cells;

public:
	/*constructors*/
	// Constructor
	// Input a vector of attributes for this tuple
	//		a vector of strings that is the values in each cell
	Tuple(vector<Attribute> attributes, vector<string> values);
	
	/*accessors*/
	// Get a list of all the values in each cell
	// Returns a vector of strings that is a list of all the values
	vector<string> get_values() const;
	// Get all of the cells as cells
	// Returns a vector of cells that are in this tuple
	vector<Cell>get_cells() const;
	// Returns the data of a specific cell
	// Input an int that is the position or column of the cell
	// Returns a string that is the data in the requested cell
	string get_cell_data(int position) const;
	// Get the number of cells in the tuple
	// Returns an int that is the number of cells
	int get_num_cells() const;

	/*modifiers*/
	// Change the data in a cell
	// Input a value that is the new data to update to
	//		a int that is the postion or column of the cell to update
	void update_cell(string value, int position);
	
	/*operators*/
	// Compare if two cells are equal
	// Returns a bool, true if they are equal else false
	bool operator==(const Tuple &t) const;
	// Prints the tuple to a output stream
	friend ostream &operator<<(ostream &os, Tuple t);

};

/* End of the Tuple Class */
