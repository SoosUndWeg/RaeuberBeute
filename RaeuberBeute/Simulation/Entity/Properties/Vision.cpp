#include "Vision.h"

namespace sim {
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
}