#include "../gui_controller.hpp"

#include "../../defines.hpp"
#include "../../vein/nodes/bifurcation_node.hpp"
#include "../../vein/nodes/cylinder_node.hpp"

namespace gui
{
	static void recalculateCylinder(vein::Node* selectedNode, bool selectedLeft, int length)
	{
		if (selectedLeft)
		{
			selectedNode->left = std::make_unique<vein::CylinderNode>(vein::CylinderNode(selectedNode, length, true));
		}
		else
		{
			selectedNode->right = std::make_unique<vein::CylinderNode>(vein::CylinderNode(selectedNode, length, false));
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
		bool cylinderChanged = false;
		bool bifurcationChanged = false;
		static int segmentType = 0;

		// Cylinder
		static int length = vein::cyl::vLayers;

		// Bifurcation
		static float angleLeftDeg = 45;
		static float angleRightDeg = 45;

		// First time mesh creation
		if (firstRender)
		{
			if (segmentType == 0)
			{
				recalculateCylinder(selectedNode, selectedLeft, length);
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
			if (ImGui::InputInt(" Segment length ", &length))
			{
				cylinderChanged = true;
			}

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
			recalculateCylinder(selectedNode, selectedLeft, length);
			return;
		}

		if (bifurcationChanged)
		{
			recalculateBifurcation(selectedNode, selectedLeft, angleLeftDeg, angleRightDeg);
			return;
		}
	}
}