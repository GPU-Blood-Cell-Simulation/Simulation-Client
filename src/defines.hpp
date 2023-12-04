#pragma once

#include <glm/vec3.hpp>

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
		inline constexpr float veinHeight = 300;
		inline constexpr float veinRadius = 50;
		inline constexpr int vLayers = 50;
		inline constexpr int hLayers = 100;
	}
}