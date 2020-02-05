#include <iostream>
#include "intcode.h"

enum ops {
	add=1, mult=2, inp=3, out=4, quit=99, jit=5, jif=6, lt=7, eq=8
};

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
				if (img.rom[img.ip]%10000 > 1000) {
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
				if (img.rom[img.ip]%10000 > 1000) {
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
				std::cout << "OUTPUT: " << param1 << std::endl;
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

int intcode(std::vector<int> rom) {
	int param1 = 0;
	int param2 = 0;
	int loc = 0;
	int ins;
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
				std::cin.tie(0);
				std::cout << "input number: ";
				std::cin >> tmp;
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
				std::cout << "OUTPUT: " << param1 << std::endl;
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
				return -99;
			default:
				//cout << "bad op: " << rom[ip] << endl;
				return -99;
		}
	}
	return -99;
}
