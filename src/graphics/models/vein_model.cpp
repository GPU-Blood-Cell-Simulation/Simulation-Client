#include "vein_model.hpp"

#include "../../simulation/vein_calculation.hpp"

#include <glad/glad.h>

namespace graphics
{
	VeinModel::VeinModel(const serializable::VeinDefinition& veinDefinition) : Model(sim::createVeinMesh(veinDefinition)), definition(veinDefinition)
	{
		// Set up offset buffer for the model
		glGenBuffers(1, &cudaOffsetBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, cudaOffsetBuffer);
		glBufferData(GL_ARRAY_BUFFER, meshes[0].vertices.size() * sizeof(glm::vec3), NULL, GL_DYNAMIC_DRAW);
	}

	VeinModel::~VeinModel()
	{
		glDeleteBuffers(1, &cudaOffsetBuffer);
	}

	unsigned int VeinModel::getCudaOffsetBuffer() const
	{
		return cudaOffsetBuffer;
	}

	void VeinModel::draw(const Shader* shader) const
	{
		Model::draw(shader, false);
	}
}


