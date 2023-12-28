#include "root_node.hpp"

#include "../../gui/gui_controller.hpp"
#include "../vein_generator.hpp"

namespace vein
{
	RootNode::RootNode() :
		CylinderNode(nullptr, cyl::veinRadius, cyl::vLayers)
	{}

	void RootNode::renderGUI(gui::GUIController& guiController)
	{
		if (ImGui::Button(getFullName().c_str()))
		{
			if (!left)
				ImGui::OpenPopup(getPopupName().c_str());
		}

		if (ImGui::BeginPopup(getPopupName().c_str()))
		{
			if (ImGui::Selectable("Add segment"))
			{
				guiController.setMode(gui::Mode::addVein);
				guiController.selectNode(this);
			}
			ImGui::EndPopup();
		}

	}

	void RootNode::addToMesh(TempMesh& finalMesh, unsigned int parentLeftBranchLastRowStart, unsigned int parentRightBranchLastRowStart,
		bool parentIsBifurcation) const
	{
		finalMesh.positions = mesh.positions;
		finalMesh.indices = mesh.indices;

		// Recurse
		if (left)
		{
			unsigned int thisSegmentLastRowStart = finalMesh.positions.size() - cyl::hLayers;
			left->addToMesh(finalMesh, thisSegmentLastRowStart, thisSegmentLastRowStart);
		}
	}
}