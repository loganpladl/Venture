#include "../include/Keyboard.h"
#include "../include/EventSystem.h"
#include "../include/KeyEvent.h"

namespace Venture {
	// Activate key
	void Keyboard::KeyPressedEventHandler::Handle(Event* event) {
		KeyPressedEvent* keyPressedEvent = dynamic_cast<KeyPressedEvent*>(event);
		KeyCode keyCode = keyPressedEvent->m_keyCode;
		buttonStates[static_cast<int>(keyCode)] = true;
	}

	// Deactivate key
	void Keyboard::KeyReleasedEventHandler::Handle(Event* event) {
		KeyReleasedEvent* keyReleasedEvent = dynamic_cast<KeyReleasedEvent*>(event);
		KeyCode keyCode = keyReleasedEvent->m_keyCode;
		buttonStates[static_cast<int>(keyCode)] = false;
	}

	void Keyboard::Init() {
		EventSystem::RegisterHandler(&keyPressedHandler, EventType::KeyPressed);
		EventSystem::RegisterHandler(&keyReleasedHandler, EventType::KeyReleased);
	}

	// Initialize statics
	Keyboard::KeyPressedEventHandler Keyboard::keyPressedHandler;
	Keyboard::KeyReleasedEventHandler Keyboard::keyReleasedHandler;
	// Initialize all to false
	bool Keyboard::buttonStates[static_cast<int>(KeyCode::DownArrow) + 1] = { false };

	Keyboard::KeyCode Keyboard::ConvertWindowsKeyCode(int keyCode) {
		// TODO: Refactor to switch statement
		if (keyCode == 0x01) {
			return KeyCode::LeftMouse;
		}
		else if (keyCode == 0x02) {
			return KeyCode::RightMouse;
		}
		else if (keyCode == 0x04) {
			return KeyCode::MiddleMouse;
		}
		else if (keyCode == 0x08) {
			return KeyCode::Backspace;
		}
		else if (keyCode == 0x09) {
			return KeyCode::Tab;
		}
		else if (keyCode == 0x0D) {
			return KeyCode::Enter;
		}
		else if (keyCode == 0x10) {
			return KeyCode::Shift;
		}
		else if (keyCode == 0x11) {
			return KeyCode::Ctrl;
		}
		else if (keyCode == 0x12) {
			return KeyCode::Alt;
		}
		else if (keyCode == 0x1B) {
			return KeyCode::Escape;
		}
		else if (keyCode == 0x20) {
			return KeyCode::Space;
		}
		else if (keyCode == 0x25) {
			return KeyCode::LeftArrow;
		}
		else if (keyCode == 0x26) {
			return KeyCode::UpArrow;
		}
		else if (keyCode == 0x27) {
			return KeyCode::RightArrow;
		}
		else if (keyCode == 0x28) {
			return KeyCode::DownArrow;
		}
		else if (keyCode >= 0x30 && keyCode <= 0x39) {
			// Convert numeric keycodes
			return (KeyCode)(static_cast<int>(KeyCode::Zero) + keyCode - 0x30);
		}
		else if (keyCode >= 0x41 && keyCode <= 0x5A) {
			// Convert alphabetical keycodes
			return (KeyCode)(static_cast<int>(KeyCode::A) + keyCode - 0x41);
		}
		else {
			return KeyCode::Unassigned;
		}
	}

	
}