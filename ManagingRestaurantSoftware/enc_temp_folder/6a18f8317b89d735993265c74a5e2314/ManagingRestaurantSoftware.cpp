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

const char TODAY_DATE_FILE[] = "todayDate.txt";

const char TURNOVER_PER_DAY_FILE[] = "turnoverPerDay.txt";

const char WAITER_MENU_OPTIONS[] = "1. Overview of the menu\n2. View order\n3. Order cancellation\n4. View past orders\n5. View past orders in alphabetical order as well as the number of orders of each item\n6. View the profits for the day";

const char MANAGER_MENU_OPTIONS[] = "1. Overview of the menu\n2. View order\n3. Order cancellation\n4. View past orders in alphabetical order as well as the number of orders of each item\n5. View past orders\n6. Overview of what is left and of what\n7. Remove a product from warehouse\n8. Add a new product to the warehouse\n9. View the profits for the day\n10. Taking a report for the day\n11. Subtract all turnovers from a given date to now\n12. Adding a new product to the menu\n13. Remove a product from the menu";

const int BUFFER_SIZE = 1024;

const int MAX_SIZE_CHAR_ARRAY = 1024;

const int DATE_LENGTH = 10;

enum workersType {
	WAITER = 'w',
	MANAGER = 'm'
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
		cout << "isContain:" << searchSubString(line, sub) << endl;
	}
	cout << endl;

	in.close();
}

int readFromTodayDateFile() {
	ifstream in(TODAY_DATE_FILE);

	if (!in.is_open()) {
		cout << "Error";
		return 0;
	}

	char line[MAX_SIZE_CHAR_ARRAY];
	int day = 0;
	int index = 0;
	//Взима единствения елемент на файла, който е просто ден
	in.getline(line, BUFFER_SIZE);

	while (line[index] >= '0' && line[index] <= '9') {
		day = day * 10 + (line[index] - '0');
		index++;
	}
	cout << "day=" << day << endl;
	in.close();

	return day;
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
		cout << line << endl;
	}

	in.close();
}


void searchArticleInMenu(int numberOrder) {
	ifstream in(MENU_FILE);
	if (!in.is_open()) {
		cout << "Error";
		return;
	}
	char line[MAX_SIZE_CHAR_ARRAY];
	int index = 0;
	while (in.getline(line, BUFFER_SIZE)) {
		int i = 0;
		int articleId = 0;

		while (line[i] >= '0' && line[i] <= '9') {
			articleId = articleId * 10 + (line[i] - '0');
			i++;
		}
		if (articleId == numberOrder) {
			// Това е за да може да започне директно да чете от името на артикула във файла, заради синтаксиса на файла
			int j = i + 1;
			while (line[j] != ';') {
				cout << line[j];
				j++;
			}

		}

		index = 0;
	}
	in.close();
}

void findNameOfArticleInMenu(char* line) {
	int numberOrder = 0;

	// +1 е, за да пропусне символа точкаи запетая и да почне да чете директно от поръчка номерата на артикулите
	for (int j = DATE_LENGTH + 1; j <= textLength(line); j++) {

		while (line[j] >= '0' && line[j] <= '9') {
			numberOrder = numberOrder * 10 + (line[j] - '0');
			j++;
		}

		if (line[j] == ';') {
			searchArticleInMenu(numberOrder);
			cout << ", ";
			numberOrder = 0;
		}

	}

	cout << endl;

}


float searchPriceInMenu(int numberOrder) {
	ifstream in(MENU_FILE);
	if (!in.is_open()) {
		cout << "Error";
		return 0;
	}
	char line[MAX_SIZE_CHAR_ARRAY];
	int index = 0;
	int i = 0;
	int articleId = 0;
	float wholeNumberPart = 0;
	float fractionalNumberPart = 0;
	float sumOfPrice = 0;

	while (in.getline(line, BUFFER_SIZE)) {
		i = 0;
		articleId = 0;

		while (line[i] >= '0' && line[i] <= '9') {
			articleId = articleId * 10 + (line[i] - '0');
			i++;
		}
		if (articleId == numberOrder) {
			cout << "articleId=" << articleId << endl;
			// Това е за да може да започне директно да чете от името на артикула във файла, заради синтаксиса на файла
			while (line[i] < '0' || line[i] > '9') {
				i++;
			}

			while (line[i] >= '0' && line[i] <= '9') {
				wholeNumberPart = wholeNumberPart * 10 + (line[i] - '0');
				i++;
			}

			//За да прескочим точката в цената и да отида диркетно на дробната част от числото
			i++;
			fractionalNumberPart = (line[i] - '0') * 10 + (line[i + 1] - '0');

			sumOfPrice = wholeNumberPart + (fractionalNumberPart / 100);

			/*cout << "sumOfPrice=" << sumOfPrice << endl;
			cout << "wholeNumberPart=" << wholeNumberPart << endl;
			cout << "line[i] and line[i+1]=" << line[i];*/
			/*cout << line[i+1] << endl;*/

		}

		index = 0;
	}
	in.close();
	return sumOfPrice;
}

float findPriceOfArticle(char* line) {
	int numberOrder = 0;
	float turnoverFromOrder = 0;
	// +1 е, за да пропусне символа точкаи запетая и да почне да чете директно от поръчка номерата на артикулите
	for (int j = DATE_LENGTH + 1; j <= textLength(line); j++) {

		while (line[j] >= '0' && line[j] <= '9') {
			numberOrder = numberOrder * 10 + (line[j] - '0');
			j++;
		}

		if (line[j] == ';') {
			turnoverFromOrder += searchPriceInMenu(numberOrder);
			numberOrder = 0;
		}

	}

	cout << endl;

	return turnoverFromOrder;

}

//void showTurnoverFromToday() {
//	ifstream in(ORDER_FILE);
//
//	if (!in.is_open()) {
//		cout << "Error";
//	}
//
//	char line[MAX_SIZE_CHAR_ARRAY];
//	int index = 0;
//	int counter = 1;
//	int todayDay = readFromTodayDateFile();
//	int dayFromDate = 0;
//	float finalTurnOverForToday = 0;
//
//	while (in.getline(line, BUFFER_SIZE)) {
//		dayFromDate = 0;
//		index = 0;
//		while (line[index] >= '0' && line[index] <= '9') {
//			dayFromDate = dayFromDate * 10 + (line[index] - '0');
//			cout << line[index] << endl;
//			index++;
//		}
//		if (dayFromDate == todayDay) {
//			finalTurnOverForToday += findPriceOfArticle(line);
//		}
//	}
//		cout << "TurnOver for Today(" << todayDay << "): " << finalTurnOverForToday << endl;
//	in.close();
//
//}




void showOrders() {
	ifstream in(ORDER_FILE);

	if (!in.is_open()) {
		cout << "Error";
	}
	char line[MAX_SIZE_CHAR_ARRAY];
	int index = 0;
	int counter = 1;


	while (in.getline(line, BUFFER_SIZE)) {
		cout << (counter++) << " - " << line;
		cout << "  -  ";

		findNameOfArticleInMenu(line);
	}
	in.close();
}

void showTurnoverForToday() {
	ifstream in(TURNOVER_PER_DAY_FILE);

	if (!in.is_open()) {
		cout << "Error";
	}
	int todayDay = readFromTodayDateFile();
	char line[MAX_SIZE_CHAR_ARRAY];
	int dayFromDate;
	int index = 0;
	float turnoverForToday = 0;
	int wholePartNumber = 0;
	float fractionalNumberPart = 0;

	while (in.getline(line, BUFFER_SIZE)) {
		dayFromDate = 0;
		index = 0;
		while (line[index] >= '0' && line[index] <= '9')
		{
			dayFromDate = dayFromDate * 10 + (line[index] - '0');
			index++;
		}
		if (dayFromDate == todayDay) {
			while (line[index] != ';') {
				index++;
			}
			index++;
			while (line[index] >= '0' && line[index] <= '9') {
				wholePartNumber = wholePartNumber * 10 + (line[index] - '0');
				index++;
			}
			if (line[index] == '.') {
				index++;
				while (line[index] >= '0' && line[index] <= '9') {
					fractionalNumberPart = fractionalNumberPart * 10 + (line[index] - '0');
					index++;
				}
			}
			turnoverForToday += wholePartNumber + (fractionalNumberPart / 100);

		}
	}
	cout << "Turnover For Today: " << turnoverForToday << endl;

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

void writeInOrderFileAppend(char* text) {
	ofstream file(ORDER_FILE, ios::app);

	file << text;

	file.close();

}

void writeInOrderFile(char* text) {
	ofstream file(ORDER_FILE);

	file << text;

	file.close();

}

void writeInTurnoverPerDayFile(char* updatedTurnover) {
	ofstream file(ORDER_FILE, ios::app);

	file << updatedTurnover;

	file.close();

}

void orderCancellation() {
	ifstream in(ORDER_FILE);

	if (!in.is_open()) {
		cout << "Error";
	}
	char line[MAX_SIZE_CHAR_ARRAY];
	char orderFileContent[MAX_SIZE_CHAR_ARRAY];
	int countRow = 0;
	int index = 0;
	while (in.getline(line, MAX_SIZE_CHAR_ARRAY)) {
		for (int i = 0; i < textLength(line); i++) {
			orderFileContent[index++] = line[i];
		}
		orderFileContent[index++] = '\n';
		countRow++;
	}
	orderFileContent[index] = '\0';
	//cout << "orderFileContent="<<orderFileContent << endl;

	int countToLastOrder = 0;
	int indexWithoutLastOrders = 0;
	char withoutLastOrders[MAX_SIZE_CHAR_ARRAY];

	while (countToLastOrder < (countRow - 1)) {
		//cout << "orderFileContent="<< countToLastOrder << endl;
		//cout << "countRow=" << countRow << endl;

		if (orderFileContent[indexWithoutLastOrders] == '\n') {
			countToLastOrder++;
			withoutLastOrders[indexWithoutLastOrders] = orderFileContent[indexWithoutLastOrders];
		}
		withoutLastOrders[indexWithoutLastOrders] = orderFileContent[indexWithoutLastOrders];
		indexWithoutLastOrders++;
	}

	withoutLastOrders[indexWithoutLastOrders] = '\0';
	/*cout << "withoutLastOrders=" << withoutLastOrders << endl;*/
	writeInOrderFile(withoutLastOrders);

	cout << "Cancel succesfully!!!";

	in.close();
}

void showDetailedOrder() {
	showOrders();

	cout << endl;

}

bool isExistArticle(int articleId) {
	ifstream file(MENU_FILE);
	char line[BUFFER_SIZE];

	if (!file.is_open()) {
		cout << "Error";

	}
	int i;
	int digit = 0;
	while (file.getline(line, BUFFER_SIZE)) {
		i = 0;
		while (line[i] >= '0' && line[i] <= '9') {
			digit = digit * 10 + (line[i] - '0');
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

int getMonthOfDayFile() {
	int month;
	const int numberMonths = 12;
	int todayDay = readFromTodayDateFile();
	int monthsWithDays[numberMonths] = { 31,28,31,30,31, 30,31,31,30,31,30,31 };
	int index = 0;
	int copyOfTodayDay = todayDay;
	while (copyOfTodayDay >= 0) {
		copyOfTodayDay -= monthsWithDays[index++];
	}
	month = index;
	return month;
}


char* getTodayDate() {
	int todayDay = readFromTodayDateFile();
	char dozens;
	char units;
	char* todayDate = new char[DATE_LENGTH];
	const int numberMonths = 12;
	int index = 0;
	int month = getMonthOfDayFile();
	if (todayDay >= 0 && todayDay <= 9) {
		units = todayDay + '0';
		todayDate[index++] = '0';
		todayDate[index++] = units;
	}
	else if (todayDay >= 10 && todayDay <= 12) {
		units = todayDay % 10 + '0';
		todayDay /= 10;
		dozens = todayDay % 10;
		todayDate[index++] = dozens;
		todayDate[index++] = units;
	}
	todayDate[index++] = '/';
	if (month >= 0 && month <= 9) {
		units = month + '0';
		todayDate[index++] = '0';
		todayDate[index++] = units;
	}
	else if (month >= 10 && month <= 12) {
		units = month % 10 + '0';
		month /= 10;
		dozens = month % 10;
		todayDate[index++] = dozens;
		todayDate[index++] = units;
	}
	todayDate[index++] = '/';
	todayDate[index++] = '2';
	todayDate[index++] = '0';
	todayDate[index++] = '2';
	todayDate[index++] = '5';
	todayDate[index] = '\0';

	return todayDate;
}

int getIndexLastLineForTurnover(char* contentFile, int counterNewLine) {
	int indexLine = 0;
	int indexContentFile = 0;

	while (indexLine <= counterNewLine) {
		while (contentFile[indexContentFile] != '\n') {
			indexContentFile++;
		}
		indexLine++;
	}
	return indexContentFile;
}


void updateTurnoverInFile(char* todayDate, float sumPriceArticle) {
	ifstream in(TURNOVER_PER_DAY_FILE);

	if (!in.is_open()) {
		cout << "Error";
		return;
	}
	cout << "sumPriceArticle=" << sumPriceArticle << endl;

	char line[MAX_SIZE_CHAR_ARRAY];
	int indexContentFile = 0;
	int indexLine = 0;
	char contentFile[MAX_SIZE_CHAR_ARRAY];
	int todayDay = readFromTodayDateFile();
	
	int dayFromFile = 0;
	int index = 0;
	int counter = 0;
	int counterNewLine = 0;
	char* todayDateForFile = getTodayDate();
	bool isExistTodayDate = false;
	cout << endl;
	while (in.getline(line, BUFFER_SIZE)) {
		indexLine = 0;
		while (line[indexLine]) {
			contentFile[indexContentFile++] = line[indexLine++];
			cout << contentFile[indexContentFile];
		}
		contentFile[indexContentFile++] = '\n';
		cout << endl;

		while (line[counter] >= '0' && line[counter] <= '9')
		{
			dayFromFile = dayFromFile * 10 + (line[counter] - '0');
			counter++;
		}
		if (todayDay == dayFromFile) {
			isExistTodayDate = true;
		}
		counterNewLine++;

		counter = 0;

	}
	if (isExistTodayDate) {

		contentFile[indexContentFile] = '\0';
		int indexContentFile = getIndexLastLineForTurnover(contentFile, counterNewLine);
		// Прескачам дължината на датата, която е фиксирана и директно почвам да заменям стойността на предишния оборот
		indexContentFile += DATE_LENGTH;
		int index = 0;
		int dayOfDate = 0;
		char sumPrice[MAX_SIZE_CHAR_ARRAY];
		int copyOfSumPriceArticle = sumPriceArticle;

		int temporary = 0;
		while (copyOfSumPriceArticle != 0) {
			temporary = copyOfSumPriceArticle % 10;
			sumPrice[index++] = temporary - '0';
			copyOfSumPriceArticle /= 10;
		}
		sumPrice[index] = '\0';
		index = textLength(sumPrice);
		while (index >= 0) {
			contentFile[indexContentFile++] = sumPrice[index--];
		}
		contentFile[indexContentFile++] = '\n';
		contentFile[indexContentFile] = '\0';
		cout << "contentFile=" << contentFile << endl;
	}
	else {

	}
	/*writeInTurnoverPerDayFile(contentFile);*/
	delete[] todayDateForFile;
	in.close();
}



void makeOrder() {
	int articleId;
	int countArticleInOrders = 0;
	int orders[MAX_SIZE_CHAR_ARRAY];
	bool isExistArticleInMenu;
	char completеОrder[MAX_SIZE_CHAR_ARRAY];
	char* todayDate = getTodayDate();
	float sumPriceArticle = 0;

	do {
		cout << endl;

		cout << "Now you can make order from the menu (if you want to finish order, enter 0(zero):" << endl;

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

	cout << "countArticleInOrders=" << countArticleInOrders;
	cout << endl;

	for (int i = 0; i < DATE_LENGTH; i++) {
		completеОrder[i] = todayDate[i];
		cout << completеОrder[i];
	}
	cout << endl;
	int indexForOrder = DATE_LENGTH;

	completеОrder[indexForOrder++] = ';';
	for (int j = 0; j < countArticleInOrders; j++) {
		cout << orders[j] << endl;


		if (orders[j] >= 0 && orders[j] <= 9) {
			completеОrder[indexForOrder++] = orders[j] + '0';
			sumPriceArticle += searchPriceInMenu(orders[j]);
		}
		else if (orders[j] >= 10)
		{
			sumPriceArticle += searchPriceInMenu(orders[j]);
			int numDigits = (int)log10(orders[j]) + 1;
			for (int i = numDigits - 1; i >= 0; i--)
			{
				int digit = orders[j] % 10;
				completеОrder[indexForOrder + i] = digit + '0';
				orders[j] /= 10;
			}
			indexForOrder += numDigits;
		}
		completеОrder[indexForOrder++] = ';';

	}
	cout << endl;
	completеОrder[indexForOrder++] = '\n';
	completеОrder[indexForOrder] = '\0';
	cout << "CompleteOrder=" << completеОrder;
	/*writeInOrderFile(completеОrder);*/
	
	updateTurnoverInFile(todayDate, sumPriceArticle);

	/*delete[] todayDate;*/
}

void entryTitles() {
	cout << endl;

	cout << "    WELCOME TO" << endl;
	cout << "    RESTAURANT SOFTWARE " << endl;
	cout << endl;

}

int main()
{

	char typeOfWorker;// = getTypeOfWorker();

	char product[MAX_SIZE_CHAR_ARRAY];
	int action;
	char ordersFromFile[MAX_SIZE_CHAR_ARRAY];


	entryTitles();
	cout << "Enter your type of hierarchy:";
	cin >> typeOfWorker;

	while (typeOfWorker != WAITER && typeOfWorker != MANAGER) {
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
				makeOrder();



			}
			else if (action == 3) {
				orderCancellation();
			}
			else if (action == 4) {
				showDetailedOrder();
			}
			else if (action == 5) {

			}
			else if (action == 6) {
				showTurnoverForToday();
			}
		} while (action >= 1 || action <= 6);

	}
	else if (typeOfWorker == 'm') {
		cout << MANAGER_MENU_OPTIONS << endl;
		cout << "Enter product:";
		cin.getline(product, MAX_SIZE_CHAR_ARRAY);

		cout << endl;



	}
}