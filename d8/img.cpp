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
	int data[6][25];
	Stats stats;
};

int main() {
	cin.tie(0);

	vector<Layer> layers;
	Layer tmp;
	tmp.stats = {0,0,0};
	char c = getchar();
	int iter = 0;
	while (c != '\n') {
		int val = c - '0';
		if (iter < LSIZE-1) {
			tmp.data[0][iter++] = val;
		} else {
			tmp.data[0][iter++] = val;
			layers.push_back(tmp);
			iter = 0;
		}
		c = getchar();
	}
	int min = 150;
	int minLayerID = 0;
	for (int i = 0; i < layers.size(); i++) {
		for (int j = 0; j < 25*6; j++) {
			switch(layers[i].data[0][j]) {
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
	int endpic[6][25];

	for (int j=0;j<6;j++) {
		for (int i=0;i<25;i++) {
			for (Layer l : layers) {
				if (l.data[j][i] == 0) {
					endpic[j][i] = l.data[j][i];
					break;
				}
				if (l.data[j][i] == 1) {
					endpic[j][i] = l.data[j][i];
					break;
				}
			}
		}
	}

	cout << layers[minLayerID].stats.ones * layers[minLayerID].stats.twos << endl;
	for (int j=0;j<6;j++) {
		for (int i=0;i<25;i++) {
			if (endpic[j][i] == 1) cout << "#";
			if (endpic[j][i] == 0) cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}
