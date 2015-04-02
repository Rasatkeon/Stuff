#include <vector>
#include <iostream>

using namespace std;

#ifndef UTILS_CPP
#define UTILS_CPP

//This file contains some common utils.

//Returns a vector of string generated from input string by dividing it at divider positions.
vector<string> split(string input, char divider) {
	vector<string> output;
	
	output.push_back("");
	for (int i = 0, 
			 j = 0; i < input.size(); i++) {

		if (input[i] == divider) {
			output.push_back("");
			j++;
		}
		else output[j] += input[i];
	}

	return output;
}

//Checks if string can be number.
bool isNumber(string input) {
	string numbers = "0123456789";
	for (int i = 0; i < input.size(); ++i) {
		if (numbers.find(input[i]) == -1) return false;
	}
	return true;
}

unsigned int getNumber() {
	string input;
	cin >> input;
	cin.ignore();

	while (!(isNumber(input))) {
		cout << "This is not a number. Please try again. ";
		cin >> input;
		cin.ignore();
	}

	unsigned int output = atoi(input.data());
	return output;
}

#endif