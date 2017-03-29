#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

//Checks if string can be number.
bool isNumber(string input) {

	string numbers = "0123456789";

	for (int i = 0; i < input.size(); ++i) {
		if (numbers.find(input[i]) == -1) return false;
	}

	return true;
}

//Gets a positive number from input.
unsigned int getNumber() {

	string input;
	getline(cin, input);

	while (!(isNumber(input))) {

		cout << "This is not a positive integer. Please try again." << endl;
		cout << "> ";
		getline(cin, input);
	}

	unsigned int output = atoi(input.data());

	return output;
}

int main()
{
	bool main = true;
	while (main) {
		cout << "Set the array length." << endl
			 << "> ";
		
		unsigned int input = getNumber();
		
		srand (time(NULL));
		
		int * p = new int [input];
		
		for (int i = 0; i < input; ++i) {
			p[i] = rand() % 10;
			cout << p[i] << " ";
			if (i % 10 == 9) cout << endl;
		}
		delete[] p;

		cout << endl << "Do you want to try again? [Y/n] ";

		string end;
		getline(cin, end);

		if (end == "n" || end == "N") break;
	}
	return 0;
}