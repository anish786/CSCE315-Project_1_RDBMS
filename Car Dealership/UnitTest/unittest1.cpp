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
			condition_exp.push_back("x1");
			condition_exp.push_back("==");
			condition_exp.push_back("x2");
			condition_exp.push_back("||");
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