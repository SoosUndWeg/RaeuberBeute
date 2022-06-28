#include "Prey.h"

namespace sim {
	Prey::Prey() : Entity{ prey, "Prey" } {}
	Prey::Prey(const char* name) : Entity{ prey, name } {}
	Prey::Prey(std::string name) : Entity{ prey, name } {}

	Vision Prey::getVision() const { return this->vision; }
	Movement Prey::getMovement() const { return this->movement; }

	void Prey::setVision(Vision vision) {
		this->vision = vision;
	}
	void Prey::setMovement(Movement movement) {
		this->movement = movement;
	}
}