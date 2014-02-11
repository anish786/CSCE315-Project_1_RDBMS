#pragma once

#include "Relation.h"

/* Declaration of the Database Class */

/*
Additional comments
Imlementations needed:


-CREATE TABLE (PRIMARY KEY)
-DROP TABLE			Delete a table

-INSERT INTO			Insert Tuble into a relation
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

using namespace std;

class Database {
	vector<Relation> relations;
public:
	/*constructors*/
	Database();
	~Database();

	/*accessors*/
	Relation get_relation(string rname);


	/*modifiers*/
	Relation evaluate_expression(vector<string> atomic_expression);
	void create_relation(string rname, vector<string> aname, vector<string> atype, vector<int> alength, vector<string> kname);
	void create_relation(string rname, vector<string> aname, vector<string> atype, vector<string> kname);
	void drop_relation(string rname);
	void insert_into(string rname, vector<string> tuple);
	void insert_into(string rname, Relation from);
	void update(string rname, vector<string> aname, vector<string> update, vector<string> conditions);
	void delete_from(string rname, vector<string> conditions);
	Relation select(vector<string> att_list, Relation r);
	Relation project(vector<string> att_list, Relation r);
	Relation rename(vector<string> att_list, Relation r);
	Relation set_union(Relation r1, Relation r2);
	Relation set_difference(Relation r1, Relation r2);
	Relation product(Relation r1, Relation r2);
	Relation join(Relation r1, Relation r2);
	/*operators*/

};

/* End of the Database Class */
