#include "root_node.hpp"

#include "../../gui/gui_controller.hpp"
#include "../vein_generator.hpp"

namespace vein
{
	RootNode::RootNode() :
		CylinderNode(nullptr)
	{}

	void RootNode::renderGUI(gui::GUIController& guiController)
	{
		if (ImGui::Button(getFullName().c_str()))
		{
			if (!left)
				ImGui::OpenPopup(popupName.c_str());
		}

		if (ImGui::BeginPopup(popupName.c_str()))
		{
			if (ImGui::Selectable("Add segment"))
			{
				guiController.setMode(gui::Mode::addVein);
				guiController.selectNode(this);
			}
			ImGui::EndPopup();
		}

	}
}