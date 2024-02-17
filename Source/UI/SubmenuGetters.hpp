#pragma once
#include "SubmenuBase.hpp"
#include "OptionBase.hpp"

namespace Saint::UserInterface
{
	template <typename T>
	class SubmenuGetters : public SubmenuBase
	{
	public:
		const char* GetName() override
		{
			return &m_Name[0];
		}

		std::uint32_t GetId() override
		{
			return m_Id;
		}

		void Execute() override
		{
			if (m_Action)
				std::invoke(m_Action, static_cast<T*>(this));
			if (m_SelectedOption >= m_Options.size())
				m_SelectedOption = 0;
		}

		void Reset() override
		{
			m_Options.clear();
		}

		OptionBase* GetOption(std::size_t i) override
		{
			if (i > m_Options.size())
				return nullptr;
			return m_Options[i].get();
		}

		std::size_t GetNumOptions() override
		{
			return m_Options.size();
		}

		std::size_t GetSelectedOption() override
		{
			return m_SelectedOption;
		}

		Color GetColor() override 
		{
			return m_color;
		}



		void SetSelectedOption(std::size_t n) override
		{
			m_SelectedOption = n;
		}

		T& SetName(const char* name)
		{
			std::strncpy(&m_Name[0], name, sizeof(m_Name) - 1);
			return static_cast<T&>(*this);
		}

		T& SetId(std::uint32_t id)
		{
			m_Id = id;
			selected_sub2 = id;
			return static_cast<T&>(*this);
		}

		T& SetAction(std::function<void(T*)> action)
		{
			m_Action = std::move(action);
			return static_cast<T&>(*this);
		}
	protected:
		explicit SubmenuGetters() = default;
		~SubmenuGetters() noexcept = default;

		SubmenuGetters(SubmenuGetters const&) = default;
		SubmenuGetters& operator=(SubmenuGetters const&) = default;
		SubmenuGetters(SubmenuGetters&&) = default;
		SubmenuGetters& operator=(SubmenuGetters&&) = default;

		char m_Name[64] = {};
		std::uint32_t m_Id{};
		std::function<void(T*)> m_Action;

		
		std::size_t m_SelectedOption{};

		Color m_color{};
	};
}
