

#include "Attribute.h"

/* Definitions of the Attribute Class */

/*constructors -------------------------------------------------------------------------------*/
Attribute::Attribute(){
}

Attribute::Attribute(const Attribute &attribute){
	attribute_name = attribute.attribute_name;
	attribute_type = attribute.attribute_type;
	attribute_length = attribute.attribute_length;
}

Attribute::Attribute(string att_name, string att_type, int att_len){
	attribute_name = att_name;
	attribute_type = att_type;
	attribute_length = att_len;
}

Attribute::Attribute(string att_name, string att_type){
	attribute_name = att_name;
	attribute_type = att_type;
}

/*accessors ----------------------------------------------------------------------------------*/
string Attribute::get_attribute_name(){
	return attribute_name;
}

string Attribute::get_attribute_type(){
	return attribute_type;
}

int Attribute::get_attribute_length(){
	return attribute_length;
}

/*modifiers ----------------------------------------------------------------------------------*/
void Attribute::update(string new_attribute_name){
	attribute_name = new_attribute_name;
}

/*operators ----------------------------------------------------------------------------------*/

/* End of definitions */