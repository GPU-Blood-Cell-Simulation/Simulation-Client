#pragma once

#include "config_data.hpp"

#include <string>

namespace serializable
{
	/// <summary>
	/// Responsible for holding the config data, loading and saving it to json as well as generating the C++ headers for server.
	/// </summary>
	class ConfigManager
	{
	public:
		void loadBloodCellConfig(const std::string& filePath);
		void saveBloodCellConfig(const std::string& filePath) const;

		void loadVeinConfig(const std::string& filePath);
		void saveVeinConfig(const std::string& filePath) const;

		void loadGeneralConfig(const std::string& filePath);
		void saveGeneralConfig(const std::string& filePath) const;

		/// <summary>
		/// Get the whole configuration data
		/// </summary>
		/// <returns>A reference to internally stored data</returns>
		ConfigData& getData();

		void serializeAllToCpp() const;

	private:
		/// <summary>
		/// Internally stored config data
		/// </summary>
		ConfigData data;
	};
}
