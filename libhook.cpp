#include <iostream>
#include <vector>
#include <algorithm>

extern "C" void test_func(void);
extern "C" void sortSprites(int* order, double* dist, int amount);

void test_func()
{
	std::cout << "CPP BBY" << std::endl;
}

void sortSprites(int* order, double* dist, int amount)
{
	std::cout << "sortSprites" << std::endl;
	
	std::vector<std::pair<double, int>> sprites(amount);
	for(int i = 0; i < amount; i++) {
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	std::sort(sprites.begin(), sprites.end());
	// restore in reverse order to go from farthest to nearest
	for(int i = 0; i < amount; i++) {
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
}
