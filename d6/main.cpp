#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

//TODO orbited by and orbitting is the same thing, its just a graph theory problem, just fix it today

struct Planet {
	Planet(string name) : name(name) {}
	string name;
	vector<Planet*> neighbours;
};

static int found = 0;

void parseInput(string inp, vector<Planet*> &plants) {
	string str1;
	string str2;

	size_t pos = inp.find(")");
	str1 = inp.substr(0, pos);
	str2 = inp.substr(pos+1, inp.length());
	Planet *p1 = nullptr;
	Planet *p2 = nullptr;
	for (Planet *p : plants) {
		if (p->name == str1) {
			p1 = p;
		}
		if (p->name == str2) {
			p2 = p;
		}
	}
	if (!p1) {
		p1 = new Planet(str1);
		plants.push_back(p1);
	}
	if (!p2) {
		p2 = new Planet(str2);
		plants.push_back(p2);
	} 
	p1->neighbours.push_back(p2);
	p2->neighbours.push_back(p1);

}


void findSanta (Planet *p, int depth) {
	//cout << "checking planet: " << p->name;
	//cout << " depth: " << depth << endl;
	if (p->name == "SAN") {
		if (depth < found || found == 0) found = depth;
		return;
	}
	p->name.clear();
	for (Planet *homie : p->neighbours) {
		if (!homie->name.empty()) findSanta(homie, depth+1);
	}
}



int main() {
	cin.tie(0);
	std::string str;
	int i = 0;

	vector<Planet*> plants;
	while (!cin.eof()) {
		cin >> str;
		parseInput(str, plants);
	}
	int n = 0;
	for (Planet *p : plants) {
		//cout << p->name << ") neighbours: ";
		//for (Planet *pp : p->neighbours) {
		//	cout << pp->name << ",";
		//}
		//cout << endl;
	}
	plants.pop_back();
	for (Planet *p : plants) {
		//cout << p->name << ") neighbours: ";
		//for (Planet *pp : p->neighbours) {
		//	cout << pp->name << ",";
		//}
		//cout << endl;
		if (p->name == "YOU") {
			//cout << p->name << endl;
			findSanta(p, 0);
			//break;
		}
	}
	
	cout << found-2 << endl;

	for (Planet *p : plants) {
		delete p;
	}
}
