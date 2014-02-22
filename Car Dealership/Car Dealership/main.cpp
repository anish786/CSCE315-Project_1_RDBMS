//#include "Dealership.h"
#include "Database.h"

void main_menu(){
	cout << "\t______________________________________________________\n" << endl
		<< "\t                     MAIN MENU" << endl
		<< "\t______________________________________________________\n" << endl
		<< "\t   Options:" << endl
		<< "\t      1. Add data " << endl
		<< "\t      2. Modify data " << endl
		<< "\t      3. Delete data" << endl
		<< "\t      4. Quit" << endl
		<< "\t______________________________________________________\n" << endl
		<< "\tPlease choose option: ";
}
void add_menu(){
		cout << "\t______________________________________________________\n" << endl
		<< "\t                     MAIN MENU -> Add Menu" << endl
		<< "\t______________________________________________________\n" << endl
		<< "\t   Options:" << endl
		<< "\t      1. Add a new car " << endl
		<< "\t      2. Add a new customer " << endl
		<< "\t      3. Add a new salesperson" << endl
		<< "\t      4. <- Back to MAIN MENU" << endl
		<< "\t      5. Quit" << endl
		<< "\t______________________________________________________\n" << endl
		<< "\tPlease choose option: ";
}
void modify_menu(){
		cout << "\t______________________________________________________\n" << endl
		<< "\t                     MAIN MENU -> Modify Menu" << endl
		<< "\t______________________________________________________\n" << endl
		<< "\t   Options:" << endl
		<< "\t      1. Modify a car " << endl
		<< "\t      2. Modify a customer " << endl
		<< "\t      3. Modify a salesperson" << endl
		<< "\t      4. <- Back to MAIN MENU" << endl
		<< "\t      5. Quit" << endl
		<< "\t______________________________________________________\n" << endl
		<< "\tPlease choose option: ";
}
void delete_menu(){
		cout << "\t______________________________________________________\n" << endl
		<< "\t                     MAIN MENU -> Delete Menu" << endl
		<< "\t______________________________________________________\n" << endl
		<< "\t   Options:" << endl
		<< "\t      1. Delete a car " << endl
		<< "\t      2. Delete a customer " << endl
		<< "\t      3. Delete a salesperson" << endl
		<< "\t      4. <- Back to MAIN MENU" << endl
		<< "\t      5. Quit" << endl
		<< "\t______________________________________________________\n" << endl
		<< "\tPlease choose option: ";
}

// main method
int main(){

	//Dealership dl;
	vector<string> open_file;
	open_file.push_back("customers");
	open_file.push_back("cars");
	open_file.push_back("salesperson");
	open_file.push_back("transactions");
	for(size_t i = 0; i < open_file.size(); i++){
		//dl.open_relation(open_file[i]);
	}
	cout << "\n\n********************************************************************************"
	 << "\n\t\t WELCOME TO CARS2GO AUTO DEALERSHIP!\n"
	 << "\n********************************************************************************";
	int choice = 0;
	int select = 0;
	bool done = false;
	string command;
	
	// Loop for main menu
	while(done == false){

		main_menu();
		cin >> choice;

		if(choice == 1){
			// Loop for Adding Menu
			while(done == false){

				add_menu();
				cin >> choice;
				if(choice >= 1 && choice <=5){
					if(choice == 1){
						cout << "\nAdding car\n";
					}
					else if(choice == 2){
						cout << "\nAdding customer\n";
					}
					else if(choice == 3){
						cout << "\nAdding salesperson\n";
					}
					else if(choice == 4){
						break;
					}
					else if(choice == 5){
						done = true;
						break;
					}
				}
				else{
					cerr << "\n****** ERROR: Option value not in specified range. *******\n";
				}
			}
		}
		else if(choice == 2){
			// Loop for Modify Menu
			while(done == false){

				modify_menu();
				cin >> choice;
				if(choice == 1){
					cout << "\nModifying car\n";
				}
				else if(choice == 2){
					cout << "\nModifying customer\n";
				}
				else if(choice == 3){
					cout << "\nModifying salesperson\n";
				}
				else if(choice == 4){
					break;
				}
				else if(choice == 5){
					done = true;
					break;
				}
				else{
					cerr << "\n****** ERROR: Option value not in specified range. *******\n";
				}
			}
		}
		else if(choice == 3){
			// Loop for Delete Menu
			while(done == false){

				delete_menu();
				cin >> choice;
				if(choice >= 1 && choice <=5){
					if(choice == 1){
						cout << "\Deleting car\n";
					}
					else if(choice == 2){
						cout << "\nDeleting customer\n";
					}
					else if(choice == 3){
						cout << "\nDeleting salesperson\n";
					}
					else if(choice == 4){
						break;
					}
					else if(choice == 5){
						done = true;
						break;
					}
				}
				else{
					cerr << "\n****** ERROR: Option value not in specified range. *******\n";
				}
			}
		}
		else if(choice == 4){
			done = true;
			break;
		}
	}
	return 0;
}