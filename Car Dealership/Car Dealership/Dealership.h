#pragma once

#include "Parser.h"

class Dealership{
	//parser object
	Parser parser;
	Database db;
public:
	//Constructor
	Dealership();
	//Destructor
	~Dealership();
	// open the files
	void open_relation(string);
	// writes to file
	void write_to_file(string);

	//Prints main menu
	void main_menu();
	//Prints car menu
	void car_menu();
	//Prints customer menu
	void customer_menu();
	//Prints sales people menu
	void salespeople_menu();
	//shows the customer relation
	void show_relation(string);
	// updates the relation
	void update_relation(string);
	// add customer to the relation
	void add_customer();
	// add salesperson to the relation
	void add_salesperson();
	// add car to the relation
	void add_car();
	//remove from relation
	void delete_from_relation(string);
	//shows a tuple in 'relation' that the 'attribute' equals 'id'
	void show_tuple(string relation, string attribute, string id);

};