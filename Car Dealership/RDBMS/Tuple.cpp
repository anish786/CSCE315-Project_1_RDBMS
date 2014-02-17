#include "Tuple.h"

/* Definitions of the Tuple Class */

/*constructors -------------------------------------------------------------------------------*/
// Constructor
// Input a vector of attributes for this tuple
//		a vector of strings that is the values in each cell
Tuple::Tuple(vector<Attribute> attributes, vector<string> values){
	// Check to make sure there are the same number of sttributes as values
	if(attributes.size() == values.size()){
		for (size_t i = 0; i < attributes.size(); i++){
			Cell c(attributes[i], values[i]);
			cells.push_back(c);
		}
	}
	else{
		throw RuntimeException("Different number of attributes and values");
	}
}

/*accessors ----------------------------------------------------------------------------------*/
// Get a list of all the values in each cell
// Returns a vector of strings that is a list of all the values
vector<string> Tuple::get_values() const{
	vector<string>temp;
	for (size_t i = 0; i < cells.size(); i++){
		temp.push_back(cells[i].get_value());
	}
	return temp;
}

// Get all of the cells as cells
// Returns a vector of cells that are in this tuple
vector<Cell> Tuple::get_cells() const{
	return cells;
}

// Returns the data of a specific cell
// Input an int that is the position or column of the cell
// Returns a string that is the data in the requested cell
string Tuple::get_cell_data(int position) const{
	if (position >= 0 && (size_t)position < cells.size()){
		return cells[position].get_value();
	}
	else{
		throw RuntimeException("Position out of bounds for cell list");
	}
}

// Get the number of cells in the tuple
// Returns an int that is the number of cells
int Tuple::get_num_cells() const{
	return cells.size();
}

/*modifiers ----------------------------------------------------------------------------------*/
// Change the data in a cell
// Input a value that is the new data to update to
//		a int that is the postion or column of the cell to update
void Tuple::update_cell(string value, int position){
	cells[position].update_data(value);
}

/*operators ----------------------------------------------------------------------------------*/
// Compare if two cells are equal
// Returns a bool, true if they are equal else false
bool Tuple::operator==(const Tuple &t) const{
	if( t.cells.size() == cells.size() )
	{
		for (size_t i = 0; i<t.cells.size(); i++)
		{
			if (!(t.cells[i] == cells[i])){
				return false;
			}
		}
	}
	else {
		return false;
	}

	return true;
}

// Prints the tuple to a output stream
ostream &operator<<(ostream &os, Tuple t){
	for (size_t i = 0; i < t.cells.size(); i++){
		os << t.cells[i].get_value() << '\t';
	}
	os << endl;
	return os;
}

/* End of definitions */