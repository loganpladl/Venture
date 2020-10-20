#include "../include/FileQueue.h"

namespace Venture {
	// Define static variables
	File::AsyncRequest* FileQueue::queue[MAX_REQUESTS];
	int FileQueue::head = 0;
	int FileQueue::tail = 0;

	void FileQueue::Init() {

	}
	int FileQueue::Enqueue(File::AsyncRequest* request) {
		// Check if queue is full
		if ((tail + 1) % MAX_REQUESTS == head) {
			// Failure
			return -1;
		}
		// Delete old request at current tail before replacing
		// Delete now instead of on dequeue so that main thread can wait on associated semaphore
		File::AsyncRequest* old = queue[tail];
		if (old != nullptr) {
			delete(old);
		}

		queue[tail] = request;
		tail = (tail + 1) % MAX_REQUESTS;
		return 0;
	}

	File::AsyncRequest* FileQueue::Dequeue() {
		// check if queue is empty
		if (head == tail) {
			return nullptr;
		}
		File::AsyncRequest* event = queue[head];

		head = (head + 1) % MAX_REQUESTS;

		return event;
	}
}