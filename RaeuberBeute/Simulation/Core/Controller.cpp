#include "Controller.h"
#include "Simulation.h"

namespace sim {
	//Konstruktor
	Controller::Controller() {}

	//Destruktor
	Controller::~Controller() {}

	void Controller::startSimulation() {
		Simulation simulation(10, 10);
		simulation.print_console_animation_create = true;
		simulation.print_console_animation_pause_ms = 100;
		simulation.createDefaultMap();
		simulation.run(20);
	}
}