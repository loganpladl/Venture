#pragma once

namespace Venture {
	enum EventType {
		KeyPressed,
		KeyReleased
	};
	const int NUM_EVENT_TYPES = 2;

	class Event {
	protected:
		EventType m_type;
		Event(EventType type) : m_type(type) {}
	public:
		virtual ~Event() {};
		inline virtual EventType getType() { return m_type; }
	};
}