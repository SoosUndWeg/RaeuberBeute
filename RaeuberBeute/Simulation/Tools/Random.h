#pragma once

#include <random>

namespace sim {
	static inline bool usedSeed = false;

	struct Random {
		Random();

		int ranIntInRange(const int&);
		int ranIntInRange(const int&, const int&);
	private:
		
	};
}