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

using namespace std;

class Attribute{
private:
	string attribute_name;
	string attribute_type;
	int attribute_length;
public:
	Attribute();
	Attribute(const Attribute &attribute){
		attribute_name = attribute.attribute_name;
		attribute_type = attribute.attribute_type;
		attribute_length = attribute.attribute_length;
	}
	Attribute(string att_name, string att_type, int att_len){
		attribute_name = att_name;
		attribute_type = att_type;
		attribute_length = att_len;
	}
	Attribute(string att_name, string att_type){
		attribute_name = att_name;
		attribute_type = att_type;
	}
	string get_attribute_name(){
		return attribute_name;
	}
	string get_attribute_type(){
		return attribute_type;
	}
	int get_attribute_length(){
		return attribute_length;
	}
	void update(string new_attribute_name){
		attribute_name = new_attribute_name;
	}
};
#endif
