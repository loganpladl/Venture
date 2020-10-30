#pragma once
#include "Window.h"

namespace Venture {
	class Application {
	private:
		Window m_window;
	public:
		Application();
		int Run();
	};
}