#include "../include/Application.h"

#include "../include/Log.h"
#include "../include/EventQueue.h"
#include "../include/Input.h"
#include "../include/FileSystem.h"
#include <thread>
#include "../include/RenderManager.h"

namespace Venture {
	Application::Application() : m_window(){
		m_window.Init();
		m_window.Create();
	}

	int Application::Run() {
		bool gotMsg;
		MSG msg;
		msg.message = WM_NULL;
		PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

		// Create thread for asynchronous file IO
		std::thread fileThread(FileSystem::ProcessRequests);

		Venture::Log::openLogFiles();
		EventQueue::Init();
		Input::Init();

		RenderManager renderManager(m_window.GetHandle());
		renderManager.Init();

		while (WM_QUIT != msg.message) {
			// Process window events
			gotMsg = PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0;

			if (gotMsg) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				// Handle Venture events
				EventQueue::DispatchEvents();
				// update and render
				renderManager.Render();
			}
		}

		Venture::Log::closeLogFiles();

		FileSystem::Terminate();
		fileThread.join();
		return 0;
	}
}