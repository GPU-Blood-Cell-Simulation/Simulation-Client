#pragma once

#include "../cpp_serializable.hpp"
#include "../util/nameof.hpp"

#include <nlohmann/json.hpp>

namespace serializable
{
	using json = nlohmann::json;

	/// <summary>
	/// Holds parameters related to displaying the simulation
	/// </summary>
	struct GraphicsConfig : public ICppSerializable
	{
		bool useLighting;
		float cameraMovementSpeedCoefficient = 0.01f;
		float cameraRotationSpeed = 0.02f;

		virtual void serializeToCpp() const override;
	};

	inline void to_json(json& j, const GraphicsConfig& o)
	{
		j = json{ {nameof(o.useLighting), o.useLighting},
			{nameof(o.cameraMovementSpeedCoefficient), o.cameraMovementSpeedCoefficient},
			{nameof(o.cameraRotationSpeed), o.cameraRotationSpeed}
		};
	}

	inline void from_json(const json& j, GraphicsConfig& o)
	{
		j.at(nameof(o.useLighting)).get_to(o.useLighting);
		j.at(nameof(o.cameraMovementSpeedCoefficient)).get_to(o.cameraMovementSpeedCoefficient);
		j.at(nameof(o.cameraRotationSpeed)).get_to(o.cameraRotationSpeed);
	}
}