#include "Dealership.h"

void read_string(string &s){
	if (cin.peek() == '\n')
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, s, '\n');
}

void read_int(int &i){
	cin >> i;
	while (!cin.good()){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\tTry again: ";
		cin >> i;
	}
}

//Constructor
Dealership::Dealership(){
	try{
		open_relation("customers");
	}
	catch (RuntimeException r){
		parser.parse_command("CREATE TABLE customers (customer_id VARCHAR(8), first_name VARCHAR(20), "
			"last_name VARCHAR(20), gender VARCHAR(1), age INTEGER) PRIMARY KEY (customer_id);");
	}
	try{
		open_relation("cars");
	}
	catch (RuntimeException r){
		parser.parse_command("CREATE TABLE cars (car_id VARCHAR(8), make VARCHAR(20), model VARCHAR(20), "
			"year INTEGER, msrp INTEGER, stock INTEGER) PRIMARY KEY (car_id);");
	}
	try{
		open_relation("salesperson");
	}
	catch (RuntimeException r){
		parser.parse_command("CREATE TABLE salesperson (sales_id VARCHAR(8), first_name VARCHAR(20), "
			"last_name VARCHAR(20), gender VARCHAR(1), age INTEGER, years_employed INTEGER) PRIMARY KEY (sales_id);");
	}
	try{
		open_relation("transactions");
	}
	catch (RuntimeException r){
		parser.parse_command("CREATE TABLE transactions (transaction_id VARCHAR(8), customer_id VARCHAR(8), "
			"sales_id VARCHAR(8), car_id VARCHAR(8), sale_price INTEGER) PRIMARY KEY (transaction_id);");
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
		<< "\t      4. Transactions" << endl
		<< "\t      5. Statistics" << endl
		<< "\t      6. Quit" << endl
		<< "\t_________________________________________________\n" << endl
		<< "\tPlease choose option: ";
}

// Prints car menu
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

// Prints customer menu
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

// Prints sales people menu
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

// Prints Transaction menu
void Dealership::transaction_menu(){
	cout << "\t_________________________________________________\n" << endl
		<< "\t                  MAIN MENU -> Transaction" << endl
		<< "\t_________________________________________________\n" << endl
		<< "\t   Options:" << endl
		<< "\t      1. Show All Transactions " << endl
		<< "\t      2. Show Transaction " << endl
		<< "\t      3. Add Transaction " << endl
		<< "\t      4. Modify Transaction" << endl
		<< "\t      5. Delete Transaction" << endl
		<< "\t      6. Back to MAIN MENU" << endl
		<< "\t_________________________________________________\n" << endl
		<< "\tPlease choose option: ";
}

// Prints statistics menu
void Dealership::statistics_menu(){
	cout << "\t_________________________________________________\n" << endl
		<< "\t                  MAIN MENU -> Statistics" << endl
		<< "\t_________________________________________________\n" << endl
		<< "\t   Options:" << endl
		<< "\t      1. List all People " << endl
		<< "\t      2. Show Old and New Cars " << endl
		<< "\t      3. Cars in Customer Price Range " << endl
		<< "\t      4. Salespersons dealt with Customers " << endl
		<< "\t      5. Cars bought by Customers " << endl
		<< "\t      6. Cars sold by Salespersons " << endl
		<< "\t      7. Back to MAIN MENU" << endl
		<< "\t_________________________________________________\n" << endl
		<< "\tPlease choose option: ";
}

// open a relation
// input the name of the relation to open
void Dealership::open_relation(string file_name){
	parser.parse_command_self_check(string("OPEN ") + file_name);
}

// writes a relation to a file
// input the name of the relation to write
void Dealership::write_to_file(string relation_name){
	parser.parse_command(string("WRITE ") + relation_name);
}

// shows the one of the relations
// input the name of the relation to show
void Dealership::show(string relation_name){
	parser.parse_command(string("SHOW ") + relation_name);
}

// add a customer to the database
void Dealership::add_customer(){
	string first_name;
	string last_name;
	string customer_id;
	string gender;
	stringstream ss;
	int age;

	cout << "\n\t***** Adding a New Customer *****\n\t_____________________________________" << endl;
	cout << "\tCustomer ID: ";
	read_string(customer_id);
	cout << "\tFirst name: ";
	read_string(first_name);
	cout << "\tLast name: ";
	read_string(last_name);
	cout << "\tGender: ";
	read_string(gender);
	cout << "\tAge: ";
	read_int(age);

	ss << age;
	string age_s = ss.str();

	string input = "INSERT INTO customers VALUES FROM (\"" + customer_id + "\", \"" + first_name + "\", \"" + last_name + "\", \"" + gender + "\", " + age_s + ");";
	try{
		parser.parse_command_self_check(input);
	}
	catch (RuntimeException r){
		cerr << "\n\t***** ERROR: ID already in use, please try again. *****\n\n";
	}
}

// add a salesperson to the database
void Dealership::add_salesperson(){
	string first_name;
	string last_name;
	string sales_id;
	int num_years_employed;
	string gender;
	stringstream ss;
	int age;

	cout << "\n\t***** Adding a New Sales Person *****\n\t_____________________________________" << endl;
	cout << "\tSales ID: ";
	read_string(sales_id);
	cout << "\tFirst name: ";
	read_string(first_name);
	cout << "\tLast name: ";
	read_string(last_name);
	cout << "\tGender: ";
	read_string(gender);
	cout << "\tAge: ";
	read_int(age);
	cout << "\tYears employeed: ";
	read_int(num_years_employed);

	ss << num_years_employed;
	string number_years_employed_s = ss.str();
	ss.str("");
	ss << age;
	string age_s = ss.str();

	string input = "INSERT INTO salesperson VALUES FROM (\"" + sales_id + "\", \"" + first_name + "\", \"" + last_name + "\", \"" + gender + "\", " + age_s + ", " + number_years_employed_s + ");";
	try{
		parser.parse_command_self_check(input);
	}
	catch (RuntimeException r){
		cerr << "\n\t***** ERROR: ID already in use, please try again. *****\n\n";
	}
}

// add a car to the database
void Dealership::add_car(){
	string make, model, car_id;
	stringstream ss;
	int msrp;
	int year;
	int stock;

	cout << "\n\t***** Adding a New Car *****\n\t_____________________________________" << endl;
	cout << "\tCar ID: ";
	read_string(car_id);
	cout << "\tMake: ";
	read_string(make);
	cout << "\tModel: ";
	read_string(model);
	cout << "\tYear: ";
	read_int(year);
	cout << "\tMSRP: ";
	read_int(msrp);
	cout << "\tStock: ";
	read_int(stock);

	ss << year;
	string year_s = ss.str();
	ss.str("");
	ss << stock;
	string stock_s = ss.str();
	ss.str("");
	ss << msrp;
	string msrp_s = ss.str();

	string input = "INSERT INTO cars VALUES FROM (\"" + car_id + "\", \"" + make + "\", \"" + model + "\", " + year_s + ", " + msrp_s + ", " + stock_s + ");";
	try{
		parser.parse_command_self_check(input);
	}
	catch (RuntimeException r){
		cerr << "\n\t***** ERROR: ID already in use, please try again. *****\n\n";
	}
}

// add a transaction to the database
void Dealership::add_transaction(){
	string trans_id;
	string sales_id;
	string customer_id;
	string car_id;
	int price;
	stringstream ss;
	
	cout << "\n\t***** Adding a Transaction *****\n\t_____________________________________" << endl;
	cout << "\tTransaction ID: ";
	read_string(trans_id);
	cout << "\tCustomer ID: ";
	read_string(customer_id);
	cout << "\tSales ID: ";
	read_string(sales_id);
	cout << "\tCar ID: ";
	read_string(car_id);
	cout << "\tSale Price: ";
	read_int(price);
	
	ss << price;
	string price_s = ss.str();
	
	string input = "INSERT INTO transactions VALUES FROM (\"" + trans_id + "\", \"" + customer_id + "\", \"" + sales_id + "\", \"" + car_id + "\", " + price_s + ");"; 
	try{
		parser.parse_command_self_check(input);
	}
	catch (RuntimeException r){
		cerr << "\n\t***** ERROR: ID already in use, please try again. *****\n\n";
	}
}

// update a customers info
void Dealership::update_customer(){
	string customer_id;
	cout << "\tCustomer ID: ";
	read_string(customer_id);
	
	int choice;
	string att_name, literaal;
	cout << "\t   What Attribue do you want to change?"
		<< "\t      1. First name" << endl
		<< "\t      2. Last name" << endl
		<< "\t      3. Gender" << endl
		<< "\t      4. Age" << endl;
	read_int(choice);
	while (choice < 1 || choice > 4){
			cerr << "\n\t***** ERROR: Please input a valid option *****"
				<< "\n\tPlease try again: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			read_int(choice);
	}

	if(choice == 1){
		cout << "\tFirst Name: ";
		read_string(literaal);
		att_name = "first_name";
	}
	else if(choice == 2){
		cout << "\tLast Name: ";
		read_string(literaal);
		att_name = "last_name";
	}
	else if(choice == 3){
		cout << "\tGender: ";
		read_string(literaal);
		att_name = "gender";
	}
	else if(choice == 4){
		cout << "\tAge: ";
		int age;
		read_int(age);
		stringstream ss;
		ss << age;
		literaal = ss.str();
		att_name = "age";
	}

	string input = "UPDATE customers SET " + att_name + " = \"" + literaal + "\" WHERE \"" + customer_id + "\" == cust_id;";
	parser.parse_command(input);
}

// update a salesperson info
void Dealership::update_salesperson(){
	string sales_id;
	cout << "\tSales ID: ";
	read_string(sales_id);
	
	int choice;
	string att_name, literaal;
	cout << "\t   What Attribue do you want to change?"
		<< "\t      1. First name" << endl
		<< "\t      2. Last name" << endl
		<< "\t      3. Gender" << endl
		<< "\t      4. Age" << endl
		<< "\t      5. Years Employeed" << endl;
	read_int(choice);
	while (choice < 1 || choice > 5){
			cerr << "\n\t***** ERROR: Please input a valid option *****"
				<< "\n\tPlease try again: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			read_int(choice);
	}

	if(choice == 1){
		cout << "\tFirst Name: ";
		read_string(literaal);
		att_name = "first_name";
	}
	else if(choice == 2){
		cout << "\tLast Name: ";
		read_string(literaal);
		att_name = "last_name";
	}
	else if(choice == 3){
		cout << "\tGender: ";
		read_string(literaal);
		att_name = "gender";
	}
	else if(choice == 4){
		cout << "\tAge: ";
		int age;
		read_int(age);
		stringstream ss;
		ss << age;
		literaal = ss.str();
		att_name = "age";
	}
	else if(choice == 5){
		cout << "\tYears Employed: ";
		int yrs_emply;
		read_int(yrs_emply);
		stringstream ss;
		ss << yrs_emply;
		literaal = ss.str();
		att_name = "years_employed";
	}

	string input = "UPDATE salesperson SET " + att_name + " = \"" + literaal + "\" WHERE \"" + sales_id + "\" == sales_id;";
	parser.parse_command(input);
}

// update a cars info
void Dealership::update_car(){
	string car_id;
	cout << "\tCar ID: ";
	read_string(car_id);
	
	int choice;
	string att_name, literaal;
	cout << "\t   What Attribue do you want to change?"
		<< "\t      1. Make" << endl
		<< "\t      2. Model" << endl
		<< "\t      3. Year" << endl
		<< "\t      4. MSPR" << endl
		<< "\t      5. Stock" << endl;
	read_int(choice);
	while (choice < 1 || choice > 5){
			cerr << "\n\t***** ERROR: Please input a valid option *****"
				<< "\n\tPlease try again: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			read_int(choice);
	}

	if(choice == 1){
		cout << "\tMake: ";
		read_string(literaal);
		att_name = "make";
	}
	else if(choice == 2){
		cout << "\tModel: ";
		read_string(literaal);
		att_name = "model";
	}
	else if(choice == 3){
		cout << "\tYear: ";
		int year;
		read_int(year);
		stringstream ss;
		ss << year;
		literaal = ss.str();
		att_name = "year";
	}
	else if(choice == 4){
		cout << "\tMSRP: ";
		int msrp;
		read_int(msrp);
		stringstream ss;
		ss << msrp;
		literaal = ss.str();
		att_name = "msrp";
	}
	else if(choice == 5){
		cout << "\tStock: ";
		int stock;
		read_int(stock);
		stringstream ss;
		ss << stock;
		literaal = ss.str();
		att_name = "stock";
	}

	string input = "UPDATE cars SET " + att_name + " = \"" + literaal + "\" WHERE \"" + car_id + "\" == car_id;";
	parser.parse_command(input);
}

// update a transaction
void Dealership::update_transaction(){
	string transaction_id;
	cout << "\tTransaction ID: ";
	read_string(transaction_id);
	
	int choice;
	string att_name, literaal;
	cout << "\t   What Attribue do you want to change?"
		<< "\t      1. Customer ID" << endl
		<< "\t      2. Sales ID" << endl
		<< "\t      3. Car ID" << endl
		<< "\t      4. Sale Price" << endl;
	read_int(choice);
	while (choice < 1 || choice > 4){
			cerr << "\n\t***** ERROR: Please input a valid option *****"
				<< "\n\tPlease try again: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			read_int(choice);
	}

	if(choice == 1){
		cout << "\tCustomer ID: ";
		read_string(literaal);
		att_name = "customer_id";
	}
	else if(choice == 2){
		cout << "\tSales ID: ";
		read_string(literaal);
		att_name = "sales_id";
	}
	else if(choice == 3){
		cout << "\tCar ID: ";
		read_string(literaal);
		att_name = "car_id";
	}
	else if(choice == 4){
		cout << "\tSales Price: ";
		int price;
		read_int(price);
		stringstream ss;
		ss << price;
		literaal = ss.str();
		att_name = "sale_price";
	}

	string input = "UPDATE transactions SET " + att_name + " = \"" + literaal + "\" WHERE \"" + transaction_id + "\" == transaction_id;";
	parser.parse_command(input);
}

// Remove a customer
void Dealership::remove_customer(){
	string cust_id;
	cout << "\tCustomer ID: ";
	read_string(cust_id);
	string input = "DELETE FROM customers WHERE (\"" + cust_id + "\" == cust_id);";
	parser.parse_command(input);
}

// remove a salesperson
void Dealership::remove_salesperson(){
	string sales_id;
	cout << "\tSalesperson ID: ";
	read_string(sales_id);
	string input = "DELETE FROM salesperson WHERE (\"" + sales_id + "\" == sales_id);";
	parser.parse_command(input);
}

// remove a car
void Dealership::remove_car(){
	string car_id;
	cout << "\tCar ID: ";
	read_string(car_id);
	string input = "DELETE FROM cars WHERE (\"" + car_id + "\" == car_id);";
	parser.parse_command(input);
}

// remove a transaction
void Dealership::remove_transaction(){
	string trans_id;
	cout << "\tTransaction ID: ";
	read_string(trans_id);
	string input = "DELETE FROM transactions WHERE (\"" + trans_id + "\" == transaction_id);";
	parser.parse_command(input);
}

// Prompts for and displays a customer by id
void Dealership::get_customer(){
	string cust_id;
	cout << "\tCustomer ID: ";
	read_string(cust_id);

	parser.parse_command("SHOW select (cust_id == " + cust_id + ") customers");
}

// Prompts for and displays a sales person by id
void Dealership::get_salesperson(){
	string sales_id;
	cout << "\tSalesperson ID: ";
	read_string(sales_id);

	parser.parse_command("SHOW select (sales_id == " + sales_id + ") salesperson");
}

// Prompts for and displays a car by id
void Dealership::get_car(){
	string car_id;
	cout << "\tCar ID: ";
	read_string(car_id);

	parser.parse_command("SHOW select (car_id == " + car_id + ") cars");
}

// Prompts for and displays a transaction by id
void Dealership::get_transaction(){
	string trans_id;
	cout << "\tTransaction ID: ";
	read_string(trans_id);

	parser.parse_command("SHOW select (transaction_id == " + trans_id + ") transactions");
}

// List all people (union, projection)
void Dealership::list_people(){

	string salesperson = "sales <- project (first_name, last_name, gender, age) salesperson;";
	string customer = "cust <- project (first_name, last_name, gender, age) customers;";
	string query = "list_of_people <- sales + cust;";
	parser.parse_command(salesperson);
	parser.parse_command(customer);
	parser.parse_command(query);
	show("list_of_people");
}

// Show old and new cars in different tables (difference)
void Dealership::show_old_and_new_cars(){
	string year;

	cout << "\tStarting year for new cars: ";
	read_string(year);
	string input1 = "old_cars <- select(year < " + year + ") cars;";
	string input2 = "new_cars <- cars - old_cars;";
	parser.parse_command(input1);
	parser.parse_command(input2);
	show("old_cars");
	show("new_cars");
}

// Shows Cars in a customers price range (cross product)
void Dealership::show_customer_options(){
	int max_price;
	cout << "\tMaximum Price: ";
	read_int(max_price);

	stringstream ss;
	ss << max_price;
	string max_price_s = ss.str();

	parser.parse_command("availabe_cars <- select (msrp <= "+ max_price_s +" && stock > 0) cars");
	parser.parse_command("options <- project (first_name, last_name, make, model, year, msrp) customers * availabe_cars");
	show("options");
}

// Salespersons dealt with Customers 
void Dealership::show_dealings(){
	parser.parse_command("rename_cust <- project (customer_id, cust_first, cust_last) rename (customer_id, cust_first, cust_last, age, gender) customers");
	parser.parse_command("rename_sales <- project (sales_id, sales_first, sales_last) rename (sales_id, sales_first, sales_last, age, gender, num_years_employed) salesperson");
	parser.parse_command("join_sales_cust <- (rename_sales JOIN transactions) JOIN rename_cust");
	parser.parse_command("dealings <- project (sales_first, sales_last, cust_first, cust_last) join_sales_cust");
	show("dealings");
}

// Cars bought by Customers 
void Dealership::show_cars_bought(){
	parser.parse_command("join_cust_cars <- (customers JOIN transactions) JOIN cars");
	parser.parse_command("cars_bought <- project (first_name, last_name, sale_price, make, model, year) join_cust_cars");
	show("cars_bought");

}

// Cars sold by Salespersons
void Dealership::show_cars_sold(){
	parser.parse_command("join_sales_cars <- (salesperson JOIN transactions) JOIN cars");
	parser.parse_command("cars_sold <- project (first_name, last_name, sale_price, make, model, year) join_sales_cars");
	show("cars_sold");
}
