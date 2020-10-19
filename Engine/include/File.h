#pragma once
#include <stdio.h>
#include <string>
#include <thread>
#include "../include/Semaphore.h"

namespace Venture {
	namespace File {
		enum class AsyncRequestType {
			Invalid, Read, Write, Open, Close
		};

		struct AsyncFile {
			FILE* pFile;
		};

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
			virtual void ProcessRequest() = 0;
		};

		class AsyncOpenRequest : public AsyncRequest {
		private:
			std::string m_path;
			AsyncFile* m_filePointer; // file pointer destination
		public:
			// Empty lambda function as default callback
			AsyncOpenRequest(std::string path, void (*callback)() = []() {}) :
				AsyncRequest(AsyncRequestType::Open, callback), m_path(path) {}
			void ProcessRequest();
		};

		struct AsyncReadRequest : public AsyncRequest {
			AsyncFile m_file;
			char* m_inputBuffer;
			size_t m_bufferSize;

			// Empty lambda as default callback
			AsyncReadRequest(AsyncFile file, char* inputBuffer, size_t bufferSize, void (*callback)() = [](){}) :
				AsyncRequest(AsyncRequestType::Read, callback), m_file(file), m_inputBuffer(inputBuffer), m_bufferSize(bufferSize) {}
			void ProcessRequest();
		};

		struct AsyncWriteRequest : public AsyncRequest {
			AsyncFile m_file;
			char* m_outputBuffer;
			size_t m_bufferSize;

			// Empty lambda as default callback
			AsyncWriteRequest(AsyncFile file, char* inputBuffer, size_t bufferSize, void (*callback)() = []() {}) :
				AsyncRequest(AsyncRequestType::Read, callback), m_file(file), m_outputBuffer(inputBuffer), m_bufferSize(bufferSize) {}
			void ProcessRequest();
		};

		struct AsyncCloseRequest : public AsyncRequest {
			AsyncFile m_file;

			// Empty lambda function as default callback
			AsyncCloseRequest(AsyncFile file, void (*callback)() = []() {}) :
				AsyncRequest(AsyncRequestType::Open, callback), m_file(file) {}
			void ProcessRequest();
		};
	}
}