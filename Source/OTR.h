#pragma once
#include "Natives.hpp" 
#include "ScriptGlobal.hpp"
#include "Signatures.hpp"
namespace Saint {
	class OTR {
	public:
		bool enabled = false;
		void init() {
			if (enabled) {
				script_global gpbd_fm_3(1895156);
				constexpr size_t arg_count = 7;
				int64_t args[arg_count] = {
					static_cast<int64_t>(1141648445),
					(int64_t)PLAYER::PLAYER_ID(),
					(int64_t)(NETWORK::GET_NETWORK_TIME() + 1),
					0,
					true,
					false,
					*gpbd_fm_3.at(g_SelectedPlayer, 608).at(510).as<int64_t*>()
				};

				g_GameFunctions->m_trigger_script_event(1, args, arg_count, 1 << g_SelectedPlayer);
			}
		}
	};
}