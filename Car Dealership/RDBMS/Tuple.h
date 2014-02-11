#pragma once

#include "Cell.h"

/* Declaration of the Tuple Class */

using namespace std;

class Tuple{
private:
	vector<Cell>cells;

public:
	/*constructors*/
	Tuple();
	Tuple(vector<Cell> c);
	Tuple(vector<Attribute> attribute, vector<string> values);
	
	/*accessors*/
	vector<string> get_values();
	string get_cell_index(int index);
	vector<Cell>get_cell();

	/*modifiers*/
	void insert(Cell c);
	void update(string value, int position);
	
	/*operators*/
	friend ostream &operator<<(ostream &os, Tuple t){
		for (size_t i = 0; i < t.cells.size(); i++){
			if(t.cells[i].get_type()==0){
				os << t.cells[i].cell_data.num << '\t';
			}
			else if(t.cells[i].get_type()==1){ // string
				os << t.cells[i].cell_data.word << '\t';
			}
		}
		os << endl;
		return os;
	}
	friend bool operator==(const Tuple &t1, const Tuple &t2)
	{
		int count = 0;
		if( t1.cells.size() == t2.cells.size() )
		{
			for (size_t i = 0; i<t1.cells.size(); i++)
			{
				if(t1.cells[i] == t2.cells[i])
					count++;
				else 
					return false;
			}
		}
		else {
			return false;
		}
		return (count == t1.cells.size());
	}

};

/* End of the Tuple Class */
