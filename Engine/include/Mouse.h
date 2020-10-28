#pragma once
#include "EventQueue.h"
#include "MouseEvent.h"

namespace Venture {
	class Mouse {
	private:
		static int m_x;
		static int m_y;

		struct MouseMoveEventHandler : EventHandler {
			void Handle(Event* event) override;
		};

		struct LeftMousePressedEventHandler : EventHandler {
			void Handle(Event* event) override;
		};

		struct LeftMouseReleasedEventHandler : EventHandler {
			void Handle(Event* event) override;
		};

		struct RightMousePressedEventHandler : EventHandler {
			void Handle(Event* event) override;
		};

		struct RightMouseReleasedEventHandler : EventHandler {
			void Handle(Event* event) override;
		};

		struct MiddleMousePressedEventHandler : EventHandler {
			void Handle(Event* event) override;
		};

		struct MiddleMouseReleasedEventHandler : EventHandler {
			void Handle(Event* event) override;
		};

		struct MouseScrollUpEventHandler : EventHandler {
			void Handle(Event* event) override;
		};

		struct MouseScrollDownEventHandler : EventHandler {
			void Handle(Event* event) override;
		};
	public:
		static void Init();
		static MouseMoveEventHandler mouseMoveHandler;
		static LeftMousePressedEventHandler leftMousePressedHandler;
		static LeftMouseReleasedEventHandler leftMouseReleasedHandler;
		static RightMousePressedEventHandler rightMousePressedHandler;
		static RightMouseReleasedEventHandler rightMouseReleasedHandler;
		static MiddleMousePressedEventHandler middleMousePressedHandler;
		static MiddleMouseReleasedEventHandler middleMouseReleasedHandler;
		static MouseScrollUpEventHandler mouseScrollUpHandler;
		static MouseScrollDownEventHandler mouseScrollDownHandler;
	};
}