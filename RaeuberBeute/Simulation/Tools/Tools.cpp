#include "Tools.h"

#include <stdlib.h>
#include <iostream>

namespace sim {
	//Konsole leeren
	void clearConsole() {
#ifdef _WIN32
		system("cls");
#endif
#ifdef LINUX
		system("clear");
#endif
#ifdef __APPLE__
		system("clear");
#endif
	}

	//Strings oder mehrere Zeilen aus der Console entfernen
	void clearByLength(const int& maxLineLength, const int& newLineCount) {
#if 0
		for(int i = 0; i < newLineCount; i++)
			std::cout << std::string(maxLineLength, '\b') << "\x1b[A";
#endif
		std::string s = "";
		for (int i = 0; i < newLineCount; i++)
			s += std::string(maxLineLength, '\b') + "\x1b[A";
		std::cout << s;
	}

	void createClearBlueprint(const int& maxLineLength, const int& newLineCount) {
		sim::clearBlueprint = "";
		for (int i = 0; i < newLineCount; i++)
			sim::clearBlueprint += std::string(maxLineLength, '\b') + "\x1b[A";
	}

	void clearByBlueprint() {
		std::cout << sim::clearBlueprint;
	}
}