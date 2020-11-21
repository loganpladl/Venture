#include "../include/File.h"
#include "../include/Log.h"

namespace Venture {
	namespace File {
		// Define externs
		const int MAX_FILES = 4096;
		FILE* openFiles[MAX_FILES];
		bool fileHandlesInUse[MAX_FILES];

		FILE* getFile(int handle) {
			return openFiles[handle];
		}

		int newFileHandle() {
			for (int i = 0; i < MAX_FILES; i++) {
				if (fileHandlesInUse[i] == false) {
					// Found unused handle
					fileHandlesInUse[i] = true;
					return i;
				}
			}
			// Couldn't find unused handle
			return -1;
		}

		void deleteFile(int handle) {
			// delete file w/ fclose
			fclose(openFiles[handle]);
			fileHandlesInUse[handle] = false;
		}
		void deleteFile(FILE* fp) {
			fclose(fp);
		}


		int AsyncOpenRequest::ProcessRequest() {
			return File::OpenFile(&openFiles[m_fileHandle], m_path, m_mode);
		}

		int AsyncReadRequest::ProcessRequest() {
			size_t bytesRead = fread(m_inputBuffer.GetBuffer(), 1, m_bufferSize, openFiles[m_fileHandle]);

			if (bytesRead != m_bufferSize) {
				// Read error
				Log::DebugPrintF(0, Log::Channel::Files, "Reading error.\n");
				return -1;
			}

			return 0;
		}

		int AsyncWriteRequest::ProcessRequest() {
			char* buf = m_outputBuffer.GetBuffer();
			size_t charsWritten = fwrite(buf, sizeof(char), m_bufferSize, openFiles[m_fileHandle]);
			return 0;
		}

		int AsyncCloseRequest::ProcessRequest() {
			deleteFile(m_fileHandle);
			return 0;
		}

		int AsyncReadFullRequest::ProcessRequest() {
			return ReadFullFile(openFiles[m_fileHandle], m_inputBuffer, m_bufferSize);
		}

		int AsyncOpenReadCloseRequest::ProcessRequest() {
			int error = 0;
			FILE* file = nullptr;
			error = File::OpenFile(&file, m_path, m_mode);
			error = File::ReadFullFile(file, m_inputBuffer, m_bufferSize);
			File::deleteFile(file);
			return error;
		}

		int OpenFile(FILE** file, std::string &path, std::string &mode) {
			errno_t err = fopen_s(file, path.c_str(), mode.c_str());
			// File failed to open
			if (err != 0) {
				Log::DebugPrintF(0, Log::Channel::Files, "Cannot open file %s\n", path);
				return -1;
			}
			return 0;
		}


		// Helper function to read entire file
		int ReadFullFile(FILE* fp, Buffer &inputBuffer, size_t &bufferSize) {
			// Find file size
			fseek(fp, 0, SEEK_END);
			long fileSize = ftell(fp);
			rewind(fp);

			inputBuffer.Create(fileSize);

			if (inputBuffer.GetBuffer() == NULL) {
				Log::DebugPrintF(0, Log::Channel::Files, "Memory error when allocating buffer to read full file.\n");
				return -1;
			}

			bufferSize = fileSize;

			size_t bytesRead = fread(inputBuffer.GetBuffer(), 1, bufferSize, fp);

			if (bytesRead != bufferSize) {
				// Read error
				Log::DebugPrintF(0, Log::Channel::Files, "Reading error.\n");
				return -1;
			}

			return 0;
		}
	}
}