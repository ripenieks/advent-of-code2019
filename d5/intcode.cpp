#include <iostream>
#include <vector>
#include <stdio.h>
#include <climits>
#include <fstream>
#include <string.h>

using namespace std;

void intcode(vector<int> &rom);

static int ip = 0;
vector<int> rom;

enum ops {
	add=1, mult=2, inp=3, out=4, quit=99, jit=5, jif=6, lt=7, eq=8
};

int main() {
	cin.tie(0);
	char data[10000];
	memset(data, 0, sizeof(data));

	ifstream infile;
	infile.open("input");
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
	//cout << val << endl;
	//for (int x : rom) {
	//	cout << x << ",";
	//}
	//cout << endl;
	//cout << rom.size() << endl;
	intcode(rom);

//	for (int x : rom) {
//		cout << x << ",";
//	}
}

void intcode(vector<int> &rom) {
	int param1 = 0;
	int param2 = 0;
	int loc = 0;
	int ins;

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
