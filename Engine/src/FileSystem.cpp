#include "../include/FileSystem.h"

namespace Venture {
	// Initialize static loop flag to true
	std::atomic<bool> FileSystem::processing = true;

	File::AsyncOpenRequest* FileSystem::AsyncOpenFile(std::string path, void (*func)()) {
		File::AsyncOpenRequest* request = new File::AsyncOpenRequest(path);
		FileQueue::Enqueue(request);
		return request;
	}

	File::AsyncReadRequest* FileSystem::AsyncReadFile(File::AsyncFile file, char* inputBuffer, size_t bufferSize, void (*func)()) {
		File::AsyncReadRequest* request = new File::AsyncReadRequest(file, inputBuffer, bufferSize, func);
		FileQueue::Enqueue(request);
		return request;
	}

	File::AsyncWriteRequest* FileSystem::AsyncWriteFile(File::AsyncFile file, char* outputBuffer, size_t bufferSize, void (*func)()) {
		File::AsyncWriteRequest* request = new File::AsyncWriteRequest(file, outputBuffer, bufferSize, func);
		FileQueue::Enqueue(request);
		return request;
	}

	File::AsyncCloseRequest* FileSystem::AsyncCloseFile(File::AsyncFile file, void (*func)()) {
		File::AsyncCloseRequest* request = new File::AsyncCloseRequest(file, func);
		FileQueue::Enqueue(request);
		return request;
	}

	// Function to be called by IO thread
	void FileSystem::ProcessRequests() {
		while (processing) {
			while (File::AsyncRequest* request = FileQueue::Dequeue()) {
				request->ProcessRequest();
			}
		}
	}

	void FileSystem::Terminate() {
		processing = false;
	}
}