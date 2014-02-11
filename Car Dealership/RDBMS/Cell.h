#pragma once

#include "Attribute.h"

/* Declaration of the Cell Class */

class Cell{
private:
	Attribute *attribute; //Pointer to the columns attribute
	string data; //Data either a string or an integer as a string
public:
	/*constructors*/
	Cell(Attribute *a, string value);

	/*accessors*/
	void print_cell();
	int get_type();
	string get_attribute_name();
	string get_value();
	string get_value() const;

	/*modifiers*/
	void update_data(string value);

	/*operators*/
	bool operator==(const Cell &c) const;

};

/* End of the Cell Class */
