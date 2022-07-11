#pragma once

#include <string>

namespace sim {
	static std::string clearBlueprint;

	void clearConsole();
	void clearByLength(const int&, const int&);
	void createClearBlueprint(const int&, const int&);
	void clearByBlueprint();
}