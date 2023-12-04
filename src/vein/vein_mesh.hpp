#pragma once

#include "../graphics/shader.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include <vector>

#include <iostream>

namespace vein
{
    class TempMesh
    {
    public:
        TempMesh(std::vector<glm::vec3>&& positions, std::vector<unsigned int>&& indices);

        TempMesh(std::vector<glm::vec3>&& positions, const std::vector<unsigned int>& indices);

        std::vector<glm::vec3> positions;
        std::vector<unsigned int> indices;
    };


    class VeinMesh : public TempMesh {
    public:

        VeinMesh(std::vector<glm::vec3>&& positions, std::vector<unsigned int>&& indices);
        VeinMesh(std::vector<glm::vec3>&& positions, const std::vector<unsigned int>& indices);
        ~VeinMesh();

        void setupMesh();
        void draw(const Shader* shader) const;

    private:
        //  render data
        unsigned int VAO = 0, VBO = 0, EBO = 0;
    };
}