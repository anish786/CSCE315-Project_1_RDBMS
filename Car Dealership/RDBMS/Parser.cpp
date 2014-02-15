#include <cstdlib>
#include "Parser.h"

using namespace std;

Parser::Parser(){
	exit = false;
}


// A command line like loop to take in commands
void Parser::parser_commandline(){
	while(!exit){
		cout << "::";
		string command;
		getline(cin, command);
		try{
			parse_command(command);
		}
		catch(RuntimeException r){
			cout << r.getMessage() << endl;
		}
	}
}

// Input a command and it will parse the command and perform the correct action
void Parser::parse_command(string command){
	vector<string> tokens;
	tokenize(command, &tokens);
	parse(tokens);
}


// Takes a tokenized command and actually does the parsing
void Parser::parse(vector<string> tokens){
	if(tokens.size() >= 2){
		if(tokens[0].compare("CREATE") == 0){

		}
		else if(tokens[0].compare("INSERT") == 0){
			if(tokens[1].compare("INTO") == 0){
				if(tokens[3].compare("VALUES") == 0){
					if(tokens[4].compare("FROM") == 0){
						if(tokens[5].compare("(") == 0){
							int i = 6;
							vector<string> tup_list;
							while(tokens[i] !=  ")"){
								if(tokens[i] != ",")
									tup_list.push_back(tokens[i]);
								i++;
							}
							db.insert_into(tokens[2], tup_list);
						}
					}
				}
			}
		}
		else if(tokens[0].compare("SHOW") == 0){

		}
		else if(tokens[0].compare("DELETE") == 0){

		}
		else if(tokens[0].compare("UPDATE") == 0){

		}
		else if(tokens[1].compare("<-") == 0){

		}
		else if(tokens[0].compare("OPEN") == 0){

		}
		else if(tokens[0].compare("CLOSE") == 0){

		}
		else if(tokens[0].compare("WRITE") == 0){

		}
		else{
			cout << "Command or Query not recognized." << endl;
		}
	}
	else if(tokens.size() >= 1 && tokens[0].compare("EXIT") == 0){
		exit = true;
	}
	else{
		cout << "Command or Query not recognized." << endl;
	}
}


// Tokenizes a command into tokens. Pass a reference to the vector that you want the tokens to be stored in.
void Parser::tokenize(string command, vector<string> * tokens){
	// Current token parsed
	string token = "";
	// Go throught each caracter in the command
	for (size_t position = 0; position < command.size(); position++){
		// Check if the character is a delimiter
		if (is_delimiter(command[position])){
			// Push back the current token if it exist
			if (token.size() > 0){
				tokens->push_back(token);
			}
			// Check to see if the delimiter is also a valid token
			if (is_token(command[position])){
				// Clear token and add the delimiter to the token
				token = "";
				token = token + command[position];
				// Check if the next character is a part of the same token
				if (position < command.size() - 1 && is_double_token(command[position+1])){
					position++;
					token = token + command[position];
				}
				// Push back the token that was a delimiter
				tokens->push_back(token);
			}
			// Clear the token
			token = "";
		}
		else{
			// Was not a delimiter to just add the character to the current token
			token = token + command[position];
		}
	}
	if(token.size() > 0){
		// Check to see if there is a token at the end of the command
		tokens->push_back(token);
	}

	//combine tokens that are strings ex. "Hello World" into a single token
	for (size_t i = 0; i < tokens->size(); i++){
		if (tokens->at(i).compare("\"") == 0){
			size_t j = i + 1;
			while (j < tokens->size() && tokens->at(j).compare("\"") != 0){
				j++;
			}

			// Create string for combined token
			string combined = tokens->at(i+1);
			for (size_t middle = i + 2; middle < j; middle++){
				combined = combined + " " + tokens->at(middle);
			}
			// Remove old tokens
			tokens->erase(tokens->begin()+i, tokens->begin()+j+1);
			// Instert combined token
			tokens->insert(tokens->begin()+i, combined);
		}
	}
}

// Checks to see if a character is a delimiter.
bool Parser::is_delimiter(char c)
{
	return db_parser_delimiters.find(c) >= 0 && db_parser_delimiters.find(c) < db_parser_delimiters.size();
}


// // Checks to see if a character is token
bool Parser::is_token(char c)
{
	return db_parser_tokens.find(c) >= 0 && db_parser_tokens.find(c) < db_parser_tokens.size();
}

// // Checks to see if a character is part of a double token
bool Parser::is_double_token(char c)
{
	return db_parser_double_tokens.find(c) >= 0 && db_parser_double_tokens.find(c) < db_parser_double_tokens.size();
}

// Uses the Db to evaluate an atomic expressions tokens
Relation Parser::evalutate_atomic_expression(vector<string> atomic_expr){
	if (atomic_expr.size() == 1){
		return db.get_relation(atomic_expr[0]);
	}
	else if (atomic_expr[0].compare("select") == 0){
		vector<string> condition;
		Condition cond(create_condition(condition));
		vector<string> next_atomic_expr;

		return db.select(cond, evalutate_atomic_expression(next_atomic_expr));
	}
	else if (atomic_expr[0].compare("project") == 0){
		vector<string> att_list;
		vector<string> next_atomic_expr;

		return db.project(att_list, evalutate_atomic_expression(next_atomic_expr));
	}
	else if (atomic_expr[0].compare("rename") == 0){
		vector<string> att_list;
		vector<string> next_atomic_expr;

		return db.rename(att_list, evalutate_atomic_expression(next_atomic_expr));
	}

	string atomic_operation;

	if (atomic_operation.compare("+") == 0){
		vector<string> first_atomic;
		vector<string> second_atomic;
		
		return evalutate_atomic_expression(first_atomic) + evalutate_atomic_expression(second_atomic);
	}
	else if (atomic_operation.compare("-") == 0){
		vector<string> first_atomic;
		vector<string> second_atomic;

		return evalutate_atomic_expression(first_atomic) + evalutate_atomic_expression(second_atomic);
	}
	else if (atomic_operation.compare("*") == 0){
		vector<string> first_atomic;
		vector<string> second_atomic;

		return evalutate_atomic_expression(first_atomic) + evalutate_atomic_expression(second_atomic);
	}
	else if (atomic_operation.compare("JOIN") == 0){
		vector<string> first_atomic;
		vector<string> second_atomic;

		return evalutate_atomic_expression(first_atomic) + evalutate_atomic_expression(second_atomic);
	}
	else{
		throw RuntimeException("Could not evaluate atomic expression");
	}
}

// Create Condition from tokens
Condition Parser::create_condition(vector<string> condition_exp){

	//TODO: make this actually do something
	vector<Conjunction> temp;
	Condition c(temp);
	return c;
}