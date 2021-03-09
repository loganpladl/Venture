#pragma once
#include <windows.h>
#include <string>
#include "Input.h"
#include "Log.h"

namespace Venture {
	class Window {
	public:
		/**
		 * Create window using Windows API.
		 */
		Window();

		/**
		 * Calls Destroy().
		 */
		~Window();

		/**
		 * Deallocate window and associated objects when the user closes the window.
		 */
		void Destroy();

		/**
		* Initial window callback which stores our Window instance on the OS side.
		*/
		static LRESULT CALLBACK WindowCallbackSetup(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

		/**
		* Immediately calls WindowCallback() using Window instance stored on the OS side. Exists only because Windows API requires a static callback.
		*/
		static LRESULT CALLBACK WindowCallbackStatic(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

		/**
		 * Primary callback function which handles windows events.
		 */
		LRESULT CALLBACK WindowCallback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
		HWND GetHandle();
		bool ProcessMessages();
		void GainFocus();
		void LoseFocus();
		void ConfineCursor();
		void FreeCursor();
		void ResizeClipRect();
	private:
		HINSTANCE m_instance;
		LPCWSTR m_windowClassName;
		HWND m_windowHandle;
		RECT m_windowRect;
		int m_width;
		int m_height;
		bool m_windowHasFocus;
		bool m_mouseConfined;
	};
}