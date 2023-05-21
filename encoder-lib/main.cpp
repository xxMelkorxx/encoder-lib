#include <iostream>
#include <vector>
#include "encoder.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	vector<bool> encoded, decoded, bits;

	cout << "Декодирование пороговым методом" << endl;

	// Входные данные.
	string input = "Hello, World!";
	cout << "Message: " << input << endl;
	ConvertToVectorBits(input, bits);
	// Кодирование данных.
	Encode(bits, encoded);
	// Вывод результатов
	cout << "Input: ";
	for (const auto& bit : bits)
		cout << bit;
	cout << endl;
	cout << "Encoded: ";
	for (const auto& bit : encoded)
		cout << bit;
	cout << endl;
	// Добавление ошибки в последовательность.
	encoded[3] = !encoded[3];
	encoded[5] = !encoded[5];
	encoded[25] = !encoded[25];
	encoded[31] = !encoded[31];
	encoded[50] = !encoded[50];
	encoded[62] = !encoded[62];
	cout << "Encoded: ";
	for (const auto& bit : encoded)
		cout << bit;
	cout << " - код с ошибкой" << endl;
	// Декодированние данных.
	Decode(encoded, decoded);
	cout << "Decoded: ";
	for (const auto& bit : decoded)
		cout << bit;
	cout << endl;
	// Конвертация битовой последовательности в строку.
	string output;
	ConvertToString(decoded, output);
	cout << "Decode message: " << output << endl;

	//##########################################################################################
	bits.clear();
	encoded.clear();
	decoded.clear();

	// Входные данные.
	bits = { 1, 0, 0, 0, 0, 0 };
	// Кодирование данных.
	Encode(bits, encoded);
	cout << "\nInput: ";
	for (const auto& bit : bits)
		cout << bit;
	cout << " - входная последовательность код" << endl;
	cout << "Encoded: ";
	for (const auto& bit : encoded)
		cout << bit;
	cout << " - полученный код" << endl;
	cout << "Encoded: 1101110000000000 - ожидаемый код" << endl;
	// Добавление ошибки в последовательность.
	encoded[3] = !encoded[3];
	encoded[5] = !encoded[5];
	cout << "Encoded: ";
	for (const auto& bit : encoded)
		cout << bit;
	cout << " - код с ошибкой" << endl;
	// Декодированние данных.
	Decode(encoded, decoded);
	cout << "Decoded: ";
	for (const auto& bit : decoded)
		cout << bit;
	cout << endl;
	
	int exit;
	cin >> exit;
}