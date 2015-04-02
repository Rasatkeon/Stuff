#include <iostream>
#include <cmath>

using namespace std;

double vectorLength(pair<double, double> point1, pair<double, double> point2) {
	double len = sqrt(pow(point2.first - point1.first, 2) + pow(point2.second - point1.second, 2));
	//cout << "Length = " << len << endl;
	return len;
}

double calcS_triangle (pair<double,double> point1, pair<double,double> point2, pair<double,double> point3) {
	double a = vectorLength(point1, point2);
	//cout << "'a' = " << a << endl;
	double b = vectorLength(point2, point3);
	//cout << "'b' = " << b << endl;
	double c = vectorLength(point3, point1);
	//cout << "'c' = " << c << endl;
	double p = 0.5 * (a + b + c);
	//cout << "'p' = " << p << endl;
	//cout << "'p'-'a' = " << p - a << endl;
	//cout << "'p'-'b' = " << p - b << endl;
	//cout << "'p'-'c' = " << p - c << endl;
	//cout << "'S' = " << sqrt(p * (p - a) * (p - b) * (p - c)) << endl;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

int main(int argc, char const *argv[])
{
	//Points with pair.first as X and pair.second as Y.
	pair <double, double> point1, point2, point3, point;
	//Last point is declared without index as it is the point we are checking.

	cout << "Enter coordinates for points setting the triangle.\nFirst point: ";
	cin >> point1.first >> point1.second;
	cin.sync();
	cout << "Second point: ";
	cin >> point2.first >> point2.second;
	cin.sync();
	cout << "Third point: ";
	cin >> point3.first >> point3.second;
	cin.sync();

	cout << "Enter the point we are checking: ";
	cin >> point.first >> point.second;
	cin.sync();

	double MainTriangleS = calcS_triangle(point1, point2, point3);
	cout << "MainTriangleS = " << MainTriangleS << endl;
	double OthTrianglesS[] = { calcS_triangle(point, point1, point2), calcS_triangle(point, point2, point3), calcS_triangle(point, point1, point3) };
	//for (int i = 0; i < 3; i++) cout << "OthTrianglesS[" << i + 1 << "] = " << OthTrianglesS[i] << endl;
	if (MainTriangleS - OthTrianglesS[0] - OthTrianglesS[1] - OthTrianglesS[2] < 0.1) cout << "The point is inside the triangle.\n";
	else cout << "The point is not inside the triangle.\n";
	}
