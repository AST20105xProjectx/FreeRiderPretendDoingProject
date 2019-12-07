#include "DataSetList.h"
#include <cstdio>
#include <ctime>
#include <time.h>
#include <windows.h>
#include <fstream>

typedef enum FOREGROUND_COLORS //define foreground colors
{
	FOREGROUND_BLACK = 0,
	//FOREGROUND_BLUE = 1,
	//FOREGROUND_GREEN = 2,
	FOREGROUND_CYAN = 3,
	//FOREGROUND_RED = 4,
	FOREGROUND_MAGENTA = 5,
	FOREGROUND_BROWN = 6,
	FOREGROUND_LIGHTGRAY = 7,
	FOREGROUND_GRAY = 8,
	FOREGROUND_LIGHTBLUE = 9,
	FOREGROUND_LIGHTGREEN = 10,
	FOREGROUND_LIGHTCYAN = 11,
	FOREGROUND_LIGHTRED = 12,
	FOREGROUND_LIGHTMAGENTA = 13,
	FOREGROUND_YELLOW = 14,
	FOREGROUND_WHITE = 15
}FOREGROUND_COLORS;


WORD GetConsoleTextAttribute(HANDLE hCon) //color
{
	CONSOLE_SCREEN_BUFFER_INFO con_info;
	GetConsoleScreenBufferInfo(hCon, &con_info);
	return con_info.wAttributes;
}

DataSetList::DataSetList()
{
	DataSetHead = new DataSet();
};



void DataSetList::fileinput() {		// insertion of dataset
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int saved_colors = GetConsoleTextAttribute(hConsole);
	DataSet* SetHead = DataSetHead;
	Node* ListHead = DataSetHead->listSet->head;
	string ID;
	string JobTitle;
	string EmailAddress;
	string LastName;
	string FirstName;
	string PhoneNumber;
	string Skills;
	string Country;
	ifstream dataSet;
	string filename = " ";

	int i = 0;

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Which DataSet you want to input?" << endl;
	cout << "Filename: ";
	SetConsoleTextAttribute(hConsole, saved_colors);
	SetConsoleTextAttribute(hConsole, FOREGROUND_MAGENTA | FOREGROUND_INTENSITY);
	cin >> filename;
	SetConsoleTextAttribute(hConsole, saved_colors);
	clock_t tStart;
	double duration;
	tStart = clock();		//start counting time taken for inserting single bath of data 
	cout << endl;

	dataSet.open(filename);
	if (!(dataSet.is_open())) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cerr << "Error. The file doesn't open correctly." << endl;
		SetConsoleTextAttribute(hConsole, saved_colors);
	}
	else {
		while (!dataSet.eof()) {
			getline(dataSet, ID, '\t');
			getline(dataSet, JobTitle, '\t');
			getline(dataSet, EmailAddress, '\t');
			getline(dataSet, LastName, '\t');
			getline(dataSet, FirstName, '\t');
			getline(dataSet, PhoneNumber, '\t');
			getline(dataSet, Skills, '\t');
			getline(dataSet, Country, '\t');
			if (ListHead == NULL) {
				Node* newList = new Node(ID, JobTitle, EmailAddress, LastName, FirstName, PhoneNumber, Skills, Country);
				DataSetHead->listSet->head = newList;
				ListHead = DataSetHead->listSet->head;
			}
			else {
				Node* newList = new Node(ID, JobTitle, EmailAddress, LastName, FirstName, PhoneNumber, Skills, Country);
				ListHead->next = newList;
				ListHead = ListHead->next;
			}
			i++;
		}
	}
	duration = (clock() - tStart) / (double)CLOCKS_PER_SEC;
	cout << "Program Run time: " << duration << "s" << '\n';//	display	the	time	elapsed
	SetConsoleTextAttribute(hConsole, saved_colors);
	SetConsoleTextAttribute(hConsole, FOREGROUND_LIGHTCYAN | FOREGROUND_INTENSITY);
	cout << "There are total " << i << " data(s) inserted" << endl;
}



void DataSetList::MainMenu() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int saved_colors = GetConsoleTextAttribute(hConsole);
	DataSet* InnerDataSetHead = DataSetHead;
	int input = NULL;
	SetConsoleTextAttribute(hConsole, FOREGROUND_LIGHTGREEN);
	cout << "Welcome to our program!!" << endl;
	SetConsoleTextAttribute(hConsole, saved_colors);
	cout << "*************************************************************" << endl;
	SetConsoleTextAttribute(hConsole, FOREGROUND_LIGHTGREEN);
	cout << "Choose which function you want to do " << endl;
	SetConsoleTextAttribute(hConsole, saved_colors);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "-1. End" << endl;
	SetConsoleTextAttribute(hConsole, saved_colors);
	SetConsoleTextAttribute(hConsole, FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
	cout << " 1. Insertion of dataset		\n 2. Deletion of record(s)\n 3. Searching for record(s)" << endl;
	SetConsoleTextAttribute(hConsole, saved_colors);
	SetConsoleTextAttribute(hConsole, FOREGROUND_MAGENTA | FOREGROUND_INTENSITY);
	cout << " Your decision: ";
	cin >> input;
	SetConsoleTextAttribute(hConsole, saved_colors);
	switch (input)
	{
	case -1: {
		system("cls");
		SetConsoleTextAttribute(hConsole, FOREGROUND_LIGHTGREEN);
		cout << "Thanks for using our program!!" << endl;
		SetConsoleTextAttribute(hConsole, saved_colors);
		system("pause");
		exit(0);
	}
	case 1: {
		fileinput();
		for (; InnerDataSetHead->next != NULL; InnerDataSetHead = InnerDataSetHead->next);
		system("pause");
		system("cls");
		MainMenu();
	}

	case 2:
		if (DataSetHead->listSet->head == NULL) {
			cout << "There is no dataSet import yet" << endl;
			cout << "Press anykey to go to insert function" << endl;
			system("pause"); system("cls");
			fileinput(); for (; InnerDataSetHead->next != NULL; InnerDataSetHead = InnerDataSetHead->next);
			system("pause");
			system("pause"); system("cls"); MainMenu();
		}
		DeletionMenu();
		system("pause");
		system("cls");
		MainMenu();

	case 3:
		if (DataSetHead->listSet->head == NULL) {
			cout << "There is no dataSet import yet" << endl;
			cout << "Press anykey to go to insert function" << endl;
			system("pause");
			system("cls");
			fileinput();
			for (; InnerDataSetHead->next != NULL; InnerDataSetHead = InnerDataSetHead->next);
			system("pause");
			system("pause");
			system("cls");
			MainMenu();
		}
		SearchingMenu();
		system("pause");
		system("cls");
		MainMenu();

	default:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "Wrong input" << endl;
		SetConsoleTextAttribute(hConsole, saved_colors);
		system("pause");
		system("cls");

		MainMenu();
	}
}


void DataSetList::SearchingMenu() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int saved_colors = GetConsoleTextAttribute(hConsole);
	int y;

	SetConsoleTextAttribute(hConsole, FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
	cout << "1. By ID	\n2. By Skills	\n3. By Job Title	\n4. By Country	\n5. By Skills x Job Title	\n6. By Skills x Country	\n7. By Skills x ID	\n8. By Job Title x Country	\n9. By Job Title x ID	\n10. By Country x ID";
	SetConsoleTextAttribute(hConsole, saved_colors);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "0. Stop Searching" << endl;
	SetConsoleTextAttribute(hConsole, saved_colors);
	SetConsoleTextAttribute(hConsole, FOREGROUND_MAGENTA | FOREGROUND_INTENSITY);
	cin >> y;
	SetConsoleTextAttribute(hConsole, saved_colors);
	switch (y)
	{
	case 0: return;
	case 1: SearchingByID();		system("pause"); system("cls"); MainMenu();	//go to searching by id function and go back to the main menu.
	case 2: SearchingBySkills();	system("pause"); system("cls"); MainMenu();	//go to searching by skills function and go back to the main menu.
	case 3: SearchingByJobTitle();	system("pause"); system("cls"); MainMenu();	//go to searching by job title function and go back to the main menu.
	case 4: SearchingByCountry();	system("pause"); system("cls"); MainMenu();	//go to searching by country function and go back to the main menu.
	default: {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "Wrong input." << endl;
		SetConsoleTextAttribute(hConsole, saved_colors);
		SearchingMenu();
	}
	}
}

void DataSetList::SearchingByID() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int saved_colors = GetConsoleTextAttribute(hConsole);
	string input;
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Enter the ID of the data" << endl;
	SetConsoleTextAttribute(hConsole, saved_colors);
	SetConsoleTextAttribute(hConsole, FOREGROUND_MAGENTA | FOREGROUND_INTENSITY);
	cin.ignore();
	getline(cin, input);
	SetConsoleTextAttribute(hConsole, saved_colors);
	clock_t tStart;
	double duration;
	tStart = clock();	//start counting the time for searching the record.
	cout << "*************************************************************" << endl;
	int counter = 0;
	DataSet* CurrSet = DataSetHead;
	Node* CurrNode = CurrSet->listSet->head;
	for (; CurrNode != NULL; CurrNode = CurrNode->next) {
		if (input.compare(CurrNode->ID) == 0) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE | FOREGROUND_INTENSITY);
			cout << CurrNode->ID << "\t" << CurrNode->JobTitle << "\t" << CurrNode->EmailAddress << "\t" << CurrNode->LastName << "\t"
				<< CurrNode->FirstName << "\t" << CurrNode->PhoneNumber << "\t" << CurrNode->Skills << "\t" << CurrNode->Country << "\n";
			SetConsoleTextAttribute(hConsole, saved_colors);
			counter++;
			break;
		}
	}

	SetConsoleTextAttribute(hConsole, FOREGROUND_LIGHTCYAN | FOREGROUND_INTENSITY);
	duration = (clock() - tStart) / (double)CLOCKS_PER_SEC;
	cout << "Program Run time: " << duration << "s" << '\n';// cout the time that use for searching
	SetConsoleTextAttribute(hConsole, saved_colors);

	if (counter == 0) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "No data found" << endl;
		SetConsoleTextAttribute(hConsole, saved_colors);
	}
	else {
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Number of Data: " << counter << endl;
		SetConsoleTextAttribute(hConsole, saved_colors);
	}

}

void DataSetList::SearchingBySkills() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int saved_colors = GetConsoleTextAttribute(hConsole);
	string input;
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Enter the Skills of the data" << endl;
	SetConsoleTextAttribute(hConsole, saved_colors);
	SetConsoleTextAttribute(hConsole, FOREGROUND_MAGENTA | FOREGROUND_INTENSITY);
	cin.ignore();
	getline(cin, input);
	SetConsoleTextAttribute(hConsole, saved_colors);
	clock_t tStart;
	double duration;
	tStart = clock();	// starting counting 
	cout << "*************************************************************" << endl;
	int counter = 0;
	DataSet* CurrSet = DataSetHead;

	Node* CurrNode = CurrSet->listSet->head;
	for (; CurrNode != NULL; CurrNode = CurrNode->next) {
		if (input.compare(CurrNode->Skills) == 0) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE | FOREGROUND_INTENSITY);
			cout << CurrNode->ID << "\t" << CurrNode->JobTitle << "\t" << CurrNode->EmailAddress << "\t" << CurrNode->LastName << "\t"
				<< CurrNode->FirstName << "\t" << CurrNode->PhoneNumber << "\t" << CurrNode->Skills << "\t" << CurrNode->Country << "\n";
			SetConsoleTextAttribute(hConsole, saved_colors);
			counter++;

		}
	}

	SetConsoleTextAttribute(hConsole, FOREGROUND_LIGHTCYAN | FOREGROUND_INTENSITY);
	duration = (clock() - tStart) / (double)CLOCKS_PER_SEC;// stop counting the time
	cout << "Program Run time: " << duration << "s" << '\n';// cout the time that 
	SetConsoleTextAttribute(hConsole, saved_colors);

	if (counter == 0) {	// cout if there not data match with the input condition
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "No data found" << endl;
		SetConsoleTextAttribute(hConsole, saved_colors);
	}
	else {		//cout the number of data match with the condition.
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Number of data: " << counter << endl;
		SetConsoleTextAttribute(hConsole, saved_colors);
	}

}

void DataSetList::SearchingByJobTitle() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int saved_colors = GetConsoleTextAttribute(hConsole);
	string input;
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Enter the Job Title of the data" << endl;
	SetConsoleTextAttribute(hConsole, saved_colors);
	SetConsoleTextAttribute(hConsole, FOREGROUND_MAGENTA | FOREGROUND_INTENSITY);
	cin.ignore();
	getline(cin, input);
	SetConsoleTextAttribute(hConsole, saved_colors);
	clock_t tStart;
	double duration;
	tStart = clock();	//start counting the time for searching the record.
	cout << "*************************************************************" << endl;
	int counter = 0;
	DataSet* CurrSet = DataSetHead;

	Node* CurrNode = CurrSet->listSet->head;
	for (; CurrNode != NULL; CurrNode = CurrNode->next) {  // searching the id for each record.
		if (input.compare(CurrNode->JobTitle) == 0) {	// if the id match with user input id, cout the record and stop searching.
			SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE | FOREGROUND_INTENSITY);
			cout << CurrNode->ID << "\t" << CurrNode->JobTitle << "\t" << CurrNode->EmailAddress << "\t" << CurrNode->LastName << "\t"
				<< CurrNode->FirstName << "\t" << CurrNode->PhoneNumber << "\t" << CurrNode->Skills << "\t" << CurrNode->Country << "\n";
			SetConsoleTextAttribute(hConsole, saved_colors);
			counter++;
			break;
		}
	}

	SetConsoleTextAttribute(hConsole, FOREGROUND_LIGHTCYAN | FOREGROUND_INTENSITY);
	duration = (clock() - tStart) / (double)CLOCKS_PER_SEC;
	cout << "Program Run time: " << duration << "s" << '\n';// cout the time that use for searching
	SetConsoleTextAttribute(hConsole, saved_colors);

	if (counter == 0) {	// cout if there are no data match.
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "No data found" << endl;
		SetConsoleTextAttribute(hConsole, saved_colors);
	}
	else {	// cout the number of data match with the input condition
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Number of Data: " << counter << endl;
		SetConsoleTextAttribute(hConsole, saved_colors);
	}

}

void DataSetList::SearchingByCountry() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int saved_colors = GetConsoleTextAttribute(hConsole);
	string input;
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Enter the Country of the data" << endl;
	SetConsoleTextAttribute(hConsole, saved_colors);
	SetConsoleTextAttribute(hConsole, FOREGROUND_MAGENTA | FOREGROUND_INTENSITY);
	cin.ignore();
	getline(cin, input);
	SetConsoleTextAttribute(hConsole, saved_colors);
	clock_t tStart;
	double duration;
	tStart = clock();	//start counting the time for searching the record.
	cout << "*************************************************************" << endl;
	int counter = 0;
	DataSet* CurrSet = DataSetHead;

	counter = 0;
	Node* CurrNode = CurrSet->listSet->head;
	for (; CurrNode != NULL; CurrNode = CurrNode->next) {
		if (input.compare(CurrNode->Country) == 0) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE | FOREGROUND_INTENSITY);
			cout << CurrNode->ID << "\t" << CurrNode->JobTitle << "\t" << CurrNode->EmailAddress << "\t" << CurrNode->LastName << "\t"
				<< CurrNode->FirstName << "\t" << CurrNode->PhoneNumber << "\t" << CurrNode->Skills << "\t" << CurrNode->Country << "\n";
			SetConsoleTextAttribute(hConsole, saved_colors);
			counter++;// user for counting how many record are match with the input condition.
			break;
		}
	}

	SetConsoleTextAttribute(hConsole, FOREGROUND_LIGHTCYAN | FOREGROUND_INTENSITY);
	duration = (clock() - tStart) / (double)CLOCKS_PER_SEC;
	cout << "Program Run time: " << duration << "s" << '\n';// cout the time that use for searching
	SetConsoleTextAttribute(hConsole, saved_colors);

	if (counter == 0) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "No data found" << endl;
		SetConsoleTextAttribute(hConsole, saved_colors);
	}
	else {
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Number of Data: " << counter << endl;
		SetConsoleTextAttribute(hConsole, saved_colors);
	}

}

void DataSetList::DeletionMenu() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int saved_colors = GetConsoleTextAttribute(hConsole);
	int input;
	SetConsoleTextAttribute(hConsole, FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
	cout << "1. By PhoneNumber   2. By Country	";
	SetConsoleTextAttribute(hConsole, saved_colors);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "0. Stop Searching" << endl;
	SetConsoleTextAttribute(hConsole, saved_colors);
	SetConsoleTextAttribute(hConsole, FOREGROUND_MAGENTA | FOREGROUND_INTENSITY);
	cin >> input;
	SetConsoleTextAttribute(hConsole, saved_colors);

	switch (input)
	{
	case 0: return;
	case 1: DeletionByPhoneNumber(); system("pause"); system("cls"); MainMenu();	//go to delete by phone function and go back to the main menu.
	case 2: DeletionByCountry();	system("pause"); system("cls"); MainMenu();	//go to delete by country function and go back to the main menu.
	default: system("cls"); DeletionMenu();
	}
}

void DataSetList::DeletionByPhoneNumber() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int saved_colors = GetConsoleTextAttribute(hConsole);
	string input;
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Enter the Phone Number (with stroke inputted) of the data" << endl;
	SetConsoleTextAttribute(hConsole, saved_colors);

	SetConsoleTextAttribute(hConsole, FOREGROUND_MAGENTA | FOREGROUND_INTENSITY);
	cin.ignore();
	getline(cin, input);
	SetConsoleTextAttribute(hConsole, saved_colors);

	clock_t tStart;
	double duration;
	tStart = clock();
	cout << "*************************************************************" << endl;
	int counter = 0;
	DataSet* CurrSet = DataSetHead;
	Node* CurrNode = CurrSet->listSet->head;
	Node* preNode = NULL;
	for (; CurrNode != NULL; preNode = CurrNode, CurrNode = CurrNode->next) {
		if (preNode == NULL && input.compare(CurrNode->PhoneNumber) == 0) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE | FOREGROUND_INTENSITY);
			cout << CurrNode->ID << "\t" << CurrNode->JobTitle << "\t" << CurrNode->EmailAddress << "\t" << CurrNode->LastName << "\t"
				<< CurrNode->FirstName << "\t" << CurrNode->PhoneNumber << "\t" << CurrNode->Skills << "\t" << CurrNode->Country << "\n";
			CurrSet->listSet->head = CurrNode->next;
			SetConsoleTextAttribute(hConsole, saved_colors);
			cout << "*************************************************************" << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "Data has been deleted" << endl;
			SetConsoleTextAttribute(hConsole, saved_colors);

			counter++;
			break;
		}
		else if (preNode != NULL && input.compare(CurrNode->PhoneNumber) == 0) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE | FOREGROUND_INTENSITY);
			cout << CurrNode->ID << "\t" << CurrNode->JobTitle << "\t" << CurrNode->EmailAddress << "\t" << CurrNode->LastName << "\t"
				<< CurrNode->FirstName << "\t" << CurrNode->PhoneNumber << "\t" << CurrNode->Skills << "\t" << CurrNode->Country << "\n";
			preNode->next = CurrNode->next;
			SetConsoleTextAttribute(hConsole, saved_colors);

			delete CurrNode;
			cout << "*************************************************************" << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "Data has been deleted" << endl;
			SetConsoleTextAttribute(hConsole, saved_colors);

			counter++;
			break;
		}
	}

	SetConsoleTextAttribute(hConsole, FOREGROUND_LIGHTCYAN | FOREGROUND_INTENSITY);
	duration = (clock() - tStart) / (double)CLOCKS_PER_SEC;
	cout << "Program Run time: " << duration << "s" << '\n';
	SetConsoleTextAttribute(hConsole, saved_colors);
	system("pause");

	if (counter == 0) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "Data not found" << endl;
		SetConsoleTextAttribute(hConsole, saved_colors);
	}
}



void DataSetList::DeletionByCountry() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int saved_colors = GetConsoleTextAttribute(hConsole);
	string input;
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Enter the Country of the data" << endl;
	SetConsoleTextAttribute(hConsole, saved_colors);
	SetConsoleTextAttribute(hConsole, FOREGROUND_MAGENTA | FOREGROUND_INTENSITY);
	cin.ignore();
	getline(cin, input);
	SetConsoleTextAttribute(hConsole, saved_colors);

	clock_t tStart;
	double duration;
	tStart = clock();
	cout << "*************************************************************" << endl;
	int	counter = 0;
	DataSet* CurrSet = DataSetHead;
	Node* newlist = NULL;
	Node* CurrNode = CurrSet->listSet->head;
	CurrSet->listSet->head = NULL;
	Node* SetHead = CurrSet->listSet->head;
	for (; CurrNode != NULL; CurrNode = CurrNode->next) {
		if (input.compare(CurrNode->Country)) {
			if (SetHead == NULL) {
				Node* newlist1 = new Node(CurrNode->ID, CurrNode->JobTitle, CurrNode->EmailAddress, CurrNode->LastName, CurrNode->FirstName,
					CurrNode->PhoneNumber, CurrNode->Skills, CurrNode->Country);
				SetHead = newlist1;
				CurrSet->listSet->head = SetHead;
			}
			else {
				Node* newlist1 = new Node(CurrNode->ID, CurrNode->JobTitle, CurrNode->EmailAddress, CurrNode->LastName, CurrNode->FirstName,
					CurrNode->PhoneNumber, CurrNode->Skills, CurrNode->Country);
				SetHead->next = newlist1;
				SetHead = SetHead->next;
			}
		}
		else {
			counter++;
		}
	}

	CurrNode = CurrSet->listSet->head;

	SetConsoleTextAttribute(hConsole, FOREGROUND_LIGHTCYAN | FOREGROUND_INTENSITY);
	duration = (double)(clock() - tStart) / (double)CLOCKS_PER_SEC;
	cout << "Program Run time: " << duration << "s" << '\n';
	SetConsoleTextAttribute(hConsole, saved_colors);
	system("pause");

	if (counter == 0) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "No data match" << endl;
		SetConsoleTextAttribute(hConsole, saved_colors);

	}
	else {
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Number of Datad deleted: " << counter << endl;
		SetConsoleTextAttribute(hConsole, saved_colors);

	}
}





