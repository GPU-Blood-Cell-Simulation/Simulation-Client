#pragma once

#include "blood_cell_json_conversion/blood_cells_definition.hpp"
#include "general_config/general_config.hpp"
#include "../vein/nodes/root_node.hpp"

namespace serializable
{
	struct ConfigData
	{
		GeneralConfig generalConfig;
		BloodCellsDefinition bloodCellsDefinition;	
		std::unique_ptr<vein::Node> veinRootNode = std::make_unique<vein::RootNode>();
	};
}
