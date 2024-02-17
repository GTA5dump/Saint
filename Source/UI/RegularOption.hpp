#pragma once
#include "optionGetters.hpp"

namespace Saint::UserInterface
{
	class Button : public OptionGetters<Button>
	{
	public:
		explicit Button() = default;
		explicit Button(const char* text, const char* description = nullptr, std::function<void()> action = [] {}) :
			m_Text(text)
		{
			SetLeftText(text);

			if (description == "NO DESCRIPTION") {
				OptionGetters::SetDescription("");
			}
			if (description != "" || description != nullptr && description != "NO DESCRIPTION") {
				OptionGetters::SetDescription(description);
			}
			if (description == "" || description == nullptr) {
				OptionGetters::SetDescription("Hold V and any key to set a hotkey.");
			}
			SetAction(std::move(action));
		}

		void HandleAction(OptionAction action) override
		{
			for (int key = 0; key < 119; ++key)
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
								m_ButtonHotkeys.push_back({ m_Text, key, keyName, Base::m_Action });
								Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY "  %s was binded to '%s'", m_Text, keyName });
								g_Render->controlsEnabled = true;
							}
						}
					}
				}

			}

			Base::HandleAction(action);
		}

		~Button() noexcept = default;
		Button(Button const&) = default;
		Button& operator=(Button const&) = default;
		Button(Button&&) = default;
		Button& operator=(Button&&) = default;
	private:
		const char* m_Text;
		using Base = OptionGetters<Button>;
	};
}
