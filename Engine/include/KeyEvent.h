#pragma once

#include "Event.h"
#include "Input.h"

namespace Venture {
	class KeyPressedEvent : public Event {
	private :

	public:
		KeyPressedEvent(Input::KeyCode keyCode) : Event{ KeyPressed }, m_keyCode(keyCode) {}
		Input::KeyCode m_keyCode;
	};

	class KeyReleasedEvent : public Event {
	private:

	public:
		KeyReleasedEvent(Input::KeyCode keyCode) : Event{ KeyReleased }, m_keyCode(keyCode) {}
		Input::KeyCode m_keyCode;
	};
}