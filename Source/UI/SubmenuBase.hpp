#pragma once
#include "../Common.hpp"
#include "OptionBase.hpp"

namespace Saint::UserInterface
{
	enum ScrollDirection {
		FORWARD,
		BACKWARD,
	};
	class SubmenuBase
	{
	public:
		virtual ~SubmenuBase() noexcept = default;

		virtual const char* GetName() = 0;
		virtual std::uint32_t GetId() = 0;
		virtual void Execute() = 0;
		virtual void Reset() = 0;

		virtual OptionBase* GetOption(std::size_t i) = 0;
		virtual std::size_t GetNumOptions() = 0;

		virtual std::size_t GetSelectedOption() = 0;
		virtual void SetSelectedOption(std::size_t) = 0;

		virtual Color GetColor() = 0;
		void Scroll(ScrollDirection direction) {
			switch (direction) {
			case FORWARD:
				if (GetSelectedOption() < GetNumOptions() - 1)
					SetSelectedOption(GetSelectedOption() + 1);
				else
					SetSelectedOption(0);
				break;
			case BACKWARD:
				if (GetSelectedOption() > 0)
					SetSelectedOption(GetSelectedOption() - 1);
				else
					SetSelectedOption(GetNumOptions() - 1);
				break;
			}
		}
	
	protected:
		explicit SubmenuBase() = default;
		SubmenuBase(SubmenuBase const&) = default;
		SubmenuBase& operator=(SubmenuBase const&) = default;
		SubmenuBase(SubmenuBase&&) = default;
		SubmenuBase& operator=(SubmenuBase&&) = default;
	};
}
