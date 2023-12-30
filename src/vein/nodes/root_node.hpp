#pragma once

#include "cylinder_node.hpp"
#include "../vein_generator.hpp"


namespace vein
{
	class RootNode : public CylinderNode
	{
	public:
		RootNode();
		RootNode(const json& j);

		RootNode(const RootNode&) = delete;
		RootNode(RootNode&&) = default;
		RootNode& operator=(const RootNode&) = delete;
		RootNode& operator=(RootNode&&) = default;

		inline static const std::string type = "root";

		virtual void renderGUI(gui::GUIController& guiController) override;
		virtual void addToMesh(TempMesh& finalMesh, unsigned int parentLeftBranchLastRowStart, unsigned int parentRightBranchLastRowStart,
			bool parentIsBifurcation) const override;
		virtual json generateJson() const override;
	};
}