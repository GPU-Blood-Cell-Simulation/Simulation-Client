#include "blood_cells_model.hpp"

#include <glad/glad.h>

namespace graphics
{
    BloodCellsModel::BloodCellsModel(serializable::BloodCellsDefinition definition) : Model("Models/Earth/low_poly_earth.fbx"), definition(definition)
    {
        // Set up offset buffer for the model
        glGenBuffers(1, &cudaOffsetBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, cudaOffsetBuffer);
        glBufferData(GL_ARRAY_BUFFER, definition.getParticleCount() * sizeof(glm::vec3), NULL, GL_DYNAMIC_DRAW);
    }

    BloodCellsModel::~BloodCellsModel()
    {
        glDeleteBuffers(1, &cudaOffsetBuffer);
    }

    unsigned int BloodCellsModel::getCudaOffsetBuffer()
    {
        return cudaOffsetBuffer;
    }

    void BloodCellsModel::draw(const Shader* shader) const
    {
        Model::draw(shader, true, definition.getParticleCount());
    }
}
