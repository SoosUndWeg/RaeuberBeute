#pragma once

#include <random>
#include <ctime>

namespace sim {
	static bool usedSeed = false;

	struct Random {
		Random();

		int ranIntInRange(int);
		int ranIntInRange(int, int);
	private:
		
	};
}