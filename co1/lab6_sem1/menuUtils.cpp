#include <iostream>

using namespace std;

#ifndef MENUUTILS_CPP
#define MENUUTILS_CPP

//This file contains some text outputs for menu arranged as void functions.
//Exception is yesNo which takes char 'input' initialized in menu, asks user a question and returns input if user enters 'y' or 'n'.

void space(int length) {
	for (int i = 0; i < length; i++) cout << ' ';
}

void clrscr() {
	for (int i = 0; i < 100; i++) space(100);
}

void wrongKey() {
	cout << "You entered a wrong key. Please try again. " << endl << '>';
}

void menuBase() {
	cout << "Welcome to aeroport database." << endl << "Enter option number (1,2,3) to choose option. Enter 'q' to exit." << endl;
	cout << "1. View database." << endl;
	cout << "2. Edit database." << endl;
	cout << "3. Search database." << endl;
	cout << '>';
}

void menuEdit() {
	cout << "What would you like to do?" << endl << "Enter option number (1,2,3) to choose option." << endl << "Enter 'p' to return to previous menu. Enter 'q' to exit." << endl;
	cout << "1. Add new database entry." << endl;
	cout << "2. Edit existing database entry." << endl;
	cout << "3. Delete existing database entry." << endl;
	cout << '>';
}

void entryFormat() {
	cout << "Enter the entry you want to add as" << endl;
	cout << "Destination|Date[mm/dd/yyyy]|Day|ID|Flight time[hh:mm]|Arrival time[hh:mm]|Passengers[1|2|3]" << endl;
	cout << '>';
}

void menuEditEntry() {
	cout << "Choose the field you want to edit." << endl;
	cout << "1. Destination." << endl;
	cout << "2. Date." << endl;
	cout << "3. Day." << endl;
	cout << "4. Flight ID." << endl;
	cout << "5. Flight time." << endl;
	cout << "6. Arrival time." << endl;
	cout << "7. Passengers list." << endl;
	cout << '>';
}

void menuEditEntryPassengers() {
	cout << "What would you like to do with passengers?" << endl;
	cout << "1. Add new passenger." << endl;
	cout << "2. Replace existing passenger." << endl;
	cout << "3. Delete existing passenger." << endl;
	cout << '>';
}

void yesNo(char &input, string question) {

	cout << question << " [y/n]" << endl << '>';
	cin >> input;
	cin.ignore();

	while (!(input == 'y' ^ input == 'n')) {

		wrongKey();
		cin >> input;
		cin.ignore();
	}

}

void menuSearch() {
	cout << "Enter the search query as \"Destination|Date|Flight id\"" << endl;
	cout << "You may skip some arguments or enter two dates to search between them." << endl;
	cout << '>';
}

void quit() {
	cout << "Good bye." << endl;
}

#endif
