#include "Attribute.h"

/* Definitions of the Attribute Class */

/*constructors -------------------------------------------------------------------------------*/
Attribute::Attribute(string att_name, int att_type, int att_len){
	attribute_name = att_name;
	attribute_type = att_type;
	attribute_length = att_len;
}

Attribute::Attribute(string att_name, int att_type){
	attribute_name = att_name;
	attribute_type = att_type;
	attribute_length = 0;
}

/*accessors ----------------------------------------------------------------------------------*/
string Attribute::get_attribute_name() const{
	return attribute_name;
}

int Attribute::get_attribute_type() const{
	return attribute_type;
}

int Attribute::get_attribute_length() const{
	return attribute_length;
}

/*modifiers ----------------------------------------------------------------------------------*/
void Attribute::update_name(string new_attribute_name){
	attribute_name = new_attribute_name;
}

/*operators ---------------------------------------------------------------------------------*/
bool Attribute::operator==(const Attribute &a) const{
	return attribute_name.compare(a.attribute_name) == 0 && attribute_type == a.attribute_type && attribute_length == a.attribute_length;
}

/* End of definitions */
