#include "spring_lines.hpp"


#include <glad/glad.h>
#include <initializer_list>

namespace graphics
{
	SpringLines::SpringLines(unsigned int VBO, const serializable::BloodCellsDefinition& bloodCellsDefinition) :
		bloodCellTypeCount(bloodCellsDefinition.bloodCellTypes.size()), VAOs(bloodCellTypeCount)
	{
		int accumulatedParticles = 0;
		// For each type
		for (int i = 0; i < bloodCellTypeCount; i++)
		{
			indexData.emplace_back(std::initializer_list<unsigned int>{0});
			auto&& bloodCellType = bloodCellsDefinition.bloodCellTypes[i];
			// Create index data template (EBO for a particle with given type)
			for (int j = 0; j < bloodCellType.springs.size(); j++)
			{
				auto&& spring = bloodCellType.springs[j];
				indexData[i].push_back(accumulatedParticles + spring.start);
				indexData[i].push_back(accumulatedParticles + spring.end);
			}

			// Multiply the index data for other particles of the same type
			int indexDataSize = indexData[i].size();
			for (int j = 1; j < bloodCellType.count; j++)
			{
				for (int k = 0; k < indexDataSize; k++)
				{
					indexData[i].push_back(j * bloodCellType.particlesInCell + indexData[i][k]);
				}
			}
			accumulatedParticles += bloodCellType.count * bloodCellType.particlesInCell;

			// setup VAO and EBO (VBO is shared with cuda-mapped position buffer
			glGenVertexArrays(1, &VAOs[i]);
			glBindVertexArray(VAOs[i]);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData[i].size() * sizeof(unsigned int), indexData[i].data(), GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

		}
	}

	// TODO : double check if this doesn't leave any memory leaks
	SpringLines::~SpringLines()
	{
		// clean up the EBO
		glBindVertexArray(VAOs[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDeleteBuffers(1, &EBO);
		glBindVertexArray(0);

		// delete VAOs
		for (int i = 0; i < bloodCellTypeCount; i++)
		{
			glDeleteVertexArrays(1, &VAOs[i]);
		}
	}

	void SpringLines::draw(const Shader* shader) const
	{
		for (int i = 0; i < bloodCellTypeCount; i++)
		{
			glBindVertexArray(VAOs[i]);
			glDrawElements(GL_LINES, static_cast<GLsizei>(indexData[i].size()), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);				
		}
	}
}