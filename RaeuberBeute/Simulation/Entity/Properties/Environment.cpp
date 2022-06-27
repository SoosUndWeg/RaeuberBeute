#include "Environment.h"

namespace sim {
	void Environment::blockMovement(bool blockingMovement) {
		this->blockingMovement = blockingMovement;
	}
	void Environment::blockVision(bool blockingVision) {
		this->blockingVision = blockingVision;
	}

	bool Environment::isBlockingMovement() { return this->blockingMovement; }
	bool Environment::isBlockingVision() { return this->blockingVision; }
}