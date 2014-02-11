#pragma once

#include "Attribute.h"

/* Declaration of the Cell Class */

class Cell{
private:
	int cell_type;

public:
	union{
		int num;
		char *word;
	}cell_data;
	
	/*constructors*/
	Cell();
	Cell(const Cell &cell);
	Cell(Attribute a, string value);

	/*accessors*/
	void print_cell();
	int get_type();
	string get_value();

	/*modifiers*/
	void update(string value);

	/*operators*/
	friend bool operator==(const Cell &cell_1, const Cell &cell_2){
		if (cell_1.cell_type == 0 && cell_2.cell_type == 0){
			return (cell_1.cell_data.num == cell_2.cell_data.num);
		}
		else if (cell_1.cell_type == 1 && cell_2.cell_type == 1){
			return (*cell_1.cell_data.word == *cell_2.cell_data.word);
		}
	}
	Cell& operator=(const Cell c);

};

/* End of the Cell Class */
