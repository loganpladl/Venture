#pragma once
#include "Window.h"
#include "../include/RenderManager.h"
#include <thread>

namespace Venture {
	class Application {
	private:
		Window m_window;
		RenderManager m_renderManager;
		std::thread m_fileThread;
		void Sleep(double frameStartTime);
	public:
		Application();
		int Run();
		int Update();
		int Render();
		int Init();
		int Shutdown();
	};
}