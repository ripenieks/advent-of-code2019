#include <vector>


struct image {
	std::vector<int> rom;
	int ip;
	int mode;
};

int intcode(struct image &img, int input);
int intcode(std::vector<int> rom);
