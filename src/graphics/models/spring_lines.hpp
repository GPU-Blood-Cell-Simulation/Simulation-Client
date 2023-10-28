#pragma once

#include "../../serializable/blood_cells_definition.hpp"
#include "../shader.hpp"

#include <memory>
#include <vector>

namespace graphics
{
	class SpringLines
	{
	public:
		SpringLines(unsigned int VBO, const serializable::BloodCellsDefinition& bloodCellsDefinition);
		~SpringLines();
		void draw(const Shader* shader) const;
	private:
		int bloodCellTypeCount;
		std::vector<unsigned int> VAOs;
		unsigned int EBO;
		std::vector<std::vector<unsigned int>> indexData;
	};
}