#include "Property.h"

namespace sim {
	//***********Property**************
	Property::Property() : name{ "unknown" } {}
	Property::Property(const char* name) : name{ name } {}

	const char* Property::getName() {
		return this->name;
	}

	//***********Vision****************
	void Vision::setRange(int range) {
		this->range = range;
	}
	void Vision::setBlockable(bool blockable) {
		this->blockable = blockable;
	}

	int Vision::getRange() {
		return this->range;
	}
	bool Vision::isBlockable() {
		return this->blockable;
	}

	//***********Environment***********
	void Environment::blockMovement(bool blockingMovement) {
		this->blockingMovement = blockingMovement;
	}
	void Environment::blockVision(bool blockingVision) {
		this->blockingVision = blockingVision;
	}

	bool Environment::isBlockingMovement() {
		return this->blockingMovement;
	}
	bool Environment::isBlockingVision() {
		return this->blockingVision;
	}

	//***********Movement**************
	void Movement::setRange(int range) {
		this->range = range;
	}
	void Movement::setBlockable(bool blockable) {
		this->blockable = blockable;
	}

	int Movement::getRange() {
		return this->range;
	}
	bool Movement::isBlockable() {
		return this->blockable;
	}

	//***********Attack****************
	void Attack::setRange(int range) {
		this->range = range;
	}

	int Attack::getRange() {
		return this->range;
	}
}