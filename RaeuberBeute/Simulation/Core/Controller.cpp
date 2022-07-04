#include "Controller.h"

namespace sim {
	//Konstruktor
	Controller::Controller() :simulationSteps{ 10 } {}
	Controller::Controller(int simulationSteps) : simulationSteps{ simulationSteps } {}

	//Destruktor
	Controller::~Controller() {}

	void Controller::startSimulation() {

	}
}