#include "Conjunction.h"


Conjunction::Conjunction(vector<Comparison> comp){
	comparisons = comp;
}


Conjunction::~Conjunction(void){

}

bool Conjunction::evaluate(vector<string> variables, vector<string> values){
	for(size_t i = 0; i < comparisons.size(); i++){
		if(!comparisons[i].evaluate(variables, values)){
			return false;
		}
	}
	return true;
}
