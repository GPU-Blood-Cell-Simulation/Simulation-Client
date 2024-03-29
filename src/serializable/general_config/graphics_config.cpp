#include "graphics_config.hpp"

#include "../../defines.hpp"
#include "../exceptions.hpp"

#include <fstream>

namespace serializable
{
	void GraphicsConfig::serializeToCpp() const
	{
		std::ofstream os(graphicsCppSerializationPath);
		if (!os)
			throw FileOpenException();

		os << "#pragma once\n\n";
		os << "#include <string>\n\n";

		os << "inline int VEIN_POLYGON_MODE = 0;\ninline bool BLOOD_CELL_SPRINGS_RENDER = true;\ninline bool BLOOD_CELL_SPHERE_RENDER = false;\n\n";
		os << "inline constexpr bool useLighting = " << (useLighting ? "true" : "false") << ";\n\n";

		os << "inline constexpr float cameraMovementSpeedCoefficient = " << cameraMovementSpeedCoefficient << ";\n";
		os << "inline constexpr float cameraRotationSpeed = " << cameraRotationSpeed << ";\n\n";

		os << "inline constexpr int windowWidth = " << videoWidth << ";\n";
		os << "inline constexpr int windowHeight = " << videoHeight << ";\n\n";

		os << "inline constexpr bool saveVideoToFile = " << (saveVideoToFile ? "true" : "false") << ";\n";
		os << "inline std::string videoFileName = \"" << videoFileName << "\";\n";

		if (!os)
			throw FileWriteException();
	}
}