#include "Property.h"

namespace sim {
	Property::Property() : name{ "unknown" } {}
	Property::Property(const char* name) : name{ name } {}
	Property::Property(std::string name) : name{ name } {}

	std::string Property::getName() const {
		return this->name;
	}
}