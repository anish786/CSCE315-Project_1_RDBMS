#include "Comparison.h"

int string_to_int(string s){
	stringstream ss(s);
	int i;
	ss >> i;
	return i;
}

Comparison::Comparison(string o1, string o2, string o){
	operand1 = o1;
	operand2 = o2;
	op = o;
}

Comparison::~Comparison(void){

}

bool Comparison::evaluate(vector<string> variables, vector<string> values){
	string eval_operand1 = operand1;
	string eval_operand2 = operand2;
	for(size_t i = 0; i < variables.size(); i++){
		if(operand1.compare(variables[i]) == 0){
			eval_operand1 = values[i];
		}
		if(operand2.compare(variables[i]) == 0){
			eval_operand2 = values[i];
		}
	}
	if(op.compare("==") == 0){
		if (eval_operand1.compare(eval_operand2) == 0){
			return true;
		}
	}
	else if(op.compare("!=") == 0){
		if (eval_operand1.compare(eval_operand2) != 0){
			return true;
		}
	}
	else if(op.compare("<") == 0){
		if (string_to_int(eval_operand1) < string_to_int(eval_operand2)){
			return true;
		}
	}
	else if(op.compare(">") == 0){
		if (string_to_int(eval_operand1) > string_to_int(eval_operand2)){
			return true;
		}
	}
	else if(op.compare("<=") == 0){
		if (string_to_int(eval_operand1) <= string_to_int(eval_operand2)){
			return true;
		}
	}
	else if(op.compare(">=") == 0){
		if (string_to_int(eval_operand1) >= string_to_int(eval_operand2)){
			return true;
		}
	}
	return false;
}
