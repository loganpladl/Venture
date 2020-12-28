#pragma once
#include <windows.h>
#include <string>
#include "Input.h"
#include "Log.h"

namespace Venture {
	class Window {
	public:
		Window();
		~Window();
		int Init();
		int Create();
		int Destroy();
		static LRESULT CALLBACK WindowCallbackSetup(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK WindowCallbackStatic(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK WindowCallback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
		HWND GetHandle();
		bool ProcessMessages();
		void GainFocus();
		void LoseFocus();
	private:
		HINSTANCE m_instance;
		LPCWSTR m_windowClassName;
		HWND m_window;
		int m_width;
		int m_height;
		bool m_windowHasFocus;
		bool m_mouseCentered;
	};
}