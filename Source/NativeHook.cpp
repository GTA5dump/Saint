#include "NativeHook.hpp"
#include "Hooking.hpp"
#include "Signatures.hpp"

namespace Saint
{
	auto ALL_SCRIPT_HASH = Joaat("ALL_SCRIPTS");

	NativeHooks::NativeHooks()
	{
		AddNativeDetour("SGI", Joaat("main_persistent"), 0x767FBC2AC802EF3D, Hooks::GetStatInt);
		AddNativeDetour("NSH", Joaat("maintransition"), 0x6F3D4ED9BEE4E61D, Hooks::NETWORK_SESSION_HOST);
		AddNativeDetour("HFWW", Joaat("ALL_SCRIPTS"), 0xEB354E5376BC81A7, Hooks::HUD_FORCE_WEAPON_WHEEL);
		AddNativeDetour("DCA", Joaat("am_mp_smpl_interior_int"), 0xFE99B66D079CF6BC, Hooks::DISABLE_CONTROL_ACTION);
		AddNativeDetour("SCPW", Joaat("am_mp_smpl_interior_int"), 0xADF692B254977C0C, Hooks::SET_CURRENT_PED_WEAPON);
		AddNativeDetour("DCA", Joaat("am_mp_property_int"), 0xFE99B66D079CF6BC, Hooks::DISABLE_CONTROL_ACTION);
		AddNativeDetour("SCPW", Joaat("am_mp_property_int"), 0xADF692B254977C0C, Hooks::SET_CURRENT_PED_WEAPON);
		AddNativeDetour("DCA", Joaat("freemode"), 0xFE99B66D079CF6BC, Hooks::DISABLE_CONTROL_ACTION);
		AddNativeDetour("SCPW", Joaat("freemode"), 0xADF692B254977C0C, Hooks::SET_CURRENT_PED_WEAPON);

		for (auto& entry : *g_GameVariables->m_ScriptProgramTable)
			if (entry.m_program)
				HookProgram(entry.m_program);

		g_NativeHooks = this;
	}

	NativeHooks::~NativeHooks()
	{
		m_ScriptHooks.clear();
		g_NativeHooks = nullptr;
	}

	void NativeHooks::AddNativeDetour(const char* name, rage::scrNativeHash hash, rage::scrNativeHandler detour)
	{
		AddNativeDetour(name, ALL_SCRIPT_HASH, hash, detour);
	}

	void NativeHooks::AddNativeDetour(const char* name, rage::joaat_t script_hash, rage::scrNativeHash hash, rage::scrNativeHandler detour)
	{
		if (const auto& it = m_NativeRegistrations.find(script_hash); it != m_NativeRegistrations.end())
		{
			it->second.emplace_back(hash, detour);
			return;
		}

		m_NativeRegistrations.emplace(script_hash, std::vector<NativeDetour>({ { hash, detour } }));

		if (Flags->isDev()) {
			g_Logger->Debug("Scanned Native %s.", name);
		}
	}
	

	void NativeHooks::HookProgram(rage::scrProgram* program)
	{
		std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> native_replacements;
		const auto script_hash = program->m_name_hash;

		// Functions that need to be detoured for all scripts
		if (const auto& pair = m_NativeRegistrations.find(ALL_SCRIPT_HASH); pair != m_NativeRegistrations.end())
			for (const auto& native_hook_reg : pair->second)
				native_replacements.insert(native_hook_reg);

		// Functions that only need to be detoured for a specific script
		if (const auto& pair = m_NativeRegistrations.find(script_hash); pair != m_NativeRegistrations.end())
			for (const auto& native_hook_reg : pair->second)
				native_replacements.insert(native_hook_reg);

		if (!native_replacements.empty())
		{
			m_ScriptHooks.emplace(
				program,
				std::make_unique<ScriptHook>(program, native_replacements)
			);
		}
	}

	void NativeHooks::UnhookProgram(rage::scrProgram* program)
	{
		m_ScriptHooks.erase(program);
	}
}