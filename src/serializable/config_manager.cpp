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

	void ConfigManager::serializeAllToCpp(const vein::Node* rootNode, graphics::GLController& glController) const
	{
		// Calculate final vein mesh
		vein::SerializableMesh finalMesh;
		rootNode->addToMesh(finalMesh, 0, 0);

		// DEBUG
		glController.setFinalMesh(finalMesh);

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

		// Serialize ConfigData
	}
}
