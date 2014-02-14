#include "Cell.h"
#include "Condition.h"

/* Definitions of the Cell Class */

/*constructors ------------------------------------------------------------------------------*/
// Constructor requring an attribute for cell type info and the value as a string
Cell::Cell(Attribute a, string value){
	if(a.get_attribute_type() == 1){
		if((int)value.size() <= a.get_attribute_length()){
			type = 1;
			size = a.get_attribute_length();
			data = value;
		}
		else{
			throw RuntimeException("String to big for cell with this attribute");
		}
	}
	else{
		type = 0;
		size = 0;
		data = value;
	}
}

/*accessors ---------------------------------------------------------------------------------*/
// Get the type of data in the cell
// Returns an int, either string (1) or int (0)
int Cell::get_type() const{
	return type;
}

// Returns the data in the cell as a string
string Cell::get_value() const{
	return data;
}

/*modifiers ---------------------------------------------------------------------------------*/
// Updates teh data in the cell with new data
// Input a string for the new data
void Cell::update_data(string value){
	if(type == 1){
		if((int)value.size() <= size){
			data = value;
		}
		else{
			throw RuntimeException("String to big for cell with this attribute");
		}
	}
	else{
		data = value;
	}
}

/*operators ---------------------------------------------------------------------------------*/
// Compares if two cells have the samme content and type
// Returns a bool, true if cells are the same else false
bool Cell::operator==(const Cell &c) const{
	return data.compare(c.data) == 0 && size == c.size && type == c.type;
}

/* End of definitions */