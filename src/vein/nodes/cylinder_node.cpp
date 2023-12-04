#include "cylinder_node.hpp"

#include "../../gui/gui_controller.hpp"
#include "../vein_generator.hpp"

#include <imgui/imgui/imgui.h>

namespace vein
{
	CylinderNode::CylinderNode(Node* parent, bool isLeft) :
		Node(parent, std::move(VeinGenerator::getInstance().createCylinder()), isLeft)
	{
		// Root node
		if (!parent)
		{
			leftBranchAngle = rightBranchAngle = 0;
			leftEndCenter = rightEndCenter = {0, -cyl::veinHeight + cyl::veinHeight / cyl::vLayers , 0};
			model = glm::identity<glm::mat4>();
			mesh.setupMesh();
			return;
		}

		// Calculate vein segment rotation and translation
		float angle = isLeft ? parent->leftBranchAngle : parent->rightBranchAngle;
		leftBranchAngle = rightBranchAngle = angle;
		auto translation = isLeft ? parent->leftEndCenter : parent->rightEndCenter;
		model = glm::rotate(glm::translate(glm::mat4(1.0f), translation), angle, glm::vec3(0, 0, 1));

		auto dist = mesh.positions[mesh.positions.size() - 1] - mesh.positions[mesh.positions.size() - 1 - cyl::hLayers/2];
		leftEndCenter = rightEndCenter = model * glm::vec4(
			mesh.positions[mesh.positions.size() - 1 - cyl::hLayers/2] + dist * 0.5f,
			1.0f);

		mesh.setupMesh();
	}

	void CylinderNode::renderGUI(gui::GUIController& guiController)
	{
		if (ImGui::Button(getFullName().c_str()))
		{
			ImGui::OpenPopup(popupName.c_str());
		}

		if (ImGui::BeginPopup(popupName.c_str()))
		{
			if (!left)
			{
				if (ImGui::Selectable("Add segment"))
				{
					guiController.setMode(gui::Mode::addVein);
					guiController.selectNode(this);
				}
			}
	
			if (ImGui::Selectable("Delete"))
			{
				parent->markChildrenToBeDeleted(isLeft);
			}
			ImGui::EndPopup();
		}
	}

	const std::string CylinderNode::getFullName() const
	{
		return std::format("Cylinder node\nid: {}", id);
	}
}