/*
* Solution to course project # N№1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
* 
* @author Alex Hristov
* @idnumber 6MI0600471
* @compiler VC
* 
*/


#include <iostream>
#include <iostream>
#include <fstream>

using namespace std;

const char UPPER_FOLDER[] = "./warehouse.txt";

const char WAREHOUSE_FILE[] = "warehouse.txt";

const char MENU_FILE[] = "menu.txt";

const char ORDER_FILE[] = "order.txt";

const char WAITER_MENU_OPTIONS[] = "1. Overview of the menu\n2. View order\n3. Order cancellation\n4. View past orders\n5. View past orders in alphabetical order as well as the number of orders of each item\n6. View the profits for the day";

const char MANAGER_MENU_OPTIONS[] = "1. Overview of the menu\n2. View order\n3. Order cancellation\n4. View past orders in alphabetical order as well as the number of orders of each item\n5. View past orders\n6. Overview of what is left and of what\n7. Remove a product from warehouse\n8. Add a new product to the warehouse\n9. View the profits for the day\n10. Taking a report for the day\n11. Subtract all turnovers from a given date to now\n12. Adding a new product to the menu\n13. Remove a product from the menu";

const int BUFFER_SIZE = 1024;

const int MAX_SIZE_CHAR_ARRAY = 1024;

void readFromFile() {
	ifstream in(WAREHOUSE_FILE);

	if (!in.is_open()) {
		cout << "Error";
		return;
	}
	
	char line[MAX_SIZE_CHAR_ARRAY];
	while (in.getline(line, BUFFER_SIZE)) {		
		cout << line<<endl;
	}

	in.close();
}

//void readCharArrayWithSpaces() {
//	ofstream out(FILE_NAME);
//	
//	char test[] = "abc de";
//	out << test;
//
//	out.close();
//
//	ifstream in(FILE_NAME);
//
//	char test2[BUFFER_SIZE];
//	in.getline(test2, BUFFER_SIZE);
//
//	in.close();
//}


void writeInFile(char* text) {
	ofstream file(WAREHOUSE_FILE, ios::app);

	file << text;

	file.close();
	readFromFile();
}

enum workersType {
    waiter,
    manager
};

int main()
{
    char order[MAX_SIZE_CHAR_ARRAY];
	char typeOfWokrer;

	cout << "Enter your type of hierarchy:";
	cin >> typeOfWokrer;

	while (typeOfWokrer != 'w' && typeOfWokrer != 'm') {
		cout << "You have to enter your type of hierarchy(Waiter - w; Manager - m):";
		cin >> typeOfWokrer;

		cin.ignore();
	}

	char product[MAX_SIZE_CHAR_ARRAY];
	
	if (typeOfWokrer == 'w') {
		cout << WAITER_MENU_OPTIONS << endl;
		readFromFile();
	}
	else if(typeOfWokrer == 'm'){
		cout << MANAGER_MENU_OPTIONS << endl;
		cout << "Enter product:";
		cin.getline(product, MAX_SIZE_CHAR_ARRAY);

		cout << endl;
		writeInFile(product);
		
		
	}
}