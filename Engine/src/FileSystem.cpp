#include "../include/FileSystem.h"

namespace Venture {
	// Initialize static loop flag to true
	std::atomic<bool> FileSystem::processing = true;

	// Array of open files

	File::AsyncOpenRequest* FileSystem::AsyncOpenFile(std::string path, std::string mode, void (*func)()) {
		File::AsyncOpenRequest* request = new File::AsyncOpenRequest(path, mode, func);
		FileQueue::Enqueue(request);
		return request;
	}

	File::AsyncReadRequest* FileSystem::AsyncReadFile(int fileHandle, Buffer& inputBuffer, size_t bufferSize, void (*func)()) {
		File::AsyncReadRequest* request = new File::AsyncReadRequest(fileHandle, inputBuffer, bufferSize, func);
		FileQueue::Enqueue(request);
		return request;
	}

	File::AsyncReadFullRequest* FileSystem::AsyncReadFullFile(int fileHandle, Buffer& inputBuffer, void (*func)()) {
		File::AsyncReadFullRequest* request = new File::AsyncReadFullRequest(fileHandle, inputBuffer, func);
		FileQueue::Enqueue(request);
		return request;
	}

	File::AsyncWriteRequest* FileSystem::AsyncWriteFile(int fileHandle, Buffer& outputBuffer, size_t bufferSize, void (*func)()) {
		File::AsyncWriteRequest* request = new File::AsyncWriteRequest(fileHandle, outputBuffer, bufferSize, func);
		FileQueue::Enqueue(request);
		return request;
	}

	File::AsyncCloseRequest* FileSystem::AsyncCloseFile(int fileHandle, void (*func)()) {
		File::AsyncCloseRequest* request = new File::AsyncCloseRequest(fileHandle, func);
		FileQueue::Enqueue(request);
		return request;
	}

	// Function to be called by IO thread
	void FileSystem::ProcessRequests() {
		while (processing) {
			while (File::AsyncRequest* request = FileQueue::Dequeue()) {
				request->ProcessRequest();
				request->Callback();
			}
		}
	}

	void FileSystem::Terminate() {
		processing = false;
	}

	void Wait(File::AsyncRequest*) {

	}
}