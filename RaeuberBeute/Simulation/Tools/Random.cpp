#include "Random.h"

namespace sim {
	Random::Random() {
		if (!usedSeed) {
			//aktuelle Zeit als Seed
			std::srand(std::time(nullptr));
			usedSeed = true;
		}
	}

	int Random::ranIntInRange(int max) {
		return std::rand() % (max + 1);
	}

	int Random::ranIntInRange(int min, int max) {
		return std::rand() % (max + 1 - min) + min;
	}
}