#include "Parser.h"

using namespace std;

int main(){
	try{
		Parser parser;
		parser.parser_commandline();
	}
	catch(RuntimeException r){
		cerr << r.getMessage() << endl;
	}
	catch (...) {
		return 1;
	}
	return 0;
}