#pragma once

#include "Attribute.h"
#include <iomanip>      // std::setw

#define MAX_LENGTH 15
/* Declaration of the Cell Class */

class Cell{
private:
	int type; //Type either string (1) or int (0)
	int size; //Size limit if string
	string data; //Data either a string or an integer as a string
public:
	/*constructors*/
	Cell(Attribute a, string value);

	/*accessors*/
	void print_cell() const;
	int get_type() const;
	string get_value() const;

	/*modifiers*/
	void update_data(string value);

	/*operators*/
	bool operator==(const Cell &c) const;

};

/* End of the Cell Class */
