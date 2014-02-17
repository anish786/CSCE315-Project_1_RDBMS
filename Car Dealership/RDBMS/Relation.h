#pragma once

#include "Tuple.h"
#include "Condition.h"
#include <iomanip>

/* Declaration of the Relation Class */

using namespace std;

class Relation{
	// The name of the relation
	string relation_name;
	// A list of attributes in the relation
	vector<Attribute> attribute_list;
	// A list of tuples in the relation
	vector<Tuple> tuple_list;
	// A list of keys in the relation stored as ints for there location in the attribute list
	vector<int> keys;

public:
	/*constructors*/
	// Constructor
	// Input a name for the relation
	Relation(string r_name);
	// Constructor
	// Input a name for the relation
	//		a vector of attributes for the relation
	//		a vector of ints representing the location of the keys in the attribute list
	Relation(string r_name, vector<Attribute> a_list, vector<int> key_list);
	// Constructor
	// Input a name for the relation
	//		a vector of attributes for the relation
	//		a vector of strings that are the attributes that are to be the keys
	Relation(string r_name, vector<Attribute> a_list, vector<string> key_names);
	
	/*accessors*/
	// Get the column that has as a specific name
	// Input a string of the name of an attribute to look for
	// Returns a int that is the column position
	int find_attribute_column(string attribute) const;
	// Check to see if an attribute is in the relation
	// Input a string of the name of an attribute to look for
	// Returns a bool, true if attribute with that name exist false otherwise
	bool has_attribute(string attribute) const;
	// Gets the name of the relation
	// Returns a string that is the name of the relation
	string get_relation_name() const;
	// Get a list of the attributes in the relation
	// Returns a vector of strings that are the names of the attributes
	vector<string> get_attributes() const;
	// Get a list of the attributes in the relation
	// Returns a vector of Attributes that are in the relation
	vector<Attribute> get_attributes_list() const;
	// Get a tuple by its index
	// Input a int that is the index of the tuple
	// Returns a tuple
	Tuple get_tuple(int index) const;
	// Get a list of the tuples
	// Returns a vector of tuples in this relation
	vector<Tuple> get_tuple_list() const;
	// Get the number of tuples in the relation
	// Returns an int
	int get_num_tuples() const;
	// Get the number of attributes in the tuple
	// Returns an int
	int get_num_attributes() const;
	// Get a list keys
	// Returns a vector of strings that are the keys in the relation
	vector<string> get_key_list() const;
	
	
	/*modifiers*/
	// Insert a tuple into the relation
	// Input a vector of strings that are the values of of the data in the tuples
	void insert_tuple(vector<string>values);
	// Insert the tuples from another relation
	// Input a relation to get tuples from
	void insert_from_relation(Relation r);
	// Delete tuples based on a condition
	// Input a condition to evaluate tuples on
	void delete_from(Condition con);
	// Updates specific attributes of all tuples with new data if they meet a condition
	// Input a vector of strings for a list of the attributes that will be updated
	//		a vector of strings for corresponding data to update attributes with
	//		a Condition to check each tuple against
	void update(vector<string> aname, vector<string> update, Condition con);
	// This relation becomes the selection of an input relation
	// Input a condition to check each tuple in the relation being selected
	//		a relation to select from
	void select(Condition con, Relation r);
	// This relation becomes the projection of an input relation
	// Input a vector of strings for the attributes to project
	//		a relation to project from
	void project(vector<string> att_list, Relation r);
	// This relation becomes the renaming of an input relation
	// Input a vector of strings that are the attributes renamed
	//		a relation to rename the attributes from
	void rename(vector<string> att_list, Relation r);
	// This relation becomes the natural join of two input relations
	// Input a relation to be the left side of the join
	//		a relation to join with the first input
	void natural_join(Relation r1, Relation r2);
	// Change the name of this relation
	// Input a string for the new name of the relation
	void rename_relation(string name);
	
	/*operators*/
	// Perform a Union of two relations
	Relation operator+(const Relation &r) const;
	// Perform a Difference of two relations
	Relation operator-(const Relation &r) const;
	// Perform a Cross Product of two relations
	Relation operator*(const Relation &r) const;
	// Print the relation to a output stream
	friend ostream& operator<<(ostream& os, Relation r);
};

/* End of the Relation Class */

