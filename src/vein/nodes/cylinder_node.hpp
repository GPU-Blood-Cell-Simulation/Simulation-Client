#pragma once

#include "../../defines.hpp"
#include "node.hpp"
#include "../vein_generator.hpp"

namespace vein
{
	class CylinderNode : public Node
	{
	public:
		CylinderNode(Node* parent, float radius, int vLayers, float skewRoll, float skewPitch, bool isLeft = true);
		CylinderNode(Node* parent, const json& j, bool isLeft = true);

		CylinderNode() = default;
		CylinderNode(const CylinderNode&) = delete;
		CylinderNode(CylinderNode&&) = default;
		CylinderNode& operator=(const CylinderNode&) = delete;
		CylinderNode& operator=(CylinderNode&&) = default;

		inline static const std::string type = "cylinder";

		virtual void renderGUI(gui::GUIController& guiController) override;
		virtual void addToMesh(TempMesh& finalMesh, unsigned int parentLeftBranchIndicesEnd, unsigned int parentRightBranchIndicesEnd,
			bool parentIsBifurcation) const override;
		virtual json generateJson() const override;

	protected:
		virtual std::string getFullName() const override;

		float radius;
		int vLayers;
		float skewRoll;
		float skewPitch;
	};
}