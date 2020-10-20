#pragma once

#include <stdio.h>
#include <direct.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>

namespace Venture {
	namespace Log {
		enum Channel {
			General,
			Gameplay,
			Animation,
			Physics,
			Resources,
			Input,
			Audio,
			Files
		};

		// Channel names indexed by enum value
		extern const char* CHANNEL_NAMES[];

		extern const int NUM_CHANNELS;
		extern const char* LOG_PATH;

		extern int logFileHandles[];

		const char* getLogFilePath(const char* name);

		int openLogFiles();

		int closeLogFiles();

		inline const char* channelToString(Channel channel) {
			return CHANNEL_NAMES[channel];
		}

		extern unsigned int g_activeChannels;

		inline bool isChannelActive(Channel channel) {
			return g_activeChannels & (1 << channel);
		}

		extern int g_verbosity;

		inline void setVerbosity(int verbosity) {
			g_verbosity = verbosity;
		}

		void EnableChannel(Channel channel);
		void DisableChannel(Channel channel);

		int DebugPrintF(int verbosity, Channel channel, const char* format, ...);

		static int VDebugPrintF(const char* format, va_list argList);
	}
}