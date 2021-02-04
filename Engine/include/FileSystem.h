#pragma once

#include "File.h"
#include <atomic>
#include "Buffer.h"
#include "CircularQueue.h"

namespace Venture {
	class FileSystem {
	private:
		static std::atomic<bool> s_processing;
		// Use "Construct Members on First Use" idiom to avoid static initialization order disaster
		static std::mutex s_queueMutex;
		static CircularQueue<File::AsyncRequest*> s_queue;
	public:
		// Functions to create requests and add to the queue
		static File::AsyncOpenRequest* AsyncOpenFile(std::string path, std::string mode, void (*func)() = [](){});
		static File::AsyncReadRequest* AsyncReadFile(int fileHandle, Buffer inputBuffer, size_t bufferSize, void (*func)() = [](){});
		static File::AsyncReadFullRequest* AsyncReadFullFile(int fileHandle, Buffer inputBuffer, void (*func)() = [](){});
		static File::AsyncWriteRequest* AsyncWriteFile(int fileHandle, Buffer outputBuffer, size_t bufferSize, void (*func)() = [](){});
		static File::AsyncCloseRequest* AsyncCloseFile(int fileHandle, void (*func)() = [](){});
		static File::AsyncOpenReadCloseRequest* AsyncOpenReadCloseFile(std::string path, std::string mode, void (*func)() = [](){});
		static void ProcessRequests();
		static void Terminate();
		static void Enqueue(File::AsyncRequest*);
		static File::AsyncRequest* Dequeue();
	};
}