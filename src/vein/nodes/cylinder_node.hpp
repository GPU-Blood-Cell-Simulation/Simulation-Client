#pragma once

#include "../../defines.hpp"
#include "node.hpp"
#include "../vein_generator.hpp"

namespace vein
{
	class CylinderNode : public Node
	{
	public:
		CylinderNode(Node* parent, float radius, int vLayers, bool isLeft = true);

		virtual void renderGUI(gui::GUIController& guiController) override;
		virtual void addToMesh(TempMesh& finalMesh, unsigned int parentLeftBranchIndicesEnd, unsigned int parentRightBranchIndicesEnd,
			bool parentIsBifurcation) const override;

	protected:
		virtual std::string getFullName() const override;

		int vLayers;
	};
}