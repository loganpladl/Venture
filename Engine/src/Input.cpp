#include "../include/Input.h"

namespace Venture {
	void Input::Init() {
		Mouse::Init();
		Keyboard::Init();
	}

	KeyPressedEvent* Input::KeyPressed(Keyboard::KeyCode keyCode) {
		KeyPressedEvent* event = new KeyPressedEvent(keyCode);
		EventSystem::Enqueue(event);
		return event;
	}

	KeyReleasedEvent* Input::KeyReleased(Keyboard::KeyCode keyCode) {
		KeyReleasedEvent* event = new KeyReleasedEvent(keyCode);
		EventSystem::Enqueue(event);
		return event;
	}

	MouseMoveEvent* Input::MouseMove(int x, int y) {
		MouseMoveEvent* event = new MouseMoveEvent(x, y);
		EventSystem::Enqueue(event);
		return event;
	}
	MouseEnterEvent* Input::MouseEnter() {
		MouseEnterEvent* event = new MouseEnterEvent();
		EventSystem::Enqueue(event);
		return event;
	}
	MouseLeaveEvent* Input::MouseLeave() {
		MouseLeaveEvent* event = new MouseLeaveEvent();
		EventSystem::Enqueue(event);
		return event;
	}
	LeftMousePressedEvent* Input::LeftMousePressed(int x, int y) {
		LeftMousePressedEvent* event = new LeftMousePressedEvent(x, y);
		EventSystem::Enqueue(event);
		return event;
	}
	LeftMouseReleasedEvent* Input::LeftMouseReleased(int x, int y) {
		LeftMouseReleasedEvent* event = new LeftMouseReleasedEvent(x, y);
		EventSystem::Enqueue(event);
		return event;
	}
	RightMousePressedEvent* Input::RightMousePressed(int x, int y) {
		RightMousePressedEvent* event = new RightMousePressedEvent(x, y);
		EventSystem::Enqueue(event);
		return event;
	}
	RightMouseReleasedEvent* Input::RightMouseReleased(int x, int y) {
		RightMouseReleasedEvent* event = new RightMouseReleasedEvent(x, y);
		EventSystem::Enqueue(event);
		return event;
	}
	MiddleMousePressedEvent* Input::MiddleMousePressed(int x, int y) {
		MiddleMousePressedEvent* event = new MiddleMousePressedEvent(x, y);
		EventSystem::Enqueue(event);
		return event;
	}
	MiddleMouseReleasedEvent* Input::MiddleMouseReleased(int x, int y) {
		MiddleMouseReleasedEvent* event = new MiddleMouseReleasedEvent(x, y);
		EventSystem::Enqueue(event);
		return event;
	}
	MouseDeltaEvent* Input::MouseDelta(int x, int y) {
		MouseDeltaEvent* event = new MouseDeltaEvent(x, y);
		EventSystem::Enqueue(event);
		return event;
	}
}