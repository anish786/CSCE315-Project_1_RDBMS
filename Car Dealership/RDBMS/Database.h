#pragma once

#include "Relation.h"

/* Declaration of the Database Class */

using namespace std;

class Database {
	// A list of all relations in this database
	vector<Relation> relations;
public:
	/*constructors*/
	// Default Constructor
	Database();

	/*accessors*/
	// Get a relation from the database
	// Input the name of the relation as a string
	// Returns a relation
	Relation get_relation(string rname) const;
	// Get the number of relations in the datbase
	// Returns the number of relations in the database
	int get_num_relations() const;

	/*modifiers*/
	// Create a relation in the database
	// Input a string for the name of the relation
	//		a vector of strings for the list of attributes
	//		a vector of ints for the attribute types 1 if string 0 if int
	//		a vector of ints for the length of the attributes (lengths will be ignored for ints so any value is acceptabe)
	//		a vector of strings for the attributes to use as keys
	void create_relation(string rname, vector<string> aname, vector<int> atype, vector<int> alength, vector<string> kname);
	// Drops a relation from the database
	// Input a string for the relation name
	void drop_relation(string rname);
	// Inserts a tuple into a relation in the database
	// Input a string for the relation to insert the tuple into
	//		a vector of strings for the tuple data
	void insert_into(string rname, vector<string> tuple);
	// Inserts the tuples from a relation to a relation in the database
	// Input a string for the relation to add tuples to
	//		a Relation to copy the tuples from
	void insert_into(string rname, Relation from);
	// Updates specific attributes of all tuples in a relation in the database with new data if they meet a condition
	// Input a string for the name of the relation to update
	//		a vector of strings for a list of the attributes that will be updated
	//		a vector of strings for corresponding data to update attributes with
	//		a Condition to check each tuple against
	void update(string rname, vector<string> aname, vector<string> update, Condition con);
	// Deletes tuples from a relation in the database if they meet a condition
	//	Input a string for the name of the relation to delete from
	//		a condition to check each tuple against
	void delete_from(string rname, Condition con);
	// Perform the select operation on a relation based on a condition
	// Input a condition to check each tuple in the relation being selected
	//		a relation to perform the selection from
	// Returns a relation that is the selection of the input relation with the input condition
	Relation select(Condition con, Relation r);
	// Perform a projection on a relation getting a subset of the tables based on attributes
	// Input a vecotr of strings that is a list of attributes to be in the projection
	//		a relation to get the projection of the listed attributes
	// Returns a relation that is a subset of the input relations attributes
	Relation project(vector<string> att_list, Relation r);
	// Perform a rename on a relation changing all of its attribute names
	// Input a vector of strings that will be the new attribute names
	//		a relation to get the renamed relation from
	// Retuns a relation that has renamed attributes of the input relation
	Relation rename(vector<string> att_list, Relation r);
	// Perform a set union between two relation
	// Input a relation that is to be unioned
	//		a second relation that is to be unioned
	// Returns a relation that is the union of the two input relations
	Relation set_union(Relation r1, Relation r2);
	// Perform a set difference between two relation
	// Input a relation to be subtracted from
	//		a second relation thats common tuples will be subtracted
	// Returns a relation that is the difference of the first input relation and the second
	Relation set_difference(Relation r1, Relation r2);
	// Perform a cross product between two relation
	// Input a relation to be the left hand side of the cross product
	//		a second relation thats the right side
	// Returns a relation that is the cross product of input relation one cross input relation two
	Relation product(Relation r1, Relation r2);
	// Performs the natural join of two relations
	// Input a relation that is the left hand side of the join
	//		a relation that is the right hand side
	// Returns a relation that is the first input relation joined with the second
	Relation join(Relation r1, Relation r2);
	/*operators*/

};

/* End of the Database Class */
