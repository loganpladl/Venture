#include "../include/Mouse.h"
#include <utility>
#include "../include/Log.h"
#include "../include/EventSystem.h"
#include "../include/MouseEvent.h"

namespace Venture {
	// initialize statics
	int Mouse::m_x = 0;
	int Mouse::m_y = 0;
	bool Mouse::m_mouseInWindow = false;
	int Mouse::m_scrollDelta = 0;

	Mouse::MouseMoveEventHandler Mouse::mouseMoveHandler;
	Mouse::LeftMousePressedEventHandler Mouse::leftMousePressedHandler;
	Mouse::LeftMouseReleasedEventHandler Mouse::leftMouseReleasedHandler;
	Mouse::RightMousePressedEventHandler Mouse::rightMousePressedHandler;
	Mouse::RightMouseReleasedEventHandler Mouse::rightMouseReleasedHandler;
	Mouse::MiddleMousePressedEventHandler Mouse::middleMousePressedHandler;
	Mouse::MiddleMouseReleasedEventHandler Mouse::middleMouseReleasedHandler;
	Mouse::MouseScrollUpEventHandler Mouse::mouseScrollUpHandler;
	Mouse::MouseScrollDownEventHandler Mouse::mouseScrollDownHandler;
	Mouse::MouseEnterEventHandler Mouse::mouseEnterHandler;
	Mouse::MouseLeaveEventHandler Mouse::mouseLeaveHandler;

	void Mouse::MouseMoveEventHandler::Handle(Event* event) {
		MouseMoveEvent* mouseMoveEvent = dynamic_cast<MouseMoveEvent*>(event);
		std::pair<int, int> position = mouseMoveEvent->GetPosition();
		m_x = position.first;
		m_y = position.second;
		Log::DebugPrintF(1, Log::Channel::Input, "Mouse Moved - x = %i, y = %i \n", m_x, m_y);
	}

	void Mouse::LeftMousePressedEventHandler::Handle(Event* event) {
		LeftMousePressedEvent* leftMousePressedEvent = dynamic_cast<LeftMousePressedEvent*>(event);
		std::pair<int, int> position = leftMousePressedEvent->GetPosition();
		Log::DebugPrintF(1, Log::Channel::Input, "Left Mouse Clicked - x = %i, y = %i \n", m_x, m_y);
	}

	void Mouse::LeftMouseReleasedEventHandler::Handle(Event* event) {
		LeftMouseReleasedEvent* leftMouseReleasedEvent = dynamic_cast<LeftMouseReleasedEvent*>(event);
		std::pair<int, int> position = leftMouseReleasedEvent->GetPosition();
		Log::DebugPrintF(1, Log::Channel::Input, "Left Mouse Released - x = %i, y = %i \n", m_x, m_y);
	}

	void Mouse::RightMousePressedEventHandler::Handle(Event* event) {
		RightMousePressedEvent* rightMousePressedEvent = dynamic_cast<RightMousePressedEvent*>(event);
		std::pair<int, int> position = rightMousePressedEvent->GetPosition();
		Log::DebugPrintF(1, Log::Channel::Input, "Right Mouse Clicked - x = %i, y = %i \n", m_x, m_y);
	}

	void Mouse::RightMouseReleasedEventHandler::Handle(Event* event) {
		RightMouseReleasedEvent* rightMouseReleasedEvent = dynamic_cast<RightMouseReleasedEvent*>(event);
		std::pair<int, int> position = rightMouseReleasedEvent->GetPosition();
		Log::DebugPrintF(1, Log::Channel::Input, "Right Mouse Released - x = %i, y = %i \n", m_x, m_y);
	}

	void Mouse::MiddleMousePressedEventHandler::Handle(Event* event) {
		MiddleMousePressedEvent* middleMousePressedEvent = dynamic_cast<MiddleMousePressedEvent*>(event);
		std::pair<int, int> position = middleMousePressedEvent->GetPosition();
		Log::DebugPrintF(1, Log::Channel::Input, "Middle Mouse Clicked - x = %i, y = %i \n", m_x, m_y);
	}

	void Mouse::MiddleMouseReleasedEventHandler::Handle(Event* event) {
		MiddleMouseReleasedEvent* middleMouseReleasedEvent = dynamic_cast<MiddleMouseReleasedEvent*>(event);
		std::pair<int, int> position = middleMouseReleasedEvent->GetPosition();
		Log::DebugPrintF(1, Log::Channel::Input, "Middle Mouse Released - x = %i, y = %i \n", m_x, m_y);
	}

	void Mouse::MouseScrollUpEventHandler::Handle(Event* event) {
		MouseScrollUpEvent* mouseScrollUpEvent = dynamic_cast<MouseScrollUpEvent*>(event);
		std::pair<int, int> position = mouseScrollUpEvent->GetPosition();
		Log::DebugPrintF(1, Log::Channel::Input, "Mouse Scroll Up - x = %i, y = %i \n", m_x, m_y);
	}

	void Mouse::MouseScrollDownEventHandler::Handle(Event* event) {
		MouseScrollDownEvent* mouseScrollDownEvent = dynamic_cast<MouseScrollDownEvent*>(event);
		std::pair<int, int> position = mouseScrollDownEvent->GetPosition();
		Log::DebugPrintF(1, Log::Channel::Input, "Mouse Scroll Down - x = %i, y = %i \n", m_x, m_y);
	}

	void Mouse::MouseEnterEventHandler::Handle(Event* event) {
		MouseEnterEvent* mouseEnterEvent = dynamic_cast<MouseEnterEvent*>(event);
		MouseEnterWindow();
		Log::DebugPrintF(1, Log::Channel::Input, "Mouse Enter \n");
	}

	void Mouse::MouseLeaveEventHandler::Handle(Event* event) {
		MouseLeaveEvent* mouseLeaveEvent = dynamic_cast<MouseLeaveEvent*>(event);
		MouseLeaveWindow();
		Log::DebugPrintF(1, Log::Channel::Input, "Mouse Leave \n");
	}

	void Mouse::Init() {
		EventSystem::RegisterHandler(&mouseMoveHandler, EventType::MouseMove);
		EventSystem::RegisterHandler(&leftMousePressedHandler, EventType::LeftMousePressed);
		EventSystem::RegisterHandler(&leftMouseReleasedHandler, EventType::LeftMouseReleased);
		EventSystem::RegisterHandler(&rightMousePressedHandler, EventType::RightMousePressed);
		EventSystem::RegisterHandler(&rightMouseReleasedHandler, EventType::RightMouseReleased);
		EventSystem::RegisterHandler(&middleMousePressedHandler, EventType::MiddleMousePressed);
		EventSystem::RegisterHandler(&middleMouseReleasedHandler, EventType::MiddleMouseReleased);
		EventSystem::RegisterHandler(&mouseScrollUpHandler, EventType::MouseScrollUp);
		EventSystem::RegisterHandler(&mouseScrollDownHandler, EventType::MouseScrollDown);
		EventSystem::RegisterHandler(&mouseEnterHandler, EventType::MouseEnter);
		EventSystem::RegisterHandler(&mouseLeaveHandler, EventType::MouseLeave);
	}

	void Mouse::MouseScrolled(int x, int y, int delta) {
		m_scrollDelta += delta;

		// Generate scroll up events when accumulated delta is WHEEL_DELTA (120)
		if (m_scrollDelta >= WHEEL_DELTA) {
			m_scrollDelta -= WHEEL_DELTA;
			MouseScrollUpEvent* event = new MouseScrollUpEvent(x, y);
			EventSystem::Enqueue(event);
		}
		// Generate scroll down events when accumulated delta is -WHEEL_DELTA (-120)
		if (m_scrollDelta <= -WHEEL_DELTA) {
			m_scrollDelta += WHEEL_DELTA;
			MouseScrollDownEvent* event = new MouseScrollDownEvent(x, y);
			EventSystem::Enqueue(event);
		}
	}

	
}