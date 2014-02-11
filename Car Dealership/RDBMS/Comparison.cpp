#include "Comparison.h"
#include <sstream>

Comparison::Comparison(string o1, string o2, string o){
	operand1 = o1;
	operand2 = o2;
	op = o;
}

Comparison::~Comparison(void){

}

int string_to_int(string s){
	stringstream ss(s);
	int i;
	ss >> i;
	return i;
}

bool Comparison::evaluate(vector<string> variables, vector<string> values){
	for(size_t i = 0; i < variables.size(); i++){
		if(operand1.compare(variables[i]) == 0){
			operand1 = values[i];
		}
		if(operand2.compare(variables[i]) == 0){
			operand2 = values[i];
		}
	}
	if(op.compare("==") == 0){
		if(operand1.compare(operand2) == 0){
			return true;
		}
	}
	else if(op.compare("!=") == 0){
		if(operand1.compare(operand2) != 0){
			return true;
		}
	}
	else if(op.compare("<") == 0){
		if(string_to_int(operand1) < string_to_int(operand2)){
			return true;
		}
	}
	else if(op.compare(">") == 0){
		if(string_to_int(operand1) > string_to_int(operand2)){
			return true;
		}
	}
	else if(op.compare("<=") == 0){
		if(string_to_int(operand1) <= string_to_int(operand2)){
			return true;
		}
	}
	else if(op.compare(">=") == 0){
		if(string_to_int(operand1) >= string_to_int(operand2)){
			return true;
		}
	}
	return false;
}
