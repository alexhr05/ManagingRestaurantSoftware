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

const char WAITER_MENU_OPTIONS[] = "1. Overview of the menu\n2. Make Order\n3. Order cancellation\n4. View past orders\n5. View past orders in alphabetical order as well as the number of orders of each item\n6. View the profits for the day";

const char MANAGER_MENU_OPTIONS[] = "1. Overview of the menu\n2. Make order\n3. Order cancellation\n4. View past orders in alphabetical order as well as the number of orders of each item\n5. View past orders\n6. Overview of what is left and of what\n7. Remove a product from warehouse\n8. Add a new product to the warehouse\n9. View the profits for the day\n10. Taking a report for the day\n11. Subtract all turnovers from a given date to now\n12. Adding a new product to the menu\n13. Remove a product from the menu";

const int BUFFER_SIZE = 1024;

const int MAX_SIZE_CHAR_ARRAY = 900;

const int DATE_LENGTH = 10;

struct Order {
	char articlesFromOrder[MAX_SIZE_CHAR_ARRAY];
	int countArticleForOrder = 0;
};

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

int searchPriceInMenu(int numberOrder) {
	ifstream in(MENU_FILE);
	if (!in.is_open()) {
		cout << "Error";
		return 0;
	}
	char line[MAX_SIZE_CHAR_ARRAY];
	int index = 0;
	int i = 0;
	int articleId = 0;
	int number = 0;
	int sumOfPrice = 0;

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
				number = number * 10 + (line[i] - '0');
				i++;
			}

			sumOfPrice += number;

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

int findPriceOfArticle(char* line) {
	int numberOrder = 0;
	int turnoverFromOrder = 0;
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
	int number = 0;

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
				number = number * 10 + (line[index] - '0');
				index++;
			}

			turnoverForToday += number;

		}
	}
	cout << "Turnover For Today: " << turnoverForToday / 100 << endl;

	in.close();
}

void AppendInWarehouseFile(char* text) {
	ofstream file(WAREHOUSE_FILE, ios::app);

	file << text;

	file.close();

}

void writeInWarehouseFile(char* text) {
	ofstream file(WAREHOUSE_FILE);

	file << text;

	file.close();

}

void appendInMenuFile(char* text) {
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

void writeInOrderMenu(char* text) {
	ofstream file(MENU_FILE);

	file << text;

	file.close();

}

void writeInTurnoverPerDayFile(char* updatedTurnover) {
	ofstream file(TURNOVER_PER_DAY_FILE);

	file << updatedTurnover;

	file.close();
}

void appendInTurnoverPerDayFile(char* updatedTurnover) {
	ofstream file(TURNOVER_PER_DAY_FILE, ios::app);
	cout << "conentFileFInalVersion=" << updatedTurnover << endl;
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

	int countToLastOrder = 0;
	int indexWithoutLastOrders = 0;
	char withoutLastOrders[MAX_SIZE_CHAR_ARRAY];

	while (countToLastOrder < (countRow - 1)) {

		if (orderFileContent[indexWithoutLastOrders] == '\n') {
			countToLastOrder++;
			withoutLastOrders[indexWithoutLastOrders] = orderFileContent[indexWithoutLastOrders];
		}
		withoutLastOrders[indexWithoutLastOrders] = orderFileContent[indexWithoutLastOrders];
		indexWithoutLastOrders++;
	}

	withoutLastOrders[indexWithoutLastOrders] = '\0';
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
	char* todayDate = new char[DATE_LENGTH + 1];
	const int numberMonths = 12;
	int index = 0;
	int month = getMonthOfDayFile();
	int zero = 0;
	int nine = 9;
	int ten = 10;
	int twelve = 12;
	int thirtyOne = 31;

	if (todayDay >= zero && todayDay <= nine) {
		units = todayDay + '0';
		todayDate[index++] = '0';
		todayDate[index++] = units;
	}
	else if (todayDay >= ten && todayDay <= thirtyOne) {
		units = todayDay % ten + '0';
		todayDay /= ten;
		dozens = todayDay % ten + '0';
		todayDate[index++] = dozens;
		todayDate[index++] = units;
	}
	todayDate[index++] = '/';
	if (month >= zero && month <= nine) {
		units = month + '0';
		todayDate[index++] = '0';
		todayDate[index++] = units;
	}
	else if (month >= ten && month <= twelve) {
		units = month % ten + '0';
		month /= ten;
		dozens = month % ten + '0';
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

	while (indexLine < counterNewLine) {

		while (contentFile[indexContentFile] != '\n') {
			indexContentFile++;
		}
		indexContentFile++;
		indexLine++;
	}
	return indexContentFile;
}

// Копира първоначлния масив от чарове и го прехъврля в другия масив
void strCopy(char* dest, char* src) {
	int index = 0;
	while (src[index] != '\0') {
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
}

int countDigits(int copyOfturnoverForToday) {
	int counter = 0;
	while (copyOfturnoverForToday != 0) {
		counter++;
		copyOfturnoverForToday /= 10;
	}
	return counter;
}

void reverseArray(char* charArray, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			int temp = charArray[j];
			charArray[j] = charArray[j + 1];
			charArray[j + 1] = temp;
		}
	}
}

void changeTurnoverForTodayInString(char* contentFile, int turnoverForToday, int indexLastLine) {
	//Конвертира число от float в int тип, като закгрълява до най-близкото цяло число
	// Измествам десетичната запетая надясно, за да направя цяло число

	int sizeNewTurnover = countDigits(turnoverForToday);
	char* newTurnover = new char[sizeNewTurnover + 1];
	int temporaryDigit = 0;
	int index = 0;

	while (turnoverForToday != 0) {
		temporaryDigit = turnoverForToday % 10;
		newTurnover[index++] = temporaryDigit + '0';
		turnoverForToday /= 10;
	}
	newTurnover[index] = '\0';
	/*cout << "newTurnover=" << newTurnover << endl;*/
	reverseArray(newTurnover, sizeNewTurnover);
	/*for (int i = 0; i < sizeNewTurnover - 1; i++) {
		for (int j = 0; j < sizeNewTurnover - i - 1; j++) {
			int temp = newTurnover[j];
			newTurnover[j] = newTurnover[j + 1];
			newTurnover[j + 1] = temp;
		}
	}*/

	index = 0;
	while (newTurnover[index] != '\0') {
		contentFile[indexLastLine++] = newTurnover[index++];
	}
	contentFile[indexLastLine] = '\0';

	writeInTurnoverPerDayFile(contentFile);
	delete[] newTurnover;
}


void addTurnoverForTodayInString(int sumPriceArticle) {
	int sizeNewTurnover = countDigits(sumPriceArticle);
	char* todayDateForFile = getTodayDate();
	char* newTurnover = new char[sizeNewTurnover + 1];
	int temporaryDigit = 0;
	int indexLineToAppend = 0;
	int index = 0;
	char* lineToAppend = new char[textLength(todayDateForFile) + sizeNewTurnover + 1];
	while (sumPriceArticle != 0) {
		temporaryDigit = sumPriceArticle % 10;
		newTurnover[index++] = temporaryDigit + '0';
		sumPriceArticle /= 10;
	}
	newTurnover[index] = '\0';

	reverseArray(newTurnover, sizeNewTurnover);

	index = 0;
	// Да запише реда на нов ред във файла
	cout << "todayDateForFile=" << todayDateForFile << endl;
	lineToAppend[indexLineToAppend++] = '\n';
	while (todayDateForFile[index] != '\0') {
		lineToAppend[indexLineToAppend] = todayDateForFile[index];
		indexLineToAppend++;
		index++;
	}
	index = 0;

	//Да добавя разделител
	lineToAppend[indexLineToAppend++] = ';';
	while (newTurnover[index] != '\0') {
		lineToAppend[indexLineToAppend] = newTurnover[index];
		index++;
		indexLineToAppend++;
	}
	lineToAppend[indexLineToAppend] = '\0';
	appendInTurnoverPerDayFile(lineToAppend);
	delete todayDateForFile;
	delete[] newTurnover;
}

void overwriteTodayTurnoverInFile(char* contentFile, int sumPriceArticle, int counterNewLine, bool isExistTodayDate) {
	int indexLastLine = getIndexLastLineForTurnover(contentFile, counterNewLine);
	// Прескачам дължината на датата, която е фиксирана и директно почвам да заменям стойността на предишния оборот
	indexLastLine = indexLastLine + DATE_LENGTH + 1;
	int index = 0;
	int dayOfDate = 0;
	char sumPrice[MAX_SIZE_CHAR_ARRAY];

	index = indexLastLine;
	int number = 0;
	int turnoverForToday = 0;
	while (contentFile[index] != '\n' && contentFile[index] != '\0') {
		if (contentFile[index] >= '0' && contentFile[index] <= '9') {
			number = number * 10 + (contentFile[index] - '0');
			index++;
		}

	}
	turnoverForToday += number;
	turnoverForToday += sumPriceArticle;
	if (isExistTodayDate) {
		changeTurnoverForTodayInString(contentFile, turnoverForToday, indexLastLine);
	}
	else {
		addTurnoverForTodayInString(sumPriceArticle);
	}

	cout << endl;
}

void updateTurnoverInFile(char* todayDate, int sumPriceArticle) {
	ifstream in(TURNOVER_PER_DAY_FILE);

	if (!in.is_open()) {
		cout << "Error";
		return;
	}

	char line[MAX_SIZE_CHAR_ARRAY];
	int indexContentFile = 0;
	int indexLine = 0;
	char contentFile[MAX_SIZE_CHAR_ARRAY];
	int todayDay = readFromTodayDateFile();

	int dayFromFile = 0;
	int index = 0;
	int counter = 0;
	int counterNewLine = 0;

	bool isExistTodayDate = false;
	bool isIndexOnDateDay = true;
	int indexLastLine;

	in.getline(contentFile, BUFFER_SIZE, '\0');
	while (contentFile[indexContentFile] != '\0') {
		if (isIndexOnDateDay) {
			dayFromFile = 0;
			while (contentFile[indexContentFile] >= '0' && contentFile[indexContentFile] <= '9')
			{
				dayFromFile = dayFromFile * 10 + (contentFile[indexContentFile] - '0');

				indexContentFile++;
			}
			isIndexOnDateDay = false;
		}

		if (todayDay == dayFromFile) {
			cout << "todayDay=" << todayDay << "; dayFromFile=" << dayFromFile << endl;
			isExistTodayDate = true;
		}

		if (contentFile[indexContentFile] == '\n') {
			isIndexOnDateDay = true;
			counterNewLine++;
		}

		indexContentFile++;
	}

	overwriteTodayTurnoverInFile(contentFile, sumPriceArticle, counterNewLine, isExistTodayDate);

	in.close();
}


int getLengthOfArticleNameFromMenu(int numberOrder) {
	ifstream in(MENU_FILE);
	if (!in.is_open()) {
		cout << "Error";

	}
	char line[MAX_SIZE_CHAR_ARRAY];
	int index = 0;
	int currentLengthArticleName = 0;
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
				currentLengthArticleName++;
				j++;
			}
			//За да се включи и дължината на терминиращата нула
			currentLengthArticleName++;


		}

		index = 0;
	}
	in.close();

	return currentLengthArticleName;
}


char* searchArticleNameInMenu(int numberOrder) {
	ifstream in(MENU_FILE);
	if (!in.is_open()) {
		cout << "Error";

	}
	char line[MAX_SIZE_CHAR_ARRAY];
	int index = 0;
	char* articleName = new char[getLengthOfArticleNameFromMenu(numberOrder)];
	int indexArticleName = 0;
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
				articleName[indexArticleName] = line[j];
				indexArticleName++;
				j++;
			}

		}

		index = 0;
	}
	in.close();
	articleName[indexArticleName] = '\0';
	return articleName;

}



int compareTwoOrders(char* order1, char* order2) {
	int index = 0;
	while (order1[index] != '\0' && order2[index] != '\0') {
		if (order1[index] < order2[index]) {
			return -1; // order1 e преди order2
		}
		else if (order1[index] > order2[index]) {
			return 1; // order1 е след order2
		}
		index++;
	}

	return 0;
}

void strCopy(char* destination, const char* original) {
	int i = 0;
	while (original[i] != '\0') {
		destination[i] = original[i];
		i++;
	}
	destination[i] = '\0';
}

void swapOrders(char* order1, char* order2) {
	char temp[MAX_SIZE_CHAR_ARRAY];
	strCopy(temp, order1);
	strCopy(order1, order2);
	strCopy(order2, temp);
}

void sortOrdersAlphabetical(Order orders[], int countOrders) {
	int sizeOrders = 0;
	/*bool isThereDifferenceInOrder = true;*/
	for (int i = 0; i < countOrders - 1; i++) {
		sizeOrders = textLength(orders[i].articlesFromOrder);
		int indexArticlesFromOrder = 0;
		if (compareTwoOrders(orders[i].articlesFromOrder, orders[i + 1].articlesFromOrder) == 1 || compareTwoOrders(orders[i].articlesFromOrder, orders[i + 1].articlesFromOrder) == 0) {
			swapOrders(orders[i].articlesFromOrder, orders[i + 1].articlesFromOrder);
		}
	}
	cout << "after swap" << endl;
	for (int i = 0; i < countOrders; i++) {
		cout << "order[" << i << "]=" << orders[i].articlesFromOrder << endl;
	}

}

int getCounterOfOrders() {
	ifstream in(ORDER_FILE);

	if (!in.is_open()) {
		cout << "Error";
	}
	char line[MAX_SIZE_CHAR_ARRAY];
	int index = 0;
	int counterNewLine = 0;
	in.getline(line, MAX_SIZE_CHAR_ARRAY, '\0');
	while (line[index] != '\0') {
		if (line[index] == '\n') {
			counterNewLine++;
		}
		index++;

	}
	in.close();
	counterNewLine++;
	return counterNewLine;
}

int getSizeOfArticleIdInOrderArray(int articleIdInOrder[]) {
	int index = 0;
	while (articleIdInOrder[index] != 0) {
		index++;
	}
	for (int i = 0; i < index; i++) {
		cout << articleIdInOrder[index] << endl;
	}

	return index;
}

int getSizeOfArticlesInOrder(int articleIdInOrder[]) {

	char line[MAX_SIZE_CHAR_ARRAY];
	int articleId = 0;
	int indexLine = 0;
	int sizeArticleIdInOrder = getSizeOfArticleIdInOrderArray(articleIdInOrder);
	int counter = 0;

	for (int i = 0; i < sizeArticleIdInOrder; i++) {
		ifstream in(MENU_FILE);

		if (!in.is_open()) {
			cout << "Error";

		}

		while (in.getline(line, MAX_SIZE_CHAR_ARRAY)) {
			indexLine = 0;
			articleId = 0;

			while (line[indexLine] >= '0' && line[indexLine] <= '9') {
				articleId = articleId * 10 + (line[indexLine] - '0');
				indexLine++;
			}
			if (articleIdInOrder[i] == articleId) {
				indexLine++;
				counter++;
				while (line[indexLine] != ';') {
					counter++;
					indexLine++;
				}
				break;
			}
		}
		in.close();
	}
	return counter;
}

char* getArticlesName(int articleIdInOrder[], int& countArticleOrder) {

	char line[MAX_SIZE_CHAR_ARRAY];
	char* allArticlesInOrder = new char[getSizeOfArticlesInOrder(articleIdInOrder) + 1];
	int articleId = 0;
	int indexLine = 0;
	int sizeArticleIdInOrder = getSizeOfArticleIdInOrderArray(articleIdInOrder);
	int indexAllArticlesInOrder = 0;
	int index = 0;

	for (int i = 0; i < sizeArticleIdInOrder; i++) {
		ifstream in(MENU_FILE);

		if (!in.is_open()) {
			cout << "Error";
		}
		while (in.getline(line, MAX_SIZE_CHAR_ARRAY)) {
			indexLine = 0;
			articleId = 0;

			while (line[indexLine] >= '0' && line[indexLine] <= '9') {
				articleId = articleId * 10 + (line[indexLine] - '0');
				indexLine++;
			}

			if (articleIdInOrder[i] == articleId) {
				indexLine++;
				while (line[indexLine] != ';') {
					allArticlesInOrder[index] = line[indexLine];
					index++;
					indexLine++;
				}
				allArticlesInOrder[index++] = ';';
				countArticleOrder += 1;
				break;
			}
		}
		in.close();
	}
	allArticlesInOrder[index] = '\0';

	return allArticlesInOrder;
}

void getNamesOfArticleAndSortOrders() {
	ifstream in(ORDER_FILE);

	if (!in.is_open()) {
		cout << "Error";
		return;
	}

	char line[MAX_SIZE_CHAR_ARRAY];
	int articleIdInOrders[MAX_SIZE_CHAR_ARRAY] = { 0 };
	int index = 0;
	int indexCurrentOrder = 0;
	int countOrders = getCounterOfOrders();
	Order* orders = new Order[countOrders];
	char* articlesName;

	while (in.getline(line, MAX_SIZE_CHAR_ARRAY)) {
		index = 0;

		for (int j = DATE_LENGTH + 1; j <= textLength(line); j++) {
			while (line[j] >= '0' && line[j] <= '9') {
				articleIdInOrders[index] = articleIdInOrders[index] * 10 + (line[j] - '0');
				j++;
			}
			index++;
		}

		articlesName = getArticlesName(articleIdInOrders, orders[indexCurrentOrder].countArticleForOrder);

		strCopy(orders[indexCurrentOrder].articlesFromOrder, articlesName);

		delete[] articlesName;

		for (int i = 0; i < index;i++) {
			articleIdInOrders[i] = 0;
		}

		indexCurrentOrder++;
	}

	sortOrdersAlphabetical(orders, countOrders);
	in.close();
	cout << "Alphabetical orders:" << endl;
	cout << endl;
	for (int i = 0; i < countOrders;i++) {
		cout << orders[i].articlesFromOrder << endl;
		cout << "Number of articles in Order:" << orders[i].countArticleForOrder << endl;
		cout << endl;

	}
}

void makeOrder() {
	int articleId;
	int countArticleInOrders = 0;
	int orders[MAX_SIZE_CHAR_ARRAY];
	bool isExistArticleInMenu;
	char completеОrder[MAX_SIZE_CHAR_ARRAY];
	char* todayDate = getTodayDate();
	int sumPriceArticle = 0;

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


	updateTurnoverInFile(todayDate, sumPriceArticle);


}

int findLastIdOfExistingArticleInMenu() {
	ifstream in(MENU_FILE);

	if (!in.is_open()) {
		cout << "Error";
	}
	char line[MAX_SIZE_CHAR_ARRAY];
	int index = 0;
	int articleId = 0;
	in.getline(line, MAX_SIZE_CHAR_ARRAY, '\0');
	while (line[index] != '\0') {
		if (line[index] == '\n') {
			articleId = 0;
			index++;
			while (line[index] >= '0' && line[index] <= '9') {
				articleId = articleId * 10 + (line[index] - '0');
				index++;
			}

		}
		index++;
	}

	in.close();
	return articleId;
}



void addNumberToCharArray(char* original, int number, int& index) {
	cout << endl;
	cout << endl;
	int counter = 0;
	int reversedNumber = 0;
	char numberInChar[MAX_SIZE_CHAR_ARRAY];
	int temp;
	int indexTemp = 0;
	while (number != 0) {
		temp = number % 10;
		numberInChar[indexTemp] = temp + '0';
		number /= 10;
		indexTemp++;
	}

	numberInChar[indexTemp] = '\0';
	reverseArray(numberInChar, textLength(numberInChar));

	int sizeNumberInChar = textLength(numberInChar);
	int sizeOriginal = textLength(original);
	for (int i = 0; i < sizeNumberInChar; i++)
	{
		original[index + i] = numberInChar[i];

	}
	index += sizeNumberInChar;
	original[index++] = ';';

	original[index] = '\0';
}

void addNewArticleNameToOrder(char* order, char* articleName, int& index) {
	int indexArticleName = 0;
	cout << "After articleName=" << articleName << endl;
	cout << "Order=" << order << endl;
	while (articleName[indexArticleName] != '\0') {
		order[index] = articleName[indexArticleName];
		cout << "articleName[" << indexArticleName << "]=" << articleName[indexArticleName] << endl;
		cout << "order[" << index << "]=" << order[index] << endl;
		index++;
		indexArticleName++;
	}
	order[index++] = ';';
	order[index] = '\0';
}

void addNewArticleToMenu() {
	char aritcleName[MAX_SIZE_CHAR_ARRAY];
	float articlePrice;
	int articlePriceCastToInt = 0;
	int newArticleId = findLastIdOfExistingArticleInMenu() + 1;
	char newLineInMenu[MAX_SIZE_CHAR_ARRAY];
	int index = 0;
	char charVersionNewArticleId = 0;

	cout << "Enter the name of new article:";
	cin.getline(aritcleName, MAX_SIZE_CHAR_ARRAY);

	cout << "Enter the price of article:";
	cin >> articlePrice;
	articlePriceCastToInt = articlePrice * 100;

	newLineInMenu[index++] = '\n';
	addNumberToCharArray(newLineInMenu, newArticleId, index);

	addNewArticleNameToOrder(newLineInMenu, aritcleName, index);
	index = textLength(newLineInMenu);

	addNumberToCharArray(newLineInMenu, articlePriceCastToInt, index);

	appendInMenuFile(newLineInMenu);
}

void removeArticleFromMenu() {
	ifstream in(MENU_FILE);

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

	int countToLastArticle = 0;
	int indexWithoutLastOrders = 0;
	char withoutLastArticle[MAX_SIZE_CHAR_ARRAY];

	while (countToLastArticle < (countRow - 1)) {

		if (orderFileContent[indexWithoutLastOrders] == '\n') {
			countToLastArticle++;
			withoutLastArticle[indexWithoutLastOrders] = orderFileContent[indexWithoutLastOrders];
		}
		withoutLastArticle[indexWithoutLastOrders] = orderFileContent[indexWithoutLastOrders];
		indexWithoutLastOrders++;
	}

	withoutLastArticle[indexWithoutLastOrders - 1] = '\0';
	writeInOrderMenu(withoutLastArticle);

	cout << "Remove article succesfully!" << endl;

	in.close();
}

void seeWhatLeftsInWarehouse() {
	ifstream in(WAREHOUSE_FILE);

	if (!in.is_open()) {
		cout << "Error";
	}

	char contentFile[MAX_SIZE_CHAR_ARRAY];

	in.getline(contentFile, MAX_SIZE_CHAR_ARRAY, '\0');

	cout << "Product name | Left in grams" << endl;
	cout << contentFile;

	in.close();
}

void addNewElementsToCharArray(char* destination, char* source) {
	int index = 0;
	int sizeDestination = textLength(destination);
	cout << endl;
	cout << endl;
	cout << "sizeDestination=" << sizeDestination << endl;
	while (source[index] != '\0') {
		destination[sizeDestination] = source[index];
		cout << "source["<<index<<"]=" << source[index] << endl;
		cout << "destination["<<sizeDestination<<"]=" << destination[sizeDestination] << endl;
		sizeDestination++;
		index++;
	}
	destination[sizeDestination] = '\0';
	cout << "destination=" << destination << endl;
}

void addNumbersCorrectlyToCharArray(char* destination, int number) {
	int temp;
	int index = 0;
	while (number != 0) {
		temp = number % 10;
		destination[index] = temp + '0';
		number /= 10;
		index++;
	}
	destination[index] = '\0';
	reverseArray(destination, textLength(destination));
}

void addNewProductToWarehouse() {
	ifstream in(WAREHOUSE_FILE);

	if (!in.is_open()) {
		cout << "Error";
	}

	char contentFile[MAX_SIZE_CHAR_ARRAY];

	char newLineInWarehouse[MAX_SIZE_CHAR_ARRAY];
	char product[MAX_SIZE_CHAR_ARRAY];
	int grams;
	int index = 0;
	int sizeNewLineInWarehouse = 0;
	char gramsInCharArray[MAX_SIZE_CHAR_ARRAY];
	cout << "Enter name of new product:";
	cin >> product;

	cout << "Enter quantity of this product (in grams):";
	cin >> grams;
	newLineInWarehouse[index++] = '\n';
	newLineInWarehouse[index] = '\0';
	addNewElementsToCharArray(newLineInWarehouse, product);
	sizeNewLineInWarehouse = textLength(newLineInWarehouse);

	newLineInWarehouse[sizeNewLineInWarehouse++] = ';';
	newLineInWarehouse[sizeNewLineInWarehouse] = '\0';

	addNumbersCorrectlyToCharArray(gramsInCharArray, grams);

	addNewElementsToCharArray(newLineInWarehouse, gramsInCharArray);

	sizeNewLineInWarehouse = textLength(newLineInWarehouse);
	newLineInWarehouse[sizeNewLineInWarehouse] = '\0';

	in.close();
	AppendInWarehouseFile(newLineInWarehouse);
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
				getNamesOfArticleAndSortOrders();
			}
			else if (action == 6) {
				showTurnoverForToday();
			}
		} while (action >= 1 || action <= 6);

	}
	else if (typeOfWorker == 'm') {
		cout << endl;
		cout << MANAGER_MENU_OPTIONS << endl;
		cout << endl;

		do {

			cout << "What you want to choose from above:";
			cin >> action;
			cin.ignore();
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
				seeWhatLeftsInWarehouse();
			}
			else if (action == 7) {

			}
			else if (action == 8) {
				addNewProductToWarehouse();
			}
			else if (action == 9) {

			}
			else if (action == 10) {

			}
			else if (action == 11) {


			}
			else if (action == 12) {
				addNewArticleToMenu();
			}
			else if (action == 13) {
				removeArticleFromMenu();
			}
		} while (action >= 1 || action <= 6);


		cout << endl;



	}
}
