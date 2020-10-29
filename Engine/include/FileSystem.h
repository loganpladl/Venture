#pragma once

#include "FileQueue.h"
#include <atomic>
#include "Buffer.h"

namespace Venture {
	class FileSystem {
	private:
		static std::atomic<bool> processing;
	public:
		// Functions to create requests and add to the queue
		static File::AsyncOpenRequest* AsyncOpenFile(std::string path, std::string mode, void (*func)() = [](){});
		static File::AsyncReadRequest* AsyncReadFile(int fileHandle, Buffer inputBuffer, size_t bufferSize, void (*func)() = [](){});
		static File::AsyncReadFullRequest* AsyncReadFullFile(int fileHandle, Buffer inputBuffer, void (*func)() = [](){});
		static File::AsyncWriteRequest* AsyncWriteFile(int fileHandle, Buffer outputBuffer, size_t bufferSize, void (*func)() = [](){});
		static File::AsyncCloseRequest* AsyncCloseFile(int fileHandle, void (*func)() = [](){});
		static void ProcessRequests();
		static void Terminate();
	};
}