#include <iostream>
#include <vector>
#include <stdio.h>
#include <climits>
#include <fstream>
#include <string.h>

using namespace std;

int intcode(vector<int> rom, vector<int> &inputs);
int intcode(struct image &img, int input);

vector<int> rom;

vector<vector<int>> permutations;

struct image {
	vector<int> rom;
	int ip;
	int mode;
};

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
	vector<int> arr = {5,6,7,8,9};
	HeapPermuts(arr, arr.size());
	int max = 0;
	struct image img1, img2,img3,img4,img5;
	img1 = img2 = img3 = img4 = img5 = {rom,0};

	for (vector<int> p : permutations) {
		int num = 0;
		struct image img1, img2,img3,img4,img5;
		img1 = img2 = img3 = img4 = img5 = {rom,0};
		img1.mode = p[0];
		img2.mode = p[1];
		img3.mode = p[2];
		img4.mode = p[3];
		img5.mode = p[4];
		while (num != -99){
			num = intcode(img1, num);
			if (num > max) max = num;
			num = intcode(img2, num);
			if (num > max) max = num;
			num = intcode(img3, num);
			if (num > max) max = num;
			num = intcode(img4, num);
			if (num > max) max = num;
			num = intcode(img5, num);
			if (num > max) max = num;
		}

	}
	cout << max << endl;
	
}

int intcode(struct image &img, int input) {
	int param1 = 0;
	int param2 = 0;
	int loc = 0;
	int ins;
	int output = -99;

	while (img.ip < img.rom.size()) {
		ins = img.rom[img.ip] % 100;
		switch(ins){
			case add:
				if ( img.rom[img.ip] % 1000 > 100) {
					param1 = img.rom[img.ip+1];
				} else {
					param1 = img.rom[img.rom[img.ip+1]];
				}
				if (rom[img.ip]%10000 > 1000) {
					param2 = img.rom[img.ip+2];
				} else {
					param2 = img.rom[img.rom[img.ip+2]];
				}
				loc = img.rom[img.ip+3];
				img.rom[loc] = param1 + param2;
				img.ip = img.ip + 4;
				break;
			case mult:
				if ( img.rom[img.ip] % 1000 > 100) {
					param1 = img.rom[img.ip+1];
				} else {
					param1 = img.rom[img.rom[img.ip+1]];
				}
				if (rom[img.ip]%10000 > 1000) {
					param2 = img.rom[img.ip+2];
				} else {
					param2 = img.rom[img.rom[img.ip+2]];
				}
				loc = img.rom[img.ip+3];
				img.rom[loc] = param1 * param2;
				img.ip = img.ip + 4;
				break;
			case inp:
				int tmp;
				//cin.tie(0);
				//cout << "input number: ";
				//cin >> tmp;
				param1 = img.rom[img.ip+1];
				if (img.mode) {
					img.rom[param1] = img.mode;
					img.mode = 0;
				} else {
					img.rom[param1] = input;
				}
				img.ip = img.ip + 2;
				break;
			case out:
				if (img.rom[img.ip] % 1000 > 100) {
					param1 = img.rom[img.ip+1];
				} else {
					param1 = img.rom[img.rom[img.ip+1]];
				}
				cout << "OUTPUT: " << param1 << endl;
				output = param1;
				img.ip = img.ip+2;
				return output;
			case jit:
				if ( img.rom[img.ip] % 1000 > 100) {
					param1 = img.rom[img.ip+1];
				} else {
					param1 = img.rom[img.rom[img.ip+1]];
				}
				if (img.rom[img.ip]%10000 > 1000) {
					param2 = img.rom[img.ip+2];
				} else {
					param2 = img.rom[img.rom[img.ip+2]];
				}
				if (param1 != 0) {
					img.ip = param2;
				} else {
					img.ip = img.ip + 3;
				}
				break;
			case jif:
				if ( img.rom[img.ip] % 1000 > 100) {
					param1 = img.rom[img.ip+1];
				} else {
					param1 = img.rom[img.rom[img.ip+1]];
				}
				if (img.rom[img.ip]%10000 > 1000) {
					param2 = img.rom[img.ip+2];
				} else {
					param2 = img.rom[img.rom[img.ip+2]];
				}
				if (param1 == 0) {
					img.ip = param2;
				} else {
					img.ip = img.ip + 3;
				}
				break;
			case lt:
				if ( img.rom[img.ip] % 1000 > 100) {
					param1 = img.rom[img.ip+1];
				} else {
					param1 = img.rom[img.rom[img.ip+1]];
				}
				if (img.rom[img.ip]%10000 > 1000) {
					param2 = img.rom[img.ip+2];
				} else {
					param2 = img.rom[img.rom[img.ip+2]];
				}
				loc = img.rom[img.ip+3];

				if (param1 < param2) {
					img.rom[loc] = 1;
				} else {
					img.rom[loc] = 0;
				}
				img.ip = img.ip + 4;
				break;
			case eq:
				if ( img.rom[img.ip] % 1000 > 100) {
					param1 = img.rom[img.ip+1];
				} else {
					param1 = img.rom[img.rom[img.ip+1]];
				}
				if (img.rom[img.ip]%10000 > 1000) {
					param2 = img.rom[img.ip+2];
				} else {
					param2 = img.rom[img.rom[img.ip+2]];
				}
				loc = img.rom[img.ip+3];
				if (param1 == param2) {
					img.rom[loc] = 1;
				} else {
					img.rom[loc] = 0;
				}
				img.ip = img.ip + 4;
				break;
			case quit:
				//cout << "exit op" << endl;
				return -99;
			default:
				//cout << "bad op: " << rom[img.ip] << endl;
				return -99;
		}
	}
	return -99;
}

