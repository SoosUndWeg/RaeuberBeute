#include "Attack.h"

namespace sim {
	void Attack::setRange(int range) {
		this->range = range;
	}

	int Attack::getRange() { return this->range; }
}