#pragma once

#include "../graphics/shader.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include <vector>

#include <iostream>

namespace vein
{
    struct TempMesh
    {
        TempMesh(std::vector<glm::vec3>&& positions, std::vector<unsigned int>&& indices) : positions(positions), indices(indices)
        {
            std::cout << "move\n";
        }

        std::vector<glm::vec3> positions;
        std::vector<unsigned int> indices;
    };


    class VeinMesh : public TempMesh {
    public:

        VeinMesh(std::vector<glm::vec3>&& positions, std::vector<unsigned int>&& indices);
        void draw(const Shader* shader) const;

    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();
    };
}