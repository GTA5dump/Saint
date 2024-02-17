#include "Render.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "D3DRenderer.hpp"
namespace Saint
{
	void tick()
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);
		ImGui::PushFont(g_D3DRenderer->m_DefaultFont);
		if (ImGui::Begin("##notifications", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize))
		{


		}
		ImGui::End();


		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImU32(ImColor(g_Render->m_OptionUnselectedBackgroundColor.r, g_Render->m_OptionUnselectedBackgroundColor.g, g_Render->m_OptionUnselectedBackgroundColor.b, 160)));

		Noti::RenderNotifications();

		ImGui::PopFont();
		ImGui::PopStyleColor(1);
	}

}