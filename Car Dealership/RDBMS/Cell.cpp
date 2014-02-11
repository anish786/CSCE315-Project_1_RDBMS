#include "Cell.h"

/* Definitions of the Cell Class */

/*constructors ------------------------------------------------------------------------------*/
Cell::Cell(){
	word_length = 0;
	cell_type = 0;
}

Cell::Cell(const Cell &cell){
	cell_type = cell.cell_type;
	cell_data.num = cell.cell_data.num;
	word_length = cell.word_length;
	if(cell.cell_type == 1){
		cell_data.word = new char[cell.word_length];
		for(int i = 0; i < cell.word_length; i++){
			cell_data.word[i] = cell.cell_data.word[i];
		}
	}
}

Cell::Cell(Attribute a, string value){
	if (a.get_attribute_type().compare("int") == 0){
		stringstream ss(value);
		if (!(ss >> cell_data.num)){
			cell_data.num = 0;
		}
		cell_type = 0;
		word_length = 0;
	}
	else if (a.get_attribute_type().compare("string") == 0){
		cell_data.word = new char[a.get_attribute_length()];
		for (size_t i = 0; i < value.size(); i++){
			cell_data.word[i] = value[i];
		}
		cell_data.word[value.size()] = '\0';
		cell_type = 1;
		word_length = a.get_attribute_length();
	}
}

Cell::~Cell(){
	if(cell_type == 1){
		delete cell_data.word;
	}
}

/*accessors ---------------------------------------------------------------------------------*/
void Cell::print_cell(){
	if (cell_type == 1){
		cout << cell_data.word << endl;
	}
	else{
		cout << cell_data.num << endl;
	}
}

int Cell::get_type(){
	return cell_type;
}

string Cell::get_value(){
	if (cell_type == 0){
		stringstream ss;
		ss << cell_data.num;
		return ss.str();
	}
	else if (cell_type == 1){
		return cell_data.word;
	}
	else {
		return NULL;
	}
}

/*modifiers ---------------------------------------------------------------------------------*/
void Cell::update(string value){
	if (cell_type == 0){
		int temp;
		stringstream ss(value);
		ss >> temp;
		cell_data.num = temp;
		cout << "cell data: " << cell_data.num << endl;
	}
	else if (cell_type == 1){
		for (size_t i = 0; i < value.size(); i++){
			cell_data.word[i] = value[i];
		}
		cell_data.word[value.size()] = '\0';
	}
}

/*operators ---------------------------------------------------------------------------------*/
Cell& Cell::operator=(const Cell c){
	cell_type = c.cell_type;
	cell_data.num = c.cell_data.num;
	word_length = c.word_length;
	if(c.cell_type == 1){
		cell_data.word = new char[c.word_length];
		for(int i = 0; i < c.word_length; i++){
			cell_data.word[i] = c.cell_data.word[i];
		}
	}
	return *this;
}

/* End of definitions */