#include "bifurcation_node.hpp"

#include "../../gui/gui_controller.hpp"
#include "../vein_generator.hpp"

namespace vein
{
	BifurcationNode::BifurcationNode(Node* parent, float leftRotation, float rightRotation, bool isLeft) :
		Node(parent, std::move(VeinGenerator::getInstance().createBifurcation(leftRotation, rightRotation)), isLeft)
	{
		if (isLeft)
		{
			leftBranchAngle = parent->leftBranchAngle + leftRotation;
			rightBranchAngle = parent->leftBranchAngle + rightRotation;
		}
		else
		{
			leftBranchAngle = parent->rightBranchAngle + leftRotation;
			rightBranchAngle = parent->rightBranchAngle + rightRotation;
		}

		glm::vec3 bifurcationHeightOffset = { 0, - mesh.positions[bif::vLayers * bif::hLayers - 1].y, 0 };
		auto translation = isLeft ? parent->leftEndCenter : parent->rightEndCenter;
		translation += bifurcationHeightOffset;
		float angle = isLeft ? - parent->leftBranchAngle : parent->rightBranchAngle;

		mesh.tranfsorm(translation, angle);

		// TODO : remember to change this when removing duplicated vertices is implemented
		auto distLeftBranch = mesh.positions[2 * bif::segmentVertexCount - 1] - mesh.positions[2 * bif::segmentVertexCount - 1 - bif::hLayers / 2];
		leftEndCenter = mesh.positions[2 * bif::segmentVertexCount - 1 - bif::hLayers / 2] + distLeftBranch * 0.5f;

		auto distRightBranch = mesh.positions[mesh.positions.size() - 1] - mesh.positions[mesh.positions.size() - 1 - bif::hLayers / 2];
		rightEndCenter = mesh.positions[mesh.positions.size() - 1 - bif::hLayers / 2] + distRightBranch * 0.5f;

		mesh.setupMesh();
	}

	void BifurcationNode::renderGUI(gui::GUIController& guiController)
	{
		if (ImGui::Button(getFullName().c_str()))
		{
			ImGui::OpenPopup(popupName.c_str());
		}

		if (ImGui::BeginPopup(popupName.c_str()))
		{
			if (!left)
			{
				if (ImGui::Selectable("Add left branch"))
				{
					guiController.setMode(gui::Mode::addVein);
					guiController.selectNode(this, true);
				}
			}

			if (!right)
			{
				if (ImGui::Selectable("Add right branch"))
				{
					guiController.setMode(gui::Mode::addVein);
					guiController.selectNode(this, false);
				}
			}
			
			if (ImGui::Selectable("Delete"))
			{
				parent->markChildrenToBeDeleted(isLeft);
			}
			ImGui::EndPopup();
		}
	}
	const std::string BifurcationNode::getFullName() const
	{
		return std::format("Bifurcation node\nid: {}", id);
	}
}