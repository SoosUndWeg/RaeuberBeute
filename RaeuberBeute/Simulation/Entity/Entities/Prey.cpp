#include "Prey.h"

namespace sim {
	Prey::Prey() : Entity{ prey, "Prey" } {}
	Prey::Prey(const char* name) : Entity{ prey, name } {}
	Prey::Prey(std::string name) : Entity{ prey, name } {}
	Prey::~Prey() {}

	std::shared_ptr<Vision> Prey::getVision() const { return this->vision; }
	std::shared_ptr<Movement> Prey::getMovement() const { return this->movement; }

	void Prey::setVision(std::shared_ptr<Vision> vision) {
		this->vision = vision;
	}
	void Prey::setVision(Vision vision) {
		this->vision = std::make_shared<Vision>(vision);
	}

	void Prey::setMovement(std::shared_ptr<Movement> movement) {
		this->movement = movement;
	}
	void Prey::setMovement(Movement movement) {
		this->movement = std::make_shared<Movement>(movement);
	}
}