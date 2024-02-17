#pragma once
#include "UI/optionGetters.hpp"
#include "UI/Framework.hpp"
#include "FiberHelper.hpp"
namespace Saint::UserInterface
{
	class color_submenu : public OptionGetters<color_submenu>
	{
	public:
		explicit color_submenu() = default;
		explicit color_submenu(const char* text, const char* description, Color color, std::uint32_t subId, std::function<void()> action = [] {}) :
			m_SubId(subId)
		{
			SetLeftText(text);
			if (description)
				SetDescription(description);
			SetAction(std::move(action));
			SetColor(color);
		}

		~color_submenu() noexcept = default;
		color_submenu(color_submenu const&) = default;
		color_submenu& operator=(color_submenu const&) = default;
		color_submenu(color_submenu&&) = default;
		color_submenu& operator=(color_submenu&&) = default;

		void HandleAction(OptionAction action) override
		{
			if (action == OptionAction::Enter)
			{
				if (m_SubId != rage::joaat("NULL")) {
					g_Render->SwitchToSubmenu(m_SubId);
				}
			}

			Base::HandleAction(action);
		}

		

		bool GetFlag(const char* flag, const char* secondary) override
		{
			if (flag == "submenu" && secondary == "color") {
				return true;
			}
			return Base::GetFlag(flag, secondary);
		}
	private:
		using Base = OptionGetters<color_submenu>;
		std::uint32_t m_SubId{};
	};
}
