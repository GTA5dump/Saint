#pragma once
#include "Signatures.hpp"
#include "ScriptGlobal.hpp"
#include "Crossmap.hpp"

namespace Saint
{
	script_global::script_global(std::size_t index) :
		m_index(index)
	{
	}

	script_global script_global::at(std::ptrdiff_t index)
	{
		return script_global(m_index + index);
	}

	script_global script_global::at(std::ptrdiff_t index, std::size_t size)
	{
		return script_global(m_index + 1 + (index * size));
	}

	void* script_global::get()
	{
		return g_GameVariables->m_GlobalBase[m_index >> 0x12 & 0x3F] + (m_index & 0x3FFFF);
	}


}
