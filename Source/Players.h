#pragma once
#include "Natives.hpp" 
#include "UI/Framework.hpp"
#include "Selected.h"
#include "Images.h"
#include "Caller.h"
#include <GTAV-Classes/script/globals/GlobalPlayerBD.hpp>
#include <GTAV-Classes/script/globals/GPBD_FM.hpp>
#include <GTAV-Classes/script/globals/GPBD_FM_3.hpp>
#include "DrawingFunctions2.h"
#define STORY_MODE_TEXT "~t~~italic~Enter GTA:O"
namespace Saint {
	class hide_informationg {
	public:
		bool ip = false;
		bool port = false;
		bool vehicle = false;
		bool state = false;
		bool wanted_level = false;
		bool all = true;
		bool ped = true;
		bool id, parachute_state, standuser, zone, street, coords, heading, distance, speed, walletandbank, totalmoney, rank, favvehicle, rp, yachtname, ceoname, mcname, offtheradar, kd, kills, deaths, ammo = false;
	};
	inline hide_informationg hide_information;
	class tags4 {
	public:
		bool self = true;
		bool saint_user = true;
		bool interior = true;
		bool script_host = true;
		bool modder = true;
	};
	inline tags4 tags;
	class PlayersData {
	public:

		GetSelected get_selected;
		void get_theme(Color col) {
			switch (g_Render->ThemeIterator) {
			case 0:
				col = { 138, 43, 226, 255 };
				break;
			case 1:
				col = { 255, 108, 116, 255 };
				break;
			case 2:
				col = { 15, 82, 186, 255 };
				break;
			case 3:
				col = { 24, 26, 24, 255 };
				break;
			case 4:
				col = { 0, 155, 119, 255 };
				break;
			case 5:
				col = { 70, 38, 180, 255 };
			case 6:
				col = { 255, 145, 164, 255 };
				break;
			case 7:
				col = { 17, 17, 17, 255 };
				break;
			case 8:
				col = { 234, 90, 81, 255 };
				break;

			}
		}
		void drawText(const char* text, float x, float y, float size, int font, bool center, Color color, bool right) {
			HUD::SET_TEXT_SCALE(size, size);
			HUD::SET_TEXT_FONT(font);
			HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
			HUD::SET_TEXT_CENTRE(center);

			if (right) {
				HUD::SET_TEXT_WRAP(0.0f, x);
				HUD::SET_TEXT_RIGHT_JUSTIFY(true);
			}
			HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
		}
		float x_offset = 0.505;
		float y_offset = 0.105f;
		float width = 0.183f;
		float height = 0.178;

		void draw_info_text(const char* text, const char* text2, int pos, float x_offset, bool first = false) {
			float x = g_Render->m_PosX;
			Color col2 = { 255, 255, 255, 255 };
			float offset = 0.02;
			float xfr = x + 0.205f + offset;
			if (first) {
				drawText(text, xfr - 0.120f, 0.105f, 0.23f, 0, false, col2, false);
				drawText(text2, xfr + 0.057f - x_offset, 0.105f, 0.23f, 0, false, col2, true);
			}
			else {
				drawText(text, xfr - 0.120f, 0.105f + 0.015f * pos, 0.23f, 0, false, col2, false);
				drawText(text2, xfr + 0.057f - x_offset, 0.105f + 0.015f * pos, 0.23f, 0, false, col2, true);
			}
		}
		void drawSprite(const char* dict, const char* texture, float x, float y, float width, float height, Color color, float rotation)
		{
			if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict))
			{
				GRAPHICS::DRAW_SPRITE(dict, texture, x, y, width, height, rotation, color.r, color.g, color.b, color.a, 0, false);
			}
			else
			{
				GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict, false);
			}
		}

		void draw_friend_info(int selected) {


		}
		std::string separateByCommas(int num) {
			std::string numStr = std::to_string(num);
			std::string result;
			int count = 0;

			// Iterate through the string from the right and add commas
			for (int i = numStr.size() - 1; i >= 0; i--) {
				result = numStr[i] + result;
				count++;
				if (count == 3 && i != 0) {
					result = "," + result;
					count = 0;
				}
			}

			return result;
		}
		bool is_in_current_vehicle(Ped ped) {
			if (PED::IS_PED_IN_VEHICLE(ped, PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), false)) {
				return true;
			}
			else {
				return false;
			}
			return false;
		}
		void info_part_1() {
			
			//infoBeingDrawn = true;
			float x = g_Render->m_PosX + 0.094 + (g_Render->m_Width / 2.f);
			float y = g_Render->m_PosY;
			Color col;

			float offset = 0.023f;
			float xfr = x + 0.205f + offset - 0.025f;
			if (g_Render->ytd.player_info) {
				UserInterface::DrawingFunctions()->Sprite(g_Render->texture_name.c_str(), "player_info", x, y + -0.090 + 0.178, 0.183f, 0.178, g_Render->m_OptionUnselectedBackgroundColor, 0);
			}
			else {
				GRAPHICS::DRAW_RECT(x, y + -0.090 + 0.178, 0.183f, 0.178, g_Render->m_OptionUnselectedBackgroundColor.r, g_Render->m_OptionUnselectedBackgroundColor.g, g_Render->m_OptionUnselectedBackgroundColor.b, g_Render->m_OptionUnselectedBackgroundColor.a, false);
			}
			
			Color col2 = { 255, 255, 255, 190 };

			if (!g_Render->ytd.player_info) {
				GRAPHICS::DRAW_RECT(x, y + -0.000, 0.183, -0.002, g_Render->m_HeaderBackgroundColor.r, g_Render->m_HeaderBackgroundColor.g, g_Render->m_HeaderBackgroundColor.b, 255, false);
				GRAPHICS::DRAW_RECT(x, y + -0.000, 0.183f, -0.002, g_Render->m_HeaderBackgroundColor.r, g_Render->m_HeaderBackgroundColor.g, g_Render->m_HeaderBackgroundColor.b, 255, false);
			}
		}
		void draw_weapon_info(Hash weapon) {
			info_part_1();
			char timesince[128];
			char max_speed[128];
			char seats[64];
			char price[128];
			char make[128];
			char make2[128];
			sprintf(timesince, "%i", WEAPON::GET_WEAPON_CLIP_SIZE(weapon));
			sprintf(max_speed, "%.f", WEAPON::GET_WEAPON_DAMAGE(weapon, 0));
			sprintf(seats, "%i", WEAPON::GET_WEAPON_TINT_COUNT(weapon));
			sprintf(price, "%.fs", WEAPON::GET_WEAPON_TIME_BETWEEN_SHOTS(weapon));
			//drawSprite(preview.dict, preview.texture, x + 0.3545595, y + -0.139, 0.1493f, 0.10f, { 255, 255, 255, 255 }, 0.0f);
			draw_info_text("Clip Size", timesince, 1, 0, true);
			draw_info_text("Damage", max_speed, 1, 0);
			draw_info_text("Tint Count", seats, 2, 0);
			draw_info_text("Time Inbetween Shots", price, 3, 0);
		}
		void draw_info4(Ped gaurd) {

			info_part_1();
			char timesince[128];
			char max_speed[128];
			char seats[64];
			char price[128];
			char make[128];
			char make2[128];
			script_global globalplayer_bd(2657704);
			script_global gpbd_fm_3(1895156);
			script_global gpbd_fm_1(1853988);
			auto& stats = gpbd_fm_1.as<GPBD_FM*>()->Entries[PLAYER::PLAYER_ID()].PlayerStats;
			auto& stats1 = gpbd_fm_1.as<GPBD_FM*>()->Entries[PLAYER::PLAYER_ID()];
			auto& stats2 = gpbd_fm_3.as<GPBD_FM_3*>()->Entries[PLAYER::PLAYER_ID()];
			auto& stats3 = globalplayer_bd.as<GlobalPlayerBD*>()->Entries[PLAYER::PLAYER_ID()];
			NativeVector3 get_coords = ENTITY::GET_ENTITY_COORDS(gaurd, false);
			sprintf(timesince, "%i", ENTITY::GET_ENTITY_HEALTH(gaurd));
			sprintf(max_speed, "%s", is_in_current_vehicle(gaurd) ? "Yes" : "No");
			sprintf(seats, "%s", ENTITY::IS_ENTITY_DEAD(gaurd, 0) ? "Yes" : "No");
			Hash street[2]{};
			PATHFIND::GET_STREET_NAME_AT_COORD(get_coords.x, get_coords.y, get_coords.z, &street[0], &street[1]);
			const char* Street = HUD::GET_STREET_NAME_FROM_HASH_KEY(street[0]);
			sprintf(price, "%s", Street);
			//drawSprite(preview.dict, preview.texture, x + 0.3545595, y + -0.139, 0.1493f, 0.10f, { 255, 255, 255, 255 }, 0.0f);
			draw_info_text("Health", timesince, 1, 0, true);
			draw_info_text("In Current Vehicle", max_speed, 1, 0);
			draw_info_text("Dead", seats, 2, 0);
			draw_info_text("Street", price, 3, 0);

		}
		void draw_info3() {

			
			info_part_1();
			char timesince[128];
			char max_speed[128];
			char seats[64];
			char price[128];
			char make[128];
			char make2[128];
			script_global globalplayer_bd(2657704);
			script_global gpbd_fm_3(1895156);
			script_global gpbd_fm_1(1853988);
			auto& stats = gpbd_fm_1.as<GPBD_FM*>()->Entries[PLAYER::PLAYER_ID()].PlayerStats;
			auto& stats1 = gpbd_fm_1.as<GPBD_FM*>()->Entries[PLAYER::PLAYER_ID()];
			auto& stats2 = gpbd_fm_3.as<GPBD_FM_3*>()->Entries[PLAYER::PLAYER_ID()];
			auto& stats3 = globalplayer_bd.as<GlobalPlayerBD*>()->Entries[PLAYER::PLAYER_ID()];
			sprintf(timesince, "$%s", separateByCommas(stats1.PropertyData.NightclubData.SafeCashValue));
			sprintf(max_speed, "%i%", (int)stats1.PropertyData.NightclubData.Popularity);
			sprintf(seats, "$%i", (int)stats1.PropertyData.NightclubData.EntryCost);
			sprintf(price, "%i", (int)stats1.PropertyData.BusinessHubData.Upgrades);
			sprintf(make, "%i", (int)stats1.PropertyData.BusinessHubData.TotalSoldProduct.Data);
			sprintf(make2, "%i", (int)stats1.PropertyData.NightclubData.CroudVariation);
			//drawSprite(preview.dict, preview.texture, x + 0.3545595, y + -0.139, 0.1493f, 0.10f, { 255, 255, 255, 255 }, 0.0f);
			draw_info_text("Safe Cash", timesince, 1, 0, true);
			draw_info_text("Popularity", max_speed, 1, 0);
			draw_info_text("Entry Cost", seats, 2, 0);
			draw_info_text("Upgrades", price, 3, 0);
			draw_info_text("Total Sold Product", make, 4, 0);
			draw_info_text("Croud Variation", make, 5, 0);
		}
		void draw_info2(Hash hash) {

			info_part_1();

			char timesince[128];
			char max_speed[128];
			char seats[64];
			char price[128];
			char make[128];
			sprintf(timesince, "%.1f", VEHICLE::GET_VEHICLE_MODEL_ACCELERATION(hash));
			sprintf(max_speed, "%.0f MPH", (VEHICLE::GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(hash)) * 2.23694);
			sprintf(seats, "%i", VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(hash));
			sprintf(price, "$%i", VEHICLE::GET_VEHICLE_MODEL_VALUE(hash));
			sprintf(make, "%s", VEHICLE::GET_MAKE_NAME_FROM_VEHICLE_MODEL(hash));
			//drawSprite(preview.dict, preview.texture, x + 0.3545595, y + -0.139, 0.1493f, 0.10f, { 255, 255, 255, 255 }, 0.0f);
			draw_info_text("Acceleration", timesince, 1, 0, true);
			draw_info_text("Max Speed (MPH)", max_speed, 1, 0);
			draw_info_text("Seats", seats, 2, 0);
			draw_info_text("Price", price, 3, 0);
			draw_info_text("Make", make, 4, 0);



			
		}
		float pedx = 0.060;
		float pedyy = 1.680f;
		float pedy = -0.224;
		float xoffset = 1.080;
		float yoffset = -2.550;
		float zoffset = 0.130;
		int GetSpeed(Ped ped) {

			int speed = (int)round(ENTITY::GET_ENTITY_SPEED(ped) * 2.24);
			return speed;
		}
		char* GetWanted(Player p)
		{
			char buffer[20];
			int Stars = (int)PLAYER::GET_PLAYER_WANTED_LEVEL(p);
			sprintf_s(buffer, "%i/5", Stars);
			return buffer;
		}
		void Text(const char* text, Color color, Vector2 position, Vector2 size, bool center)
		{
			HUD::SET_TEXT_CENTRE(center);
			HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
			HUD::SET_TEXT_FONT(0);
			HUD::SET_TEXT_SCALE(size.x, size.y);
			HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y, 0);
		}
		bool is_player_stand_user(std::int32_t player) {
			const char* name = PLAYER::GET_PLAYER_NAME(player);
			if (name != nullptr)
				if ((((std::uint64_t)(name - 0x24) >> 32) & 0xFFFFFFFF) == NULL)
					return true;
			return false;
		}
		CNetGamePlayer* get_net_player(std::uint32_t player) {
			return g_GameVariables->m_net_game_player(player) == nullptr ? nullptr : g_GameVariables->m_net_game_player(player);
		}
		rage::rlGamerInfo* get_net_data(std::uint32_t player) const
		{
			return g_GameVariables->m_net_game_player(player) == nullptr ? nullptr : g_GameVariables->m_net_game_player(player)->get_net_data();
		}
		Network* get_network()
		{
			return *g_GameFunctions->m_network;
		}
		rage::snPlayer* get_session_player(std::uint32_t player)
		{
			for (std::uint32_t i = 0; i < get_network()->m_game_session_ptr->m_player_count; i++)
			{
				if (get_network()->m_game_session_ptr->m_players[i]->m_player_data.m_host_token == get_net_data(player)->m_host_token)
				{
					return get_network()->m_game_session_ptr->m_players[i];
				}
			}

			if (get_network()->m_game_session_ptr->m_local_player.m_player_data.m_host_token == get_net_data(player)->m_host_token)
				return &get_network()->m_game_session_ptr->m_local_player;

			return nullptr;
		}

		netAddress get_ip_address(std::uint32_t player)
		{

			if (player == PLAYER::PLAYER_ID())
				return (*g_GameFunctions->m_pedFactory)->m_local_ped->m_player_info->m_net_player_data.m_external_ip;

			if (auto session_player = get_session_player(player))
				if (auto peer = g_GameFunctions->m_get_connection_peer(get_network()->m_game_session_ptr->m_net_connection_mgr, (int)get_session_player(player)->m_player_data.m_peer_id_2))
					return netAddress{
						((netConnectionPeer*)peer)->m_external_ip
				};

			return { 0 };
		}
		uint16_t get_port(std::uint32_t player)
		{

			if (player == PLAYER::PLAYER_ID())
				return (*g_GameFunctions->m_pedFactory)->m_local_ped->m_player_info->m_net_player_data.m_external_port;

			if (auto session_player = get_session_player(player))
				if (auto peer = g_GameFunctions->m_get_connection_peer(get_network()->m_game_session_ptr->m_net_connection_mgr, (int)get_session_player(player)->m_player_data.m_peer_id_2))
					return ((netConnectionPeer*)peer)->m_external_port;


			return { 0 };
		}
		struct scene_preset {
			struct scene_preset_element {
				char _0x0000[24];
				rage::fvector4 m_position;
				rage::fvector4 m_position_43;
				rage::fvector4 m_rotation_xyz;
				rage::fvector4 m_bg_rect_xywh;
				rage::fvector4 m_bg_rect_xywh_43;
				uint32_t m_bg_rect_color;
				uint32_t m_blend_color;
				bool m_enabled;
				char _0x0071[15];
			};

			uint32_t m_name;
			char _0x0004[4];
			scene_preset_element m_elements[5];
			char _0x0288[8];
			int32_t m_element_count;
			char _0x0294[12];

			void set_element_rot(uint32_t element, Vector3 rot) {
				if (element >= 0 && element < 5) {
					m_elements[element].m_rotation_xyz.x = rot.x;
					m_elements[element].m_rotation_xyz.y = rot.y;
					m_elements[element].m_rotation_xyz.z = rot.z;
				}
			}

			void set_element_pos(uint32_t element, Vector2 xy, Vector2 wh) {
				if (element >= 0 && element < 5) {
					m_elements[element].m_bg_rect_xywh.z = wh.x; // make fullscreen
					m_elements[element].m_bg_rect_xywh.w = wh.y; // make fullscreen
					m_elements[element].m_bg_rect_xywh.x = xy.x; // convert and set pos
					m_elements[element].m_bg_rect_xywh.y = xy.y; // convert and set pos
					m_elements[element].m_bg_rect_xywh_43.z = wh.x; // make fullscreen
					m_elements[element].m_bg_rect_xywh_43.w = wh.y; // make fullscreen
					m_elements[element].m_bg_rect_xywh_43.x = xy.x; // convert and set pos
					m_elements[element].m_bg_rect_xywh_43.y = xy.y; // convert and set pos
					m_elements[element].m_bg_rect_color = 0x0;
				}
			}
		};
		void draw_on_screen_ped(CPed* ped, Vector2 pos, Vector2 scale, Vector3 position_offset) {
			uint32_t scene_hash = 0x390DCCF5;

			if (!HUD::IS_PAUSE_MENU_ACTIVE()) {
				if (GRAPHICS::UI3DSCENE_IS_AVAILABLE()) {
					uint32_t element = 0;

					uintptr_t ui_3d_draw_manager = *(uint64_t*)(g_GameVariables->ui_3d_draw_manager);
					if (ui_3d_draw_manager) {
						
						*(uint8_t*)((uint64_t)ped + 0x1163) |= 0x40u;
						*(uint32_t*)((uint64_t)ped + 0x114C) |= 0xC0u;
						scene_preset* preset = call<scene_preset*>(g_GameVariables->get_scene_preset, ui_3d_draw_manager, &scene_hash);
						if (preset) {
							preset->m_elements[element].m_rotation_xyz.x = 0.0f;
							preset->m_elements[element].m_rotation_xyz.y = 0.0f;
							preset->m_elements[element].m_rotation_xyz.z = 0.0f;
							preset->set_element_pos(element, pos, scale);
						}

						if (call<bool>(g_GameVariables->push_scene_preset_manager, ui_3d_draw_manager, &scene_hash)) {
							if (call<bool>(g_GameVariables->add_element_to_scene, ui_3d_draw_manager, &scene_hash, element, ped, position_offset, 1.0f)) {
								call<bool>(g_GameVariables->set_scene_element_lighting, ui_3d_draw_manager, &scene_hash, element, 1.0f); 
							}
						}
					}
				}
			}
		}
		float width22 = 0.730;
		float height22 = 0.720;
		float xmill = 0.001;
		void draw_info(std::uint32_t player) {
			try {
				//infoBeingDrawn = true;
				Color m_InfoBG{ g_Render->m_OptionUnselectedBackgroundColor };
				float x = g_Render->m_PosX + 0.128 + (g_Render->m_Width / 2.f);
				float y = g_Render->m_PosY;
				float offset = 0.012;
				Color m_white{ 255, 255, 255, 255 };
				float PosX = x;
				float PosY = y + 0.168f;
				float LTextX = PosX - 0.1225;
				float RTextX = PosX + 0.009f;
				float TextY = y - 0.055;
				float SeperatorX = PosX + 0.05;

				float RTextX2 = PosX + 0.1215f;

				float rightresult = 0.49f;
				float righttext = SeperatorX - 0.048f;

				float LeftOffset = SeperatorX - 0.0523f;

				if (g_Render->ytd.player_info) {
					//main
					UserInterface::DrawingFunctions()->Sprite(g_Render->texture_name.c_str(),
						"player_info",
						PosX, PosY + 0.0202f, 0.25f, 0.375f,
						m_InfoBG,
						0.f);

					//ped preview
					UserInterface::DrawingFunctions()->Sprite(g_Render->texture_name.c_str(),
						"player_info",
						PosX + 0.195, PosY + 0.0202f, 0.135f, 0.375f,
						m_InfoBG,
						0.f);

					UserInterface::DrawingFunctions()->Sprite(g_Render->texture_name.c_str(),
						"player_info",
						PosX, PosY + 0.28, 0.25f, 0.125,
						m_InfoBG,
						0.f);
				}
				else {
					UserInterface::DrawingFunctions()->Rectangle(PosX, PosY + 0.0202f, 0.25f, 0.375f, m_InfoBG); // main
					UserInterface::DrawingFunctions()->Rectangle(PosX, PosY - 0.0220f * 7.652f + xmill, 0.25f, 0.002f, g_Render->m_HeaderBackgroundColor);
					if (hide_information.ped) {
						UserInterface::DrawingFunctions()->Rectangle(PosX + 0.195, PosY + 0.0202f, 0.135f, 0.375f, m_InfoBG); //ped preview
						UserInterface::DrawingFunctions()->Rectangle(PosX + 0.195, PosY - 0.0220f * 7.652f + xmill, 0.135f, 0.002f, g_Render->m_HeaderBackgroundColor);
					}
					UserInterface::DrawingFunctions()->Rectangle(PosX, PosY + 0.28, 0.25f, 0.125, m_InfoBG); // second bar
					UserInterface::DrawingFunctions()->Rectangle(PosX, PosY + 0.312 - 0.09375, 0.25f, 0.002f, g_Render->m_HeaderBackgroundColor);
				}

				Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

				NativeVector3 get_coords = ENTITY::GET_ENTITY_COORDS(ped, 0);
				std::string wantedlvl = GetWanted(player);
				std::string ammo = std::format("{}", WEAPON::GET_AMMO_IN_PED_WEAPON(ped, WEAPON::GET_SELECTED_PED_WEAPON(ped)));
				std::string coords = std::format("{0},{1},{2}", std::roundl(get_coords.x), std::roundl(get_coords.y), std::roundl(get_coords.z));

				script_global globalplayer_bd(2657704);
				script_global gpbd_fm_3(1895156);
				script_global gpbd_fm_1(1853988);
				auto& stats = gpbd_fm_1.as<GPBD_FM*>()->Entries[all_players.get_id(player)].PlayerStats;
				auto& stats1 = gpbd_fm_1.as<GPBD_FM*>()->Entries[all_players.get_id(player)];
				auto& stats2 = gpbd_fm_3.as<GPBD_FM_3*>()->Entries[all_players.get_id(player)];
				auto& stats3 = globalplayer_bd.as<GlobalPlayerBD*>()->Entries[all_players.get_id(player)];
				Hash street[2]{};
				PATHFIND::GET_STREET_NAME_AT_COORD(get_coords.x, get_coords.y, get_coords.z, &street[0], &street[1]);
				std::string Street = HUD::GET_STREET_NAME_FROM_HASH_KEY(street[0]);
				std::string Zone = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ZONE::GET_NAME_OF_ZONE(get_coords.x, get_coords.y, get_coords.z));
				std::string heading = std::format("{}", roundf(ENTITY::GET_ENTITY_HEADING(ped)));

				NativeVector3 playerCoords = ENTITY::GET_ENTITY_COORDS(ped, false);
				NativeVector3 selfCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
				float distance = MISC::GET_DISTANCE_BETWEEN_COORDS(selfCoords.x, selfCoords.y, selfCoords.z, playerCoords.x, playerCoords.y, playerCoords.z, true);
				std::string Distance = std::format("{}m", roundf(distance));
				std::string Speed = std::to_string(GetSpeed(ped));
				std::string passive = PLAYER::IS_PLAYER_BATTLE_AWARE(ped) ? "Yes" : "No";
				std::string rockstar = NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(ped) ? "Yes" : "No";

				const char* playerstate2 = "None / If you see this, buy a lottery ticket!";
				const char* parachutestate2 = "None";
				Ped playerPed = ped;
				std::string total_money = NETWORK::NETWORK_IS_SESSION_STARTED() ? std::format("${}", separateByCommas(stats.Money)) : STORY_MODE_TEXT;
				if (PED::GET_PED_PARACHUTE_STATE(playerPed) == 0)
				{
					parachutestate2 = "Wearing";

				}
				if (PED::GET_PED_PARACHUTE_STATE(playerPed) == 1)
				{
					parachutestate2 = "Opening";
				}
				if (PED::GET_PED_PARACHUTE_STATE(playerPed) == 2)
				{
					parachutestate2 = "Open";
				}
				if (PED::GET_PED_PARACHUTE_STATE(playerPed) == 3)
				{
					parachutestate2 = "Falling To Death";
				}


				if (PED::IS_PED_RAGDOLL(playerPed))
				{
					playerstate2 = "Ragdolling";
				}
				if (PED::IS_PED_DEAD_OR_DYING(playerPed, 1))
				{
					playerstate2 = "Respawning";
				}
				if (!PED::IS_PED_SHOOTING(playerPed) && TASK::IS_PED_STILL(playerPed) && !PED::IS_PED_RAGDOLL(playerPed) && !PED::IS_PED_RELOADING(playerPed) && !TASK::IS_PED_GETTING_UP(playerPed) && !PED::IS_PED_DEAD_OR_DYING(playerPed, 1));
				{
					playerstate2 = "Standing Still";
				}
				if (TASK::IS_PED_GETTING_UP(playerPed) && !PED::IS_PED_DEAD_OR_DYING(playerPed, 1))
				{
					playerstate2 = "Getting Up From Ragdoll";
				}
				if (PED::IS_PED_RELOADING(playerPed) && !PED::IS_PED_DEAD_OR_DYING(playerPed, 1))
				{
					playerstate2 = "Reloading";
				}
				if (PED::IS_PED_SHOOTING(playerPed) && !PED::IS_PED_DOING_DRIVEBY(playerPed) && !PED::IS_PED_DEAD_OR_DYING(playerPed, 1))
				{
					playerstate2 = "Shooting";
				}
				if (PED::IS_PED_DOING_DRIVEBY(playerPed))
				{
					playerstate2 = "Doing Drive-by";
				}
				if (PED::IS_PED_SHOOTING(playerPed) && TASK::IS_PED_SPRINTING(playerPed) || PED::IS_PED_SHOOTING(playerPed) && TASK::IS_PED_RUNNING(playerPed) && !PED::IS_PED_RELOADING(playerPed) && !PED::IS_PED_DEAD_OR_DYING(playerPed, 1))
				{
					playerstate2 = "Sprinting & Shooting";
				}
				if (!PED::IS_PED_SHOOTING(playerPed) && TASK::IS_PED_SPRINTING(playerPed) || !PED::IS_PED_SHOOTING(playerPed) && TASK::IS_PED_RUNNING(playerPed) && !PED::IS_PED_RELOADING(playerPed) && !PED::IS_PED_DEAD_OR_DYING(playerPed, 1))
				{
					playerstate2 = "Sprinting";
				}
				if (PED::IS_PED_SHOOTING(playerPed) && TASK::IS_PED_WALKING(playerPed) && !PED::IS_PED_RELOADING(playerPed))
				{
					playerstate2 = "Shooting & Walking";
				}
				if (!PED::IS_PED_SHOOTING(playerPed) && TASK::IS_PED_WALKING(playerPed) && !PED::IS_PED_RELOADING(playerPed))
				{
					playerstate2 = "Walking";
				}
				if (PED::IS_PED_JUMPING(playerPed) && !TASK::IS_PED_GETTING_UP(playerPed))
				{
					playerstate2 = "Jumping";
				}
				char wantedLevel[128];
				//info
				//UserInterface::DrawingFunctions()->Rectangle(SeperatorX - 0.05, TextY + 0.135f, 0.001f, 0.015f, m_white);
				if (!PLAYER::ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP(playerPed))
				{
					sprintf(wantedLevel, "%i/5", PLAYER::GET_PLAYER_WANTED_LEVEL(player));
				}
				if (PLAYER::ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP(playerPed))
				{
					sprintf(wantedLevel, "%i/5 (Flashing/About To Drop)", PLAYER::GET_PLAYER_WANTED_LEVEL(player));
				}
				float placey = 0.057f;
				Text("Vehicle", { m_white }, { LTextX, TextY + placey }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.vehicle ? "~t~~italic~Hidden" : (PED::GET_VEHICLE_PED_IS_IN(ped, false) == 0) ? "N/A" : HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(playerPed, false)))), RTextX2, TextY + placey, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

				float placey2 = 0.077f;
				Text("State", { m_white }, { LTextX, TextY + placey2 }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.vehicle ? "~t~~italic~Hidden" : playerstate2, RTextX2, TextY + placey2, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

				Text("Wanted Level", { m_white }, { LTextX, TextY + placey2 + 0.020f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.wanted_level ? "~t~~italic~Hidden" : wantedLevel, RTextX2, TextY + placey2 + 0.020f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

				Text("ID", { m_white }, { LTextX, TextY + placey2 + 0.040f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.id ? "~t~~italic~Hidden" : std::to_string(player).c_str(), RTextX2, TextY + placey2 + 0.040f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

				Text("Parachute State", { m_white }, { LTextX, TextY + 0.139f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.parachute_state ? "~t~~italic~Hidden" : parachutestate2, LeftOffset, TextY + 0.139f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

				UserInterface::DrawingFunctions()->Rectangle(SeperatorX - 0.05, TextY + 0.148f, 0.001f, 0.015f, m_white);
				Text("Ammo", { m_white }, { SeperatorX - 0.048f, TextY + 0.139f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.ammo ? "~t~~italic~Hidden" : ammo.c_str(), RTextX2, TextY + 0.139f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

				Text("Stand User", { m_white }, { LTextX, TextY + 0.16f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.standuser ? "~t~~italic~Hidden" : is_player_stand_user(player) ? "Yes" : "No", RTextX2, TextY + 0.16f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

				Text("Zone", { m_white }, { LTextX, TextY + 0.185f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.zone ? "~t~~italic~Hidden" : Zone.c_str(), RTextX2, TextY + 0.185, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

				Text("Street", { m_white }, { LTextX, TextY + 0.21f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.street ? "~t~~italic~Hidden" : Street.c_str(), RTextX2, TextY + 0.21, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

				Text("Coords", { m_white }, { LTextX, TextY + 0.235f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.coords ? "~t~~italic~Hidden" : coords.c_str(), SeperatorX - 0.0523f, TextY + 0.235f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
				UserInterface::DrawingFunctions()->Rectangle(SeperatorX - 0.05, TextY + 0.245f, 0.001f, 0.015f, m_white);
				Text("Heading", { m_white }, { SeperatorX - 0.048f, TextY + 0.235f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.heading ? "~t~~italic~Hidden" : heading.c_str(), RTextX2, TextY + 0.235f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

				Text("Distance", { m_white }, { LTextX, TextY + 0.26f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.distance ? "~t~~italic~Hidden" : Distance.c_str(), SeperatorX - 0.0523f, TextY + 0.26f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
				UserInterface::DrawingFunctions()->Rectangle(SeperatorX - 0.05, TextY + 0.27f, 0.001f, 0.015f, m_white);
				Text("Speed", { m_white }, { SeperatorX - 0.048f, TextY + 0.26f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.speed ? "~t~~italic~Hidden" : Speed.c_str(), RTextX2, TextY + 0.26f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);



				std::string get_wallet_and_bank = NETWORK::NETWORK_IS_SESSION_STARTED() ? std::format("${} | ${}", separateByCommas(stats.WalletBalance), separateByCommas(stats.Money - stats.WalletBalance)) : STORY_MODE_TEXT;
				Text("Wallet & Bank", { m_white }, { LTextX, TextY + 0.285f }, { 0.23f, 0.23f }, false);
				if (hide_information.walletandbank) {
					UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, "~t~~italic~Hidden", SeperatorX - 0.0523f, TextY + 0.285f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
				}
				else {
					if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
						UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, get_wallet_and_bank.c_str(), SeperatorX - 0.0523f, TextY + 0.285f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
					}
					else {
						UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, STORY_MODE_TEXT, SeperatorX - 0.0523f, TextY + 0.285f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
					}
				}
				UserInterface::DrawingFunctions()->Rectangle(SeperatorX - 0.05, TextY + 0.295f, 0.001f, 0.015f, m_white);
				Text("Total Money", { m_white }, { SeperatorX - 0.048f, TextY + 0.285f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.totalmoney ? "~t~~italic~Hidden" : total_money.c_str(), RTextX2, TextY + 0.285f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

				Text("Rank", { m_white }, { LTextX, TextY + 0.31f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.rank ? "~t~~italic~Hidden" : NETWORK::NETWORK_IS_SESSION_STARTED() ? std::to_string(stats.Rank).c_str() : STORY_MODE_TEXT, SeperatorX - 0.0523f, TextY + 0.31f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
				UserInterface::DrawingFunctions()->Rectangle(SeperatorX - 0.05, TextY + 0.32f, 0.001f, 0.015f, m_white);
				Text("Favorite Vehicle", { m_white }, { SeperatorX - 0.048f, TextY + 0.31f }, { 0.23f, 0.23f }, false);
				const char* fav_veh = NETWORK::NETWORK_IS_SESSION_STARTED() ? HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(stats.FavoriteVehicle)) : STORY_MODE_TEXT;
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.favvehicle ? "~t~~italic~Hidden" : fav_veh == "NULL" ? "None" : fav_veh, RTextX2, TextY + 0.31f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

				Text("RP", { m_white }, { LTextX, TextY + 0.335f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.rp ? "~t~~italic~Hidden" : NETWORK::NETWORK_IS_SESSION_STARTED() ? std::to_string(stats.GlobalRP).c_str() : STORY_MODE_TEXT, SeperatorX - 0.0523f, TextY + 0.335f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
				UserInterface::DrawingFunctions()->Rectangle(SeperatorX - 0.05, TextY + 0.345f, 0.001f, 0.015f, m_white);
				Text("Yacht Name", { m_white }, { SeperatorX - 0.048f, TextY + 0.335f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.yachtname ? "~t~~italic~Hidden" : NETWORK::NETWORK_IS_SESSION_STARTED() ? stats3.YachtData.Appearance.Name.Data : STORY_MODE_TEXT, RTextX2, TextY + 0.335f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);

				Text("CEO Name", { m_white }, { LTextX, TextY + 0.36f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.ceoname ? "~t~~italic~Hidden" : NETWORK::NETWORK_IS_SESSION_STARTED() ? stats2.BossGoon.GangName.Data : STORY_MODE_TEXT, SeperatorX - 0.0523f, TextY + 0.36f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
				UserInterface::DrawingFunctions()->Rectangle(SeperatorX - 0.05, TextY + 0.37f, 0.001f, 0.015f, m_white);
				Text("MC Name", { m_white }, { SeperatorX - 0.048f, TextY + 0.36f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.mcname ? "~t~~italic~Hidden" : NETWORK::NETWORK_IS_SESSION_STARTED() ? stats2.BossGoon.MCName.Data : STORY_MODE_TEXT, RTextX2, TextY + 0.36f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
				Text("Off The Radar", { m_white }, { LTextX, TextY + 0.385f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.offtheradar ? "~t~~italic~Hidden" : NETWORK::NETWORK_IS_SESSION_STARTED() ? stats3.OffRadarActive == 1 ? "Yes" : "No" : STORY_MODE_TEXT, SeperatorX - 0.0523f, TextY + 0.385f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);


				UserInterface::DrawingFunctions()->Rectangle(SeperatorX - 0.05, TextY + 0.395f, 0.001f, 0.015f, m_white);
				Text("KD", { m_white }, { SeperatorX - 0.048f, TextY + 0.385f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.kd ? "~t~~italic~Hidden" : NETWORK::NETWORK_IS_SESSION_STARTED() ? std::to_string(stats1.PlayerStats.KdRatio).c_str() : STORY_MODE_TEXT, RTextX2, TextY + 0.385f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);


				Text("Kills", { m_white }, { LTextX, TextY + 0.41f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.kills ? "~t~~italic~Hidden" : NETWORK::NETWORK_IS_SESSION_STARTED() ? std::to_string(stats1.PlayerStats.DeathsByPlayers).c_str() : STORY_MODE_TEXT, SeperatorX - 0.0523f, TextY + 0.41f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
				UserInterface::DrawingFunctions()->Rectangle(SeperatorX - 0.05, TextY + 0.42f, 0.001f, 0.015f, m_white);
				Text("Deaths", { m_white }, { SeperatorX - 0.048f, TextY + 0.41f }, { 0.23f, 0.23f }, false);
				UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, hide_information.deaths ? "~t~~italic~Hidden" : NETWORK::NETWORK_IS_SESSION_STARTED() ? std::to_string(stats1.PlayerStats.KillsOnPlayers).c_str() : STORY_MODE_TEXT, RTextX2, TextY + 0.41f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
				if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
					Text("IP", { m_white }, { LTextX, TextY + 0.445f }, { 0.23f, 0.23f }, false);
					if (hide_information.ip) {
						UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, "~t~~italic~Hidden", SeperatorX - 0.0523f, TextY + 0.445f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
					}
					else {
						UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, std::format("{}.{}.{}.{}", get_ip_address(player).m_field1, get_ip_address(player).m_field2, get_ip_address(player).m_field3, get_ip_address(player).m_field4).c_str(), SeperatorX - 0.0523f, TextY + 0.445f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
					}
					UserInterface::DrawingFunctions()->Rectangle(SeperatorX - 0.05, TextY + 0.455f, 0.001f, 0.015f, m_white);
					Text("Port", { m_white }, { SeperatorX - 0.048f, TextY + 0.445f }, { 0.23f, 0.23f }, false);
					if (hide_information.port) {
						UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, "~t~~italic~Hidden", RTextX2, TextY + 0.445f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
					}
					else {
						UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, std::to_string(get_port(player)).c_str(), RTextX2, TextY + 0.445f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
					}
				}
				else {
					Text("IP", { m_white }, { LTextX, TextY + 0.445f }, { 0.23f, 0.23f }, false);
					UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, STORY_MODE_TEXT, SeperatorX - 0.0523f, TextY + 0.445f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
					UserInterface::DrawingFunctions()->Rectangle(SeperatorX - 0.05, TextY + 0.455f, 0.001f, 0.015f, m_white);
					Text("Port", { m_white }, { SeperatorX - 0.048f, TextY + 0.445f }, { 0.23f, 0.23f }, false);
					UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, STORY_MODE_TEXT, RTextX2, TextY + 0.445f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
				}
				if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
					Text("Crew Name", { m_white }, { LTextX, TextY + 0.47f }, { 0.23f, 0.23f }, false);
					UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, get_net_player(player)->m_clan_data.m_clan_name, SeperatorX - 0.0523f, TextY + 0.47f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
					UserInterface::DrawingFunctions()->Rectangle(SeperatorX - 0.05, TextY + 0.48f, 0.001f, 0.015f, m_white);
					Text("Crew Tag", { m_white }, { SeperatorX - 0.048f, TextY + 0.47f }, { 0.23f, 0.23f }, false);
					UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, get_net_player(player)->m_clan_data.m_clan_tag, RTextX2, TextY + 0.47f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
					Text("Crew ID", { m_white }, { LTextX, TextY + 0.495f }, { 0.23f, 0.23f }, false);
					UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, std::to_string(get_net_player(player)->m_clan_data.m_clan_id).c_str(), RTextX2, TextY + 0.495f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
					Text("Crew Member Count", { m_white }, { LTextX, TextY + 0.52f }, { 0.23f, 0.23f }, false);
					UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, std::to_string(get_net_player(player)->m_clan_data.m_clan_member_count).c_str(), RTextX2, TextY + 0.52f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
					Text("Crew Motto", { m_white }, { LTextX, TextY + 0.545f }, { 0.23f, 0.23f }, false);
					UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, get_net_player(player)->m_clan_data.m_clan_motto, RTextX2, TextY + 0.545f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
				}
				else {
					Text("Crew Name", { m_white }, { LTextX, TextY + 0.47f }, { 0.23f, 0.23f }, false);
					UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, STORY_MODE_TEXT, SeperatorX - 0.0523f, TextY + 0.47f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
					UserInterface::DrawingFunctions()->Rectangle(SeperatorX - 0.05, TextY + 0.48f, 0.001f, 0.015f, m_white);
					Text("Crew Tag", { m_white }, { SeperatorX - 0.048f, TextY + 0.47f }, { 0.23f, 0.23f }, false);
					UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, STORY_MODE_TEXT, RTextX2, TextY + 0.47f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
					Text("Crew ID", { m_white }, { LTextX, TextY + 0.495f }, { 0.23f, 0.23f }, false);
					UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, STORY_MODE_TEXT, RTextX2, TextY + 0.495f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
					Text("Crew Member Count", { m_white }, { LTextX, TextY + 0.52f }, { 0.23f, 0.23f }, false);
					UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, STORY_MODE_TEXT, RTextX2, TextY + 0.52f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
					Text("Crew Motto", { m_white }, { LTextX, TextY + 0.545f }, { 0.23f, 0.23f }, false);
					UserInterface::DrawingFunctions()->Text(UserInterface::TextPosition::Right, STORY_MODE_TEXT, RTextX2, TextY + 0.545f, 0.23f, g_Render->m_OptionFont, m_white, 0, 0);
				}



				if (hide_information.ped) {
					draw_on_screen_ped(
						NETWORK::NETWORK_IS_SESSION_STARTED() ? all_players.get_ped(player) : (*g_GameFunctions->m_pedFactory)->m_local_ped->m_player_info->m_ped, 
						{ g_Render->m_PosX + pedx + (g_Render->m_Width / 2.f), g_Render->m_PosY + pedy },
						{ width22, height22 },
						{ xoffset, yoffset, zoffset }
					);
				}
			}
			catch (const std::exception& e) {
				g_Logger->Info(e.what());
			}




		}
	};
	inline PlayersData g_players;
}