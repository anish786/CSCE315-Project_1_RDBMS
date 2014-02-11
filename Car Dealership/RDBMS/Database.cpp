#include "Database.h"

/* Definitions of the Database Class */
/*
Additional comments
Imlementations needed:


CREATE TABLE (PRIMARY KEY)
DROP TABLE

INSERT INTO
UPDATE
DELETE FROM

SELECTION
PROJECTION
RENAMING
SET UNION
SET DIFFERENCE
CROSS PRODUCT

No file I/0
No parser (everything is through funtion call)
*/

/*constructors -------------------------------------------------------------------------------*/
Database::Database(){
}

Database::~Database(){
}

/*accessors ----------------------------------------------------------------------------------*/

/*modifiers ----------------------------------------------------------------------------------*/

void Database::create_relation(string rname, vector<string> aname, vector<string> atype, vector<int> alength, vector<string> kname){
	vector<Attribute> attributes;
	for(size_t i = 0; i < aname.size(); i++){
		attributes.push_back(Attribute(aname[i], atype[i], alength[i]));
	}
	relations.push_back(Relation(rname, attributes, kname));
}

void Database::create_relation(string rname, vector<string> aname, vector<string> atype, vector<string> kname){
	vector<Attribute> attributes;
	for(size_t i = 0; i < aname.size(); i++){
		attributes.push_back(Attribute(aname[i], atype[i]));
	}
	relations.push_back(Relation(rname, attributes, kname));
}

void Database::drop_relation(string rname){
	for(size_t i = 0; i < relations.size(); i++){
		if(rname.compare(relations[i].get_relation_name()) == 0){
			relations.erase(relations.begin()+i);
			break;
		}
	}
}

/*operators ----------------------------------------------------------------------------------*/

/* End of definitions */