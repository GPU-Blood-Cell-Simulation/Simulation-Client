#pragma once

#include "blood_cell_json_conversion/blood_cells_definition.hpp"
#include "general_config/physics_config.hpp"
#include "general_config/simulation_config.hpp"
#include "../vein/nodes/root_node.hpp"

namespace serializable
{
	struct ConfigData
	{
		BloodCellsDefinition bloodCellsDefinition;
		PhysicsConfig physicsConfig;
		SimulationConfig simulationConfig;
		std::unique_ptr<vein::Node> veinRootNode = std::make_unique<vein::RootNode>();
	};
}
