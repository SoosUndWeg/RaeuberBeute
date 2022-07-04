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

		void step();
		void run(int);
		void moveEntity(int, int);

		void clearEntityTracker();
		void addToEntityTracker(int, int);
		void updateEntityTracker();

		int getRoleCount(Role) const;
	private:
		Map* map;

		std::vector<std::weak_ptr<Entity>> entityTracker;

		const int mapXSize;
		const int mapYSize;
	};
}