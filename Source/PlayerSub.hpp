#pragma once
#include "Ui/optionGetters.hpp"
#include "UI/Framework.hpp"
#include "FiberHelper.hpp"
namespace Saint::UserInterface
{
	class playersubmenu : public OptionGetters<playersubmenu>
	{
	public:
		explicit playersubmenu() = default;
		explicit playersubmenu(const char* text, const char* description, std::uint32_t subId, int headshot_id, std::function<void()> action = [] {}, int blipid = -1) :
			m_SubId(subId)
		{
			SetLeftText(text);
			if (description)
				SetDescription(description);
			SetAction(std::move(action));
			SetHeadshotId(headshot_id);
		}

		~playersubmenu() noexcept = default;
		playersubmenu(playersubmenu const&) = default;
		playersubmenu& operator=(playersubmenu const&) = default;
		playersubmenu(playersubmenu&&) = default;
		playersubmenu& operator=(playersubmenu&&) = default;

		void HandleAction(OptionAction action) override
		{
			if (action == OptionAction::Enter)
			{
				g_Render->SwitchToSubmenu(m_SubId);
			}

			OptionGetters::HandleAction(action);
		}

		bool GetFlag(const char* flag, const char* secondary) override
		{
			if (flag == "submenu" && secondary == "player") {
				return true;
			}
			return OptionGetters::GetFlag(flag, secondary);
		}
	private:
		std::uint32_t m_SubId{};
	};
}
