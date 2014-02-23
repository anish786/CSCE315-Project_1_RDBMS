#include "Dealership.h"

// prints main menu
void Dealership::main_menu(){
	cout << "\t\t\t*********************"<<endl;
	cout << "\t\t\t*     Main Menu     *"<<endl;
	cout << "\t\t\t*********************"<<endl;
	cout << "\t\t\t*  1. Cars          *"<<endl;
	cout << "\t\t\t*  2. Sales Person  *"<<endl;
	cout << "\t\t\t*  3. Customers     *"<<endl;
	cout << "\t\t\t*  4. Quit          *"<<endl;
	cout << "\t\t\t*********************"<<endl;
	cout << "Choose option: ";
}
// prints customers
void Dealership::print_customers(){
	cout <<"\t\t\t*************************"<<endl;
	cout <<"\t\t\t*      Customers        *"<<endl;
	cout <<"\t\t\t*************************"<<endl;
	cout <<"\t\t\t* 1. Show Customers     *"<<endl;
	cout <<"\t\t\t* 2. Add Customer       *"<<endl;
	cout <<"\t\t\t* 3. Edit Customer      *"<<endl;
	cout <<"\t\t\t* 4. Delete Customer    *"<<endl;
	cout <<"\t\t\t* 5. Back to Main Menu  *"<<endl;
	cout <<"\t\t\t*************************"<<endl;
	cout <<  "Choose option: ";
}
// prints cars
void Dealership::print_cars(){
	cout <<"\t\t\t*************************"<<endl;
	cout <<"\t\t\t*       Inventory       *"<<endl;
	cout <<"\t\t\t*************************"<<endl;
	cout <<"\t\t\t* 1. Show Inventory     *"<<endl;
	cout <<"\t\t\t* 2. Add Vehicle        *"<<endl;
	cout <<"\t\t\t* 3. Edit Vehicle       *"<<endl;
	cout <<"\t\t\t* 4. Delete Vehicle     *"<<endl;
	cout <<"\t\t\t* 5. Back to Main Menu  *"<<endl;
	cout <<"\t\t\t*************************"<<endl;
	cout <<"Choose option: ";
}
// prints salesperson
void Dealership::print_salesperson(){
	cout <<"\t\t\t******************************"<<endl;
	cout <<"\t\t\t*         Sales Person       *"<<endl;
	cout <<"\t\t\t******************************"<<endl;
	cout <<"\t\t\t* 1. Show Sales Person       *"<<endl;
	cout <<"\t\t\t* 2. Add Sales Person        *"<<endl;
	cout <<"\t\t\t* 3. Edit Sales Person       *"<<endl;
	cout <<"\t\t\t* 4. Delete Sales Person     *"<<endl;
	cout <<"\t\t\t* 5. Back to Main Menu       *"<<endl;
	cout <<"\t\t\t******************************"<<endl;
	cout <<"Choose option: ";
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
	cout << "First name: ";
	cin >> first_name;
	string last_name;
	cout << "Last name: ";
	cin >> last_name;
	string customer_id;
	cout << "Customer ID: ";
	cin >> customer_id;
	char gender;
	cout << "Gender: ";
	cin >> gender;
	int age;
	cout << "Age: ";
	cin >> age;
	stringstream ss;
	ss << age;
	string agee = ss.str();

	string input = "INSERT INTO " + relation_name + " VALUES FROM (" + first_name + ", " + last_name + ", " + customer_id + ", " + gender + ", " + agee + ");";
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
	cout << "First name: ";
	cin >> first_name;
	string last_name;
	cout << "Last name: ";
	cin >> last_name;
	string sales_id;
	cout << "Sales ID: ";
	cin >> sales_id;
	int num_years_employed;
	cout << "Years employeed: ";
	cin >> num_years_employed;
	stringstream ss;
	ss << num_years_employed;
	string number_years_employeed = ss.str();

	string input = "INSERT INTO " + relation_name + " VALUES FROM (" + first_name + ", " + last_name + ", " + sales_id + ", " + number_years_employeed + ");";
	parser.parse_command(input);
}

void Dealership::add_car(string relation_name){
	string make, model, car_id;
	int year;
	cout << "Make: ";
	cin >> make;
	cout << "Model: ";
	cin >> model;
	cout << "Year: ";
	cin >> year;
	cout << "Car ID: ";
	cin >> car_id;
	stringstream ss;
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