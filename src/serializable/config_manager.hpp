#pragma once

#include "config_data.hpp"
#include "../simulation/simulation_instance.hpp"

#include <string>

namespace serializable
{
	class ConfigManager
	{
	public:
		void loadConfiguration(const std::string& filePath);
		void saveConfiguration(const std::string& filePath);
		const ConfigData& getData() const;

	private:
		ConfigData data;
		ConfigData previousData;
	};
}

