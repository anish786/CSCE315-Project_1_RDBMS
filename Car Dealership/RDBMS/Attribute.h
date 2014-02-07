#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>

/* Declaration of the Attribute Class */

using namespace std;

class Attribute{
private:
	string attribute_name;
	string attribute_type;
	int attribute_length;

public:
	/*constructors*/
	Attribute();
	Attribute(const Attribute &attribute);
	Attribute(string att_name, string att_type, int att_len);
	Attribute(string att_name, string att_type);
	
	/*accessors*/
	string get_attribute_name();
	string get_attribute_type();
	int get_attribute_length();

	/*modifiers*/
	void update(string new_attribute_name);

	/*operators*/

};

/* End of Attribute Class */

#endif