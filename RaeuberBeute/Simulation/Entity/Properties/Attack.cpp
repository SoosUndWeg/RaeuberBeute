#include "Attack.h"

namespace sim {
	Attack::Attack() : Property{ "Attack" } {};
	Attack::Attack(const char* name) : Property{ name } {};
	Attack::Attack(const std::string& name) : Property{ name } {};

	void Attack::setRange(const int& range) {
		this->range = range;
	}

	int Attack::getRange() { return this->range; }
}