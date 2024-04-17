
#include <iostream>
#include <windows.h>
#include <string>
#include <stdio.h>
#include <fstream>

using namespace std;

struct Date {
	unsigned short day;
	unsigned short month;
	unsigned short year;
};

struct Record
{
	char surName[17];
	char ident[6];
	unsigned short year;
	float salary;
	struct Date date;
};

struct node {
	Record data;
	struct node* next;
};

node* myHead;
int countItem = 0;

void myCentr(string s, int wLine) {

	int w = s.length();
	int delta = (wLine - w) / 2;
	cout << left;
	cout.width(delta); cout << " ";
	cout << s;
	cout.width(delta + 1); cout << " ";

}

void printDate(unsigned short day, unsigned short month, unsigned short year, int wLine) {
	int w = 10;
	int delta = (wLine - w) / 2 - 1;
	cout << left;
	cout.width(delta); cout << " ";
	if (day > 9) {
		cout << day;
	}
	else {
		cout << "0" << day;
	}
	cout << ".";
	if (month > 9) {
		cout << month;
	}
	else {
		cout << "0" << month;
	}
	cout << ".";
	cout << year;
	cout.width(delta); cout << " ";
}

void Draw(struct Record* records, int num) {
	cout << endl;	cout.width(79); cout.fill('-'); cout << "-" << endl;
	cout.fill(' '); cout.width(78);  cout << left << "|Отдел кадров"; cout << "|" << endl;
	cout.width(79); cout.fill('-'); cout << "-" << endl;
	cout.fill(' ');

	cout << left << "|"; myCentr("Фамилия", 16);
	cout << left << "|"; myCentr("Инициалы", 11);
	cout << left << "|"; myCentr("Год рожд", 10);
	cout << left << "|"; myCentr("Оклад", 10);
	cout << left << " |"; myCentr("Дата приема на работу", 24);
	cout << "|" << endl;
	cout.width(79); cout.fill('-'); cout << "-" << endl;
	cout.fill(' ');
	for (int i = 0; i < num; i++) {
		cout << left << "|"; cout.width(16); cout << left << records[i].surName;
		cout << left << "|"; cout.width(11); cout << left << records[i].ident;
		cout << left << "|+"; cout.width(10); cout << left << records[i].year;
		std::cout.precision(2);
		cout << left << "|"; cout.width(11); cout << left << fixed << records[i].salary;
		cout << left << "|";
		printDate(records[i].date.day, records[i].date.month, records[i].date.year, 26);
		cout << "|" << endl;
	}
	cout.width(79); cout.fill('-'); cout << "-" << endl;
	cout.fill(' '); cout.width(78);  cout << left << "|Примечание: оклад установлен по состоянию на 1 января 2000 года"; cout << "|" << endl;
	cout.width(79); cout.fill('-'); cout << "-" << endl;
}


struct Date getMinDate(struct Record* records) {
	unsigned short minYear = records[0].date.year;
	for (int i = 1; i < 3; i++) {
		if (records[i].date.year < minYear)
			minYear = records[i].date.year;
	}

	unsigned short minMonth = records[0].date.month;
	for (int i = 1; i < 3; i++) {
		if (records[i].date.year == minYear and records[i].date.month < minMonth)
			minMonth = records[i].date.month;
	}

	unsigned short minDay = records[0].date.day;
	for (int i = 1; i < 3; i++) {
		if (records[i].date.year == minYear and records[i].date.month == minMonth and records[i].date.day < minDay)
			minDay = records[i].date.day;
	}

	struct Date minDate = { minDay, minMonth, minYear };
	return minDate;
};


struct Date getMaxDate(struct Record* records) {
	unsigned short maxYear = records[0].date.year;
	for (int i = 1; i < 3; i++) {
		if (records[i].date.year > maxYear)
			maxYear = records[i].date.year;
	}

	unsigned short maxMonth = records[0].date.month;
	for (int i = 1; i < 3; i++) {
		if (records[i].date.year == maxYear and records[i].date.month > maxMonth)
			maxMonth = records[i].date.month;
	}

	unsigned short maxDay = records[0].date.day;
	for (int i = 1; i < 3; i++) {
		if (records[i].date.year == maxYear and records[i].date.month == maxMonth and records[i].date.day > maxDay)
			maxDay = records[i].date.day;
	}

	struct Date minDate = { maxDay, maxMonth, maxYear };
	return minDate;
};

int  findIndex(struct Record* records, const struct Date date) {
	int ind = -1;
	for (int i = 0; i < 3; i++) {
		if (records[i].date.year == date.year && records[i].date.month == date.month && records[i].date.day == date.day)
			ind = i;
	}
	return ind;
};

void addItem(Record data)
{
	struct node* newItem = new node();
	newItem->data = data;
	if (countItem == 0) {
		newItem->next = NULL;
	}
	else
	{
		newItem->next = myHead;
	}
	myHead = newItem;
	countItem++;
}

void insertItem(int index, Record data) {
	if (not (index >= 0 and index <= countItem and countItem >= 0))
		return;
	if (index == 0) {
		addItem(data);
	}
	else {
		struct node* current = myHead;
		for (int i = 0; i < index - 1; i++) {
			current = current->next;
		}
		struct node* newItem = new node();
		newItem->data = data;
		newItem->next = current->next;
		current->next = newItem;
		countItem++;
	}
}
void editItem(int index, Record data) {
	if (index >= 0 and index < countItem and countItem>0) {
		struct node* current = myHead;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}
		current->data = data;
	}
	else {
		cout << endl << "Ошибка индекс не в диапазоне";
	}
}
void deleteItem(int index) {
	if (index >= 0 and index < countItem and countItem>0) {
		struct node* current = myHead;
		struct node* old;
		if (index == 0) {
			old = myHead;
			myHead = current->next;
			delete old;
			countItem--;
		}
		else {
			int i = 0;
			while (current) {
				if (i == index - 1) {
					old = current->next->next;
					delete current->next;
					current->next = old;
					countItem--;
					break;
				}
				i++;
				current = current->next;
			}
		}
	}

}
void printMyList() {
	struct node* current = myHead;
	cout << endl;
	while (current) {
		cout << " " << current->data.surName;
		current = current->next;
	}
}
void DrawWithList() {
	cout << endl;	cout.width(79); cout.fill('-'); cout << "-" << endl;
	cout.fill(' '); cout.width(78);  cout << left << "|Отдел кадров"; cout << "|" << endl;
	cout.width(79); cout.fill('-'); cout << "-" << endl;
	cout.fill(' ');
	cout << left << "|"; myCentr("Фамилия", 16);
	cout << left << "|"; myCentr("Инициалы", 11);
	cout << left << "|"; myCentr("Год рожд", 10);
	cout << left << "|"; myCentr("Оклад", 10);
	cout << left << " |"; myCentr("Дата приема на работу", 24);
	cout << "|" << endl;
	cout.width(79); cout.fill('-'); cout << "-" << endl;
	cout.fill(' ');
	struct node* current = myHead;
	while (current) {
		cout << left << "|"; cout.width(16); cout << left << current->data.surName;
		cout << left << "|"; cout.width(11); cout << left << current->data.ident;
		cout << left << "|+"; cout.width(10); cout << left << current->data.year;
		std::cout.precision(2);
		cout << left << "|"; cout.width(11); cout << left << fixed << current->data.salary;
		cout << left << "|";
		printDate(current->data.date.day, current->data.date.month, current->data.date.year, 26);
		cout << "|" << endl;
		current = current->next;
	}
	cout.width(79); cout.fill('-'); cout << "-" << endl;
	cout.fill(' '); cout.width(78);  cout << left << "|Примечание: оклад установлен по состоянию на 1 января 2000 года"; cout << "|" << endl;
	cout.width(79); cout.fill('-'); cout << "-" << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// Практика 0
	struct Record records[10];
	records[0] = { "Иванов", "И.И.", 1975, 517.50, {01,02,2010} };
	records[1] = { "Петренко", "П.П.", 1956, 219.10, {02,03,2020} };
	records[2] = { "Панковский", "М.С.", 1967, 300.10, {12,12,2012} };
	cout << "Исходные данные:" << endl;
	Draw(records, 3);

	FILE* textFile;
	fopen_s(&textFile, "textFile.txt", "w+");
	for (int i = 0; i < 3; i++) {
		fprintf(textFile, "%s %s %d %f %d %d %d \n", \
			records[i].surName, \
			records[i].ident, \
			records[i].year, \
			records[i].salary, \
			records[i].date.day, records[i].date.month, records[i].date.year);
	}
	fclose(textFile);
	fopen_s(&textFile, "textFile.txt", "r");
	Record readRecords[3];
	for (int i = 0; i < 3; i++) {
		fscanf_s(textFile, "%s", readRecords[i].surName, _countof(readRecords[i].surName));
		fscanf_s(textFile, "%s", readRecords[i].ident, _countof(readRecords[i].ident));
		fscanf_s(textFile, "%d", &readRecords[i].year);
		fscanf_s(textFile, "%f", &readRecords[i].salary);
		fscanf_s(textFile, "%d", &readRecords[i].date.day);
		fscanf_s(textFile, "%d", &readRecords[i].date.month);
		fscanf_s(textFile, "%d", &readRecords[i].date.year);
	}
	fclose(textFile);
	Draw(readRecords, 3);
	FILE* binaryFile;
	fopen_s(&binaryFile, "binaryFile.txt", "w");
	fwrite(records, sizeof(records), 1, binaryFile);
	fclose(binaryFile);
	fopen_s(&binaryFile, "binaryFile.txt", "rb");
	fread_s(readRecords, sizeof(readRecords), sizeof(readRecords), 1, binaryFile);
	fclose(binaryFile);
	Draw(readRecords, 3);


	ofstream binariFstreamFile;
	binariFstreamFile.open("binariFstreamFile.txt", ios_base::out | ios_base::binary);
	binariFstreamFile << records;  
	binariFstreamFile.close();

	Record inRecord = { "Пасочникова", "А.Р.", 2006, 1500.50, {28,04,2023} }; ;

	fopen_s(&textFile, "textFile.txt", "a");
	fprintf(textFile, "%s %s %d %f %d %d %d \n", \
		inRecord.surName, \
		inRecord.ident, \
		inRecord.year, \
		inRecord.salary, \
		inRecord.date.day, inRecord.date.month, inRecord.date.year);
	fclose(textFile);
	Record fileRecords[4];
	fopen_s(&textFile, "./textFile.txt", "r");
	for (int i = 0; i < 4; i++) {
		fscanf_s(textFile, "%s", fileRecords[i].surName, _countof(fileRecords[i].surName));
		fscanf_s(textFile, "%s", fileRecords[i].ident, _countof(fileRecords[i].ident));
		fscanf_s(textFile, "%d", &fileRecords[i].year);
		fscanf_s(textFile, "%f", &fileRecords[i].salary);
		fscanf_s(textFile, "%d", &fileRecords[i].date.day);
		fscanf_s(textFile, "%d", &fileRecords[i].date.month);
		fscanf_s(textFile, "%d", &fileRecords[i].date.year);
	}
	fclose(textFile);
	Draw(fileRecords, 4);
	fopen_s(&textFile, "textFile.txt", "r");
	for (int i = 0; i < 4; i++) {
		fscanf_s(textFile, "%s", fileRecords[i].surName, _countof(fileRecords[i].surName));
		fscanf_s(textFile, "%s", fileRecords[i].ident, _countof(fileRecords[i].ident));
		fscanf_s(textFile, "%d", &fileRecords[i].year);
		fscanf_s(textFile, "%f", &fileRecords[i].salary);
		fscanf_s(textFile, "%d", &fileRecords[i].date.day);
		fscanf_s(textFile, "%d", &fileRecords[i].date.month);
		fscanf_s(textFile, "%d", &fileRecords[i].date.year);
	}
	swap(fileRecords[2].date.day, fileRecords[3].date.day);
	swap(fileRecords[2].date.month, fileRecords[3].date.month);
	swap(fileRecords[2].date.year, fileRecords[3].date.year);
	fclose(textFile);
	fopen_s(&textFile, "textFile.txt", "w+");
	for (int i = 0; i < 4; i++) {
		fprintf(textFile, "%s %s %d %f %d %d %d \n", \
			fileRecords[i].surName, \
			fileRecords[i].ident, \
			fileRecords[i].year, \
			fileRecords[i].salary, \
			fileRecords[i].date.day, fileRecords[i].date.month, fileRecords[i].date.year);
	}
	fclose(textFile);
	Draw(fileRecords, 4);

}
