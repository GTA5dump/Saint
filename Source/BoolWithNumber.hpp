#pragma once
#include "UI/OptionGetters.hpp"
#include "UI/Framework.hpp"

namespace Saint::UserInterface {
    template <typename NumberType>
    class ToggleWithNumber : public OptionGetters<ToggleWithNumber<NumberType>>
    {
    public:
        explicit ToggleWithNumber() = default;
        explicit ToggleWithNumber(const char* text, const char* description, bool* b00l, NumberType* number, NumberType min, NumberType max, NumberType step = 1, std::size_t precision = 3, bool actionOnHorizontal = true, const char* prefix = "", const char* suffix = "", std::function<void()> action = [] {}) :
            m_Text(text),
            m_ActionOnHorizontal(actionOnHorizontal),
            m_Bool(b00l),
            m_Number(number),
            m_Min(min),
            m_Max(max),
            m_Step(step),
            m_Precision(precision)
        {
            Base::SetLeftText(text);
            if (description)
                Base::SetDescription(description);
            if (description == "" || description == nullptr) {
                Base::SetDescription("Hold V and any key to set a hotkey.");
            }
            Base::SetAction(std::move(action));
            Base::HandleAction(*m_Bool ? OptionAction::Enter : OptionAction::Enter);
            std::strncpy(&m_Prefix[0], prefix, sizeof(m_Prefix) - 1);
            std::strncpy(&m_Suffix[0], suffix, sizeof(m_Suffix) - 1);
        }

        ~ToggleWithNumber() noexcept = default;
        ToggleWithNumber(ToggleWithNumber const&) = default;
        ToggleWithNumber& operator=(ToggleWithNumber const&) = default;
        ToggleWithNumber(ToggleWithNumber&&) = default;
        ToggleWithNumber& operator=(ToggleWithNumber&&) = default;

        bool GetFlag(const char* flag, const char* secondary) override
        {
            if (flag == "number" && secondary == "bool") {
                g_Render->ToggledOn = *m_Bool;
                return true;
            }
            return Base::GetFlag(flag, secondary);
        }
        const char* GetRightText() override
        {
            
            if (g_Render->show_max) {
                MemoryStringStream stream(Base::m_RightText);
                stream
                    << std::setprecision(m_Precision)
                    << std::fixed
                    << m_Prefix
                    << static_cast<DisplayType>(*m_Number)
                    << "/"
                    << static_cast<DisplayType>(m_Max)
                    << m_Suffix;
            }
            else {
                MemoryStringStream stream(Base::m_RightText);
                stream
                    << std::setprecision(m_Precision)
                    << std::fixed
                    << m_Prefix
                    << static_cast<DisplayType>(*m_Number)
                    << m_Suffix;
            }
            return Base::GetRightText();
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
                if (*m_Number - m_Step < m_Min)
                    *m_Number = m_Max;
                else
                    *m_Number -= m_Step;

                if (m_ActionOnHorizontal && Base::m_Action)
                    std::invoke(Base::m_Action);
            }
            else if (action == OptionAction::Right)
            {
                if (*m_Number + m_Step > m_Max)
                    *m_Number = m_Min;
                else
                    *m_Number += m_Step;

                if (m_ActionOnHorizontal && Base::m_Action)
                    std::invoke(Base::m_Action);
                Base::HandleAction(action);
            }


        }
    private:
        const char* m_Text;
        char m_Prefix[32] = {};
        char m_Suffix[32] = {};
        bool m_ActionOnHorizontal{};
        bool* m_Bool;
        NumberType* m_Number{};
        NumberType m_Min{};
        NumberType m_Max{};
        NumberType m_Step{};
        std::size_t m_Precision{};


        using Base = OptionGetters<ToggleWithNumber<NumberType>>;
        using DisplayType = std::conditional_t<sizeof(NumberType) == 1, std::uint32_t, NumberType>;
    };
}