#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <JSON/json.hpp>
#include "Logger.hpp"
class Translations {
private:
	inline static std::vector<std::pair<std::string, std::string>> translations;
public:
	inline static bool LoadTranslation(std::string path) {
		std::ifstream f = std::ifstream(path);
		if (!f.good())
			return false;
		std::stringstream s;
		s << f.rdbuf();
		try {
			nlohmann::json j = nlohmann::json::parse(s.str());
			translations.clear();
			for (auto i = j.begin(); i != j.end(); ++i)
				translations.push_back(std::pair<std::string, std::string>(i.key(), i.value().get<std::string>()));
			return true;
		}
		catch (nlohmann::detail::exception const&) {
			return false;
		}
	}
	inline static std::string GetTranslation(std::string name) {
		for (int i = 0; i < translations.size(); i++) {
			if (translations[i].first == name)
				return translations[i].second;
		}
		return name;
	}
};