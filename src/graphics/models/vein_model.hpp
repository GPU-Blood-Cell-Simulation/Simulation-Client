#pragma once

#include "model.hpp"
#include "../../serializable/vein_definition.hpp"

namespace graphics
{
	class VeinModel : public Model
	{
	public:
		VeinModel(const serializable::VeinDefinition& veinDefinition);
		~VeinModel();
		unsigned int getCudaOffsetBuffer() const;
		void draw(const Shader* shader) const;

	private:
		serializable::VeinDefinition definition;
		// Array of translation vectors for each instance - cuda writes to this
		unsigned int cudaOffsetBuffer;
	};
}