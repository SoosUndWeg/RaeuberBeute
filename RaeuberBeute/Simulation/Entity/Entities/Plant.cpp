#include "Plant.h"

namespace sim {
	Plant::Plant() : Entity{ plant, "Plant" } {}
	Plant::Plant(const char* name) : Entity{ plant, name } {}
	Plant::Plant(std::string name) : Entity{ plant, name } {}
}