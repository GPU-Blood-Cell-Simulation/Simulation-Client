#pragma once

#include "blood_cells_definition.hpp"
#include "general_config/physics_config.hpp"
#include "general_config/simulation_config.hpp"
#include "vein_definition.hpp"

namespace serializable
{
	using json = nlohmann::json;

	struct ConfigData
	{
		BloodCellsDefinition bloodCellsDefinition;
		PhysicsConfig physicsConfig;
		SimulationConfig simulationConfig;
		VeinDefinition veinDefinition;
	};

	inline void to_json(json& j, const ConfigData& o)
	{
		j = json{ {"bloodCells", o.bloodCellsDefinition}, {"physics", o.physicsConfig}, {"simulation", o.simulationConfig}, {"vein", o.veinDefinition} };
	}

	inline void from_json(const json& j, ConfigData& o)
	{
		j.at("bloodCells").get_to(o.bloodCellsDefinition);
		j.at("physics").get_to(o.physicsConfig);
		j.at("simulation").get_to(o.simulationConfig);
		j.at("vein").get_to(o.veinDefinition);
	}
}
