#pragma once

namespace Saint
{
	template<typename T>
	static T call(uint64_t address) { return ((T(*)())address)(); }

	template<typename T, typename P1>
	static T call(uint64_t address, P1 p1) { return ((T(*)(P1))address)(p1); }

	template<typename T, typename P1, typename P2>
	static T call(uint64_t address, P1 p1, P2 p2) { return ((T(*)(P1, P2))address)(p1, p2); }

	template<typename T, typename P1, typename P2, typename P3>
	static T call(uint64_t address, P1 p1, P2 p2, P3 p3) { return ((T(*)(P1, P2, P3))address)(p1, p2, p3); }

	template<typename T, typename P1, typename P2, typename P3, typename P4>
	static T call(uint64_t address, P1 p1, P2 p2, P3 p3, P4 p4) { return ((T(*)(P1, P2, P3, P4))address)(p1, p2, p3, p4); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
	static T call(uint64_t address, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) { return ((T(*)(P1, P2, P3, P4, P5))address)(p1, p2, p3, p4, p5); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	static T call(uint64_t address, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) { return ((T(*)(P1, P2, P3, P4, P5, P6))address)(p1, p2, p3, p4, p5, p6); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	static T call(uint64_t address, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) { return ((T(*)(P1, P2, P3, P4, P5, P6, P7))address)(p1, p2, p3, p4, p5, p6, p7); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	static T call(uint64_t address, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8) { return ((T(*)(P1, P2, P3, P4, P5, P6, P7, P8))address)(p1, p2, p3, p4, p5, p6, p7, p8); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
	static T call(uint64_t address, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9) { return ((T(*)(P1, P2, P3, P4, P5, P6, P7, P8, P9))address)(p1, p2, p3, p4, p5, p6, p7, p8, p9); }

	template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10>
	static T call(uint64_t address, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10) { return ((T(*)(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10))address)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
}