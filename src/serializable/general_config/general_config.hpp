#pragma once

#include "graphics_config.hpp"
#include "physics_config.hpp"
#include "simulation_config.hpp"

namespace serializable
{
	using json = nlohmann::json;

	struct GeneralConfig : public ICppSerializable
	{
		SimulationConfig simulation;
		PhysicsConfig physics;
		GraphicsConfig graphics;

		inline virtual void serializeToCpp() const override
		{
			simulation.serializeToCpp();
			physics.serializeToCpp();
			graphics.serializeToCpp();
		}
	};

	inline void to_json(json& j, const GeneralConfig& o)
	{
		j = { {nameof(o.simulation), o.simulation}, {nameof(o.physics), o.physics}, {nameof(o.graphics), o.graphics} };
	}

	inline void from_json(const json& j, GeneralConfig& o)
	{
		j.at(nameof(o.simulation)).get_to(o.simulation);
		j.at(nameof(o.physics)).get_to(o.physics);
		j.at(nameof(o.graphics)).get_to(o.graphics);
	}
}