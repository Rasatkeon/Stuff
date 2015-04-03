#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

struct Stud {
	string Family;
	int Grade[4];
	Stud *next;
	Stud *prev;
};
void createStudList (Stud *&head, Stud *&tail);
Stud* deleteStud (Stud *student, Stud* &head, Stud* &tail);
void printList (Stud *p);
void checkList (Stud* p);
bool checkStud (Stud *student);
void parseGrades (Stud *student);
vector<string> split(const string &input, const char &divider);
bool isNumber(const string &input);
