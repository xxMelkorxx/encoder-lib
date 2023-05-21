#pragma once

/*Код ошибки
* INVALID_INPUT - неверный входной параметр (пустой вектор).
* OK - результат выполнения без ошибок.
*/
enum CODE_RESULT
{
	INVALID_INPUT,
	OK
};

/*
Функция, конвертирующая строку в вектор битов.
* input - входная строка.
* output - выходной вектор битового представления строки.
*/
CODE_RESULT ConvertToVectorBits(std::string input, std::vector<bool>& output);

/*
Функция, конвертирующая последовательность битов в строку.
* input - входная строка.
* output - выходной вектор битового представления строки.
*/
CODE_RESULT ConvertToString(std::vector<bool> input, std::string& output);

/*
Функция, реализующая кодирование строки в двоичный код.
* input - входной вектор битовой последовательности.
* output - выходной вектор битовой последовательности.
Функция возвращает код ошибки - OK или INVALID.
*/
CODE_RESULT Encode(std::vector<bool>input, std::vector<bool>& output);

/*
Функция, реализующая кодирование строки в двоичный код.
* input - входной вектор кодированных битовой последовательности.
* output - выходной вектор декодированных битовой последовательности.
Функция возвращает код ошибки - OK или INVALID.
*/
CODE_RESULT Decode(std::vector<bool> input, std::vector<bool>& output);