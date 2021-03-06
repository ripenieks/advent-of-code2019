#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

struct Planet {
	Planet(string name, Planet *orbit) : name(name), orbit(orbit) {}
	string name;
	Planet *orbit;
	vector<Planet*> orbitedBy;
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
		p1 = new Planet(str1, nullptr);
		plants.push_back(p1);
	}
	if (!p2) {
		p2 = new Planet(str2, p1);
		plants.push_back(p2);
		p1->orbitedBy.push_back(p2);
	} else {
		p2->orbit = p1;
		p1->orbitedBy.push_back(p2);
	}
}

int countOrbits(Planet *p, int n) {
	if (p->orbit == nullptr) return n;
	else return countOrbits(p->orbit, n+1);
}

void freePlants() {
	for (Planet *p : plants) {
		delete p;
	}
}

void findSanta (Planet *you) {
	
}

int main() {
	cin.tie(0);
	std::string str;
	int i = 0;

	while (!cin.eof()) {
		cin >> str;
		parseInput(str);
		i++;
	}
	cout << i;
	
	for (Planet *p : plants) {
		if (p->orbit) {
			cout << p->name << " orbits)" << p->orbit->name << endl;
		} else {
			cout << p-> name << " no orbit" << endl;
		}
	}

	for (Planet *p : plants) {
		if (p->name == "B"){
			for (Planet *p2 : p->orbitedBy) {
				cout << p2->name << endl;
			}
		}
	}

	int sum = 0;

	for (Planet *p : plants) {
		sum = sum + countOrbits(p, 0);
	}
	cout << sum << endl;

	freePlants();
}
