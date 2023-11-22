#include "../gui_controller.hpp"

#include "../../vein/nodes/bifurcation_node.hpp"
#include "../../vein/nodes/cylinder_node.hpp"

namespace gui
{
	void GUIController::renderAddVein()
	{
		ImGui::Text("Vein parameter selection");

		static int segmentType = 0;

		ImGui::RadioButton("Cylinder segment", &segmentType, 0);
		ImGui::SameLine(); ImGui::RadioButton("Bifurcation segment", &segmentType, 1);

		static float angleLeftDeg = 45;
		static float angleRightDeg = 45;

		if (segmentType == 0) // cylinder segment
		{

		}
		else // bifurcation segment
		{
			ImGui::SliderFloat("left branch angle", &angleLeftDeg, 0.0f, 90.0f);
			ImGui::SliderFloat("right branch angle", &angleRightDeg, 0.0f, 90.0f);
		}

		if (ImGui::Button("Cancel"))
		{
			setMode(Mode::veinEdit);
		} 
		ImGui::SameLine();
		if (ImGui::Button("Add"))
		{
			if (segmentType == 0)
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
			else
			{
				float angleLeftRad = glm::pi<float>() * angleLeftDeg / 180.0f;
				float angleRightRad = glm::pi<float>() * angleRightDeg / 180.0f;

				if (selectedLeft)
				{
					selectedNode->left = std::make_unique<vein::BifurcationNode>(vein::BifurcationNode(selectedNode, - angleLeftRad, angleRightRad, true));
				}
				else
				{
					selectedNode->right = std::make_unique<vein::BifurcationNode>(vein::BifurcationNode(selectedNode, - angleLeftRad, angleRightRad, false));
				}
			}
			
			setMode(Mode::veinEdit);
		}
	}
}