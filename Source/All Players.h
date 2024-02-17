#pragma once
#include "Natives.hpp"
#include "ScriptCallback.hpp"
#include "Jets.h"
#include "Explode.h"
namespace Saint {
	inline CNetGamePlayer* m_player_to_use_complaint_kick;
	class Notifications {
	public:
		bool leaving_and_joining = true;
		bool respawning_players = true;
		bool anti_cheat_triggered = true;
		bool log = false;
		bool log_ips = false;
		bool log_rid{};
	};
	class ESP2 {
	public:
		bool tracer = false;
		bool box = false;
		bool name = false;
		bool distance = false;
		void init() {
			if (name) {
				for (std::uint32_t i = 0; i < PLAYER::GET_NUMBER_OF_PLAYERS(); ++i) {
					NativeVector3 pHCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 0, 0, 0);

					float xPos;
					float yPos;

					BOOL screencoords = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(pHCoords.x, pHCoords.y, pHCoords.z, &xPos, &yPos);

					HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
					HUD::SET_TEXT_COLOUR(255, 255, 255, 255);
					HUD::SET_TEXT_FONT(0);
					HUD::SET_TEXT_SCALE(0.3f, 0.3f);
					HUD::SET_TEXT_CENTRE(true);

					std::string name = PLAYER::GET_PLAYER_NAME(i);
					if (distance) {
						NativeVector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
						float distance = GetDistanceFloat(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false), Coords);
						name.append(std::format("\n{}", (int)distance));
					}
					HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(name.c_str());
					HUD::END_TEXT_COMMAND_DISPLAY_TEXT(xPos, yPos, 0);
				}
			}
			if (tracer) {
				for (std::uint32_t i = 0; i < PLAYER::GET_NUMBER_OF_PLAYERS(); ++i) {
					NativeVector3 c = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 0, 0, 0);

					float xPos;
					float yPos;

					BOOL screencoords = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(c.x, c.y, c.z, &xPos, &yPos);

					NativeVector3 selfcoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
					GRAPHICS::DRAW_LINE(selfcoords.x, selfcoords.y, selfcoords.z, c.x, c.y, c.z, 255, 255, 255, 255);
				}
			
			}
			if (box) {
				for (std::uint32_t i = 0; i < PLAYER::GET_NUMBER_OF_PLAYERS(); ++i) {
					NativeVector3 v0, v1;

					NativeVector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), -(v1.x + 0.3f), v1.y - 0.3f, -0.9f);
					NativeVector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), -(v1.x + 0.3f), v1.y + 0.3f, -0.9f);
					NativeVector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), +(v1.x + 0.3f), v1.y - 0.3f, -0.9f);
					NativeVector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), +(v1.x + 0.3f), v1.y + 0.3f, -0.9f);
					NativeVector3 coords2from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + -0.3f, +(v1.y + 0.3f), -0.9f);
					NativeVector3 coords2to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + 0.3f, +(v1.y + 0.3f), -0.9f);
					NativeVector3 coords3from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + -0.3f, -(v1.y + 0.3f), -0.9f);
					NativeVector3 coords3to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + 0.3f, -(v1.y + 0.3f), -0.9f);
					NativeVector3 coords4from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), -(v1.x + 0.3f), v1.y - 0.3f, 0.9f);
					NativeVector3 coords4to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), -(v1.x + 0.3f), v1.y + 0.3f, 0.9f);
					NativeVector3 coords5from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), +(v1.x + 0.3f), v1.y - 0.3f, 0.9f);
					NativeVector3 coords5to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), +(v1.x + 0.3f), v1.y + 0.3f, 0.9f);
					NativeVector3 coords6from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + -0.3f, +(v1.y + 0.3f), 0.9f);
					NativeVector3 coords6to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + 0.3f, +(v1.y + 0.3f), 0.9f);
					NativeVector3 coords7from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + -0.3f, -(v1.y + 0.3f), 0.9f);
					NativeVector3 coords7to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + 0.3f, -(v1.y + 0.3f), 0.9f);
					NativeVector3 coords8from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + 0.3f, -(v1.y + 0.3f), -0.9f);
					NativeVector3 coords8to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + 0.3f, -(v1.y + 0.3f), 0.9f);
					NativeVector3 coords9from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + -0.3f, -(v1.y + -0.3f), -0.9f);
					NativeVector3 coords9to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + -0.3f, -(v1.y + -0.3f), 0.9f);
					NativeVector3 coords10from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + -0.3f, +(v1.y + -0.3f), -0.9f);
					NativeVector3 coords10to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + -0.3f, +(v1.y + -0.3f), 0.9f);
					NativeVector3 coords11from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + 0.3f, +(v1.y + 0.3f), -0.9f);
					NativeVector3 coords11to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), v1.x + 0.3f, +(v1.y + 0.3f), 0.9f);

					GRAPHICS::DRAW_LINE(coords0from.x, coords0from.y, coords0from.z, coords0to.x, coords0to.y, coords0to.z, 255, 255, 255, 255);
					GRAPHICS::DRAW_LINE(coords1from.x, coords1from.y, coords1from.z, coords1to.x, coords1to.y, coords1to.z, 255, 255, 255, 255);
					GRAPHICS::DRAW_LINE(coords2from.x, coords2from.y, coords2from.z, coords2to.x, coords2to.y, coords2to.z, 255, 255, 255, 255);
					GRAPHICS::DRAW_LINE(coords3from.x, coords3from.y, coords3from.z, coords3to.x, coords3to.y, coords3to.z, 255, 255, 255, 255);
					GRAPHICS::DRAW_LINE(coords4from.x, coords4from.y, coords4from.z, coords4to.x, coords4to.y, coords4to.z, 255, 255, 255, 255);
					GRAPHICS::DRAW_LINE(coords5from.x, coords5from.y, coords5from.z, coords5to.x, coords5to.y, coords5to.z, 255, 255, 255, 255);
					GRAPHICS::DRAW_LINE(coords6from.x, coords6from.y, coords6from.z, coords6to.x, coords6to.y, coords6to.z, 255, 255, 255, 255);
					GRAPHICS::DRAW_LINE(coords7from.x, coords7from.y, coords7from.z, coords7to.x, coords7to.y, coords7to.z, 255, 255, 255, 255);
					GRAPHICS::DRAW_LINE(coords8from.x, coords8from.y, coords8from.z, coords8to.x, coords8to.y, coords8to.z, 255, 255, 255, 255);
					GRAPHICS::DRAW_LINE(coords9from.x, coords9from.y, coords9from.z, coords9to.x, coords9to.y, coords9to.z, 255, 255, 255, 255);
					GRAPHICS::DRAW_LINE(coords10from.x, coords10from.y, coords10from.z, coords10to.x, coords10to.y, coords10to.z, 255, 255, 255, 255);
					GRAPHICS::DRAW_LINE(coords11from.x, coords11from.y, coords11from.z, coords11to.x, coords11to.y, coords11to.z, 255, 255, 255, 255);
				}
			}
		}
	};
	class All_players {
	public:
		ESP2 esp2;
		uint8_t get_id(int p) const
		{
			
			return g_GameVariables->m_net_game_player(p) == nullptr ? -1 : g_GameVariables->m_net_game_player(p)->m_player_id;
		}
		CPlayerInfo* get_player_info(int p) const
		{
			if (g_GameVariables->m_net_game_player(p) != nullptr && g_GameVariables->m_net_game_player(p)->m_player_info != nullptr)
				return g_GameVariables->m_net_game_player(p)->m_player_info;
			return nullptr;
		}
		
		CPed* get_ped(int p) const
		{
			if (const auto player_info = get_player_info(p); player_info != nullptr)
				if (const auto ped = player_info->m_ped; ped != nullptr)
					return ped;
			return nullptr;
		}
		Notifications notifications;
		m_Jets jet;
		Explode m_explode;
		int bounty_amount = 10000;
		
		void set_bounty(int i) {
			const size_t arg_count = 22;
			int64_t args[arg_count] = { (int64_t)1459520933,
				PLAYER::PLAYER_ID(),
				get_id(i),
				1,
				bounty_amount,
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
				*script_global(1923597).at(10).as<int64_t*>() };

			g_GameFunctions->m_trigger_script_event(1, args, arg_count, 1 << get_id(i));
		}
		void get(std::uint32_t buffer) {
			buffer = PLAYER::GET_NUMBER_OF_PLAYERS();
		}
		bool off_the_radar = false;
		void init() {
			esp2.init();
			if (off_the_radar) {
				for (std::uint32_t i = 0; i < PLAYER::GET_NUMBER_OF_PLAYERS(); ++i) {
					script_global gpbd_fm_3(1895156);
					constexpr size_t arg_count = 7;
					int64_t args[arg_count] = {
						static_cast<int64_t>(1141648445),
						(int64_t)PLAYER::PLAYER_ID(),
						(int64_t)(NETWORK::GET_NETWORK_TIME() + 1),
						0,
						true,
						false,
						*gpbd_fm_3.at(i, 608).at(510).as<int64_t*>()
					};

					g_GameFunctions->m_trigger_script_event(1, args, arg_count, 1 << i);
				}
			}
		}
	};
	inline All_players all_players;
}