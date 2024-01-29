#pragma once

#include <glm/vec3.hpp>


/// <summary>
/// A struct representing a light source in OpenGL
/// </summary>
struct Light
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

/// <summary>
/// A struct representing a directional light source in OpenGL
/// </summary>
struct DirLight : public Light
{
    glm::vec3 direction;
};