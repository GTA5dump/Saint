#pragma once

// GTA-V
#include <GTAV-Classes/script/scrProgramTable.hpp>
#include <GTAV-Classes/script/scrNativeHandler.hpp>
#include <GTAV-Classes/script/scrNativeRegistration.hpp>
#include <GTAV-Classes/script/scrNativeRegistrationTable.hpp>
#include <GTAV-Classes/ped/CPedFactory.hpp>
#include <GTAV-Classes/network/CMsgTextMessage.hpp>
#include "Classes.h"
#include "Types.hpp"
#include <GTAV-Classes/netsync/nodes/player/CPlayerGameStateDataNode.hpp>

#include "Protections.h"
#include "Common.hpp"
#include <GTAV-Classes/rage/rlSessionByGamerTaskResult.hpp>
#include <GTAV-Classes/rage/rlScHandle.hpp>
#include <GTAV-Classes/rage/rlQueryPresenceAttributesContext.hpp>
#include <GTAV-Classes/rage/rlTaskStatus.hpp>
#include <GTAV-Classes/network/Network.hpp>
#include <GTAV-Classes/socialclub/FriendRegistry.hpp>
#include <GTAV-Classes/netsync/nodes/vehicle/CVehicleGadgetDataNode.hpp>
#include <GTAV-Classes/base/HashTable.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <GTAV-Classes/network/CNetworkPlayerMgr.hpp>
namespace Saint
{
	class datBitBuffer2;
	class netConnectionManager;
	class CWaterTune
	{
	public:
		DWORD dwWaterColor; //0x0000  Default: 0x1A00191C
		float fRippleScale; //0x0004  Default: 0.040000f
		float fOceanFoamScale; //0x0008  Default: 0.050000f
		float fSpecularFalloff; //0x000C  Default: 1118.000000f
		float fFodPierceIntensity; //0x0010  Default: 1.100000f
		float fRefractionBlend; //0x0014  Default: 0.700000f
		float fRefractionExponent; //0x0018  Default: 0.250000f
		float fWaterCycleDepth; //0x001C  Default: 10.000000f
		float fWaterCycleFade; //0x0020  Default: 50.000000f
		float fWaterLightningDepth; //0x0024  Default: 0.000000f
		float fWaterLightningFade; //0x0028  Default: 10.000000f
		float fDeepWaterModDepth; //0x002C  Default: 90.000000f
		float fDeepWaterModFade; //0x0030  Default: 80.000000f
		float fGodRaysLerpStart; //0x0034  Default: 0.000000f
		float fGodRaysLerpEnd; //0x0038  Default: 200.000000f
		float fDisturbFoamScale; //0x003C  Default: 0.050000f
		void* vec2FogMin; //0x0040  Default: x = -4000.000000 y = -4000.000000
		void* vec2FogMax; //0x0048  Default: x = 4500.000000 y= 8000.000000
	};
	struct vfx_wheel {
		float m_slip_min; //0x0004
		float m_slip_max; //0x0008
		float m_pressure_min; //0x000C
		float m_pressure_max; //0x0010
		int m_type1; //0x0014
		BOOL m_unk1; //0x0018
		int m_type2; //0x001c
		BOOL m_unk2; //0x0010
		int m_type3; //0x0024
		BOOL m_unk3; //0x0028
		int m_type4; //0x002c
		BOOL m_unk4; //0x0030
		uint8_t m_r; //0x0034
		uint8_t m_g; //0x0035
		uint8_t m_b; //0x0036
		char _0x0037[1]; //0x0037
		float m_friction_thresh_min; //0x0038
		float m_friction_thresh_max; //0x003C
		uint32_t m_friction_fx1; //0x0040
		uint32_t m_friction_fx2; //0x0044
		uint32_t m_friction_fx3; //0x0048
		float m_disp_thresh_min; //0x004C
		float m_disp_thresh_max; //0x0050
		uint32_t m_displacement_fx1; //0x0054
		uint32_t m_displacement_fx2; //0x0058
		uint32_t m_displacement_fx3; //0x005C
		uint32_t m_displacement_fx_lod; //0x0060
		float m_burn_friction_evo_min; //0x0064
		float m_burn_friction_evo_max; //0x0068
		float m_burn_temp_evo_min; //0x006C
		float m_burn_temp_evo_max; //0x0070
		uint32_t m_burnout_fx1; //0x0074
		uint32_t m_burnout_fx2; //0x0078
		uint32_t m_burnout_fx3; //0x007C
		bool m_lights_on; //0x0080
		uint8_t m_lights_col_min_r; //0x0081
		uint8_t m_lights_col_min_g; //0x0082
		uint8_t m_lights_col_min_b; //0x0083
		uint8_t m_lights_col_max_r; //0x0084
		uint8_t m_lights_col_max_g; //0x0085
		uint8_t m_lights_col_max_b; //0x0086
		char _0x0087[1]; //0x0087
		float m_lights_intensity_min; //0x0088
		float m_lights_intensity_max; //0x008C
		float m_lights_range_min; //0x0090
		float m_lights_range_max; //0x0094
		float m_lights_falloff_min; //0x0098
		float m_lights_falloff_max; //0x009C
	};
	class netConnectionPeer
	{
	public:
		uint32_t m_internal_ip; //0x0000
		uint16_t m_internal_port; //0x0004
		uint32_t m_external_ip; //0x0008
		uint16_t m_external_port; //0x000C
		uint64_t m_peer_id; //0x0010
		uint32_t unk_0018; //0x0018
		uint16_t unk_001C; //0x001C
		uint8_t m_platform; //0x001E
	};
	static_assert(sizeof(netConnectionPeer) == 0x20);
	struct sExplosionFX {
		Hash NameHash;
		char Unk[0x20];
		float Scale;
		char Unk2[0x38];
	};
	class Pointers {
	public:
		explicit Pointers();
		~Pointers() noexcept = default;
		Pointers(Pointers const&) = delete;
		Pointers(Pointers&&) = delete;
		Pointers& operator=(Pointers const&) = delete;
		Pointers& operator=(Pointers&&) = delete;

		void PostInit();

		using FallTaskConstructor = std::uint64_t* (std::uint64_t* _this, std::uint32_t flags);
		FallTaskConstructor* m_FallTaskConstructor;

		using get_sync_tree2 = std::uint64_t (CNetworkObjectMgr* first, eNetObjType a2);
		get_sync_tree2* get_sync_tree;

		using ProcessNetObject = bool(uint64_t sync_tree, uint64_t net_obj);
		ProcessNetObject* m_ProcessNetObject;

		PVOID m_invalid_decal_crash{};
		PVOID m_serialize_dynamic_entity_game_state_data_node{};

		PVOID process_net_obj{};

		PVOID chat_data{};

		uint64_t g_get_net_msg_net_player;

		std::unordered_map<uint64_t, std::pair<uint32_t, uint32_t>> g_raw_buffer_translations;
	};
	class GameVariables
	{
	public:
		explicit GameVariables();
		~GameVariables() noexcept = default;
		GameVariables(GameVariables const&) = delete;
		GameVariables(GameVariables&&) = delete;
		GameVariables& operator=(GameVariables const&) = delete;
		GameVariables& operator=(GameVariables&&) = delete;

		void PostInit();

		std::uint32_t* m_GameState;
		std::uint32_t* m_FrameCount;
		HWND m_GameWindow;
		IDXGISwapChain* m_Swapchain;

		rage::scrProgramTable* m_ScriptProgramTable;
		rage::scrNativeRegistrationTable* m_NativeRegistrations;
		void* m_NativeReturnAddress;
		std::uint64_t** m_GlobalBase;
		PVOID m_ModelSpawnBypass;
		char* m_GameBuild;
		uint32_t* m_region_code;

		using get_net_game_player = CNetGamePlayer * (*) (uint32_t player);
		get_net_game_player m_net_game_player;

		

		using handle_to_ptr = rage::CDynamicEntity* (*)(Entity);
		handle_to_ptr m_handle_to_ptr{};

		bool* m_is_session_started{};

		using request_control = void (*)(rage::netObject* net_object);
		request_control m_request_control;

		uintptr_t ui_3d_draw_manager;
		uintptr_t add_element_to_scene;
		uintptr_t push_scene_preset_manager;
		uintptr_t set_scene_element_lighting;
		uintptr_t get_scene_preset;

		uint64_t m_WorldPtr;

		FriendRegistry* m_friendRegistry;
		const char* m_version = MENU_VERSION;

		int* m_resolution_x;
		int* m_resolution_y;

		sExplosionFX* ExplosionsFXData;

		

	};

	class GameFunctions
	{
	public:
		explicit GameFunctions();
		~GameFunctions() noexcept = default;
		GameFunctions(GameFunctions const&) = delete;
		GameFunctions(GameFunctions&&) = delete;
		GameFunctions& operator=(GameFunctions const&) = delete;
		GameFunctions& operator=(GameFunctions&&) = delete;

		
		PVOID m_NetworkEvents{};

		

		using clear_ped_tasks_network = void(*)(CPed* ped, bool immediately);
		clear_ped_tasks_network m_clear_ped_tasks_network;

		int64_t** m_send_chat_ptr{};
		using chat_message = bool(*)(int64_t* send_chat_ptr, rage::rlGamerInfo* gamer_info, const char* message, bool is_team);
		chat_message m_send_chat_message{};

		using WndProc = LRESULT(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		WndProc* m_WndProc;

		PVOID crashProtection;

		using GetLabelText = const char* (void* unk, const char* label);
		GetLabelText* m_GetLabelText;

		using GetNativeHandler = rage::scrNativeHandler(rage::scrNativeRegistrationTable*, rage::scrNativeHash);
		GetNativeHandler* m_GetNativeHandler;

		using FixVectors = void(rage::scrNativeCallContext*);
		FixVectors* m_FixVectors;

		CPedFactory** m_pedFactory;

		using CPlayerListMenuConstructor = __int64(__int64 a1, __int64 a2, __int64 a3);
		CPlayerListMenuConstructor* m_PlayerListMenuConstructor;

		using ChatSender = CNetGamePlayers * (__int64 player);
		ChatSender* get_chat_sender;

		using ChatMessage = void(void* thisptr, __int64  unk1, __int64 unk2, const char* message);
		ChatMessage* m_ChatMessage;

		PVOID m_owned_explosion;
		rage::hash_list* m_vehicle_hash_pool;

		bool* should_sync_money_rewards;

		using trigger_script_event = void(*)(int event_group, int64_t* args, int arg_count, int player_bits);
		trigger_script_event m_trigger_script_event{};

		

		using CPlayerWildCard = __int64* (std::int32_t friendindex);
		CPlayerWildCard* m_PlayerWildcard;

		using RegisterFile = std::uint32_t(*)(std::uint32_t* texture_id, const char* path, bool p1, const char* name, bool p2);
		RegisterFile m_RegisterFile;

		using send_event_ack = void(*)(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, int event_index, int event_handled_bitset);
		send_event_ack m_send_event_ack{};

		using GetEventData = bool(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount);
		GetEventData* m_GetEventData;

		using IncrementStatEvent = int(__int64 neteventsclass, CNetGamePlayers* targetPlayer);
		IncrementStatEvent* m_IncrementStatEvent;

		using increment_Stat = void (*) (Hash hash, unsigned int value, CNetGamePlayer* player);
		increment_Stat m_remote_increment;
		PVOID m_write_player_gamer_data_node{};

		using write_player_game_state_data_node2 = bool(*)(rage::netObject* plr, CPlayerGameStateDataNode* node);
		write_player_game_state_data_node2 m_write_player_game_state_data_node;

		using SendNetInfoo = bool(netPlayerData* player, __int64 a2, __int64 a3, DWORD* a4);
		SendNetInfoo* m_SendNetInfo;

		PVOID m_AssignPhysicalIndexHandler;

		PVOID m_received_event{};

		PVOID m_pickup_creation{};

		using start_get_session_by_gamer_handle = bool (*)(int profile_index, rage::rlGamerHandle* handles, int count, rage::rlSessionByGamerTaskResult* result, int unk, bool* success, rage::rlTaskStatus* state);
		start_get_session_by_gamer_handle m_start_get_session_by_gamer_handle;
		Network** m_network;
		using join_session_by_info = bool (*)(Network* network, rage::rlSessionInfo* info, int unk, int flags, rage::rlGamerHandle* handles, int handlecount);
		join_session_by_info m_join_session_by_info;

		PVOID m_get_network_event_data;

		rage::atArray<GtaThread*>* m_script_threads{};

		PVOID m_received_array_update;
		PVOID m_task_parachute_object_0x270{};
		PVOID m_serialize_take_off_ped_variation_task;

		

		
		using GetNetworkData = bool(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount);
		GetNetworkData* m_GetScriptEvent;


		void* m_data; //0x0000
		uint32_t m_bitOffset; //0x0008
		uint32_t m_maxBit; //0x000C
		uint32_t m_bitsRead; //0x0010
		uint32_t m_curBit; //0x0014
		uint32_t m_highestBitsRead; //0x0018
		uint8_t m_flagBits; //0x001C

		

		using get_net_object = rage::netObject* (*)(CNetworkObjectMgr* mgr, int16_t id, bool can_delete_be_pending);
		get_net_object m_get_net_object{};

		PVOID m_received_clone_sync;
		PVOID m_received_clone_create;
		PVOID m_constraint_attachment_crash{};

		PVOID m_fragment_physics_crash;
		PVOID m_fragment_physics_crash_2;

		using get_connection_peer = netConnectionPeer* (*)(rage::netConnectionManager* manager, int peer_id);
		using send_remove_gamer_cmd = void (*)(rage::netConnectionManager* net_connection_mgr, netConnectionPeer* player, int connection_id, rage::snMsgRemoveGamersFromSessionCmd* cmd, int flags);
		using handle_remove_gamer_cmd = void* (*)(rage::snSession* session, rage::snPlayer* origin, rage::snMsgRemoveGamersFromSessionCmd* cmd);
		get_connection_peer m_get_connection_peer{};
		send_remove_gamer_cmd m_send_remove_gamer_cmd{};
		handle_remove_gamer_cmd m_handle_remove_gamer_cmd{};

		PVOID m_ped_creation_data_node{};
		PVOID m_player_creation_data_node{};
		PVOID m_object_creation_data_node{};
		PVOID m_vehicle_creation_data_node{};
		PVOID m_player_appearance_data_node{};
		PVOID m_invalid_player_crash_patch;

		char* m_east_azimuth_patch;//0F 29 62 20
		char* m_west_azimuth_patch;//0F 29 62 50
		char* m_azimuth_transition_patch;//0F 29 A2 80 00 00 00
		char* m_zenith_patch;//0F 29 A2 B0 00 00 00 8B 81 58 03 00 00
		char* m_zenith_transition_patch;//0F 29 A2 E0 00 00 00
		char* m_cloud_mid_patch;//0F 29 8B 60 03 00 00
		char* m_cloud_base_patch;//0F 29 A2 80 03 00 00


		using ReadBitbufDword = bool(datBitBuffer2* buffer, PVOID read, int bits);
		ReadBitbufDword* m_ReadBitbufDword;

		using read_bitbuf_array = bool (*)(datBitBuffer2* buffer, PVOID read, int bits, int unk);
		read_bitbuf_array m_read_bitbuf_array;

		PVOID m_FallTaskConstructor;

		bool* m_send_clone_sync;

		std::uintptr_t m_NetworkObjectMgrInterface;

		using GetEntityFromScript = std::uint64_t(std::int32_t script_index);
		using ChangeNetworkObjectOwner = std::uint64_t(std::uint64_t obj_mgr, std::uint64_t net_obj, CNetGamePlayer* player, std::uint64_t unk);
		GetEntityFromScript* m_GetEntityFromScript;
		ChangeNetworkObjectOwner* m_ChangeNetworkObjectOwner;

		using GetNetPlayer = CNetGamePlayer * (std::uint32_t id);
		GetNetPlayer* m_GetNetPlayer;

		using GetNetPlayer2 = rage::CNetGamePlayer * (std::uint32_t id);
		GetNetPlayer2* m_GetNetPlayer2;
		
		using get_vehicle_gadget_array_size = int (*)(eVehicleGadgetType type);
		get_vehicle_gadget_array_size m_get_vehicle_gadget_array_size;

		PVOID m_serialize_vehicle_gadget_data_node;

		using get_sync_tree_for_type = rage::netSyncTree* (*)(CNetworkObjectMgr* mgr, uint16_t sync_type);
		get_sync_tree_for_type m_get_sync_tree_for_type{};
		CNetworkObjectMgr** m_network_object_mgr{};

		using get_entity_attached_to = rage::CDynamicEntity* (*)(rage::CDynamicEntity* entity);
		get_entity_attached_to m_get_entity_attached_to;

		HashTable<CBaseModelInfo*>* m_model_table;


		PVOID m_can_apply_data;

		CNetworkPlayerMgr** m_NetworkPlayerManager;

		PVOID test222;

		using reset_network_complaints = void (*)(CNetComplaintMgr* mgr);
		reset_network_complaints m_reset_network_complaints{};

		CWaterTune* m_water_tune;

		bool* m_force_player_card_refresh{};

		PVOID m_send_player_card_stats{};

		PVOID m_sort_session_details;

		using read_bitbuf_string = bool (*)(datBitBuffer2* buffer, char* read, int bits);
		read_bitbuf_string m_read_bitbuf_string{};

		PVOID m_receive_net_message{};

		uint64_t address;
		std::pair<vfx_wheel*, uint8_t> g_vfx_wheel;
		CReplayInterface** m_ReplayInterface{};

		PVOID m_allow_weapons_in_vehicle{};

		using ModelMgr = __int64(__int64 a1, DWORD* a2);
		ModelMgr* m_ModelInfo;

		using read_bitbuf_bool = bool (*)(datBitBuffer2* buffer, bool* read, int bits);
		read_bitbuf_bool m_read_bitbuf_bool{};
		
		


	};
	inline GameFunctions get_functions_from_here;
	class datBitBuffer2 {
	public:
		bool ReadDword(std::uint32_t* integer, int bits)
		{
			return get_functions_from_here.m_ReadBitbufDword(this, integer, bits);
		}
		bool ReadQWord(uint64_t* integer, int bits)
		{
			if (bits <= 32)
			{
				uint32_t v10;
				if (ReadDword(&v10, bits))
				{
					*integer = v10;
					return true;
				}
			}
			else
			{
				uint32_t v10, v11;
				if (ReadDword(&v11, 32u) && ReadDword(&v10, bits - 32u))
				{
					*integer = v11 | ((uint64_t)v10 << 32);
					return true;
				}
			}
			return false;
		}
		bool Seek(std::uint32_t bits)
		{
			if (bits >= 0) {
				std::uint32_t length = (m_flagBits & 1) ? m_maxBit : m_curBit;
				if (bits <= length)
					m_bitsRead = bits;
			}
			return false;
		}
		bool ReadInt64(int64_t* integer, int bits)
		{
			uint32_t v8;
			uint64_t v9;
			if (ReadDword(&v8, 1u) && ReadQWord(&v9, bits - 1))
			{
				*integer = v8 + (v9 ^ -(int64_t)v8);
				return true;
			}
			return false;
		}
		bool ReadString(char* string, int32_t length) {
			auto extended = Read<bool>(1);
			auto len = Read<int32_t>(extended ? 15 : 7);
			if (len > length)
				return false;
			ReadArray(string, len * 8);
			if (string[len - 1] != '\0')
				return false;
			return true;
		}
		bool ReadBool(bool* integer)
		{
			return get_functions_from_here.m_read_bitbuf_bool(this, integer, 1);
		}
		bool ReadPeerId(uint64_t* integer)
		{
			return this->ReadQWord(integer, 0x40);
		}
		bool ReadInt32(int32_t* integer, int bits)
		{
			int32_t v8;
			int32_t v9;
			if (ReadDword((uint32_t*)&v8, 1u) && ReadDword((uint32_t*)&v9, bits - 1))
			{
				*integer = v8 + (v9 ^ -v8);
				return true;
			}
			return false;
		}

		bool ReadArray(PVOID array, int size)
		{
			return get_functions_from_here.m_read_bitbuf_array(this, array, size, 0);
		}

		template<typename T>
		inline T ReadSigned(int length)
		{
			static_assert(sizeof(T) <= 4, "maximum of 32 bit read");

			int val = 0;
			ReadInt32(&val, length);

			return T(val);
		}

		template<typename T>
		inline T Read(int length)
		{
			static_assert(sizeof(T) <= 4, "maximum of 32 bit read");

			std::uint32_t val = 0;
			ReadDword(&val, length);

			return T(val);
		}
		inline float ReadFloat(int length, float divisor)
		{
			auto integer = Read<int>(length);

			float max = (1 << length) - 1;
			return ((float)integer / max) * divisor;
		}
		inline float ReadSignedFloat(int length, float divisor)
		{
			auto integer = ReadSigned<int>(length);

			float max = (1 << (length - 1)) - 1;
			return ((float)integer / max) * divisor;
		}
		
	public:
		void* m_data; //0x0000
		std::uint32_t m_bitOffset; //0x0008
		std::uint32_t m_maxBit; //0x000C
		std::uint32_t m_bitsRead; //0x0010
		std::uint32_t m_curBit; //0x0014
		std::uint32_t m_highestBitsRead; //0x0018
		std::uint8_t m_flagBits; //0x001C
	};

	inline std::unique_ptr<GameVariables> g_GameVariables;
	inline std::unique_ptr<GameFunctions> g_GameFunctions;
	inline std::unique_ptr<Pointers> pointers;

	


}
