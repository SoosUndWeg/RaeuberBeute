#include "Predator.h"

namespace sim {
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