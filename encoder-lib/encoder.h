#pragma once
#define encode_output "output_encode.txt"
#define decode_output "output_decode.txt"

/*Код ошибки
* INVALID_FORMAT - неверный формат
*/
enum CODE_RESULT
{
	INVALID,
	OK
};

/*
Функция, реализующая кодирование строки в двоичный код.
* input - входная строка, которую необходимо закодировать.
* output - выходной вектор двоичного представления строки.
Функция возвращает код ошибки - OK или INVALID.
*/
CODE_RESULT Encode(std::string input, std::vector<bool>& output);

/*
Функция, реализующая кодирование строки в двоичный код.
* input - входная строка, которую необходимо закодировать.
* output - выходной вектор двоичного представления строки.
Функция возвращает код ошибки - OK или INVALID.
*/
CODE_RESULT Decode(std::vector<bool> input, std::string& output);