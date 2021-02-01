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
		MouseMoveEvent(int x, int y) : MouseEvent(EventType::MouseMove, x, y) {}
	};
	
	class LeftMousePressedEvent : public MouseEvent {
	public:
		LeftMousePressedEvent(int x, int y) : MouseEvent(EventType::LeftMousePressed, x, y) {}
	};

	class LeftMouseReleasedEvent : public MouseEvent {
	public:
		LeftMouseReleasedEvent(int x, int y) : MouseEvent(EventType::LeftMouseReleased, x, y) {}
	};

	class RightMousePressedEvent : public MouseEvent {
	public:
		RightMousePressedEvent(int x, int y) : MouseEvent(EventType::RightMousePressed, x, y) {}
	};

	class RightMouseReleasedEvent : public MouseEvent {
	public:
		RightMouseReleasedEvent(int x, int y) : MouseEvent(EventType::RightMouseReleased, x, y) {}
	};

	class MiddleMousePressedEvent : public MouseEvent {
	public:
		MiddleMousePressedEvent(int x, int y) : MouseEvent(EventType::MiddleMousePressed, x, y) {}
	};

	class MiddleMouseReleasedEvent : public MouseEvent {
	public:
		MiddleMouseReleasedEvent(int x, int y) : MouseEvent(EventType::MiddleMouseReleased, x, y) {}
	};

	class MouseScrollUpEvent : public MouseEvent {
	public:
		MouseScrollUpEvent(int x, int y) : MouseEvent(EventType::MouseScrollUp, x, y) {}
	};

	class MouseScrollDownEvent : public MouseEvent {
	public:
		MouseScrollDownEvent(int x, int y) : MouseEvent(EventType::MouseScrollDown, x, y) {}
	};

	class MouseEnterEvent : public MouseEvent {
	public:
		MouseEnterEvent() : MouseEvent(EventType::MouseEnter) {}
	};

	class MouseLeaveEvent : public MouseEvent {
	public:
		MouseLeaveEvent() : MouseEvent(EventType::MouseLeave) {}
	};

	// Raw input to be used with FPS camera
	class MouseDeltaEvent : public MouseEvent {
	public:
		MouseDeltaEvent(int x, int y) : MouseEvent(EventType::MouseDelta, x, y) {}
	};
}