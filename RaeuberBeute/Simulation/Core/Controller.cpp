#include "Controller.h"

#include "Simulation.h"

namespace sim {
	//Konstruktor
	Controller::Controller() {}

	//Destruktor
	Controller::~Controller() {}

	void Controller::startSimulation() {
		Simulation simulation(10, 10);
		simulation.loadSimulationSettings();
		simulation.createDefaultMap();
		simulation.run(20);
	}
}