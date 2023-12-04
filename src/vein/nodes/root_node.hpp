#pragma once

#include "cylinder_node.hpp"
#include "../vein_generator.hpp"


namespace vein
{
	class RootNode : public CylinderNode
	{
	public:
		RootNode();

		virtual void renderGUI(gui::GUIController& guiController) override;
	};
}