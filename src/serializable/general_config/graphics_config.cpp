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
		os << "inline int VEIN_POLYGON_MODE = 0;\ninline bool BLOOD_CELL_SPRINGS_RENDER = true;\n\n";
		os << "inline constexpr bool useLighting = " << (useLighting ? "true" : "false") << ";\n\n";
		os << "inline constexpr int windowWidth = 800;\ninline constexpr int windowHeight = 800;\n\n";

		os << "inline constexpr float cameraMovementSpeedCoefficient = " << cameraMovementSpeedCoefficient << ";\n";
		os << "inline constexpr float cameraRotationSpeed = " << cameraRotationSpeed << ";\n";

		if (!os)
			throw FileWriteException();
	}
}