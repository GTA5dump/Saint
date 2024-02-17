#pragma once
#include "Disassembler.h"
#include "Logger.hpp"
#include "Common.hpp"
#include <Psapi.h>
#include <MinHook/src/hde/hde64.h>
namespace Saint
{
	namespace modules {
		inline std::map<strung, std::pair<uint64_t, uint64_t>> g_moduleMap{};
		inline decltype(g_moduleMap) getAllModuleInfos() {
			decltype(g_moduleMap) map{};
			HMODULE modules[1024]{};
			HANDLE process{ GetCurrentProcess() };
			DWORD cbNeeded{};
			if (K32EnumProcessModules(process, modules, 1024, &cbNeeded)) {
				for (int32_t i{}; i != (cbNeeded / sizeof(HMODULE)); ++i) {
					//Get the full path to the module's file.
					char modNameCharArray[MAX_PATH];
					if (K32GetModuleFileNameExA(process, modules[i], modNameCharArray, MAX_PATH)) {
						strung modName(modNameCharArray);
						MODULEINFO info{};
						if (K32GetModuleInformation(process, modules[i], &info, sizeof(MODULEINFO))) {
							map.emplace(modName, std::make_pair(uintptr_t(info.lpBaseOfDll), uintptr_t(info.SizeOfImage)));
						}
					}
				}
			}
			return map;
		}
		template <typename addressType = uintptr_t>
		inline char const* getModuleNameFromAddressImpl(addressType address) {
			for (auto const& [key, val] : g_moduleMap) {
				if (uintptr_t(address) > val.first && uintptr_t(address) < (val.first + val.second)) {
					return std::format("{}+0x{:X}", key.substr(key.find_last_of('\\') + 1, key.find('.') + 3), uintptr_t(address) - val.first).c_str();
				}
			}
			return {};
		}
		template <typename addressType = uintptr_t>
		inline char const* getModuleNameFromAddress(addressType address) {
			if (g_moduleMap.empty())
				g_moduleMap = getAllModuleInfos();
			auto returnValue = getModuleNameFromAddressImpl<addressType>(address);
			if (!returnValue) {
				g_moduleMap.clear();
				g_moduleMap = getAllModuleInfos(); //Incase the module isn't found, we update the module map and try again. (vali skid)
				returnValue = getModuleNameFromAddressImpl<addressType>(address);
			}
			return returnValue;
		}
	}
	namespace exceptions {
		inline bool attemptStackRecovery(PEXCEPTION_POINTERS exceptionInfo) {
			auto& ctx = exceptionInfo->ContextRecord;
			hde64s hde{};
			if (const auto len = x64::getInstructionLength(reinterpret_cast<uint8_t*>(ctx->Rip)); len) {
				ctx->Rip += len;
				return true;
			}
			else if (uint8_t len = hde64_disasm((void*)ctx->Rip, &hde); len) {
				return len;
			}
			return false;
		}
		inline std::map<long, std::string> g_exceptionTypes = {
			{ 0x00000000L, "STATUS_WAIT_0" },
			{ 0x00000080L, "STATUS_ABANDONED_WAIT_0" },
			{ 0x000000C0L, "STATUS_USER_APC" },
			{ 0x00000102L, "STATUS_TIMEOUT" },
			{ 0x00000103L, "STATUS_PENDING" },
			{ 0x00010001L, "DBG_EXCEPTION_HANDLED" },
			{ 0x00010002L, "DBG_CONTINUE" },
			{ 0x40000005L, "STATUS_SEGMENT_NOTIFICATION" },
			{ 0x40000015L, "STATUS_FATAL_APP_EXIT" },
			{ 0x40010001L, "DBG_REPLY_LATER" },
			{ 0x40010003L, "DBG_TERMINATE_THREAD" },
			{ 0x40010004L, "DBG_TERMINATE_PROCESS" },
			{ 0x40010005L, "DBG_CONTROL_C" },
			{ 0x40010006L, "DBG_PRINTEXCEPTION_C" },
			{ 0x40010007L, "DBG_RIPEXCEPTION" },
			{ 0x40010008L, "DBG_CONTROL_BREAK" },
			{ 0x40010009L, "DBG_COMMAND_EXCEPTION" },
			{ 0x4001000AL, "DBG_PRINTEXCEPTION_WIDE_C" },
			{ 0x80000001L, "STATUS_GUARD_PAGE_VIOLATION" },
			{ 0x80000002L, "STATUS_DATATYPE_MISALIGNMENT" },
			{ 0x80000003L, "STATUS_BREAKPOINT" },
			{ 0x80000004L, "STATUS_SINGLE_STEP" },
			{ 0x80000026L, "STATUS_LONGJUMP" },
			{ 0x80000029L, "STATUS_UNWIND_CONSOLIDATE" },
			{ 0x80010001L, "DBG_EXCEPTION_NOT_HANDLED" },
			{ 0xC0000005L, "STATUS_ACCESS_VIOLATION" },
			{ 0xC0000006L, "STATUS_IN_PAGE_ERROR" },
			{ 0xC0000008L, "STATUS_INVALID_HANDLE" },
			{ 0xC000000DL, "STATUS_INVALID_PARAMETER" },
			{ 0xC0000017L, "STATUS_NO_MEMORY" },
			{ 0xC000001DL, "STATUS_ILLEGAL_INSTRUCTION" },
			{ 0xC0000025L, "STATUS_NONCONTINUABLE_EXCEPTION" },
			{ 0xC0000026L, "STATUS_INVALID_DISPOSITION" },
			{ 0xC000008CL, "STATUS_ARRAY_BOUNDS_EXCEEDED" },
			{ 0xC000008DL, "STATUS_FLOAT_DENORMAL_OPERAND" },
			{ 0xC000008EL, "STATUS_FLOAT_DIVIDE_BY_ZERO" },
			{ 0xC000008FL, "STATUS_FLOAT_INEXACT_RESULT" },
			{ 0xC0000090L, "STATUS_FLOAT_INVALID_OPERATION" },
			{ 0xC0000091L, "STATUS_FLOAT_OVERFLOW" },
			{ 0xC0000092L, "STATUS_FLOAT_STACK_CHECK" },
			{ 0xC0000093L, "STATUS_FLOAT_UNDERFLOW" },
			{ 0xC0000094L, "STATUS_INTEGER_DIVIDE_BY_ZERO" },
			{ 0xC0000095L, "STATUS_INTEGER_OVERFLOW" },
			{ 0xC0000096L, "STATUS_PRIVILEGED_INSTRUCTION" },
			{ 0xC00000FDL, "STATUS_STACK_OVERFLOW" },
			{ 0xC0000135L, "STATUS_DLL_NOT_FOUND" },
			{ 0xC0000138L, "STATUS_ORDINAL_NOT_FOUND" },
			{ 0xC0000139L, "STATUS_ENTRYPOINT_NOT_FOUND" },
			{ 0xC000013AL, "STATUS_CONTROL_C_EXIT" },
			{ 0xC0000142L, "STATUS_DLL_INIT_FAILED" },
			{ 0xC00001B2L, "STATUS_CONTROL_STACK_VIOLATION" },
			{ 0xC00002B4L, "STATUS_FLOAT_MULTIPLE_FAULTS" },
			{ 0xC00002B5L, "STATUS_FLOAT_MULTIPLE_TRAPS" },
			{ 0xC00002C9L, "STATUS_REG_NAT_CONSUMPTION" },
			{ 0xC0000374L, "STATUS_HEAP_CORRUPTION" },
			{ 0xC0000409L, "STATUS_STACK_BUFFER_OVERRUN" },
			{ 0xC0000417L, "STATUS_INVALID_CRUNTIME_PARAMETER" },
			{ 0xC0000420L, "STATUS_ASSERTION_FAILURE" },
			{ 0xC00004A2L, "STATUS_ENCLAVE_VIOLATION" },
			{ 0xC0000515L, "STATUS_INTERRUPTED" },
			{ 0xC0000516L, "STATUS_THREAD_NOT_RUNNING" },
			{ 0xC0000718L, "STATUS_ALREADY_REGISTERED" },
			{ 0xC015000FL, "STATUS_SXS_EARLY_DEACTIVATION" },
			{ 0xC0150010L, "STATUS_SXS_INVALID_DEACTIVATION" },
		};
		inline std::map<ULONG_PTR, strung> g_exceptionErrorReasons = {
			{ 0, "attempt to read invalid address" },
			{ 1, "attempt to write to invalid address" },
			{ 8, "data exception prevention (DEP)" },
		};
		inline strung getExceptionType(ULONG_PTR type) {
			if (auto t = g_exceptionErrorReasons.find(type); t != g_exceptionErrorReasons.end()) {
				return t->second;
			}
			return "unknown";
		}
		inline LONG CALLBACK onExceptionCallback(PEXCEPTION_POINTERS exceptionInfo) {
			stackWalker sw(StackWalker::AfterExcept);
			auto& except = exceptionInfo->ExceptionRecord;
			auto& ctx = exceptionInfo->ContextRecord;
			auto& exceptionRecordInfo = except->ExceptionInformation;
			auto& exceptionType = exceptionRecordInfo[0];
			auto& exceptionAddress = exceptionRecordInfo[1];
			switch (except->ExceptionCode) {
			case CONTROL_C_EXIT: { return EXCEPTION_CONTINUE_EXECUTION; } break;
			case EXCEPTION_BREAKPOINT: { return EXCEPTION_CONTINUE_EXECUTION; } break;
			case EXCEPTION_ACCESS_VIOLATION: {
				auto exceptionTypeStr = getExceptionType(exceptionType);
				auto exceptionName = g_exceptionErrorReasons[except->ExceptionCode] != "" ? g_exceptionErrorReasons[except->ExceptionCode] : std::format("0x{:X}", except->ExceptionCode);
				auto fileoffsetStr = modules::getModuleNameFromAddress(except->ExceptionAddress);
				g_Logger->Error("uWu my ass is getting railed."); //LMAO
				
			} break;
			default: {
				auto exceptionName = g_exceptionErrorReasons[except->ExceptionCode] != "" ? g_exceptionErrorReasons[except->ExceptionCode] : std::format("0x{:X}", except->ExceptionCode);
				auto fileoffsetStr = modules::getModuleNameFromAddress(except->ExceptionAddress);	
				g_Logger->Error("uWu my ass is getting railed.");
			}
			}
			if (attemptStackRecovery(exceptionInfo))
				return EXCEPTION_CONTINUE_EXECUTION;
			g_Logger->Error("uWu my ass is getting railed.");
			sw.ShowCallstack(GetCurrentThread(), ctx);
			return EXCEPTION_CONTINUE_SEARCH;
			g_Logger->Error("uWu my ass is getting railed.");
		}
		inline bool onExceptionCallback_TryExcept(PEXCEPTION_POINTERS exceptionInfo) {
			if (onExceptionCallback(exceptionInfo) != EXCEPTION_CONTINUE_EXECUTION)
				return false;
			return true;
		}
		inline LONG CALLBACK exceptionHandler(PEXCEPTION_POINTERS exceptionInfo) {
			return onExceptionCallback(exceptionInfo);
		}
		inline LONG CALLBACK unhandledExceptionHandler(PEXCEPTION_POINTERS exceptionInfo) {
			return onExceptionCallback(exceptionInfo);
		}
		inline PVOID vecExcepHandlerHandle{};
		inline void initExceptionHandler() {
			vecExcepHandlerHandle = AddVectoredExceptionHandler(TRUE, PVECTORED_EXCEPTION_HANDLER(exceptionHandler));
			SetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER(unhandledExceptionHandler));
		}
		inline void uninitExceptionHandler() {
			if (vecExcepHandlerHandle)
				RemoveVectoredExceptionHandler(vecExcepHandlerHandle);
		}
	}
}