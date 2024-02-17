#pragma once

namespace Saint {
	class VehicleKick {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
	};
	inline VehicleKick vehicle_kick;
	class Bounty {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::Bounty;
	};
	inline Bounty bounty;
	class CeoBan {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::CeoBan;
	};
	inline CeoBan ceo_ban;
	class CeoKick {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::CeoKick;
	};
	inline CeoKick ceo_kick;
	class CeoMoney {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::CeoMoney;
	};
	inline CeoMoney ceo_money;
	class ClearWantedLevel {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::ClearWantedLevel;
	};
	inline ClearWantedLevel clear_wanted_level;
	class ForceMission {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::ForceMission;
	};
	inline ForceMission force_mission;
	class GiveCollectible {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::GiveCollectible;
	};
	inline GiveCollectible give_coll;
	class GtaBanner {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::GtaBanner;
	};
	inline GtaBanner gta_banner;
	class NetworkBail {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::NetworkBail;
	};
	inline NetworkBail network_bail;
	class PersonalVehicleDestroyed {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::PersonalVehicleDestroyed;
	};
	inline PersonalVehicleDestroyed  personal_veh_destroyed;
	class RemoteOffradar {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::RemoteOffradar;
	};
	inline RemoteOffradar off_radar;
	class SendToCutscene {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::SendToCutscene;
	};
	inline SendToCutscene send_to_cutscene;
	class SendToCayoPerico {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::SendToCayoPerico;
	};
	inline SendToCayoPerico send_to_cayo_perico;
	class SendToLocation {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::SendToLocation;
	};
	inline SendToLocation send_to_location;
	class SoundSpam {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::SoundSpam;
	};
	inline SoundSpam sound_spam;
	class Spectate {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::Spectate;
	};
	inline Spectate spectate;
	class Teleport2 {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::Teleport;
	};
	inline Teleport2 teleport2;
	class TeleportToWarehouse {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::TeleportToWarehouse;
	};
	inline TeleportToWarehouse tp_to_warehouse;
	class TransactionError {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::TransactionError;
	};
	inline TransactionError t_error;
	class MCTeleport {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::MCTeleport;
	};
	inline MCTeleport  mc_teleport;
	class StartActivity {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::StartActivity;
	};
	inline StartActivity  start_activ;
	class MarkPlayerAsBeast {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::MarkPlayerAsBeast;
	};
	inline MarkPlayerAsBeast  mark_as_beast;
	class KickFromInterior {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::KickFromInterior;
	};
	inline KickFromInterior  kick_from_int;
	class InteriorControl {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::InteriorControl;
	};
	inline InteriorControl int_control;
	
	class SendTextLabelSMS {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::SendTextLabelSMS;
	};
	inline SendTextLabelSMS sms2;
	class Crash {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::Crash;
	};
	inline Crash crash;
	class Crash2 {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::Crash2;
	};
	inline Crash2 crash2;
	class Crash3 {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::Crash3;
	};
	inline Crash3 crash3;
	class TSECommand {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::TSECommand;
	};
	inline TSECommand tse_command;
	class TSECommandRotateCam {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::TSECommandRotateCam;
	};
	inline TSECommandRotateCam rotate_cam;
	class Notification {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::Notification;
	};
	inline Notification noti;
	class NotificationMoneyBanked {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::NotificationMoneyBanked;
	};
	inline NotificationMoneyBanked  money_banked;
	class NotificationMoneyRemoved {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::NotificationMoneyRemoved;
		
	};
	inline NotificationMoneyRemoved  money_removed;
	class NotificationMoneyStolen {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::NotificationMoneyStolen;
	};
	inline NotificationMoneyStolen  money_stolen;
	class DestroyPersonalVehicle {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::DestroyPersonalVehicle;
	};
	inline DestroyPersonalVehicle destroy_personal_vehicle;
	class TriggerCEORaid {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::TriggerCEORaid;
	};
	inline TriggerCEORaid  ceo_raid;
	class StartScriptBegin {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::StartScriptBegin;
	};
	inline StartScriptBegin  script_begin;
	class StartScriptProceed {
	public:
		bool block;
		bool notify = false;
		bool log = false;
		bool allow_from_friends = false;
		int64_t hash = (int64_t)eRemoteEvent::StartScriptProceed;
	};
	inline StartScriptProceed  script_proceed;
}
