#include <iostream>
#include <vector>
#include <stdio.h>

const int low = 147981;
const int high = 691423;

int find(char c, char *pass) {
	int res = 0;
	for (int i = 0; i < 6; i++) {
		if (pass[i] == c) {
			res++;
		}
	}
	return res;
}

int checkIfGood(int num){
	char pass[6];
	sprintf(pass, "%d", num);
	//check if order is increasing
	char check = '1';
	for (char c : pass) {
		if (c >= check) {
			check = c;
		} else return 0;
	}
	// check for the repeating digits
	bool dubs = false;
	int i = 0;
	int seq = 1;
	while(i < sizeof(pass)-1) {
		if (pass[i] == pass[i+1]){
			seq++;
			i++;
			if (seq == 2) {
				if (pass[i] != pass[i+1] && i < sizeof(pass)){
					dubs = true;
					break;
				}
			}
		} else {
			seq = 1;
			i++;
		}
	}
	if(dubs) return 1;
	else return 0;
	
}

int main() {
	int test = 111122;
	int res = checkIfGood(test);
	if (res) printf("%d, das good\n", test);
	else printf("%d, das badd\n", test);
	int total = 0;
	for (int i = low; i < high; i++) {
		total = total + checkIfGood(i);
	}
	printf("total good passwords: %d", total);
}
