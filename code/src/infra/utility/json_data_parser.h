#pragma once

#include "cereal/archives/json.hpp"
#include <fstream>
#include <optional>

template <class T>
class JsonDataParser {
public:
	std::optional<T> Deserialize(std::string_view fileName) {
		std::ifstream is(fileName.data());

		if (is.is_open()) {
			try {
				T parsedData;
				cereal::JSONInputArchive archive_in(is);
				archive_in(parsedData);

				return parsedData;
			}
			catch (cereal::RapidJSONException&) {
				return std::nullopt;
			}
		}
		else {
			return std::nullopt;
		}
	}

	bool Serialize(std::string_view fileName, const T& data, std::string_view jsonObjName = "Object") {
		try {
			std::ofstream os(fileName.data());

			cereal::JSONOutputArchive archive_out(os);
			archive_out(cereal::make_nvp(jsonObjName.data(), data));

			return true;
		}
		catch (cereal::RapidJSONException&) {
			return false;
		}
	}
};