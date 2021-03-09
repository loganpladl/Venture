#pragma once
#include "Window.h"
#include "../include/RenderManager.h"
#include <thread>
#include <memory>

namespace Venture
{
	/**
	 * Top level application class that contains initialization, game loop, and shutdown logic.
	 */
	class Application 
	{
	private:
		/**
		 *  Game window.
		 */
		Window m_window;

		/**
		 * Rendering subsystem.
		 */
		RenderManager m_renderManager;

		/**
		 * Thread responsible for handling file I/O.
		 */
		std::thread m_fileThread;

		/**
		 * Sleep for the remainder of a frame. Currently not in use. 
		 */
		void Sleep(double frameStartTime);
	public:
		Application();

		/**
		 * Top level function containing initialization, game loop, and shutdown.
		 * Called immediately from program entry point.
		 */
		int Run();

		/**
		 * Update all components.
		 */
		int Update();

		/**
		 * Draw frame using data submitted by updated components.
		 */
		int Render();

		int Init();
		int Shutdown();
	};
}