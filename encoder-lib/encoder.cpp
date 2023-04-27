#include <string>
#include <vector>
#include <map>
#include <queue>
#include <iostream>
#include <fstream>
#include "encoder.h"
using namespace std;

class huffman_tree_node {
private:
	char data;										// Символ
	unsigned freq;									// Частота
	huffman_tree_node* left, * right;				// Левый и правый потомок
	friend class huffman_coding;
public:
	huffman_tree_node(char _data, unsigned _freq) {
		this->left = this->right = NULL;
		this->data = _data;
		this->freq = _freq;
	}
	~huffman_tree_node() {
		delete left;
		delete right;
	}
};

typedef huffman_tree_node* pointer_huffman;

class huffman_coding {
private:
	pointer_huffman root_main;
	map<char, string> replace_abc;
	string encode;
	string decode;
public:
	struct compare {
		bool operator()(huffman_tree_node* left, huffman_tree_node* right) {
			return (left->freq > right->freq);
		}
	};
	void HuffmanCodes(string data, int freq[]);									// Кодирование.
	void encode_text(string text);												// Кодирование-замена в самой стринге.
	string get_encode();														// Возврат encode строки.
	void output_file(string filename, bool flag);								// Вывод в файл
	string decode_text(string str, bool flag_ex);								// Раскодирование через дерево
};

/* Функция, которая строит дерево Хаффмана и печатает коды обходя это построенное Дерево Хаффмана */
void huffman_coding::HuffmanCodes(string data, int freq[])
{
	pointer_huffman left, right, top;

	// Создаем узлы с данными и частотой (учитывая compare функцию сравнения)
	priority_queue<pointer_huffman, vector<huffman_tree_node*>, compare> min_heap;
	for (int i = 0; i < data.size(); ++i) {
		pointer_huffman temp = new huffman_tree_node(data[i], freq[i]);
		min_heap.push(temp);
	}

	// Пока размер очереди не дойдёт до единицы.
	while (min_heap.size() != 1) {
		// Достаем два минимальных по частоте элемента из дерева.
		left = min_heap.top();
		min_heap.pop();

		right = min_heap.top();
		min_heap.pop();

		// Создаем новый узел с частотой, равной сумме двух частот узлов c наименьшей частотой.
		top = new huffman_tree_node('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		min_heap.push(top);
	}
}

/* Кодирование текста */
void huffman_coding::encode_text(string text) {
	for (int i = 0; i < text.size(); i++) {
		for (auto it = replace_abc.begin(); it != replace_abc.end(); ++it) {
			if (text[i] == it->first) {
				encode += it->second;
			}
		}
	}
}

/* Получение кодовой строки */
string huffman_coding::get_encode() {
	return encode;
}

/* Вывод текста в файл*/
void huffman_coding::output_file(string filename, bool flag) {
	fstream file;
	file.open(filename, ios::out);
	if (flag) {
		for (int i = 0; i < encode.size(); i++) {
			file << encode[i];
		}
	}
	else {
		for (int i = 0; i < decode.size(); i++) {
			file << decode[i];
		}
	}
	file.close();
}

/* Раскодирование текста */
string huffman_coding::decode_text(string str, bool flag_ex)
{
	int main_counter = 0;
	decode = "";
	for (int i = main_counter; i < str.size();) {
		pointer_huffman temp = root_main;
		while (true) {
			if (str[i] == '0') {
				if (temp->left != NULL) {
					temp = temp->left;
				}
				else {
					decode += temp->data;
					break;
				}
			}
			else {
				if (temp->right != NULL) {
					temp = temp->right;
				}
				else {
					decode += temp->data;
					break;
				}
			}
			i++;
			main_counter = i;
		}

		if (flag_ex) {
			i++;
		}
		else {
			i = main_counter;
		}
	}
	return decode;
}

/* Создание алфавита */
string get_repeat(string text) {
	string abc;
	bool exit_flag = 0;
	abc.push_back(text[0]);
	for (int i = 1; i < text.size(); i++) {
		exit_flag = 0;
		for (int j = 0; j < abc.size(); j++) {
			// Если в нашем алфавите уже есть такая буква, то выходим из цикла.
			if (abc[j] == text[i]) {
				exit_flag = 1;
				break;
			}
		}
		// Если мы находили букву ранее, то переходим на следующую итерацию для следующей буквы.
		if (exit_flag == 1)	continue;
		// Если буква найдена не была, то добавляем в алфавит. 
		else {
			abc.push_back(text[i]);
			continue;
		}
	}
	return abc;
}

/* Получение массива частоты использования символов */
void get_frequency(string text, int* frequencies, string abc) {
	for (int i = 0; i < abc.size(); i++) {
		frequencies[i] = 0;
	}
	for (int j = 0; j < abc.size(); j++) {
		for (int i = 0; i < text.size(); i++) {
			if (abc[j] == text[i]) {
				frequencies[j]++;
			}
		}
	}
}

CODE_RESULT Encode(string input, vector<bool>& output) {
	// Получаем массив частот.
	string abc = get_repeat(input);
	int* frequencies = new int[abc.size()];
	get_frequency(input, frequencies, abc);

	/* Кодирование */
	huffman_coding encoding;
	encoding.HuffmanCodes(abc, frequencies);
	string temp = encoding.get_encode();
	for (char& c : temp) {
		output.push_back(c != '0');
	}
	encoding.output_file(encode_output, true);

	return OK;
}

CODE_RESULT Decode(vector<bool> input, string& output) {
	/* Обработка исключения: один символ */

	bool flag_ex = 0;
	string abc = "fdfdfdsfsd";
	if (abc.size() < 2)
	{
		flag_ex = !flag_ex;
	}

	string str;
	for (int i = 0; i < input.size(); i++) {
		str.push_back(input[i] ? '1' : '0');
	}

	huffman_coding encoding;
	encoding.decode_text(str, flag_ex);
	encoding.output_file(decode_output, false);

	return OK;
}