#pragma once

#include "../include/FileQueue.h"
#include <atomic>

namespace Venture {
	class FileSystem {
	private:
		static std::atomic<bool> processing;
	public:
		// Functions to create requests and add to the queue
		static File::AsyncOpenRequest* AsyncOpenFile(std::string path, std::string mode, void (*func)() = [](){});
		static File::AsyncReadRequest* AsyncReadFile(int fileHandle, char* inputBuffer, size_t bufferSize, void (*func)() = [](){});
		static File::AsyncWriteRequest* AsyncWriteFile(int fileHandle, char* outputBuffer, size_t bufferSize, void (*func)() = [](){});
		static File::AsyncCloseRequest* AsyncCloseFile(int fileHandle, void (*func)() = [](){});
		static void ProcessRequests();
		static void Terminate();
		static void Wait(File::AsyncRequest*);
	};
}