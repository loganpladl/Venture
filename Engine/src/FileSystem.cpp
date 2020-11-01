#include "../include/FileSystem.h"

namespace Venture {
	// Initialize static loop flag to true
	std::atomic<bool> FileSystem::s_processing = true;
	std::mutex FileSystem::s_queueMutex;
	CircularQueue<File::AsyncRequest*> FileSystem::s_queue;

	// Array of open files

	File::AsyncOpenRequest* FileSystem::AsyncOpenFile(std::string path, std::string mode, void (*func)()) {
		File::AsyncOpenRequest* request = new File::AsyncOpenRequest(path, mode, func);
		Enqueue(request);
		return request;
	}

	File::AsyncReadRequest* FileSystem::AsyncReadFile(int fileHandle, Buffer inputBuffer, size_t bufferSize, void (*func)()) {
		File::AsyncReadRequest* request = new File::AsyncReadRequest(fileHandle, inputBuffer, bufferSize, func);
		Enqueue(request);
		return request;
	}

	File::AsyncReadFullRequest* FileSystem::AsyncReadFullFile(int fileHandle, Buffer inputBuffer, void (*func)()) {
		File::AsyncReadFullRequest* request = new File::AsyncReadFullRequest(fileHandle, inputBuffer, func);
		Enqueue(request);
		return request;
	}

	File::AsyncWriteRequest* FileSystem::AsyncWriteFile(int fileHandle, Buffer outputBuffer, size_t bufferSize, void (*func)()) {
		File::AsyncWriteRequest* request = new File::AsyncWriteRequest(fileHandle, outputBuffer, bufferSize, func);
		Enqueue(request);
		return request;
	}

	File::AsyncCloseRequest* FileSystem::AsyncCloseFile(int fileHandle, void (*func)()) {
		File::AsyncCloseRequest* request = new File::AsyncCloseRequest(fileHandle, func);
		Enqueue(request);
		return request;
	}

	// Function to be called by IO thread
	void FileSystem::ProcessRequests() {
		while (s_processing) {
			while (File::AsyncRequest* request = Dequeue()) {
				request->ProcessRequest();
				request->Callback();
				request->Signal();
			}
		}
	}

	void FileSystem::Terminate() {
		s_processing = false;
	}

	void Wait(File::AsyncRequest*) {

	}

	void FileSystem::Enqueue(File::AsyncRequest* request) {
		s_queueMutex.lock();
		// Delete the request that we are about to replace in the queue if one exists
		File::AsyncRequest* old = s_queue.PeekTail();
		if (old != nullptr) {
			delete old;
		}
		s_queue.Enqueue(request);
		s_queueMutex.unlock();
	}

	File::AsyncRequest* FileSystem::Dequeue() {
		s_queueMutex.lock();
		File::AsyncRequest*  request = s_queue.Dequeue();
		s_queueMutex.unlock();
		return request;
	}
}