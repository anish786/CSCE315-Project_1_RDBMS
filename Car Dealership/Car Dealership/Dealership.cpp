#include "Dealership.h"

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
	parser.parse_command(string("OPEN ") + file_name);
}
//void Dealership::create_relation(string relation_name){
//	db.add_relation(relation_name);
//	parser.parse_command(string("WRITE ") + relation_name);
//}
void Dealership::write_to_file(string relation_name){
	string input =  "WRITE " + relation_name;
	parser.parse_command(input);
}
void Dealership::show_relations(string relation_name){
	string input = "SHOW " + relation_name;
	parser.parse_command(input);
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
void Dealership::add_customer(string relation_name){
	string first_name;
	string last_name;
	string customer_id;
	string gender;
	stringstream ss;
	char gender_char;
	int age;

	cout << "\tFirst name: ";
	cin >> first_name;
	cout << "\tLast name: ";
	cin >> last_name;
	while(true){
		cout << "\tCustomer ID: ";
		cin >> customer_id;
		//check if ID is already used
		string query = string("") + "match <- select (customer_id == \"" + customer_id + "\") customers;";
		parser.parse_command(query);
		Database database = parser.get_database();

		//if no matches continue
		if(database.get_relation("match").get_num_tuples() == 0){
			parser.parse_command("CLOSE match");
			break;
		}
		else
			cerr << "\n\t***** ERROR: ID already in use, please try again. *****\n\n";
	}

	cout << "\tGender: ";
	cin >> gender;
	ss << gender;
	ss >> gender_char;
	cout << "\tAge: ";
	cin >> age;
	ss.str("");
	ss << age;
	string agee = ss.str();

	string input = "INSERT INTO " + relation_name + " VALUES FROM (" + first_name + ", " + last_name + ", " + customer_id + ", " + gender_char + ", " + agee + ");";
	parser.parse_command(input);
}
void Dealership::delete_relation(string relation_name){
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

void Dealership::add_salesperson(string relation_name){
	string first_name;
	string last_name;
	string sales_id;
	int num_years_employed;
	stringstream ss;

	cout << "First name: ";
	cin >> first_name;
	cout << "Last name: ";
	cin >> last_name;
	cout << "Sales ID: ";
	cin >> sales_id;
	cout << "Years employeed: ";
	cin >> num_years_employed;
	ss << num_years_employed;
	string number_years_employeed = ss.str();

	string input = "INSERT INTO " + relation_name + " VALUES FROM (" + first_name + ", " + last_name + ", " + sales_id + ", " + number_years_employeed + ");";
	parser.parse_command(input);
}

void Dealership::add_car(string relation_name){
	string make, model, car_id;
	stringstream ss;
	int year;
	cout << "Make: ";
	cin >> make;
	cout << "Model: ";
	cin >> model;
	cout << "Year: ";
	cin >> year;
	cout << "Car ID: ";
	cin >> car_id;
	ss << year;
	string yearr = ss.str();

	string input = "INSERT INTO " + relation_name + " VALUES FROM (" + make + ", " + model + ", " + car_id + ", " + yearr + ");";
	parser.parse_command(input);
}
void Dealership::close_file(string file_name){
	string input = "CLOSE " + file_name;
	parser.parse_command(input);
}
void Dealership::exit(){
	string input = "EXIT;";
	parser.parse_command(input);
}