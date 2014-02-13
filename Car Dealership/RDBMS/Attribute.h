#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "RuntimeException.h"

/* Declaration of the Attribute Class */

using namespace std;

class Attribute{
	string attribute_name; //Name of this attribute
	int attribute_type; //Type either string (1) or int (0)
	int attribute_length; //Length of cells for string types

public:
	/*constructors*/
	Attribute(string att_name, int att_type);
	Attribute(string att_name, int att_type, int att_len);
	
	/*accessors*/
	string get_attribute_name() const;
	int get_attribute_type() const;
	int get_attribute_length() const;

	/*modifiers*/
	void update_name(string new_attribute_name);

	/*operators*/
	bool operator==(const Attribute &a) const;

};

/* End of Attribute Class */
