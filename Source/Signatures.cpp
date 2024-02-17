#include "Signatures.hpp"
#include "Invoker.hpp"
#include "hex_memory.h"
#include "ClassHelper.h"
namespace Saint
{
	Pointers::Pointers() :
		m_FallTaskConstructor(Signature("E8 ? ? ? ? B3 04 08 98 A0 00 00 00").Scan().Add(1).Rip().As<decltype(m_FallTaskConstructor)>()),
		get_sync_tree(Signature("0F B7 CA 83 F9 07", "GST").Scan().Add(0x14).Rip().As<decltype(get_sync_tree)>()),
		m_invalid_decal_crash(Signature("E8 ? ? ? ? 8B 9C 24 B8 00 00 00 4C 8B AC 24 A8 00 00 00", "IDC").Scan().Add(1).Rip().As<PVOID>()),
		m_serialize_dynamic_entity_game_state_data_node(Signature("48 89 5C 24 18 55 56 57 41 56 41 57 48 83 EC 20 48 8B 02 48 8D 99", "").Scan().As<PVOID>()),
		process_net_obj(Signature("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 EC 20 4C 8B F2 48 8B E9 BB 01 00 00 00", "PNO").Scan().As<decltype(process_net_obj)>()),
		chat_data(Signature("E8 ? ? ? ? 84 C0 74 0A 48 8D 4C 24 ? E8 ? ? ? ? 48 8B 45 50", "CT").Scan().As<decltype(chat_data)>())
	{
		
	}
	GameVariables::GameVariables() :
		m_GameState(Signature("83 3D ? ? ? ? ? 75 17 8B 43 20 25").Scan().Add(2).Rip().As<decltype(m_GameState)>()),
		m_FrameCount(Signature("8B 15 ? ? ? ? 41 FF CF").Scan().Add(2).Rip().As<decltype(m_FrameCount)>()),
		m_GameWindow(FindWindowA("grcWindow", nullptr)),
		m_Swapchain(Signature("44 38 35 ? ? ? ? 48 8B 01").Scan().Sub(13).Rip().As<decltype(m_Swapchain)&>()),
		m_ScriptProgramTable(Signature("44 8B 0D ? ? ? ? 4C 8B 1D ? ? ? ? 48 8B 1D ? ? ? ? 41 83 F8 FF 74 3F 49 63 C0 42 0F B6 0C 18 81 E1").Scan().Add(17).Rip().As<decltype(m_ScriptProgramTable)>()),
		m_NativeRegistrations(Signature("76 32 48 8B 53 40 48 8D 0D").Scan().Add(9).Rip().As<decltype(m_NativeRegistrations)>()),
		m_NativeReturnAddress(Signature("FF E3").Scan().As<decltype(m_NativeReturnAddress)>()),
		m_GlobalBase(Signature("48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D").Scan().Add(3).Rip().As<decltype(m_GlobalBase)>()),
		m_region_code(Signature("48 83 EC 28 83 3D ? ? ? ? ? 75 10").Scan().Add(16).Rip().Add(1).As<decltype(m_region_code)>()),
		m_net_game_player(Signature("48 83 EC ? 33 C0 38 05 ? ? ? ? 74 ? 83 F9").Scan().As<decltype(m_net_game_player)>()),
		m_handle_to_ptr(Signature("83 F9 FF 74 31 4C 8B 0D").Scan().As<decltype(m_handle_to_ptr)>()),
		m_request_control(Signature("E8 ? ? ? ? EB 3E 48 8B D3").Scan().Add(1).Rip().As<decltype(m_request_control)>()),
		ui_3d_draw_manager(Signature("4C 8B 15 ? ? ? ? F3 0F 11 45 ? F3 0F 10 05 ? ? ? ? BF ? ? ? ? BB ? ? ? ? 41 BE ? ? ? ? F3 0F 11").Scan().Add(3).Rip().As<decltype(ui_3d_draw_manager)>()),
		push_scene_preset_manager(Signature("40 53 48 83 EC 20 8B 02 48 8D 54 24 38 48 8B D9 89 44 24 38 E8 ? ? ? ? 48 8B C8").Scan().As<decltype(push_scene_preset_manager)>()),
		add_element_to_scene(Signature("4C 8B DC 48 83 EC 58 8B").Scan().As<decltype(add_element_to_scene)>()),
		set_scene_element_lighting(Signature("48 8B C4 48 89 58 10 48 89 70 18 57 48 83 EC 30 48 83 B9").Scan().As<decltype(set_scene_element_lighting)>()),
		get_scene_preset(Signature("0F B7 81 10 08 00 00").Scan().As<decltype(get_scene_preset)>()),
		m_is_session_started(Signature("40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE").Scan().Add(3).Rip().As<bool*>()),
		m_resolution_x(Signature("66 0F 6E 0D ? ? ? ? 0F B7 3D").Scan().Sub(4).Rip().As<int*>()),
		m_resolution_y(Signature("66 0F 6E 0D ? ? ? ? 0F B7 3D").Scan().Add(4).Rip().As<int*>()),
		m_friendRegistry(Signature("3B 0D ? ? ? ? 73 17").Scan().Add(2).Rip().As<FriendRegistry*>()),
		
		m_ModelSpawnBypass(Signature("48 8B C8 FF 52 30 84 C0 74 05 48").Scan().Add(8).As<decltype(m_ModelSpawnBypass)>())
	{
		char* c_location = nullptr;
		char* c_location2 = nullptr;
		auto p_worldPtr = Memory::pattern("48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07");
		c_location = p_worldPtr.count(1).get(0).get<char>(0);
		m_WorldPtr = reinterpret_cast<uint64_t>(c_location) + *reinterpret_cast<int*>(reinterpret_cast<uint64_t>(c_location) + 3) + 7;
		
		m_GameBuild = Signature("48 83 EC 60 48 8D 0D ? ? ? ? E8").Scan().Sub(17).Add(268).Rip().As<decltype(m_GameBuild)>();
	}

	void GameVariables::PostInit()
	{
	}

	GameFunctions::GameFunctions() :

		//m_GetScriptEvent(Signature("48 85 C0 74 14 4C 8B 10").Scan().Sub(28).As<decltype(m_GetScriptEvent)>()),
		m_GetLabelText(Signature("48 89 5C 24 ? 57 48 83 EC 20 48 8B DA 48 8B F9 48 85 D2 75 44 E8").Scan().As<decltype(m_GetLabelText)>()),
		m_WndProc(Signature("44 8B E2 4C 8B E9 3B D0").Scan().Sub(52).As<decltype(m_WndProc)>()),
		m_GetNativeHandler(Signature("48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A").Scan().Add(12).Rip().As<decltype(m_GetNativeHandler)>()),
		m_FixVectors(Signature("83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA").Scan().As<decltype(m_FixVectors)>()),
		m_pedFactory(Signature("48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81").Scan().Add(3).Rip().As<decltype(m_pedFactory)>()),
		m_owned_explosion(Signature("0F 85 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 48 08 E8").Scan().As<decltype(m_owned_explosion)>()),
		m_vehicle_hash_pool(Signature("4C 03 05 ? ? ? ? EB 09 49 83 C2 04 EB 8B").Scan().Add(3).Rip().As<decltype(m_vehicle_hash_pool)>()),
		//Script Event
		m_trigger_script_event(Signature("45 8B F0 41 8B F9 48 8B EA").Scan().Sub(0x1C).As<decltype(m_trigger_script_event)>()),
		//Junk
		//Increment
		m_remote_increment(Signature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 49 8B F0 8B EA 8B F9 E8").Scan().As<decltype(m_remote_increment)>()),
		m_IncrementStatEvent(Signature("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 55 41 56 41 57 48 8B EC 48 83 EC 60 8B 79 30").Scan().As<decltype(m_IncrementStatEvent)>()),
		get_chat_sender(Signature("E8 ? ? ? ? 83 BD ? ? ? ? ? 48 8B D8 0F 8D ? ? ? ? 48 8B ? ? ?").Scan().Add(0x1).Rip().As<decltype(get_chat_sender)>()),
		//Spoofing
		m_write_player_game_state_data_node(Signature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 30 0F B7 81").Scan().As<decltype(m_write_player_game_state_data_node)>()),
		m_write_player_gamer_data_node(Signature("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 81 C1 ? ? ? ? 48 8B DA E8").Scan().As<PVOID>()),
		m_SendNetInfo(Signature("E8 ? ? ? ? 84 C0 74 26 8B 96").Scan().Sub(0xC4).As<decltype(m_SendNetInfo)>()),
		//Chat Spammer
		m_send_chat_ptr(Signature("83 7E 1C 01 48 8B 3D").Scan().Add(7).Rip().As<int64_t**>()),
		m_send_chat_message(Signature("48 83 EC 20 48 8B F1 48 8B CA 41 8A E9").Scan().Sub(21).As<decltype(m_send_chat_message)>()),
		//	m_ChatMessage(Signature("40 88 B3 ? ? ? ? 89 73 08 48 39 B3 ? ? ? ? 75 24 48 8D 05 ? ? ? ? 48 8B CB 48 89 B3").Scan().Add(0x16).Rip().As<decltype(m_ChatMessage)>()),
		//Notifications
		m_AssignPhysicalIndexHandler(Signature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 20 41 8A E8").Scan().As<PVOID>()),
		//Trolling
		m_clear_ped_tasks_network(Signature("E8 ? ? ? ? EB 28 48 8B 8F A0 10 00 00").Scan().Add(1).Rip().As<decltype(m_clear_ped_tasks_network)>()),
		//YTD
		m_RegisterFile(Signature("84 C0 74 0D 4C 8B 07").Scan().Sub(0x6C).As<decltype(m_RegisterFile)>()),
		//Protections
		m_send_event_ack(Signature("E8 ? ? ? ? 66 83 7B 08 5B").Scan().Add(1).Rip().As<decltype(m_send_event_ack)>()),
		m_pickup_creation(Signature("48 8B EC 48 83 EC 20 80 B9 C0 00 00 00 00").Scan().As<PVOID>()),
		//RID Joiner
		m_start_get_session_by_gamer_handle(Signature("E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 8B 05 ? ? ? ? 48 8D 4C 24").Scan().Add(1).Rip().As<start_get_session_by_gamer_handle>()),
		m_join_session_by_info(Signature("E8 ? ? ? ? 0F B6 CB 84 C0 41 0F 44 CD").Scan().Add(1).Rip().As<decltype(m_join_session_by_info)>()),
		//Network
		m_network(Signature("48 8B 0D ? ? ? ? 48 8B D7 E8 ? ? ? ? 84 C0 75 17 48 8B 0D ? ? ? ? 48 8B D7").Scan().Add(3).Rip().As<Network**>()),
		m_NetworkEvents(Signature("66 41 83 F9 ? 0F 83").Scan().As<decltype(m_NetworkEvents)>()),
		
		m_get_net_object(Signature("4C 8B EA 41 0F B7 D1").Scan().Add(0xEE).Rip().As<decltype(m_get_net_object)>()),
		//Crash Protections
		crashProtection(Signature("E8 ? ? ? ? 40 88 7C 24 ? 49 89 9C 24").Scan().Add(1).Rip().As<PVOID>()),
		m_received_clone_sync(Signature("4C 8B EA 41 0F B7 D1").Scan().Sub(0x1C).Rip().As<decltype(m_received_clone_sync)>()),
		m_fragment_physics_crash(Signature("E8 ? ? ? ? 44 8B 4D 1C").Scan().Add(1).Rip().As<PVOID>()),
		m_fragment_physics_crash_2(Signature("E8 ? ? ? ? 84 C0 75 0B 41 FF CF").Scan().Add(1).Rip().As<PVOID>()),
		m_received_clone_create(Signature("48 8B C4 66 44 89 48").Scan().As<PVOID>()),
		m_constraint_attachment_crash(Signature("40 53 48 83 EC 20 48 8B D9 48 8B 49 38 48 8B 01").Scan().As<PVOID>()),
		m_object_creation_data_node(Signature("48 89 5C 24 10 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC 50 F7 81 4C 01 00 00 FD FF FF FF").Scan().As<PVOID>()),
		m_ped_creation_data_node(Signature("48 89 5C 24 10 55 48 8B EC 48 83 EC 20 8B 45 10 8B 89 C4 00 00 00").Scan().As<PVOID>()),
		m_vehicle_creation_data_node(Signature("48 89 5C 24 ? 55 48 8B EC 48 83 EC 20 8B 45 10 8B 89 C8 00 00 00").Scan().As<PVOID>()),
		m_player_appearance_data_node(Signature("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B B1").Scan().As<PVOID>()),
		m_received_array_update(Signature("48 89 5C 24 10 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC 30 48 8B 05").Scan().As<PVOID>()),
		m_task_parachute_object_0x270(Signature("0F 88 ? ? ? ? 75 34").Scan().Sub(6).As<PVOID>()),
		m_serialize_take_off_ped_variation_task(Signature("40 55 53 57 41 56 48 8B EC 48 83 EC 68").Scan().As<PVOID>()),
		m_get_entity_attached_to(Signature("48 83 EC 28 48 8B 51 50 48 85 D2 74 04").Scan().As<get_entity_attached_to>()),
		m_invalid_player_crash_patch(Signature("48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC 20 48 8B 59 40 4C 8B F2 48 8B F1 48 85 DB 74 22 48 8B 02 48 8B CA FF 50 48 4C 8D 05 ? ? ? ? 48 8D 15 ? ? ? ? 4C 8B C8 48 8B CB E8 ? ? ? ? 44 0F B7 46 ? 33 DB 33 C9 49 63 D0 45 85 C0 7E 18 48 8B 46 50 48 8B 18 48 85 DB 75 0C 48 FF C1 48 83 C0 08 48 3B CA 7C EC 33 FF 33 C9 45 85 C0 7E 69 48 8B 46 50 48 8B 18 48 85 DB 75 10 48 FF C1 FF C7 48 83 C0 08 49 3B C8 7C EA EB 4D 48 8B 4B 08 48 85 C9 74 12 48 8B 49 48 48 85 C9 74 09 48 8B 01 49 8B D6 FF 50 10").Scan().As<PVOID>()),
		//BreakupKick
		m_get_connection_peer(Signature("8D 42 FF 83 F8 FD 77 3D").Scan().Add(23).Rip().As<get_connection_peer>()),
		m_send_remove_gamer_cmd(Signature("8D 42 FF 83 F8 FD 77 3D").Scan().Add(65).Rip().As<send_remove_gamer_cmd>()),
		m_handle_remove_gamer_cmd(Signature("41 FF C6 FF C7").Scan().Sub(0x6E).As<handle_remove_gamer_cmd>()),
		//m_get_network_event_data(Signature("53 43 52 49 50 54 5F 4E 45 54 57 4F 52 4B").Scan().Sub(0x38).As<PVOID*>()),
		should_sync_money_rewards(Signature("40 8A 2D ? ? ? ? 48 83 64 24 40 00").Scan().Add(3).Rip().As<decltype(should_sync_money_rewards)>()),
		m_east_azimuth_patch(Signature("0F 29 62 20").Scan().As<decltype(m_east_azimuth_patch)>()),
		m_west_azimuth_patch(Signature("0F 29 62 50 8B 81 9C 03 00 00").Scan().As<decltype(m_west_azimuth_patch)>()),
		m_azimuth_transition_patch(Signature("0F 29 A2 80 00 00 00").Scan().As<decltype(m_azimuth_transition_patch)>()),
		m_zenith_patch(Signature("0F 29 A2 B0 00 00 00 8B 81 58 03 00 00").Scan().As<decltype(m_zenith_patch)>()),
		m_zenith_transition_patch(Signature("0F 29 A2 E0 00 00 00").Scan().As<decltype(m_zenith_transition_patch)>()),
		m_cloud_mid_patch(Signature("0F 29 8B 60 03 00 00").Scan().As<decltype(m_cloud_mid_patch)>()),
		m_ReadBitbufDword(Signature("48 89 74 24 ? 57 48 83 EC 20 48 8B D9 33 C9 41 8B F0 8A").Scan().Sub(5).As<decltype(m_ReadBitbufDword)>()),
		m_read_bitbuf_array(Signature("48 89 5C 24 ? 57 48 83 EC 30 41 8B F8 4C", "RBA").Scan().As<decltype(m_read_bitbuf_array)>()),
		//m_read_bitbuf_string(Signature("E8 ? ? ? ? 48 8D 4F 3C").Scan().Add(1).Rip().As<decltype(m_read_bitbuf_string)>()), unused so im too lazy to update it
		m_FallTaskConstructor(Signature("E8 ? ? ? ? B3 04 08 98 A0 00 00 00", "FTC").Scan().Add(1).As<decltype(m_FallTaskConstructor)>()),
		m_NetworkObjectMgrInterface(Signature("48 8B 0D ? ? ? ? 45 33 C0 E8 ? ? ? ? 33 FF 4C 8B F0", "NOMI").Scan().Add(3).Rip().As<decltype(m_NetworkObjectMgrInterface)>()),
		m_ChangeNetworkObjectOwner(Signature("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 81 EC ? ? ? ? 44 8A 62 4B", "CNOO").Scan().As<decltype(m_ChangeNetworkObjectOwner)>()),
		m_GetEntityFromScript(Signature("E8 ? ? ? ? 8D 53 01 33 DB", "GEFS").Scan().Add(1).Rip().As<decltype(m_GetEntityFromScript)>()),
		m_GetNetPlayer(Signature("48 83 EC 28 33 C0 38 05 ? ? ? ? 74 0A").Scan().As<decltype(m_GetNetPlayer)>()),
		m_GetNetPlayer2(Signature("48 83 EC 28 33 C0 38 05 ? ? ? ? 74 0A", "GNP").Scan().As<decltype(m_GetNetPlayer2)>()),
		m_send_clone_sync(Signature("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F B7 42", "SCS").Scan().As<decltype(m_send_clone_sync)>()),
		m_get_vehicle_gadget_array_size(Signature("40 53 48 83 EC 40 33 DB E8", "GVGAS").Scan().As<decltype(m_get_vehicle_gadget_array_size)>()),
		m_serialize_vehicle_gadget_data_node(Signature("48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 56 41 57 48 83 EC 30 48 8B 02 48 8D", "SVGDN").Scan().Add(0x14).Rip().As<PVOID>()),
		m_get_sync_tree_for_type(Signature("4C 8B EA 41 0F B7 D1", "GSTFT").Scan().Add(0x14).Rip().As<decltype(m_get_sync_tree_for_type)>()),
		m_network_object_mgr(Signature("48 8B 0D ? ? ? ? 45 33 C0 E8 ? ? ? ? 33 FF 4C 8B F0", "NOM").Scan().Add(3).Rip().As<CNetworkObjectMgr**>()),
		m_can_apply_data(Signature("E8 ? ? ? ? 84 C0 0F 84 AF 01 00 00 48 8B 03", "CAD").Scan().Add(1).Rip().As<PVOID>()),
		m_NetworkPlayerManager(Signature("48 8B 0D ? ? ? ? 8A D3 48 8B 01 FF 50 ? 4C 8B 07 48 8B CF", "NPM").Scan().Add(3).Rip().As<decltype(m_NetworkPlayerManager)>()),
		m_reset_network_complaints(Signature("E8 ? ? ? ? 8B 8B ? ? ? ? 03 CF", "RNC").Scan().Add(1).Rip().As<reset_network_complaints>()),
		m_script_threads(Signature("45 33 F6 8B E9 85 C9 B8", "ST").Scan().Sub(4).Rip().Sub(8).As<decltype(m_script_threads)>()),
		m_send_player_card_stats(Signature("48 89 5C 24 08 57 48 83 EC 30 48 83 64 24 20 00 48 8B DA 41", "SPCS").Scan().As<PVOID>()),
		m_sort_session_details(Signature("C3 0F 2E 42 0C", "SSD").Scan().Sub(0x10).As<PVOID>()),
		m_receive_net_message(Signature("48 83 EC 20 4C 8B 71 50 33 ED", "RNM").Scan().Sub(0x19).As<PVOID>()),
		m_ReplayInterface(Signature("0F B7 44 24 ? 66 89 44 4E", "RI").Scan().Add(0x1f).Rip().As<CReplayInterface**>()),
		m_allow_weapons_in_vehicle(Signature("49 8B 40 08 39 10", "AWIV").Scan().Sub(23).As<PVOID>()),
		m_ModelInfo(Signature("0F B7 05 ? ? ? ? 45 33 C9 4C 8B DA 66 85 C0 0F 84 ? ? ? ? 44 0F B7 C0 33 D2 8B C1 41 F7 F0 48 8B 05 ? ? ? ? 4C 8B 14 D0 EB 09 41 3B 0A 74 54", "MI").Scan().As<decltype(m_ModelInfo)>()),
		m_force_player_card_refresh(Signature("44 38 2D ? ? ? ? 74 1D 44 00 A6 BB 07 00 00", "FPCR").Scan().Add(3).Rip().As<bool*>()),
		m_read_bitbuf_bool(Signature("E8 ? ? ? ? 84 C0 74 41 48 8D 56 2C", "RBB").Scan().Add(1).Rip().As<decltype(m_read_bitbuf_bool)>())

	{
		//m_water_tune = Signature("4C 8D 0D ?? ?? ?? ?? 48 0F 45 D1").Scan().From_Instruction().As<decltype(m_water_tune)>();
		//g_vfx_wheel = { (vfx_wheel*)memory::read_instruction(address, 3, 7),*(uint8_t*)(address + 0xA) }; // good
	}



}
