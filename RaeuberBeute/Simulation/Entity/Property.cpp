#include "Property.h"
#include <vector>

namespace sim {
	Property::Property() : name{ "unknown" } {}
	Property::Property(const char* name) : name{ name } {}

	const char* Property::getName() {
		return this->name;
	}
}