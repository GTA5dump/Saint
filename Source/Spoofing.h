#pragma once

namespace Saint {
	class Crew {
	public:
		std::string nameBuffer;
		std::string tag = "gang";
		bool enabled = false;
		bool open = false;
		int member_count = 0;
		const char* name = "Saint";
	};
	class IP {
	public:
		bool enabled;
		int field1 = 255;
		int field2 = 255;
		int field3 = 255;
		int field4 = 255;
		std::string f1;
		std::string f2;
		std::string f3;
		std::string f4;
	};
	class Spoofing {
	public:
		Crew m_crew;
		IP ip;
		bool m_godmode = false;
		bool m_superjump = false;
		bool spectating = false;
		bool respawning = false;
		bool seatbelt = false;

		bool qa_tester = false;
		bool rockstar_dev = false;
	};
	inline Spoofing spoofing;
}
