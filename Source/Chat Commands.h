#pragma once

namespace Saint {
	class Commands {
	public:
		bool m_spawn = true;
	};
	class ChatCommands {
	public:
		Commands m_commands;
		bool m_enabled = true;
		
	};
	inline ChatCommands m_chat_commands;
}