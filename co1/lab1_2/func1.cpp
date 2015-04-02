#include <iostream>
#include <cmath>

using namespace std;

double RadiusVectorLength (double x, double y) {
	double r = sqrt (pow (x,2) + pow (y,2)); //sqrt(x^2+y^2)
	return r;
}

int main () {
	double x, y;
	cout << "Enter X: ";
	cin >> x;
	cout << "Enter Y: ";
	cin >> y;
	double r = RadiusVectorLength (x,y);
	double z = log10 (sqrt (exp (-r)) + abs (r - 1)); //z=lg(sqrt(e^(-r))+|r-1|)
	cout << "Z = " << z;
	char en;
	cin >> en;
	return 0;
}
