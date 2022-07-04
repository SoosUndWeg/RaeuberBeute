#pragma once
#include "../Map.h"

namespace sim {
	class Controller {
	public:
		Controller();
		Controller(int);
		~Controller();

		void startSimulation();
	private:
		const int simulationSteps;
		static inline bool printToConsole = false;
		static inline bool printToFile = false;
	};
}