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

		/// <summary>
		/// Constructor from json
		/// </summary>
		/// <param name="j">A json describing this node and its children (if present)</param>
		RootNode(const json& j);

		RootNode(const RootNode&) = delete;
		RootNode(RootNode&&) = default;
		RootNode& operator=(const RootNode&) = delete;
		RootNode& operator=(RootNode&&) = default;

		inline static const std::string type = "root";

		/// <summary>
		/// Renders a button in a tree-like hierarchy in the ImGui window
		/// </summary>
		/// <param name="guiController">The GUIController instance</param>
		/// <param name="width">the window width at which the center of the button should be rendered</param>
		virtual void renderGUI(gui::GUIController& guiController, float width) override;

		/// <summary>
		/// Initializes the final mash
		/// </summary>
		/// <param name="finalMesh">The final mesh that this node will append to</param>
		/// <param name="parentLeftBranchLastRowStart">The starting index of the parent's left branch's last row</param>
		/// <param name="parentRightBranchLastRowStart">The starting index of the parent's right branch's last row</param>
		/// <param name="parentIsBifurcation">Whether the parent is a bifurcation (has two endings)</param>
		virtual void addToMesh(SerializableMesh& finalMesh, unsigned int parentLeftBranchLastRowStart, unsigned int parentRightBranchLastRowStart,
			bool parentIsBifurcation) const override;

		/// <summary>
		/// Generate a json sub-object containing the information needed to reconstruct this node and its child (if present) recursively
		/// </summary>
		/// <returns>A json object</returns>
		virtual json generateJson() const override;
	};
}