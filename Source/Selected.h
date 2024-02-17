#pragma once
#include "Flash Blip.h"
#include "OTR.h"
#include "Kick.h"
#include "Notifications.h"
#include "All Players.h"
namespace Saint {
    class ExplosiveAmmo2 {
    public:
        bool enabled = false;
        bool invisible = false;
        bool sound = true;
        float damage = 1.0f;
        float camera_shake = 0.0f;
        
        std::size_t explode_int = 0;
        void add(Ped ped, float x, float y, float z, int explosionType, float damageScale, BOOL isAudible, BOOL isInvisible, float cameraShake) {
            *(unsigned short*)g_GameFunctions->m_owned_explosion = 0xE990;
            FIRE::ADD_OWNED_EXPLOSION(ped, x, y, z, explosionType, damageScale, isAudible, isInvisible, cameraShake);
            *(unsigned short*)g_GameFunctions->m_owned_explosion = 0x850F;
        }
        void init() {
            if (enabled) {
                if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer)))
                {
                    float Tmp[6];
                    WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), (NativeVector3*)Tmp);
                    if (Tmp[0] != 0 || Tmp[2] != 0 || Tmp[4] != 0) {
                       add(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), Tmp[0], Tmp[2], Tmp[4], explode_int, damage, sound, invisible, camera_shake);

                        
                    }
                }
            }
        }
    };
    class BlockActions {
    public:
        bool aiming = false;
        bool shooting = false;
        void init() {
            if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
                if (shooting) {
                    if (PED::IS_PED_SHOOTING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer))) {
                        g_GameFunctions->m_clear_ped_tasks_network(all_players.get_ped(g_SelectedPlayer), true);
                    }
                }
               
            }
           
        }
    };
	class GetSelected {
	public:
       const char* PlaySounds[3][4] = {
        { "Orbital Cannon", "Beep", "Yacht Horn", "Garage Door"},
        { "DLC_XM_Explosions_Orbital_Cannon", "Hack_Success", "Horn", "Garage_Door"},
        { 0, "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS", "DLC_Apt_Yacht_Ambient_Soundset", "DLC_HEISTS_GENERIC_SOUNDS"},
        };
        void PlaySound22(const char* first, const char* second) {
            NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
            AUDIO::PLAY_SOUND_FROM_COORD(AUDIO::GET_SOUND_ID(), first, coords.x, coords.y, coords.z, second, true, 0, true);
        }
        void PlaySound22(const char* first, int second) {
            NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
            AUDIO::PLAY_SOUND_FROM_COORD(AUDIO::GET_SOUND_ID(), first, coords.x, coords.y, coords.z, PlaySounds[2][0], true, 0, true);
        }
        bool looped_sound = false;
        ExplosiveAmmo2 explosiveAmmo;
		FlashBlip flash_blip;
		OTR otr;
		Kicks events;
        int wanted_level = 0;
        bool freeze = false;
        std::string buffer;
        std::uint64_t int_id = 0;
        BlockActions block_actions;
        
        uint8_t get_id() const
        {

            return g_GameVariables->m_net_game_player(g_SelectedPlayer) == nullptr ? -1 : g_GameVariables->m_net_game_player(g_SelectedPlayer)->m_player_id;
        }
        void bounty(int value)
        {
            const size_t arg_count = 22;
            int64_t args[arg_count] =
            {
                (int64_t)1459520933,
                PLAYER::PLAYER_ID(),
                get_id(),
                1,
                value,
                0,
                1,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                *script_global(1923597).at(9).as<int64_t*>(),
                *script_global(1923597).at(10).as<int64_t*>()
            };

            g_GameFunctions->m_trigger_script_event(1, args, arg_count, 1 << get_id());
        }
        void send_to_int(const std::vector<std::uint64_t>& _args) {
            if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
                float max = 1e+38f;
                auto coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(all_players.get_id(g_SelectedPlayer)), FALSE);
                const size_t arg_count = 15;
                int64_t args[arg_count] =
                {
                    (int64_t)1727896103,
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

                g_GameFunctions->m_trigger_script_event(1, args, arg_count, 1 << all_players.get_id(g_SelectedPlayer));
            }
            else {
                g_NotificationManager->add("Please start a session.");

            }
           
        }
        void send_to_tutorial(int scriptId) {
           
        }
        const char* kick_type[2] = { "Smooth", "Rough" };
        std::size_t pos;
        inline bool ChangeNetworkObjectOwner(std::int32_t script_index, CNetGamePlayer* owner)
        {
            if (*g_GameVariables->m_is_session_started && !ENTITY::IS_ENTITY_A_PED(script_index))
            {
                std::uint64_t NetworkObjectMgrInterface = *(std::uint64_t*)(g_GameFunctions->m_NetworkObjectMgrInterface);
                if (NetworkObjectMgrInterface == NULL)
                    return false;

                if (!ENTITY::DOES_ENTITY_EXIST(script_index))
                    return false;

                std::uint64_t Entity = g_GameFunctions->m_GetEntityFromScript(script_index);
                if (Entity == NULL)
                    return false;

                std::uint64_t NetObject = *(std::uint64_t*)(Entity + 0xD0);
                if (NetObject == NULL)
                    return false;

                if (*(std::uint16_t*)(NetObject + 0x8) == 11)
                    return false;

                int NetworkHandle = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(script_index);
                g_GameFunctions->m_ChangeNetworkObjectOwner(NetworkObjectMgrInterface, NetObject, owner, 0ui64);
                NETWORK::SET_NETWORK_ID_CAN_MIGRATE(NetworkHandle, TRUE);

                return true;
            }

        }
        void kick_from_vehicle(int pos) {
            if (pos == 0) {
                const size_t arg_count = 9;
                int64_t args[arg_count] = {
                    (int64_t)-1603050746,
                    PLAYER::PLAYER_ID(), 0, 0, 0, 0, 0, 0, 0
                };

                g_GameFunctions->m_trigger_script_event(1, args, arg_count, 1 << get_id());
            }
            if (pos == 1) {
                auto Vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), FALSE);
                ChangeNetworkObjectOwner(Vehicle, g_GameFunctions->m_GetNetPlayer(PLAYER::PLAYER_ID()));
            }
        }
        bool network_has_control_of_entity(rage::netObject* net_object)
        {
            return !net_object || !net_object->m_next_owner_id && (net_object->m_control_id == -1);
        }

        bool request_control(Entity ent, int timeout = 300)
        {
            auto ptr = g_GameVariables->m_handle_to_ptr(ent);
                if (ptr)
                {
                    if (!*g_GameVariables->m_is_session_started || network_has_control_of_entity(ptr->m_net_object))
                        return true;
                    for (int i = 0; !network_has_control_of_entity(ptr->m_net_object) && i < timeout; i++)
                    {
                        g_GameVariables->m_request_control(ptr->m_net_object);
                        if (timeout != 0)
                            fbr::cur()->wait();
                    }
                    if (!network_has_control_of_entity(ptr->m_net_object))
                        return false;
                    int netHandle = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(ent);
                    NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netHandle, true);
                }
                return true;
            
        }
        void set_wanted_level(int level) {
            PLAYER::REPORT_CRIME(all_players.get_id(g_SelectedPlayer), 8, PLAYER::GET_WANTED_LEVEL_THRESHOLD(level));
        }
        void taze() {
            int currentAttempt = 0;
            int maxAttempts = 20;
            while (!ENTITY::IS_ENTITY_DEAD(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0))
            {
                if (currentAttempt >= maxAttempts)
                {
                    break;
                }
                else
                {
                    NativeVector3 destination = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), SKEL_ROOT, 0.0f, 0.0f, 0.0f);
                    NativeVector3 origin = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), SKEL_R_Hand, 0.0f, 0.0f, 0.2f);
                    Hash tazerHash = MISC::GET_HASH_KEY("WEAPON_STUNGUN");
                    MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 1, 0, tazerHash, PLAYER::PLAYER_PED_ID(), false, false, 1);
                    currentAttempt++;
                }
                m_queue.add(1s, "Tazing player..", [] {});
            }
        }
        bool fire_loop = false;
        bool water_loop = false;
		void init() {
            if (fire_loop) {
                NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
                *(unsigned short*)g_GameFunctions->m_owned_explosion = 0xE990;
                FIRE::ADD_OWNED_EXPLOSION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), c.x, c.y, c.z, 12, 500, true, false, 0);
                *(unsigned short*)g_GameFunctions->m_owned_explosion = 0x850F;
            }
            if (water_loop) {
                NativeVector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
                *(unsigned short*)g_GameFunctions->m_owned_explosion = 0xE990;
                FIRE::ADD_OWNED_EXPLOSION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), c.x, c.y, c.z, 13, 500, true, false, 0);
                *(unsigned short*)g_GameFunctions->m_owned_explosion = 0x850F;
            }
            if (freeze) {
                if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
                    g_GameFunctions->m_clear_ped_tasks_network(all_players.get_ped(g_SelectedPlayer), true);
                }
            }
            explosiveAmmo.init();
			flash_blip.init();
			otr.init();
            block_actions.init();
			
		}
	};
	
}