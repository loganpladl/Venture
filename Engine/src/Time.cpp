#include "../include/Time.h"

namespace Venture {
	// Initialize statics
	double Time::s_fixedTimeStep = 0.00833333333;
	double Time::s_deltaTime;
	std::chrono::steady_clock::time_point Time::s_previousTime;
	std::chrono::steady_clock::time_point Time::s_startTime;

	// Delta is in seconds
	double Time::NewDelta() {
		auto current = std::chrono::high_resolution_clock::now();
		s_deltaTime = std::chrono::duration<double>(current - s_previousTime).count();

		s_previousTime = current;
		return s_deltaTime;
	}

	// Initialize time point for the start of the game
	void Time::Init() {
		s_startTime = std::chrono::high_resolution_clock::now();
	}

	// Time since start of program in seconds
	double Time::CurrentTime() {
		auto current = std::chrono::high_resolution_clock::now();
		return std::chrono::duration<double>(current - s_startTime).count();
	}
}