#include "../include/EventSystem.h"

namespace Venture {
	// Initialize static variables
	std::list<EventHandler*> EventSystem::s_eventHandlers[NUM_EVENT_TYPES];
	CircularQueue<Event*> EventSystem::s_eventQueue;

	void EventSystem::DispatchEvents() {
		// Broadcast all events in queue
		while (Event* event = s_eventQueue.Dequeue()) {
			Dispatch(event);
		}
	}

	void EventSystem::Dispatch(Event* event) {
		EventType type = event->getType();
		std::list<EventHandler*> handlers = s_eventHandlers[static_cast<int>(type)];
		for (auto& handler : handlers) {
			handler->Handle(event);
		}
		delete(event);
	}

	void EventSystem::RegisterHandler(EventHandler* handler, EventType type) {
		s_eventHandlers[static_cast<int>(type)].push_back(handler);
	}

	void EventSystem::Enqueue(Event* event) {
		s_eventQueue.Enqueue(event);
	}

	Event* EventSystem::Dequeue() {
		Event* event = s_eventQueue.Dequeue();
		return event;
	}
}