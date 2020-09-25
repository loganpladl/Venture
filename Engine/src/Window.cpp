#include "../include/Window.h"

namespace Venture {
	Window::Window(HINSTANCE hInstance) {
		m_instance = hInstance;
		m_windowClassName = L"VentureWindowClass";
		m_window = NULL;
	}

	int Window::Init() {
		// Game Icon
		HICON icon = NULL;
		WCHAR exePath[MAX_PATH];
		GetModuleFileName(NULL, exePath, MAX_PATH);

		// Get default icon
		if (icon == NULL) {
			icon = ExtractIcon(m_instance, exePath, 0);
		}

		// Register the window class
		WNDCLASS windowClass;
		windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = WindowCallback;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = m_instance;
		windowClass.hIcon = icon;
		windowClass.hCursor = NULL;
		windowClass.hbrBackground = NULL;
		windowClass.lpszMenuName = NULL;
		windowClass.lpszClassName = m_windowClassName;

		if (!RegisterClass(&windowClass)) {
			// Registering window class failed
			DWORD error = GetLastError();
			if (error != ERROR_CLASS_ALREADY_EXISTS) {
				return HRESULT_FROM_WIN32(error);
			}
		}
		return 0;
	}

	int Window::Create() {
		RECT rect;
		int x = CW_USEDEFAULT;
		int y = CW_USEDEFAULT;

		// No menu for now.
		
		int defaultWidth = 640;
		int defaultHeight = 480;
		SetRect(&rect, 0, 0, defaultWidth, defaultHeight);
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);


		m_window = CreateWindowEx(
			0,
			m_windowClassName,
			L"Venture",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			x, y,
			(rect.right - rect.left),
			(rect.bottom - rect.top),
			0,
			0,
			m_instance,
			0
		);

		if (m_window == NULL) {
			DWORD error = GetLastError();
			return HRESULT_FROM_WIN32(error);
		}

		return 0;
	}

	LRESULT CALLBACK Window::WindowCallback(
		HWND window,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	) {
		LRESULT result = 0;

		switch (message) {
			case WM_SIZE: {
				break;
			}
			case WM_CLOSE: {
				HMENU menu;
				menu = GetMenu(window);
				if (menu != NULL) {
					DestroyMenu(menu);
				}
				DestroyWindow(window);
				//UnregisterClass
				break;
			}
			case WM_DESTROY: {
				PostQuitMessage(0);
				break;
			}
			case WM_ACTIVATEAPP: {
				break;
			}
			case WM_KEYDOWN: {
				Input::KeyCode keyCode = Input::ConvertWindowsKeyCode((int)wParam);
				// Only create events for relevant keycodes and eliminate repeats
				int prevState = lParam & 0x40000000;
				if (keyCode != Input::Unassigned && prevState == 0) {
					KeyPressedEvent* event = new KeyPressedEvent(keyCode);
					EventQueue::Enqueue(event);
				}
				break;
			}
			case WM_KEYUP: {
				Input::KeyCode keyCode = Input::ConvertWindowsKeyCode((int)wParam);
				// Only create events for relevant keycodes
				if (keyCode != Input::Unassigned) {
					KeyReleasedEvent* event = new KeyReleasedEvent(keyCode);
					EventQueue::Enqueue(event);
				}
				break;
			}
			default: {
				result = DefWindowProc(window, message, wParam, lParam);
				break;
			}
		}
		return result;
	}
}