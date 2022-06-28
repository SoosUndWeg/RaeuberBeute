#include "Predator.h"

namespace sim {
	Predator::Predator() : Entity{ predator, "Predator" } {}
	Predator::Predator(const char* name) : Entity{ predator, name } {}
	Predator::Predator(std::string name) : Entity{ predator, name } {}

	Vision Predator::getVision() const { return this->vision; }
	Movement Predator::getMovement() const { return this->movement; }
	Attack Predator::getAttack() const { return this->attack; }

	void Predator::setVision(Vision vision) {
		this->vision = vision;
	}
	void Predator::setMovement(Movement movement) {
		this->movement = movement;
	}
	void Predator::setAttack(Attack attack) {
		this->attack = attack;
	}
}