#pragma once

#include <chrono>

namespace Venture {
	// All doubles represent time duration in seconds
	class Time {
	private:
		// Fixed timestep duration
		static double s_fixedTimeStep;
		// Variable timestep duration
		static double s_deltaTime;
		static std::chrono::steady_clock::time_point s_previousTime;
		// Time point at the start of the game
		static std::chrono::steady_clock::time_point s_startTime;
	public:
		static double NewDelta();
		// Use for updating and physics
		inline static double DeltaTime() {
			return s_deltaTime;
		}
		static void Init();
		static double CurrentTime();
		// Use for rendering if necessary
		inline static double FixedTimeStep() {
			return s_fixedTimeStep;
		}
	};
}