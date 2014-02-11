#pragma once

#include "Tuple.h"
#include "Condition.h"

/* Declaration of the Relation Class */

using namespace std;

class Relation{
	string relation_name;
	vector<Attribute> attribute_list;
	vector<Tuple> tuple_list;
	vector<int> keys;

public:
	/*constructors*/
	Relation(string r_name);
	Relation(string r_name, vector<Attribute> a_list, vector<int> key_list);
	Relation(string r_name, vector<Attribute> a_list, vector<string> key_names);
	
	/*accessors*/
	int find_attribute_column(string attribute);
	bool has_attribute(string attribute);
	string get_relation_name();
	vector<string> get_attributes();
	Tuple get_tuple(int index);
	
	
	/*modifiers*/
	void insert_tuple(vector<string>values);
	void insert_from_relation(Relation r);
	void delete_from(Condition con);
	void update(vector<string> aname, vector<string> update, Condition con);
	void select(Condition con, Relation r);
	void project(vector<string> att_list, Relation r);
	void rename(vector<string> att_list, Relation r);
	Relation natural_join(Relation &r1, Relation &r2);
	
	/*operators*/
	//Union
	Relation operator+(const Relation &r) const;
	//Difference
	Relation operator-(const Relation &r) const;
	//Cross Product
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

