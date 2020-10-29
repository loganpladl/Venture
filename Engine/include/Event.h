#pragma once

namespace Venture {
	enum EventType {
		KeyPressed,
		KeyReleased,
		MouseMove,
		LeftMousePressed,
		LeftMouseReleased,
		RightMousePressed,
		RightMouseReleased,
		MiddleMousePressed,
		MiddleMouseReleased,
		MouseScrollUp,
		MouseScrollDown,
		MouseEnter,
		MouseLeave
	};
	const int NUM_EVENT_TYPES = 13;

	class Event {
	protected:
		EventType m_type;
		Event(EventType type) : m_type(type) {}
	public:
		virtual ~Event() {};
		inline virtual EventType getType() { return m_type; }
	};
}