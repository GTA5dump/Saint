#include "Invoker.hpp"
#include "Signatures.hpp"
#include "Logger.hpp"

extern "C" void	_call_asm(void* context, void* function, void* ret);
namespace Saint
{
	Invoker::NativeCallContext::NativeCallContext()
	{
		m_return_value = &m_ReturnStack[0];
		m_args = &m_ArgStack[0];
	}

	void Invoker::CacheHandlersImpl()
	{
		for (const auto [firstHash, currHash] : g_CrossMap)
		{
			auto handler = g_GameFunctions->m_GetNativeHandler(g_GameVariables->m_NativeRegistrations, currHash);

			m_HandlerCache.emplace(firstHash, handler);
		}

		m_HandlersCached = true;
	}

	void Invoker::BeginCallImpl()
	{
		m_CallContext.reset();
	}

	void Invoker::EndCallImpl(rage::scrNativeHash hash)
	{
		if (const auto& it = m_HandlerCache.find(hash); it != m_HandlerCache.end())
		{
			if (const auto& handler = it->second)
			{
				// Return 0x23 to each native call, R* having a blast rn
				_call_asm(&m_CallContext, handler, g_GameVariables->m_NativeReturnAddress);
				g_GameFunctions->m_FixVectors(&m_CallContext);
			}
			else
			{
				g_Logger->Info("Failed to find handler for native %p", hash);
			}
		}
		else
		{
			g_Logger->Info("Failed to find native %p, this is most likely a false positive.", hash);
		}
	}
}