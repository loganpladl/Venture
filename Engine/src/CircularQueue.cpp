#include "../include/CircularQueue.h"

namespace Venture {
	// Define static variables
	template<class T>
	T CircularQueue<T>::queue[MAX_ELEMENTS];
	template<class T>
	int CircularQueue<T>::head = 0;
	template<class T>
	int CircularQueue<T>::tail = 0;

	template<class T>
	int CircularQueue<T>::Enqueue(T event) {
		// Check if queue is full
		if ((tail + 1) % MAX_ELEMENTS == head) {
			// Failure
			return -1;
		}
		queue[tail] = event;
		tail = (tail + 1) % MAX_ELEMENTS;
		return 0;
	}
	template<class T>
	T CircularQueue<T>::Dequeue() {
		// check if queue is empty
		if (head == tail) {
			return nullptr;
		}
		T element = queue[head];

		head = (head + 1) % MAX_ELEMENTS;

		return element;
	}
}