#pragma once

#include "Mouse.h"
#include "Keyboard.h"
#include "EventSystem.h"
#include "KeyEvent.h"
#include "MouseEvent.h"

namespace Venture {
	class Input {
	private:
		
	public:
		static void Init();

		static KeyPressedEvent* KeyPressed(Keyboard::KeyCode);
		static KeyReleasedEvent* KeyReleased(Keyboard::KeyCode);

		static MouseMoveEvent* MouseMove(int x, int y);
		static MouseEnterEvent* MouseEnter();
		static MouseLeaveEvent* MouseLeave();
		static LeftMousePressedEvent* LeftMousePressed(int x, int y);
		static LeftMouseReleasedEvent* LeftMouseReleased(int x, int y);
		static RightMousePressedEvent* RightMousePressed(int x, int y);
		static RightMouseReleasedEvent* RightMouseReleased(int x, int y);
		static MiddleMousePressedEvent* MiddleMousePressed(int x, int y);
		static MiddleMouseReleasedEvent* MiddleMouseReleased(int x, int y);
		static MouseDeltaEvent* MouseDelta(int x, int y);
	};
}