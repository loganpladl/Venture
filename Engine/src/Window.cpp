#include "../include/Window.h"

namespace Venture {
	Window::Window() {
		m_instance = GetModuleHandle(NULL);
		m_windowClassName = L"VentureWindowClass";
		m_window = NULL;
		// Default width and height
		m_width = 640;
		m_height = 480;
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
		
		SetRect(&rect, 0, 0, m_width, m_height);
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
			this // pointer to window instance so we can retrieve member function callback
		);

		if (m_window == NULL) {
			DWORD error = GetLastError();
			return HRESULT_FROM_WIN32(error);
		}

		return 0;
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
				break;
			}
			case WM_CLOSE: {
				Destroy();
				break;
			}
			case WM_KILLFOCUS: {
				// clear pressed keystates
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
						MouseLeaveEvent* leaveEvent = new MouseLeaveEvent();
						EventQueue::Enqueue(leaveEvent);
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
				Input::KeyCode keyCode = Input::ConvertWindowsKeyCode((int)wParam);
				// Only create events for relevant keycodes and eliminate repeats
				int prevState = lParam & 0x40000000;
				if (keyCode != Input::Unassigned && prevState == 0) {
					KeyPressedEvent* event = new KeyPressedEvent(keyCode);
					EventQueue::Enqueue(event);
				}
				break;
			}
			case WM_KEYUP:
			case WM_SYSKEYUP: {
				Input::KeyCode keyCode = Input::ConvertWindowsKeyCode((int)wParam);
				// Only create events for relevant keycodes
				if (keyCode != Input::Unassigned) {
					KeyReleasedEvent* event = new KeyReleasedEvent(keyCode);
					EventQueue::Enqueue(event);
				}
				break;
			}
			case WM_CHAR: {
				// Text input
			}
			case WM_MOUSEMOVE: {
				if (!m_windowHasFocus) {
					break;
				}
				const POINTS point = MAKEPOINTS(lParam);
				// Check if mouse is in window, create move event if so
				if (point.x >= 0 && point.x < m_width && point.y >= 0 && point.y < m_height) {
					
					MouseMoveEvent* moveEvent = new MouseMoveEvent(point.x, point.y);
					EventQueue::Enqueue(moveEvent);

					// If mouse was not previously in window, create enter event
					if (!Mouse::IsMouseInWindow()) {
						
						SetCapture(window);
						MouseEnterEvent* enterEvent = new MouseEnterEvent();
						EventQueue::Enqueue(enterEvent);
					}
				}

				// If getting messages while mouse is not in window, continue creating move events while mouse is held
				// Release capture and create leave event when mouse is not held
				else {
					if (wParam & (MK_LBUTTON | MK_RBUTTON)) {
						MouseMoveEvent* moveEvent = new MouseMoveEvent(point.x, point.y);
						EventQueue::Enqueue(moveEvent);
					}
					else {
						ReleaseCapture();
						MouseLeaveEvent* leaveEvent = new MouseLeaveEvent();
						EventQueue::Enqueue(leaveEvent);
					}
				}
				
				break;
			}
			case WM_LBUTTONDOWN: {
				const POINTS point = MAKEPOINTS(lParam);
				LeftMousePressedEvent* event = new LeftMousePressedEvent(point.x, point.y);
				EventQueue::Enqueue(event);
				break;
			}
			case WM_LBUTTONUP: {
				const POINTS point = MAKEPOINTS(lParam);
				LeftMouseReleasedEvent* event = new LeftMouseReleasedEvent(point.x, point.y);
				EventQueue::Enqueue(event);
				break;
			}
			case WM_RBUTTONDOWN: {
				const POINTS point = MAKEPOINTS(lParam);
				RightMousePressedEvent* event = new RightMousePressedEvent(point.x, point.y);
				EventQueue::Enqueue(event);
				break;
			}
			case WM_RBUTTONUP: {
				const POINTS point = MAKEPOINTS(lParam);
				RightMouseReleasedEvent* event = new RightMouseReleasedEvent(point.x, point.y);
				EventQueue::Enqueue(event);
				break;
			}
			case WM_MBUTTONDOWN: {
				const POINTS point = MAKEPOINTS(lParam);
				MiddleMousePressedEvent* event = new MiddleMousePressedEvent(point.x, point.y);
				EventQueue::Enqueue(event);
				break;
			}
			case WM_MBUTTONUP: {
				const POINTS point = MAKEPOINTS(lParam);
				MiddleMouseReleasedEvent* event = new MiddleMouseReleasedEvent(point.x, point.y);
				EventQueue::Enqueue(event);
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
			default: {
				result = DefWindowProc(window, message, wParam, lParam);
				break;
			}
		}
		return result;
	}

	int Window::Destroy() {
		HMENU menu;
		menu = GetMenu(m_window);
		if (menu != NULL) {
			DestroyMenu(menu);
		}
		DestroyWindow(m_window);
		// Unregister window class
		UnregisterClass(m_windowClassName, m_instance);
		// Success
		return 0;
	}

	Window::~Window() {
		Destroy();
	}

	HWND Window::GetHandle() {
		return m_window;
	}

	// Return true to continue program execution, false to quit
	bool Window::ProcessMessages() {
		bool gotMsg;
		MSG msg;

		// Process window events
		gotMsg = PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0;

		if (gotMsg) {
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
	}
}