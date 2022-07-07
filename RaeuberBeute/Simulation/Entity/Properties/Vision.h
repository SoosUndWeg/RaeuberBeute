#pragma once

#include "../Property.h"

namespace sim {
	class Vision : public Property {
	public:
		Vision();
		Vision(const char*);
		Vision(std::string);

		void setRange(int);
		void setBlockable(bool);

		int getRange();
		bool isBlockable();
	private:
		int range = 1;
		bool blockable = true;
	};
}