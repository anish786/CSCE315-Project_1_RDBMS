#include "stdafx.h"
#include "CppUnitTest.h"

#include "Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestDilimiterAndTokenChecks)
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

		TEST_METHOD(TestTokenizer)
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
	};
}