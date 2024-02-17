#pragma once

#include "Natives.hpp"
#include "Queue.h"
#include "All Players.h"
#include "FiberHelper.hpp"
namespace Saint {
	class Kicks {
	public:
		inline CNetworkPlayerMgr* GetNetworkPlayerMgr()
		{
			if (auto NetworkPlayerMgr = *g_GameFunctions->m_NetworkPlayerManager)
				return NetworkPlayerMgr;

			return nullptr;
		}
		std::chrono::system_clock::time_point last{};
		void DeleteEntity(Entity ent)
		{
			ENTITY::DETACH_ENTITY(ent, TRUE, TRUE);
			ENTITY::SET_ENTITY_VISIBLE(ent, FALSE, FALSE);
			NETWORK::NETWORK_SET_ENTITY_ONLY_EXISTS_FOR_PARTICIPANTS(ent, TRUE);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ent, 0.f, 0.f, 0.f, FALSE, FALSE, FALSE);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ent, TRUE, TRUE);
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ent);
			ENTITY::DELETE_ENTITY(&ent);
			OBJECT::DELETE_OBJECT(&ent);
		}
		const char* Menu[1]
		{
			"Kiddions"
		};

		std::size_t Menu_Data = 0;
		const char* CrashMenu[3]
		{
			"Basic", "Atomic", "Who Shot Cupid (Stay Away)"
		};

		std::size_t Menu_DataCrash = 0;
		void VehicleModifier2(int type, int index, Vehicle veh)
		{
			if (index == -1)
			{
				VEHICLE::REMOVE_VEHICLE_MOD(veh, type);
			}
			else
			{
				VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
				VEHICLE::SET_VEHICLE_MOD(veh, type, index, false);
			}
		}
		void spawn_for_ped2(Hash hash, Vehicle* buffer) {
			*script_global(4540726).as<bool*>() = true;
			g_CallbackScript->AddCallback<ModelCallback>(hash, [=]
				{



					NativeVector3 c = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS2(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), { 0.f, 0.f, 1.0f });
			*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
			Vehicle vehicle = VEHICLE::CREATE_VEHICLE(hash, c.x, c.y, c.z, ENTITY::GET_ENTITY_HEADING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer)), true, false, false);

			*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574;
			DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);

			auto networkId = NETWORK::VEH_TO_NET(vehicle);
			if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);

			VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
			VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle, true, true, true);
			fbr::cur()->wait(1s);
			VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
			VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_HOOD, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, 7), false);




				});
		}
		void DeleteEntity2(Entity ent)
		{
			ENTITY::DETACH_ENTITY(ent, TRUE, TRUE);
			ENTITY::SET_ENTITY_VISIBLE(ent, FALSE, FALSE);
			NETWORK::NETWORK_SET_ENTITY_ONLY_EXISTS_FOR_PARTICIPANTS(ent, TRUE);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ent, 0.f, 0.f, 0.f, FALSE, FALSE, FALSE);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ent, TRUE, TRUE);
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ent);
			ENTITY::DELETE_ENTITY(&ent);
			OBJECT::DELETE_OBJECT(&ent);
		}
		void send_to_int22(const std::vector<std::uint64_t>& _args) {
			if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
				float max = 1e+38f;
				auto coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), FALSE);
				const size_t arg_count = 15;
				int64_t args[arg_count] =
				{
					(int64_t)eRemoteEvent::InteriorControl,
					(int64_t)PLAYER::PLAYER_ID(),
					(int64_t)(int)_args[0],
					(int64_t)PLAYER::PLAYER_ID(),
					(int64_t)false,
					(int64_t)true, // true means enter sender interior
					(int64_t) * (uint32_t*)&coords.x,
					(int64_t) * (uint32_t*)&coords.y,
					(int64_t) * (uint32_t*)&coords.z,
					0,
					0,
					1,
					(int64_t) * (uint32_t*)&max,
					(int64_t)true,
					-1
				};

				g_GameFunctions->m_trigger_script_event(1, args, arg_count, 1 << PLAYER::PLAYER_ID());
			}
			

		}
		Cam anti_crash_camera;
		void crash() {
			if (Menu_DataCrash == 0) {
				std::int64_t Args1[] = { (std::int64_t)eRemoteEvent::Crash, (std::int64_t)PLAYER::PLAYER_ID() };
				g_GameFunctions->m_trigger_script_event(1, Args1, sizeof(Args1) / sizeof(Args1[0]), 1 << g_SelectedPlayer);

				std::int64_t Args2[] = { (std::int64_t)eRemoteEvent::Crash2, (std::int64_t)PLAYER::PLAYER_ID(), rand() % INT64_MAX };
				g_GameFunctions->m_trigger_script_event(1, Args2, sizeof(Args2) / sizeof(Args2[0]), 1 << g_SelectedPlayer);

				std::int64_t Args3[] = { (std::int64_t)eRemoteEvent::MCTeleport, (std::int64_t)PLAYER::PLAYER_ID(), rand() % INT64_MAX, rand() % INT64_MAX };
				g_GameFunctions->m_trigger_script_event(1, Args3, sizeof(Args3) / sizeof(Args3[0]), 1 << g_SelectedPlayer);
			}
			if (Menu_DataCrash == 1) {
				Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_CHECK"  Preparing.. Make sure to stay in until they leave." });
				send_to_int22({ 123 });
				fbr::cur()->wait(2s);
				if (!CAM::DOES_CAM_EXIST(anti_crash_camera)) {
					anti_crash_camera = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", true);
					CAM::SET_CAM_ROT(anti_crash_camera, CAM::GET_GAMEPLAY_CAM_ROT(0), 0);
					CAM::SET_CAM_COORD(anti_crash_camera, { CAM::GET_GAMEPLAY_CAM_COORD().x, CAM::GET_GAMEPLAY_CAM_COORD().y, CAM::GET_GAMEPLAY_CAM_COORD().z + 8000 });
				}
				g_Render->m_SubmenuStack.pop();
				g_Render->m_SubmenuStack.pop();
				g_Render->m_SubmenuStack.pop();
				g_Render->m_SubmenuStack.pop();
				Player ID = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
				PED::REMOVE_PED_ELEGANTLY(&ID);
				Blip blip = HUD::GET_BLIP_FROM_ENTITY(ID);
				HUD::REMOVE_BLIP(&blip);
				NativeVector3 C = ENTITY::GET_ENTITY_COORDS(ID, 0);
				g_CallbackScript->AddCallback<ModelCallback>((0x431D501C), [=] {
					Ped ped1 = PED::CREATE_PED(26, 0x431D501C, C.x, C.y, C.z, 1, 1, 0);
					DeleteEntity2(ped1);
					Ped ped2 = PED::CREATE_PED(26, 0x431D501C, C.x, C.y, C.z, 1, 1, 0);
					DeleteEntity2(2);
					WEAPON::GIVE_WEAPON_TO_PED(ped1, -581044007, 1, false, true);
					WEAPON::SET_CURRENT_PED_WEAPON(ped1, -581044007, true);
					TASK::TASK_COMBAT_PED(ped1, ID, 0, 16);
					NativeVector3 C2 = ENTITY::GET_ENTITY_COORDS(ped1, 0);
					FIRE::ADD_EXPLOSION(C2.x, C2.y, C2.z, 72, 100, false, true, 0, false);
					TASK::TASK_STAND_GUARD(ped1, C.x, C.y, C.z, 180, "WORLD_HUMAN_GUARD_STAND");

				});
				g_CallbackScript->AddCallback<ModelCallback>((0x431D501C), [=] {
					Ped ped2 = PED::CREATE_PED(26, 0x431D501C, C.x, C.y, C.z, 1, 1, 0);
					DeleteEntity2(2);
					WEAPON::GIVE_WEAPON_TO_PED(ped2, -581044007, 1, false, true);
					WEAPON::SET_CURRENT_PED_WEAPON(ped2, -581044007, true);
					TASK::TASK_COMBAT_PED(ped2, ID, 0, 16);
					NativeVector3 C2 = ENTITY::GET_ENTITY_COORDS(ped2, 0);
					FIRE::ADD_EXPLOSION(C2.x, C2.y, C2.z, 72, 100, false, true, 0, false);
					TASK::TASK_STAND_GUARD(ped2, C.x, C.y, C.z, 180, "WORLD_HUMAN_GUARD_STAND");

				});
				DWORD dummy = 0xFF;
				Hash hash = MISC::GET_HASH_KEY("adder");;
				uint64_t model_info = g_GameFunctions->m_ModelInfo(hash, &dummy);
				if (model_info != 0) {

					g_CallbackScript->AddCallback<ModelCallback>((hash), [=] {
						*reinterpret_cast<int*>(model_info + 0x340) = 8;
						NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 1);
						Vehicle veh = VEHICLE::CREATE_VEHICLE(hash, coords.x, coords.y, coords.z, 0, true, false, 0);
						NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NETWORK::VEH_TO_NET(veh), 1);
						if (ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(veh))
							DECORATOR::DECOR_SET_INT(veh, "MPBitset", (1 << 10));
						if (ENTITY::DOES_ENTITY_EXIST(veh)) {
							ENTITY::SET_ENTITY_VISIBLE(veh, 1, 0);
							VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, 0);
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
						}
						*reinterpret_cast<int*>(model_info + 0x340) = 0;

						});

				}
				Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_CHECK"  Sent!" });
				
			}
			if (Menu_DataCrash == 2) {
				g_Render->m_SubmenuStack.pop();
				g_Render->m_SubmenuStack.pop();
				g_Render->m_SubmenuStack.pop();
				g_Render->m_SubmenuStack.pop();
				if (!CAM::DOES_CAM_EXIST(anti_crash_camera)) {
					anti_crash_camera = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", true);
					CAM::SET_CAM_ROT(anti_crash_camera, CAM::GET_GAMEPLAY_CAM_ROT(0), 0);
					CAM::SET_CAM_COORD(anti_crash_camera, { CAM::GET_GAMEPLAY_CAM_COORD().x, CAM::GET_GAMEPLAY_CAM_COORD().y, CAM::GET_GAMEPLAY_CAM_COORD().z + 8000 });
				}
				if (g_SelectedPlayer == PLAYER::PLAYER_ID()) {
					if (CAM::DOES_CAM_EXIST(anti_crash_camera)) {
						CAM::RENDER_SCRIPT_CAMS(false, true, 700, true, true, true);
						CAM::SET_CAM_ACTIVE(anti_crash_camera, false);
						CAM::DESTROY_CAM(anti_crash_camera, true);
					}
					return;
				}
 				for (int i = 0; i < sizeof(Lists::crash_models) / sizeof(uint32_t); i++)
				{
					NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 1);
					if (STREAMING::IS_MODEL_A_PED(Lists::crash_models[i]) && STREAMING::IS_MODEL_VALID(Lists::crash_models[i])) {
						g_CallbackScript->AddCallback<ModelCallback>(Lists::crash_models[i], [=] {
							PED::CREATE_PED(28, Lists::crash_models[i], coords.x, coords.y, coords.z, 0, true, false);
						});
					}
					else if (STREAMING::IS_MODEL_A_VEHICLE(Lists::crash_models[i]) && STREAMING::IS_MODEL_VALID(Lists::crash_models[i])) {
						g_CallbackScript->AddCallback<ModelCallback>(Lists::crash_models[i], [=] {
							Vehicle veh = VEHICLE::CREATE_VEHICLE(Lists::crash_models[i], coords.x, coords.y, coords.z, 0, true, false, 0);
							NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NETWORK::VEH_TO_NET(veh), 1);
							if (ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(veh))
								DECORATOR::DECOR_SET_INT(veh, "MPBitset", (1 << 10));
							if (ENTITY::DOES_ENTITY_EXIST(veh)) {
								ENTITY::SET_ENTITY_VISIBLE(veh, 1, 0);
								VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, 0);
								ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
							}
						});
					}
					else if (!STREAMING::IS_MODEL_A_VEHICLE(Lists::crash_models[i]) && STREAMING::IS_MODEL_A_PED(Lists::crash_models[i]) && STREAMING::IS_MODEL_VALID(Lists::crash_models[i])){
						g_CallbackScript->AddCallback<ModelCallback>(Lists::crash_models[i], [=] {
							OBJECT::CREATE_OBJECT(Lists::crash_models[i], coords.x, coords.y, coords.z, true, false, 0);
						});

					}
				}
				if (CAM::DOES_CAM_EXIST(anti_crash_camera)) {
					CAM::RENDER_SCRIPT_CAMS(false, true, 700, true, true, true);
					CAM::SET_CAM_ACTIVE(anti_crash_camera, false);
					CAM::DESTROY_CAM(anti_crash_camera, true);
				}
			}
			if (Menu_DataCrash == 3) {
				Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_CHECK"  Preparing.. Make sure to stay in until they leave." });
				send_to_int22({ 123 });
				fbr::cur()->wait(2s);
				if (!CAM::DOES_CAM_EXIST(anti_crash_camera)) {
					anti_crash_camera = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", true);
					CAM::SET_CAM_ROT(anti_crash_camera, CAM::GET_GAMEPLAY_CAM_ROT(0), 0);
					CAM::SET_CAM_COORD(anti_crash_camera, { CAM::GET_GAMEPLAY_CAM_COORD().x, CAM::GET_GAMEPLAY_CAM_COORD().y, CAM::GET_GAMEPLAY_CAM_COORD().z + 8000 });
				}
				g_Render->m_SubmenuStack.pop();
				g_Render->m_SubmenuStack.pop();
				g_Render->m_SubmenuStack.pop();
				g_Render->m_SubmenuStack.pop();
				DWORD dummy = 0xFF;
				Hash hash = MISC::GET_HASH_KEY("deluxo");;
				uint64_t model_info = g_GameFunctions->m_ModelInfo(hash, &dummy);
				if (model_info != 0) {

					g_CallbackScript->AddCallback<ModelCallback>((hash), [=] {
						*reinterpret_cast<int*>(model_info + 0x340) = 8;
						NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 1);
						Vehicle veh = VEHICLE::CREATE_VEHICLE(hash, coords.x, coords.y, coords.z, 0, true, false, 0);
						NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NETWORK::VEH_TO_NET(veh), 1);
						if (ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(veh))
							DECORATOR::DECOR_SET_INT(veh, "MPBitset", (1 << 10));
						if (ENTITY::DOES_ENTITY_EXIST(veh)) {
							ENTITY::SET_ENTITY_VISIBLE(veh, 1, 0);
							VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, 0);
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
						}
						*reinterpret_cast<int*>(model_info + 0x340) = 0;

						});

				}
				Noti::InsertNotification({ ImGuiToastType_None, 2000, ICON_FA_CHECK"  Sent!" });
			}
			

			
			

		}
		Network* get_network()
		{
			return *g_GameFunctions->m_network;
		}
		rage::rlGamerInfo* get_net_data() const
		{
			return g_GameVariables->m_net_game_player(g_SelectedPlayer) == nullptr ? nullptr : g_GameVariables->m_net_game_player(g_SelectedPlayer)->get_net_data();
		}
		
		inline rage::snPeer* get_session_peer(CNetGamePlayer* target)
		{
			for (std::uint32_t i = 0; i < get_network()->m_game_session_ptr->m_peer_count; i++)
			{
				if (get_network()->m_game_session_ptr->m_peers[i]->m_peer_data.m_gamer_handle_2.m_rockstar_id == target->get_net_data()->m_gamer_handle_2.m_rockstar_id)
				{
					return get_network()->m_game_session_ptr->m_peers[i];
				}
			}

			return nullptr;
		}
		bool is_host() const
		{
			return  g_GameVariables->m_net_game_player(g_SelectedPlayer) == nullptr ? false : g_GameVariables->m_net_game_player(g_SelectedPlayer)->is_host();
		}
		bool is_host2(int p) const
		{
			return  g_GameVariables->m_net_game_player(p) == nullptr ? false : g_GameVariables->m_net_game_player(p)->is_host();
		}
		inline rage::snPlayer* GetSessionPlayer(CNetGamePlayer* target)
		{
			for (std::uint32_t i = 0; i < get_network()->m_game_session_ptr->m_player_count; i++)
			{
				if (get_network()->m_game_session_ptr->m_players[i]->m_player_data.m_host_token == target->get_net_data()->m_host_token)
				{
					return get_network()->m_game_session_ptr->m_players[i];
				}
			}

			if (get_network()->m_game_session_ptr->m_local_player.m_player_data.m_host_token == target->get_net_data()->m_host_token)
				return &get_network()->m_game_session_ptr->m_local_player;

			return nullptr;
		}
		void remove(int pos) {
			if (pos == 0) {
				const size_t arg_count = 15;
				int64_t args[arg_count] =
				{
					(int64_t)1727896103,
					(int64_t)PLAYER::PLAYER_ID(),
					(int64_t)(int)-1
				};

				g_GameFunctions->m_trigger_script_event(1, args, arg_count, 1 << g_SelectedPlayer);

				m_queue.add(18s, "Removing player..", [] {});
			}
			if (pos == 1) {
				if (std::chrono::system_clock::now() - last < 10s)
				{
					return;
				}

				last = std::chrono::system_clock::now();

				auto PlayerManager = GetNetworkPlayerMgr();
				if (PlayerManager == nullptr) {
					return;
				}
				auto LocalPlayer = PlayerManager->m_local_net_player;
				auto target = g_GameFunctions->m_GetNetPlayer(g_SelectedPlayer);
				if (!target) {
					return;
				}
				if (LocalPlayer == nullptr) {
					return;
				}
				if (target == nullptr) {
					return;
				}
				if (target == LocalPlayer) {
					return;
				}
				if (target->is_host()) {
					return;
				}
				if (target->is_valid()) {
					PlayerManager->RemovePlayer(target);
					WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target->m_player_id), FALSE);
					PlayerManager->UpdatePlayerListsForPlayer(LocalPlayer);
				}
				
			}
		}
	};
}