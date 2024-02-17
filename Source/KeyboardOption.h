#pragma once
#include "UI/BaseOption.hpp"

namespace Saint::UserInterface
{
	class KeyboardOption : public BaseOption<KeyboardOption>
	{
	public:
		explicit KeyboardOption() = default;
		explicit KeyboardOption(const char* text, const char* description = nullptr, std::string right = "", std::function<void()> action = [] {}, bool has_pen = true):
			m_HasPen(has_pen)
		{
			SetLeftText(text);
			if (right == "") {
				SetRightText("None");
			}
			else {
				SetRightText(right.c_str());
			}
			if (description)
				SetDescription(description);
			SetAction(std::move(action));
		}

		bool GetFlag(OptionFlag flag) override
		{
			if (m_HasPen) {
				if (flag == OptionFlag::KeyboardNoPen)
				{
					return true;
				}
			}
			else {
				if (flag == OptionFlag::Keyboard)
				{
					return true;
				}
			}

			return BaseOption::GetFlag(flag);
		}

		~KeyboardOption() noexcept = default;
		KeyboardOption(KeyboardOption const&) = default;
		KeyboardOption& operator=(KeyboardOption const&) = default;
		KeyboardOption(KeyboardOption&&) = default;
		KeyboardOption& operator=(KeyboardOption&&) = default;
	private:
		bool m_HasPen{};
	};
}
