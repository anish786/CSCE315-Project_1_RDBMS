#include "Database.h"

/* Definitions of the Database Class */

/*constructors -------------------------------------------------------------------------------*/
Database::Database(){
}

Database::~Database(){
}

/*accessors ----------------------------------------------------------------------------------*/
Relation Database::get_relation(string rname) const{
	for(size_t i = 0; i < relations.size(); i++){
		if(rname.compare(relations[i].get_relation_name()) == 0){
			return relations[i];
		}
	}
	throw RuntimeException("Relation not found");
}

int Database::get_num_relations() const{
	return relations.size();
}

/*modifiers ----------------------------------------------------------------------------------*/

void Database::create_relation(string rname, vector<string> aname, vector<int> atype, vector<int> alength, vector<string> kname){
	if(aname.size() == atype.size() && aname.size() == alength.size()){

		vector<Attribute> attributes;
		for(size_t i = 0; i < aname.size(); ++i){
			attributes.push_back(Attribute(aname[i], atype[i], alength[i]));
		}
		relations.push_back(Relation(rname, attributes, kname));
	}
	else{
		throw RuntimeException("Can not create new relation, attribute lengths do not match");
	}
}

void Database::drop_relation(string rname){
	for(size_t i = 0; i < relations.size(); i++){
		if(rname.compare(relations[i].get_relation_name()) == 0){
			relations.erase(relations.begin()+i);
			break;
		}
	}
}

void Database::insert_into(string rname, vector<string> tuple){
	for(size_t i = 0; i < relations.size(); i++){
		if(rname.compare(relations[i].get_relation_name()) == 0){
			relations[i].insert_tuple(tuple);
			break;
		}
	}
}

void Database::insert_into(string rname, Relation from){
	for(size_t i = 0; i < relations.size(); i++){
		if(rname.compare(relations[i].get_relation_name()) == 0){
			relations[i].insert_from_relation(from);
			break;
		}
	}
}

void Database::update(string rname, vector<string> aname, vector<string> update, Condition con){
	for(size_t i = 0; i < relations.size(); i++){
		if(rname.compare(relations[i].get_relation_name()) == 0){
			relations[i].update(aname, update, con);
			break;
		}
	}
}

void Database::delete_from(string rname, Condition con){
	for(size_t i = 0; i < relations.size(); i++){
		if(rname.compare(relations[i].get_relation_name()) == 0){
			relations[i].delete_from(con);
			break;
		}
	}
}

Relation Database::select(Condition con, Relation r){
	Relation selected("Selection");
	selected.select(con, r);
	return selected;
}

Relation Database::project(vector<string> att_list, Relation r){
	Relation projection("Projection");
	projection.project(att_list, r);
	return projection;
}

Relation Database::rename(vector<string> att_list, Relation r){
	Relation renamed("Renamed");
	renamed.rename(att_list, r);
	return renamed;
}

Relation Database::set_union(Relation r1, Relation r2){
	return r1 + r2;
}

Relation Database::set_difference(Relation r1, Relation r2){
	return r1 - r2;
}

Relation Database::product(Relation r1, Relation r2){
	return r1 * r2;
}

Relation Database::join(Relation r1, Relation r2){
	Relation joined("Natural Join");
	joined.natural_join(r1, r2);
	return joined;
}

/*operators ----------------------------------------------------------------------------------*/

/* End of definitions */
