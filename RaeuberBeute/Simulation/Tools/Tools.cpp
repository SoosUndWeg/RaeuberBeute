#include "Tools.h"

namespace sim {
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
}