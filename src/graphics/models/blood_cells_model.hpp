#pragma once

#include "model.hpp"
#include "../../serializable/blood_cells_definition.hpp"

namespace graphics
{
	class BloodCellsModel : public Model
	{
	public:
		BloodCellsModel(serializable::BloodCellsDefinition definition);
		~BloodCellsModel();
		unsigned int getCudaOffsetBuffer();
		void draw(const Shader* shader) const;

	private:
		serializable::BloodCellsDefinition definition;
		// Array of translation vectors for each instance - cuda writes to this
		unsigned int cudaOffsetBuffer;
	};
}