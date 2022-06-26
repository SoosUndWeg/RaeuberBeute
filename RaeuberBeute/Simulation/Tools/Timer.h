#pragma once

#include <chrono>

namespace sim::debug {
	class Timer {
	public:
		Timer();
		~Timer();

	private:
		std::chrono::time_point<std::chrono::steady_clock> start;
		std::chrono::time_point<std::chrono::steady_clock> end;
		//std::chrono::duration<float> duration;
	};
}