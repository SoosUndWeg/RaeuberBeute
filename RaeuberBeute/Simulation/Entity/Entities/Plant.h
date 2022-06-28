#pragma once

#include "../Entity.h"

namespace sim {
	struct Plant : public Entity {
		Plant();
		Plant(const char*);
		Plant(std::string);
	private:

	};
}