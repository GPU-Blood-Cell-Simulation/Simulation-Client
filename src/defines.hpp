#pragma once

#include <glm/vec3.hpp>
#include <string>

inline int VEIN_POLYGON_MODE = 0;

// Window size
inline constexpr int windowWidth = 800;
inline constexpr int windowHeight = 800;

// Camera movement constants
inline constexpr float cameraMovementSpeedCoefficient = 0.01f;
inline constexpr float cameraRotationSpeed = 0.02f;

// Simulation dimensions
// TODO: calculate automatically from vein definition
inline constexpr float width = 300.0f;
inline constexpr float height = 500.0f;
inline constexpr float depth = 300.0f;

// Serialization
inline const std::string cppSerializationPath =
#ifdef _WIN32
 	"SimulationGeneratedConfig/";
#else
	"../SimulationGeneratedConfig/";
#endif

inline const std::string veinCppSerializationPath = cppSerializationPath + "vein_definition.hpp";
inline const std::string bloodCellsDefinitionCppSerializationPath = cppSerializationPath + "blood_cells_definition.hpp";
inline const std::string bloodCellPresetsCppSerializationPath = cppSerializationPath + "blood_cell_presets.hpp";
inline const std::string graphicsCppSerializationPath = cppSerializationPath + "graphics.hpp";
inline const std::string physicsCppSerializationPath = cppSerializationPath + "physics.hpp";
inline const std::string simulationCppSerializationPath = cppSerializationPath + "simulation.hpp";

inline const std::string cppConfigDataPath =
#ifdef _WIN32
 	"SimulationConfigData/";
#else
	"../SimulationConfigData/";
#endif

inline const std::string veinDefinitionConfigDataPath = cppConfigDataPath + "template_vein_definition.hpp";
inline const std::string bloodCellsDefinitionConfigDataPath = cppConfigDataPath + "template_blood_cells_definition.hpp";
inline const std::string bloodCellPresetsConfigDataPath = cppConfigDataPath + "template_blood_cell_presets.hpp";

// cylinder model data:

namespace vein
{
	// bifurcation segment (1/3)
	namespace bif
	{
		inline constexpr float veinHeight = 100;
		inline constexpr float veinRadius = 50;
		inline constexpr int vLayers = 20;
		inline constexpr int hLayers = 100;
		inline constexpr int segmentVertexCount = vLayers * hLayers;
	}

	namespace cyl
	{
		inline constexpr float triangleHeight = 5;
		inline constexpr float veinRadius = 50;
		inline constexpr int vLayers = 50;
		inline constexpr int hLayers = 100;
	}
}