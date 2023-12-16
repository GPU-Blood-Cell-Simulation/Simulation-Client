#pragma once

#include "config_data.hpp"
#include "../vein/nodes/node.hpp"
#include "../graphics/glcontroller.hpp"

#include <string>

namespace serializable
{
	class ConfigManager
	{
	public:
		void loadConfiguration(const std::string& filePath);
		void saveConfiguration(const std::string& filePath);
		const ConfigData& getData() const;
		void serializeAllToCpp(const vein::Node* rootNode, graphics::GLController& glController) const;

	private:
		ConfigData data;
		ConfigData previousData;
	};
}

