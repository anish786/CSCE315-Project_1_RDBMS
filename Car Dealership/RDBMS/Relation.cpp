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

vector<string> Relation::get_attributes(){
	vector<string> atts;
	for(size_t i = 0; i < attribute_list.size(); i++){
		atts.push_back(attribute_list[i].get_attribute_name());
	}
	return atts;
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

void Relation::natural_join(Relation &r1, Relation &r2){
	//vector<Attribute> temp_attribute;
	//vector<string> temp_keys;

	//bool key_match = false;
	//for(int i = 0; i < r2.tuple_list.size(); i++){
	//	for(int j = 0; j < r1.tuple_list.size(); j++){
			
	//	}
	//}
}

Tuple Relation::get_tuple(int index){
	return tuple_list[index];
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

void Relation::delete_from(Condition con){
	size_t i = 0;
	while(i < tuple_list.size()){
		if(con.evaluate(get_attributes() , tuple_list[i].get_values())){
			tuple_list.erase(tuple_list.begin()+i);
		}
		else{
			i++;
		}
	}
}

void Relation::update(vector<string> aname, vector<string> update, Condition con){
	
	for(size_t i = 0; i < tuple_list.size(); i++){
		if(con.evaluate(get_attributes() , tuple_list[i].get_values())){
			for(size_t j = 0; j < aname.size(); j++){
				tuple_list[i].update(update[j], find_position(aname[j]));
			}
		}
	}
}

void Relation::select(Condition con, Relation r){
	Relation new_r("Selection", r.attribute_list, r.keys);
	for(size_t i = 0; i < r.tuple_list.size(); i++){
		if(con.evaluate(get_attributes() , tuple_list[i].get_values())){
			new_r.insert_tuple(r.tuple_list[i].get_values());
		}
	}
	*this = new_r;
}

void Relation::rename(vector<string> att_list, Relation r){
	for(size_t i = 0; i < attribute_list.size(); i++){
		attribute_list[i].update(att_list[i]);
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
Relation Relation::operator+(const Relation &r) const{
	//Set Union
	Relation set_union("Set Union");

	// TODO Check to make sure attributes are the same

	//add all attributes in first set
	for(size_t i=0; i<r.attribute_list.size(); ++i){
		Attribute a(r.attribute_list[i]);
		set_union.attribute_list.push_back(a);
	}
	//add all tuples in the first set
	for(size_t i=0; i<r.tuple_list.size(); ++i){
		Tuple t(r.tuple_list[i]);
		set_union.tuple_list.push_back(t);
	}
	//add non-duplicate tuples in the second relation
	for(size_t i=0; i<this->tuple_list.size(); ++i){
		bool found = false;
		for(size_t j=0; j<r.tuple_list.size(); ++j){
			if(r.tuple_list[j] == this->tuple_list[i]){	//if tuples match
				found = true;
				break;
			}
		}
		if(found == false){								//tuple was not found
			Tuple t2(this->tuple_list[i]);
			set_union.tuple_list.push_back(t2);
		}
	}
	return set_union;
}

Relation Relation::operator-(const Relation &r) const{
	//Set Difference

	Relation set_diff("Set Difference");

	// TODO Check to make sure attributes are the same

	//add all attributes in first set
	for(size_t i=0; i<r.attribute_list.size(); ++i){
		Attribute a(r.attribute_list[i]);
		set_diff.attribute_list.push_back(a);
	}

	//add all tuples in the first set that are not in the second
	for(size_t i=0; i<r.tuple_list.size(); ++i){
		bool found = false;
		for(size_t j=0; j<this->tuple_list.size(); ++j){
			if(r.tuple_list[i] == this->tuple_list[j]){	//if tuples match
				found = true;
				break;
			}
		}
		if(found == false){								//tuple was not found
			Tuple t1(r.tuple_list[i]);
			set_diff.tuple_list.push_back(t1);
		}
	}
	//add all tuples in the second set that are not in the first
	for(size_t i=0; i<this->tuple_list.size(); ++i){
		bool found = false;
		for(size_t j=0; j<r.tuple_list.size(); ++j){
			if(r.tuple_list[j] == this->tuple_list[i]){	//if tuples match
				found = true;
				break;
			}
		}
		if(found == false){								//tuple was not found
			Tuple t2(this->tuple_list[i]);
			set_diff.tuple_list.push_back(t2);
		}
	}	
	return set_diff;
}

Relation Relation::operator*(const Relation &r) const{
	Relation cross_product;
	int count = r.tuple_list.size() * this->tuple_list.size();
	vector<Attribute>::iterator it;

	cross_product.relation_name = r.relation_name;
	cross_product.attribute_list = r.attribute_list;
	cross_product.keys = r.keys;

	cross_product.attribute_list.insert(attribute_list.end(), this->attribute_list.begin(), this->attribute_list.end());

	vector<string> values;

	for (size_t j = 0; j < this->tuple_list.size(); j++)
	{
		for (size_t i = 0; i < r.tuple_list.size(); i++)
		{
			values = r.tuple_list[i].get_values();
			for (size_t k = 0; k < this->attribute_list.size(); k++){
				values.push_back(this->tuple_list[j].get_cell()[k].get_value());
			}
			cross_product.insert_tuple(values);
		}
	}
	return cross_product;
}
/* End of definitions */
