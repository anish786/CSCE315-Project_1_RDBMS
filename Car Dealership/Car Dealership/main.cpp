#include "Dealership.h"
// main method
int main(){

	Dealership dl;
	
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
		while (choice < 1 || choice > 4){
			cerr << "\n\t***** ERROR: Please input a valid option *****"
				<< "\n\tPlease try again: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> choice;
		}
		// Cars Menu
		if(choice == 1){
			while(true){
				dl.car_menu();
				cin >> select;
				while(select < 1 || select > 6){
					cerr << "\n\t***** ERROR: Please input a valid option *****"
						<< "\n\tPlease try again: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> select;
				}
				if(select == 1){
					dl.show_relation("cars");
				}
				if(select == 2){
					string car_id;
					cout << "\tCar ID: ";
					cin >> car_id;
					dl.show_tuple("cars", "car_id", car_id);
				}
				if(select == 3){
					dl.add_car();
				}
				if(select == 4){
					dl.update_relation("cars");
				}
				if(select == 5){
					dl.delete_from_relation("cars");
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
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cin >> select;
				}
				if(select == 1){
					dl.show_relation("customers");
				}
				if(select == 2){
					string cust_id;
					cout << "\tCustomer ID: ";
					cin >> cust_id;
					dl.show_tuple("customers", "customer_id", cust_id);
				}
				if(select == 3){
					dl.add_customer();
				}
				if(select == 4){
					dl.update_relation("customers");
				}
				if(select == 5){
					dl.delete_from_relation("customers");
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
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> select;
				}
				if(select == 1){
					dl.show_relation("salesperson");
				}
				else if(select == 2){
					string sales_id;
					cout << "\tSales ID: ";
					cin >> sales_id;
					dl.show_tuple("salesperson", "sales_id", sales_id);
				}
				else if(select == 3){
					dl.add_salesperson();
				}
				else if(select == 4){
					dl.update_relation("salesperson");
				}
				else if(select == 5){
					dl.delete_from_relation("salesperson");
				}
				else if(select == 6){
					dl.write_to_file("salesperson");
					break;
				}
			}
		}
		else if(choice == 4){
			break;
		}
	}
	return 0;
}