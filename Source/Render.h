#ifndef IMGUI_NOTIFY
#define IMGUI_NOTIFY

#pragma once
#include <vector>
#include <string>

#include "ImGui/imgui.h"
#include "UI/Framework.hpp"
#include "font_awesome.h"
#include "fa_solid_900.h"
#include "FiberHelper.hpp"
#include <set>
#define NOTIFY_MAX_MSG_LENGTH			4096		// Max message content length
#define NOTIFY_PADDING_X				5.f		// Bottom-left X padding
inline int NOTIFY_PADDING_Y = 1330.f;		// Bottom-left Y padding
#define NOTIFY_PADDING_MESSAGE_Y		4.f		// Padding Y between each message
#define NOTIFY_FADE_IN_OUT_TIME			1050			// Fade in and out duration
#define NOTIFY_DEFAULT_DISMISS			5000		// Auto dismiss after X ms (default, applied only of no data provided in constructors)
#define NOTIFY_OPACITY					0.8f		// 0-1 Toast opacity
#define NOTIFY_TOAST_FLAGS				ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing
// Comment out if you don't want any separator between title and content
#define NOTIFY_USE_SEPARATOR

#define NOTIFY_INLINE					inline
#define NOTIFY_NULL_OR_EMPTY(str)		(!str ||! strlen(str))
#define NOTIFY_FORMAT(fn, format, ...)	if (format) { va_list args; va_start(args, format); fn(format, args, __VA_ARGS__); va_end(args); }

typedef int ImGuiToastType;
typedef int ImGuiToastPhase;
typedef int ImGuiToastPos;
#pragma comment(lib, "winmm.lib")
#include <urlmon.h>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>



enum ImGuiToastType_
{
	ImGuiToastType_None,
	ImGuiToastType_Success,
	ImGuiToastType_Warning,
	ImGuiToastType_Error,
	ImGuiToastType_Info,
	ImGuiToastType_COUNT
};

enum ImGuiToastPhase_
{
	ImGuiToastPhase_FadeIn,
	ImGuiToastPhase_Wait,
	ImGuiToastPhase_FadeOut,
	ImGuiToastPhase_Expired,
	ImGuiToastPhase_COUNT
};

enum ImGuiToastPos_
{
	ImGuiToastPos_TopLeft,
	ImGuiToastPos_TopCenter,
	ImGuiToastPos_TopRight,
	ImGuiToastPos_BottomLeft,
	ImGuiToastPos_BottomCenter,
	ImGuiToastPos_BottomRight,
	ImGuiToastPos_Center,
	ImGuiToastPos_COUNT
};
class Ini2
{
private:
	std::string inifile;
public:
	Ini2(std::string file)
	{
		this->inifile = file;
	}

	void WriteString(std::string string, std::string app, std::string key)
	{
		WritePrivateProfileStringA(app.c_str(), key.c_str(), string.c_str(), this->inifile.c_str());
	}
	std::string GetString(std::string app, std::string key)
	{
		try {
			char buf[100];
			GetPrivateProfileStringA(app.c_str(), key.c_str(), "NULL", buf, 100, this->inifile.c_str());
			return (std::string)buf;
		}
		catch (...) {


		}
	}

	void WriteInt(int value, std::string app, std::string key)
	{
		WriteString(std::to_string(value), app, key);
	}
	void WriteHash(Hash value, std::string app, std::string key)
	{
		WriteString(std::to_string(value), app, key);
	}
	int GetInt(std::string app, std::string key)
	{
		return std::stoi(GetString(app, key));
	}

	void WriteFloat(float value, std::string app, std::string key)
	{
		WriteString(std::to_string(value), app, key);
	}
	float GetFloat(std::string app, std::string key)
	{
		return std::stof(GetString(app, key));
	}

	void WriteBool(bool value, std::string app, std::string key)
	{
		WriteString(std::to_string(value), app, key);
	}
	bool GetBool(std::string app, std::string key)
	{
		std::string Fetched = GetString(app, key);
		if (Fetched == "1") {
			return true;
		}
		if (Fetched == "0") {
			return false;
		}
		return false;
	}

};
class ImGuiToast
{
private:
	ImGuiToastType	type = ImGuiToastType_None;
	char			title[NOTIFY_MAX_MSG_LENGTH];
	char			content[NOTIFY_MAX_MSG_LENGTH];
	char			content2[NOTIFY_MAX_MSG_LENGTH];
	int				dismiss_time = 2000;
	uint64_t		creation_time = 0;

private:
	// Setters

	NOTIFY_INLINE auto set_title(const char* format, va_list args) { vsnprintf(this->title, sizeof(this->title), format, args); }

	NOTIFY_INLINE auto set_content(const char* format, va_list args) { vsnprintf(this->content, sizeof(this->content), format, args); }
	NOTIFY_INLINE auto set_content2(const char* format, va_list args) { vsnprintf(this->content, sizeof(this->content), format, args); }

public:

	NOTIFY_INLINE auto set_title(const char* format, ...) -> void { NOTIFY_FORMAT(this->set_title, format); }

	NOTIFY_INLINE auto set_content(const char* format, ...) -> void { NOTIFY_FORMAT(this->set_content, format); }
	NOTIFY_INLINE auto set_content2(const char* format, ...) -> void { NOTIFY_FORMAT(this->set_content2, format); }

	NOTIFY_INLINE auto set_type(const ImGuiToastType& type) -> void { IM_ASSERT(type < ImGuiToastType_COUNT); this->type = type; };

public:
	// Getters

	NOTIFY_INLINE auto get_title() -> char* { return this->title; };

	NOTIFY_INLINE auto get_default_title() -> char*
	{
		if (!strlen(this->title))
		{
			switch (this->type)
			{
			case ImGuiToastType_None:
				return NULL;
			case ImGuiToastType_Success:
				return NULL;
			case ImGuiToastType_Warning:
				return NULL;
			case ImGuiToastType_Error:
				return NULL;
			case ImGuiToastType_Info:
				return NULL;
			}
		}

		return this->title;
	};

	NOTIFY_INLINE auto get_type() -> const ImGuiToastType& { return this->type; };

	NOTIFY_INLINE auto get_color() -> const ImVec4&
	{
		switch (this->type)
		{
		case ImGuiToastType_None:
			return { 255, 255, 255, 255 }; // White
		case ImGuiToastType_Success:
			return { 0, 255, 0, 255 }; // Green
		case ImGuiToastType_Warning:
			return { 255, 255, 0, 255 }; // Yellow
		case ImGuiToastType_Error:
			return { 255, 0, 0, 255 }; // Error
		case ImGuiToastType_Info:
			return { 0, 157, 255, 255 }; // Blue
		}
	}

	NOTIFY_INLINE auto get_icon() -> const char*
	{
		switch (this->type)
		{
		case ImGuiToastType_None:
			return NULL;
		case ImGuiToastType_Success:
			return NULL;
		case ImGuiToastType_Warning:
			return NULL;
		case ImGuiToastType_Error:
			return NULL;
		case ImGuiToastType_Info:
			return NULL;
		}
	}

	NOTIFY_INLINE auto get_content() -> char* { return this->content; };

	NOTIFY_INLINE auto get_elapsed_time() { return GetTickCount64() - this->creation_time; }
	NOTIFY_INLINE auto get_dismiss_time() -> const int {
		return this->dismiss_time;
	}
	NOTIFY_INLINE auto get_phase() -> const ImGuiToastPhase&
	{
		const auto elapsed = get_elapsed_time();

		if (elapsed > NOTIFY_FADE_IN_OUT_TIME + this->dismiss_time + NOTIFY_FADE_IN_OUT_TIME)
		{
			return ImGuiToastPhase_Expired;
		}
		else if (elapsed > NOTIFY_FADE_IN_OUT_TIME + this->dismiss_time)
		{
			return ImGuiToastPhase_FadeOut;
		}
		else if (elapsed > NOTIFY_FADE_IN_OUT_TIME)
		{
			return ImGuiToastPhase_Wait;
		}
		else
		{
			return ImGuiToastPhase_FadeIn;
		}
	}

	NOTIFY_INLINE auto get_fade_percent() -> const float
	{
		const auto phase = get_phase();
		const auto elapsed = get_elapsed_time();

		if (phase == ImGuiToastPhase_FadeIn)
		{
			return ((float)elapsed / (float)NOTIFY_FADE_IN_OUT_TIME) * NOTIFY_OPACITY;
		}
		else if (phase == ImGuiToastPhase_FadeOut)
		{
			return (1.f - (((float)elapsed - (float)NOTIFY_FADE_IN_OUT_TIME - (float)this->dismiss_time) / (float)NOTIFY_FADE_IN_OUT_TIME)) * NOTIFY_OPACITY;
		}

		return 1.f * NOTIFY_OPACITY;
	}

public:
	// Constructors

	ImGuiToast(ImGuiToastType type, int dismiss_time = NOTIFY_DEFAULT_DISMISS)
	{
		IM_ASSERT(type < ImGuiToastType_COUNT);

		this->type = type;
		this->dismiss_time = 2000;
		this->creation_time = GetTickCount64();

		memset(this->title, 0, sizeof(this->title));
		memset(this->content, 0, sizeof(this->content));
		memset(this->content2, 0, sizeof(this->content2));
	}

	ImGuiToast(ImGuiToastType type, const char* format, ...) : ImGuiToast(type) { NOTIFY_FORMAT(this->set_content, format); }

	ImGuiToast(ImGuiToastType type, int dismiss_time, const char* format, ...) : ImGuiToast(type, dismiss_time) { NOTIFY_FORMAT(this->set_content, format); }
};

namespace Saint {
	inline void update() {
		if (g_Render->reso == 0) {
			NOTIFY_PADDING_Y = 1000.f;
		}
		if (g_Render->reso == 1) {
			NOTIFY_PADDING_Y = 1330.f;
		}
	}
	inline bool DoesIniExists(const char* path)
	{

		struct stat buffer;
		return (stat(path, &buffer) == 0);

	}
	inline bool wants_sounds() {

		std::string MenuFolderPath = "C:\\Saint\\";
		if (DoesIniExists((MenuFolderPath + "tutorial" + ".ini").c_str())) {
			Ini2* ColorIni = new Ini2(MenuFolderPath + "tutorial" + ".ini");

			if (ColorIni->GetBool("Tutorial", "Sounds") == true) {
				return true;
			}
			if (ColorIni->GetBool("Tutorial", "Sounds") == false) {
				return false;
			}
			return false;




		}
	}
	namespace Noti
	{
		
		NOTIFY_INLINE std::vector<ImGuiToast> notifications;

		/// <summary>
		/// Insert a new toast in the list
		/// </summary>
		NOTIFY_INLINE VOID InsertNotification(ImGuiToast toast)
		{
			for (auto& noti : notifications) {
				if (noti.get_title() == toast.get_title()) {
					return;
				}
			}
			update();
			if (notifications.size() < 10) {
				if (wants_sounds()) {
					PlaySound(TEXT("C:\\Saint\\Sounds\\Notification.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);

				}
				notifications.push_back(toast);
			}
		}

		/// <summary>
		/// Remove a toast from the list by its index
		/// </summary>
		/// <param name="index">index of the toast to remove</param>
		NOTIFY_INLINE VOID RemoveNotification(int index)
		{
			notifications.erase(notifications.begin() + index);
		}

		/// <summary>
		/// Render toasts, call at the end of your rendering!
		/// </summary>
		NOTIFY_INLINE VOID RenderNotifications()
		{
			
			const auto vp_size = ImGui::GetMainViewport()->Size;

			float height = 0.f;

			for (auto i = 0; i < notifications.size(); i++)
			{

				auto* current_toast = &notifications[i];


				// Remove toast if expired
				if (current_toast->get_phase() == ImGuiToastPhase_Expired)
				{
					RemoveNotification(i);
					continue;
				}




				// Get icon, title and other data
				const auto icon = current_toast->get_icon();
				const auto title = current_toast->get_title();
				const auto content = current_toast->get_content();
				const auto default_title = current_toast->get_default_title();
				const auto opacity = current_toast->get_fade_percent(); // Get opacity based of the current phase
				const auto time = current_toast->get_elapsed_time();
				std::string content_s = current_toast->get_content();
				int length = content_s.length();
				// Window rendering
				auto text_color = current_toast->get_color();
				text_color.w = opacity;


				// Generate new unique name for this toast
				char window_name[50];
				sprintf_s(window_name, "##TOAST%d", i);

				//ImGui::PushStyleColor(ImGuiCol_Text, text_color);


				ImGui::SetNextWindowPos(ImVec2(vp_size.x - NOTIFY_PADDING_X, vp_size.y - NOTIFY_PADDING_Y - height), ImGuiCond_Always, ImVec2(1.0f, 1.0f));
				ImGui::SetNextWindowSize(ImVec2(NULL, 50), 0);
				ImGui::Begin(window_name, NULL, NOTIFY_TOAST_FLAGS);

				// Here we render the toast content
				{




					ImDrawList* draw_list = ImGui::GetWindowDrawList();
					ImVec2 panelPos = ImGui::GetWindowPos();
					auto height = ImGui::GetWindowHeight();
					ImGui::PushTextWrapPos(vp_size.x / 3.f); // We want to support multi-line text, this will wrap the text after 1/3 of the screen width
					for (int i = 0; i < height; i++)
					{
						int timefr = time / 11.7f;
						draw_list->AddRectFilled(ImVec2(panelPos.x, panelPos.y + i), ImVec2(panelPos.x + 5, panelPos.y + 90), ImU32(ImColor(g_Render->m_HeaderBackgroundColor.r, g_Render->m_HeaderBackgroundColor.g, g_Render->m_HeaderBackgroundColor.b, 255)));
						//line
						draw_list->AddRectFilled(ImVec2(panelPos.x + 5.5, panelPos.y + i + 48), ImVec2(panelPos.x + 350 - timefr, panelPos.y + 99), ImU32(ImColor(255, 255, 255, 255)));

					}





					ImGui::InvisibleButton("##123", ImVec2(1, panelPos.y), 0); ImGui::SameLine();
					ImGui::Text(content); ImGui::SameLine(); ImGui::InvisibleButton("##1234", ImVec2(1, panelPos.y), 0);


					ImGui::PopTextWrapPos();

				}
				//ImGui::PopStyleColor();
				height -= ImGui::GetWindowHeight() + NOTIFY_PADDING_MESSAGE_Y;



				// End
				ImGui::End();
			}
		}

		/// <summary>
		/// Adds font-awesome font, must be called ONCE on initialization
		/// <param name="FontDataOwnedByAtlas">Fonts are loaded from read-only memory, should be set to false!</param>
		/// </summary>
		/// 
		NOTIFY_INLINE VOID MergeIconsWithLatestFont(float font_size, bool FontDataOwnedByAtlas = false)
		{
			static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

			ImFontConfig icons_config;
			icons_config.MergeMode = true;
			icons_config.PixelSnapH = true;
			icons_config.FontDataOwnedByAtlas = FontDataOwnedByAtlas;

			ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)fa_solid_900, sizeof(fa_solid_900), font_size, &icons_config, icons_ranges);
		}

	}

#endif
}
namespace Saint
{
	void tick();
}