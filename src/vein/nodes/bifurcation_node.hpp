#pragma once

#include "node.hpp"
#include "../vein_generator.hpp"

namespace vein
{
	class BifurcationNode : public Node
	{
	public:
		BifurcationNode(Node* parent, float radiusLeft, float radiusRight, float leftRotation, float rightRotation, bool isLeft);

		virtual void renderGUI(gui::GUIController& guiController) override;
		virtual void addToMesh(TempMesh& finalMesh, unsigned int parentLeftBranchLastRowStart, unsigned int parentRightBranchLastRowStart,
			bool parentIsBifurcation) const override;

	protected:
		virtual std::string getFullName() const override;
	};
}