#pragma once

#include "light.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>


/// <summary>
/// A wrapper class for GLSL shaders. heavily inspired by https://learnopengl.com/Getting-started/Shaders
/// </summary>
class Shader
{
public:
    // the program ID
    unsigned int ID;
    // use/activate the shader
    virtual ~Shader() = default;
    virtual void use();
    // utility uniform functions
    void setFloat(const char* name, float value) const;
    void setInt(const char* name, int value) const;
    void setVector(const char* name, glm::vec3 vector) const;
    void setMatrix(const char* name, glm::mat4 matrix) const;
    void setLighting(DirLight dirLight) const;
protected:
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
};


/// <summary>
/// Vein color shader
/// </summary>
class VeinSolidColorShader : public Shader
{
public:
    VeinSolidColorShader();
};