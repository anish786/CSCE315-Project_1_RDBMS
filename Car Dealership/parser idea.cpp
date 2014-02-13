Relation Database::evaluate_expression(vector<string> atomic_expr){
	if(atomic_expr.size() == 1){
		return get_relation(atomic_expr[0]);
	}
	else if(atomic_expr[0].compare("select") == 0){
		vector<string> att_list;

		return select(att_list, evaluate_expression());
	}
	else if(atomic_expr[0].compare("project") == 0){
		vector<string> att_list;

		return project(att_list, evaluate_expression());
	}
	else if(atomic_expr[0].compare("rename") == 0){

		return rename(att_list, evaluate_expression());
	}
	else if(atomic_expr[1].compare("+") == 0){
		vector<string> next_atomic;
		size_t i = 2;
		size_t e =  atomic_expr.size()-1;
		if(atomic_expr[i].compare("(")){
			i++;
			if(atomic_expr[e].compare(")")){
				e--;
			}
		}
		for(; i <= e; i++){
			next_atomic.push_back(atomic_expr[i]);
		}
		return atomic_expr[0] + evaluate_expression(next_atomic);
	}
	else if(atomic_expr[1].compare("-") == 0){
		vector<string> next_atomic;
		size_t i = 2;
		size_t e =  atomic_expr.size()-1;
		if(atomic_expr[i].compare("(")){
			i++;
			if(atomic_expr[e].compare(")")){
				e--;
			}
		}
		for(; i <= e; i++){
			next_atomic.push_back(atomic_expr[i]);
		}
		return atomic_expr[0] - evaluate_expression(next_atomic);
	}
	else if(atomic_expr[1].compare("*") == 0){
		vector<string> next_atomic;
		size_t i = 2;
		size_t e =  atomic_expr.size()-1;
		if(atomic_expr[i].compare("(")){
			i++;
			if(atomic_expr[e].compare(")")){
				e--;
			}
		}
		for(; i <= e; i++){
			next_atomic.push_back(atomic_expr[i]);
		}
		return atomic_expr[0] * evaluate_expression(next_atomic);
	}
	else if(atomic_expr[1].compare("JOIN") == 0){
		vector<string> next_atomic;
		size_t i = 2;
		size_t e =  atomic_expr.size()-1;
		if(atomic_expr[i].compare("(")){
			i++;
			if(atomic_expr[e].compare(")")){
				e--;
			}
		}
		for(; i <= e; i++){
			next_atomic.push_back(atomic_expr[i]);
		}
		return join(atomic_expr[0], evaluate_expression(next_atomic));
	}
}