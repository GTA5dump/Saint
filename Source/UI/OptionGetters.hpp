#pragma once
#include "../Common.hpp"
#include "OptionBase.hpp"

namespace Saint::UserInterface
{
	template <typename T>
	class OptionGetters : public OptionBase
	{
	public:
		int GetHeadshotID() override 
		{
			return headshotId;
		}
		int GetBlipID() override
		{
			return blipId;
		}
		const char* GetLeftText() override
		{
			return &m_LeftText[0];
		}

		const char* GetRightText() override
		{
			return &m_RightText[0];
		}

		bool* GetBool() override {
			return m_Bool;
		}

		Color GetColor() override
		{
			return m_Color;
		}

		const char* GetCenteredText() override
		{
			return &m_CenteredText[0];
		}

		const char* GetDescription() override
		{
			return &m_Description[0];
		}

		void HandleAction(OptionAction action) override
		{
			if (action == OptionAction::Enter)
			{
				if (m_Action)
				{
					std::invoke(m_Action);
				}
			}
		}

		bool GetFlag(const char*, const char*) override
		{
			return false;
		}

		T& SetLeftText(const char* text)
		{
			std::strncpy(&m_LeftText[0], text, sizeof(m_LeftText) - 1);
			return static_cast<T&>(*this);
		}

		T& SetColor(Color color)
		{
			m_Color = color;
			return static_cast<T&>(*this);
		}
		T& SetHeadshotId(int id)
		{
			headshotId = id;
			return static_cast<T&>(*this);
		}
		T& SetBlipId(int id)
		{
			headshotId = id;
			return static_cast<T&>(*this);
		}
		T& SetBool(bool* color)
		{
			m_Bool = color;
			return static_cast<T&>(*this);
		}
		T& SetRightText(const char* text)
		{
			std::strncpy(&m_RightText[0], text, sizeof(m_RightText) - 1);
			return static_cast<T&>(*this);
		}

		T& SetCenteredText(const char* text)
		{
			std::strncpy(&m_CenteredText[0], text, sizeof(m_CenteredText) - 1);
			return static_cast<T&>(*this);
		}

		T& SetDescription(const char* text)
		{
			if (text)
				std::strncpy(&m_Description[0], text, sizeof(m_Description) - 1);
			return static_cast<T&>(*this);
		}

		T& SetAction(std::function<void()> action)
		{
			m_Action = std::move(action);
			return static_cast<T&>(*this);
		}

	protected:
		explicit OptionGetters() = default;
		~OptionGetters() noexcept = default;

		OptionGetters(OptionGetters const&) = default;
		OptionGetters& operator=(OptionGetters const&) = default;
		OptionGetters(OptionGetters&&) = default;
		OptionGetters& operator=(OptionGetters&&) = default;

		char m_LeftText[64] = {};
		char m_RightText[64] = {};
		char m_CenteredText[64] = {};
		char m_Description[64] = {};
		std::function<void()> m_Action;
		Color m_Color = {};
		int headshotId = {};
		int blipId = {};
		bool* m_Bool;
	};
}
