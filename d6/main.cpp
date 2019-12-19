#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

//TODO orbited by and orbitting is the same thing, its just a graph theory problem, just fix it today

struct Planet {
	Planet(string name) : name(name) {}
	string name;
	vector<Planet*> linkedBy;
};

vector<Planet*> plants;

void parseInput(string inp) {
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
	p1->linkedBy.push_back(p2);
	p2->linkedBy.push_back(p1);

}

void freePlants() {
	for (Planet *p : plants) {
		delete p;
	}
}

int findSanta (Planet *p, int steps) {
	cout << "checking planet: " << p->name << endl;
	cout << "neighbours: ";
	for (Planet *P : p->linkedBy){
		cout << P->name << ",";
	}
	cout << endl;
	if (p->name == "SAN") return steps;
	p->name == "";
	for (Planet *P : p->linkedBy){
		if (P->name != ""){
			//steps = findSanta(P, steps+1);
		}
	}
	return steps;
}



int main() {
	cin.tie(0);
	std::string str;
	int i = 0;

	while (!cin.eof()) {
		cin >> str;
		parseInput(str);
	}
	int n = 0;
	for (Planet *p : plants) {
		if (p->name == "YOU") {
			cout << p->name;
			n = findSanta(p, 0);
			break;
		}
	}
	cout << n << endl;

	freePlants();
}
