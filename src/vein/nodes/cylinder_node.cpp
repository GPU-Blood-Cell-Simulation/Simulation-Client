#include "cylinder_node.hpp"

#include "../../gui/gui_controller.hpp"
#include "../vein_generator.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui/imgui.h>

namespace vein
{
	CylinderNode::CylinderNode(Node* parent, float radius, int vLayers, float skewRoll, float skewPitch, bool isLeft) :
		Node(parent, std::move(VeinGenerator::createCylinder
			(
			parent == nullptr ? cyl::veinRadius : (isLeft ? parent->leftBranchRadius : parent->rightBranchRadius),
			radius, vLayers, skewRoll, skewPitch
			)
		), radius, radius, isLeft),
		radius(radius), vLayers(vLayers), skewRoll(skewRoll), skewPitch(skewPitch)
	{
		// Root node
		if (!parent)
		{
			leftEndCenter = rightEndCenter = {0, -cyl::vLayers * cyl::triangleHeight + cyl::triangleHeight , 0};
			mesh.setupMesh();
			return;
		}

		// Calculate vein segment rotation and translation
		auto& parentQuat = isLeft ? parent->leftQuat : parent->rightQuat;
		auto rotation = glm::toMat4(parentQuat) * glm::toMat4(glm::quat(glm::vec3(skewPitch, 0, skewRoll)));
		leftQuat = rightQuat = glm::toQuat(rotation);

		auto translation = isLeft ? parent->leftEndCenter : parent->rightEndCenter;
		model = glm::translate(glm::mat4(1.0f), translation) * glm::toMat4(parentQuat);

		auto dist = mesh.positions[mesh.positions.size() - 1] - mesh.positions[mesh.positions.size() - 1 - cyl::hLayers/2];
		leftEndCenter = rightEndCenter = model * glm::vec4(
			mesh.positions[mesh.positions.size() - 1 - cyl::hLayers/2] + dist * 0.5f,
			1.0f);

		mesh.setupMesh();
	}

	void CylinderNode::renderGUI(gui::GUIController& guiController, float width)
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

	void CylinderNode::addToMesh(TempMesh& finalMesh, unsigned int parentLeftBranchLastRowStart, unsigned int parentRightBranchLastRowStart,
		bool parentIsBifurcation) const
	{
		unsigned int positionsInitialSize = finalMesh.positions.size();
		// Copy positions
		finalMesh.positions.reserve(positionsInitialSize + (vLayers - 1) * cyl::hLayers);
		std::transform(mesh.positions.cbegin() + cyl::hLayers, mesh.positions.cend(), std::back_inserter(finalMesh.positions), [&](auto&& position)
			{
				return model * glm::vec4(position, 1.0f);
			});

		// Swap the first row of indices to glue the two meshes together
		finalMesh.indices.reserve(finalMesh.indices.size() + 6 * (vLayers - 1) * cyl::hLayers);
		int previousMeshLastRowStart = isLeft ? parentLeftBranchLastRowStart : parentRightBranchLastRowStart;
		if (parentIsBifurcation)
		{
			for (int j = 0; j < bif::hLayers / 2; j++)
			{
				int nextj = j + 1;
				finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 2 - j);
				finalMesh.indices.push_back(previousMeshLastRowStart + j);
				finalMesh.indices.push_back(previousMeshLastRowStart + nextj);
				finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 2 - j);
				finalMesh.indices.push_back(previousMeshLastRowStart + nextj);
				finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 2 - nextj);
			}

			finalMesh.indices.push_back(positionsInitialSize);
			finalMesh.indices.push_back(previousMeshLastRowStart + bif::hLayers / 2);
			finalMesh.indices.push_back(previousMeshLastRowStart + bif::hLayers / 2 + 1);
			finalMesh.indices.push_back(positionsInitialSize);
			finalMesh.indices.push_back(previousMeshLastRowStart + bif::hLayers / 2 + 1);
			finalMesh.indices.push_back(positionsInitialSize + bif::hLayers - 1);

			for (int j = 1; j < bif::hLayers / 2 - 1; j++)
			{
				int nextj = j + 1;
				finalMesh.indices.push_back(positionsInitialSize + bif::hLayers - j);
				finalMesh.indices.push_back(previousMeshLastRowStart + bif::hLayers / 2 + j);
				finalMesh.indices.push_back(previousMeshLastRowStart + bif::hLayers / 2 + nextj);
				finalMesh.indices.push_back(positionsInitialSize + bif::hLayers - j);
				finalMesh.indices.push_back(previousMeshLastRowStart + bif::hLayers / 2 + nextj);
				finalMesh.indices.push_back(positionsInitialSize + bif::hLayers - nextj);
			}

			finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 2);
			finalMesh.indices.push_back(previousMeshLastRowStart + bif::hLayers - 1);
			finalMesh.indices.push_back(previousMeshLastRowStart);
			finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 2);
			finalMesh.indices.push_back(previousMeshLastRowStart);
			finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 2 + 1);
		}
		else
		{
			for (int j = 0; j < bif::hLayers; j++)
			{
				int nextj = (j + 1) % bif::hLayers;
				finalMesh.indices.push_back(positionsInitialSize + j);
				finalMesh.indices.push_back(previousMeshLastRowStart + j);
				finalMesh.indices.push_back(previousMeshLastRowStart + nextj);
				finalMesh.indices.push_back(positionsInitialSize + j);
				finalMesh.indices.push_back(previousMeshLastRowStart + nextj);
				finalMesh.indices.push_back(positionsInitialSize + nextj);
			}
		}

		// Copy next rows of indices
		std::transform(mesh.indices.cbegin() + 6 * cyl::hLayers, mesh.indices.cend(), std::back_inserter(finalMesh.indices), [&](auto&& index)
			{
				return index + positionsInitialSize - cyl::hLayers;
			});

		// Recurse
		if (left)
		{
			unsigned int thisSegmentLastRowStart = positionsInitialSize + (vLayers - 2) * cyl::hLayers;
			left->addToMesh(finalMesh, thisSegmentLastRowStart, thisSegmentLastRowStart);
		}
	}

	std::string CylinderNode::getFullName() const
	{
		return "Cylinder\nid: " + std::to_string(id);
	}

	json CylinderNode::generateJson() const
	{
		auto&& [leftJson, rightJson] = generateLeftAndRightJson();
		return json{ {nameof(type),type}, {nameof(radius), radius}, {nameof(vLayers), vLayers},
			{nameof(skewRoll), skewRoll}, {nameof(skewPitch), skewPitch}, leftJson, rightJson };
	}
}