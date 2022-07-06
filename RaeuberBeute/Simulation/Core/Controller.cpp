#include "Controller.h"
#include "Simulation.h"

namespace sim {
	//Konstruktor
	Controller::Controller() {}

	//Destruktor
	Controller::~Controller() {}

	void Controller::startSimulation() {
		Simulation simulation(10, 10);
		simulation.plants_respawn = true;
		simulation.print_console_animation_pause_ms = 500;
		simulation.print_console = true;
		simulation.print_console_map = false;
		simulation.print_console_detailed_map = true;
		simulation.print_console_animation_create = false;
		simulation.print_console_score_map = true;
		simulation.print_file_positions_detailed = false;
		simulation.createDefaultMap();
		simulation.run(5);
	}
}