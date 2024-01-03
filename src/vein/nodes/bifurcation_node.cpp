#include "bifurcation_node.hpp"

#include "../../gui/gui_controller.hpp"
#include "../vein_generator.hpp"


namespace vein
{
	BifurcationNode::BifurcationNode(Node* parent, float radiusLeft, float radiusRight,
		float leftRoll, float rightRoll, float leftPitch, float rightPitch, bool isLeft) :
		Node(parent, std::move(VeinGenerator::createBifurcation
		(
			parent == nullptr ? bif::veinRadius : (isLeft ? parent->leftBranchRadius : parent->rightBranchRadius),
			radiusLeft, radiusRight, leftRoll, rightRoll, leftPitch, rightPitch
		)
		), radiusLeft, radiusRight, isLeft),
		radiusLeft(radiusLeft), radiusRight(radiusRight), leftRoll(leftRoll), rightRoll(rightRoll), leftPitch(leftPitch), rightPitch(rightPitch)
	{
		auto& parentQuat = isLeft ? parent->leftQuat : parent->rightQuat;
		auto rotationLeft = glm::toMat4(parentQuat) * glm::toMat4(quat(glm::vec3(-leftPitch, 0, leftRoll)));
		auto rotationRight = glm::toMat4(parentQuat) * glm::toMat4(quat(glm::vec3(-rightPitch, 0, rightRoll)));

		leftQuat = glm::toQuat(rotationLeft);
		rightQuat = glm::toQuat(rotationRight);

		glm::vec3 bifurcationHeightOffset = { 0, - mesh.positions[bif::vLayers * bif::hLayers - 1].y, 0 };
		auto translation = isLeft ? parent->leftEndCenter : parent->rightEndCenter;
		translation += glm::vec3(glm::toMat4(parentQuat) * glm::vec4(bifurcationHeightOffset, 1.0f));

		model = glm::translate(glm::mat4(1.0f), translation) * glm::toMat4(parentQuat);

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

	void BifurcationNode::renderGUI(gui::GUIController& guiController, float width)
	{
		ImGui::SetCursorPosX(width - buttonWidth / 2);
		if (ImGui::Button(getFullName().c_str(), ImVec2(buttonWidth, buttonHeight)))
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
		return "Bifurcation\nid: " + std::to_string(id);
	}

	json BifurcationNode::generateJson() const
	{
		auto&& [leftJson, rightJson] = generateLeftAndRightJson();
		return json{ {nameof(type), type}, {nameof(radiusLeft), radiusLeft}, {nameof(radiusRight), radiusRight},
			{nameof(leftRoll), leftRoll}, {nameof(rightRoll), rightRoll},
			{nameof(leftPitch), leftPitch}, {nameof(rightPitch), rightPitch},
			leftJson, rightJson };
	}

	float BifurcationNode::leftChildButtonOffset() const
	{
		return -ImGui::GetWindowWidth() / (2 << level);
	}
	float BifurcationNode::rightChildButtonOffset() const
	{
		return ImGui::GetWindowWidth() / (2 << level);
	}
}