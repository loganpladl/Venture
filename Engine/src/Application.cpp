#include "../include/Application.h"

#include "../include/Log.h"
#include "../include/EventSystem.h"
#include "../include/Input.h"
#include "../include/FileSystem.h"
#include "../include/Time.h"
#include "../include/GameObject.h"

#include "../include/DefaultGameObjects.h"
#include <Windows.h>


namespace Venture {
	Application::Application() : m_window()
	{
		// Create thread for asynchronous file IO
		m_fileThread = std::thread(FileSystem::ProcessRequests);

		Venture::Log::SetVerbosity(0);
		Venture::Log::openLogFiles();
		Input::Init();
		Time::Init();

		//Create camera
		DefaultGameObjects::GetNewFPSCamera();
		//Create cube
		DefaultGameObjects::GetNewCube();

		m_renderManager.Init(m_window.GetHandle());
	}

	int Application::Run() {
		Init();

		// Fixed timestep, 120fps
		auto TIME_PER_UPDATE = Time::FixedTimeStep();

		const auto SECOND = 1.0;
		int renderedFrames = 0;

		// Set current time
		Time::NewDelta();
		// Timer used to update game logic with fixed timestep
		double accumulatedTime = 0.0;
		// Timer used for frames per second calculation
		double secondTimer = 0.0;

		double framesPerSecond = 0;

		while (m_window.ProcessMessages()) {
			auto deltaTime = Time::NewDelta();
			
			auto frameStartTime = Time::CurrentTime(); // Not currently using this. Can use to sleep until next frame.

			accumulatedTime += deltaTime;
			secondTimer += deltaTime;

			// Handle Venture events
			EventSystem::DispatchEvents();

			// Update with fixed timestep
			while (accumulatedTime >= TIME_PER_UPDATE) {
				accumulatedTime-= TIME_PER_UPDATE;
				
				// Update all gameobject components
				Update();
			}

			// Render every loop
			Render();
			renderedFrames++;

			
			// Once a second has passed, update frames per second and reset variables
			if (secondTimer >= SECOND) {
				framesPerSecond = renderedFrames;
				renderedFrames = 0;
				secondTimer = 0;
				Log::DebugPrintF(0, Log::Channel::General, "FPS: %f\n", framesPerSecond);
			}
		}
		Shutdown();
		return 0;
	}

	// Sleep at end of frame given frame start time to meet target FPS (not currently using this)
	void Application::Sleep(double frameStartTime) {
		// Sleep until next frame
		double milliseconds = (frameStartTime + Time::FixedTimeStep() - Time::CurrentTime()) * 1000;

		if (milliseconds > 0) {
			Sleep(static_cast<DWORD>(milliseconds));
		}
	}

	int Application::Init() {
		return 0;
	}

	int Application::Shutdown() {
		Venture::Log::closeLogFiles();

		FileSystem::Terminate();
		m_fileThread.join();
		return 0;
	}
	int Application::Update() {
		// Clear renderables before new ones are submitted in updates
		m_renderManager.Clear();

		// Update all GameObjects
		// TODO: Faster to store struct of arrays of components and update components of same type sequentially.
		GameObject** gameObjects = GameObject::GetAllGameObjects();
		int maxGameObjects = GameObject::GetMaxGameObjects();
		for (int i = 0; i < maxGameObjects; i++) {
			if (gameObjects[i] != nullptr) {
				GameObject* gameObject = gameObjects[i];
				gameObject->Update();
			}
		}
		return 0;
	}
	int Application::Render() {
		m_renderManager.Render();
		return 0;
	}
}