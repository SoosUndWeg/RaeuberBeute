#include "Environment.h"

namespace sim {
	Environment::Environment() :Property{ "Environment" } {}
	Environment::Environment(const char* name) :Property{ name } {}
	Environment::Environment(const std::string& name) :Property{ name } {}

	void Environment::blockMovement(const bool& blockingMovement) {
		this->blockingMovement = blockingMovement;
	}
	void Environment::blockVision(const bool& blockingVision) {
		this->blockingVision = blockingVision;
	}

	bool Environment::isBlockingMovement() { return this->blockingMovement; }
	bool Environment::isBlockingVision() { return this->blockingVision; }
}