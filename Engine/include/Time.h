#pragma once

#include <chrono>

namespace Venture {
	class Time {
	private:
		static double s_deltaTime;
		static std::chrono::steady_clock::time_point s_previousTime;
		// Time point at the start of the game
		static std::chrono::steady_clock::time_point s_startTime;
	public:
		static double NewDelta();
		inline static double DeltaTime() {
			return s_deltaTime;
		}
		static void Init();
		static double CurrentTime();
	};
}