#include "config_manager.hpp"
#include "blood_cells_definition.hpp"

#include "../defines.hpp"

#include <fstream>

using json = nlohmann::json;

namespace serializable
{
	void ConfigManager::loadBloodCellConfig()
	{
		std::ifstream is(bloodCellConfigPath);
		json jsonData = json::parse(is);
		data.bloodCellsDefinition = jsonData.template get<BloodCellsDefinition>();
	}
	void ConfigManager::saveBloodCellConfig() const
	{
		std::ofstream os(bloodCellConfigPath);
		json jsonData = data.bloodCellsDefinition;
		os << std::setw(3) << jsonData;
	}

	void ConfigManager::loadVeinConfig()
	{
		// TODO
	}

	void ConfigManager::saveVeinConfig() const
	{
		// TODO
	}

	void ConfigManager::loadGeneralConfig()
	{
		// TODO
	}

	void ConfigManager::saveGeneralConfig() const
	{
		// TODO
	}

	ConfigData& ConfigManager::getData()
	{
		return data;
	}

	void ConfigManager::serializeAllToCpp() const
	{
		// Calculate final vein mesh
		vein::SerializableMesh finalMesh;
		data.veinDefinition.rootNode->addToMesh(finalMesh, 0, 0);

		// Serialize vein
		try
		{
			finalMesh.serializeToCpp();
		}
		catch (std::ofstream::failure& e)
		{
			std::cout << "ostream error : " << e.what() << "\n";
		}
		catch (...)
		{
			std::cout << "other error during mesh generation\n";
		}

		// Serialize BloodCells
		data.bloodCellsDefinition.serializeToCpp();

		// Serialize GeneralConfig
			// TODO
	}
}
