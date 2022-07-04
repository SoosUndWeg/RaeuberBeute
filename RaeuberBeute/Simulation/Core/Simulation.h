#pragma once

#include <memory>
#include <vector>

#include "../Map.h"

namespace sim {
	struct Simulation {
		Simulation();
		Simulation(int);
		Simulation(int, int);
		~Simulation();
		
		void createDefaultMap();
		void createTestMap();

		void moveEntity(int, int);

	private:
		Map* map;

		std::vector<std::weak_ptr<Entity>> entityTracker;

		int mapXSize;
		int mapYSize;
	};
}