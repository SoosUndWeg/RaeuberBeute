#pragma once

#include <tuple>

#include "../Map.h"
#include "../Entity/Entities/Predator.h"
#include "../Entity/Entities/Prey.h"
#include "../Entity/Entities/Plant.h"
#include "../Tools/Random.h"

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
		int mapXSize;
		int mapYSize;
	};
}