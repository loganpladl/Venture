#pragma once

#include "Event.h"
#include <utility>

namespace Venture {
	// Abstract mouse event containing mouse position
	class MouseEvent : public Event {
	protected:
		int m_x;
		int m_y;
		MouseEvent(EventType type, int x, int y) : Event{type}, m_x(x), m_y(y) {}
		MouseEvent(EventType type) : Event{type}, m_x(0), m_y(0) {}
	public:
		std::pair<int, int> GetPosition() {
			return std::pair<int, int>(m_x, m_y);
		}
	};

	class MouseMoveEvent : public MouseEvent {
	public:
		MouseMoveEvent(int x, int y) : MouseEvent(MouseMove, x, y) {}
	};
	
	class LeftMousePressedEvent : public MouseEvent {
	public:
		LeftMousePressedEvent(int x, int y) : MouseEvent(LeftMousePressed, x, y) {}
	};

	class LeftMouseReleasedEvent : public MouseEvent {
	public:
		LeftMouseReleasedEvent(int x, int y) : MouseEvent(LeftMouseReleased, x, y) {}
	};

	class RightMousePressedEvent : public MouseEvent {
	public:
		RightMousePressedEvent(int x, int y) : MouseEvent(RightMousePressed, x, y) {}
	};

	class RightMouseReleasedEvent : public MouseEvent {
	public:
		RightMouseReleasedEvent(int x, int y) : MouseEvent(RightMouseReleased, x, y) {}
	};

	class MiddleMousePressedEvent : public MouseEvent {
	public:
		MiddleMousePressedEvent(int x, int y) : MouseEvent(MiddleMousePressed, x, y) {}
	};

	class MiddleMouseReleasedEvent : public MouseEvent {
	public:
		MiddleMouseReleasedEvent(int x, int y) : MouseEvent(MiddleMouseReleased, x, y) {}
	};

	class MouseScrollUpEvent : public MouseEvent {
	public:
		MouseScrollUpEvent(int x, int y) : MouseEvent(MouseScrollUp, x, y) {}
	};

	class MouseScrollDownEvent : public MouseEvent {
	public:
		MouseScrollDownEvent(int x, int y) : MouseEvent(MouseScrollDown, x, y) {}
	};

	class MouseEnterEvent : public MouseEvent {
	public:
		MouseEnterEvent() : MouseEvent(MouseEnter) {}
	};

	class MouseLeaveEvent : public MouseEvent {
	public:
		MouseLeaveEvent() : MouseEvent(MouseLeave) {}
	};
}