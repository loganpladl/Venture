#include "../include/Application.h"

#include "../include/Log.h"
#include "../include/EventSystem.h"
#include "../include/Input.h"
#include "../include/FileSystem.h"
#include "../include/Time.h"
#include "../include/GameObject.h"

#include "../include/DefaultGameObjects.h"


namespace Venture {
	Application::Application() : m_window(){
		m_window.Init();
		m_window.Create();
	}

	int Application::Run() {
		Init();

		// Fixed timestep
		auto TIME_PER_UPDATE = .01666666;

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

			accumulatedTime += deltaTime;
			secondTimer += deltaTime;

			// Update with fixed timestep
			while (accumulatedTime >= TIME_PER_UPDATE) {
				accumulatedTime-= TIME_PER_UPDATE;
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
			}
		}
		Shutdown();
		return 0;
	}

	int Application::Init() {
		// Create thread for asynchronous file IO
		m_fileThread = std::thread(FileSystem::ProcessRequests);

		Venture::Log::SetVerbosity(3);
		Venture::Log::openLogFiles();
		Input::Init();
		Time::Init();

		//Create camera
		DefaultGameObjects::GetNewFPSCamera();

		m_renderManager.Init(m_window.GetHandle());
		return 0;
	}

	int Application::Shutdown() {
		Venture::Log::closeLogFiles();

		FileSystem::Terminate();
		m_fileThread.join();
		return 0;
	}
	int Application::Update() {
		// Handle Venture events
		EventSystem::DispatchEvents();

		// Update all GameObjects
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