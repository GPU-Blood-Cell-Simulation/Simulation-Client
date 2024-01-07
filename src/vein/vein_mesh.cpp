#include "vein_mesh.hpp"

#include "../defines.hpp"
#include "../serializable/exceptions.hpp"
#include "../serializable/util/vec_to_string.hpp"

#include <glad/glad.h>
#include <fstream>
#include <memory>

namespace vein
{
	TempMesh::TempMesh(std::vector<glm::vec3>&& positions, std::vector<unsigned int>&& indices) : positions(positions), indices(indices)
	{}

	TempMesh::TempMesh(std::vector<glm::vec3>&& positions, const std::vector<unsigned int>& indices) : positions(positions), indices(indices)
	{}

	VeinMesh::VeinMesh(std::vector<glm::vec3>&& positions, std::vector<unsigned int>&& indices) :
		TempMesh(std::move(positions), std::move(indices))
	{}

	VeinMesh::VeinMesh(std::vector<glm::vec3>&& positions, const std::vector<unsigned int>& indices) :
		TempMesh(std::move(positions), indices)
	{}

	VeinMesh::~VeinMesh()
	{
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glDeleteBuffers(1, &VBO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDeleteBuffers(1, &EBO);

		glDeleteVertexArrays(1, &VAO);
		glBindVertexArray(0);
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

	void SerializableMesh::serializeToCpp() const
	{	
		std::ifstream is(veinDefinitionConfigDataPath);
		std::ofstream os(veinCppSerializationPath);
		if (!is || !os)
			throw serializable::FileOpenException();

		os << is.rdbuf();
		if (!is)
			throw serializable::FileReadException();

		int veinPositionCount = positions.size();

		// serialize positions
		os << "\n";
		os << "inline constexpr std::array<cvec, " << veinPositionCount << "> veinPositions {\n";
		for (int i = 0; i < veinPositionCount - 1; i++)
		{
			os << positions[i] << ",\n";
		}
		if (veinPositionCount > 0)
		{
			os << positions[veinPositionCount - 1] << "\n";
		}
		os << "};\n\n";

		// serialize indices
		int indexCount = indices.size();
		os << "inline constexpr std::array<unsigned int, " << indexCount << "> veinIndices {\n";
		for (int i = 0; i < indexCount - 6; i+= 6)
		{
			for (int j = 0; j < 5; j++)
			{
				os << indices[i + j] << ", ";
			}
			os << indices[i + 5] << ",\n";
		}
		if (veinPositionCount > 0)
		{
			for (int j = 0; j < 5; j++)
			{
				os << indices[indexCount - 6 + j] << ", ";
			}
			os << indices[indexCount - 1] << "\n";
		}
		os << "};\n\n";

		// Serialize vein ending centers
		os << "using VeinEndingCenters = mp_list<\n";
		for (int i = 0; i < endingPositions.size() - 1; i++)
		{
			auto&& pos = endingPositions[i];
			os << "mp_float3<" << static_cast<int>(pos.x * 1000) << ", " << static_cast<int>(pos.y * 1000) << ", "
				<< static_cast<int>(pos.z * 1000) << ", 4>,\n";
		}
		if (endingPositions.size() > 0)
		{
			auto&& pos = endingPositions[endingPositions.size() - 1];
			os << "mp_float3<" << static_cast<int>(pos.x * 1000) << ", " << static_cast<int>(pos.y * 1000) << ", "
				<< static_cast<int>(pos.z * 1000) << ", 4>\n";
		}
		os << ">;\n\n";

		// Serialize vein ending radii
		os << "using VeinEndingRadii = mp_list<\n";
		for (int i = 0; i < endingRadii.size() - 1; i++)
		{
			float radius = endingRadii[i];
			os << "mp_float<" << static_cast<int>(radius * 1000) << ", 4>,\n";
		}
		if (endingRadii.size() > 0)
		{
			auto&& radius = endingRadii[endingRadii.size() - 1];
			os << "mp_float<" << static_cast<int>(radius * 1000) << ", 4>\n";
		}
		os << ">;";

		if (!os)
			throw serializable::FileWriteException();
	}

	void SerializableMesh::addEnding(const glm::vec3& endingPosition, float endingRadius)
	{
		endingPositions.push_back(endingPosition);
		endingRadii.push_back(endingRadius);
	}
}
