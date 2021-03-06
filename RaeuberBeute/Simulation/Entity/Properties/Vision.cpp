#include "Vision.h"

namespace sim {
	Vision::Vision() : Property{ "Vision" } {}
	Vision::Vision(const char* name) : Property{ name } {}
	Vision::Vision(const std::string& name) : Property{ name } {}

	void Vision::setRange(const int& range) {
		this->range = range;
	}
	void Vision::setBlockable(const bool& blockable) {
		this->blockable = blockable;
	}

	int Vision::getRange() {
		return this->range;
	}
	bool Vision::isBlockable() {
		return this->blockable;
	}
}