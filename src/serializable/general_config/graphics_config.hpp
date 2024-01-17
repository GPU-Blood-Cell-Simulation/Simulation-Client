#pragma once

#include "../cpp_serializable.hpp"
#include "../util/nameof.hpp"

#include <string>

#include <nlohmann/json.hpp>

namespace serializable
{
	using json = nlohmann::json;

	/// <summary>
	/// Holds parameters related to displaying the simulation
	/// </summary>
	struct GraphicsConfig : public ICppSerializable
	{
		bool useLighting = true;
		float cameraMovementSpeedCoefficient = 0.01f;
		float cameraRotationSpeed = 0.02f;

		int videoWidth = 800;
		int videoHeight = 800;

		bool saveVideoToFile = true;
		char videoFileName[256] = "blood_simulation.mov";

		virtual void serializeToCpp() const override;
	};

	inline void to_json(json& j, const GraphicsConfig& o)
	{
		j = json{
			{nameof(o.useLighting), o.useLighting},
			{nameof(o.cameraMovementSpeedCoefficient), o.cameraMovementSpeedCoefficient},
			{nameof(o.cameraRotationSpeed), o.cameraRotationSpeed},
			{nameof(o.videoWidth), o.videoWidth},
			{nameof(o.videoHeight), o.videoHeight},
			{nameof(o.saveVideoToFile), o.saveVideoToFile},
			{nameof(o.videoFileName), o.videoFileName}
		};
	}

	inline void from_json(const json& j, GraphicsConfig& o)
	{
		std::string videoFileName;

		j.at(nameof(o.useLighting)).get_to(o.useLighting);
		j.at(nameof(o.cameraMovementSpeedCoefficient)).get_to(o.cameraMovementSpeedCoefficient);
		j.at(nameof(o.cameraRotationSpeed)).get_to(o.cameraRotationSpeed);
		j.at(nameof(o.videoWidth)).get_to(o.videoWidth);
		j.at(nameof(o.videoHeight)).get_to(o.videoHeight);
		j.at(nameof(o.saveVideoToFile)).get_to(o.saveVideoToFile);
		j.at(nameof(o.videoFileName)).get_to(videoFileName);


		strcpy(o.videoFileName, videoFileName.c_str());
	}
}