#pragma once

#include "../cpp_serializable.hpp"

#include <nlohmann/json.hpp>

namespace serializable
{
	using json = nlohmann::json;

	struct SimulationConfig : public ICppSerializable
	{
		int maxCudaStreams = 16;
		float dt = 0.1f;	

		// uniform grid cell count
		int cellWidth = 20;
		int cellHeight = 20;
		int cellDepth = 20;

		virtual void serializeToCpp() const override {}
	};

	inline void to_json(json& j, const SimulationConfig& o)
	{
		j = json{ {nameof(o.dt), o.dt}, {nameof(o.cellWidth), o.cellWidth}, {nameof(o.cellHeight), o.cellHeight}, {nameof(o.cellDepth), o.cellDepth} };
	}

	inline void from_json(const json& j, SimulationConfig& o)
	{
		j.at(nameof(o.dt)).get_to(o.dt);
		j.at(nameof(o.cellWidth)).get_to(o.cellWidth);
		j.at(nameof(o.cellHeight)).get_to(o.cellHeight);
		j.at(nameof(o.cellDepth)).get_to(o.cellDepth);
	}
}