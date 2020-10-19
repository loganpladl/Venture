#pragma once

#include "../include/FileQueue.h"
#include <atomic>

namespace Venture {
	class FileSystem {
	private:
		static std::atomic<bool> processing;
	public:
		// Functions to create requests and add to the queue
		static File::AsyncOpenRequest* AsyncOpenFile(std::string path, void (*func)() = [](){});
		static File::AsyncReadRequest* AsyncReadFile(File::AsyncFile file, char* inputBuffer, size_t bufferSize, void (*func)() = [](){});
		static File::AsyncWriteRequest* AsyncWriteFile(File::AsyncFile file, char* outputBuffer, size_t bufferSize, void (*func)() = [](){});
		static File::AsyncCloseRequest* AsyncCloseFile(File::AsyncFile file, void (*func)() = [](){});
		static void ProcessRequests();
		static void Terminate();
	};
}