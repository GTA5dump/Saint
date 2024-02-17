#pragma once
#include "Natives.hpp"
#include "ScriptCallback.hpp"
namespace Saint {
	class Excludes {
	public:
		bool friends = false;
		bool self = true;
	};
	class jetHandler {
	public:
		jetHandler(Vehicle m_veh, Ped m_ped) {
			veh = m_veh;
			ped = m_ped;

		}
	public:
		Vehicle veh;
		Ped ped;
	};
	class m_Jets {
	public:
		Vehicle angryPlanesPlane;
		Ped angryPlanesPed;
		Excludes excludes;
		std::vector<jetHandler> spawned = {

		};
		void add_jet(std::uint32_t buffer) {
			Entity playerEntity = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(buffer);
			NativeVector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerEntity, true);
			const char* modelName = "TITAN";
			float spawnX = MISC::GET_RANDOM_FLOAT_IN_RANGE(playerCoords.x - 10.0f, playerCoords.x + 10.0f);
			float spawnY = MISC::GET_RANDOM_FLOAT_IN_RANGE(playerCoords.y - 10.0f, playerCoords.y + 10.0f);
			float spawnZ = MISC::GET_RANDOM_FLOAT_IN_RANGE(300.0f, 500.0f);
			float spawnHeading = 360.0f;
			modelName = "lazer";


			Hash modelHash = MISC::GET_HASH_KEY(modelName);
			Hash pedModelHash = MISC::GET_HASH_KEY("A_F_Y_Golfer_01");
			g_CallbackScript->AddCallback<ModelCallback>(modelHash, [=] {
				*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
			angryPlanesPlane = VEHICLE::CREATE_VEHICLE(modelHash, spawnX + MISC::GET_RANDOM_INT_IN_RANGE(50, 550), spawnY + MISC::GET_RANDOM_INT_IN_RANGE(50, 550), spawnZ, spawnHeading, true, false, false);
			*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
			DECORATOR::DECOR_SET_INT(angryPlanesPlane, "MPBitset", 0);
			auto networkId = NETWORK::VEH_TO_NET(angryPlanesPlane);
			if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(angryPlanesPlane))
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
			VEHICLE::SET_VEHICLE_IS_STOLEN(angryPlanesPlane, FALSE);
			VEHICLE::SET_VEHICLE_ENGINE_ON(angryPlanesPlane, true, true, true);
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(angryPlanesPlane, MISC::GET_RANDOM_INT_IN_RANGE(50, 350));
			ENTITY::SET_ENTITY_INVINCIBLE(angryPlanesPlane, 1);
			ENTITY::SET_ENTITY_PROOFS(angryPlanesPlane, true, true, true, true, true, true, true, true);
			VEHICLE::SET_VEHICLE_DAMAGE(angryPlanesPlane, 0.f, 0.f, 0.f, 0.f, 200.f, false);
				});

			g_CallbackScript->AddCallback<ModelCallback>(pedModelHash, [=]
				{
					angryPlanesPed = PED::CREATE_PED(26, pedModelHash, spawnX, spawnY, spawnZ + 100.0f, spawnHeading, true, true);
					PED::SET_PED_INTO_VEHICLE(angryPlanesPed, angryPlanesPlane, -1);
					PED::SET_DRIVER_ABILITY(angryPlanesPed, 0.99f);
					ENTITY::SET_ENTITY_INVINCIBLE(angryPlanesPed, 1);
					TASK::TASK_COMBAT_PED(angryPlanesPed, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(buffer), 0, 16);
				});
			spawned.push_back({ angryPlanesPlane, angryPlanesPed });
		}
		void spawn() {

			for (std::uint32_t i = 0; i < PLAYER::GET_NUMBER_OF_PLAYERS(); ++i) {
				if (excludes.friends) {
					int netHandle[13];
					NETWORK::NETWORK_HANDLE_FROM_PLAYER(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), netHandle, 13);
					if (!NETWORK::NETWORK_IS_FRIEND(&netHandle[0])) {
						add_jet(i);
					}
				}
				if (excludes.self) {
					if (i != PLAYER::PLAYER_ID()) {
						add_jet(i);
					}
				}
				if (!excludes.self && !excludes.friends) {
					add_jet(i);
				}



			}
		}
	};
	
}
