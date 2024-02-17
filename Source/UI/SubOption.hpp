#pragma once
#include "OptionGetters.hpp"
#include "Framework.hpp"
#include "../FiberHelper.hpp"
namespace Saint::UserInterface
{
	class submenu : public OptionGetters<submenu>
	{
	public:
		explicit submenu() = default;
		explicit submenu(const char* text, const char* description, std::uint32_t subId, std::function<void()> action = [] {}) :
			m_SubId(subId)
		{
			SetLeftText(text);
			if (description)
				SetDescription(description);
			SetAction(std::move(action));
		}
		explicit submenu(const char* text, std::uint32_t subId, std::function<void()> action = [] {}) :
			m_SubId(subId)
		{
			SetLeftText(text);
			SetAction(std::move(action));
		}
		explicit submenu(const char* text, const char* description, const char* subId, std::function<void()> action = [] {}) :
			m_SubId(rage::joaat(subId))
		{
			SetLeftText(text);
			if (description)
				SetDescription(description);
			SetAction(std::move(action));
		}
		explicit submenu(const char* text, const char* subId, std::function<void()> action = [] {}) :
			m_SubId(rage::joaat(subId))
		{
			SetLeftText(text);
			SetAction(std::move(action));
		}

		~submenu() noexcept = default;
		submenu(submenu const&) = default;
		submenu& operator=(submenu const&) = default;
		submenu(submenu&&) = default;
		submenu& operator=(submenu&&) = default;

		void HandleAction(OptionAction action) override
		{
			if (action == OptionAction::Enter)
			{
				if (m_SubId != rage::joaat("NULL")) {
					g_Render->SwitchToSubmenu(m_SubId);
				}
				
			}

			OptionGetters::HandleAction(action);
		}
		bool GetFlag(const char* flag, const char* secondary) override
		{
			if (flag == "submenu" && secondary == "none") {
				return true;
			}
			return OptionGetters::GetFlag(flag, secondary);
		}
	private:
		std::uint32_t m_SubId{};
	};
}
