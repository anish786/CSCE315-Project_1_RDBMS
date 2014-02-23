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
	//prints customers menu
	void print_customers();
	//prints cars menu
	void print_cars();
	//prints salesperson menu
	void print_salesperson();
	//shows the customer relation
	void show_relations(string);
	// updates the relation
	void update_relation(string);
	// add customer into the relation
	void add_customer(string);
	//remove customer from relation
	void delete_relation(string);

	//SALESPERSON
	void add_salesperson(string);
	void add_car(string);

};