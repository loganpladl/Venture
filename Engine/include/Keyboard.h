#pragma once
#include "EventHandler.h"

namespace Venture {
	class Keyboard {
	private:
		struct KeyPressedEventHandler : EventHandler {
			void Handle(Event* event) override;
		};

		struct KeyReleasedEventHandler : EventHandler {
			void Handle(Event* event) override;
		};
	public:
		static KeyPressedEventHandler keyPressedHandler;
		static KeyReleasedEventHandler keyReleasedHandler;
		enum class KeyCode {
			Unassigned, LeftMouse, RightMouse, MiddleMouse,
			A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine,
			Backspace, Tab, Enter, Shift, Ctrl, Alt, Escape, Space,
			LeftArrow, UpArrow, RightArrow, DownArrow
		};
		static const int NUM_KEY_CODES = 52;

		static bool buttonStates[NUM_KEY_CODES];

		static KeyCode ConvertWindowsKeyCode(int keyCode);

		inline static bool IsButtonPressed(KeyCode keyCode) {
			return buttonStates[static_cast<int>(keyCode)];
		}
		static void Init();
	};
}