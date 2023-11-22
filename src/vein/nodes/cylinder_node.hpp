#pragma once

#include "node.hpp"
#include "../vein_generator.hpp"

namespace vein
{
	class CylinderNode : public Node
	{
	public:
		CylinderNode(Node* parent, bool isLeft = true);

		virtual void renderGUI(gui::GUIController& guiController) override;

	protected:
		virtual const std::string getFullName() const override;
	};
}