#include "Tuple.h"

/* Definitions of the Tuple Class */

/*constructors -------------------------------------------------------------------------------*/
Tuple::Tuple(vector<Cell> c){
	cells = c;
}

Tuple::Tuple(vector<Attribute*> attributes, vector<string> values){
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
vector<string> Tuple::get_values(){
	vector<string>temp;
	for (size_t i = 0; i < cells.size(); i++){
		temp.push_back(cells[i].get_value());
	}
	return temp;
}

vector<string> Tuple::get_values() const{
	vector<string>temp;
	for (size_t i = 0; i < cells.size(); i++){
		temp.push_back(cells[i].get_value());
	}
	return temp;
}

vector<Cell> Tuple::get_cells(){
	return cells;
}

vector<Cell> Tuple::get_cells() const{
	return cells;
}

string Tuple::get_cell_data(int position){
	return cells[position].get_value();
}

/*modifiers ----------------------------------------------------------------------------------*/

void Tuple::update_cell(string value, int position){
	cells[position].update_data(value);
}

/*operators ----------------------------------------------------------------------------------*/
bool Tuple::operator==(const Tuple &t) const{
	if( t.cells.size() == this->cells.size() )
	{
		for (size_t i = 0; i<t.cells.size(); i++)
		{
			if(t.cells[i] == this->cells[i]){
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
		if(t.cells[i].get_type()==0){
			os << setw(MAX_LENGTH) << t.cells[i].get_value() << '\t';
		}
		else if(t.cells[i].get_type()==1){ // string
			os << setw(MAX_LENGTH) << t.cells[i].get_value() << '\t';
		}
	}
	os << endl;
	return os;
}

/* End of definitions */