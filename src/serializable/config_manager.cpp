#include "config_manager.hpp"

#include <fstream>

using json = nlohmann::json;

namespace serializable
{
	void ConfigManager::loadConfiguration(const std::string& filePath)
	{
		// read file

		// TODO: check errors
		std::ifstream is(filePath);
		json jsonData = json::parse(is);

		data = jsonData.template get<ConfigData>();
		previousData = data;
	}

	void ConfigManager::saveConfiguration(const std::string& filePath)
	{
		// save to files

		// TODO: check errors
		std::ofstream os(filePath);
		json jsonData = data;
		os << jsonData;

		previousData = data;
	}

	const ConfigData& ConfigManager::getData() const
	{
		return data;
	}
}
