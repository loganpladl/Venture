#pragma once

#include "Event.h"
#include "Keyboard.h"

namespace Venture {
	class KeyPressedEvent : public Event {
	private :

	public:
		KeyPressedEvent(Keyboard::KeyCode keyCode) : Event{ KeyPressed }, m_keyCode(keyCode) {}
		Keyboard::KeyCode m_keyCode;
	};

	class KeyReleasedEvent : public Event {
	private:

	public:
		KeyReleasedEvent(Keyboard::KeyCode keyCode) : Event{ KeyReleased }, m_keyCode(keyCode) {}
		Keyboard::KeyCode m_keyCode;
	};
}