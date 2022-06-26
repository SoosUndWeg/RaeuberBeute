#include "Timer.h"
#include <iostream>

//TODO Timer fixen
namespace sim::debug {
	
	Timer::Timer() : start{ std::chrono::high_resolution_clock::now() } {}

	Timer::~Timer() {
		end = std::chrono::high_resolution_clock::now();
		//duration = (end - start);
		//std::cout << duration.count() * 1000 << "ms\n";
	}
}