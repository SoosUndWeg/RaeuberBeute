#include "Random.h"

namespace sim {
	Random::Random() {
		if (!usedSeed) {
			//aktuelle Zeit als Seed
			std::srand(std::time(nullptr));
			usedSeed = true;
		}
	}

	int Random::ranIntInRange(const int& max) {
		return max < 0 ? 0 : std::rand() % (max + 1);
	}

	int Random::ranIntInRange(const int& min, const int& max) {
		return max - min < 0 ? 0 : std::rand() % (max + 1 - min) + min;
	}
}