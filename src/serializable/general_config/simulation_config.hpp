#pragma once

#include "../cpp_serializable.hpp"
#include "../util/nameof.hpp"

#include <nlohmann/json.hpp>

namespace serializable
{
	using json = nlohmann::json;

	/// <summary>
	/// Holds general simulation parameters
	/// </summary>
	struct SimulationConfig : public ICppSerializable
	{
		const static int framerate = 30;
		float simulationTime = 20;	// Simulation time in seconds
		int maxCudaStreams = 16;
		float dt = 0.008f;

		bool useBloodFlow = true;
		bool enableReactionForce = true;

		// uniform grid cell count
		int cellWidth = 3;
		int cellHeight = 3;
		int cellDepth = 3;

		// represents ratio of radius of maximal and actual bounding sphere
		// for particles in cells
		int boundingSpheresCoeff = 3;
		float gridMargin = 40.0f;

		float minSpawnY = -20;

		virtual void serializeToCpp() const override;
	};

	inline void to_json(json& j, const SimulationConfig& o)
	{
		j = json{
			{nameof(o.dt), o.dt},
			{nameof(o.useBloodFlow), o.useBloodFlow},
			{nameof(o.enableReactionForce), o.enableReactionForce},
			{nameof(o.cellWidth), o.cellWidth},
			{nameof(o.cellHeight), o.cellHeight},
			{nameof(o.cellDepth), o.cellDepth},
			{nameof(o.boundingSpheresCoeff), o.boundingSpheresCoeff},
			{nameof(o.gridMargin), o.gridMargin},
			{nameof(o.minSpawnY), o.minSpawnY}
		};
	}

	inline void from_json(const json& j, SimulationConfig& o)
	{
		j.at(nameof(o.dt)).get_to(o.dt);
		j.at(nameof(o.useBloodFlow)).get_to(o.useBloodFlow);
		j.at(nameof(o.enableReactionForce)).get_to(o.enableReactionForce);
		j.at(nameof(o.cellWidth)).get_to(o.cellWidth);
		j.at(nameof(o.cellHeight)).get_to(o.cellHeight);
		j.at(nameof(o.cellDepth)).get_to(o.cellDepth);
		j.at(nameof(o.boundingSpheresCoeff)).get_to(o.boundingSpheresCoeff);
		j.at(nameof(o.gridMargin)).get_to(o.gridMargin);
		j.at(nameof(o.minSpawnY)).get_to(o.minSpawnY);
	}
}