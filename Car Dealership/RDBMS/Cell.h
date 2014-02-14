#pragma once

#include "Attribute.h"

/* Declaration of the Cell Class */

class Cell{
private:
	//Type either string (1) or int (0)
	int type; 
	//Size limit if string
	int size; 
	//Data either a string or an integer as a string
	string data;
public:
	/*constructors*/
	// Constructor requring an attribute for cell type info and the value as a string
	Cell(Attribute a, string value);

	/*accessors*/
	// Get the type of data in the cell
	// Returns an int, either string (1) or int (0)
	int get_type() const;
	// Returns the data in the cell as a string
	string get_value() const;

	/*modifiers*/
	// Updates teh data in the cell with new data
	// Input a string for the new data
	void update_data(string value);

	/*operators*/
	// Compares if two cells have the samme content and type
	// Returns a bool, true if cells are the same else false
	bool operator==(const Cell &c) const;

};

/* End of the Cell Class */
