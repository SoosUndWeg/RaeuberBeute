#include "Prey.h"

namespace sim {
	Vision Prey::getVision() const { return this->vision; }
	Movement Prey::getMovement() const { return this->movement; }

	void Prey::setVision(Vision vision) {
		this->vision = vision;
	}
	void Prey::setMovement(Movement movement) {
		this->movement = movement;
	}
}