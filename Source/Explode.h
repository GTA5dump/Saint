#pragma once
#include "Natives.hpp"
namespace Saint {
	class Ex_Settings {
	public:
		bool sound = true;
		bool looped = false;
		bool invisible = false;
		float camera_shake = 0.0f;
		float damage_scale = 100.0f;
		bool blame = false;
		const char* explosions[81] = { "Grenade", "Grenade (Launcher)", "Sticky Bomb", "Molotov", "Rocket", "Tank Shell", "HI Octane", "Car", "Plane", "Gas Pump", "Bike", "Steam", "Flame", "Water", "Gas", "Boat", "Ship Destroy", "Truck", "Bullet", "Smoke", "Smoke 2", "BZ Gas", "Flare",
			"Unkown", "Extinguisher", "Unkown", "Train", "Barrel", "Propane", "Blimp", "Flame 2", "Tanker", "Plane Rocket", "Vehicle Bullet", "Gas Tank", "Bird Crap", "Railgun", "Blimp 2", "Firework", "Snowball", "Proximity Mine", "Valkyrie Cannon", "Air Defense", "Pipe Bomb",
			"Vehicle Mine", "Explosive Ammo", "APC Shell", "Cluster Bomb", "Gas Bomb", "Incendiary Bomb", "Bomb", "Torpedo", "Torpedo (Underwater)", "Bombushka Cannon", "Cluster Bomb 2", "Hunter Barrage", "Hunter Cannon", "Rouge Cannon", "Underwater Mine", "Orbital Cannon",
			"Bomb (Wide)", "Explosive Ammo (Shotgun)", "Oppressor MK II", "Kinetic Mortar", "Kinetic Vehicle Mine", "EMP Vehicle Mine", "Spike Vehicle Mine", "Slick Vehicle Mine", "Tar Vehicle Mine", "Script Drone", "Up-n-Atomizer", "Burried Mine", "Script Missle", "RC Tank Rocket",
			"Bomb (Water)", "Bomb (Water 2)", "Flash Grenade", "Stun Grenade", "Script Missle (Large)", "Submarine (Big)", "EMP Launcher" };
		std::size_t data = 0;
		int blamed_person = 0;
	};
	class Ex_Excludes {
	public:
		bool friends = true;
		bool self = false;
		
	};
	class Explode {
	public:
		Ex_Settings settings;
		Ex_Excludes excludes;
		void add(Ped ped, NativeVector3 vec, int explosionType, float damageScale, BOOL isAudible, BOOL isInvisible, float cameraShake) {
			*(unsigned short*)g_GameFunctions->m_owned_explosion = 0xE990;
			FIRE::ADD_OWNED_EXPLOSION(ped, vec.x, vec.y, vec.z, explosionType, damageScale, isAudible, isInvisible, cameraShake);
			*(unsigned short*)g_GameFunctions->m_owned_explosion = 0x850F;
		}
		void once() {
			for (std::uint32_t i = 0; i < PLAYER::GET_NUMBER_OF_PLAYERS(); ++i) {
				if (excludes.friends) {
					int netHandle[13];
					NETWORK::NETWORK_HANDLE_FROM_PLAYER(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), netHandle, 13);
					if (!NETWORK::NETWORK_IS_FRIEND(&netHandle[0])) {
						if (settings.blame) {
							NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
							add(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(settings.blamed_person), c, settings.data, settings.damage_scale, settings.sound, settings.invisible, settings.camera_shake);
						}
						else {
							NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
							FIRE::ADD_EXPLOSION(c.x, c.y, c.z, settings.data, settings.damage_scale, settings.sound, settings.invisible, settings.camera_shake, false);
						}
					}
				}
				if (excludes.self) {
					if (i != PLAYER::PLAYER_ID()) {
						if (settings.blame) {
							NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
							add(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(settings.blamed_person), c, settings.data, settings.damage_scale, settings.sound, settings.invisible, settings.camera_shake);
						}
						else {
							NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
							FIRE::ADD_EXPLOSION(c.x, c.y, c.z, settings.data, settings.damage_scale, settings.sound, settings.invisible, settings.camera_shake, false);
						}
					}
				}
				if (!excludes.self && !excludes.friends) {
					if (settings.blame) {
						NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
						add(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(settings.blamed_person), c, settings.data, settings.damage_scale, settings.sound, settings.invisible, settings.camera_shake);
					}
					else {
						NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
						FIRE::ADD_EXPLOSION(c.x, c.y, c.z, settings.data, settings.damage_scale, settings.sound, settings.invisible, settings.camera_shake, false);
					}
				}
			}
		}
		void init() {
			if (settings.looped) {
				for (std::uint32_t i = 0; i < PLAYER::GET_NUMBER_OF_PLAYERS(); ++i) {
					if (excludes.friends) {
						int netHandle[13];
						NETWORK::NETWORK_HANDLE_FROM_PLAYER(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), netHandle, 13);
						if (!NETWORK::NETWORK_IS_FRIEND(&netHandle[0])) {
							if (settings.blame) {
								NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
								add(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(settings.blamed_person), c, settings.data, settings.damage_scale, settings.sound, settings.invisible, settings.camera_shake);
							}
							else {
								NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
								FIRE::ADD_EXPLOSION(c.x, c.y, c.z, settings.data, settings.damage_scale, settings.sound, settings.invisible, settings.camera_shake, false);
							}
						}
					}
					if (excludes.self) {
						if (i != PLAYER::PLAYER_ID()) {
							if (settings.blame) {
								NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
								add(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(settings.blamed_person), c, settings.data, settings.damage_scale, settings.sound, settings.invisible, settings.camera_shake);
							}
							else {
								NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
								FIRE::ADD_EXPLOSION(c.x, c.y, c.z, settings.data, settings.damage_scale, settings.sound, settings.invisible, settings.camera_shake, false);
							}
						}
					}
					if (!excludes.self && !excludes.friends) {
						if (settings.blame) {
							NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
							add(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(settings.blamed_person), c, settings.data, settings.damage_scale, settings.sound, settings.invisible, settings.camera_shake);
						}
						else {
							NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
							FIRE::ADD_EXPLOSION(c.x, c.y, c.z, settings.data, settings.damage_scale, settings.sound, settings.invisible, settings.camera_shake, false);
						}
					}
				}
			}
		}
	};
	
}
