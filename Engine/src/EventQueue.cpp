#include "../include/EventQueue.h"

namespace Venture {
	// Define static variables
	Event* EventQueue::queue[MAX_EVENTS];
	int EventQueue::head = 0;
	int EventQueue::tail = 0;
	std::list<EventHandler*> EventQueue::eventHandlers[NUM_EVENT_TYPES];

	void EventQueue::Init() {

	}
	int EventQueue::Enqueue(Event* event) {
		// Check if queue is full
		if ((head + 1) % MAX_EVENTS == tail) {
			// Failure
			return -1;
		}
		queue[tail] = event;
		tail = (tail + 1) % MAX_EVENTS;
		return 0;
	}

	Event* EventQueue::Dequeue() {
		// check if queue is empty
		if (head == tail) {
			return nullptr;
		}
		Event* event = queue[head];

		head = (head + 1) % MAX_EVENTS;

		return event;
	}

	void EventQueue::DispatchEvents() {
		// Broadcast all events in queue
		while (Event* event = Dequeue()) {
			Dispatch(event);
		}
	}

	void EventQueue::Dispatch(Event* event) {
		EventType type = event->getType();
		std::list<EventHandler*> handlers = eventHandlers[type];
		for (auto& handler : handlers) {
			handler->Handle(event);
		}
		delete(event);
	}

	void EventQueue::RegisterHandler(EventHandler* handler, EventType type) {
		eventHandlers[type].push_back(handler);
	}
}