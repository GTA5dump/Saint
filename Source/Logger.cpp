#include "Logger.hpp"

namespace Saint
{
	Logger::Logger()
	{
		

		if (!AttachConsole(GetCurrentProcessId()))
			AllocConsole();
		SetConsoleTitleW(BIGBASE_WIDE(BRANDING));
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		SetLayeredWindowAttributes(GetConsoleWindow(), NULL, 235, LWA_ALPHA);
		SetConsoleCP(CP_UTF8);
		SetConsoleOutputCP(CP_UTF8);

		m_Console.open("CONOUT$");
		m_Input.open("CONIN$");
		m_File.open(m_FilePath, std::ios_base::out | std::ios_base::app);
	}

	Logger::~Logger() noexcept
	{
		FreeConsole();
	}

	

	void Logger::Info(const char* format, ...)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		std::va_list args{};
		va_start(args, format);
		Log("Info", format, args);
		va_end(args);
	}

	void Logger::Theme(const char* format, ...)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
		std::va_list args{};
		va_start(args, format);
		Log("Theme", format, args);
		va_end(args);
	}

	void Logger::Debug(const char* format, ...)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
		std::va_list args{};
		va_start(args, format);
		Log("Debug", format, args);
		va_end(args);
	}

	void Logger::Success(const char* format, ...)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
		std::va_list args{};
		va_start(args, format);
		Log("Success", format, args);
		va_end(args);
	}

	void Logger::Error(const char* format, ...)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::va_list args{};
		va_start(args, format);
		Log("Error", format, args);
		va_end(args);
	}

	void Logger::Push(const char* title, LogFlag flag, const char* format, ...)
	{
		switch (flag) {
		case LogFlag::Warning:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			break;
		case LogFlag::Info:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			break;
		case LogFlag::Error:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			break;
		case LogFlag::Success:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			break;
		}
		std::va_list args{};
		va_start(args, format);
		Log("Info", title, args);
		va_end(args);
	}

	void Logger::Log(const char* type, const char* format, std::va_list args)
	{
		std::lock_guard lock(m_Mutex);

		auto time = std::time(nullptr);
		auto tm = std::localtime(&time);

		char prefix[64] = {};
		std::snprintf(prefix, sizeof(prefix) - 1, " ", type);

		std::size_t messageLength = std::vsnprintf(nullptr, 0, format, args) + 1;
		auto messageBuffer = std::make_unique<char[]>(messageLength);
		
		std::uninitialized_fill_n(messageBuffer.get(), messageLength, '\0');
		std::vsnprintf(messageBuffer.get(), messageLength, format, args);

		m_File << prefix << messageBuffer.get() << std::endl;
		m_Console << prefix << messageBuffer.get() << std::endl;

		m_Messages.push_back(std::move(messageBuffer));
	}

	std::mutex& Logger::GetMutex()
	{
		return m_Mutex;
	}

	std::pair<std::unique_ptr<char[]>*, std::size_t> Logger::GetMessages()
	{
		return std::make_pair(m_Messages.data(), m_Messages.size());
	}

	std::istream& Logger::GetInput()
	{
		return m_Input;
	}
}
