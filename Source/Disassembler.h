#pragma once
#define COUNT(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))


namespace Saint
{
	namespace x64 {
		enum class x64Register : uint8_t {
			RA = 0,
			RC,
			RB,
			RD,
			SP,
			BP,
			SI,
			DI,
			R8,
			R9,
			R10,
			R11,
			R12,
			R13,
			R14,
			R15,
			IP,
			IMM,
			DIS,
		};
		enum class x64AccessType : uint8_t {
			ACCESS_64 = 64,
			ACCESS_32 = 32,
			ACCESS_16 = 16,
			ACCESS_8 = 8,
			ACCESS_8_H = 0,
		};
#pragma pack(push, 1)
		struct x64Operand {
			x64Register m_reg;
			union {
				struct { //Register
					x64AccessType m_accessType;
					uint8_t m_derefSize;
					int32_t m_derefOffset;
				};
				struct { //Immediate
					uint64_t m_val;
				};
				struct { //Displacement
					int64_t m_displacement;
				};
			};
			void reset() {
				m_val = 0;
			}
			void decode(bool rex, uint8_t size, uint8_t reg, bool x) {
				reg |= (x << 3);
				m_reg = static_cast<x64Register>(reg);
				m_accessType = static_cast<x64AccessType>(size);
				if (reg >= static_cast<uint8_t>(x64Register::SP) && reg <= static_cast<uint8_t>(x64Register::DI) && !rex && size != 64) {
					m_reg = static_cast<x64Register>(static_cast<uint8_t>(m_reg) - 4);
					m_accessType = x64AccessType::ACCESS_8_H;
				}
			}
		};
#pragma pack(pop)
		enum class x64OperandEncoding : uint16_t {
			ZO = NULL,
			O = 0b001,
			M = 0b010,
			R = 0b011,
			I = 0b100,
			D = 0b101,
			A = 0b111,
			OPERAND_MASK = 0b111,
			BITS_PER_OPERAND = 3,
			MR = M | (R << BITS_PER_OPERAND),
			RM = R | (M << BITS_PER_OPERAND),
			OI = O | (I << BITS_PER_OPERAND),
			MI = M | (I << BITS_PER_OPERAND),
			AI = A | (I << BITS_PER_OPERAND),
			RMI = R | (M << BITS_PER_OPERAND) | (I << (BITS_PER_OPERAND * 2)),
		};
		struct x64Operation {
			const char* m_name;
			uint16_t m_opcode;
			x64OperandEncoding m_operandEncoding;
			uint8_t m_operandSize;
			uint8_t m_distinguish;
			static constexpr uint8_t m_maxOperands = 3;
			x64Operation(const char* name, uint16_t opcode, x64OperandEncoding operandEncoding) : x64Operation(name, opcode, operandEncoding, 0, 8) {}
			x64Operation(const char* name, uint16_t opcode, x64OperandEncoding operandEncoding, uint8_t operandSize) : x64Operation(name, opcode, operandEncoding, operandSize, 8) {}
			x64Operation(const char* name, uint16_t opcode, x64OperandEncoding operandEncoding, uint8_t operandSize, uint8_t distinguish) : m_name(name), m_opcode(opcode), m_operandEncoding(operandEncoding), m_operandSize(operandSize), m_distinguish(distinguish) {}
			uint16_t getUniqueId() {
				return m_distinguish == 8 ? m_opcode : (m_opcode << 3) | m_distinguish;
			}
			bool matches(const uint8_t* code) {
				uint16_t b = *code;
				if (b == 0xF)
					++code, b <<= 8, b |= *code;
				if (getOprEncoding(0) == x64OperandEncoding::O)
					b &= ~7;
				return m_opcode == b && (m_distinguish == 8 || ((code[1] >> 3) & 7) == m_distinguish);
			}
			x64OperandEncoding getOprEncoding(uint8_t i) {
				return static_cast<x64OperandEncoding>((static_cast<uint8_t>(m_operandEncoding) >> (static_cast<uint8_t>(x64OperandEncoding::BITS_PER_OPERAND) * i)) & static_cast<uint8_t>(x64OperandEncoding::OPERAND_MASK));
			}
			uint8_t getNumOperands() {
				uint8_t i{};
				while (i != m_maxOperands) {
					if (getOprEncoding(i) == x64OperandEncoding::ZO)
						break;
					++i;
				}
				return i;
			}
			uint8_t getNumModrmOperands() {
				uint8_t count{};
				for (uint8_t i{}; i != m_maxOperands; ++i)
					if (auto enc = getOprEncoding(i); enc == x64OperandEncoding::M || enc == x64OperandEncoding::R)
						++count;
				return count;
			}
		};
		//TODO: Improve operation table
		inline static x64Operation m_operations[] = {
			{ "mov", 0x88, x64OperandEncoding::MR, 8 },
			{ "mov", 0x89, x64OperandEncoding::MR },
			{ "mov", 0x8A, x64OperandEncoding::RM, 8 },
			{ "mov", 0x8B, x64OperandEncoding::RM },
			{ "mov", 0xB0, x64OperandEncoding::OI, 8 },
			{ "mov", 0xB8, x64OperandEncoding::OI },
			{ "mov", 0xC6, x64OperandEncoding::MI, 8 },
			{ "mov", 0xC7, x64OperandEncoding::MI, 32 },
			{ "ret", 0xC3, x64OperandEncoding::ZO },
			{ "push", 0x50, x64OperandEncoding::O, 64 },
			{ "pop", 0x58, x64OperandEncoding::O, 64 },
			{ "push", 0xFF, x64OperandEncoding::M, 64, 6},
			{ "add", 0x81, x64OperandEncoding::MI, 32, 0 },
			{ "add", 0x83, x64OperandEncoding::MI, 8, 0 },
			{ "sub", 0x81, x64OperandEncoding::MI, 32, 5 },
			{ "sub", 0x83, x64OperandEncoding::MI, 8, 5 },
			{ "cmp", 0x80, x64OperandEncoding::MI, 8, 7 },
			{ "cmp", 0x83, x64OperandEncoding::MI, 8, 7 },
			{ "cmp", 0x3C, x64OperandEncoding::AI, 8 },
			{ "cmp", 0x3D, x64OperandEncoding::AI, 32 },
			{ "cmp", 0x38, x64OperandEncoding::MR, 8 },
			{ "cmp", 0x39, x64OperandEncoding::MR },
			{ "lea", 0x8D, x64OperandEncoding::RM },
			{ "jz", 0x74, x64OperandEncoding::D, 8 },
			{ "jnz", 0x75, x64OperandEncoding::D, 8 },
			{ "call", 0xE8, x64OperandEncoding::D, 32 },
			{ "jmp", 0xEB, x64OperandEncoding::D, 8 },
			{ "jmp", 0xE9, x64OperandEncoding::D, 32 },
			{ "test", 0x84, x64OperandEncoding::MR, 8 },
			{ "test", 0x85, x64OperandEncoding::MR },
			{ "xor", 0x33, x64OperandEncoding::RM },
			{ "movzx", 0x0FB6, x64OperandEncoding::RM, 8 },
			{ "movzx", 0x0FB7, x64OperandEncoding::RM, 16 },
			{ "imul", 0x69, x64OperandEncoding::RMI, 32 },
			{ "nop", 0x90, x64OperandEncoding::ZO },
		};
		struct x64Instruction {
			x64Operation* m_operation = nullptr;
			x64Operand m_operands[x64Operation::m_maxOperands];
			bool isValid() {
				return m_operation != nullptr;
			}
			void reset() {
				m_operation = nullptr;
				for (auto& opr : m_operands)
					opr.reset();
			}
			strung toBytecode() {
				strung res{};
				if (m_operands[0].m_accessType == x64AccessType::ACCESS_64)
					res.push_back('\x48'); //REX.W
				if ((m_operation->m_opcode >> 8) & 0xFF)
					res.push_back((m_operation->m_opcode >> 8) & 0xFF);
				res.push_back(m_operation->m_opcode & 0xFF);
				if (m_operation->getNumModrmOperands() != NULL) {
					uint8_t modrm{};
					modrm |= (0b11 << 6); // direct
					modrm |= (static_cast<uint8_t>(m_operands[1].m_reg) << 3); // reg
					modrm |= static_cast<uint8_t>(m_operands[0].m_reg); // r/m
					res.push_back(modrm);
				}
				return res;
			}
		};
		template <typename t = uint64_t>
		inline static void getImmediate(t& val, uint8_t*& code, uint8_t immBytes) {
			++code;
			val = 0;
			for (auto i = immBytes; i-- != 0;)
				val <<= 8, val |= code[i];
			code += (immBytes - 1);
		}
		inline x64Instruction disassembleInstructionCode(uint8_t*& code) {
			bool operandSizeOverride = false;
			bool addressSizeOverride = false;
			bool rex = false;
			bool defaultOperandSize = true;
			bool regX = false;
			bool rmX = false;
			if (*code == 0x66)
				operandSizeOverride = true, ++code;
			if (*code == 0x67)
				addressSizeOverride = true, ++code;
			if ((*code >> 4) == 4) {
				rex = true;
				if ((*code >> 3) & 1)
					defaultOperandSize = false;
				regX = ((*code >> 2) & 1);
				rmX = (*code & 1);
				++code;
			}
			//Opcodes
			x64Instruction res{};
			for (auto& op : m_operations) {
				if (op.matches(code)) {
					if (*code == 0x0F)
						++code;
					res.m_operation = &op;
					if (op.m_operandEncoding != x64OperandEncoding::ZO) {
						uint8_t operandSize{};
						uint8_t immediateSize{};
						if (operandSizeOverride)
							operandSize = immediateSize = 16;
						else if (op.m_operandSize == NULL)
							operandSize = immediateSize = (defaultOperandSize ? 32 : 64);
						else if (defaultOperandSize)
							operandSize = immediateSize = op.m_operandSize;
						else
							operandSize = 64, immediateSize = op.m_operandSize;
						uint8_t opcode = *code;
						uint8_t oprI{};
						uint8_t numModrmOprs = op.getNumModrmOperands();
						bool modrmRead{ false };
						uint8_t modrm{};
						uint8_t sib{};
						for (uint8_t oprEnc; oprEnc = ((static_cast<uint8_t>(op.m_operandEncoding) >> (oprI * static_cast<uint8_t>(x64OperandEncoding::BITS_PER_OPERAND))) & static_cast<uint8_t>(x64OperandEncoding::OPERAND_MASK)), static_cast<x64OperandEncoding>(oprEnc) != x64OperandEncoding::ZO;) {
							x64Operand& opr = res.m_operands[oprI];
							if (static_cast<x64OperandEncoding>(oprEnc) == x64OperandEncoding::O) {
								opr.decode(rex, operandSize, opcode & 7, rmX);
							}
							else if (static_cast<x64OperandEncoding>(oprEnc) == x64OperandEncoding::M || static_cast<x64OperandEncoding>(oprEnc) == x64OperandEncoding::R) {
								if (!modrmRead)
									modrmRead = true, modrm = *++code;
								const bool direct = ((modrm >> 6) == 3);
								if (static_cast<x64OperandEncoding>(oprEnc) == x64OperandEncoding::M) {
									opr.decode(rex || !direct, operandSize, modrm & 7, rmX);
									if (!direct) {
										opr.m_accessType = (addressSizeOverride ? x64AccessType::ACCESS_32 : x64AccessType::ACCESS_64);
										opr.m_derefSize = ((numModrmOprs == 2) ? 1 : operandSize); //Hiding pointer type when other operand makes it apparent
										if (opr.m_reg == x64Register::SP)
											sib = *++code;
										switch (modrm >> 6) {
										case 0: {
											//Absolute address
											if (opr.m_reg == x64Register::SP && sib == 0x25)
												opr.m_reg = x64Register::IMM, getImmediate(opr.m_val, code, 4);
											//Read as RIP-relative
											else if (opr.m_reg == x64Register::BP)
												opr.m_reg = x64Register::IP, getImmediate(opr.m_derefOffset, code, 4);
										} break;
										case 1: {
											opr.m_derefOffset = (int8_t) * ++code;
										} break;
										case 2: {
											getImmediate(opr.m_derefOffset, code, 4);
										} break;
										}
									}
								}
								else if (static_cast<x64OperandEncoding>(oprEnc) == x64OperandEncoding::R)
									opr.decode(rex, operandSize, (modrm >> 3) & 7, regX);
							}
							else if (static_cast<x64OperandEncoding>(oprEnc) == x64OperandEncoding::I)
								opr.m_reg = x64Register::IMM, getImmediate(opr.m_val, code, immediateSize / 8);
							else if (static_cast<x64OperandEncoding>(oprEnc) == x64OperandEncoding::D) {
								opr.m_reg = x64Register::DIS;
								getImmediate(opr.m_val, code, immediateSize / 8);
								if (immediateSize == 8)
									opr.m_displacement = uint8_t(opr.m_val);
								else if (immediateSize == 32)
									opr.m_displacement = uint32_t(opr.m_val);
							}
							else if (static_cast<x64OperandEncoding>(oprEnc) == x64OperandEncoding::A)
								opr.decode(rex, operandSize, static_cast<uint8_t>(x64Register::RA), regX);
							if (++oprI == COUNT(res.m_operands))
								break;
						}
					}
					++code;
					break;
				}
			}
			return res;
		}
		inline uint8_t getInstructionLength(uint8_t* code) {
			auto start = code;
			return disassembleInstructionCode(code).isValid() ? uint8_t(code - start) : NULL;
		}
	}
}