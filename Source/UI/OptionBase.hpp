#pragma once
namespace Saint::UserInterface
{
	
	enum class OptionAction
	{
		Left,
		Right,
		Enter,
		Hotkey,
		RShift,
	};
	
	class OptionBase
	{
	public:
		virtual ~OptionBase() noexcept = default;
	
		virtual const char* GetLeftText() = 0;
		virtual const char* GetRightText() = 0;
		virtual const char* GetCenteredText() = 0;
		virtual const char* GetDescription() = 0;
		virtual Color GetColor() = 0;
		virtual bool* GetBool() = 0;
		virtual int GetHeadshotID() = 0;
		virtual int GetBlipID() = 0;
		virtual void HandleAction(OptionAction action) = 0;
		virtual bool GetFlag(const char* flag, const char* flag2) = 0;
	protected:
		explicit OptionBase() = default;
		OptionBase(OptionBase const&) = default;
		OptionBase& operator=(OptionBase const&) = default;
		OptionBase(OptionBase&&) = default;
		OptionBase& operator=(OptionBase&&) = default;
	};

	inline std::vector<std::unique_ptr<OptionBase>> m_Options;
	inline std::vector<OptionBase> m_Options2;
	inline int selected_sub2;
}
