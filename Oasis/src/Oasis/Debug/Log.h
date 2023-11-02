#pragma once

#include <string>

namespace Oasis {

	typedef void* HANDLE;

	class Log
	{
	private:
		static HANDLE s_ConsoleHandle;
	public:
		static void Init();
		static void Shutdown();

		static void Info(const std::string& fmt, ...);
		static void Warn(const std::string& fmt, ...);
		static void Error(const std::string& fmt, ...);
	};

#define OASIS_LOG_INFO(fmt, ...) Log::Info(fmt, __VA_ARGS__)
#define OASIS_LOG_WARN(fmt, ...) Log::Warn(fmt, __VA_ARGS__)
#define OASIS_LOG_ERROR(fmt, ...) Log::Error(fmt, __VA_ARGS__)

}
