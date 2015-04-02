#include "menuUtils.cpp"
#include "structUtils.cpp"

using namespace std;

int main(int argc, const char* argv[]) {

	const string DATABASE_PATH = "Database";
	bool menu1 = true;

	do {
		vector <Flight> database = getDatabase(DATABASE_PATH);
		menuBase();

		char input;
		cin >> input;
		cin.ignore();

		while (!(input == '1' ^ input == '2' ^ input == '3' ^ input == 'q')) {
			cout << "You entered a wrong key. Please try again. ";
			cin >> input;
			cin.ignore();
		}

		bool menu2 = true;

		switch (input) {

		case '1': {
			database = getDatabase(DATABASE_PATH);
			viewdb(database);
			break;
		}

		case '2': {
			do {
				menuEdit();

				cin >> input;
				cin.ignore();

				while (!(input == '1' ^ input == '2' ^ input == '3' ^ input == 'q' ^ input == 'p')) {
					wrongKey();
					cin >> input;
					cin.ignore();
				}

				switch (input) {

				case '1': {

					entryFormat();
					addEntry(database);
					writeDatabase(DATABASE_PATH, database);

					break;
				}

				case '2': {

					viewdb(database);

					while (true) {

						uint index = getIndex(database);
					
						cout << "This is the entry you want to edit:" << endl << endl << database[index - 1];
					
						char input;
						yesNo(input, "Is it right?");
					
						if (input == 'n') continue;

						menuEditEntry();
						cin >> input;
						cin.ignore();

						while (!(input == '1' ^ input == '2' ^ input == '3' ^ input == '4' ^ input == '5' ^ input == '6' ^ input == '7')) {
							wrongKey();
							cin >> input;
							cin.ignore();
						}

						editEntry(database, index, input);
						writeDatabase(DATABASE_PATH, database);

						break;
					}

					break;
				}

				case '3': {

					viewdb(database);

					cout << "Enter the index for entry you want to delete." << endl << '>';
					uint entryIndex;
					cin >> entryIndex;
					cin.ignore();

					while (entryIndex > database.size()) {
						wrongKey();
						cin >> entryIndex;
						cin.ignore();
					}

					cout << "This is the entry you want to delete:" << endl;
					cout << database[entryIndex-1] << endl;

					char input;
					yesNo(input, "Are you sure?");

					if (input == 'n') break;

					database.erase(database.begin() + entryIndex);
					writeDatabase(DATABASE_PATH, database);

					break;
				}

				case 'p': {
					menu2 = false;
					break;
				}

				case 'q': {
					menu2 = false;
					menu1 = false;
					break;
				}

				default:
					break;
				}
			} while (menu2);
			break;
		}

		case '3': {
			do {

				menuSearch();
					
				while (true) {
					
					string searchQueryInput;
					cin >> searchQueryInput;
					cin.ignore();
					
					vector<string> arguments = split(searchQueryInput, '|');
					
					string idArg = "", destinationArg = "";
					Date dateArgMin, dateArgMax;
					bool badQuery = false;
					for (int i = 0; i < arguments.size(); ++i) {

						if (isDate(arguments[i]) && dateArgMin.month == 0) {
					
							dateArgMin = Date::parse(arguments[i]);
						}
						else if (isDate(arguments[i]) && arguments[i] != dateArgMin && dateArgMax.month == 0) {
							dateArgMax = Date::parse(arguments[i]);
							if (dateArgMin > dateArgMax) swap(dateArgMin, dateArgMax);
						}
						else if (isNumber(arguments[i]) && idArg == "") {
					
							idArg = arguments[i];
						}
						else if (destinationArg == "") {

							destinationArg = arguments[i];
						}
						else {
							cout << "Wrong search query." << endl;
							badQuery = true;
						}
					}

					if (badQuery) {
						char input;
						yesNo(input, "Do you want to enter new query?");
						if (input == 'y') continue;
						else break;
					}

					vector<Flight> searchResults = searchDatabase(destinationArg, dateArgMin, dateArgMax, idArg, database);

						if (searchResults.empty()) {

							cout << "There is no such entry in database." << endl;
							char input;
							yesNo(input, "Would you like to enter other search query?");

							if (input == 'n') break;
							else continue;
						}

						for (int i = 0; i < searchResults.size(); ++i) {
							cout << "Result #" << i + 1 << endl << searchResults[i];
						}
						break;
				}
				menu2 = false;

			} while (menu2);
			break;
		}

		case 'q': {
			menu1 = false;
			break;
		}

		default:
			break;
		}
	} while (menu1);
	quit();
	return 0;
}