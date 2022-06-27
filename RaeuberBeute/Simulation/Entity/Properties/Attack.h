#pragma once

#include "../Property.h"
#include <vector>

namespace sim {
	class Attack : public Property {
	public:
		using Property::Property;
		void setRange(int);

		int getRange();
	private:
		int range = 1;
	};
}