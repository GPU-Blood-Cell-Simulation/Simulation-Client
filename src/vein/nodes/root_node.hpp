#pragma once

#include "cylinder_node.hpp"
#include "../vein_generator.hpp"


namespace vein
{
	/// <summary>
	/// A special cylinder node that is always present at the top (and only there). Cannot be deleted.
	/// </summary>
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

		virtual void renderGUI(gui::GUIController& guiController, float width) override;
		virtual void addToMesh(TempMesh& finalMesh, unsigned int parentLeftBranchLastRowStart, unsigned int parentRightBranchLastRowStart,
			bool parentIsBifurcation) const override;
		virtual json generateJson() const override;
	};
}