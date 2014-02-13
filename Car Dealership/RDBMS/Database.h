#pragma once

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
	Relation get_relation(string rname) const;
	int get_num_relations() const;

	/*modifiers*/
	void create_relation(string rname, vector<string> aname, vector<int> atype, vector<int> alength, vector<string> kname);
	void drop_relation(string rname);
	void insert_into(string rname, vector<string> tuple);
	void insert_into(string rname, Relation from);
	void update(string rname, vector<string> aname, vector<string> update, Condition con);
	void delete_from(string rname, Condition con);
	Relation select(Condition con, Relation r);
	Relation project(vector<string> att_list, Relation r);
	Relation rename(vector<string> att_list, Relation r);
	Relation set_union(Relation r1, Relation r2);
	Relation set_difference(Relation r1, Relation r2);
	Relation product(Relation r1, Relation r2);
	Relation join(Relation r1, Relation r2);
	/*operators*/

};

/* End of the Database Class */
