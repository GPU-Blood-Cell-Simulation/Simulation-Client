#include "../gui_controller.hpp"

#include "../../defines.hpp"
#include "../../vein/nodes/bifurcation_node.hpp"
#include "../../vein/nodes/cylinder_node.hpp"

namespace gui
{
	static void recalculateCylinder(vein::Node* selectedNode, bool selectedLeft, float radius, int length, float skewDeg)
	{
		float skewRad = glm::pi<float>() * skewDeg / 180.0f;

		if (selectedLeft)
		{
			selectedNode->left.reset();
			selectedNode->left = std::make_unique<vein::CylinderNode>(selectedNode, radius, length, skewRad, true);
		}
		else
		{
			selectedNode->right.reset();
			selectedNode->right = std::make_unique<vein::CylinderNode>(selectedNode, radius, length, skewRad, false);
		}
	}

	static void recalculateBifurcation(vein::Node* selectedNode, bool selectedLeft, float radiusLeft, float radiusRight, float angleLeftDeg, float angleRightDeg)
	{
		float angleLeftRad = glm::pi<float>() * angleLeftDeg / 180.0f;
		float angleRightRad = glm::pi<float>() * angleRightDeg / 180.0f;

		if (selectedLeft)
		{
			selectedNode->left.reset();
			selectedNode->left = std::make_unique<vein::BifurcationNode>(selectedNode, radiusLeft, radiusRight, -angleLeftRad, angleRightRad, true);
		}
		else
		{
			selectedNode->right.reset();
			selectedNode->right = std::make_unique<vein::BifurcationNode>(selectedNode, radiusLeft, radiusRight, -angleLeftRad, angleRightRad, false);
		}
	}

	void GUIController::renderAddVein()
	{
		bool cylinderChanged = false;
		bool bifurcationChanged = false;
		static int segmentType = 0;

		// Cylinder
		static int length = vein::cyl::vLayers;
		static float cylRadius = vein::cyl::veinRadius; 
		static float cylSkewDeg = 0;

		// Bifurcation
		static float angleLeftDeg = 45;
		static float angleRightDeg = 45;
		static float bifRadiusLeft = vein::bif::veinRadius;
		static float bifRadiusRight = vein::bif::veinRadius; 

		// First time mesh creation
		if (firstRender)
		{
			if (segmentType == 0)
			{
				recalculateCylinder(selectedNode, selectedLeft, cylRadius, length, cylSkewDeg);
			}
			else
			{		
				recalculateBifurcation(selectedNode, selectedLeft, bifRadiusLeft, bifRadiusRight, angleLeftDeg, angleRightDeg);
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
				if (length < 5)
					length = 5;
				if (length > 10000)
					length = 10000;

				cylinderChanged = true;
			}
			if (ImGui::SliderFloat("Segment end radius", &cylRadius, vein::cyl::veinRadius / 3, vein::cyl::veinRadius * 3) ||
				ImGui::SliderFloat("Skew [deg]", &cylSkewDeg, -90.0f, 90.0f))
			{
				cylinderChanged = true;
			}
		}
		else // bifurcation segment
		{
			if (ImGui::SliderFloat("left branch angle [deg]", &angleLeftDeg, 0.0f, 90.0f) ||
				ImGui::SliderFloat("right branch angle [deg]", &angleRightDeg, 0.0f, 90.0f) ||
				ImGui::SliderFloat("left branch radius", &bifRadiusLeft, vein::bif::veinRadius / 3, vein::bif::veinRadius * 3) ||
				ImGui::SliderFloat("right branch radius", &bifRadiusRight, vein::bif::veinRadius / 3, vein::bif::veinRadius * 3))
			{
				bifurcationChanged = true;
			}
		}

		if (ImGui::Button("Cancel"))
		{
			if (selectedLeft)
				selectedNode->left.reset();
			else
				selectedNode->right.reset();
				
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
			recalculateCylinder(selectedNode, selectedLeft, cylRadius, length, cylSkewDeg);
			return;
		}

		if (bifurcationChanged)
		{
			recalculateBifurcation(selectedNode, selectedLeft, bifRadiusLeft, bifRadiusRight, angleLeftDeg, angleRightDeg);
			return;
		}
	}
}