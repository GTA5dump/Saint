#pragma once
#include "UI/OptionGetters.hpp"
#include "UI/Framework.hpp"

namespace Saint::UserInterface {
	class ToggleWithScroller : public OptionGetters<ToggleWithScroller>
	{
	public:
		explicit ToggleWithScroller() = default;

		template <std::size_t N>
		explicit ToggleWithScroller(const char* text, const char* description, bool* b00l, const char*(*array)[N], std::size_t* position, bool actionOnHorizontal = false, std::function<void()> action = [] {}) :
			m_Text(text),
			m_Bool(b00l),
			m_Data(&(*array)[0]),
			m_DataSize(N),
			m_Position(position),
			m_ActionOnHorizontal(actionOnHorizontal)
		{
			Base::SetLeftText(text);
			if (description != "" || description != nullptr)
				Base::SetDescription(description);
			if (description == "" || description == nullptr) {
				Base::SetDescription("Hold V and any key to set a hotkey.");
			}
			Base::SetAction(std::move(action));
		}

		template <typename VectorType>
		explicit ToggleWithScroller(const char* text, const char* description, bool* b00l, const VectorType* v, std::size_t* position, bool actionOnHorizontal = true, std::function<void()> action = [] {}) :
			m_Text(text),
			m_Bool(b00l),
			m_Data(v->data()),
			m_DataSize(v->size()),
			m_Position(position),
			m_ActionOnHorizontal(actionOnHorizontal)
		{
			Base::SetLeftText(text);
			if (description != "" || description != nullptr)
				Base::SetDescription(description);
			if (description == "" || description == nullptr) {
				Base::SetDescription("Hold V and any key to set a hotkey.");
			}
			Base::SetAction(std::move(action));
		}

		enum class BoolDisplay
		{
			OnOff,
			YesNo
		};
		template <typename BoolType = bool>
		explicit ToggleWithScroller(const char* text, const char* description, bool* b00l, std::size_t* position, BoolDisplay displayType, bool displayInverted = true, std::function<void()> action = [] {}) :
			m_Text(text),
			m_Bool(b00l),
			m_DisplayInverted(displayInverted),
			m_DisplayType(displayType)
		{
			Base::SetLeftText(text);
			if (description != "" || description != nullptr)
				Base::SetDescription(description);
			if (description == "" || description == nullptr) {
				Base::SetDescription("Hold V and any key to set a hotkey.");
			}
			Base::SetAction(std::move(action));
		}

		const char* GetRightText() override
		{
			MemoryStringStream stream(Base::m_RightText);

			if (m_Data)
			{
				if (g_Render->show_positions) {
					stream << m_Data[*m_Position];
					stream << " ~c~[" << *m_Position + 1 << "/" << m_DataSize << "]";
				}
				else {
					stream << m_Data[*m_Position];
					stream << " ";
				}

			}
			else
			{
				stream << "N/A";
			}

			return OptionGetters::GetRightText();
		}

		bool GetFlag(const char* flag, const char* secondary) override
		{
			if (flag == "choose" && secondary == "bool") {
				g_Render->ToggledOn = *m_Bool;
				return true;
			}
			return Base::GetFlag(flag, secondary);
		}

		void HandleAction(OptionAction action) override
		{
			for (int key = 0; key < 256; ++key)
			{
				if (action == OptionAction::Hotkey)
				{
					if (Game->KeyPress(key, true))
					{
						int scanCode = MapVirtualKey(key, MAPVK_VK_TO_CHAR);
						char keyName[256];
						if (GetKeyNameText(scanCode << 16, keyName, sizeof(keyName)))
						{
							if (key != 0x57 && key != 0x41 && key != 0x53 && key != 0x53 && key != 0x56)
							{
								g_Render->controlsEnabled = false;
								m_Hotkeys.push_back({ m_Text, key, (bool*)m_Bool, keyName, Base::m_Action });
								Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_KEY "  %s was binded to '%s'", m_Text, keyName });
								g_Render->controlsEnabled = true;
							}
						}
					}
				}

			}
			if (action == OptionAction::Enter)
			{
				*m_Bool = !*m_Bool;
			}
			if (action == OptionAction::Left)
			{
				if (m_Data)
				{
					if (*m_Position > 0)
						--(*m_Position);
					else
						*m_Position = static_cast<std::size_t>(m_DataSize - 1);

					if (m_ActionOnHorizontal && Base::m_Action)
						std::invoke(Base::m_Action);
				}
			}
			else if (action == OptionAction::Right)
			{
				if (m_Data)
				{
					if (*m_Position < m_DataSize - 1)
						++(*m_Position);
					else
						*m_Position = 0;

					if (m_ActionOnHorizontal && Base::m_Action)
						std::invoke(Base::m_Action);
				}
			}

			if (m_Data)
				Base::HandleAction(action);
		}

		~ToggleWithScroller() noexcept = default;
		ToggleWithScroller(ToggleWithScroller const&) = default;
		ToggleWithScroller& operator=(ToggleWithScroller const&) = default;
		ToggleWithScroller(ToggleWithScroller&&) = default;
		ToggleWithScroller& operator=(ToggleWithScroller&&) = default;
	private:
		const char* m_Text;
		const const char** m_Data{};
		std::size_t m_DataSize{};
		std::size_t* m_Position{};
		bool m_ActionOnHorizontal{};

		bool* m_Bool;
		BoolDisplay m_DisplayType;
		bool m_DisplayInverted = false;

		using Base = OptionGetters<ToggleWithScroller>;
	};
}