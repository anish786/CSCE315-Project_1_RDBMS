#include "Database.h"

using namespace std;
int main(){
	Attribute a( "Make", "string", 16);
	Attribute b( "Model", "string", 16);
	Attribute c( "Year", "int");
    
	vector< Attribute > t1att;
	t1att.push_back(a);
	t1att.push_back(b);
	t1att.push_back(c);

	vector< string > values1;
	values1.push_back("Toyota");
	values1.push_back("Yaris");
	values1.push_back("2012");
	
	vector< string > values2;
	values2.push_back("Toyota");
	values2.push_back("Corolla");
	values2.push_back("2013");
	
	vector< string > values3;
	values3.push_back("Toyota");
	values3.push_back("Matrix");
	values3.push_back("2014");
    
	vector<string> t1keys;
	t1keys.push_back("Model");
	t1keys.push_back("Year");
    
	Relation cars("CARS", t1att, t1keys);
	cars.insert_tuple(values1); 
	cars.insert_tuple(values2);
	cars.insert_tuple(values3);

	vector< string > values1_2;
	values1_2.push_back("Toyota");
	values1_2.push_back("Yaris");
	values1_2.push_back("2012");
	
	vector< string > values2_2;
	values2_2.push_back("Ford");
	values2_2.push_back("F150");
	values2_2.push_back("2011");
	
	vector< string > values3_2;
	values3_2.push_back("Ford");
	values3_2.push_back("Fiesta");
	values3_2.push_back("2013");
    
	Relation cars2("CARS", t1att, t1keys);
	cars2.insert_tuple(values1_2); 
	cars2.insert_tuple(values2_2);
	cars2.insert_tuple(values3_2);

	Relation cars_union = cars + cars2;
	Relation cars_diff = cars - cars2;

	cout << cars << cars2 << cars_union << endl;
	
	//-----------------------------
	Attribute ta( "cust", "string", 32);
	Attribute tb( "age", "int");
    
	vector< Attribute > t2att;
	t2att.push_back(ta);
	t2att.push_back(tb);
    
	vector< string > values12;
	values12.push_back("Clifton");
	values12.push_back("20");
	
	
	vector< string > values22;
	values22.push_back("Michael");
	values22.push_back("19");
    
	vector< string > values32;
	values32.push_back("Nathan");
	values32.push_back("20");
    
	vector<string> t2keys;
	t2keys.push_back("cust");
    
	Relation customer("CUSTOMER", t2att, t2keys);
	customer.insert_tuple(values12);
	customer.insert_tuple(values22);
	customer.insert_tuple(values32);

	cout << customer << endl;

	Relation r3;
	//r3.cross_product(cars, customer);
    
	cout << "New Table " << endl;
	cout << r3 << endl;
	cout << r3.projection("cust") << endl;

	cout << endl << "------------Before-Renaming------------" << endl;
    Relation relation("Inventory", t1att, t1keys);
    
    
	relation.insert_tuple(values1);
	relation.insert_tuple(values2);
	relation.insert_tuple(values3);
    
    cout << relation << endl;
    
    vector<string> primKey;
    primKey.push_back("Corolla");
    primKey.push_back("2013");
    
    string attToChange = "Year";
    string newVal = "1992";
    
    relation.rename_cell(primKey, attToChange, newVal);
    
    cout << "------------After--Renaming------------" << endl;
    cout << relation << endl;
		system("PAUSE");
	return 0;
}