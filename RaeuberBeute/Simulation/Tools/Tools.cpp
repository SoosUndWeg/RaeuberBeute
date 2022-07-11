#include "Tools.h"

#include <stdlib.h>
#include <iostream>
#include <string>

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
		for(int i = 0; i < newLineCount; i++)
			std::cout << std::string(maxLineLength, '\b') << "\x1b[A";
	}
}