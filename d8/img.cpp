#include <iostream>
#include <vector>
#define LSIZE 25*6

using namespace std;

struct Stats {
	int zeros;
	int ones;
	int twos;
};

struct Layer {
	vector<int> data;
	Stats stats;
};

int main() {
	cin.tie(0);

	vector<Layer> layers;
	Layer tmp;
	tmp.stats = {0,0,0};
	char c = getchar();
	while (c != '\n') {
		int val = c - '0';
		if (tmp.data.size() < LSIZE-1) {
			tmp.data.push_back(val);
		} else {
			tmp.data.push_back(val);
			layers.push_back(tmp);
			tmp.data.clear();
		}
		c = getchar();
	}
	int min = 150;
	int minLayerID = 0;
	for (int i = 0; i < layers.size(); i++) {
		for (int x : layers[i].data) {
			switch(x) {
				case 0:
					layers[i].stats.zeros++;
					break;
				case 1:
					layers[i].stats.ones++;
					break;
				case 2:
					layers[i].stats.twos++;
					break;
				default:
					cout << "im sorry what now?" << endl;
					break;
			}
		}
		if (layers[i].stats.zeros < min) {
			min = layers[i].stats.zeros;
			minLayerID = i;
		}
	}
	cout << layers[minLayerID].stats.ones * layers[minLayerID].stats.twos << endl;
}
