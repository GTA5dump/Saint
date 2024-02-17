#include <string>
#include "Signatures.hpp"
#include "LogScript.hpp"
#include "UI/Framework.hpp"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "D3DRenderer.hpp"
#include "ImGui/imgui_internal.h"
#include "UI/Framework.hpp"
#include "Features.h"
namespace Saint
{
	bool LogScript::IsInitialized()
	{
		return m_Initialized;
	}

	ScriptType LogScript::GetType()
	{
		return ScriptType::D3D;
	}

	void LogScript::Initialize()
	{
		m_Initialized = true;
	}

	void LogScript::Destroy()
	{
	}
	ImVec2 addDX(ImVec2* vectorA, ImVec2* vectorB) {
		ImVec2 result;
		result.x = vectorA->x;
		result.y = vectorA->y;
		result.x += vectorB->x;
		result.y += vectorB->y;

		return result;
	}
	void DrawRect2(ImU32 Color, ImVec2 Pos, ImVec2 Size, bool Filled, ImDrawList* draw_list)
	{
		ImVec2 m_Position = { 0, 0 };
		ImVec2 size = ImGui::CalcItemSize(ImVec2(Size.x, Size.y), 0.0f, 0.0f);
		ImVec2 poss = ImVec2(Pos.x + m_Position.x, Pos.y + m_Position.y);
		const ImRect c_IM(ImVec2(Pos.x + m_Position.x, Pos.y + m_Position.y), addDX(&poss, &size));

		if (!Filled) draw_list->AddRectFilled(c_IM.Max, c_IM.Min, ImGui::GetColorU32(Color));
		else draw_list->AddRectFilledMultiColor(c_IM.Max, c_IM.Min, ImGui::GetColorU32(Color), ImGui::GetColorU32(Color), ImGui::GetColorU32(Color), ImGui::GetColorU32(Color));
	}
	namespace
	{
		std::size_t s_LastLogCount = 0;
	}
	ImU32 ConvertRectColor(Color p1) {
		float p2 = 1.0f;
		__int32 p3 = 255;
		float p4 = (p2 / p3) * p1.r;
		float p5 = (p2 / p3) * p1.g;
		float p6 = (p2 / p3) * p1.b;
		float p7 = (p2 / p3) * p1.a;
		return ImU32(ImColor(p4, p5, p6, p7));
	}
	static char buf1[64] = "Fortnite";
	void remove_from_string(std::string str, std::string what) {
		std::size_t spacePos = str.find(' ');
		str = str.substr(spacePos + 1);
	}
	
	bool Command(std::string str, std::string check)
	{
		std::size_t found = str.find(' ');
		if (found != std::string::npos)
		{
			if (str.substr(0, found) == check)
			{
				str = str.substr(found + 1, str.size());
				return true;
			}
		}
		else
		{
			if (str == check)
				return true;
		}
		return false;
	}
	void copytoclipboard2(const std::string& tocopy)
	{
		OpenClipboard(NULL);
		EmptyClipboard();
		HGLOBAL HG = GlobalAlloc(GMEM_MOVEABLE, tocopy.size());
		if (!HG)
		{
			CloseClipboard();
		}
		memcpy(GlobalLock(HG), tocopy.c_str(), tocopy.size());
		GlobalUnlock(HG);
		SetClipboardData(CF_TEXT, HG);
		CloseClipboard();
		GlobalFree(HG);
	}
	ImU32 RGBtoU32(int r, int g, int b)
	{
		float fr = (float)r / 255.0;
		float fg = (float)g / 255.0;
		float fb = (float)b / 255.0;
		return ImGui::GetColorU32(ImVec4(fr, fg, fb, 1));
	}
	bool has_string_attached2(const std::string& str, const std::string& check)
	{
		std::string strLower = str;
		std::string checkLower = check;
		std::transform(strLower.begin(), strLower.end(), strLower.begin(), [](unsigned char c) {
			return std::tolower(c);
			});
		std::transform(checkLower.begin(), checkLower.end(), checkLower.begin(), [](unsigned char c) {
			return std::tolower(c);
			});

		size_t found = strLower.find(checkLower);
		if (found != std::string::npos) {
			return true;
		}
		else {
			return false;
		}
	}
	void LogScript::Tick()
	{
			if (g_Render->m_Opened && g_Render->m_HeaderTextData)
			{
				auto m_Hello = ImGui::CalcTextSize("Hello").y;
				auto m_XPosition = ((g_Render->m_PosX - (g_Render->m_Width / g_Render->m_FooterTextPadding)) * ImGui::GetIO().DisplaySize.x);
				auto m_YPosition = (g_Render->m_PosY + (g_Render->m_HeaderHeight / 100.f) + ((ImGui::CalcTextSize(g_Render->m_CurrentSubMenuName).y / 1920) / 4.f)) * ImGui::GetIO().DisplaySize.y;
				if (ImGui::Begin("", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground)) {
					ImGui::PushFont(g_D3DRenderer->m_HeaderFontData);
					auto DrawList = ImGui::GetWindowDrawList();
					DrawList->AddText(ImVec2(m_XPosition, m_YPosition), ImColor(g_Render->m_HeaderTextColor.r, g_Render->m_HeaderTextColor.g, g_Render->m_HeaderTextColor.b, g_Render->m_HeaderTextColor.a), g_Render->m_CurrentSubMenuName);
					ImGui::PopFont();
				}
			}  ImGui::End();
			if (g_Settings.command_window)
			{
				
			} 
		
		if (g_Render->m_Opened && g_Settings.m_LogWindow)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 250), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
			if (ImGui::Begin("Logger"))
			{
				std::lock_guard lock(g_Logger->GetMutex());
				auto msgs = g_Logger->GetMessages();

				for (std::size_t i = 0; i < msgs.second; ++i)
				{
					ImGui::TextUnformatted(msgs.first[i].get());
				}

				if (s_LastLogCount != msgs.second)
				{
					s_LastLogCount = msgs.second;
					ImGui::SetScrollHereY(1.f);
				}
			}  ImGui::End();
		}
	}
}
