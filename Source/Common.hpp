#pragma once
#define MENU_VERSION "1.9.7"
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT _WIN32_WINNT_WIN7
#include <winsdkver.h>
#include <sdkddkver.h>
#include <windows.h>
#include <winternl.h>
#include <d3d11.h>

#include <cassert>
#include <cinttypes>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <deque>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <optional>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <vector>

// JSON
#include <JSON/json.hpp>
#include <JSON/json_fwd.hpp>

//Stack Walker
#include <stackwalker/Main/StackWalker/StackWalker.h>

// GTA-V
#include <GTAV-Classes/script/scrNativeHandler.hpp>
#include <GTAV-Classes/script/scrNativeRegistration.hpp>
#include <GTAV-Classes/script/scrNativeRegistrationTable.hpp>

#define BIGBASE_WIDE_IMPL(str) L ## str
#define BIGBASE_WIDE(str) BIGBASE_WIDE_IMPL(str)

#define BIGBASE_STRINGIZE_IMPL(x) #x
#define BIGBASE_STRINGIZE(x) BIGBASE_STRINGIZE_IMPL(x)

#define BRANDING "Saint"
using strung = std::string;

namespace Saint
{
	using namespace std::chrono_literals;
	namespace fs = std::filesystem;

	inline HMODULE g_Module{};
	inline std::atomic_bool g_Running = true;

	inline std::uint32_t g_SelectedPlayer{};

	inline bool g_LogScriptEvents = false;
	inline bool infoBeingDrawn = false;
	class stackWalker : public StackWalker {
	public:
		stackWalker() : StackWalker() {}
		stackWalker(ExceptType exType) : StackWalker(exType) {}
		virtual void OnOutput(LPCSTR szText);
		virtual void OnLoadModule(LPCSTR img, LPCSTR mod, DWORD64 baseAddr, DWORD size, DWORD result, LPCSTR symType, LPCSTR pdbName, ULONGLONG fileVersion);
		virtual void OnSymInit(LPCSTR szSearchPath, DWORD symOptions, LPCSTR szUserName);
		virtual void OnDbgHelpErr(LPCSTR szFuncName, DWORD gle, DWORD64 addr);
		virtual void OnCallstackEntry(CallstackEntryType eType, CallstackEntry& entry);
	};
}
#include "Settings.hpp"
#include "Logger.hpp"
#include "Util.hpp"
#include "Memory.hpp"
#include "Signatures.hpp"
#include "ScriptGlobal.hpp"
#include "DatBitBuffer.h"
