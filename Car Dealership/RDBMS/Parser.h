#pragma once

#include <vector>
#include <string>
#include "Database.h"

using namespace std;

/* Delimiter and tokens */

// All delimiters
static const string db_parser_delimiters = " =|<>!*+-,()\";";
// Delimiters that should be treated as tokens
static const string db_parser_tokens = "=|<>!*+-,()\"";
// Characters that could be the second part of a delimiter token
static const string db_parser_double_tokens = "=-";

/* Declaration of the Parser Class */

class Parser
{
	// The database to perform operations on
	Database db;
	// A control flag for exiting the parser commandline
	bool exit;
public:
	// The default constructor
	Parser();
	// A command line like loop to take in commands
	void parser_commandline();
	// Input a command and it will parse the command and perform the correct action
	void parse_command(string command);
	// Takes a tokenized command and actually does the parsing
	void parse(vector<string> tokens);
	// Tokenizes a command into tokens. Pass a reference to the vector that you want the tokens to be stored in.
	void tokenize(string command, vector<string> * tokens);
	// Checks to see if a character is a delimiter.
	bool is_delimiter(char c);
	// Checks to see if a character is token
	bool is_token(char c);
	// Checks to see if a character is part of a double token
	bool Parser::is_double_token(char c);
	// Uses the Db to evaluate an atomic expressions tokens
	Relation evalutate_atomic_expression(vector<string> atomic_exp);
	// Create Condition from tokens
	Condition create_condition(vector<string> condition_exp);
};

/* End of the Parser Class */


