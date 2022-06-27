#pragma once

#include "../Property.h"

namespace sim {
	class Environment : public Property {
	public:
		using Property::Property;

		void blockMovement(bool);
		void blockVision(bool);

		bool isBlockingMovement();
		bool isBlockingVision();
	private:
		bool blockingMovement = false;
		bool blockingVision = false;
	};
}