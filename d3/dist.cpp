#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>


using namespace std;

struct Point{
	int x;
	int y;
};

static std::vector<Point> collisions;

void compare(std::vector<Point> &w1, std::vector<Point> &w2) {
	printf("comparing");
	for (int i = 1; i < w1.size(); i++) {
		for (int j = 1; j < w2.size(); j++) {
			if (w1[i].x == w2[j].x && w1[i].y == w2[j].y) {
				printf("collision found");
				collisions.push_back(w1[i]);
			}
		}
	}
}

void move(char *command, std::vector<Point> &wirepoints) {

	char dir = command[0];
	int i = 1;
	char it = 0;
	int value = 0;
	while (command[i] != 0){
		it = command[i];
		value = 10*value + it - '0';
		i++;
	}
	
	Point currentPos = wirepoints.back();
	switch(dir){
		case 'R':
			for (i = 0; i < value; i++){
				Point p = wirepoints.back();
				p.x += 1;
				wirepoints.push_back(p);
			}
			break;
		case 'L':
			for (i = 0; i < value; i++){
				Point p = wirepoints.back();
				p.x -= 1;
				wirepoints.push_back(p);
			}
			break;
		case 'U':
			for (i = 0; i < value; i++){
				Point p = wirepoints.back();
				p.y += 1;
				wirepoints.push_back(p);
			}
			break;
		case 'D':
			for (i = 0; i < value; i++){
				Point p = wirepoints.back();
				p.y -= 1;
				wirepoints.push_back(p);
			}
			break;
	}
}

int main() {
	std::vector<Point> WIRE1;
	std::vector<Point> WIRE2;

	Point start;
	start.x = 0;
	start.y = 0;

	WIRE1.push_back(start);
	WIRE2.push_back(start);

	string wire1;
	string wire2;

	cin.tie(0);
	cin >> wire1;
	cin >> wire2;

	int w1Size = wire1.length();
	int w2Size = wire2.length();
	
	char w1[w1Size];
	char w2[w2Size];

	strcpy(w1, wire1.c_str());
	strcpy(w2, wire2.c_str());

	char delim[] = ",";

	char *ptr = strtok(w1, delim);
	while (ptr != nullptr) {
		move(ptr, WIRE1);
		ptr = strtok(nullptr, delim);
	}
	ptr = strtok(w2, delim);
	while (ptr != nullptr) {
		move(ptr, WIRE2);
		ptr = strtok(nullptr, delim);
	}
	
	printf("w1 size: %d,  w1 size: %d\n", WIRE1.size(), WIRE2.size());
	compare(WIRE1, WIRE2);
	int closest = 10000000;
	for (Point p : collisions) {
		printf("collision: [%d,%d]\n", p.x, p.y);
		if (p.x < 0) p.x = -p.x;
		if (p.y < 0) p.y = -p.y;
		int tmp = p.x + p.y;
		if (tmp < closest) {
			closest = tmp;
		}
	}
	printf("closest place: %d", closest);

}
