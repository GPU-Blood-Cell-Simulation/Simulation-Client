#pragma once

#include "node.hpp"
#include "../vein_generator.hpp"

namespace vein
{
	class BifurcationNode : public Node
	{
	public:
		BifurcationNode();

		virtual void draw(Shader* shader) const override;

	protected:
		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;
	};
}