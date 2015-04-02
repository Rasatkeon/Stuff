#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

namespace Autils { //Contains custom utils for square array aka plain vector...
	//Fills "array" of ints with random numbers.
	void Fill (vector <int> &ar) {
		srand (time (NULL));
		for (int i = 0; i < ar.size(); ++i)
		{
			ar[i] = rand ();
			//cout << ar[i] << endl;
		}
	}

	//Reverses "arrays" order.
	void Reverse (vector <int> &ar) {
		for (int i = 0; i < ar.size() / 2; ++i)
		{
			swap (ar[i],ar[ar.size() - i - 1]);
		}
	}

	//Prints out "array".
	void Print (vector <int> ar, int n) {
		int i = 0;
		while (i < ar.size()) {
			/*for (int j = 0; j < n; ++j)
			{
				cout << ar[i] << ' ';
				i++;
			}*/
			cout << ar[i] << ((ar.size() % i < n) ? " " : "/n");
			cout << endl;
		}
	}
}

namespace Sutils {//Contains custom sorting utils for this plain vector.
	//Sorts "array" using selection sort algorythm.
	void SelectionSort (vector <int> &ar) {
		for (int j = 0; j < ar.size(); j++) {
			int iMin = j;
			for (int i = j + 1; i < ar.size(); i++) {
				if (ar[i] < ar[iMin]) {
					iMin = i;
				}
			}
			if (iMin!=j) {
				swap(ar[j],ar[iMin]);
			}
		}
	}
/*
	//Merges left and right sublists for MergeSort function.
	vector <int> Merge (vector <int> left, vector <int> right){
		vector <int> result;
		while ((left.size() > 0) || (right.size() > 0)){
			if ((left.size() > 0) && (right.size() > 0)){
				if (left[0] <= right[0]){
					result.push_back(left[0]);
					left.erase(left.begin());
				}
				else {
					result.push_back(right[0]);
					right.erase(right.begin());
				}
			}
			else if (left.size() > 0){
				result.push_back(left[0]);
				left.erase(right.begin());
			}
			else if (right.size() > 0){
				result.push_back(0);
				right.erase(right.begin());
			}
		}
		return result;
	}
	
	//Mergesort sorting function.
	void MergeSort (vector <int> &ar) {
		//Array of zero or one element is already sorted.
		if (ar.size() > 1){
			vector <int> left, right;
			int middle = ar.size()/2;
			for (int i = 0; i < middle; ++i){
				left[i] = ar[i];
			}
			for (int i = 0; i < middle; ++i){
				right[ar.size()-i] = ar[i];
			}
			//Recursion for the win!
			MergeSort (left);
			MergeSort (right);

			ar = Merge (left, right);
		}
	}
*/
	void siftDown (vector <int> &ar, int i, int j) {
		bool done = false;
		int maxChild;

		while ((i * 2 + 1 < j) && (!done)) {
			if (i * 2 + 1 == j - 1) {
				maxChild = i * 2 + 1;
			}
			else if	(ar[i * 2 + 1] > ar[i * 2 + 2]) {
				maxChild = i * 2 + 1;
			}
			else { 
				maxChild = i * 2 + 2;
			}
	
			if (ar[i] < ar[maxChild]) {
				swap (ar[i],ar[maxChild]);
				i = maxChild;
			}
			else {
				done = true;
			}
		}
	}

	void HeapSort (vector <int> &ar) {
		int i, temp;

		for (i = ar.size() / 2 - 1; i >= 0; --i) {
			siftDown (ar,i,ar.size());
		}

		for (i = ar.size() - 1; i >= 1; --i) {
			swap (ar[0],ar[i]);
			siftDown(ar,0,i);
		}
	}
}