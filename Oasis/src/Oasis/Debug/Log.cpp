#include <Oasis/Debug/Log.h>

#include <cstdarg>
#include <cstring>
#include <cstdio>
#include <iostream>

#include <Windows.h>

#include <Oasis/Events/EventBus.h>

namespace Oasis {

	HANDLE Log::s_ConsoleHandle;

	void Log::Init()
	{
		s_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void Log::Shutdown()
	{
	}

	void Log::Info(const std::string& fmt, ...)
	{
		static char buffer[256];
		memset(buffer, 0, 256);

		va_list argptr;
		va_start(argptr, &fmt);
		vsprintf(buffer, fmt.c_str(), argptr);
		va_end(argptr);

		std::string stringBuffer = std::string(buffer);

		LogInfoEvent e(stringBuffer);
		EventBus::Send(e);

		std::string finalString = std::string("Info: ") + stringBuffer + std::string("\n");

		SetConsoleTextAttribute(s_ConsoleHandle, 3);

		std::cout << finalString;

		SetConsoleTextAttribute(s_ConsoleHandle, 7);
	}

	void Log::Warn(const std::string& fmt, ...)
	{
		static char buffer[256];
		memset(buffer, 0, 256);

		va_list argptr;
		va_start(argptr, &fmt);
		vsprintf(buffer, fmt.c_str(), argptr);
		va_end(argptr);

		std::string stringBuffer = std::string(buffer);

		LogWarnEvent e(stringBuffer);
		EventBus::Send(e);

		std::string finalString = std::string("Warn: ") + stringBuffer + std::string("\n");

		SetConsoleTextAttribute(s_ConsoleHandle, 6);

		std::cout << finalString;

		SetConsoleTextAttribute(s_ConsoleHandle, 7);
	}

	void Log::Error(const std::string& fmt, ...)
	{
		static char buffer[256];
		memset(buffer, 0, 256);

		va_list argptr;
		va_start(argptr, &fmt);
		vsprintf(buffer, fmt.c_str(), argptr);
		va_end(argptr);

		std::string stringBuffer = std::string(buffer);

		LogErrorEvent e(stringBuffer);
		EventBus::Send(e);

		std::string finalString = std::string("Error: ") + stringBuffer + std::string("\n");

		SetConsoleTextAttribute(s_ConsoleHandle, 4);

		std::cout << finalString;

		SetConsoleTextAttribute(s_ConsoleHandle, 7);
	}

}
