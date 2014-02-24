#include "Dealership.h"

//Constructor
Dealership::Dealership(){
	try{
		open_relation("customers");
	}
	catch (RuntimeException r){
		parser.parse_command("CREATE TABLE customers (first_name VARCHAR(20), last_name VARCHAR(20), "
			"customer_id VARCHAR(8), gender VARCHAR(1), age INTEGER) PRIMARY KEY (customer_id);");
	}
	try{
		open_relation("cars");
	}
	catch (RuntimeException r){
		parser.parse_command("CREATE TABLE cars (make VARCHAR(20), model VARCHAR(20), car_id VARCHAR(8), "
			"year INTEGER, stock INTEGER) PRIMARY KEY (car_id);");
	}
	try{
		open_relation("salesperson");
	}
	catch (RuntimeException r){
		parser.parse_command("CREATE TABLE salesperson (first_name VARCHAR(20), last_name VARCHAR(20), "
			"sales_id VARCHAR(8), years_employed INTEGER) PRIMARY KEY (sales_id);");
	}
	try{
		open_relation("transactions");
	}
	catch (RuntimeException r){
		parser.parse_command("CREATE TABLE transactions (transaction_id VARCHAR(10)) PRIMARY KEY (transaction_id);");
	}
}

//Destructor
Dealership::~Dealership(){
	write_to_file("customers");
	write_to_file("cars");
	write_to_file("salesperson");
	write_to_file("transactions");
}

// prints main menu
void Dealership::main_menu(){
	cout << "\t_________________________________________________\n" << endl
		<< "\t                  MAIN MENU" << endl
		<< "\t_________________________________________________\n" << endl
		<< "\t   Options:" << endl
		<< "\t      1. Cars " << endl
		<< "\t      2. Customers " << endl
		<< "\t      3. Sales People" << endl
		<< "\t      4. Quit" << endl
		<< "\t_________________________________________________\n" << endl
		<< "\tPlease choose option: ";
}
void Dealership::car_menu(){
		cout << "\t_________________________________________________\n" << endl
		<< "\t                  MAIN MENU -> Cars" << endl
		<< "\t_________________________________________________\n" << endl
		<< "\t   Options:" << endl
		<< "\t      1. Show Inventory " << endl
		<< "\t      2. Show Vehicle " << endl
		<< "\t      3. Add Vehicle " << endl
		<< "\t      4. Edit Vehicle" << endl
		<< "\t      5. Delete Vehicle" << endl
		<< "\t      6. Back to MAIN MENU" << endl
		<< "\t_________________________________________________\n" << endl
		<< "\tPlease choose option: ";
}
void Dealership::customer_menu(){
		cout << "\t_________________________________________________\n" << endl
		<< "\t                  MAIN MENU -> Customers" << endl
		<< "\t_________________________________________________\n" << endl
		<< "\t   Options:" << endl
		<< "\t      1. Show All Customers " << endl
		<< "\t      2. Show Customer " << endl
		<< "\t      3. Add Customer " << endl
		<< "\t      4. Edit Customer" << endl
		<< "\t      5. Delete Customer" << endl
		<< "\t      6. Back to MAIN MENU" << endl
		<< "\t_________________________________________________\n" << endl
		<< "\tPlease choose option: ";
}
void Dealership::salespeople_menu(){
		cout << "\t_________________________________________________\n" << endl
		<< "\t                  MAIN MENU -> Sales People" << endl
		<< "\t_________________________________________________\n" << endl
		<< "\t   Options:" << endl
		<< "\t      1. Show All Sales People " << endl
		<< "\t      2. Show Sales Person " << endl
		<< "\t      3. Add Sales Person " << endl
		<< "\t      4. Modify Sales Person" << endl
		<< "\t      5. Delete Sales Person" << endl
		<< "\t      6. Back to MAIN MENU" << endl
		<< "\t_________________________________________________\n" << endl
		<< "\tPlease choose option: ";
}

void Dealership::open_relation(string file_name){
	parser.parse_command_self_check(string("OPEN ") + file_name);
}

void Dealership::write_to_file(string relation_name){
	parser.parse_command(string("WRITE ") + relation_name);
}

void Dealership::show_relation(string relation_name){
	parser.parse_command(string("SHOW ") + relation_name);
}

//---------------------------------------------------------------------------
void Dealership::update_relation(string relation_name){
	string att_name;
	cout << "Attribute name: ";
	cin >> att_name;
	string literall;
	cout << "Literal: ";
	cin >> literall;
	string operator1;
	cout << "Operator: ";
	cin >> operator1;
	string operand;
	cout << "Operand: ";
	cin >> operand;
	string input = "UPDATE " + relation_name + " SET " + att_name + " = " + literall + " WHERE " + att_name + operator1 + operand + ";";
	parser.parse_command(input);
}
void Dealership::add_customer(){
	string first_name;
	string last_name;
	string customer_id;
	string gender;
	stringstream ss;
	char gender_char;
	int age;

	cout << "\n\t***** Adding a New Customer *****\n\t_____________________________________" << endl;
	cout << "\tCustomer ID: ";
	cin >> customer_id;
	cout << "\tFirst name: ";
	cin >> first_name;
	cout << "\tLast name: ";
	cin >> last_name;
	cout << "\tGender: ";
	cin >> gender;
	cout << "\tAge: ";
	cin >> age;

	ss << gender;
	ss >> gender_char;
	ss.str("");
	ss << age;
	string agee = ss.str();

	string input = "INSERT INTO customers VALUES FROM (" + first_name + ", " + last_name + ", " + customer_id + ", " + gender_char + ", " + agee + ");";
	try{
		parser.parse_command_self_check(input);
	}
	catch (RuntimeException r){
		cerr << "\n\t***** ERROR: ID already in use, please try again. *****\n\n";
	}
}
void Dealership::delete_from_relation(string relation_name){
	string operand1, operatorr, operand2;
	cout << "Operand 1: ";
	cin >> operand1;
	cout << "Operator: ";
	cin >> operatorr;
	cout << "Operator 2: ";
	cin >> operand2;
	string input = "DELETE FROM " + relation_name + " WHERE (" + operand1 + operatorr + operand2 + ");";
	parser.parse_command(input);
}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

void Dealership::add_salesperson(){
	string first_name;
	string last_name;
	string sales_id;
	int num_years_employed;
	stringstream ss;

	cout << "\n\t***** Adding a New Sales Person *****\n\t_____________________________________" << endl;
	cout << "\tSales ID: ";
	cin >> sales_id;
	cout << "\tFirst name: ";
	cin >> first_name;
	cout << "\tLast name: ";
	cin >> last_name;
	cout << "\tYears employeed: ";
	cin >> num_years_employed;

	ss << num_years_employed;
	string number_years_employeed = ss.str();

	string input = "INSERT INTO salesperson VALUES FROM (" + first_name + ", " + last_name + ", " + sales_id + ", " + number_years_employeed + ");";
	try{
		parser.parse_command_self_check(input);
	}
	catch (RuntimeException r){
		cerr << "\n\t***** ERROR: ID already in use, please try again. *****\n\n";
	}
}

void Dealership::add_car(){
	string make, model, car_id;
	stringstream ss;
	int year;
	int stock;

	cout << "\n\t***** Adding a New Car *****\n\t_____________________________________" << endl;
	cout << "\tCar ID: ";
	cin >> car_id;
	cout << "\tMake: ";
	cin >> make;
	cout << "\tModel: ";
	cin >> model;
	cout << "\tYear: ";
	cin >> year;
	cout << "\tStock: ";
	cin >> stock;

	ss << year;
	string year_s = ss.str();
	ss.str("");
	ss << stock;
	string stock_s = ss.str();

	string input = "INSERT INTO cars VALUES FROM (" + make + ", " + model + ", " + car_id + ", " + year_s + ", " + stock_s + ");";
	try{
		parser.parse_command_self_check(input);
	}
	catch (RuntimeException r){
		cerr << "\n\t***** ERROR: ID already in use, please try again. *****\n\n";
	}
}
void Dealership::show_tuple(string relation, string attribute, string id){
	string input = "Query <- select(" + attribute + " == \"" + id + "\") " + relation;
	parser.parse_command(input);
	
	if(parser.get_database().get_relation("Query").get_num_tuples() == 0){
		cout << "\n\t***** ERROR: Could not find a tuple by that ID *****\n" << endl;
	}
	else{
		parser.parse_command("SHOW Query");
	}
}