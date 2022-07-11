#pragma once

#include "../Property.h"

namespace sim {
	class Attack : public Property {
	public:
		Attack();
		Attack(const char*);
		Attack(const std::string&);

		void setRange(const int&);

		int getRange();
	private:
		int range = 1;
	};
}