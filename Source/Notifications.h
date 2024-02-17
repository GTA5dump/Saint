#pragma once
#include "Render.h"

namespace Saint {
	class Notifcations {
	public:
		const char* get_name[2] = {"Traditional", "In-Game"};
		int type = 0;
		void add(const char* text, int ms = 2000, int noti = 0, const char* header = "Notification") {
			switch (noti) {
			case 0:
				Noti::InsertNotification({ ImGuiToastType_None, ms, text });
				break;
			case 1:
				HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
				constexpr const char* name = "Protections ~\u00A6~";
				constexpr const char* subtitle = "~c~Notification";
				constexpr const char* picture = "Textures";
				constexpr const char* clan_tag = "PULMENU";
				constexpr const char* picture2 = "icon";

				HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG_AND_ADDITIONAL_ICON("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", false, 7, header, "Protections", 1.0f, "", 7, -1);

				HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(TRUE, FALSE);
			}
		}
	};
	inline Notifcations* g_NotificationManager;
}
