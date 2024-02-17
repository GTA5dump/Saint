#pragma once
#include "Signatures.hpp"


namespace Saint
{
	inline std::pair<uint64_t, uint32_t> g_game_address;
	inline std::string capitalize(const std::string& word) {
		if (word.empty()) {
			return word;
		}
		std::string capitalized = word;
		capitalized[0] = std::toupper(capitalized[0]);
		return capitalized;
	}

	inline std::string correctGrammar(const std::string& text) {
		std::istringstream iss(text);
		std::ostringstream oss;
		std::string word;

		std::vector<std::string> specialCases = { "dont", "cant", "wont" };

		bool capitalizeNextWord = true;

		while (iss >> word) {
			if (capitalizeNextWord) {
				word = capitalize(word);
			}
			else {
				std::transform(word.begin(), word.end(), word.begin(), ::tolower);
				if (std::find(specialCases.begin(), specialCases.end(), word) != specialCases.end()) {
					word = capitalize(word);
				}
			}

			oss << word << " ";

			if (word.find_first_of(".!?") != std::string::npos) {
				capitalizeNextWord = true;
			}
			else {
				capitalizeNextWord = false;
			}
		}

		return oss.str();
	}
	class SimpleTimer
	{
	public:
		void Initialize(std::uint64_t ticks)
		{
			if (this->m_Tick)
			{
				this->m_WakeTime = GetTickCount64() + ticks;
				this->m_Tick = false;
			}
		}

		bool IsReady()
		{
			return GetTickCount64() > this->m_WakeTime;
		}

		void Destroy()
		{
			this->m_Tick = true;
		}
	private:
		std::uint64_t m_WakeTime;
		bool m_Tick;
	};

	template<typename T>
	inline bool is_valid_ptr(T ptr) {
	
		uint64_t address = (uint64_t)ptr;
		if (address < 0x5000) return false;
		if ((address & 0xFFFFFFFF) == 0xFFFFFFFF) return false;
		if ((address & 0xFFFFFFFF) <= 0xFF) return false;

		if (*(uint8_t*)((uint64_t)&address + 6) != 0 || *(uint8_t*)((uint64_t)&address + 7) != 0) return false;

		return true;
	}

	inline bool has_string(std::string& str, std::string check)
	{
		std::size_t found = str.find_first_of(' ');
		if (found != std::string::npos)
		{
			if (str.substr(0, found) == check)
			{
				str = str.substr(found + 1, str.size());
				return true;
			}
		}
		else
		{
			if (str == check)
				return true;
		}
		return false;
	}
	/**
	 * \brief Checks if a key is pressed
	 * \param key A virtual key code
	 * \return bool
	 */
	inline void IsKeyHeld(bool& value, std::uint16_t key, std::size_t delay)
	{
		static SimpleTimer timer;
		if (GetForegroundWindow() == g_GameVariables->m_GameWindow)
		{
			if (GetAsyncKeyState(key) & 1)
				value = true;
			else if (GetAsyncKeyState(key) & 0x8000)
			{
				timer.Initialize(delay * 100);
				if (timer.IsReady())
					value = true;
			}
			else
				timer.Destroy();
		}
	}
	inline bool IsKeyPressed(std::uint16_t key)
	{
		if (GetForegroundWindow() == g_GameVariables->m_GameWindow)
		{
			if (GetAsyncKeyState(key) & 0x8000)
			{
				return true;
			}
		}

		return false;
	}

	/**
	 * \brief A stream buffer that uses a char[] buffer
	 */
	class MemoryStreamBuf : public std::streambuf
	{
	public:
		MemoryStreamBuf(char* array, std::size_t size)
		{
			std::fill_n(array, size, '\0');
			std::streambuf::setp(array, array + size - 1);
		}

		template <std::size_t size>
		MemoryStreamBuf(char(&array)[size]) :
			MemoryStreamBuf(&array[0], size)
		{
		}
	};

	/**
	 * \brief An input/output stream that uses a char[] buffer
	 */
	class MemoryStringStream : virtual MemoryStreamBuf, public std::iostream
	{
	public:
		MemoryStringStream(char* array, std::size_t size) :
			MemoryStreamBuf(array, size),
			std::iostream(static_cast<MemoryStreamBuf*>(this))
		{
		}

		template <std::size_t size>
		MemoryStringStream(char(&array)[size]) :
			MemoryStreamBuf(array),
			std::iostream(static_cast<MemoryStreamBuf*>(this))
		{
		}
	};

	/**
	 * \brief A MemoryStringStream with a built in buffer
	 */
	template <std::size_t N>
	class MemoryStringStreamWithBuffer : public MemoryStringStream
	{
	public:
		MemoryStringStreamWithBuffer():
			MemoryStringStream(m_Buffer)
		{}
	private:
		char m_Buffer[N];
	};

	inline constexpr char ToLower(const char c)
	{
		return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
	}

	/**
	 * \brief Calculates JOAAT hash of string at compile time
	 */
	template <std::size_t CharCount>
	struct ConstexprJooat
	{
		char data[CharCount];

		template <std::size_t... Indices>
		constexpr ConstexprJooat(const char* str, std::index_sequence<Indices...>) :
			data{ (str[Indices])... }
		{
		}

		constexpr std::uint32_t GetHash()
		{
			std::uint32_t hash = 0;

			for (std::size_t i = 0; i < CharCount; ++i)
			{
				hash += ToLower(data[i]);
				hash += (hash << 10);
				hash ^= (hash >> 6);
			}

			hash += (hash << 3);
			hash ^= (hash >> 11);
			hash += (hash << 15);

			return hash;
		}
	};

	/**
	 * \brief Hashes a string with the Jenkins-one-at-a-time hash function
	 * \param str The string to be hashed
	 * \return Hash of str
	 */
	inline constexpr std::uint32_t Joaat(const char* str)
	{
		std::uint32_t hash = 0;
		while (*str)
		{
			hash += ToLower(*str++);
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}

		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);

		return hash;
	}

#	define CONSTEXPR_JOAAT_IMPL(x) (::Saint::ConstexprJooat<sizeof(x) - 1>((x), std::make_index_sequence<sizeof(x) - 1>()).GetHash())
#	define CONSTEXPR_JOAAT(x) (std::integral_constant<std::uint32_t, CONSTEXPR_JOAAT_IMPL(x)>::value)
}
