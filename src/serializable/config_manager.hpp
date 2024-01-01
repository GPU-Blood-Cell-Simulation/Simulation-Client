#pragma once

#include "config_data.hpp"

#include <string>

namespace serializable
{
	class ConfigManager
	{
	public:
		void loadBloodCellConfig(const std::string& filePath);
		void saveBloodCellConfig(const std::string& filePath) const;

		void loadVeinConfig(const std::string& filePath);
		void saveVeinConfig(const std::string& filePath) const;

		void loadGeneralConfig(const std::string& filePath);
		void saveGeneralConfig(const std::string& filePath) const;

		ConfigData& getData();
		void serializeAllToCpp() const;

	private:
		ConfigData data;
	};
}
