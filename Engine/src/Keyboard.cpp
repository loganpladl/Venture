#include "../include/Keyboard.h"
#include "../include/EventSystem.h"
#include "../include/KeyEvent.h"

namespace Venture {
	// Activate key
	void Keyboard::KeyPressedEventHandler::Handle(Event* event) {
		KeyPressedEvent* keyPressedEvent = dynamic_cast<KeyPressedEvent*>(event);
		KeyCode keyCode = keyPressedEvent->m_keyCode;
		buttonStates[keyCode] = true;
	}

	// Deactivate key
	void Keyboard::KeyReleasedEventHandler::Handle(Event* event) {
		KeyReleasedEvent* keyReleasedEvent = dynamic_cast<KeyReleasedEvent*>(event);
		KeyCode keyCode = keyReleasedEvent->m_keyCode;
		buttonStates[keyCode] = false;
	}

	void Keyboard::Init() {
		EventSystem::RegisterHandler(&keyPressedHandler, EventType::KeyPressed);
		EventSystem::RegisterHandler(&keyReleasedHandler, EventType::KeyReleased);
	}

	// Initialize statics
	Keyboard::KeyPressedEventHandler Keyboard::keyPressedHandler;
	Keyboard::KeyReleasedEventHandler Keyboard::keyReleasedHandler;
	// Initialize all to false
	bool Keyboard::buttonStates[DownArrow + 1] = { false };

	Keyboard::KeyCode Keyboard::ConvertWindowsKeyCode(int keyCode) {
		if (keyCode == 0x01) {
			return LeftMouse;
		}
		else if (keyCode == 0x02) {
			return RightMouse;
		}
		else if (keyCode == 0x04) {
			return MiddleMouse;
		}
		else if (keyCode == 0x08) {
			return Backspace;
		}
		else if (keyCode == 0x09) {
			return Tab;
		}
		else if (keyCode == 0x0D) {
			return Enter;
		}
		else if (keyCode == 0x10) {
			return Shift;
		}
		else if (keyCode == 0x11) {
			return Ctrl;
		}
		else if (keyCode == 0x12) {
			return Alt;
		}
		else if (keyCode == 0x20) {
			return Space;
		}
		else if (keyCode == 0x25) {
			return LeftArrow;
		}
		else if (keyCode == 0x26) {
			return UpArrow;
		}
		else if (keyCode == 0x27) {
			return RightArrow;
		}
		else if (keyCode == 0x28) {
			return DownArrow;
		}
		else if (keyCode >= 0x30 && keyCode <= 0x39) {
			// Convert numeric keycodes
			return (KeyCode)(Zero + keyCode - 0x30);
		}
		else if (keyCode >= 0x41 && keyCode <= 0x5A) {
			// Convert alphabetical keycodes
			return (KeyCode)(A + keyCode - 0x41);
		}
		else {
			return Unassigned;
		}
	}

	
}