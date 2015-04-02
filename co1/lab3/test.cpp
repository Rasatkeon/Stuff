#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "myutils.cpp"

using namespace std;

int main(){
	cout << "Enter n: ";

	int n;
	cin >> n;

	cout << "Generating matrix of size " << n << 'x' << n << '.' << endl;

	int sqn = n * n;
	vector <int> ar (sqn);
	Autils::Fill (ar);
	cout << "Generation finished:" << endl << endl;
	Autils::Print (ar,n);
	
	cout << endl << "Shall we use [S]electionSort or [H]eapSort for sorting the array? S/h ";
	
	char inp;
	cin >> inp;
	((inp == 'H') || (inp == 'h'))?(Sutils::HeapSort(ar)):(Sutils::SelectionSort(ar));
	
	cout << "Shall we sort it [u]p or [d]own? U/d ";
	
	cin >> inp;
	
	if ((inp == 'D') || (inp == 'd'))
	{
		Autils::Reverse(ar);
	}
	
	cout << endl;
	
	Autils::Print (ar,n);
	return 0;
}
