#pragma once
#include "Natives.hpp"
namespace Saint {
	class BypassMaxSpeed {
	public:
		bool enabled = false;
		void init(){
			if (enabled) {
				Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
				ENTITY::SET_ENTITY_MAX_SPEED(playerVehicle, 9999999.f);
			}
		}
		void disable() {
			if (!enabled) {
				Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
				ENTITY::SET_ENTITY_MAX_SPEED(playerVehicle, 150.f);
			}
		}
	};
}
