#pragma once
#include "../Common.hpp"
#include "../Types.hpp"
#include "TextBox.hpp"
#include "AbstractSubmenu.hpp"

namespace Saint::UserInterface
{
	
	class tooltipHandler {
	public:
		tooltipHandler(const char* m_name) {
			name = m_name;
		}
	public:
		const char* name;
	};
	
	enum class Font : std::int32_t
	{
		ChaletLondon = 0,
		HouseScript = 1,
		Monospace = 2,
		Wingdings = 3,
		ChaletComprimeCologne = 4,
		Pricedown = 7
	};
	enum class Outfits : std::int32_t
	{
		Face = 0,
		Head = 1,
		Hair = 2,
		Torso = 3,
		Torso2 = 4,
		Legs = 5,
		Hands = 6,
		Feet = 7,
		Eyes = 8,
		Accessories = 9,
		Vests = 10,
		Decals = 11,
	};
	enum class Props : std::int32_t
	{
		Hats = 0,
		Glasses = 1,
		Ears = 2,
		Watches = 3,
		Bracelets = 4,

	};
	enum class HeaderType : std::int32_t
	{
		Static = 0,
		YTD = 1
	};

	struct Rectangle
	{
		Vector2 m_Center;
		Vector2 m_Size;

		bool IsInBounds(Vector2 point)
		{
			auto left = m_Center.x - (m_Size.x / 2.f);
			auto right = m_Center.x + (m_Size.x / 2.f);
			auto top = m_Center.y + (m_Size.y / 2.f);
			auto bottom = m_Center.y - (m_Size.y / 2.f);

			if (point.x > right || point.x < left)
				return false;
			if (point.y > top || point.y < bottom)
				return false;

			return true;
		}
	};

	struct RGBA
	{
		std::int32_t r;
		std::int32_t g;
		std::int32_t b;
		std::int32_t a;
		RGBA(std::int32_t r, std::int32_t g, std::int32_t b, std::int32_t a)
			: r(r), g(g), b(b), a(a) {}
	};
	class SubmenuIndicators {
	public:
		float width_offset = -0.001f;
		float x_offset = 0.0f;
		const char* names[3]
		{
			"Arrows",
			"Lines",
			"None"
		};
		std::size_t position = 1;
	};
	class Glare {
	public:
		float height_offset;
	};
	class UIManager
	{
	public:
		explicit UIManager() = default;
		~UIManager() noexcept = default;
		UIManager(UIManager const&) = delete;
		UIManager(UIManager&&) = delete;
		UIManager& operator=(UIManager const&) = delete;
		UIManager& operator=(UIManager&&) = delete;

		template <typename SubmenuType, typename ...TArgs>
		void draw_submenu(TArgs&&... args)
		{
			auto sub = std::make_unique<SubmenuType>(std::forward<TArgs>(args)...);
			if (m_SubmenuStack.empty())
			{
				m_SubmenuStack.push(sub.get());
			}

			m_AllSubmenus.push_back(std::move(sub));
		}

		void SwitchToSubmenu(std::uint32_t id)
		{
			for (auto&& sub : m_AllSubmenus)
			{
				if (sub->GetId() == id)
				{
					m_SubmenuStack.push(sub.get());
					return;
				}
			}
		}

		std::stack<AbstractSubmenu*, std::vector<AbstractSubmenu*>> GetSubmenus() { return m_SubmenuStack; }

		void OnTick();
	public:
		
		std::mutex m_Mutex;

		bool m_Opened = false;
		bool m_MouseLocked = false;
		float m_PosX = 0.18f;
		float m_PosY = 0.1f;
		float m_Width = 0.20;
		std::size_t m_OptionsPerPage = 13;
		bool m_Sounds = true;
		bool welcomemessage = false;

		// Glare
		bool m_render_glare = { true };
		int m_glare_handle;
		float m_glare_direction;
		void draw_glare();

		int y_test = 70;


		int open_key = 0x73;
		//ToolTip
		void RenderToolTip();
		RGBA m_ToolTipColor = RGBA{ 255, 255, 255, 255 };
		Font m_ToolTipFont = Font::ChaletLondon;
		float m_ToolTipTextSize = 0.4f;
		//resolution
		const char* Resolution[2] =
		{
			"1920x1080",
			"2560x1440"
		};
		std::size_t reso = 1920;
		// Header
		float m_HeaderHeight = { 0.083f };
		bool m_HeaderTextData = false;
		bool m_HeaderNativeText = true;
		float m_HeaderTextSize = 1.f;
		Font m_HeaderFont = Font::HouseScript;
		
		HeaderType m_HeaderType = HeaderType::Static;
		HeaderType m_HeaderType2 = HeaderType::Static;

		bool m_HeaderGradientTransparent = false;
		bool m_HeaderGradientFlip = false;
		float m_HeaderGradientStretch = 0.f;
		float m_HeaderGradientFiller = 0.f;

		// Footer Text
		bool LeftFooterText = false;
		bool RightFooterText = true;
		float m_FooterTextSize = 0.27f;
		Font m_FooterTextFont = Font::ChaletLondon;
		float m_FooterTextPadding = 2.1f;
		

		//enables
		bool footer_enabled = true;
		bool lines_enabled = false;

		Glare glare;

		// Smooth Scrolling
		float lerp(float a, float b, float t)
		{
			return a + t * (b - a);
		}

		float m_CurrentCoord = m_PosY;

		//Themes
		const char* ThemeList[9]
		{
			"Saint Purple",
			"Red Salmon",
			"Sapphire Blue",
			"Soft Black",
			"Emerald Green",
			"Violet Purple",
			"Salmon Pink",
			"Stash Skid Menu",
			"Ozark"
		};
		std::size_t ThemeIterator = 0;

		const char* HeaderFont[6]
		{
			"Chalet London",
			"House Script",
			"Monospace",
			"Wingdings",
			"Chalet Comprime Cologne",
			"Pricedown"
		};
		const char* HeaderFont2[7]
		{
			"Chalet London",
			"House Script",
			"Monospace",
			"Wingdings",
			"Chalet Comprime Cologne",
			"Pricedown",
			"Custom"
		};
		std::size_t HeaderFontIterator = 3;
		std::size_t HeaderFontIterator2 = 3;
		bool center_head = false;
		Outfits outfits = Outfits::Face;

		Props props = Props::Hats;


		// Options
		float m_OptionHeight = 0.0315f;
		float m_OptionTextSize = 0.25f;
		Font m_OptionFont = Font::ChaletLondon;
		Font m_SeperatorFont = Font::HouseScript;
		float m_OptionPadding = 2.1f;
		std::size_t option_font_it = 0;

		//submenubar
		bool submenu_enabled = true;

		bool dynamic_text = false;

		bool ytd_header = false;

		
		float m_SubheaderHeight = 0.03f;

		//misc
		

		bool animation_enabled = false;

		std::string header_name = "Saint";

		// Footer
		bool m_dynamic_footer = { false };
		int m_option_count;
		int m_current_option;
		int m_previous_option;

		float m_FooterHeight = 0.029;
		float m_FooterSpriteSize = 0.027000f;
		

		//Enterable
		
		SubmenuIndicators enterable;
		bool controlsEnabled = true;
		// Bool Toogles
		bool ToggledOn = false;
		bool ToggledOff = false;
		float m_ToggleSize = { 0.028f };
		const char* ToggleList[5]
		{
			"Circles",
			"Checkmarks (Squares)",
			"None",
			"Checkmarks",
			"Custom",
		};
		std::size_t ToggleIterator = 0;
		std::string custom_toggle_dict_on = "commonmenu";
		std::string custom_toggle_asset_on = "shop_tick_icon";
		std::string custom_toggle_dict_off = "commonmenu";
		std::string custom_toggle_asset_off = "shop_tick_icon";
		float toggle_height = 0.032500f;
		float toggle_width = 0.016960f;
		float toggle_height_off = 0.041000f;
		float toggle_width_off = 0.024000f;
		bool toggle_show_on = true;
		bool toggle_show_off = false;
		float toggle_on_rotation = 5.0f;
		float toggle_off_rotation = 45.000;

		//Header
		float header_x_offset = -0.063;
		//smooth scroll
		float smooth_scroll_speed = 0.170000f;

		//break
		bool break_italic = true;

		//footer
		bool freeze_icon = false;

		//submenu
		int sub_alpha = 190;

		// Description
		float m_DescriptionHeightPadding = 0.01f;
		float m_DescriptionHeight = 0.060f;
		float m_DescriptionHeight2 = 0.033f;
		float m_DescriptionTextSize = 0.28f;
		Font m_DescriptionFont = Font::ChaletLondon;
		float m_DescriptionSpriteSize = 0.025f;
		float m_DescriptionPadding = 2.1f;

		float glare_x_offset = 0.014;

		bool fov_circle = false;

		bool m_MenuOpeningAnimation = false;
		int g_MenuAlpha = 255;
		const char* m_CurrentSubMenuName = "Hello";
		bool m_AnimationCheck = false;
		float m_DrawBaseY{};
		Vector2 GetMousePos();
		void SetMousePos(int x, int y);

		const char* to_add = "";

		bool tooltips_enabled = true;

		bool connect_description = false;

		float description_x = 0.21f;
		float description_y = 0.0f;
		float description_x2 = 0.21f;
		float description_y2 = 0.0f;

		bool scrollbar = false;

		std::stack<AbstractSubmenu*, std::vector<AbstractSubmenu*>> m_SubmenuStack;
		std::vector<std::unique_ptr<AbstractSubmenu>> m_AllSubmenus;
		
		
	public:
		Color m_DescriptionBackgroundColor{ 0, 0, 0, 160 };
		Color m_DescriptionTextColor{ 255,255,255, 255 };
		Color m_DescriptionSpriteColor{ 255,255,255, 255 };
		//toggles
		Color m_ToggleOnColor{ 130, 214, 157, 255 };
		Color m_ToggleOffColor{ 200, 55, 80, 255 };
		Color m_ToggleCheckColor{ 255,255,255, 255 };
		//footer
		Color m_FooterBackgroundColor{ 0, 0, 0, 255 };
		Color m_FooterSpriteColor{ 255,255,255, 255 };
		Color m_FooterTextColor{ 255,255,255, 255 };
		//subheader
		Color m_SubheaderBackground{ 0, 0, 0, 255 };
		Color m_SubheaderText{ 255,255,255, 255 };
		Color m_SubheaderTextRight{ 255,255,255, 255 };
		//misc
		Color m_RadiusSphere{ 255, 0, 0, 160 };
		//option selected/off
		Color m_OptionSelectedTextColor{ 0,0,0, 255 };
		Color m_OptionUnselectedTextColor{ 255,255,255, 255 };
		Color m_OptionSelectedBackgroundColor{ 255, 255, 255, 255 };
		Color m_OptionUnselectedBackgroundColor{ 0, 0, 0, 160 };
		//header
		Color m_HeaderBackgroundColor{ 255, 150, 184, 255 };
		Color m_HeaderTextColor{ 255, 255, 255, 255 };
		Color m_HeaderGradientColorLeft{ 0, 0, 0, 255 };
		Color m_HeaderGradientColorRight{ 255, 255, 255, 255 };
	public:
		std::int32_t m_OpenDelay = 200;
		std::int32_t m_BackDelay = 300;
		std::int32_t m_EnterDelay = 300;
		std::int32_t m_VerticalDelay = 120;
		std::int32_t m_HorizontalDelay = 120;
	private:
		bool m_OpenKeyPressed = false;
		bool m_OpenKeyPressed2 = false;
		bool m_BackKeyPressed = false;
		bool m_EnterKeyPressed = false;
		bool m_UpKeyPressed = false;
		bool m_DownKeyPressed = false;
		bool m_LeftKeyPressed = false;
		bool m_RightKeyPressed = false;
		void CheckForInput();
		void HandleInput();
		void ResetInput();


		void DrawHeader();
		void drawstring(char* text, float X, float Y);
		void setupdraw(bool outline);


		void DrawOption(AbstractOption* opt, bool selected);
		void DrawFooter();
		void DrawDescription();
		void DrawSubmenuBar(AbstractSubmenu* sub);

		bool IsMouseLocked();
		Rectangle GetMenuRect();



		

	};

}

namespace Saint
{
	inline std::unique_ptr<UserInterface::UIManager> g_Render;
}