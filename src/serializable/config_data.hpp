#pragma once

#include "blood_cell_json_conversion/blood_cells_definition.hpp"
#include "general_config/general_config.hpp"
#include "../vein/nodes/root_node.hpp"

/// <summary>
/// This namespace contains objects that can be serialized and classes/functions that provide the functionality to do so
/// </summary>
namespace serializable
{
	/// <summary>
	/// Holds the entire config data
	/// </summary>
	struct ConfigData
	{
		GeneralConfig generalConfig;
		BloodCellsDefinition bloodCellsDefinition;	
		std::unique_ptr<vein::Node> veinRootNode = std::make_unique<vein::RootNode>();
	};
}
