#include "../include/File.h"
#include "../include/Log.h"

namespace Venture {
	namespace File {
		// Define externs
		const int MAX_FILES = 1024;
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
			fileHandlesInUse[handle] = false;
		}


		int AsyncOpenRequest::ProcessRequest() {
			errno_t err = fopen_s(&openFiles[m_fileHandle], m_path.c_str(), m_mode.c_str());
			// File failed to open
			if (err != 0) {
				Log::DebugPrintF(0, Log::Channel::Files, "Cannot open file %s\n", m_path);
				return -1;
			}
			return 0;
		}

		int AsyncReadRequest::ProcessRequest() {
			return 0;
		}

		int AsyncWriteRequest::ProcessRequest() {
			return 0;
		}

		int AsyncCloseRequest::ProcessRequest() {
			deleteFile(m_fileHandle);
			return 0;
		}
	}
}