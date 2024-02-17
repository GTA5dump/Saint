#include <memory>
#include "../Script.hpp"
#include "../Types.hpp"
#include "../Natives.hpp"

namespace SessionOptions {
	void Loop();

	extern bool spectate[32];
	void Spectate(int target);

	void TeleportToPlayer(int player);
	void TeleportInsideVehicle(int player);

	void CloneVehicle(int ped);
	void MaxVehicle(int player);
	void FixVehicle(int player);
	void PopTires(int target);
	void ExplodeVehicle(int players);
	void VehicleKick(int player);
	void StopVehicle(int player);
	void LaunchVehicle(int player);
	void KillVehicleEngine(int player);

	void SendFriendRequest(int player);
	void ShowProfile(int player);

	void EnterSession(int type);
	void LeaveGTAOnline();

	extern bool bypasschatrestrictions;
	void BypassChatRestrictions();

	//PROTECTIONS
	extern bool freezeprotection;
	void FreezeProtection();
	extern bool cloneprotection;
	void CloneProtection();

	//CHAT COMMANDS
	extern bool ChatCommands, /*SlashVehicle, SlashOtr, SlashSnow, SlashWeapons, SlashNeverWanted, */SlashClone;
	std::int32_t getPlayerId(const char* name);
}