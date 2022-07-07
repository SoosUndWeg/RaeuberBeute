#pragma once

#include "../Property.h"

namespace sim {
	class Attack : public Property {
	public:
		Attack();
		Attack(const char*);
		Attack(std::string);

		void setRange(int);

		int getRange();
	private:
		int range = 1;
	};
}