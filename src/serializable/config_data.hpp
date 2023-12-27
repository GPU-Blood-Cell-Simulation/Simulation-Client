#pragma once

#include "blood_cells_definition.hpp"
#include "general_config/physics_config.hpp"
#include "general_config/simulation_config.hpp"
#include "vein_definition.hpp"

namespace serializable
{
	struct ConfigData
	{
		BloodCellsDefinition bloodCellsDefinition;
		PhysicsConfig physicsConfig;
		SimulationConfig simulationConfig;
		VeinDefinition veinDefinition;
	};
}
