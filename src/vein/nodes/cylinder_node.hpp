#pragma once

#include "../../defines.hpp"
#include "node.hpp"
#include "../vein_generator.hpp"

namespace vein
{
	class CylinderNode : public Node
	{
	public:
		CylinderNode(Node* parent, bool isLeft = true, int vLayers = cyl::vLayers);

		virtual void renderGUI(gui::GUIController& guiController) override;
		virtual void addToMesh(TempMesh& finalMesh, unsigned int parentLeftBranchIndicesEnd, unsigned int parentRightBranchIndicesEnd,
			bool parentIsBifurcation) const override;

	protected:
		virtual const std::string getFullName() const override;

		int vLayers;
	};
}