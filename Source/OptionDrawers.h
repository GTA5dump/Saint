#pragma once
#include "UI/SubmenuBase.hpp"
#include "UI/BoolOption.hpp"
#include "UI/ChooseOption.hpp"
#include "UI/NumberOption.hpp"
#include "UI/SubOption.hpp"
#include "UI/PlayerSubmenu.hpp"
#include "UI/RegularOption.hpp"
#include "BoolWithNumber.hpp"
#include "BoolWithChoose.h"
#include "HotkeyOption.hpp"
namespace Saint {
	template <typename ...TArgs>
	void addToggle(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::toggle>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addBreak(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::Break>(std::forward<TArgs>(args)...));
	}
	template <typename NumberType, typename ...TArgs>
	void addToggleWithNumber(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::ToggleWithNumber<NumberType>>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addToggleWithScroll(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::ToggleWithScroller>(std::forward<TArgs>(args)...));
	}
	template <typename NumberType, typename ...TArgs>
	void addNumber(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::number<NumberType>>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addScroll(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::Scroll>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addSubmenu(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::submenu>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addColorSubmenu(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::color_submenu>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addButton(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::Button>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addKeyboard(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::Keyboard>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addPlayerSubmenu(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::playersubmenu>(std::forward<TArgs>(args)...));
	}
	template <typename ...TArgs>
	void addHotkey(TArgs&&... args)
	{
#ifdef logoptions
		std::string soos = std::string(std::get<0>(std::tie(args...)));
		bool found = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == soos) {
				found = true;
				break;
			}
		}
		if (!found) {
			s.push_back(soos);
			soos = soos + "\n";
			std::ofstream o("C:\\Users\\Tim\\sainttranslation.txt", std::ios_base::app);
			o.write(soos.c_str(), soos.size());
			o.close();
		}

#endif
		UserInterface::m_Options.push_back(std::make_unique<UserInterface::Hotkey>(std::forward<TArgs>(args)...));
	}
	
	class GetMenuOptions {
	public:
		void pushButton(const char* name, std::function<void()> action = [] {}) {
			addButton(name, "", action);
		}
	};
	GetMenuOptions* menu;

	
	
}

