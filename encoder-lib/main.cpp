#include <iostream>
#include <vector>
#include "encoder.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "ru");

	vector<bool> data = { 0, 1, 1, 0, 0, 1 };				// Входные данные
	vector<bool> encoded, decoded;
	CODE_RESULT result_encode = Encode(data, encoded);		// Закодированные данные
	CODE_RESULT result_decode = Decode(encoded, decoded);	// Декодированные данные

	// Вывод результатов
	cout << "Input: ";
	for (const auto& bit : data)
		cout << bit;
	cout << endl;

	cout << "Encoded: ";
	for (const auto& bit : encoded)
		cout << bit;
	cout << " - полученный код" << endl;
	cout << "Encoded: 00111001001101 - ожидаемый код" << endl;

	cout << "Decoded: ";
	for (const auto& bit : decoded)
		cout << bit;
	cout << endl;

	int exit;
	cin >> exit;
}