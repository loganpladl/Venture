#include "../include/FileQueue.h"

namespace Venture {
	// Define static variables
	File::AsyncRequest* FileQueue::queue[MAX_REQUESTS];
	int FileQueue::head = 0;
	int FileQueue::tail = 0;
	std::mutex FileQueue::mutex;

	void FileQueue::Init() {

	}
	int FileQueue::Enqueue(File::AsyncRequest* request) {
		mutex.lock();
		// Check if queue is full
		if ((tail + 1) % MAX_REQUESTS == head) {
			// Failure
			mutex.unlock();
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
		mutex.unlock();

		return 0;
	}

	File::AsyncRequest* FileQueue::Dequeue() {
		mutex.lock();
		// check if queue is empty
		if (head == tail) {
			mutex.unlock();
			return nullptr;
		}
		File::AsyncRequest* event = queue[head];

		head = (head + 1) % MAX_REQUESTS;
		mutex.unlock();

		return event;
	}
}