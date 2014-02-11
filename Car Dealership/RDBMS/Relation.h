#pragma once

#include "Tuple.h"

/* Declaration of the Relation Class */

using namespace std;

class Relation{
private:
	string relation_name;
	vector<Attribute> attribute_list;
	vector<Tuple> tuple_list;
	vector<int> keys;

public:
	/*constructors*/
	Relation();
	Relation(string r_name);
	Relation(string r_name, vector<Attribute> a_list, vector<string> key_names);
	
	/*accessors*/

	/*find position in vector*/
	int find_position(string keyword);

	/*check if values exist*/
	bool check(string keyword);

	string get_relation_name();
	int find_tuple(vector<string>values);
	vector<int> find_columns(vector<string> attribute_names);
	bool check_key(vector<string>values);
	Tuple projection(string attribute_name);
	void cross_product(Relation &r1, Relation &r2);
	void natural_join(Relation &r1, Relation &r2);
	
	/*modifiers*/
	void insert_tuple(vector<string>values);
	void delete_tuple(vector<string>values);
	void insert_attribute(string name, string type, int length);
	void update(vector<string> keywords, string value, int column_index);
	void rename_attributes(vector<string> primaryKey, string attToRename, string value);
	void rename_attributes(string attToRename, string value);
	
	/*operators*/
	friend ostream& operator<<(ostream& os, Relation r){
		//table name
		os << "\t\t" << r.get_relation_name() << endl;
		os << endl;

		/*attribute list*/
		for (size_t i = 0; i<r.attribute_list.size(); i++){
			os << r.attribute_list[i].get_attribute_name() << "\t";
		}
		os << endl << endl;

		/*cell info*/
		for (size_t i = 0; i<r.tuple_list.size(); i++)
		{
			os << r.tuple_list[i];
		}
		return os;
	}
	friend Relation operator+(const Relation &r1, const Relation &r2){
		//Set Union
		Relation set_union("Set Union");

		// TODO Check to make sure attributes are the same

		//add all attributes in first set
		for(size_t i=0; i<r1.attribute_list.size(); ++i){
			Attribute a(r1.attribute_list[i]);
			set_union.attribute_list.push_back(a);
		}
		//add all tuples in the first set
		for(size_t i=0; i<r1.tuple_list.size(); ++i){
			Tuple t(r1.tuple_list[i]);
			set_union.tuple_list.push_back(t);
		}
		//add non-duplicate tuples in the second relation
		for(size_t i=0; i<r2.tuple_list.size(); ++i){
			bool found = false;
			for(size_t j=0; j<r1.tuple_list.size(); ++j){
				if(r1.tuple_list[j] == r2.tuple_list[i]){	//if tuples match
					found = true;
					break;
				}
			}
			if(found == false){								//tuple was not found
				Tuple t2(r2.tuple_list[i]);
				set_union.tuple_list.push_back(t2);
			}
		}
		return set_union;
	}
	friend Relation operator-(const Relation &r1, const Relation &r2){
		//Set Difference
		Relation set_diff("Set Difference");

		return set_diff;
	}
};

/* End of the Relation Class */

