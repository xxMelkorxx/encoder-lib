#include <iostream>
#include <vector>
#include "encoder.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	vector<bool> encoded, decoded, bits;

	//// Входные данные.
	//string str = "Hello";

	//// Кодирование данных.
	//CODE_RESULT result = Encode(str, encoded, bits);
	//if (result == OK) {

	//	// Вывод результатов
	//	cout << "Input: ";
	//	for (const auto& bit : bits)
	//		cout << bit;
	//	cout << " - это битовое представление: \"" << str << "\"" << endl;
	//	cout << "Encoded: ";
	//	for (const auto& bit : encoded)
	//		cout << bit;
	//	cout << " - полученный код" << endl;

	//	// Декодированние данных.
	//	CODE_RESULT result = Decode(encoded, decoded);
	//	if (result == OK) {
	//		cout << "Decoded: ";
	//		for (const auto& bit : decoded)
	//			cout << bit;
	//		cout << endl << endl;
	//	}
	//}
	//else if (result == INVALID_INPUT) {
	//	cout << "Ошибка: Неверный входной параметр!" << endl;
	//}

	//##########################################################################################
	bits.clear();
	encoded.clear();
	decoded.clear();

	// Входные данные.
	bits = { 0, 1, 1, 0, 0, 1 };

	// Кодирование данных.
	CODE_RESULT result = Encode(bits, encoded);
	if (result == OK) {
		cout << "Input: ";
		for (const auto& bit : bits)
			cout << bit;
		cout << " - входная последовательность код" << endl;

		cout << "Encoded: ";
		for (const auto& bit : encoded)
			cout << bit;
		cout << " - полученный код" << endl;
		cout << "Encoded: 0011101011110111 - ожидаемый код" << endl;

		// Добавляем ошибку в последовательность.
		encoded[10] = !encoded[10];
		cout << "Encoded: ";
		for (const auto& bit : encoded)
			cout << bit;
		cout << " - код с ошибкой" << endl;

		// Декодированние данных.
		result = Decode(encoded, decoded);
		if (result == OK) {
			cout << "Decoded: ";
			for (const auto& bit : decoded)
				cout << bit;
		}
		cout << " - декодированный код" << endl;
	}
	else if (result == INVALID_INPUT) {
		cout << "Ошибка: Неверный входной параметр!" << endl;
	}

	int exit;
	cin >> exit;
}