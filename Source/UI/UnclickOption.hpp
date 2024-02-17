#pragma once
#include "optionGetters.hpp"
#include "Framework.hpp"

namespace Saint::UserInterface
{
	class Break : public OptionGetters<Break>
	{
	public:
		explicit Break() = default;
		explicit Break(const char* text)
		{
			std::string text2 = std::string(text);
			const char* textfinal = text2.c_str();
			SetCenteredText(textfinal);
		}

		bool GetFlag(const char* flag, const char* secondary) override
		{
			if (flag == "break" && secondary == "none") {
				return true;
			}
			return OptionGetters::GetFlag(flag, secondary);
		}

		~Break() noexcept = default;
		Break(Break const&) = default;
		Break& operator=(Break const&) = default;
		Break(Break&&) = default;
		Break& operator=(Break&&) = default;
	};
}
