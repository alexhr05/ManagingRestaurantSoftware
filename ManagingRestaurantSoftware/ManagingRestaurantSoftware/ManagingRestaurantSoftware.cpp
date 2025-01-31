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

const char RECIPES_FILE[] = "recipes.txt";

const char WAITER_MENU_OPTIONS[] = "1. Overview of the menu\n2. Make Order\n3. Order cancellation\n4. View past orders\n5.View past orders in alphabetical order as well as the number of orders of each item\n6.View the profits for the day\n7.See all your options";

const char MANAGER_MENU_OPTIONS[] = "1. Overview of the menu\n2. Make order\n3. Order cancellation\n4. View past orders in alphabetical order as well as the number of orders of each item\n5. View past orders\n6. Overview of what is left and of what\n7. Remove a product from warehouse\n8. Add a new product to the warehouse\n9. View the profits for the day\n10. Taking a report for the day\n11. Adding a new product to the menu\n12. Remove a product from the menu\n13.See all your options";

const int BUFFER_SIZE = 1024;

const int MAX_SIZE_CHAR_ARRAY = 900;

const int DATE_LENGTH = 10;

const int digitsInDate = 3;

struct Order {
	char articlesFromOrder[MAX_SIZE_CHAR_ARRAY];
	int countArticleForOrder = 0;
};

enum workersType {
	WAITER = 'w',
	MANAGER = 'm'
};

//Връща дължината на подадения му char масив
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
	cout << endl;
	cout << "MENU:" << endl;
	char line[MAX_SIZE_CHAR_ARRAY];

	while (in.getline(line, BUFFER_SIZE)) {
		cout << line << endl;
	}
	cout << endl;

	in.close();
}

//Взима деня от файла с текущата дата
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

//Търси опрделен артикул чрез Id-то му
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


//Намира името на артикул в менюто и го записва в масива line
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

//Търси цената на определен артикул в менюто
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
			// Това е за да може да започне директно да чете от името на артикула във файла, заради синтаксиса на файла
			while (line[i] < '0' || line[i] > '9') {
				i++;
			}
			while (line[i] >= '0' && line[i] <= '9') {
				number = number * 10 + (line[i] - '0');
				i++;
			}

			sumOfPrice += number;

		}

		index = 0;
	}
	in.close();
	return sumOfPrice;
}

// Показва всички поръчки от файла
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
		// Замества Id-то на артикула в поръчки с името му от менюто
		findNameOfArticleInMenu(line);
	}
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

void writeIntodayDateFile(char* text) {
	ofstream file(TODAY_DATE_FILE);

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

	file << updatedTurnover;

	file.close();

}


// Отменя поръчка, ако не съществува даден артикул въвден от потребителя
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

	withoutLastOrders[indexWithoutLastOrders - 1] = '\0';
	writeInOrderFile(withoutLastOrders);

	cout << "Cancel succesfully!" << endl;

	in.close();
}

void showDetailedOrder() {
	showOrders();
	cout << endl;
}

//Проверява дали съществува даден артикул 
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

// Преобразува деня, който сме запазили във файла с дата в текущия ден
int getDayOfDayFile(int todayDay) {
	int index = 0;
	const int numberMonths = 12;
	int monthsWithDays[numberMonths] = { 31,28,31,30,31, 30,31,31,30,31,30,31 };
	int copyOfTodayDay = todayDay;
	while (todayDay >= 0) {
		todayDay -= monthsWithDays[index++];
	}
	todayDay += monthsWithDays[--index];

	return todayDay;
}

// Преобразува деня, който сме запазили във файла с дата в текущия месец
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

// Образува цялостната текуща дата във формата dd/mm/yyyy
char* getTodayDate() {
	int todayDay = readFromTodayDateFile();
	char* todayDate = new char[DATE_LENGTH + 1];
	const int numberMonths = 12;
	int index = 0;
	int month = getMonthOfDayFile();
	int zero = 0;
	int nine = 9;
	char units;
	char dozens;
	int ten = 10;
	int twelve = 12;
	int thirtyOne = 31;
	int dayFromTodayDate = getDayOfDayFile(todayDay);

	if (dayFromTodayDate >= zero && dayFromTodayDate <= nine) {
		units = dayFromTodayDate + '0';
		todayDate[index++] = '0';
		todayDate[index++] = units;
	}
	else if (dayFromTodayDate >= ten && dayFromTodayDate <= thirtyOne) {
		units = dayFromTodayDate % ten + '0';
		dayFromTodayDate /= ten;
		dozens = dayFromTodayDate % ten + '0';
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

// Взима индекса на последния записан ред във файла с оборота
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

// Брои цифрите на число
int countDigits(int copyOfturnoverForToday) {
	int counter = 0;
	while (copyOfturnoverForToday != 0) {
		counter++;
		copyOfturnoverForToday /= 10;
	}
	return counter;
}

// Обръща реда на char масива
void reverseArray(char* charArray, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			int temp = charArray[j];
			charArray[j] = charArray[j + 1];
			charArray[j + 1] = temp;
		}
	}
}

// Обновява оборота за деня, ако съществува запис за текущата дата какъв е оборота
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
	reverseArray(newTurnover, sizeNewTurnover);

	index = 0;
	while (newTurnover[index] != '\0') {
		contentFile[indexLastLine++] = newTurnover[index++];
	}
	contentFile[indexLastLine] = '\0';

	writeInTurnoverPerDayFile(contentFile);
	delete[] newTurnover;
}

// Ако не съществува запис във файла с оборота за деня, добавя нов ред с текущата дата и оборота за деня
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

// Фунцкия за сглобяване на оборота заденя и проверка дали съществува запис за текущия ден
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

// Преглежда файла с оборотите и гледа дали съществува текущата дата и отива в друга фунцкия
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
	int dayOfTodayDate = getDayOfDayFile(todayDay);
	int monthOfTodayDate = getMonthOfDayFile();
	int dayFromFile = 0;
	int monthFromFile = 0;
	int index = 0;
	int counter = 0;
	int counterNewLine = 0;

	bool isExistTodayDate = false;
	bool isIndexOnDateDay = true;

	in.getline(contentFile, BUFFER_SIZE, '\0');
	while (contentFile[indexContentFile] != '\0') {
		if (isIndexOnDateDay) {
			dayFromFile = 0;
			monthFromFile = 0;
			while (contentFile[indexContentFile] >= '0' && contentFile[indexContentFile] <= '9')
			{
				dayFromFile = dayFromFile * 10 + (contentFile[indexContentFile] - '0');

				indexContentFile++;
			}

			indexContentFile += 2;
			while (contentFile[indexContentFile] >= '0' && contentFile[indexContentFile] <= '9')
			{
				monthFromFile = monthFromFile * 10 + (contentFile[indexContentFile] - '0');

				indexContentFile++;
			}
			isIndexOnDateDay = false;
		}

		if (dayOfTodayDate == dayFromFile && monthOfTodayDate == monthFromFile) {
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

// Взима дължината на името на артикула
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

// Връща като char масив името на артикула от менюто
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

// Проверява дали order1 като поръчка е лексикографски по-голям или не от order2
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

// Копира char масив
void strCopy(char* destination, const char* original) {
	int i = 0;
	while (original[i] != '\0') {
		destination[i] = original[i];
		i++;
	}
	destination[i] = '\0';
}

// Сменя местата на char масиви 
void swapOrders(char* order1, char* order2) {
	char temp[MAX_SIZE_CHAR_ARRAY];
	strCopy(temp, order1);
	strCopy(order1, order2);
	strCopy(order2, temp);
}


void sortOrdersAlphabetical(Order orders[], int countOrders) {
	int sizeOrders = 0;
	for (int i = 0; i < countOrders - 1; i++) {
		sizeOrders = textLength(orders[i].articlesFromOrder);
		int indexArticlesFromOrder = 0;
		int temp;
		if (compareTwoOrders(orders[i].articlesFromOrder, orders[i + 1].articlesFromOrder) == 1 || compareTwoOrders(orders[i].articlesFromOrder, orders[i + 1].articlesFromOrder) == 0) {
			swapOrders(orders[i].articlesFromOrder, orders[i + 1].articlesFromOrder);
			temp = orders[i].countArticleForOrder;
			orders[i].countArticleForOrder = orders[i + 1].countArticleForOrder;
			orders[i + 1].countArticleForOrder = temp;
		}
	}


}

// Взима броя на поръчките
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

// Взима броя артикули в една поръчка, за да се създаде динамичен масив предварително
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

// Взима броя артикули в една поръчка
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

// Връща char масив от името на артикул
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

// Основната фунцкия за сортиране по азбучен ред
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

// Връща число, което е броя цифри в числото, което отговаря за количеството продукти
int getCountDigitsCurrentQuantityProduct(int currentQuantityProduct) {
	int counter = 0;
	while (currentQuantityProduct != 0) {
		currentQuantityProduct /= 10;
		counter++;
	}

	return counter++;
}

// Връща char масив от количеството на продукти
char* turningNumberInCharArray(int currentQuantityProduct) {
	int index = 0;
	int digit = 0;
	char* source = new char[getCountDigitsCurrentQuantityProduct(currentQuantityProduct) + 1];
	while (currentQuantityProduct != 0) {
		digit = currentQuantityProduct % 10;
		source[index] = digit + '0';
		currentQuantityProduct /= 10;
		index++;
	}
	source[index] = '\0';
	reverseArray(source, textLength(source));

	return source;
}

// Презаписва новата стойност за количество на продукт
void rewriteNewValueOfQuantity(char* contentFile, char* newQuantityInCharArray, char* oldQuantityInCharArray, int index) {
	index -= textLength(oldQuantityInCharArray);
	int indexForQuantityArray = 0;

	if (textLength(oldQuantityInCharArray) > textLength(newQuantityInCharArray)) {
		contentFile[index++] = '0';
	}
	while (contentFile[index] != '\n' && contentFile[index] != '\0') {
		contentFile[index] = newQuantityInCharArray[indexForQuantityArray];
		indexForQuantityArray++;
		index++;

	}
	writeInWarehouseFile(contentFile);

}

bool checkIsAvailableToChangeProductInWarehouse(int productId, int quantityProduct) {
	ifstream in(WAREHOUSE_FILE);

	if (!in.is_open()) {
		cout << "Error";
	}

	char contentFile[MAX_SIZE_CHAR_ARRAY];
	int index = 0;
	int currentIdProduct = 0;
	int currentQuantityProduct = 0;
	bool isIndexOnId = true;

	in.getline(contentFile, MAX_SIZE_CHAR_ARRAY, '\0');
	while (contentFile[index] != '\0') {
		if (isIndexOnId) {
			currentIdProduct = 0;
			while (contentFile[index] >= '0' && contentFile[index] <= '9') {
				currentIdProduct = currentIdProduct * 10 + contentFile[index] - '0';
				index++;
			}
			isIndexOnId = false;
		}

		if (currentIdProduct == productId) {
			//За да прескочи точката и запетая като символ
			index++;
			currentQuantityProduct = 0;
			while (contentFile[index] != ';') {
				index++;

			}
			index++;

			while (contentFile[index] >= '0' && contentFile[index] <= '9') {
				currentQuantityProduct = currentQuantityProduct * 10 + contentFile[index] - '0';
				index++;
			}

			//Намаляваме количеството на продукта
			currentQuantityProduct -= quantityProduct;
			if (currentQuantityProduct > 0) {
				return true;
			}
			else {
				return false;
			}


		}
		if (contentFile[index] == '\n') {
			isIndexOnId = true;

		}
		index++;

	}
	in.close();

}

// Обновява колко е останало от даден продукт като количество
void updateLeftProductInWaehouseFile(int productId, int quantityProduct) {
	ifstream in(WAREHOUSE_FILE);

	if (!in.is_open()) {
		cout << "Error";
		return;
	}

	char contentFile[MAX_SIZE_CHAR_ARRAY];
	char* oldQuantityInCharArray;
	char* newQuantityInCharArray;
	int index = 0;
	int currentIdProduct = 0;
	int currentQuantityProduct = 0;
	bool isIndexOnId = true;

	in.getline(contentFile, MAX_SIZE_CHAR_ARRAY, '\0');
	while (contentFile[index] != '\0') {
		if (isIndexOnId) {
			currentIdProduct = 0;
			while (contentFile[index] >= '0' && contentFile[index] <= '9') {
				currentIdProduct = currentIdProduct * 10 + contentFile[index] - '0';
				index++;
			}
			isIndexOnId = false;
		}
		if (currentIdProduct == productId) {
			//За да прескочи точката и запетая като символ
			index++;
			currentQuantityProduct = 0;
			while (contentFile[index] != ';') {
				index++;
			}
			index++;
			while (contentFile[index] >= '0' && contentFile[index] <= '9') {
				currentQuantityProduct = currentQuantityProduct * 10 + contentFile[index] - '0';
				index++;
			}
			oldQuantityInCharArray = turningNumberInCharArray(currentQuantityProduct);
			//Намаляваме количеството на продукта
			currentQuantityProduct -= quantityProduct;
			newQuantityInCharArray = turningNumberInCharArray(currentQuantityProduct);
			rewriteNewValueOfQuantity(contentFile, newQuantityInCharArray, oldQuantityInCharArray, index);
			delete[] newQuantityInCharArray;
			delete[] oldQuantityInCharArray;

		}
		if (contentFile[index] == '\n' || contentFile[index] == '\0') {
			isIndexOnId = true;
		}
		index++;

	}
	in.close();

}

// Проверява дали количеството в склада на даден продукт ще стане отрицателно или 0 и ако е така не се извършва поръчката
void isAvailableUpdateLeftProductInWaehouseFile(int productId, int quantityProduct, bool& isAvailableProducts) {
	ifstream in(WAREHOUSE_FILE);

	if (!in.is_open()) {
		cout << "Error";
		return;
	}

	char contentFile[MAX_SIZE_CHAR_ARRAY];
	int index = 0;
	int currentIdProduct = 0;
	int currentQuantityProduct = 0;
	bool isIndexOnId = true;

	in.getline(contentFile, MAX_SIZE_CHAR_ARRAY, '\0');
	while (contentFile[index] != '\0') {
		if (isIndexOnId) {
			currentIdProduct = 0;
			while (contentFile[index] >= '0' && contentFile[index] <= '9') {
				currentIdProduct = currentIdProduct * 10 + contentFile[index] - '0';
				index++;
			}
			isIndexOnId = false;
		}
		if (currentIdProduct == productId) {
			//За да прескочи точката и запетая като символ
			index++;
			currentQuantityProduct = 0;
			while (contentFile[index] != ';') {
				index++;

			}
			index++;

			while (contentFile[index] >= '0' && contentFile[index] <= '9') {
				currentQuantityProduct = currentQuantityProduct * 10 + contentFile[index] - '0';
				index++;
			}
			//Намаляваме количеството на продукта
			currentQuantityProduct -= quantityProduct;

			if (currentQuantityProduct <= 0) {
				isAvailableProducts = false;
				break;
			}
		}
		if (contentFile[index] == '\n' || contentFile[index] == '\0') {
			isIndexOnId = true;
		}
		index++;

	}
	in.close();
}


// Чете какво количество от даден продукт има в склада и неговото Id
void readRecipesFileAndUpdateProductQuantity(int orders[], int sizeArticleInOrders) {
	char line[MAX_SIZE_CHAR_ARRAY];
	int articleId = 0;
	int index = 0;
	int productId = 0;
	int quantityProduct = 0;

	for (int i = 0; i < sizeArticleInOrders;i++) {
		ifstream in(RECIPES_FILE);

		if (!in.is_open()) {
			cout << "Error";
			return;
		}
		while (in.getline(line, MAX_SIZE_CHAR_ARRAY)) {
			index = 0;
			productId = 0;
			quantityProduct = 0;
			articleId = 0;
			while (line[index] >= '0' && line[index] <= '9') {
				articleId = articleId * 10 + line[index] - '0';
				index++;
			}
			if (articleId == orders[i]) {
				//Прескача точка и запетая символа във файла
				index++;
				while (line[index] != ';') {
					index++;
				}
				index++;
				//Прескача точка и запетая символа във файла
				while (line[index] >= '0' && line[index] <= '9') {
					productId = productId * 10 + line[index] - '0';
					index++;
				}

				index++;
				//Прескача точка и запетая символа във файла
				while (line[index] >= '0' && line[index] <= '9') {
					quantityProduct = quantityProduct * 10 + line[index] - '0';
					index++;
				}
				updateLeftProductInWaehouseFile(productId, quantityProduct);
			}
		}
		in.close();
	}
}

// Чете какво количество от даден продукт има в склада и неговото Id
bool readRecipesFileAndCheckIsAvailableProductQuantity(int orders[], int sizeArticleInOrders) {
	char line[MAX_SIZE_CHAR_ARRAY];
	int articleId = 0;
	int index = 0;
	int productId = 0;
	int quantityProduct = 0;
	bool isAvailableProducts = true;

	for (int i = 0; i < sizeArticleInOrders;i++) {
		ifstream in(RECIPES_FILE);

		if (!in.is_open()) {
			cout << "Error";
		}
		while (in.getline(line, MAX_SIZE_CHAR_ARRAY)) {
			index = 0;
			productId = 0;
			quantityProduct = 0;
			articleId = 0;
			while (line[index] >= '0' && line[index] <= '9') {
				articleId = articleId * 10 + line[index] - '0';
				index++;
			}
			if (articleId == orders[i]) {
				//Прескача точка и запетая символа във файла
				index++;
				while (line[index] != ';') {
					index++;
				}
				index++;
				//Прескача точка и запетая символа във файла
				while (line[index] >= '0' && line[index] <= '9') {
					productId = productId * 10 + line[index] - '0';
					index++;
				}
				index++;
				//Прескача точка и запетая символа във файла
				while (line[index] >= '0' && line[index] <= '9') {
					quantityProduct = quantityProduct * 10 + line[index] - '0';
					index++;
				}
				isAvailableUpdateLeftProductInWaehouseFile(productId, quantityProduct, isAvailableProducts);

				if (isAvailableProducts != true) {
					break;
				}

			}
		}
		in.close();
	}
	return isAvailableProducts;
}

// Прави поръчка
void makeOrder() {
	int articleId;
	int countArticleInOrders = 0;
	int orders[MAX_SIZE_CHAR_ARRAY];
	bool isExistArticleInMenu;
	char completеОrder[MAX_SIZE_CHAR_ARRAY];
	char* todayDate = getTodayDate();
	int sumPriceArticle = 0;
	int indexForOrder = 0;
	int checkAvailabeProducts = 1;
	int updateLeftProducts = 2;;
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
	completеОrder[indexForOrder++] = '\n';
	for (int i = 0; i < DATE_LENGTH; i++) {
		completеОrder[indexForOrder++] = todayDate[i];
	}
	cout << endl;

	completеОrder[indexForOrder++] = ';';
	for (int j = 0; j < countArticleInOrders; j++) {
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
	completеОrder[indexForOrder] = '\0';

	if (readRecipesFileAndCheckIsAvailableProductQuantity(orders, countArticleInOrders)) {
		readRecipesFileAndUpdateProductQuantity(orders, countArticleInOrders);
		updateTurnoverInFile(todayDate, sumPriceArticle);
		writeInOrderFileAppend(completеОrder);
	}
	else {
		cout << "Cannot place order due to unavailability of products" << endl;
	}

}

// Намира последното Id на съществиващ артикул в менюто
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

// Добавя число към char масив
void addNumberToCharArray(char* original, int number, int& index) {
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


// Добавя име на артикул към поръчка
void addNewArticleNameToOrder(char* order, char* articleName, int& index) {
	int indexArticleName = 0;
	while (articleName[indexArticleName] != '\0') {
		order[index] = articleName[indexArticleName];
		index++;
		indexArticleName++;
	}
	order[index++] = ';';
	order[index] = '\0';
}


// Добавя нов артикул към менюто
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
	if (articlePrice > 0) {
		articlePriceCastToInt = articlePrice * 100;

		newLineInMenu[index++] = '\n';
		addNumberToCharArray(newLineInMenu, newArticleId, index);

		addNewArticleNameToOrder(newLineInMenu, aritcleName, index);
		index = textLength(newLineInMenu);

		addNumberToCharArray(newLineInMenu, articlePriceCastToInt, index);

		appendInMenuFile(newLineInMenu);
	}
	else {
		cout << "Incorrect input data!" << endl;
	}

}

//Изтрива артикул от менюто
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

// Изписва какво е останало в склада
void seeWhatLeftsInWarehouse() {
	ifstream in(WAREHOUSE_FILE);

	if (!in.is_open()) {
		cout << "Error";
	}

	char contentFile[MAX_SIZE_CHAR_ARRAY];

	in.getline(contentFile, MAX_SIZE_CHAR_ARRAY, '\0');

	cout << "Id product | Product name | Left in grams" << endl;
	cout << contentFile << endl;

	in.close();
}

void addNewElementsToCharArray(char* destination, char* source) {
	int index = 0;
	int sizeDestination = textLength(destination);

	while (source[index] != '\0') {
		destination[sizeDestination] = source[index];
		sizeDestination++;
		index++;
	}
	destination[sizeDestination] = '\0';
}

// Добавя числа правилно към char масив
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

// Намира цифрите на последнто Id на продукт в склада
int findDigitsOfLastIdProductWarehouse() {
	ifstream in(WAREHOUSE_FILE);

	if (!in.is_open()) {
		cout << "Error";
	}
	char line[MAX_SIZE_CHAR_ARRAY];
	int index = 0;
	int counter = 0;
	in.getline(line, MAX_SIZE_CHAR_ARRAY, '\0');
	while (line[index] != '\0') {
		if (line[index] == '\n') {
			index++;
			while (line[index] >= '0' && line[index] <= '9') {
				counter++;
				index++;
			}

		}
		index++;
	}

	in.close();
	return counter;
}

// Намира последното Id на продукт в склада
char* findLastIdOfProductInWarehouse() {
	ifstream in(WAREHOUSE_FILE);

	if (!in.is_open()) {
		cout << "Error";
	}
	char line[MAX_SIZE_CHAR_ARRAY];
	char* lastProductId = new char[findDigitsOfLastIdProductWarehouse()];
	int productId = 0;
	int indexProductId = 0;
	int index = 0;
	in.getline(line, MAX_SIZE_CHAR_ARRAY, '\0');

	while (line[index] != '\0') {
		if (line[index] == '\n') {
			productId = 0;
			index++;

			while (line[index] >= '0' && line[index] <= '9') {
				productId = productId * 10 + (line[index] - '0');
				index++;
			}

		}
		index++;
	}
	//Увеличиаваме стойноста на новото id с +1
	productId++;
	index = 0;
	int digit;
	while (productId != 0) {
		digit = productId % 10;
		lastProductId[index] = digit + '0';
		productId /= 10;
		index++;
	}
	lastProductId[index] = '\0';

	reverseArray(lastProductId, textLength(lastProductId));

	in.close();
	return lastProductId;
}

//Добавя нов продукт към склада
void addNewProductToWarehouse() {
	char contentFile[MAX_SIZE_CHAR_ARRAY];
	char newLineInWarehouse[MAX_SIZE_CHAR_ARRAY];
	char product[MAX_SIZE_CHAR_ARRAY];
	int grams;
	int index = 0;
	int sizeNewLineInWarehouse = 0;
	char gramsInCharArray[MAX_SIZE_CHAR_ARRAY];
	char* lastIdOfProduct = findLastIdOfProductInWarehouse();
	cout << "Enter name of new product:";
	cin >> product;

	cout << "Enter quantity of this product (in grams):";
	cin >> grams;
	if (grams > 0) {
		newLineInWarehouse[index++] = '\n';
		newLineInWarehouse[index] = '\0';
		//Добавям +1 на id-то за новия продукт и го вкарвам в char масив
		addNewElementsToCharArray(newLineInWarehouse, lastIdOfProduct);
		sizeNewLineInWarehouse = textLength(newLineInWarehouse);
		newLineInWarehouse[sizeNewLineInWarehouse++] = ';';
		newLineInWarehouse[sizeNewLineInWarehouse] = '\0';

		//Добавям името на продукта в масива
		addNewElementsToCharArray(newLineInWarehouse, product);
		sizeNewLineInWarehouse = textLength(newLineInWarehouse);
		newLineInWarehouse[sizeNewLineInWarehouse++] = ';';
		newLineInWarehouse[sizeNewLineInWarehouse] = '\0';

		addNumbersCorrectlyToCharArray(gramsInCharArray, grams);

		addNewElementsToCharArray(newLineInWarehouse, gramsInCharArray);

		sizeNewLineInWarehouse = textLength(newLineInWarehouse);
		newLineInWarehouse[sizeNewLineInWarehouse] = '\0';

		AppendInWarehouseFile(newLineInWarehouse);

		delete[] lastIdOfProduct;
	}
	else {
		cout << "Incorrect input data!" << endl;
	}

}

//Изтрива продукт от склада
void removeProductFromWarehouse() {
	ifstream in(WAREHOUSE_FILE);

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
	writeInWarehouseFile(withoutLastArticle);

	cout << "Remove product succesfully!" << endl;

	in.close();
}

// Увеличава текущата дата
void incrementDate() {
	//За да увеличи датата с единица
	int incrementedDate = readFromTodayDateFile() + 1;
	// За да се включи и терминиращата нула
	char newDate[digitsInDate + 1];
	int index = 0;
	int digit = 0;

	while (incrementedDate) {
		digit = incrementedDate % 10;
		newDate[index] = digit + '0';
		index++;
		incrementedDate /= 10;
	}
	newDate[index] = '\0';

	reverseArray(newDate, textLength(newDate));

	writeIntodayDateFile(newDate);

}

int getCountNewLine(char* contentFile) {
	int indexContentFile = 0;
	int counterNewLine = 0;

	while (contentFile[indexContentFile] != '\0') {
		if (contentFile[indexContentFile] == '\n') {

			counterNewLine++;
		}
	}

	return counterNewLine;
}

//Показва оборота за деня
void showTurnoverForToday() {
	ifstream in(TURNOVER_PER_DAY_FILE);

	if (!in.is_open()) {
		cout << "Error";
	}
	int todayDay = readFromTodayDateFile();
	char line[MAX_SIZE_CHAR_ARRAY];
	int dayFromTodayDate = getDayOfDayFile(todayDay);
	int monthFromTodayDate = getMonthOfDayFile();
	int dayFromDate;
	int monthFromDate;
	int index = 0;
	float turnoverForToday = 0;
	int number = 0;

	while (in.getline(line, BUFFER_SIZE)) {
		dayFromDate = 0;
		monthFromDate = 0;
		index = 0;
		while (line[index] >= '0' && line[index] <= '9')
		{
			dayFromDate = dayFromDate * 10 + (line[index] - '0');
			index++;
		}
		// За да прескочи ; символа
		index++;
		while (line[index] >= '0' && line[index] <= '9')
		{
			monthFromDate = monthFromDate * 10 + (line[index] - '0');
			index++;
		}
		if (dayFromDate == dayFromTodayDate && monthFromTodayDate == monthFromDate) {
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

void showReportForToday() {
	showTurnoverForToday();
	incrementDate();
}

// Заглавие 
void entryTitles() {
	cout << endl;
	cout << "   WELCOME TO" << endl;
	cout << endl;
	cout << "       MY" << endl;
	cout << endl;
	cout << " RESTAURANT SOFTWARE " << endl;
	cout << endl;
}

void showOptionsForWaiter() {
	cout << endl;
	cout << WAITER_MENU_OPTIONS << endl;
	cout << endl;
}

void showOptionsForManager() {
	cout << endl;
	cout << MANAGER_MENU_OPTIONS << endl;
	cout << endl;
}

int main()
{
	char typeOfWorker;

	char product[MAX_SIZE_CHAR_ARRAY];
	int action;
	char ordersFromFile[MAX_SIZE_CHAR_ARRAY];

	incrementDate();

	entryTitles();
	cout << "Enter your type of hierarchy:";
	cin >> typeOfWorker;

	while (typeOfWorker != WAITER && typeOfWorker != MANAGER) {
		cout << "You have to enter your type of hierarchy(Waiter - w; Manager - m):";
		cin >> typeOfWorker;

		cin.ignore();
	}

	if (typeOfWorker == 'w') {
		showOptionsForWaiter();

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
			else  if (action == 7) {
				showOptionsForWaiter();
			}
		} while (action >= 1 || action <= 7);

	}
	else if (typeOfWorker == 'm') {
		showOptionsForManager();

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
				getNamesOfArticleAndSortOrders();
			}
			else if (action == 5) {
				showDetailedOrder();
			}
			else if (action == 6) {
				seeWhatLeftsInWarehouse();
			}
			else if (action == 7) {
				removeProductFromWarehouse();
			}
			else if (action == 8) {
				addNewProductToWarehouse();
			}
			else if (action == 9) {
				showTurnoverForToday();
			}
			else if (action == 10) {
				showReportForToday();
			}
			else if (action == 11) {
				addNewArticleToMenu();
			}
			else if (action == 12) {
				removeArticleFromMenu();
			}
			else  if (action == 13) {
				showOptionsForManager();
			}
		} while (action >= 1 || action <= 13);
	}
}
