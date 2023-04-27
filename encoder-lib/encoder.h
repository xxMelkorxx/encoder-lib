#pragma once
#define encode_output "output_encode.txt"
#define decode_output "output_decode.txt"

/*��� ������
* INVALID_FORMAT - �������� ������
*/
enum CODE_RESULT
{
	INVALID,
	OK
};

/*
�������, ����������� ����������� ������ � �������� ���.
* input - ������� ������, ������� ���������� ������������.
* output - �������� ������ ��������� ������������� ������.
������� ���������� ��� ������ - OK ��� INVALID.
*/
CODE_RESULT Encode(std::string input, std::vector<bool>& output);

/*
�������, ����������� ����������� ������ � �������� ���.
* input - ������� ������, ������� ���������� ������������.
* output - �������� ������ ��������� ������������� ������.
������� ���������� ��� ������ - OK ��� INVALID.
*/
CODE_RESULT Decode(std::vector<bool> input, std::string& output);