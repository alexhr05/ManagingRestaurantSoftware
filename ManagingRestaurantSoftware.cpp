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
#include <cmath> 

using namespace std;

const char WAREHOUSE_FILE[] = "warehouse.txt";

const char MENU_FILE[] = "menu.txt";

const char ORDER_FILE[] = "order.txt";

const char TURNOIVER_PER_DAY_FILE[] = "turnoverPerDay.txt";

const char _FILE[] = "order.txt";

const char WAITER_MENU_OPTIONS[] = "1. Overview of the menu\n2. View order\n3. Order cancellation\n4. View past orders\n5. View past orders in alphabetical order as well as the number of orders of each item\n6. View the profits for the day";

const char MANAGER_MENU_OPTIONS[] = "1. Overview of the menu\n2. View order\n3. Order cancellation\n4. View past orders in alphabetical order as well as the number of orders of each item\n5. View past orders\n6. Overview of what is left and of what\n7. Remove a product from warehouse\n8. Add a new product to the warehouse\n9. View the profits for the day\n10. Taking a report for the day\n11. Subtract all turnovers from a given date to now\n12. Adding a new product to the menu\n13. Remove a product from the menu";

const int BUFFER_SIZE = 1024;

const int MAX_SIZE_CHAR_ARRAY = 1024;

enum workersType {
	waiter,
	manager
};

int textLength(char* text) {
	int counter = 0;

	while (*text != '\0') {
		counter++;
		text++;
	}
	return counter;
}

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

bool searchSubString(char* main, char* sub) {
	if (main == nullptr || sub == nullptr) {
		return false;
	}
	int mainLength = textLength(main);
	int subLength = textLength(sub);

	if (subLength > mainLength) {
		return false;
	}


	for (int i = 0; i < mainLength - subLength; i++) {
		int j = 0;
		while (j < subLength && main[i + j] == sub[j]) {
			j++;
		}
		if (j == subLength) {
			return true;
		}
	}
	return false;

}


void readFromMenuFile() {
	ifstream in(MENU_FILE);

	if (!in.is_open()) {
		cout << "Error";
		return;
	}

	char line[MAX_SIZE_CHAR_ARRAY];
	cout << endl;
	
	while (in.getline(line, BUFFER_SIZE)) {
		cout << endl;
		cout << line << endl;
		char sub[] = "Soup";
		cout<<"isContain:"<<searchSubString(line, sub)<<endl;
	}
	cout << endl;

	
	in.close();
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
	int i = 0;
	int digit = 0;
	while (file.getline(line, BUFFER_SIZE)) {
		i = 0;
		cout << "digitChar=" << articleId << endl;
		
		cout << "line[0]=" << line[0] << endl;
		cout << "Novo vlizane;";
		while (line[i] >= '0' && line[i] <= '9') {
			 digit = digit*10 + line[i] - '0';
			 cout << endl;
			 cout << "line["<<i<<"]=" << line[i]<<endl;
			 cout << "digit=" << digit<<endl;
			 i++;
		}
		
		
		
		
		if (articleId == digit) {
			return true;
		}
		digit = 0;
	}


	file.close();
	return false;
}


void entryTitles() {
	cout << endl;
	
	cout << "    WELCOME TO"<<endl;
	cout << "    RESTAURANT SOFTWARE " << endl;
	cout << endl;

}

int main()
{
	int orders[MAX_SIZE_CHAR_ARRAY];
	char typeOfWorker;// = getTypeOfWorker();

	char product[MAX_SIZE_CHAR_ARRAY];
	int action;
	char ordersFromFile[MAX_SIZE_CHAR_ARRAY];
	char completеОrder[MAX_SIZE_CHAR_ARRAY];
	char date[] = "01/01/2025";

	entryTitles();
	cout << "Enter your type of hierarchy:";
	cin >> typeOfWorker;

	while (typeOfWorker != 'w' && typeOfWorker != 'm') {
		cout << "You have to enter your type of hierarchy(Waiter - w; Manager - m):";
		cin >> typeOfWorker;

		cin.ignore();
	}


	if (typeOfWorker == 'w') {
		cout << endl;
		cout << WAITER_MENU_OPTIONS << endl;
		cout << endl;

		do {
			
			cout << "What you want to choose from above:";
			cin >> action;

			if (action == 1) {
				readFromMenuFile();
			}
			else if (action == 2) {
				int articleId;
			

				int countArticleInOrders = 0;
				bool isExistArticleInMenu;
				do {
					cout << endl;
					
					cout << "Now you can make order from the menu (if you want to finish order, enter 0(zero):"<<endl;
					
					cin >> articleId;
					if (articleId == 0) {
						break;
					}

					isExistArticleInMenu = isExistArticle(articleId);
					if (isExistArticleInMenu) {
						cout << "Article is CONTAINED" << endl;
						orders[countArticleInOrders] = articleId;
						countArticleInOrders++;
					}
					else {
						cout << "Article is NOT CONTAINED" << endl;
					}
					

				} while (isExistArticleInMenu != false);

				if (isExistArticleInMenu == false) {
					countArticleInOrders = 0;
				}

				cout << "countArticleInOrders="<< countArticleInOrders;
				cout << endl;

				int dateLength = textLength(date);
				
				cout << "dateLength=" << dateLength<<endl;
				for (int i = 0; i < dateLength; i++) {
					completеОrder[i] = date[i];
					cout << completеОrder[i];
				}
				cout << endl;
				//completеОrder[dateLength] = ';';
				///*dateLength++;*/
				int indexForOrder = dateLength;
				
				for (int j = 0; j < countArticleInOrders; j++) {
					cout << orders[j] << endl;
					completеОrder[indexForOrder++] = ';';

					if (orders[j]>=0 && orders[j]<=9) {
						completеОrder[indexForOrder++] = orders[j] + '0';
					}else if (orders[j] >= 10) {

						int numDigits = (int)log10(orders[j]) + 1;
						cout << "numDigits=" << numDigits<<endl;
						for (int i = numDigits - 1 ; i >= 0; i--) {
							int digit = orders[j] % 10;
							cout << "Digit=" << digit << endl;
							completеОrder[indexForOrder + i] = digit + '0';
							orders[j] /= 10;
						}
						indexForOrder += numDigits;
					}
					
					
					cout << "completеОrder[dateLength + j]="<<completеОrder[dateLength + j]<<endl;
					
					
					cout << "completеОrder[dateLength + j + 1]=" << completеОrder[dateLength + j + 1]<<endl;
					
					
				}
				cout << endl;
				completеОrder[indexForOrder++] = '\n';
				completеОrder[indexForOrder] = '\0';
				cout << "CompleteOrder=" << completеОrder;
				writeInOrderFile(completеОrder);


			}
			else if (action == 3) {
				
			}
			else if (action == 4) {

			}
			else if (action == 5) {

			}
		} while (action >= 1 || action <= 5);

	}
	else if (typeOfWorker == 'm') {
		cout << MANAGER_MENU_OPTIONS << endl;
		cout << "Enter product:";
		cin.getline(product, MAX_SIZE_CHAR_ARRAY);

		cout << endl;



	}
}