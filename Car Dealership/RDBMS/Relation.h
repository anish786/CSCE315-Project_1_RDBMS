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
	void natural_join(Relation &r1, Relation &r2);
	Tuple get_tuple(int index);
	
	/*modifiers*/
	void insert_tuple(vector<string>values);
	void delete_tuple(vector<string>values);
	void insert_from_relation(Relation r);
	void delete_from();
	void update(vector<string> keywords, string value, int column_index);
	void rename_cell(vector<string> primaryKey, string attToRename, string value);
	void rename_cell(string attToRename, string value);
	
	/*operators*/
	Relation operator+(const Relation &r) const;
	Relation operator-(const Relation &r) const;
	Relation operator*(const Relation &r) const;
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
};

/* End of the Relation Class */

