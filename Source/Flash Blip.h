#pragma once
#include "Natives.hpp" 
namespace Saint {
	class FlashBlip {
	public:
		bool enabled = false;
		void init() {
			if (enabled) {
				Blip b = HUD::GET_BLIP_FROM_ENTITY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));
				HUD::SET_BLIP_FLASHES(b, true);
			}
		}
	};
}