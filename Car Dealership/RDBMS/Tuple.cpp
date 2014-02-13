#include "Tuple.h"

/* Definitions of the Tuple Class */

/*constructors -------------------------------------------------------------------------------*/

Tuple::Tuple(vector<Attribute> attributes, vector<string> values){
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
vector<string> Tuple::get_values() const{
	vector<string>temp;
	for (size_t i = 0; i < cells.size(); i++){
		temp.push_back(cells[i].get_value());
	}
	return temp;
}

vector<Cell> Tuple::get_cells() const{
	return cells;
}

string Tuple::get_cell_data(int position) const{
	return cells[position].get_value();
}

int Tuple::get_num_cells() const{
	return cells.size();
}

/*modifiers ----------------------------------------------------------------------------------*/

void Tuple::update_cell(string value, int position){
	cells[position].update_data(value);
}

/*operators ----------------------------------------------------------------------------------*/
bool Tuple::operator==(const Tuple &t) const{
	if( t.cells.size() == cells.size() )
	{
		for (size_t i = 0; i<t.cells.size(); i++)
		{
			if(t.cells[i] == cells[i]){
				//do nothing
			}
			else {
				return false;
			}
		}
	}
	else {
		return false;
	}

	return true;
}

ostream &operator<<(ostream &os, Tuple t){
	for (size_t i = 0; i < t.cells.size(); i++){
		os << t.cells[i].get_value() << '\t';
	}
	os << endl;
	return os;
}

/* End of definitions */