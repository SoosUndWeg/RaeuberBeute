#pragma once
#include "Entity/Animal.h"
#include <vector>

namespace sim {
	class Map {
	public:
		Map(int, int);
	private:
		std::vector<std::vector<Animal>> map;
	};
}