#include "config_manager.hpp"
#include "blood_cell_json_conversion/blood_cells_definition.hpp"
#include "vein_node_json_conversion.hpp"

#include "../defines.hpp"
#include "exceptions.hpp"

#include <fstream>

using json = nlohmann::json;

namespace serializable
{
	static json parseJson(const std::string& filePath)
	{
		std::ifstream is(filePath);
		if (!is)
			throw FileOpenException();
		return json::parse(is);
	}

	static void writeToJson(std::ofstream& os, const json& jsonData)
	{
		os << std::setw(3) << jsonData;
		if (!os)
			throw FileWriteException();
	}

	void ConfigManager::loadBloodCellConfig(const std::string& filePath)
	{
		json jsonData = parseJson(filePath);
		data.bloodCellsDefinition = jsonData.template get<BloodCellsDefinition>();
	}
	void ConfigManager::saveBloodCellConfig(const std::string& filePath) const
	{
		std::ofstream os(filePath);
		json jsonData = data.bloodCellsDefinition;
		writeToJson(os, jsonData);
	}

	void ConfigManager::loadVeinConfig(const std::string& filePath)
	{
		json jsonData = parseJson(filePath);
		data.veinRootNode.reset();
		data.veinRootNode = std::make_unique<vein::RootNode>(jsonData);
	}

	void ConfigManager::saveVeinConfig(const std::string& filePath) const
	{
		std::ofstream os(filePath);
		json jsonData = data.veinRootNode->generateJson();
		writeToJson(os, jsonData);
	}

	void ConfigManager::loadGeneralConfig(const std::string& filePath)
	{
		json jsonData = parseJson(filePath);
		data.generalConfig = jsonData.template get<GeneralConfig>();
	}

	void ConfigManager::saveGeneralConfig(const std::string& filePath) const
	{
		std::ofstream os(filePath);
		json jsonData = data.generalConfig;
		writeToJson(os, jsonData);
	}

	ConfigData& ConfigManager::getData()
	{
		return data;
	}

	void ConfigManager::serializeAllToCpp() const
	{
		// Calculate final vein mesh
		vein::SerializableMesh finalMesh;
		data.veinRootNode->addToMesh(finalMesh, 0, 0);

		// Serialize vein
		finalMesh.serializeToCpp();

		// Serialize BloodCells
		data.bloodCellsDefinition.serializeToCpp();

		// Serialize GeneralConfig
		data.generalConfig.serializeToCpp();
	}
}
