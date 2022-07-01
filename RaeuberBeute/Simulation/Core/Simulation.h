#pragma once

#include "../Map.h"
//#include "../Entity/Entity.h"
#include "../Entity/Entities/Predator.h"
#include "../Entity/Entities/Prey.h"
#include "../Entity/Entities/Plant.h"

namespace sim {
	struct Simulation {
		Simulation();
		Simulation(int);
		~Simulation();
		
		void createDefaultMap();
		void createTestMap();

		void moveEntity(int, int);

	private:
		Map* map;
		int mapSize;
	};
}