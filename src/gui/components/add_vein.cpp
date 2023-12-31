#include "../gui_controller.hpp"

#include "../../defines.hpp"
#include "../../vein/nodes/bifurcation_node.hpp"
#include "../../vein/nodes/cylinder_node.hpp"

namespace gui
{
	static void recalculateCylinder(vein::Node* selectedNode, bool selectedLeft, float radius, int length, float skewRollDeg, float skewPitchDeg)
	{
		float skewRollRad = glm::pi<float>() * skewRollDeg / 180.0f;
		float skewPitchRad = glm::pi<float>() * skewPitchDeg / 180.0f;

		if (selectedLeft)
		{
			selectedNode->left.reset();
			selectedNode->left = std::make_unique<vein::CylinderNode>(selectedNode, radius, length, skewRollRad, skewPitchRad, true);
		}
		else
		{
			selectedNode->right.reset();
			selectedNode->right = std::make_unique<vein::CylinderNode>(selectedNode, radius, length, skewRollRad, skewPitchRad, false);
		}
	}

	static void recalculateBifurcation(vein::Node* selectedNode, bool selectedLeft, float radiusLeft, float radiusRight,
		float rollLeftDeg, float rollRightDeg, float pitchLeftDeg, float pitchRightDeg)
	{
		float rollLeftRad = glm::pi<float>() * rollLeftDeg / 180.0f;
		float rollRightRad = glm::pi<float>() * rollRightDeg / 180.0f;
		float pitchLeftRad = glm::pi<float>() * pitchLeftDeg / 180.0f;
		float pitchRightRad = glm::pi<float>() * pitchRightDeg / 180.0f;

		if (selectedLeft)
		{
			selectedNode->left.reset();
			selectedNode->left = std::make_unique<vein::BifurcationNode>(selectedNode, radiusLeft, radiusRight,
				rollLeftRad, rollRightRad, pitchLeftRad, pitchRightRad,  true);
		}
		else
		{
			selectedNode->right.reset();
			selectedNode->right = std::make_unique<vein::BifurcationNode>(selectedNode, radiusLeft, radiusRight,
				rollLeftRad, rollRightRad, pitchLeftRad, pitchRightRad, false);
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
		static float cylSkewRollDeg = 0;
		static float cylSkewPitchDeg = 0;

		// Bifurcation
		static float rollLeftDeg = -45;
		static float rollRightDeg = 45;
		static float pitchLeftDeg = 0;
		static float pitchRightDeg = 0;
		static float bifRadiusLeft = vein::bif::veinRadius;
		static float bifRadiusRight = vein::bif::veinRadius; 

		// First time mesh creation
		if (firstRender)
		{
			if (segmentType == 0)
			{
				recalculateCylinder(selectedNode, selectedLeft, cylRadius, length, cylSkewRollDeg, cylSkewPitchDeg);
			}
			else
			{		
				recalculateBifurcation(selectedNode, selectedLeft, bifRadiusLeft, bifRadiusRight,
					rollLeftDeg, rollRightDeg, pitchLeftDeg, pitchRightDeg);
			}
			firstRender = false;
		}

		ImGui::Text("Vein parameter selection");

		cylinderChanged |= ImGui::RadioButton("Cylinder segment", &segmentType, 0);
		ImGui::SameLine();
		bifurcationChanged |= ImGui::RadioButton("Bifurcation segment", &segmentType, 1);
		
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
			cylinderChanged |= ImGui::SliderFloat("Skew - Roll [deg]", &cylSkewRollDeg, -90.0f, 90.0f);
			cylinderChanged |= ImGui::SliderFloat("Skew - Pitch [deg]", &cylSkewPitchDeg, -90.0f, 90.0f);
			cylinderChanged |= ImGui::SliderFloat("Segment end radius", &cylRadius, vein::cyl::veinRadius / 3, vein::cyl::veinRadius * 3);
		}
		else // bifurcation segment
		{
			bifurcationChanged |= ImGui::SliderFloat("Left branch roll angle [deg]", &rollLeftDeg, -90.0f, 0.0f);
			bifurcationChanged |= ImGui::SliderFloat("Left branch pitch angle [deg]", &pitchLeftDeg, -45.0f, 45.0f);
			bifurcationChanged |= ImGui::SliderFloat("Left branch radius", &bifRadiusLeft, vein::bif::veinRadius / 3, vein::bif::veinRadius * 3);
			ImGui::NewLine();
			bifurcationChanged |= ImGui::SliderFloat("Right branch roll angle [deg]", &rollRightDeg, 0.0f, 90.0f);
			bifurcationChanged |= ImGui::SliderFloat("Right branch pitch angle [deg]", &pitchRightDeg, -45.0f, 45.0f);
			bifurcationChanged |= ImGui::SliderFloat("Right branch radius", &bifRadiusRight, vein::bif::veinRadius / 3, vein::bif::veinRadius * 3);
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
			recalculateCylinder(selectedNode, selectedLeft, cylRadius, length, cylSkewRollDeg, cylSkewPitchDeg);
			return;
		}

		if (bifurcationChanged)
		{
			recalculateBifurcation(selectedNode, selectedLeft, bifRadiusLeft, bifRadiusRight,
				rollLeftDeg, rollRightDeg, pitchLeftDeg, pitchRightDeg);
			return;
		}
	}
}