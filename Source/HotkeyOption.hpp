#pragma once
#include "UI/OptionGetters.hpp"
#include "UI/Framework.hpp"
#include "Hotkeys.h"
namespace Saint::UserInterface
{
	class Hotkey : public OptionGetters<Hotkey>
	{
	public:
		explicit Hotkey() = default;
		explicit Hotkey(const char* text, const char* description, int* hotkey, std::string right = "", std::function<void()> action = [] {}) :
			m_Text(text),
			m_HasPen(false),
			m_Hotkey(hotkey)
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
								*m_Hotkey = key;
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
			if (flag == "keyboard" && secondary == "no_pen")
			{
				return true;
			}
			
			return OptionGetters::GetFlag(flag, secondary);
		}

		~Hotkey() noexcept = default;
		Hotkey(Hotkey const&) = default;
		Hotkey& operator=(Hotkey const&) = default;
		Hotkey(Hotkey&&) = default;
		Hotkey& operator=(Hotkey&&) = default;
	private:
		const char* m_Text;
		bool m_HasPen{};
		int* m_Hotkey{};
	};
}
