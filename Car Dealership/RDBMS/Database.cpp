#include "Database.h"

/* Definitions of the Database Class */

/*constructors -------------------------------------------------------------------------------*/
// Default Constructor
Database::Database(){
}

/*accessors ----------------------------------------------------------------------------------*/
// Get a relation from the database
// Input the name of the relation as a string
// Returns a relation
Relation Database::get_relation(string rname) const{
	for(size_t i = 0; i < relations.size(); i++){
		if(rname.compare(relations[i].get_relation_name()) == 0){
			return relations[i];
		}
	}
	throw RuntimeException("Relation not found");
}

// Get the number of relations in the datbase
// Returns the number of relations in the database
int Database::get_num_relations() const{
	return relations.size();
}

/*modifiers ----------------------------------------------------------------------------------*/
// Adds a relation to the database
// Input a relation to be added to the database
void Database::add_relation(Relation r){
	string rname = r.get_relation_name();
	for (size_t i = 0; i < relations.size(); i++){
		if (rname.compare(relations[i].get_relation_name()) == 0){
			relations[i] = r;
			return;
		}
	}
	relations.push_back(r);
}

// Create a relation in the database
// Input a string for the name of the relation
//		a vector of strings for the list of attributes
//		a vector of ints for the attribute types 1 if string 0 if int
//		a vector of ints for the length of the attributes (lengths will be ignored for ints so any value is acceptabe)
//		a vector of strings for the attributes to use as keys
void Database::create_relation(string rname, vector<string> aname, vector<int> atype, vector<int> alength, vector<string> kname){
	if(aname.size() == atype.size() && aname.size() == alength.size()){
		vector<Attribute> attributes;
		for (size_t i = 0; i < aname.size(); ++i){
			attributes.push_back(Attribute(aname[i], atype[i], alength[i]));
		}
		for (size_t i = 0; i < relations.size(); i++){
			if (relations[i].get_relation_name().compare(rname) == 0){
				relations[i] = Relation(rname, attributes, kname);
				return;
			}
		}
		relations.push_back(Relation(rname, attributes, kname));
	}
	else{
		throw RuntimeException("Can not create new relation, attribute lengths do not match");
	}
}

// Drops a relation from the database
// Input a string for the relation name
void Database::drop_relation(string rname){
	for(size_t i = 0; i < relations.size(); i++){
		if(rname.compare(relations[i].get_relation_name()) == 0){
			relations.erase(relations.begin()+i);
			break;
		}
	}
}

// Inserts a tuple into a relation in the database
// Input a string for the relation to insert the tuple into
//		a vector of strings for the tuple data
void Database::insert_into(string rname, vector<string> tuple){
	for(size_t i = 0; i < relations.size(); i++){
		if(rname.compare(relations[i].get_relation_name()) == 0){
			relations[i].insert_tuple(tuple);
			break;
		}
	}
}

// Inserts the tuples from a relation to a relation in the database
// Input a string for the relation to add tuples to
//		a Relation to copy the tuples from
void Database::insert_into(string rname, Relation from){
	for(size_t i = 0; i < relations.size(); i++){
		if(rname.compare(relations[i].get_relation_name()) == 0){
			relations[i].insert_from_relation(from);
			break;
		}
	}
}

// Updates specific attributes of all tuples in a relation in the database with new data if they meet a condition
// Input a string for the name of the relation to update
//		a vector of strings for a list of the attributes that will be updated
//		a vector of strings for corresponding data to update attributes with
//		a Condition to check each tuple against
void Database::update(string rname, vector<string> aname, vector<string> update, Condition con){
	for(size_t i = 0; i < relations.size(); i++){
		if(rname.compare(relations[i].get_relation_name()) == 0){
			relations[i].update(aname, update, con);
			break;
		}
	}
}

// Deletes tuples from a relation in the database if they meet a condition
//	Input a string for the name of the relation to delete from
//		a condition to check each tuple against
void Database::delete_from(string rname, Condition con){
	for(size_t i = 0; i < relations.size(); i++){
		if(rname.compare(relations[i].get_relation_name()) == 0){
			relations[i].delete_from(con);
			break;
		}
	}
}

// Perform the select operation on a relation based on a condition
// Input a condition to check each tuple in the relation being selected
//		a relation to perform the selection from
// Returns a relation that is the selection of the input relation with the input condition
Relation Database::select(Condition con, Relation r){
	Relation selected("Selection");
	selected.select(con, r);
	return selected;
}

// Perform a projection on a relation getting a subset of the tables based on attributes
// Input a vecotr of strings that is a list of attributes to be in the projection
//		a relation to get the projection of the listed attributes
// Returns a relation that is a subset of the input relations attributes
Relation Database::project(vector<string> att_list, Relation r){
	Relation projection("Projection");
	projection.project(att_list, r);
	return projection;
}

// Perform a rename on a relation changing all of its attribute names
// Input a vector of strings that will be the new attribute names
//		a relation to get the renamed relation from
// Retuns a relation that has renamed attributes of the input relation
Relation Database::rename(vector<string> att_list, Relation r){
	Relation renamed("Renamed");
	renamed.rename(att_list, r);
	return renamed;
}

// Perform a set union between two relation
// Input a relation that is to be unioned
//		a second relation that is to be unioned
// Returns a relation that is the union of the two input relations
Relation Database::set_union(Relation r1, Relation r2){
	return r1 + r2;
}

// Perform a set difference between two relation
// Input a relation to be subtracted from
//		a second relation thats common tuples will be subtracted
// Returns a relation that is the difference of the first input relation and the second
Relation Database::set_difference(Relation r1, Relation r2){
	return r1 - r2;
}

// Perform a cross product between two relation
// Input a relation to be the left hand side of the cross product
//		a second relation thats the right side
// Returns a relation that is the cross product of input relation one cross input relation two
Relation Database::product(Relation r1, Relation r2){
	return r1 * r2;
}

// Performs the natural join of two relations
// Input a relation that is the left hand side of the join
//		a relation that is the right hand side
// Returns a relation that is the first input relation joined with the second
Relation Database::join(Relation r1, Relation r2){
	Relation joined("Natural Join");
	joined.natural_join(r1, r2);
	return joined;
}

// Write a relation to a file
// Input a string for the name of the relation in the database to write
void Database::write_relation(string rname){
	size_t r_pos;
	for (r_pos = 0; r_pos < relations.size(); r_pos++){
		if (rname.compare(relations[r_pos].get_relation_name()) == 0){
			break;
		}
	}
	/*
	if (r_pos >= (int)relations.size()){
		throw RuntimeException("Relation not in database");
	}*/

	ofstream db_file;
	string db_filename = rname + ".db";
	db_file.open(db_filename);

	db_file << "CREATE TABLE " + rname + "(";

	vector<Attribute> atts = relations[r_pos].get_attributes_list();
	size_t i;
	for (i = 0; i < atts.size() - 1; i++){
		if (atts[i].get_attribute_type() == 1){
			db_file <<atts[i].get_attribute_name() << " VARCHAR(" << atts[i].get_attribute_length() << "), ";
		}
		else{
			db_file << atts[i].get_attribute_name() << " INTEGER,";
		}
	}
	if (atts[i].get_attribute_type() == 1){
		db_file << "\"" << atts[i].get_attribute_name() << "\" VARCHAR(" << atts[i].get_attribute_length() << ")) PRIMARY KEY (";
	}
	else{
		db_file << atts[i].get_attribute_name() << " INTEGER) PRIMARY KEY (";
	}

	vector<string> keys = relations[r_pos].get_key_list();
	for (i = 0; i < keys.size() - 1; i++){
		db_file << keys[i] << ", ";
	}
	db_file << keys[i] << ");\n";

	vector<Tuple> tuples = relations[r_pos].get_tuple_list();
	for (size_t i = 0; i < tuples.size(); i++){
		db_file << "INSERT INTO " << rname << " VALUES FROM (";
		vector<Cell> cells = tuples[i].get_cells();
		size_t j;
		for (j = 0; j < cells.size() - 1; j++){
			if (cells[j].get_type() == 1){
				db_file << "\"" << cells[j].get_value() << "\", ";
			}
			else{
				db_file << cells[j].get_value() << ", ";
			}
		}
		if (cells[j].get_type() == 1){
			db_file << "\"" << cells[j].get_value() << "\");\n";
		}
		else{
			db_file << cells[j].get_value() << ");\n";
		}
	}

	db_file.close();
}

/*operators ----------------------------------------------------------------------------------*/

/* End of definitions */
