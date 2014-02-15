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
		// checks for the CREATE command
		if(tokens[0].compare("CREATE") == 0){
			// checks for the TABLE command
			if(tokens[1].compare("TABLE") == 0){
				// check for the total size of tokens
				if(tokens.size() >= 12){
					// compares if the 4th token is (
					if(tokens[3].compare("(") == 0){
						// initializing i to 4
						int i = 4;
						// declaring vector of ints for relation name, and keys
						vector<string> temp_name, temp_keys;
						//declaring vector of ints for attribute type and attribute length
						vector<int> temp_type, temp_len;
						// while loop checks for the token )
						while(tokens[i]!= ")"){
							// checks for the token ,
							if(tokens[i] != ","){
								// relation name been pushed to temp_name
								temp_name.push_back(tokens[i]);
								i++;
								// checks if token is VARCHAR
								if(tokens[i].compare("VARCHAR") == 0)
									// 1 (string) is been push to attribute type (temp_type)
									temp_type.push_back(1);
								// checks if token is INTEGER
								else if(tokens[i].compare("INTEGER") == 0){
									// 0 is been push to attribute length (temp_len)
									temp_len.push_back(0);
									// 0 (int) is been push to attribute type (temp_type)
									temp_type.push_back(0);
								}
								// checks if token is (
								if(tokens[i+1] =="("){
									i+=2;
									// attribute length is push to temp_len
									temp_len.push_back(stoi(tokens[i]));
									i+=2;
								}
								else
									i+=1;
							}
							// checks if token is )
							if(tokens[i]!= ")")
								i++;
						}
						i+=4;
						// checks if token is not )
						while(tokens[i] !=  ")"){
							// checks if token is not ,
							if(tokens[i] != ","){
								//push back a keys into temp_keys
								temp_keys.push_back(tokens[i]);
							}
							i++;
						}
						// pushing relation name, attribute names, attribute types, attribute length, attribute keys to the database
						db.create_relation(tokens[2],temp_name,temp_type,temp_len,temp_keys);
					}
					else {
						throw RuntimeException("Expected token \"(\".");
					}
					Relation temp(tokens[2]);
				}
				else{
					throw RuntimeException("Command does not have enough arguments.");
				}
			}
			else{
				throw RuntimeException("Command not recognized.");
			}
		}
		// Checks for the command INSERT
		else if(tokens[0].compare("INSERT") == 0){
			//checks for the token size
			if(tokens.size() >  6){
			// Checks if the second token is INTO
				if(tokens[1].compare("INTO") == 0){ 
					// checks if the fourth token is VALUES
					if(tokens[3].compare("VALUES") == 0){ 
						// checks if the fifth token is FROM
						if(tokens[4].compare("FROM") == 0){
							// checks if the sixth token is (
							if(tokens[5].compare("(") == 0){ 
								int i = 6;						
								vector<string> tup_list;
								// while loops runs until it find ) token
								while(tokens[i] !=  ")"){
									// checks if token is not ,
									if(tokens[i] != ","){
										//push back a cell into tup_list
										tup_list.push_back(tokens[i]);
									}
									i++;
								}
								// inserting into the database
								db.insert_into(tokens[2], tup_list);
							}
						}
					}
				}
			}
		}
		// checks if the command is SHOW
		else if(tokens[0].compare("SHOW") == 0){
			// checks if the token size is 2
			if(tokens.size() == 2)
				// prints the relation on console
				cout << db.get_relation(tokens[1]);
			else
				throw RuntimeException("Invalid Query.");
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