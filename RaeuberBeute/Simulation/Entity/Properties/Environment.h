#pragma once

#include "../Property.h"

namespace sim {
	class Environment : public Property {
	public:
		Environment();
		Environment(const char*);
		Environment(const std::string&);

		void blockMovement(const bool&);
		void blockVision(const bool&);

		bool isBlockingMovement();
		bool isBlockingVision();
	private:
		bool blockingMovement = false;
		bool blockingVision = false;
	};
}