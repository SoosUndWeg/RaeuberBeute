#include "Controller.h"
#include "Simulation.h"

namespace sim {
	//Konstruktor
	Controller::Controller() {}

	//Destruktor
	Controller::~Controller() {}

	void Controller::startSimulation() {
		Simulation simulation(10, 10);
		simulation.respawn_plants = true;
		simulation.print_console = true;
		simulation.print_console_map = false;
		simulation.print_console_detailed_map = false;
		simulation.print_console_animation_create = true;
		simulation.print_console_score_map = false;
		simulation.print_file_detailed_positions = false;
		simulation.createDefaultMap();
		simulation.run(20);
	}
}