#pragma once

namespace sim {
	class Controller {
	public:
		Controller();
		~Controller();

		void startSimulation();
	private:
		static inline bool printToConsole = false;
		static inline bool printToFile = false;
	};
}