#include "Tuple.h"

/* Definitions of the Tuple Class */

/*constructors -------------------------------------------------------------------------------*/
Tuple::Tuple(){
}

Tuple::Tuple(vector<Cell> c){
	cells = c;
}

Tuple::Tuple(vector<Attribute> attribute, vector<string> values){
	for (size_t i = 0; i < attribute.size(); i++){
		Cell c(attribute[i], values[i]);
		cells.push_back(c);
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

string Tuple::get_cell_index(int index){
	return cells[index].get_value();
}

vector<Cell> Tuple::get_cell(){
	return cells;
}

vector<Cell> Tuple::get_cell() const{
	return cells;
}

/*modifiers ----------------------------------------------------------------------------------*/
void Tuple::insert(Cell c){
	cells.push_back(c);
}

void Tuple::update(string value, int position){
	cells[position].update(value);
}

/*operators ----------------------------------------------------------------------------------*/
bool Tuple::operator==(const Tuple &t) const{
	int count = 0;
	if( t.cells.size() == this->cells.size() )
	{
		for (size_t i = 0; i<t.cells.size(); i++)
		{
			if(t.cells[i] == this->cells[i])
				count++;
			else 
				return false;
		}
	}
	else {
		return false;
	}
	return (count == t.cells.size());
}
/* End of definitions */