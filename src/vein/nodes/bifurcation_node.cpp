#include "bifurcation_node.hpp"

#include "../../gui/gui_controller.hpp"
#include "../vein_generator.hpp"


namespace vein
{
	BifurcationNode::BifurcationNode(Node* parent, float radiusLeft, float radiusRight, float leftRotation, float rightRotation, bool isLeft) :
		Node(parent, std::move(VeinGenerator::getInstance().createBifurcation
		(
			parent == nullptr ? bif::veinRadius : (isLeft ? parent->leftBranchRadius : parent->rightBranchRadius),
			radiusLeft, radiusRight, leftRotation, rightRotation
		)
		), radiusLeft, radiusRight, isLeft)
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
		float angle = isLeft ? parent->leftBranchAngle : parent->rightBranchAngle;
		translation += glm::vec3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1)) * glm::vec4(bifurcationHeightOffset, 1.0f));
		model = glm::rotate(glm::translate(glm::mat4(1.0f), translation), angle, glm::vec3(0, 0, 1));

		auto distLeftBranch = mesh.positions[2 * bif::segmentVertexCount - 1] - mesh.positions[2 * bif::segmentVertexCount - 1 - bif::hLayers / 2];
		leftEndCenter = model * glm::vec4(
			mesh.positions[2 * bif::segmentVertexCount - 1 - bif::hLayers / 2] + distLeftBranch * 0.5f,
			1.0f);

		auto distRightBranch = mesh.positions[mesh.positions.size() - 1] - mesh.positions[mesh.positions.size() - 1 - bif::hLayers / 2];
		rightEndCenter = model * glm::vec4(
			mesh.positions[mesh.positions.size() - 1 - bif::hLayers / 2] + distRightBranch * 0.5f,
			1.0f);

		mesh.setupMesh();
	}

	void BifurcationNode::renderGUI(gui::GUIController& guiController)
	{
		if (ImGui::Button(getFullName().c_str()))
		{
			ImGui::OpenPopup(getPopupName().c_str());
		}

		if (ImGui::BeginPopup(getPopupName().c_str()))
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

	std::string BifurcationNode::getFullName() const
	{
		return "Bifurcation node\nid: " + std::to_string(id);
	}
}