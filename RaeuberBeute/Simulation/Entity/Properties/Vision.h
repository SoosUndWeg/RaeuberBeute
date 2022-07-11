#pragma once

#include "../Property.h"

namespace sim {
	class Vision : public Property {
	public:
		Vision();
		Vision(const char*);
		Vision(const std::string&);

		void setRange(const int&);
		void setBlockable(const bool&);

		int getRange();
		bool isBlockable();
	private:
		int range = 1;
		bool blockable = true;
	};
}