#pragma once

#include "Tuple.h"
#include "Condition.h"

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
	Relation(string r_name, vector<Attribute> a_list, vector<int> key_list);
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
	Relation natural_join(Relation &r1, Relation &r2);
	Tuple get_tuple(int index);
	vector<string> get_attributes();
	
	/*modifiers*/
	void insert_tuple(vector<string>values);
	void delete_tuple(vector<string>values);
	void insert_from_relation(Relation r);
	void delete_from(Condition con);
	void update(vector<string> aname, vector<string> update, Condition con);
	void select(Condition con, Relation r);
	void project(vector<string> att_list, Relation r);
	void rename(vector<string> att_list, Relation r);
	void update(vector<string> keywords, string value, int column_index);
	void rename_cell(vector<string> primaryKey, string attToRename, string value);
	void rename_cell(string attToRename, string value);
	
	/*operators*/
	Relation operator+(const Relation &r) const;
	Relation operator-(const Relation &r) const;
	Relation operator*(const Relation &r) const;
	friend ostream& operator<<(ostream& os, Relation r);
};

/* End of the Relation Class */

