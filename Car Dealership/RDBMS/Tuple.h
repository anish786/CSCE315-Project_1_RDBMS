#ifndef TUPLE_H_
#define TUPLE_H_

#include "Cell.h"

class Tuple{
private:
	vector<Cell>cells;
public:
	Tuple(){}
	Tuple(vector<Cell> c){
		cells = c;
	}
	Tuple(vector<Attribute> attribute, vector<string> values){
		for(int i = 0; i < attribute.size(); i++){
			Cell c(attribute[i], values[i]);
			cells.push_back(c);
		}
	}
	void insert(Cell c){
		cells.push_back(c);
	}
	void update(string value, int position){
		cells[position].update(value);
	}
	vector<string>get_values(){
		vector<string>temp;
		for(int i = 0; i < cells.size(); i++){
			temp.push_back(cells[i].get_value());
		}
		return temp;
	}
	string get_cell_index(int index){
		return cells[index].get_value();
	}
	vector<Cell>get_cell(){
		return cells;
	}
	friend ostream &operator<<(ostream &os, Tuple t){
		for(int i = 0; i < t.cells.size(); i++){
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
			for(int i = 0; i<t1.cells.size(); i++)
			{
				if(t1.cells[i] == t2.cells[i])
					count++;
				else 
					return false;
			}
		}
		else return false;

		return (count == t1.cells.size());
	}
};



#endif