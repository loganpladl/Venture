#include "../include/Time.h"

namespace Venture {
	// Initialize statics
	double Time::s_deltaTime;
	std::chrono::steady_clock::time_point Time::s_previousTime;

	double Time::NewDelta() {
		auto current = std::chrono::high_resolution_clock::now();
		s_deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(current - s_previousTime).count();

		s_previousTime = current;
		return s_deltaTime;
	}

	double Time::CurrentTime() {
		auto current = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::duration<double>>(current.time_since_epoch()).count();
	}
}