#include <iostream>
#include <vector>
#include <stdio.h>
#include <climits>
#include <fstream>
#include <string.h>

using namespace std;

void intcode(vector<int> &rom);
int intcode(vector<int> rom, vector<int> &inputs);

vector<int> rom;

vector<vector<int>> permutations;

enum ops {
	add=1, mult=2, inp=3, out=4, quit=99, jit=5, jif=6, lt=7, eq=8
};

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
	vector<int> arr = {0,1,2,3,4};
	HeapPermuts(arr, arr.size());
	int max = 0;

	for (vector<int> p : permutations) {
		int out = 0;
		vector<int> inp(2);

		for (int i = 0; i < p.size(); i++) {
			inp = {p[i], out};
			out = intcode(rom, inp);
		}
		if (out > max) {
			max = out;
		}
	}
	cout << max << endl;
	
}

int intcode(vector<int> rom, vector<int> &inputs) {
	int param1 = 0;
	int param2 = 0;
	int loc = 0;
	int ins;
	int inpIT = 0;
	int output = -99;
	int ip = 0;

	while (ip < rom.size()) {
		ins = rom[ip] % 100;
		switch(ins){
			case add:
				if ( rom[ip] % 1000 > 100) {
					param1 = rom[ip+1];
				} else {
					param1 = rom[rom[ip+1]];
				}
				if (rom[ip]%10000 > 1000) {
					param2 = rom[ip+2];
				} else {
					param2 = rom[rom[ip+2]];
				}
				loc = rom[ip+3];
				rom[loc] = param1 + param2;
				ip = ip + 4;
				break;
			case mult:
				if ( rom[ip] % 1000 > 100) {
					param1 = rom[ip+1];
				} else {
					param1 = rom[rom[ip+1]];
				}
				if (rom[ip]%10000 > 1000) {
					param2 = rom[ip+2];
				} else {
					param2 = rom[rom[ip+2]];
				}
				loc = rom[ip+3];
				rom[loc] = param1 * param2;
				ip = ip + 4;
				break;
			case inp:
				int tmp;
				//cin.tie(0);
				//cout << "input number: ";
				//cin >> tmp;
				param1 = rom[ip+1];
				rom[param1] = inputs[inpIT++];
				ip = ip + 2;
				break;
			case out:
				if (rom[ip] % 1000 > 100) {
					param1 = rom[ip+1];
				} else {
					param1 = rom[rom[ip+1]];
				}
				//cout << "OUTPUT: " << param1 << endl;
				output = param1;
				ip = ip+2;
				break;
			case jit:
				if ( rom[ip] % 1000 > 100) {
					param1 = rom[ip+1];
				} else {
					param1 = rom[rom[ip+1]];
				}
				if (rom[ip]%10000 > 1000) {
					param2 = rom[ip+2];
				} else {
					param2 = rom[rom[ip+2]];
				}
				if (param1 != 0) {
					ip = param2;
				} else {
					ip = ip + 3;
				}
				break;
			case jif:
				if ( rom[ip] % 1000 > 100) {
					param1 = rom[ip+1];
				} else {
					param1 = rom[rom[ip+1]];
				}
				if (rom[ip]%10000 > 1000) {
					param2 = rom[ip+2];
				} else {
					param2 = rom[rom[ip+2]];
				}
				if (param1 == 0) {
					ip = param2;
				} else {
					ip = ip + 3;
				}
				break;
			case lt:
				if ( rom[ip] % 1000 > 100) {
					param1 = rom[ip+1];
				} else {
					param1 = rom[rom[ip+1]];
				}
				if (rom[ip]%10000 > 1000) {
					param2 = rom[ip+2];
				} else {
					param2 = rom[rom[ip+2]];
				}
				loc = rom[ip+3];

				if (param1 < param2) {
					rom[loc] = 1;
				} else {
					rom[loc] = 0;
				}
				ip = ip + 4;
				break;
			case eq:
				if ( rom[ip] % 1000 > 100) {
					param1 = rom[ip+1];
				} else {
					param1 = rom[rom[ip+1]];
				}
				if (rom[ip]%10000 > 1000) {
					param2 = rom[ip+2];
				} else {
					param2 = rom[rom[ip+2]];
				}
				loc = rom[ip+3];
				if (param1 == param2) {
					rom[loc] = 1;
				} else {
					rom[loc] = 0;
				}
				ip = ip + 4;
				break;
			case quit:
				//cout << "exit op" << endl;
				return output;
			default:
				//cout << "bad op: " << rom[ip] << endl;
				return -99;
		}
	}
	return -99;
}

void intcode(vector<int> &rom) {
	int param1 = 0;
	int param2 = 0;
	int loc = 0;
	int ins;
	int ip = 0;

	while (ip < rom.size()) {
		ins = rom[ip] % 100;
		switch(ins){
			case add:
				if ( rom[ip] % 1000 > 100) {
					param1 = rom[ip+1];
				} else {
					param1 = rom[rom[ip+1]];
				}
				if (rom[ip]%10000 > 1000) {
					param2 = rom[ip+2];
				} else {
					param2 = rom[rom[ip+2]];
				}
				loc = rom[ip+3];
				rom[loc] = param1 + param2;
				ip = ip + 4;
				break;
			case mult:
				if ( rom[ip] % 1000 > 100) {
					param1 = rom[ip+1];
				} else {
					param1 = rom[rom[ip+1]];
				}
				if (rom[ip]%10000 > 1000) {
					param2 = rom[ip+2];
				} else {
					param2 = rom[rom[ip+2]];
				}
				loc = rom[ip+3];
				rom[loc] = param1 * param2;
				ip = ip + 4;
				break;
			case inp:
				int tmp;
				cin.tie(0);
				cout << "input number: ";
				cin >> tmp;
				param1 = rom[ip+1];
				rom[param1] = tmp;
				ip = ip + 2;
				break;
			case out:
				if (rom[ip] % 1000 > 100) {
					param1 = rom[ip+1];
				} else {
					param1 = rom[rom[ip+1]];
				}
				cout << "OUTPUT: " << param1 << endl;
				ip = ip+2;
				break;
			case jit:
				if ( rom[ip] % 1000 > 100) {
					param1 = rom[ip+1];
				} else {
					param1 = rom[rom[ip+1]];
				}
				if (rom[ip]%10000 > 1000) {
					param2 = rom[ip+2];
				} else {
					param2 = rom[rom[ip+2]];
				}
				if (param1 != 0) {
					ip = param2;
				} else {
					ip = ip + 3;
				}
				break;
			case jif:
				if ( rom[ip] % 1000 > 100) {
					param1 = rom[ip+1];
				} else {
					param1 = rom[rom[ip+1]];
				}
				if (rom[ip]%10000 > 1000) {
					param2 = rom[ip+2];
				} else {
					param2 = rom[rom[ip+2]];
				}
				if (param1 == 0) {
					ip = param2;
				} else {
					ip = ip + 3;
				}
				break;
			case lt:
				if ( rom[ip] % 1000 > 100) {
					param1 = rom[ip+1];
				} else {
					param1 = rom[rom[ip+1]];
				}
				if (rom[ip]%10000 > 1000) {
					param2 = rom[ip+2];
				} else {
					param2 = rom[rom[ip+2]];
				}
				loc = rom[ip+3];

				if (param1 < param2) {
					rom[loc] = 1;
				} else {
					rom[loc] = 0;
				}
				ip = ip + 4;
				break;
			case eq:
				if ( rom[ip] % 1000 > 100) {
					param1 = rom[ip+1];
				} else {
					param1 = rom[rom[ip+1]];
				}
				if (rom[ip]%10000 > 1000) {
					param2 = rom[ip+2];
				} else {
					param2 = rom[rom[ip+2]];
				}
				loc = rom[ip+3];
				if (param1 == param2) {
					rom[loc] = 1;
				} else {
					rom[loc] = 0;
				}
				ip = ip + 4;
				break;
			case quit:
				cout << "exit op" << endl;
				return;
			default:
				cout << "bad op: " << rom[ip] << endl;
				return;
		}
	}
}
