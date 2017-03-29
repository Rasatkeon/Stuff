#include <iostream>
#include <cmath>

using namespace std;

double ZeroToOne (double x) {
	double f = 0.5 * x * (pow (x,2) + 1) * exp (x-1);//f=0.5x(x^2+1)*e^(x-1)
	return f;
}

double OneToInfinity (double x) {
	double f = 1 - log (x);//f=1-ln(x)
	return f;
}

int main () {
	double x,f;
	cout << "Enter X: ";
	cin >> x;
	if ((x >= 0) && (x < 1)) {
		f = ZeroToOne (x);
		cout << "f(x)=" << f;
	}
	else if (x >= 1) {
		f = OneToInfinity (x);
		cout << "f(x)=" << f;
	}
	else {
		cout << "f(x) does not exist";
	}
	char en;
	cin >> en;
	return 0;
}
