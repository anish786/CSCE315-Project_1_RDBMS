#include "Parser.h"

class Dealership{
	//parser object
	Parser parser;
	Database db;
public:
	// open the files
	void open_relation(string);
	// writes to file
	void write_to_file(string);

	void close_file(string);
	void exit();
	//Prints main menu
	void main_menu();
	//Prints car menu
	void car_menu();
	//Prints customer menu
	void customer_menu();
	//Prints sales people menu
	void salespeople_menu();
	//shows the customer relation
	void show_relations(string);
	// updates the relation
	void update_relation(string);
	// add customer to the relation
	void add_customer(string);
	// add salesperson to the relation
	void add_salesperson(string);
	// add car to the relation
	void add_car(string);
	//remove customer from relation
	void delete_relation(string);

};