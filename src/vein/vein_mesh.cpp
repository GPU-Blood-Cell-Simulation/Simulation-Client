#include "vein_mesh.hpp"

#include <glad/glad.h>
#include <memory>


namespace vein
{
	TempMesh::TempMesh(std::vector<glm::vec3>&& positions, std::vector<unsigned int>&& indices) : positions(positions), indices(indices)
	{}

	TempMesh::TempMesh(std::vector<glm::vec3>&& positions, const std::vector<unsigned int>& indices) : positions(positions), indices(indices)
	{}

	void TempMesh::tranfsorm(glm::vec3 translation, float angle)
	{
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1));
		for (auto&& position : positions)
		{
			position = rotation * glm::vec4(position, 1.0f);
			position += translation;
		}
	}

	VeinMesh::VeinMesh(std::vector<glm::vec3>&& positions, std::vector<unsigned int>&& indices) :
		TempMesh(std::move(positions), std::move(indices)) {}

	VeinMesh::VeinMesh(std::vector<glm::vec3>&& positions, const std::vector<unsigned int>& indices) :
		TempMesh(std::move(positions), indices) {}

	VeinMesh::~VeinMesh()
	{
		// TODO: clean up openGL memory
	}

	void VeinMesh::setupMesh()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), &positions[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int),
			&indices[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

		glBindVertexArray(0);
	}

	void VeinMesh::draw(const Shader* shader) const
	{
		// draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
