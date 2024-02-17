#pragma once
#include "VMTHook.hpp"
#include "Invoker.hpp"
#include "../Libraries/Include/GTAV-Classes/netsync/nodes/player/CPlayerGamerDataNode.hpp"
#include "../Libraries/Include/GTAV-Classes/network/CNetworkPlayerMgr.hpp"
#include "../Libraries/Include/GTAV-Classes/network/CNetGamePlayer.hpp"
#include "Enums.h"
#include <GTAV-Classes/netsync/nodes/object/CObjectCreationDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/ped/CPedCreationDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/vehicle/CVehicleCreationDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/task/ClonedTakeOffPedVariationInfo.hpp>
#include <GTAV-Classes/netsync/nodes/vehicle/CVehicleGadgetDataNode.hpp>
#include <GTAV-Classes/netsync/netSyncDataNode.hpp>
#include <GTAV-Classes/netsync/netSyncTree.hpp>
#include <GTAV-Classes/netsync/nodes/door/CDoorCreationDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/dynamic_entity/CDynamicEntityGameStateDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/object/CObjectCreationDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/ped/CPedAttachDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/ped/CPedCreationDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/ped/CPedInventoryDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/physical/CPhysicalAttachDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/pickup/CPickupCreationDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/player/CPlayerAppearanceDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/player/CPlayerCreationDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/proximity_migrateable/CSectorDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/train/CTrainGameStateDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/vehicle/CVehicleCreationDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/vehicle/CVehicleGadgetDataNode.hpp>
#include <GTAV-Classes/netsync/nodes/vehicle/CVehicleProximityMigrationDataNode.hpp>
#include <GTAV-Classes/network/CNetGamePlayer.hpp>
#include <GTAV-Classes/stats/CPlayerCardStats.hpp>
#include <GTAV-Classes/netsync/nodes/dynamic_entity/CDynamicEntityGameStateDataNode.hpp>
#include <GTAV-Classes/network/netPlayerMgrBase.hpp>
#include <GTAV-Classes/network/CNetComplaintMgr.hpp>
namespace Saint
{
	class JoinedInfo {
	public:
		bool join_queued = false;
		rage::rlSessionInfo information;
	};
	inline JoinedInfo session_information;
	inline bool m_EnableSCIDJoiner;
	inline __int64 m_SCIDJoiner;
	inline __int64 m_PlayerListPointer;
	inline int menu_version = 87456845654;
	inline bool streamer_mode = false;
	inline std::string streamer_mode_name = "Saint";
	inline bool weapons_in_int = false;
	inline bool jump_in_int = false;
	inline bool join_queue = false;
	inline CNetGamePlayer* m_syncing_player = nullptr;
	inline rage::rlSessionInfo g_Session_info;
	inline bool BeastLanding = false;
	inline bool spoof_as_reg = false;
	inline bool rank = false;
	inline int rank_value = 0;
	enum eChatCommandType {
		NONE_INVALID,
		SPAWN,
		EXPLODE
	};
	struct ChatCommandData {
		eChatCommandType type;
		std::string argument;
	};
	class ChatCommands22 {
	public:
		std::string right = "";
		std::string input = "";
		bool caseInsensitiveStringCompare(char a, char b) {
			return (std::tolower(a) == std::tolower(b));
		}
		bool has_string_attached(const std::string& str, const std::string& check)
		{
			std::string strLower = str;
			std::string checkLower = check;
			std::transform(strLower.begin(), strLower.end(), strLower.begin(), [](unsigned char c) {
				return std::tolower(c);
				});
			std::transform(checkLower.begin(), checkLower.end(), checkLower.begin(), [](unsigned char c) {
				return std::tolower(c);
				});

			size_t found = strLower.find(checkLower);
			if (found != std::string::npos) {
				return true;
			}
			else {
				return false;
			}
		}
		std::string getArugmentFromString(std::string input) {
			if (has_string_attached(input, "/spawn")) {
				std::string substringToReplace1 = "/spawn ";
				std::string replacement1 = "";

				size_t pos = input.find(substringToReplace1);
				while (pos != std::string::npos) {
					input.replace(pos, substringToReplace1.length(), replacement1);
					pos = input.find(substringToReplace1, pos + replacement1.length());
				}
				return input;
			}
			else {
				return "Not Found";
			}
			
		}
		ChatCommandData getArugmentFromString2(std::string input) {
			if (has_string_attached(input, "/spawn")) {
				std::string substringToReplace1 = "/spawn ";
				std::string replacement1 = "";

				size_t pos = input.find(substringToReplace1);
				while (pos != std::string::npos) {
					input.replace(pos, substringToReplace1.length(), replacement1);
					pos = input.find(substringToReplace1, pos + replacement1.length());
				}
				return { eChatCommandType::SPAWN, input };
			}
			else {
				return { eChatCommandType::NONE_INVALID, "Not Found" };
			}

		}
		
		bool enabled = false;
	};
	class FeatureListForHooks {
	public:
		bool weapons_in_vehs;
		ChatCommands22 chat_commands;
		bool log_chat_message = false;
		bool magnet = false;
		int magnet_count = 0;
	};
	inline FeatureListForHooks hook_features;
	class MenuFlag {
	public:
		bool isDev() {
			if (spoof_as_reg) {
				return false;
			}
			else {
				#ifndef DEV
					return false;
				#else
					return true;
				#endif	
			}
		}
	};
	
	inline MenuFlag* Flags;
	struct Hooks
	{
		struct global_msg_context {
			char m_message[0x100];
			uint64_t m_sender_chat_token;
			bool m_flag0_is_neg1;
		};
		static void GetStatInt(rage::scrNativeCallContext* src);

		static const char* GetLabelText(void* unk, const char* label);
		static LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		static constexpr auto PresentIndex = 8;
		static HRESULT Present(IDXGISwapChain* dis, UINT syncInterval, UINT flags);

		static constexpr auto ResizeBuffersIndex = 13;
		static HRESULT ResizeBuffers(IDXGISwapChain* dis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);

		static __int64* PlayerWildCardHandler(std::int32_t friendIndex);
		static __int64 CPlayerListMenuConstructor(__int64 a1, __int64 a2, __int64 a3);

		static bool GetScriptEvent(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount);
		static void NETWORK_SESSION_HOST(rage::scrNativeCallContext* src);
		static void DISABLE_CONTROL_ACTION(rage::scrNativeCallContext* src);
		static void HUD_FORCE_WEAPON_WHEEL(rage::scrNativeCallContext* src);
		static void SET_CURRENT_PED_WEAPON(rage::scrNativeCallContext* src);
		static bool IncrementStatEvent(CNetworkIncrementStatEvent* neteventclass, CNetGamePlayer* Source);

		static void ChatMessage(void* thisptr, __int64 unk1, __int64 unk2, const char* message);
		static bool write_player_game_state_data_node(rage::netObject* player, CPlayerGameStateDataNode* node);
		static void write_player_gamer_data_node(rage::netObject* player, CPlayerGamerDataNode* node);

		static bool SendNetInfo(netPlayerData* player, __int64 a2, __int64 a3, DWORD* a4);

		static bool send_chat_message(void* team_mgr, rage::rlGamerInfo* local_gamer_info, const char* message, bool is_team);

		static void* AssignNewPhysicalIndexHandler(CNetworkPlayerMgr* NetworkPlayerMgr, CNetGamePlayer* player, uint8_t new_index);
		static void InvalidModsCrashPatch(std::int64_t a1, std::int64_t a2, int a3, char a4);

		

		static bool GameEvent(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint16_t event_id, int event_index, int event_handled_bitset, int buffer_size, rage::datBitBuffer* buffer);
		static bool pickup_creation_node(CPickupCreationDataNode* node, rage::netObject* obj);

		static void NetworkEventHandler(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint16_t event_id, int event_index, int event_handled_bitset, int buffer_size, datBitBuffer2* buffer);

		static bool GetEventData(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount, int64_t sender);

		//crashes
		static bool received_clone_create(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, int32_t object_id, int32_t object_flag, rage::datBitBuffer* buffer, int32_t timestamp);
		static eAckCode received_clone_sync(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, uint16_t object_id, datBitBuffer2* bufer, uint16_t unk, uint32_t timestamp);
		static std::int64_t constraint_attachment_crash(std::uintptr_t a1);
		static bool fragment_physics_crash(uintptr_t a1, uint32_t a2, uintptr_t a3, uintptr_t a4, uintptr_t a5);
		static bool fragment_physics_crash_2(float* a1, float* a2);

		static void invalid_player_crash(uint64_t a1, uint64_t a2);
		static bool object_creation_data_node(CObjectCreationDataNode* node, rage::netObject* obj);
		static bool hk_ped_creation_data_node(CPedCreationDataNode* node);
		static bool hk_vehicle_creation_data_node(CVehicleCreationDataNode* node);

		static bool received_array_update(rage::netArrayHandlerBase* array, CNetGamePlayer* sender, rage::datBitBuffer* buffer, int size, std::int16_t cycle);
		static uint64_t task_parachute_object_0x270(uint64_t _this, int a2, int a3);
		static void serialize_take_off_ped_variation_task(ClonedTakeOffPedVariationInfo* info, rage::CSyncDataBase* serializer);
		static std::uint64_t* FallTaskConstructor(std::uint64_t* _this, std::uint32_t flags);

		static bool can_apply_data(rage::netSyncTree* tree, rage::netObject* object);

		static void serialize_vehicle_gadget_data_node(CVehicleGadgetDataNode* node, rage::CSyncDataBase* data);

		static rage::netGameEvent* send_player_card_stats(rage::netGameEvent* a1, CPlayerCardStats* stats);
		static bool sort_session_details(SessionSortEntry* e1, SessionSortEntry* e2);
		static bool receive_net_message(void* netConnectionManager, void* a2, rage::netConnection::InFrame* frame);

		static bool weapon_info_group(int64_t unk, int weaponinfo_group);
		static int apply_vehicle_data__crash(rage::netObject* object, uint64_t node_data);
		static bool ProcessNetObject(std::uint64_t sync_tree, std::uint64_t net_obj);
		static uint64_t invalid_decal(uintptr_t a1, int a2);
		static void serialize_dynamic_entity_game_state_data_node(CDynamicEntityGameStateDataNode* node, rage::CSyncDataBase* data);
		static bool process_net_obj_hook(std::uint64_t sync_tree, std::uint64_t net_obj);
		static bool get_chat_msg_data_hook(CMsgTextMessage* output, std::uint64_t sync_data);
		static bool read_chat_message(global_msg_context* context, datBitBuffer2* bit_buffer);
		






	};

	class Hooking
	{
	public:
		explicit Hooking();
		~Hooking() noexcept;
		Hooking(Hooking const&) = delete;
		Hooking(Hooking&&) = delete;
		Hooking& operator=(Hooking const&) = delete;
		Hooking& operator=(Hooking&&) = delete;

		void Hook();
		void Unhook();

		friend struct Hooks;
		void* m_OriginalChatSend{};
	private:
		void* m_NtQueryVirtualMemory{};

		void* m_OriginalGetLabelText{};
		void* m_OriginalWndProc{};
		VMTHook m_D3DHook;
		void* m_OriginalRIDFunction{};
		void* m_OriginalJoinSessionHook{};
		void* m_OriginalIncrementStatEvent{};

		void* m_Original_write_player_game_state_data_node{};
		void* m_Original_write_player_gamer_data_node{};
		void* m_OriginalSendNetInfo{};

		void* m_OriginalAssignPhysicalIndex{};
		void* m_OriginalRecieveEvent{};
		void* m_OriginalModCrash{};

		void* OriginalRecivied{};

		void* m_OriginalPickupNode{};

		void* m_OriginalNetworkHandler{};

		void* originalDetection{};

		void* m_OriginalGetEventData{};
		void* m_OriginalFragmentCrash{};
		void* m_OriginalFragmentCrash2{};
		void* AttachmentCrash{};
		void* InvalidObjectCrash{};
		void* InvalidObjectCrash2{};

		void* m_OriginalInvalidPlayer{};
		void* m_OriginalInvalidPlayer222{};
		void* ped_creation{};
		void* vehicle_creation{};
		void* array_update{};
		void* parachute{};
		void* parachute2{};
		void* m_OriginalFallTaskConstructor{};

		void* crashover{};

		void* yim_crash{};

		void* yim_crash2{};

		void* can_applydata{};
		void* spoofing3{};
		void* magnet{};

		void* net_message{};

		void* weapon_info_group2{};
		void* vehicle_data{};

		void* m_OriginalProcessNetObject{};

		void* orignalnigger{};
		void* originalfaggot{};

		void* model_infocrashnigger{};


		void* chat_commands{};

		void* chat_command_not_ozark{};
	};

	inline std::unique_ptr<Hooking> g_Hooking;
}
