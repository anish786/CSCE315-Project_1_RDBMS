#include "stdafx.h"
#include "CppUnitTest.h"

#include "Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestParserDilimiterAndTokenChecks)
		{
			Parser parser;
			//Test delimiter checks
			bool test = parser.is_delimiter('\"');
			Assert::IsTrue(test);
			test = parser.is_delimiter('p');
			Assert::IsFalse(test);

			//Test token checks
			test = parser.is_token('+');
			Assert::IsTrue(test);
			test = parser.is_token(' ');
			Assert::IsFalse(test);

			//Test double token checks
			test = parser.is_double_token('+');
			Assert::IsFalse(test);
			test = parser.is_double_token('=');
			Assert::IsTrue(test);
		}

		TEST_METHOD(TestParserTokenizer)
		{
			std::string test_command = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind)";
			std::vector<std::string> tokens;
			Parser parser;

			parser.tokenize(test_command, &tokens);

			Assert::AreEqual(26, (int)tokens.size());
			Assert::AreEqual("CREATE", tokens[0].c_str());
			Assert::AreEqual("TABLE", tokens[1].c_str());

			test_command = "INSERT INTO tools VALUES FROM (\"screw driver\", 1, 2)";
			std::vector<std::string> tokens2;

			parser.tokenize(test_command, &tokens2);

			Assert::AreEqual(12, (int)tokens2.size());
			Assert::AreEqual("INSERT", tokens2[0].c_str());
			Assert::AreEqual("screw driver", tokens2[6].c_str());

			test_command = "INSERT INTO tools VALUES FROM (\"hammer\", 3, 10)";
			std::vector<std::string> tokens3;

			parser.tokenize(test_command, &tokens3);

			Assert::AreEqual(12, (int)tokens2.size());
			Assert::AreEqual("INSERT", tokens3[0].c_str());
			Assert::AreEqual("hammer", tokens3[6].c_str());
		}

		TEST_METHOD(TestParserCreateCondition)
		{
			vector<string> condition_exp;
			condition_exp.push_back("(");
			condition_exp.push_back("x1");
			condition_exp.push_back(">=");
			condition_exp.push_back("0");
			condition_exp.push_back("&&");
			condition_exp.push_back("(");
			condition_exp.push_back("x1");
			condition_exp.push_back("<");
			condition_exp.push_back("3");
			condition_exp.push_back("||");
			condition_exp.push_back("x1");
			condition_exp.push_back("==");
			condition_exp.push_back("10");
			condition_exp.push_back(")");
			condition_exp.push_back(")");
			condition_exp.push_back("||");
			condition_exp.push_back("x1");
			condition_exp.push_back("==");
			condition_exp.push_back("x2");

			Parser parser;

			Condition cond(parser.create_condition(condition_exp));

			vector<string> variables;
			variables.push_back("x1");
			variables.push_back("x2");

			vector<string> values;
			values.push_back("2");
			values.push_back("5");

			Assert::IsTrue(cond.evaluate(variables, values));
		}

		TEST_METHOD(TestParser)
		{
			Parser psr;
			psr.parse_command("CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);");
			psr.parse_command("INSERT INTO animals VALUES FROM(\"Joe\", \"cat\", 4);");
			psr.parse_command("INSERT INTO animals VALUES FROM (\"Spot\", \"dog\", 10);");
			psr.parse_command("INSERT INTO animals VALUES FROM (\"Snoopy\", \"dog\", 3);");
			psr.parse_command("INSERT INTO animals VALUES FROM (\"Tweety\", \"bird\", 1);");
			psr.parse_command("INSERT INTO animals VALUES FROM (\"Joe\", \"bird\", 2);");

			Assert::AreEqual(1, psr.get_database().get_num_relations());
			Assert::AreEqual(3, psr.get_database().get_relation("animals").get_num_attributes());
			Assert::AreEqual(5, psr.get_database().get_relation("animals").get_num_tuples());

			psr.parse_command("WRITE animals;");
			psr.parse_command("OPEN animals;");

			Assert::AreEqual(1, psr.get_database().get_num_relations());
			Assert::AreEqual(3, psr.get_database().get_relation("animals").get_num_attributes());
			Assert::AreEqual(5, psr.get_database().get_relation("animals").get_num_tuples());

			psr.parse_command("CREATE TABLE tools (kind VARCHAR(8), weight INTEGER, cost INTEGER) PRIMARY KEY (kind);");
			psr.parse_command("INSERT INTO tools VALUES FROM (\"hammer\", 3, 10);");
			psr.parse_command("INSERT INTO tools VALUES FROM (\"screw driver\", 1, 2);");
			psr.parse_command("INSERT INTO tools VALUES FROM (\"plane\", 2, 10);");
			psr.parse_command("INSERT INTO tools VALUES FROM (\"hand saw\", 2, 22);");
			psr.parse_command("INSERT INTO tools VALUES FROM (\"blow torch\", 3, 25);");
			psr.parse_command("INSERT INTO tools VALUES FROM (\"jack hammer\", 55, 300);");
			psr.parse_command("INSERT INTO tools VALUES FROM (\"plow\", 300, 500);");

			Assert::AreEqual(2, psr.get_database().get_num_relations());
			Assert::AreEqual(3, psr.get_database().get_relation("tools").get_num_attributes());
			Assert::AreEqual(4, psr.get_database().get_relation("tools").get_num_tuples());

			psr.parse_command("CREATE TABLE friends (fname VARCHAR(20), lname VARCHAR(20), personality VARCHAR(20), value INTEGER) PRIMARY KEY (fname, lname);");
			psr.parse_command("INSERT INTO friends VALUES FROM (\"X\", \"N/A\", \"Awesome!\", 100);");
			psr.parse_command("INSERT INTO friends VALUES FROM (\"Smith\", \"Smith\", \"Annoying\", 5);");
			psr.parse_command("INSERT INTO friends VALUES FROM (\"Algebra\", \"Homework\", \"Boring\", -100);");

			Assert::AreEqual(3, psr.get_database().get_num_relations());
			Assert::AreEqual(4, psr.get_database().get_relation("friends").get_num_attributes());
			Assert::AreEqual(3, psr.get_database().get_relation("friends").get_num_tuples());

			psr.parse_command("CREATE TABLE enemies (fname VARCHAR(20), lname VARCHAR(20), personality VARCHAR(20), value INTEGER) PRIMARY KEY (fname, lname);");
			psr.parse_command("INSERT INTO enemies VALUES FROM (\"X\", \"N/A\", \"Awesome!\", 100);");
			psr.parse_command("INSERT INTO enemies VALUES FROM (\"The\", \"Penguin\", \"Weird\", 100);");
			psr.parse_command("INSERT INTO enemies VALUES FROM (\"Joker\", \"N/A\", \"Weird\", 150);");

			Assert::AreEqual(4, psr.get_database().get_num_relations());
			Assert::AreEqual(4, psr.get_database().get_relation("enemies").get_num_attributes());
			Assert::AreEqual(3, psr.get_database().get_relation("enemies").get_num_tuples());

			psr.parse_command("project_test <- project (fname, lname) friends;");

			Assert::AreEqual(5, psr.get_database().get_num_relations());
			Assert::AreEqual(2, psr.get_database().get_relation("project_test").get_num_attributes());
			Assert::AreEqual(3, psr.get_database().get_relation("project_test").get_num_tuples());

			psr.parse_command("rename_test <- rename (v_fname, v_lname, v_personality, v_bounty) enemies;");

			Assert::AreEqual(6, psr.get_database().get_num_relations());
			Assert::AreEqual(4, psr.get_database().get_relation("rename_test").get_num_attributes());
			Assert::AreEqual(3, psr.get_database().get_relation("rename_test").get_num_tuples());
			Assert::AreEqual("v_fname", psr.get_database().get_relation("rename_test").get_attributes()[0].c_str());

			psr.parse_command("good_and_bad_guys <- friends + enemies;");

			Assert::AreEqual(7, psr.get_database().get_num_relations());
			Assert::AreEqual(4, psr.get_database().get_relation("good_and_bad_guys").get_num_attributes());
			Assert::AreEqual(5, psr.get_database().get_relation("good_and_bad_guys").get_num_tuples());

			psr.parse_command("diff_test <- friends - enemies;");

			Assert::AreEqual(8, psr.get_database().get_num_relations());
			Assert::AreEqual(4, psr.get_database().get_relation("diff_test").get_num_attributes());
			Assert::AreEqual(2, psr.get_database().get_relation("diff_test").get_num_tuples());

			psr.parse_command("CREATE TABLE baseball_players (fname VARCHAR(20), lname VARCHAR(30), team VARCHAR(20), homeruns INTEGER, salary INTEGER) PRIMARY KEY (fname, lname);");
			psr.parse_command("INSERT INTO baseball_players VALUES FROM (\"Joe\", \"Swatter\", \"Pirates\", 40, 1000000);");
			psr.parse_command("INSERT INTO baseball_players VALUES FROM (\"Sarah\", \"Batter\", \"Dinosaurs\", 100, 5000000);");
			psr.parse_command("INSERT INTO baseball_players VALUES FROM (\"Snoopy\", \"Slinger\", \"Pirates\", 3, 200000);");
			psr.parse_command("INSERT INTO baseball_players VALUES FROM (\"Donald\", \"Runner\", \"Dinosaurs\", 89, 200000);");
			psr.parse_command("INSERT INTO baseball_players VALUES FROM (\"Alexander\", \"Smith\", \"Pirates\", 2, 150000);");

			Assert::AreEqual(9, psr.get_database().get_num_relations());
			Assert::AreEqual(5, psr.get_database().get_relation("baseball_players").get_num_attributes());
			Assert::AreEqual(5, psr.get_database().get_relation("baseball_players").get_num_tuples());

			psr.parse_command("high_hitters <- select (homeruns >= 40) baseball_players;");

			Assert::AreEqual(10, psr.get_database().get_num_relations());
			Assert::AreEqual(5, psr.get_database().get_relation("high_hitters").get_num_attributes());
			Assert::AreEqual(3, psr.get_database().get_relation("high_hitters").get_num_tuples());

			psr.parse_command("dinosaur_players <- select (team == \"Dinosaurs\") baseball_players;");

			Assert::AreEqual(11, psr.get_database().get_num_relations());
			Assert::AreEqual(5, psr.get_database().get_relation("dinosaur_players").get_num_attributes());
			Assert::AreEqual(2, psr.get_database().get_relation("dinosaur_players").get_num_tuples());

			psr.parse_command("high_hit_pirates <- select (team == \"Pirates\") (select (homeruns >= 40) baseball_players);");

			Assert::AreEqual(12, psr.get_database().get_num_relations());
			Assert::AreEqual(5, psr.get_database().get_relation("high_hit_pirates").get_num_attributes());
			Assert::AreEqual(1, psr.get_database().get_relation("high_hit_pirates").get_num_tuples());

			psr.parse_command("CREATE TABLE shapes (shape VARCHAR(20)) PRIMARY KEY (shape);");
			psr.parse_command("INSERT INTO shapes VALUES FROM (\"circle\");");
			psr.parse_command("INSERT INTO shapes VALUES FROM (\"square\");");
			psr.parse_command("INSERT INTO shapes VALUES FROM (\"rectangle\");");
			psr.parse_command("INSERT INTO shapes VALUES FROM (\"triangle\");");

			Assert::AreEqual(13, psr.get_database().get_num_relations());
			Assert::AreEqual(1, psr.get_database().get_relation("shapes").get_num_attributes());
			Assert::AreEqual(4, psr.get_database().get_relation("shapes").get_num_tuples());

			psr.parse_command("CREATE TABLE colors (color VARCHAR(20)) PRIMARY KEY (color);");
			psr.parse_command("INSERT INTO colors VALUES FROM (\"red\");");
			psr.parse_command("INSERT INTO colors VALUES FROM (\"blue\");");

			Assert::AreEqual(14, psr.get_database().get_num_relations());
			Assert::AreEqual(1, psr.get_database().get_relation("colors").get_num_attributes());
			Assert::AreEqual(2, psr.get_database().get_relation("colors").get_num_tuples());

			psr.parse_command("product_test <- shapes * colors;");

			Assert::AreEqual(15, psr.get_database().get_num_relations());
			Assert::AreEqual(2, psr.get_database().get_relation("product_test").get_num_attributes());
			Assert::AreEqual(8, psr.get_database().get_relation("product_test").get_num_tuples());

			psr.parse_command("CREATE TABLE shape_color (shape VARCHAR(20), color VARCHAR(20)) PRIMARY KEY (shape, color);");
			psr.parse_command("INSERT INTO shape_color VALUES FROM (\"circle\", \"red\");");
			psr.parse_command("INSERT INTO shape_color VALUES FROM (\"circle\", \"blue\");");
			psr.parse_command("INSERT INTO shape_color VALUES FROM (\"square\", \"red\");");
			psr.parse_command("INSERT INTO shape_color VALUES FROM (\"rectangle\", \"blue\");");
			psr.parse_command("INSERT INTO shape_color VALUES FROM (\"sphere\", \"orange\");");

			Assert::AreEqual(16, psr.get_database().get_num_relations());
			Assert::AreEqual(2, psr.get_database().get_relation("shape_color").get_num_attributes());
			Assert::AreEqual(5, psr.get_database().get_relation("shape_color").get_num_tuples());

			psr.parse_command("set_diff_test <- product_test - shape_color;");

			Assert::AreEqual(17, psr.get_database().get_num_relations());
			Assert::AreEqual(2, psr.get_database().get_relation("set_diff_test").get_num_attributes());
			Assert::AreEqual(4, psr.get_database().get_relation("set_diff_test").get_num_tuples());

			psr.parse_command("CREATE TABLE points (x INTEGER, y INTEGER, z INTEGER) PRIMARY KEY (x, y, z);");
			psr.parse_command("INSERT INTO points VALUES FROM (0, 0, 0);");
			psr.parse_command("INSERT INTO points VALUES FROM (1, 1, 1);");
			psr.parse_command("INSERT INTO points VALUES FROM (0, 1, 2);");
			psr.parse_command("INSERT INTO points VALUES FROM (-1, 20, 3);");
			psr.parse_command("INSERT INTO points VALUES FROM (-15, 0, 5);");

			Assert::AreEqual(18, psr.get_database().get_num_relations());
			Assert::AreEqual(3, psr.get_database().get_relation("points").get_num_attributes());
			Assert::AreEqual(5, psr.get_database().get_relation("points").get_num_tuples());

			psr.parse_command("CREATE TABLE dots (x1 INTEGER, y1 INTEGER, z1 INTEGER) PRIMARY KEY (x1, y1, z1);");
			psr.parse_command("INSERT INTO dots VALUES FROM (-1, 0, 20);");
			psr.parse_command("INSERT INTO dots VALUES FROM (3, 2, 5);");
			psr.parse_command("INSERT INTO dots VALUES FROM (0, 0, 0);");

			Assert::AreEqual(19, psr.get_database().get_num_relations());
			Assert::AreEqual(3, psr.get_database().get_relation("dots").get_num_attributes());
			Assert::AreEqual(3, psr.get_database().get_relation("dots").get_num_tuples());

			psr.parse_command("bad_query <- project (t) points;");

			Assert::AreEqual(19, psr.get_database().get_num_relations());

			psr.parse_command("dots_to_points <- rename (x2, y2, z2) dots;");

			Assert::AreEqual(20, psr.get_database().get_num_relations());
			Assert::AreEqual(3, psr.get_database().get_relation("dots_to_points").get_num_attributes());
			Assert::AreEqual(3, psr.get_database().get_relation("dots_to_points").get_num_tuples());
			Assert::AreEqual("x2", psr.get_database().get_relation("dots_to_points").get_attributes()[0].c_str());

			psr.parse_command("UPDATE dots SET x1 = 0 WHERE x1 < 0;");

			Assert::AreEqual("0", psr.get_database().get_relation("dots").get_tuple(0).get_cell_data(0).c_str());

			psr.parse_command("INSERT INTO points VALUES FROM RELATION select (z2 > 0) dots_to_points;");

			Assert::AreEqual(7, psr.get_database().get_relation("points").get_num_tuples());

			psr.parse_command("DELETE FROM dots WHERE (y1 <= 0);");

			Assert::AreEqual(1, psr.get_database().get_relation("dots").get_num_tuples());

			psr.parse_command("advanced_query <- project (x) (select (y == y2) (points * dots_to_points));");

			Assert::AreEqual(21, psr.get_database().get_num_relations());
			Assert::AreEqual(1, psr.get_database().get_relation("advanced_query").get_num_attributes());
			Assert::AreEqual(4, psr.get_database().get_relation("advanced_query").get_num_tuples());

		}

		TEST_METHOD(TestCompareTuple){
			Attribute a( "Make", 1, 16);
			Attribute b( "Model", 1, 16);
			Attribute c( "Year", 0);

			vector< Attribute > t1att;
			t1att.push_back(a);
			t1att.push_back(b);
			t1att.push_back(c);
	
			vector< string > values1;
			values1.push_back("Toyota");
			values1.push_back("Matrix");
			values1.push_back("2014");

			vector< string > values2;
			values2.push_back("Ford");
			values2.push_back("Prius");
			values2.push_back("2012");
    
			Tuple t1(t1att, values1);
			Tuple t2(t1att, values1);
			Tuple t3(t1att, values2);

			Assert::IsTrue(t1 == t2);
			Assert::IsFalse(t1 == t3);

		}
		TEST_METHOD(TestCompareCell){

			Attribute a( "Make", 1, 16);
			Attribute b( "Name", 1, 16);

			Cell c1(a, "Toyota");
			Cell c2(a, "Toyota");
			Cell c3(b, "Corolla");

			Assert::IsTrue(c1 == c2);
			Assert::IsFalse(c1 == c3);
		}

		TEST_METHOD(TestDBCommands){
			Database db;
			// Test creating a Relation
			vector<string> atts;
			atts.push_back("Attribute 1");
			atts.push_back("Attribute 2");
			atts.push_back("Attribute 3");

			vector<int> atts_types;
			atts_types.push_back(1);
			atts_types.push_back(1);
			atts_types.push_back(0);

			vector<int> atts_lengths;
			atts_lengths.push_back(20);
			atts_lengths.push_back(20);
			atts_lengths.push_back(0);

			vector<string> keys;
			keys.push_back("Attribute 1");
			keys.push_back("Attribute 3");

			db.create_relation("Relation 1", atts, atts_types, atts_lengths, keys);

			Assert::AreEqual(1, db.get_num_relations());
			Assert::AreEqual("Relation 1", db.get_relation("Relation 1").get_relation_name().c_str());

			// Test inserting a Tuple
			vector<string> tuple;
			tuple.push_back("String 1");
			tuple.push_back("String 2");
			tuple.push_back("10");

			db.insert_into("Relation 1", tuple);

			// Test inserting from another relation
			db.create_relation("Relation 2", atts, atts_types, atts_lengths, keys);
			vector<string> tuple2;
			tuple2.push_back("String 3");
			tuple2.push_back("String 4");
			tuple2.push_back("20");
			db.insert_into("Relation 2", tuple2);

			db.insert_into("Relation 1", db.get_relation("Relation 2"));
			Assert::AreEqual(2, db.get_relation("Relation 1").get_num_tuples());

			// Test update
			vector<string> att;
			att.push_back("Attribute 1");
			vector<string> new_value;
			new_value.push_back("String renamed");

			Comparison comp("Attribute 1", "String 1", "==");
			vector<Comparison> comps;
			comps.push_back(comp);
			Conjunction conj(comps);
			vector<Conjunction> conjs;
			conjs.push_back(conj);
			Condition cond(conjs);

			db.update("Relation 1", att, new_value, cond);
			Assert::AreEqual("String renamed", db.get_relation("Relation 1").get_tuple(0).get_cell_data(0).c_str());

			// Test Delete From
			Comparison comp2("Attribute 1", "String renamed", "==");
			vector<Comparison> comps2;
			comps2.push_back(comp2);
			Conjunction conj2(comps2);
			vector<Conjunction> conjs2;
			conjs2.push_back(conj2);
			Condition cond2(conjs2);

			db.delete_from("Relation 1", cond2);
			Assert::AreEqual(1, db.get_relation("Relation 1").get_num_tuples());

			// Test drop Relation
			db.drop_relation("Relation 1");
			Assert::AreEqual(1, db.get_num_relations());

		}

		TEST_METHOD(TestDBSelect){
			// Set up for Test
			Database db;
			
			vector<string> atts;
			atts.push_back("Attribute 1");
			atts.push_back("Attribute 2");
			atts.push_back("Attribute 3");

			vector<int> atts_types;
			atts_types.push_back(1);
			atts_types.push_back(1);
			atts_types.push_back(0);

			vector<int> atts_lengths;
			atts_lengths.push_back(20);
			atts_lengths.push_back(20);
			atts_lengths.push_back(0);

			vector<string> keys;
			keys.push_back("Attribute 1");
			keys.push_back("Attribute 3");

			db.create_relation("Relation 1", atts, atts_types, atts_lengths, keys);

			vector<string> tuple;
			tuple.push_back("String 1");
			tuple.push_back("String 2");
			tuple.push_back("0");

			db.insert_into("Relation 1", tuple);

			vector<string> tuple2;
			tuple2.push_back("String 3");
			tuple2.push_back("String 4");
			tuple2.push_back("50");

			db.insert_into("Relation 1", tuple2);

			vector<string> tuple3;
			tuple3.push_back("String 5");
			tuple3.push_back("String 6");
			tuple3.push_back("100");

			db.insert_into("Relation 1", tuple3);

			Comparison comp("Attribute 3", "50", ">=");
			vector<Comparison> comps;
			comps.push_back(comp);
			Conjunction conj(comps);
			vector<Conjunction> conjs;
			conjs.push_back(conj);
			Condition cond(conjs);

			// Test selection
			Relation r(db.select(cond, db.get_relation("Relation 1")));

			Assert::AreEqual(2, r.get_num_tuples());
			Assert::AreEqual("String 3", r.get_tuple(0).get_cell_data(0).c_str());
			Assert::AreEqual("String 5", r.get_tuple(1).get_cell_data(0).c_str());
		}

		TEST_METHOD(TestDBProject){
			// Set up for Test
			Database db;

			vector<string> atts;
			atts.push_back("Attribute 1");
			atts.push_back("Attribute 2");
			atts.push_back("Attribute 3");

			vector<int> atts_types;
			atts_types.push_back(1);
			atts_types.push_back(1);
			atts_types.push_back(0);

			vector<int> atts_lengths;
			atts_lengths.push_back(20);
			atts_lengths.push_back(20);
			atts_lengths.push_back(0);

			vector<string> keys;
			keys.push_back("Attribute 1");
			keys.push_back("Attribute 3");

			db.create_relation("Relation 1", atts, atts_types, atts_lengths, keys);

			vector<string> tuple;
			tuple.push_back("String 1");
			tuple.push_back("String 2");
			tuple.push_back("0");

			db.insert_into("Relation 1", tuple);

			vector<string> tuple2;
			tuple2.push_back("String 3");
			tuple2.push_back("String 4");
			tuple2.push_back("50");

			db.insert_into("Relation 1", tuple2);

			vector<string> tuple3;
			tuple3.push_back("String 5");
			tuple3.push_back("String 6");
			tuple3.push_back("100");

			db.insert_into("Relation 1", tuple3);

			vector<string> project_atts;
			project_atts.push_back("Attribute 1");
			project_atts.push_back("Attribute 3");

			// Test projection
			Relation r(db.project(project_atts, db.get_relation("Relation 1")));

			Assert::AreEqual(2, r.get_num_attributes());
			Assert::AreEqual(3, r.get_num_tuples());
			Assert::AreEqual("Attribute 1", r.get_attributes()[0].c_str());
			Assert::AreEqual("Attribute 3", r.get_attributes()[1].c_str());
		}

		TEST_METHOD(TestDBRename){
			// Set up for Test
			Database db;

			vector<string> atts;
			atts.push_back("Attribute 1");
			atts.push_back("Attribute 2");
			atts.push_back("Attribute 3");

			vector<int> atts_types;
			atts_types.push_back(1);
			atts_types.push_back(1);
			atts_types.push_back(0);

			vector<int> atts_lengths;
			atts_lengths.push_back(20);
			atts_lengths.push_back(20);
			atts_lengths.push_back(0);

			vector<string> keys;
			keys.push_back("Attribute 1");
			keys.push_back("Attribute 3");

			db.create_relation("Relation 1", atts, atts_types, atts_lengths, keys);

			vector<string> tuple;
			tuple.push_back("String 1");
			tuple.push_back("String 2");
			tuple.push_back("0");

			db.insert_into("Relation 1", tuple);

			vector<string> tuple2;
			tuple2.push_back("String 3");
			tuple2.push_back("String 4");
			tuple2.push_back("50");

			db.insert_into("Relation 1", tuple2);

			vector<string> tuple3;
			tuple3.push_back("String 5");
			tuple3.push_back("String 6");
			tuple3.push_back("100");

			db.insert_into("Relation 1", tuple3);

			vector<string> atts_renamed;
			atts_renamed.push_back("New 1");
			atts_renamed.push_back("New 2");
			atts_renamed.push_back("New 3");

			// Test renaming
			Relation r(db.rename(atts_renamed, db.get_relation("Relation 1")));

			Assert::AreEqual("New 1", r.get_attributes()[0].c_str());
			Assert::AreEqual("New 2", r.get_attributes()[1].c_str());
			Assert::AreEqual("New 3", r.get_attributes()[2].c_str());
			Assert::AreEqual(3, r.get_num_tuples());

		}

		TEST_METHOD(TestDBSetUnion){
			// Set up for Test
			Database db;

			vector<string> atts;
			atts.push_back("Attribute 1");
			atts.push_back("Attribute 2");
			atts.push_back("Attribute 3");

			vector<int> atts_types;
			atts_types.push_back(1);
			atts_types.push_back(1);
			atts_types.push_back(0);

			vector<int> atts_lengths;
			atts_lengths.push_back(20);
			atts_lengths.push_back(20);
			atts_lengths.push_back(0);

			vector<string> keys;
			keys.push_back("Attribute 1");
			keys.push_back("Attribute 3");

			db.create_relation("Relation 1", atts, atts_types, atts_lengths, keys);

			vector<string> tuple;
			tuple.push_back("String 1");
			tuple.push_back("String 2");
			tuple.push_back("0");

			db.insert_into("Relation 1", tuple);

			vector<string> tuple2;
			tuple2.push_back("String 3");
			tuple2.push_back("String 4");
			tuple2.push_back("50");

			db.insert_into("Relation 1", tuple2);

			vector<string> tuple3;
			tuple3.push_back("String 5");
			tuple3.push_back("String 6");
			tuple3.push_back("100");

			db.insert_into("Relation 1", tuple3);

			db.create_relation("Relation 2", atts, atts_types, atts_lengths, keys);

			db.insert_into("Relation 2", tuple);

			vector<string> tuple4;
			tuple4.push_back("String 7");
			tuple4.push_back("String 8");
			tuple4.push_back("25");

			db.insert_into("Relation 2", tuple4);

			vector<string> tuple5;
			tuple5.push_back("String 9");
			tuple5.push_back("String 6");
			tuple5.push_back("100");

			db.insert_into("Relation 2", tuple5);

			// Test union
			Relation r(db.get_relation("Relation 1") + db.get_relation("Relation 2"));

			Assert::AreEqual(5, r.get_num_tuples());
			Assert::AreEqual(3, r.get_num_attributes());

		}

		TEST_METHOD(TestDBSetDifference){
			// Set up for Test
			Database db;

			vector<string> atts;
			atts.push_back("Attribute 1");
			atts.push_back("Attribute 2");
			atts.push_back("Attribute 3");

			vector<int> atts_types;
			atts_types.push_back(1);
			atts_types.push_back(1);
			atts_types.push_back(0);

			vector<int> atts_lengths;
			atts_lengths.push_back(20);
			atts_lengths.push_back(20);
			atts_lengths.push_back(0);

			vector<string> keys;
			keys.push_back("Attribute 1");
			keys.push_back("Attribute 3");

			db.create_relation("Relation 1", atts, atts_types, atts_lengths, keys);

			vector<string> tuple;
			tuple.push_back("String 1");
			tuple.push_back("String 2");
			tuple.push_back("0");

			db.insert_into("Relation 1", tuple);

			vector<string> tuple2;
			tuple2.push_back("String 3");
			tuple2.push_back("String 4");
			tuple2.push_back("50");

			db.insert_into("Relation 1", tuple2);

			vector<string> tuple3;
			tuple3.push_back("String 5");
			tuple3.push_back("String 6");
			tuple3.push_back("100");

			db.insert_into("Relation 1", tuple3);

			db.create_relation("Relation 2", atts, atts_types, atts_lengths, keys);

			db.insert_into("Relation 2", tuple);

			db.insert_into("Relation 2", tuple2);

			vector<string> tuple4;
			tuple4.push_back("String 7");
			tuple4.push_back("String 8");
			tuple4.push_back("25");

			db.insert_into("Relation 2", tuple4);

			vector<string> tuple5;
			tuple5.push_back("String 9");
			tuple5.push_back("String 6");
			tuple5.push_back("100");

			db.insert_into("Relation 2", tuple5);

			// Test difference
			Relation r(db.get_relation("Relation 1") - db.get_relation("Relation 2"));
			Relation r2(db.get_relation("Relation 2") - db.get_relation("Relation 1"));

			Assert::AreEqual(1, r.get_num_tuples());
			Assert::AreEqual(2, r2.get_num_tuples());

		}

		TEST_METHOD(TestDBProduct){
			// Set up for Test
			Database db;

			vector<string> atts;
			atts.push_back("Attribute 1");
			atts.push_back("Attribute 2");
			atts.push_back("Attribute 3");

			vector<int> atts_types;
			atts_types.push_back(1);
			atts_types.push_back(1);
			atts_types.push_back(0);

			vector<int> atts_lengths;
			atts_lengths.push_back(20);
			atts_lengths.push_back(20);
			atts_lengths.push_back(0);

			vector<string> keys;
			keys.push_back("Attribute 1");
			keys.push_back("Attribute 3");

			db.create_relation("Relation 1", atts, atts_types, atts_lengths, keys);

			vector<string> tuple;
			tuple.push_back("String 1");
			tuple.push_back("String 2");
			tuple.push_back("0");

			db.insert_into("Relation 1", tuple);

			vector<string> tuple2;
			tuple2.push_back("String 3");
			tuple2.push_back("String 4");
			tuple2.push_back("50");

			db.insert_into("Relation 1", tuple2);

			vector<string> tuple3;
			tuple3.push_back("String 5");
			tuple3.push_back("String 6");
			tuple3.push_back("100");

			db.insert_into("Relation 1", tuple3);

			vector<string> atts2;
			atts2.push_back("Attribute 4");
			atts2.push_back("Attribute 5");
			
			vector<int> atts_types2;
			atts_types2.push_back(1);
			atts_types2.push_back(0);

			vector<int> atts_lengths2;
			atts_lengths2.push_back(20);
			atts_lengths2.push_back(0);

			vector<string> keys2;
			keys2.push_back("Attribute 4");

			db.create_relation("Relation 2", atts2, atts_types2, atts_lengths2, keys2);

			vector<string> tuple4;
			tuple4.push_back("String 7");
			tuple4.push_back("5");

			db.insert_into("Relation 2", tuple4);

			vector<string> tuple5;
			tuple5.push_back("String 8");
			tuple5.push_back("13");

			db.insert_into("Relation 2", tuple5);

			//Test product
			Relation r(db.get_relation("Relation 1") * db.get_relation("Relation 2"));
			Relation r2(db.get_relation("Relation 2") * db.get_relation("Relation 1"));

			Assert::AreEqual(5, r.get_num_attributes());
			Assert::AreEqual(6, r.get_num_tuples());
			Assert::AreEqual(5, r2.get_num_attributes());
			Assert::AreEqual(6, r2.get_num_tuples());
			Assert::AreEqual("Attribute 1", r.get_attributes()[0].c_str());
			Assert::AreEqual("Attribute 4", r2.get_attributes()[0].c_str());
		}

		TEST_METHOD(TestDBJoin){
			// Set up for Test
			Database db;

			vector<string> atts;
			atts.push_back("Attribute 1");
			atts.push_back("Attribute 2");
			atts.push_back("Attribute 3");

			vector<int> atts_types;
			atts_types.push_back(1);
			atts_types.push_back(1);
			atts_types.push_back(0);

			vector<int> atts_lengths;
			atts_lengths.push_back(20);
			atts_lengths.push_back(20);
			atts_lengths.push_back(0);

			vector<string> keys;
			keys.push_back("Attribute 2");
			keys.push_back("Attribute 3");

			db.create_relation("Relation 1", atts, atts_types, atts_lengths, keys);

			vector<string> tuple;
			tuple.push_back("String 1");
			tuple.push_back("String 2");
			tuple.push_back("0");

			db.insert_into("Relation 1", tuple);

			vector<string> tuple2;
			tuple2.push_back("String 3");
			tuple2.push_back("String 4");
			tuple2.push_back("50");

			db.insert_into("Relation 1", tuple2);

			vector<string> tuple3;
			tuple3.push_back("String 1");
			tuple3.push_back("String 6");
			tuple3.push_back("100");

			db.insert_into("Relation 1", tuple3);

			vector<string> atts2;
			atts2.push_back("Attribute 1");
			atts2.push_back("Attribute 4");

			vector<int> atts_types2;
			atts_types2.push_back(1);
			atts_types2.push_back(0);

			vector<int> atts_lengths2;
			atts_lengths2.push_back(20);
			atts_lengths2.push_back(0);

			vector<string> keys2;
			keys2.push_back("Attribute 4");

			db.create_relation("Relation 2", atts2, atts_types2, atts_lengths2, keys2);

			vector<string> tuple4;
			tuple4.push_back("String 1");
			tuple4.push_back("5");

			db.insert_into("Relation 2", tuple4);

			vector<string> tuple5;
			tuple5.push_back("String 7");
			tuple5.push_back("13");

			db.insert_into("Relation 2", tuple5);

			//Test natural join
			Relation r(db.join(db.get_relation("Relation 1"), db.get_relation("Relation 2")));

			Assert::AreEqual(4, r.get_num_attributes());
			Assert::AreEqual(2, r.get_num_tuples());
		}

	};
}