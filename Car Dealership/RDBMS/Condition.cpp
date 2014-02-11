#include "Condition.h"


Condition::Condition(vector<Conjunction> con){
	conjunctions = con;
}

Condition::~Condition(void){

}

bool Condition::evaluate(vector<string> variables, vector<string> values){
	for(size_t i = 0; i < conjunctions.size(); i++){
		if(conjunctions[i].evaluate(variables, values)){
			return true;
		}
	}
	return false;
}
