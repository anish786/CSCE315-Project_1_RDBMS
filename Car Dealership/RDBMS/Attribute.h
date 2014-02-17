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
	//Name of this attribute
	string attribute_name; 
	//Type either string (1) or int (0)
	int attribute_type;
	//Length of cells for string types
	int attribute_length; 

public:
	/*Constructors*/
	// Constructor for Integer type or type without length
	Attribute(string att_name, int att_type);
	// Constructor for String type with length
	Attribute(string att_name, int att_type, int att_len);
	
	/*accessors*/
	// Returns a string that is the name of the attribute
	string get_attribute_name() const;
	// Returns an integer that is the type of the attribute 
	// String (1) or int (0)
	int get_attribute_type() const;
	// Returns the max length of the attribute for strings
	int get_attribute_length() const;

	/*modifiers*/
	// Update the name of the attribute
	// Input is a string for the new name
	void update_name(string new_attribute_name);

	/*operators*/
	// Compares if the Attributes have the same name, type, and length
	// Returns a bool, true if same false if not
	bool operator==(const Attribute &a) const;

};

/* End of Attribute Class */
