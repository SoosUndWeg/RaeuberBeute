#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#include "Entity.h"
#include "Property.h"

namespace sim {
	class EntityLoader {
	public:
		EntityLoader();
		~EntityLoader();

		Entity load(const char*);
	private:
		Entity* entity;
	};
}