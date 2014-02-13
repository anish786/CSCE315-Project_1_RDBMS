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
int Relation::find_attribute_column(string attribute) const
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
bool Relation::has_attribute(string attribute) const
{
	for (size_t i = 0; i<attribute_list.size(); i++){
		if (attribute_list[i].get_attribute_name().compare(attribute) == 0){
			return true;
		}
	}
	return false;
}

string Relation::get_relation_name() const{
	return relation_name;
}

vector<string> Relation::get_attributes() const{
	vector<string> atts;
	for(size_t i = 0; i < attribute_list.size(); i++){
		atts.push_back(attribute_list[i].get_attribute_name());
	}
	return atts;
}

Tuple Relation::get_tuple(int index) const{
	return tuple_list[index];
}

int Relation::get_num_tuples() const{
	return tuple_list.size();
}

int Relation::get_num_attributes() const{
	return attribute_list.size();
}

/*modifiers ----------------------------------------------------------------------------------*/
void Relation::insert_tuple(vector<string>values){
	if(values.size() == attribute_list.size()){
		vector<Attribute> atts;
		for(size_t i = 0; i < attribute_list.size(); i++){
			atts.push_back(attribute_list[i]);
		}
		tuple_list.push_back(Tuple(atts, values));
	}
	else{
		throw RuntimeException("Can not insert new tuple wrong number of attributes");
	}
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
		a_list.push_back(r.attribute_list[r.find_attribute_column(att_list[i])]);
	}
	
	attribute_list = a_list;
	for(size_t i = 0; i < r.tuple_list.size(); i++){
		vector<string> new_t;
		for(size_t j = 0; j < a_list.size(); j++){
			new_t.push_back(r.tuple_list[i].get_cell_data(r.find_attribute_column(a_list[j].get_attribute_name())));
		}
		insert_tuple(new_t);
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
				tuple_list[i].update_cell(update[j], find_attribute_column(aname[j]));
			}
		}
	}
}

void Relation::select(Condition con, Relation r){
	attribute_list = r.attribute_list;
	keys = r.keys;
	for(size_t i = 0; i < r.tuple_list.size(); i++){
		if(con.evaluate(r.get_attributes() , r.tuple_list[i].get_values())){
			insert_tuple(r.tuple_list[i].get_values());
		}
	}
}

void Relation::rename(vector<string> att_list, Relation r){
	if(att_list.size() == r.attribute_list.size()){
		attribute_list = r.attribute_list;
		keys = r.keys;
		tuple_list = r.tuple_list;
		for(size_t i = 0; i < attribute_list.size(); i++){
			attribute_list[i].update_name(att_list[i]);
		}
	}
	else{
		throw RuntimeException("In rename, number of attributes to rename differs from actual number of attributes in relation");
	}
}

void Relation::natural_join(Relation r1, Relation r2){
	vector<string> common_attributes;
	for (int i = 0; i < r1.get_num_attributes(); i++){
		for (int j = 0; j < r2.get_num_attributes(); j++){
			if (r1.attribute_list[i] == r2.attribute_list[j]){
				common_attributes.push_back(r1.attribute_list[i].get_attribute_name());
				break;
			}
		}
	}

	if (common_attributes.size() == 0){
		throw RuntimeException("No common attributes cannot perform join");
	}

	//Add all attributes from r1
	attribute_list = r1.attribute_list;
	//Add non matching attributes from r2
	for (int i = 0; i < r2.get_num_attributes(); i++){
		bool found = false;
		for (int j = 0; j < r1.get_num_attributes(); j++){
			if (r2.attribute_list[i] == r1.attribute_list[i]){
				found = true;
				break;
			}
		}
		if (!found){
			attribute_list.push_back(r2.attribute_list[i]);
		}
	}

	for (int i = 0; i < r1.get_num_tuples(); i++){
		for (int j = 0; j < r2.get_num_tuples(); j++){
			bool matching = true;
			for (size_t k = 0; k < common_attributes.size(); k++){
				if (!(r1.get_tuple(i).get_cells()[r1.find_attribute_column(common_attributes[k])] == r2.get_tuple(j).get_cells()[r2.find_attribute_column(common_attributes[k])])){
					matching = false;
					break;
				}
			}
			if (matching){
				vector<string> data = r1.tuple_list[i].get_values();
				for (int k = 0; k < r2.get_num_attributes(); k++){
					bool common_attribute = false;
					for (size_t l = 0; l < common_attributes.size(); l++){
						if (common_attributes[l].compare(r2.attribute_list[k].get_attribute_name()) == 0){
							common_attribute = true;
							break;
						}
					}
					if (!common_attribute){
						data.push_back(r2.tuple_list[k].get_values()[k]);
					}
				}
				tuple_list.push_back(Tuple(attribute_list, data));
			}
		}
	}
}


/*operators ----------------------------------------------------------------------------------*/
Relation Relation::operator+(const Relation &r) const{
	//Set Union
	Relation set_union("Set Union");

	if (attribute_list.size() == r.attribute_list.size()){
		for (size_t i = 0; i < attribute_list.size(); i++){
			if (!(attribute_list[i] == r.attribute_list[i])){
				throw RuntimeException("Attributes do not match in union");
			}
		}
	}
	else{
		throw RuntimeException("Different number of Attributes in union");
	}

	//add all attributes in first set
	set_union.attribute_list = attribute_list;
	//add all tuples in the first set
	set_union.tuple_list = tuple_list;
	//add non-duplicate tuples in the second relation
	for(size_t i=0; i< r.tuple_list.size(); ++i){
		bool found = false;
		for(size_t j=0; j<tuple_list.size(); ++j){
			if(r.tuple_list[i] == tuple_list[j]){	//if tuples match
				found = true;
				break;
			}
		}
		if(!found){								//tuple was not found
			set_union.tuple_list.push_back(r.tuple_list[i]);
		}
	}
	return set_union;
}

Relation Relation::operator-(const Relation &r) const{
	//Set Difference

	Relation set_diff("Set Difference");

	if (attribute_list.size() == r.attribute_list.size()){
		for (size_t i = 0; i < attribute_list.size(); i++){
			if (!(attribute_list[i] == r.attribute_list[i])){
				throw RuntimeException("Attributes do not match in difference");
			}
		}
	}
	else{
		throw RuntimeException("Different number of Attributes in difference");
	}

	//add all attributes in first set
	set_diff.attribute_list = attribute_list;

	//add all tuples in the first set that are not in the second
	for(size_t i=0; i<tuple_list.size(); ++i){
		bool found = false;
		for(size_t j=0; j<r.tuple_list.size(); ++j){
			if(r.tuple_list[j] == tuple_list[i]){	//if tuples match
				found = true;
				break;
			}
		}
		if(!found){								//tuple was not found
			set_diff.tuple_list.push_back(tuple_list[i]);
		}
	}	
	return set_diff;
}

Relation Relation::operator*(const Relation &r) const{
	Relation cross_product("Cross Product");
	
	for (size_t i = 0; i < attribute_list.size(); i++){
		for (size_t j = 0; j < r.attribute_list.size(); j++){
			if (attribute_list[i] == r.attribute_list[j]){
				throw RuntimeException("Relations have a matching attribute can not commpute cross product");
			}
		}
	}

	//Add attributes from first relation
	cross_product.attribute_list = attribute_list;
	cross_product.keys = keys;

	//Add attributes from the second relation
	cross_product.attribute_list.insert(cross_product.attribute_list.end(), r.attribute_list.begin(), r.attribute_list.end());

	vector<string> values;

	for (size_t j = 0; j < tuple_list.size(); j++)
	{
		for (size_t i = 0; i < r.tuple_list.size(); i++)
		{
			values = tuple_list[j].get_values();
			for (size_t k = 0; k < r.attribute_list.size(); k++){
				values.push_back(r.tuple_list[i].get_cells()[k].get_value());
			}
			cross_product.insert_tuple(values);
		}
	}
	return cross_product;
}

ostream& operator<<(ostream& os, Relation r){
	//table name
	os << "\t\t" << r.get_relation_name() << endl;
	os << "--------------------------------------------" << endl;

	/*attribute list*/
	for (size_t i = 0; i<r.attribute_list.size(); i++){
		os << left << setw(MAX_LENGTH) << r.attribute_list[i].get_attribute_name() << "\t";
	}
	os << endl << endl;

	/*cell info*/
	for (size_t i = 0; i<r.tuple_list.size(); i++)
	{
		os << setw(MAX_LENGTH) << r.tuple_list[i];
	}
	os << "\n";
	return os;
}

/* End of definitions */
