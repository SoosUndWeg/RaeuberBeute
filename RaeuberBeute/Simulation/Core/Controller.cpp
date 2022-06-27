#include "Controller.h"

namespace sim {
	Controller::Controller(sim::Map* map) {
		this->map = map;
	}
	Controller::~Controller() {
		if (map != nullptr)
			delete map;
	}
}