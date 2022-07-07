#pragma once

#include "../Property.h"

namespace sim {
	class Movement : public Property {
	public:
		using Property::Property;
		Movement();
		Movement(const char*);
		Movement(std::string);

		void setRange(int);
		void setBlockable(bool);

		int getRange();
		bool isBlockable();
	private:
		int range = 1;
		bool blockable = true;
	};
}