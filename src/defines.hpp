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
inline constexpr float cylinderHeight = 0.8 * height;
inline constexpr float cylinderRadius = 0.2 * width;
inline glm::vec3 cylinderBaseCenter = glm::vec3(width / 2.0f, 0.1f * height, depth / 2.0f);
inline constexpr int cylinderVerticalLayers = 100;
inline constexpr int cylinderHorizontalLayers = 30;

inline constexpr int veinHeight = static_cast<int>(cylinderHeight);
inline constexpr int veinRadius = static_cast<int>(cylinderRadius);