#include "Cell.h"

/* Definitions of the Cell Class */

/*constructors ------------------------------------------------------------------------------*/
Cell::Cell(){
}

Cell::Cell(const Cell &cell){
	cell_type = cell.cell_type;
	cell_data = cell.cell_data;
}

Cell::Cell(Attribute a, string value){
	if (a.get_attribute_type().compare("int") == 0){
		stringstream ss(value);
		if (!(ss >> cell_data.num)){
			cell_data.num = 0;
		}
		cell_type = 0;
	}
	else if (a.get_attribute_type().compare("string") == 0){
		cell_data.word = new char[a.get_attribute_length()];
		for (int i = 0; i < a.get_attribute_length(); i++){
			cell_data.word[i] = value[i];
		}
		//value.copy(cell_data.word, a.get_attribute_length(), 0);
		cell_data.word[value.size()] = '\0';
		cell_type = 1;
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
		//value.copy(cell_data.word, value.size(), 0);
		cell_data.word[value.size()] = '\0';
	}
}

/*operators ---------------------------------------------------------------------------------*/
Cell& Cell::operator=(const Cell c){
	cell_type = c.cell_type;
	cell_data = c.cell_data;
	return *this;
}

/* End of definitions */