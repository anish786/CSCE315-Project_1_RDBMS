#include "Cell.h"
#include "Condition.h"

/* Definitions of the Cell Class */

/*constructors ------------------------------------------------------------------------------*/

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
void Cell::print_cell() const{
	if (type == 1){
		cout << data << endl;
	}
	else{
		cout << string_to_int(data) << endl;
	}
}

int Cell::get_type() const{
	return type;
}


string Cell::get_value() const{
	return data;
}

/*modifiers ---------------------------------------------------------------------------------*/
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
bool Cell::operator==(const Cell &c) const{
	return data.compare(c.data) == 0 && size == c.size && type == c.type;
}

/* End of definitions */