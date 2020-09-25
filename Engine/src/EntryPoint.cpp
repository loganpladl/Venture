#include <windows.h>
#include "../include/Window.h"

#include "../include/Log.h"
#include "../include/EventQueue.h"
#include "../include/Input.h"

using namespace Venture;

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
) {
	Window window{ hInstance };
	window.Init();
	window.Create();

	bool gotMsg;
	MSG msg;
	msg.message = WM_NULL;
	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

	Venture::Log::openLogFiles();
	EventQueue::Init();
	Input::Init();

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
			
		}
	}


	Venture::Log::closeLogFiles();

}