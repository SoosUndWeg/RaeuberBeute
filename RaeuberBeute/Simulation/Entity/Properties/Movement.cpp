#include "Movement.h"

namespace sim {
	Movement::Movement() : Property{ "Movement" } {}
	Movement::Movement(const char* name) : Property{ name } {}
	Movement::Movement(std::string name) : Property{ name } {}

	void Movement::setRange(int range) {
		this->range = range;
	}
	void Movement::setBlockable(bool blockable) {
		this->blockable = blockable;
	}

	int Movement::getRange() { return this->range; }
	bool Movement::isBlockable() { return this->blockable; }
}