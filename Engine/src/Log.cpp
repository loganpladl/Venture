#include "../include/Log.h"
#include "../include/FileSystem.h"
#include "../include/Buffer.h"

namespace Venture {
	namespace Log {
		// All channels active by default (-1 sets all bits to true)
		unsigned int g_activeChannels = -1;

		// Default to max verbosity (0-3)
		int g_verbosity = 3;

		const char* CHANNEL_NAMES[] = {
			"General",
			"Gameplay",
			"Animation",
			"Physics",
			"Resources",
			"Input",
			"Audio",
			"Files",
			"Rendering"
		};

		bool g_initialized = false;

		const int NUM_CHANNELS = 9;
		const char* LOG_PATH = "log\\";

		int logFileHandles[NUM_CHANNELS];

		void EnableChannel(Channel channel) {
			g_activeChannels |= 1 << static_cast<int>(channel);
		}
		void DisableChannel(Channel channel) {
			g_activeChannels &= ~(1 << static_cast<int>(channel));
		}

		const char* getLogFilePath(char* target, const char* name) {
			strcpy_s(target, 100, LOG_PATH);
			strcat_s(target, 100, name);
			return target;
		}

		int openLogFiles() {
			if (_mkdir("log") == 0) {
				DebugPrintF(0, Channel::Files, "Directory created\n");
			}
			for (int i = 0; i < NUM_CHANNELS; i++) {
				char path[100];
				getLogFilePath(path, CHANNEL_NAMES[i]);

				File::AsyncOpenRequest* request = FileSystem::AsyncOpenFile(path, "w+");
				logFileHandles[i] = request->getFileHandle();
			}
			g_initialized = true;
			return 0;
		}

		int closeLogFiles() {
			for (int i = 0; i < NUM_CHANNELS; i++) {
				if (logFileHandles[i] >= 0) {
					File::AsyncCloseRequest* request = FileSystem::AsyncCloseFile(logFileHandles[i]);
				}
			}
			return 0;
		}

		int DebugPrintF(int verbosity, Channel channel, const char* format, ...) {
			const int MAX_CHARS = 1024;
			// Temporary buffer of max size to be used for formatting
			Buffer tempBuffer(MAX_CHARS);

			va_list argList;

			va_start(argList, format);
			int charsWritten = vsnprintf(tempBuffer.GetBuffer(), MAX_CHARS, format, argList);
			va_end(argList);

			// Only print to console when global verbosity level is high enough and channel is active
			// Print temp buffer since its null terminated
			if (g_verbosity >= verbosity && isChannelActive(channel)) {
				OutputDebugStringA(tempBuffer.GetBuffer());
			}

			// Only print to log files if Log has been initialized
			if (!g_initialized) {
				return -1;
			}

			// Not null terminated, could add one for null terminator
			size_t size = (size_t)charsWritten;
			// Truncated buffer of proper size to be written
			Buffer newBuffer(size);
			memcpy(newBuffer.GetBuffer(), tempBuffer.GetBuffer(), size);

			// Print to file depending on channel
			if (logFileHandles[static_cast<int>(channel)] >= 0) {
				File::AsyncWriteRequest* request = FileSystem::AsyncWriteFile(logFileHandles[static_cast<int>(channel)], newBuffer, size);
			}

			return 0;
		}
	}
}