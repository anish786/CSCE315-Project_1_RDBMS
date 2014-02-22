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

}
void delete_menu(){

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

					}
					else if(choice == 2){

					}
					else if(choice == 3){

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
			//dl.print_salesperson();
		}
		else if(choice == 3){
			//dl.print_customers();
			cin >> select;
			if(select == 1){
				//dl.show_customer();
				cout <<"Choose option: ";
				cin >> select;
			}
			if(select == 2){

			}
			if(select == 3){
				//dl.add_customer();
				//dl.print_customers();
				cin >> select;
			}
			if(select == 4){

			}
			if(select == 5){

			}
			if(select == 6){
				//dl.main_menu();

			}
			else if(choice == 4){
				break;
			}
			cin >> choice;
		}
		else if(choice == 4){
			done = true;
			break;
		}
	}
	return 0;
}