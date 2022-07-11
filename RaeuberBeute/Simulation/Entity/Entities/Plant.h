#pragma once

#include "../Entity.h"

namespace sim {
	struct Plant : public Entity {
		Plant();
		Plant(const char*);
		Plant(const std::string&);
	private:

	};
}