#pragma once
#include "File.h"

namespace Venture {
	class FileQueue {
	private:
		// Request Queue
		static const int MAX_REQUESTS = 256;
		static File::AsyncRequest* queue[MAX_REQUESTS];
		static int head, tail;
	public:
		static void Init();
		static int Enqueue(File::AsyncRequest* request);
		static File::AsyncRequest* Dequeue();
	};
}