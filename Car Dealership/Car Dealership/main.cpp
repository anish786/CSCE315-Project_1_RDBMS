#include "Parser.h"

// prints main menu
void main_menu(){
	cout << "\n\n********************************************************************************"
		 << "\n\t\t WELCOME TO CARS2GO AUTO DEALERSHIP!\n"
		 << "\n********************************************************************************";
	cout << "\t\t\t*********************"<<endl;
	cout << "\t\t\t*     Main Menu     *"<<endl;
	cout << "\t\t\t*********************"<<endl;
	cout << "\t\t\t*  1. Cars          *"<<endl;
	cout << "\t\t\t*  2. Sales Person  *"<<endl;
	cout << "\t\t\t*  3. Customers     *"<<endl;
	cout << "\t\t\t*  4. Quit          *"<< endl;
	cout << "\t\t\t*********************"<<endl;
	cout << "Choose option: ";
}
// prints customers
void print_customers(){
	cout <<"\t\t\t*************************"<<endl;
	cout <<"\t\t\t*      Customers        *"<<endl;
	cout <<"\t\t\t*************************"<<endl;
	cout <<"\t\t\t* 1. Show Customers     *"<<endl;
	cout <<"\t\t\t* 2. Search for customer*"<<endl;
	cout <<"\t\t\t* 3. Add Customer       *"<<endl;
	cout <<"\t\t\t* 4. Edit Customer      *"<<endl;
	cout <<"\t\t\t* 5. Delete Customer    *"<<endl;
	cout <<"\t\t\t* 6. Back to Main Menu  *"<<endl;
	cout <<"\t\t\t*************************"<<endl;
	cout <<  "Choose option: ";
}
// prints cars
void print_cars(){
	cout <<"\t\t\t*************************"<<endl;
	cout <<"\t\t\t*       Inventory       *"<<endl;
	cout <<"\t\t\t*************************"<<endl;
	cout <<"\t\t\t* 1. Show Inventory     *"<<endl;
	cout <<"\t\t\t* 2. Search for vehicle *"<<endl;
	cout <<"\t\t\t* 3. Add Vehicle        *"<<endl;
	cout <<"\t\t\t* 4. Edit Vehicle       *"<<endl;
	cout <<"\t\t\t* 5. Delete Vehicle     *"<<endl;
	cout <<"\t\t\t* 6. Back to Main Menu  *"<<endl;
	cout <<"\t\t\t*************************"<<endl;
	cout <<"Choose option: ";
}
// prints salesperson
void print_salesperson(){
	cout <<"\t\t\t******************************"<<endl;
	cout <<"\t\t\t*         Sales Person       *"<<endl;
	cout <<"\t\t\t******************************"<<endl;
	cout <<"\t\t\t* 1. Show Sales Person       *"<<endl;
	cout <<"\t\t\t* 2. Search for Sales Person *"<<endl;
	cout <<"\t\t\t* 3. Add Sales Person        *"<<endl;
	cout <<"\t\t\t* 4. Edit Sales Person       *"<<endl;
	cout <<"\t\t\t* 5. Delete Sales Person     *"<<endl;
	cout <<"\t\t\t* 6. Back to Main Menu       *"<<endl;
	cout <<"\t\t\t******************************"<<endl;
	cout <<"Choose option: ";
}
// main method
int main(){
	int choice = 0;
	string command;
	//----------------
	main_menu();
	cin >> choice;
	while(choice  != 4){
		if(choice == 1){
			print_cars();
		}
		else if(choice == 2){
			print_customers();
		}
		else if(choice == 3){
			print_salesperson();
		}
		else if(choice == 4){
			break;
		}
		cin >> choice;
	}
	return 0;
}