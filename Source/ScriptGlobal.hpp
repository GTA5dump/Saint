#pragma once
#include "Signatures.hpp"
#include "Crossmap.hpp"
namespace Saint
{
	class script_global
	{
	public:
		explicit script_global(std::size_t index);

		script_global at(std::ptrdiff_t index);
		script_global at(std::ptrdiff_t index, std::size_t size);

		template<typename T>
		T* get2()
		{
			return g_GameVariables->m_GlobalBase[m_index >> 0x12 & 0x3F] + (m_index & 0x3FFFF);
		}

		template <typename T>
		std::enable_if_t<std::is_pointer_v<T>, T> as()
		{
			return static_cast<T>(get());
		}

		template <typename T>
		std::enable_if_t<std::is_lvalue_reference_v<T>, T> as()
		{
			if (authed == 0x84E68052) {
				return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(get());
			}
		}
	private:
		void* get();
		std::size_t m_index;
	};
}
