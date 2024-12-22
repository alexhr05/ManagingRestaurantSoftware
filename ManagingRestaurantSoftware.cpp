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

const char FILE_NAME[] = "warehouse.txt";

const char MANAGER_MENU_OPTIONS[] = "warehouse.txt";

const char WORKER_MENU_OPTIONS[] = "1.Overview of the menu\n2.View order\n3.Order cancellation\n";

const int BUFFER_SIZE = 1024;

const int MAX_SIZE_CHAR_ARRAY = 1024;

void printSourceCode() {
	ifstream in(FILE_NAME);

	if (!in.is_open()) {
		cout << "Error";
		return;
	}
	
	while (!in.eof()) {
		char buffer[BUFFER_SIZE];
		in.getline(buffer, BUFFER_SIZE);
		cout << buffer;
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
	ofstream file("warehouse.txt", ios::app);

	file << text;

	file.close();
	printSourceCode();
}

enum workersType {
    waiter,
    manager
};

int main()
{
    char order[MAX_SIZE_CHAR_ARRAY];
	char typeOfWokrer;

	cout << MANAGER_MENU_OPTIONS<<endl;

	do {
		cout << "Enter your type of hierarchy:";
		cin >> typeOfWokrer;
		cin.ignore();
	} while (typeOfWokrer != 'w' && typeOfWokrer != 'm');

	char product[MAX_SIZE_CHAR_ARRAY];
	

	if (typeOfWokrer == 'w') {
		printSourceCode();
	}
	else if(typeOfWokrer == 'm'){
		cout << "Enter product:";
		cin.getline(product, MAX_SIZE_CHAR_ARRAY);
		writeInFile(product);
		
		
	}
}