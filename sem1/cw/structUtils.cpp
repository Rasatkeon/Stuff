#include "struct.cpp"
#include "menuUtils.cpp"

using namespace std;

#ifndef STRUCTUTILS_CPP
#define STRUCTUTILS_CPP

//This file contains all the functions which use custom structures.

//Checks if input can be parsed as Date.
bool isDate(string input) {
	Date temp = Date::parse(input);
	if (temp.month == 0 || temp.month > 12) return false;
	else return true;
}

//Returns minimal date from two.
Date minDate(Date left, Date right) {
	return (left < right) ? left : right;
}

//Returns maximal date from two.
Date maxDate(Date left, Date right) {
	return (left > right) ? left : right;
}

//Parses database at DATABASE_PATH
vector<Flight> getDatabase (const string &DATABASE_PATH) {

	fstream databaseFile(DATABASE_PATH, fstream::in);
	vector<Flight>database;
	string buff;

	while (databaseFile.good()) {
		getline(databaseFile, buff);
		database.push_back(Flight::parse(buff));
	}

	databaseFile.close();

	return database;
}

//Prints out database.
void viewdb(vector<Flight> database) {
	for (int i = 0; i != database.size(); ++i) cout << "Entry #" << i + 1 << endl << database[i];
}


//Writes database back to file.
void writeDatabase (const string &DATABASE_PATH, const vector<Flight> &database) {

	fstream databaseFile(DATABASE_PATH, fstream::trunc | fstream::out);

	for (int i = 0; i < database.size(); ++i) {

		Flight temp = database[i];

		databaseFile << temp.destination << '|' << temp.date << '|' << temp.day << '|'
					 << temp.id << '|' << temp.flight_time << '|' << temp.arrival_time << '|';

		for (int j = 0; j < temp.passengers.size(); ++j) {

			databaseFile << temp.passengers[j];
			if (j != temp.passengers.size() - 1) databaseFile << '|';
		}
		
			if (i != database.size()-1) databaseFile << '\n';
	
	}
	databaseFile.close();
}

//Adds new entry to database.
void addEntry(vector<Flight> &database) {

	cin.ignore();
	string input;
	getline(cin, input);

	Flight newEntry = Flight::parse(input);
	database.push_back(newEntry);
}

//Gets index for database entry.
uint getIndex(const vector<Flight> &database) {
	
	cout << "Enter the index for entry you want to edit. " << endl << '>';
	uint index = getNumber();

	while (index > database.size()) {
		cout << "There is no such entry in database. Please try again. " << endl << '>';
		index = getNumber();
	}

	return index;
}

//Lists passengers from Flight.
void listPassengers(const Flight &flight) {
	for (int i = 0; i < flight.passengers.size(); ++i) {
		cout << "Passenger #" << i + 1 << ": " << flight.passengers[i] << endl;
	}
}

//Lets you edit passengers.
void editPassengers(Flight &temp) {

	menuEditEntryPassengers();
	char input;
	cin >> input;
	cin.ignore();

	while (!(input == '1' ^ input == '2' ^ input == '3')) {
		wrongKey();
		cin >> input;
		cin.ignore();
	}

	switch (input) {

	case '1': {

		cout << "Enter new passenger." << endl;
		string newPassenger;
		getline(cin, newPassenger);
		temp.passengers.push_back((string)newPassenger);
		break;
	}
	case '2': {

		listPassengers(temp);
		cout << "Enter the # of passenger you want to edit: ";
		uint passengerIndex;
		cin >> passengerIndex;
		cin.ignore();

		while (passengerIndex > temp.passengers.size()) {
			wrongKey();
			cin >> passengerIndex;
			cin.ignore();
		}

		cout << "Old passenger is " << temp.passengers[passengerIndex - 1] << endl;
		cout << "Enter new passenger: ";
		string newPassenger;
		getline(cin, newPassenger);
		temp.passengers[passengerIndex - 1] = newPassenger;
		break;
	}
	case '3': {

		listPassengers(temp);
		uint passengerIndex;
		cin >> passengerIndex;
		cin.ignore();

		while (passengerIndex > temp.passengers.size()) {
			wrongKey();
			cin >> passengerIndex;
			cin.ignore();
		}

		cout << "You want to delete " << temp.passengers[passengerIndex - 1] << endl;
		yesNo(input, "Are you sure?");
		if (input == 'n') break;

		temp.passengers.erase(temp.passengers.begin() + passengerIndex - 1);
	}

	}
}

//Lets you edit a database entry.
void editEntry(vector<Flight> &database, uint index, char field) {
	
	Flight temp = database[index-1];
	switch(field) {

	case '1': {
		cout << "Old field: " << temp.destination << endl << "New field: ";
		getline(cin, temp.destination);
		break;
	}
	case '2': {
		cout << "Old field: " << temp.date << endl << "New field: ";
		cin >> temp.date;
		break;
	} 
	case '3': {
		cout << "Old field: " << temp.day << endl << "New field: ";
		cin >> temp.day;
		cin.ignore();
		break;
	}
	case '4': {
		cout << "Old field: " << temp.id << endl << "New field: ";
		cin >> temp.id;
		cin.ignore();
		break;
	}
	case '5': {
		cout << "Old field: " << temp.flight_time << endl << "New field: ";
		cin >> temp.flight_time;
		break;
	}
	case '6': {
		cout << "Old field: " << temp.arrival_time << endl << "New field: ";
		cin >> temp.arrival_time;
		break;
	}
	case '7': {
		editPassengers(temp);
		break;
	}
	default:
		cout << "Something went wrong...";
		break;
	}

	database[index-1] = temp;

}

//Searches database.
vector<Flight> searchDatabase(string destinationArg, Date dateArgMin, Date dateArgMax, string idArg, vector<Flight> database) {

	vector<Flight> searchResults;
	for (int i = 0; i < database.size(); ++i) {

		if ((destinationArg == "" || destinationArg == database[i].destination) && 
			(dateArgMin.month == 0 || dateArgMin == database[i].date ||
			(database[i].date <= dateArgMax && database[i].date >= dateArgMin)) &&
			(idArg == "" || idArg == database[i].id)) {

			searchResults.push_back(database[i]);
		}
	}
	return searchResults;
}

#endif