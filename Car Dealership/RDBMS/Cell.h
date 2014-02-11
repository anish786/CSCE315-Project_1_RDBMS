#pragma once

#include "Attribute.h"

/* Declaration of the Cell Class */

class Cell{
private:
	int cell_type;
	int word_length;
public:
	union{
		int num;
		char *word;
	}cell_data;
	
	/*constructors*/
	Cell();
	Cell(const Cell &cell);
	Cell(Attribute a, string value);
	~Cell();

	/*accessors*/
	void print_cell();
	int get_type();
	string get_value();
	string get_value() const;

	/*modifiers*/
	void update(string value);

	/*operators*/
	bool operator==(const Cell &c) const;
	Cell& operator=(const Cell c);

};

/* End of the Cell Class */
