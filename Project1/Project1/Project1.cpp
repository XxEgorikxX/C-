﻿#include <iostream>
#include <cmath>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	float x, y;
	cout << "Введите x: ";
	cin >> x;
	cout << "Введите y: ";
	cin >> y;

	float R = sqrt(x * x + y * y) * sin(x);
	float S = exp(x / y);

	cout << "R = " << R << endl;
	cout << "S = " << S << endl;

	float C = max(R, S);

	cout << "C = " << C << endl;

	return 0;
}