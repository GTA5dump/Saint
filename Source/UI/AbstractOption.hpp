#pragma once

namespace Saint::UserInterface
{
	enum class OptionAction
	{
		LeftPress,
		RightPress,
		EnterPress,
		HotkeyPress,
	};

	enum class OptionFlag
	{
		Horizontal = (1 << 0),
		Enterable = (1 << 1),
		BoolOption = (1 << 2),
		UnclickOption = (1 << 3),
		BoolWithNumber = (1 << 4),
		ChooseBool = (1 << 5),
		Choose = (1 << 6),
		Keyboard = (1 << 7),
		PlayerSub = (1 << 8),
		ColorSub = (1 << 9),
	};

	class AbstractOption
	{
	public:
		virtual ~AbstractOption() noexcept = default;
	
		virtual const char* GetLeftText() = 0;
		virtual const char* GetRightText() = 0;
		virtual const char* GetCenteredText() = 0;
		virtual const char* GetDescription() = 0;
		virtual Color GetColor() = 0;
		virtual void HandleAction(OptionAction action) = 0;
		virtual bool GetFlag(OptionFlag flag) = 0;
	protected:
		explicit AbstractOption() = default;
		AbstractOption(AbstractOption const&) = default;
		AbstractOption& operator=(AbstractOption const&) = default;
		AbstractOption(AbstractOption&&) = default;
		AbstractOption& operator=(AbstractOption&&) = default;
	};
}
