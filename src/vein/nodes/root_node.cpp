#include "root_node.hpp"

#include "../../gui/gui_controller.hpp"
#include "../vein_generator.hpp"

namespace vein
{
	RootNode::RootNode() :
		CylinderNode(nullptr, cyl::veinRadius, cyl::vLayers, 0, 0)
	{}

	void RootNode::renderGUI(gui::GUIController& guiController, float width)
	{
		ImGui::SetCursorPosX(width - buttonWidth / 2);
		if (ImGui::Button(getFullName().c_str(), ImVec2(buttonWidth, buttonHeight)))
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

	void RootNode::addToMesh(SerializableMesh& finalMesh, unsigned int parentLeftBranchLastRowStart, unsigned int parentRightBranchLastRowStart,
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
		else
		{
			finalMesh.addEnding(leftEndCenter, leftBranchRadius);
		}
	}

	json RootNode::generateJson() const
	{
		auto&& [leftJson, rightJson] = generateLeftAndRightJson();
		return json{ {nameof(type), type}, leftJson, rightJson};
	}
}