#pragma once

#include "Event.h"
#include "EventHandler.h"
#include <list>

namespace Venture {
	class EventQueue {
	private:
		static const int MAX_EVENTS = 256;
		static Event* queue[MAX_EVENTS];
		static int head, tail;
		// Array of lists of registered event handlers to receive events of each event type
		static std::list<EventHandler*> eventHandlers[NUM_EVENT_TYPES];
	public:
		static int Enqueue(Event* event);
		static Event* Dequeue();
		// Dispatch all events
		static void DispatchEvents();
		// Dispatch event to all listeners
		static void Dispatch(Event* event);
		static void RegisterHandler(EventHandler* handler, EventType type);
	};
}