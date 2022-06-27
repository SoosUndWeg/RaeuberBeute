#include "Movement.h"

namespace sim {
	void Movement::setRange(int range) {
		this->range = range;
	}
	void Movement::setBlockable(bool blockable) {
		this->blockable = blockable;
	}

	int Movement::getRange() { return this->range; }
	bool Movement::isBlockable() { return this->blockable; }
}