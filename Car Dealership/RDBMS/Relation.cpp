#include "Relation.h"

/* Definitions of the Relation Class */

/*constructors -------------------------------------------------------------------------------*/

Relation::Relation(string r_name){
	relation_name = r_name;
}

Relation::Relation(string r_name, vector<Attribute> a_list, vector<int> key_list){
	relation_name = r_name;
	for (size_t i = 0; i < a_list.size(); i++){
		attribute_list.push_back(a_list[i]);
	}
	keys = key_list;
}

Relation::Relation(string r_name, vector<Attribute> a_list, vector<string> key_names){
	relation_name = r_name;
	for (size_t i = 0; i < a_list.size(); i++){
		attribute_list.push_back(a_list[i]);
	}
	for (size_t i = 0; i < key_names.size(); i++){
		if (has_attribute(key_names[i])){
			keys.push_back(find_attribute_column(key_names[i]));
		}
		else{
			throw RuntimeException("One of the given keys is not in the attribute list");
		}
	}
}

/*accessors ----------------------------------------------------------------------------------*/

/*find position in vector*/
int Relation::find_attribute_column(string attribute)
{
	for (size_t i = 0; i<attribute_list.size(); i++)
	{
		if (attribute_list[i].get_attribute_name().compare(attribute) == 0)
		{
			return i;
		}
	}
	throw RuntimeException("Attribute is not in this relation");
}

/*check if values exist*/
bool Relation::has_attribute(string attribute)
{
	for (size_t i = 0; i<attribute_list.size(); i++){
		if (attribute_list[i].get_attribute_name().compare(attribute) == 0){
			return true;
		}
	}
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

Relation Relation::natural_join(Relation &r1, Relation &r2){
	Relation r(r1.relation_name, r1.attribute_list, r1.keys);
	vector<Tuple> natural_join;
	for(size_t i = 0; i < r1.tuple_list.size(); i++){
		for(size_t j = 0; j < r2.tuple_list.size(); j++){
			if(r1.tuple_list[i] == r2.tuple_list[j]){
				natural_join.push_back(r1.tuple_list[i]);
			}
		}
	}
	r.tuple_list = natural_join;
	return r;
}

Tuple Relation::get_tuple(int index){
	return tuple_list[index];
}

/*modifiers ----------------------------------------------------------------------------------*/
void Relation::insert_tuple(vector<string>values){
	vector<Attribute*> att_pointers;
	for(size_t i = 0; i < attribute_list.size(); i++){
		att_pointers[i] = &attribute_list[i];
	}
	tuple_list.push_back(Tuple(att_pointers, values));
}

void Relation::insert_from_relation(Relation r){
	for(size_t i = 0; i < r.tuple_list.size(); i++){
		insert_tuple(r.tuple_list[i].get_values());
	}
}

void Relation::project(vector<string> att_list, Relation r){
	vector<Attribute> a_list;
	vector<int> a_loc;
	for(size_t i = 0; i < att_list.size(); i++){
		for(size_t j = 0; j < r.attribute_list.size(); j++){
			if(r.attribute_list[j].get_attribute_name().compare(att_list[i]) == 0){
				a_list.push_back(r.attribute_list[j]);
				a_loc.push_back(j);
			}
		}
	}
	Relation new_r("Projection", a_list, a_loc);
	for(size_t i = 0; i < r.tuple_list.size(); i++){
		vector<string> new_t;
		for(size_t j = 0; j < a_list.size(); j++){
			new_t.push_back(r.tuple_list[i].get_values()[a_loc[j]]);
		}
		new_r.insert_tuple(new_t);
	}
	*this = new_r;
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
				tuple_list[i].update_cell(update[j], find_attribute_column(aname[j]));
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
		attribute_list[i].update_name(att_list[i]);
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
	Relation cross_product("Cross Product");
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
				values.push_back(this->tuple_list[j].get_cells()[k].get_value());
			}
			cross_product.insert_tuple(values);
		}
	}
	return cross_product;
}
/* End of definitions */
