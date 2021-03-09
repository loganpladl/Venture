#include "../include/Window.h"

#include <hidusage.h>

namespace Venture {
	Window::Window() : 
		m_instance(GetModuleHandle(NULL)), m_windowClassName(L"VentureWindowClass"),
		m_windowHandle(NULL), m_width(640), m_height(480), m_windowHasFocus(false), m_mouseConfined(false), m_windowRect() 
	{
		// Game Icon
		HICON icon = NULL;
		WCHAR exePath[MAX_PATH];
		GetModuleFileName(NULL, exePath, MAX_PATH);

		// Get default icon
		if (icon == NULL) {
			icon = ExtractIcon(NULL, exePath, 0);
		}

		// Register the window class
		WNDCLASS windowClass;
		windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = WindowCallbackSetup;
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
				//return HRESULT_FROM_WIN32(error);
				// TODO: Throw exception
			}
		}

		RECT rect;
		int x = CW_USEDEFAULT;
		int y = CW_USEDEFAULT;

		// No menu for now.

		SetRect(&rect, 0, 0, m_width, m_height);
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		m_windowHandle = CreateWindowEx(
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
			this // pointer to window instance so we can retrieve member function callback
		);

		if (m_windowHandle == NULL) {
			DWORD error = GetLastError();
			//return HRESULT_FROM_WIN32(error);
			// TODO: Throw exception
		}

		//GetWindowRect(m_window, &m_windowRect);

		// Register mouse as raw input device to be able to use WM_INPUT
		// TODO: Find cleaner spot for this
		RAWINPUTDEVICE Rid[1];
		Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
		//Rid[0].dwFlags = RIDEV_INPUTSINK;
		Rid[0].dwFlags = 0;
		Rid[0].hwndTarget = m_windowHandle;
		RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));
		// TODO: Check for failure
	}

	LRESULT CALLBACK Window::WindowCallbackSetup(
		HWND window,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	) {
		LRESULT result = 0;

		switch (message) {
			case WM_NCCREATE: {
				// Get pointer to window instance
				const CREATESTRUCT* const createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
				Window* const windowInstance = static_cast<Window*>(createStruct->lpCreateParams);
				SetWindowLongPtr(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(windowInstance));
				SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::WindowCallbackStatic));
				result = windowInstance->WindowCallback(window, message, wParam, lParam);
				break;
			}
			default: {
				result = DefWindowProc(window, message, wParam, lParam);
				break;
			}
		}
		return result;
	}

	LRESULT CALLBACK Window::WindowCallbackStatic(
		HWND window,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	) {
		// Get instance of window and call member callback function so long as window is not null
		Window* windowInstance = reinterpret_cast<Window*>(GetWindowLongPtr(window, GWLP_USERDATA));
		if (windowInstance) {
			return windowInstance->WindowCallback(window, message, wParam, lParam);
		}
		else {
			return DefWindowProc(window, message, wParam, lParam);
		}
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
				ResizeClipRect();
				break;
			}
			case WM_MOVE: {
				ResizeClipRect();
				break;
			}
			case WM_CLOSE: {
				Destroy();
				break;
			}
			case WM_KILLFOCUS: {
				// TODO: clear pressed keystates
				break;
			}
			case WM_DESTROY: {
				PostQuitMessage(0);
				break;
			}
			case WM_ACTIVATE: {
				// Low order word of wParam is 1 if activated, 2 if activated by mouse click, 3 if deactivated
				if (LOWORD(wParam) == 1) {
					GainFocus();
				}
				else if (LOWORD(wParam) == 2) {
					GainFocus();
				}
				else  {
					LoseFocus();
					if (Mouse::IsMouseInWindow()) {
						ReleaseCapture();
						Input::MouseLeave();
					}
				}
				break;
			}
			case WM_ACTIVATEAPP: {
				// wParam is true if window is being activated; false if window is being deactivated
				if (wParam) {

				}
				else {
					
				}
				break;
			}
			case WM_KEYDOWN:
			// WM_SYSKEYDOWN is needed for ALT key and other system keys
			case WM_SYSKEYDOWN: {
				Keyboard::KeyCode keyCode = Keyboard::ConvertWindowsKeyCode((int)wParam);
				// Only create events for relevant keycodes and eliminate repeats
				int prevState = lParam & 0x40000000;
				if (keyCode != Keyboard::KeyCode::Unassigned && prevState == 0) {
					Input::KeyPressed(keyCode);
				}
				// NOTE: Maybe do this through event system instead of here
				// Free cursor if user presses escape in first person mode
				// Close window if user presses escape in normal use
				if (keyCode == Keyboard::KeyCode::Escape && m_mouseConfined) {
					FreeCursor();
				}
				else if (keyCode == Keyboard::KeyCode::Escape && !m_mouseConfined) {
					Destroy();
				}
				break;
			}
			case WM_KEYUP:
			case WM_SYSKEYUP: {
				Keyboard::KeyCode keyCode = Keyboard::ConvertWindowsKeyCode((int)wParam);
				// Only create events for relevant keycodes
				if (keyCode != Keyboard::KeyCode::Unassigned) {
					Input::KeyReleased(keyCode);
				}
				break;
			}
			case WM_CHAR: {
				// Text input
				break;
			}
			case WM_MOUSEMOVE: {
				if (!m_windowHasFocus) {
					break;
				}
				const POINTS point = MAKEPOINTS(lParam);
				// Check if mouse is in window, create move event if so
				if (point.x >= 0 && point.x < m_width && point.y >= 0 && point.y < m_height) {
					// If mouse was not previously in window, create enter event
					if (!Mouse::IsMouseInWindow()) {
						SetCapture(window);
						Input::MouseEnter();
					}
					// Generate mouse move event regardless
					Input::MouseMove(point.x, point.y);
				}

				// If getting messages while mouse is not in window, continue creating move events while mouse is held
				// Release capture and create leave event when mouse is not held
				else {
					if (wParam & (MK_LBUTTON | MK_RBUTTON)) {
						Input::MouseMove(point.x, point.y);
					}
					else {
						ReleaseCapture();
						Input::MouseLeave();
					}
				}
				
				break;
			}
			case WM_LBUTTONDOWN: {
				if (!m_mouseConfined) {
					ConfineCursor();
				}
				const POINTS point = MAKEPOINTS(lParam);
				Input::LeftMousePressed(point.x, point.y);
				break;
			}
			case WM_LBUTTONUP: {
				const POINTS point = MAKEPOINTS(lParam);
				Input::LeftMouseReleased(point.x, point.y);
				break;
			}
			case WM_RBUTTONDOWN: {
				const POINTS point = MAKEPOINTS(lParam);
				Input::RightMousePressed(point.x, point.y);
				break;
			}
			case WM_RBUTTONUP: {
				const POINTS point = MAKEPOINTS(lParam);
				Input::RightMouseReleased(point.x, point.y);
				break;
			}
			case WM_MBUTTONDOWN: {
				const POINTS point = MAKEPOINTS(lParam);
				Input::MiddleMousePressed(point.x, point.y);
				break;
			}
			case WM_MBUTTONUP: {
				const POINTS point = MAKEPOINTS(lParam);
				Input::MiddleMouseReleased(point.x, point.y);
				break;
			}
			case WM_MOUSEWHEEL: {
				const POINTS point = MAKEPOINTS(lParam);
				int delta = GET_WHEEL_DELTA_WPARAM(wParam);
				// Delegate event creation to helper function in mouse class
				// Will only create scrolled events once WHEEL_DELTA rotation is accumulated
				Mouse::MouseScrolled(point.x, point.y, delta);
				break;
			}
			case WM_INPUT:
			{
				// Only process raw input if mouse is confined (FPS mode)
				if (!m_mouseConfined) {
					break;
				}

				UINT dwSize = sizeof(RAWINPUT);
				static BYTE lpb[sizeof(RAWINPUT)];

				GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

				RAWINPUT* raw = (RAWINPUT*)lpb;

				if (raw->header.dwType == RIM_TYPEMOUSE)
				{
					RAWMOUSE rawMouse = raw->data.mouse;
					if ((rawMouse.usFlags & MOUSE_MOVE_RELATIVE) == MOUSE_MOVE_RELATIVE) {
						int xPosRelative = raw->data.mouse.lLastX;
						int yPosRelative = raw->data.mouse.lLastY;
						// Don't make events for clicks
						if (xPosRelative != 0 || yPosRelative != 0) {
							Input::MouseDelta(xPosRelative, yPosRelative);
						}
					}
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

	void Window::Destroy()
	{
		HMENU menu;
		menu = GetMenu(m_windowHandle);
		if (menu != NULL) {
			DestroyMenu(menu);
		}
		DestroyWindow(m_windowHandle);
		// Unregister window class
		UnregisterClass(m_windowClassName, m_instance);
	}

	Window::~Window()
	{
		Destroy();
	}

	HWND Window::GetHandle() {
		return m_windowHandle;
	}

	// Return true to continue program execution, false to quit
	bool Window::ProcessMessages() {
		bool gotMsg;
		MSG msg;

		// Process all window events
		while (gotMsg = PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0) {
			if (WM_QUIT == msg.message) {
				return false;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return true;
	}

	void Window::GainFocus() {
		m_windowHasFocus = true;
	}

	void Window::LoseFocus() {
		m_windowHasFocus = false;
		FreeCursor();
	}

	void Window::ConfineCursor() {
		m_mouseConfined = true;
		ResizeClipRect();
		ClipCursor(&m_windowRect);
		ShowCursor(FALSE);
	}

	void Window::FreeCursor() {
		m_mouseConfined = false;
		ClipCursor(nullptr);
		ShowCursor(TRUE);
	}

	void Window::ResizeClipRect() {
		// Rect in client coordinates starting at zero
		GetClientRect(m_windowHandle, &m_windowRect);
		// Convert to screen coordinates
		POINT topLeft{ m_windowRect.left, m_windowRect.top };
		POINT bottomRight{ m_windowRect.right, m_windowRect.bottom };
		ClientToScreen(m_windowHandle, &topLeft);
		ClientToScreen(m_windowHandle, &bottomRight);
		m_windowRect.left = topLeft.x;
		m_windowRect.top = topLeft.y;
		m_windowRect.right = bottomRight.x;
		m_windowRect.bottom = bottomRight.y;
	}
}