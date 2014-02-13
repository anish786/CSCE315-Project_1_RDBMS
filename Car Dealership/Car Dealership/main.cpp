#include "Database.h"

int main(){
	Database db;

	Attribute a( "Make", 1, 16);
	Attribute b( "Model", 1, 16);
	Attribute c( "Year", 0);

	vector< Attribute > t1att;
	t1att.push_back(a);
	t1att.push_back(b);
	t1att.push_back(c);

	vector<string> atts;
	atts.push_back("Make");
	atts.push_back("Model");
	atts.push_back("Year");

	vector<int> atts_types;
	atts_types.push_back(1);
	atts_types.push_back(1);
	atts_types.push_back(0);

	vector<int> atts_lengths;
	atts_lengths.push_back(12);
	atts_lengths.push_back(12);
	atts_lengths.push_back(0);

	vector<string> keys;
	keys.push_back("Make");
	keys.push_back("Model");

	vector<string> t1;
	t1.push_back("Ford");
	t1.push_back("F150");
	t1.push_back("2013");

	vector<string> t2;
	t2.push_back("Toyota");
	t2.push_back("Matrix");
	t2.push_back("2012");

	vector<string> t3;
	t3.push_back("Ford");
	t3.push_back("Prius");
	t3.push_back("2011");

	vector<string> t4;
	t4.push_back("Lamborghini");
	t4.push_back("Diablo");
	t4.push_back("2014");

	Relation c1 = Relation("Cars1", t1att, keys);
	c1.insert_tuple(t1);
	c1.insert_tuple(t2);
	Relation c2 = Relation("Cars2", t1att, keys);
	c2.insert_tuple(t1);
	c2.insert_tuple(t3);
	c2.insert_tuple(t4);
	
	db.create_relation("CARS", atts, atts_types, atts_lengths, keys);
	db.get_relation("CARS").insert_tuple(t1);
	db.get_relation("CARS").insert_tuple(t2);
	db.create_relation("CARS2", atts, atts_types, atts_lengths, keys);
	db.get_relation("CARS2").insert_tuple(t1);
	db.get_relation("CARS2").insert_tuple(t3);
	db.get_relation("CARS2").insert_tuple(t4);

	cout << db.get_relation("CARS") << db.get_relation("CARS2") << c1 << c2 << endl;
}