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
		while (choice < 1 || choice > 6){
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
					dl.show("cars");
				}
				if(select == 2){
					dl.get_car();
				}
				if(select == 3){
					dl.add_car();
				}
				if(select == 4){
					dl.update_car();
				}
				if(select == 5){
					dl.remove_car();
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
					dl.show("customers");
				}
				if(select == 2){
					dl.get_customer();
				}
				if(select == 3){
					dl.add_customer();
				}
				if(select == 4){
					dl.update_customer();
				}
				if(select == 5){
					dl.remove_customer();
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
					dl.show("salesperson");
				}
				else if(select == 2){
					dl.get_salesperson();
				}
				else if(select == 3){
					dl.add_salesperson();
				}
				else if(select == 4){
					dl.update_salesperson();
				}
				else if(select == 5){
					dl.remove_salesperson();
				}
				else if(select == 6){
					dl.write_to_file("salesperson");
					break;
				}
			}
		}
		else if(choice == 4){
			while(true){
				dl.transaction_menu();
				cin >> select;
				while(select < 1 || select > 6){
					cerr << "\n\t***** ERROR: Please input a valid option *****"
						<< "\n\tPlease try again: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> select;
				}
				if(select == 1){
					dl.show("transactions");
				}
				else if(select == 2){
					dl.get_transaction();
				}
				else if(select == 3){
					dl.add_transaction();
				}
				else if(select == 4){
					dl.update_transaction();
				}
				else if(select == 5){
					dl.remove_transaction();
				}
				else if(select == 6){
					dl.write_to_file("transactions");
					break;
				}
			}
		}
		else if(choice == 5){
			while(true){
				dl.statistics_menu();
				cin >> select;
				while(select < 1 || select > 7){
					cerr << "\n\t***** ERROR: Please input a valid option *****"
						<< "\n\tPlease try again: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> select;
				}
				if(select == 1){
					dl.list_people();
				}
				else if (select == 2){
					dl.show_old_and_new_cars();
				}
				else if(select == 3){
					dl.show_customer_options();
				}
				else if(select == 4){
					dl.show_dealings();
				}
				else if(select == 5){
					dl.show_cars_bought();
				}
				else if(select == 6){
					dl.show_cars_sold();
				}
				else if (select == 7){
					break;
				}
			}
		}
		else if(choice == 6){
			break;
		}
	}
	return 0;
}