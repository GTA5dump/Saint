#pragma once
#include "UI/OptionGetters.hpp"

namespace Saint::UserInterface
{
	class Keyboard : public OptionGetters<Keyboard>
	{
	public:
		explicit Keyboard() = default;
		explicit Keyboard(const char* text, const char* description = nullptr, std::string right = "", std::function<void()> action = [] {}, bool has_pen = true) :
			m_Text(text),
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

			OptionGetters::HandleAction(action);
		}
		bool GetFlag(const char* flag, const char* secondary) override
		{
			if (m_HasPen) {
				if (flag == "keyboard" && secondary == "none")
				{
					return true;
				}
			}
			else {
				if (flag == "keyboard" && secondary == "no_pen")
				{
					return true;
				}
			}
			return OptionGetters::GetFlag(flag, secondary);
		}

		~Keyboard() noexcept = default;
		Keyboard(Keyboard const&) = default;
		Keyboard& operator=(Keyboard const&) = default;
		Keyboard(Keyboard&&) = default;
		Keyboard& operator=(Keyboard&&) = default;
	private:
		const char* m_Text{};
		bool m_HasPen{};
	};
}
