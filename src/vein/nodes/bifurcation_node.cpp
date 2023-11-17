#include "bifurcation_node.hpp"
#include "../vein_generator.hpp"

namespace vein
{
	BifurcationNode::BifurcationNode() : Node(VeinGenerator().createBifurcation(glm::pi<float>() * 1.0f / 5.0f, glm::pi<float>() * 1.0f / 7.0f))
	{}

	void BifurcationNode::draw(Shader* shader) const
	{
		mesh.draw(shader);

		if (left)
		{
			left->draw(shader);
		}
		if (right)
		{
			right->draw(shader);
		}
	}
}