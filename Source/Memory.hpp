#pragma once

namespace Saint
{
#pragma once
#include <span>

	inline std::vector<const char*> pointerNames = {

	};

	namespace memory
	{
		uint64_t read_instruction(uint64_t address, int opcode_size, int opcode_length) {
			return (uint64_t)(*(int*)(address + opcode_size) + address + opcode_length);
		}
		template<typename T>
		concept SpanCompatibleType = requires(T a)
		{
			std::span{ a };
		};

		class byte_patch
		{
		public:
			virtual ~byte_patch();

			void apply() const;

			void restore() const;

			void remove() const;

			template <typename TAddr>
			static const std::unique_ptr<byte_patch>& make(TAddr address, std::remove_pointer_t<std::remove_reference_t<TAddr>> value)
			{
				return m_patches.emplace_back(
					std::unique_ptr<byte_patch>(new byte_patch(address, value)));
			}

			template <typename TAddr, typename T> requires SpanCompatibleType<T>
			static const std::unique_ptr<byte_patch>& make(TAddr address, T span_compatible)
			{
				return m_patches.emplace_back(
					std::unique_ptr<byte_patch>(new byte_patch(address, std::span{ span_compatible })));
			}

			static void restore_all();

		private:
			template <typename TAddr>
			byte_patch(TAddr address, std::remove_pointer_t<std::remove_reference_t<TAddr>> value)
				: m_address(address)
			{
				m_size = sizeof(std::remove_pointer_t<std::remove_reference_t<TAddr>>);

				m_original_bytes = std::make_unique<byte[]>(m_size);
				memcpy(m_original_bytes.get(), m_address, m_size);

				m_value = std::make_unique<byte[]>(m_size);
				memcpy(m_value.get(), &value, m_size);
			}

			template <typename TAddr, typename T, std::size_t N>
			byte_patch(TAddr address, std::span<T, N> span)
				: m_address((void*)address)
			{
				m_size = span.size();

				m_original_bytes = std::make_unique<byte[]>(m_size);
				memcpy(m_original_bytes.get(), m_address, m_size);

				m_value = std::make_unique<byte[]>(m_size);
				for (int i = 0; i < m_size; i++)
					m_value[i] = span[i];
			}

		protected:
			static inline std::vector<std::unique_ptr<byte_patch>> m_patches;

		private:
			void* m_address;
			std::unique_ptr<byte[]> m_value;
			std::unique_ptr<byte[]> m_original_bytes;
			std::size_t m_size;

			friend bool operator== (const std::unique_ptr<byte_patch>& a, const byte_patch* b);
		};
	}

	class MemoryHandle
	{
	public:
		constexpr MemoryHandle(void* p = nullptr) :
			m_Ptr(p)
		{}
		explicit MemoryHandle(std::uintptr_t p) :
			m_Ptr(reinterpret_cast<void*>(p))
		{}

		template <typename T>
		constexpr std::enable_if_t<std::is_pointer_v<T>, T> As()
		{
			return static_cast<T>(m_Ptr);
		}
		template <typename T>
		constexpr std::enable_if_t<std::is_lvalue_reference_v<T>, T> As()
		{
			return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(m_Ptr);
		}
		template <typename T>
		constexpr std::enable_if_t<std::is_same_v<T, std::uintptr_t>, T> As()
		{
			return reinterpret_cast<T>(m_Ptr);
		}
		template <typename T>
		constexpr MemoryHandle Add(T offset)
		{
			return MemoryHandle(As<std::uintptr_t>() + offset);
		}
		template <typename T>
		constexpr MemoryHandle Sub(T offset)
		{
			return MemoryHandle(As<std::uintptr_t>() - offset);
		}

		constexpr MemoryHandle Rip()
		{
			if (!m_Ptr)
				return nullptr;
			return Add(As<std::int32_t&>()).Add(4U);
		}
		constexpr MemoryHandle From_Instruction()
		{
			return Add(3).Rip();
		}
		constexpr explicit operator bool() noexcept
		{
			return m_Ptr;
		}
	protected:
		void* m_Ptr;
	};

	class MemoryRegion
	{
	public:
		constexpr explicit MemoryRegion(MemoryHandle base, std::size_t size):
			m_Base(base),
			m_Size(size)
		{}
		constexpr MemoryHandle Base()
		{
			return m_Base;
		}
		constexpr MemoryHandle End()
		{
			return m_Base.Add(m_Size);
		}
		constexpr std::size_t Size()
		{
			return m_Size;
		}
		constexpr bool Contains(MemoryHandle p)
		{
			if (p.As<std::uintptr_t>() < m_Base.As<std::uintptr_t>())
				return false;
			if (p.As<std::uintptr_t>() > m_Base.Add(m_Size).As<std::uintptr_t>())
				return false;

			return true;
		}
	protected:
		MemoryHandle m_Base;
		std::size_t m_Size;
	};

	class Module : public MemoryRegion
	{
	public:
		explicit Module(std::nullptr_t):
			Module(static_cast<char*>(nullptr))
		{}
		explicit Module(const char* name):
			Module(GetModuleHandleA(name))
		{
		}
		Module(HMODULE hmod):
			MemoryRegion(hmod, 0)
		{
			auto dosHeader = m_Base.As<IMAGE_DOS_HEADER*>();
			auto ntHeader = m_Base.Add(dosHeader->e_lfanew).As<IMAGE_NT_HEADERS64*>();
			m_Size = ntHeader->OptionalHeader.SizeOfImage;
		}

		
		IMAGE_DOS_HEADER* GetDosHeaders()
		{
			return m_Base.As<IMAGE_DOS_HEADER*>();
		}

		
		IMAGE_NT_HEADERS64* GetNtHeaders()
		{
			return m_Base.Add(m_Base.As<IMAGE_DOS_HEADER*>()->e_lfanew).As<IMAGE_NT_HEADERS64*>();
		}
	private:
		
		template <typename TReturn, typename TOffset>
		TReturn GetRVA(TOffset rva)
		{
			return m_Base.Add(rva).As<TReturn>();
		}
	};

	class Signature
	{
	public:
		struct Element
		{
			std::uint8_t m_Data{};
			bool m_Wildcard{};
		};

		
		explicit Signature(const char* pattern, const char* name = "")
		{
			if (name != "") {
				pointerNames.push_back(name);
			}
			auto toUpper = [](char c) -> char
			{
				return c >= 'a' && c <= 'z' ? static_cast<char>(c + ('A' - 'a')) : static_cast<char>(c);
			};

			auto isHex = [&](char c) -> bool
			{
				switch (toUpper(c))
				{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				case 'A':
				case 'B':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
					return true;
				default:
					return false;
				}
			};

			do
			{
				if (*pattern == ' ')
					continue;
				if (*pattern == '?')
				{
					m_Elements.push_back(Element{ {}, true });
					continue;
				}

				if (*(pattern + 1) && isHex(*pattern) && isHex(*(pattern + 1)))
				{
					char str[3] = { *pattern, *(pattern + 1), '\0' };
					auto data = std::strtol(str, nullptr, 16);

					m_Elements.push_back(Element{ static_cast<std::uint8_t>(data), false });
				}
			} while (*(pattern++));
		}
		MemoryHandle Scan(MemoryRegion region = Module(nullptr))
		{
			auto compareMemory = [](std::uint8_t* data, Element* elem, std::size_t num) -> bool
			{
				for (std::size_t i = 0; i < num; ++i)
				{
					if (!elem[i].m_Wildcard)
						if (data[i] != elem[i].m_Data)
							return false;
				}

				return true;
			};

			for (std::uintptr_t i = region.Base().As<std::uintptr_t>(), end = region.End().As<std::uintptr_t>(); i != end; ++i)
			{
				if (compareMemory(reinterpret_cast<std::uint8_t*>(i),  m_Elements.data(), m_Elements.size()))
				{
					return MemoryHandle(i);
				}
			}

			return {};
		}
	private:
		std::vector<Element> m_Elements;
	};
}
