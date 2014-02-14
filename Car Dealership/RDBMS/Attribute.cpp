#include "Attribute.h"

/* Definitions of the Attribute Class */

/*constructors -------------------------------------------------------------------------------*/
// Constructor for Integer type or type without length
Attribute::Attribute(string att_name, int att_type, int att_len){
	attribute_name = att_name;
	attribute_type = att_type;
	attribute_length = att_len;
}

// Constructor for String type with length
Attribute::Attribute(string att_name, int att_type){
	attribute_name = att_name;
	attribute_type = att_type;
	attribute_length = 0;
}

/*accessors ----------------------------------------------------------------------------------*/
// Returns a string that is the name of the attribute
string Attribute::get_attribute_name() const{
	return attribute_name;
}

// Returns an integer that is the type of the attribute 
// String (1) or int (0)
int Attribute::get_attribute_type() const{
	return attribute_type;
}

// Returns the max length of the attribute for strings
int Attribute::get_attribute_length() const{
	return attribute_length;
}

/*modifiers ----------------------------------------------------------------------------------*/
// Update the name of the attribute
// Input is a string for the new name
void Attribute::update_name(string new_attribute_name){
	attribute_name = new_attribute_name;
}

/*operators ---------------------------------------------------------------------------------*/
// Compares if the Attributes have the same name, type, and length
// Returns a bool, true if same false if not
bool Attribute::operator==(const Attribute &a) const{
	return attribute_name.compare(a.attribute_name) == 0 && attribute_type == a.attribute_type && attribute_length == a.attribute_length;
}

/* End of definitions */
