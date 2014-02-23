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
	string command;
	//----------------
	dl.main_menu();
	cin >> choice;
	while(choice  != 4){
		if(choice == 1){
			dl.print_cars();
			cin >> select;
			if(select == 1){
				dl.show_relations("cars");
				dl.print_salesperson();
				cin >> select;
			}
			if(select == 2){
				dl.add_car("cars");
				dl.print_salesperson();
				cin >> select;
			}
			if(select == 3){
				dl.update_relation("cars");
				dl.print_customers();
				cin >> select;
			}
			if(select == 4){
				dl.delete_relation("cars");
				dl.print_customers();
				cin >> select;
			}
			if(select == 5){
				dl.main_menu();
				dl.write_to_file("cars");
			}
		}
		else if(choice == 2){
			dl.print_salesperson();
			cin >> select;
			if(select == 1){
				dl.show_relations("salesperson");
				dl.print_salesperson();
				cin >> select;
			}
			if(select == 2){
				dl.add_salesperson("salesperson");
				dl.print_salesperson();
				cin >> select;
			}
			if(select == 3){
				dl.update_relation("salesperson");
				dl.print_customers();
				cin >> select;
			}
			if(select == 4){
				dl.delete_relation("salesperson");
				dl.print_customers();
				cin >> select;
			}
			if(select == 5){
				dl.main_menu();
				dl.write_to_file("salesperson");
			}
		}
		else if(choice == 3){
			dl.print_customers();
			cin >> select;
			if(select == 1){
				dl.show_relations("customers");
				dl.print_customers();
				cin >> select;
			}
			if(select == 2){
				dl.add_customer("customers");
				dl.print_customers();
				cin >> select;
			}
			if(select == 3){
				dl.update_relation("customers");
				dl.print_customers();
				cin >> select;
			}
			if(select == 4){
				dl.delete_relation("customers");
				dl.print_customers();
				cin >> select;
			}
			if(select == 5){
				dl.main_menu();
				dl.write_to_file("customers");
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
			dl.close_file("transaction");
			dl.exit();
		}
		cin >> choice;
	}
	return 0;
}