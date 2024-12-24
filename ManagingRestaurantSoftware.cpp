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

const char WAREHOUSE_FILE[] = "warehouse.txt";

const char MENU_FILE[] = "menu.txt";

const char ORDER_FILE[] = "order.txt";

const char TURNOIVER_PER_DAY_FILE[] = "turnoverPerDay.txt";

const char WAITER_MENU_OPTIONS[] = "1. Overview of the menu\n2. View order\n3. Order cancellation\n4. View past orders\n5. View past orders in alphabetical order as well as the number of orders of each item\n6. View the profits for the day";

const char MANAGER_MENU_OPTIONS[] = "1. Overview of the menu\n2. View order\n3. Order cancellation\n4. View past orders in alphabetical order as well as the number of orders of each item\n5. View past orders\n6. Overview of what is left and of what\n7. Remove a product from warehouse\n8. Add a new product to the warehouse\n9. View the profits for the day\n10. Taking a report for the day\n11. Subtract all turnovers from a given date to now\n12. Adding a new product to the menu\n13. Remove a product from the menu";

const int BUFFER_SIZE = 1024;

const int MAX_SIZE_CHAR_ARRAY = 1024;

enum workersType {
	waiter,
	manager
};


void readFromWarehouseFile() {
	ifstream in(WAREHOUSE_FILE);

	if (!in.is_open()) {
		cout << "Error";
		return;
	}

	char line[MAX_SIZE_CHAR_ARRAY];
	while (in.getline(line, BUFFER_SIZE)) {
		cout << line << endl;
	}

	in.close();
}

void readFromMenuFile() {
	ifstream in(MENU_FILE);

	if (!in.is_open()) {
		cout << "Error";
		return;
	}

	char line[MAX_SIZE_CHAR_ARRAY];
	while (in.getline(line, BUFFER_SIZE)) {
		cout << line << endl;
	}

	in.close();
}

int textLength(char* text) {
	int counter = 0;

	while (*text != '\0') {
		counter++;
		text++;
	}
	return counter;
}



void readFromOrderFile() {
	ifstream in(ORDER_FILE);
	char ordersFromFile[MAX_SIZE_CHAR_ARRAY];

	if (!in.is_open()) {
		cout << "Error";
		return;
	}

	char line[MAX_SIZE_CHAR_ARRAY];
	int counterChar = 0;
	while (in.getline(line, BUFFER_SIZE)) {
		/*while (*line != '\0') {
			counterChar++;
			line++;
		}*/

		cout << line << endl;
	}

	in.close();
}

void writeInWarehouseFile(char* text) {
	ofstream file(ORDER_FILE, ios::app);

	file << text;

	file.close();

}

void writeInMenuFile(char* text) {
	ofstream file(MENU_FILE, ios::app);

	file << text;

	file.close();

}

void writeInOrderFile(char* text) {
	ofstream file(ORDER_FILE, ios::app);

	file << text;

	file.close();

}
bool isExistArticle(int articleId) {
	ifstream file(MENU_FILE);
	char line[BUFFER_SIZE];

	if (!file.is_open()) {
		cout << "Error";

	}
	
	while (file.getline(line, BUFFER_SIZE)) {
		cout << "digitChar=" << articleId << endl;
		
		cout << "line[0]=" << line[0] << endl;
		int digit = line[0] - '0';
			if (articleId == digit) {
				return true;
			}

	}


	file.close();
	return false;
}



int main()
{
	int orders[MAX_SIZE_CHAR_ARRAY];
	char typeOfWokrer;

	char product[MAX_SIZE_CHAR_ARRAY];
	int action;
	char ordersFromFile[MAX_SIZE_CHAR_ARRAY];


	cout << "Enter your type of hierarchy:";
	cin >> typeOfWokrer;

	while (typeOfWokrer != 'w' && typeOfWokrer != 'm') {
		cout << "You have to enter your type of hierarchy(Waiter - w; Manager - m):";
		cin >> typeOfWokrer;

		cin.ignore();
	}


	if (typeOfWokrer == 'w') {
		cout << WAITER_MENU_OPTIONS << endl;
		cout << endl;

		do {
			cout << "What you want to choose from above:";
			cin >> action;

			if (action == 1) {
				cout << endl;
				readFromMenuFile();
			}
			else if (action == 2) {
				int articleId;
			

				int i = 0;
				do {
					cout << "Now you can make order from the menu:";
					cin >> articleId;
					if (isExistArticle(articleId)) {
						cout << "Article is CONTAINED" << endl;
						orders[i] = articleId;
						i++;
					}
					else {
						cout << "Article is NOT CONTAINED" << endl;
					}
					

				} while (articleId != 0);
				cout << endl;
				for (int j = 0; j < i; j++) {
					cout << orders[j] << endl;
				}


			}
			else if (action == 3) {

			}
			else if (action == 4) {

			}
			else if (action == 5) {

			}
		} while (action >= 1 || action <= 5);

	}
	else if (typeOfWokrer == 'm') {
		cout << MANAGER_MENU_OPTIONS << endl;
		cout << "Enter product:";
		cin.getline(product, MAX_SIZE_CHAR_ARRAY);

		cout << endl;



	}
}