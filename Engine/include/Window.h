#pragma once
#include <windows.h>
#include <string>
#include "EventQueue.h"
#include "Event.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "Input.h"
#include "Log.h"

namespace Venture {
	class Window {
	public:
		Window(HINSTANCE hInstance);
		int Init();
		int Create();
		static LRESULT CALLBACK WindowCallbackSetup(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK WindowCallbackStatic(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK WindowCallback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
	private:
		HINSTANCE m_instance;
		LPCWSTR m_windowClassName;
		HWND m_window;
		int m_width;
		int m_height;
	};
}