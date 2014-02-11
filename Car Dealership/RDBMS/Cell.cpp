#include "Cell.h"
#include "Condition.h"

/* Definitions of the Cell Class */

/*constructors ------------------------------------------------------------------------------*/

Cell::Cell(Attribute *a, string value){
	attribute = a;
	if(attribute->get_attribute_type() == 1){
		if((int)value.size() <= attribute->get_attribute_length()){
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

/*accessors ---------------------------------------------------------------------------------*/
void Cell::print_cell(){
	if (attribute->get_attribute_type() == 1){
		cout << data << endl;
	}
	else{
		cout << string_to_int(data) << endl;
	}
}

int Cell::get_type(){
	return attribute->get_attribute_type();
}

string Cell::get_attribute_name(){
	return attribute->get_attribute_name();
}

string Cell::get_value(){
	return data;
}

string Cell::get_value() const{
	return data;
}

/*modifiers ---------------------------------------------------------------------------------*/
void Cell::update_data(string value){
	if(attribute->get_attribute_type() == 1){
		if((int)value.size() <= attribute->get_attribute_length()){
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
	return this->data.compare(c.data) == 0 && this->attribute->get_attribute_type() == c.attribute->get_attribute_type();
}

/* End of definitions */