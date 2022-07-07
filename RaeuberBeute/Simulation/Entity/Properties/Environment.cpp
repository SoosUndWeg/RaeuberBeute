#include "Environment.h"

namespace sim {
	Environment::Environment() :Property{ "Environment" } {}
	Environment::Environment(const char* name) :Property{ name } {}
	Environment::Environment(std::string name) :Property{ name } {}

	void Environment::blockMovement(bool blockingMovement) {
		this->blockingMovement = blockingMovement;
	}
	void Environment::blockVision(bool blockingVision) {
		this->blockingVision = blockingVision;
	}

	bool Environment::isBlockingMovement() { return this->blockingMovement; }
	bool Environment::isBlockingVision() { return this->blockingVision; }
}