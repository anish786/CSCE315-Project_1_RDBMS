#include "Database.h"

/* Definitions of the Database Class */
/*
Additional comments
Imlementations needed:


CREATE TABLE (PRIMARY KEY)
DROP TABLE			Delete a table

INSERT INTO			Insert Tuble into a relation
UPDATE				Update a Tuple
DELETE FROM			Delete a Tuble from a relation

SELECTION			Creates a subset of the tuples in a relation that satisfy a condition
PROJECTION			Creates a relation that lists only a subset of columns (attributes) for the tuples
RENAMING			
SET UNION			Set of all elements in A or B or both
SET DIFFERENCE		Set of all elements that are either in A or B
CROSS PRODUCT		Creates a relation between two relations of all the sets of pairs between the two
(NATURAL JOIN)		Combine two relations that have at least one matching attribute, delete tuples that do not share matching
					values in the matching relation.

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
