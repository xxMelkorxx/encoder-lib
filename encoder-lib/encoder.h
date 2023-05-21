#pragma once

/*��� ������
* INVALID_INPUT - �������� ������� �������� (������ ������).
* OK - ��������� ���������� ��� ������.
*/
enum CODE_RESULT
{
	INVALID_INPUT,
	OK
};

/*
�������, �������������� ������ � ������ �����.
* input - ������� ������.
* output - �������� ������ �������� ������������� ������.
*/
CODE_RESULT ConvertToVectorBits(std::string input, std::vector<bool>& output);

/*
�������, �������������� ������������������ ����� � ������.
* input - ������� ������.
* output - �������� ������ �������� ������������� ������.
*/
CODE_RESULT ConvertToString(std::vector<bool> input, std::string& output);

/*
�������, ����������� ����������� ������ � �������� ���.
* input - ������� ������ ������� ������������������.
* output - �������� ������ ������� ������������������.
������� ���������� ��� ������ - OK ��� INVALID.
*/
CODE_RESULT Encode(std::vector<bool>input, std::vector<bool>& output);

/*
�������, ����������� ����������� ������ � �������� ���.
* input - ������� ������ ������������ ������� ������������������.
* output - �������� ������ �������������� ������� ������������������.
������� ���������� ��� ������ - OK ��� INVALID.
*/
CODE_RESULT Decode(std::vector<bool> input, std::vector<bool>& output);