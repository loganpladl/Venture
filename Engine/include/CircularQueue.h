#pragma once

namespace Venture {
	template <class T>
	class CircularQueue {
	private:
		static const int MAX_ELEMENTS = 256;
		T queue[MAX_ELEMENTS] = {};
		// Remove elements at the head index
		int head = 0;
		// Add elements at the tail index
		int tail = 0;
	public:
		int Enqueue(T event) {
			// Check if queue is full
			if ((tail + 1) % MAX_ELEMENTS == head) {
				// Failure
				return -1;
			}
			queue[tail] = event;
			tail = (tail + 1) % MAX_ELEMENTS;
			return 0;
		}
		T Dequeue() {
			// check if queue is empty
			if (head == tail) {
				return nullptr;
			}
			T element = queue[head];

			head = (head + 1) % MAX_ELEMENTS;

			return element;
		}
		// Return the element at the tail without removing from the queue
		T PeekTail() {
			return queue[tail];
		}
	};
}