#pragma once
#include "Features.h"
namespace Saint {
	class hotkeyHandler {
	public:
		hotkeyHandler(std::string m_name, int m_key, bool* m_toggle, std::string m_key_name, std::function<void()> m_action) {
			name = m_name;
			key = m_key;
			toggle = m_toggle;
			key_name = m_key_name;
			action = m_action;
		}
	public:
		std::string name;
		int key;
		bool* toggle;
		std::string key_name;
		std::function<void()> action;
	};
	class hotkeyButtonHandler {
	public:
		hotkeyButtonHandler(std::string m_name, int m_key, std::string m_key_name, std::function<void()> m_action) {
			name = m_name;
			key = m_key;
			key_name = m_key_name;
			action = m_action;
		}
	public:
		std::string name;
		int key;
		std::string key_name;
		std::function<void()> action;
	};
	inline std::vector<hotkeyHandler> m_Hotkeys = {

	};
	inline std::vector<hotkeyButtonHandler> m_ButtonHotkeys = {

	};
	inline void hotkey_tick() {
		int status = MISC::UPDATE_ONSCREEN_KEYBOARD();
		if (!HUD::IS_MP_TEXT_CHAT_TYPING() || status != 0) {
			for (auto& hotkey : m_Hotkeys) {
				if (Game->KeyPress(hotkey.key, true)) {
					*hotkey.toggle = !*hotkey.toggle;
					Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY"  '%s' hotkey was used.", hotkey.name });
					std::invoke(std::move(hotkey.action));

				}
			}
			for (auto& hotkey : m_ButtonHotkeys) {
				if (Game->KeyPress(hotkey.key, true)) {
					Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY"  '%s' hotkey was used.", hotkey.name });
					std::invoke(std::move(hotkey.action));

				}
			}
		}
	}
}
