#include <string>
#include <vector>
#include <map>
#include <bitset>
#include "encoder.h"
using namespace std;

map<vector<bool>, vector<bool>> states = {
	{{1, 1}, {0, 1}},

};

CODE_RESULT Encode(const string input, vector<bool>& output, vector<bool>& bits) {
	if (input.size() == 0) {
		return INVALID_INPUT;
	}
	
	//vector<bool> bits;
    // ����������� ������ � ������������������ ����� � ���� �������.
    for (const auto& c : input) {
        bitset<8> binary_ascii(c);
        for (int i = 7; i >= 0; --i)
            bits.push_back(binary_ascii[i]);
    }

    // �������������� ������ ����� ������� ������.
	bits.push_back(0);
	bits.push_back(0);
    vector<bool> encoded(bits.size() * 2);

	vector<bool> state(2, 0);
	for (int i = 0; i < bits.size(); i++) {
		bool b1 = bits[i] ^ state[1];
		bool b2 = bits[i] ^ state[0] ^ state[1];
		encoded[i * 2] = b1;
		encoded[i * 2 + 1] = b2;
		state[0] = bits[i];
		state[1] = b1 ^ b2;
	}

    output.assign(encoded.begin(), encoded.end());

	return OK;
}

CODE_RESULT Encode(const vector<bool>input, vector<bool>& output) {
	if (input.size() == 0) {
		return INVALID_INPUT;
	}

    vector<bool> bits;
    bits.assign(input.begin(), input.end());
    bits.push_back(0);
    bits.push_back(0);
    vector<bool> encoded(bits.size() * 2);

    vector<bool> state(2, 0);
    for (int i = 0; i < bits.size(); i++) {
		bool b1 = bits[i] ^ state[1];
		bool b2 = bits[i] ^ state[0] ^ state[1];
        encoded[i * 2] = b1;
        encoded[i * 2 + 1] = b2;
		state[0] = bits[i];
		state[1] = b1 ^ b2;
    }

    output.assign(encoded.begin(), encoded.end());

    return OK;
}

CODE_RESULT Decode(const vector<bool> input, string& output) {
    vector<bool> bits(input.size() / 2);

    // �������������.

    // ����������� ����� ����� � ASCII-��� ��������
    for (int i = 0; i < bits.size(); i += 8) {
        bitset<8> byte;
        for (int j = 0; j < 8; ++j) {
            if (bits[i + j])
                byte.set(7 - j);
        }
        output += static_cast<char>(byte.to_ulong());
    }

	return OK;
}

// ������� f1 = (1, 1)
const vector<int> f1 = { 1, 1 };
// ������� f2 = (1, 0, 1)
const vector<int> f2 = { 1, 0, 1 };

CODE_RESULT Decode(vector<bool> input, vector<bool>& output) {
	vector<bool> a;
	// ��������� �������������� ������������������.
	for (int i = 0; i < input.size() / 2; i++) {
		a.push_back(input[i * 2] ^ input[i * 2 + 1]);
	}
	a.insert(a.begin(), 0);
	a.push_back(0);

	vector<bool> u(a.begin() + 2, a.end() - 2);
	u.push_back(0);
	u.push_back(0);

	// b1 - ���� �� ���������� ������������������; b1 ���� �� ������ ��������.
	vector<bool> b1, b1d;
	for (int i = 0; i < u.size(); i++) {
		b1.push_back(input[i * 2]);
		b1d.push_back(u[i] ^ a[i]);
	}

	// �������� �� ������������ ��� �����.
	for (int i = 0; i < u.size() - 2; i++) {
		if (b1[i] != b1d[i] && b1[i + 2] != b1d[i + 2]) {
			u[i] = !u[i];
			b1d[i + 2] = !b1d[i + 2];
		}
	}

	output.assign(u.begin(), u.end() - 2);

	//const int num_states = 4;  // ���������� ��������� �������� ������ (2 ����)

	//// ������������� ������� ������ ��������� ����������
	//vector<vector<int>> metrics(num_states, vector<int>(2, 0));

	//// ���������� ��� ���������� ���� �� ������ �������
	//vector<vector<int>> trellis(num_states, vector<int>(2, 0));

	//// �������� �� ���� ����� ������� ������������������
	//for (int i = 0; i < input.size() / 2; ++i) {
	//	// �������� �� ���� ��������� ����������
	//	for (int j = 0; j < num_states; ++j) {
	//		// �������� �� ���� ��������� ������� ��������
	//		for (int k = 0; k <= 1; ++k) {
	//			// ������������ ������� ��� ���������� ���������
	//			int next_state = (j & 1) << 1 | k;
	//			int expected_output1 = (f1[0] & next_state) ^ (f1[1] & next_state >> 1) ^ k;
	//			int expected_output2 = (f2[0] & next_state) ^ (f2[1] & next_state >> 1) ^ (f2[2] & j >> 1) ^ k;

	//			int metric = metrics[j][k] + (expected_output1 != input[i * 2]) + (expected_output2 != input[i * 2 + 1]);

	//			if (i == 0 || metric < metrics[next_state][k]) {
	//				// ��������� ������ ������� � ���� �� ���������
	//				metrics[next_state][k] = metric;
	//				trellis[next_state][k] = j;
	//			}
	//		}
	//	}
	//}

	//// ������� ���� � ������ ��������
	//int best_state = -1;
	//int best_metric = -1;

	//for (int j = 0; j < num_states; ++j) {
	//	if (best_state == -1 || metrics[j][0] + metrics[j][1] < best_metric) {
	//		best_state = j;
	//		best_metric = metrics[j][0] + metrics[j][1];
	//	}
	//}

	//// ��������������� ���� �������������
	//vector<int> decoded_indexes(input.size() / 2);
	//for (int i = input.size() / 2 - 1; i >= 0; --i) {
	//	decoded_indexes[i] = trellis[best_state][input[i * 2 + 1]];
	//	best_state = decoded_indexes[i];
	//}

	//// ���������� �������������� ������ � �������� �������
	//vector<bool> decoded(input.size() / 2);
	//for (int i = 0; i < input.size() / 2; ++i)
	//	decoded[i] = decoded_indexes[decoded_indexes.size() - i - 1] & 1;

	//output.assign(decoded.begin(), decoded.end());

	return OK;
}