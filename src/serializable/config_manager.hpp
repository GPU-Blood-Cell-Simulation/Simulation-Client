#pragma once

#include "config_data.hpp"
#include "../vein/nodes/node.hpp"

#include <string>

namespace serializable
{
	class ConfigManager
	{
	public:
		void loadBloodCellConfig();
		void saveBloodCellConfig() const;

		void loadVeinConfig();
		void saveVeinConfig() const;

		void loadGeneralConfig();
		void saveGeneralConfig() const;

		ConfigData& getData();
		void serializeAllToCpp() const;

	private:
		ConfigData data;
	};
}
