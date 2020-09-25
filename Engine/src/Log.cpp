#include "../include/Log.h"

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
			"Log"
		};

		const int NUM_CHANNELS = 8;
		const char* LOG_PATH = "log\\";

		FILE* logFiles[NUM_CHANNELS];

		void EnableChannel(Channel channel) {
			g_activeChannels |= 1 << channel;
		}
		void DisableChannel(Channel channel) {
			g_activeChannels &= ~(1 << channel);
		}

		const char* getLogFilePath(char* target, const char* name) {
			strcpy_s(target, 100, LOG_PATH);
			strcat_s(target, 100, name);
			return target;
		}

		int openLogFiles() {
			if (_mkdir("log") == 0) {
				DebugPrintF(0, Channel::Log, "Directory created\n");
			}
			for (int i = 0; i < NUM_CHANNELS; i++) {
				char path[100];
				getLogFilePath(path, CHANNEL_NAMES[i]);
				errno_t err = fopen_s(&logFiles[i], path, "w+");
				// File failed to open
				if (err != 0) {
					DebugPrintF(0, Channel::Log, "Cannot open file %s\n", path);
					return -1;
				}
			}
			return 0;
		}

		int closeLogFiles() {
			for (int i = 0; i < NUM_CHANNELS; i++) {
				if (logFiles[i] != nullptr) {
					fclose(logFiles[i]);
				}
			}
			return 0;
		}

		int DebugPrintF(int verbosity, Channel channel, const char* format, ...) {
			const int MAX_CHARS = 1024;
			static char buffer[MAX_CHARS];

			va_list argList;

			va_start(argList, format);
			int charsWritten = vsnprintf(buffer, MAX_CHARS, format, argList);
			va_end(argList);

			// Print to file depending on channel
			if (logFiles[channel] != nullptr) {
				fputs(buffer, logFiles[channel]);
			}

			// Only print to console when global verbosity level is high enough and channel is active
			if (g_verbosity >= verbosity && isChannelActive(channel)) {
				OutputDebugStringA(buffer);
			}
			return 0;
		}
	}
}