#pragma once

#include <nlohmann/json.hpp>

namespace serializable
{
	using json = nlohmann::json;

	struct SimulationConfig
	{
		int maxCudaStreams = 16;
		float dt = 0.1f;	

		// uniform grid cell count
		int cellWidth = 20;
		int cellHeight = 20;
		int cellDepth = 20;
	};

	inline void to_json(json& j, const SimulationConfig& o)
	{
		j = json{ {"cellWidth", o.cellWidth}, {"cellHeight", o.cellHeight}, {"cellDepth", o.cellDepth} };
	}

	inline void from_json(const json& j, SimulationConfig& o)
	{
		j.at("cellWidth").get_to(o.cellWidth);
		j.at("cellHeight").get_to(o.cellHeight);
		j.at("cellDepth").get_to(o.cellDepth);
	}
}