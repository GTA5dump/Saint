#pragma once
#include "../Libraries/Include/GTAV-Classes/network/netPlayer.hpp"
#include "../Libraries/Include/GTAV-Classes/network/ClanData.hpp"
#include "../Libraries/Include/GTAV-Classes/rage/rlSessionInfo.hpp"
#include "../Libraries/Include/GTAV-Classes/network/CNetGamePlayer.hpp"
#include "Signatures.hpp"
#include <GTAV-Classes/script/GtaThread.hpp>
namespace rage {
	class tlsContext
	{
	public:
		char m_padding1[0xB8];         // 0x00
		sysMemAllocator* m_allocator;  // 0xB8
		char m_padding2[0x788];        // 0xD0
		scrThread* m_script_thread;    // 0x848
		bool m_is_script_thread_active;// 0x850

		static tlsContext* get()
		{
			return *reinterpret_cast<tlsContext**>(__readgsqword(0x58));
		}
	};
	static_assert(sizeof(tlsContext) == 0x858);
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
	class CSyncDataBase
	{
	public:
		virtual ~CSyncDataBase() = default;
		virtual bool SerializeDword(uint32_t* dword, int size) = 0;
		virtual bool SerializeWord(uint16_t* word, int size) = 0;
		virtual bool SerializeByte(uint8_t* byte, int size) = 0;
		virtual bool SerializeInt32(int32_t* i, int size) = 0;
		virtual bool SerializeInt16(int16_t* i, int size) = 0;
		virtual bool SerializeSignedByte(int8_t* byte, int size) = 0;
		virtual bool SerializeBool(bool* flag) = 0;
		virtual bool SerializeInt64(int64_t* i, int size) = 0;
		virtual bool SerializeInt32Alt(int32_t* i, int size) = 0;
		virtual bool SerializeInt16Alt(int16_t* i, int size) = 0;
		virtual bool SerializeSignedByteAlt(int8_t* byte, int size) = 0;
		virtual bool SerializeQword(uint64_t* qword, int size) = 0;
		virtual bool SerializeDwordAlt(uint32_t* dword, int size) = 0;
		virtual bool SerializeWordAlt(uint16_t* word, int size) = 0;
		virtual bool SerializeByteAlt(uint8_t* byte, int size) = 0;
		virtual bool SerializeSignedFloat(float* flt, float divisor, int size) = 0;
		virtual bool SerializeFloat(float* flt, float divisor, int size) = 0;
		virtual bool SerializeNetworkId(uint16_t* net_id) = 0;
		virtual bool SerializeVector3(rage::fvector3* vec3, float divisor, int size) = 0;
		virtual bool SerializeQuaternion(void* unk) = 0;// i have no clue what that is
		virtual bool SerializeVector3SignedZComponent(rage::fvector3* vec3, float divisor, int size) = 0;
		virtual bool SerializeOrientation(rage::fvector4* vec4, float size) = 0;// yes, the size is a float
		virtual bool SerializeArray(void* array, int size) = 0;
		virtual bool SerializeString(char* str, int max_length) = 0;
		virtual bool IsSizeCalculator() = 0;
		virtual bool IsSizeCalculator2() = 0;

		void* unk_0x8;
		void* syncLog;
		datBitBuffer* buffer;
	};
	enum class eNetMessage : uint32_t
	{
		MsgInvalid = 0xFFFFF,
		MsgSessionAcceptChat = 0x62,
		MsgStartMatchCmd = 0x2D,
		MsgSetInvitableCmd = 0x1F,
		MsgSessionMemberIds = 0x23,
		MsgRequestGamerInfo = 0x54,
		MsgRemoveGamersFromSessionCmd = 0x53,
		MsgNotMigrating = 0x35,
		MsgMigrateHostResponse = 0x12,
		MsgMigrateHostRequest = 0x66,
		MsgJoinResponse = 0x2A,
		MsgJoinRequest = 0x41,
		MsgHostLeftWhilstJoiningCmd = 0x58,
		MsgConfigResponse = 0x5F,
		MsgConfigRequest = 0x48,
		MsgChangeSessionAttributesCmd = 0x5A,
		MsgAddGamerToSessionCmd = 0x64, // this is where send net info to lobby is called, among other things
		MsgReassignResponse = 0x10,
		MsgReassignNegotiate = 0x01,
		MsgReassignConfirm = 0x26,
		MsgPlayerData = 0x18,
		MsgPackedReliables = 0x30,
		MsgPackedCloneSyncACKs = 0x3B,
		MsgNonPhysicalData = 0x16,
		MsgNetArrayMgrUpdateAck = 0x5D,
		MsgNetArrayMgrUpdate = 0x60,
		MsgNetArrayMgrSplitUpdateAck = 0x25,
		MsgScriptVerifyHostAck = 0x0B,
		MsgScriptVerifyHost = 0x3E,
		MsgScriptNewHost = 0x0E,
		MsgScriptMigrateHostFailAck = 0x1A,
		MsgScriptMigrateHost = 0x33,
		MsgScriptLeaveAck = 0x40,
		MsgScriptLeave = 0x17,
		MsgScriptJoinHostAck = 0x4D,
		MsgScriptJoinAck = 0x43,
		MsgScriptJoin = 0x5C,
		MsgScriptHostRequest = 0x67,
		MsgScriptHandshakeAck = 0x5B,
		MsgScriptHandshake = 0x57,
		MsgScriptBotLeave = 0x2B, // unused?
		MsgScriptBotJoinAck = 0x63, // unused?
		MsgScriptBotJoin = 0x1C, // unused?
		MsgScriptBotHandshakeAck = 0x31, // unused?
		MsgScriptBotHandshake = 0x4B, // unused?
		MsgPartyLeaveGame = 0x3D,
		MsgPartyEnterGame = 0x1E,
		MsgCloneSync = 0x4E, // aka clone_create, clone_sync etc.
		MsgActivateNetworkBot = 0x65, // unused?
		MsgRequestObjectIds = 0x29,
		MsgInformObjectIds = 0x09,
		MsgTextMessage = 0x24, // this one is for chat
		MsgPlayerIsTyping = 0x61,
		MsgPackedEvents = 0x4F, // aka received_event
		MsgPackedEventReliablesMsgs = 0x20,
		MsgRequestKickFromHost = 0x0D,
		MsgTransitionToGameStart = 0x50,
		MsgTransitionToGameNotify = 0x02,
		MsgTransitionToActivityStart = 0x06,
		MsgTransitionToActivityFinish = 0x36,
		MsgTransitionParameters = 0x3C,
		MsgTransitionParameterString = 0x37,
		MsgTransitionLaunchNotify = 0x1B,
		MsgTransitionLaunch = 0x19,
		MsgTransitionGamerInstruction = 0x14,
		MsgTextMessage2 = 0x0A, // this one is for phone message
		MsgSessionEstablishedRequest = 0x52,
		MsgSessionEstablished = 0x07,
		MsgRequestTransitionParameters = 0x42,
		MsgRadioStationSyncRequest = 0x47,
		MsgRadioStationSync = 0x46,
		MsgPlayerCardSync = 0x3A,
		MsgPlayerCardRequest = 0x6A,
		MsgLostConnectionToHost = 0x81,
		MsgKickPlayer = 0x34, // host kick
		MsgDebugStall = 0x7E, // unused?
		MsgCheckQueuedJoinRequestReply = 0x59,
		MsgCheckQueuedJoinRequest = 0x51,
		MsgBlacklist = 0x0C,
		MsgRoamingRequestBubbleRequiredResponse = 0x83,
		MsgRoamingRequestBubbleRequiredCheck = 0x82,
		MsgRoamingRequestBubble = 0x2E,
		MsgRoamingJoinBubble = 0x4C,
		MsgRoamingJoinBubbleAck = 0x3F,
		MsgRoamingInitialBubble = 0x32,
		MsgVoiceStatus = 0x03,
		MsgTextChatStatus = 0x00,
		MsgJoinResponse2 = 0x08,
		MsgJoinRequest2 = 0x68,
		MsgNetTimeSync = 0x38, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 37
		MsgNetComplaint = 0x55, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 54
		MsgNetLagPing = 0x27, // unused? ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 26
		MsgSearchResponse = 0x6B, // unused? ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 6A
		MsgSearchRequest = 0x05, // unused?
		MsgQosProbeResponse = 0x2C, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 2B
		MsgQosProbeRequest = 0x1D, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 1C
		MsgCxnRelayAddressChanged = 0x49, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 48
		MsgCxnRequestRemoteTimeout = 0x2F, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 2E
		MsgSessionDetailRequest = 0x22, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 21
		MsgSessionDetailResponse = 0x13, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 12
		MsgKeyExchangeOffer = 0x0F, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 0E (last result)
		MsgKeyExchangeAnswer = 0x44, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 43
		Msg_0x87 = 0x87,
		Msg_0x88 = 0x88,
		Msg_0x80 = 0x80,
		Msg_0x28 = 0x28,
		Msg_0x11 = 0x11,
		Msg_0x45 = 0x45,
		Msg_0x89 = 0x89,
		Msg_0x86 = 0x86,
	};
	namespace netConnection
	{
		class InFrame
		{
		public:
			enum class EventType
			{
				ConnectionClosed = 3,
				FrameReceived = 4,
				BandwidthExceeded = 6,
				OutOfMemory = 7
			};

			virtual ~InFrame() = default;

			virtual void destroy() = 0;
			virtual EventType get_event_type() = 0;
			virtual uint32_t _0x18() = 0;

			uint32_t m_timestamp;            //0x0008
			char pad_0008[52];               //0x000C
			uint32_t m_msg_id;               //0x0040
			uint32_t m_connection_identifier;//0x0044
			InFrame* m_this;                 //0x0048
			uint32_t m_peer_id;              //0x0050
			char pad_0050[44];               //0x0058
			uint32_t m_length;               //0x0080
			char pad_007C[4];                //0x0084
			void* m_data;                    //0x0088
		};
		static_assert(sizeof(InFrame) == 0x90);
	}

	class netSyncDataUnit_Dynamic
	{
	public:
		virtual ~netSyncDataUnit_Dynamic() = default;// 0x00

		virtual void _0x08() = 0;

		virtual void _0x10() = 0;

		virtual void set_data_counter(int index, uint16_t counter) = 0;// 0x18

		virtual void reset_data_counter(int index) = 0;// 0x20

		// ...

		int m_players_need_ack; // 0x08
		int m_players_need_sync;// 0x0C
	};
	class netSyncData_Dynamic
	{
	public:
		virtual ~netSyncData_Dynamic() = default;// 0x00

		virtual rage::datBitBuffer* _0x08() = 0;

		virtual rage::datBitBuffer* _0x10() = 0;

		virtual int get_num_receivers() = 0;// 0x18

		virtual int _0x20() = 0;

		virtual void _0x28() = 0;// same as get_sync_unit_for_element

		virtual netSyncDataUnit_Dynamic* get_sync_unit_for_element(uint32_t element) = 0;// 0x30

		// ...
	};
	class netArrayHandlerBase
	{
	public:
		virtual ~netArrayHandlerBase() = default;// 0x00

		virtual void _0x08() = 0;

		virtual void _0x10() = 0;

		virtual void _0x18() = 0;

		virtual void _0x20() = 0;

		virtual void _0x28() = 0;

		virtual void _0x30() = 0;

		virtual void _0x38() = 0;//

		virtual void _0x40() = 0;//

		virtual int _0x48(CNetGamePlayer* player, int max_size, uint32_t* a3, uint32_t* a4) = 0;//

		virtual int get_size(CNetGamePlayer* player, int max_size, uint32_t element) = 0;// 0x50

		virtual int pack_array_data(CNetGamePlayer* player, rage::datBitBuffer* bit_buffer, uint16_t counter, uint32_t* elem_start, bool silent) = 0;// 0x58

		virtual void _0x60() = 0;//

		virtual bool _0x68(CNetGamePlayer* player) = 0;// is_player_out_of_scope or something like that

		virtual void _0x70() = 0;//

		virtual bool can_send_update(CNetGamePlayer* player) = 0;// 0x78

		virtual void _0x80() = 0;//

		virtual void _0x88() = 0;//

		virtual void* get_identifier() = 0;// 0x90

		virtual void* _0x98() = 0;// same as get_identifier

		virtual void _0xA0() = 0;//

		virtual bool can_verify_array_data() = 0;// 0xA8

		virtual void _0xB0() = 0;//

		virtual void _0xB8() = 0;//

		virtual void should_sync_element(uint32_t element) = 0;// 0xC0

		virtual void _0xC8() = 0;//

		virtual void _0xD0() = 0;//

		virtual bool are_all_elements_in_scope() = 0;// 0xD8

		virtual void _0xE0() = 0;//

		virtual void verify_array_data() = 0;// 0xE8

		virtual void _0xF0() = 0;//

		virtual char* get_name() = 0;// 0xF8

		virtual bool is_local_player_owner_of_array() = 0;// 0x100

		virtual CNetGamePlayer* get_owner_of_array() = 0;// 0x108

		virtual void _0x110() = 0;

		virtual uint32_t get_array_hash() = 0;

		virtual int _0x120() = 0;// gets array size for hashing

		virtual netSyncData_Dynamic* _0x128() = 0;// same as get_dynamic_sync_data

		virtual netSyncData_Dynamic* get_dynamic_sync_data() = 0;// 0x130

		virtual void _0x138() = 0;

		virtual bool is_element_in_scope(uint32_t element, CNetGamePlayer* player) = 0;// 0x140

		virtual int get_receiver_index_from_player(CNetGamePlayer*) = 0;// 0x148

		virtual void _0x150() = 0;

		virtual void _0x158() = 0;

		// pasted from fivem
		virtual bool is_element_empty(uint32_t element) = 0;// 0x160

		virtual void set_element_empty(uint32_t element) = 0;// 0x168

		virtual void write_element_index(rage::datBitBuffer& buffer, uint32_t) = 0;// 0x170

		virtual void read_element_index(rage::datBitBuffer& buffer, uint32_t&) = 0;// 0x178

		virtual bool is_valid_index(uint32_t) = 0;// 0x180

		virtual void recalculate_dirty_elements() = 0;// 0x188

		virtual void reset_element_sync_data(uint32_t element) = 0;// 0x190

		virtual void do_post_read_processing() = 0;// 0x198

		virtual void do_post_element_read_processing(uint32_t element) = 0;// 0x1A0

		virtual bool can_apply_element_data(uint32_t element, const rage::netPlayer& sender, bool force) = 0;// 0x1A8

		virtual void extract_data_for_serializing(uint32_t elem) = 0;// 0x1B0

		virtual void write_element(rage::datBitBuffer& buffer, uint32_t elem, void* logger) = 0;// 0x1B8

		virtual void read_element(rage::datBitBuffer& buffer, uint32_t elem, void* logger) = 0;// 0x1C0

		virtual void log_element(uint32_t elem, void* logger) = 0;// 0x1C8

		virtual uint32_t get_current_element_size_in_bits(uint32_t elem) = 0;// 0x1D0

		virtual void apply_element_data(uint32_t element, const rage::netPlayer& sender) = 0;// 0x1D8

		virtual void _0x1E0() = 0;

		virtual void _0x1E8(bool) = 0;// very important! changes send function to use some kind of cached buffer that prevents us from modifing array data per player

		void* m_something;// 0x10

		netArrayHandlerBase* m_next;// 0x18

		uint8_t m_pad[100 - 0x18];// +8
		uint32_t m_hash;
		uint8_t m_pad2[244 - 104];// +8
		uint16_t m_index;         // 244
		uint16_t m_count;         // 246
		uint8_t m_max_elements;   // 248
		uint8_t m_element_size;   // 249
		uint8_t m_element_size_2; // 250
		uint8_t m_pad3[13];       // 251
		void* m_array;            // 264

#if 0
		static inline netArrayHandlerBase* get_by_data(void* data)
		{
			if (auto array_mgr = *big::g_pointers->m_gta.m_game_array_mgr)
			{
				if (auto handler = array_mgr->m_start)
				{
					do
					{
						if (handler->m_array == data)
							return handler;
					} while (handler = handler->m_next);
				}
			}

			return nullptr;
		}
#endif
	};

	static_assert(sizeof(netArrayHandlerBase) == 272);
	enum class eEventNetworkType : int64_t
	{
		CEventNetworkPlayerJoinScript = 153,
		CEventNetworkPlayerLeftScript = 154,
		CEventNetworkStorePlayerLeft = 155,
		CEventNetworkStartSession = 156,
		CEventNetworkEndSession = 157,
		CEventNetworkStartMatch = 158,
		CEventNetworkRemovedFromSessionDueToStall = 160,
		CEventNetworkRemovedFromSessionDueToComplaints = 161,
		CEventNetworkConnectionTimeout = 162,
		CEventNetworkPedDroppedWeapon = 163,
		CEventNetworkPlayerSpawn = 164,
		CEventNetworkPlayerCollectedPickup = 165,
		CEventNetworkPlayerCollectedAmbientPickup = 166,
		CEventNetworkPlayerCollectedPortablePickup = 167,
		CEventNetworkPlayerDroppedPortablePickup = 168,
		CEventNetworkInviteAccepted = 170,
		CEventNetworkInviteConfirmed = 171,
		CEventNetworkInviteRejected = 172,
		CEventNetworkSummo = 173,
		CEventNetworkScriptEvent = 174,
		CEventNetworkSignInStateChanged = 176,
		CEventNetworkSignInChangeActioned = 177,
		CEventNetworkRosChanged = 178,
		CEventNetworkBail = 179,
		CEventNetworkHostMigration = 180,
		CEventNetworkFindSession = 181,
		EventNetworkHostSession = 182,
		CEventNetworkJoinSession = 183,
		CEventNetworkJoinSessionResponse = 184,
		CEventNetworkCheatTriggered = 185,
		CEventNetworkEntityDamage = 186,
		CEventNetworkPlayerArrest = 187,
		CEventNetworkTimedExplosion = 188,
		CEventNetworkPrimaryClanChanged = 189,
		CEventNetworkClanJoined = 190,
		CEventNetworkClanLeft = 191,
		CEventNetworkClanInviteReceived = 192,
		CEventNetworkVoiceSessionStarted = 193,
		CEventNetworkVoiceSessionEnded = 194,
		CEventNetworkVoiceConnectionRequested = 195,
		CEventNetworkVoiceConnectionResponse = 196,
		CEventNetworkVoiceConnectionTerminated = 197,
		CEventNetworkTextMessageReceived = 198,
		CEventNetworkCloudFileResponse = 199,
		CEventNetworkPickupRespawned = 200,
		CEventNetworkPresence_StatUpdate = 201,
		CEventNetworkPedLeftBehind = 202,
		CEventNetwork_InboxMsgReceived = 203,
		CEventNetworkAttemptHostMigration = 204,
		CEventNetworkIncrementStat = 205,
		CEventNetworkSessionEvent = 206,
		CEventNetworkTransitionStarted = 207,
		CEventNetworkTransitionEvent = 208,
		CEventNetworkTransitionMemberJoined = 209,
		CEventNetworkTransitionMemberLeft = 210,
		CEventNetworkTransitionParameterChanged = 211,
		CEventNetworkClanKicked = 212,
		CEventNetworkTransitionStringChanged = 213,
		EventNetworkTransitionGamerInstruction = 214,
		CEventNetworkPresenceInvite = 215,
		EventNetworkPresenceInviteRemoved = 216,
		EventNetworkPresenceInviteReply = 217,
		CEventNetworkCashTransactionLog = 218,
		CEventNetworkClanRankChanged = 219,
		CEventNetworkVehicleUndrivable = 220,
		CEventNetworkPresenceTriggerEvent = 221,
		CEventNetworkEmailReceivedEvent = 222,
		CEventNetworkFollowInviteReceived = 223,
		CEventNetworkSpectateLocal = 225,
		CEventNetworkCloudEvent = 226,
		CEventNetworkShopTransaction = 227,
		CEventNetworkOnlinePermissionsUpdated = 230,
		CEventNetworkSystemServiceEvent = 231,
		CEventNetworkRequestDelay = 232,
		CEventNetworkSocialClubAccountLinked = 233,
		CEventNetworkScAdminPlayerUpdated = 234,
		CEventNetworkScAdminReceivedCash = 235,
		CEventNetworkClanInviteRequestReceived = 236,
		CEventNetworkMarketingEmailReceivedEvent = 237,
		CEventNetworkStuntPerformed = 238,
		CEventNetworkFiredDummyProjectile = 239,
		CEventNetworkPlayerEnteredVehicle = 240,
		CEventNetworkPlayerActivatedSpecialAbility = 241,
		CEventNetworkPlayerDeactivatedSpecialAbility = 242,
		CEventNetworkPlayerSpecialAbilityFailedActivation = 243,
		CEventNetworkFiredVehicleProjectile = 244,
	};
	class CEventNetwork
	{
	public:
		virtual ~CEventNetwork() = default; //0x0000 (0)
		virtual void unk_0008() = 0; //0x0008 (1)
		virtual void unk_0010() = 0; //0x0010 (2)
		virtual eEventNetworkType get_type2() = 0; //0x0018 (3)
		virtual void unk_0020() = 0; //0x0020 (4)
		virtual void unk_0028() = 0; //0x0028 (5)
		virtual bool get_extra_information(void* info_array, int check) = 0; //0x0030 (6)
		virtual void unk_0038() = 0; //0x0038 (7)
	}; //Size: 0x0008
	class netEventMgr;
#pragma pack(push, 1)

	class netGameEvent
	{
	public:
		virtual ~netGameEvent() = default;

		virtual const char* get_name()
		{
			return 0;
		};
		virtual bool is_in_scope(netPlayer* player)
		{
			return 0;
		};
		virtual bool time_to_resend(std::uint32_t time)
		{
			return 0;
		};
		virtual bool can_change_scope()
		{
			return 0;
		};

		virtual void prepare_data(datBitBuffer* buffer, netPlayer* source_player, netPlayer* target_player) {};
		virtual void handle_data(datBitBuffer* buffer, netPlayer* source_player, netPlayer* target_player) {};

		virtual bool decide(netPlayer* source_player, netPlayer* target_player)
		{
			return 0;
		};

		virtual void prepare_reply(datBitBuffer* buffer, netPlayer* reply_player) {};
		virtual void handle_reply(datBitBuffer* buffer, netPlayer* souce_player) {};

		virtual void prepare_extra_data(datBitBuffer* buffer, bool is_reply, netPlayer* player, netPlayer* player2) {};
		virtual void handle_extra_data(datBitBuffer* buffer, bool is_reply, netPlayer* player, netPlayer* player2) {};

	private:
		virtual void unk_0x60() {};
		virtual void unk_0x68() {};
		virtual void unk_0x70() {};
		virtual void unk_0x78() {};

	public:
		virtual bool operator==(netGameEvent const& other)
		{
			return 0;
		};
		virtual bool operator!=(netGameEvent const& other)
		{
			return 0;
		};

		virtual bool must_persist()
		{
			return 0;
		};
		virtual bool must_persist_when_out_of_scope()
		{
			return 0;
		};
		virtual bool has_timed_out()
		{
			return 0;
		};

	public:
		std::uint16_t m_id;   // 0x08
		bool m_requires_reply;// 0x0A
	private:
		char m_padding1[0x05];// 0x0B
	public:
		netPlayer* m_source_player; // 0x10
		netPlayer* m_target_player; // 0x18
		std::uint32_t m_resend_time;// 0x20
	private:
		std::uint16_t m_0x24;// 0x24
		std::uint8_t m_0x26; // 0x26
		std::uint8_t m_0x27; // 0x27
		std::uint32_t m_0x28;// 0x28
		char m_padding2[0x04];
	};
	class hash_list
	{
	public:
		std::uint64_t* list; //0x0000
		std::int32_t capacity; //0x0008
		char pad_000C[4]; //0x000C
		std::int32_t free; //0x0010
		char pad_0014[4]; //0x0014
		std::uint64_t item_size; //0x0018
		char pad_0020[16]; //0x0020
		std::uint32_t* data; //0x0030
		char pad_0038[16]; //0x0038
		std::int32_t occupied; //0x0048
		const std::uint64_t get(std::int32_t index) const {
			if ((this->data[index >> 5] >> (index & 0x1F)) & 1)
				return this->list[index];
			return NULL;
		}
	}; // Size: 0x004C
#pragma pack(pop)
}

namespace Saint {
	class CScriptParticipant
	{
	public:
		char pad_0000[16];                      //0x0000
		class CNetGamePlayer* m_net_game_player;//0x0010
		char pad_0018[2];                       //0x0018
		int16_t m_participant_index;            //0x001A
		char pad_001C[12];                      //0x001C
	};                                          //Size: 0x0028
	static_assert(sizeof(CScriptParticipant) == 0x28);
	class CGameScriptHandler : public rage::scriptHandler
	{
	public:
		CGameScriptId m_script_id;// 0x60
	};

	class CGameScriptHandlerNetwork : public CGameScriptHandler
	{
	public:
		std::uint8_t m_0xA0;       // 0xA0
		std::uint8_t m_0xA1;       // 0xA1
		std::uint8_t m_0xA2;       // 0xA2
		std::uint8_t m_0xA3;       // 0xA3
		std::uint8_t m_num_players;// 0xA4
		std::uint8_t m_0xA5;       // 0xA5
		std::uint8_t m_0xA6;       // 0xA6
		std::uint8_t m_0xA7;       // 0xA7
		std::uint8_t m_0xA8;       // 0xA8
		std::uint8_t m_0xA9;       // 0xA9
		std::uint8_t m_0xAA;       // 0xAA
		std::uint8_t m_0xAB;       // 0xAB
		std::uint8_t m_0xAC;       // 0xAC
		std::uint8_t m_0xAD;       // 0xAD
		std::uint8_t m_0xAE;       // 0xAE
		std::uint8_t m_0xAF;       // 0xAF
	};

	class CGameScriptHandlerNetComponent
	{
	public:
		virtual ~CGameScriptHandlerNetComponent() = default;

		virtual bool _0x08(void*) = 0;

		virtual void _0x10(CNetGamePlayer*) = 0;// creates a scriptId?

		virtual void* player_left(CNetGamePlayer* player) = 0;

		virtual void* send_host_migration_event(CNetGamePlayer* player) = 0;

		virtual void* player_joined(void**, void* msg_ctx) = 0;

		virtual void* player_joined_ack(void**, void* msg_ctx) = 0;

		virtual bool _0x38(void*, void*) = 0;// join_script?

		virtual void* _0x40(void*, void*) = 0;

		virtual void* _0x48(void*, void*, void*) = 0;

		virtual void* _0x50(void*, void*) = 0;

		virtual void* _0x58(void*, void*) = 0;

		virtual void* _0x60(void*, void*) = 0;

		virtual void* _0x68(void*, void*) = 0;

		virtual void _0x70(void*, void*) = 0;

		virtual void _0x78(void*, void*) = 0;

		virtual short _0x80(void*, void*) = 0;

		virtual void* _0x88(void*, void*) = 0;

		virtual void* _0x90(void*, void*) = 0;// HOST_MIGRATION_FAILED

		virtual bool _0x98(void*, void*) = 0;

		virtual void* _0xA0(void*, void*) = 0;

		virtual void* _0xA8(void*, void*) = 0;

		virtual short _0xB0(void*, void*) = 0;

		virtual bool register_host_broadcast_data(void* data, int size, char* a3) = 0;

		virtual bool register_player_broadcast_data(int a1, int size, bool a3) = 0;

		virtual bool _0xC8() = 0;// something to do to joining session

		virtual bool _0xD0() = 0;

		virtual bool add_player_to_script(CNetGamePlayer* player, short* outParticipantID, short* outSlot, int* outFailReason) = 0;

		virtual bool add_player_to_script_internal(CNetGamePlayer* player, short participantID, short slot) = 0;// player aka participant

		virtual bool remove_player_from_script(CNetGamePlayer* player) = 0;

		virtual void* player_left_impl(CNetGamePlayer*, bool) = 0;

		virtual bool do_host_migration(CNetGamePlayer* player, short host_token, bool unk) = 0;// aka _0xF8

		virtual void* leave_from_script() = 0;// calls above function with player = nullptr

		virtual bool _0x108() = 0;

		virtual void* _0x110() = 0;

		virtual bool _0x118() = 0;// related to above function

		CGameScriptHandler* m_script_handler;        //0x0008
		char pad_0010[32];                           //0x0010
		class CScriptParticipant* m_host;            //0x0030
		int16_t m_local_participant_index;           //0x0038
		char pad_003A[6];                            //0x003A
		uint32_t m_participant_bitset;               //0x0040
		char pad_0044[36];                           //0x0044
		class CScriptParticipant* m_participants[32];//0x0068
		char pad_0168[12];                           //0x0168
		int16_t m_num_participants;                  //0x0174
		char pad_0176[28];                           //0x0176
		uint8_t m_host_migration_flags;              //0x0192
		char pad_0193[29];                           //0x0193

		int get_participant_index(CNetGamePlayer* player);
		bool is_player_a_participant(CNetGamePlayer* player);

		inline bool is_local_player_host()
		{
			if (!m_host)
				return true;// or return false?

			return m_host->m_participant_index == m_local_participant_index;
		}

		inline CNetGamePlayer* get_host()
		{
			if (!m_host)
				return nullptr;

			return m_host->m_net_game_player;
		}

		// not 100% foolproof
		inline void block_host_migration(bool toggle)
		{
			if (toggle)
				m_host_migration_flags |= (1 << 7);
			else
				m_host_migration_flags &= ~(1 << 7);
		}

	};//Size: 0x01B0
	static_assert(sizeof(CGameScriptHandlerNetComponent) == 0x1B0);

	class CNetworkObjectMgr;
#pragma pack(push, 8)
	class CPickupCreationDataNode
	{
	public:
		char pad_0000[192]; //0x0000
		bool m_has_placement; //0x00C0
		char pad_00C1[7]; //0x00C1
		uint64_t* unk_struct_00C8; //0x00C8
		uint32_t unk_00D0; //0x00D0
		uint16_t unk_00D4; //0x00D4
		char pad_00D6[66]; //0x00D6
		uint32_t m_pickup_hash; //0x0118
		uint32_t m_amount; //0x011C
		uint32_t m_custom_model; //0x0120
		uint32_t m_life_time; //0x0124
		uint32_t m_weapon_component[11]; //0x0128
		uint32_t m_num_weapon_components; //0x0154
		uint32_t m_tint_index; //0x0158
		bool m_player_gift; //0x015C
		bool unk_015D; //0x015D
		char pad_015E[6]; //0x015E
		uint32_t unk_0164; //0x0164
		bool unk_0168; //0x0168
	}; //Size: 0x0170
	static_assert(sizeof(CPickupCreationDataNode) == 0x170);
#pragma pack(pop)
#ifndef __PE_IMAGE__
#define __PE_IMAGE__
	typedef const IMAGE_NT_HEADERS64 NT64H;
	typedef std::vector<char> bufferVec;

	class PEImage {
	public:

		PEImage();
		~PEImage();

		bool			Load(const std::string& path);

		bool			IsOpenVHookCompatible();

		bool			PatchCompatibility();

	private:

		uint64_t		GetDirectoryAddress(int index);
		uint64_t		RVAToVA(uint32_t rva) const;

		bool			ParsePE();

	private:

		std::string		filePath;
		bufferVec		fileBuffer;
		NT64H* ntHeader = nullptr;
	};
#endif // __PE_IMAGE__
#pragma pack(push, 4)
	class vehicle_item final
	{
	public:
		char m_name[16];
		char m_display_name[32];
		char m_display_manufacturer[32];
		char m_vehicle_class[32];
		std::uint32_t m_hash;
	};
#pragma pack(pop)
	class CScriptedGameEvent : public rage::netGameEvent
	{
	public:
		char m_padding[0x40];     // 0x30
		std::int64_t m_args[54];  // 0x70
		std::uint32_t m_bitset;   // 0x220
		std::uint32_t m_args_size;// 0x224
	};

	class netPlayerData
	{
	public:
		char pad_0000[8]; //0x0000
		int64_t m_rockstar_id_0; //0x0008
		char pad_0010[56]; //0x0010
		uint16_t N000005BF; //0x0048
		char pad_004A[2]; //0x004A
		netAddress m_online_ip; //0x0054
		int16_t m_online_port; //0x0058
		netAddress m_relay_ip; //0x004C
		int32_t m_relay_port; //0x0050
		char pad_005A[6]; //0x005A
		uint32_t m_host_token; //0x0060
		char pad_0064[12]; //0x0064
		int64_t m_rockstar_id; //0x0070
		char pad_0078[12]; //0x0078
		const char* m_name; //0x0084
	}; //Size: 0x0098



	class CNetGamePlayers : public rage::netPlayer
	{
	public:
		char pad_0x0008[0x10]; //0x0008
		std::uint32_t msg_id; // 0x18
		char pad_0x001C[0x4]; //0x001C
		std::int8_t active_id; //0x0020 
		std::int8_t m_player_id; //0x0021 
		char pad_0x0022[0x6E]; //0x0022
		BYTE local_player_check;//0x0090
		char pad_0x00A1[0xF]; //0x0091
		CPlayerInfo* PlayerInfo; //0x00A0

		inline bool is_local_player()
		{
			return local_player_check & 1;
		}
	};

	class CNetworkIncrementStatEvent : public rage::netGameEvent
	{
	public:
		std::uint32_t m_stat;           // 0x30
		std::uint32_t m_amount;// 0x34
	};
	class CFlyingHandlingData : public CBaseSubHandlingData {
	public:
		char pad_0x0000[0x8]; //0x0000
		float fThrust; //0x0008 
		float fThrustFallOff; //0x000C 
		float fThrustVectoring; //0x0010 
		char pad_0x0014[0x8]; //0x0014
		float fYawMult; //0x001C 
		float fYawStabilise; //0x0020 
		float fSideSlipMult; //0x0024 
		char pad_0x0028[0x4]; //0x0028
		float fRollMult; //0x002C 
		float fRollStabilise; //0x0030 
		float N000026D3; //0x0034 
		float fPitchMult; //0x0038 
		float fPitchStabilise; //0x003C 
		char pad_0x0040[0x4]; //0x0040
		float fFormLiftMult; //0x0044 
		float fAttackLiftMult; //0x0048 
		float fAttackDiveMult; //0x004C 
		float fGearDownDragV; //0x0050 
		float fGearDownLiftMult; //0x0054 
		float fWindMult; //0x0058 
		float fMoveRes; //0x005C 
		rage::fvector3 vecTurnRes; //0x0060 
		char pad_0x006C[0x4]; //0x006C
		rage::fvector3 vecSpeedRes; //0x0070 
		char pad_0x007C[0x4]; //0x007C
		float fGearDoorFrontOpen; //0x0080 
		float fGearDoorRearOpen; //0x0084 
		float fGearDoorRearOpen2; //0x0088 
		float fGearDoorRearMOpen; //0x008C 
		float fTurublenceMagnitudeMax; //0x0090 
		float fTurublenceForceMulti; //0x0094 
		float fTurublenceRollTorqueMulti; //0x0098 
		float fTurublencePitchTorqueMulti; //0x009C 
		float fBodyDamageControlEffectMult; //0x00A0 
		float fInputSensitivityForDifficulty; //0x00A4 
		float fOnGroundYawBoostSpeedPeak; //0x00A8 
		float fOnGroundYawBoostSpeedCap; //0x00AC 
		float fEngineOffGlideMulti; //0x00B0 

	}; //Size=0x00B4

	class CBoatHandlingData : public CBaseSubHandlingData {
	public:
		char pad_0x0000[0x8]; //0x0000
		float fBoxFrontMult; //0x0008 
		float fBoxRearMult; //0x000C 
		float fBoxSideMult; //0x0010 
		float fSampleTop; //0x0014 
		float fSampleBottom; //0x0018 
		float N000028C4; //0x001C 
		float fAquaplaneForce; //0x0020 
		float fAquaplanePushWaterMult; //0x0024 
		float fAquaplanePushWaterCap; //0x0028 
		float fAquaplanePushWaterApply; //0x002C 
		float fRudderForce; //0x0030 
		float fRudderOffsetSubmerge; //0x0034 
		float fRudderOffsetForce; //0x0038 
		float fRudderOffsetForceZMult; //0x003C 
		float fWaveAudioMult; //0x0040 
		float N000028CE; //0x0044 
		float N0000283E; //0x0048 
		float N000028D0; //0x004C 
		rage::fvector3 vecMoveResistance; //0x0050 
		float N000028D4; //0x005C 
		rage::fvector3 vecTurnResistance; //0x0060 
		float N000028D8; //0x006C 
		float fLook_L_R_CamHeight; //0x0070 
		float fDragCoefficient; //0x0074 
		float fKeelSphereSize; //0x0078 
		float fPropRadius; //0x007C 
		float fLowLodAngOffset; //0x0080 
		float fLowLodDraughtOffset; //0x0084 
		float fImpellerOffset; //0x0088 
		float fImpellerForceMult; //0x008C 
		float fDinghySphereBuoyConst; //0x0090 
		float fProwRaiseMult; //0x0094 

	}; //Size=0x0098

	class CBikeHandlingData : public CBaseSubHandlingData {
	public:
		char pad_0x0000[0x8]; //0x0000
		float fLeanFwdCOMMult; //0x0008 
		float fLeanFwdForceMult; //0x000C 
		float fLeanBakCOMMult; //0x0010 
		float fLeanBakForceMult; //0x0014 
		float fMaxBankAngle; //0x0018 
		char pad_0x001C[0x4]; //0x001C
		float fFullAnimAngle; //0x0020 
		float fDesLeanReturnFrac; //0x0024 
		float fStickLeanMult; //0x0028 
		float fBrakingStabilityMult; //0x002C 
		float fInAirSteerMult; //0x0030 
		float fWheelieBalancePoint; //0x0034 
		float fStoppieBalancePoint; //0x0038 
		float fWheelieSteerMult; //0x003C 
		float fRearBalanceMult; //0x0040 
		float fFrontBalanceMult; //0x0044 
		float fBikeGroundSideFrictionMult; //0x0048 
		float fBikeWheelGroundSideFrictionMult; //0x004C 
		float fBikeOnStandLeanAngle; //0x0050 c
		float fBikeOnStandSteerAngle; //0x0054 
		float fJumpForce; //0x0058 

	}; //Size=0x005C


	
	class CPickup {
	public:
		char pad_0000[48]; //0x0000
		class CNavigation* m_navigation; //0x0030
		char pad_0038[88]; //0x0083
		rage::fvector3 m_position; //0x0090
		char pad_009C[1012]; //0x009C
		int32_t m_money; //0x0490
		char pad_0484[260]; //0x0484
	};//Size: 0x0588
	class CPickupHandle {
	public:
		CPickup* m_pointer; //0x0000 
		int32_t m_handle; //0x0008 
		char pad_0x000C[4]; //0x000C
	}; //Size: 0x0010
	class CPickupList {
	public:
		CPickupHandle m_array[73]; //0x0000 
		uintptr_t addr(int index) {
			uintptr_t addr = (uintptr_t)static_cast<void*>(this) + (index * 0x10);
			return *(uintptr_t*)addr;
		}
	}; //Size=0x0490
	class CPickupInterface {
	public:
		char pad_0x0000[0x100]; //0x0000
		CPickupList* m_list; //0x0100 
		int32_t m_size; //0x0108 
		int32_t m_count; //0x0110 
		CPickup* get(const int& index) {
			if (index < m_size)
				return m_list->m_array[index].m_pointer;
			return nullptr;
		}
	}; //Size: 0x0114
	class CObjectHandle {
	public:
		CObject* m_pointer; //0x0000
		int32_t m_handle; //0x0008
		char pad_000C[4]; //0x000C
	}; //Size: 0x0010
	static_assert(sizeof(CObjectHandle) == 0x10);
	class CObjectList {
	public:
		CObjectHandle m_array[2300]; //0x0000
		uintptr_t addr(int index) {
			uintptr_t addr = (uintptr_t)static_cast<void*>(this) + (index * 0x10);
			return *(uintptr_t*)addr;
		}
	}; //Size: 0x8FC0
	class CObjectInterface {
	public:
		char pad_0000[344]; //0x0000
		CObjectList* m_list; //0x0158
		int32_t m_size; //0x0160
		char pad_0164[4]; //0x0164
		int32_t m_count; //0x0168
		CObject* get(const int& index) {
			if (index < m_size)
				return m_list->m_array[index].m_pointer;
			return nullptr;
		}
	}; //Size: 0x016C
	class CPedHandle {
	public:
		CPed* m_pointer; //0x0000
		int32_t m_handle; //0x0008
		char pad_000C[4]; //0x000C
	}; //Size: 0x0010
	static_assert(sizeof(CPedHandle) == 0x10);
	class CPedList {
	public:
		CPedHandle m_array[256]; //0x0000
		uintptr_t addr(int index) {
			uintptr_t addr = (uintptr_t)static_cast<void*>(this) + (index * 0x10);
			return *(uintptr_t*)addr;
		}
	}; //Size: 0x1000
	class CPedInterface {
	public:
		char pad_0000[256]; //0x0000
		CPedList* m_list; //0x0100
		int32_t m_size; //0x0108
		char pad_010C[4]; //0x010C
		int32_t m_count; //0x0110
		CPed* get(const int& index) {
			if (index < m_size)
				return m_list->m_array[index].m_pointer;
			return nullptr;
		}
	}; //Size: 0x0114
	class CVehicleHandle {
	public:
		class CVehicle* m_pointer; //0x0000
		int32_t m_handle; //0x0008
		char pad_000C[4]; //0x000C
	}; //Size: 0x0010
	static_assert(sizeof(CVehicleHandle) == 0x10);
	class CVehicleList {
	public:
		CVehicleHandle m_array[300]; //0x0000
		uintptr_t addr(int index) {
			uintptr_t addr = (uintptr_t)static_cast<void*>(this) + (index * 0x10);
			return *(uintptr_t*)addr;
		}
	}; //Size: 0x12C0
	class CVehicleInterface {
	public:
		char pad_0000[384]; //0x0000
		CVehicleList* m_list; //0x0180
		int32_t m_size; //0x0188
		char pad_018C[4]; //0x018C
		int32_t m_count; //0x0190
		CVehicle* get(const int& index) {
			if (index < m_size)
				return m_list->m_array[index].m_pointer;
			return nullptr;
		}
	}; //Size: 0x0194
	class CCameraInterface {
	public:
		char pad_0x0000[1032]; //0x0000
	}; //Size: 0x0408
	class CReplayInterface {
	public:
		char pad_0000[8]; //0x0000
		CCameraInterface* m_camera_interface; //0x0008
		CVehicleInterface* m_vehicle_interface; //0x0010
		CPedInterface* m_ped_interface; //0x0018
		CPickupInterface* m_pickup_interface; //0x0020 
		CObjectInterface* m_object_interface; //0x0028
		char pad_0030[16]; //0x0030
	}; //Size: 0x0040

}