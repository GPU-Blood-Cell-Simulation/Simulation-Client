#include "cylinder_node.hpp"

#include "../../gui/gui_controller.hpp"
#include "../vein_generator.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui/imgui.h>

namespace vein
{
	CylinderNode::CylinderNode(Node* parent, bool isLeft, int vLayers) :
		Node(parent, std::move(VeinGenerator::getInstance().createCylinder()), isLeft), vLayers(vLayers)
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

	const std::string CylinderNode::getFullName() const
	{
		return std::format("Cylinder node\nid: {}", id);
	}
}