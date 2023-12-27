#pragma once

#include "node.hpp"
#include "../vein_generator.hpp"

namespace vein
{
	class BifurcationNode : public Node
	{
	public:
		BifurcationNode(Node* parent, float leftRotation, float rightRotation, bool isLeft = true);

		virtual void renderGUI(gui::GUIController& guiController) override;
		virtual void addToMesh(TempMesh& finalMesh, unsigned int parentLeftBranchLastRowStart, unsigned int parentRightBranchLastRowStart,
			bool parentIsBifurcation) const override;

	protected:
		virtual const std::string getFullName() const override;
	};
}