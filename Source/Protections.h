#pragma once
#include "Render.h"
#include "Enums.h"
#include "ScriptEventClasses.h"
namespace Saint {
	
	class Crash222 {
	public:
		bool loading_screen = true;
		bool rope = true;
		bool groupoverride = true;
		bool invalidworldstate = true;
		bool task = true;
		bool weapon = true;
		bool fragment = true;
		bool train = true;
		bool entity = true;
		bool object = true;
		bool player = true;
		bool ped = true;
		bool vehicle = true;
		bool invalid_script_entity = true;
	};
	class GameEvents {
	public:
		bool remove_sticky_bomb = false;
		bool request_map_pickup = true;
		bool give_pickup_rewards = true;
		bool ragdoll_request = true;
		bool remove_weapon = true;
		bool remove_all_weapons = true;
		bool particle_spam = true;
		bool freeze = true;
		bool give_weapons = true;
		bool fire_event = true;
		bool explosion = true;
		bool alter_wanted_level = true;
		bool play_sound = true;
		bool request_control = true;
		bool request_pickup = true;
		bool clear_area = true;
		bool weapon_damage = false;
		bool vehicle_component_control = false;
		bool chnage_radio_station = false;
		bool car_horn = true;
		bool vote_kick = true;
		bool blow_up_vehicle = true;
		
	};
	class ScriptEvents {
	public:
		bool bounty = false;
		bool globals = true;
		bool vehicle_kick = true;
		bool text_messages = true;
		bool notifications = true;
		bool destroy_personal_vehicle = true;
		bool ceo_events = true;
		bool rotate_cam = true;
		bool transaction_error = true;
		bool tutorial = true;
	};
	class Entites {
	public:
		bool cage = false;
		bool invalid_pickups = true;
		bool money_bags = false;
		void init() {
			
		}
	};
	//fortnier, // IT COULD GET FUCKING HECTIC
	
	class eventHandler {
	public:
		eventHandler(int64_t m_hash, std::string m_name, bool* m_toggle, std::function<void()> m_action = [] {}) {
			hash = m_hash;
			name = m_name;
			toggled = m_toggle;
			action = m_action;
		}
	public:
		std::string name;
		int64_t hash;
		bool* toggled;
		std::function<void()> action = [] {};
	};
	class eventHandler2 {
	public:
		eventHandler2(int64_t m_hash, std::string m_name, bool m_block, bool m_notify, bool m_log, bool m_allow_from_friends) {
			hash = m_hash;
			name = m_name;
			block = m_block;
			notify = m_notify;
			log = m_log;
			allow_from_friends = m_allow_from_friends;
		}
	public:
		std::string name;
		int64_t hash;
		bool block;
		bool notify;
		bool log;
		bool allow_from_friends;
	};
	class Reactions {
	public:
		const char* type[3] = { "None", "Cage", "Kick"};
		int type_2 = 0;
	};
	class Protections {
	public:
		
		Reactions reaction;
		Crash222 Crashes;
		GameEvents GameEvents;
		ScriptEvents ScriptEvents;
		Entites Entities;
		
		bool crash_blocked = false;
		void push_notification(const char* body) {


			Noti::InsertNotification({ ImGuiToastType_None, 4000, body });
		}
		void push_notification2(const char* body) {

			if (!crash_blocked) {
				Noti::InsertNotification({ ImGuiToastType_None, 4000, body });
				crash_blocked = true;
			}
		}
		bool send_to_location = true;
		bool mc_teleport = true;
		bool sound_spam = true;
		bool block_reports = false;
		//teleports
		bool teleport = true;
		bool Interior = true;
		bool cayo_perico = true;
		bool warehouse = true;
		bool sms_with_attachment = true;
		bool mission = true;
		//ceo
		bool ceo_kick = true;
		bool ceo_ban = true;
		bool ceo_money = true;
		bool ceo_raid = true;
		//kick
		bool kick = true;
		//Activity
		bool activity = true;

		bool exclude_self = true;
		bool exclude_friends = false;

		//Misc
		
		//Notifcations
		bool regular_noti = true;
		bool moneybanked = true;
		bool moneystolen = true;
		bool moneyremoved = true;

		const char* types[4] = { "Block", "Notify", "Log", "Allow From Friends" };
		std::size_t data;
		std::size_t data2;
		
	};
	inline Protections protections;
	
	inline std::string selected_name;
	inline std::vector<eventHandler2> gameEvents = {
		{ -1603050746, "Vehicle Kick", vehicle_kick.block, vehicle_kick.notify, vehicle_kick.log, vehicle_kick.allow_from_friends},
		{
			ceo_kick.hash,
			"CEO Kick",
			ceo_kick.block,
			ceo_kick.notify,
			ceo_money.log,
			ceo_kick.allow_from_friends
		},
		{ ceo_ban.hash, "CEO Ban", ceo_ban.block,ceo_ban.notify,ceo_ban.log,ceo_ban.allow_from_friends},
		{ 
			ceo_money.hash, 
			"CEO Money", 
			ceo_money.block,
			ceo_money.notify,
			ceo_money.log,
			ceo_money.allow_from_friends
		},
		{
			ceo_raid.hash,
			"CEO Raid",
			ceo_raid.block,
			ceo_raid.notify,
			ceo_raid.log,
			ceo_raid.allow_from_friends
		},
		{
			give_coll.hash,
			"Give Collectible",
			give_coll.block,
			give_coll.notify,
			give_coll.log,
			give_coll.allow_from_friends
		},
		{
			clear_wanted_level.hash,
			"Clear Wanted Level",
			clear_wanted_level.block,
			clear_wanted_level.notify,
			clear_wanted_level.log,
			clear_wanted_level.allow_from_friends
		},

		{
			force_mission.hash,
			"Force Mission",
			force_mission.block,
			force_mission.notify,
			force_mission.log,
			force_mission.allow_from_friends
		},
		{
			script_begin.hash,
			"Script Begin",
			script_begin.block,
			script_begin.notify,
			script_begin.log,
			script_begin.allow_from_friends
		},
		{
			script_proceed.hash,
			"Script Proceed",
			script_proceed.block,
			script_proceed.notify,
			script_proceed.log,
			script_proceed.allow_from_friends
		},
		{
			script_proceed.hash,
			"Script Proceed",
			script_proceed.block,
			script_proceed.notify,
			script_proceed.log,
			script_proceed.allow_from_friends
		},
		{
			destroy_personal_vehicle.hash,
			"Destroy Personal Vehicle",
			destroy_personal_vehicle.block,
			destroy_personal_vehicle.notify,
			destroy_personal_vehicle.log,
			destroy_personal_vehicle.allow_from_friends
		},
		{
			personal_veh_destroyed.hash,
			"Destroy Personal Vehicle 2",
			personal_veh_destroyed.block,
			personal_veh_destroyed.notify,
			personal_veh_destroyed.log,
			personal_veh_destroyed.allow_from_friends
		},
		{
			crash.hash,
			"Crash",
			crash.block,
			crash.notify,
			crash.log,
			crash.allow_from_friends
		},
		{
			crash2.hash,
			"Crash 2",
			crash2.block,
			crash2.notify,
			crash2.log,
			crash2.allow_from_friends
		},
		{
			crash3.hash,
			"Crash 3",
			crash3.block,
			crash3.notify,
			crash3.log,
			crash3.allow_from_friends
		},
		
		{
			gta_banner.hash,
			"Banner",
			gta_banner.block,
			gta_banner.notify,
			gta_banner.log,
			gta_banner.allow_from_friends
		},
		{
			off_radar.hash,
			"Off The Radar",
			off_radar.block,
			off_radar.notify,
			off_radar.log,
			off_radar.allow_from_friends
		},
		{
			teleport2.hash,
			"Teleport",
			teleport2.block,
			teleport2.notify,
			teleport2.log,
			teleport2.allow_from_friends
		},
				{
			mc_teleport.hash,
			"Teleport To MC Bike",
			mc_teleport.block,
			mc_teleport.notify,
			mc_teleport.log,
			mc_teleport.allow_from_friends
				},
				{
			tp_to_warehouse.hash,
			"Teleport To Warehouse",
			tp_to_warehouse.block,
			tp_to_warehouse.notify,
			tp_to_warehouse.log,
			tp_to_warehouse.allow_from_friends
				},
				{
			send_to_cayo_perico.hash,
			"Teleport To Cayo Perico",
			send_to_cayo_perico.block,
			send_to_cayo_perico.notify,
			send_to_cayo_perico.log,
			send_to_cayo_perico.allow_from_friends
				},
				{
			send_to_cutscene.hash,
			"Start Cutscene",
			send_to_cutscene.block,
			send_to_cutscene.notify,
			send_to_cutscene.log,
			send_to_cutscene.allow_from_friends
				},
				{
			sound_spam.hash,
			"Sound Spam",
			sound_spam.block,
			sound_spam.notify,
			sound_spam.log,
			sound_spam.allow_from_friends
				},
				{
			t_error.hash,
			"Transaction Error",
			t_error.block,
			t_error.notify,
			t_error.log,
			t_error.allow_from_friends
				},
				{
			spectate.hash,
			"Spectate",
			spectate.block,
			spectate.notify,
			spectate.log,
			spectate.allow_from_friends
				},
				{
			noti.hash,
			"Notification",
			noti.block,
			noti.notify,
			noti.log,
			noti.allow_from_friends
				},
				{
			money_banked.hash,
			"Money Banked",
			money_banked.block,
			money_banked.notify,
			money_banked.log,
			money_banked.allow_from_friends
				},
				{
			money_removed.hash,
			"Money Removed",
			money_removed.block,
			money_removed.notify,
			money_removed.log,
			money_removed.allow_from_friends
				},
				{
			money_stolen.hash,
			"Money Stolen",
			money_stolen.block,
			money_stolen.notify,
			money_stolen.log,
			money_stolen.allow_from_friends
				},
				
				{
			sms2.hash,
			"Text Message (Label)",
			sms2.block,
			sms2.notify,
			sms2.log,
			sms2.allow_from_friends
				},
				{
			tse_command.hash,
			"Command",
			tse_command.block,
			tse_command.notify,
			tse_command.log,
			tse_command.allow_from_friends
				},
				{
			rotate_cam.hash,
			"Rotate Camera",
			rotate_cam.block,
			rotate_cam.notify,
			rotate_cam.log,
			rotate_cam.allow_from_friends
				},
				{
			int_control.hash,
			"Send To Interior",
			int_control.block,
			int_control.notify,
			int_control.log,
			int_control.allow_from_friends
				},
				{
			kick_from_int.hash,
			"Kick From Interior",
			kick_from_int.block,
			kick_from_int.notify,
			kick_from_int.log,
			kick_from_int.allow_from_friends
				},
				{
			start_activ.hash,
			"Start Activity ",
			start_activ.block,
			start_activ.notify,
			start_activ.log,
			start_activ.allow_from_friends
				},
				{
			mark_as_beast.hash,
			"Beast",
			mark_as_beast.block,
			mark_as_beast.notify,
			mark_as_beast.log,
			mark_as_beast.allow_from_friends
				},
				{
			network_bail.hash,
			"Bail",
			network_bail.block,
			network_bail.notify,
			network_bail.log,
			network_bail.allow_from_friends
				},



	};
	
}