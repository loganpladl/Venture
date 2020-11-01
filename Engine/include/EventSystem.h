#pragma once

#include "Event.h"
#include "EventHandler.h"
#include <list>
#include "CircularQueue.h"

namespace Venture {
	class EventSystem {
	private:
		static CircularQueue<Event*> s_eventQueue;
		// Array of lists of registered event handlers to receive events of each event type
		static std::list<EventHandler*> s_eventHandlers[NUM_EVENT_TYPES];
	public:
		// Dispatch all events
		static void DispatchEvents();
		// Dispatch event to all listeners
		static void Dispatch(Event* event);
		static void RegisterHandler(EventHandler* handler, EventType type);
		static void Enqueue(Event*);
		static Event* Dequeue();
	};
}