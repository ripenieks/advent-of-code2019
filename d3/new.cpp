#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int ifNumBetween(int x, int num1, int num2)
{
	int max, min;
	if (num1 >= num2) {
		max = num1;
		min = num2;
	} else {
		max = num2;
		min = num1;
	}
	if (x < max && x > min) {
		return 1;
	} else {
		return 0;
	}
}

struct Point {
	Point() {}
	Point(int x, int y) : x(x),y(y) {}
	int x;
	int y;
};
vector<Point> collisions;

void findCollisions(vector<Point> w1, vector<Point> w2)
{
	for (int i = 1; i < w1.size(); i++) {
		for (int j = 1; j < w2.size(); j++) {
			if ((w1[i].x == w1[i-1].x && w2[j].x == w2[j-1].x) || (w1[i].y == w1[i-1].y && w2[j].y == w2[j-1].y)) {
// lines are parallel therefore no intersection
//printf("lines w1[%d, %d | %d, %d], w2 [%d, %d || %d, %d]\n", w1[i-1].x, w1[i-1].y, w1[i].x, w1[i].y, \
				w2[j-1].x, w2[j-1].y, w2[j].x, w2[j].y);
				continue;
			}
			//printf("lines w1[%d, %d | %d, %d], w2 [%d, %d | %d, %d]\n", w1[i-1].x, w1[i-1].y, w1[i].x, w1[i].y, \
			       w2[j-1].x, w2[j-1].y, w2[j].x, w2[j].y);
			if (w1[i-1].x == w1[i].x) {
				if ((ifNumBetween(w1[i].x, w2[j-1].x, w2[j].x)) && (ifNumBetween(w2[j].y, w1[i-1].y, w1[i].y))) {
					Point p(w1[i].x, w2[j].y);
					printf("collision at point [%d, %d]\n", p.x, p.y);
					collisions.push_back(p);
				}
			}
			if (w1[i-1].y == w1[i].y) {
				if ((ifNumBetween(w1[i].y, w2[j-1].y, w2[j].y)) && (ifNumBetween(w2[j].x, w1[i-1].x, w1[i].x))) {
					Point p(w2[j].x, w1[i].y);
					printf("collision at point [%d, %d]\n", p.x, p.y);
					collisions.push_back(p);
				}
			}
		}
	}
}

int abs(int n)
{
	if (n < 0) return -n;
	else return n;
}

void getPoints(char *command, vector<Point> &points)
{
	char dir = command[0];
	int value = 0;
	int i = 1;
	while (command[i] != 0) {
		value = value*10 + command[i] - '0';
		i++;
	}

	Point p = points.back();
	switch(dir) {
	case 'R':
		p.x = p.x + value;
		points.push_back(p);
		break;
	case 'L':
		p.x = p.x - value;
		points.push_back(p);
		break;
	case 'U':
		p.y = p.y + value;
		points.push_back(p);
		break;
	case 'D':
		p.y = p.y - value;
		points.push_back(p);
		break;
	}
}

int main()
{
	cin.tie(0);

	std::string wire1;
	std::string wire2;

	cin >> wire1;
	cin >> wire2;

	char w1[wire1.length()];
	char w2[wire2.length()];

	strcpy(w1, wire1.c_str());
	strcpy(w2, wire2.c_str());

	char delim[] = ",";

	vector<Point> w1Points;
	vector<Point> w2Points;
	Point start;
	start.x = 0;
	start.y = 0;
	w1Points.push_back(start);
	w2Points.push_back(start);

	char *sub = strtok(w1, delim);

	while(sub != 0) {
		getPoints(sub, w1Points);
		sub = strtok(nullptr, delim);
	}
	sub = strtok(w2, delim);
	while(sub != 0) {
		getPoints(sub, w2Points);
		sub = strtok(nullptr, delim);
	}


	findCollisions(w1Points, w2Points);
	int closest = 9000000;
	for (Point p : collisions) {
		if (abs(p.x) + abs(p.y) < closest) {
			closest = abs(p.x) + abs(p.y);
		}
	}
	printf("%d\n", closest);

}
