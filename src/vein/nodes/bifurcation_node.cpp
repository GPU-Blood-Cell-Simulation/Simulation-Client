#include "bifurcation_node.hpp"

#include "../../gui/gui_controller.hpp"
#include "../vein_generator.hpp"


namespace vein
{
	BifurcationNode::BifurcationNode(Node* parent, float radiusLeft, float radiusRight, float leftYaw, float rightYaw, bool isLeft) :
		Node(parent, std::move(VeinGenerator::createBifurcation
		(
			parent == nullptr ? bif::veinRadius : (isLeft ? parent->leftBranchRadius : parent->rightBranchRadius),
			radiusLeft, radiusRight, leftYaw, rightYaw
		)
		), radiusLeft, radiusRight, isLeft),
		radiusLeft(radiusLeft), radiusRight(radiusRight), leftYaw(leftYaw), rightYaw(rightYaw)
	{
		if (isLeft)
		{
			leftBranchYaw = parent->leftBranchYaw + leftYaw;
			rightBranchYaw = parent->leftBranchYaw + rightYaw;
			leftBranchPitch = parent->leftBranchPitch;
			rightBranchPitch = parent->leftBranchPitch;
		}
		else
		{
			leftBranchYaw = parent->rightBranchYaw + leftYaw;
			rightBranchYaw = parent->rightBranchYaw + rightYaw;
			leftBranchPitch = parent->rightBranchPitch;
			rightBranchPitch = parent->rightBranchPitch;
		}

		glm::vec3 bifurcationHeightOffset = { 0, - mesh.positions[bif::vLayers * bif::hLayers - 1].y, 0 };
		auto translation = isLeft ? parent->leftEndCenter : parent->rightEndCenter;
		float yawAngle = isLeft ? parent->leftBranchYaw : parent->rightBranchYaw;
		float pitchAngle = isLeft ? parent->leftBranchPitch : parent->rightBranchPitch;
		translation += glm::vec3(
			glm::rotate(glm::mat4(1.0f), pitchAngle, glm::vec3(1, 0, 0)) *
			glm::rotate(glm::mat4(1.0f), yawAngle, glm::vec3(0, 0, 1)) *
			glm::vec4(bifurcationHeightOffset, 1.0f)
		);
		setupModelMatrix(translation, yawAngle, pitchAngle);

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

	json BifurcationNode::generateJson() const
	{
		auto&& [leftJson, rightJson] = generateLeftAndRightJson();
		return json{ {nameof(type), type}, {nameof(radiusLeft), radiusLeft}, {nameof(radiusRight), radiusRight},
			{nameof(leftYaw), leftYaw}, {nameof(rightYaw), rightYaw}, leftJson, rightJson };
	}
}