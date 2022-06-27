#pragma once
#include "../Map.h"

namespace sim {
	class Controller {
	public:
		Controller(sim::Map*);
		~Controller();
	private:
		sim::Map* map = nullptr;
	};
}