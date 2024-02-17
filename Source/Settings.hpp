#pragma once

namespace Saint
{
	class Settings
	{
	public:
		std::atomic_bool m_LogWindow = false;
		std::atomic_bool m_LockMouse = false;
		std::atomic_bool command_window = false;
	};

	inline Settings g_Settings;
}
