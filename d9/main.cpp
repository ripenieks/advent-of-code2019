#include <iostream>
#include <vector>
#include <stdio.h>
#include <climits>
#include <fstream>
#include <string.h>
#include "intcode.h"

using namespace std;

vector<vector<int>> permutations;

void HeapPermuts(vector<int> &arr, int size) {
	if (size == 1) {
		permutations.push_back(arr);
		return;
	}
	for (int i = 0; i < size ; i++) {
		HeapPermuts(arr, size-1);

		if (size%2==1) {
			swap(arr[0], arr[size-1]);
		} else {
			swap(arr[i], arr[size-1]);
		}
	}
}

int main(int argc, char* argv[]) {
	cin.tie(0);
	vector<int> rom;
	if (argc < 2) {
		printf("filename: \n");
		exit(-1);
	}
	char data[10000];
	memset(data, 0, sizeof(data));

	ifstream infile;
	infile.open(argv[1]);
	if (!infile) {
		printf("no such file friendo\n");
		exit(-1);
	}
	infile >> data;
	infile.close();
	int val = 0;
	char c = '0';
	bool neg = false;
	int i = 0;
	while (c != EOF && c != '\n' && c != '\0') {
		c = data[i++];
		if (c == ',' || c == '\n' || c == '\0') {
			if (!neg) {
				rom.push_back(val);
				val = 0;
			} else {
				rom.push_back(-val);
				val = 0;
				neg = false;
			}
			continue;
		}
		if (c == '-') {
			neg = true;
			continue;
		}
		if (c == EOF) break;
		val = 10*val+c-'0';
	}
	intcode(rom);
}

