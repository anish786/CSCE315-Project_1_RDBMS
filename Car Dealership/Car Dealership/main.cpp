#include "Dealership.h"
// main method
int main(){

	Dealership dl;
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
		}
		else if(choice == 2){
			dl.print_salesperson();
		}
		else if(choice == 3){
			dl.print_customers();
			cin >> select;
			if(select == 1){
				dl.show_customer();
				cout <<"Choose option: ";
				cin >> select;
			}
			if(select == 2){

			}
			if(select == 3){
				dl.add_customer();
				dl.print_customers();
				cin >> select;
			}
			if(select == 4){

			}
			if(select == 5){

			}
			if(select == 6){
				dl.main_menu();

			}
		}
		else if(choice == 4){
			break;
		}
		cin >> choice;
	}
	return 0;
}