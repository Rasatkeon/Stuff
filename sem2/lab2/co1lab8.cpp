#include "co1lab8.h"

using namespace std;

bool DEBUG_MODE = false;

//Base structure
struct Stud;

//Creates new students untill you enter something starting with y/Y
void createStudList (Stud *&head, Stud *&tail) {
	Stud *p, *prev;
	prev = NULL;
	string input;

	while (input[0] != 'y' && input[0] != 'Y') {
		p = new Stud;
	
		cout << "Type Family." << endl << "> ";
		getline(cin, p -> Family);
		
		cout << "Type four Grades." << endl << "> ";
		parseGrades(p);

		p -> prev = prev;
		if (prev) prev -> next = p;
		else head = p;
		prev = p;

		cout << "Enough? [y/N]" << endl << "> ";
		getline(cin, input);
		//if (DEBUG_MODE) cout << input;
	}

	tail = p;
	tail -> next = NULL;
}

Stud* deleteStud (Stud* student, Stud* &head, Stud* &tail) {
	if (student == tail && student == head) {
		delete student;
		head = NULL;
		tail = NULL;
		return NULL;
	}
	else if (student == head) {
		head = head -> next;
		head -> prev = NULL;
		delete student;
		return head;
	}
	else if (student == tail) {
		tail = tail -> prev;
		tail -> next = NULL;
		delete student;
		return tail;
	}
	else {
		student -> next -> prev = student -> prev;
		student -> prev -> next = student -> next;
		Stud* curr = student -> next ? student -> next : student -> prev ? student -> prev : NULL;
		delete student;
		return curr;
	}
}

//Nothing of interest
void printList (Stud *p) {
	int number = 1;
	if (p == NULL) cout << "Empty list or just NULL.";
	else if ((!p -> prev) && (!p -> next)) {
		cout << "There is one record in this list:" << endl;
		cout << "Record #" << number << endl;
		cout << "Family: " << p -> Family << endl;
		cout << "Grades: ";
		for (int i = 0; i < 4; ++i) {
			cout << p -> Grade[i] << " ";
		}
		cout << endl << endl;
	}
	else if (p -> next)
		while (p) {
			cout << "Record #" << number << endl;
			cout << "Family: " << p -> Family << endl;
			cout << "Grades: ";
			for (int i = 0; i < 4; ++i) {
				cout << p -> Grade[i] << " ";
			}
			cout << endl << endl;

			p = p -> next;
			number++;
		}
	else if (p -> prev) {
		while (p) {

			cout << "Record #" << number << endl;
			cout << "Family: " << p -> Family << endl;
			cout << "Grades: ";
			for (int i = 0; i < 4; ++i) {
				cout << p -> Grade[i] << " ";
			}
			cout << endl << endl;

			p = p -> prev;
			number++;
		}
	}
	else cout << "Wrong address";
}

void checkList (Stud* p, Stud* &head, Stud* &tail) {
	if ((!p -> prev) && (!p -> next)) {
		if (checkStud(p)) {
			p = deleteStud(p, head, tail);
			return;
		}
	}
	else if (!p -> prev)
		while (p) {
			if (checkStud(p)) p = deleteStud(p, head, tail);
			if (p) p = p -> next;
			else break;
		}
	else if (!p -> next)
		while (p) {
			if (checkStud(p)) p = deleteStud(p, head, tail);
			if (p) p = p -> prev;
			else break;
		}
	return;
};

bool checkStud (Stud *student) {
	for (int i = 0; i < 4; ++i) if (student -> Grade[i] == 2 || student -> Grade[i] == 3) return true;
	return false;
};

//Dummy protector
void parseGrades (Stud *student) {
	bool end = false;
	string input;
	do {
		getline(cin, input);
		vector<string> grades = split(input, ' ');
		for (int i = 0; i < grades.size(); ++i) {
			//if (DEBUG_MODE) cout << "Vector " << i << " " << grades[i];
			if (grades[i] == "") {
				grades.erase(grades.begin() + i);
				i--;
			}
		}
		if (grades.size() != 4) {
			cout << "Wrong input. Please try again." << endl << "> ";
			continue;
		}
		for (int i = 0; i < 4; ++i) {
			int temp = 7;
			if (isNumber(grades[i])) temp = atoi(grades[i].data());
				if (temp < 6) student -> Grade[i] = temp;
				else student -> Grade[i] = 0;
		}

		end = true;

		for (int i = 0; i < 4; ++i) {
			if (student -> Grade[i] == 0) {
				end = false;
				cout << "Wrong input. Please try again." << endl << "> ";
				break;
			}
		}
	} while (!end);
}

//Returns a vector of string generated from input string by dividing it at divider positions.
vector<string> split(const string &input, const char &divider) {
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
bool isNumber(const string &input) {
	string numbers = "0123456789";
	for (int i = 0; i < input.size(); ++i) {
		if (numbers.find(input[i]) == -1) return false;
	}
	return true;
}

int main() {
	string end;
	Stud *head, *tail;
	createStudList(head, tail);
	printList (head);
	cout << endl << "Some magic" << endl << endl << endl;
	checkList(head, head, tail);
	printList(head);
	getline(cin, end);
	return 0;
}