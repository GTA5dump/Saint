#pragma once

namespace Saint
{
	enum LogFlag {
		Info,
		Success,
		Error,
		Warning,
		stackwalker,
	};
	class Logger
	{
	public:
		explicit Logger();
		~Logger() noexcept;

		Logger(Logger const&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(Logger const&) = delete;
		Logger& operator=(Logger&&) = delete;

		/**
		 * \brief Logs an info message
		 * \param format The format of the logged text
		 * \param ... The arguments to format the string
		 */
		void Info(const char* format, ...);
		void Theme(const char* format, ...);
		void Debug(const char* format, ...);
		void Success(const char* format, ...);

		void Push(const char* title, LogFlag flag, const char* format, ...);


		/**
		 * \brief Logs an error message
		 * \param format The format of the logged text
		 * \param ... The arguments to format the string
		 */
		void Error(const char* format, ...);

		/**
		 * \brief Logs a message
		 * \param type The type of the logged text, visual only
		 * \param format The format of the logged text
		 * \param args The arguments to format the string
		 */
		void Log(const char* type, const char* format, std::va_list args);

		std::mutex& GetMutex();
		std::pair<std::unique_ptr<char[]>*, std::size_t> GetMessages();
		std::istream& GetInput();
	private:
		std::mutex m_Mutex;
		std::vector<std::unique_ptr<char[]>> m_Messages;

		fs::path m_FilePath;
		std::ofstream m_File;
		std::ofstream m_Console;
		std::ifstream m_Input;
	};

	inline std::unique_ptr<Logger> g_Logger;
	inline Logger loggerGetter;
	inline Logger* getLogger() {
		return &loggerGetter;
	}
}
