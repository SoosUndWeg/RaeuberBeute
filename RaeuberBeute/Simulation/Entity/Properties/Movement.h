#pragma once

#include "../Property.h"

namespace sim {
	class Movement : public Property {
	public:
		using Property::Property;
		Movement();
		Movement(const char*);
		Movement(const std::string&);

		void setRange(const int&);
		void setBlockable(const bool&);

		int getRange();
		bool isBlockable();
	private:
		int range = 1;
		bool blockable = true;
	};
}