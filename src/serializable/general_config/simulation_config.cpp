#include "simulation_config.hpp"

#include "../../defines.hpp"
#include "../exceptions.hpp"

#include <fstream>

namespace serializable
{
	void SimulationConfig::serializeToCpp() const
	{
		std::ofstream os(simulationCppSerializationPath);
		if (!os)
			throw FileOpenException();

		os << "#pragma once\n\n";
		os << "inline constexpr int maxFrames = " << maxFrames << ";\n";
		os << "inline constexpr int maxCudaStreams = 16;\n";
		os << "inline constexpr float dt = " << dt << ";\n";
		os << "inline constexpr bool useBloodFlow = " << useBloodFlow << ";\n";
		os << "inline constexpr bool enableReactionForce = " << enableReactionForce << ";\n\n";

		os << "inline constexpr int cellWidth = " << cellWidth << ";\n";
		os << "inline constexpr int cellHeight = " << cellHeight << ";\n";
		os << "inline constexpr int cellDepth  = " << cellDepth << ";\n\n";

		os << "inline constexpr int boundingSpheresCoeff = " << boundingSpheresCoeff << ";\n";
		os << "inline constexpr float gridYMargin = " << gridMargin << ";\n";
		os << "inline constexpr float gridXZMargin  = " << gridMargin << ";\n";
		os << "inline constexpr float minSpawnY = " << minSpawnY << ";\n";

		if (!os)
			throw FileWriteException();
	}
}