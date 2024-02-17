#pragma once
#include "optionGetters.hpp"
#include "Framework.hpp"
#include "../Features.h"
namespace Saint::UserInterface
{
	std::string sliderKeyboardBuffer;
	template <typename NumberType>
	class number : public OptionGetters<number<NumberType>>
	{
	public:
		explicit number() = default;
		explicit number(const char* text, const char* description, NumberType* number, NumberType min, NumberType max, NumberType step = 1, std::size_t precision = 3, bool actionOnHorizontal = true, const char* prefix = "", const char* suffix = "", std::function<void()> action = [] {}, bool can_be_saved = false):
			m_Text(text),
			m_ActionOnHorizontal(actionOnHorizontal),
			m_Number(number),
			m_Min(min),
			m_Max(max),
			m_Step(step),
			m_Precision(precision)
		{
			OptionGetters::SetLeftText(text);
			if (description == "NO DESCRIPTION") {
				OptionGetters::SetDescription("");
			}
			if (description != "" || description != nullptr && description != "NO DESCRIPTION") {
				OptionGetters::SetDescription(description);
			}
			if (description == "" || description == nullptr) {
				OptionGetters::SetDescription("Hold V and any key to set a hotkey.");
			}
			OptionGetters::SetAction(std::move(action));
			std::strncpy(&m_Prefix[0], prefix, sizeof(m_Prefix) - 1);
			std::strncpy(&m_Suffix[0], suffix, sizeof(m_Suffix) - 1);
		}
		explicit number(const char* text, NumberType* number, NumberType min, NumberType max, NumberType step = 1, std::size_t precision = 3, bool actionOnHorizontal = true, const char* prefix = "", const char* suffix = "", std::function<void()> action = [] {}, bool can_be_saved = false) :
			m_Text(text),
			m_ActionOnHorizontal(actionOnHorizontal),
			m_Number(number),
			m_Min(min),
			m_Max(max),
			m_Step(step),
			m_Precision(precision)
		{
			OptionGetters::SetLeftText(text);
			OptionGetters::SetDescription("");
			OptionGetters::SetAction(std::move(action));
			std::strncpy(&m_Prefix[0], prefix, sizeof(m_Prefix) - 1);
			std::strncpy(&m_Suffix[0], suffix, sizeof(m_Suffix) - 1);
		}

		~number() noexcept = default;
		number(number const&) = default;
		number& operator=(number const&) = default;
		number(number&&) = default;
		number& operator=(number&&) = default;



		bool GetFlag(const char* flag, const char* secondary) override
		{
			if (flag == "number" && secondary == "none") {
				return true;
			}
			return OptionGetters::GetFlag(flag, secondary);
		}
		const char* GetRightText() override
		{
			
			
			MemoryStringStream stream(OptionGetters::m_RightText);
				stream
					<< std::setprecision(m_Precision)
					<< std::fixed
					<< m_Prefix
					<< static_cast<DisplayType>(*m_Number)
					<< m_Suffix;
				return OptionGetters::GetRightText();
		}

		void HandleAction(OptionAction action) override
		{
			for (int key = 0; key < 256; ++key)
			{
				if (action == OptionAction::Hotkey)
				{
					if (Game->KeyPress(key, true))
					{
						int scanCode = MapVirtualKey(key, MAPVK_VK_TO_VSC);
						char keyName[256];
						if (GetKeyNameText(scanCode << 16, keyName, sizeof(keyName)))
						{
							if (key != 0x57 && key != 0x41 && key != 0x53 && key != 0x53 && key != 0x56)
							{
								g_Render->controlsEnabled = false;
								m_ButtonHotkeys.push_back({ m_Text, key, keyName, OptionGetters::m_Action });
								Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY "  %s was binded to '%s'", m_Text, keyName });
								g_Render->controlsEnabled = true;
							}
						}
					}
				}

			}

				
			if (action == OptionAction::Left)
			{
				if (*m_Number - m_Step < m_Min)
					*m_Number = m_Max;
				else
					*m_Number -= m_Step;

				if (m_ActionOnHorizontal && OptionGetters::m_Action)
					std::invoke(OptionGetters::m_Action);
			}
			else if (action == OptionAction::Right)
			{
				if (*m_Number + m_Step > m_Max)
					*m_Number = m_Min;
				else
					*m_Number += m_Step;

				if (m_ActionOnHorizontal && OptionGetters::m_Action)
					std::invoke(OptionGetters::m_Action);
			}
			OptionGetters::HandleAction(action);
		}
	private:
		const char* m_Text{};
		char m_Prefix[32] = {};
		char m_Suffix[32] = {};
		bool m_ActionOnHorizontal{};

		NumberType* m_Number{};
		NumberType m_Min{};
		NumberType m_Max{};
		NumberType m_Step{};
		std::size_t m_Precision{};


		using OptionGetters = OptionGetters<number<NumberType>>;
		using DisplayType = std::conditional_t<sizeof(NumberType) == 1, std::uint32_t, NumberType>;
	};
}
