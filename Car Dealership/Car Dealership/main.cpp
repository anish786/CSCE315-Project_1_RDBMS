#include "Dealership.h"
// main method
int main(){

	Dealership dl;
	vector<string> open_file;
	open_file.push_back("customers");
	open_file.push_back("cars");
	open_file.push_back("salesperson");
	open_file.push_back("transactions");
	ifstream db_file;
	for(size_t i = 0; i < open_file.size(); i++){
		dl.open_relation(open_file[i]);
		//dl.write_to_file(open_file[0]);
	}

	cout << "\n\n********************************************************************************"
	 << "\n\t\t WELCOME TO CARS2GO AUTO DEALERSHIP!\n"
	 << "\n********************************************************************************";
	int choice = 0;
	int select = 0;
	bool done = false;
	string command;

	while(done == false){
		dl.main_menu();
		cin >> choice;
		// Cars Menu
		if(choice == 1){
			while(true){
				dl.car_menu();
				cin >> select;
				while(select < 1 || select > 6){
					cerr << "\n\t***** ERROR: Please input a valid option *****"
						<< "\n\tPlease try again: ";
					cin >> select;
				}
				if(select == 1){
					dl.show_relations("cars");
				}
				if(select == 2){
					string car_id;
					cout << "\tCar ID: ";
					cin >> car_id;
					dl.show_tuple("cars", "car_id", car_id);
				}
				if(select == 3){
					dl.add_car("cars");
				}
				if(select == 4){
					dl.update_relation("cars");
				}
				if(select == 5){
					dl.delete_relation("cars");
				}
				if(select == 6){
					dl.write_to_file("cars");
					break;
				}
			}
		}
		// Customer Menu
		else if(choice == 2){
			while(true){
				dl.customer_menu();
				cin >> select;
				while(select < 1 || select > 6){
						cerr << "\n\t***** ERROR: Please input a valid option *****"
							<< "\n\tPlease try again: ";
						cin >> select;
				}
				if(select == 1){
					dl.show_relations("customers");
				}
				if(select == 2){
					string cust_id;
					cout << "\tCustomer ID: ";
					cin >> cust_id;
					dl.show_tuple("customers", "customer_id", cust_id);
				}
				if(select == 3){
					dl.add_customer("customers");
				}
				if(select == 4){
					dl.update_relation("customers");
				}
				if(select == 5){
					dl.delete_relation("customers");
				}
				if(select == 6){
					dl.write_to_file("customers");
					break;
				}
			}
		}
		// Sales People Menu
		else if(choice == 3){
			while(true){
				dl.salespeople_menu();
				cin >> select;
				while(select < 1 || select > 6){
					cerr << "\n\t***** ERROR: Please input a valid option *****"
						<< "\n\tPlease try again: ";
					cin >> select;
				}
				if(select == 1){
					dl.show_relations("salesperson");
				}
				else if(select == 2){
					string sales_id;
					cout << "\tSales ID: ";
					cin >> sales_id;
					dl.show_tuple("salesperson", "sales_id", sales_id);
				}
				else if(select == 3){
					dl.add_salesperson("salesperson");
				}
				else if(select == 4){
					dl.update_relation("salesperson");
				}
				else if(select == 5){
					dl.delete_relation("salesperson");
				}
				else if(select == 6){
					dl.write_to_file("salesperson");
					break;
				}
			}
		}
		else if(choice == 4){
			
			dl.write_to_file("customers");
			dl.write_to_file("cars");
			dl.write_to_file("salesperson");
			dl.write_to_file("transactions");
			dl.close_file("customers");
			dl.close_file("cars");
			dl.close_file("salesperson");
			dl.close_file("transactions");
			dl.exit();
			break;
		}
	}
	return 0;
}