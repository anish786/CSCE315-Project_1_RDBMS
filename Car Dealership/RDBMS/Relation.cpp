#include "Relation.h"

/* Definitions of the Relation Class */

/*constructors -------------------------------------------------------------------------------*/
Relation::Relation(){}

Relation::Relation(string r_name){
	relation_name = r_name;
}

Relation::Relation(string r_name, vector<Attribute> a_list, vector<string> key_names){
	relation_name = r_name;
	for (size_t i = 0; i < a_list.size(); i++){
		attribute_list.push_back(a_list[i]);
	}
	for (size_t i = 0; i < key_names.size(); i++){
		if (check(key_names[i])){
			keys.push_back(find_position(key_names[i]));
		}
		else{
			cout << "did not found" << endl;
		}
	}
}

/*accessors ----------------------------------------------------------------------------------*/

/*find position in vector*/
int Relation::find_position(string keyword)
{
	int address = 0;
	for (size_t i = 0; i<attribute_list.size(); i++)
	{
		if (attribute_list[i].get_attribute_name().compare(keyword) == 0)
		{
			address = i;
			break;
		}
	}
	return address;
}

/*check if values exist*/
bool Relation::check(string keyword)
{
	int a = 0;
	for (size_t i = 0; i<attribute_list.size(); i++)
	if (attribute_list[i].get_attribute_name().compare(keyword) == 0)
		a = 1;
	if (a == 1)
		return true;
	else 
		return false;
}

string Relation::get_relation_name(){
	return relation_name;
}

int Relation::find_tuple(vector<string>values){
	int temp = 0;
	int count = 0;
	bool flag = false;

	for (size_t i = 0; i < tuple_list.size(); i++){
		for (size_t j = 0; j < keys.size(); j++){
			if (tuple_list[i].get_cell()[keys[j]].get_type() == 0){
				stringstream ss(values[j]);
				int int_value;
				ss >> int_value;
				if (int_value == tuple_list[i].get_cell()[keys[j]].cell_data.num){
					count++;
				}
			}
			else if (tuple_list[i].get_cell()[keys[j]].get_type() == 1){
				string s = tuple_list[i].get_cell()[keys[j]].cell_data.word;
				if (s.compare(values[j]) == 0){
					count++;
				}
			}
		}
		if (count == keys.size()){
			temp = i;
			flag = 1;
			break;
		}
		count = 0;
	}
	if (flag == 0){
		cerr << "Search is not found" << endl;
	}
	return temp;
}

vector<int> Relation::find_columns(vector<string> attribute_names){
	vector<int>columns;
	vector<Attribute> a_list;
	for (size_t i = 0; i < attribute_names.size(); i++){
		if (check(attribute_names[i])){
			columns.push_back(find_position(attribute_names[i]));
		}
	}
	return columns;
}

bool Relation::check_key(vector<string>values){
	int count = 0;
	bool flag = false;
	if (keys.size() != values.size()){
		return flag;
	}
	for (size_t i = 0; i < tuple_list.size(); i++){
		count = 0;
		for (size_t j = 0; j < keys.size(); j++){
			if (tuple_list[i].get_cell()[keys[j]].get_type() == 0){
				stringstream ss(values[j]);
				int int_value;
				ss >> int_value;
				if (int_value == tuple_list[i].get_cell()[keys[j]].cell_data.num){
					count++;
				}
			}
			else if (tuple_list[i].get_cell()[keys[j]].get_type() == 1){
				string s = tuple_list[i].get_cell()[keys[j]].cell_data.word;
				if (s.compare(values[j]) == 0)
				{
					count++;
				}
			}

		}
		if (count == keys.size()){
			flag = true;
			break;
		}
	}
	return flag;
}

Tuple Relation::projection(string attribute_name){
	if (check(attribute_name)){
		int position = find_position(attribute_name);
		vector<Cell> column_value;
		for (size_t i = 0; i < tuple_list.size(); i++){
			column_value.push_back(tuple_list[i].get_cell()[position]);
		}
		Tuple column(column_value);
		return column;
	}
	return Tuple();
}

void Relation::cross_product(Relation &r1, Relation &r2)
{
	int count = r1.tuple_list.size() * r2.tuple_list.size();
	vector<Attribute>::iterator it;

	relation_name = r1.relation_name;
	attribute_list = r1.attribute_list;
	keys = r1.keys;

	attribute_list.insert(attribute_list.end(), r2.attribute_list.begin(), r2.attribute_list.end());

	vector<string> values;

	for (size_t j = 0; j<r2.tuple_list.size(); j++)
	{
		for (size_t i = 0; i<r1.tuple_list.size(); i++)
		{
			values = r1.tuple_list[i].get_values();
			for (size_t k = 0; k<r2.attribute_list.size(); k++){
				values.push_back(r2.tuple_list[j].get_cell()[k].get_value());
			}
			insert_tuple(values);
		}
	}
	for (size_t i = 0; i<attribute_list.size(); i++)
		cout << "Attribute Name: " << attribute_list[i].get_attribute_name() << endl;
}
void Relation::natural_join(Relation &r1, Relation &r2){
	//vector<Attribute> temp_attribute;
	//vector<string> temp_keys;

	//bool key_match = false;
	//for(int i = 0; i < r2.tuple_list.size(); i++){
	//	for(int j = 0; j < r1.tuple_list.size(); j++){
			
	//	}
	//}
}

/*modifiers ----------------------------------------------------------------------------------*/
void Relation::insert_tuple(vector<string>values){
	Tuple t(attribute_list, values);
	tuple_list.push_back(t);
}

void Relation::delete_tuple(vector<string>values){
	if (check_key(values)){
		int a = find_tuple(values);
		tuple_list.erase(tuple_list.begin() + a);
	}
}

void Relation::insert_from_relation(Relation r){
	for(size_t i = 0; i < tuple_list.size(); i++){
		insert_tuple(tuple_list[i].get_values());
	}
}



void Relation::update(vector<string> keywords, string value, int column_index){
	if (keywords[0] == "0"){
		attribute_list[column_index].update(value);
	}
	else{
		cout << "Keywords: " << keywords[0] << ", " << keywords[1] << endl;
		int row_index = find_tuple(keywords);
		cout << "changing row index: " << row_index << " and column index: " << column_index << endl;
		tuple_list[row_index].update(value, column_index);
	}
}

void Relation::rename_cell(vector<string> primaryKey, string attToRename, string value){
	for (size_t i = 0; i<attribute_list.size(); i++){
		if ((attribute_list[i].get_attribute_name().compare(attToRename)) == 0){
			update(primaryKey, value, i);
			cout << "The attribute " << attToRename << " has been renamed " << value << endl;
		}
	}
}

void Relation::rename_cell(string attToRename, string value){
	vector<string> nullKey(1, "0");
	for (size_t i = 0; i<attribute_list.size(); i++) {
		for (size_t j = 0; j<attToRename.size(); j++) {
			if (attribute_list[i].get_attribute_name().compare(attToRename) == 0) {
				update(nullKey, value, i);
				cout << "The table attribute " << attToRename << " has been renamed " << value << endl;
			}
		}
	}
}

/*operators ----------------------------------------------------------------------------------*/

/* End of definitions */
