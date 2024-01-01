#pragma once

#include "../graphics/shader.hpp"
#include "../serializable/cpp_serializable.hpp"

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
        virtual ~TempMesh() {}

        std::vector<glm::vec3> positions;
        std::vector<unsigned int> indices;
    protected:
        TempMesh() {}
    };

    class VeinMesh : public TempMesh {
    public:
        VeinMesh(std::vector<glm::vec3>&& positions, std::vector<unsigned int>&& indices);
        VeinMesh(std::vector<glm::vec3>&& positions, const std::vector<unsigned int>& indices);
        virtual ~VeinMesh() override;

        // constructors needed for json serialization
        VeinMesh() = default;
        VeinMesh(const VeinMesh&) = default;
        VeinMesh(VeinMesh&&) = default;
        VeinMesh& operator=(const VeinMesh&) = default;
        VeinMesh& operator=(VeinMesh&&) = default;

        void setupMesh();
        void draw(const Shader* shader) const;

    private:
        //  render data
        unsigned int VAO = 0, VBO = 0, EBO = 0;
    };

    class SerializableMesh : public TempMesh, public serializable::ICppSerializable
    {
    public:
        SerializableMesh() {}

        virtual void serializeToCpp() const override;
    };
}