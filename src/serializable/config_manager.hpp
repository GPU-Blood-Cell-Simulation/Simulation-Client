#pragma once

#include "config_data.hpp"
#include "../simulation/simulation_instance.hpp"

#include <string>

namespace serializable
{
	/// <summary>
	/// A class responsible for serialization/deserialization of configuration files and providing the data necessary to create a Simulation Instance
	/// </summary>
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

