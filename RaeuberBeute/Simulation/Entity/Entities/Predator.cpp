#include "Predator.h"

namespace sim {
	Predator::Predator() : Entity{ predator, "Predator" } {}
	Predator::Predator(const char* name) : Entity{ predator, name } {}
	Predator::Predator(std::string name) : Entity{ predator, name } {}
	Predator::~Predator() {}

	std::shared_ptr<Vision> Predator::getVision() const { return this->vision; }
	std::shared_ptr<Movement> Predator::getMovement() const { return this->movement; }
	std::shared_ptr<Attack> Predator::getAttack() const { return this->attack; }

	void Predator::setVision(std::shared_ptr<Vision> vision) {
		this->vision = vision;
	}
	void Predator::setVision(Vision vision) {
		this->vision = std::make_shared<Vision>(vision);
	}

	void Predator::setMovement(std::shared_ptr<Movement> movement) {
		this->movement = movement;
	}
	void Predator::setMovement(Movement movement) {
		this->movement = std::make_shared<Movement>(movement);
	}

	void Predator::setAttack(std::shared_ptr<Attack> attack) {
		this->attack = attack;
	}
	void Predator::setAttack(Attack attack) {
		this->attack = std::make_shared<Attack>(attack);
	}
}