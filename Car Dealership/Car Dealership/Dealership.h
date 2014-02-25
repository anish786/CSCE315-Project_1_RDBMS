#pragma once

#include "Parser.h"

using namespace std;

class Dealership{
	//parser object
	Parser parser;
public:
	// Constructor
	Dealership();
	// Destructor
	~Dealership();
	// open a relation
	// input the name of the relation to open
	void open_relation(string);
	// writes a relation to a file
	// input the name of the relation to write
	void write_to_file(string);
	// shows the one of the relations
	// input the name of the relation to show
	void show(string);

	// Prints main menu
	void main_menu();
	// Prints car menu
	void car_menu();
	// Prints customer menu
	void customer_menu();
	// Prints sales people menu
	void salespeople_menu();
	// Prints Transaction menu
	void transaction_menu();
	// Prints statistics menu
	void statistics_menu();
	
	// add a customer to the database
	void add_customer();
	// add a salesperson to the database
	void add_salesperson();
	// add a car to the database
	void add_car();
	// add a transaction to the database
	void add_transaction();

	// update a customers info
	void update_customer();
	// update a salesperson info
	void update_salesperson();
	// update a cars info
	void update_car();
	// update a transaction
	void update_transaction();

	// Remove a customer
	void remove_customer();
	// remove a salesperson
	void remove_salesperson();
	// remove a car
	void remove_car();
	// remove a transaction
	void remove_transaction();

	// Prompts for and displays a customer by id
	void get_customer();
	// Prompts for and displays a sales person by id
	void get_salesperson();
	// Prompts for and displays a car by id
	void get_car();
	// Prompts for and displays a transaction by id
	void get_transaction();

	// List all people (union, projection)
	void list_people();
	// Show old and new cars in different tables (difference)
	void show_old_and_new_cars();
	// Shows Cars in a customers price range (cross product)
	void show_customer_options();
	// Salespersons dealt with Customers 
	void show_dealings();
	// Cars bought by Customers 
	void show_cars_bought();
	// Cars sold by Salespersons
	void show_cars_sold();
};