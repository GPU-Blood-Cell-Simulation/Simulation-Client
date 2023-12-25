#include "../gui_controller.hpp"

#include "../../vein/nodes/bifurcation_node.hpp"
#include "../../vein/nodes/cylinder_node.hpp"

namespace gui
{
	static void recalculateCylinder(vein::Node* selectedNode, bool selectedLeft)
	{
		if (selectedLeft)
		{
			selectedNode->left = std::make_unique<vein::CylinderNode>(vein::CylinderNode(selectedNode, true));
		}
		else
		{
			selectedNode->right = std::make_unique<vein::CylinderNode>(vein::CylinderNode(selectedNode, false));
		}
	}

	static void recalculateBifurcation(vein::Node* selectedNode, bool selectedLeft, float angleLeftDeg, float angleRightDeg)
	{
		float angleLeftRad = glm::pi<float>() * angleLeftDeg / 180.0f;
		float angleRightRad = glm::pi<float>() * angleRightDeg / 180.0f;
		if (selectedLeft)
		{
			selectedNode->left = std::make_unique<vein::BifurcationNode>(vein::BifurcationNode(selectedNode, -angleLeftRad, angleRightRad, true));
		}
		else
		{
			selectedNode->right = std::make_unique<vein::BifurcationNode>(vein::BifurcationNode(selectedNode, -angleLeftRad, angleRightRad, false));
		}
	}

	void GUIController::renderAddVein()
	{
		static int segmentType = 0;
		static float angleLeftDeg = 45;
		static float angleRightDeg = 45;
		bool cylinderChanged = false;
		bool bifurcationChanged = false;

		// First time mesh creation
		if (firstRender)
		{
			if (segmentType == 0)
			{
				recalculateCylinder(selectedNode, selectedLeft);
			}
			else
			{		
				recalculateBifurcation(selectedNode, selectedLeft, angleLeftDeg, angleRightDeg);
			}
			firstRender = false;
		}

		ImGui::Text("Vein parameter selection");

		if (ImGui::RadioButton("Cylinder segment", &segmentType, 0))
		{
			cylinderChanged = true;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Bifurcation segment", &segmentType, 1))
		{
			bifurcationChanged = true;
		}
		
		if (segmentType == 0) // cylinder segment
		{
			// TODO: cylinder height etc.
		}
		else // bifurcation segment
		{
			if (ImGui::SliderFloat("left branch angle", &angleLeftDeg, 0.0f, 90.0f) ||
				ImGui::SliderFloat("right branch angle", &angleRightDeg, 0.0f, 90.0f))
			{
				bifurcationChanged = true;
			}
		}

		if (ImGui::Button("Cancel"))
		{
			if (selectedLeft)
				selectedNode->left.reset(nullptr);
			else
				selectedNode->right.reset(nullptr);
			setMode(Mode::veinEdit);
		} 
		ImGui::SameLine();
		if (ImGui::Button("Save"))
		{
			setMode(Mode::veinEdit);
		}

		// Recalculate nodes based on changes
		if (cylinderChanged)
		{
			recalculateCylinder(selectedNode, selectedLeft);
			return;
		}

		if (bifurcationChanged)
		{
			recalculateBifurcation(selectedNode, selectedLeft, angleLeftDeg, angleRightDeg);
			return;
		}
	}
}