#include "Natives.hpp"
namespace Saint::UserInterface 
{
	enum TextPosition {
		Left = 0,
		Right = 1,
		Center = 2,
	};
	class DrawingFunctions2 {
	public:
		void Rectangle(float x, float y, float width, float height, Color color)
		{
			GRAPHICS::DRAW_RECT(x, y, width, height, color.r, color.g, color.b, color.a, 0);
		}
		void Sprite(const char* dict, const char* texture, float x, float y, float width, float height, Color color, float rotation)
		{
			if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict))
			{
				GRAPHICS::DRAW_SPRITE(dict, texture, x, y, width, height, rotation, color.r, color.g, color.b, color.a, 0, -1);
			}
			else
			{
				GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict, false);
			}
		}
		void Text(TextPosition position, const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow, bool wrap = false)
		{
			if (position == TextPosition::Left) {
				HUD::SET_TEXT_SCALE(size, size);
				HUD::SET_TEXT_FONT(static_cast<int>(font));
				HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, 255);
				if (outline)
					HUD::SET_TEXT_OUTLINE();
				if (shadow)
					HUD::SET_TEXT_DROP_SHADOW();
				if (wrap) {

				}
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
				HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
			}
			if (position == TextPosition::Right) {
				HUD::SET_TEXT_WRAP(0.f, x);
				HUD::SET_TEXT_RIGHT_JUSTIFY(true);
				HUD::SET_TEXT_SCALE(size, size);
				HUD::SET_TEXT_FONT(static_cast<int>(font));
				HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, 255);
				if (outline)
					HUD::SET_TEXT_OUTLINE();
				if (shadow)
					HUD::SET_TEXT_DROP_SHADOW();
				if (wrap) {

				}
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
				HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
			}
			if (position == TextPosition::Center) {
				HUD::SET_TEXT_CENTRE(true);
				HUD::SET_TEXT_SCALE(size, size);
				HUD::SET_TEXT_FONT(static_cast<int>(font));
				HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, 255);
				if (outline)
					HUD::SET_TEXT_OUTLINE();
				if (shadow)
					HUD::SET_TEXT_DROP_SHADOW();
				if (wrap) {

				}
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
				HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
			}
		}
		void Text(std::string text, std::float_t x, std::float_t y, Font font, std::float_t scale, RGBA color, bool centered, bool right_justified, bool outlined)
		{
			HUD::SET_TEXT_FONT(static_cast<int>(font));
			HUD::SET_TEXT_SCALE(0.f, scale);
			HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
			if (right_justified)
				HUD::SET_TEXT_WRAP(0.f, x);
			else HUD::SET_TEXT_WRAP(0.f, 1.f);
			HUD::SET_TEXT_CENTRE(centered);
			if (outlined)
				HUD::SET_TEXT_OUTLINE();
			HUD::SET_TEXT_RIGHT_JUSTIFY(right_justified);
			HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_WEBSITE(text.c_str());
			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, NULL);
		}
	};
	
	DrawingFunctions2* drawingFunctions;
	
}

namespace Saint {
	
}