#ifndef CELL_H_
#define CELL_H_

#include "Attribute.h"

class Cell{
private:
	int cell_type;
public:
	union{
		int num;
		char *word;
	}cell_data;

	Cell();
	Cell(const Cell &cell){
		cell_type = cell.cell_type;
		cell_data = cell.cell_data;
	}
	Cell(Attribute a, string value){
		if(a.get_attribute_type().compare("int")==0){
			stringstream ss(value);
			if(!(ss >> cell_data.num)){
				cell_data.num = 0;
			}
			cell_type = 0;
		}
		else if(a.get_attribute_type().compare("string")==0){
			cell_data.word = new char[a.get_attribute_length()];
			value.copy(cell_data.word,a.get_attribute_length(),0);
			cell_data.word[value.size()] = '\0';
			cell_type = 1;
		}
	}
	friend bool operator==(const Cell &cell_1, const Cell &cell_2){
		if(cell_1.cell_type == 0 && cell_2.cell_type == 0){
			return (cell_1.cell_data.num == cell_2.cell_data.num);
		}
		else if(cell_1.cell_type == 1 && cell_2.cell_type == 1){
			return (cell_1.cell_data.word == cell_2.cell_data.word);
		}
	}
	Cell& operator=(const Cell c){
		cell_type = c.cell_type;
		cell_data = c.cell_data;
		return *this;
	}
	void print_cell(){
		if(cell_type == 1){
			cout << cell_data.word << endl;
		}
		else{
			cout << cell_data.num << endl;
		}
	}
	int get_type(){
		return cell_type;
	}
	string get_value(){
		if(cell_type == 0){
			stringstream ss;
			ss << cell_data.num;
			return ss.str();
		}
		else if(cell_type == 1){
			return cell_data.word;
		}
	}
	void update(string value){
		if(cell_type == 0){
			int temp;
			stringstream ss(value);
			ss >> temp;
			cell_data.num = temp;
			cout << "cell data: " << cell_data.num << endl;
		}
		else if(cell_type == 1){
			value.copy(cell_data.word, value.size(), 0);
			cell_data.word[value.size()] = '\0';
		}
	}
};

#endif