#pragma once

#include "../../graphics/shader.hpp"
#include "../vein_mesh.hpp"

#include <memory>

namespace vein
{
	class Node
	{
	public:
		Node(VeinMesh&& mesh) : mesh(mesh) {};

		virtual void draw(Shader* shader) const = 0;

	protected:
		VeinMesh mesh;

		std::unique_ptr<Node> parent;
	};
}