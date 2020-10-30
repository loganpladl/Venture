#include <windows.h>

#include "../include/Application.h"

using namespace Venture;

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
) {
	Application app;
	app.Run();
}