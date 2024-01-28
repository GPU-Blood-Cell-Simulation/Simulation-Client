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
		/// <summary>
		/// Load blood cells config from JSON file
		/// </summary>
		/// <param name="filePath">Path to JSON config file with blood cells definitions</param>
		void loadBloodCellConfig(const std::string& filePath);

		/// <summary>
		/// Saves blood cells config to JSON file
		/// </summary>
		/// <param name="filePath">Path to new JSON config file</param>
		void saveBloodCellConfig(const std::string& filePath) const;

		/// <summary>
		/// Load vein config from JSON file
		/// </summary>
		/// <param name="filePath">Path to JSON config file with vein definition</param>
		void loadVeinConfig(const std::string& filePath);

		/// <summary>
		/// Saves vein config to JSON file
		/// </summary>
		/// <param name="filePath">Path to new JSON config file</param>
		void saveVeinConfig(const std::string& filePath) const;

		/// <summary>
		/// Load general simulation config from JSON file
		/// </summary>
		/// <param name="filePath">Path to JSON config file with simulation definition</param>
		void loadGeneralConfig(const std::string& filePath);

		/// <summary>
		/// Saves general config to JSON file
		/// </summary>
		/// <param name="filePath">Path to new JSON config file</param>
		void saveGeneralConfig(const std::string& filePath) const;

		/// <summary>
		/// Get the whole configuration data
		/// </summary>
		/// <returns>A reference to internally stored data</returns>
		ConfigData& getData();

		/// <summary>
		/// Generates C++ header files with simulation config. These file should be used
		/// during server compilation.
		/// </summary>
		void serializeAllToCpp() const;

	private:
		/// <summary>
		/// Internally stored config data
		/// </summary>
		ConfigData data;
	};
}
