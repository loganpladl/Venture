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
		MouseLeave,
		MouseDelta
	};
	const int NUM_EVENT_TYPES = 14;

	class Event {
	protected:
		EventType m_type;
		Event(EventType type) : m_type(type) {}
	public:
		virtual ~Event() {};
		inline virtual EventType getType() { return m_type; }
	};
}