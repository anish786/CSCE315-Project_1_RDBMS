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
		parse_command(command);
	}
}

// Input a command and it will parse the command and perform the correct action
void Parser::parse_command(string command){
	vector<string> tokens;
	tokenize(command, &tokens);
	try{
		parse(tokens);
	}
	catch (RuntimeException r){
		cout << r.getMessage() << endl;
	}
}

// Input a command and it will parse the command and perform the correct action
// This version does not catch exceptions
void Parser::parse_command_self_check(string command){
	vector<string> tokens;
	tokenize(command, &tokens);
	parse(tokens);
}

// Takes a tokenized command and actually does the parsing
void Parser::parse(vector<string> tokens){
	if(tokens.size() >= 2){
		// checks for the CREATE command
		if(tokens[0].compare("CREATE") == 0){
			parse_create(tokens);
		}
		// Checks for the command INSERT
		else if(tokens[0].compare("INSERT") == 0){
			parse_insert(tokens);
		}
		// checks if the command is SHOW
		else if(tokens[0].compare("SHOW") == 0){
			parse_show(tokens);
		}
		// checks if the command is DELETE
		else if(tokens[0].compare("DELETE") == 0){
			parse_delete(tokens);
		}
		// checks if the command is UPDATE
		else if(tokens[0].compare("UPDATE") == 0){
			parse_update(tokens);
		}
		// checks if the command is a query
		else if(tokens[1].compare("<-") == 0){
			parse_query(tokens);
		}
		// checks if the command is OPEN
		else if(tokens[0].compare("OPEN") == 0){
			parse_open(tokens);
		}
		// checks if the command is CLOSE
		else if(tokens[0].compare("CLOSE") == 0){
			parse_close(tokens);
		}
		// checks if the command is WRITE
		else if(tokens[0].compare("WRITE") == 0){
			parse_write(tokens);
		}
		else{
			throw RuntimeException("Command or Query not recognized.");
		}
	}
	else if(tokens.size() == 1 && tokens[0].compare("EXIT") == 0){
		exit = true;
	}
	else{
		throw RuntimeException("Command or Query not recognized.");
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
				if (position < command.size() - 1 && is_double_token(command[position+1]) && is_first_double_token(command[position])){
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

// Checks to see if a character is the first part of a double token
bool Parser::is_first_double_token(char c){
	return db_first_parser_double_tokens.find(c) >= 0 && db_first_parser_double_tokens.find(c) < db_first_parser_double_tokens.size();
}

// // Checks to see if a character is part of a double token
bool Parser::is_double_token(char c)
{
	return db_parser_double_tokens.find(c) >= 0 && db_parser_double_tokens.find(c) < db_parser_double_tokens.size();
}

// Uses the Db to evaluate an atomic expressions tokens
Relation Parser::evalutate_atomic_expression(vector<string> atomic_expr){
	if (atomic_expr.size() >= 3 && atomic_expr[0].compare("(") == 0) {
		int pos = 1;
		int open_count = 0;
		bool in_parentheses = false;
		while (pos < (int)atomic_expr.size() && atomic_expr[pos].compare(")") != 0 || open_count != 0 ){
			if (atomic_expr[pos].compare("(") == 0){
				open_count++;
			}
			if (atomic_expr[pos].compare(")") == 0){
				open_count--;
			}
			pos++;
		}
		if (pos == (int)atomic_expr.size() - 1){
			in_parentheses = true;
		}
		if (in_parentheses){
			atomic_expr = vector<string>(atomic_expr.begin()+1, atomic_expr.end()-1);
		}
	}

	if (atomic_expr.size() == 1){
		return db.get_relation(atomic_expr[0]);
	}
	else if ((int)atomic_expr.size() > 1 && atomic_expr[0].compare("select") == 0){
		int begin = 1;
		if (begin >= (int)atomic_expr.size() || atomic_expr[begin] != "("){
			throw RuntimeException("Expected token (");
		}

		int end = 2;
		if (end >= (int)atomic_expr.size()){
			throw RuntimeException("Expected token condition");
		}

		int open_par = 0;
		while (end < (int)atomic_expr.size() - 1 && (atomic_expr[end].compare(")") != 0 || open_par != 0)){
			if (atomic_expr[end].compare("(") == 0){
				open_par++;
			}
			if (atomic_expr[end].compare(")") == 0){
				open_par--;
			}
			end++;
		}
		vector<string> condition(atomic_expr.begin() + begin + 1, atomic_expr.begin() + end);
		Condition cond(create_condition(condition));

		begin = end + 1;
		int end_par = 0;
		if (atomic_expr[begin].compare("(") == 0){
			begin++;
			end_par = 1;
		}
		vector<string> next_atomic_expr(atomic_expr.begin()+begin, atomic_expr.end()-end_par);

		return db.select(cond, evalutate_atomic_expression(next_atomic_expr));
	}
	else if ((int)atomic_expr.size() > 1 && atomic_expr[0].compare("project") == 0){
		int begin = 1;
		if (begin >= (int)atomic_expr.size() || atomic_expr[begin] != "("){
			throw RuntimeException("Expected token (");
		}

		int end = 2;
		int open_par = 0;
		while (end < (int)atomic_expr.size() - 1 && (atomic_expr[end].compare(")") != 0 || open_par != 0)){
			if (atomic_expr[end].compare("(") == 0){
				open_par++;
			}
			if (atomic_expr[end].compare(")") == 0){
				open_par--;
			}
			end++;
		}
		vector<string> att_list(atomic_expr.begin() + begin + 1, atomic_expr.begin() + end);

		for (size_t i = 0; i < att_list.size(); i++){
			if (att_list[i].compare(",") == 0){
				att_list.erase(att_list.begin()+i);
				i--;
			}
		}

		begin = end + 1;
		int end_par = 0;
		if (atomic_expr[begin].compare("(") == 0){
			begin++;
			end_par = 1;
		}
		vector<string> next_atomic_expr(atomic_expr.begin() + begin, atomic_expr.end() - end_par);

		return db.project(att_list, evalutate_atomic_expression(next_atomic_expr));
	}
	else if ((int)atomic_expr.size() > 1 && atomic_expr[0].compare("rename") == 0){
		int begin = 1;
		if (begin >= (int)atomic_expr.size() || atomic_expr[begin] != "("){
			throw RuntimeException("Expected token (");
		}

		int end = 2;
		int open_par = 0;
		while (end < (int)atomic_expr.size() - 1 && (atomic_expr[end].compare(")") != 0 || open_par != 0)){
			if (atomic_expr[end].compare("(") == 0){
				open_par++;
			}
			if (atomic_expr[end].compare(")") == 0){
				open_par--;
			}
			end++;
		}
		vector<string> att_list(atomic_expr.begin() + begin + 1, atomic_expr.begin() + end);

		for (size_t i = 0; i < att_list.size(); i++){
			if (att_list[i].compare(",") == 0){
				att_list.erase(att_list.begin() + i);
				i--;
			}
		}

		begin = end + 1;
		int end_par = 0;
		if (atomic_expr[begin].compare("(") == 0){
			begin++;
			end_par = 1;
		}
		vector<string> next_atomic_expr(atomic_expr.begin() + begin, atomic_expr.end() - end_par);

		return db.rename(att_list, evalutate_atomic_expression(next_atomic_expr));
	}
	
	int operation_loc = 0;
	if ((int)atomic_expr.size() > 1 && atomic_expr[0].compare("(") == 0){
		operation_loc++;
		int open_par = 0;
		while (operation_loc < (int)atomic_expr.size() - 1 && (atomic_expr[operation_loc].compare(")") != 0 || open_par != 0)){
			if (atomic_expr[operation_loc].compare("(") == 0){
				open_par++;
			}
			if (atomic_expr[operation_loc].compare(")") == 0){
				open_par--;
			}
			operation_loc++;
		}
		if (atomic_expr[operation_loc].compare(")") != 0){
			throw RuntimeException("Expected closing ) token");
		}
	}

	operation_loc++;
	if (operation_loc >= (int)atomic_expr.size()){
		throw RuntimeException("Expected operator token for atomic expresion");
	}
	string atomic_operation = atomic_expr[operation_loc];
	int parentheses = 0;
	if (atomic_expr[0].compare("(") == 0){
		parentheses = 1;
	}
	vector<string> first_atomic(atomic_expr.begin() + parentheses, atomic_expr.begin() + operation_loc - parentheses);
	parentheses = 0;
	if (atomic_expr[operation_loc + 1].compare("(") == 0){
		parentheses = 1;
	}
	vector<string> second_atomic(atomic_expr.begin() + operation_loc + 1 + parentheses, atomic_expr.end() - parentheses);

	if (atomic_operation.compare("+") == 0){
		return evalutate_atomic_expression(first_atomic) + evalutate_atomic_expression(second_atomic);
	}
	else if (atomic_operation.compare("-") == 0){
		return evalutate_atomic_expression(first_atomic) - evalutate_atomic_expression(second_atomic);
	}
	else if (atomic_operation.compare("*") == 0){
		return evalutate_atomic_expression(first_atomic) * evalutate_atomic_expression(second_atomic);
	}
	else if (atomic_operation.compare("JOIN") == 0){
		Relation r("JOIN");
		r.natural_join(evalutate_atomic_expression(first_atomic), evalutate_atomic_expression(second_atomic));
		return r;
	}
	else{
		throw RuntimeException("Could not evaluate atomic expression");
	}
}

// Create Condition from tokens
Condition Parser::create_condition(vector<string> condition_exp){
	vector<Conjunction> conjs;
	int start = 0;
	size_t end;
	for (end = 0; end < condition_exp.size(); end++){
		if (condition_exp[end].compare("||") == 0){
			int end_par = 0;
			if (condition_exp[start].compare("(") == 0){
				start++;
				end_par = 1;
			}
			vector<string> conjunction(condition_exp.begin() + start, condition_exp.begin() + end-end_par);
			conjs.push_back(create_conjunction(conjunction));
			start = end + 1;
		}
		if (condition_exp[end].compare("(") == 0){
			end++;
			int open_par = 0;
			while (end < condition_exp.size()-1 && (condition_exp[end].compare(")") != 0 || open_par != 0)){
				if (condition_exp[end].compare("(") == 0){
					open_par++;
				}
				if (condition_exp[end].compare(")") == 0){
					open_par--;
				}
				end++;
			}
			if (condition_exp[end].compare(")") != 0){
				throw RuntimeException("Expected closing ) token");
			}
		}
	}
	int end_par = 0;
	if (condition_exp[start].compare("(") == 0){
		start++;
		end_par = 1;
	}
	vector<string> conjunction(condition_exp.begin() + start, condition_exp.begin() + end - end_par);
	conjs.push_back(create_conjunction(conjunction));
	return Condition(conjs);
}

// Create Conjunction from tokens
Conjunction Parser::create_conjunction(vector<string> conj_exp){
	vector<Comparison> comps;
	int start = 0;
	size_t end;
	for (end = 0; end < conj_exp.size(); end++){
		if (conj_exp[end].compare("&&") == 0){
			int end_par = 0;
			if (conj_exp[start].compare("(") == 0){
				start++;
				end_par = 1;
			}
			vector<string> comparison(conj_exp.begin() + start, conj_exp.begin() + end - end_par);
			comps.push_back(create_comparison(comparison));
			start = end + 1;
		}
		if (conj_exp[end].compare("(") == 0){
			end++;
			int open_par = 0;
			while (end < conj_exp.size() - 1 && (conj_exp[end].compare(")") != 0 || open_par != 0)){
				if (conj_exp[end].compare("(") == 0){
					open_par++;
				}
				if (conj_exp[end].compare(")") == 0){
					open_par--;
				}
				end++;
			}
			if (conj_exp[end].compare(")") != 0){
				throw RuntimeException("Expected closing ) token");
			}
		}
	}
	int end_par = 0;
	if (conj_exp[start].compare("(") == 0){
		start++;
		end_par = 1;
	}
	vector<string> comparison(conj_exp.begin() + start, conj_exp.begin() + end - end_par);
	comps.push_back(create_comparison(comparison));
	return Conjunction(comps);
}

// Create Comparison from tokens
Comparison Parser::create_comparison(vector<string> comp_exp){
	if (comp_exp.size() == 3){
		Comparison temp(comp_exp[0], comp_exp[2], comp_exp[1]);
		return temp;
	}
	else{
		Comparison temp(create_condition(comp_exp));
		return temp;
	}
}

// Parse the create command
void Parser::parse_create(vector<string> tokens){
	// checks for the TABLE command
	if (tokens.size() >= 5 && tokens[1].compare("TABLE") == 0){
		// compares if the 4th token is (
		if (tokens[3].compare("(") == 0){
			// initializing i to 4
			int i = 4;
			// declaring vector of ints for relation name, and keys
			vector<string> temp_name, temp_keys;
			//declaring vector of ints for attribute type and attribute length
			vector<int> temp_type, temp_len;
			// while loop checks for the token )
			while (tokens[i] != ")"){
				// checks for the token ,
				if (tokens[i] != ","){
					// relation name been pushed to temp_name
					temp_name.push_back(tokens[i]);
					//Increment position
					i++;
					// checks if token is VARCHAR
					if (i < (int)tokens.size() && tokens[i].compare("VARCHAR") == 0){
						// 1 (string) is been push to attribute type (temp_type)
						temp_type.push_back(1);
						//Increment position
						i++;
						// checks if token is (
						if (i < (int)tokens.size() && tokens[i] == "("){
							//Increment position and check for still in token bounds
							i++;
							if (i >= (int)tokens.size()){
								throw RuntimeException("Expected token size");
							}
							// attribute length is push to temp_len
							temp_len.push_back(string_to_int(tokens[i]));
							//Increment position and check for still in token bounds
							i++;
							if (i >= (int)tokens.size() || tokens[i] != ")"){
								throw RuntimeException("Expected token )");
							}
						}
						else{
							throw RuntimeException("Expected token (");
						}
					}
					// checks if token is INTEGER
					else if (i < (int)tokens.size() && tokens[i].compare("INTEGER") == 0){
						// 0 is been push to attribute length (temp_len)
						temp_len.push_back(0);
						// 0 (int) is been push to attribute type (temp_type)
						temp_type.push_back(0);
					}
					else{
						throw RuntimeException("Expected token VARCHAR or INTEGER");
					}
				}
				i++;
				if (i >= (int)tokens.size()){
					throw RuntimeException("Expected more tokens");
				}
			}
			i++;
			if (i >= (int)tokens.size() || tokens[i].compare("PRIMARY") != 0){
				throw RuntimeException("Expected token PRIMARY");
			}
			i++;
			if (i >= (int)tokens.size() || tokens[i].compare("KEY") != 0){
				throw RuntimeException("Expected token KEY");
			}
			i++;
			if (i >= (int)tokens.size() || tokens[i].compare("(") != 0){
				throw RuntimeException("Expected token (");
			}
			i++;
			if (i >= (int)tokens.size()){
				throw RuntimeException("Expected token key-name");
			}
			// checks if token is not )
			while (tokens[i] != ")"){
				// checks if token is not ,
				if (tokens[i] != ","){
					//push back a keys into temp_keys
					temp_keys.push_back(tokens[i]);
				}
				i++;
				if (i >= (int)tokens.size()){
					throw RuntimeException("Expected more tokens");
				}
			}
			// pushing relation name, attribute names, attribute types, attribute length, attribute keys to the database
			db.create_relation(tokens[2], temp_name, temp_type, temp_len, temp_keys);
		}
		else {
			throw RuntimeException("Expected token \"(\".");
		}
	}
	else{
		throw RuntimeException("Incorrect format for CREATE TABLE command");
	}
}

// Parse the insert commands
void Parser::parse_insert(vector<string> tokens){
	//checks for the token size
	if (tokens.size() >  7){
		// Checks if the second token is INTO
		if (tokens[1].compare("INTO") == 0){
			// checks if the fourth token is VALUES
			if (tokens[3].compare("VALUES") == 0){
				// checks if the fifth token is FROM
				if (tokens[4].compare("FROM") == 0){
					// checks if the sixth token is (
					if (tokens[5].compare("(") == 0){
						int i = 6;
						vector<string> tup_list;
						// while loops runs until it find ) token
						while (tokens[i] != ")"){
							// checks if token is not ,
							if (tokens[i] != ","){
								if (tokens[i] == "-"){
									i++;
									if (i >= (int)tokens.size()){
										throw RuntimeException("Expected token int");
									}
									tup_list.push_back(tokens[i-1]+tokens[i]);
								}
								else{
									//push back a cell into tup_list
									tup_list.push_back(tokens[i]);
								}
							}
							i++;
							if (i >= (int)tokens.size()){
								throw RuntimeException("Expected more tokens");
							}
						}
						// inserting into the database
						db.insert_into(tokens[2], tup_list);
					}
					else if (tokens[5].compare("RELATION") == 0){
						vector<string> atomic_expression(tokens.begin()+6, tokens.end());
						Relation r(evalutate_atomic_expression(atomic_expression));
						db.insert_into(tokens[2], r);
					}
					else{
						throw RuntimeException("Expected token ( or RELATION");
					}
				}
				else{
					throw RuntimeException("Expected token FROM");
				}
			}
			else{
				throw RuntimeException("Expected token VALUES");
			}
		}
		else{
			throw RuntimeException("Expected token INTO");
		}
	}
	else{
		throw RuntimeException("Expected more tokens");
	}
}

// Parse the show command
void Parser::parse_show(vector<string> tokens){
	// checks if the token size is 2
	if (tokens.size() >= 2)
		// prints the relation on console
		cout << evalutate_atomic_expression(vector<string>(tokens.begin()+1, tokens.end()));
	else
		throw RuntimeException("Invalid Query.");
}

// Parse the delete command
void Parser::parse_delete(vector<string> tokens){
	int i = 1;
	if (i >= (int)tokens.size() || tokens[i].compare("FROM") != 0){
		throw RuntimeException("Expected token FROM");
	}
	i++;
	if (i >= (int)tokens.size()){
		throw RuntimeException("Expected token relation-name.");
	}
	string relation_name = tokens[i];

	i++;
	if (i >= (int)tokens.size() || tokens[i].compare("WHERE") != 0){
		throw RuntimeException("Expected token WHERE");
	}

	i++;
	if (i >= (int)tokens.size()){
		throw RuntimeException("Expected token condition");
	}
	vector<string> condition(tokens.begin() + i, tokens.end());
	Condition cond(create_condition(condition));

	db.delete_from(relation_name, cond);
}

// Parse the update command
void Parser::parse_update(vector<string> tokens){
	int i = 1;
	if (i >= (int)tokens.size()){
		throw RuntimeException("Expected token relation-name.");
	}
	string relation_name = tokens[i];

	i++;
	if (i >= (int)tokens.size() || tokens[i].compare("SET") != 0){
		throw RuntimeException("Expected token SET");
	}

	i++;
	if (i >= (int)tokens.size()){
		throw RuntimeException("Expected token attribute-name.");
	}

	vector<string> attribute_name;
	vector<string> update_value;

	while (tokens[i].compare("WHERE") != 0){
		attribute_name.push_back(tokens[i]);
		i++;
		if (i >= (int)tokens.size() || tokens[i].compare("=") != 0){
			throw RuntimeException("Expected token =");
		}
		i++;
		if (i >= (int)tokens.size()){
			throw RuntimeException("Expected token literal.");
		}
		update_value.push_back(tokens[i]);
		i++;
		if (i >= (int)tokens.size() || (tokens[i].compare(",") != 0 && tokens[i].compare("WHERE") != 0)){
			throw RuntimeException("Expected token , or WHERE.");
		}
		if (tokens[i].compare(",") == 0){
			i++;
			if (i >= (int)tokens.size()){
				throw RuntimeException("Expected more tokens");
			}
		}
	}

	i++;
	if (i >= (int)tokens.size()){
		throw RuntimeException("Expected token condition");
	}
	vector<string> condition(tokens.begin()+i, tokens.end());
	Condition cond(create_condition(condition));

	db.update(relation_name, attribute_name, update_value, cond);
}

// Parse queries
void Parser::parse_query(vector<string> tokens){
	vector<string> atomic_expression;
	if (tokens.size() >= 3){
		atomic_expression.insert(atomic_expression.begin(), tokens.begin() + 2, tokens.end());
		Relation temp(evalutate_atomic_expression(atomic_expression));
		temp.rename_relation(tokens[0]);
		db.add_relation(temp);
	}
	else {
		throw RuntimeException("Query does not have enough arguments.");
	}
}

// Parse the open command
void Parser::parse_open(vector<string> tokens){
	if (tokens.size() == 2){
		Relation r (tokens[1]);
		
		ifstream db_file;
		string db_filename = tokens[1] + ".db";

		db_file.open(db_filename);
		if (db_file.is_open()){
			string command;
			while (!db_file.eof()){
				getline(db_file, command);
				if (command.size() > 0){
					parse_command(command);
				}
			}
		}
		else{
			throw RuntimeException("Could not open " + db_filename +  " file.");
		}
	}
	else{
		throw RuntimeException("Invalid command usage.");
	}
}

// Parse the close command
void Parser::parse_close(vector<string> tokens){
	if (tokens.size() == 2){
		db.write_relation(tokens[1]);
		exit = true;
	}
	else{
		throw RuntimeException("Invalid command usage.");
	}
}

// Parse the write command
void Parser::parse_write(vector<string> tokens){
	if (tokens.size() == 2){
		db.write_relation(tokens[1]);
	}
	else{
		throw RuntimeException("Invalid command usage.");
	}
}

// Retruns a copy of the database
Database Parser::get_database(){
	return db;
}
