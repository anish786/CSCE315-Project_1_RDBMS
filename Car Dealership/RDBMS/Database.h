#pragma once

/*
Additional comments
Imlementations needed:

-CREATE TABLE (PRIMARY KEY)
-DROP TABLE

-INSERT INTO
-UPDATE
DELETE FROM

SELECTION
PROJECTION
-RENAMING
-SET UNION
SET DIFFERENCE
-CROSS PRODUCT

No file I/0
No parser (everything is through funtion call)
*/

#include "Relation.h"

/* Declaration of the Database Class */

using namespace std;

class Database {
	vector<Relation> relations;
public:
	/*constructors*/
	Database();
	~Database();

	/*accessors*/

	/*modifiers*/
	void create_relation(string rname, vector<string> aname, vector<string> atype, vector<int> alength, vector<string> kname);
	void create_relation(string rname, vector<string> aname, vector<string> atype, vector<string> kname);
	void drop_relation(string rname);

	/*operators*/

};

/* End of the Database Class */
