#pragma once

#include <memory>
#include <vector>
#include <fstream>

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

		void printStep();

		//Einstellungen
		static inline bool print_console = true;
		static inline bool print_console_map = false;
		static inline bool print_console_detailed_map = false;
		static inline bool print_console_score_map = false;
		static inline bool print_console_entity_count = true;

		static inline bool print_console_animation_create = false;
		static inline int print_console_animation_pause_ms = 100;

		static inline bool print_file_positions = false;
		static inline bool print_file_positions_compressed = false;
		static inline bool print_file_positions_detailed_compressed = false;
		static inline bool print_file_positions_detailed = false;
		static inline bool print_file_entity_count = false;

		static inline int predator_max_age = 12;
		static inline int predator_reproduction_threshold = 8;
		static inline int predator_reproduction_cost = 4;
		static inline int predator_quantity = 0;
		static inline int predator_vision_range = 1;
		static inline int predator_movement_range = 1;

		static inline int prey_max_age = 12;
		static inline int prey_reproduction_threshold = 8;
		static inline int prey_reproduction_cost = 4;
		static inline int prey_quantity = 0;
		static inline int prey_vision_range = 1;
		static inline int prey_movement_range = 1;

		static inline int plant_quantity = 0;
		static inline bool plants_respawn = true;
		static inline int plant_food_count = 4;
	private:
		Map* map;

		std::ofstream fileStream;

		std::vector<std::weak_ptr<Entity>> entityTracker;

		static inline bool print_file = true;

		int steps = 0;

		const int mapXSize;
		const int mapYSize;
	};
}