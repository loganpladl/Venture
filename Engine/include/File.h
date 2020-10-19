#pragma once
#include <stdio.h>
#include <string>
#include <thread>
#include "Semaphore.h"

namespace Venture {
	namespace File {
		enum class AsyncRequestType {
			Invalid, Read, Write, Open, Close
		};

		extern const int MAX_FILES;
		extern FILE* openFiles[];
		extern bool fileHandlesInUse[];

		FILE* getFile(int handle);

		// Search open files array for first unused handle
		int newFileHandle();

		void deleteFile(int handle);

		class AsyncRequest {
		protected:
			AsyncRequestType m_type;
			void (*m_callback)();
			Semaphore sem{0};
			AsyncRequest(AsyncRequestType type, void (*callback)()) : m_type(type), m_callback(callback) {}
		public:
			virtual ~AsyncRequest() {}
			inline virtual AsyncRequestType GetType() {
				return m_type;
			}
			virtual int ProcessRequest() = 0;
		};

		class AsyncOpenRequest : public AsyncRequest {
		private:
			std::string m_path;
			int m_fileHandle;
			std::string m_mode;
		public:
			// Empty lambda function as default callback
			AsyncOpenRequest(std::string path, std::string mode, void (*callback)() = []() {}) :
				AsyncRequest(AsyncRequestType::Open, callback), m_path(path), m_mode(mode) {
				m_fileHandle = newFileHandle();
			}
			int ProcessRequest() override;
			inline int getFileHandle() {
				return m_fileHandle;
			}
		};

		struct AsyncReadRequest : public AsyncRequest {
			int m_fileHandle;
			char* m_inputBuffer;
			size_t m_bufferSize;

			// Empty lambda as default callback
			AsyncReadRequest(int fileHandle, char* inputBuffer, size_t bufferSize, void (*callback)() = [](){}) :
				AsyncRequest(AsyncRequestType::Read, callback), m_fileHandle(fileHandle), m_inputBuffer(inputBuffer), m_bufferSize(bufferSize) {}
			int ProcessRequest() override;
		};

		struct AsyncWriteRequest : public AsyncRequest {
			int m_fileHandle;
			char* m_outputBuffer;
			size_t m_bufferSize;

			// Empty lambda as default callback
			AsyncWriteRequest(int fileHandle, char* inputBuffer, size_t bufferSize, void (*callback)() = []() {}) :
				AsyncRequest(AsyncRequestType::Read, callback), m_fileHandle(fileHandle), m_outputBuffer(inputBuffer), m_bufferSize(bufferSize) {}
			int ProcessRequest() override;
		};

		struct AsyncCloseRequest : public AsyncRequest {
			int m_fileHandle;

			// Empty lambda function as default callback
			AsyncCloseRequest(int fileHandle, void (*callback)() = []() {}) :
				AsyncRequest(AsyncRequestType::Open, callback), m_fileHandle(fileHandle) {}
			int ProcessRequest() override;
		};
	}
}